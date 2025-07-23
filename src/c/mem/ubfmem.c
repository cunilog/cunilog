/****************************************************************************************

	File:		ubfmem.c
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

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	// We need this if the Microsoft compiler is not used.
	#include <assert.h>
#endif

#include <malloc.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubfmem.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
			#include "./ubfmemdebug.h"
		#endif
	#else
		#include "./../dbg/ubfdebug.h"
		#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
			#include "./../mem/ubfmemdebug.h"
		#endif
	#endif

#endif

#ifdef _WIN32
	#ifdef USE_WINDOWS_NATIVE_HEAP_FUNCTIONS
		#include <windows.h>

		/*
		void *memset (void *ptr, int value, size_t num)
		{
			char *p = ptr;

			while (num-- > 0)
				*p ++ = value;
			return ptr;
		}
		*/

		/*
			memcpy
			memcmp

			Because we are not using the run-time library to obtain a small executable size we
			got to provide our own standard functions.
		*/
		/*
		void *memcpy (void *dest, const void *src, size_t len)
		{
			char *d = dest;
			const char *s = src;

			while (len--)
			{
				*d++ = *s++;
			}
			return dest;
		}
		*/

		int memcmp (const void *str1, const void *str2, size_t count)
		{
			const unsigned char *s1 = (const unsigned char*) str1;
			const unsigned char *s2 = (const unsigned char*) str2;

			while (count-- > 0)
			{
				if (*s1 ++ != *s2 ++)
					return s1 [-1] < s2 [-1] ? -1 : 1;
			}
			return 0;
		}

	#endif
#endif

#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	void *ubf_malloc	(size_t size)
	{	// See https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm .
		void	*pnew;
	
		pnew = ubf_memdbg_malloc (size);
		return pnew;
	}

	void *ubf_calloc	(size_t nitems, size_t size)
	{	// See https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm .
		void	*pnew;
	
		pnew = ubf_memdbg_calloc (nitems, size);
		return pnew;
	}

	void *ubf_realloc	(void *ptr, size_t new_size)
	{	// See https://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm .
		void	*pnew;

		pnew = ubf_memdbg_realloc (ptr, new_size);
		return pnew;
	}

	char *ubf_strdup	(const char *cc)
	{
		char		*pchnew;

		pchnew = ubf_memdbg_strdup (cc);			
		return pchnew;
	}
	
	void ubf_free		(void *ptr)
	{	// See https://www.tutorialspoint.com/c_standard_library/c_function_free.htm .
		/*
			The debug version does not allow a NULL pointer argument. Use

			#ifdef DEBUG
				if (p)
			#endif
					ubf_free (p);

			or
				ubf_free_accept_NULL (p)

			if you expect a NULL pointer to be passed to ubf_free ().
		*/
		ubf_assert (UBF_NULL != ptr);
		ubf_assert (NULL != ptr);
		ubf_memdbg_free (ptr);
	}
	
	void ubf_free_accept_NULL	(void *ptr)
	{
		#ifdef DEBUG
			if (ptr)
		#endif
				ubf_memdbg_free (ptr);
	}

	void *ubf_memcpy	(void *bse, void *dst, const void *src, size_t len)
	{
		return ubf_memdbg_memcpy (bse, dst, src, len);
	}

	void *ubf_memmove	(void *bse, void *dst, const void *src, size_t len)
	{
		return ubf_memdbg_memmove (bse, dst, src, len);
	}
	
	void *ubf_memset (void *bse, void *ptr, int value, size_t num)
	{
		return ubf_memdbg_memset (bse, ptr, value, num);
	}
	
	int ubf_memcmp (const void *bse, const void *ptr1, const void *ptr2, size_t num)
	{
		return ubf_memdbg_memcmp (bse, ptr1, ptr2, num);
	}
	
	void ubf_mem_init_ptr (void *btm, size_t usize)
	{
		ubf_memdbg_fill_alloc_guards_botm (btm, usize);
	}
	
	void *ubf_mem_usr_ptr (void *btm)
	{
		ubf_memdbg_check_alloc_guards_botm (btm);
		return ubf_memdbg_get_base_from_botm (btm);
	}
	
	void ubf_mem_chk_ptr (void *btm)
	{
		ubf_memdbg_check_alloc_guards_botm (btm);
	}
	
	void ubf_mem_chk_bse (void *bse)
	{
		ubf_memdbg_check_alloc_guards_base (bse);
	}
	
	void ubf_mem_test_memdbg (void)
	{
		ubf_memdbg_test_module ();
	}
	
	void ubf_mem_done (void)
	{
	
	}
#endif

#ifdef OS_IS_WINDOWS
	#ifdef DEBUG
	void *ubf_aligned_malloc_intern (size_t alignment, size_t size)
	{	// It's easy to confuse the parameters. The first one's the alignment, the second one
		//	is the size of the memory block to allocate. We assume here that size is always
		//	greater or equal to alignment. Maybe this catches some bugs.
		ASSERT (size >= alignment);								// Parameters confused?
		return _aligned_malloc (alignment, size);
	}
	#else
		// Covered in the header.
		//return _aligned_malloc (alignment, size);
	#endif
#else
	// POSIX.
	#include <stdlib.h>
	
	void *ubf_aligned_malloc_intern (size_t alignment, size_t size)
	{
		void	*pRet = NULL;
		
		// It's easy to confuse the parameters. The first one's the alignment, the second one
		//	is the size of the memory block to allocate. We assume here that size is always
		//	greater or equal to alignment. Maybe this catches some bugs.
		ASSERT (size >= alignment);								// Parameters confused?
		// See http://pubs.opengroup.org/onlinepubs/9699919799/functions/posix_memalign.html .
		if (posix_memalign (&pRet, alignment, size))
			return NULL;
		return pRet;
	}
#endif

#ifdef DEBUG
	/*
	void *ubf_alloca (size_t size)
	{
		return alloca (size);
	}
	*/
#endif

void *ubf_memdup (const void *mem, size_t len)
{
	void	*dup;
	
	dup = ubf_malloc (len);
	if (dup)
	{
		if (len)
			memcpy (dup, mem, len);
	}
	return dup;
}

void *ubf_memdup_siz (const void *mem, size_t len, size_t siz)
{
	void	*dup;
	
	ubf_assert (siz >= len);
	
	dup = ubf_malloc (siz);
	if (dup)
	{
		if (len && siz > len)
			memcpy (dup, mem, len);
	}
	return dup;
}

char *strdup_l (const char *str, size_t len)
{
	ubf_assert_non_NULL (str);

	char *szNew = ubf_malloc (len + 1);
	if (szNew)
	{
		memcpy (szNew, str, len);
		szNew [len] = ASCII_NUL;
	}
	return szNew;
}
