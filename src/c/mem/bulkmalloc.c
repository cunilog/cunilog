/****************************************************************************************

	File:		bulkmalloc.c
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
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
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

	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./bulkmalloc.h"
	#include "./ubfmem.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ArrayMacros.h"
		#include "./ubf_date_and_time.h"
		#include "./ubfdebug.h"
	#else
		#include "./../pre/ArrayMacros.h"
		#include "./../datetime/ubf_date_and_time.h"
		#include "./../dbg/ubfdebug.h"
	#endif

	#ifdef BUILD_BULKMALLOC_TEST_FUNCTIONS
		#include <stdio.h>
	#endif

#endif

static void AssertAlignment (uint16_t alignment)
{
	ubf_assert	(
						   0 == alignment
					||	   1 == alignment
					||	   8 == alignment
					||	  16 == alignment
					||	  32 == alignment
					||	  64 == alignment
					||	 128 == alignment
					||	 256 == alignment
					||	 512 == alignment
					||	1024 == alignment
					||	2048 == alignment
					||	4096 == alignment
				);
	UNREFERENCED_PARAMETER (alignment);
}

size_t CalculateSizeFromUnit (size_t size, enum en_sbulkmem_unit unit)
{
	size_t		stRet	= 0;

	ubf_assert ((size_t) -1 != size);
	// Some assertions aboout the unit constants.
	ubf_assert (EN_SBULKMEM_UNIT_BYTES == EN_SBULKMEM_UNIT_OCTETS);
	ubf_assert (EN_SBULKMEM_UNIT_KiB > EN_SBULKMEM_UNIT_BYTES);
	ubf_assert (EN_SBULKMEM_UNIT_MiB > EN_SBULKMEM_UNIT_KiB);
	ubf_assert (EN_SBULKMEM_UNIT_GiB > EN_SBULKMEM_UNIT_MiB);
	if (size)
	{
		stRet = size;
		stRet *= unit >= EN_SBULKMEM_UNIT_KiB ? 1024 : 1;
		stRet *= unit >= EN_SBULKMEM_UNIT_MiB ? 1024 : 1;
		stRet *= unit >= EN_SBULKMEM_UNIT_GiB ? 1024 : 1;
	} else
	{
		stRet = DEFAULT_SBULKMEM_SIZE;
	}
	return stRet;
}

size_t CalculateAlignedSize (size_t size, uint16_t alignment)
{
	size_t	stRequested;

	ubf_assert ((size_t) -1 != size);
	switch (alignment)
	{
		case 1:
			stRequested = size;
			break;
		case 0:
			alignment = DEFAULT_SBULKMEM_ALIGNMENT;
		default:
			AssertAlignment (alignment);
			stRequested = ALIGNED_SIZE (size, alignment);
			break;
	}
	return stRequested;
}

void *AlignMemblock (void *pBlock, size_t size, uint16_t alignment)
{
	size_t	asize = CalculateAlignedSize (size, alignment);
	ubf_assert (asize >= size);

	char	*p	= pBlock;
	p += asize - size;
	return p;
}

#ifdef DEBUG
	void InitSBULKMEM (SBULKMEM *pPlinth, size_t defaultSize)
	{
		ubf_assert_non_NULL (pPlinth);

		pPlinth->psbulkFirst	=	NULL;
		pPlinth->psbulkLast		=	NULL;
		pPlinth->stDefaultSize		= defaultSize;
		pPlinth->uiFlags			= 0;
		#ifdef BUILD_POPSBULKMEM
			pPlinth->psbulkLastUsed	= NULL;
		#endif
	}
#endif

SBULKMEM *AllocInitSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							stDefaultSize
							)
{
	SBULKMEM	*plinth;
	size_t		stTotal;
	size_t		stSBULKMEM			= ALIGNED_SIZE (sizeof (SBULKMEM), DEFAULT_SBULKMEM_ALIGNMENT);
	size_t		stSBULKMEMBLOCK		= ALIGNED_SIZE (sizeof (SBULKMEMBLOCK), DEFAULT_SBULKMEM_ALIGNMENT);
	size_t		stMemblockSize		= ALIGNED_SIZE (stDefaultSize, DEFAULT_SBULKMEM_ALIGNMENT);

	ubf_assert (0 != stDefaultSize);
	ubf_assert ((size_t) -1 != stDefaultSize);
	ubf_assert (1 == sizeof (char));
	ubf_assert (1 == sizeof (uint8_t));

	if (pPlinth)
	{
		plinth = pPlinth;
		if (pPlinth->psbulkFirst)
		{
			GrowSBULKMEM (plinth, 0);
		} else
		{
			SBULKMEMBLOCK		*pbm;
			
			stTotal								= stSBULKMEMBLOCK + stMemblockSize;
			plinth->uiFlags						= 0;
			plinth->stDefaultSize				= stMemblockSize;
			pbm = ubf_malloc (stTotal);
			if (pbm)
			{
				char			*pWork;							// Just a pointer to work with.
	
				pWork = (char *) pbm;
				pWork += stSBULKMEMBLOCK;
				plinth->psbulkFirst				= pbm;
				plinth->psbulkLast				= pbm;
				pbm->uiFlags					= USBM_STRUCT_ALLOCATED | USBM_STRUCT_INITIALISED;
				pbm->pMemBlockBase				= pWork;
				pbm->pNextAvailable				= pWork;
				pbm->pNextElement				= NULL;
				pbm->stSize						= stMemblockSize;
				pbm->stFreeSize					= stMemblockSize;
			} else
			{
				plinth->psbulkFirst				= NULL;
				plinth->psbulkLast				= NULL;
			}
		}
	} else
	{
		stTotal									= stSBULKMEM + stSBULKMEMBLOCK + stMemblockSize;
		plinth = ubf_malloc (stTotal);
		if (plinth)
		{
			char			*pWork;							// Just a pointer to work with.
	
			plinth->uiFlags						= USBM_STRUCT_ALLOCATED | USBM_STRUCT_INITIALISED;
			plinth->stDefaultSize				= stMemblockSize;
			pWork = (char *) plinth;
			pWork += stSBULKMEM;
			plinth->psbulkFirst					= (SBULKMEMBLOCK *) pWork;
			plinth->psbulkLast					= (SBULKMEMBLOCK *) pWork;
			plinth->psbulkFirst->pMemBlockBase	= (void *) (pWork + stSBULKMEM + stSBULKMEMBLOCK);
			plinth->psbulkFirst->pNextAvailable	= (void *) (pWork + stSBULKMEM + stSBULKMEMBLOCK);
			plinth->psbulkFirst->pNextElement	= NULL;
			plinth->psbulkFirst->stSize			= stMemblockSize;
			plinth->psbulkFirst->stFreeSize		= stMemblockSize;
			plinth->psbulkFirst->uiFlags		= 0;
		#ifdef BUILD_POPSBULKMEM
			plinth->psbulkLastUsed				= NULL;
		#endif
		}
	}
	return plinth;
}

void EmptySBULKMEM (SBULKMEM *pPlinth)
{
	ubf_assert_non_NULL (pPlinth);

	SBULKMEMBLOCK *p = pPlinth->psbulkFirst;
	while (p)
	{
		p->pNextAvailable		= p->pMemBlockBase;
		p->stFreeSize			= p->stSize;
		p						= p->pNextElement;
	}
	#ifdef BUILD_POPSBULKMEM
		pPlinth->psbulkLastUsed	= NULL;
	#endif
}

SBULKMEM *DoneSBULKMEM (SBULKMEM *pPlinth)
{
	SBULKMEMBLOCK	*p;
	SBULKMEMBLOCK	*l;

	ubf_assert (NULL != pPlinth);
	p = pPlinth->psbulkFirst;
	while (p)
	{
		if (p->uiFlags & USBM_MEM_BLOCK_ALLOCATED && p->pMemBlockBase)
		{
			ubf_free (p->pMemBlockBase);
		}
		l = p;
		p = p->pNextElement;
		if (l->uiFlags & USBM_STRUCT_ALLOCATED)
			ubf_free (l);
	}
	if (pPlinth->uiFlags & USBM_MEM_BLOCK_ALLOCATED)
	{
		ubf_free (pPlinth);
		return NULL;
	}
	pPlinth->psbulkFirst	= NULL;
	pPlinth->psbulkLast		= NULL;
#ifdef BUILD_POPSBULKMEM
	pPlinth->psbulkLastUsed	= NULL;
#endif
	return pPlinth;
}

void AddSBULKMEMBLOCKtoPlinth (SBULKMEM *pPlinth, SBULKMEMBLOCK *pnew)
{
	ubf_assert_non_NULL (pPlinth);
	ubf_assert_non_NULL (pnew);
	
	if (pPlinth->psbulkLast)
	{
		pPlinth->psbulkLast->pNextElement		= pnew;
		pPlinth->psbulkLast						= pnew;
	} else
	{
		pPlinth->psbulkFirst					= pnew;
		pPlinth->psbulkLast						= pnew;
	}
}

SBULKMEMBLOCK *AllocAndAddEmptySBULKMEMBLOCK (SBULKMEM *pPlinth)
{
	SBULKMEMBLOCK	*pnew;
	size_t			stSBULKMEMBLOCK	= ALIGNED_SIZE (sizeof (SBULKMEMBLOCK), DEFAULT_SBULKMEM_ALIGNMENT);

	ubf_assert_non_NULL (pPlinth);
	pnew = ubf_malloc (stSBULKMEMBLOCK);
	if (pnew)
	{
		pnew->uiFlags							= USBM_STRUCT_ALLOCATED;
		pnew->pMemBlockBase						= NULL;
		pnew->pNextAvailable					= NULL;
		pnew->pNextElement						= NULL;
		pnew->stFreeSize						= 0;
		pnew->stSize							= 0;
		AddSBULKMEMBLOCKtoPlinth (pPlinth, pnew);
	}
	return pnew;
}

SBULKMEMBLOCK *GrowSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							size
							)
{
	SBULKMEMBLOCK	*pnew;

	ubf_assert_non_NULL (pPlinth);
	ubf_assert ((size_t) -1 != size);

	if (size <= pPlinth->stDefaultSize)
		size = pPlinth->stDefaultSize;
	if (size)
	{
		size_t			stSBULKMEMBLOCK	= ALIGNED_SIZE (sizeof (SBULKMEMBLOCK), DEFAULT_SBULKMEM_ALIGNMENT);
		size_t			stMemoryBlock	= CalculateAlignedSize (size, DEFAULT_SBULKMEM_ALIGNMENT);

		pnew = ubf_malloc (stSBULKMEMBLOCK + stMemoryBlock);
		if (pnew)
		{
			pnew->uiFlags						= USBM_STRUCT_ALLOCATED;
			pnew->pMemBlockBase					= ((char *) pnew) + stSBULKMEMBLOCK;
			pnew->pNextAvailable				= ((char *) pnew) + stSBULKMEMBLOCK;
			pnew->pNextElement					= NULL;
			pnew->stSize						= stMemoryBlock;
			pnew->stFreeSize					= stMemoryBlock;
			AddSBULKMEMBLOCKtoPlinth (pPlinth, pnew);
		}
	} else
	{	// 0 == size.
		pnew = AllocAndAddEmptySBULKMEMBLOCK (pPlinth);
	}
	return pnew;
}

SBULKMEMBLOCK *FindAvailableSizeOrGrow	(
			SBULKMEM						*p,
			size_t							size,
			enum en_sbulkmem_allow_growth	grow
										)
{
	ubf_expect_non_NULL (p);
	ubf_assert ((size_t) -1 != size);

	SBULKMEMBLOCK	*pbm	= p->psbulkFirst;

	while (pbm)
	{
		if (size <= pbm->stFreeSize)
			return pbm;
		pbm = pbm->pNextElement;
	}
	if (EN_SBULKMEM_CANNOT_GROW == grow)
		return NULL;
	// Note that size has been aligned here already.
	pbm = GrowSBULKMEM (p, size);
	if (pbm)
	{
		ubf_assert (pbm->stFreeSize >= size);
		ubf_assert (pbm->stSize >= size);
	}
	return pbm;
}

void *GetMemFromSBULKMEMBLOCKifAvailable (SBULKMEMBLOCK *pbm, size_t size)
{
	void	*pRet		= NULL;

	ubf_assert_not_NULL (pbm);
	ubf_assert ((size_t) -1 != size);

	if (pbm->stFreeSize >= size)
	{
		pRet			= pbm->pNextAvailable;
		char	*p		= pRet;

		p += size;
		pbm->pNextAvailable		= p;
		pbm->stFreeSize			-= size;
	}
	return pRet;
}

void *GetMemFromSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							size,
			uint8_t							alignment,
			enum en_sbulkmem_allow_growth	grow
							)
{
	SBULKMEMBLOCK		*pbm;
	size_t				stRequested;

	ubf_assert_non_NULL (pPlinth);
	ubf_assert ((size_t) -1 != size);

	AssertAlignment (alignment);
	stRequested = CalculateAlignedSize (size, alignment);
	pbm = FindAvailableSizeOrGrow (pPlinth, stRequested, grow);
	if (pbm)
	{
		void *pRet = NULL;

		pRet = GetMemFromSBULKMEMBLOCKifAvailable (pbm, stRequested);
		// Align the returned block.
		ubf_assert (stRequested >= size);

		char *p = pRet;
		p += stRequested - size;
		#ifdef BUILD_POPSBULKMEM
			pPlinth->psbulkLastUsed = pbm;
		#endif
		return p;
	}
	return NULL;
}

/*
	Copy of GetMemFromSBULKMEM () with the most common parameters.
	Alignment is 8 for 16 bit CPUs and 16 for 64 bit CPUs, and the block can grow.
*/
void *GetAlignedMemFromSBULKMEMgrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
{
	SBULKMEMBLOCK		*pbm;
	size_t				stRequested;

	ubf_assert (NULL != pPlinth);
	ubf_assert ((size_t) -1 != size);

	stRequested = ALIGNED_SIZE (size, DEFAULT_SBULKMEM_ALIGNMENT);
	pbm = FindAvailableSizeOrGrow (pPlinth, stRequested, EN_SBULKMEM_CAN_GROW);
	if (pbm)
	{
		void *pRet = NULL;

		pRet = GetMemFromSBULKMEMBLOCKifAvailable (pbm, stRequested);
		// Align the returned block.
		ubf_assert (stRequested >= size);

		char *p = pRet;
		p += stRequested - size;
		#ifdef BUILD_POPSBULKMEM
			pPlinth->psbulkLastUsed = pbm;
		#endif
		return p;
	}
	return NULL;
}

