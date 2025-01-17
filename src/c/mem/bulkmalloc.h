/****************************************************************************************

	File:		bulkmalloc.h
	Why:		Functions for bulk dynamic memory handling.
	OS:			C99
	Author:		Thomas
	Created:	2021-07-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-07-29	Thomas			Created.

****************************************************************************************/

/*
	Simple module for providing dynamically allocated bulk memory (or memory pools;
	also called arenas). See
	https://en.wikipedia.org/wiki/Region-based_memory_management .
	
	The idea is to allocate a huge piece of heap memory and then gradually consume it instead
	of single malloc () calls.

	This module is not meant to replace fully-grown memory managers. A bulk memory block
	can only be deallocated as a whole. When the bulk memory block is exhausted, either
	new allocations fail or additional bulk blocks are allocated in a singly linked list.
	To keep performance high it is recommended to make the bulk blocks as big as
	required/reasonably possible to avoid the singly-link list from growing too big.
	
	None of the functions in this module/unit are thread-safe. In multi-threaded environments
	the caller is responsible for providing suitable locking mechanisms.

	For the user, the heart of a bulk memory list is the SBULKMEM structure. This structure
	serves as its plinth.
	
	To initialise an SBULKMEM structure when it is static or automatic, use the macro
	SBULKMEM_INITIALISER(). Otherwise call InitSBULKMEM () to initialise the structure.
	
	static SBULKMEM sbm	= SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_SIZE);

	To create an SBULKMEM structure on the heap and initialise it, call AllocInitSBULKMEM ().
	The function AllocInitSBULKMEM () initialises an already existing structure, or creates a
	new one on the heap, depending on its first parameter.

	Memory can then be requested with calls to GetMemFromSBULKMEM () or one of its wrappers.
	
	Example 1 (static SBULKMEM structure):

		#define OUR_BULK_DATA_ARRAY_SIZE	(100)

		SBULKMEM	sbulk	= SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_SIZE);
		void		*pData [OUR_BULK_DATA_ARRAY_SIZE];
		int			i;

		for (i = 0; i < OUR_BULK_DATA_ARRAY_SIZE; ++i)
		{
			pData [i] = GetMemFromSBULKMEM (&sbulk, 1024, 8, EN_SBULKMEM_CAN_GROW);
			if (pData [i])
			{
				memset (pData [i], 0xFF, 1024);
			}
		}
		DoneSBULKMEM (&sbulk);

	Example 2 (SBULKMEM structure on heap):

		#define OUR_BULK_DATA_ARRAY_SIZE	(100)
		SBULKMEM	*pBulk	= AllocInitSBULKMEM (NULL, DEFAULT_SBULKMEM_SIZE);
		if (pBulk)
		{
			void		*pData [OUR_BULK_DATA_ARRAY_SIZE];
			int			i;

			for (i = 0; i < OUR_BULK_DATA_ARRAY_SIZE; ++i)
			{
				pData [i] = GetMemFromSBULKMEM (&sbulk, 1024, 0, EN_SBULKMEM_CAN_GROW);
				if (pData [i])
				{
					memset (pData [i], 0xFF, 1024);
				}
			}
			DoneSBULKMEM (&sbulk);
		}

*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024, 2025 Thomas

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify,
	merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be included in all copies
	or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
	Builds support for the function popSBULKMEM ().
*/
#ifndef BUILD_POPSBULKMEM
//#define BUILD_POPSBULKMEM
#endif

#ifndef BULKMALLOC_H
#define BULKMALLOC_H

#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./SingleBits.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/SingleBits.h"
	#endif

#endif

#ifndef DEFAULT_SBULKMEM_SIZE
#define DEFAULT_SBULKMEM_SIZE					(1024 * 1024)	// Default bulk memory block size
																//	in octets (bytes).
#endif

/*
	See
	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc?view=msvc-150 .
	Default alignment size on 32 bit Windows is 8 octets and 16 octets on 64 bit platforms.
*/
// Memory alignments. Use 16 octets/bytes for 64 bit platforms. We're going to support more
//	platforms in the future.
#if defined (_WIN64) || defined (__x86_64__)
	// For 64 bit platforms.
    #define DEFAULT_SBULKMEM_ALIGNMENT			(16)
