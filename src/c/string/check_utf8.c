/****************************************************************************************

	File:		check_utf8.c
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

	Note that this file must be saved in UTF-8 encoding without a BOM.
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

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

bool c_check_utf8(const char *str, size_t len)
{
	int		 i, bytes;
	unsigned int	 oct, ch;
	const char	*pos, *end;

	len = USE_STRLEN == len ? strlen (str) : len;

	pos = str;
	end = str + len;
	while (pos < end) {
		oct = *pos;
		if ((oct & 0x80) == 0) {
			bytes = 1;
			ch = oct & 0x7f;
		} else if ((oct & 0xe0) == 0xc0) {
			bytes = 2;
			ch = oct & 0x1f;
		} else if ((oct & 0xf0) == 0xe0) {
			bytes = 3;
			ch = oct & 0xf;
		} else if ((oct & 0xf8) == 0xf0) {
			bytes = 4;
			ch = oct & 0x7;
		} else
			return false;
		if (pos + bytes > end)
			return false;
		for (i = 1; i < bytes; i++) {
			oct = pos[i];
			if ((oct & 0xc0) != 0x80)
				return false;
			ch = ch << 6 | (oct & 0x3f);
		}
		if (!(bytes == 1 || (bytes == 2 && ch >= 0x80) ||
		    (bytes == 3 && ch >= 0x800) ||
		    (bytes == 4 && ch >= 0x10000)))
			return false;
		pos += bytes;
	}

	return true;
}

/*
	https://github.com/yasuoka/check_utf8/blob/main/check_utf8_test.c
*/
#ifdef U_CHECK_UTF8_BUILD_TEST_FNCT
	bool Check_utf8_test_function (void)
	{
		bool b = true;

		b &= c_check_utf8("ほげほげ", 12);
		//ほげほげ in Shift-JIS
		b &= c_check_utf8("\x82\xd9\x82\xb0\x82\xd9\x82\xb0", 8) == false;
		//copyright mark in UTF-8
		b &= c_check_utf8 ("\xC2\xA9", 2);
		b &= c_check_utf8("©", 2) == true;
		// face in medical mask in UTF-8
		b &= c_check_utf8("\xF0\x9F\x98\xB7", 4) == true;
		// length invalid
		b &= c_check_utf8("ふがふが", 11) == false;
		// ascii
		b &= c_check_utf8("Hello world.", 12) == true;
		// empty
		b &= c_check_utf8("", 1) == true;
		// specials
		b &= c_check_utf8("\t\b", 2) == true;

		return b;
	}
#endif