void *GetAlignedMemFromSBULKMEMnogrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
{
	ubf_assert (NULL != pPlinth);
	ubf_assert ((size_t) -1 != size);

	return GetMemFromSBULKMEM (pPlinth, size, DEFAULT_SBULKMEM_ALIGNMENT, EN_SBULKMEM_CANNOT_GROW);
}

void *GetUnalignedMemFromSBULKMEMgrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
{
	ubf_assert (NULL != pPlinth);
	ubf_assert ((size_t) -1 != size);

	return GetMemFromSBULKMEM (pPlinth, size, 1, EN_SBULKMEM_CAN_GROW);
}

void *GetUnalignedMemFromSBULKMEMnogrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
{
	ubf_assert (NULL != pPlinth);
	ubf_assert ((size_t) -1 != size);

	return GetMemFromSBULKMEM (pPlinth, size, 1, EN_SBULKMEM_CANNOT_GROW);
}

void popSBULKMEMBLOCK					(
			SBULKMEMBLOCK					*pb,
			size_t							size
										)
{
	ubf_assert_non_NULL (pb);
	ubf_assert ((char *) pb->pNextAvailable - size >= (char *) pb->pMemBlockBase);
	
	pb->pNextAvailable	= (char *) pb->pNextAvailable - size;
	pb->stFreeSize		+= size;
}