#elif defined (_WIN32)
	// For 32 bit platforms.
    #define DEFAULT_SBULKMEM_ALIGNMENT			(8)
#else
    #error "Either a 32 bit or a 64 bit platform must be determined."
#endif

enum en_sbulkmem_unit
{
		EN_SBULKMEM_UNIT_OCTETS									// Size is in octets (bytes).
	,	EN_SBULKMEM_UNIT_BYTES		= EN_SBULKMEM_UNIT_OCTETS
	,	EN_SBULKMEM_UNIT_IGNORED	= EN_SBULKMEM_UNIT_OCTETS
	,	EN_SBULKMEM_UNIT_KiB									// Size is in KiB.
	,	EN_SBULKMEM_UNIT_MiB									// Size is in MiB.
	,	EN_SBULKMEM_UNIT_GiB									// Size is in GiB.
};

/*
	CalculateSizeFromUnit

	Helper function to calculate the size form a unit.
*/
size_t CalculateSizeFromUnit (size_t size, enum en_sbulkmem_unit unit)
;

/*
	One bulk memory block.
	
	pMemBlockBase is a pointer to the allocated bulk memory. This structure is
	usually transparent to the caller/user.
*/
typedef struct sbulkmemblock
{
	void					*pMemBlockBase;					// Pointer to the base of the block.
	size_t					stSize;							// Its total size.
	void					*pNextAvailable;				// Pointer to the next available
															//	memory block, which is returned
															//	on next allocation.
	size_t					stFreeSize;
	struct sbulkmemblock	*pNextElement;					// Next element in the linked list.
	uint64_t				uiFlags;
} SBULKMEMBLOCK;

/*
	The plinth of a bulk memory block list and the interface structure.
*/
typedef struct sbulkmemplinth
{
	SBULKMEMBLOCK			*psbulkFirst;					// The first bulk memory block.
	SBULKMEMBLOCK			*psbulkLast;					// The last bulk memory block.
	size_t					stDefaultSize;					// Default size of a single block.
	uint64_t				uiFlags;
#ifdef BUILD_POPSBULKMEM
	SBULKMEMBLOCK			*psbulkLastUsed;				// The block to which has been
															//	written most recently.
#endif
} SBULKMEM;

/*
	Flags for the uiFlags member of the SBULKMEMBLOCK and SBULKMEM structures.
*/
#define USBM_STRUCT_ALLOCATED		SINGLE_BIT_UINT64 (0)	// Structure itself on heap.
#define USBM_MEM_BLOCK_ALLOCATED	SINGLE_BIT_UINT64 (1)	// Member pMemBlockBase of SBULKMEMBLOCK
															//	allocated on heap.
#define USBM_STRUCT_INITIALISED		SINGLE_BIT_UINT64 (2)	// Structure is initialised already.

/*
	CalculateAlignedSize

	Calculates the required size to ensure a given alignment is possible. For instance, if
	size is 10 and an alignment of 8 is wanted, the function returns 16 to ensure there's a
	memory block of at least 10 octets available with a base address aligned to 8 octets,
	independent of the original start address.
*/
size_t CalculateAlignedSize (size_t size, uint16_t alignment)
;

/*
	AlignMemblock

	Increments the pointer pBlock to alignment. The caller is responsible for ensuring that
	the memory block pBlock points to is big enough to be aligned.

	Example:

	// Windows aligns memory on an 8 octet boundary (32 bit) or 16 octet boundary (64 bit)
	//	only but we require 32.
	void *p = malloc (CalculateAlignedSize (237, 32));
	if (p)
	{
		p_aligned = AlignMemblock (p, 237, 32);
	}
*/
void *AlignMemblock (void *pBlock, size_t size, uint16_t alignment)
;

/*
	InitSBULKMEM

	Initialises the SBULKMEM plinth pPlinth points to.
*/
#ifdef DEBUG
	void InitSBULKMEM (SBULKMEM *pPlinth, size_t defaultSize);
