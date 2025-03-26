/****************************************************************************************

	File		membuf.h
	Why:		Helpers for memory buffers
	OS:			C99
	Created:	2022-05-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-05-11	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Module/unit that provides a simplistic buffer (SMEMBUF).
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

#ifndef U_MEMBUF_H
#define U_MEMBUF_H

#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./functionptrtpydef.h"
		#include "./restrict.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/functionptrtpydef.h"
		#include "./../pre/restrict.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifdef _DEBUG
	// Define DEBUG and undefine RELEASE.
	#ifndef DEBUG
	#define DEBUG
	#endif
	#ifndef UBF_DEBUG
	#define UBF_DEBUG
	#endif
	#ifdef	_RELEASE
	#undef	_RELEASE
	#endif
	#ifdef	RELEASE
	#undef	RELEASE
	#endif
	#ifdef	UBF_RELEASE
	#undef	UBF_RELEASE
	#endif
#endif

// Aligns the supplied size to the specified PowerOfTwo
#ifndef ALIGN_SIZE
#define ALIGN_SIZE(sizeToAlign, PowerOfTwo)				\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif
#ifndef ALIGNED_SIZE
#define ALIGNED_SIZE(sizeToAlign, PowerOfTwo)			\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif

EXTERN_C_BEGIN

/*
	The structure that holds the buffer and its length. It is meant to be a generic
	buffer. If a required type is missing, please feel free to add it.
*/
typedef struct smembuf
{
	union
	{
		void			*pvoid;
		char			*pch;
		const char      *pcc;
		signed char		*psc;
		unsigned char	*puc;
		size_t			*pst;
		uint64_t		*pu64;
	} buf;
	size_t				size;
	#ifdef DEBUG
		char			initComplete;
	#endif
} SMEMBUF;

/*
	initSMEMBUF

	Initialises the SMEMBUF structure p points to.
*/
#ifndef DEBUG
	#define initSMEMBUF(p)								\
		(p)->buf.pvoid		= NULL;						\
		(p)->size			= 0
#else
	#define initSMEMBUF(p)								\
		(p)->buf.pvoid		= NULL;						\
		(p)->size			= 0;						\
		(p)->initComplete	= 'A'
#endif

/*
	INITSMEMBUF

	Initialises the SMEMBUF structure s.
*/
#ifndef DEBUG
	#define INITSMEMBUF(s)								\
		(s).buf.pvoid		= NULL;						\
		(s).size			= 0
#else
	#define INITSMEMBUF(s)								\
		(s).buf.pvoid		= NULL;						\
		(s).size			= 0;						\
		(s).initComplete	= 'A'
#endif


/*
	SMEMBUF_INITIALISER
	SMEMBUF_INITIALIZER

	For automatic and static structures.
*/
#ifndef DEBUG
	#define SMEMBUF_INITIALISER							\
		{												\
			{NULL},										\
			0											\
		}
#else
	#define SMEMBUF_INITIALISER							\
		{												\
			{NULL},										\
			0,											\
			'A'											\
		}
#endif
// For the Muricans.
#define SMEMBUF_INITIALIZER	SMEMBUF_INITIALISER

/*
	initSMEMBUFtoSize

	Allocates a buffer size of s and initialises the structure.
*/
#ifndef DEBUG
	#define initSMEMBUFtoSize(p,s)						\
		(p)->buf.pvoid		= ubf_malloc (s);			\
		if ((p)->buf.pvoid)								\
			(p)->size		= s;						\
		else											\
			(p)->size		= 0
#else
	#define initSMEMBUFtoSize(p,s)						\
		(p)->buf.pvoid		= ubf_malloc (s);			\
		if ((p)->buf.pvoid)								\
			(p)->size		= s;						\
		else											\
			(p)->size		= 0;						\
		(p)->initComplete	= 'A';
#endif

/*
	setToSizeSMEMBUF

	Sets the size of the buffer of the SMEMBUF structure pb points to to exactly size siz,
	if it is not identical to size yet by calling ubf_realloc () or ubf_free () and
	ubf_malloc () on it. If the new size is smaller then the current one, ubf_realloc () is
	called to resize the buffer. In this case there's a good chance the current content of
	the buffer is preserved unless ubf_realloc () fails. When the parameter size is greater
	than the current size of the buffer, the function calls ubf_free () and ubf_malloc () to
	accommodate for the new size. The current content of the buffer is lost in this case.

	Note that this function reallocates or frees and newly allocates the buffer size every time
	the parameter siz is not exactly the size of the existing buffer, even if size is smaller
	and a reallocation would actually not be required to hold the intended data. Consider
	calling growToSizeSMEMBUF () instead, which only reallocates when the buffer is too small.
	
	The function returns a pointer to ps->buf.pvoid.
	
	If the function fails it calls doneSMEMBUF () on the structure to free its memory block and
	make it unusable. Check with isUsableSMEMBUF() if the structure can be used afterwards.
	Note that the functions returning a value unequal to NULL alone is not a reliable way of
	determining that the function succeeded.
*/
void *setToSizeSMEMBUF (SMEMBUF *pb, size_t siz);
TYPEDEF_FNCT_PTR (void *, setToSizeSMEMBUF) (SMEMBUF *pb, size_t siz);