#ifdef BUILD_POPSBULKMEM
	void popSBULKMEM						(
				SBULKMEM						*pPlinth,
				size_t							size
											)
	{
		ubf_assert_non_NULL (pPlinth);
		ubf_assert_non_NULL (pPlinth->psbulkLastUsed);
		
		popSBULKMEMBLOCK (pPlinth->psbulkLastUsed, size);
	}
#endif

void getSBULKMEMstats (SBULKMEMSTATS *pStats, SBULKMEM *pPlinth)
{
	ubf_assert_non_NULL (pStats);
	ubf_assert_non_NULL (pPlinth);

	pStats->stDefaultSize		= pPlinth->stDefaultSize;
	pStats->nSBULKMEMBLOCKs		= 0;
	pStats->stFreeLargest		= 0;
	pStats->stFreeSmallest		= (size_t) -1;
	pStats->stTotal				= 0;
	pStats->stFreeTotal			= 0;
	pStats->stFreeAverage		= 0;

	SBULKMEMBLOCK	*p	= pPlinth->psbulkFirst;
	while (p)
	{
		++ pStats->nSBULKMEMBLOCKs;
		pStats->stTotal += p->stSize;
		pStats->stFreeTotal += p->stFreeSize;
		if (p->stFreeSize > pStats->stFreeLargest)
			pStats->stFreeLargest = p->stFreeSize;
		if (p->stFreeSize < pStats->stFreeSmallest)
			pStats->stFreeSmallest = p->stFreeSize;
		p = p->pNextElement;
	}
	if (pStats->nSBULKMEMBLOCKs)
	{
		pStats->stFreeAverage = pStats->stFreeTotal / pStats->nSBULKMEMBLOCKs;
	} else
	{
		pStats->stFreeSmallest = 0;
	}
}

