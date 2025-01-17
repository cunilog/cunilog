/****************************************************************************************

	File		struri.c
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./struri.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./strhex.h"
	#else
		#include "./../pre/externC.h"
		#include "./../string/strhex.h"
	#endif

#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static inline bool isValidURIcharacter (const char c)
{
	return (isalnum (c) || '-' == c || '_' == c || '.' == c || '~' == c);
}

// Function to encode a string in URI format.
size_t uri_encode_str (char *szURIencoded, const char *str, size_t len)
{

	size_t			ret     = 0;

	len = USE_STRLEN ? strlen (str) : len;

	unsigned char   c;
	if (szURIencoded)
	{
		while (len)
		{
			c = str [0];
			if (isValidURIcharacter (c))
			{
				*szURIencoded ++ = c;
				++ ret;
			} else
			{
				URI_encode_hex_from_octet (szURIencoded, c);
				szURIencoded	+= 3;
				ret				+= 3;
			}
			-- len;
			++ str;
		}
		*szURIencoded = ASCII_NUL;
	} else
	{
		while (len)
		{
			c = str [0];
			if (isValidURIcharacter (c))
				++ ret;
			else
				ret += 3;
			-- len;
			++ str;
		}
		++ ret;
	}
	return ret;
}
