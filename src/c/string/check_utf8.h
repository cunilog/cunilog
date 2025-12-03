/****************************************************************************************

	File:		check_utf8.h
	Why:		Checks for valid UTF-8
	OS:			C99
	Author:		Thomas
	Created:	2025-01-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-27	Thomas			This history created.
							Acquired from https://github.com/yasuoka/check_utf8 .
							Thanks to YASUOKA Masahiko.
							Function renamed to c_check_utf8 ().

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
	For the original unchanged version, see https://github.com/yasuoka/check_utf8 .
*/

/*
 * Copyright (c) 2024 YASUOKA Masahiko <yasuoka@yasuoka.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef U_CHECK_UTF8_H
#define U_CHECK_UTF8_H

#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	c_check_utf8

	Checks if str points to a valid UTF-8 character set string with length len.

	Returns true if every character in str is a valid
*/
bool c_check_utf8(const char *str, size_t len);
TYPEDEF_FNCT_PTR (bool, c_check_utf8) (const char *str, size_t len);

/*
	nOctetsInUTF8char

	Returns the amount of octets/bytes the UTF-8 character/code point c
	requires if c is the first octet/byte of a UTF-8 code point.

	Valid return values are 1, meaning that c is the only octet, 2, 3,
	and 4.

	The function returns 0 if c is not a valid first octet of a UTF-8
	code point.
*/
unsigned int nOctetsInUTF8char (uint8_t c);
TYPEDEF_FNCT_PTR (unsigned int, nOctetsInUTF8char) (unsigned int c);

/*
	nWordsInUTF16char

	Returns the amount of 16 bit words the UTF-16 character/code point
	c requires if c is the first word/character of a UTF-16 code point.

*/
unsigned int nWordsInUTF16char (uint16_t c);
TYPEDEF_FNCT_PTR (unsigned int, nWordsInUTF16char) (uint16_t c);

/*
	Check_utf8_test_function

	Test function for the module.
*/
#ifdef U_CHECK_UTF8_BUILD_TEST_FNCT
	bool Check_utf8_test_function (void);
#else
	#define Check_utf8_test_function() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_CHECK_UTF8_H.