#ifdef BUILD_BULKMALLOC_TEST_FUNCTIONS
	bool bulkmalloc_test_fnct (void)
	{
		bool			b		= false;
		SBULKMEM		sbm		= SBULKMEM_INITIALISER (128);
		//SBULKMEM		*pbm;
		void			*p;
		SBULKMEMBLOCK	*pbmb;

		// The SBULKMEM structure doesn't have any memory block attached.
		p = GetUnalignedMemFromSBULKMEMnogrow (&sbm, 1);
		ubf_assert_NULL (p);
		p = GetAlignedMemFromSBULKMEMnogrow (&sbm, 1);
		ubf_assert_NULL (p);
		p = GetUnalignedMemFromSBULKMEMnogrow (&sbm, 1024);
		ubf_assert_NULL (p);
		p = GetAlignedMemFromSBULKMEMnogrow (&sbm, 1024);
		ubf_assert_NULL (p);
		p = GetAlignedMemFromSBULKMEMnogrow (&sbm, 1022);
		ubf_assert_NULL (p);

		pbmb = GrowSBULKMEM (&sbm, 0);
		ubf_assert_non_NULL (pbmb);
		pbmb = GrowSBULKMEM (&sbm, 12);
		ubf_assert_non_NULL (pbmb);
		p = GetAlignedMemFromSBULKMEMnogrow (&sbm, 1022);
		ubf_assert_NULL (p);
		// This should succeed.
		p = GetAlignedMemFromSBULKMEMnogrow (&sbm, 16);
		ubf_assert_non_NULL (p);
		p = GetAlignedMemFromSBULKMEMgrow (&sbm, 12);
		ubf_assert_non_NULL (p);

		DoneSBULKMEM (&sbm);

		p = GetAlignedMemFromSBULKMEMgrow (&sbm, 1024);
		ubf_assert_non_NULL (p);
		if (p)
		{
			memset (p, 0, 1024);
		}
		DoneSBULKMEM (&sbm);

		/*
			Let's compare the two solutions when it comes to speed.
			We allocate 100 000 memory blocks with 128 octets each, write to the block,
			then deallocate it again. Method 2) allocates 200 MiB.

			1) malloc () and free ()
			2) AllocInitSBULKMEM (), GetMemFromSBULKMEM (), and DoneSBULKMEM ()
		*/
		SBULKMEM	*pTest;

		FILETIME	ft1, ft2;
		uint64_t	ut1, ut2, ut3;
		uint64_t	u;

		puts ("Starting...");
		GetSystemTimeAsFileTime (&ft1);
		char *pCh [100000];
		for (u = 0; u < 100000; ++u)
		{
			pCh [u] = malloc (128);
			if (pCh [u])
				memset (pCh [u], 0, 128);
		}
		for (u = 0; u < 100000; ++u)
		{
			free (pCh [u]);
		}
		GetSystemTimeAsFileTime (&ft2);
		ut1 = ft1.dwHighDateTime;
		ut1 <<= 32;
		ut1 += ft1.dwLowDateTime;
		ut2 = ft2.dwHighDateTime;
		ut2 <<= 32;
		ut2 += ft2.dwLowDateTime;
		ut3 = ut2 - ut1;
		ut3 /= 10000;			// milliseconds.
		printf ("Diff - malloc (): %" PRIu64 " ms.\n", ut3);

		GetSystemTimeAsFileTime (&ft1);
		pTest = AllocInitSBULKMEM (NULL, 200 * 1024 * 1024);
		if (pTest)
		{
			for (u = 0; u < 100000; ++u)
			{
				pCh [u] = GetMemFromSBULKMEM (pTest, 128, 0, EN_SBULKMEM_CANNOT_GROW);
				if (pCh [u])
					memset (pCh [u], 0, 128);
			}
			DoneSBULKMEM (pTest);
			GetSystemTimeAsFileTime (&ft2);
			ut1 = ft1.dwHighDateTime;
			ut1 <<= 32;
			ut1 += ft1.dwLowDateTime;
			ut2 = ft2.dwHighDateTime;
			ut2 <<= 32;
			ut2 += ft2.dwLowDateTime;
			ut3 = ut2 - ut1;
			ut3 /= 10000;			// milliseconds.
			printf ("Diff - memblock:  %" PRIu64 " ms.\n", ut3);
		}
		/*
			End of speed comparison.
		*/

		// Example 1 used for the top of the header file.
		//	->
		#define OUR_BULK_DATA_ARRAY_SIZE	(100)

		SBULKMEM	sbulk	= SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_SIZE);
		void		*pDat2 [OUR_BULK_DATA_ARRAY_SIZE];
		int			i;

		for (i = 0; i < OUR_BULK_DATA_ARRAY_SIZE; ++i)
		{
			pDat2 [i] = GetMemFromSBULKMEM (&sbulk, 1024, 8, EN_SBULKMEM_CAN_GROW);
			if (pDat2 [i])
			{
				memset (pDat2 [i], 0xFF, 1024);
			}
		}
		DoneSBULKMEM (&sbulk);
		//	<-

		// Example 2 used for the top of the header file.
		//	->
		#define OUR_BULK_DATA_ARRAY_SIZE	(100)
		SBULKMEM	*pBulk	= AllocInitSBULKMEM (NULL, DEFAULT_SBULKMEM_SIZE);
		if (pBulk)
		{
			void		*pData [OUR_BULK_DATA_ARRAY_SIZE];
			int			j;

			for (j = 0; j < OUR_BULK_DATA_ARRAY_SIZE; ++j)
			{
				pData [j] = GetMemFromSBULKMEM (&sbulk, 1024, 0, EN_SBULKMEM_CAN_GROW);
				if (pData [j])
				{
					memset (pData [j], 0xFF, 1024);
				}
			}
			DoneSBULKMEM (&sbulk);
		}
		//	<-



		return b;
	}
#endif