/*
	growToSizeSMEMBUF

	Grows the buffer of the SMEMBUF structure pb points to to size siz via a call to
	ubf_realloc () and/or ubf_malloc () if it is smaller than siz. If the size is already at
	least siz the function does not change the buffer. In other words the buffer can only
	grow but never shrinks, which is what you most likely want.

	The function returns a pointer to ps->buf.pvoid.
	
	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeSMEMBUF (SMEMBUF *pb, size_t siz);
TYPEDEF_FNCT_PTR (void *, growToSizeSMEMBUF) (SMEMBUF *pb, size_t siz);

/*
	growToSizeSMEMBUF64aligned

	The function is identical to growToSizeSMEMBUF () but always aligns the size to
	64 octets/bytes.

	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeSMEMBUF64aligned (SMEMBUF *pb, size_t siz);
TYPEDEF_FNCT_PTR (void *, growToSizeSMEMBUF64aligned) (SMEMBUF *pb, size_t siz);

/*
	freeSMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer but does not
	initialise it again with initSMEMBUF(). To re-use the structure, a call to
	initSMEMBUF() is required.

	Not to be called on structures that do not have any buffer allocated.

	This function/macro is probably a few CPU cycles faster than doneSMEMBUF ()
	for structures that won't be re-used.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void freeSMEMBUF (SMEMBUF *pb);
	TYPEDEF_FNCT_PTR (void, freeSMEMBUF) (SMEMBUF *pb);
#else
	#define freeSMEMBUF(pb)								\
		ubf_free ((pb)->buf.pvoid)
#endif

/*
	doneSMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer and initialises it
	with initSMEMBUF() so that it can/could be re-used.

	Not to be called on structures that do not have any buffer allocated.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void doneSMEMBUF (SMEMBUF *pb);
	TYPEDEF_FNCT_PTR (void, doneSMEMBUF) (SMEMBUF *pb);
#else
	#define doneSMEMBUF(p)								\
		freeSMEMBUF (p);								\
		initSMEMBUF (p)
#endif

/*
	DONESMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer and initialises it
	with initSMEMBUF() so that it can/could be re-used.

	Not to be called on structures that do not have any buffer allocated.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#define DONESMEMBUF(s) doneSMEMBUF (&(s))
#else
	#define DONESMEMBUF(s)								\
		freeSMEMBUF (&(s));								\
		INITSMEMBUF (s)
#endif

/*
	isUsableSMEMBUF
	
	Evaluates to true if the structure has a buffer and a size. If the evaluation
	passes it can be assumed that a previous call to any of the functions or macros
	in this module/unit has passed and that the structure can be used safely
	afterwards with the set/agreed buffer size.
*/
#define isUsableSMEMBUF(pb)								\
	((pb)->buf.pvoid && (pb)->size)

/*
	isInitialisedSMEMBUF

	Evaluates to true in debug versions if the structure has been initialised. This may
	help find some bugs when a structure is not initialised before being used.
*/
#ifdef DEBUG
	#define isInitialisedSMEMBUF(pb)					\
		('A' == (pb)->initComplete)
#else
	#define isInitialisedSMEMBUF(pb)					\
		(true)
#endif

/*
	copySMEMBUF

	Copies the buffer of src into dst. The buffer size of dst does not shrink.

	The function does not return a value. Check with isUsableSMEMBUF (dst) to see if the
	copy operation was successful.
*/
void copySMEMBUF (SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src)
;
TYPEDEF_FNCT_PTR (void, copySMEMBUF)
	(SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src)
	;

/*
	copySMEMBUFsiz

	Copies the buffer of src into dst up to a size of siz. The buffer size of dst does
	not shrink.

	The function does not return a value. Check with isUsableSMEMBUF (dst) to see if the
	copy operation was successful.
*/
void copySMEMBUFsiz (SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src, size_t siz)
;
TYPEDEF_FNCT_PTR (void, copySMEMBUFsiz)
	(SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src, size_t siz)
	;

EXTERN_C_END

#endif														// Of #ifndef U_MEMBUF_H.
