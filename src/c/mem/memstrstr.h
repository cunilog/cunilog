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
