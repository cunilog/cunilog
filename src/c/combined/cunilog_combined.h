/****************************************************************************************

	File:		head.h
	Why:		Provides the head of the combined cunilog.h header file.
	OS:			C99.
	Author:		Thomas
	Created:	2024-08-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-01	Thomas			Created.

****************************************************************************************/

#ifndef CUNILOG_USE_COMBINED_MODULE
#define CUNILOG_USE_COMBINED_MODULE
#endif

/*
	Our include guard.
	The #endif is in bottom.h.
*/
#ifndef CUNILOG_COMBINED_INCLUDED
#define CUNILOG_COMBINED_INCLUDED
/****************************************************************************************

	Project:	cunilog
	File:		cunilogversion.h
	Why:		
	OS:			
	Autor:		Thomas
	Created:	2024-10-16
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-16	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef HAVE_CUNILOG_VERSION__H
#define HAVE_CUNILOG_VERSION__H

// Some constants.
#define CUNILOG_PROJECT_NAME	"cunilog"					// Name of the project.
#define CUNILOG_PROGRAM_NAME	"cunilog"					// The application's name.
#define CUNILOG_PROGRAM_EXE		CUNILOG_PROGRAM_NAME ".exe"
#define CUNILOG_PROGRAM_DESCR	"Logging utility"			// Its description.
#define CUNILOG_PROGRAM_COMPANY "-"							// Company.
#define CUNILOG_PROGRAM_AUTHOR	"Thomas"					// Author.
#define CUNILOG_PROGRAM_EMAIL	"-"							// Email.

// Version numbers.
#define CUNILOG_VERSION_MAJOR	1							// Major version.
#define CUNILOG_VERSION_MINOR	0							// Minor version.
#define CUNILOG_VERSION_SUB		2							// Subversion for maintenance.
#define CUNILOG_VERSION_BUILD	6							// Build number.
#define CUNILOG_VERSION_YEAR	"2025"						// Copyright year.

// Convert constants to strings using ANSI stringify operator.
#define STRINGIFY(x) #x

// Convert constants to strings while expanding macros.
//	This is actually a helper define to force macro expansion.
#define EXPANDSTRINGIFY(x) STRINGIFY(x)

// Version string for display on startup.
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR)
#if (CUNILOG_VERSION_SUB != 0)
#undef CUNILOG_VERSION_STRING
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) "." EXPANDSTRINGIFY(CUNILOG_VERSION_SUB)
#endif
#if (CUNILOG_VERSION_BUILD != 0)
#undef CUNILOG_VERSION_STRING
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) "." EXPANDSTRINGIFY(CUNILOG_VERSION_SUB) \
	"." EXPANDSTRINGIFY(CUNILOG_VERSION_BUILD)
#endif
// Version string for executable version information.
#define CUNILOG_VERSION_RESOURCE	EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) ", " \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) ", " EXPANDSTRINGIFY(CUNILOG_VERSION_SUB) \
	", " EXPANDSTRINGIFY(CUNILOG_VERSION_BUILD)

// Copyright notice in executable version information.
#define CUNILOG_VERSION_COPYRIGHT	"Copyright (C) " CUNILOG_VERSION_YEAR \
	", " CUNILOG_PROGRAM_AUTHOR

#endif															// Of #ifndef HAVE_CUNILOG_VERSION__H.
/****************************************************************************************

	File:		cunilogdefs.h
	Why:		Required definitions for Cunilog to build.
	OS:			-
	Author:		Thomas
	Created:	2024-11-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-06	Thomas			Created.

****************************************************************************************/

/*
	The definitions in this module are required for Cunilog to build.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_CUNILOGDEFS_H
#define U_CUNILOGDEFS_H

/*
	Suppresses the MSVC warnings for strcpy (), memcpy (), etc.
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

/*
	Probably not required.
*/
#ifndef HAVE_STRWILDCARDS
#define HAVE_STRWILDCARDS
#endif

/*
	For MoveToRecycleBinU8 ().
*/
#ifndef HAVE_SHELLAPI
#define HAVE_SHELLAPI
#endif

/*
	For GetDefaultUserProfileDirectoryU8 ().
*/
#ifndef HAVE_USERENV
#define HAVE_USERENV
#endif

#endif														// Of #ifndef U_CUNILOGDEFS_H.
/****************************************************************************************

	File		externC.h
	Why:		Macros for the "extern C" declarations.
	OS:			-
	Created:	2020-12-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-11	Thomas			Created. Copied from ubf_type_definitions.h.
2024-07-09	Thomas			Master version is now in folder cunilog.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef EXTERN_C_H
#define EXTERN_C_H

/*
	BEGIN_C_DECLS		END_C_DECLS
	EXTERN_C_BEGIN		EXTERN_C_END

	Lets C++ compilers know that this is C, not C++.

	Idea and original version nicked from
	https://code.woboq.org/userspace/glibc/misc/sys/cdefs.h.html#117 .

	Leading double underscores removed to get rid of compiler warnings.
	Two different flavours can be used: BEGIN_C_DECLS and END_C_DECLS,
	and EXTERN_C_BEGIN and EXTERN_C_END.
*/
// BEGIN_C_DECLS and END_C_DECLS.
#ifdef	__cplusplus
	#ifndef BEGIN_C_DECLS
	#define BEGIN_C_DECLS        extern "C"	{
	#endif
	#ifndef END_C_DECLS
	#define END_C_DECLS						}
	#endif
#else
	#ifndef BEGIN_C_DECLS
	#define BEGIN_C_DECLS
	#endif
	#ifndef END_C_DECLS
	#define END_C_DECLS
	#endif
#endif
// EXTERN_C_BEGIN and EXTERN_C_END.
#ifdef	__cplusplus
	#ifndef EXTERN_C_BEGIN
	#define EXTERN_C_BEGIN       extern "C"	{
	#endif
	#ifndef EXTERN_C_END
	#define EXTERN_C_END					}
	#endif
#else
	#ifndef EXTERN_C_BEGIN
	#define EXTERN_C_BEGIN
	#endif
	#ifndef EXTERN_C_END
	#define EXTERN_C_END
	#endif
#endif

#endif														// Of #ifndef EXTERN_C_H.
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
	Module/unit that provides a simplistic buffer (SMEMBUF).
		
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
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
*/
void *setToSizeSMEMBUF (SMEMBUF *pb, size_t siz);

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

/*
	growToSizeSMEMBUF64aligned

	The function is identical to growToSizeSMEMBUF () but always aligns the size to
	64 octets/bytes.

	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeSMEMBUF64aligned (SMEMBUF * pb, size_t siz);

/*
	freeSMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer but does not
	initialise it again with initSMEMBUF(). To re-use the structure, a call to
	initSMEMBUF() is required.

	Not to be called on structures that do not have any buffer allocated.

	This function/macro is probably a few CPU cycles faster than doneSMEMBUF ()
	for structures that won't be re-used.
*/
#ifdef DEBUG
	void freeSMEMBUF (SMEMBUF *pb);
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
#ifdef DEBUG
	void doneSMEMBUF (SMEMBUF *pb);
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
#ifdef DEBUG
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
void copySMEMBUF (SMEMBUF *dst, SMEMBUF *src)
;

/*
	copySMEMBUFsiz

	Copies the buffer of src into dst up to a size of siz. The buffer size of dst does
	not shrink.

	The function does not return a value. Check with isUsableSMEMBUF (dst) to see if the
	copy operation was successful.
*/
void copySMEMBUFsiz (SMEMBUF *dst, SMEMBUF *src, size_t siz)
;

EXTERN_C_END

#endif														// Of #ifndef U_MEMBUF_H.
/****************************************************************************************

	File		WinAPI_U8.h
	Why:		UTF-8 versions of many Windows APIs.
	OS:			Windows
	Created:	2020-12-13

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-13	Thomas			Created.

****************************************************************************************/

/*
	This is a simple module/unit that provides UTF-8 versions of some common Windows API
	calls.

	If you need a fully-fledged UTF-8 wrapper library for the Windows API, there's a neat
	library on Github (https://github.com/thpatch/win32_utf8) that may be better suitable
	than this module/unit. Due to its design, the win32_utf8 library is more flexible and
	much more complete but also slower. The main difference is that win32_utf8 always
	allocates buffers on the heap while this module here attempts to use stack-based buffers
	if possible.

	The purpose of this module here is to keep it small, simple, and fast. Only a small
	subset of the Windows API is supported. None of the Window system (GUI) functions are
	implemented.
	
	Most functions that work with files and/or folders exist in two versions: One for
	standard paths that allow for relative paths and paths that include path navigators
	("..\.."). These functions end in U8, as for instance in MoveFileU8 (). The other
	type of file and/or folder functions end in U8long, like for instance in
	MoveFileU8long (). These functions implicitely prepend path and filename parameters
	with a long filename prefix ("\\?\") but do not support relative paths or paths that
	contain navigators. See https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
	for details.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef WINDOWSU8_H
#define WINDOWSU8_H

#ifdef _WIN32

/*
	We do need the full header.

	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif
*/

#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../../pre/externC.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	// We need this if the Microsoft compiler is not used.
	#include <assert.h>
#endif

#ifdef HAVE_NETAPI32
	#include <lmaccess.h>
	#include <Lm.h>
	pragma comment (lib, "Netapi32.lib")
#endif
#ifdef HAVE_SHELLAPI
	#include <shellapi.h>
	#pragma comment (lib, "Shell32.lib")
#endif

#ifdef HAVE_KERNEL32
	#include <tlhelp32.h>
	#pragma comment (lib, "Kernel32.lib")
#endif
#ifdef HAVE_ADVAPI32
	// See https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew .
	#include <Lmcons.h>
	#pragma comment (lib, "Advapi32.lib")
#endif
#ifdef HAVE_SHLWAPI
	#include <shlwapi.h>
	#pragma comment (lib, "Shlwapi.lib")
#endif
#ifdef HAVE_USERENV
	#include <UserEnv.h>
	 #pragma comment (lib, "Userenv.lib")
#endif


#ifndef UBF_MEM_NO_UBFMEM
	#ifndef CUNILOG_USE_COMBINED_MODULE
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./ubfmem.h"
		#else
			#include "./../../mem/ubfmem.h"
		#endif
	#endif
#else
	#include <stdlib.h>
	#define ubf_malloc(size)			malloc (size)
	#define ubf_calloc(n,s)				calloc (n, s)
	#define ubf_realloc(p,s)			realloc (p, s)
	#define ubf_strdup(s)				strdup (s)
	#define ubf_free(ptr)				free (ptr)
	#define ubf_free_accept_NULL(ptr)	free (ptr)
	#define ubf_memcpy(b,d,s,l)			memcpy (d, s, l)
	#define ubf_memmove(b,d,s,l)		memmove (d, s, l)
	#define ubf_memset(b,d,v,l)			memset (d, v, l)
	#define ubf_memcmp(b,p1,p2,l)		memcmp (p1, p2, l)
	#define ubf_mem_init_ptr(b,s)
	#define ubf_mem_usr_ptr(b)			(b)
	#define ubf_mem_chk_ptr(b)
	#define ubf_mem_chk_bse(b)
	#define ubf_mem_test_memdbg()
	#define ubf_mem_done()
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef HAVE_MEMBUF
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./membuf.h"
		#else
			#include "./../../mem/membuf.h"
		#endif
	#endif

#endif

EXTERN_C_BEGIN

#ifndef ASSERT
#define ASSERT(x)	_ASSERT(x)
#endif
#ifndef assert
#define assert(x)	_ASSERT(x)
#endif

#ifdef _DEBUG
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif
#ifndef DEBUG
	#ifndef RELEASE
	#define RELEASE
	#endif
#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

extern WCHAR		wcLongFileNamePrefix [];					// "\\?\" prefix for very
																//	long filenames.
extern const char	ccLongFileNamePrefix [];					// The ASCII/UTF-8 version.
#define LENOFLONGFILENAMEPREFIX		(4)							// Its length, excluding
																//	the NUL-terminator.

// The threshold up to which buffers are placed on the stack as automatic
//	variables.
#ifndef BUILD_TEST_WINAPI_U8_TEST_DEBUG
	#ifndef WINAPI_U8_HEAP_THRESHOLD
	#define WINAPI_U8_HEAP_THRESHOLD		(1024)
	#endif
#else
	#ifndef WINAPI_U8_HEAP_THRESHOLD
	#define WINAPI_U8_HEAP_THRESHOLD		(1024)
	#endif
#endif

/*
	Implicit forward to backslash conversion. This was defined here for testing.
	If required/wanted, define WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH in the project.
*/
#ifndef WINAPIU8_DONT_CONVERT_FORWARD_TO_BACKSLASH
	#ifndef WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH
	//#define WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH
	#endif
#endif

/*
	reqUTF8sizeFromUTF16wchars
	
	Computes the maximum size, in octets (bytes), required by the UTF-8
	representation of a UTF-16 string with the amount of w UTF-16 characters.
	This macro can be used for buffer allocations.
	
	See https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings for more
	information.
	
	Excerpt:
	"UTF-8 requires 8, 16, 24 or 32 bits (one to four bytes) to encode a Unicode character,
	UTF-16 requires either 16 or 32 bits to encode a character, and UTF-32 always requires
	32 bits to encode a character. The first 128 Unicode code points, U+0000 to U+007F, used
	for the C0 Controls and Basic Latin characters and which correspond one-to-one to their
	ASCII-code equivalents, are encoded using 8 bits in UTF-8, 16 bits in UTF-16, and 32 bits
	in UTF-32.
	The next 1,920 characters, U+0080 to U+07FF (encompassing the remainder of almost all
	Latin-script alphabets, and also Greek, Cyrillic, Coptic, Armenian, Hebrew, Arabic, Syriac,
	Tāna and N'Ko), require 16 bits to encode in both UTF-8 and UTF-16, and 32 bits in UTF-32.
	For U+0800 to U+FFFF, i.e. the remainder of the characters in the Basic Multilingual Plane
	(BMP, plane 0, U+0000 to U+FFFF), which encompasses the rest of the characters of most of
	the world's living languages, UTF-8 needs 24 bits to encode a character, while UTF-16
	needs 16 bits and UTF-32 needs 32. Code points U+010000 to U+10FFFF, which represent
	characters in the supplementary planes (planes 1–16), require 32 bits in UTF-8, UTF-16
	and UTF-32."
	
	In other words, UTF-8 can require up to 1.5 * the size of UTF-16.
	
	Since this macro expects the amount of UTF-16 characters as its parameter, which is 2
	octets per character, it returns 2 * w + w.
*/
#define reqUTF8sizeFromUTF16wchars(w)					\
			(sizeof (WCHAR) * (w) + (w))

/*
	reqUTF16charsFromUTF8chars
	
	Computes the maximum size, in WCHARs, required by the UTF-16
	representation of a UTF-8 string with the amount of c UTF-8 octets.
	This macro can be used for buffer allocations.
	
	See https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings for more
	information.
	
	Since this macro expects the amount of UTF-8 octets as its parameter and returns
	the amount of required UTF-16 characters, which is 16 bits for each given octet,
	it returns exactly this amount, unchanged.
*/
#define reqUTF16charsFromUTF8chars(c)					\
			(c)

/*
	reqUTF16sizeFromUTF8chars
	
	Computes the maximum size, in octets (bytes), required by the UTF-16
	representation of a UTF-8 string with the amount of c UTF-8 octets.
	This macro can be used for buffer allocations.
	
	See https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings for more
	information.
	
	Since this macro expects the amount of UTF-8 octets as its parameter and returns
	the maximum amount of octets required by its UTF-8 representation, it returns
	2 * c.
*/
#define reqUTF16sizeFromUTF8chars(c)					\
			(sizeof (WCHAR) * (c))

/*
	reqUTF8size
	
	Returns the required size for the UTF-8 representation from the Windows
	UTF-16 string wcU16 points to.

	This is a function in debug versions and a macro in release builds.
*/
#ifdef DEBUG
	int reqUTF8size (const WCHAR *wcU16);
#else
	#define reqUTF8size(wcU16)							\
		WideCharToMultiByte (CP_UTF8, 0, wcU16, -1, NULL, 0, NULL, NULL)
#endif

/*
	UTF8_from_WinU16
	
	Simplified invocation of WideCharToMultiByte () that converts from Windows
	UTF-16 to UTF8.

	This is a function in debug versions and a macro in release builds.
*/
#ifdef DEBUG
	int UTF8_from_WinU16 (char *chU8, int sizeU8, const WCHAR *wcU16);
#else
	#define UTF8_from_WinU16(chU8, sizeU8, wcU16)		\
		WideCharToMultiByte (CP_UTF8, 0, wcU16, -1, chU8, sizeU8, NULL, NULL)
#endif

/*
	reqWinU16wchars
	
	Returns the required size for the Windows UTF-16 representation of the UTF-8
	string chU8 points to.

	This is a function in debug versions and a macro in release builds.
*/
#ifdef DEBUG
	int reqWinU16wchars (const char *chU8);
#else
	#define reqWinU16wchars(chU8)						\
		MultiByteToWideChar (CP_UTF8, 0, chU8, -1, NULL, 0)
#endif
#define reqWinU16size(chU8)								\
	error Function renamed to reqWinU16wchars () because it returns the amount of WCHARs required

/*
	WinU16_from_UTF8
	
	Simplified invocation of MultiByteToWideChar () that converts from UTF-8 to
	Windows UTF-16.
	
	This is a function in debug versions and a macro in release builds.

	2021-02-05: Function/macro renamed to make it clearer that it does NOT return the
	amount of bytes but the amount of WCHARs required.
*/
#ifdef DEBUG
	int WinU16_from_UTF8 (WCHAR *wcU16, int sizeU16, const char *chU8);
#else
	#define WinU16_from_UTF8(wcU16, sizeU16, chU8)		\
		MultiByteToWideChar (CP_UTF8, 0, chU8, -1, wcU16, sizeU16)
#endif

/*
	reqWinU16wcharsFileName

	Returns the required buffer size, in characters, for the wide character
	(Windows UTF-16) representation of the UTF-8 filename ccU8FileName points
	to plus the size in characters required to prepend this filename with a long
	filename prefix ("\\?\"), if it doesn't start with one yet.
	
	Call WinU16_from_UTF8_FileName () with a buffer the size of the return value
	of this function.
	
	2021-02-05: Function renamed to make it clearer that it does NOT return the
	amount of bytes but the amount of WCHARs required.
*/
int reqWinU16wcharsFileName (const char *ccU8FileName);
#define reqWinU16sizeFileName()							\
	error Function renamed to reqWinU16FileNameWCHARs () because it returns the amount of WCHARs required

/*
	HasLongFileNamePrefixW
	
	Returns or evaluates to TRUE if wcFileName starts with a long file name prefix,
	FALSE if not.
*/
#ifdef DEBUG
	BOOL HasLongFileNamePrefixW (const WCHAR *wcFileName);
#else
	#define HasLongFileNamePrefixW(wcfn)				\
		(!wcsncmp (wcfn, wcLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX))
#endif

/*
	HasLongFileNamePrefixU8
	
	Returns or evaluates to TRUE if ccFileName starts with a long file name prefix,
	FALSE if not.
*/
#ifdef DEBUG
	BOOL HasLongFileNamePrefixU8 (const char *ccFileName);
#else
	#define HasLongFileNamePrefixU8(ccfn)				\
		(!strncmp (ccfn, ccLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX))
#endif

/*
	WinU16_from_UTF8_FileName
	
	Converts the UTF-8 filename ccU8FileName points to to its Windows UTF-16
	wide character representation. The function prepends a Windows long file name
	prefix ("\\?\") to wcU16FileName if ccU8FileName doesn't already contain one.
	
	Returns the number of characters written to wcU16FileName.
*/
int WinU16_from_UTF8_FileName (WCHAR *wcU16FileName, int sizeU16, const char *ccU8FileName);

/*
	AllocWinU16_from_UTF8
	AllocWinU16_from_UTF8_00
	
	Allocates memory for the WCHAR representation of ccU8 and performs the conversion,
	returning a pointer to the UTF-8 string converted to a UTF-16 Windows wide-character
	string, or NULL if either ccU8 is NULL or the heap allocation fails.
	
	The caller is responsible for calling DoneWinU16 () on the returned pointer when it
	is not needed anymore to deallocate the memory block again.

	The function AllocWinU16_from_UTF8_00 () terminates the returned string with two NUL
	characters instead of one. Some Windows APIs require this, for instance, some members of
	a SHFILEOPSTRUCTW structure. See
	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shfileopstructw
	and check the members pFrom and pTo. Both need to be terminated with two NUL characters.
*/
WCHAR *AllocWinU16_from_UTF8 (const char *ccU8);
WCHAR *AllocWinU16_from_UTF8_00 (const char *ccU8);

/*
	AllocWinU16_from_UTF8_FileName
	
	Allocates memory for the WCHAR representation of ccU8 and performs the conversion,
	returning a pointer to the converted string at the address pwc points to, or NULL
	if either ccU8 is NULL or the heap allocation fails. The function assumes that
	ccU8FileName points to a file name and prepends the resulting wide character
	string with a long file name prefix if it is not provided in ccU8FileName.
	
	The caller is responsible for calling free () on the returned pointer when it
	is not needed anymore.
*/
WCHAR *AllocWinU16_from_UTF8_FileName (const char *ccU8FileName);

/*
	DoneWinU16
	
	This function/macro calls ubf_free () on the provided pointer pwc. It currently
	exists for aesthetic reasons only but this might change in the future if the
	allcoation method is changed.
	
	WCHAR *pwc = AllocWinU16_from_UTF8_FileName (L"Filename.ext");
	...
	DoneWinU16 (pwc);
*/
#ifdef DEBUG
	void DoneWinU16 (WCHAR *pwc);
#else
	#define DoneWinU16(p)								\
		if (p)											\
			ubf_free (p)
#endif

/*
	AllocU8_from_WinU16

	Allocates memory for the UTF-8 representation of wc16 and performs the conversion,
	returning a pointer to the Windows UTF-16 string converted to UTF-8, or NULL if
	either wc16 is NULL or the heap allocation fails.
	
	The caller is responsible for calling DoneU8 () on the returned pointer when it
	is not needed anymore to deallocate the memory associated with it.
*/
char *AllocU8_from_WinU16 (const WCHAR *wc16);

/*
	AllocU8path_from_U8path_and_WinU16FileName
	
	Returns a pointer to a newly allocated buffer that consists of the UTF-8 path ccPath
	and the file or subfolder name wcFileName, which is in Windows UTF-16. The complete
	path is then copied into the buffer and returned to the caller.
	
	The caller is responsible for calling DoneU8 () on the returned pointer.
	
	The parameter ccPath is expected to contain a valid path that was passed to the
	Windows API function FindFirstFile (). It can therefore contain wildcards in the
	filename part. See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilea
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew
	for more information on this API.
	
	The parameter wcFileName is expected to contain a filename as valid by the member
	cFileName of a WIN32_FIND_DATAW structure. See
	https://docs.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-win32_find_dataw
	for more information on this structure.
	
	Valid parameters:							Return value
	"D:\Test", L"file.ext"						"D:\\Test\\file.ext"
	"D:\Test*", L"file.ext"						"D:\\file.ext"
	"\\\\Server\share", L"file.ext"				"\\\\Server\\share\\file.ext"
	"\\\\Server\share*", L"file.ext"			"\\\\Server\\file.ext"

	To use this function, define HAVE_STRWILDCARDS and add string/strwildcards.c/h to
	the project.
*/
#ifdef HAVE_STRWILDCARDS
	char *AllocU8path_from_U8path_and_WinU16FileName (const char *ccPath, WCHAR *wcFileName);
#endif

/*
	U8pathSMEMBUF_from_U8path_and_WinU16FileName

	This function is identical to AllocU8path_from_U8path_and_WinU16FileName () but does
	not return a newly allocated buffer. Instead, it returns its result in an SMEMBUF structure
	that can be re-used for consecutive invokations and can therefore be much faster.

	Before the function is called, the caller must initialise the SMEMBUF structure pmbResult
	correctly, either with initSMEMBUF (), initSMEMBUFtoSize (), or by assigning it
	SMEMBUF_INITIALISER.

	After the function returns and the SMEMBUF structure is not required anymore, a call
	to doneSMEMBUF () or freeSMEMBUF () on it deallocates its buffer.

	To use this function, define HAVE_STRWILDCARDS and add string/strwildcards.c/h to
	the project. Additionally, define HAVE_MEMBUF and add mem/membuf.c/h to the project.

	The function returns true on success, false otherwise. The SMEMBUF structure can be
	re-used between calls to the function. When the function returns false, the SMEMBUF
	structure remains correctly initialised but the returned result is most likely not correct.
	Only when the function returns true is the SMEMBUF structure correctly filled.
*/
#if defined (HAVE_STRWILDCARDS) && defined (HAVE_MEMBUF)
	bool U8pathSMEMBUF_from_U8path_and_WinU16FileName	(
					SMEMBUF				*pmbResult,
					const char			*ccPath,
					size_t				lnPath,
					WCHAR				*wcFileName
														);
#endif

/*
	DoneU8
	
	This function/macro calls ubf_free () on the provided pointer pch. It currently
	exists for aesthetic reasons only but this might change in the future if the
	allcoation method is changed.
*/
#ifdef DEBUG
	void DoneU8 (char *pch);
#else
	#define DoneU8(p)									\
		if (p)											\
			ubf_free (p)
#endif

/*
	AllocWinU16fromU8orUseThreshold
	AllocWinU16fromU8orUseThreshold_00

	Converts the UTF-8 string pchU8 points to to its Windows UTF-16 representation.
	Returns a pointer to pwcStackVar if the required length of the Windows UTF-16
	representation of pchU8 fits in a UTF-16 string with WINAPI_U8_HEAP_THRESHOLD
	characters, including a terminating NUL character. It returs a newly allocated
	WCHAR * if the UTF-16 string does not fit in the buffer pointed to by
	pwcStackVar.
	
	The function returns a pointer to a UTF-16 string that contains the UTF-16
	representation of pchU8. The returned pointer is either pwcStackVar or a newly
	allocated memory block. The function returns NULL if pchU8 is NULL.
	
	Call DoneWinU16fromU8orUseThreshold with the returned pointer and the same
	pwcStackVar variable to conditionally deallocate the buffer again.
	
	The function AllocWinU16fromU8orUseThreshold_00 () is identical to
	AllocWinU16fromU8orUseThreshold () with the exception that it terminates the
	returned string with two NUL characters instead of one. This is a requirement
	by some Windows APIs, for instance some members of a SHFILEOPSTRUCTW structure. See
	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shfileopstructw
	and check the members pFrom and pTo. Both need to be terminated with two NULs.

	Parameters:
	pwcStackVar		Pointer to a WCHAR array (WCHAR [WINAPI_U8_HEAP_THRESHOLD]).
	pchU8			The UTF-8 string to be converted to UTF-16.
	
	Example:
	
	void WindowsAPIfunctionU8 (const char *pszU8)
	{
		WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	*pwcFileName;
		
		pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, pszU8);
		// Call the Windows API with parameter pwcFileName.
		//	...
		DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	}
*/
WCHAR *AllocWinU16fromU8orUseThreshold (WCHAR *pwcStackVar, const char *pchU8)
;
WCHAR *AllocWinU16fromU8orUseThreshold_00 (WCHAR *pwcStackVar, const char *pchU8)
;

/*
	AllocWinU16fromU8orUseThresholdLongFileName
	
	The function is identical to AllocWinU16fromU8orUseThreshold () in principal but
	assumes that the parameter pchU8 is an absolute long filename without relative
	parts. It prepends the Windows UTF-16 representation with a long filename prefix.

	Call DoneWinU16fromU8orUseThreshold with the returned pointer and the same
	pwcStackVar variable to conditionally deallocate the buffer again.
*/
WCHAR *AllocWinU16fromU8orUseThresholdLongFileName (WCHAR *pwcStackVar, const char *pchU8)
;

/*
	DoneWinU16fromU8orUseThreshold
	
	Conditionally deallocates the memory allocated by
	AllocWinU16fromU8orUseThreshold () or
	AllocWinU16fromU8orUseThresholdLongFileName ().
	
	Does nothing if pwcHeapVar is NULL. Does nothing if pwcHeapVar points to
	pwcStackVar. In all other cases ubf_free () is called with pwcHeapVar as its
	parameter.

	Debug versions abort if one of the parameters is NULL. This would indicate
	a bug somewhere.
*/
void DoneWinU16fromU8orUseThreshold (WCHAR *pwcHeapVar, WCHAR *pwcStackVar)
;

/*
	AllocU8ArgsFromWinU16
	
	Returns an array of UTF-8 strings that have been created from the UTF-16
	array of strings argvw.
	
	To free the the allocated array again, call DoneU8Args ().
*/
char **AllocU8ArgsFromWinU16 (int argc, WCHAR *argvw []);

/*
	DoneU8Args
	
	Deallocates the memory allocated by AllocU8ArgsFromWinU16 ().
*/
void DoneU8Args (int argc, char *args []);

/*
	CmdLineArgsW
	
	Retrieves an array of WCHAR with the command-line arguments. The function/
	macro is a wrapper for the Windows API function CommandLineToArgvW ().
	This is a function in debug versions, a macro in release builds.
	
	Define HAVE_SHELLAPI to use this function and link to Shell32.lib.
*/
#ifdef HAVE_SHELLAPI
	#ifdef DEBUG
		WCHAR **CmdLineArgsW (int *nArgs);
	#else
		#define CmdLineArgsW(n)							\
			CommandLineToArgvW	(						\
				GetCommandLineW (), (n)					\
								)
	#endif
#endif

BOOL CopyFileU8(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
;

BOOL CopyFileU8long(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
;

/*
	CreateAllFoldersW

	Creates all folders in wcPath and returns TRUE on success, FALSE otherwise.
	Success means that the path either has been created by the function or that
	it existed already prior to invoking the function.
*/
BOOL CreateAllFoldersW (WCHAR *wcPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateAllFoldersU8
	
	UTF-8 version of CreateAllFoldersW (). See above.
*/
BOOL CreateAllFoldersU8 (const char *szPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
;

/*
	CreateDirectoryIfNotExistsW

	Calls CreateDirectoryW () to create a directory but also returns TRUE if
	the directory exists already.
*/
BOOL CreateDirectoryIfNotExistsW (WCHAR *wcDir, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateDirectoryOrExistsU8

	Calls CreateDirectoryU8 () to create a directory but also returns TRUE if
	the directory exists already.
*/
BOOL CreateDirectoryIfNotExistsU8 (const char *ccPathU8, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateDirectoryU8
	
	UTF-8 version of CreateDirectoryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createdirectoryw
	for reference.
*/
BOOL CreateDirectoryU8(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
;

/*
	CreateDirectoryU8long
	
	The function is identical to CreateDirectoryU8 () but allows lpPathNameU8 to be
	a very long path because it prepends a long filename prefix if required. Does not
	support relative elements.
*/
BOOL CreateDirectoryU8long(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
;

/*
	CreateEventU8
	
	UTF-8 version of the Windows API function CreateEventW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventw
	for more information.
*/
HANDLE CreateEventU8(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCSTR                lpName
)
;

/*
	CreateEventExU8
	
	UTF-8 version of the Windows API function CreateEventExW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventexw
	for more information.
*/
HANDLE CreateEventExU8(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);

/*
	CreateFileMappingU8
	
	UTF-8 version of CreateFileMappingW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-createfilemappingw
	for reference.
*/
HANDLE CreateFileMappingU8(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCSTR                lpName
)
;

/*
	CreateFileU8
	
	A UTF-8 version of CreateFileW (). Its parameters are identical to the ASCII version
	of CreateFile (), which is CreateFileA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew
	for more information.
	
	The return value of the function is the return value of CreateFileW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_HANDLE_VALUE.
*/
HANDLE CreateFileU8(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
;

/*
	CreateFileU8long
	
	A UTF-8 version of CreateFileW (). Its parameters are identical to the ASCII version
	of CreateFile (), which is CreateFileA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew
	for more information.
	
	The function expects the filename in the parameter lpFileNameU8 and converts it
	from UTF-8 to the Windows UTF-16 character set (wide character set). Before invoking
	CreateFileW (), the function also prepends the UTF-16 version of the filename with
	a Windows long filename prefix ("\\?\") to support long filenames, unless the UTF-8
	filename already contains this prefix. This means that the function's length
	restriction for paths could be 32 767 characters.

	Since this function automatically prepends a long filename prefix it does not
	accept relative paths or ellipsis ("." or "..").
			
	The return value of the function is the return value of CreateFileW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_HANDLE_VALUE.
*/
HANDLE CreateFileU8long(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
;

/*
	STARTUPINFOW_from_STARTUPINFOA
	
	Converts a UTF-8 STARTUPINFOA structure to a Windows UTF-16 STARTUPINFOW
	structure. The function exists because Windows does not natively support
	UTF-8 strings in a STARTUPINFOA structure.

	Since the strings of the STARTUPINFOW structure are allocated on the heap,
	call DoneSTARTUPINFOW () on it when it is not required anymore to avoid
	memory leaks.
*/
void STARTUPINFOW_from_STARTUPINFOA (STARTUPINFOW *siw, STARTUPINFOA *sia);

/*
	DoneSTARTUPINFOW
	
	Releases the allocated string members of STARTUPINFOW sturcture siw points
	to. The function STARTUPINFOW_from_STARTUPINFOA () allocates these strings.

	Call this function on STARTUPINFOW structures that have been filled by the
	function STARTUPINFOW_from_STARTUPINFOA () to avoid memory leaks.
*/
void DoneSTARTUPINFOW (STARTUPINFOW *siw);

/*
	CloseHandleAndInvalidate
	
	Calls CloseHandle on the HANDLE phHandle points to and sets it to
	INVALID_HANDLE_VALUE.
	
	The function returns the return value of the Windows API CloseHandle ().
*/
BOOL CloseHandleAndInvalidate (HANDLE *phHandle);

/*
	CreateMutexU8
	
	UTF-8 version of the Windows API CreateMutexW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw
	for reference.

	The function returns the handle returned by CreateMutexW () or NULL if an error
	occurred.
*/
HANDLE CreateMutexU8(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  BOOL                  bInitialOwner,
  LPCSTR                lpName
)
;

/*
	CreateMutexExU8
	
	UTF-8 version of the Windows API CreateMutexExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexexw
	for reference.

	The function returns the handle returned by CreateMutexExW () or NULL if an error
	occurred.
*/
HANDLE CreateMutexExU8(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);

/*
	CreateProcessU8EnvW
	
	UTF-8 version of CreateProcessW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessw
	for reference.
	
	This function expects all parameters apart from lpEnvironment to be UTF-8 encoded.
	For lpEnvironment, the function expects a WCHAR block. Use CreateProcessU8 ()
	when the environment block is not NULL and should be UTF-8 encoded too.
*/
BOOL CreateProcessU8EnvW(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
)
;
/*
	CreateProcessU8
	
	UTF-8 version of CreateProcessW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessw
	for reference.
	
	The function expects all parameters, including lpEnvironment, to be UTF-8 encoded.
	If lpEnvironment is not NULL, it creates a Windows UTF-16 encoded version of the
	environment by calling CreateWinU16EnvironmentFromU8 (), calls
	CreateProcessU8EnvW (), and finally deallocates the UTF-16 environment block again
	before it returns. If lpEnvironment is NULL the function calls CreateProcessW ()
	directly with a value of NULL for lpEnvironment.
*/
BOOL CreateProcessU8(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
)
;

/*
	CreateSemaphoreU8
	
	UTF-8 version of CreateSemaphoreW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createsemaphorew
	for reference.

	The function returns the return value of the Windows API CreateSemaphoreW (),
	which is a handle to the semaphore or NULL if it fails.
*/
HANDLE CreateSemaphoreU8(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpNameU8
)
;

/*
	CreateServiceU8
	
	UTF-8 version of CreateServiceW ().
	See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicew .
	
	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
SC_HANDLE CreateServiceU8(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  LPCSTR    lpDisplayName,
  DWORD     dwDesiredAccess,
  DWORD     dwServiceType,
  DWORD     dwStartType,
  DWORD     dwErrorControl,
  LPCSTR    lpBinaryPathName,
  LPCSTR    lpLoadOrderGroup,
  LPDWORD   lpdwTagId,
  LPCSTR    lpDependencies,
  LPCSTR    lpServiceStartName,
  LPCSTR    lpPassword
)
;
#endif

/*
	CreateWin16tringArrayFromU8
	
	Creates a Windows UTF-16 version of the UTF-8 string array pu8 points
	to on the heap and returns a pointer to it.
	
	Call DoneWin16StringArray () on the returned pointer when it is not
	required anymore to deallocate its resources.
*/
WCHAR **CreateWin16tringArrayFromU8 (const char **pu8, WORD numStrings);


/*
	DoneWin16StringArray
	
	Deallocates the resources of a Windows UTF-16 string array created with
	CreateWin16tringArrayFromU8 ().
*/
void DoneWin16StringArray (WCHAR **pwcStringArray, WORD numStrings);

/*
	CreateWinU16EnvironmentFromU8
	
	Creates a Windows UTF-16 environment block from the given UTF-8 environment
	block. An environment block consists of continuous memory that contains
	single NUL terminated strings with the block terminated with an additional
	NUL.
	
	"Text\0"
	"Next text\0"
	"\0"
	
	The function returns a newly allocated memory block created from the UTF-8
	environment block szU8Environment points to.
	
	Call DoneWinU16Environment () to release the memory of the returned pointer
	again, which is a wrapper for free ().
*/
WCHAR *CreateWinU16EnvironmentFromU8 (const char *szU8Environment);

/*
	DoneWinU16Environment
	
	Deallocates the memory of the Windows UTF-8 environment block. Simple
	function that calls free () to look more consistent. This is a macro
	in release builds.
	
	WCHAR *pe = CreateWinU16EnvironmentFromU8 (szEnv);
	...
	DoneWinU16Environment (pe);
*/
#ifdef DEBUG
	void DoneWinU16Environment (WCHAR *wcEnvironment);
#else
	#define DoneWinU16Environment(p)					\
		free (p)
#endif

/*
	DecryptFileU8
	
	UTF-8 version of DecryptFileW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-decryptfilew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL DecryptFileU8(
  LPCSTR lpFileName,
  DWORD  dwReserved
)
;
#endif

/*
	DeleteFileU8
	
	A UTF-8 version of the DeleteFileW () Windows API. See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-deletefilew
	for reference.
*/
BOOL DeleteFileU8(
  LPCSTR lpFileNameU8
)
;

/*
	DeleteFileU8long
	
	A UTF-8 version that supports long filenames of the DeleteFileW () Windows API. See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-deletefilew
	for reference.
	
	Since the function prepends the filename with a long filename prefix ("\\?\"),
	this version does not support paths that contain "." or ".." path components.
*/
BOOL DeleteFileU8long(
  LPCSTR lpFileNameU8
)
;

/*
	EncryptFileU8
	
	UTF-8 version of EncryptFileW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-encryptfilew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL EncryptFileU8(
  LPCSTR lpFileNameU8
)
;
#endif

/*
	FileEncryptionStatusU8
	
	UTF-8 version of FileEncryptionStatusW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-fileencryptionstatusw
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL FileEncryptionStatusU8(
  LPCSTR  lpFileNameU8,
  LPDWORD lpStatus
)
;
#endif

/*
	FileExists

	Returns TRUE if the given file exists and returns FALSE
	if it doesn't. It also returns FALSE if the given file name exists
	as a directory already.
	
	Note that the function cannot determine with absolute certainty that
	a file does not exists when it returns FALSE. The file could for
	instance be a network resource that is only temporarily not available.
*/
BOOL FileExistsU8 (const char *lpszFilenameU8);

/*
	FileExistsU8long

	Returns TRUE if the given file exists and returns FALSE
	if it doesn't. It also returns FALSE if the given file name exists
	as a directory already.
	
	Note that the function cannot determine with absolute certainty that
	a file does not exists when it returns FALSE. The file could for
	instance be a network resource that is only temporarily not available.
	
	Since the function prepends the filename with a long filename prefix ("\\?\"),
	this version does not support paths that contain "." or ".." path components.
*/
BOOL FileExistsU8long (const char *lpszFilenameU8);

/*
	FileOrPathExists

	Returns TRUE if the given path or file name exists already and FALSE
	if it doesn't.

	Note that the function cannot determine with absolute certainty that
	a path does not exists when it returns FALSE. The file/directory could
	for instance be a network resource that is only temporarily not available.
*/
BOOL FileOrPathExistsU8 (const char *lpszFilenameU8);
#define FileOrDirExistsU8(fn)	FileOrPathExistsU8 (fn)

/*
	FindFirstChangeNotificationU8
	
	A UTF-8 version of FindFirstChangeNotificationW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstchangenotificationw
	for more information.
*/
HANDLE FindFirstChangeNotificationU8(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
;

/*
	FindFirstChangeNotificationU8long
	
	A UTF-8 version of FindFirstChangeNotificationW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstchangenotificationw
	for more information.
	
	Before calling FindFirstChangeNotificationW () the function prepends a long filename
	prefix ("\\?\") if lpPathNameU8 doesn't have one already.
*/
HANDLE FindFirstChangeNotificationU8long(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
;

/*
	FindFirstFileExU8
	
	A UTF-8 version of the Windows API function FindFirstFileExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
	for more information.

	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().
*/
HANDLE FindFirstFileExU8(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
;

/*
	FindFirstFileExU8long
	
	A UTF-8 version of the Windows API function FindFirstFileExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
	for more information.

	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	Before calling FindFirstFileExW () the function prepends a long filename
	prefix ("\\?\") if lpFileNameU8 doesn't start with one already. This means the function
	does not support relative paths.
*/
HANDLE FindFirstFileExU8long(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
;

/*
	FindFirstFileU8
	
	A UTF-8 version of FindFirstFileW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew
	for more information.
	
	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	The function actually calls FindFirstFileExU8 (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
	for details. The search is case-sensitive and does not return 8.3 filenames.
*/
HANDLE FindFirstFileU8(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
;

/*
	FindFirstFileU8long
	
	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	Before calling FindFirstFileU8 () the function prepends a long filename
	prefix ("\\?\") if lpFileNameU8 doesn't start with one already. This means the function
	does not support relative paths.
*/
HANDLE FindFirstFileU8long(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
;

/*
	WIN32_FIND_DATAU8
	
	UTF-8 version of a WIN32_FIND_DATAW structure. Use
	WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW () to fill it.
	
	The member cAlternateFileName is not available.
	
	Note that UTF-8 encoded data stores between 1 and 4 octets per
	character. See https://en.wikipedia.org/wiki/UTF-8 for reference.
*/
#ifndef UTF8_MAX_PATH
#define UTF8_MAX_PATH	(4 * MAX_PATH)
#endif
typedef struct win32_find_dataU8
{
	DWORD		dwFileAttributes;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		nFileSizeHigh;
	DWORD		nFileSizeLow;
	DWORD		dwReserved0;
	DWORD		dwReserved1;
	char		cFileName [UTF8_MAX_PATH];
	//WCHAR		cAlternateFileName[14];							// Not used.
	DWORD		dwFileType;
	DWORD		dwCreatorType;
	WORD		wFinderFlags;
} WIN32_FIND_DATAU8;

/*
	WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW
	
	Converts a WIN32_FIND_DATAW structure into a WIN32_FIND_DATAU8 structure.
	A WIN32_FIND_DATAU8 is version that uses UTF-8 for the cFileName member.
	
	Returns TRUE on success, FALSE otherwise. The function may return FALSE
	if the Windows UTF-16 filename does not fit in the UTF-8 cFileName
	member. See the definition of UTF8_MAX_PATH.
*/
void WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW (WIN32_FIND_DATAU8 *pwfdU8, WIN32_FIND_DATAW *pwfdW);

/*
	copyWIN32_FIND_DATAW
	
	Copies the entire WIN32_FIND_DATAW structure pwfdSrc points to to the structre
	pwfdDest points to.
*/
void copyWIN32_FIND_DATAW (WIN32_FIND_DATAW *pwfdDest, WIN32_FIND_DATAW *pwfdSrc);

/*
	copyWIN32_FIND_DATAU8

	Copies the entire WIN32_FIND_DATAU8 structure pu8fdSrc points to to the structre
	pu8fdDest points to.
*/
void copyWIN32_FIND_DATAU8 (WIN32_FIND_DATAU8 *pu8fdDest, WIN32_FIND_DATAU8 *pu8fdSrc);

/*
	FindProcessByNameU8
	
	Returns a handle to the process szProcessName.
	
	Returns a handle to the process if the process exists, FALSE otherwise.
	If the function returns NULL, use GetLastError () to obtain more
	information. The function returns NULL and sets the last error to
	ERROR_FILE_NOT_FOUND if the process could not be found.

	To build this function, define HAVE_KERNEL32 and link to Kernel32.lib.
*/
#ifdef HAVE_KERNEL32
	HANDLE FindProcessByNameU8 (const char *szProcessName);
#endif

/*
	GetComputerNameExU8
	
	UTF-8 version of GetComputerNameExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getcomputernameexw
	for reference.
*/
BOOL GetComputerNameExU8(
  COMPUTER_NAME_FORMAT NameType,
  LPSTR                lpBuffer,
  LPDWORD              lpnSize
)
;

/*
	GetComputerNameU8
	
	UTF-8 version of GetComputerNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamew
	for reference.
*/
BOOL GetComputerNameU8(
  LPSTR   lpBuffer,
  LPDWORD lpnSize
)
;

/*
	GetEnvironmentVariableU8
	
	UTF-8 version of the Windows API GetEnvironmentVariableW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getenvironmentvariablew
	for more information.
*/
DWORD GetEnvironmentVariableU8(
  char		*szNameU8,
  char		*szOut,
  DWORD		nSize
)
;

/*
	GetFileAttributesU8
	
	A UTF-8 version of GetFileAttributes (). Its parameters are identical to the ASCII
	version of GetFileAttributes (), which is GetFileAttributesA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
	for more information.
	
	The function expects the filename in the parameter lpFileNameU8 and converts it
	from UTF-8 to the Windows UTF-16 (UTF-2) character set before invoking
	GetFileAttributesW ().
	
	The return value of the function is the return value of GetFileAttributesW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_FILE_ATTRIBUTES.
*/
DWORD GetFileAttributesU8(
  LPCSTR lpFileNameU8
)
;

/*
	GetFileAttributesU8long
	
	A UTF-8 version of GetFileAttributes () that adds a long filename prefix ("\\?\") if not
	provided by the caller. The function does therefore not support relative paths.
	
	Its parameters are identical to the ASCII
	version of GetFileAttributes (), which is GetFileAttributesA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
	for more information.
	
	The function expects the filename in the parameter lpFileNameU8 and converts it
	from UTF-8 to the Windows UTF-16 (UTF-2) character set before invoking
	GetFileAttributesW ().
	
	The return value of the function is the return value of GetFileAttributesW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_FILE_ATTRIBUTES.
*/
DWORD GetFileAttributesU8long(
  LPCSTR lpFileNameU8
)
;

/*
	GetFilePointerEx
	
	Obtains the current file pointer within a file and returns it at the location
	liCurrFilePointer points to.
	
	The function returns TRUE on success, FALSE otherwise.

	The function is implemented via a call to SetFilePointerEx (). See
	https://stackoverflow.com/questions/17707020/is-there-no-getfilepointerex-windows-api-function
	for more information.
*/
BOOL GetFilePointerEx (LARGE_INTEGER *liCurrFilePointer, HANDLE hFile);

/*
	GetFileSecurityU8
	
	UTF-8 version of the Windows API GetFileSecurityW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-getfilesecurityw
	for reference.
	
	To use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL GetFileSecurityU8(
		LPCSTR					lpFileName,
		SECURITY_INFORMATION	RequestedInformation,
		PSECURITY_DESCRIPTOR	pSecurityDescriptor,
		DWORD					nLength,
		LPDWORD					lpnLengthNeeded
)
;
#endif

/*
	Our filesystem types.
*/
enum en_wapi_fs_type
{
	FS_TYPE_ERROR,
	FS_TYPE_FAT,
	FS_TYPE_FAT32,
	FS_TYPE_NTFS
};

/*
	GetFileSystemType
*/
enum en_wapi_fs_type GetFileSystemType (const char *chDriveRoot);
BOOL IsFileSystemFAT (const char *chDriveRoot);
BOOL IsFileSystemFAT32 (const char *chDriveRoot);
BOOL IsFileSystemFATorFAT32 (const char *chDriveRoot);

/*
	GetFullPathNameU8
	
	UTF-8 version of GetFullPathNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamew
	for reference.
	
	Unlike GetFullPathNameW (), the function does not return the amount of characters
	but octets (bytes) it has written to lpBuffer, excluding the terminating NUL
	character. It also expects nBufferLength in octets instead of characters.
	
	Likewise, if the buffer is not big enough to hold the returned absolute path, the
	function returns the amount of octets (bytes) required to hold the returned path,
	including a terminating NUL character.
*/
DWORD GetFullPathNameU8(
  LPCSTR lpFileName,
  DWORD  nBufferLength,
  LPSTR  lpBuffer,
  LPSTR  *lpFilePart
)
;

/*
	GetModuleFileNameU8
	
	UTF-8 version of GetModuleFileNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew
	for reference.

	To build an assertion that the provided buffer is not too small, define
	GETMODULEFILENAMEU8_ASSERT_BUFFER_TOO_SMALL .
*/
DWORD GetModuleFileNameU8(
		HMODULE	hModule,
		LPSTR	lpFilenameU8,
		DWORD	nSize
)
;

/*
	GetModuleHandleU8
	
	UTF-8 version of GetModuleHandleW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlew
	for more info.
*/
HMODULE GetModuleHandleU8(
  LPCSTR lpModuleName
);

/*
	GetPrivateProfileStringU8
	
	UTF-8 version of GetPrivateProfileStringW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getprivateprofilestringw
	for reference.
	
	Note that the return value of this function differs from the return value
	of GetPrivateProfileStringW (). The function does not return the number of
	characters but the number of octets written instead.
*/
DWORD GetPrivateProfileStringU8(
	LPCSTR lpAppName,
	LPCSTR lpKeyName,
	LPCSTR lpDefault,
	LPSTR  lpReturnedString,
	DWORD  nSize,
	LPCSTR lpFileName
)
;

/*
	GetUserNameU8
	
	UTF-8 version of GetUserNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew
	for more information.
	
	Note that the parameter pcbBuffer of this function differs from the version
	of GetUserNameW (). The function does not expect the number of characters at
	pcbBuffer but the size, in octets, of lpBuffer instead. Likewise, the function
	does not return the number of characters but the number of octets written to
	lpBuffer instead, which includes the terminating NUL character.
	
	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL GetUserNameU8(
  LPSTR   lpBuffer,
  LPDWORD pcbBuffer
)
;
#endif

/*
	GetDefaultUserProfileDirectoryU8

	This function is untested!

	UTF-8 version of GetDefaultUserProfileDirectoryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/userenv/nf-userenv-getdefaultuserprofiledirectoryw
	for more information.

	Note that the parameter lpcchSize of this function differs from the version
	of GetDefaultUserProfileDirectoryU8 (). The function does not expect the number of
	characters at lpcchSize but the size, in octets, of lpProfileDirU8 instead. Likewise, the
	function does not return the number of characters but the number of octets written to
	lpProfileDirU8 instead, which includes the terminating NUL character.

	Define HAVE_USERENV to build this function and link to Userenv.lib.
*/
#ifdef HAVE_USERENV
BOOL GetDefaultUserProfileDirectoryU8(
	LPSTR   lpProfileDirU8,
	LPDWORD lpcchSize
);
#endif

/*
	GetUserProfileDirectoryU8

	UTF-8 version of GetUserProfileDirectoryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/userenv/nf-userenv-getuserprofiledirectoryw
	for more information.

	Note that the parameter lpcchSize of this function differs from the version
	of GetUserProfileDirectoryW (). The function does not expect the number of
	characters at lpcchSize but the size, in octets, of lpProfileDirU8 instead. Likewise, the
	function does not return the number of characters but the number of octets written to
	lpProfileDirU8 instead, which includes the terminating NUL character.

	Define HAVE_USERENV to build this function and link to Userenv.lib.
*/
#ifdef HAVE_USERENV
BOOL GetUserProfileDirectoryU8(
	HANDLE  hToken,
	LPSTR   lpProfileDirU8,
	LPDWORD lpcchSize
);
#endif

/*
	GetVolumeInformationU8
	
	A UTF-8 version of GetVolumeInformationW  (). Its parameters are identical to the
	ASCII version, which is GetVolumeInformationA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationa
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationw
	for more information.
	
	The function does currently not support the full set of functionality of
	GetVolumeInformationW (). The function expects the parameters lpVolumeNameBuffer
	to be NULL and nVolumeNameSize to be 0.
	
	The return value of the function is the return value of GetVolumeInformationW ().
*/
BOOL GetVolumeInformationU8(
  LPCSTR  lpRootPathName,
  LPSTR   lpVolumeNameBuffer,
  DWORD   nVolumeNameSize,
  LPDWORD lpVolumeSerialNumber,
  LPDWORD lpMaximumComponentLength,
  LPDWORD lpFileSystemFlags,
  LPSTR   lpFileSystemNameBuffer,
  DWORD   nFileSystemNameSize
)
;

/*
	GetWinErrorTextU8
	
	Obtains a clear text message for the error code dwError. The error code is
	added to the text in parentheses and without line ending characters.
	
	The function returns TRUE on success, FALSE otherwise. A return value of
	FALSE usually means that a buffer size limit has been exceeded.
*/
BOOL GetWinErrorTextU8 (char *lpszBuf, DWORD dwSize, DWORD dwError);

/*
	InitiateSystemShutdownExU8

	UTF-8 version of the Windows API InitiateSystemShutdownExW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-initiatesystemshutdownexw
	for more information.

	To build and use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	BOOL InitiateSystemShutdownExU8(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwTimeout,
		BOOL   bForceAppsClosed,
		BOOL   bRebootAfterShutdown,
		DWORD  dwReason
	)
	;
#endif
	
	/*
	InitiateShutdownU8

	UTF-8 version of the Windows API InitiateShutdownW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-initiateshutdownw
	for more information.

	To build and use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	DWORD InitiateShutdownU8(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwGracePeriod,
		DWORD  dwShutdownFlags,
		DWORD  dwReason
	)
	;
#endif

enum en_is_cmd_argument
{
		EN_IS_CMD_ARG_ALLOW_DASH_OR_NO_DASH						// Allows "-Switch" and "Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_ONLY							// Only "-Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_DASH							// Only "--Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH					// Allows "--Switch" and "-Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH_OR_NO_DASH		// Allows double dash, no dash,
																//	and no dash at all.
	,	EN_IS_CMD_ARG_ALLOW_NO_DASH_ONLY						// Only without dash.
};

enum en_is_cmd_case_sensitive
{
		EN_IS_CMD_CASE_SENSITIVE
	,	EN_IS_CMD_CASE_INSENSITIVE
};

/*
	IsCmdArgumentSwitchW
	
	Compares the Windows UTF-16 text wcArgument points to with the Windows UTF-16
text wcConstIs points to, which is expected to be a constant string. 
	The argument can be shortened down to at least nRelevant characters. The parameter
	enHow tells the function if single or double dashes before the actual switch
	are accepted or not.
	
	The function returns TRUE if the condition for the argument is met, FALSE if
	it is not met.
	
	Example:
	if (
			IsCmdArgumentSwitchW	(
				arg, L"doit", 2,
				EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH,
				EN_IS_CMD_CASE_IGNORE_CASE
							)
		)
	{
		// "-doit"			(EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH)
		// "--doit"			(EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH)
		// "-do"			(nRelevant == 2)
		// "-Do"			(nRelevant == 2 and EN_IS_CMD_CASE_INSENSITIVE)
	}
*/
BOOL IsCmdArgumentSwitchW	(
			WCHAR							*wcArgument,
			const WCHAR						*wcConstIs,
			size_t							nRelevant,
			enum en_is_cmd_argument			enHow,
			enum en_is_cmd_case_sensitive	enCase
							)
;

/*
	IsEqualUpToW
	
	Compares wc1 with wc2 where wc2 can be shorter but must be at least n characters
	long. The parameter cse sets the comparison to case-sensitive or case-insensitive.
	
	The idea of this function is to compare command-line argument switches without
	requiring the user to provide the full name of the switch.
	
	Example:
	
	Argument should be "delete", but we want to accept "del", "dele", and "delet" in
	upper or lower-case letters too but not "delicious".
	
	if (IsEqualUpToW (arg, "delete", 3, EN_IS_CMD_CASE_INSENSITIVE))
	{	// Accepted.
	}
*/
BOOL IsEqualUpToW	(
			const WCHAR						*wc1,				// Argument.
			const WCHAR						*wc2,				// What we expect.
			size_t							n,					// Minimum length that must fit.
			enum en_is_cmd_case_sensitive	cse
					)
;

/*
	IsPathDirectoryU8
	
	Returns TRUE if the given path is a directory, FALSE otherwise. This is the
	UTF-8 version.
*/
BOOL IsPathDirectoryU8 (const char *szPath);

/*
	IsPathDirectoryW
	
	Returns TRUE if the given path is a directory, FALSE otherwise. This is the
	Windows UTF-16 version.
*/
BOOL IsPathDirectoryW (const WCHAR *wcPath);

/*
	LoadLibraryU8

	UTF-8 version of the Windows API LoadLibraryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryw
	for more information.
*/
HMODULE LoadLibraryU8(
  char *chLibFileNameU8
)
;

/*
	LookupAccountNameU8
	
	UTF-8 version of LookupAccountNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lookupaccountnamew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL LookupAccountNameU8(
  LPCSTR        lpSystemName,
  LPCSTR        lpAccountName,
  PSID          Sid,
  LPDWORD       cbSid,
  LPSTR         ReferencedDomainName,
  LPDWORD       cchReferencedDomainName,
  PSID_NAME_USE peUse
)
;
#endif

/*
	LookupAccountSidU8
	
	UTF-8 version of LookupAccountSidW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lookupaccountsidw
	for more information.
	
	To use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL LookupAccountSidU8(
	LPCSTR        lpSystemNameU8,
	PSID          Sid,
	LPSTR         NameU8,
	LPDWORD       cchNameU8,
	LPSTR         ReferencedDomainNameU8,
	LPDWORD       cchReferencedDomainNameU8,
	PSID_NAME_USE peUse
)
;
#endif

/*
	MessageBoxU8
	
	UTF-8 version of MessageBoxW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxw
	for reference.
	
	The function calls MessageBoxExU8 () with a wLanguageId parameter of 0, which uses
	the default system language.
	
	To build this function, link to User32.lib and define HAVE_USER32.
*/
#ifdef HAVE_USER32
int MessageBoxU8(
  HWND   hWnd,
  LPCSTR lpText,
  LPCSTR lpCaption,
  UINT   uType
)
;
#endif

/*
	MessageBoxExU8
	
	UTF-8 version of MessageBoxExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxexw
	for reference.
	
	To build this function, link to User32.lib and define HAVE_USER32.
*/
#ifdef HAVE_USER32
int MessageBoxExU8(
  HWND   hWnd,
  LPCSTR lpText,
  LPCSTR lpCaption,
  UINT   uType,
  WORD   wLanguageId
)
;
#endif

/*
	MaxiMiseThisConsoleWindow
	MaxiMizeThisConsoleWindow
	MaximiseThisConsoleWindow
	MaximizeThisConsoleWindow
	
	Maximises the console window of the current process, if it has one.
	
	The function returns TRUE if the current process has a console and the message
	to maximise it has been posted successfully. It returns FALSE if the message
	could not be posted or if the current process does not have a console window.
	
	To use this function, define HAVE_WINUSER and link to User32.lib.
*/
#ifdef HAVE_WINUSER
	BOOL MaxiMiseThisConsoleWindow (void);
	#define MaxiMizeThisConsoleWindow()						\
				MaxiMiseThisConsoleWindow ()
	#define MaximiseThisConsoleWindow()						\
				MaxiMiseThisConsoleWindow ()
	#define MaximizeThisConsoleWindow()						\
				MaxiMiseThisConsoleWindow ()
#endif

/*
	MiniMiseThisConsoleWindow
	MiniMizeThisConsoleWindow
	MinimiseThisConsoleWindow
	MinimizeThisConsoleWindow
	
	Minimises the console window of the current process, if it has one.
	
	The function returns TRUE if the current process has a console and the message
	to minimise it has been posted successfully. It returns FALSE if the message
	could not be posted or if the current process does not have a console window.
	
	To use this function, define HAVE_WINUSER and link to User32.lib.
*/
#ifdef HAVE_WINUSER
	BOOL MiniMiseThisConsoleWindow (void);
	#define MiniMizeThisConsoleWindow()						\
				MiniMiseThisConsoleWindow ()
	#define MinimiseThisConsoleWindow()						\
				MiniMiseThisConsoleWindow ()
	#define MinimizeThisConsoleWindow()						\
				MiniMiseThisConsoleWindow ()
#endif

/*
	RestoreThisConsoleWindow

	Restores the console window of the current process, if it has one, meaning that
	the window is resized to its normal size.
	
	The function returns TRUE if the current process has a console and the message
	to restore it has been posted successfully. It returns FALSE if the message
	could not be posted or if the current process does not have a console window.
	
	To use this function, define HAVE_WINUSER and link to User32.lib.
*/
#ifdef HAVE_WINUSER
	BOOL RestoreThisConsoleWindow (void);
#endif

/*
	UTF-8 version of MoveFileW ().
	See https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilew
	for details.
*/
BOOL MoveFileU8(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
);

/*
	MoveFileU8long
	
	UTF-8 version of MoveFileW () that supports long file names but not relative paths.
	The function prepends a long filename prefix to both parameters before passing them on
	to MoveFileW () if one is not already there.
	
	See https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilew
	for details.
*/
BOOL MoveFileU8long(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
);

/*
	MoveFileExU8

	UTF-8 version of MoveFileExW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefileexw
	for more information.
*/
BOOL MoveFileExU8(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
;

/*
	MoveFileExU8long

	UTF-8 version of MoveFileExW () that supports long file names but not relative paths.
	The function prepends a long filename prefix to both parameters before passing them on
	to MoveFileExW () if one is not already there. See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefileexw
	for more information.
*/
BOOL MoveFileExU8long(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
;

/*
	MoveFileWithProgressU8

	UTF-8 version of MoveFileWithProgressW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilewithprogressw
	for details.
*/
BOOL MoveFileWithProgressU8(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
;

/*
	MoveFileWithProgressU8long

	UTF-8 version of MoveFileWithProgressW () that supports long file names but not relative
	paths. The function prepends a long filename prefix to both parameters before passing them
	on to MoveFileWithProgressW () if one is not already there. See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilewithprogressw
	for details.
*/
BOOL MoveFileWithProgressU8long(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
;

/*
	MoveToRecycleBinU8
	MoveToRecycleBinW
	
	Moves the given file to the recycle bin. The function ending with U8 is the
	UTF-8 version while the function ending with W is the Windows UTF-16 version.

	The Windows API SHFileOperationW () requires that the filename is terninated
	with two consecutive NUL characters. While MoveToRecycleBinU8 () implicitely adds
	a second NUL terminator before it calls SHFileOperationW (), the function
	MoveToRecycleBinW () does not. The caller is responsible for providing a string
	that is NUL-terminated twice for the parameter wcFileName. See
	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shfileoperationw
	for more information.

	Returns TRUE on success, FALSE otherwise.
	
	Define #ifdef HAVE_SHELLAPI and link to Shell32.lib to build these functions.
*/
#ifdef HAVE_SHELLAPI
	BOOL MoveToRecycleBinU8 (const char *chFileName);
#endif
#ifdef HAVE_SHELLAPI
	BOOL MoveToRecycleBinW (const WCHAR *wcFileName);
#endif

/*
	NetUserEnumU8

	UTF-8 version of the NetUserEnum () Windows API.
	https://learn.microsoft.com/en-us/windows/win32/api/lmaccess/nf-lmaccess-netuserenum?redirectedfrom=MSDN

	To use this function, define HAVE_NETAPI32 and link to Netapi32.lib.
*/
#ifdef HAVE_NETAPI32
	NET_API_STATUS NET_API_FUNCTION NetUserEnumU8(
		LPCSTR  servernameU8,
		DWORD   level,
		DWORD   filter,
		LPBYTE  *bufptr,
		DWORD   prefmaxlen,
		LPDWORD entriesread,
		LPDWORD totalentries,
		PDWORD  resume_handle
	);
#endif

/*
	OpenEventU8

	UTF-8 version of OpenEventW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-openeventw
	for more information.
*/
HANDLE OpenEventU8(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
;

/*
	OpenEventLogU8

	UTF-8 version of OpenEventLogW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openeventlogw
	for more information.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
HANDLE OpenEventLogU8(
	LPCSTR lpUNCServerNameU8,
	LPCSTR lpSourceNameU8
)
;
#endif

/*
	ClearEventLogU8

	UTF-8 version of ClearEventLogW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-cleareventlogw
	for more information.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL ClearEventLogU8(
  HANDLE  hEventLog,
  LPCSTR lpBackupFileNameU8
)
;
#endif

/*
	OpenFileMappingU8

	UTF-8 version of OpenFileMappingW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-openfilemappingw
	for details.
*/
HANDLE OpenFileMappingU8(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
;

/*
	OpenMutexU8

	UTF-8 version of OpenMutexW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-openmutexw
	for details.
*/
HANDLE OpenMutexU8(
  DWORD		dwDesiredAccess,
  BOOL		bInheritHandle,
  LPCSTR	lpNameU8
)
;

/*
	OpenSCManagerU8
	
	UTF-8 version of OpenSCManagerW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-openscmanagerw
	for reference.

	Return value
	
	If the function succeeds, the return value is a handle to the specified service
	control manager database.
	If the function fails, the return value is NULL. To get extended error information,
	call GetLastError ().

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
SC_HANDLE OpenSCManagerU8(
  LPCSTR lpMachineName,
  LPCSTR lpDatabaseName,
  DWORD  dwDesiredAccess
)
;
#endif

/*
	OpenServiceU8
	
	UTF-8 version of OpenServiceW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-openservicew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
SC_HANDLE OpenServiceU8(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  DWORD     dwDesiredAccess
)
;
#endif

/*
	PathsEqualfromEndW

	Compares the executable and the argument from the end.

	Returns TRUE if the executable and the argument appear to name the same
	file.
*/
BOOL PathsEqualfromEndW (WCHAR *exe, WCHAR *arg);

/*
	PathIsUNCU8
	
	UTF-8 version of the Windows API PathIsUNCW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathisuncw
	for more information.
	
	To use this function, define HAVE_SHLWAPI and link to Shlwapi.lib.
*/
#ifdef HAVE_SHLWAPI
BOOL PathIsUNCU8(
	LPSTR	pszPathU8
)
;
#endif

/*
	PathFindNextComponentU8

	UTF-8 version of the Windows API PathFindNextComponenW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfindnextcomponentw
	for reference.

	To use this function, define HAVE_SHLWAPI. Linking to Shlwapi.lib is not required.
	Unlike PathFindNextComponenW (), this function is implemented directly in the code file and
	does not require linking to Shlwapi.lib. However, for compatibility reasons with
	PathFindNextComponenW (), it is recommended to define HAVE_SHLWAPI and link to Shlwapi.lib.
*/
#ifdef HAVE_SHLWAPI
LPCSTR PathFindNextComponentU8(
	LPSTR pszPathU8
)
;
#endif

/*
	RegisterEventSourceU8
	
	UTF-8 version of RegisterEventSourceW ().
	See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registereventsourcew .
	
	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
HANDLE RegisterEventSourceU8(
  LPCSTR lpUNCServerName,
  LPCSTR lpSourceName
)
;
#endif

/*
	RegisterServiceCtrlHandlerU8
	
	UTF-8 function of RegisterServiceCtrlHandlerW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-registerservicectrlhandlerw
	for reference.
	
	To use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerU8(
  LPCSTR             lpServiceName,
  LPHANDLER_FUNCTION lpHandlerProc
)
;
#endif

/*
	RegisterServiceCtrlHandlerExU8
	
	UTF-8 function of RegisterServiceCtrlHandlerExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-registerservicectrlhandlerexw
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerExU8(
  LPCSTR                lpServiceName,
  LPHANDLER_FUNCTION_EX lpHandlerProc,
  LPVOID                lpContext
)
;
#endif

/*
	RemoveDirectoryU8
	
	UTF-8 version of RemoveDirectoryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-removedirectoryw
	for details.
*/
BOOL RemoveDirectoryU8(
	LPCSTR lpPathNameU8
)
;

/*
	RemoveDirectoryU8long
	
	UTF-8 version of RemoveDirectoryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-removedirectoryw
	for details.
	
	This function prepends a long filename prefix if one does not exist yet. Although
	very often quite convenient due to the removal of the path limit this renders the
	function unusable for relative paths. Use RemoveDirectoryU8 () if the path is
	relative or contains path climbers ("../").
*/
BOOL RemoveDirectoryU8long(
	LPCSTR lpPathNameU8
)
;

/*
	ReportEventU8
	
	UTF-8 version of the WinAPI function ReportEventW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-reporteventw
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL ReportEventU8(
  HANDLE hEventLog,
  WORD   wType,
  WORD   wCategory,
  DWORD  dwEventID,
  PSID   lpUserSid,
  WORD   wNumStrings,
  DWORD  dwDataSize,
  LPCSTR *lpStrings,
  LPVOID lpRawData
)
;
#endif

/*
	SetConsoleCodePageToANSI
	
	Calls SetConsoleCP () and SetConsoleOutputCP () with the parameter 1252
	to switch the console to ANSI Latin I (Western).
*/
void SetConsoleCodePageToANSI (void);

/*
	SetConsoleCodePageToUTF8
	
	Calls SetConsoleCP () and SetConsoleOutputCP () with the parameter CP_UTF8
	to switch the console to UTF-8.
*/
void SetConsoleCodePageToUTF8 (void);

/*
	SetCurrentDirectoryU8
	
	UTF-8 version of SetCurrentDirectoryW ().
*/
BOOL SetCurrentDirectoryU8(
  const char *lpPathName
)
;

/*
	SetCurrentDirectoryU8long
	
	UTF-8 version of SetCurrentDirectoryU8 () that supports long filenames but does
	not accept relative paths.
*/
BOOL SetCurrentDirectoryU8long(
  const char *lpPathNameU8
)
;

/*
	SetFileAttributesU8
	
*/
DWORD SetFileAttributesU8(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
;

/*
	SetFileAttributesU8long
	
*/
DWORD SetFileAttributesU8long(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
;

/*
	SetFileSecurityU8

	UTF-8 version of SetFileSecurityW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-setfilesecurityw
	for details.

	To use/build this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL SetFileSecurityU8(
  char					*lpFileNameU8,
  SECURITY_INFORMATION	SecurityInformation,
  PSECURITY_DESCRIPTOR	pSecurityDescriptor
)
;
#endif

/*
	IsFirstArgumentExeArgumentW

	Returns TRUE if the function determined that the first argument in the argument
	list pargv points to is the name of the executable as required by POSIX systems
	but not for Windows applications.

	The function returns FALSE if it considers the first argument not being the
	name of the executable file.
*/
BOOL IsFirstArgumentExeArgumentW (int *pargc, WCHAR **pargv [])
;

/*
	SwallowExeArgumentW
	
	Examines the first element of the command-line argument list pargv points to
	and disposes of it if is an executable argument.

	Applications for POSIX systems require the first command-line argument (index 0)
	to be the path to the executable called. In Windows, this is optional. This
	function tries to identify if the first argument is the name of executable itself,
	and if it is disposes of it. This way an application can assume that the first
	argument it examines is the first argument it expects.

	The function returns TRUE if an exe argument has been swallowed, FALSE otherwise.
*/
BOOL SwallowExeArgumentW (int *pargc, WCHAR **pargv []);

/*
	InsertExeArgumentIfMissingW

	Examines the first element of the command-line argument list pargv points to
	and inserts an executable argument as the first element if it is considered missing.

	The function returns pargv if the first argument of the argument list is the
	name of the executable. If the first argument is not the name of the executable,
	the function allocates a new argument list with the name of the executable inserted
	as the first element of the list, increments the value pargc points to, and returns
	a pointer to the newly allocated argument list with the name of the executable
	inserted.
	
	In the latter case the caller is responsible for deallocating the returned
	buffer, in the former case the caller must not deallocate it. However, deallocating
	should normally not be required since to allow the new argument list to  live throughout
	the application's lifetime, and when the software exits the operating system deallocates
	it automatically.

	WCHAR **argvWithExe = InsertExeArgumentIfMissingW (&argc, &argv)) == argv)
	{
		DoStuff ();
	} else
	{
		DoStuff ();
		free (argvWithExe);
	}
*/
WCHAR **InsertExeArgumentIfMissingW (int *pargc, WCHAR **pargv [])
;

/*
	WNetGetUniversalNameU8

	UTF-8 version of the Windows API WNetGetUniversalNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winnetwk/nf-winnetwk-wnetgetuniversalnamew
	for reference.

	To use this function, define HAVE_MPR and link to Mpr.lib.
*/
#ifdef HAVE_MPR
DWORD WNetGetUniversalNameU8(
	LPCSTR  lpLocalPathU8,
	DWORD   dwInfoLevel,
	LPVOID  lpBuffer,
	LPDWORD lpBufferSize
)
;
#endif

/*
	WritePrivateProfileStringU8
	
	UTF-8 function of the Windows API WritePrivateProfileStringW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-writeprivateprofilestringw
	for details.
*/
BOOL WritePrivateProfileStringU8(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8
)
;

/*
	Only an example! The API does not support long filename prefixes!
	
	WritePrivateProfileStringU8long
	
	UTF-8 function of the Windows API WritePrivateProfileStringW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-writeprivateprofilestringw
	for details.
	
	This function prepends the filename with a long filename prefix (if it doesn't have
	one yet) before it calls WritePrivateProfileStringW (). This means the parameter
	lpFileNameU8absolute must be an absolute path and not contain relative path components
	like ".\" and "..\".
*/
/*
BOOL WritePrivateProfileStringU8long(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8absolute
)
;
*/

/*
	fprintfU8

	UTF-8 version of fprintf ().
*/
int fprintfU8 (FILE *stream, const char *format, ...);

/*
	printfU8

	UTF-8 version of printf (). See http://www.cplusplus.com/reference/cstdio/printf/ .
*/
#define printfU8(...) fprintfU8 (stdout, __VA_ARGS__)

/*
	putsU8

	UTF-8 version of puts (). See http://www.cplusplus.com/reference/cstdio/puts/ .
*/
int putsU8 (const char *strU8);


EXTERN_C_END

#endif															// Of #ifdef _WIN32.

#endif															// Of #ifndef WINDOWSU8_H.
/****************************************************************************************

	File:		platform.h
	Why:		Determines the target OS (platform) and build type;
				also includes OS specific headers.
	OS:			-
	Author:		Thomas
	Created:	2024-07-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-07-10	Thomas			Created.

****************************************************************************************/

/*
	The OS_IS_ definitions provide the target operating system, for instance OS_IS_LINUX.
	The PLATFORM_IS_ definitions provide the platform, for instance PLATFORM_IS_POSIX or
	PLATFORM_IS_WINDOWS.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_PLATFORM_H
#define U_PLATFORM_H

#include <limits.h>
#include <inttypes.h>

// Detect AIX.
#ifdef _AIX
	#ifndef OS_IS_AIX
	#define OS_IS_AIX
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Android.
#ifdef __ANDROID__
	#ifndef OS_IS_ANDROID
	#define OS_IS_ANDROID
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Linux.
#ifdef __gnu_linux__
	#ifndef OS_IS_LINUX
	#define OS_IS_LINUX
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Apple OSes.
//	See for instance
//	https://github.com/xybp888/iOS-SDKs/blob/master/iPhoneOS13.0.sdk/usr/include/TargetConditionals.h .
#if defined (__APPLE__) && defined (__MACH__)
	#include <TargetConditionals.h>
	#if defined (TARGET_OS_IPHONE) && defined (TARGET_OS_SIMULATOR) == 1
		/// iOS in simulator
		#ifndef OS_IS_IOS
		#define OS_IS_IOS
		#endif
	#elif TARGET_OS_IPHONE == 1
		// iOS on iPhone, iPad, etc.
		#ifndef OS_IS_IOS
		#define OS_IS_IOS
		#endif
	#elif TARGET_OS_MAC == 1
		// OSX.
		#ifndef OS_IS_OSX
		#define OS_IS_OSX
		#endif
	#endif
	#ifndef OS_IS_MACOS
	#define OS_IS_MACOS
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Windows.
#ifdef _WIN32
	#ifndef OS_IS_WINDOWS
	#define OS_IS_WINDOWS
	#endif
	#ifndef PLATFORM_IS_WINDOWS
	#define PLATFORM_IS_WINDOWS
	#endif
	#include <crtdbg.h>
#endif

#ifdef QT_DEBUG
	#ifndef _DEBUG
	#define _DEBUG
	#endif
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif

#ifdef DEBUG
	#ifndef _DEBUG
	#define _DEBUG
	#endif
#endif

#ifdef _DEBUG
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif

#if defined (__GNUC__)
	#ifdef NDEBUG
		#ifdef _DEBUG
		#undef _DEBUG
		#endif
		#ifdef DEBUG
		#undef DEBUG
		#endif
	#else
		#ifndef _DEBUG
		#define _DEBUG
		#endif
		#ifndef DEBUG
		#define DEBUG
		#endif
	#endif
#endif

// The Windows _ASSERT() macro.
//	See https://msdn.microsoft.com/en-us/library/ezb1wyez.aspx on how to use these macros.
//	The Wikipedia article https://en.wikipedia.org/wiki/Assert.h explains the Unix/Linux version.
#ifndef _ASSERT
	#ifdef DEBUG
		#define _ASSERT(x) assert(x)
	#else
		#define _ASSERT(ignore) ((void)0)
	#endif
#endif
#ifndef ASSERT
	#ifdef DEBUG
		#define ASSERT(x) _ASSERT(x)
	#else
		#define ASSERT(ignore) ((void)0)
	#endif
#endif

// We expect that CHAR_BIT is 8.
#if CHAR_BIT != 8
#   error Platforms with CHAR_BIT != 8 are not supported
#endif

// The directory separator.
#ifndef UBF_DIR_SEP
	#ifndef UBF_WIN_DIR_SEP
		#define UBF_WIN_DIR_SEP			'\\'
		#define UBF_WIN_DIR_SEP_STR		"\\"
	#endif
	#ifndef UBF_PSX_DIR_SEP
		#define UBF_PSX_DIR_SEP			'/'
		#define UBF_PSX_DIR_SEP_STR		"/"
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		#define UBF_DIR_SEP				UBF_WIN_DIR_SEP
		#define UBF_WRONG_DIR_SEP		UBF_PSX_DIR_SEP
		#define UBF_DIR_SEP_STR			UBF_WIN_DIR_SEP_STR
		#define UBF_WRONG_DIR_SEP_STR	UBF_PSX_DIR_SEP_STR
	#else
		#define UBF_DIR_SEP				UBF_PSX_DIR_SEP
		#define UBF_WRONG_DIR_SEP		UBF_WIN_DIR_SEP
		#define UBF_DIR_SEP_STR			UBF_PSX_DIR_SEP_STR
		#define UBF_WRONG_DIR_SEP_STR	UBF_WIN_DIR_SEP_STR
	#endif
#endif

// NUL character.
#ifndef ASCII_NUL
#define ASCII_NUL			'\0'
#endif
// End of Text.
#ifndef ASCII_ETX
#define ASCII_ETX			'\3'
#endif
// End of Transmission.
#ifndef ASCII_EOT
#define ASCII_EOT			'\4'
#endif
// TAB (tabulator).
#ifndef ASCII_TAB
#define ASCII_TAB			'\x09'
#endif
#ifndef ASCII_VT
#define ASCII_VT			'\x0B'
#endif
#ifndef ASCII_CR
#define ASCII_CR			'\x0D'
#endif
#ifndef ASCII_CR_STR
#define ASCII_CR_STR		"\x0D"
#endif
#ifndef ASCII_LF
#define ASCII_LF			'\x0A'
#endif
#ifndef ASCII_LF_STR
#define ASCII_LF_STR		"\x0A"
#endif
#ifndef ASCII_CRLF_STR
#define ASCII_CRLF_STR		"\x0D\x0A"
#endif
#ifndef ASCII_CR_VAL
#define ASCII_CR_VAL		(0x0D)
#endif
#ifndef ASCII_LF_VAL
#define ASCII_LF_VAL		(0x0A)
#endif
// End of File, CTRL-Z or SUB.
#ifndef ASCII_SUB
#define ASCII_SUB			'\x1A'
#endif
#ifndef ASCII_SPC
#define ASCII_SPC			'\x20'
#endif
#ifndef ASCII_SLASH
#define ASCII_SLASH			'/'
#endif
#ifndef ASCII_BACKSLASH
#define ASCII_BACKSLASH		'\\'
#endif

// Wrapper macro for function isdigit (). Note that isdigit () on some platforms
//	(for instance Windows) aborts if the character is outside a uint8_t range. That's why
//	we're casting it to an unsigned char.
//	See
//	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/isdigit-iswdigit-isdigit-l-iswdigit-l?view=vs-2019 .
#ifdef __cplusplus
	#define ubf_isdigit(c)								\
				(isdigit (static_cast<unsigned char>(c)))
#else
	#define ubf_isdigit(c)								\
				(isdigit ((unsigned char) c))
#endif
// Wrapper macro for function isalpha (). Note that isalpha () on some platforms
//	(for instance Windows) aborts if the character is outside a uint8_t range. That's why
//	we're casting it to an unsigned char.
#ifdef __cplusplus
	#define ubf_isalpha(c)								\
				(isalpha (static_cast<unsigned char>(c)))
#else
	#define ubf_isalpha(c)								\
				(isalpha ((unsigned char) c))
#endif

// Test for lower and upper case letters.
#define ubf_is_lower_case_letter(c)						\
	((unsigned char) c > 'a' - 1 && (unsigned char) c < 'z' + 1)
#define ubf_is_upper_case_letter(c)						\
	((unsigned char) c > 'A' - 1 && (unsigned char) c < 'Z' + 1)

/*
	ubf_isdirseparator
*/
#ifdef __cplusplus
	#define ubf_isdirseparator(c)						\
			(											\
					UBF_WIN_DIR_SEP == (c)				\
				||	UBF_PSX_DIR_SEP == (c)				\
			)
#else
	#define ubf_isdirseparator(c)						\
			(											\
					UBF_WIN_DIR_SEP == (c)				\
				||	UBF_PSX_DIR_SEP == (c)				\
			)
#endif

// The type ssize_t. See https://github.com/vlm/asn1c/issues/159 .
#ifdef _MSC_VER
	#ifndef HAVE_SSIZE_T
	#define HAVE_SSIZE_T
		#include <basetsd.h>
		typedef SSIZE_T ssize_t;
	#endif
#endif

// Typical Windows types.
#ifndef OS_IS_WINDOWS
	#ifndef ULONGLONG
	#define ULONGLONG	uint64_t
	#endif
	#ifndef LONGLONG
	#define LONGLONG	int64_t
	#endif
	#ifndef DWORD
	#define DWORD		uint32_t
	#endif
	#ifndef WORD
	#define WORD		uint16_t
	#endif
	#ifndef BYTE
	#define BYTE		uint8_t
	#endif
	
	#ifndef _FILETIME_
	typedef struct _FILETIME {
		DWORD dwLowDateTime;
		DWORD dwHighDateTime;
	} FILETIME, *PFILETIME, *LPFILETIME;
	#define _FILETIME_
	#endif
#endif

// The LARGE_INTEGER type. This has been taken from winnt.h.
#ifndef OS_IS_WINDOWS
	typedef long LONG;
	#if defined(MIDL_PASS)
	typedef struct _LARGE_INTEGER {
	#else // MIDL_PASS
	typedef union _LARGE_INTEGER {
		struct
		{
			DWORD LowPart;
			LONG HighPart;
		} DUMMYSTRUCTNAME;
		struct
		{
			DWORD LowPart;
			LONG HighPart;
		} u;
	#endif //MIDL_PASS
		LONGLONG QuadPart;
	} LARGE_INTEGER;
	// See https://msdn.microsoft.com/en-us/library/windows/desktop/aa383742(v=vs.85).aspx .
	typedef union _ULARGE_INTEGER
	{
		struct
		{
			DWORD LowPart;
			DWORD HighPart;
		} DUMMYSTRUCTNAME;
		struct
		{
			DWORD LowPart;
			DWORD HighPart;
		} u;
		ULONGLONG QuadPart;
	} ULARGE_INTEGER, *PULARGE_INTEGER;
#endif

#if defined (PLATFORM_IS_WINDOWS)
	#define Sleep_s(s)			Sleep (s * 1000)
	#define Sleep_ms(mseconds)	Sleep (mseconds)
#elif defined (PLATFORM_IS_POSIX)
	#define Sleep_s(s)			sleep (s)
	// The function usleep () expects microseconds.
	#define Sleep_ms(ms)		usleep (ms * 1000)
	#define Sleep(ms)			usleep (ms * 1000)
#endif

#endif														// Of #ifndef U_PLATFORM_H.
/****************************************************************************************

	File:		ArrayMacros.h
	Why:		Macros for arrays and alignments. This header file does not have a code
				file.
	OS:			C99
	Author:		Thomas
	Created:	2022-03-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-27	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef HAVE_ARRAYMACROS_H
#define HAVE_ARRAYMACROS_H

#ifndef CUNILOG_USE_COMBINED_MODULE
	#include "./externC.h"
#endif

EXTERN_C_BEGIN

#ifndef UBF_TYPE_DEFINITIONS_INCL_H

// Some macros taken from
//	https://www.codeproject.com/Articles/567335/Essential-Macros-for-C-Programming .
// Number of elements in an array.
#ifndef GET_ARRAY_LEN
#define GET_ARRAY_LEN(arrayName) (sizeof (arrayName) / sizeof ((arrayName)[0]))
#endif
#ifndef UBF_GET_ARRAY_LEN
#define UBF_GET_ARRAY_LEN(arrayName)					\
			GET_ARRAY_LEN (arrayName)
#endif
#ifndef GET_ARRAY_MAX_IDX
#define GET_ARRAY_MAX_IDX(arrayName)					\
		((sizeof(arrayName) / sizeof ((arrayName)[0])) - 1)
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
// Checks whether the supplied size is aligned to the specified PowerOfTwo
#ifndef IS_SIZE_ALIGNED
#define IS_SIZE_ALIGNED(sizeToTest, PowerOfTwo)			\
		(((sizeToTest) & ((PowerOfTwo) - 1)) == 0)
#endif
// Allocate the structure StructName.
#ifndef ALLOC_STRUCT
#define ALLOC_STRUCT(StructName) ((StructName *) ubf_malloc (sizeof (StructName)))
#endif

#endif														// Of #ifndef UBF_TYPE_DEFINITIONS_INCL_H.

EXTERN_C_END

#endif														// Of #ifndef HAVE_ARRAYMACROS_H.
/****************************************************************************************

	File:		Warnings.h
	Why:		Macros to disable/enable some warnings.
	OS:			C99
	Author:		Thomas
	Created:	2024-08-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-07	Thomas			Created.

****************************************************************************************/

#ifdef _MSC_VER

	// Array is too small to include a terminating NUL.
	#ifndef DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()		\
		_Pragma ("warning (disable: 4295)")
	#endif

	#ifndef DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()		\
		_Pragma ("warning (default: 4295)")
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()	\
		_Pragma ("warning (disable: 4701)")
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()	\
		_Pragma ("warning (default: 4701)")
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()	\
		_Pragma ("warning (disable: 4703)")
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()	\
		_Pragma ("warning (default: 4703)")
	#endif

	// Assignment within conditional expression.
	#ifndef DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()	\
		_Pragma ("warning (disable: 4706)")
	#endif

	#ifndef DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()	\
		_Pragma ("warning (default: 4706)")
	#endif

#else

	// Array is too small to include a terminating NUL.
	#ifndef DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()
	#endif

	#ifndef DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()
	#endif

	// Assignment within conditional expression.
	#ifndef DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()
	#endif

	#ifndef DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()
	#endif

#endif														// Of #ifdef _MSC_VER.
/****************************************************************************************

	File:		SingleBits.h
	Why:		Macros for single bits.
	OS:			Platform independent
	Author:		Thomas
	Created:	2019-05-07

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-05-07	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef SINGLEBITS_H
#define SINGLEBITS_H

#define SINGLE_BIT(bitnum)									\
	(1 << bitnum)

#ifdef __cplusplus
	#define SINGLE_BIT_UINT32(bitnum)						\
		((static_cast<uint32_t>(1)) << bitnum)
#else
	#define SINGLE_BIT_UINT32(bitnum)						\
		(((uint32_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UINT64(bitnum)						\
		((static_cast<uint64_t>(1)) << bitnum)
#else
	#define SINGLE_BIT_UINT64(bitnum)						\
		(((uint64_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UINT64_NONE							\
		(static_cast<uint64_t>(0))
#else
	#define SINGLE_BIT_UINT64_NONE							\
		((uint64_t) 0)
#endif

// Short form of SINGLE_BIT_UINT64().
#ifdef __cplusplus
	#define SINGLEBIT64(bitnum)								\
		((static_cast<uint64_t>(1)) << bitnum)
#else
	#define SINGLEBIT64(bitnum)								\
		(((uint64_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLEBIT64_NONE								\
		(static_cast<uint64_t>(0))
#else
	#define SINGLEBIT64_NONE								\
		((uint64_t) 1)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UNSIGNED_INT(bitnum)					\
		((static_cast<unsigned int>(1)) << bitnum)
#else
	#define SINGLE_BIT_UNSIGNED_INT(bitnum)					\
		(((unsigned int) 1) << bitnum)
#endif

#define SetBit(val, bit)	(val | (1 << bit))					// Set.
#define ClrBit(val, bit)	(val & (~(1 << bit)))				// Clear.
#define TglBit(val, bit)	(val ^ (1 << bit))					// Toggle.
#define HasBit(val, bit)	((val >> bit) & 1)					// Check.

#endif															// Of #ifndef SINGLEBITS_H.
/****************************************************************************************

	File:		unref.h
	Why:		Some macros for unreferenced parameters/arguments etc.
	OS:			-
	Author:		Thomas
	Created:	2024-09-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-23	Thomas			Created.

****************************************************************************************/

/*
	Include this file _after_ <Windows.h> or when <Windows.h> is not included at all,
	like for instance on POSIX.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef UNREF_H_INCLUDED
#define UNREF_H_INCLUDED

#ifndef CUNILOG_USE_COMBINED_MODULE

	// Unreferenced parameters. These come from winnt.h and other sources.
	#ifndef UNREFERENCED_PARAMETER
	#define UNREFERENCED_PARAMETER(P)			\
		{										\
			(P) = (P);							\
		}
	#endif
	#ifndef UNUSED_PARAMETER
	#define UNUSED_PARAMETER(x) (void)(x)
	#endif
	#ifndef UNUSED_PARAMETER2
	#define UNUSED_PARAMETER2(x,y) UNUSED_PARAMETER(x),UNUSED_PARAMETER(y)
	#endif

	#ifndef UNREFERENCED_LOCAL_VARIABLE
	#define UNREFERENCED_LOCAL_VARIABLE(V)		(V)
	#endif
	#ifndef DBG_UNREFERENCED_PARAMETER
	#define DBG_UNREFERENCED_PARAMETER(P)		(P)
	#endif
	#ifndef DBG_UNREFERENCED_LOCAL_VARIABLE
	#define DBG_UNREFERENCED_LOCAL_VARIABLE(V)	(V)
	#endif

#endif														// Of #ifndef CUNILOG_USE_COMBINED_MODULE.

#ifndef UNUSED
#define UNUSED(var) (void)(var)
#endif

#endif														// Of #ifndef UNREF_H_INCLUDED.
/****************************************************************************************

	File		WinAPI_ReadDirFncts.h
	Why:		Functions to read directory contents
	OS:			Windows
	Created:	2022-01-15

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-01-15	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef WINAPI_READDIRFNCTS_H
#define WINAPI_READDIRFNCTS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_U8.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../../pre/externC.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef _WIN32

#ifndef HAVE_STRWILDCARDS
	#error This module requires HAVE_STRWILDCARDS to be defined and strwildcards.c/h
#endif

/*
	Parameter u of the function ReadDirectoryEntriesSDIRW_WU8 ().
*/
enum enrdirentssdirw
{
	EN_READ_DIR_ENTS_SDIRW_UTF8,
	EN_READ_DIR_ENTS_SDIRW_UTF16
};

/*
	One singly-linked list element. Note the WIN32_FIND_DATAW member, which is in
	Windows UTF-16.
*/
typedef struct sDirW
{
	struct sDirW		*_next;
	WIN32_FIND_DATAW	wfdW;
} SDIRW;

/*
	The plinth (base) of an SDIRW singly-linked list.
*/
typedef struct sDirWplinth
{
	uint64_t				nElements;						// Amount of elements in the list.
	SDIRW					*_first;						// Pointer to the first element of the
															//	singly-linked list.
	SDIRW					**_array;						// Array of sorted pointers.
	union
	{
		void				*pstrPathWorU8;					// UTF-8 or UTF-16;
		char				*chPathU8;						// UTF-8.
		unsigned char		*ucPathU8;						// Unsigned UTF-8.
		WCHAR				*wcPathU8;						// UTF-16.
	} UTF8orUTF16;
	enum enrdirentssdirw	u;
} SDIRWPLINTH;

/*
	SRDIRONEENTRYSTRUCT

	The structure passed on to the ignore callback function.
*/
typedef struct srdirOneEntryStruct
{
	union
	{
		const void			*pstrPathWorU8;					// UTF-8 or UTF-16;
		const char			*chPathU8;						// UTF-8.
		const unsigned char	*ucPathU8;						// Unsigned UTF-8.
		const WCHAR			*wcPathU8;						// UTF-16.
	} UTF8orUTF16;
	WIN32_FIND_DATAW		*pwfd;
	void					*pCustom;
	enum enrdirentssdirw	u;
} SRDIRONEENTRYSTRUCT;

/*
	Callback function for ReadDirectoryEntriesSDIRW_WU8 () that returns TRUE
	for directory entries to be ignored.
*/
typedef BOOL (*IgnoreCondCB)(SRDIRONEENTRYSTRUCT *);

/*
	Callback function for memory allocations within ReadDirectoryEntriesSDIRW_WU8 ().
	The parameter is the size of the memory block to allocate.
*/
typedef void *(*RDEMallocCB)(size_t);

/*
	ReadDirectoryEntriesSDIRW_WU8_ex

	Reads the contents of a directory/folder and returns the first element of a
	singly-linked list of SDIRW structures.

	If pdwEntries is not NULL the function returns the amount of entries found/
	enumerated at the location it points to. This is the amount of list entries
	returned.

	To deallocate the memory used by the singly-linked list, the returned pointer
	can be passed on to the ReleaseDirectoryEntriesSDIRW () function, which
	releases the list.

	The parameter strPathWorU8 can either be in Windows UTF-16 encoding or UTF-8.
	The parameter u distinguishes the character set of this parameter. Set u to
	EN_READ_DIR_ENTS_SDIRW_UTF16 for the function to expect strPathWorU8 to be
	in UTF-16. Set u to EN_READ_DIR_ENTS_SDIRW_UTF8 for the function to treat the
	path name in UTF-8.

	Note that the parameter strPathWorU8 names the path of the directory whose
	entries are to be enumerated and that this parameter can either be in UTF-8 or
	UTF-16, depending on the parameter u, but the returned SDIRW elements hold
	the filenames in the WIN32_FIND_DATAW structure wfdW, which is always in
	Windows UTF-16.

	strPathWorU8	The path whose directory entries are to be retrieved. Can be
					UTF-8 or Windows UTF-16, depending on the paramter u.

	u				Specifies the character set of the parameter strPathWorU8
					(read as "string Path W or U8").
					EN_READ_DIR_ENTS_SDIRW_UTF8		-> strPathWorU8 is in UTF-8
					EN_READ_DIR_ENTS_SDIRW_UTF16	-> strPathWorU8 is in UTF-16

	pdwEntries		Pointer to the amount of singly-linked list entries the
					function created. If this is parameter is NULL the amount is
					not returned.

	pIgnore			Callback function that returns TRUE for each entry to be
					ignored. Entries for which this function returns FALSE are
					added to the singly-linked list. If this parameter is NULL,
					the default callback function
					ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition () will be
					called to determine whether an entry should be ignored or not.
					The default function ignores the entries ".", "..", and hidden
					and system files. See the definition of the function
					ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition () in the code
					file for reference.

	pCustom			A custom pointer argument passed on to the callback function
					pIgnore as the member pCustom of the SRDIRONEENTRYSTRUCT structure
					that can be used for custom data by the caller. This can be NULL
					if it is not required.

	pMalloc			A custom memory allocation function. Basically a replacement
					for malloc () or ubf_malloc (). If this parameter is NULL
					ubf_malloc () is used for allocating list elements.

	The function returns NULL if the directory is empty or if there is not enough
	space on the heap to allocate memory for all directory entries.

	In case of a heap error, the function sets *pdwEntries to (DWORD) -1, provided
	that pwdEntries is not NULL. It is therefore recommended to provide the
	parameter pdwEntries to distinguish between an empty folder and a heap error.
	Alternatively GetLastError () returns ERROR_NOT_ENOUGH_MEMORY as an indicator.
	When not enough space is available on the heap, the function releases already
	created list elements first.

	The caller is responsible for calling ReleaseDirectoryEntriesSDIRW () on the
	returned singly-linked liste when the data is not required anymore.
*/
SDIRW *ReadDirectoryEntriesSDIRW_WU8_ex	(
						void					*strPathWorU8,
						enum enrdirentssdirw	u,
						DWORD					*pdwEntries,
						IgnoreCondCB			pIgnore,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;

/*
	ReadDirectoryEntriesSDIRW_W
	ReadDirectoryEntriesSDIRW_U8

	These functions read the contents of a directory/folder and return the first
	element of a singly-linked list of SDIRW structures. They call
	ReadDirectoryEntriesSDIRW_WU8_ex () with the appropriate parameter for the
	character set of the path parameter. ReadDirectoryEntriesSDIRW_W () calls
	ReadDirectoryEntriesSDIRW_WU8_ex () with a parameter u of
	EN_READ_DIR_ENTS_SDIRW_UTF16 while ReadDirectoryEntriesSDIRW_U8 () calls it
	with a paramter u of EN_READ_DIR_ENTS_SDIRW_UTF8.

	Like ReadDirectoryEntriesSDIRW_WU8_ex (), if pdwEntries is not NULL the functions
	return the amount of entries found/enumerated at the location this parameter
	points to.

	To deallocate the memory used by the singly-linked list the returned pointer
	can be passed on to the ReleaseDirectoryEntriesSDIRW () function, which
	releases the list.

	Note that in case of the UTF-8 version of the function the parameter strPathU8
	uses the UTF-8 character set. This is in contrast to the returned SDIRW elements.
	The filenames in the WIN32_FIND_DATAW structure wfdW are in Windows UTF-16.
*/
SDIRW *ReadDirectoryEntriesSDIRW_W		(
						WCHAR					*wstrPath,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;
SDIRW *ReadDirectoryEntriesSDIRW_U8		(
						char					*strPathU8,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;

/*
	ReleaseDirectoryEntriesSDIRW

	Releases the singly-linked list swd points to from the heap. The function
	always returns NULL.

	Use ReleaseDirectoryEntriesSDIRW_cnt () instead to retrieve the amount of directory
	entries released.
*/
SDIRW *ReleaseDirectoryEntriesSDIRW (SDIRW *swd);

/*
	ReleaseDirectoryEntriesSDIRW_cntReleaseDirectoryEntriesSDIRW_cnt

	Releases the singly-linked list swd points to from the heap and returns the
	amount of list elements freed. Use the function ReleaseDirectoryEntriesSDIRW ()
	instead if the amount of list elements freed is not required.
*/
uint64_t ReleaseDirectoryEntriesSDIRW_cnt (SDIRW *swd);

/*
	The callback function for ForEachDirectoryEntryU8 ().

	The function ForEachDirectoryEntryU8 () stops when the callback function returns
	FALSE.
*/
/* Obsolete declaration.
typedef bool (*pForEachDirEntryU8) (SRDIRONEENTRYSTRUCT *psdE, void *pCustom);
*/
typedef bool (*pForEachDirEntryU8) (SRDIRONEENTRYSTRUCT *psdE);

/*
	ForEachDirectoryEntryU8_Ex
	ForEachDirectoryEntryU8

	Enumerates the UTF-8 directory strPathU8 points to and calls the callback
	function fedEnt for each found file or folder entry.

	The function ForEachDirectoryEntryU8_Ex () uses a re-usable SMEMBUF structure for its
	internal heap allocations while ForEachDirectoryEntryU8 () does not, which makes
	ForEachDirectoryEntryU8_Ex () slightly faster when a directory contains many subfolders.

	strPathU8			The path as a UTF-8 string.
	fedEnt				Pointer to the callback function. The function is called
						for each found entry.
	pCustom				Pointer to custom data that is passed on to the callback
						function.
	*pnSubLevels		A pointer to an unsigned int variable that contains the
						amount of subfolder levels to enumerate. If this parameter
						is NULL or points to a value of 0, only the folder in strPathU8
						is processed. Any other number specifies the amount of
						subfolders to be enumerated by recursively calling this
						function. The function uses the variable to count its
						recursion levels. This means if it is not NULL and points
						to a value greater than 0, the function alters it for
						each subfolder level. Make sure the value is correct each
						time before the function is called.

	pmb                 Function ForEachDirectoryEntryU8_Ex () only: A pointer to an
                        initialised SMEMBUF structure the function uses as a buffer
						to store the path of the directory to process when it calls
						itself recursively (when pnSubLevels is neihter NULL nor points
						to a value of 0).
                        If there are many subfolders to process, this can reduce the
						amount of required heap allocations significantly. The caller is
						responsible for initialising the structure before the call and
						deallocating its resources again after the call.

	The function returns the amount of entries processed. Since the callback function
	is not called for the "." and ".." directory entries, these are not included in
	the return value.

	Since the function does not indicate when or if an error occurred, the caller is
	advised to check with a call to GetLastError () if the function succeeded. Do not check
	for ERROR_SUCCESS. The function buffers the system error returned either by FindFirstFileU8 ()
	or by the very last call to FindNextFileW () so that the caller does not see the system
	error code returned by FindClose (), which would be of no use.

	If no files can be found, the function is assumed to have succeeded when GetLastError ()
	returns ERROR_FILE_NOT_FOUND. In case at least one file or folder is found, the function
	is assumed to have succeeded when GetLastError () returns a value of ERROR_NO_MORE_FILES.
	Hence, expect ERROR_FILE_NOT_FOUND when the function's return value is 0, and
	ERROR_NO_MORE_FILES for return values greater than 0.

	See
	https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew and
	https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findnextfilew for
	more information.

	The function can return early if the callback function fedEnt returns false. In this case
	the error retrieved by GetLastError () is whatever the callback function set it to. For
	instance, the callback function could call SetLastError (ERROR_OPERATION_ABORTED) before
	it returns false and SetLastError (ERROR_SUCCESS) before it returns true. Upon return of
	ForEachDirectoryEntryU8 (), the caller could then check GetLastError () for
	ERROR_OPERATION_ABORTED, which means the callback function returned false, for
	ERROR_FILE_NOT_FOUND, which would indicate that no files were found, and for
	ERROR_NO_MORE_FILES, indicating success.
*/
#ifdef HAVE_MEMBUF
uint64_t ForEachDirectoryEntryU8_Ex	(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				unsigned int			*pnSubLevels,
				SMEMBUF                 *pmb
									)
;
#endif
uint64_t ForEachDirectoryEntryU8	(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				unsigned int			*pnSubLevels
									)
;

EXTERN_C_END

#endif														// Of #ifdef _WIN32.

#endif														// Of #ifndef WINAPI_READDIRFNCTS_H.
/****************************************************************************************

	File		CompressNTFS_U8.h
	Why:		Performs NTFS compression.
	OS:			Windows
	Created:	2020-12-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-06	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef COMPRESSNTFS_U8
#define COMPRESSNTFS_U8

#ifdef _WIN32

#include <stdbool.h>
#include <Windows.h>

#ifdef	__cplusplus
	extern "C"	{
#endif

/*
	CompressFileNTFS_U8ExLong
	
	Compresses or uncompresses the file in chFileName. The function calls
	CreateFileU8long () to open the file, meaning it supports very long
	paths. Filename restrictions apply, for instance path navigators ("../")
	are not supported by this function. See
	https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
	for more information. Use CompressFileNTFS_U8Ex () to support path
	navigators.
	
	usState can be:
	0 = COMPRESSION_FORMAT_NONE
	1 = COMPRESSION_FORMAT_DEFAULT
	2 = COMPRESSION_FORMAT_LZNT1
	
	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8ExLong (const char *chFileName, USHORT usState);

/*
	CompressFileNTFS_U8Ex
	
	Compresses or uncompresses the file in chFileName. The function calls
	CreateFileU8 () to open the file, meaning it does not support very long
	paths but the filename can contain path navigators ("../".
	
	usState can be:
	0 = COMPRESSION_FORMAT_NONE
	1 = COMPRESSION_FORMAT_DEFAULT
	2 = COMPRESSION_FORMAT_LZNT1
	
	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8Ex (const char *chFileName, USHORT usState);

/*
	CompressFileNTFS_U8long
	
	Compresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8ExLong ().

	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8long (const char *chFileName);

/*
	CompressFileNTFS_U8
	
	Compresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8Ex ().

	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8 (const char *chFileName);

/*
	UnCompressFileNTFS_U8long
	
	Uncompresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8ExLong ().

	Returns true on success, false otherwise.
*/
bool UnCompressFileNTFS_U8long (const char *chFileName);

/*
	UnCompressFileNTFS_U8
	
	Uncompresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8Ex ().

	Returns true on success, false otherwise.
*/
bool UnCompressFileNTFS_U8 (const char *chFileName);

/*
	enntfscompressresult

	Return values for the compression check functions.
*/
enum enntfscompressresult
{
	ntfscompress_compressed,
	ntfscompress_uncompressed,
	ntfscompress_error
};
typedef enum enntfscompressresult enntfscompressresult;

/*
	IsFileNTFSCompressedByName
	IsFileNTFSCompressedByHandle

	The functions return ntfscompress_compressed if the given file is NTFS compressed. They
	return ntfscompress_uncompressed if the file is not compressed.
	
	On error, for instance if the file doesn't exist, the functions return ntfscompress_error.
	You can call GetLastError () to obtain more details about why the functions failed.
*/
enntfscompressresult IsFileNTFSCompressedByName (const char *szFileName);
enntfscompressresult IsFileNTFSCompressedByHandle (HANDLE hFile);

#ifdef	__cplusplus
				}
#endif

#endif															// Of #ifdef _WIN32

#endif															// Of #ifndef COMPRESSNTFS_U8.
/****************************************************************************************

	File:		WinExeFileName.h
	Why:		Obtains the name of the executable.
	OS:			Windows.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef WIN_EXEFILENAME_H
#define WIN_EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

#ifdef DEBUG
	#ifndef EXEFILENAME_MALLOC_BLOCKSIZE
	#define EXEFILENAME_MALLOC_BLOCKSIZE		(32)
	#endif
#else
	#ifndef EXEFILENAME_MALLOC_BLOCKSIZE
	#define EXEFILENAME_MALLOC_BLOCKSIZE		(256)
	#endif
#endif

EXTERN_C_BEGIN

#ifdef OS_IS_WINDOWS

/*
	WinObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t WinObtainExecutableModuleName (SMEMBUF *mb)
;

/*
	WinObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path or ".exe" filename extension.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "C:/temp/app.exe" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t WinObtainAppNameFromExecutableModule (SMEMBUF *mb)
;

/*
	WinObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
size_t WinObtainPathFromExecutableModule (SMEMBUF *mb)
;

#endif														// Of #ifdef OS_IS_WINDOWS.

EXTERN_C_END

#endif														// Of #ifndef WIN_EXEFILENAME_H.
/****************************************************************************************

	File:		PsxCompressFile.h
	Why:		Module to compress files on POSIX platforms.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-17	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_PSXCOMPRESS_FILE_H
#define U_PSXCOMPRESS_FILE_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX


#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef U_PSXCOMPRESS_FILE_H.
/****************************************************************************************

	File:		PsxExeFileName.h
	Why:		Obtains the name of the executable.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-14

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-14	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef PSX_EXEFILENAME_H
#define PSX_EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	PsxObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t PsxObtainExecutableModuleName (SMEMBUF *mb)
;

/*
	PsxObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "/temp/app" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t PsxObtainAppNameFromExecutableModule (SMEMBUF *mb)
;

/*
	PsxObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
size_t PsxObtainPathFromExecutableModule (SMEMBUF *mb)
;

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef PSX_EXEFILENAME_H.
/****************************************************************************************

	File:		PsxReadDirFncts.h
	Why:		POSIX functions to read directory/folder contents.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-22

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-22	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef PSXREADDIRFNCTS_H
#define PSXREADDIRFNCTS_H

#include <stdbool.h>

#ifdef PLATFORM_IS_POSIX
	#include <dirent.h>
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"								// Currently actually not required.
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"						// Currently actually not required.
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	The structure for the callback.
*/
typedef struct sonedirent
{
	struct dirent	*dirEnt;
	void			*pCustom;
} SONEDIRENT;

/*
	The callback function for ForEachPsxDirEntry ().

	The function ForEachPsxDirEntry () stops when the callback function returns
	FALSE.
*/
typedef bool (*pForEachPsxDirEntry) (SONEDIRENT *pod);

/*
	ForEachPsxDirEntry

*/
uint64_t ForEachPsxDirEntry	(
				const char				*strFolderName,
				pForEachPsxDirEntry		fedEnt,
				void					*pCustom,
				unsigned int			*pnSubLevels
							)
;

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef PSXREADDIRFNCTS_H.
/****************************************************************************************

	File:		PsxHome.h
	Why:		Obtains a user's home directory on POSIX.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-03

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-03	Thomas			Created.

****************************************************************************************/

/*
	Functions for retrieving username, user home directory, etc. on POSIX.
	
	This module/unit can also be included on Windows builds but does not provide
	any functionality.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_PSX_HOME_H
#define U_PSX_HOME_H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	/*
	// See https://www.man7.org/linux/man-pages/man3/getpwnam.3.html .
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE
	#endif
	#ifndef _BSD_SOURCE
	#define _BSD_SOURCE
	#endif
	#ifndef _SVID_SOURCE
	#define _SVID_SOURCE
	#endif
	*/
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	InitPsxHome
	
	Initialises the module/unit. Calling this function is not required because all
	other functions initialise the module implicitely. The caller may save a few
	CPU cycles by calling this function first.
*/
bool InitPsxHome (void)
;

/*
	UserHomeDirectoryPOSIX

	Returns the current user's home folder. The optional parameter plen retrieves
	the length of the returned string, if not NULL.

	The function is only re-entrant after its first invocation.

	The function returns a pointer to a string that contains the name of the current
	user's home directory.
*/
const char *UserHomeDirectoryPOSIX (size_t *plen)
;

/*
	UserTrashFolder
	
	Returns a user's trash folder.
*/
const char *UserTrashFolder (size_t *plen)
;

EXTERN_C_END

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_BEGIN

#ifdef DEBUG
	#ifndef PSXHOME_BUILD_TEST_FNCT
	#define PSXHOME_BUILD_TEST_FNCT
	#endif
#endif

/*
	TestPsxHome
	
	Function to test this module/unit.
*/
#ifdef PLATFORM_IS_POSIX
	#ifdef PSXHOME_BUILD_TEST_FNCT
		bool TestPsxHome (void);
	#else
		#define TestPsxHome()	(true)
	#endif
#else
		#define TestPsxHome()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_PSX_HOME_H.
/****************************************************************************************

	File:		PsxTrash.h
	Why:		Handles the trash can for POSIX.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-03

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-03	Thomas			Created.

****************************************************************************************/

/*
	The name of this module is actually slightly wrong as it isn't really POSIX.
	It tries to follow the XDG specification
	(https://specifications.freedesktop.org/trash-spec/latest/)
	on trash (https://specifications.freedesktop.org/trash-spec/latest/).
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_PSX_TRASH_H
#define U_PSX_TRASH_H

#ifdef OS_IS_LINUX

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	MoveFileToTrashPOSIX

	Moves the file named in szFilename to the trash bin/can on POSIX according to the
	XDG specification. See
	https://specifications.freedesktop.org/trash-spec/latest/ for details.

	The path of szFilename can neither be relative nor can it contain path navigators
	("../"). It must be a corrected absolute path.
*/
bool MoveFileToTrashPOSIX (const char *szFilename);

EXTERN_C_END

#endif														// Of #ifdef OS_IS_LINUX.

#endif														// Of #ifndef U_PSX_TRASH_H.
/****************************************************************************************

	File:		TrashCan.h
	Why:		Trash can function for Apple devices.
	OS:			C99
	Author:		Robert Guetzkow; Thomas (wrapper module only)
	Created:	2024-10-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-21	Thomas			This wrapper module created.

****************************************************************************************/

/*
	This module is mainly a wrapper for Robert Guetzkow's trashcan_soft_delete () function
	for Apple devices. See
	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

/* MIT License
	*
	* Copyright (c) 2019 Robert Guetzkow
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	*
	* The above copyright notice and this permission notice shall be included in all
	* copies or substantial portions of the Software.
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	* SOFTWARE. 
	*/

// See	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .

#ifndef APPLE_TRASHCAN_H_INCL
#define APPLE_TRASHCAN_H_INCL

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef OS_IS_MACOS

#include <CoreFoundation/CoreFoundation.h>
#include <objc/runtime.h>
#include <objc/message.h>

#ifndef LIBTRASHCAN_ERROR
#define LIBTRASHCAN_ERROR	(0)
#endif
#ifndef LIBTRASHCAN_SUCCESS
#define LIBTRASHCAN_SUCCESS	(0)
#endif

EXTERN_C_BEGIN

/*
	trashcan_soft_delete_apple

	Robert Guetzkow's trashcan_soft_delete () function. See
	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .
*/
static int trashcan_soft_delete_apple (const char *path);

EXTERN_C_END

#endif														// Of #ifdef OS_IS_MACOS.

#endif														// Of #ifndef APPLE_TRASHCAN_H_INCL.
/****************************************************************************************

	File:		CompressFile.h
	Why:		Module to compress a file on different platforms.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-10-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-17	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_COMPRESS_FILE_H
#define U_COMPRESS_FILE_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./platform.h"
		#include "./externC.h"

		#if defined (OS_IS_WINDOWS)
			#include "./CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)
		
		#endif

	#else

		#include "./../pre/platform.h"
		#include "./../pre/externC.h"

		#if defined (OS_IS_WINDOWS)
			#include "./Windows/CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)
		
		#endif

	#endif

#endif

EXTERN_C_BEGIN

/*
	enfilecompressresult

	Return values for the compression check functions.
*/
enum enfilecompressresult
{
	fscompress_compressed,
	fscompress_uncompressed,
	fscompress_error
};
typedef enum enfilecompressresult enfilecompressresult;

/*
	IsFileCompressedByName

	Returns true if the file is already compressed, false if it isn't.
*/
#ifdef DEBUG
	enfilecompressresult IsFileCompressedByName (const char *szFilename);
#else
	#if defined (OS_IS_WINDOWS)
		#define IsFileCompressedByName(fn)				\
			IsFileNTFSCompressedByName (fn)
	#elif defined (OS_IS_LINUX)
		#define IsFileCompressedByName(fn)				\
			(false)
	#endif
#endif

/*
	FScompressFileByName

	Compresses the file szFilename and returns true on success, false otherwise.
*/
bool FScompressFileByName (const char *szFilename)
;

EXTERN_C_END

#endif														// Of #ifndef U_COMPRESS_FILE_H.
/****************************************************************************************

	File:		ExeFileName.h
	Why:		Obtains the name of the executable.
				This is the platform-independent abstraction module for the Windows
				module WinExeFileName and the POSIX module PsxExeFileName.
	OS:			C99/Windows/POSIX.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef EXEFILENAME_H
#define EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../pre/platform.h"
	#endif

	#ifdef OS_IS_WINDOWS
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./WinExeFileName.h"
		#else
			#include "./Windows/WinExeFileName.h"
		#endif
	#else
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./PsxExeFileName.h"
		#else
			#include "./POSIX/PsxExeFileName.h"
		#endif
	#endif

#endif

EXTERN_C_BEGIN

/*
	ObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainExecutableModuleName(mb)				\
		WinObtainExecutableModuleName (mb)
#else
	#define ObtainExecutableModuleName(mb)				\
		PsxObtainExecutableModuleName (mb)
#endif

/*
	ObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path or ".exe" filename extension.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "C:/temp/app.exe" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainAppNameFromExecutableModule(mb)		\
		WinObtainAppNameFromExecutableModule (mb)
#else
	#define ObtainAppNameFromExecutableModule(mb)		\
		PsxObtainAppNameFromExecutableModule (mb)
#endif

/*
	ObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainPathFromExecutableModule(mb)			\
		WinObtainPathFromExecutableModule (mb)
#else
	#define ObtainPathFromExecutableModule(mb)			\
		PsxObtainPathFromExecutableModule (mb)
#endif

EXTERN_C_END

#endif														// Of #ifndef EXEFILENAME_H.
/****************************************************************************************

	File:		ExtCompressors.h
	Why:		Interface module/unit for external compressors.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-01	Thomas			Created.

****************************************************************************************/

/*
	This module is an interface for external compressors/external compression libraries.
	This implies that when this module is used, the application requires to be linked to
	additional external libraries.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_EXTCOMPRESSORS_H
#define U_EXTCOMPRESSORS_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

	#include "./platform.h"

		#if defined (OS_IS_WINDOWS)
			//#include "./CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)

	#endif

	#else

		#include "./../pre/platform.h"

		#if defined (OS_IS_WINDOWS)
			//#include "./Windows/CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)

		#endif

	#endif

#endif


#endif														// Of #ifndef U_EXTCOMPRESSORS_H.
/****************************************************************************************

	File:		ubfdebug.h
	Why:		Contains debugging functions.
	OS:			Windows/POSIX
	Author:		Thomas
	Created:	2017-10-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2017-10-24	Thomas			Created.
2018-05-26	Thomas			Compiler warning Linux/Android fixed by changing
							 the loop variable from int to unsigned int.
2019-08-24	Thomas			Module OS/ubf_debug.c/h should be obsolete now.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_UBF_DEBUG_DEB_H_INCLUDED
#define U_UBF_DEBUG_DEB_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	#include <assert.h>
#endif

/*
	Below are the macros that turn on the functions listed in the comments on the right-
	hand side of the macro definitions.
*/
#ifndef UBF_DEBUG_HEX_DUMP
//#define UBF_DEBUG_HEX_DUMP									// When defined, enables
																//	ubf_debug_hex_dump ().
#endif
#ifdef UBF_DEBUG_NO_HEX_DUMP
	#undef UBF_DEBUG_HEX_DUMP
#endif

// When defined, enables ubf_debug_printf () and ubf_debug_puts ().
#ifdef DEBUG
	#ifndef UBF_DEBUG_USE_PRINTF
	#define UBF_DEBUG_USE_PRINTF
	#endif
#endif

// When defined, uses our output abort functions. If not, a simple
//	ABORT() macro is used. It is not recommended to uncomment this
//	definition. Rather define UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
//	in the development environment or project file.
#ifdef DEBUG
	#ifndef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#define UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#endif
#endif
#ifdef DEBUG
	#ifdef UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
		#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#undef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#endif
	#endif
#endif

#ifndef UBF_DEBUG_MSG_STRLEN
#define UBF_DEBUG_MSG_STRLEN		(4096)
#endif

// The character used to identify buffer overruns and uninitialised areas. Can (and
//	should) be used as a general filler for debug purposes.
#ifndef UBF_ERROR_CHAR
#define UBF_ERROR_CHAR	'\x55'
#endif
#ifndef UBF_ERROR_CINT
#define UBF_ERROR_CINT	0x55
#endif

EXTERN_C_BEGIN

/*
	Macros to check if all members of a structure or union have been initialised.
	Check to see if we forgot to initialise a member. This is important when more
	members are added later.
	
	UBF_DEBUG_CHECK_STRUCT_DECLARATION()
	
	Sets the character used to initialise the structure before the real initialisation
	takes place.
	
	UBF_DEBUG_CHECK_STRUCT_ASSERTION()
	
	Checks if there are any octets within the structure's memory block that haven't been
	initialised by testing that no byte contains the character set with the macro
	UBF_DEBUG_CHECK_STRUCT_DECLARATION().
	
	
	Example:
	
	typedef struct structname
	{
		int		i1;
		int		i2;
		int		i3;
		int		i4;
		int		in;
	} STRUCTNAME;
	
	void test (void)
	{
		STRUCTNAME		sn;
		
		UBF_DEBUG_CHECK_STRUCT_DECLARATION (&sn, STRUCTNAME, 0x0D);
		sn.i1 = 1;
		sn.i2 = 2;
		//...
		sn.in = -1;
		UBF_DEBUG_CHECK_STRUCT_ASSERTION (&sn, STRUCTNAME);
	}
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(pstructure, typestruct, c)				\
		unsigned int	uStructCheck;													\
		unsigned char	*chStructCheck;													\
		unsigned char	cStructCheck		= (c);										\
		memset ((pstructure), (c), sizeof (typestruct))
#else
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(c)
#endif
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)						\
		chStructCheck = (char *) (pstructure);											\
		for (uStructCheck = 0; uStructCheck < sizeof (typestruct); uStructCheck ++)		\
		{																				\
			if (*chStructCheck == cStructCheck)											\
				_ASSERT (false);														\
			++ chStructCheck;															\
		}
#else
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)
#endif

/*
	UBF_DEBUG_CHECK_CALLED_ONLY_ONCE
	
	Macro to check that the function using it is only invoked once. Useful for
	initialisation functions.
	
	UBF_DEBUG_CHECK_RESET_ONLY_ONCE
	
	Resets the flag. Useful to check that a function that is not re-entrant is
	not called again before the previous instance has returned.
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)	\
		static bool	flagname;							\
		ubf_assert (!flagname);							\
		flagname = TRUE
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)	\
		flagname = FALSE
#else
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)
#endif

/*
	UBF_DEFINE_GUARD_VAR										// Define guard variable.
	UBF_CHECK_GUARD_VAR											// Check/test guard variable.
	UBF_DEF_GUARD_VAR											// Define guard variable.
	UBF_TST_GUARD_VAR											// Check/test guard variable.
	UBF_CHK_GUARD_VAR											// Check/test guard variable.
	
	Macros to define and to check guard variables. The variable defined is of
	type char []. These macros can help find buffer overruns.
	
	Examples:
	
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	The following example checks for an overrun of the array:
	
	int		i [105];
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	...
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	If data is written beyond the array's memory location testvar is overwritten,
	at least on some platforms.
	Test data is defined with UBF_DEFINE_GUARD_VAR().
	The macro UBF_CHECK_GUARD_VAR() determines if the test variable's content has
	been destroyed.
*/
#ifdef DEBUG
	#ifndef UBF_DEFINE_GUARD_VAR
	#define UBF_DEFINE_GUARD_VAR(var, value)			\
		char	var [] = #value
	#endif
	#ifndef UBF_CHECK_GUARD_VAR
	#define UBF_CHECK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_DEF_GUARD_VAR
	#define UBF_DEF_GUARD_VAR(var, value)				\
		char	var [] = #value
	#endif
	#ifndef UBF_TST_GUARD_VAR
	#define UBF_TST_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_CHK_GUARD_VAR
	#define UBF_CHK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
#else
	#define UBF_DEFINE_GUARD_VAR(var, value)
	#define UBF_CHECK_GUARD_VAR(var, value)
	#define UBF_DEF_GUARD_VAR(var, value)
	#define UBF_TST_GUARD_VAR(var, value)
	#define UBF_CHK_GUARD_VAR(var, value)
#endif

/*
	ubf_debug_assert

	Outputs the message only if the assertion doesn't pass.
	
	ubf_debug_assert_pass

	Outputs the message chDebugMessage and then implements an _ASSERT () with bAssert.

	Use the macro UBF_DEBUG_ASSERT() or ubf_assert_msg() to fill in __FILE__ and __LINE__
	for the parameters chFilePath and uiLineNum. Both macros are identical. See
	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html for an explanation
	of the __FILE__ and __LINE__ macros. The macro ubf_assert () is probably what should
	be used as often as possible.

	In release versions these are macros that expand to nothing.
	
	It is recommended to use the ubf_assert() macro, which expects one parameter only. It
	stringifies this parameter for the output text. Since this is sometimes not possible
	due to the limitations of the preprocessor's stringify operator, or it's not
	desirable if condition and message text should differ, the macro ubf_assert_msg() can
	be used.

	Examples:

	// All these lines have the same or similar functionality:
	ubf_debug_assert (a > b, "a > b", __FILE__, __LINE__);
	UBF_DEBUG_ASSERT (a > b, "a > b", __FILE__, __LINE__);
	ubf_assert (a > b);
	ubf_assert_msg (a > b, "a > b");
	
	Explanation and further notes:
	
	Although assert () on Windows and Linux works great, it does exactly what the
	documentation says on Android: it aborts. No message, no information on where
	it stopped, nor why.
	
	ubf_assert (a > b) is a replacement for assert (). It displays a message with
	the assertion before it aborts.
	
	ubf_assert_msg (a > b, "Arbitrary message") is a replacement for assert () that
	outputs "Arbitrary message" when the assertion fails instead of the actual
	assertion.
*/
#ifdef DEBUG
	// Debug version.
	#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		void ubf_debug_assert		(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert(b, c, p, n)			\
			ASSERT (b)
	#endif
	#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		void ubf_debug_assert_pass	(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert_pass(b, c, p, n)		\
			ASSERT (b)
	#endif
	#ifndef UBF_DEBUG_ASSERT
	#define UBF_DEBUG_ASSERT(b)							\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert
	#define ubf_assert(b)								\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_msg
	#define ubf_assert_msg(b,m)							\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_message
	#define ubf_assert_message(b,m)						\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_pass
	#define ubf_assert_pass(b)							\
				ubf_debug_assert_pass (b, #b, __FILE__, __LINE__)
	#endif
	/*
		ubf_assert_Android
		
		Prints the message on Android but is a simple _ASSERT() on other platforms. That's
		because the application simply dies with an _ASSERT() on Android.
	*/
	#ifdef OS_IS_ANDROID
		#define ubf_assert_Android(b)					\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
		#define ubf_assert_Android_msg(b,m)				\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Android(b)					\
				_ASSERT (b)
		#define ubf_assert_Android_msg(b,m)				\
				_ASSERT (b)
	#endif
	/*
		ubf_assert_Linux
		
		Prints the message on Linux but is a simple _ASSERT() on other platforms.
	*/
	#ifdef OS_IS_LINUX
		#define ubf_assert_Linux(b)						\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
		#define ubf_assert_Linux_msg(b,m)				\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Linux(b)						\
				_ASSERT (b)
		#define ubf_assert_Linux_msg(b,m)				\
				_ASSERT (b)
	#endif
#else
	// Release version.
	#define ubf_debug_assert(b,m,f,l)
	#define ubf_debug_assert_pass(b,m,f,l)
	#define UBF_DEBUG_ASSERT(b)
	#define ubf_assert(b)
	#define ubf_assert_msg(b,m)
	#define ubf_assert_message(b,m)
	#define ubf_assert_pass(b)
	#ifdef UBF_ANDROID
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#else
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#endif
	#ifdef UBF_LINUX
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#else
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#endif
#endif

/*
	ubf_debug_fill_mem

	Fills the memory mem points to with UBF_ERROR_CHAR, which is 55h, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem (void *mem, size_t len);
#else
	#define ubf_debug_fill_mem(m,l)
#endif

/*
	ubf_debug_check_mem
	
	Assert that a memory block consists of UBF_ERROR_CHAR octets.
*/
#ifdef DEBUG
	void ubf_debug_check_mem (char *mem, size_t len);
#else
	#define ubf_debug_check_mem(m, l)
#endif

/*
	ubf_debug_fill_mem_with

	Fills the memory mem points to with the value of c, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem_with (void *mem, char c, size_t len);
#else
	#define ubf_debug_fill_mem_with(m, c, l)
#endif

/*
	ubf_debug_check_mem_with

	Assert that a memory block consists of len octets filled with c.
*/
#ifdef DEBUG
	void ubf_debug_check_mem_with (char *mem, char c, size_t len);
#else
	#define ubf_debug_check_mem_with(m, c, l)
#endif

/*
	ubf_debug_hex_dump
	
	Calls ubf_data_dump_puts () in ubfdump.c if UBF_DEBUG_HEX_DUMP is defined.
	If UBF_DEBUG_HEX_DUMP is not defined, the function is expanded to a no-operation.
*/
#ifdef UBF_DEBUG_HEX_DUMP
	void ubf_debug_hex_dump (const char *chOutput, size_t stOutput);
#else
	#define ubf_debug_hex_dump(ch,st)
#endif

/*
	ubf_debug_printf
	ubf_debug_puts
	
	Debug versions of printf () and puts (). To make these calls no-operations (empty)
	macros, undefine UBF_DEBUG_USE_PRINTF. In release versions they are empty definitions.
*/
#ifdef UBF_DEVICE_GUI
	#ifdef DEBUG
		void ubf_debug_printf (const char *format, ...);
		void ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
	#ifdef UBF_DEBUG_USE_PRINTF
		#undef UBF_DEBUG_USE_PRINTF
	#endif
#else
	#ifdef UBF_DEBUG_USE_PRINTF
		int ubf_debug_printf (const char *format, ...);
		int ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
#endif

// Debug sleep. Sleeps in debug versions (milliseconds) but not in release builds.
#ifdef DEBUG
	#define ubf_debug_sleep_ms(s)			ubf_sleep_ms (s)
#else
	#define ubf_debug_sleep_ms(s)
#endif

// Macros to abort in debug versions.
#ifdef DEBUG
	#define DEBUGABORT()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORTDEBUG()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORT()			ASSERT (false)
#else
	#define DEBUGABORT()
	#define DBGABORT()
	#define ABORTDEBUG()
	#define DBGABORT()
	#define ABORT()
#endif

/*
	ubf_expect_bool_AND

	Macro to binary AND an expectation. Useful in test functons.

	bool	bOk		= TRUE;
	int		a		= 0;
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 3 == a);
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 6 == a);
	ubf_assert_true (bOk);
*/
#define ubf_expect_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))

/*
	ubf_assert_TRUE
	ubf_assert_FALSE
	ubf_expect_TRUE
	ubf_expect_FALSE
	ubf_assert_true
	ubf_expect_true
	ubf_assert_false
	ubf_expect_false

	Macros that assert that the provided boolean is either TRUE or FALSE.
*/
#define ubf_assert_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_expect_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_assert_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_expect_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_assert_true(b)								\
			ubf_assert (true == (b))
#define ubf_expect_true(b)								\
			ubf_assert (true == (b))
#define ubf_assert_false(b)								\
			ubf_assert (false == (b))
#define ubf_expect_false(b)								\
			ubf_assert (false == (b))


/*
	ubf_assert_NULL
	ubf_expect_NULL
	ubf_assert_not_NULL
	ubf_expect_not_NULL
	ubf_assert_non_NULL
	ubf_expect_non_NULL

	Macros that assert that the provided pointer is either NULL or non-NULL.
*/
#define ubf_assert_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_expect_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_assert_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_assert_non_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_non_NULL(p)							\
			ubf_assert (NULL != (p))

/*
	ubf_assert_0
	ubf_expect_0
	ubf_assert_non_0
	ubf_expect_non_0
	ubf_assert_zero
	ubf_expect_zero
	ubf_assert_non_zero
	ubf_expect_non_zero

	Macros that assert that the parameter expression evaluates to zero or
	non-zero.
*/
#define ubf_assert_0(v)									\
			ubf_assert (0 == (v))
#define ubf_expect_0(v)									\
			ubf_assert (0 == (v))
#define ubf_assert_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_expect_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_assert_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_expect_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_assert_non_zero(v)							\
			ubf_assert (0 != (v))
#define ubf_expect_non_zero(v)							\
			ubf_assert (0 != (v))


EXTERN_C_END

#endif															// Of U_UBF_DEBUG_DEB_H_INCLUDED.
/****************************************************************************************

	File:		ubfmem.h
	Why:		Functions for memory handling.
	OS:			C99
	Author:		Thomas
	Created:	2016-10-31
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2016-10-31	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_UBFMEM_H_INCLUDED
#define U_UBFMEM_H_INCLUDED

// The Windows _ASSERT() macro.
//	Check out https://msdn.microsoft.com/en-us/library/ezb1wyez.aspx on how to use these macros.
//	The Wikipedia article https://en.wikipedia.org/wiki/Assert.h explains the Unix/Linux version.
#ifndef _ASSERT
	#ifdef DEBUG
		#define _ASSERT assert
	#else
		#define _ASSERT(ignore) ((void)0)
	#endif
#endif
#ifndef ASSERT
	#ifdef DEBUG
		#define ASSERT(x) _ASSERT(x)
	#else
		#define ASSERT(ignore) ((void)0)
	#endif
#endif

#include <malloc.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

// On Windows we could use the native functions.
#ifdef _WIN32
	#ifndef OS_IS_WINDOWS
	#define OS_IS_WINDOWS
	#endif
	#ifdef USE_WINDOWS_NATIVE_HEAP_FUNCTIONS
		#include <windows.h>
		#define malloc(size)			HeapAlloc (GetProcessHeap (), 0, size)
		#define calloc(n, s)			HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY, n * s)
		#define realloc(p, s)			HeapReAlloc (GetProcessHeap (), 0, p, s)
		//#define strdup(s)
		#define free(ptr)				HeapFree (GetProcessHeap (), 0, ptr)
		#define free(ptr)				HeapFree (GetProcessHeap (), 0, ptr)
		#define memcpy(d, s, l)			CopyMemory (d, s, l)
		#define memmovy(d, s, l)		MoveMemory (d, s, l)
		#define memset(p, v, s)			FillMemory (p, s, v)
		int memcmp (const void *str1, const void *str2, size_t count);
		#define DONT_USE_UBF_TYPE_DEFINITIONS
	#else
		#include <string.h>
	#endif
#endif

// https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif

/*
#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#define DONT_USE_UBF_TYPE_DEFINITIONS
#endif
#ifdef DONT_USE_UBF_TYPE_DEFINITIONS
	#include "./externC.h"
#else
	#ifdef UBF_TYPE_DEFINITIONS_USE_CURR_DIR
		#include "./ubf_type_definitions.h"
	#else
		#include "./../OS/ubf_type_definitions.h"
	#endif
#endif
*/

#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	#ifdef DEBUG
	#else
		// Not for release versions.
		#undef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	#endif
#endif

EXTERN_C_BEGIN

/*
	ubf_malloc
	ubf_calloc
	ubf_realloc
	ubf_strdup
	ubf_free
	ubf_free_accept_NULL
	ubf_memcpy
	ubf_memmove
	ubf_memset
	ubf_memcmp
	
	Debugging replacement for malloc (), calloc (), free (), etc. See
	https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm ,
	https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm ,
	and
	https://www.tutorialspoint.com/c_standard_library/c_function_free.htm .
	
	The function ubf_free () does not accept a NULL pointer in debug versions.
	Use ubf_free_accept_NULL () if the parameter can be NULL.

	Note that the functions ubf_memcpy (), ubf_memmove (), ubf_memset (),
	and ubf_memcmp () expect the base pointer (the one returned by ubf_malloc)
	as the first parameter, which is ignored when the debug versions are not used.
	For ubf_memcmp () the bse parameter is the base pointer of ptr1.
	
	
	ubf_mem_init_ptr
	
	Initialises the memory block of the bottom pointer btm with a usable size
	of usize.
	
	ubf_mem_usr_ptr
	
	Returns the start of the usable portion of the memory block with the bottom
	btm points to.
	
	ubf_mem_chk_ptr
	
	Checks the bottom pointer's memory debug guards. Note that ptr is a bottom
	pointer, not a base pointer.
	
	ubf_mem_chk_bse
	
	Checks the base pointer's memory debug guards. Note that bse is a base
	pointer, not a bottom pointer.
	
	ubf_mem_test_memdbg
	
	This function tests the memory debug functions.
	
	ubf_mem_done
	
	Performs cleanup work; should be called just before the application exists.
*/
#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	void *ubf_malloc			(size_t size);
	void *ubf_calloc			(size_t nitems, size_t size);
	void *ubf_realloc			(void *ptr, size_t new_size);
	char *ubf_strdup			(const char *cc);
	void ubf_free				(void *ptr);
	void ubf_free_accept_NULL	(void *ptr);
	void *ubf_memcpy			(void *bse, void *dst, const void *src, size_t len);
	void *ubf_memmove			(void *bse, void *dst, const void *src, size_t len);
	void *ubf_memset			(void *bse, void *ptr, int value, size_t num);
	int ubf_memcmp				(const void *bse, const void *ptr1, const void *ptr2, size_t num);
	void ubf_mem_init_ptr		(void *btm, size_t usize);
	void *ubf_mem_usr_ptr		(void *btm);
	void ubf_mem_chk_ptr		(void *btm);
	void ubf_mem_chk_bse		(void *bse);
	void ubf_mem_test_memdbg	(void);
	void ubf_mem_done			(void);
#else
	#define ubf_malloc(size)			malloc (size)
	#define ubf_calloc(n,s)				calloc (n, s)
	#define ubf_realloc(p,s)			realloc (p, s)
	#define ubf_strdup(s)				strdup (s)
	#define ubf_free(ptr)				free (ptr)
	#define ubf_free_accept_NULL(ptr)	free (ptr)
	#define ubf_memcpy(b,d,s,l)			memcpy (d, s, l)
	#define ubf_memmove(b,d,s,l)		memmove (d, s, l)
	#define ubf_memset(b,d,v,l)			memset (d, v, l)
	#define ubf_memcmp(b,p1,p2,l)		memcmp (p1, p2, l)
	#define ubf_mem_init_ptr(b,s)
	#define ubf_mem_usr_ptr(b)			(b)
	#define ubf_mem_chk_ptr(b)
	#define ubf_mem_chk_bse(b)
	#define ubf_mem_test_memdbg()
	#define ubf_mem_done()
#endif

/*
	ubf_aligned_malloc_intern

	Wrapper function or macro for aligned_alloc () or similar, depending on the target
	platform and compiler. See https://en.cppreference.com/w/c/memory/aligned_alloc .
	Note that the first argument is the size of the alignment, and the second parameter
	specifies the size of the memory block to allocate. The debug version of the function
	checks for size >= alignment and asserts that this condition is met. The idea behind
	this is that an aligned memory block is only required if the data requires alignment,
	which can only be the case when the data block has at least the size of the
	alignment. On Android, this function calls posix_memalign (), which is only available
	since API level 16. It is always a function on Android, never a macro. See
	http://pubs.opengroup.org/onlinepubs/9699919799/functions/posix_memalign.html for the
	documentation of posix_memalign (). It should also be noted that the system function
	is called _aligned_malloc () on Windows while it is called aligned_alloc () on other
	Linux type platforms. Pay attention to "...malloc" and "...alloc" in these function
	names, not just the underscore ("_") character.
*/
#ifdef OS_IS_WINDOWS
	#ifdef DEBUG
		// The debug version has a function definition.
		void *ubf_aligned_malloc_intern (size_t alignment, size_t size);
	#else
		#define ubf_aligned_malloc_intern(alignment,size) _aligned_malloc (alignment, size)
	#endif
#else
	void *ubf_aligned_malloc_intern (size_t alignment, size_t size);
#endif

// Memory allocation. See https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
//	and https://linux.die.net/man/3/aligned_alloc . We can use ubf_aligned_malloc ()
//	to be compatible with both worlds. The functions and macros are defined in
//	ubfmem.h/c.
#ifdef OS_IS_ANDROID
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_IOS
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_LINUX
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_OSX
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_UNIX
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_WINDOWS
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					_aligned_free (p)
#endif

/*
	ubf_alloca

	This is a wrapper for the various alloca () functions, inline functions, and macros.
*/
/*
#ifdef DEBUG
	void *ubf_alloca (size_t size);
#else
	#define ubf_alloca(s)	alloca (s)
#endif
*/

/*
	ubf_memdup
	
	Like strdup () but with a length.
*/
void *ubf_memdup (const void *mem, size_t len);

/*
	ubf_memdup_siz
	
	Like strdup () but with length to copy and size to allocate.
	In other words, a copy of mem with a size of siz is created and the first len octets
	copied from mem to the new buffer.
	
	Debug versions abort if siz <= len.
*/
void *ubf_memdup_siz (const void *mem, size_t len, size_t siz);

/*
	ZeroMemory
	
	See
	https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366920(v%3Dvs.85) .
	
	This is to provide the Windows function for non-Windows platforms.
*/
#ifndef OS_IS_WINDOWS
	#ifndef _WIN32
		#define ZeroMemory(Destination,Length)				\
					memset((Destination),0,(Length))
	#endif
#endif

EXTERN_C_END

#endif															// Of U_UBFMEM_H_INCLUDED.
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

	Copyright (c) 2024 Thomas

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
/****************************************************************************************

	File:		memstrstr.h
	Created:	?

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2014-03-10	Thomas			This history added.
2019-10-13	Thomas			Include files moved to the header.

	The original version of this function has been taken from
	http://www.koders.com/c/fid2330745E0E8C0A0F5E2CF94799642712318471D0.aspx?s=getopt#L459
	which needed fixing first. The page has disappeared in the meantime (2018). The
	Wayback Machine also holds no copy of it.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef MEMSTRSTR_H
#define MEMSTRSTR_H

// Make sure that rand_s() is available on Windows systems with MSVC 2005
//	or higher.
#if defined(_MSC_VER) && _MSC_VER>=1400
	#ifndef _CRT_RAND_S
		#define _CRT_RAND_S
	#endif
#endif
// Actually, we're not building with outdated compilers anymore.
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif
#include <stdio.h>
#ifdef _MSC_VER
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
	memstrstr

	The function returns a pointer to the first occurrence of s2 in s1.
	If s2 cannot be found in s1 the return value is NULL. If size2 is
	0 the function returns s1.

	The function memstrstr is basically a replacement for strstr
	(http://www.cppreference.com/stdstring/strstr.html) but does not require
	NULL terminated strings. It can handle any buffer which can contain any
	byte sequence including NULL characters.

	The original version of this function has been taken from
	http://www.koders.com/c/fid2330745E0E8C0A0F5E2CF94799642712318471D0.aspx?s=getopt#L459
	which needed fixing first. The page has disappeared in the meantime (2018). The
	Wayback Machine also holds no copy of it.
*/
char *memstrstr (const char *s1, size_t size1, const char *s2, size_t size2)
;

/*
	memstrstrn

	Like memstrstr but only returns the nth occurrance of s2 in s1 if
	s2 has been found amount times in s1. Returns NULL if s1 does not
	contain s2 amount times.

	Example:
	s1: "This is a test for memstrstrn."
	s2: "e"
	amount: 2 (second occurrance of s2 in s1)
	memstrstrn (s1, strlen (s1), s2, strlen (s2), 2);
	Returns "emstrstrn."
*/
char *memstrstrn (char *s1, size_t size1, char *s2, size_t size2, size_t amount)
;

/*
	memchrreplace

	Replaces all occurrences of s1 in s with s2.
*/
size_t memchrreplace (char *s, size_t size, char s1, char s2)
;

/*
	memstrchr
	
	Like strchr but honours the length of str by returning NULL if character is not
	within the memory block up to str + len. See
	https://cplusplus.com/reference/cstring/strchr/ for more information.
*/
char *memstrchr (const char *str, size_t len, char character);

/*
	memstrrchr
	
	Like strrchr but with a length parameter instead of a NUL-terminated string.
	See https://cplusplus.com/reference/cstring/strrchr/ for more information.
*/
char *memstrrchr (const char *str, size_t len, char character);

#ifdef __cplusplus
}																// Closing bracket for extern "C".
#endif

#endif															// Of #ifndef MEMSTRSTR_H .
/****************************************************************************************

	File:		VectorC.h
	Why:		Implements vector types in C.
	OS:			-
	Author:		Thomas
	Created:	2019-12-09
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-12-09	Thomas			Created.
2020-01-17	Thomas			Documentation from https://github.com/rxi/vec partly
							 added here for convenience.
							 
****************************************************************************************/

/*
	Implements vectors (variable arrays) in C. If you change this text please copy
	and paste it in the code or header file too.

	The code has been inspired by several different sources and changed/extended.

	Sources:
	https://github.com/rxi/vec
	https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
	https://stackoverflow.com/questions/4694401/how-to-replicate-vector-in-c
	https://github.com/Mashpoe/c-vector

	Most of the code comes from https://github.com/rxi/vec .
	A good introduction can be found at https://jameshfisher.com/2017/04/06/rxi-vec/ .
	The project itself at https://github.com/rxi/vec contains the basics.

	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Since most of the code is from the rxi implementation: Copyright (c) 2014 rxi

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

#ifndef VECTORC_H
#define VECTORC_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../pre/externC.h"
	#endif

#endif

BEGIN_C_DECLS

/** 
 * Copyright (c) 2014 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */
 
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <stdlib.h>
#include <string.h>

#define VEC_VERSION "0.2.1"

/*
	vec
	
	A type-safe dynamic array implementation for C.
	Installation
	
	The vec.c and vec.h files can be dropped into an existing C project and compiled along with it.
	Usage
	
	Before using a vector it should first be initialised using the vec_init() function.
	
	vec_int_t v;
	vec_init(&v);
	vec_push(&v, 123);
	vec_push(&v, 456);
	
	To access the elements of the vector directly the vector's data field can be used.
	
	printf("%d\n", v.data[1]); // Prints the value at index 1
	
	The current length of the vector is stored in the length field of the vector
	
	printf("%d\n", v.length); // Prints the length of the vector
	
	When you are done with the vector the vec_deinit() function should be called on it.
	This will free any memory the vector allocated during use.
	
	vec_deinit(&v);
	
	Types
	
	vec.h provides the following predefined vector types:
	Contained Type 	Type name
	void* 	vec_void_t
	char* 	vec_str_t
	int 	vec_int_t
	char 	vec_char_t
	float 	vec_float_t
	double 	vec_double_t
	
	To define a new vector type the vec_t() macro should be used:
	
	/// Creates the type uint_vec_t for storing unsigned ints
	typedef vec_t(unsigned int) uint_vec_t;
	
	Functions
	
	All vector functions are macro functions. The parameter v in each function should be
	a pointer to the vec struct which the operation is to be performed on.
	vec_t(T)
	
	Creates a vec struct for containing values of type T.
	
	// Typedefs the struct `fp_vec_t` as a container for type FILE*
	typedef vec_t(FILE*) fp_vec_t;
	
*/

#define vec_unpack_(v)\
  (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)


#define vec_t(T)\
  struct { T *data; size_t length, capacity; }

/*
	vec_init(v)
	
	Initialises the vector, this must be called before the vector can be used.
*/
#define vec_init(v)\
  memset((v), 0, sizeof(*(v)))

/*
	vec_deinit(v)
	
	Deinitialises the vector, freeing the memory the vector allocated during use;
	this should be called when we're finished with a vector.
*/
#define vec_deinit(v)\
  ( free((v)->data),\
    vec_init(v) ) 

/*
	vec_push(v, val)
	
	Pushes a value to the end of the vector. Returns 0 if the operation was successful,
	otherwise -1 is returned and the vector remains unchanged.
*/
#define vec_push(v, val)\
  ( vec_expand_(vec_unpack_(v)) ? -1 :\
    ((v)->data[(v)->length++] = (val), 0), 0 )

/*
	vec_pop(v)
	
	Removes and returns the value at the end of the vector.
*/
#define vec_pop(v)\
  (v)->data[--(v)->length]

/*
	vec_splice(v, start, count)
	
	Removes the number of values specified by count, starting at the index start.
	
	vec_splice(&v, 2, 4); // Removes the values at indices 2, 3, 4 and 5
*/
#define vec_splice(v, start, count)\
  ( vec_splice_(vec_unpack_(v), start, count),\
    (v)->length -= (count) )

/*
	vec_swapsplice(v, start, count)
	
	Removes the number of values specified by count, starting at the index start;
	the removed values are replaced with the last count values of the vector. This
	does not preserve ordering but is O(1).
*/
#define vec_swapsplice(v, start, count)\
  ( vec_swapsplice_(vec_unpack_(v), start, count),\
    (v)->length -= (count) )

/*
	vec_insert(v, idx, val)
	
	Inserts the value val at index idx shifting the elements after the index to make
	room for the new value.
	
	// Inserts the value 123 at the beginning of the vec
	vec_insert(&v, 0, 123);
	
	Returns 0 if the operation was successful, otherwise -1 is returned and the
	vector remains unchanged.
*/
#define vec_insert(v, idx, val)\
  ( vec_insert_(vec_unpack_(v), idx) ? -1 :\
    ((v)->data[idx] = (val), 0), (v)->length++, 0 )
    
/*
	vec_sort(v, fn)
	
	Sorts the values of the vector; fn should be a qsort-compatible compare function.
*/
#define vec_sort(v, fn)\
  qsort((v)->data, (size_t) (v)->length, sizeof(*(v)->data), fn)

/*
	vec_swap(v, idx1, idx2)
	
	Swaps the values at the indices idx1 and idx2 with one another.
*/
#define vec_swap(v, idx1, idx2)\
  vec_swap_(vec_unpack_(v), idx1, idx2)

/*
	vec_truncate(v, len)
	
	Truncates the vector's length to len. If len is greater than the vector's current
	length then no change is made.
*/
#define vec_truncate(v, len)\
  ((v)->length = (len) < (v)->length ? (len) : (v)->length)

/*
	vec_clear(v)
	
	Clears all values from the vector reducing the vector's length to 0.
*/
#define vec_clear(v)\
  ((v)->length = 0)

/*
	vec_first(v)
	
	Returns the first value in the vector. This should not be used on an empty vector.
*/
#define vec_first(v)\
  (v)->data[0]

/*
	vec_last(v)
	
	Returns the last value in the vector. This should not be used on an empty vector.
*/
#define vec_last(v)\
  (v)->data[(v)->length - 1]

/*
	vec_reserve(v, n)
	
	Reserves capacity for at least n elements in the given vector; if n is less than
	the current capacity then vec_reserve() does nothing. Returns 0 if the operation
	was successful, otherwise -1 is returned and the vector remains unchanged.
*/
#define vec_reserve(v, n)\
  vec_reserve_(vec_unpack_(v), n)

/*
	vec_compact(v)
	
	Reduces the vector's capacity to the smallest size required to store its current
	number of values. Returns 0 if the operation is successful, otherwise -1 is
	returned and the vector remains unchanged.
*/
#define vec_compact(v)\
  vec_compact_(vec_unpack_(v))

/*
	vec_pusharr(v, arr, count)
	
	Pushes the contents of the array arr to the end of the vector. count should be the
	number of elements in the array.
*/
#define vec_pusharr(v, arr, count)\
  do {\
    int i__, n__ = (count);\
    if (vec_reserve_po2_(vec_unpack_(v), (v)->length + n__) != 0) break;\
    for (i__ = 0; i__ < n__; i__++) {\
      (v)->data[(v)->length++] = (arr)[i__];\
    }\
  } while (0)

/*
	vec_extend(v, v2)
	
	Appends the contents of the v2 vector to the v vector.
*/
#define vec_extend(v, v2)\
  vec_pusharr((v), (v2)->data, (v2)->length)

/*
	vec_find(v, val, idx)
	
	Finds the first occurrence of the value val in the vector. idx should be an int
	where the value's index will be written; idx is set to -1 if val could not be
	found in the vector.
*/
#define vec_find(v, val, idx)\
  do {\
    for ((idx) = 0; (idx) < (v)->length; (idx)++) {\
      if ((v)->data[(idx)] == (val)) break;\
    }\
    if ((idx) == (v)->length) (idx) = -1;\
  } while (0)

/*
	vec_remove(v, val)
	
	Removes the first occurrence of the value val from the vector. If the val is not
	contained in the vector then vec_remove() does nothing.
*/
#define vec_remove(v, val)\
  do {\
    int idx__;\
    vec_find(v, val, idx__);\
    if (idx__ != -1) vec_splice(v, idx__, 1);\
  } while (0)

/*
	vec_reverse(v)
	
	Reverses the order of the vector's values in place. For example, a vector
	containing 4, 5, 6 would contain 6, 5, 4 after reversing.
*/
#define vec_reverse(v)\
  do {\
    int i__ = (v)->length / 2;\
    while (i__--) {\
      vec_swap((v), i__, (v)->length - (i__ + 1));\
    }\
  } while (0)

/*
	vec_foreach(v, var, iter)
	
	Iterates the values of the vector from the first to the last. var should be a
	variable of the vector's contained type where the value will be stored with each
	iteration. iter should be an int used to store the index during iteration.
	
	// Iterates and prints the value and index of each value in the float vec
	int i; float val;
	vec_foreach(&v, val, i) {
	  printf("%d : %f\n", i, val);
	}
*/
#define vec_foreach(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = 0;\
        (iter) < (v)->length && (((var) = (v)->data[(iter)]), 1);\
        ++(iter))

/*
	vec_foreach_rev(v, var, iter)
	
	Iterates the values of the vector from the last to the first. See vec_foreach()
*/
#define vec_foreach_rev(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = (v)->length - 1;\
        (iter) >= 0 && (((var) = (v)->data[(iter)]), 1);\
        --(iter))

/*
	vec_foreach_ptr(v, var, iter)
	
	Iterates the value pointers of the vector from first to last. var should be a
	variable of the vector's contained type's pointer. See vec_foreach().
	
	// Iterates and prints the value and index of each value in the float vector
	int i; float *val;
	vec_foreach_ptr(&v, val, i) {
	  printf("%d : %f\n", i, *val);
}
*/
#define vec_foreach_ptr(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = 0;\
        (iter) < (v)->length && (((var) = &(v)->data[(iter)]), 1);\
        ++(iter))

/*
	vec_foreach_ptr_rev(v, var, iter)
	
	Iterates the value pointers of the vector from last to first. See vec_foreach_ptr()
*/
#define vec_foreach_ptr_rev(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = (v)->length - 1;\
        (iter) >= 0 && (((var) = &(v)->data[(iter)]), 1);\
        --(iter))

/*
	License
	
	This library is free software; you can redistribute it and/or modify it under the
	terms of the MIT license. See LICENSE for details.
*/

int vec_expand_(char **data, size_t *length, size_t *capacity, size_t memsz);
int vec_reserve_(char **data, size_t *length, size_t *capacity, size_t memsz, size_t n);
int vec_reserve_po2_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t n);
int vec_compact_(char **data, size_t *length, size_t *capacity, size_t memsz);
int vec_insert_(char **data, size_t *length, size_t *capacity, size_t memsz,
                size_t idx);
void vec_splice_(char **data, size_t *length, size_t *capacity, size_t memsz,
	size_t start, size_t count);
void vec_swapsplice_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t start, size_t count);
void vec_swap_(char **data, size_t *length, size_t *capacity, size_t memsz,
               size_t idx1, size_t idx2);

typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(float) vec_float_t;
typedef vec_t(double) vec_double_t;
// More type definitions can be found in VectorCtypes.h.

END_C_DECLS

#endif															// End of VECTORC_H.
/****************************************************************************************

	File:		ubf_time.h
	Why:		Contains structures and functions to work with UBF_TIMESTAMP
				and SUBF_TIMESTRUCT structures.
	OS:			C99.
	Author:		Thomas
	Created:	2018-03-29
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2018-03-29	Thomas			Created.
2020-09-23	Thomas			Extended.
2021-01-01	Thomas			Format of UBF_TIMESTAMP changed. The old one had a few
							 issues.
							 
****************************************************************************************/

/*
	This module deals with our own timestamp formats. UBF_TIMESTAMP is a
	64 bit unsigned type and can and should be used whenever a timestamp is
	required. A UBF_TIMESTAMP can be extracted to a SUBF_TIMESTRUCT for
	accessing its members.
	
	This module is included by ubf_data_and_time.h. So, if you include that
	file you don't need to include this one separately.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_UBF_TIME_H_INCLUDED
#define U_UBF_TIME_H_INCLUDED

/*
#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#include "./ubf_type_definitions.h"
#else
	#include "./../OS/ubf_type_definitions.h"
#endif
*/

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _WIN32
	#ifndef OS_IS_WINDOWS
	#define OS_IS_WINDOWS
	#endif
	#include <Windows.h>
#else
	#include <time.h>
	#include <sys/timeb.h>
#endif

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)	(P) = (P);
#endif
#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER(x) (void)(x)
#endif

/*
	Time intervals valid for values in FILETIME structures.
*/
#ifndef FT_D_NANOSECOND
#define FT_D_NANOSECOND ((ULONGLONG) 100)						/* This is 1/100! */
#endif
#ifndef FT_MICROSECOND
#define FT_MICROSECOND ((ULONGLONG) 10)
#endif
#ifndef FT_MILLISECOND
#define FT_MILLISECOND ((ULONGLONG) 10000)
#endif
#ifndef FT_SECOND
#define FT_SECOND ((ULONGLONG) 10000000)
#endif
#ifndef FT_MINUTE
#define FT_MINUTE (60 * FT_SECOND)
#endif
#ifndef FT_HOUR
#define FT_HOUR   (60 * FT_MINUTE)
#endif
#ifndef FT_DAY
#define FT_DAY    (24 * FT_HOUR)
#endif

// Lengths and sizes. Lengths exclude and sizes include a terminating NUL
//	character.
#ifndef LEN_ISO8601WEEK
#define LEN_ISO8601WEEK						(3)					// "Wnn"
#endif
#ifndef SIZ_ISO8601WEEK
#define SIZ_ISO8601WEEK						(LEN_ISO8601WEEK + 1)
#endif
#ifndef LEN_ISO8601YEAR
#define LEN_ISO8601YEAR						(4)					// "YYYY"
#endif
#ifndef SIZ_ISO8601YEAR
#define SIZ_ISO8601YEAR						(LEN_ISO8601YEAR + 1)
#endif
#ifndef LEN_ISO8601YEARANDMONTH
#define LEN_ISO8601YEARANDMONTH				(7)					// "YYYY-MM"
#endif
#ifndef SIZ_ISO8601YEARANDMONTH
#define SIZ_ISO8601YEARANDMONTH				(LEN_ISO8601YEARANDMONTH + 1)
#endif
#ifndef LEN_ISO8601YEARANDWEEK
#define LEN_ISO8601YEARANDWEEK				(8)					// "YYYY-Wnn"
#endif
#ifndef SIZ_ISO8601YEARANDWEEK
#define SIZ_ISO8601YEARANDWEEK				(LEN_ISO8601YEARANDWEEK + 1)
#endif
#ifndef LEN_ISO8601SHORTDATE
#define LEN_ISO8601SHORTDATE				(8)					// "YYYYMMDD"
#endif
#ifndef SIZ_ISO8601SHORTDATE
#define SIZ_ISO8601SHORTDATE				(LEN_ISO8601SHORTDATE + 1)
#endif
#ifndef LEN_ISO8601DATE
#define LEN_ISO8601DATE						(10)				// "YYYY-MM-DD"
#endif
#ifndef SIZ_ISO8601DATE
#define SIZ_ISO8601DATE						(LEN_ISO8601DATE + 1)
#endif
#ifndef LEN_ISO8601DATEANDHOUR
#define LEN_ISO8601DATEANDHOUR				(13)				// "YYYY-MM-DD HH"
#endif
#ifndef SIZ_ISO8601DATEANDHOUR
#define SIZ_ISO8601DATEANDHOUR				(LEN_ISO8601DATEANDOUR + 1)
#endif
#ifndef LEN_ISO8601DATEHOURANDMINUTE
#define LEN_ISO8601DATEHOURANDMINUTE		(16)				// "YYYY-MM-DD HH:MI"
#endif
#ifndef SIZ_ISO8601DATEHOURANDMINUTE
#define SIZ_ISO8601DATEHOURANDMINUTE		(LEN_ISO8601DATEHOURANDMINUTE + 1)
#endif
#ifndef LEN_ISO8601SHORTDATEHOURSONLY
#define LEN_ISO8601SHORTDATEHOURSONLY		(11)				// "YYYYMMDDTHH"
#endif
#ifndef SIZ_ISO8601SHORTDATEHOURSONLY
#define SIZ_ISO8601SHORTDATEHOURSONLY		(LEN_ISO8601SHORTDATEHOURSONLY + 1)
#endif
#ifndef LEN_ISO8601SHORTDATEHOURSMINS
#define LEN_ISO8601SHORTDATEHOURSMINS		(13)				// "YYYYMMDDTHHMI"
#endif
#ifndef SIZ_ISO8601SHORTDATEHOURSMINS
#define SIZ_ISO8601SHORTDATEHOURSMINS		(LEN_ISO8601SHORTDATEHOURSMINS + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMELOCAL
#define	LEN_ISO8601SHORTDATETIMELOCAL		(15)				// "YYYYMMDDTHHMISS"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMELOCAL
#define	SIZ_ISO8601SHORTDATETIMELOCAL		(LEN_ISO8601SHORTDATETIMELOCAL + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIME
#define	LEN_ISO8601SHORTDATETIME			(16)				// "YYYYMMDDTHHMISSZ"
#endif
#ifndef SIZ_ISO8601SHORTDATETIME
#define	SIZ_ISO8601SHORTDATETIME			(LEN_ISO8601SHORTDATETIME + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMP_NO_OFFS
#define LEN_ISO8601DATETIMESTAMP_NO_OFFS	(19)				// "YYYY-MM-DD hh:mm:ss"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMP_NO_OFFS	(LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMS								// "YYYYMMDDTHHMISS.misZ"
#define	LEN_ISO8601SHORTDATETIMEMS			(20)
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMS								// "YYYYMMDDTHHMISS.misZ"
#define	SIZ_ISO8601SHORTDATETIMEMS			(LEN_ISO8601SHORTDATETIMEMS)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMSOFFSH
#define	LEN_ISO8601SHORTDATETIMEMSOFFSH		(22)				// "YYYYMMDDTHHMISS.mis+HH"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMSOFFSH
#define	SIZ_ISO8601SHORTDATETIMEMSOFFSH		(LEN_ISO8601SHORTDATETIMEMSOFFSH + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMSUS
#define	LEN_ISO8601SHORTDATETIMEMSUS		(23)				// "YYYYMMDDTHHMISS.mis000Z"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMSUS
#define	SIZ_ISO8601SHORTDATETIMEMSUS		(LEN_ISO8601SHORTDATETIMEMSUS + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS_NO_OFFS
#define LEN_ISO8601DATETIMESTAMPMS_NO_OFFS	(23)				// "YYYY-MM-DD hh:mm:ss.xxx"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPMS_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMPMS_NO_OFFS	(LEN_ISO8601DATETIMESTAMPMS_NO_OFFS + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMSUSOFFSH
#define	LEN_ISO8601SHORTDATETIMEMSUSOFFSH	(25)				// "YYYYMMDDTHHMISS.mis000+HH"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMSUSOFFSH
#define	SIZ_ISO8601SHORTDATETIMEMSUSOFFSH	(LEN_ISO8601SHORTDATETIMEMSUSOFFSH + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMP								// "YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMP			(25)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP								// "YYYY-MM-DD HH:MI:SS+01:00"
#define SIZ_ISO8601DATETIMESTAMP			(LEN_ISO8601DATETIMESTAMP + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMP_HOL							// "1YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMP_HOL		(26)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_HOL							// "1YYYY-MM-DD HH:MI:SS+01:00"
#define SIZ_ISO8601DATETIMESTAMP_HOL		(LEN_ISO8601DATETIMESTAMP_HOL + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS								// "YYYY-MM-DD HH:MI:SS.000+01:00"
#define LEN_ISO8601DATETIMESTAMPMS			(29)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPMS								// "YYYY-MM-DD HH:MI:SS.000+01:00"
#define SIZ_ISO8601DATETIMESTAMPMS			(LEN_ISO8601DATETIMESTAMPMS + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPUS								// "YYYY-MM-DD HH:MI:SS.000000+01:00"
#define LEN_ISO8601DATETIMESTAMPUS			(32)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPUS								// "YYYY-MM-DD HH:MI:SS.000000+01:00"
#define SIZ_ISO8601DATETIMESTAMPUS			(LEN_ISO8601DATETIMESTAMPUS + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS_HOL							// "1YYYY-MM-DD HH:MI:SS.000+01:00"
#define LEN_ISO8601DATETIMESTAMPMS_HOL		(30)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPMS_HOL							// "1YYYY-MM-DD HH:MI:SS.000+01:00"
#define SIZ_ISO8601DATETIMESTAMPMS_HOL		(LEN_ISO8601DATETIMESTAMPMS_HOL + 1)
#endif

#ifndef NUM_MS_IN_SECOND
#define NUM_MS_IN_SECOND					(1000)
#endif
#ifndef NUM_MS_IN_MINUTE
#define NUM_MS_IN_MINUTE					(60 * NUM_MS_IN_SECOND)
#endif
#ifndef NUM_MS_IN_HOUR
#define NUM_MS_IN_HOUR						(60 * NUM_MS_IN_MINUTE)
#endif
#ifndef NUM_MS_IN_DAY
#define NUM_MS_IN_DAY						(24 * NUM_MS_IN_HOUR)
#endif

// Android.
#ifdef OS_IS_ANDROID
	#include <sys/types.h>
	#include <sys/time.h>
    struct timeb
    {
        time_t         time;
        unsigned short millitm;
        short          timezone;
        short          dstflag;
    };
	//#include <sys/timeb.h>
	#include <time.h>
#endif

// IOS.
#ifdef OS_IS_IOS
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <time.h>
#endif

// Linux.
#ifdef OS_IS_LINUX
    #include <sys/types.h>
	#include <sys/timeb.h>
    #include <sys/time.h>
    #include <time.h>
#endif

// OSX.
#ifdef OS_IS_OSX
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <time.h>
#endif

// Unix.
#ifdef OS_IS_UNIX
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <time.h>
#endif

// Windows.
#ifdef OS_IS_WINDOWS
	#include <time.h>
	#include <sys/timeb.h>
	// Windows doesn't know gmtime_r () but it has gmtime_s () with swapped parameters.
	#define gmtime_r(a,b)		gmtime_s(b, a)
	#define localtime_r(a,b)	localtime_s(b, a)
	#define timeb				_timeb
	// Note that ftime () is actually deprecated on POSIX.
	#define ftime(t)			_ftime(t)
#endif

/*
	Android doesn't seem to support ftime (), at least not all versions.
*/
#ifdef OS_IS_ANDROID
	#ifndef HAVE_ANDROID_FTIME
		int ftime (struct timeb *tb);
		#define HAVE_ANDROID_FTIME
		#define BUILD_ANDROID_FTIME_HERE
	#endif
#endif

EXTERN_C_BEGIN

/*
	Our representation of a timestamp. Experimental.
	
	The timestamp is either the local time containing an offset to UTC
	or the time in UTC. When one of the offset bits is set (1) the time
	is assumed to be a local time containing an offset and converted
	to UTC whenever UTC is required.
	If no offset is given (bit 0...7 cleared) the time is assumed to 
	be in UTC and converted whenever the local time is required.
	
	The size of a UBF_TIMESTAMP is 64 bit (uint64_t). A value of 0
	is identical to no time. A value of (uint64_t) -1 denotes infinity.

	Unit	Values required	-> ~ 2^?		~  n bits
	-------------------------------------------------
	Year	2000..3023		-> ~ 1024		~ 10 bits
	Month	1..12			-> ~ 16			~  4 bits
	Day		1..31			-> ~ 32			~  5 bits
	Hour	0..23			-> ~ 32			~  5 bits
	Minute	0..59			-> ~ 64			~  6 bits
	Second	0..59			-> ~ 64			~  6 bits
	ms		0..999			-> ~ 1024		~ 10 bits
	us		0..999			-> ~ 1024		~ 10 bits
	ns		0..999			-> ~ 1024		~ 10 bits
	Offset	0..14			-> ~ 16			~  4 bits

	Bit reference starting from 2021-01-01:
	---------------------------------------
	
    6666555555555544444444443333333333222222222211111111110000000000
    3210987654321098765432109876543210987654321098765432109876543210
    I        ||     I               I               I           |  I
    I       I||     I       I       I       I       I       I   |  I
    7654321076543210765432107654321076543210765432107654321076543210
             ||	                        |         |         |   |  x	unused 
             ||                         |         9876543210|   |		us
             ||	                        9876543210..........|...|...	ms
             ||	                  543210....................|...|...	s
             ||	  	        543210..........................|...|...	min
             ||	  	   43210................................|...|...	h
             ||	  43210.....................................|...|...	day
             |3210..........................................|...|...	month
    9876543210..............................................|...|...	year
                                                            3210|||.	UTC offset in hours
                                                                0||.	1: UTC offset is negative
                                                                 ||.	0: UTC offset is positive 
                                                                 0|.	1: UTC offset + 30 minutes
                                                                  |.	0: UTC offset unchanged
                                                                  0.	1: UTC offset + 15 minutes
                                                                        0: UTC offset unchanged
    
	Microseconds (us) can have a value from 0 to 999. In binary, this is from
	0000000000 (  0 decimal) to 
	1111100111 (999 decimal).
	The same applies to milliseconds (ms).
	
	According to https://en.wikipedia.org/wiki/List_of_UTC_time_offsets, time offsets
	range from -12 (west) to 14 (east). Most timezones are at full hours but there are
	some exceptions. Our structure can add 30 and/or 15 minutes if required. This covers
	the 15, 30, and 45 minutes exceptions.
*/
#ifndef HAVE_UBF_TIMESTAMP
	typedef	uint64_t				UBF_TIMESTAMP;				// A timestamp in host byte order.
	typedef uint64_t				UBF_TIMESTAMPN;				// A timestamp in network order.
	#define is_infinity_UBF_TIMESTAMP(pt)				\
				((uint64_t) -1 == *(pt))
	#define IS_INFINITY_UBF_TIMESTAMP(t)				\
				((uint64_t) -1 == t))
	typedef struct subf_timestruct
	{
		unsigned int	uYear;									// Year: 0 == 2000, 1023 = 3023.
		unsigned int	uMonth;									// Month: 1..12.
		unsigned int	uDay;									// Day: 1..31.
		unsigned int	uHour;									// Hour: 0..24.
		unsigned int	uMinute;								// Minute: 0..59.
		unsigned int	uSecond;								// Second: 0..59.
		unsigned int	uMillisecond;							// Millisecond: 0..999.
		unsigned int	uMicrosecond;							// Microsecond: 0..999.
		unsigned int	uOffsetHours;							// The offset to UTC in hours.
		unsigned int	uOffsetMinutes;							// Additional minutes to UTC offset.
		bool			bOffsetNegative;						// UTC offset is negative.
	} SUBF_TIMESTRUCT;
	#define HAVE_UBF_TIMESTAMP
#endif

/*
	HasTimeOffset_UBF_TIMESTAMP
	HasNoTimeOffset_UBF_TIMESTAMP
	IsUTC_UBF_TIMESTAMP
	IsNotUTC_UBF_TIMESTAMP
	
	Macros to determine whether a UBF_TIMESTAMP is a UTC timestamp or a local time.
*/
#define HasTimeOffset_UBF_TIMESTAMP(ut)					\
	(ut & 0x7F)
#define HasNoTimeOffset_UBF_TIMESTAMP(ut)				\
	(0 == ut & 0x7F)
#define IsUTC_UBF_TIMESTAMP(ut)							\
	(0 == ut & 0x7F)
#define IsNotUTC_UBF_TIMESTAMP(ut)						\
	(ut & 0x7F)

/*
	IsUTC_SUBF_TIMESTRUCT
	IsNotUTC_SUBF_TIMESTRUCT
	
	Macros to determine whether a SUBF_TIMESTRUCT is in UTC or local time.
*/
#define IsUTC_SUBF_TIMESTRUCT(ts)						\
	((ts)->uOffsetHours || (ts)->uOffsetMinutes)
#define IsNotUTC_SUBF_TIMESTRUCT(ts)					\
	(!((ts)->uOffsetHours || (ts)->uOffsetMinutes))
	
/*
	UBF_TIMESTAMP_OFFSET_BITS

	Returns the bits that need to be set in a UBF_TIMESTAMP date/time stamp for the time
	offset in the SUBF_TIMESTRUCT structure ts points to.
*/
UBF_TIMESTAMP UBF_TIMESTAMP_OFFSET_BITS (SUBF_TIMESTRUCT *ts);

/*
	Macros to obtain the bits required to set in a UBF_TIMESTAMP date/time stamp for the
	different values from a SUBF_TIMESTRUCT structure.
*/
#define UBF_TIMESTAMP_MICROSECOND_BITS(ts)				\
	(((UBF_TIMESTAMP) (ts)->uMicrosecond) << 8)

#define UBF_TIMESTAMP_MILLISECOND_BITS(ts)				\
	(((UBF_TIMESTAMP) (ts)->uMillisecond) << 18)

#define UBF_TIMESTAMP_SECOND_BITS(ts)					\
	(((UBF_TIMESTAMP) (ts)->uSecond) << 28)

#define UBF_TIMESTAMP_MINUTE_BITS(ts)					\
	(((UBF_TIMESTAMP) (ts)->uMinute) << 34)

#define UBF_TIMESTAMP_HOUR_BITS(ts)						\
	(((UBF_TIMESTAMP) (ts)->uHour) << 40)

#define UBF_TIMESTAMP_DAY_BITS(ts)						\
	(((UBF_TIMESTAMP) (ts)->uDay) << 45)

#define UBF_TIMESTAMP_MONTH_BITS(ts)					\
	(((UBF_TIMESTAMP) (ts)->uMonth) << 50)

#define UBF_TIMESTAMP_YEAR_BITS(ts)						\
	((((UBF_TIMESTAMP) (ts)->uYear) - 2000) << 54)

/*
	SET_UBF_TIMESTAMP_OFFSET_BITS

	This macro clears the UBF_TIMESTAMP first. It must therefore be called before
	any of the other SET_UBF_TIMESTAMP_ macros below.

	UBF_TIMESTAMP		uts
	offset hours		oh
	offset minutes		om
	bool				bn		(offset negative yes/no)

		Specification from 2021-01-01:

		Bit 76543210
			3210|||.	UTC offset in hours
				0||.	1: UTC offset is negative
				 ||.	0: UTC offset is positive
				 0|.	1: UTC offset + 30 minutes
				  |.	0: UTC offset unchanged
				  0.	1: UTC offset + 15 minutes
						0: UTC offset unchanged
	
*/
#define SET_UBF_TIMESTAMP_OFFSET_BITS(uts, oh, om, bn)	\
	(uts) = oh;											\
	(uts) <<= 4;										\
	(uts) |= bn ? 0x08 : 0;								\
	switch (om)											\
	{													\
		case 0:											\
			break;										\
		case 15:										\
			(uts) |= 0x02;								\
			break;										\
		case 30:										\
			(uts) |= 0x04;								\
			break;										\
		case 45:										\
			(uts) |= 0x06;								\
			break;										\
		default:										\
			ubf_assert (false);							\
	}

/*
	Macros to set the bits required to for a UBF_TIMESTAMP date/time stamp for the
	different values.

	The macro SET_UBF_TIMESTAMP_OFFSET_BITS() above must be called first.
*/
#define SET_UBF_TIMESTAMP_MICROSECOND_BITS(us)			\
	((UBF_TIMESTAMP) (us) << 8)

#define SET_UBF_TIMESTAMP_MILLISECOND_BITS(ms)			\
	((UBF_TIMESTAMP) (ms) << 18)

#define SET_UBF_TIMESTAMP_SECOND_BITS(s)				\
	((UBF_TIMESTAMP) (s) << 28)

#define SET_UBF_TIMESTAMP_MINUTE_BITS(mi)				\
	((UBF_TIMESTAMP) (mi) << 34)

#define SET_UBF_TIMESTAMP_HOUR_BITS(h)					\
	((UBF_TIMESTAMP) (h) << 40)

#define SET_UBF_TIMESTAMP_DAY_BITS(d)					\
	((UBF_TIMESTAMP) (d) << 45)

#define SET_UBF_TIMESTAMP_MONTH_BITS(mo)				\
	((UBF_TIMESTAMP) (mo) << 50)

#define SET_UBF_TIMESTAMP_YEAR_BITS(y)					\
	(((UBF_TIMESTAMP) (y) - 2000) << 54)

/*
	Macros to extract the binary date in a UBF_TIMESTAMP.
*/
#define UBF_TIMESTAMP_OFFSETHOURS(u)					\
	(((u) & 0xF0) >> 4)											// 1111 0000

/*
	0000		0
	0010		15
	0100		30
	0110		45
*/
#define UBF_TIMESTAMP_OFFSETMINUTES(u)					\
	(((u) & 0x04) && ((u) & 0x02)) ? 45 : ((u) & 0x04) ? 30 : ((u) & 0x02) ? 15 : 0

#define UBF_TIMESTAMP_OFFSETNEGATIVE(u)					\
	((u) & 0x08)

#define UBF_TIMESTAMP_MICROSECOND(u)					\
	(((u) >> 8) & 0x3FF)

#define UBF_TIMESTAMP_MILLISECOND(u)					\
	(((u) >> 18) & 0x3FF)

#define UBF_TIMESTAMP_SECOND(u)							\
	(((u) >> 28) & 0x3F)

#define UBF_TIMESTAMP_MINUTE(u)							\
	(((u) >> 34) & 0x3F)

#define UBF_TIMESTAMP_HOUR(u)							\
	(((u) >> 40) & 0x1F)

#define UBF_TIMESTAMP_DAY(u)							\
	(((u) >> 45) & 0x1F)

#define UBF_TIMESTAMP_MONTH(u)							\
	(((u) >> 50) & 0x0F)

#define UBF_TIMESTAMP_YEAR(u)							\
	((((u) >> 54) & 0x3FF) + 2000)

/*
	Preservation bit masks.
*/
#define UBF_TIMESTAMP_KEEP_OFFSET_BITS				(0xF7)
#define UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS			(0xFFFFFFFFF0000000)
#define UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS			(0xFFFFFFFC00000000)
#define UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS			(0xFFFFFF0000000000)
#define UBF_TIMESTAMP_KEEP_FROM_DAY_BITS			(0xFFFFE00000000000)
#define UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS			(0xFFFC000000000000)
#define UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS			(0xFFC0000000000000)

/*
	SUBF_TIMESTRUCT_to_UBF_TIMESTAMP
	UBF_TIMESTAMP_from_UBF_TIMESTRUCT

	Converts the SUBF_TIMESTRUCT ts points to into the UBF_TIMESTAMP t points
	to. Since a UBF_TIMESTAMP always references an offset to UTC, debug versions
	abort when the member bLocalTime of the SUBF_TIMESTRUCT ts points to is true.

	The macro UBF_TIMESTAMP_from_SUBF_TIMESTRUCT() is provided for parameter
	consistency with its name, which is function (target, source).
*/
void SUBF_TIMESTRUCT_to_UBF_TIMESTAMP (UBF_TIMESTAMP * t, SUBF_TIMESTRUCT * ts);

#define UBF_TIMESTAMP_from_SUBF_TIMESTRUCT(ut, ts)		\
			SUBF_TIMESTRUCT_to_UBF_TIMESTAMP ((ut), (ts))

/*
	GetSystemTime_SUBF_TIMESTRUCT
	
	Returns the system time as a SUBF_TIMESTRUCT. The system time is in UTC.
	The returned SUBF_TIMESTRUCT does not contain a time offset.
*/
void GetSystemTime_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts);

/*
	GetSystemTime_UBF_TIMESTAMP

	Returns the system time as a UBF_TIMESTAMP. The system time is in UTC.
	The returned SUBF_TIMESTAMP contains no time offset.
	
	The function calls GetSystemTime_SUBF_TIMESTRUCT () to obtain the system time,
	then calls SUBF_TIMESTRUCT_to_UBF_TIMESTAMP () on the obtained time.
*/
void GetSystemTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut);

/*
	GETSYSTEMTIME_UBF_TIMESTAMP

	Wrapper macro for GetSystemTime_UBF_TIMESTAMP () to reference the
	UBF_TIMESTAMP parameter t.
*/
#define GETSYSTEMTIME_UBF_TIMESTAMP(t)					\
	GetSystemTime_UBF_TIMESTAMP (&(t))

/*
	GetLocalTime_SUBF_TIMESTRUCT
	
	Returns the local time as a SUBF_TIMESTRUCT. The local time is the system
	time (UTC) with an offset.
	
	Local time - offset = system time
*/
#ifdef DEBUG
	void GetLocalTime_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts);
#else
	// The POSIX version is twice as fast here as the Windows
	//	version in debug versions and three times as fast in
	//	release builds.
	void GetLocalTime_SUBF_TIMESTRUCT_psx (SUBF_TIMESTRUCT *pts);

	#define GetLocalTime_SUBF_TIMESTRUCT(p)				\
		GetLocalTime_SUBF_TIMESTRUCT_psx (pts)
#endif

/*
	GetLocalTime_UBF_TIMESTAMP

	Returns the local time as a UBF_TIMESTAMP. The timestamp contains the offset
	to UTC.
	
	Local time - offset = system time
*/
void GetLocalTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut);

/*
	GETLOCALTIME_UBF_TIMESTAMP

	Wrapper macro for GETLOCALTIME_UBF_TIMESTAMP () to reference the
	UBF_TIMESTAMP parameter t.
*/
#define GETLOCALTIME_UBF_TIMESTAMP(t)					\
	GetLocalTime_UBF_TIMESTAMP (&(t))

/*
	SystemTime_UBF_TIMESTAMP

	Returns the system time as a UBF_TIMESTAMP. The system time is in UTC.
	The returned SUBF_TIMESTAMP contains no time offset.
*/
UBF_TIMESTAMP SystemTime_UBF_TIMESTAMP (void)
;

/*
	LocalTime_UBF_TIMESTAMP

	Returns the local time as a UBF_TIMESTAMP. The local time is the system
	time (UTC) with an offset.
	
	Local time - offset = system time
*/
UBF_TIMESTAMP LocalTime_UBF_TIMESTAMP (void)
;


EXTERN_C_END

#endif															// End of U_UBF_TIME_H_INCLUDED.
/****************************************************************************************

	File:		ubf_date_and_time.h
	Why:		Functions for handling date and time.
	OS:			Windows NT Ver. 4.0/2000/XP/Vista/7/8...
	Author:		Thomas
	Created:	2016-11-02
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2016-11-02	Thomas			Created.
2017-06-09	Thomas			Definition of FILETIME moved to ubf_type_definitions.h.
2017-08-29	Thomas			Function GetISO8601DateTimeStampT () added.
2019-08-13	Thomas			Underscore character removed from time interval names.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_UBF_DATETIME_H_INCLUDED
#define U_UBF_DATETIME_H_INCLUDED

/*
#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#include "./ubf_type_definitions.h"
#else
	#include "./../OS/ubf_type_definitions.h"
#endif
*/

#include <time.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubf_times.h"
	
	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _DEBUG
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif

/* Already defined in ubf_times.h.
// Lengths.
#ifndef LEN_ISO8601DATETIMESTAMPMS_NO_OFFS
#define LEN_ISO8601DATETIMESTAMPMS_NO_OFFS	24					// "YYYY-MM-DD hh:mm:ss.xxx"
#endif
#ifndef LEN_ISO8601DATETIMESTAMP								// "YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMP			26
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS								// "YYYY-MM-DD HH:MI:SS.000+01:00"
#define LEN_ISO8601DATETIMESTAMPMS			30
#endif
*/

/*
	ULONGLONGfromFILETIME	macro
	FILETIMEtoULONGLONG		macro
	
	Retrieves the contents of the FILETIME structure as a ULONGLONG
	(unsigned __int64, uint64_t).
	
	Usage:
	ui64Result = ULONGLONGfromFILETIME (ft);
	ui64Result = FILETIMEtoULONGLONG (ft);
*/
#ifndef ULONGLONGfromFILETIME
#define ULONGLONGfromFILETIME(x)((((ULONGLONG) (x).dwHighDateTime) << 32) + (x).dwLowDateTime)
#endif
#ifndef FILETIMEtoULONGLONG
#define FILETIMEtoULONGLONG ULONGLONGfromFILETIME
#endif

/*
	FILETIMEfromULONGLONG	macro
	ULONGLONGtoFILETIME		macro
	
	Copies the high and low values of a ULONGLONG (unsigned __int64)
	into the high and low double words of a FILETIME structure.
	
	Usage:
	FILETIMEfromULONGLONG (ftResult, ui64);
	ULONGLONGtoFILETIME (ftResult, ui64);
*/
#ifndef FILETIMEfromULONGLONG
#define FILETIMEfromULONGLONG(f,u)											\
			(f).dwHighDateTime	= (uint32_t) (u >> 32 & 0x00000000FFFFFFFF);	\
			(f).dwLowDateTime	= (uint32_t) (u & 0x00000000FFFFFFFF)
#endif
#ifndef ULONGLONGtoFILETIME
#define ULONGLONGtoFILETIME FILETIMEfromULONGLONG
#endif

#ifndef GetReadableTimeSpanFromFILETIME
#define GetReadableTimeSpanFromFILETIME	GetReadableTimeSpanFILETIME
#endif

/*
	Macros to set TIMEVAL values.

	Examples:

	TIMEVAL		tv;
	SET_pTIMEVAL_S		(&tv, 10);
	SET_TIMEVAL_S		(tv, 10);

	These macros set one member of the structure to the provided value. The other member is set
	to 0.
	
	SET_pTIMEVAL_S		(&tv,	10);							// Set timeout to 10 seconds.
	SET_TIMEVAL_S		(tv,	10);							// Set timeout to 10 seconds.
	SET_pTIMEVAL_US		(&tv,	100);							// Set timeout to 100 microseconds.
	SET_TIMEVAL_US		(tv,	100);							// Set timeout to 100 microseconds.
	SET_pTIMEVAL_MS		(&tv,	1000);							// Set timeout to 1 second
																//	(1000 milliseconds).
	SET_TIMEVAL_MS		(tv,	1000);							// Set timeout to 1 second
																//	(1000 milliseconds).
	SET_pTIMEVAL_NS 	(&tv,	1000);							// Set timeout to 1 microsecond
																//	(1000 nanoseconds).
	SET_TIMEVAL_NS		(tv,	1000);							// Set timeout to 1 microsecond
																//	(1000 nanoseconds).
*/
#define SET_pTIMEVAL_S(t,vs)	(t)->tv_sec	= vs;	(t)->tv_usec	= 0
#define SET_TIMEVAL_S(t,vs)		(t).tv_sec	= vs;	(t).tv_usec		= 0
#define SET_pTIMEVAL_US(t,us)	(t)->tv_sec	= 0;	(t)->tv_usec	= (us * 1000)
#define SET_TIMEVAL_US(t,us)	(t).tv_sec	= 0;	(t).tv_usec		= (us * 1000)
#define SET_pTIMEVAL_MS(t,ms)	(t)->tv_sec	= 0;	(t)->tv_usec	= (ms * 1000 * 1000)
#define SET_TIMEVAL_MS(t,ms)	(t).tv_sec	= 0;	(t).tv_usec		= (ms * 1000 * 1000)
#define SET_pTIMEVAL_NS(t,ns)	(t)->tv_sec	= 0;	(t)->tv_usec	= ns
#define SET_TIMEVAL_NS(t,ns)	(t).tv_sec	= 0;	(t).tv_usec		= ns

/*
	Macros for the TIMSPEC structure.

	Examples:

	TIMESPEC	tc;

	SET_pTIMESPEC_MINS	(&tc, 2);								// 2 minutes.
	SET_TIMESPEC_MINS	(tc, 2);								// 2 minutes.
*/
#define SET_pTIMESPEC_MINS(t,mins)	(t)->tv_sec = (mins) * 60;	(t)->tv_nsec = 0
#define SET_TIMESPEC_MINS(t,mins)	(t).tv_sec = (mins) * 60;	(t).tv_nsec = 0

#ifdef __cplusplus
	extern "C" {
#endif

// If we haven't got the timespec struct, define it here.
#if defined OS_IS_WINDOWS && defined _CRT_NO_TIME_T
	// See http://pubs.opengroup.org/onlinepubs/7908799/xsh/time.h.html .
    struct timespec
    {
        time_t tv_sec;  // Seconds - >= 0
        long   tv_nsec; // Nanoseconds - [0, 999999999]
    };
#else
	//typedef struct timeval TIMEVAL
#endif
typedef struct timespec TIMESPEC;

/*
	GetReadableTimeSpan
	
	Returns the value of ullTime in a readable format in chBuf.
	The smallest value returned is 1 us (microsecond).
	
	Parameters
	----------
	
	chBuf			A pointer to the buffer that receives the output.
	stLen			The length of chBuf in bytes. It includes the terminating
					NUL character.
	ullIime			A ULONGLONG (unsignded __int64) value that contains
					the timespan. It is expected that the value has been
					converted from a FILETIME structure.
					
	Remarks
	-------
	
	The return buffer contains the value of ullTime in a readable format.
	The format is "nnnd hh:mm:ss.mssuss".
	nnn				The amount of days the timespan covers.
	hh				The amount of remaining hours.
	mm				The amount of remaining minutes.
	ss				The amount of remaining seconds.
	mss				The amount of remaining milliseconds.
	uss				The amount of remainind microseconds.
	Example: "  7d 19:22:10.731322"
	
	If the buffer is too small to hold the value of ullTime in a readable
	format it is truncated but still terminated with a NUL character.
*/
void GetReadableTimeSpan			(
										char		*chBuf,
										size_t		stLen,
										ULONGLONG 	ullTime
									)
;

/*
	GetReadableTimeSpanFILETIME
	GetReadableTimeSpanFromFILETIME macro
	
	This function is identical to GetReadableTimeSpan () with the difference that the
	input parameter is a FILETIME structure.
*/
void GetReadableTimeSpanFILETIME	(
										char		*chBuf,
										size_t		stLen,
										FILETIME	ftTime
									)
;

/*
	GetSystemTimeAsULONGLONG
	
	Retrieves the current date and time (system time) as a Windows FILETIME
	ULONGLONG.
	
	On Windows it retrieves the system time as FILETIME with a call to
	GetSystemTimeAsFileTime () and converts it to an unsigned long integer
	(64 bit) ULONGLONG.
	
	On POSIX systems it calls clock_gettime () with a clock ID of CLOCK_REALTIME
	and then calls ULONGLONG_from_timespec () to retrieve the time as a ULONGLONG.
	The function ULONGLONG_from_timespec () adds the difference between the Unix
	epoch and the Windows FILETIME epoch before returning, which is
	116444736000000000. This makes results retrieved on Windows compatible with
	results retrieved on POSIX systems.
	
	If no absolute time is required it is faster on POSIX platforms to use
	GetSystemTimeAsULONGLONGrel () instead. There is no difference on Windows
	between these two functions.
	
	The function returns the time as FILETIME ULONGLONG, which is the amount
	of 100 nanoseconds ticks since the FILETIME epoch. The FILETIME epoch starts
	on 1601-01-01. See
	https://docs.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-filetime
	for more information.
*/									
ULONGLONG GetSystemTimeAsULONGLONG (void);

/*
	GetSystemTimeAsULONGLONGrel
	
	Retrieves a relative FILETIME value as a ULONGLONG that can be used for time
	measurements.

	On Windows it retrieves the system time as FILETIME with a call to
	GetSystemTimeAsFileTime () and converts it to an unsigned long integer
	(64 bit) ULONGLONG.

	On POSIX systems it calls clock_gettime () with a clock ID of CLOCK_MONOTONIC_COARSE,
	if available, and then calls ULONGLONG_from_timespec_rel () to retrieve the time
	as a ULONGLONG. On systems that do not support a CLOCK_MONOTONIC_COARSE clock the
	function uses CLOCK_MONOTONIC.
	
	The function does not add the difference between the Unix epoch and the Windows
	FILETIME epoch before returning. This makes results retrieved by this function
	on Windows incompatible with results retrieved on POSIX systems.
	
	On POSIX platforms the function is a faster alternative to
	GetSystemTimeAsULONGLONG () when a relative time is sufficient. On Windows the
	function is identical to GetSystemTimeAsULONGLONG ().
	
	The function returns a FILETIME ULONGLONG which is not adjusted to the Windows
	epoch but suitable for relative measurements. On Windows the return value is
	correctly adjusted to the Windows epoch but in order to retain compatibility
	between platforms it should only be used for relative time measurements.
*/
ULONGLONG GetSystemTimeAsULONGLONGrel (void);

/*
	GetSystemTimeAsFileTime
	
	Implementation of the Windows API GetSystemTimeAsFileTime () to make it available
	on POSIX. See
	https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtimeasfiletime
	for details.
*/
#ifdef PLATFORM_IS_POSIX
	void GetSystemTimeAsFileTime (FILETIME *ft);
#endif

/*
	SUBSTRUCT_ULONGLONG_FROM_ULONGLONG
	
	Substracts u2 from u1 provided that u1 is greater or equal to u2.
	If this is not the case the macro sets u1 to (ULONGLONG) -1 to
	signal the underflow.
*/
#define SUBSTRUCT_ULONGLONG_FROM_ULONGLONG(u1, u2)		\
	(((u1) >= (u2)) ? ((u1) - (u2)) : ((ULONGLONG) -1))

/*
	SetFILETIMEtoZero

	Zeros all members of the FILETIME ft.
*/
void SetFILETIMEtoZero (FILETIME *ft);

/*
	SETFILETIMETOZERO
	
	Wrapper macro for SetFILETIMEtoZero () to dereference the pointer to the FILETIME
	structure.
*/
#define SETFILETIMETOZERO(ft)	\
			SetFILETIMEtoZero (&(ft))

/*
	SetFILETIMEtoMaxFILETIME

	Sets both double words of the given FILETIME structure to the max value
	of (-1).
*/
void SetFILETIMEtoMaxFILETIME (FILETIME *ft);

/*
	cpyFILETIME
	
	Copies the contents of the FILETIME structure ftsource into fttarget.
*/
void cpyFILETIME (FILETIME *fttarget, FILETIME *ftsource);

/*
	CPYFILETIME
	
	Convenience wrapper for cpyFILETIME () that adds references to the FILETIME
	parameters.
*/
#define CPYFILETIME(ft1, ft2)							\
	cpyFILETIME (&(ft1), &(ft2))
	
/*
	cmpFILETIME
	
	Compares the FILETIME structure ft1 with the FILETIME structure ft2.
	
	The function returns 0, if both structures are identical, 1 if ft1 is
	greater than ft2, and -1 if ft1 is smaller than ft2.
*/
int cmpFILETIME (FILETIME *ft1, FILETIME *ft2);

/*
	CMPFILETIME
	
	Wrapper for cmpFILETIME () to add references to the FILETIME parameters.
*/
#define CMPFILETIME(ft1, ft2)							\
	cmpFILETIME (&(ft1), &(ft2))
	
/*
	isFileTimeNotZero

	Returns true if either part (member) of the FILETIME structure ft is not 0, false
	otherwise.
*/
bool isFileTimeNotZero (FILETIME *ft);

/*
	isFileTimeZero

	Returns true if both members of the FILETIME structure ft are 0, false otherwise.
*/
bool isFileTimeZero (FILETIME *ft);

/*
	ISFILETIMEZERO
	
	Convenience wrapper macro for isFileTimeZero () to dereference the pointer to the
	FILETIME structure.
*/
#define ISFILETIMEZERO(ft)	\
			isFileTimeZero ((&ft))
/*
	FILETIMEfromUnixTimeT
	FILETIMEfromUnixTime
	UnixTimeToFILETIME

	Converts a time_t value to a FILETIME.
	
	Note that this function was called UnixTimeToFileTime () previously
	and that the parameters have been swapped. Target parameter is now
	the first parameter with the time_t second.
*/
//void UnixTimeToFileTime (time_t t, LPFILETIME pft);
void FILETIMEfromUnixTimeT (FILETIME *pft, time_t t);
// We want a compilation error if the old name is used.
#define UnixTimeToFileTime(t,pft)						\
	Error - UnixTimeToFileTime () has been renamed to FILETIMEfromUnixTimeT ()\
	Note that the parameters have also been swapped!
#define UnixTimeToFILETIME(pft, f)						\
	FILETIMEfromUnixTimeT ((pft), (f))
#define FILETIMEfromUnixTime(pft, f)						\
	FILETIMEfromUnixTimeT ((pft), (f))

/*
 *	POSIX systems do not have this structure.
*/
#ifndef _WIN32
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif

/*
*/
void UnixTimeToSystemTime (time_t t, LPSYSTEMTIME pst);

/*
	FileTime_to_POSIX
	
	Converts the FILETIME ft to Unix/POSIX time (or Unix or POSIX epoch). See
	https://en.wikipedia.org/wiki/Unix_time
	
	The function returns the FILETIME parameter ft converted to Unix/POSIX.
*/
LONGLONG FileTime_to_POSIX (FILETIME ft);

/*
	GetISO8601Date

	Retrieves the current local date in ISO 8601 format. The buffer chISO8601 points
	to must be at least SIZ_ISO8601DATE octets long.

	Example of returned string: "YYYY-MM-DD"
*/
void GetISO8601Date (char *chISO8601Date);

/*
	GetISO8601Week_s

	Retrieves the current local date as a string in ISO 8601 format. The buffer
	chISO8601Week points to must be at least SIZ_ISO8601WEEK octets long.
	The function calls snprintf () to compile the output string and might therefore
	be slightly slower than GetISO8601Week_c ().

	Example of returned string: "YYYY-W04"
*/
void GetISO8601Week_s (char *chISO8601Week);

/*
	GetISO8601Week_c

	Retrieves the current local date as a string in ISO 8601 format. The buffer
	chISO8601Week points to must be at least SIZ_ISO8601WEEK octets long.
	The function does not call snprintf () and might therefore be a slightly faster
	alternative to GetISO8601Week_s ().

	Example of returned string: "YYYY-W04"
*/
void GetISO8601Week_c (char *chISO8601Week);

/*
	GetISO8601Week

	Wrapper macro for GetISO8601Week_c ().
*/
#define GetISO8601Week(sz)								\
			GetISO8601Week_c (sz)

/*
	Retrieves the current date/time as a text of the
	International Standard ISO 8601 format:
	YYYY-MM-DD HH:MI:SS +/-TDIF
	The buffer chISO8601DateTimeStamp points to must be at least
	SIZ_ISO8601DATETIMESTAMP bytes long.

	Example return values:	YYYY-MM-DD HH:MI:SS+01:00
							YYYY-MM-DD HH:MI:SS-04:00
							2017-08-29 21:39:10+01:00

	See https://www.cl.cam.ac.uk/~mgk25/iso-time.html and https://en.wikipedia.org/wiki/ISO_8601
	for good summaries.
*/
void GetISO8601DateTimeStamp (char *chISO8601DateTimeStamp);

/*
	GetISO8601DateTimeStampT
	
	The function is identical to GetISO8601DateTimeStamp (), which retrieves the
	current date/time as a text of the International Standard ISO 8601 format,
	with the exception that GetISO8601DateTimeStampT () inserts the 'T' character
	referred to by the standard. The buffer chISO8601DateTimeStamp points to must be
	at least SIZ_ISO8601DATETIMESTAMP bytes long.

	Example return values:	YYYY-MM-DDTHH:MI:SS+01:00
							YYYY-MM-DDTHH:MI:SS-04:00
							2017-08-29T21:39:10+01:00
							
	While it is easier for a human to read an ISO 8601 date/time containing a
	blank (or space) character (' ', ASCII 20h, 32d) instead of a capital 'T',
	some applications might require precise conformity to the standard.
*/
void GetISO8601DateTimeStampT (char *chISO8601DateTimeStamp);

/*
	GetISO8601DateTimeStampMS

	Returns the current date/time in ISO 8601 format.
	2008-10-23 10:44:42.012+01:00

	Retrieves the current date/time as a text of the
	International Standard ISO 8601 format:
	YYYY-MM-DD HH:MI:SS.mis+/-TDIF
	yyyy-mm-dd hh:mi:ss.mis+01:00

	Example: YYYY-MM-DD HH:MI:SS.125+01:00
	         YYYY-MM-DD HH:MI:SS.490-04:00

	The string chISODateTime must hold enough space for 29 characters + NUL. The constant
	SIZ_ISO8601DATETIMESTAMPMS can be used for this length.
	
*/
void GetISO8601DateTimeStampMS (char *chISO8601DateTimeStampMS);

/*
	GetISO8601DateTimeStampMST
	
	The function calls GetISO8601DateTimeStampMS () to obtain an ISO 8601 date and timestamp,
	including milliseconds and offset, then inserts the 'T' the standard requires.

	The buffer chISO8601DateTimeStampMS points to must be at least SIZ_ISO8601DATETIMESTAMPMS
	octets long.
*/
void GetISO8601DateTimeStampMST (char *chISO8601DateTimeStampMS);

/*
	ubf_get_system_time
	
	Returns the system time (in UTC) as a FILETIME structure.
*/
void ubf_get_system_time (FILETIME *ft);

/*
	UBF_GET_SYSTEM_TIME

	Convenience macro to dereference the pointer parameter of ubf_get_system_time ().
*/
#define UBF_GET_SYSTEM_TIME(t)	\
			ubf_get_system_time (&(t))
/*
	ubf_get_local_time
	
	Returns the local time as a FILETIME structure.
*/
//void ubf_get_local_time (FILETIME *ft);

/*
	UBF_GET_LOCAL_TIME

	Convenience macro to dereference the pointer parameter of ubf_get_local_time ().
*/
/* Maybe this function is not required.
#define UBF_GET_LOCAL_TIME(t)	\
			ubf_get_local_time (&(t))
*/

/*
	ubf_get_system_time_ULONGLONG

	Returns the system time as ULONGLONG in the buffer pulltime points to.
*/
void ubf_get_system_time_ULONGLONG (ULONGLONG *pulltime);

/*
	UBF_GET_SYSTEM_TIME_ULONGLONG

	Convenience wrapper macro for ubf_get_system_time_ULONGLONG () to dereference the
	parameter.
*/
#define UBF_GET_SYSTEM_TIME_ULONGLONG(l)	\
			ubf_get_system_time_ULONGLONG (&(l))

/*
	ubf_get_system_time_ULONGLONG_rel
	
	Returns the relative system time as ULONGLONG in the buffer pulltime
	points to by calling GetSystemTimeAsULONGLONG_rel ().
*/
void ubf_get_system_time_ULONGLONG_rel (ULONGLONG *pulltime);

/*
	UBF_GET_SYSTEM_TIME_ULONGLONG_REL

	Convenience wrapper macro for ubf_get_system_time_ULONGLONG_rel () to dereference the
	parameter.
*/
#define UBF_GET_SYSTEM_TIME_ULONGLONG_REL(l)	\
			ubf_get_system_time_ULONGLONG_rel (&(l))

/*
	clock_gettime

	Dodgy implementation of the clock_gettime () API on Linux/Unix derivatives for
	Windows. See https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
	and https://linux.die.net/man/3/clock_gettime . For us, this function is good enough
	at the moment since we're not using high precisions. It is fast and simple.
	http://www.catb.org/esr/time-programming/ shows that clock_gettime () is part of
	POSIX, hence should be available on all supported platforms.
*/
#ifdef UBF_WINDOWS
	int clock_gettime (int iclk_id, struct timespec *spec);
#endif

/*
	Parameters for clock_gettime (). We only support CLOCK_REALTIME and CLOCK_MONOTONIC.
	These are again for Windows only since Unix/Linux platforms should come with them
	natively. Their values here have been made up by me (2017-10-02, Thomas) and have
	nothing to do with their values in time.h on Linux/Unix platforms.
*/
#ifdef OS_IS_WINDOWS
	#ifndef CLOCK_REALTIME
	#define CLOCK_REALTIME		0
	#endif
	#ifndef CLOCK_MONOTONIC
	#define CLOCK_MONOTONIC		1
	#endif
#endif

// The coarse clock IDs on POSIX systems. See
//	http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE			CLOCK_REALTIME
#endif
#ifndef CLOCK_MONOTONIC_COARSE
#define CLOCK_MONOTONIC_COARSE			CLOCK_MONOTONIC
#endif

/*
	IsLeapYear

	Returns TRUE if the year in Y is a leap year, FALSE otherwise.
*/
bool IsLeapYear (uint32_t Y);

/*
	GetISO8601DayOfYear
*/
uint32_t GetISO8601DayOfYear (uint32_t Y, uint32_t M, uint32_t D);

/*
	GetISO8601Jan1WeekDay
*/
uint32_t GetISO8601Jan1WeekDay (uint32_t Y);

/*
	GetISO8601WeekDay
*/
uint32_t GetISO8601WeekDay (uint32_t Y, uint32_t M, uint32_t D);

/*
	GetISO8601WeekNumberFromDate
	
	Returns the ISO 8601 week number for the given date. The parameter
	aY points to a long variable in which the function stores the year
	number which may have been adjusted to Y + 1. The caller is advised
	to always work with this returned year.
*/
uint32_t GetISO8601WeekNumberFromDate (uint32_t Y, uint32_t M, uint32_t D, uint32_t *aY);

/*
	HasMonth28Days
	
	Returns true if the month m has 28 days. In addition to the month, this
	function requires the year to determine if it is a leap year.
*/
bool HasMonth28Days (uint8_t m, uint32_t y);

/*
	HasMonth29Days
	
	Returns true if the month m has 29 days. In addition to the month, this
	function requires the year to determine if it is a leap year.
*/
bool HasMonth29Days (uint8_t m, uint32_t y);

/*
	HasMonth30Days
	
	Returns true if the month m has 30 days.
*/
bool HasMonth30Days (uint8_t m);

/*
	HasMonth31Days
	
	Returns true if the month m has 31 days.
*/
bool HasMonth31Days (uint8_t m);

/*
	DaysInMonth
	
	Returns the number of days within month m of year y.
*/
uint8_t DaysInMonth (uint8_t m, uint32_t y);

/*
	_DayOfWeek
	
	Returns the day of the week starting with 0 == Sunday, 1 == Monday, etc.
	The function has been taken from
	https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Implementation-dependent_methods
	(Tomohiko Sakamoto).
	
	The year must be > 1752, at least in the UK.
	
	Use the function DayOfWeek () to obtain the weekday according to ISO 8601
	where 0 == Monday, 1 == Tuesday, ..., 6 == Sunday.
*/
int _DayOfWeek (int y, int m, int d);

/*
	DayOfWeek
	
	Returns the day of the week according to ISO 8601 weekday ordering, starting with
	0 == Monday, 1 == Tuesday, ..., 6 == Sunday.

	The year must be > 1752, at least in the UK, since the function calls _DayOfWeek ()
	to obtain the day of week and adjusts it to an ISO 8601 week.	
*/
int DayOfWeek (int y, int m, int d);

/*
	FILETIME_to_ISO8601

	Writes an array of characters in ISO 8601 format to chISO from the FILETIME structure
	ft points to. Since a FILETIME structure does not contain an offset to UTC, the
	output has the format "YYYY-MM-DD hh:mm:ss.xxx" and does not include an offset. The
	buffer chISO points to is expected to be at least LEN_ISO8601DATETIMESTAMPMS_NO_OFFS
	bytes long.
	
	The function has never been implemented.
*/
void FILETIME_to_ISO8601 (char *chISO, FILETIME *ft);

/*
	IsBuildYearOrNewer_UBF_TIMESTAMP

	Returns true if the UBF_TIMESTAMP pts points to is reasonably recent
	and seems legit. Reasonably recent means at least from the year the function
	BuildYear_uint64 () returns, which is the compilation/build year of this
	module. All values are checked against their maximum ranges. The function
	does not check if the given date/timestamp exists. For instance, the
	function returns true for 2021-02-31 if the module was compiled in
	2021. It would return false for 2021-02-31 if the module was compiled
	in 2022.
*/
bool IsBuildYearOrNewer_UBF_TIMESTAMP (UBF_TIMESTAMP *pts);

/*
	ValuesWithinLimits_SUBF_TIMESTRUCT

	Returns true if all values of the SUBF_TIMESTRUCT ts points to are
	within the limits, false otherwise. The function does not check whether the
	date/timestamp is valid/exists. For instance, the function returns true for
	2021-02-31, which is not a valid date because it does not exist.
*/
bool ValuesWithinLimits_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *ts);

/*
	UBF_TIMESTAMP_to_SUBF_TIMESTRUCT

	Converts the UBF_TIMESTAMP to a SUBF_TIMESTRUCT and stores it at the memory
	ts points to.

	The macro SUBF_TIMESTRUCT_from_UBF_TIMESTAMP() is provided for parameter
	consistency with its name, which is function (target, source).

	The function returns true on success, false otherwise.
*/
bool UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *ts, UBF_TIMESTAMP t);

#define SUBF_TIMESTRUCT_from_UBF_TIMESTAMP(ts, ut)		\
			UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (ts, ut)

/*
	SUBF_TIMESTRUCT_to_ISO8601
	ISO8601_from_SUBF_TIMESTRUCT

	Writes an array of characters in ISO 8601 format to chISO from the SUBF_TIMESTRUCT
	pts points to. Since a SUBF_TIMESTRUCT structure contains an offset to UTC,
	the output has the format "YYYY-MM-DD HH:MI:SS.000+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMPMS, or LEN_ISO8601DATETIMESTAMPMS + 1, bytes long, which
	includes a terminating NUL byte.
*/
void SUBF_TIMESTRUCT_to_ISO8601 (char *chISO, SUBF_TIMESTRUCT *pts);

#define ISO8601_from_SUBF_TIMESTRUCT(i, p)				\
	SUBF_TIMESTRUCT_to_ISO8601((i), (p))

/*
	ISO8601_from_UBF_TIMESTAMP_s

	Writes an array of characters in ISO 8601 format to chISO from the UBF_TIMESTAMP
	ts. Instead of the ISO 8601 date and time separator ("T") this functions inserts a
	space for easier human readability. Since a UBF_TIMESTAMP timestamp contains an offset
	to UTC, the output has the format "YYYY-MM-DD HH:MI:SS.000+01:00", which includes the
	offset to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMPMS, or LEN_ISO8601DATETIMESTAMPMS + 1, bytes long, which
	includes a terminating NUL byte.

	If a fully ISO 8601 compliant representation is required, the function
	ISO8601T_from_UBF_TIMESTAMP () returns the same string but with the correct
	date and time separator ("T"), i.e. "YYYY-MM-DDTHH:MI:SS.000+01:00".
*/
void ISO8601_from_UBF_TIMESTAMP_s (char *chISO, UBF_TIMESTAMP ts);

/*
	This macro should be made obsolete. 2024-08-13, Thomas.
*/
#define UBF_TIMESTAMP_to_ISO8601(i, t)				\
	ISO8601_from_UBF_TIMESTAMP ((i), (t))

/*
	ISO8601_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601_from_UBF_TIMESTAMP () but does not use snprintf (),
	which means it is faster than ISO8601_from_UBF_TIMESTAMP ().
*/
void ISO8601_from_UBF_TIMESTAMP_c (char *chISO, UBF_TIMESTAMP ts);

/*
	ISO8601_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601_from_UBF_TIMESTAMP(c,t)				\
		ISO8601_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601_from_UBF_TIMESTAMP(c,t)			\
		ISO8601_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601T_from_UBF_TIMESTAMP

	Writes an array of characters in ISO 8601 format to chISO from the UBF_TIMESTAMP
	ts. Since a UBF_TIMESTAMP timestamp contains an offset to UTC,
	the output has the format "YYYY-MM-DDTHH:MI:SS.000+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMPMS, or LEN_ISO8601DATETIMESTAMPMS + 1, bytes long, which
	includes a terminating NUL byte.

	This function inserts the fully compliant date and time separator, which is a capital
	"T". The function ISO8601_from_UBF_TIMESTAMP () produces an identical result but
	replaces the T with a more human readable space character.
*/
void ISO8601T_from_UBF_TIMESTAMP_s (char *chISO, UBF_TIMESTAMP ts);

/*
	This macro should be made obsolete. 2024-08-13, Thomas.
*/
#define UBF_TIMESTAMP_to_ISO8601T(i, t)				\
	ISO8601T_from_UBF_TIMESTAMP ((i), (t))

/*
	ISO8601T_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601T_from_UBF_TIMESTAMP () but does not use snprintf (),
	which means it is much faster than ISO8601T_from_UBF_TIMESTAMP ().
*/
void ISO8601T_from_UBF_TIMESTAMP_c (char *chISO, UBF_TIMESTAMP ts);

/*
	ISO8601T_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601T_from_UBF_TIMESTAMP(c,t)			\
		ISO8601T_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601T_from_UBF_TIMESTAMP(c,t)			\
		ISO8601T_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601Date_from_UBF_TIMESTAMP

	Saves the NUL-terminated date of the UBF_TIMESTAMP ts in the buffer chISODateOnly
	points to. The buffer must have a size of at least SIZ_ISO8601DATE octets.

	Example of returned string: "YYYY-MM-DD"
*/
void ISO8601Date_from_UBF_TIMESTAMP (char *chISODateOnly, UBF_TIMESTAMP ts);

/*
	ISO8601Date_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601Date_from_UBF_TIMESTAMP () but does not use snprintf (),
	which means it is faster than ISO8601Date_from_UBF_TIMESTAMP ().
*/
void ISO8601Date_from_UBF_TIMESTAMP_c (char *chISODateOnly, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndWeek_from_UBF_TIMESTAMP_s

	Retrieves the date/time stamp ts as a NUL-terminated string in ISO 8601 format. The buffer
	chISO8601Week points to must be at least SIZ_ISO8601YEARANDWEEK octets long.

	Example of returned string: "YYYY-W04"
*/
void ISO8601YearAndWeek_from_UBF_TIMESTAMP_s (char *chISO8601YearAndWeek, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndWeek_from_UBF_TIMESTAMP_c

	Identical to ISO8601YearAndWeek_from_UBF_TIMESTAMP () but does not call snprintf (),
	which means it might be slightly faster.

	Example of returned string: "YYYY-W04"
*/
void ISO8601YearAndWeek_from_UBF_TIMESTAMP_c (char *chISO8601YearAndWeek, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndWeek_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601YearAndWeek_from_UBF_TIMESTAMP(c,t)	\
		ISO8601YearAndWeek_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601YearAndWeek_from_UBF_TIMESTAMP(c,t)	\
		ISO8601YearAndWeek_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601DateAndHour_from_UBF_TIMESTAMP_s

	Retrieves the date/time stamp in ts as a NUL-terminated string in ISO 8601 that contains the
	date and the hour. The buffer chISODateAndHour points to must be at least
	SIZ_ISO8601DATEANDHOUR octets long.

	The function does not take an offset into consideration and might therefore
	result in an hour value that is perceived as being incorrect (although it is not).

	Example of returned string: "YYYY-MM-DD 18"
*/
void ISO8601DateAndHour_from_UBF_TIMESTAMP_s (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601DateAndHour_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601DateAndHour_from_UBF_TIMESTAMP () but does not
	call snprintf (), which means it is faster than ISO8601DateAndHour_from_UBF_TIMESTAMP ().
*/
void ISO8601DateAndHour_from_UBF_TIMESTAMP_c (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601DateAndHour_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601DateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateAndHour_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601DateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateAndHour_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601TDateAndHour_from_UBF_TIMESTAMP_s

	The function is identical to ISO8601DateAndHour_from_UBF_TIMESTAMP_s () but inserts
	a "T" instead of a space between date and time.
*/
void ISO8601TDateAndHour_from_UBF_TIMESTAMP_s (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601TDateAndHour_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601DateAndHour_from_UBF_TIMESTAMP_c () but inserts
	a "T" instead of a space between date and time.
*/
void ISO8601TDateAndHour_from_UBF_TIMESTAMP_c (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601TDateAndHour_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601TDateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateAndHour_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601TDateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateAndHour_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_s

	Retrieves the date/time stamp in ts as a NUL-terminated string in ISO 8601 that contains the
	date, hour, and minute. The buffer chISODateHourAndMinute points to must be at least
	SIZ_ISO8601DATEHOURANDMINUTE octets long.

	The function does not take an offset into consideration and might therefore
	result in an hour value that is perceived as being incorrect (although it is not).

	Example of returned string: "2023-11-16 09:47"
*/
void ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_s (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601DateHourAndMinute_from_UBF_TIMESTAMP () but does not call
	snprintf. It is therefore much faster.
*/
void ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_c (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601DateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601DateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_s

	The function is identical to ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_s () but inserts
	a "T" instead of a space between date and time.

	Example of returned string: "2023-11-16T09:47"
*/
void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_s (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_c () but inserts
	a "T" instead of a space between date and time.

	Example of returned string: "2023-11-16T09:47"
*/
void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_c (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_s (c, t)
#else
	#define ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_c (c, t)
#endif

/*
	ISO8601Year_from_UBF_TIMESTAMP

	Returns the year extracted from ts as "YYYY" as a NUL-terminated string. The buffer
	chYear points to must be at least SIZ_ISO8601YEAR octets big.
*/
void ISO8601Year_from_UBF_TIMESTAMP (char *chYear, UBF_TIMESTAMP ts);

/*
	ISO8601Year_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601Year_from_UBF_TIMESTAMP () but is slightly faster
	since it does not not call snprintf ().

	Returns the year extracted from ts as "YYYY" as a NUL-terminated string. The buffer
	chYear points to must be at least SIZ_ISO8601YEAR octets big.
*/
void ISO8601Year_from_UBF_TIMESTAMP_c (char *chYear, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndMonth_from_UBF_TIMESTAMP

	Returns the extracted year and month as "YYYY-MM". The buffer pointed to by
	chISOYearAndMonth must be at least SIZ_ISO8601YEARANDMONTH bytes long. The returned
	string is NUL-terminated.
*/
void ISO8601YearAndMonth_from_UBF_TIMESTAMP (char *chISOYearAndMonth, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndMonth_from_UBF_TIMESTAMP_c

	The function is identical to ISO8601YearAndMonth_from_UBF_TIMESTAMP () but is faster
	because it does not call snprintf ().
*/
void ISO8601YearAndMonth_from_UBF_TIMESTAMP_c (char *chISOYearAndMonth, UBF_TIMESTAMP ts);

/*
	UBF_TIMESTAMP_to_ISO8601_Holocene
	ISO8601_Holocene_from_UBF_TIMESTAMP

	Identical to UBF_TIMESTAMP_to_ISO8601 () but returns the timestamp in the
	Holocene format. See https://en.wikipedia.org/wiki/Holocene_calendar .
	The buffer chISO points to must be at least SIZ_ISO8601DATETIMESTAMPMS_HOL
	long. This includes a terminating NUL byte.
*/
void UBF_TIMESTAMP_to_ISO8601_Holocene (char *chISO, UBF_TIMESTAMP ts);

#define ISO8601_Holocene_from_UBF_TIMESTAMP(i, ts)		\
	UBF_TIMESTAMP_to_ISO8601_Holocene ((i), (ts))

/*
	SUBF_TIMESTRUCT_to_ISO8601_no_ms
	ISO8601_no_ms_from_SUBF_TIMESTRUCT

	Writes an array of characters in ISO 8601 format to chISO from the SUBF_TIMESTRUCT
	t points to but without milliseconds. Since a SUBF_TIMESTRUCT contains an offset to UTC,
	the output has the format "YYYY-MM-DD HH:MI:SS+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMP bytes long.
*/
void SUBF_TIMESTRUCT_to_ISO8601_no_ms (char *chISO, SUBF_TIMESTRUCT *t)
;

#define ISO8601_no_ms_from_SUBF_TIMESTRUCT(i, t)		\
	SUBF_TIMESTRUCT_to_ISO8601_no_ms ((i), (t))

/*
	UBF_TIMESTAMP_to_ISO8601_no_ms

	Writes an array of characters in ISO 8601 format to chISO from the UBF_TIMESTAMP
	ts but without milliseconds. Since a UBF_TIMESTAMP timestamp contains an offset to UTC,
	the output has the format "YYYY-MM-DD HH:MI:SS+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMP bytes long.

	The function first converts the UBF_TIMESTAMP ts into a SUBF_TIMESTRUCT structure,
	then calls SUBF_TIMESTRUCT_to_ISO8601_no_ms ().
*/
void UBF_TIMESTAMP_to_ISO8601_no_ms (char *chISO, UBF_TIMESTAMP ts);


/*
	UBF_TIMESTAMP_to_ISO8601_no_ms_Holocene

	Identical to UBF_TIMESTAMP_to_ISO8601_no_ms () but returns the timestamp
	in the Holocene format, which is 10000 years greater than the ISO8601
	timestamp. See https://en.wikipedia.org/wiki/Holocene_calendar for more information.
	The buffer chISO must have space for at least SIZ_ISO8601DATETIMESTAMP_HOL
	octets. This number includes the terminating NUL character.
*/
void UBF_TIMESTAMP_to_ISO8601_no_ms_Holocene (char *chISO, UBF_TIMESTAMP ts);

/*
	MS_from_SUBF_TIMESTRUCT

	Returns the amount of milliseconds of the time of the SUBF_TIMESTRUCT pts points
	to. The date is not taken into account, and neither is an offset.
*/
uint64_t MS_from_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts);

/*
	GetLocalTime_ISO8601T_noMSnoOffs

	Returns the current local date and time in ISO 8601 format, excluding milliseconds
	and excluding a timezone.

	The buffer szISO points to must be at least LEN_ISO8601DATETIMESTAMP_NO_OFFS octets/bytes
	long. The function does not NUL-terminate the string. It writes out exactly
	LEN_ISO8601DATETIMESTAMP_NO_OFFS octets/bytes. For an identical function that does
	NUL-terminate the string, see GetLocalDateTime_ISO8601T_noMSnoOffs_n () below.

	"YYYY-MM-DDThh:mm:ss"
*/
void GetLocalDateTime_ISO8601T_noMSnoOffs (char *szISO)
;

/*
	GetLocalDateTime_ISO8601T_noMSnoOffs_n

	Returns the current local date and time in ISO 8601 format, excluding milliseconds
	and excluding a timezone.

	The buffer szISO points to must be at least SIZ_ISO8601DATETIMESTAMP_NO_OFFS, which is
	LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1 octets/bytes long. The function writes out exactly
	SIZ_ISO8601DATETIMESTAMP_NO_OFFS octets/bytes. For an identical function that does
	not write a NUL terminator, see GetLocalDateTime_ISO8601T_noMSnoOffs () below.

	"YYYY-MM-DDThh:mm:ss"
*/
void GetLocalDateTime_ISO8601T_noMSnoOffs_n (char *szISO)
;

/*
	BuildYear_uint64

	Returns the compilation year of the module (when it is compiled) as an unsigned
	16 bit integer. It uses the C/C++ default preprocessor macro __DATE__ to obtain
	this year.
*/
uint64_t BuildYear_uint64 (void);

/*
	BuildYear_uint16

	Returns the compilation year of the module (when it is compiled) as an unsigned
	16 bit integer. The function calls YearOfBuilduint64 and shortens its result
	to a uint16_t.
*/
uint16_t BuildYear_uint16 (void);

/*
	FormattedMilliseconds

	Copies the time value in uiTimeInMilliseconds as a formatted string to the
	buffer chFormatted points to.

	The output copied to chFormatted is "hh:mm:ss.mis", where hh are the hours,
	mm the minutes, ss the seconds, and mis the remaining milliseconds. The
	caller is responsible for providing a buffer of at least 13 octets (bytes),
	which is defined by FORMATTEDMILLISECONDS_SIZE.

	The function returns true if the value of uiTimeInMilliseconds was written
	to the buffer chFormatted points to. The function returns false if the value
	does not fit in a maximum of 99 hours, 59 minutes, 59 seconds, and 999
	milliseconds. When the function returns false nothing is written to
	chFormatted.
*/
#define FORMATTEDMILLISECONDS_SIZE		(13)
#define FORMATTEDMILLISECONDS_LEN		(FORMATTEDMILLISECONDS_SIZE - 1)
bool FormattedMilliseconds (char *chFormatted, const uint64_t uiTimeInMilliseconds);

#ifdef DEBUG
	#ifndef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
	#define UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
	#endif
#endif

#ifndef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
//#define UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
#endif

/*
	TestFormattedMilliseconds

	Test function.
*/
#ifdef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
		void Test_ubf_times_functions (void);
#else
		#define Test_ubf_times_functions()
#endif


#ifdef __cplusplus
	}
#endif

#endif															// Of U_UBF_DATETIME_H_INCLUDED.
/****************************************************************************************

	File:		timespecfncts.h
	Why:		Functions and macros that deal with struct timespec.
	OS:			POSIX/C99.
	Author:		Thomas
	Created:	2019-12-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-12-10	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef TIMESPECFNCTS_H
#define TIMESPECFNCTS_H

#include <stdbool.h>
#include <time.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		//#include "./ubf_date_and_time.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		//#include "./../datetime/ubf_date_and_time.h"
	#endif

	#ifdef PLATFORM_IS_WINDOWS
		#include <Windows.h>
	#endif

	#ifdef PLATFORM_IS_POSIX
		#include <time.h>
		#include <unistd.h>
	#endif
#endif

/*
	The differences between the timeval and timespec structures:
	
	struct timeval {
		long    tv_sec;
		long    tv_usec;										// Microseconds.
	};
	
	struct timespec {
		long    tv_sec;
		long    tv_nsec;										// Nanoseconds.
	};
	
	All functions here expect that the values of the struct timespec have
	been retrieved with clock_gettime () with a clk_id parameter of either
	CLOCK_MONOTONIC,
	CLOCK_MONOTONIC_COARSE, or
	CLOCK_BOOTTIME.
	
	See http://man7.org/linux/man-pages/man2/clock_gettime.2.html for more
	information on the clock_gettime () system call.
	
	All functions here only deal with timespans, not with absolute time
	values.
*/

// Test function.
#ifndef TIMESPECFNCTS_BUILD_TEST
#define TIMESPECFNCTS_BUILD_TEST
#endif

BEGIN_C_DECLS

/*
	TIMESPEC_INIT_ZERO
	
	Initialiser for a struct timeval.
*/
#define TIMESPEC_INIT_ZERO	{0,0}

/*
	timespec_from_ULONGLONG
	
	Converts the value ullValue from a FILETIME ULONGLONG to the struct
	timespec ts points to. Only relative timespans are computed correctly.
*/
void timespec_from_ULONGLONG (struct timespec *ts, ULONGLONG ullDiff);

/*
	ULONGLONG_from_timespec
	
	Retrieves the value of ts as a FILETIME ULONGLONG. The returned
	value is adjusted correctly for the Windows FILETIME epoch.
	
	If the epoch adjustment is not required, the function
	ULONGLONG_from_timespec_rel () can be called instead.
*/
ULONGLONG ULONGLONG_from_timespec (struct timespec *ts);

/*
	ULONGLONG_from_timespec_rel
	
	Retrieves the value of ts as a FILETIME ULONGLONG. Only relative
	timespans are computed correctly.
	
	To get an absolute value, add 116444736000000000 to the return value,
	which is the difference between the FILETIME and the Unix epoch, or
	use the function ULONGLONG_from_timespec () instead.
*/
ULONGLONG ULONGLONG_from_timespec_rel (struct timespec *ts);

/*
	timespec_substract_ULONGLONG
	
	Substracts the value (ULONGLONG FILETIME) ullValue from the struct
	timespec ts points to.
*/
bool timespec_substract_ULONGLONG (struct timespec *ts, ULONGLONG ullDiff);

/*
	timespec_testfunction

	The function to test the other functions.
*/
#ifdef TIMESPECFNCTS_BUILD_TEST
	bool timespec_testfunction (void);
#else
	#define timespec_testfunction()
#endif

END_C_DECLS

#endif															// End of #ifndef TIMESPECFNCTS_H.
/****************************************************************************************

	File		ISO__DATE__.h
	Why:		Predefined macros __DATE__ and __TIME__ in ISO 8601 format.
	OS:			C99
	Created:	2024-10-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-29	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef ISO__DATE__H
#define ISO__DATE__H

#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifndef LEN_ISO8601DATE
#define LEN_ISO8601DATE						(10)				// "YYYY-MM-DD"
#endif
#ifndef SIZ_ISO8601DATE
#define SIZ_ISO8601DATE						(LEN_ISO8601DATE + 1)
#endif

#ifndef LEN_ISO8601DATETIMESTAMP_NO_OFFS
#define LEN_ISO8601DATETIMESTAMP_NO_OFFS	(19)				// "YYYY-MM-DD hh:mm:ss"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMP_NO_OFFS	(LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1)
#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef _ISO_DATE_
#define _ISO_DATE_						"_ISO_DATE_"
#endif

EXTERN_C_BEGIN

/*
	szBuild_ISO__DATE__

	Returns the build date in ISO 8601 format, like "2024-10-30".

	The function is only re-entrant after it returned from its first invocation.
*/
const char *szBuild_ISO__DATE__ (void)
;

/*
	szBuild_ISO__TIME__

	Returns the build time, like "16:20:14". This function/macro only exists for
	completeness, because the predefinded macro __TIME__ serves the very same
	purpose, which is in fact precisely what the function/macro returns.
*/
#ifdef DEBUG
	const char *szBuild_ISO__TIME__ (void);
#else
	#define szBuild_ISO__TIME__()	__TIME__
#endif

/*
	szBuild_ISO__DATE__TIME__

	Returns the build date and time in ISO 8601 format, like "2024-10-30 23:59:01".
	Note that ISO 8601 requires a 'T' between date and time, while this function
	puts a blank (space, ' ') in its place instead.

	The function is only re-entrant after it returned from its first invocation, or
	after the function szBuild_ISO__DATE__ () has been called.
*/
const char *szBuild_ISO__DATE__TIME__ (void)
;

/*
	replace_ISO_DATE_

	Replaces all occurrences of "_ISO_DATE_" in sz with the build date in ISO 8601
	format, like "2024-10-30". Note that the two strings have the same length, hence
	the replacement(s) won't change the length of sz.
	
	The parameter len can be (size_t) -1, in which case the function calls strlen ()
	to obtain it. For convenience, the macro USE_STRLEN is defined as ((size_t) -1).

	The function returns the amount of replacements carried out.

	The function is only re-entrant after it returned from its first invocation, or
	after the function szBuild_ISO__DATE__ () has been called.
*/
size_t replace_ISO_DATE_ (char *sz, size_t len)
;

EXTERN_C_END

#endif														// Of #ifndef ISO__DATE__H.
/****************************************************************************************

	File:		ubfdebug.h
	Why:		Contains debugging functions.
	OS:			Windows/POSIX
	Author:		Thomas
	Created:	2017-10-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2017-10-24	Thomas			Created.
2018-05-26	Thomas			Compiler warning Linux/Android fixed by changing
							 the loop variable from int to unsigned int.
2019-08-24	Thomas			Module OS/ubf_debug.c/h should be obsolete now.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_UBF_DEBUG_DEB_H_INCLUDED
#define U_UBF_DEBUG_DEB_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	#include <assert.h>
#endif

/*
	Below are the macros that turn on the functions listed in the comments on the right-
	hand side of the macro definitions.
*/
#ifndef UBF_DEBUG_HEX_DUMP
//#define UBF_DEBUG_HEX_DUMP									// When defined, enables
																//	ubf_debug_hex_dump ().
#endif
#ifdef UBF_DEBUG_NO_HEX_DUMP
	#undef UBF_DEBUG_HEX_DUMP
#endif

// When defined, enables ubf_debug_printf () and ubf_debug_puts ().
#ifdef DEBUG
	#ifndef UBF_DEBUG_USE_PRINTF
	#define UBF_DEBUG_USE_PRINTF
	#endif
#endif

// When defined, uses our output abort functions. If not, a simple
//	ABORT() macro is used. It is not recommended to uncomment this
//	definition. Rather define UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
//	in the development environment or project file.
#ifdef DEBUG
	#ifndef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#define UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#endif
#endif
#ifdef DEBUG
	#ifdef UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
		#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#undef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#endif
	#endif
#endif

#ifndef UBF_DEBUG_MSG_STRLEN
#define UBF_DEBUG_MSG_STRLEN		(4096)
#endif

// The character used to identify buffer overruns and uninitialised areas. Can (and
//	should) be used as a general filler for debug purposes.
#ifndef UBF_ERROR_CHAR
#define UBF_ERROR_CHAR	'\x55'
#endif
#ifndef UBF_ERROR_CINT
#define UBF_ERROR_CINT	0x55
#endif

EXTERN_C_BEGIN

/*
	Macros to check if all members of a structure or union have been initialised.
	Check to see if we forgot to initialise a member. This is important when more
	members are added later.
	
	UBF_DEBUG_CHECK_STRUCT_DECLARATION()
	
	Sets the character used to initialise the structure before the real initialisation
	takes place.
	
	UBF_DEBUG_CHECK_STRUCT_ASSERTION()
	
	Checks if there are any octets within the structure's memory block that haven't been
	initialised by testing that no byte contains the character set with the macro
	UBF_DEBUG_CHECK_STRUCT_DECLARATION().
	
	
	Example:
	
	typedef struct structname
	{
		int		i1;
		int		i2;
		int		i3;
		int		i4;
		int		in;
	} STRUCTNAME;
	
	void test (void)
	{
		STRUCTNAME		sn;
		
		UBF_DEBUG_CHECK_STRUCT_DECLARATION (&sn, STRUCTNAME, 0x0D);
		sn.i1 = 1;
		sn.i2 = 2;
		//...
		sn.in = -1;
		UBF_DEBUG_CHECK_STRUCT_ASSERTION (&sn, STRUCTNAME);
	}
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(pstructure, typestruct, c)				\
		unsigned int	uStructCheck;													\
		unsigned char	*chStructCheck;													\
		unsigned char	cStructCheck		= (c);										\
		memset ((pstructure), (c), sizeof (typestruct))
#else
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(c)
#endif
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)						\
		chStructCheck = (char *) (pstructure);											\
		for (uStructCheck = 0; uStructCheck < sizeof (typestruct); uStructCheck ++)		\
		{																				\
			if (*chStructCheck == cStructCheck)											\
				_ASSERT (false);														\
			++ chStructCheck;															\
		}
#else
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)
#endif

/*
	UBF_DEBUG_CHECK_CALLED_ONLY_ONCE
	
	Macro to check that the function using it is only invoked once. Useful for
	initialisation functions.
	
	UBF_DEBUG_CHECK_RESET_ONLY_ONCE
	
	Resets the flag. Useful to check that a function that is not re-entrant is
	not called again before the previous instance has returned.
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)	\
		static bool	flagname;							\
		ubf_assert (!flagname);							\
		flagname = TRUE
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)	\
		flagname = FALSE
#else
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)
#endif

/*
	UBF_DEFINE_GUARD_VAR										// Define guard variable.
	UBF_CHECK_GUARD_VAR											// Check/test guard variable.
	UBF_DEF_GUARD_VAR											// Define guard variable.
	UBF_TST_GUARD_VAR											// Check/test guard variable.
	UBF_CHK_GUARD_VAR											// Check/test guard variable.
	
	Macros to define and to check guard variables. The variable defined is of
	type char []. These macros can help find buffer overruns.
	
	Examples:
	
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	The following example checks for an overrun of the array:
	
	int		i [105];
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	...
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	If data is written beyond the array's memory location testvar is overwritten,
	at least on some platforms.
	Test data is defined with UBF_DEFINE_GUARD_VAR().
	The macro UBF_CHECK_GUARD_VAR() determines if the test variable's content has
	been destroyed.
*/
#ifdef DEBUG
	#ifndef UBF_DEFINE_GUARD_VAR
	#define UBF_DEFINE_GUARD_VAR(var, value)			\
		char	var [] = #value
	#endif
	#ifndef UBF_CHECK_GUARD_VAR
	#define UBF_CHECK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_DEF_GUARD_VAR
	#define UBF_DEF_GUARD_VAR(var, value)				\
		char	var [] = #value
	#endif
	#ifndef UBF_TST_GUARD_VAR
	#define UBF_TST_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_CHK_GUARD_VAR
	#define UBF_CHK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
#else
	#define UBF_DEFINE_GUARD_VAR(var, value)
	#define UBF_CHECK_GUARD_VAR(var, value)
	#define UBF_DEF_GUARD_VAR(var, value)
	#define UBF_TST_GUARD_VAR(var, value)
	#define UBF_CHK_GUARD_VAR(var, value)
#endif

/*
	ubf_debug_assert

	Outputs the message only if the assertion doesn't pass.
	
	ubf_debug_assert_pass

	Outputs the message chDebugMessage and then implements an _ASSERT () with bAssert.

	Use the macro UBF_DEBUG_ASSERT() or ubf_assert_msg() to fill in __FILE__ and __LINE__
	for the parameters chFilePath and uiLineNum. Both macros are identical. See
	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html for an explanation
	of the __FILE__ and __LINE__ macros. The macro ubf_assert () is probably what should
	be used as often as possible.

	In release versions these are macros that expand to nothing.
	
	It is recommended to use the ubf_assert() macro, which expects one parameter only. It
	stringifies this parameter for the output text. Since this is sometimes not possible
	due to the limitations of the preprocessor's stringify operator, or it's not
	desirable if condition and message text should differ, the macro ubf_assert_msg() can
	be used.

	Examples:

	// All these lines have the same or similar functionality:
	ubf_debug_assert (a > b, "a > b", __FILE__, __LINE__);
	UBF_DEBUG_ASSERT (a > b, "a > b", __FILE__, __LINE__);
	ubf_assert (a > b);
	ubf_assert_msg (a > b, "a > b");
	
	Explanation and further notes:
	
	Although assert () on Windows and Linux works great, it does exactly what the
	documentation says on Android: it aborts. No message, no information on where
	it stopped, nor why.
	
	ubf_assert (a > b) is a replacement for assert (). It displays a message with
	the assertion before it aborts.
	
	ubf_assert_msg (a > b, "Arbitrary message") is a replacement for assert () that
	outputs "Arbitrary message" when the assertion fails instead of the actual
	assertion.
*/
#ifdef DEBUG
	// Debug version.
	#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		void ubf_debug_assert		(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert(b, c, p, n)			\
			ASSERT (b)
	#endif
	#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		void ubf_debug_assert_pass	(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert_pass(b, c, p, n)		\
			ASSERT (b)
	#endif
	#ifndef UBF_DEBUG_ASSERT
	#define UBF_DEBUG_ASSERT(b)							\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert
	#define ubf_assert(b)								\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_msg
	#define ubf_assert_msg(b,m)							\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_message
	#define ubf_assert_message(b,m)						\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_pass
	#define ubf_assert_pass(b)							\
				ubf_debug_assert_pass (b, #b, __FILE__, __LINE__)
	#endif
	/*
		ubf_assert_Android
		
		Prints the message on Android but is a simple _ASSERT() on other platforms. That's
		because the application simply dies with an _ASSERT() on Android.
	*/
	#ifdef OS_IS_ANDROID
		#define ubf_assert_Android(b)					\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
		#define ubf_assert_Android_msg(b,m)				\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Android(b)					\
				_ASSERT (b)
		#define ubf_assert_Android_msg(b,m)				\
				_ASSERT (b)
	#endif
	/*
		ubf_assert_Linux
		
		Prints the message on Linux but is a simple _ASSERT() on other platforms.
	*/
	#ifdef OS_IS_LINUX
		#define ubf_assert_Linux(b)						\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
		#define ubf_assert_Linux_msg(b,m)				\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Linux(b)						\
				_ASSERT (b)
		#define ubf_assert_Linux_msg(b,m)				\
				_ASSERT (b)
	#endif
#else
	// Release version.
	#define ubf_debug_assert(b,m,f,l)
	#define ubf_debug_assert_pass(b,m,f,l)
	#define UBF_DEBUG_ASSERT(b)
	#define ubf_assert(b)
	#define ubf_assert_msg(b,m)
	#define ubf_assert_message(b,m)
	#define ubf_assert_pass(b)
	#ifdef UBF_ANDROID
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#else
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#endif
	#ifdef UBF_LINUX
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#else
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#endif
#endif

/*
	ubf_debug_fill_mem

	Fills the memory mem points to with UBF_ERROR_CHAR, which is 55h, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem (void *mem, size_t len);
#else
	#define ubf_debug_fill_mem(m,l)
#endif

/*
	ubf_debug_check_mem
	
	Assert that a memory block consists of UBF_ERROR_CHAR octets.
*/
#ifdef DEBUG
	void ubf_debug_check_mem (char *mem, size_t len);
#else
	#define ubf_debug_check_mem(m, l)
#endif

/*
	ubf_debug_fill_mem_with

	Fills the memory mem points to with the value of c, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem_with (void *mem, char c, size_t len);
#else
	#define ubf_debug_fill_mem_with(m, c, l)
#endif

/*
	ubf_debug_check_mem_with

	Assert that a memory block consists of len octets filled with c.
*/
#ifdef DEBUG
	void ubf_debug_check_mem_with (char *mem, char c, size_t len);
#else
	#define ubf_debug_check_mem_with(m, c, l)
#endif

/*
	ubf_debug_hex_dump
	
	Calls ubf_data_dump_puts () in ubfdump.c if UBF_DEBUG_HEX_DUMP is defined.
	If UBF_DEBUG_HEX_DUMP is not defined, the function is expanded to a no-operation.
*/
#ifdef UBF_DEBUG_HEX_DUMP
	void ubf_debug_hex_dump (const char *chOutput, size_t stOutput);
#else
	#define ubf_debug_hex_dump(ch,st)
#endif

/*
	ubf_debug_printf
	ubf_debug_puts
	
	Debug versions of printf () and puts (). To make these calls no-operations (empty)
	macros, undefine UBF_DEBUG_USE_PRINTF. In release versions they are empty definitions.
*/
#ifdef UBF_DEVICE_GUI
	#ifdef DEBUG
		void ubf_debug_printf (const char *format, ...);
		void ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
	#ifdef UBF_DEBUG_USE_PRINTF
		#undef UBF_DEBUG_USE_PRINTF
	#endif
#else
	#ifdef UBF_DEBUG_USE_PRINTF
		int ubf_debug_printf (const char *format, ...);
		int ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
#endif

// Debug sleep. Sleeps in debug versions (milliseconds) but not in release builds.
#ifdef DEBUG
	#define ubf_debug_sleep_ms(s)			ubf_sleep_ms (s)
#else
	#define ubf_debug_sleep_ms(s)
#endif

// Macros to abort in debug versions.
#ifdef DEBUG
	#define DEBUGABORT()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORTDEBUG()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORT()			ASSERT (false)
#else
	#define DEBUGABORT()
	#define DBGABORT()
	#define ABORTDEBUG()
	#define DBGABORT()
	#define ABORT()
#endif

/*
	ubf_expect_bool_AND

	Macro to binary AND an expectation. Useful in test functons.

	bool	bOk		= TRUE;
	int		a		= 0;
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 3 == a);
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 6 == a);
	ubf_assert_true (bOk);
*/
#define ubf_expect_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))

/*
	ubf_assert_TRUE
	ubf_assert_FALSE
	ubf_expect_TRUE
	ubf_expect_FALSE
	ubf_assert_true
	ubf_expect_true
	ubf_assert_false
	ubf_expect_false

	Macros that assert that the provided boolean is either TRUE or FALSE.
*/
#define ubf_assert_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_expect_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_assert_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_expect_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_assert_true(b)								\
			ubf_assert (true == (b))
#define ubf_expect_true(b)								\
			ubf_assert (true == (b))
#define ubf_assert_false(b)								\
			ubf_assert (false == (b))
#define ubf_expect_false(b)								\
			ubf_assert (false == (b))


/*
	ubf_assert_NULL
	ubf_expect_NULL
	ubf_assert_not_NULL
	ubf_expect_not_NULL
	ubf_assert_non_NULL
	ubf_expect_non_NULL

	Macros that assert that the provided pointer is either NULL or non-NULL.
*/
#define ubf_assert_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_expect_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_assert_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_assert_non_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_non_NULL(p)							\
			ubf_assert (NULL != (p))

/*
	ubf_assert_0
	ubf_expect_0
	ubf_assert_non_0
	ubf_expect_non_0
	ubf_assert_zero
	ubf_expect_zero
	ubf_assert_non_zero
	ubf_expect_non_zero

	Macros that assert that the parameter expression evaluates to zero or
	non-zero.
*/
#define ubf_assert_0(v)									\
			ubf_assert (0 == (v))
#define ubf_expect_0(v)									\
			ubf_assert (0 == (v))
#define ubf_assert_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_expect_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_assert_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_expect_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_assert_non_zero(v)							\
			ubf_assert (0 != (v))
#define ubf_expect_non_zero(v)							\
			ubf_assert (0 != (v))


EXTERN_C_END

#endif															// Of U_UBF_DEBUG_DEB_H_INCLUDED.
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
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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
/****************************************************************************************

	File:		strfilesys.h
	Why:		File system string functions.
	OS:			C99.
	Author:		Thomas
	Created:	2023-05-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-27	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRFILESYS_H
#define STRFILESYS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	is_directory_separator

	Macro to check if c is a directory separator.
*/
#ifndef is_directory_separator
#define is_directory_separator(c)						\
			(UBF_WIN_DIR_SEP == c || UBF_PSX_DIR_SEP == c)
#endif

/*
	str_find_path_navigator
	
	Returns a pointer to the first path navigator found in szString, or NULL if
	szString does not contain any path navigators. A path navigator is "../" on
	POSIX platforms and "..\" on Windows. The function treats both as equally
	valid on either platform and returns a pointer to the first one found.

	Note that this function does NOT support USE_STRLEN, which is (size_t) -1
	for the parameter lnString. The length MUST be specified appropriately.
*/
char *str_find_path_navigator (char *szString, size_t lnString)
;

/*
	str_remove_path_navigators
	remove_path_navigators_str
	
	Removes relative path navigators from chPath. The macro remove_path_navigators_str()
	is a redefinition of the function str_remove_path_navigators (). Relative path
	navigators consist of two periods followed by a slash, which is a forward slash on
	Unix/Linux platforms and a backward slash on Windows. The function recognises both
	types of path navigators.

	Relative path navigator
	"../"					Unix/Linux/Android/iOS/...
	"..\", escaped "..\\"	Windows

	Parameters

	chPath			A pointer to a string that contains the path with
					relative path navigators. This parameter cannot be NULL.

	pLen			A pointer to a size_t that contains the length of the string in
					chPath, not counting a NUL terminator. If this parameter is NULL,
					the function calls strlen (chPath) to obtain the length of the string
					chPath points to. If this parameter points to a size_t variable with a
					value of USE_STRLEN, which is (size_t) -1, the function calls
					strlen (chPath) too. If this parameter points to a size_t variable that
					contains a length other than USE_STRLEN, the parameter chPath does not
					need to be NUL-terminated.
					On return, the function updates the value with the new length of the path
					after relative path navigators have been removed, provided that pLen is
					not NULL.
					
	Examples - chPath as input on the left, chPath changed as output on the right:
	"../../test1/test2/test3/../../file.ext"	->	"../../test1/file.ext"
	"../../../1/2/3/4/5/6/7/../f.ext"			->	"../../../1/2/3/4/5/6/f.ext"
	"C:this is a test/test1/test2/../file.ext"	->	"C:this is a test/test1/file.ext"
	"/1/2/3/4/../../../../f.e"					->	"/f.e"
	"1/../f"									->	"f"
	"../f"										->	"../f"
	"1/2/../../f"								->	"f"
	"1/2/../../../f"							->	"../f"

	The function returns the amount of relative path navigators that were removed by the
	function. If pLen is not NULL, the function returns the new length in this size_t value
	after all relative path navigators have been removed.

	If path navigators have been removed, the function adds a NUL terminator to chPath since
	the string always shrinks in this case and at least several byte of additional space are
	made available. If no replacement occurs, the function does not change the buffer chPath
	points to.
*/
size_t str_remove_path_navigators (char *chPath, size_t *pLen);
#define remove_path_navigators_str(chPath,pLen)	str_remove_path_navigators (chPath, pLen)

/*
	ubf_correct_directory_separators_str
	
	The function replaces all directory separators with the correct directory separator
	of the host system before it removes all duplicate separators apart from the first
	two forward/backward slashes in a UNC path ("//server/share" or "\\server\share").
	
	chPath			Pointer to the path in which directory separators should be
					corrected.
	plenPath		Pointer to a value that specifies the length of the path chPath
					points to, excluding a terminating NUL character. If this parameter
					is NULL or points to a value of (size_t) -1, which is
					SUBF_STRING_USE_STRLEN or SUBF_STRING_UNKNOWN_LENGTH, the function
					uses strlen (chPath) to obtain its length.
	pReps			Pointer to a size_t that receives the amount of
					replacements the function has performed. This parameter can be NULL
					if this information is not needed.
	
	The function returns true on success, false when it fails. The amount of adjustments
	made is returned at the address pReps points to, i.e the amount of path
	separators replaced or removed, provided pReps is not NULL. If stPath is not NULL,
	the function returns the new length, excluding a terminating NUL, at the address it
	points to. The function returns false when chPath is NULL, in which case debug
	versions abort. The function also returns false when *pstPath is 0. Debug versions
	abort in this case too.
*/
bool ubf_correct_directory_separators_str (char *chPath, size_t *plenPath, size_t *pReps);

/*
	ubf_change_directory_separators
	
	Changes all directory separators ('/' and '\\') to newSeparator. Note that newSeparator
	can be any character that fits in a char.
*/
void ubf_change_directory_separators (char *szPath, size_t len, char newSeparator);

/*
	ubf_len_with_last_directory_separator
	
	Returns the length of szPath that includes the last directory separator,
	or 0 if sz does not contain any directory separators.
	
	"/home/file"	-> 6, which would be the same as strlen ("/home/");
	"/"				-> 1, which would be the same as strlen ("/");
	"home"			-> 0, which would be the same as strlen ("");
	"C:\\dir"		-> 3, which would be the same as strlen ("C:\\");
	
	In Windows, although "C:file.ext" is actually the current path of the current
	process on the C: drive, the function accepts this as an absolute path for a file,
	but only if the first character of szPath is a letter and the second character is
	a colon, and no other directory separator can be found:
	"C:file.ext"	-> 2, which would be the same as strlen ("C:");
	
	If szPath is NULL, the function returns 0.
*/
size_t ubf_len_with_last_directory_separator (const char *szPath, size_t len);

/*
	str_correct_dir_separators
	
	Corrects the directory separators in str.
	
	The function returns the amount of directory separators replaced.
*/
size_t str_correct_dir_separators (char *str, size_t len)
;

/*
	ubf_test_ubf_strfilesys
	
	Tests this module.
*/
#ifdef BUILD_DEBUG_UBF_STRFILESYS_TESTS
	bool ubf_test_ubf_strfilesys (void);
#else
	#define ubf_test_ubf_strfilesys()
#endif

EXTERN_C_END

#endif // STRFILESYS_H
/****************************************************************************************

	File:		strhex.h
	Why:		Functions for hexadecimal digits.
	OS:			C99
	Author:		Thomas
	Created:	2020-03-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-03-07	Thomas			Created. Functions have been moved from ubfsecure.c/h into
							 this module and renamed (without the "secure" part in them).

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_STR_HEX_H
#define U_STR_HEX_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

// Minimum string length and size to hold an 8 bit hexadecimal number in ASCII.
#ifndef UBF_HEX8_STRLEN
#define UBF_HEX8_STRLEN				(2)
#endif
#ifndef UBF_HEX8_STRSIZ
#define UBF_HEX8_STRSIZ				(UBF_HEX8_STRLEN + 1)
#endif
// Minimum string length and size to hold a 16 bit hexadecimal number in ASCII.
#ifndef UBF_HEX16_STRLEN
#define UBF_HEX16_STRLEN			(4)
#endif
#ifndef UBF_HEX16_STRSIZ
#define UBF_HEX16_STRSIZ			(UBF_HEX16_STRLEN + 1)
#endif
// Minimum string length and size to hold a 32 bit hexadecimal number in ASCII.
#ifndef UBF_HEX32_STRLEN
#define UBF_HEX32_STRLEN			(8)
#endif
#ifndef UBF_HEX32_STRSIZ
#define UBF_HEX32_STRSIZ			(UBF_HEX32_STRLEN + 1)
#endif
// Minimum string length and size to hold a 64 bit hexadecimal number in ASCII.
#ifndef UBF_HEX64_STRLEN
#define UBF_HEX64_STRLEN			(16)
#endif
#ifndef UBF_HEX64_STRSIZ
#define UBF_HEX64_STRSIZ			(UBF_HEX64_STRLEN + 1)
#endif

// We can as well have SIZE_T_MAX because it seems more natural/reasonable.
#ifndef SIZE_T_MAX
#define SIZE_T_MAX	SIZE_MAX
#endif

// Error codes.
#define UBF_INVALID_HEX_CHAR		((unsigned char) -1)
#define UBF_INVALID_OCT_CHAR		((unsigned char) -1)
#define UBF_INVALID_BIN_CHAR		((unsigned char) -1)

// The maximum amount of hexadecimal ASCII digits for
#define UINT16_ASCII_HEX_DIGITS			 (4)
#define UINT32_ASCII_HEX_DIGITS			 (8)
#define UINT64_ASCII_HEX_DIGITS			(16)

/*
	ubf_is_octal_digit

	Returns or evaluates to TRUE if c contains an ASCII digit between 0 and 7, FALSE
	otherwise.
*/
#ifdef DEBUG
	bool ubf_is_octal_digit (char c);
#else
    #define ubf_is_octal_digit(c)						\
		((unsigned char) (c) >= '0' && (unsigned char) (c) <= '7')
#endif

/*
	ubf_is_hex_digit

	Returns or evaluates to true if c contains an ASCII hexadecimal digit, false
	otherwise. Hexadecimal digits are the decimal digits 0 to 9, plus the the letters
	A to F.
*/
#ifdef DEBUG
	bool ubf_is_hex_digit (char c);
#else
	#define ubf_is_hex_digit(c)							\
	(													\
			((unsigned char) (c) >= '0' && (unsigned char) (c) <= '9')\
		||	((unsigned char) (c) >= 'A' && (unsigned char) (c) <= 'F')\
		||	((unsigned char) (c) >= 'a' && (unsigned char) (c) <= 'f')\
	)
#endif

/*
	ubf_value_of_ASCII_hex
	
	Returns the value of the hexadecimal character in c. The function returns
	UBF_INVALID_HEX_CHAR, which is defined as (unsigned char) -1 if c does not
	contain a valid hexadecimal character.
	
	Valid hexadecimal characters are the digits "0" to "9", and the letters
	"A" to "F" or "a" to "f".
	"0" returns 0.
	"1" returns 1.
	...
	"9" returns 9.
	"A" returns 10.
	...
	"F" returns 15.
	"a" returns 10.
	...
	"f" returns 15.
	Anything else returns UBF_INVALID_HEX_CHAR, which is defined as (unsigned char) -1.
*/
#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_hex (const char c);
#else
	#define ubf_value_of_ASCII_hex(c)					\
		(												\
			(unsigned char) (c) >= '0' && (unsigned char) (c) <= '9' ? (unsigned char) (c) - '0' :\
			(unsigned char) (c) >= 'a' && (unsigned char) (c) <= 'f' ? (unsigned char) (c) - 'a' + 10 :\
			(unsigned char) (c) >= 'A' && (unsigned char) (c) <= 'F' ? (unsigned char) (c) - 'A' + 10 :\
			UBF_INVALID_HEX_CHAR						\
		)
#endif

/*
	ubf_value_of_ASCII_oct
	
	Returns the value of the octal character in c. The function returns
	UBF_INVALID_OCT_CHAR, which is defined as (unsigned char) -1 if c does
	not contain a valid octal character ('0', '1', '2', '3', '4', '5', '6',
	or '7').
*/
#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_oct (const char c);
#else
	#define ubf_value_of_ASCII_oct(c)					\
		(												\
				(unsigned char) (c) >= '0'				\
			&&	(unsigned char) (c) <= '7'				\
			?	(unsigned char) (c) - '0'				\
			:	UBF_INVALID_OCT_CHAR					\
		)
#endif

/*
	ubf_octet_from_hex
	
	Reads up to two hexadecimal characters from chHx and writes the resulting
	binary octet to the location o points to.
	
	The function expects that it can read up to two characters from chHx.
	It does not perform a NUL check.
		
	The function returns the amount of hexadecimal characters that were
	read and used from the location chHx points to to produce the octet
	stored at o, which can be either 0 (if the first character is not a hex
	character), 1 (if only the first character is a hexadecimal character),
	or 2 (if both characters are hexadecimal).
*/
size_t ubf_octet_from_hex (unsigned char *o, const char *chHx);

/*
	ubf_octet_from_oct
	
	Reads up to three octal characters from chOc and writes the resulting
	binary octet (byte) to the location o points to.
	
	Valid octal bytes start at 000 (0d) up to 377 (255d, FFh). The function
	does not consume anything above octet boundary. For instance, an input
	of "477" would consume the first two characters ("47") only because the
	octal number 477 requires more than a single octet to be stored.
	
	The function returns the amount of octal characters consumed to produce
	the value that is written to the location o points to.
*/
size_t ubf_octet_from_oct (unsigned char *o, const char *chOc);

/*
	ubf_octet_from_bin
	
	Reads up to 8 binary characters from chOb and writes the resulting
	binary octet (byte) to the location o points to.
	
	Valid binary characters are '0' and '1'. The function does not consume
	anything above byte boundary.
	
	The function returns the amount of binary digits consumed to produce
	the value that is written to the location o points to.
*/
size_t ubf_octet_from_bin (unsigned char *o, const char *chOb);

/*
	ubf_uint16_from_hex

	Returns a 16 bit unsigned integer read from its hexadecimal ASCII
	representation chHx16 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx16
	and used to create the 16 bit unsigned value stored at the location pui16
	points to. If chHx16 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui16 points
	to.
	
	The pointer to the target value pui16 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.
	
	The function consumes a maximum of 4 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint16_from_hex (uint16_t *pui16, const char *chHx16)
;

/*
	ubf_uint32_from_hex
	
	Returns a 32 bit unsigned integer read from its hexadecimal ASCII
	representation chHx32 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx32
	and used to create the 32 bit unsigned value stored at the location pui32
	points to. If chHx32 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui32 points
	to.
	
	The pointer to the target value pui32 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.

	The function consumes a maximum of 8 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint32_from_hex (uint32_t *pui32, const char *chHx32)
;

/*
	ubf_uint64_from_hex
	
	Returns a 64 bit unsigned integer read from its hexadecimal ASCII
	representation chHx64 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx64
	and used to create the 64 bit unsigned value stored at the location pui64
	points to. If chHx64 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui64 points
	to.
	
	The pointer to the target value pui64 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.

	The function consumes a maximum of 16 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint64_from_hex (uint64_t *pui64, const char *chHx64)
;

/*
	uint64_from_hex_str

	Returns the value of the hexadecimal string hexstr points to as a uint64_t. The
	function does not check for an overrun. Processing stops at the first character in
	hexstr that is not a hexadecimal character. Both, upper and lower-case characters
	are accepted.

	Examples:						Return value
	"12345"							-> 12345
	"A"								-> 10
	"228"							-> 552
	"ax"							-> 10
	"g"								-> 0
	""								-> 0
*/
uint64_t uint64_from_hex_str (const char *hexstr);

/*
	uint64_from_dec_or_hex_str

	Returns the value of the decimal or hexadecimal string decorhex points to as a
	uint64_t. Processing stops at the first character in decorhex that is not a digit
	or a hexadecimal character. A hexadeximal number is expected to start with "0x"
	or "0X", otherwise the number is assumed to be a decimal number and treated
	accordingly, for instance "0A" would return 0.

	Examples:						Return value
	"0A"							-> 0
	"0xA"							-> 10
	"55"							-> 55
*/
uint64_t uint64_from_dec_or_hex_str (const char *decorhex);

/*
	ubf_hex2bin
	
	This is our own version of Libsodium's sodium_hex2bin () function.
	
	The function expects a hexadecimal ASCII string in hex_input with hex_len octets/
	characters and writes the binary version of it to bin_output. The parameter
	bin_maxlen specifies the size of the buffer bin_output points to.
	
	Note that each octet written to bin_output requires two hexadecimal ASCII digits
	read from hex_input. This means that
	a) hex_len must be an even number, and
	b) bin_maxlen must be at least hex_len/2 if the input is supposed to be fully
	converted.
	
	The function stops converting when it encounters a character in hex_input that
	is not a valid hexadecimal ASCII digit ("0" to "9", "A" to "F", or "a" to "f").

	The function returns the amount of octets written to bin_output at the address
	pbin_len points to, provided it is not NULL.
	
	Note that if the binary output is interpreted as a multi-octet number this
	number will be in big-endian notation, since this function converts octet by
	octet in the order of the hexadecimal input.

	Returns TRUE on success, FALSE if it fails. The function returns FALSE if
	hex_len is not an even number, as this would not allow for a conversion. If
	pbin_len is not NULL, the function writes the amount of bytes written to
	bin_output to this address. It does this independent of the function's return
	value of TRUE or FALSE.
*/
bool ubf_hex2bin	(
			unsigned char		*bin_output,					// The output.
			const size_t		bin_maxlen,						// Length of the output buffer,
																//	in octets (bytes).
			const char			*hex_input,						// The input in hexadecimal
																//	ASCII representation.
			const size_t		hex_len,						// Length of the input buffer,
																//	in octets (bytes).
			size_t *const		pbin_len						// The amount of bytes written.
                   )
;

/*
	asc_hex_from_octet
	asc_hex_from_octet_lower

	Writes the two characters representing the hexadecimal notation of the byte/octet
	(8 bit data word) ui to the location pc points to. The function writes exactly two
	ASCII characters to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_octet (char *pc, uint8_t ui)
;
void asc_hex_from_octet_lower (char *pc, uint8_t ui)
;

/*
	URI_encode_hex_from_octet

	Writes a percent character ("%") plus two characters representing the hexadecimal notation
	of the byte/octet (8 bit data word) ui to the location pc points to. The function writes
	exactly three ASCII characters to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void URI_encode_hex_from_octet (char *pc, uint8_t ui)
;
void URI_encode_hex_from_octet_lower (char *pc, uint8_t ui)
;

/*
	asc_hex_from_word

	Writes the four characters representing the hexadecimal notation of the 16 bit data word
	ui to the location pc points to. The function writes exactly four ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_word (char *pc, uint16_t ui)
;
void asc_hex_from_word_lower (char *pc, uint16_t ui)
;

/*
	asc_hex_from_dword

	Writes the 8 characters representing the hexadecimal notation of the 32 bit data
	ui to the location pc points to. The function writes exactly 8 ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_dword (char *pc, uint32_t ui)
;
void asc_hex_from_dword_lower (char *pc, uint32_t ui)
;

/*
	asc_hex_from_qword

	Writes the 16 characters representing the hexadecimal notation of the 64 bit data
	ui to the location pc points to. The function writes exactly 16 ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_qword (char *pc, uint64_t ui)
;
void asc_hex_from_qword_lower (char *pc, uint64_t ui)
;

/*
	asc_bin_from_octet

	Writes the 8 characters representing the binary notation of the byte/octet
	(8 bit data word) ui to the location pc points to. The function writes exactly 8
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_octet (char *pc, uint8_t ui)
;

/*
	asc_bin_from_word

	Writes the 16 characters representing the binary notation of the 16 bit data
	word ui to the location pc points to. The function writes exactly 16
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_word (char *pc, uint16_t ui)
;

/*
	asc_bin_from_dword

	Writes the 32 characters representing the binary notation of the 32 bit data
	word ui to the location pc points to. The function writes exactly 32
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_dword (char *pc, uint32_t ui)
;

/*
	ubf_hex_from_octet

	Returns the hexadecimal ASCII notation of ui in chResult. It is expected that the
	buffer chResult points to is at least 3 characters (including the terminating NUL
	character) long.
	Byte 0 is for the ASCII character of the MSB nibble (tetrade). Values are from '0'
	to 'F'.
	Byte 1 is for the ASCII character of the LSB nibble (tetrade). Values are from '0'
	to 'F'.
	Byte 2 is overwritten with a NUL byte to terminate the result.
*/
void ubf_hex_from_octet (char *chResult, uint8_t ui);

/*
	ubf_hex_from_word
	ubf_hex_from_uint16

	Returns the hexadecimal notation of the 16 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 5 characters long, which
	includes the terminating NUL character. The constant UBF_HEX16_STRSIZ can be used
	to determine this length, which is 4 + 1 octets.
*/
void ubf_hex_from_word (char *chResult, uint16_t ui);
#define ubf_hex_from_uint16(r,u)			\
			ubf_hex_from_word (r, u)

/*
	ubf_hex_from_dword
	ubf_hex_from_uint32

	Returns the hexadecimal notation of the 32 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 9 characters long, which
	includes the terminating NUL character. The constant UBF_HEX32_STRSIZ is defined as
	9 and can be utilised for this purpose.
*/
void ubf_hex_from_dword (char *chResult, uint32_t ui);
#define ubf_hex_from_uint32(r,u)			\
			ubf_hex_from_dword (r, u)

/*
	ubf_hex_from_qword
	ubf_hex_from_uint64

	Returns the hexadecimal notation of the 64 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 17 characters long, which
	includes the terminating NUL character. The constant UBF_HEX64_STRSIZ is defined as
	being this length, including the NUL character.
*/
void ubf_hex_from_qword (char *chResult, uint64_t ui);
#define ubf_hex_from_uint64(r,u)			\
			ubf_hex_from_qword (r, u)

/*
	asc_hex_zero_from_qword

	Returns the hexadecimal notation of the 64 bit unsigned integer ui in the buffer
	chResult points to. The parameter stWidthResult restricts or extends the width of the
	result, beginning from the right side, excluding a terminating NUL character.

	The function is identical to asc_hex_zero_from_qword () except that it does not write
	a terminating NUL character.
*/
void asc_hex_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui)
;

/*
	ubf_hex_str_zero_from_qword
	
	Returns the hexadecimal notation of the 64 bit unsigned integer ui in the buffer
	chResult points to. The parameter stWidthResult restricts or extends the width of the
	result, beginning from the right side, excluding a terminating NUL character. To use
	chResult as a standard C string it must hold space for at least stWidthResult
	characters plus an additional NUL character, hence the buffer chResult points to must
	always provide space for at least stWidthResult + 1 octets (bytes).
	
	Examples:
	
	ui		stWidthResult	chResult
	----------------------------------------
	65535	4				"FFFF"
	16		2				"10"
	16		1				"0"
	65535	5				"0FFFF"
	65535	10				"000000FFFF"
	65535	2				"FF"
	
	int main(void)
	{
		char		ch [1024];
		int			i;
		
		for (i = 0; i <= 30; i ++)
		{
			ubf_hex_str_zero_from_qword (ch, i, 5);
			printf ("i: %d, \"%s\", len = %zu\n", i, ch, strlen (ch));
		}
		return 0;
	}

	i: 0, "", len = 0
	i: 1, "5", len = 1
	i: 2, "05", len = 2
	i: 3, "005", len = 3
	i: 4, "0005", len = 4
	i: 5, "00005", len = 5
	i: 6, "000005", len = 6
	i: 7, "0000005", len = 7
	i: 8, "00000005", len = 8
	i: 9, "000000005", len = 9
	i: 10, "0000000005", len = 10
	i: 11, "00000000005", len = 11
	i: 12, "000000000005", len = 12
	i: 13, "0000000000005", len = 13
	i: 14, "00000000000005", len = 14
	i: 15, "000000000000005", len = 15
	i: 16, "0000000000000005", len = 16
	i: 17, "00000000000000005", len = 17
	i: 18, "000000000000000005", len = 18
	i: 19, "0000000000000000005", len = 19
	i: 20, "00000000000000000005", len = 20
	i: 21, "000000000000000000005", len = 21
	i: 22, "0000000000000000000005", len = 22
	i: 23, "00000000000000000000005", len = 23
	i: 24, "000000000000000000000005", len = 24
	i: 25, "0000000000000000000000005", len = 25
	i: 26, "00000000000000000000000005", len = 26
	i: 27, "000000000000000000000000005", len = 27
	i: 28, "0000000000000000000000000005", len = 28
	i: 29, "00000000000000000000000000005", len = 29
	i: 30, "000000000000000000000000000005", len = 30
	
*/
void ubf_hex_str_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui);

/*
	ubf_hex_str_blank_from_qword
	
	The function is identical to ubf_hex_str_zero_from_qword () with the exception
	that leading zeros are replaced by blanks (spaces, SPC, ASCII 32d, 20h).
*/
void ubf_hex_str_blank_from_qword (char *chResult, size_t stWidthResult, uint64_t ui);

/*
	UCS2UTF16bin_from_hex
	
	The function expects a hexadecimal ASCII input string that contains UCS-2 or UTF-16
	characters, represented as hexadecimal ASCII. It writes out the 16 bit characters
	to u16result, up to max_u16result characters.
	
	If u16result is NULL, the function does not write output but returns the amount of
	uint16_t that would have been written at the address pU16written points to, unless
	pU16written is also NULL. Note that the value of max_u16result is still taken into
	consideration in this case. So, in order to obtain the size of the required array
	of u16result, set max_u16result to a value greater than the expected size or to
	SIZE_T_MAX.
	
	size_t		required_size;
	UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, "00410042", 8, &required_size);
	// Amount of uint16_t required is now in required_size.
	required_size *= sizeof (uint16_t);							// In bytes/octets.
	
	The function fails if len_cchex is not dividable by 4, as each UCS-2 or UTF-16 16 bit
	data written to u16result requires four hexadecimal ASCII characters in the input
	string cchex. The function also fails when len_cchex is 0.
	
	cchex				u16result
	"0031"				31
	"00310032"			31, 32
	
	Note that the function does not terminate the buffer u16result points to with a NUL
	character unless the hexadecimal ASCII input string cchex ends with a character
	string of "0000", which is a NUL terminator in UCS-2/UTF-16.
	
	The function returns TRUE on success, FALSE otherwise. Independent of the function's
	return value the amount of uint16_t (16 bit) values written to u16result is returned
	at the address pU16written points to.
*/
bool UCS2UTF16bin_from_hex	(
			uint16_t			*u16result,						// The output as 16 bit UCS-2 or
																//	UTF-16.
			size_t				max_u16result,					// The size of the buffer
																//	u16result points to, in
																//	uint16_t (NOT octets).
			const char			*cchex,							// The input string consisting
																//	of hexadecimal ASCII characters,
																//	4 hexadecimal ASCII characters
																//	for each uint16_t (UCS-2 or
																//	UTF-16) written to u16result.
			size_t				len_cchex,						// The length of the input string,
																//	excluding NUL.
			size_t				*pU16written
							)
;

/*
	ubf_hex_simple_hash
	
	This is a very simple hash function. It is meant as a (pretty simplistic)
	stand-in for Libsodium's ubf_crypto_generichash () in its absense.
	
	Do not use this function in security-critical applications.
	Use ubf_crypto_generichash () if the hash is important.
	
	The length of the hash stLenHash is currently fixed at 32 octets.
*/
void ubf_hex_simple_hash	(
				unsigned char	*pHash,		size_t	stLenHash,	// Hash and its length.
				const char		*pData,		size_t	stLenData	// Data and its length.
							)
;

/*
	ubf_hex_test_function
	
	Test function. Tests the functions in this module.
*/
#ifdef DEBUG
	#ifndef UBF_HEX_BUILD_TEST_FUNCTION
	#define UBF_HEX_BUILD_TEST_FUNCTION
	#endif
#else
#endif
#ifdef UBF_HEX_BUILD_TEST_FUNCTION
	void ubf_hex_test_function (void);
#else
	#define ubf_hex_test_function()
#endif

EXTERN_C_END

#endif															// End of #ifndef U_STR_HEX_H.
/****************************************************************************************

	File:		strnewline.h
	Why:		New line functions.
	OS:			C99
	Author:		Thomas
	Created:	2022-04-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-04-11	Thomas			Created.

****************************************************************************************/

/*
	This module supports the following build options:


	CUNILOG_NEWLINE_POSIX_ONLY
	
	Only POSIX line endings (LF) are supported. The enumeration values for other line endings
	are removed by the preprocessor.


	CUNILOG_NEWLINE_WINDOWS_ONLY

	Only Windows (CRLF) line endings are supported. The enumeration values for other line
	endings are removed by the preprocessor.


	CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY

	Only POSIX (LF) and Windows (CRLF) line endings are supported. The enumeration values
	for other line endings are removed by the preprocessor.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

// Used for testing the definitions.
//#define CUNILOG_NEWLINE_WINDOWS_ONLY

#ifndef STRNEWLINE_H
#define STRNEWLINE_H

/*
	Correct the definitions. This also sets priorities and overrides of the definitions.
*/
#if defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
#endif
#if defined (CUNILOG_NEWLINE_POSIX_ONLY) && defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

/*
	strIsNewLine

	Checks if ch points to one or more newline markers. The function returns the amount of
	new lines found, 0 if ch does not point to a new line marker.

	Since 2024-11-29 this function is considered deprecated. Use strIsLineEndings () instead.
	The function might be made obsolete in the future.

	See https://en.wikipedia.org/wiki/Newline .
	
	For our implementation, a new line is found when:
		<CR>		(0x0D)
		<CR><LF>	(0x0D)(0x0A)
		<LF>		(0x0A)
		This counts as two new lines (a single CR and a single LF):
		<LF><CR>	(0x0A)(0x0D)

	Parameters:
	ch					A pointer to the character string to be checked.
						Since stJump stores the amount of bytes that make up the
						newline marker, if the caller increments ch by stJump the
						new value of ch points to the first byte after the newline
						marker.
	stLen				Length of the character string in octets, not including
						a terminating NUL character.  If this parameter is (size_t) -1,
						the function obtains the length with a call to strlen (ch).
	stJump				A pointer to the amount of octets in the new line phrase
						returned by the function. The caller can for instance use
						this information to increment the pointer to the character
						string in order to jump over the new line marker. If
						stJump is NULL, this parameter is ignored.
						Possible return values:
						stJump = 0			The found byte is not part of a newline
											marker.
						stJump = 1			A single <CR> (carriage return) was found
											or a single <LF> was found.
						stJump = 2			A <CR><LF> pair was found.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.
*/
unsigned int strIsNewLine (char *ch, size_t stLen, size_t *stJump);

/*
	strIsLineEndings

	Checks if ch points to one or more newline markers/line endings. The function returns
	the amount of consecutive line endings encountered, or 0 if ch does not point to at
	least one.

	The function is similar to strIsNewLine () but treats all possible line endings
	of the enum enLineEndings as line endings, and counts them accordingly.

	Parameters:
	ch					A pointer to the character string to be checked.
						Since stJump stores the amount of octets that make up the
						newline marker(s), if the caller increments ch by stJump the
						new value of ch points to the first byte after the encountered
						line endings.
	stLen				Length of the character string in octets, not including
						a terminating NUL character.  If this parameter is (size_t) -1,
						the function obtains the length with a call to strlen (ch).
	stJump				A pointer to the amount of octets of consecutive line endings
						returned by the function. The caller can for instance use
						this information to increment the pointer to the character
						string in order to jump over new line markers.
						If not required, this parameter can be NULL.
						Possible return values:
						stJump = 0			The found byte is not part of a newline
											marker.
						stJump = 1			A single <CR> (carriage return) was found
											or a single <LF> was found.
						stJump = 2			A <CR><LF> pair was found.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.
*/
size_t strIsLineEndings (char *ch, size_t stLen, size_t *stJump)
;

/*
	newline_t

	Represents a new line.

	Recommended is unilogNewLineDefault.

	The value cunilogNewLineSystem uses the operating system/platform default, which is
	currently cunilogNewLineWindows (CRLF) in Windows and cunilogNewLinePOSIX (LF) for every
	other system.

	The value cunilogNewLineDefault used to be cunilogNewLineSystem to ensure logfiles
	could be opened with Notepad on Windows systems but since newer versions of Notepad
	(Windows 10 and newer) can perfectly display files that have POSIX line endings, the
	default is now cunilogNewLinePOSIX to save one octet per event line. Use
	cunilogNewLineWindows or cunilogNewLineSystem if textual logfiles need to be opened/
	viewed with Notepad for Windows versions before Windows 10.
*/
#if defined (CUNILOG_NEWLINE_POSIX_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLineWindows							// CR + LF.
		,	cunilogNewLineDefault = cunilogNewLineWindows
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		,	cunilogNewLineWindows							// CR + LF.
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#else
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		,	cunilogNewLineWindows							// CR + LF.
		,	cunilogNewLineApple								// CR only.
		,	cunilogNewLineRISCOS							// LF + CR.
		,	cunilogNewLineQNXbef4							// RS (1Eh)
		,	cunilogNewLineIBMzOS							// EBCDIC NL (15h)
		,	cunilogNewLineNEL								// Unicode newline NEL (U+0085)
		,	cunilogNewLineLS								// Unicode line separator LS (U+2028)
		,	cunilogNewLinePS								// Unicode paragraph separator PS (U+2029)
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#endif
typedef enum enLineEndings	newline_t;

/*
	ccLineEnding

	Returns the line ending for nl. Note that szLineEnding () also returns
	its length.
*/
const char *ccLineEnding (newline_t nl);

/*
	lnLineEnding

	Returns the length of the line ending nl. The value does not include the NUL
	terminator.
*/
size_t lnLineEnding (newline_t nl);

/*
	szLineEnding

	Returns the line ending and its length. The length does not include the NUL
	terminator.
*/
const char *szLineEnding (newline_t, size_t *pln)
;

/*
	lnLineEnding

	Returns the length of the string that represents the line ending nl.
	The returned value is the length of the string excluding a NUL terminator.
*/
size_t lnLineEnding (newline_t nl);

#ifdef DEBUG
	#ifndef STRNEWLINE_BUILD_TEST
	#define STRNEWLINE_BUILD_TEST
	#endif
#endif

/*
	Test function.
*/
#ifdef STRNEWLINE_BUILD_TEST
	void test_strnewline (void);
#else
	#define test_strnewline()
#endif

EXTERN_C_END

#endif														// Of #ifndef STRNEWLINE_H.
/****************************************************************************************

	File:		strhexdumpstructs.h
	Why:		Structures for data dumps.
	OS:			C99
	Author:		Thomas
	Created:	2024-09-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-10	Thomas			Created. Based on ubfdumpstructs.h, which is now obsolete.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRHEXDUMPSTRUCTS_H
#define STRHEXDUMPSTRUCTS_H

#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strnewline.h"

#endif

// Errors.
#define STR_DATA_DUMP_ERR_NO_ERROR						0
#define STR_DATA_DUMP_ERR_NO_DATA						2		// Either chDumpData is NULL or the
																//	length is 0.
#define STR_DATA_DUMP_ERR_NUM_FORMAT					3		// Only one number system is
																//	possible.
#define STR_DATA_DUMP_ERR_OUT_OF_MEMORY					4		// Not enough space available on
																//	the heap.

// Option flags.
#define STR_DATA_DUMP_OPTS_NONE					0x00000000		// No option. Everything is
																//	default.
#define STR_DATA_DUMP_OPTS_BINARY				0x00000001		// Use binary format for data
																//	instead of hex.
#define STR_DATA_DUMP_OPTS_DECIMAL				0x00000002		// Use decimal format for data
																//	instead of hex.
/*
#define STR_DATA_DUMP_OPTS_NO_FIRST_OFF_SEP		0x00000004		// Suppresses the first separator
																//	(usually a colon) after the
																//	offset.
*/
/*
#define STR_DATA_DUMP_OPTS_NO_LAST_VAL_SEP		0x00000008		// Omit the last value separator.
*/
#define STR_DATA_DUMP_OPTS_OFFS_DECIMAL			0x00000010		// The offset is in decimal.
#define STR_DATA_DUMP_OPTS_NS_INDICATOR_L		0x00000020		// Add an indicator which number
																//	system is used
																//	in lower case.
																//	Uses "h" for hexadecimal,
																//	"b" for binary, and
																//	"d" for decimal.
#define STR_DATA_DUMP_OPTS_NS_INDICATOR_U		0x00000040		// Add an indicator which number
																//	system is used
																//	in upper case.
																//	Uses "H" for hexadecimal,
																//	"B" for binary, and
																//	"D" for decimal.
#define STR_DATA_DUMP_OPTS_HEX_DATA_LOWER		0x00000080		// Show hexadecimal data in
																//	lower case. Default is upper
																//	case.
#define STR_DATA_DUMP_OPTS_OFFS_USE_BLANKS		0x00000100		// Output blanks (" ") in the
																//	offset instead of zeros ("0").
#define STR_DATA_DUMP_OPTS_LINEST_FIRST_ONLY	0x00000200		// The member chLineStart is only
																//	used for the first output
																//	line. All other lines are
																//	filled up with stLineStart
																//	blanks (SCP, ASCII 20h, 32d).

#ifdef __cplusplus
	extern "C" {
#endif

/*
	SHEX_DUMP_PARS
	
	The parameter structure for data dumps.

	A data dump consists of the following characteristics:
	- An optional text provided by the caller that precedes each line of the dump.
		The example from Wikipedia below does not contain such a text.
	- The offset value. The offset values in the example below contain offsets of
		0000, 0010, 0020, and 0030 hexadecimal.
	- The first offset separator. In the example below this is a colon (":").
	- The second offset separator. In the example below this is a space (or blank),
		ASCII 20h, 30d.
	- The data values. The first line of data values in the example below starts with
		57, 69, 6B, 69, etc, in hexadecimal.
	- The data value separators. Each data value in the example below is separated by
		a blank (or space) character, which is ASCII 32d, or 20h. Data value separators
		follow the extracted data. The separator of the last data value may not be
		desired and can therefore be suppressed with the option flag
		STR_DATA_DUMP_OPTS_NO_LAST_VAL_SEP.
	- The display separator. In the example from Wikipedia below the display separator
		is a blank (or space) character (ASCII 20 hex, 32 decimal).
	- The plain display text. In the example below, the plain display text of the first
		dump line is "Wikipedia, the f".
	
	Example of a hex dump, taken from https://en.wikipedia.org/wiki/Hex_dump:

		      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+------ Number of values (uinValues)
		      !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !
		      V  V  V  V  V  V  V  V  V  V  V  V  V  V  V  V
		0000: 57 69 6B 69 70 65 64 69 61 2C 20 74 68 65 20 66  Wikipedia, the f
		0010: 72 65 65 20 65 6E 63 79 63 6C 6F 70 65 64 69 61  ree encyclopedia
		0020: 20 74 68 61 74 20 61 6E 79 6F 6E 65 20 63 61 6E   that anyone can
		0030: 20 65 64 69 74 00 00 00 00 00 00 00 00 00 00 00   edit...........
	^	^   ^ ^ ^                    ^                     ^ ^ ^
	!	!   ! ! !                    !                     ! ! !
	!	!   ! ! !                    !                     ! ! +-- Plain display text.
	!	!   ! ! !                    !                     ! ! 
	!	!   ! ! !                    !                     ! +---- Display separator.
	!	!   ! ! !                    !                     +------ Last data value.
	!	!   ! !                      +---------------------------- Half line separator (ccHalfLineSep).
	!	!   ! ! +------------------------------------------------- First data value separator.
	!	!   ! +--------------------------------------------------- First data value.
	!	!	!
	!	!   +----------------------------------------------------- Offset separator (member ccOffsetSep).
	!	+--------------------------------------------------------- Offset value.
	+------------------------------------------------------------- Line start (member ccLineStart).

	Members of the structure:
	
	le						The line ending/newline character(s) to use. See enum enLineEndings
							in strnewline.h for details. If unsure, use unilogNewLineDefault,
							which is a POSIX line ending of LF only. This works on POSIX platforms
							as well as on Windows 10 and up. Use unilogNewLineSystem or
							unilogNewLineWindows for Windows versions before Windows 10.

	ccHeader				A pointer to a string that serves as header text. A line ending is
							added automatically. If this member is NULL, the member lenHeader also
							needs to be 0, and this does not insert a header at all. To create a
							header that consists of a single line ending only, point ccHeader to
							an empty string ("") and set lenHeader to either 0 or USE_STRLEN.
	
	lenHeader				The length of the buffer ccHeader points to, in octets/bytes.
							If lenHeader is USE_STRLEN, which is (size_t) -1, ccHeader must be
							NUL-terminated and obviously can't contain NUL bytes.

	ccLineStart				An optional text provided that precedes each line of the dump.
							This member can be NULL, if not required/used. Since the member
							stLineStart provides the length of this string, in octets,
							excluding a terminating NUL character, the buffer ccLineStart
							points to does not have to be NUL terminated. If this member
							is NULL, the member lenLineStart also must be 0.
							
	lenLineStart			The length of the optional text that precedes each line of
							the dump. If this member is 0, a call to strlen (ccLineStart) is used
							to obtain its value, which means that ccLineStart must be NUL-
							terminated.
							
	stFirstOffset			An optional value that is added to each offset in the output.
							A value of 0 makes the offset start at 0. The offset in the
							output is placed after a line start (member chLineStart).

	uiError					An error code in case of failure. This member contains one of
							the STR_DATA_DUMP_ERR... constants when one of the functions
							fails. This is the only member that is returned by one of the
							dump functions. All other members are input members, meaning
							the functions read and use their values. A value of
							STR_DATA_DUMP_ERR_NO_ERROR is returned if no error occurred.
							
	uiOffsetWidth			The width of the offset. This value must not be 0.
	
	uiOffsetSep01			This member contains the character placed directly after the
							offset.
	
*/
typedef struct shex_dump_pars
{
	newline_t			le;										// How to represent line endings.

	const char			*ccHeader;								// Header.
	size_t				lenHeader;								// Length of ccHeader.

	const char			*ccLineStart;							// Pointer to a character string
																//	to be inserted at the start
																//	of each line.
	size_t				lenLineStart;							// The length of chLineStart, not
																//	including a terminating NUL
																//	character.

	size_t				stFirstOffset;							// This value is added to the
																//	returned offset. If this member
																//	is set to (size_t) -1, the
																//	pointer value of the data to
																//	dump is used.
	uint8_t				uiOffsetWidth;							// The amount of digits in the offset.

	const char			*ccOffsetSep;							// The separator between the offset
																//	and the values.
	size_t				lenOffsetSep;							// Its length.

	uint8_t				uinValues;								// The width of a data dump line.
																//	This is the amount of values
																//	(usually octets/bytes)
																//	displayed on a single line.

	uint8_t				uiValueSize;							// The width of a single value,
																//	in bytes (octets). Not (yet)
																//	supported. Ignored.

	const char			*ccValSeparator;						// The separator between values.
																//	Default is SPC (20h, 32d).
	size_t				lenValSeparator;						// Its length.

	const char			*ccHalfLineSep;							// The separator between half of
																//	the values.
	uint8_t				lenHalfLineSep;							// Its length.

	const char			*ccDisplaySep;							// The separator between the
																//	values block and the ASCII
																//	display.
	uint8_t				lenDispSep;								// Its length.

	const char			*ccUnprintable;							// Representation of an
																//	unprintable character.
	size_t				lenUnprintable;							//	Its length.

	const char			*ccNoMoreDataVal;						// Representation of a value
																//	when the data
																//	can't fill the last line
																//	(values).
	size_t				lenNoMoreDataVal;						// Its length.
	const char			*ccNoMoreDataDisp;						// Representation when the data
																//	can't fill the last line
																//	(ASCII display text).
	size_t				lenNoMoreDataDisp;						// Its length.

	unsigned int		uiOptions;								// Option flags. See above.
	unsigned int		uiError;								// A more detailed error code on
																//	failure. See above.
} SHEX_DUMP_PARS;

/*
	The structure that holds the values already calculated.

	The member bInitialised is used as an indicator that the function requires initialisation.
	To initialise the structure:

	SHEX_DUMP_SAN	s;
	s.bInitialised = false;

*/
typedef struct shex_dump_san
{
	bool				bInitialised;
	size_t				lenHeader;
	size_t				lenLineStart;
	size_t				lenOffset;
	size_t				lenOffsetSep;
	size_t				lenValSeparator;
	size_t				lenHalfLineSep;
	size_t				lenUnprintable;
	size_t				lenNoMoreDataVal;
	size_t				lenNoMoreDataDisp;
	size_t				lenDispSeparator;
	size_t				lenOneLine;
	size_t				lenValuesWidth;
	size_t				stNextOffset;
	const char			*ccNxtValToDump;
	size_t				lenValToDumpLeft;
} SHEX_DUMP_SAN;

#ifdef __cplusplus
	}
#endif

#endif															// Of #ifndef STRHEXDUMPSTRUCTS_H.
/****************************************************************************************

	File:		strhexdump.h
	Why:		Functions for data dumps.
	OS:			C99
	Author:		Thomas
	Created:	2024-09-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-10	Thomas			Created. Based on ubfdump.h, which is now obsolete.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRHEXDUMP_H
#define STRHEXDUMP_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./strhexdumpstructs.h"
		#include "./strmembuf.h"
	#else
		#include "./strhexdumpstructs.h"
		#include "./strmembuf.h"
	#endif

#endif

/*
#include "./../fncts/msvcdbgmemdef.h"
#include "./../OS/ubf_type_definitions.h"
#include "./../ubfstring/ubfstringstruct.h"
*/

#ifdef __cplusplus
	extern "C" {
#endif

/*
	A default SUBF_DUMP_PARS structure for general use.
*/
extern	SHEX_DUMP_PARS		sdp_default;

/*
	ubf_data_dump_def_SUBF_DUMP_PARS
	
	Copies all members of the default SUBF_DUMP_PARS structure into the
	SUBF_DUMP_PARS structure s points to.
*/
void ubf_data_dump_def_SUBF_DUMP_PARS (SHEX_DUMP_PARS *s);

/*
	UBF_DATA_DUMP_DEF_SUBF_DUMP_PARS
	
	Convenience wrapper macro for ubf_data_dump_def_SUBF_DUMP_PARS to dereference the
	pointer.
*/
#define UBF_DATA_DUMP_DEF_SUBF_DUMP_PARS(a)		\
			ubf_data_dump_def_SUBF_DUMP_PARS (&(a))

/*
	ubf_data_dump_SMEMBUF
	
	Creates a dump of the data pointed to by chDumpData with the length stDumpDataLen
	into the SMEMBUF structure pointed to by mbOutput. The type and parameters of the
	data dump is determined by the SUBF_DUMP_PARS structure pointed to by sDumpPars.
	
	mbOutput			The SMEMBUF structure that receives the output.

	chDumpData			A pointer to the start of the dump data.

	lenDumpData			The length of the dump data, in octets (bytes).

	sDumpPars			A pointer to a SHEX_DUMP_PARS structure, which determines several
						parameters of the output.

	pdSanDPars			A pointer to a writable SHEX_DUMP_SAN structure. This can
						be used for consecutive invocations to avoid recalculating some
						values. If this parameter is NULL, the function uses its own
						automatic version and recalculates its members every time it is
						called. Each SHEX_DUMP_PARS requires its own SHEX_DUMP_SAN
						structure to preserve its calculated parameters.
						Set the structures lenHeader header to 0 before calling the
						function the first time. This tells it to calculate its values.
						It can then be re-used in consecutive calls and no recalculations
						are required.

	The function returns the amount of octets/bytes written to the buffer of mbOutput,
	excluding the terminating NUL character.
*/
size_t ubf_data_dump_SMEMBUF	(
		SMEMBUF				*mbOutput,						// The target SUBF_STRING.
		const char			*ccDumpData,					// The data to dump.
		size_t				lenDumpData,					// The length of the data to dump.
		SHEX_DUMP_PARS		*psDumpPars,					// The SUBF_DUMP_PARS structure.
		SHEX_DUMP_SAN		*pdSanDPars						// Can be carried to the next invokation.
								)
;

#ifdef nix
/*
	ubf_data_dump_puts

	The function is identical to ubf_data_dump_SUBF_STRING () with the exception that it
	doesn't need the SUBF_STRING parameter ssTarget and directly prints the dump output
	to stdout.

	The function provides a SUBF_STRING structure and calls ubf_data_dump_SUBF_STRING (),
	then uses puts () to output the SUBF_STRING structure's buffer if the call to
	ubf_data_dump_SUBF_STRING () was successful. It outputs nothing when the call
	to ubf_data_dump_SUBF_STRING () failed.

	If the type (const char *) is an issue, use ubf_data_dump_puts_typeless () to cast
	the first parameter.

	The function returns TRUE on success, FALSE on failure. The return value is obtained
	from the call to ubf_data_dump ().
*/
bool ubf_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
						);

/*
	ubf_debug_data_dump_puts
	
	Debug-only version of ubf_data_dump_puts (). Only outputs the data dump in debug
	versions.
*/
#ifdef DEBUG
	bool ubf_debug_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
									);
#else
	#define ubf_debug_data_dump_puts(a, b, c)
#endif

/*
	ubf_data_dump_puts_typeless

	Wrapper macro for ubf_data_dump_puts () to cast the first parameter into the (const
	char *) ubf_data_dump_puts () is declared for.
*/
#define ubf_data_dump_puts_typeless(d,l,p)		\
			ubf_data_dump_puts ((const char *) d, l, p)

/*
	ubf_debug_data_dump_puts_typeless
	
	Debug version of the macro ubf_data_dump_puts_typeless(). Only outputs in debug
	versions.
*/
#define ubf_debug_data_dump_puts_typeless(d,l,p)		\
			ubf_debug_data_dump_puts ((const char *) d, l, p)


/*
	ubf_data_dump_puts_default
	
	Macro wrapper for ubf_data_dump_puts () that only requires the first two parameters
	and sets the last one (SUBF_DUMP_PARS) to NULL.
*/
#define ubf_data_dump_puts_default(d,l)			\
			ubf_data_dump_puts ((const char *) d, l, NULL)

#endif // Of #ifdef 0.

/*
	test_strhexdump

	Test function.
*/
#ifdef DEBUG
	#ifndef BUILD_STRHEXDUMP_TEST_FNCT
	#define BUILD_STRHEXDUMP_TEST_FNCT
	#endif
#endif
#ifdef BUILD_STRHEXDUMP_TEST_FNCT
	bool test_strhexdump (void);
#else
	#define test_strhexdump()
#endif

#ifdef __cplusplus
	}
#endif

#endif															// Of #ifndef STRHEXDUMP_H.
/****************************************************************************************

	File:		strintuint.h
	Why:		Conversion functions between character strings and integers.
	OS:			C99.
	Author:		Thomas
	Created:	2019-08-28
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-08-28	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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


	The functions ubf_itoa (), ubf_n_itoa10 (), ubf_str_from_uint16 (), ubf_str_from_int64 (),
	and ubf_str_from_uint64 () are (c) Lukas Chmela and derived from the versions at
	http://www.strudel.org.uk/itoa/ :

	* C++ version 0.4 char* style "itoa":
	* Written by Lukas Chmela
	* Released under GPLv3.

*/

#ifndef U_STR_INT_UINT_INCLUDED
#define U_STR_INT_UINT_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../pre/platform.h"
	#endif
#endif

// Maximum lengths of unsigned and signed integer values in ASCII representation.
//	The definitions that end with _LEN specify the length excluding NUL, the ones
//	that end with _SIZE include the NUL terminator.
#ifndef UBF_INT8_LEN
#define UBF_INT8_LEN					(4)						// "-128"
// "1234" = 4.
#endif
#ifndef UBF_INT8_SIZE
#define UBF_INT8_SIZE					(4 + 1)					// "-128"
// "1234" = 4.
#endif
#ifndef UBF_INT16_LEN
#define UBF_INT16_LEN					(6)						// "-32768" = 6.
#endif
#ifndef UBF_INT16_SIZE
#define UBF_INT16_SIZE					(6 + 1)					// "-32768" = 6.
#endif
#ifndef UBF_INT32_LEN
#define UBF_INT32_LEN					(11)					// "-4294967296" = 11.
#endif
#ifndef UBF_INT32_SIZE
#define UBF_INT32_SIZE					(11 + 1)				// "-4294967296" = 11.
#endif
#ifndef UBF_INT64_LEN
#define UBF_INT64_LEN					(21)					// "+18446744073709551615".
// "+12345678901234567890" = 21.
#endif
#ifndef UBF_INT64_SIZE
#define UBF_INT64_SIZE					(21 + 1)				// "+18446744073709551615".
// "+12345678901234567890" = 21.
#endif
#ifndef UBF_UINT8_LEN
#define UBF_UINT8_LEN					(3)						// "255".
// "123" = 3.
#endif
#ifndef UBF_UINT8_SIZE
#define UBF_UINT8_SIZE					(3 + 1)					// "255".
// "123" = 3.
#endif
#ifndef UBF_UINT16_LEN
#define UBF_UINT16_LEN					(5)						// "65535".
// "12345" = 5.
#endif
#ifndef UBF_UINT16_SIZE
#define UBF_UINT16_SIZE					(5 + 1)					// "65535".
// "12345" = 5.
#endif
#ifndef UBF_UINT32_LEN
#define UBF_UINT32_LEN					(10)					// "4294967296";
// "1234567890" = 10.
#endif
#ifndef UBF_UINT32_SIZE
#define UBF_UINT32_SIZE					(10 + 1)				// "4294967296";
// "1234567890" = 10.
#endif
#ifndef UBF_UINT64_LEN
#define UBF_UINT64_LEN					(20)					// "18446744073709551615".
// "12345678901234567890" = 20.
#endif
#ifndef UBF_UINT64_SIZE
#define UBF_UINT64_SIZE					(20 + 1)				// "18446744073709551615".
// "12345678901234567890" = 20.
#endif

#ifndef ASCII_NUL
#define ASCII_NUL			'\0'
#endif

// Fall through comment used in switch () statements. See
//	https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wimplicit-fallthrough .
#if defined(_MSC_VER)
#ifndef UBF_FALLTHROUGH_HINT
#define UBF_FALLTHROUGH_HINT		/* FALLTHRU */
#endif
#else
#ifndef UBF_FALLTHROUGH_HINT
#define UBF_FALLTHROUGH_HINT						\
			__attribute__((fallthrough));
#endif
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef HAVE_C_ITO_ALPHABET
	#define HAVE_C_ITO_ALPHABET
	#define UBUILD_C_ITO_ALPHABET_IN_HERE
	extern char	c_ito_alphabet [];
#endif

/*
	Our version of itoa (). Taken from http://www.strudel.org.uk/itoa/ .
	It seems to be a very fast version.
*/
char *ubf_itoa (int value, char *result, int base);

/*
	ubf_n_itoa10

	This is an itoa () function that returns the amount of bytes written to result and
	uses a base of 10.
*/
size_t ubf_n_itoa10 (int value, char *result);

/*
	ubf_str0_from_59max

	Copies the resulting ASCII representation of the value ui59m, which can have values
	between 0 and 59, to the buffer result points to. This buffer must therefore have a
	size of at least two octets/bytes.

	The actual range of ui59m can be from 0 to 61, and the lookup table is big enough.
	See https://en.cppreference.com/w/c/chrono/tm for more details.
	"Range allows for a positive leap second. Two leap seconds in the same minute are
	not allowed (the C89 range 0..61 was a defect)."
	The lookup table holds 62 values (0 to 61) to avoid issues with C89 compilers.

	The function does not add a NUL-terminator to result, nor does it return a value.
	It always writes exactly two bytes to result. For example, if ui59m is 26, the
	function writes the non-NUL-terminated string "26" to result.
	The caller is responsible for ensuring that the function is not called with any
	values of ui59m greater than 59.

	The function's purpose is to return ASCII representations of minutes, seconds,
	months, hours, days in a month, week numbers, or any unsigned integer of up to 59 very
	quickly through an indexed table.

	If the returned string is required to be NUL-terminated, use ubf_str0_from_59max_n ()
	instead.

*/
#ifdef DEBUG
	void ubf_str0_from_59max (char *result, uint8_t ui59m);
#else
	extern char c_0_to_59_str0 [62][2];
	#define ubf_str0_from_59max(r,u)	memcpy (r, c_0_to_59_str0 [u], 2)
#endif

/*
	ubf_str0_from_59max_n

	The function or macro is identical to ubf_str0_from_59max () but does add a NUL-
	terminator.

	Copies the resulting ASCII representation of the value ui59m, which can have values
	between 0 and 59, to the buffer result points to. This buffer must therefore have a
	size of at least three octets/bytes since the function adds a NUL-terminator to result.

	The function's purpose is to return ASCII representations of minutes, seconds,
	months, hours, days in a month, week numbers, or any unsigned integer of up to 59 very
	quickly through a lookup table.
*/
#ifdef DEBUG
	void ubf_str0_from_59max_n (char *result, uint8_t ui59m);
#else
	#define ubf_str0_from_59max_n(r,u)					\
		memcpy (r, c_0_to_59_str0 [u], 2);				\
		r [2] = '\0'
#endif

/*
	ubf_str_from_uint8
	
	Returns an ASCII representation of the value of ui8, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT8_SIZE octets long.

	The function returns the amount of decimal digits written to result, not
	counting the terminating NUL character.
*/
size_t ubf_str_from_uint8 (char *result, uint8_t ui8);

/*
	ubf_str_from_uint16
	
	Returns an ASCII representation of the value of ui16, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT16_SIZE bytes long.

	The function returns the amount of decimal digits written to result, which
	does not include the terminating NUL character.
*/
size_t ubf_str_from_uint16 (char *result, uint16_t ui16);

/*
	ubf_str0_from_uint16

	Returns an ASCII representation with leading zeroes of the value of ui16,
	in decimal (base 10). The buffer result points to must be at least digits + 1
	octets/bytes long.

	The parameter dgts cannot be 0.

	The function is identical to ubf_str_from_uint16 but writes leading zeroes to
	the buffer result points to. The parameter digits specifies the total amount
	of digits for the result, which should be any value between 1 and UBF_UINT16_LEN,
	which is 5. Values for digits greater than UBF_UINT16_LEN always produce leading
	zeroes only for the range between UBF_UINT16_LEN + 1 and digits because the
	value of ui16 can never become big enough to fill this area with any other
	number.

	The function returns the amount of digits written to result, not counting
	leading zeros, and also not counting a terminating NUL, or STR0_NOT_ENOUGH_DIGITS
	if the value of ui16 cannot be represented in the specified amount of digits.
	
	If the value of digits is not big enough to hold the ASCII
	representation of the value ui16, the function fills result up to digits
	numerical digits from the right and returns (size_t) -1, which is defined as
	STR0_NOT_ENOUGH_DIGITS.
	
	Note that the buffer result points to must be at least one octet larger
	than digits to hold a terminating NUL character. It is recommended to use a
	buffer size of UBF_UINT16_SIZE, which is UBF_UINT16_LEN + 1 for the NUL
	character.
*/
size_t ubf_str0_from_uint16 (char *result, size_t digits, uint16_t ui16);

/*
	ubf_str_from_int64

	Returns an ASCII representation of the value of i64, in decimal (base 10). The
	buffer result points to must be at least UBF_INT64_LEN bytes long.

	The function returns the amount of characters written to result, not counting
	the terminating NUL character.
*/
size_t ubf_str_from_int64 (char *result, int64_t i64);

/*
	ubf_str_to_int64

	Obtains a signed 64 bit integer of the ASCII string chStr in the address pi points
	to. The function stops at the first character that is not a numerical digit. However,
	chStr may start with an ASCII '+' or an ASCII '-' character. If pi is not NULL, the
	result of the conversion is returned at the memory location pi points to. For a
	function that is more picky and returns an error if chStr contains non-numerical
	characters, see ubf_int64_from_str ().

	The function returns the amount of characters used up for the conversion.
*/
size_t ubf_str_to_int64 (const char *chStr, int64_t *pi);

/*
	ubf_std_int64_from_str
	
	Wrapper macro for ubf_str_to_int64 () that reverses the order of its parameters
	and provides an API that is more standardised.
*/
#define ubf_std_int64_from_str(pi, pS)					\
	ubf_str_to_int64 (pS, pi)

/*
	ubf_str_from_uint64

	Returns an ASCII representation of the value of ui64, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT64_SIZE bytes long, which is
	UBF_UINT64_LEN + 1, or 21.

	The function returns the amount of digits written to result, not counting the
	terminating NUL character.
*/
size_t ubf_str_from_uint64 (char *result, uint64_t ui64);

#ifndef STR0_NOT_ENOUGH_DIGITS
#define STR0_NOT_ENOUGH_DIGITS	((size_t) -1)
#endif

/*
	ubf_str0_from_uint64

	Returns an ASCII representation with leading zeroes of the value of ui64,
	in decimal (base 10). The buffer result points to must be at least digits + 1
	octets/bytes long.

	The parameter dgts cannot be 0.

	The function is identical to ubf_str_from_uint64 but writes leading zeroes to
	the buffer result points to. The parameter digits specifies the total amount
	of digits for the result, which should be any value between 1 and UBF_UINT64_LEN,
	which is 20. Values for dgts greater than UBF_UINT64_LEN always produce leading
	zeroes only for the range between UBF_UINT64_LEN + 1 and digits because the
	value of ui64 can never become big enough to fill this area with any other
	number.

	The function returns the amount of digits written to result, not counting
	leading zeros, and also not counting a terminating NUL, or STR0_NOT_ENOUGH_DIGITS
	if the value of ui64 cannot be represented in the specified amount of digits.
	
	If the value of digits is not big enough to hold the ASCII
	representation of the value ui64, the function fills result up to digits
	numerical digits from the right and returns (size_t) -1, which is defined as
	STR0_NOT_ENOUGH_DIGITS.
	
	Note that the buffer result points to must be at least one octet larger
	than digits to hold a terminating NUL character. It is recommended to use a
	buffer size of UBF_UINT64_SIZE, which is UBF_UINT64_LEN + 1 for the NUL
	character.
*/
size_t ubf_str0_from_uint64 (char *result, size_t digits, uint64_t ui64);

/*
	ubf_uint64_from_str

	Obtains an unsigned 64 bit integer of the ASCII string chStr in ui. The conversion
	stops at the first white space or any character that is not a valid decimal digit.
	Additionally, the string chStr may start with an ASCII '+' character. If ui is not
	NULL, the result of the conversion is returned at the memory location ui points to.
	If ui is NULL, the result of the conversion is not stored but all checks are
	performed and the result value indicates success or failure. If chStr is NULL the
	function treats it as an emptry string, with the result of the conversion being 0.
	If chStr starts with an ASCII '-' or any other non-numeric character the function
	treats it as an empty string/number, which means 0 is returned.

	The function returns TRUE if the conversion was successful, FALSE otherwise. The
	conversion fails if chStr contains a number that is greater than UINT64_MAX.
	
	If the amount of characters consumed by the function is required, or if the
	amount of characters to be processed needs to be restricted, use
	ubf_uint64_from_str_n () instead.
*/
bool ubf_uint64_from_str (uint64_t *ui, const char *chStr);

/*
	ubf_uint64_from_str_n
	
	The function is similar to ubf_uint64_from_str () but only processes chStr
	up to nLen bytes/characters and returns the amount of characters consumed
	and used up for the value stored in ui by the function. The returned value
	includes an optional preceeding '+' if the parameter s is enUintFromStrAllowPlus.
	
	If nLen should not be used, pass (size_t) -1 to the function. The function
	then stops when the NUL terminator is encountered.
	
	The function returns the amount of octets consumed from chStr.
*/
enum enUintFromStrN
{
	enUintFromStrDontAllowPlus,									// No '+' allowed.
	enUintFromStrAllowPlus										// Allow preceding '+'.
};
size_t ubf_uint64_from_str_n (uint64_t *ui, const char *chStr, size_t nLen, enum enUintFromStrN s);

/*
	ubf_std_uint64_from_str
	
	Wrapper macro for ubf_uint64_from_str_n () that provides an API that is more
	standardised.
*/
#define ubf_std_uint64_from_str(pui, pStr)				\
	ubf_uint64_from_str_n (pui, pStr, (size_t) -1,		\
			enUintFromStrAllowPlus)
	
/*
	ubf_int64_from_str

	Obtains a signed 64 bit integer of the ASCII string chStr in the address pi points
	to. All possible checks are performed. The string in chStr must not contain white
	space or any character that is not a valid decimal digit. However, chStr may start
	with an ASCII '+' or an ASCII '-' character. If pi is not NULL, the result of the
	conversion is returned at the memory location pi points to. If pi is NULL, the result
	of the conversion is not stored but all checks are performed and the result value
	indicates success or failure. If chStr is NULL the function treats it as an emptry
	string, with the result of the conversion being 0. For a function that stops at the
	first non-numerical digit, see ubf_str_to_int64 ().

	The function returns TRUE if the conversion was successful, FALSE otherwise. The
	conversion fails if chStr contains a number that is greater than INT64_MAX or
	smaller than INT64_MIN. It also fails if chStr contains any character that is not a
	digit, and not a '+', or a '-' as its first character.
*/
bool ubf_int64_from_str (int64_t *pi, const char *chStr);

/*
	ubf_uint16_from_str
	ubf_ushort_from_str

	Returns an unsigned 16 bit integer (uint16_t) of the ASCII string chStr in the
	address pu points to. The function calls ubf_uint64_from_str () to obtain the result.
	If pus is NULL, the return value of the function indicates the success or failure of
	the conversion without returning the actual result of the conversion. The biggest
	number that can be successfully converted to a uint16_t is USHRT_MAX, which is
	usually 0xFFFF.

	A return value of TRUE means the conversion was successful. If the function returns
	FALSE the conversion was unsuccessful. The function returns TRUE if the conversion
	was successful but due to pus being NULL the result of it could not be returned to
	the caller.
*/
bool ubf_uint16_from_str (uint16_t *pus, const char *chStr);
#define ubf_ushort_from_str(a,b)					\
			ubf_uint16_from_str (a, b)
/*
	ubf_strd_from_uint64

	Returns the decimal representation of u64 in ASCII. The buffer chStr points to must
	be at least UBF_UINT64_STRLEN bytes long. For a function with identical functionality
	but that returns the bytes written to the result, see ubf_str_from_uint64 (). Unlike
	ubf_str_from_uint64 (), the function ubf_strd_from_uint64 () calls the library
	routine snprintf () to perform the conversion but discards its return value.
	
	Note that this function is around 4 times slower than ubf_str_from_uint64 (). It is
	therefore disabled.
*/
//void ubf_strd_from_uint64 (char *chStr, uint64_t u64);
#define ubf_strd_from_uint64(s,u)						\
		error Function ubf_strd_from_uint64 () is obsolete. Use ubf_str_from_uint64. See comment.

/*
	Test function builds.
*/
#ifdef DEBUG
	#ifndef UBF_BUILD_STRINTUINT_TEST
	#define UBF_BUILD_STRINTUINT_TEST
	#endif
#endif
#ifdef UBF_BUILD_STRINTUINT_TEST
	bool ubf_test_str_from_uint8 (void);
	bool ubf_test_str0 (void);
	bool Test_strintuint (void);
#else
	#define ubf_test_str_from_uint8()		(true)
	#define ubf_test_str0()					(true)
	#define Test_strintuint()				(true)
#endif


#ifdef __cplusplus
	}
#endif

#endif															// End of U_STR_INT_UINT_INCLUDED.
/****************************************************************************************

	File:		strabsolutepath.h
	Why:		String functions for absolute/relative paths.
	OS:			C99
	Author:		Thomas
	Created:	2021-07-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

****************************************************************************************/

/*
	The functions in this module do not use any file system functions.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRISABSOLUTEPATH_H
#define STRISABSOLUTEPATH_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

EXTERN_C_BEGIN

/*
	is_absolute_path_unix
	is_absolute_path_unx
	
	Returns or evaluates to true if the string chPath points to is an absolute Unix/Linux path,
	false if it is not. An absolute Unix/Linux path starts with a forward slash
	("/").

	The buffer chPath (in debug versions) or p (in release versions) points to must be at least
	one octet/byte long.
*/
#ifdef DEBUG
	bool is_absolute_path_unix (const char *chPath);
#else
	#define is_absolute_path_unix(p)					\
			('/' == (p)[0])
#endif
#define is_absolute_path_unx(p)							\
			is_absolute_path_unix (p)

/*
	is_unc_path

	Evaluates to true if the NUL-terminated string p is a UNC path
	like "\\host\path" or "//host/path". The buffer p points to must
	be NUL-terminated.
*/
#define is_unc_path(p)									\
			(											\
					(									\
							'\\' == (p)[0]				\
						&&	'\\' == (p)[1]				\
					)									\
				||	(									\
							'/' == (p)[0]				\
						&&	'/' == (p)[1]				\
					)									\
			)

/*
	is_absolute_drive_path

	Evaluates to true if the NUL-terminated string p is a typical Windows drive path
	like "X:\" or "X:/". The buffer p points to must be NUL-terminated.
*/
#define is_absolute_drive_path(p)						\
			(											\
					isalpha ((p)[0])					\
				&&	':' == (p)[1]						\
				&&	('\\' == (p)[2]	||	'/' == (p)[2])	\
			)

#define is_drive_path(p)								\
	error "Macro obsolete. Use is_full_drive_path() instead"

/*
	is_absolute_path_win
	is_absolute_path_windows
	
	Returns true if the string chPath points to is an absolute Windows path,
	false otherwise. An absolute Windows path either starts with two consecutive
	slashes (forward or backward) or starts with a drive letter and a colon
	sequence.
	
	Note that the function does not accept a mix of starting forward and backward
	slashes like "/\" or "\/". The function returns false in these cases.
*/
bool is_absolute_path_win (const char *chPath);
#define is_absolute_path_windows(p)						\
			is_absolute_path_win (p)

/*
	is_absolute_path
	
	Returns true if the path is an absolute path on either Windows or Unix/Linux.
	
	This is a function in debug versions, a macro in release versions.
	The function/macro calls is_absolute_path_unix () and is_absolute_path_win ().
*/
#ifdef DEBUG
	bool is_absolute_path (const char *chPath);
#else
	#define is_absolute_path(p)							\
		(												\
				is_absolute_path_unix	(p)				\
			||	is_absolute_path_win	(p)				\
		)

#endif

/*
	is_absolute_path_unix_l

	Returns or evaluates to true if len is greater than 0 and the first character
	chPath points to is a forward slash.

	This is a function in debug versions, a macro in release versions.
*/
#ifdef DEBUG
	bool is_absolute_path_unix_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_unix_l(p, l)				\
		(l && '/' == (p)[0])
#endif

/*
	is_absolute_path_win_l

	Returns or evaluates to true if chPath either points to a Windows UNC path or
	a full drive path. UNC paths start with two backslashes. A full drive path starts
	with a drive letter, a colon, and a backslash.

	The parameter len specifies the length of the buffer chPath points to.

	This is a function in debug versions, a macro in release versions.
*/
#ifdef DEBUG
	bool is_absolute_path_win_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_win_l(p, l)				\
		(												\
				(l > 1 && is_unc_path (p))				\
			||	(l > 2 && is_absolute_drive_path (p))	\
		)
#endif

/*
	is_absolute_path_l

	Returns true if the path is an absolute path on either Windows or Unix/Linux.

	The parameter len specifies the length of the buffer chPath points to.

	This is a function in debug versions, a macro in release versions.
	The function/macro calls is_absolute_path_unix_l () and is_absolute_path_win_l ().
*/
#ifdef DEBUG
	bool is_absolute_path_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_l(p, l)					\
		(												\
				is_absolute_path_unix_l (p, l)			\
			||	is_absolute_path_win_l (p, l)			\
		)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRISABSOLUTEPATH_H.
/****************************************************************************************

	File:		strisdotordotdot.h
	Why:		Checks for "." and ".." file/folder names.
	OS:			C99.
	Author:		Thomas
	Created:	2022-05-18

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-05-18	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRISDOTORDOTDOT_H
#define STRISDOTORDOTDOT_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	isDotOrDotDotW

	Returns true if the path wcPath points to is "." or "..", false otherwise.
*/
#ifdef OS_IS_WINDOWS
	bool isDotOrDotDotW (wchar_t *wcPath);
#endif

/*
	isDotOrDotDotU8

	UTF-8 version of isDotOrDotDotW (). Returns true if the path cPath points to
	is "." or "..", false otherwise.
*/
bool isDotOrDotDotU8 (char *cPath);

EXTERN_C_END

#endif														// Of #ifndef STRISDOTORDOTDOT_H.
/****************************************************************************************

	File		struri.h
	Why:		Helpers for URIs.
	OS:			C99
	Created:	2025-01-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-06	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRURI_H
#define STRURI_H

#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../pre/externC.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

EXTERN_C_BEGIN

/*
	uri_encode_str

	Encodes the source string str suitable for URIs. The parameter len specifies the length
	of the buffer str points to. If len is USE_STRLEN, the function obtains its length via a
	call to strlen ().

	The function returns the amounts of characters written to szURIencoded, excluding the
	terminating NUL. If szURIencoded is NULL, the functions returns the amount of characters
	(octets) required to store the encoded string, including the terminating NUL.

	The maximum buffer required to store str as a URI encoded string is 3 times the length of
	str (plus NUL terminator).
*/
size_t uri_encode_str (char *szURIencoded, const char *str, size_t len)
;

EXTERN_C_END

#endif														// Of #ifndef STRURI_H.
/****************************************************************************************

	File:		strmembuf.h
	Why:		String helper functions for SMEMBUF structures.
	OS:			C99
	Author:		Thomas
	Created:	2023-05-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-25	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef STRMEMBUF_H
#define STRMEMBUF_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./membuf.h"
	#else
		#include "./../mem/membuf.h"
	#endif

#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

/*
	SMEMBUFfromStr
	
	Duplicates str and fills the SMEMBUF structure pmb points to accordingly.
	If len is (size_t) -1, the function strlen () is used to obtain the length of str.
	The macro USE_STRLEN is defined as ((size_t) -1).
	The buffer the function allocates is len + reserve octets (bytes).
	The string in the buffer is always NUL-terminated.

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, which is len on success, or 0 when the heap allocation fails. The NUL
	terminator the function always writes is not included in the return value.
*/
size_t SMEMBUFfromStrReserveBytes (SMEMBUF *pmb, const char *str, size_t len, size_t reserve)
;

/*
	SMEMBUFfromStr

	Duplicates str and fills the SMEMBUF structure pmb points to accordingly.
	If len is USE_STRLEN the function calls strlen () to obtain the string's length.
	A NUL terminator is written at the end of the buffer.

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes, which is len on success,
	or 0 when the heap allocation fails.
*/
size_t SMEMBUFfromStr (SMEMBUF *pmb, const char *str, size_t len);

/*
	SMEMBUFstrFromUINT64
	
	Converts the value of ui to a string and stores the result in the buffer of pmb.
	The string is NUL-terminated.
	
	The function returns the amount of octets/bytes written to the buffer of the SMEMBUF
	structure, not counting the NUL-terminator.
*/
size_t SMEMBUFstrFromUINT64 (SMEMBUF *pmb, uint64_t ui)
;

EXTERN_C_END

#endif // STRMEMBUF_H
/****************************************************************************************

	File:		strwildcards.h
	Why:		Wildcard functions
	OS:			C99.
	Author:		Thomas
	Created:	2022-03-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-21	Thomas			Created.

****************************************************************************************/

#ifndef STRWILDCARDS_H
#define STRWILDCARDS_H

#include <stdbool.h>
#include <inttypes.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

/*
	Test function in debug versions only (default).
*/
#ifdef DEBUG
	#ifndef STRWILDCARDS_BUILD_TEST_FNCT
	#define STRWILDCARDS_BUILD_TEST_FNCT
	#endif
#endif

EXTERN_C_BEGIN

/*
	wildCardFileName
	
	Obtains the last part of a path if it contains wildcard characters.
	
	The function returns the filename, preceeded by a directory separator, of a path that
	contains wildcard characters and optionally, with parameter plen, its length. If no
	wildcard filename can be found, the function returns NULL. If the function returns
	NULL, and plen is not NULL, the address plen points to is set to 0.
	
	Examples:
	
	ccPath					returns		plen
	"C:\*.*"				"\*.*"		4
	"C:\test\*.tx?"			"\*.tx?"	6
*/
const char *wildCardFileName (size_t *plen, const char *ccPath)
;

/*
	lenPathWithoutWildcardFileName
	
	Returns the length of the path that ends with a wildcard filename, including the
	directory separator.
	
	ccPath					returns
	"C:\*.*"				3
	"C:\test\*.tx?"			8
	"C:*.*"					2
	"C:\test"				7			There are no wildcards.
*/
size_t lenPathWithoutWildcardFileName (const char *ccPath)
;

/*
	globMatch

	The function compares ccStri with length lnStri against the glob pattern (a string
	that can contain wildcard characters) ccGlob with length lnGlob. It is not a replacement
	for fnmatch () (https://www.man7.org/linux/man-pages/man3/fnmatch.3.html) and does
	not support any type of regular expression. It is a simple helper function that filters
	for a file mask when enumerating the contents of a directory.

	The string parameter ccStri is not meant to contain wildcard characters. The string
	parameter ccGlob can contain wildard characters.

	The length arguments lnStri and lnGlob can have the value USE_STRLEN, which is (size_t)
	-1, in which case the length in question is obtained via a call to strlen ().

	Both, ccStri and ccGlob, can contain NUL characters if lnStri and lnGlob are provided,
	i.e. are not USE_STRLEN.

	Unless a length is USE_STRLEN, the function does not read from the buffers beyond their
	length parameters. This means that if a length value is 0 nothing will ever be read from
	the string buffer. In the examples below the buffer in these cases is shown as "" but
	could as well be NULL or any other arbitrary value.

	The function returns true if ccStri matches the pattern ccGlob points to, false if not.

	If both lengths are 0, the function treats this as a match and returns true. If lnStri
	is 0 but lnGlob is not, the function in this case assumes that a match is impossible and
	returns false. If lnGlob is 0, this is treated as a match against anything, and the
	function returns true.

	Match rules for the glob pattern ccGlob:
	- A single question mark ("?") matches a single octet in ccStri.
	- An asterisk ("*") matches zero or more octets but not path separators ("/" or "\").
	- Two or more asterisks ("**", "***", "****", etc.) match zero or more octets including
		path separators ("/" or "\").
	- The path separators (forward and backward, "/" and "\") are treated as equal.
	- A question mark ("?") after two or more asterisks ("**", "***", "****", etc.) never
		matches because the asterisks will have consumed the string entirely.
	
	The function treats forward slashes and backslashes as being identical characters.

	ccStri		lnStri		ccGlob		lnGlob			return
	""			0			""			0				true
	"a"			1			""			0				true
	"a"			1			"a"			1				true
	"a/b/c"		5			"a\*"		3				false
	"a\b\c"		5			"a\*\*"		5				true
	"/"			1			"\"			1				true
	"/home/usr" USE_STRLEN	"\*?usr"	6				true

	See function strwildcards_test_function () for a more complete list of expectations.
*/
bool globMatch (const char *ccStri, size_t lnStri, const char *ccGlob, size_t lnGlob)
;

/*
	strwildcards_test_function

	Test function for the module.
*/
#ifdef STRWILDCARDS_BUILD_TEST_FNCT
	bool strwildcards_test_function (void);
#else
	#define strwildcards_test_function() true
#endif

EXTERN_C_END

#endif														// Of #ifndef STRWILDCARDS_H.
/****************************************************************************************

	File:		ubfcharscountsandchecks.h
	Why:		Character counting and check routines
	OS:			C99
	Author:		Thomas
	Created:	2020-08-31
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-08-31	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef UBFCHARSCOUNTSANDCHECKS
#define UBFCHARSCOUNTSANDCHECKS

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

/*
	The defintion for unknown string lengths. Functions taking this value for a length
	call strlen () to obtain the correct length.
*/
#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif
#ifndef SUBF_STRING_UNKNOWN_LENGTH
#define SUBF_STRING_UNKNOWN_LENGTH			USE_STRLEN
#endif
#ifndef SUBF_STRING_LENGTH_UNKNOWN
#define SUBF_STRING_LENGTH_UNKNOWN			USE_STRLEN
#endif
#ifndef SUBF_STRING_USE_STRLEN
#define SUBF_STRING_USE_STRLEN				USE_STRLEN
#endif

EXTERN_C_BEGIN

/*
	ubf_is_printable_ASCII

	Returns true if the value of c is greater than 0x1F and lower than 0x7F.
	A character counts as printable if it is within the range from SPC (20h, 32d) to '~'
	(7Eh, 126d), in which case the function returns true. The function returns false if
	the octet in C is outside this range.
*/
#ifdef DEBUG
	bool ubf_is_printable_ASCII (char c);
#else
	// From SPC (20h, 32d) to '~' (7Eh, 126d).
	#define ubf_is_printable_ASCII(c)					\
		((unsigned char) c > 0x1F && (unsigned char) c < 0x7F)
#endif

/*
	ubf_is_letter
	
	Returns true if the character in c is >= 'A' and <= 'Z' or >= 'a' and <= 'z',
	false otherwise. The function is identical to the standard C function isalpha (),
	which is defined as ubf_isalpha () in platform.h.
*/
#ifdef DEBUG
	bool ubf_is_letter (char c);
#else
	#define ubf_is_letter(c)	ubf_isalpha(c)
#endif

/*
	ubf_is_letter_until
	
	Returns a pointer that points after the first occurrance of c in ch, provided that all
	characters before this first occurrance are letters, determined by invokations of
	ubf_is_letter () for each character.
	
	The function returns NULL if the string in c contains anything but letters or if c
	could not be found.
*/
char *ubf_is_letter_until (char *ch, char c);

/*
	ubf_is_special
	
	Macro that evaluates to TRUE if the character c is not a letter and not a numerical
	digit. In other words, it evaluates to TRUE if the character c is a special character.
*/
#define ubf_is_special(c)								\
	(													\
			!ubf_is_letter	(c)							\
		&&	!ubf_isdigit	(c)							\
	)

/*
	isWhiteSpace

	Returns true if c is white space. CR, LF, and FF do not count as white space.
*/
#ifdef DEBUG
	bool isWhiteSpace (char c);
#else
	#define isWhiteSpace(c)								\
		(			UBF_SPC			== (c)				\
				||	UBF_TAB			== (c)				\
				||	UBF_VT			== (c)				\
		)
#endif

/*
	isDirectorySeparator
	isDirSep

	Evaluates to true if c is a directory separator, which can be either a forward
	or a backward slash.
*/
#ifdef DEBUG
	bool isDirectorySeparator (char c);
#else
	#define isDirectorySeparator(c)						\
		('/' == (c) || '\\' == (c))
#endif
#define isDirSep(c)			isDirectorySeparator (c)

/*
	isWrongDirectorySeparator
	isWrongDirSep
	
	Evaluates to true if c is the wrong directory separator. The wrong directory separator
	on Windows systems is the forward slash ("/"), on POSIX systems the backslash ("\").
*/
#ifdef DEBUG
	bool isWrongDirectorySeparator (char c);
#else
	#define isWrongDirectorySeparator(c)				\
		(UBF_WRONG_DIR_SEP == c)
#endif
#define isWrongDirSep(c)	isWrongDirectorySeparator (c)

/*
	ubf_count_numerical_digits
	
	Returns the amount of numerical digits (between '0' and '9') within the character string
	cc points to. The string cc points to is required to be NUL-terminated.
*/
size_t ubf_count_numerical_digits (const char *cc);

/*
	ubf_count_starts_with_numerical_digits_up_to
	
	Returns the amount of numerical digits (between '0' and '9') the character string
	cc points starts with, up to len characters/octets.
*/
size_t ubf_count_starts_with_numerical_digits_up_to (const char *cc, size_t len);

/*
	ubf_count_special_characters
	
	Returns the amount of special characters in the string cc points to. Special characters
	for this function are characters that are neither upper or lower case letters nor numerical
	digits.
*/
size_t ubf_count_special_characters (const char *cc);

/*
	ubf_count_char

	Counts how many times c occurs in cc and returns this number.
*/
size_t ubf_count_char (const char *cc, char c);

/*
	ubf_obtain_strlen
	STRLENSZ

	Returns the length of the NUL-terminated or non-NUL-terminated string sz.

	- If sz is NULL, the function returns 0.
	- If providedLength is (size_t) -1, the function returns strlen (sz). This requires sz to
		be NUL-terminated.
	- For any other value of providedLength, the function or macro returns providedLength.
		This should be the length of sz without the NUL-terminator, as would be obtained
		via strlen (sz) if sz was NUL-terminated.
*/
#ifdef DEBUG
	size_t ubf_obtain_strlen (const char *sz, size_t providedLength);
#else
	#define ubf_obtain_strlen(sz, len)					\
		(sz) ? (USE_STRLEN == (len) ? strlen (sz) : (len)) : 0
#endif
#define STRLENSZ(s, l)	ubf_obtain_strlen (s, l)

EXTERN_C_END

#endif															// Of UBFCHARSCOUNTSANDCHECKS.
/****************************************************************************************

	File:		cunilogstructs.h
	Why:		Structures for cunilog.
	OS:			C99.
	Author:		Thomas
	Created:	2022-10-05

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-10-05	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef CUNILOGSTRUCTS_H
#define CUNILOGSTRUCTS_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./SingleBits.h"
		#include "./ubf_times.h"
		#include "./membuf.h"
		#include "./bulkmalloc.h"
		#include "./VectorC.h"
		#include "./platform.h"
		#include "./strnewline.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/SingleBits.h"
		#include "./../datetime/ubf_times.h"
		#include "./../mem/membuf.h"
		#include "./../mem/bulkmalloc.h"
		#include "./../mem/VectorC.h"
		#include "./../pre/platform.h"
		#include "./../string/strnewline.h"
	#endif

#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
//#define CUNILOG_BUILD_SINGLE_THREADED_ONLY
#endif

#ifdef OS_IS_WINDOWS
	#include <Windows.h>
#else
	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		#include <semaphore.h>
		#include <pthread.h>
	#endif
#endif

/*
	Build options.

	CUNILOG_BUILD_SINGLE_THREADED_ONLY			Builds for a single-threaded application only.
												Code for other types than unilogSingleThreaded
												won't be built.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef CUNILOG_BUILD_MULTI_THREADED
	#error Either CUNILOG_BUILD_SINGLE_THREADED_ONLY or CUNILOG_BUILD_MULTI_THREADED can be defined but not both.
	#endif
	#ifdef CUNILOG_BUILD_MULTI_PROCESSES
	#error Only CUNILOG_BUILD_SINGLE_THREADED_ONLY or UNILOG_BUILD_MULTI_PROCESSES can be defined but not both.
	#endif
#endif
/*
	Currently not planned.

#ifdef CUNILOG_BUILD_MULTI_THREADED
	#ifdef CUNILOG_BUILD_MULTI_PROCESSES
	#error Only CUNILOG_BUILD_MULTI_THREADED or CUNILOG_BUILD_MULTI_PROCESSES can be defined but not both.
	#endif
#endif
#ifdef CUNILOG_BUILD_MULTI_PROCESSES
#endif
*/

BEGIN_C_DECLS

/*
	The constants for the log file extension. We got this in UTF-8
	(szCunilogLogFileNameExtension) and Windows UTF-16 (wcCunilogLogFileNameExtension).
	The constant lenCunilogLogFileNameExtension is the length in characters (not octets!).
*/
extern const char		*szCunilogLogFileNameExtension;			// ".log"
extern const wchar_t	*wcCunilogLogFileNameExtension;			// ".log"
extern const size_t		lenCunilogLogFileNameExtension;			// ".log"
extern const size_t		sizCunilogLogFileNameExtension;

/*
	enum unilogtype

	Specifies the application type of a cunilog target and how processing events is
	protected. These values are valid for a single target.
	Applications however can in theory work with an arbitrary number of targets, even if
	the targets are configured differently.


	cunilogSingleThreaded

	Only a single thread from one instance of the current application can safely write out
	logging information. Cunilog does not apply any concurrency protection.
	Writing logging information from more than a single thread, another instance of the
	same application, or from a different application is not supported and resulta in data
	corruption and application crashes. In a best case it may only lead to unusable
	logging information.

	Every logging function blocks as it executes the list of processors before returning.


	cunilogSingleThreadedSeparateLoggingThread

	Identical to cunilogSingleThreaded but the application must be built with multi-threading
	support. The process of writing out logging information (i.e. executing the list of
	processors) takes place in a separate thread.
	Calling logging functions from more than a single thread, another instance of the
	same application, or from a different application is not supported and results in
	data corruption and application crashes. In a best case it may only lead to unusable
	logging information.
	
	However, due to how this is currently implemented, some of these restrictions do not apply
	right now because cunilogSingleThreadedSeparateLoggingThread is actually identical to
	unilogMultiThreadedSeparateLoggingThread. Since this might and most likely will change in
	future versions of the software, use cunilogMultiThreadedSeparateLoggingThread to be safe.


	cunilogMultiThreaded

	Multiple threads from a single instance of the current application can safely write out
	logging information. Cunilog provides necessary concurrency protection for this case but
	does not protect logging information from being overwritten/destroyed by other processes.
	Any logging function called from any thread blocks as it works its way through the list of
	processors before releasing its lock and returning.


	cunilogMultiThreadedSeparateLoggingThread

	Identical to cunilogMultiThreaded but the process of writing out logging information (i.e.
	executing the list of processors) takes place in its own thread. Logging functions do
	not block. This is the preferred mode for most multi-threaded applications.


	cunilogMultiProcesses

	Logging information is fully protected and can be written from different threads as well
	as from different processes.
*/
enum cunilogtype
{
		cunilogSingleThreaded
	,	cunilogSingleThreadedSeparateLoggingThread
	,	cunilogMultiThreaded
	,	cunilogMultiThreadedSeparateLoggingThread
	,	cunilogMultiProcesses
	// Do not add anything below this line.
	,	cunilogTypeAmountEnumValues								// Used for table sizes.
	// Do not add anything below unilogTypeAmountEnumValues.
};

enum cunilogpostfix
{
		cunilogPostfixNone
	,	cunilogPostfixMinute
	,	cunilogPostfixMinuteT
	,	cunilogPostfixHour
	,	cunilogPostfixHourT
	,	cunilogPostfixDay
	,	cunilogPostfixDefault = cunilogPostfixDay
	,	cunilogPostfixWeek
	,	cunilogPostfixMonth
	,	cunilogPostfixYear
	// Do not add anything below this line.
	,	cunilogPostfixAmountEnumValues						// Used for table sizes.
	// Do not add anything below unilogRotationAmountEnumValues.
};

/*
	The possible processors.
*/
enum cunilogprocesstask
{
		cunilogProcessNoOperation							// Does nothing.
	,	cunilogProcessEchoToConsole							// Echoes to console.
	,	cunilogProcessUpdateLogFileName						// Updates full path to logfile.
	,	cunilogProcessWriteToLogFile						// Writes to logfile.
	,	cunilogProcessFlushLogFile							// Flushes the logfile.
	,	cunilogProcessRotateLogfiles						// Rotates logfiles.
	,	cunilogProcessCustomProcessor						// An external/custom processor.
	// Do not add anything below this line.
	,	cunilogProcessAmountEnumValues						// Used for table sizes.
	// Do not add anything below unilogRotationAmountEnumValues.
};

enum cunilogprocessfrequency
{
		cunilogProcessAppliesTo_nEvents						// Threshold is incremented for
															//	each event.
	,	cunilogProcessAppliesTo_nOctets						// Threshold counts the amount of
															//	octets logged.
	,	cunilogProcessAppliesTo_nAlways						// Threshold does not apply; always
															//	processed.
	,	cunilogProcessAppliesTo_SecondChanged				// Processed whenever the second
															//	changes.
	,	cunilogProcessAppliesTo_MinuteChanged				// Processed whenever the minute
															//	changes.
	,	cunilogProcessAppliesTo_HourChanged					// Processed whenever the hour
															//	changes.
	,	cunilogProcessAppliesTo_DayChanged					// Processed whenever the day
															//	changes.
	,	cunilogProcessAppliesTo_WeekChanged					// Processed whenever the week
															//	changes.
	,	cunilogProcessAppliesTo_MonthChanged				// Processed whenever the month
															//	changes.
	,	cunilogProcessAppliesTo_YearChanged					// Processed whenever the year
															//	changes.
	,	cunilogProcessAppliesTo_Auto						// Picks frequency automatically.
};

typedef struct scunilogtarget SCUNILOGTARGET;
typedef struct cunilog_processor
{
	/*
	SCUNILOGTARGET				*pSCUNILOGTARGET;			// Pointer to the target the
															//	processor belongs to.
	*/
	enum cunilogprocesstask			task;					// What to apply.
	enum cunilogprocessfrequency	freq;					// When to apply
															//	(frequency/theshold type).

	// Trigger threshold and its current value.
	uint64_t						thr;					// Required value of cur before this
															//	processor is applied/run.
	uint64_t						cur;					// The current counter value.

	void							*pData;					// Pointer to processor-specific data.
	uint64_t						uiOpts;					// Option flags. See OPT_CUNPROC_
															//	definitions below.
} CUNILOG_PROCESSOR;

/*
	Option flags for the uiOpts member of a CUNILOG_PROCESSOR structure.
*/
#define OPT_CUNPROC_NONE				(0)
#define OPT_CUNPROC_FORCE_NEXT			SINGLEBIT64 (0)		// Carry on with the next processor
															//	even if this one has not been
															//	processed.
#define OPT_CUNPROC_AT_STARTUP			SINGLEBIT64 (1)		// Executes the processor on startup
															//	by ignoring cunilogprocesstype.
															//	The flag is then cleared.
#define OPT_CUNPROC_ALLOCATED			SINGLEBIT64 (2)		// This processor has been allocated
															//	on the heap and needs to be freed.
#define OPT_CUNPROC_DATA_ALLOCATED		SINGLEBIT64	(3)		// The pData member has been allocated
															//	on the heap and needs to be freed.

/*
	Macros for some flags.
*/
#define optCunProcHasOPT_CUNPROC_AT_STARTUP(v)			\
	((v) & OPT_CUNPROC_AT_STARTUP)
#define optCunProcClrOPT_CUNPROC_AT_STARTUP(v)			\
	((v) &= ~ OPT_CUNPROC_AT_STARTUP)

/*
	A pData structure for a unilogProcessWriteToLogFile or a unilogProcessFlushLogFile processor.
*/
typedef struct cunilog_logfile
{
	#ifdef OS_IS_WINDOWS
		HANDLE			hLogFile;
	#else
		FILE			*fLogFile;
	#endif
} CUNILOG_LOGFILE;

enum cunilogrotationtask
{
		cunilogrotationtask_None							// Ignored. No operation.
	,	cunilogrotationtask_FScompressLogfiles				// Compress logfiles with the help
															//	of the file system.
	,	cunilogrotationtask_MoveToRecycleBinLogfiles
	,	cunilogrotationtask_DeleteLogfiles
};

/*
	A pData structure for a unilogProcessRotateLogfiles processor.
*/
typedef struct cunilog_rotation_data
{
	enum cunilogrotationtask	tsk;						// The task to carry out.
	uint64_t					nIgnore;					// Amount of files/objects/artefacts
															//	to ignore.
	uint64_t					nCnt;						// Counter for nIgnore.
	uint64_t					nMaxToRotate;				// Don't rotate more than this.
															//	Ignored when 0.

	// Source and destiantion path names. Probably not required, at least with NTFS compression.
	SMEMBUF						mbSrcMask;					// Search mask. Only used when
															//	CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK
															//	set. See option flags below.
	SMEMBUF						mbDstFile;					// Name of file to rotate (destination
															//	file name). Only used when
															//	CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE
															//	set. See option flags below.
	uint64_t					uiFlgs;						// Option flags. See below.
} CUNILOG_ROTATION_DATA;

/*
	CUNILOG_ROTATION_DATA option flags.
*/
#define CUNILOG_ROTATOR_FLAG_NONE							(0)

// Used by some rotators to distinguish if they need further initialisation.
#define CUNILOG_ROTATOR_FLAG_INITIALISED		SINGLEBIT64 (0)

// The rotator makes use of the mbSrcMask member. Without this flag, the rotator uses the
//	member mbLogFileMask of the SCUNILOGTARGET structure.
#define CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK		SINGLEBIT64 (1)

// The rotator makes use of the mbDstFile member. Without this flag, the rotator uses the
//	member mbFilToRotate of the SCUNILOGTARGET structure
#define CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE		SINGLEBIT64 (2)

/*
	Macros for some checking, setting, and clearing some of the flags above.
*/
#define cunilogHasRotatorFlag_USE_MBSRCMASK(pt)			\
	((pt)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogSetRotatorFlag_USE_MBSRCMASK(pt)			\
	((pt)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogClrRotatorFlag_USE_MBSRCMASK(pt)			\
	((pt)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)

#define cunilogHasRotatorFlag_USE_MBDSTFILE(pt)			\
	((pt)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogSetRotatorFlag_USE_MBDSTFILE(pt)			\
	((pt)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogClrRotatorFlag_USE_MBDSTFILE(pt)			\
	((pt)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	typedef struct cunilog_locker
	{
		#ifdef OS_IS_WINDOWS
			CRITICAL_SECTION	cs;
		#else
			pthread_mutex_t		mt;
		#endif
		#ifdef DEBUG
			bool				bInitialised;
		#endif
	} CUNILOG_LOCKER;

	typedef struct cunilog_semaphore
	{
		#ifdef OS_IS_WINDOWS
			HANDLE				hSemaphore;
		#else
			sem_t				tSemaphore;
		#endif
	} CUNILOG_SEMAPHORE;

	typedef struct cunilog_thread
	{
		#ifdef OS_IS_WINDOWS
			HANDLE				hThread;
		#else
			pthread_t			tThread;
		#endif
	} CUNILOG_THREAD;

	typedef struct scunilogevent SCUNILOGEVENT;
	typedef struct cunilog_queue_base
	{
		SCUNILOGEVENT			*first;						// A *SCUNILOGEVENT.
		SCUNILOGEVENT			*last;						// A *SCUNILOGEVENT.
		size_t					num;						// Current amount of queue
															//	elements.
	} CUNILOG_QUEUE_BASE;
#endif

/*
	Textual representations of date/timestamp formats for an event/event line.
	The default is ""YYYY-MM-DD HH:MI:SS.000+01:00", followed by a space character.
	The value unilogEvtTS_ISO8601T follows the ISO 8601 specification by separating
	date and time with a 'T'.

	The value cunilogEvtTS_ISO8601_3spc adds 3 spaces instead of one, and so does the
	value cunilogEvtTS_ISO8601T_3spc but with a 'T' between date and time.
*/
enum cunilogeventTSformat
{
		cunilogEvtTS_ISO8601								// "YYYY-MM-DD HH:MI:SS.000+01:00 "
	,	cunilogEvtTS_Default		= cunilogEvtTS_ISO8601
	,	cunilogEvtTS_ISO8601T								// "YYYY-MM-DDTHH:MI:SS.000+01:00 "
	,	cunilogEvtTS_ISO8601_3spc							// "YYYY-MM-DD HH:MI:SS.000+01:00   "
	,	cunilogEvtTS_ISO8601T_3spc							// "YYYY-MM-DDTHH:MI:SS.000+01:00   "
	// Do not add anything below this line.
	,	cunilogEvtTS_AmountEnumValues						// Used for table sizes.
	// Do not add anything below unilogRotationAmountEnumValues.
};

enum cunilogRunProcessorsOnStartup
{
	cunilogRunProcessorsOnStartup,
	cunilogDontRunProcessorsOnStartup
};
typedef enum cunilogRunProcessorsOnStartup runProcessorsOnStartup;

/*
	SCUNILOGDUMP

	Holds the parameter structures for binary/octal/decimal/hex dumps.
*/
typedef struct scunilogdump
{
	void		*dump_prs;									// Pointer to a SHEX_DUMP_SAN structure.
	void		*dump_sns;									// Pointer to a SHEX_DUMP_SAN structure.
	SMEMBUF		mbDumpHeader;
	size_t		lnDumpHeader;
} SCUNILOGDUMP;

/*
	Structure for the vector that holds the filenames.
	A single char * would probably do if no length information is required.
*/
typedef struct cunilog_fls
{
	char	*chFilename;
	size_t	stFilename;
} CUNILOG_FLS;
typedef vec_t(CUNILOG_FLS) vec_cunilog_fls;

/*
	Base folder for a relative path or path if no log path at all is given.

	These are the possible enumeration values of the parameter relLogPath of the
	SCUNILOGTARGET initialisation functions.


	cunilogLogPath_relativeToExecutable
	
	If szLogPath is a relative path, the path is assumed to be relative to the path of
	the executable file. If szLogPath is NULL, the path of the executable file is used.


	cunilogLogPath_relativeToCurrentDir

	If szLogPath is a relative path, the path is assumed to be relative to the current
	working directory. If szLogPath is NULL, the current working directory is used.
	The current working directory is obtained by the SCUNILOGTARGET initialisation functions
	and stays constant during the lifetime of this SCUNILOGTARGET. It is therefore safe for
	the application to change this directory any time after the initialisation function
	returned. Or, an application could set the current working directory to the desired
	szLogPath, call an SCUNILOGTARGET initialisation function with szLogPath set to NULL.


	cunilogLogPath_relativeToHomeDir

	If szLogPath is a relative path, the path is assumed to be relative to the current user's
	home folder. If szPath is NULL, the user's home directory is used.
*/
enum cunilogRelLogPath
{
	cunilogLogPath_relativeToExecutable,
	cunilogLogPath_relativeToCurrentDir,
	cunilogLogPath_relativeToHomeDir
};
typedef enum cunilogRelLogPath enCunilogRelLogPath;

/*
	Structure to leave some information for the next processor.
*/
typedef struct scunilognpi
{
	SMEMBUF							smbRotMask;				// File search mask/glob pattern the
															//	next processor should use to
															//	enumerate files. Only required for
															//	rotators.
	size_t							lenRotMask;				// The length, excluding NUL, of
															//	smbRotMask; If this is 0,
															//	smbRotMask is unused/uninitialised.
	uint64_t						nIgnoredTotal;			// Ignored so far. Only if lenRotMask
															//	is 0.
	vec_cunilog_fls					*pNextVecCunilogFls;	// The next file to process. If this
															//	is NULL, the next rotator
															//	needs to start from scratch.
} SCUNILOGNPI;

/*
	SUNILOGTARGET

	The base config structure for using cunilog. Do not alter any of its members directly.
	Always use the provided functions to alter its members.
*/
typedef struct scunilogtarget
{
	enum cunilogtype				culogType;
	enum cunilogpostfix				culogPostfix;
	uint64_t						uiOpts;
	SMEMBUF							mbLogPath;				// The logging folder/path to logfiles.
															//	On Windows, its last character is a
															//	backslash. On POSIX, its last character
															//	is a forward slash. It is not NUL-
															//	terminated.
	size_t							lnLogPath;				// Its length excl. NUL terminator.
	SMEMBUF							mbAppName;				// Plain application name. Not NUL-terminated.
	size_t							lnAppName;				// Its length.
	#ifdef PLATFORM_IS_POSIX
		SMEMBUF						mbLogFold;				// The logging folder/path to logfiles.
															//	Same as mbLogPath but NUL-terminated
															//	and without slash at the end.
		size_t						lnLogFold;				// Its length exl. NUL terminator.
	#endif
	SMEMBUF							mbLogfileName;			// Path and name of current log file.
	char							*szDateTimeStamp;		// Points inside mbLogfileName.buf.pch.
	char							cPrevDateTimeStamp [LEN_ISO8601DATEHOURANDMINUTE];
	SMEMBUF							mbLogFileMask;			// The search mask for log files.
	#ifdef PLATFORM_IS_POSIX
		// Required for platforms that cannot return a directory listing with a search mask
		//	but return every file instead. The callback function then compares each returned
		//	filename with this mask/glob pattern.
		char						*szLogFileMask;			// Points inside mbLogFileMask to the
															//	application name plus stamp plus ".log".
		size_t						lnsLogFileMask;			// Its length.
	#endif
	SMEMBUF							mbFilToRotate;			// The file obtained by the cb function.
	SMEMBUF							mbLogEventLine;			// Buffer that holds the event line.
	size_t							lnLogEventLine;			// The current length of the event line.
	SCUNILOGNPI						scuNPI;					// Information for the next processor.
	CUNILOG_PROCESSOR				**cprocessors;
	unsigned int					nprocessors;

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		CUNILOG_LOCKER				cl;						// Locker for functions and event queue.
		CUNILOG_SEMAPHORE			sm;						// Semaphore for event queue.
		CUNILOG_QUEUE_BASE			qu;						// The actual event queue.
		CUNILOG_THREAD				th;						// The separate logging thread.

		size_t						nPendingNoRotEvts;		// Amount of currently pending non-
															//	rotation events.

		size_t						nPausedEvents;			// Amount of events queued because
															//	the logging thread is/was paused.
	#endif
	enum cunilogeventTSformat		unilogEvtTSformat;		// The format of an event timestamp.
	enum enLineEndings				unilogNewLine;
	SBULKMEM						sbm;					// Bulk memory block.
	vec_cunilog_fls					fls;					// The vector with str pointers to
															//	the files to rotate within sbm.
	SCUNILOGDUMP					*psdump;				// Holds the dump parameters.
} SCUNILOGTARGET;

/*
	The default initial size of an event line. Note that this is not the space for the text
	but rather the entire line, including timestamp etc. If you know in advance that your
	texts (including stamp etc) are going to be longer you may override this with a higher
	value to possibly save some initial heap reallocations.
*/
#ifndef CUNILOG_INITIAL_EVENTLINE_SIZE
#define CUNILOG_INITIAL_EVENTLINE_SIZE			(256)
#endif

/*
	Option flags for the uiOpts member of a SCUNILOGTARGET structure.
*/

// The initialiser.
#define CUNILOGTARGET_NO_FLAGS					(0)

// Event queue is shutting down or has shut down already.
//	This flags prevents further logging.
#define CUNILOGTARGET_SHUTDOWN					SINGLEBIT64 (0)

// Separate logging thread has shut down.
#define CUNILOGTARGET_HAS_SHUT_DOWN				SINGLEBIT64 (1)

// The structure has been allocated on the heap. This is for DoneSUNILOGTARGET ()
//	to deallocate it.
#define CUNILOGTARGET_ALLOCATED					SINGLEBIT64 (2)

// The filename of the log file has been allocated on the heap.
#define CUNILOGTARGET_LOGPATH_ALLOCATED			SINGLEBIT64 (3)

// The application name has been allocated on the heap.
#define CUNILOGTARGET_APPNAME_ALLOCATED			SINGLEBIT64 (4)

// The entire path plus name of the logfile has been allocated on the heap.
#define CUNILOGTARGET_LOGFILE_ALLOCATED			SINGLEBIT64 (5)

// The file mask.
#define CUNILOGTARGET_LOGF_MASK_ALLOCATED		SINGLEBIT64 (6)

// The (complete) filename of the file to rotate.
#define CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED	SINGLEBIT64 (7)

// The single event line.
#define CUNILOGTARGET_EVTLINE_ALLOCATED			SINGLEBIT64 (8)

// The array of pointers to processors.
#define CUNILOGTARGET_PROCESSORS_ALLOCATED		SINGLEBIT64 (9)

// Run all processors on startup, independent of their individual flags.
#define CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP	SINGLEBIT64 (10)

// The filesystem that holds the log files doesn't return filenames in
//	descending alphabetic order.
#define CUNILOGTARGET_FS_NEEDS_SORTING			SINGLEBIT64 (11)

// The separate logging thread, if one exists, is paused.
#define CUNILOGTARGET_PAUSED					SINGLEBIT64 (12)

// Debug versions ensure that one of the initialisation function has been called.
#ifdef DEBUG
	#define CUNILOGTARGET_INITIALISED			SINGLEBIT64 (13)
	#define cunilogSetTargetInitialised(pt)				\
			((pt)->uiOpts |= CUNILOGTARGET_INITIALISED)
	#define cunilogIsTargetInitialised(pt)				\
			((pt)->uiOpts & CUNILOGTARGET_INITIALISED)
#else
	#define cunilogSetTargetInitialised(pt)
	#define cunilogIsTargetInitialised(pt)
#endif

/*
	Macros for some flags.
*/
#define cunilogSetShutdownTarget(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_SHUTDOWN)
#define cunilogIsShutdownTarget(pt)						\
	((pt)->uiOpts & CUNILOGTARGET_SHUTDOWN)

#define cunilogSetTargetHasShutdown(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_HAS_SHUT_DOWN)
#define cunilogIsTargetHasShutdown(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_HAS_SHUT_DOWN)

#define cunilogSetTargetAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_ALLOCATED)
#define cunilogIsTargetAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_ALLOCATED)

#define cunilogSetLogPathAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED)
#define cunilogIsLogPathAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_LOGPATH_ALLOCATED)

#define cunilogSetAppNameAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_APPNAME_ALLOCATED)
#define cunilogIsAppNameAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_APPNAME_ALLOCATED)

#define cunilogSetLogFileAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_LOGFILE_ALLOCATED)
#define cunilogIsLogFileAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_LOGFILE_ALLOCATED)

#define cunilogSetLogFileMaskAllocated(pt)				\
	((pt)->uiOpts |= CUNILOGTARGET_LOGF_MASK_ALLOCATED)
#define cunilogIsLogFileMaskAllocated(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_LOGF_MASK_ALLOCATED)

#define cunilogSetFileToRotateAllocated(pt)				\
	((pt)->uiOpts |= CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)
#define cunilogIsFileToRotateAllocated(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)

#define cunilogSetEvtLineAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_EVTLINE_ALLOCATED)
#define cunilogIsEvtLineAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_EVTLINE_ALLOCATED)

#define cunilogSetProcessorsAllocated(pt)				\
	((pt)->uiOpts |= CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogClrProcessorsAllocated(pt)				\
	((pt)->uiOpts &= ~ CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogIsProcessorsAllocated(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_PROCESSORS_ALLOCATED)

#define cunilogHasRunAllProcessorsOnStartup(pt)			\
	((pt)->uiOpts & CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogClrRunAllProcessorsOnStartup(pt)			\
	((pt)->uiOpts &= ~ CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogSetRunAllProcessorsOnStartup(pt)			\
	((pt)->uiOpts |= CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)

#define cunilogIsFSneedsSorting(pt)						\
	((pt)->uiOpts & CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogClrFSneedsSorting(pt)					\
	((pt)->uiOpts &= ~ CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogSetFSneedsSorting(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_FS_NEEDS_SORTING)

#define cunilogIsPaused(pt)								\
	((pt)->uiOpts & CUNILOGTARGET_PAUSED)
#define cunilogClrPaused(pt)							\
	((pt)->uiOpts &= ~ CUNILOGTARGET_PAUSED)
#define cunilogSetPaused(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_PAUSED)



/*
	Event severities.

	If changed, please update the copy in the comments of cunilog.c too.
*/
enum cunilogeventseverity
{
		cunilogEvtSeverityNone									//  0
	,	cunilogEvtSeverityBlanks								//  1
	,	cunilogEvtSeverityEmergency								//	2
	,	cunilogEvtSeverityNotice								//	3
	,	cunilogEvtSeverityInfo									//  4
	,	cunilogEvtSeverityMessage								//  5
	,	cunilogEvtSeverityWarning								//  6
	,	cunilogEvtSeverityError									//  7
	,	cunilogEvtSeverityFail									//  8
	,	cunilogEvtSeverityCritical								//  9
	,	cunilogEvtSeverityFatal									// 10
	,	cunilogEvtSeverityDebug									// 11
	,	cunilogEvtSeverityTrace									// 12
	,	cunilogEvtSeverityDetail								// 13
	,	cunilogEvtSeverityVerbose = cunilogEvtSeverityDetail	// 13
	,	cunilogEvtSeverityIllegal								// 14
};
typedef enum cunilogeventseverity cueventseverity;

/*
	SCUNILOGEVENT

	A logging event structure.
*/
typedef struct scunilogevent
{
	SCUNILOGTARGET				*pSCUNILOGTARGET;			// The event's target/destination.
	uint64_t					uiOpts;						// Option flags.
	UBF_TIMESTAMP				stamp;						// Its date/timestamp.
	unsigned char				*szDataToLog;				// Data to log.
	size_t						lenDataToLog;				// Its length, not NUL-terminated.

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		struct scunilogevent	*next;
	#endif
	cueventseverity				evSeverity;
} SCUNILOGEVENT;

/*
	FillSCUNILOGEVENT

	Macro to fill a SCUNILOGEVENT structure. Note that the structure doesn't have a
	->next member if CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define FillSCUNILOGEVENT(pev, pt,					\
				opts, dts, sev, dat, len)				\
		(pev)->pSCUNILOGTARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->evSeverity				= sev;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len
#else
	#define FillSCUNILOGEVENT(pev, pt,					\
				opts, dts, sev, dat, len)				\
		(pev)->pSCUNILOGTARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->evSeverity				= sev;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len;			\
		(pev)->next						= NULL
#endif

/*
	Member uiOpts of a SCUNILOGEVENT structure.
*/

#define CUNILOGEVENT_NO_FLAGS			(0)

// The structure has been allocated on the heap. This is for DoneSUNILOGEVENT ()
//	to deallocate it.
#define CUNILOGEVENT_ALLOCATED			SINGLEBIT64 (0)

// The data has been allocated. This is also for DoneSUNILOGEVENT ().
#define CUNILOGEVENT_DATA_ALLOCATED		SINGLEBIT64 (1)

// Shuts down logging.
#define CUNILOGEVENT_SHUTDOWN			SINGLEBIT64 (2)

// Cancels outstanding events and shuts down logging.
// Unused/obsolete.
//#define CUNILOGEVENT_CANCEL				SINGLEBIT64 (3)

// The data is to be written out as a binary dump.
#define CUNILOGEVENT_AS_HEXDUMP			SINGLEBIT64 (4)

// Add fullstop automatically.
#define CUNILOGEVENT_AUTO_FULLSTOP		SINGLEBIT64 (5)

// No rotation for this event. This is very fast/quick logging.
//	It is also used for internal logging.
#define CUNILOGEVENT_NOROTATION			SINGLEBIT64 (6)

// Macros to set and check flags.
#define cunilogSetEventAllocated(pue)					\
	((pue)->uiOpts |= CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventAllocated(pue)					\
	((pue)->uiOpts & CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventDataAllocated(pue)				\
	((pue)->uiOpts & CUNILOGEVENT_DATA_ALLOCATED)
#define cunilogSetEventShutdown(pue)					\
	((pue)->uiOpts |= CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventShutdown(pue)						\
	((pue)->uiOpts & CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventCancel(pue)						\
	((pue)->uiOpts & CUNILOGEVENT_CANCEL)

#define cunilogSetEventHexdump(pue)						\
	((pue)->uiOpts |= CUNILOGEVENT_AS_HEXDUMP)
#define cunilogIsEventHexdump(pue)						\
	((pue)->uiOpts & CUNILOGEVENT_AS_HEXDUMP)
#define cunilogSetEventAutoFullstop(pue)				\
	((pue)->uiOpts |= CUNILOGEVENT_AUTO_FULLSTOP)
#define cunilogIsEventAutoFullstop(pue)					\
	((pue)->uiOpts & CUNILOGEVENT_AUTO_FULLSTOP)

#define cunilogHasEventNoRotation(pue)					\
	((pue)->uiOpts & CUNILOGEVENT_NOROTATION)
#define cunilogSetEventNoRotation(pue)					\
	((pue)->uiOpts |= CUNILOGEVENT_NOROTATION)

/*
	Return type of the separate logging thread.
*/
#ifdef OS_IS_WINDOWS
	#define SEPARATE_LOGGING_THREAD_RETURN_TYPE			\
			DWORD WINAPI
#else
	#define SEPARATE_LOGGING_THREAD_RETURN_TYPE			\
			void *
#endif

/*
	Return values of the separate logging thread.
*/
#ifdef OS_IS_WINDOWS
	#define SEPARATE_LOGGING_THREAD_RETURN_SUCCESS		\
			(EXIT_SUCCESS)
	#define SEPARATE_LOGGING_THREAD_RETURN_FAILURE		\
			(EXIT_FAILURE)
#else
	#define SEPARATE_LOGGING_THREAD_RETURN_SUCCESS		\
			((void *) EXIT_SUCCESS)
	#define SEPARATE_LOGGING_THREAD_RETURN_FAILURE		\
			((void *) EXIT_FAILURE)
#endif

/*
	Parameter structure for rotator processor.
*/
typedef struct cunilog_rotator_args
{
	CUNILOG_PROCESSOR		*cup;
	SCUNILOGEVENT			*pev;
	char					*nam;							// Name of file to rotate.
	size_t					siz;							// Its size, incl. NUL.
} CUNILOG_ROTATOR_ARGS;

/*
	A callback function of a custom processor.
*/
typedef void		(*pfCustProc) (CUNILOG_PROCESSOR *, SCUNILOGEVENT *);

/*
	A pData structure for a unilogProcessCustomProcessor (custom/external) processor.
*/
typedef struct cunilog_custprocess
{
	void			*pData;
	pfCustProc		procFnc;
} CUNILOG_CUSTPROCESS;

/*
	The priority levels of the separate logging thread.

	When changing this enum, please also update the comment in cunilog.c.
*/
enum enCunilogLogPriority
{
	cunilogPrioNormal,
	cunilogPrioBelowNormal,
	cunilogPrioLow,
	cunilogPrioIdle,
	// Do not insert enum values below this line.
	cunilogPrioInvalid
};
typedef enum enCunilogLogPriority	cunilogprio;

/*
	An element of the array with the files.
*/
typedef struct cunilogfilename
{
	const char	*szFilename;
	size_t		stLen;
} CUNILOGFILENAME;

END_C_DECLS

#endif														// Of #ifndef CUNILOGSTRUCTS_H.
/****************************************************************************************

	File:		cunilog.h
	Why:		Interface functions for cunilog.
	OS:			C99.
	Author:		Thomas
	Created:	2022-10-05

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-10-05	Thomas			Created.

****************************************************************************************/

/*
	1. Create a SCUNILOGTARGET structure and initialise it. Use either your own structure
		or create a new one with CreateNewSUNILOGTARGET () or InitOrCreateSUNILOGTARGET ().
		Or use the internal structure of this module with InitSUNILOGTARGETstatic () instead.
		The latter is most likely what you want.

	2. Use the logging functions repeatedly as you please. Depending on the member unilogType
		of the SCUNILOGTARGET structure, you might do this from a single or multiple
		threads.

	4. When not required anymore, probably just before the application exits, call
		ShutdownSCUNILOGTARGET () or ShutdownSCUNILOGTARGETstatic, depending on the structure
		you used. Call DoneSUNILOGTARGET () on the the SCUNILOGTARGET structure afterwards,
		or call DoneSUNILOGTARGETstatic () if the internal structure was used.

		Example for internal static structure:

		// Application start
		InitSUNILOGTARGETstatic (...);

		// Use the log...static () family of functions and macros for logging.
		logTextU8_static (...);

		// Just before the application exists shut down logging and deallocate its resources.
		ShutdownSCUNILOGTARGETstatic ();
		DoneSUNILOGTARGETstatic ();
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef CUNILOG_H
#define CUNILOG_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../pre/externC.h"
	#endif

	#include "./cunilogversion.h"
	#include "./cunilogstructs.h"

#endif

// To build the test functions.
#ifndef CUNILOG_BUILD_TEST_FNCTS
#define CUNILOG_BUILD_TEST_FNCTS
#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

// Failure return value for (size_t).
#ifndef CUNILOG_SIZE_ERROR
#define CUNILOG_SIZE_ERROR				((size_t) -1)
#endif

// Value of member nMaxToRotate of a CUNILOG_ROTATION_DATA structure to be obtained
//	during initialisation.
#ifndef CUNILOG_MAX_ROTATE_AUTO
#define CUNILOG_MAX_ROTATE_AUTO			(UINT64_MAX)
#endif

// Memory alignments. Use 16 octets/bytes for 64 bit platforms.
#if defined (_WIN64) || defined (__x86_64__)
	#define CUNILOG_DEFAULT_ALIGNMENT	(16)
#else
	#define CUNILOG_DEFAULT_ALIGNMENT	(8)
#endif

// Our standard size for error messages on the stack.
#define CUNILOG_STD_MSG_SIZE			(256)

// Our standard size for bulk memory allocations.
#define CUNILOG_STD_BULK_ALLOC_SIZE		(4096 - sizeof (SBULKMEMBLOCK))

// The size we're going to expand the vector containing the names of logfiles.
#define CUNILOG_STD_VECT_EXP_SIZE		(128)

// The stack/heap threshold for the ...sfmt type logging functions.
#ifndef CUNILOG_DEFAULT_SFMT_SIZE
#define CUNILOG_DEFAULT_SFMT_SIZE		(256)
#endif

// This seems to make sense.
#define requiresSCUNILOGTARGETseparateLoggingThread(p) hasSCUNILOGTARGETqueue (p)

// The mode for opening the current logfile.
#ifdef PLATFORM_IS_WINDOWS
	#define CUNILOG_DEFAULT_OPEN_MODE	(FILE_APPEND_DATA)
	/*
		pl->hLogFile = CreateFileU8	(
						szLogFileName, GENERIC_WRITE,
						FILE_SHARE_DELETE | FILE_SHARE_READ,
						NULL, OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
									);
	*/
#else
	#define CUNILOG_DEFAULT_OPEN_MODE	"a"
#endif

EXTERN_C_BEGIN

/*
	The pointer to the module's internal static SCUNILOGTARGET structure and a pointer to it.
	The _static versions of the logging functions operate on this structure.
*/
extern SCUNILOGTARGET *pSCUNILOGTARGETstatic;

/*
	Funcitons
*/

/*
	InitCUNILOG_PROCESSOR

	Function/macro to initialise a CUNILOG_PROCESSOR structure. The data (pData) member
	is set to NULL and the member uiOpts to OPT_CUNPROC_NONE, which means no option flags
	are set. The caller is responsible for setting those members to their desired values
	afterwards.
*/
#ifdef DEBUG
	void InitCUNILOG_PROCESSOR	(
			CUNILOG_PROCESSOR				*cup,
			enum cunilogprocesstask			task,
			enum cunilogprocessfrequency	freq,
			uint64_t						thrs
								)
	;
#else
	#define InitCUNILOG_PROCESSOR(cup, task,				\
									type, thrs)				\
		ubf_assert_non_NULL (cup);							\
		(cup)->task		= task;								\
		(cup)->freq		= freq;								\
		(cup)->thr		= thrs;								\
		(cup)->cur		= 0;								\
		(cup)->pData	= NULL;								\
		(cup)->uiOpts	= OPT_CUNPROC_NONE;
#endif

/*
	Table with the length of the rotational date/timestamp.
*/
extern size_t arrLengthTimeStampFromPostfix [cunilogPostfixAmountEnumValues];

/*
	lenDateTimeStampFromRotation
	
	Returns the length of the timestamp of the current rotation.
*/
#ifdef DEBUG
	size_t lenDateTimeStampFromPostfix (enum cunilogpostfix postfix);
#else
	#define lenDateTimeStampFromPostfix(pfx)			\
		(arrLengthTimeStampFromPostfix [(pfx)])
#endif

/*
	Table with the rotation wildcard masks.
*/
extern const char *arrPostfixWildcardMask [cunilogPostfixAmountEnumValues];

/*
	postfixMaskFromLogPostfix
	
	Returns a string representing a file name wildcard mask for rotation that can be used
	to search for files, for instance a rotation with a value of unilogEveryMinute returns
	"????-??-?? ??:??".
*/
#ifdef DEBUG
	const char *postfixMaskFromLogPostfix (enum cunilogpostfix postfix);
#else
	#define postfixMaskFromLogPostfix(pfx)			\
		(arrPostfixWildcardMask [pfx])
#endif

/*
	InitSCUNILOGTARGET

	Initialises an existing SCUNILOGTARGET structure.

	Parameters

	put					A pointer to an SCUNILOGTARGET structure that holds all required
						parameters. The function does not create a copy of this structure and
						therefore it must be available/accessible until DoneSUNILOGTARGET ()
						and ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () are called on
						it. In other words the structure is required to either be static or is
						created as an automatic structure in main ().
						The function InitSCUNILOGTARGETstatic () uses the module's internal static
						structure.

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify the
						base path if szLogPath is either relative or NULL. If szLogPath is relative,
						the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory),
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be NULL
						if no cunilog processors apart from the standard processors are required.
						If this parameter is not NULL, the function does not create a copy of
						this list and therefore must be available/accessible until
						DoneSUNILOGTARGET () and ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET () are called on it. In other words the list is
						required to either reside on the heap, static, or is created as
						automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either unilogRunProcessorsOnStartup or
						unilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to puz on success, NULL otherwise.
*/
SCUNILOGTARGET *InitSCUNILOGTARGET
(
	  SCUNILOGTARGET			*put				// Must not be NULL.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	CreateNewSCUNILOGTARGET

	Creates a new SCUNILOGTARGET structure on the heap and initialises it.

	Parameters

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify the
						base path if szLogPath is either relative or NULL. If szLogPath is relative,
						the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory),
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be NULL
						if no cunilog processors apart from the standard processors are required.
						If this parameter is not NULL, the function does not create a copy of
						this list and therefore must be available/accessible until
						DoneSUNILOGTARGET () and ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET () are called on it. In other words the list is
						required to either reside on the heap, is static, or is created as
						automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either unilogRunProcessorsOnStartup or
						unilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	For performance reasons and to simplify data handling, the function allocates a single memory
	block that holds enough space for the SCUNILOGTARGET structure as well as szLogPath and
	szAppName.

	If the function succeeds it returns a pointer to a valid SUNILOGTARGET structure.
	If the function fails, the return value is NULL.
*/
SCUNILOGTARGET *CreateNewSCUNILOGTARGET
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	InitOrCreateSCUNILOGTARGET

	Initialises an existing SCUNILOGTARGET structure or creates a new one on the heap.

	If put is NULL, the function calls CreateNewSCUNILOGTARGET () and returns a pointer
	to the newly allocated and initialised SCUNILOGTARGET structure.
	
	If put is not NULL, the function initialises it and returns put by calling
	InitSCUNILOGTARGET () on it. If put is not NULL, the function does not create a copy of
	this structure. The caller therefore must ensure that it is available/accessible until
	DoneSCUNILOGTARGET () and ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () are called
	on it, i.e. that the structure is either static or is created as an automatic structure
	in main ().

	If the cuProcessorList parameter is not NULL, the function does not create a copy of
	this list and therefore must be available/accessible until DoneSCUNILOGTARGET () and
	ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () are called on it. In other
	words the list is required to either reside on the heap, is static, or is created
	as automatic in main ().

	The function returns NULL if it fails.

	Call DoneSCUNILOGTARGET () when done with the structure, independent of whether it
	has been created on the heap or provided as the parameter psu.
*/
SCUNILOGTARGET *InitOrCreateSCUNILOGTARGET
(
	  SCUNILOGTARGET			*put				// If NULL, a new structure is allocated.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	InitSCUNILOGTARGETstatic
	
	Initialises the internal SCUNILOGTARGET structure. If the _static versions of the logging
	functions are used, an application must call this function before any of these functions
	are called.
	
	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify the
						base path if szLogPath is either relative or NULL. If szLogPath is relative,
						the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory),
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be NULL
						if no cunilog processors apart from the standard processors are required.
						If this parameter is not NULL, the function does not create a copy of
						this list and therefore must be available/accessible until
						DoneSUNILOGTARGET () and ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET () are called on it. In other words the list is
						required to either reside on the heap, is static, or is created as
						automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either unilogRunProcessorsOnStartup or
						unilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to the internal SCUNILOGTARGET cunilognewlinestructure upon success,
	NULL otherwise.

	Call DoneSCUNILOGTARGETstatic () to free the structures resources.
*/
SCUNILOGTARGET *InitSCUNILOGTARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelLogPath		relLogPath
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	DoneSCUNILOGTARGET

	Deallocates all resources of the SCUNILOGTARGET put points to. After a structure has been
	processed by this function, none of the logging functions can be called on it anymore, but
	it could however be re-used by initialising it again.

	Before calling this function, call ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET ()
	first to either process or discard it's event queue.

	The function always returns NULL.
*/
SCUNILOGTARGET *DoneSCUNILOGTARGET (SCUNILOGTARGET *put)
;

/*
	DoneSCUNILOGTARGETstatic
	
	Deallocates all resources of the internal static SCUNILOGTARGET structure by calling
	DoneSCUNILOGTARGET () on it.

	The function always returns NULL.
*/
SCUNILOGTARGET *DoneSCUNILOGTARGETstatic (void)
;

/*
	ShutdownSCUNILOGTARGET

	Blocks further logging by forcing all logging functions to return false. It then waits
	for the events of the current queue to be processed and returns after an existing separate
	logging thread has exited.

	Logging events that are produced by currently executing logging functions themselves are
	not blocked until the queue is empty. This means internal non-rotating events like
	"Deleting file..." etc. are still processed until none are left.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, meaning that only further logging is blocked and logging functions called
	afterwards return false.

	This function should be called just before DoneSCUNILOGTARGET ().
*/
void ShutdownSCUNILOGTARGET (SCUNILOGTARGET *put);

/*
	ShutdownSCUNILOGTARGETstatic

	Calls ShutdownSCUNILOGTARGET () on the internal static SUNILOGSTRUCT structure.
	This function should be called just before DoneSUNILOGTARGETstatic ();
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.
*/
void ShutdownSCUNILOGTARGETstatic (void);

/*
	CancelSCUNILOGTARGET

	Empties the logging queue for the SCUNILOGTARGET put without processing its events.
	The events currently in the queue are discarded. Logging functions called afterwards
	for this SCUNILOGTARGET structure fail and return false.

	The function waits for an existing separate logging thread to exit.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.
*/
void CancelSCUNILOGTARGET (SCUNILOGTARGET *put);

/*
	CancelSCUNILOGTARGETstatic

	Calls CancelSCUNILOGTARGET () on the internal static SUNILOGSTRUCT structure.
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.
*/
void CancelSCUNILOGTARGETstatic (void);

/*
	SetLogPrioritySCUNILOGTARGET

	Sets the priority of the separate logging thread that belongs to the specified
	SCUNILOGTARGET structure put points to.
	
	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file).
	Neither the table nor this function have been tested to ensure the approximations
	are accurate.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the SCUNILOGTARGET structure doesn't
	have a separate logging thread, the function returns true.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool SetLogPrioritySCUNILOGTARGET (SCUNILOGTARGET *put, cunilogprio prio)
	;
#else
	#define SetLogPrioritySCUNILOGTARGET(p, p)	(true)
#endif

/*
	SetLogPrioritySCUNILOGTARGETstatic

	Sets the priority of the separate logging thread that belongs to internal static
	SCUNILOGTARGET structure.

	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file).
	Neither the table nor this function have been tested to ensure the approximations
	are accurate.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the SCUNILOGTARGET structure doesn't
	have a separate logging thread, the function returns true.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool SetLogPrioritySCUNILOGTARGETstatic (cunilogprio prio)
	;
#else
	#define SetLogPrioritySCUNILOGTARGETstatic(p, p)	(true)
#endif

/*
	PauseLogSCUNILOGTARGET

	Pauses/suspends logging to the SCUNILOGTARGET structure put points to while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogSCUNILOGTARGET () to resume the separate logging thread.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
#else
	define PauseLogSCUNILOGTARGET(p)
#endif

/*
	PauseLogSCUNILOGTARGETstatic

	Pauses/suspends logging to the internal SCUNILOGTARGET structure while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogSCUNILOGTARGETstatic () to resume the separate logging thread again.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogSCUNILOGTARGETstatic (void)
	;
#else
	define PauseLogSCUNILOGTARGETstatic(p)
#endif

/*
	ResumeLogSCUNILOGTARGET

	Resumes logging to the SCUNILOGTARGET structure put points to after a call to
	PauseLogSCUNILOGTARGET () and triggers it for each queued event since
	PauseLogSCUNILOGTARGET () was called.

	The function returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogSCUNILOGTARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
#else
	define ResumeLogSCUNILOGTARGET (p)
#endif

/*
	ResumeLogSCUNILOGTARGETstatic

	Resumes logging to the internal SCUNILOGTARGET structure after a call to
	PauseLogSCUNILOGTARGET () and triggers it for each queued event since
	PauseLogSCUNILOGTARGET () was called.

	The function returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogSCUNILOGTARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogSCUNILOGTARGETstatic (void)
	;
#else
	define ResumeLogSCUNILOGTARGETstatic (p)
#endif

/*
	CreateSCUNILOGEVENTwithData

	Allocates a buffer that points to a new event structure SCUNILOGEVENT plus data, initialises
	it with the function parameters, and returns a pointer to the newly created and initialised
	structure and data buffer. The event is written out as binary data.

	Note that you can NOT use USE_STRLEN as the parameter siz.

	The function returns false if it fails.
*/
SCUNILOGEVENT *CreateSCUNILOGEVENTwithData	(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz
											)
;

/*
	CreateSCUNILOGEVENTwithText

	This is the text version of CreateSCUNILOGEVENTwithData (). If the string ccText is
	NUL-terminated a value of USE_STRLEN for len can be used.
*/
SCUNILOGEVENT *CreateSCUNILOGEVENTwithText	(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;

/*
	DoneSUNILOGEVENT

	Destroys an SUNILOGEVENT structure including all its resources.

	The function always returns NULL.
*/
SCUNILOGEVENT *DoneSUNILOGEVENT (SCUNILOGEVENT *pev)
;

/*
	Logging functions.
	==================
*/

/*
	logEv

	Writes out the event pev points to to the logging target put points to. The function
	only sets the pSCUNILOGTARGET member of the SCUNILOGEVENT structure and calls
	cunilogProcessOrQueueEvent () on it.
	This function is called by all logging functions.

	Returns true on success, false otherwise. The function fails after ShutdownSCUNILOGTARGET ()
	or CancelSCUNILOGTARGET () have been called on the SCUNILOGTARGET structure put points to.
*/
bool logEv (SCUNILOGTARGET *put, SCUNILOGEVENT *pev);

/*
	logEv_static

	Macro wrapper for the static version of logEv () that uses the module's internal static
	structure and does not require a pointer to a SCUNILOGTARGET structure as their first
	parameter.
*/
#define logEv_static(pev)	logEv (pSCUNILOGTARGETstatic, (pev))

/*
	The functions expect an SCUNILOGTARGET structure as their first parameter.
	The _static macros use the module's internal static structure and do not require
	a pointer to a SCUNILOGTARGET structure as their first parameter. If you only intend to
	write to a single logfile, the _static macros are ideal.

	The logText functions or macros expect text output.
	The logHexDump functions expect text and binary data to output a hex dump with the text
	as caption.

	The logBinary () function outputs
	a hex dump. The function logBinOrTextU8 () examines the provided data and treats it either
	as UTF-8 text or binary data for a hex dump.

	The functions without a severity use severity level/severity type cunilogEvtSeverityNone.
	Functions containing sev in their names accept a severity type.

	Functions that have U8 in their names are for UTF-8, the ones with a W are intended for
	Windows UTF-16 encoding.

	Functions ending in l accept a length parameter for the text's length, in octets/bytes. You
	can use USE_STRLEN for this parameter, in which case the text buffer's length is obtained
	via a call to strlen () and the string needs to be NUL-terminated. NUL-termination is not
	required otherwise. Note that the length parameter denotes the length of the text, in octets,
	not its size, and also not in characters. The text "abc" has a length of 3 but a size of 4
	octets, which includes the NUL-terminator. UTF-8 characters can have up to 4 octets/bytes.
	Cunilog writes out only UTF-8 but doesn't actually understand its encoding.

	The fmt versions offer variadic functionality like printf () does. The function
	logTextU8fmt () uses an additional memory allocation and deallocation internally. The sfmt
	type functions like logTextU8sfmt () use the stack for the fmt output if less than
	CUNILOG_DEFAULT_SFMT_SIZE bytes are required. Otherwise the heap is used.
	
	Function names containing a "q" (for quick) do not invoke any rotation processors.

	The functions logTextU8smbfmtsev () and logTextU8smbfmt () additionally expect an
	initialised parameter structure of type SMEMBUF. The SMEMBUF structure can be re-used
	for consecutive calls. Within the same thread this can save memory allocations if the
	functions are called several times. Example:

	SMEMBUF smb = SMEMBUF_INITIALISER;
	logTextU8smbfmt_static (&smb, "Text to log");
	logTextU8smbfmt_static (&smb, "Another text to log");
	doneSMEMBUF (&smb);

	All functions return true on success, false otherwise. Functions may for instance fail if
	a memory allocation fails or if a separate logging thread failed to start.
	They also fail after ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () have been called
	on the SCUNILOGTARGET structure put points to.
*/
bool logTextU8sevl		(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextWsevl		(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len);
bool logTextU8sev		(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText);
bool logTextWsev		(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText);
bool logTextU8l			(SCUNILOGTARGET *put, const char *ccText, size_t len);
bool logTextU8ql		(SCUNILOGTARGET *put, const char *ccText, size_t len);
bool logTextWl			(SCUNILOGTARGET *put, const wchar_t *cwText, size_t len);
bool logTextU8			(SCUNILOGTARGET *put, const char *ccText);
bool logTextU8q			(SCUNILOGTARGET *put, const char *ccText);
bool logTextW			(SCUNILOGTARGET *put, const wchar_t *cwText);
bool logTextU8fmt		(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8qfmt		(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sfmt		(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sqfmt		(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sfmtsev	(SCUNILOGTARGET *put, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbfmtsev	(SCUNILOGTARGET *put, cueventseverity sev, SMEMBUF *smb, const char *fmt, ...);
bool logTextU8smbfmt	(SCUNILOGTARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logHexDumpU8sevl	(SCUNILOGTARGET *put, cueventseverity sev, const char ccText, size_t len, const void *pBlob, size_t size);
bool logHexDumpU8l		(SCUNILOGTARGET *put, const char ccText, size_t len, const void *pBlob, size_t size);
bool logBinary			(SCUNILOGTARGET *put, const void *pBlob, size_t size);
bool logBinOrTextU8		(SCUNILOGTARGET *put, const void *szU8TextOrBin, size_t size);

#define logTextU8tsevl_static(v, t, l)			logTextU8sevl		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextWsevl_static(v, t, l)			logTextWsevl		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextU8sev_static(v, t)				logTextU8sevl		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextWsev_static(v, t)				logTextWsevl		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8l_static(t, l)					logTextU8l			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextU8ql_static(t, l)				logTextU8ql			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextWl_static(t, l)					logTextWl			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextU8_static(t)						logTextU8l			(pSCUNILOGTARGETstatic, (t), USE_STRLEN)
#define logTextU8q_static(t)					logTextU8ql			(pSCUNILOGTARGETstatic, (t), USE_STRLEN)
#define logTextW_static(t)						logTextW			(pSCUNILOGTARGETstatic, (t));
#define logTextU8fmt_static(...)				logTextU8fmt		(pSCUNILOGTARGETstatic, __VA_ARGS__)
#define logTextU8sfmt_static(...)				logTextU8sfmt		(pSCUNILOGTARGETstatic, __VA_ARGS__)
#define logTextU8sfmtsev_static(s, ...)			logTextU8sfmtsev	(pSCUNILOGTARGETstatic, (s), __VA_ARGS__)
#define logTextU8smbfmtsev_static(s, m, ...)	logTextU8smbfmtsev	(pSCUNILOGTARGETstatic, (s), (m), __VA_ARGS__)
#define logTextU8smbfmt_static(m, ...)			logTextU8smbfmt		(pSCUNILOGTARGETstatic, (m), __VA_ARGS__)
#define logBinary_static(d, s)					logBinary			(pSCUNILOGTARGETstatic, (d), (s))
#define logBinOrTextU8_static(d, s)				logBinOrTextU8		(pSCUNILOGTARGETstatic, (d), (s))

/*
	The version as text, its year, and as a 64 bit number.
*/
extern const char		ccCunilogVersionText [];
extern const char		ccCunilogVersionYear [];
extern const uint64_t	uiCunilogVersion;

/*
	cunilogCheckVersion

	Compares the version of cunilog.c with the version of cunilogversion.h and returns
	the result of the comparison.

	-1		The version of cunilog.c is less than the one in cunilogversion.h.
	0		The version of cunilog.c is identical to the one in cunilogversion.h.
	1		The version of cunilog.c is greater than the one in cunilogversion.h.

	When cunilog is built as a static library, an application includes cunilog_combined.h
	only. This function ensures that the static library and cunilog_combined.h (actually:
	cunilogversion.h) fit together.

	The function aborts in debug versions. In release builds it merely returns the result
	of the comparison.
*/
/*
#define CUNILOG_VERSION_HDR							\
(		((uint64_t) CUNILOG_VERSION_MAJOR	<< 48)	\
	|	((uint64_t) CUNILOG_VERSION_MINOR	<< 32)	\
	|	((uint64_t) CUNILOG_VERSION_SUB		<< 16)	\
	|	((uint64_t) CUNILOG_VERSION_BUILD)			\
)
*/
#define CUNILOG_VERSION_HDR	((uint64_t) CUNILOG_VERSION_BUILD)
int cunilogCheckVersionIntChk (uint64_t cunilogHdrVersion);
#define cunilogCheckVersion() cunilogCheckVersionIntChk (CUNILOG_VERSION_HDR)

/*
	Tests
	=====
*/
#ifdef CUNILOG_BUILD_TEST_FNCTS
	bool test_cunilog (void);
#else
	#define cunilog()
#endif

EXTERN_C_END

#endif														// Of #ifndef CUNILOG_H.
/****************************************************************************************

	File:		bottom.h
	Why:		Provides the bottom/foot of the combined cunilog.h header file.
	OS:			C99.
	Author:		Thomas
	Created:	2024-08-05

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-05	Thomas			Created.

****************************************************************************************/

#endif														// Of #ifndef CUNILOG_COMBINED_INCLUDED.
