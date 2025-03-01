/****************************************************************************************

	File:		ubfcharscountsandchecks.c
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

#include <ctype.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubfcharscountsandchecks.h"

#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool ubf_is_printable_ASCII (char c)
	{	// From SPC (20h, 32d) to '~' (7Eh, 126d).
		return ((unsigned char) c > 0x1F && (unsigned char) c < 0x7F);
	}
#endif

bool str_has_only_printable_ASCII (const char *sz, size_t len)
{
	len = STRLENSZ (sz, len);

	unsigned int ui;

	for (ui = 0; ui < len; ++ ui)
	{
		if (!ubf_is_printable_ASCII (sz [ui]))
			return false;
	}
	return true;
}

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool ubf_is_letter (char c)
	{
		return	(
				((unsigned char) c > 'A' - 1 && (unsigned char) c < 'Z' + 1)
			||	((unsigned char) c > 'a' - 1 && (unsigned char) c < 'z' + 1)
				);
	}
#endif

char *ubf_is_letter_until (char *ch, char c)
{
	while (*ch && c != *ch)
	{
		if (!ubf_is_letter (*ch))
		{
			return NULL;
		}
		++ ch;
	}
	if (c == *ch)
	{
		return ch;
	}
	return NULL;
}

/*
	Returns true when c is a white space character.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool isWhiteSpace (char c)
	{
		return	(
						ASCII_SPC			== c
					||	ASCII_TAB			== c
					||	ASCII_VT			== c
				);
	}
#endif

#ifdef _MSC_VER
#pragma warning (default: 4706)									// Assignment within conditional expression.
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool isDirectorySeparator (char c)
	{
		return ('/' == c || '\\' == c);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool isWrongDirectorySeparator (char c)
	{
		return (UBF_WRONG_DIR_SEP == c);
	}
#endif

size_t ubf_count_numerical_digits (const char *cc)
{
	size_t		stRet = 0;
	
	while (*cc)
	{
		if  (	/*
						(unsigned char) '0' - 1 < (unsigned char) *cc
					&&	(unsigned char) '9' + 1 > (unsigned char) *cc
				*/
				ubf_isdigit (*cc)
			)
		{
			++ stRet;
		}
		++ cc;
	}
	return stRet;
}

size_t ubf_count_starts_with_numerical_digits_up_to (const char *cc, size_t len)
{
	size_t		stRet = 0;
	
	while (*cc && len -- && ubf_isdigit (*cc))
	{
		++ stRet;
		++ cc;
	}
	return stRet;
}

size_t ubf_count_special_characters (const char *cc)
{
	size_t		stRet = 0;
	
	while (*cc)
	{
		if (ubf_is_special (*cc))
		{
			++ stRet;
		}
		++ cc;
	}
	return stRet;
}

size_t ubf_count_char (const char *cc, char c)
{
	size_t		stRet = 0;
	
	while (*cc)
	{
		if  (c == *cc)
		{
			++ stRet;
		}
		++ cc;
	}
	return stRet;
}

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	size_t ubf_obtain_strlen (const char *sz, size_t providedLength)
	{
		return sz ? (USE_STRLEN == providedLength ? strlen (sz) : providedLength) : 0;
	}
#endif