#else
	#ifdef BUILD_POPSBULKMEM
		#define InitSBULKMEM(p, defaultSize)			\
			(p)->psbulkFirst	= NULL;					\
			(p)->psbulkLast		= NULL;					\
			(p)->stDefaultSize	= defaultSize;			\
			(p)->uiFlags		= 0;					\
			(p)->psbulkLastUsed = NULL
	#else
		#define InitSBULKMEM(p, defaultSize)			\
			(p)->psbulkFirst	= NULL;					\
			(p)->psbulkLast		= NULL;					\
			(p)->stDefaultSize	= defaultSize;			\
			(p)->uiFlags		= 0
	#endif
#endif

/*
	AllocInitSBULKMEM

	Allocates memory for a new block of bulk memory.
	
	If pPlinth is NULL, the function allocates an SBULKMEM structure, a memory block
	header structure SBULKMEMBLOCK, and the associated memory block (buffer) on the heap.
	The entire construct is correctly initialised.
	
	If pPlinth is not NULL, the function expects that it points to an already existing
	and initialised SBULKMEM structure. In this case the function only allocates a
	memory block header structure SBULKMEMBLOCK and its associated memory block on the
	heap if the SBULKMEM structure does not contain them yet. If a memory block for the
	structure is available already, the function does nothing.

	The function returns a pointer, either to the newly created and initialised SBULKMEM
	structure, block header, and memory block upon success, or pPlinth if pPlinth is not
	NULL.
	The function returns NULL if not enough heap memory is available or any other error
	occurred.
*/
SBULKMEM *AllocInitSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							stDefaultSize
							)
;

/*
	SBULKMEM_INITIALISER

	Static or automatic initialiser.

	Example:
	SBULKMEM smp = SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_PAGE_SIZE);
*/
#ifdef BUILD_POPSBULKMEM
	#define SBULKMEM_INITIALISER(s)						\
		{												\
			NULL,										\
			NULL,										\
			(s),										\
			USBM_STRUCT_INITIALISED,					\
			NULL										\
		}
#else
	#define SBULKMEM_INITIALISER(s)						\
		{												\
			NULL,										\
			NULL,										\
			(s),										\
			USBM_STRUCT_INITIALISED						\
		}
#endif

/*
	EmptySBULKMEM

	Empties the singly-linked SBULKMEM list pPlinth points to without deallocating
	its buffers. After the function returns, the entire bulk memory is available again.

	The function does not overwrite or reset the buffers' contents. It simply resets the
	level pointers of all its SBULKMEMBLOCK structures.

	To deallocate the SBULKMEM structure pPlinth points to call DoneSBULKMEM ().
*/
void EmptySBULKMEM (SBULKMEM *pPlinth)
;

/*
	DoneSBULKMEM

	Deallocates the singly-linked SBULKMEM list pPlinth points to, including maintenance
	structures, memory blocks, and the base SBULKMEM structure. The function takes into
	consideration when the plinth SBULKMEM structure is static or automatic, in which case
	it is not deallocated.

	The parameter pPlinth cannot be NULL, and debug versions abort.

	The function returns NULL to indicate that the entire list, including the SBULKMEM
	structure pPlinth points to, has been deallocated. The function returns pPlinth if
	it is a static or automatic structure.

	After the function returns and its return value is not NULL, the SBULKMEM structure
	can be re-used. However, if the SBULKMEM structure is intended to be re-used, it is
	recommended to call EmptySBULKMEM () instead of DoneSBULKMEM (). The function
	EmptySBULKMEM () resets the level pointers only rather than deallocating the actual
	buffers, which is usually a much faster operation.
*/
SBULKMEM *DoneSBULKMEM (SBULKMEM *pPlinth)
;

/*
	The enum for the parameter grow of the function GetMemFromSBULKMEM ().
*/
enum en_sbulkmem_allow_growth
{
		EN_SBULKMEM_CAN_GROW
	,	EN_SBULKMEM_ALLOW_GROWTH	= EN_SBULKMEM_CAN_GROW
	,	EN_SBULKMEM_CANNOT_GROW
	,	EN_SBULKMEM_PREVENT_GROWTH	= EN_SBULKMEM_CANNOT_GROW
};

