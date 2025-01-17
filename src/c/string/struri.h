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
