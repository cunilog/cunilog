/****************************************************************************************

	File:		strcustomfmt.h
	Why:		Functions for user-defined format specifiers.
	OS:			C99
	Author:		Thomas
	Created:	2024-12-26

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-12-26	Thomas			Created.

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

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef STRCUSTOMFMT_H
#define STRCUSTOMFMT_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdarg.h>
	#include <stdbool.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

typedef struct sstrcustfmt SSTRCUSTFMT;

/*
	Functions provided by the caller/user.

	The module first calls custfmtGetRqSize () to obtain the required buffer size for the
	associated argument pCustFmtArg of the custom format specifier. This size is assumed to
	be without space for a terminating NUL character.
	
	The module then provides a buffer big enough for this size plus an additional NUL-
	terminator before it calls custfmtStoreData ().

	custfmtGetRqSize		User function that returns the required output buffer size for
							pCustFmtArg. The return value of this function is without a
							terminating NUL character.

	custfmtStoreData		User function that stores the output of pCustFmtArg in szBuf.
							The parameter len contains the length of the buffer szBuf points
							to. This is equal to or greater than the value returned by
							custfmtGetRqSize ().
							Although there is an additional octet/byte after this buffer
							reserved for a NUL terminator, the parameter len does not include
							it. In other words, the user can still write a NUL terminator at
							the end. Like custfmtGetRqSize (), the function must return the amount
							of characters written to szBuf, also without counting a terminating
							NUL character.
*/
typedef size_t (*custfmtGetRqSize)	(void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT);
typedef size_t (*custfmtStoreData)	(char *szBuf, size_t len, void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT);

/*
	The structure for a custom format specifier.
	
	The member pCustom is ignored by this module and therefore entirely available to the caller/
	user for passing on information from getRqSize () to storeData ().
*/
typedef struct sstrcustfmt
{
	const char			*ccFormatSpecifier;					// A custom format specifier. Cannot
															//	be NULL and cannot point to empty
															//	string.
	size_t				lenFormatSpecifier;					// Its length. This cannot be
															//	0 and also not (size_t) -1.
	custfmtGetRqSize	getRqSize;							// Returns the required buffer size.
	custfmtStoreData	storeData;							// Actual output function.

	void				*pCustom;							// Arbitrary pointer. Can be set by
															//	getRqSize () and read by
															//	storeData ().
} SSTRCUSTFMT;

/*
	The base (or plinth) of an array of SSTRCUSTFMT structures. This is what the functions in
	this module expect. See function TestStrCustomFmt () on how to construct this array with its
	plinth/base.
*/
typedef struct sstrcustfmtbase
{
	SSTRCUSTFMT			*psstrcustfmt;						// Pointer to an array of SSTRCUSTFMT
															//	structures.
	size_t				n;									// Number of elements in the array.
} SSTRCUSTFMTBASE;

/*
	strcustomfmtGetRqSizeCust

	Returns the required size for custom format specifiers.

	pb				A pointer to a fully initialised SSTRCUSTFMTBASE structure. The caller
					is responsible for initialising this structure. Cannot be NULL.

	lenCust			The length, in octets/bytes, of the buffer cust points to. Can be
					USE_STRLEN, in which case the function calls strlen () on the string
					to obtain its length.

	cust			The string that may contain custom format specifiers.

	The function returns the required length, excluding NUL terminator, the function
	strcustomfmtStoreDataCust () requires to store its output in strBuf.
	Before calling strcustomfmtStoreDataCust (), make sure the buffer for the parameter strBuf
	is at least strcustomfmtGetRqSizeCust () + 1 octets.
*/
size_t strcustomfmtGetRqSizeCust (SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, ...)
;

/*
	strcustomfmtStoreDataCust

	Stores the actual data expanded by custom format specifiers.

	strBuf			A pointer to the buffer that receives the output. Cannot be NULL. The
					size of this buffer is expected to be strcustomfmtGetRqSizeCust () + 1
					to accommodate for an additional NUL terminator.

	sizBuf			The size, in octets, of the buffer strBuf points to. The buffer must
					be big enough to hold the data to store including room for a NUL
					terminator, if required. Use strcustomfmtGetRqSizeCust ()
					to obtain this size and provide a buffer for strBuf of
					strcustomfmtGetRqSizeCust () + 1.
					This parameter cannot be 0.

	pb				A pointer to a fully initialised SSTRCUSTFMTBASE structure. The caller
					is responsible for initialising this structure. Cannot be NULL.

	lenCust			The length, in octets/bytes, of the buffer cust points to. Can be
					USE_STRLEN, in which case the function calls strlen () on the string
					to obtain its length.

	cust			The string that may contain custom format specifiers.
*/
size_t strcustomfmtStoreDataCust (char *strBuf, size_t sizBuf, SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, ...)
;

#ifdef DEBUG
	#define STRCUSTOMFMT_BUILD_TEST_FNCTS
#endif

/*
	TestStrCustomFmt

	Test function.
*/
#ifdef STRCUSTOMFMT_BUILD_TEST_FNCTS
	void TestStrCustomFmt (void);
#else
	#define TestStrCustomFmt()
#endif

EXTERN_C_END

#endif														// Of #ifndef STRCUSTOMFMT_H.