/*
	GrowSBULKMEM
	
	Grows the SBULKMEM structure pbm points to by one element, i.e. extends the singly
	linked list by one bulk memory block, consisting of structure and actual memory
	block.
	
	The parameter pPlinth must not be NULL but is not checked by the function. Debug
	versions abort, release versions run into undefined behaviour or access violations.

	If size is less than the default size stored in the member stDefaultSize of the
	SBULKMEM structure pPlinth points to, the value of stDefaultSize is used.
	If size is greater than the stored default size, the new bulk memory block will
	have the size of the parameter size to honour the caller's request.
	
	The function returns a pointer to the newly allocated SBULKMEMBLOCK structure after
	it has been added to the singly linked list with pPlinth as its base/plinth. The
	function returns NULL if not enough heap memory is available and no new block
	could be added.
*/
SBULKMEMBLOCK *GrowSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							size
							)
;

/*
	GetMemFromSBULKMEMBLOCKifAvailable

	Returns a pointer to a memory block of size size from the SBULKMEMBLOCK structure
	pbm points to. The function fails and returns NULL if the block does not contain
	enough empty space for size octets.

	The function does not perform parameter checks. The parameter pbm must not be
	NULL.

	The function does not perform any memory alignment. If you need the returned memory
	block to be aligned, call AlignMemblock () on the returned pointer.

	Example for an alignment of 32 octets:

	SBULKMEMBLOCK	*pbm = GrowSBULKMEM (pPlinth, 1024, 32);
	void			*pData;

	pData = GetMemFromSBULKMEMBLOCKifAvailable (pbm, 128);
	pData = AlignMemblock (pData, 128, 32);
*/
void *GetMemFromSBULKMEMBLOCKifAvailable (SBULKMEMBLOCK *pbm, size_t size)
;

/*
	GetMemFromSBULKMEM
	
	Returns a block of memory from the bulk memory block SBULKMEM pPlinth points to.
	This parameter must therefore not be NULL.

	The requested size of the memory block is specified by the parameter size.
	
	The parameter alignment specifies the alignment, if needed. If this parameter
	is 0, a default alignment of 8 is assumed on 32 bit platforms and 16 octets on
	64 bit platforms. If it is 1, the returned memory block is not aligned. If not 0,
	only powers of 2 are allowed for this parameter, with the lowest allowed value being
	8 (i.e. 8, 16, 32, etc). The highest possible alignment size is 128 octets.
	
	The parameter grow specifies if the bulk memory block is allowed to grow. If grow
	is EN_SBULKMEM_CANNOT_GROW or EN_SBULKMEM_PREVENT_GROWTH, the function fails when
	the bulk memory block can not provide the requested size. If grow is
	EN_SBULKMEM_CAN_GROW or EN_SBULKMEM_ALLOW_GROWTH the function tries to add another
	SBULKMEMBLOCK structure to the singly linked list, allocates bulk memory for it, and
	returns a valid memory block from the newly created bulk memory block to the caller
	(provided, of course, that none of the heap allocations fails).
	When the total requested size, while unit is taken into consideration, is smaller than
	or equal to the member stDefaultSize of the SBULKMEM structure, the new bulk memory
	block gets this block's default size. When the size is bigger than the default size,
	the function creates a block with the requested size and marks the block as fully
	filled/occupied.
	
	The function returns a pointer to a memory block within the bulk memory block it
	reserved for the caller. The function returns NULL when it fails. The function
	can fail when the bulk memory block is exhausted but the block is prevented
	from growing. The function can also fail when a heap allocation function fails.
	
	In most cases the caller might want to use GetAlignedMemFromSBULKMEMgrow () instead,
	which is the equivalent to malloc () for bulk memory blocks.
*/
void *GetMemFromSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							size,
			uint8_t							alignment,
			enum en_sbulkmem_allow_growth	grow
							)
;

/*
	GetAlignedMemFromSBULKMEMgrow

	The function works as if it calls GetMemFromSBULKMEM () with the parameter alignment
	set to 0 and parameter grow set to EN_SBULKMEM_ALLOW_GROWTH. In reality, for performance
	reasons the function is an altered copy of GetMemFromSBULKMEM ().
	
	This is most likely the function you want to call most of the time. The function
	is the equivalent call to malloc () for bulk memory blocks.
	
	The function returns the same value GetMemFromSBULKMEM () would have returned.
*/
void *GetAlignedMemFromSBULKMEMgrow	(
			SBULKMEM						*pPlinth,
			size_t							size
									)
;

