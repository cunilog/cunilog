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

bool c_check_utf8(const char *str, size_t len);
TYPEDEF_FNCT_PTR (bool, c_check_utf8) (const char *str, size_t len);

#ifdef U_CHECK_UTF8_BUILD_TEST_FNCT
	bool Check_utf8_test_function (void);
#else
	#define Check_utf8_test_function() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_CHECK_UTF8_H.
