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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <malloc.h>

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
		#define ubf_aligned_malloc_intern(alignment, size) _aligned_malloc (alignment, size)
	#endif
#else
	#ifdef DEBUG
		// The debug version has a function definition.
		void *ubf_aligned_malloc_intern (size_t alignment, size_t size);
	#else
		#define ubf_aligned_malloc_intern(alignment, size) aligned_alloc (alignment, size)
	#endif
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

	Debug versions assert that siz >= len.
*/
void *ubf_memdup_siz (const void *mem, size_t len, size_t siz);

/*
	strdup_l

	Since MSVC doesn't provide strndup () yet, we roll our own.

	Copies len bytes/octets from str to a newly allocated buffer. The new buffer is always
	NUL-terminated.
*/
char *strdup_l (const char *str, size_t len);

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