/*
	GetAlignedMemFromSBULKMEMnogrow
	
	Calls GetMemFromSBULKMEM () with the parameter alignment set to 8 on 32 bit platforms
	and 16 on 64 bit platforms, and parameter grow set to EN_SBULKMEM_PREVENT_GROWTH to
	prevent the bulk memory block from growing.
	
	The function returns the value returned by GetMemFromSBULKMEM (). The function fails
	and returns NULL if the builk memory does not hold enough space to reserve the requested
	amount of memory.
*/
void *GetAlignedMemFromSBULKMEMnogrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
;

/*
	GetUnalignedMemFromSBULKMEMgrow
	
	Calls GetMemFromSBULKMEM () with the parameter alignment set to 1 and parameter grow
	set to EN_SBULKMEM_ALLOW_GROWTH. This means the returned memory block is not
	aligned in any way.
	
	The function returns the value returned by GetMemFromSBULKMEM ().
*/
void *GetUnalignedMemFromSBULKMEMgrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
;

/*
	GetUnalignedMemFromSBULKMEMnogrow
	
	Calls GetMemFromSBULKMEM () with the parameter alignment set to 1 and parameter grow
	set to EN_SBULKMEM_PREVENT_GROWTH. This means the memory block returned is not
	aligned in any way.
	
	The function returns the value returned by GetMemFromSBULKMEM ().
*/
void *GetUnalignedMemFromSBULKMEMnogrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
;

/*
	popSBULKMEMBLOCK
	
	Pops the provided size (parameter size) of bytes from the SBULKMEMBLOCK structure's
	bulk memory block.
	
	The function increases the available size of the memory block by decreasing its
	used space by size octets. The function does not perform any checks. It blindly
	substracts the size, in octets, from the member pNextAvailable and increases
	stFreeSize by the same amount. The caller is responsible for the correct alignment
	and prevention of data corruption.
*/
void popSBULKMEMBLOCK					(
			SBULKMEMBLOCK					*pb,
			size_t							size
										)
;

/*
	popSBULKMEM
	
	Pops the provided size (parameter size) of bytes from the SBULKMEM bulk memory
	pPlinth points to. The pop occurs on the most recently used SBULKMEMBLOCK structure
	within the singly-linked list. This should ensure that the most recently allocated
	memory block can be popped.

	The function increases the available size of the memory block by decreasing its
	used space by size octets. The function does not perform any checks. It blindly
	substracts the size, in octets, from the member pNextAvailable and increases
	stFreeSize by the same amount. The caller is responsible for the correct alignment
	and prevention of data corruption.
	
	The trick with storing the most recently used SBULKMEMBLOCK in one of the plinth's
	members is probably not the best approach. The entire design might change in the
	future.
*/
#ifdef BUILD_POPSBULKMEM
	void popSBULKMEM						(
				SBULKMEM						*pPlinth,
				size_t							size
											)
	;
#endif

/*
	Result structur for getSBULKMEMstats ().
*/
typedef struct sbulkmemstats
{
	unsigned int		nSBULKMEMBLOCKs;					// Amount of SBULKMEMBLOCK structures
															//	in the singly-linked list.
	size_t				stDefaultSize;						// The default size.
	size_t				stTotal;							// Total size of all blocks.
	size_t				stFreeTotal;						// Combined available (free) size.
	size_t				stFreeLargest;						// Largest available (free) block.
	size_t				stFreeSmallest;						// Smallest available (free) block.
	size_t				stFreeAverage;						// Average available size.
} SBULKMEMSTATS;

/*
	getSBULKMEMstats

	Obtains some statistics of the SBULKMEM structure pPlinth points to and returns
	the data in the SBULKMEMSTATS structure pStats points to.

	Neither parameter must be NULL.
*/
void getSBULKMEMstats (SBULKMEMSTATS *pStats, SBULKMEM *pPlinth)
;

// To build the test function.
#ifdef DEBUG
	#ifndef BUILD_BULKMALLOC_TEST_FUNCTIONS
	#define BUILD_BULKMALLOC_TEST_FUNCTIONS
	#endif
#endif

#ifdef BUILD_BULKMALLOC_TEST_FUNCTIONS
	bool bulkmalloc_test_fnct (void);
#else
	#define bulkmalloc_test_fnct()						\
		(true)
#endif

#endif															// Of #ifndef BULKMALLOC_H.
