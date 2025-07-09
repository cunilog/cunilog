/****************************************************************************************

	File:		stransi.c
	Why:		Functions for ANSI escape codes.
	OS:			C99
	Author:		Thomas
	Created:	2025-02-14

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-14	Thomas			Created.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./stransi.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
		#include "./ubfdebug.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

/*
	The Wikipedia article https://en.wikipedia.org/wiki/ANSI_escape_code has been used
	as the basis to determine if sz is an ANSI escape sequence:

	https://en.wikipedia.org/wiki/ANSI_escape_code#Control_Sequence_Introducer_commands

	"For Control Sequence Introducer, or CSI, commands, the ESC [ (written as \e[, \x1b[
	or \033[ in several programming languages) is followed by any number (including none)
	of "parameter bytes" in the range 0x30-0x3F (ASCII 0-9:;<=>?), then by any number of
	"intermediate bytes" in the range 0x20-0x2F (ASCII space and !"#$%&'()*+,-./), then
	finally by a single "final byte" in the range 0x40-0x7E (ASCII @A-Z[\]^_`a-z{|}~)"
*/
#define UC	unsigned char

size_t isANSIescSequence (const char *sz, size_t ln)
{
	size_t n = 0;

	ln = USE_STRLEN == ln ? strlen (sz) : ln;

	if (ln && (UC) ASCII_ESC == (UC) sz [n])
	{
		++ n;
		if (n < ln && (UC) '[' == (UC) sz [n])
		{
			++ n;
			while	(n < ln && (UC) '\x30' <= (UC) sz [n] && (UC) '\x3F' >= (UC) sz [n])	++ n;
			while	(n < ln && (UC) '\x20' <= (UC) sz [n] && (UC) '\x2F' >= (UC) sz [n])	++ n;
			if		(n < ln && (UC) '\x40' <= (UC) sz [n] && (UC) '\x7E' >= (UC) sz [n])	++ n;
		}
	}
	return n;
}

size_t removeANSIescSequences (char *sz, size_t ln)
{
	ln = USE_STRLEN == ln ? strlen (sz) : ln;

	size_t rt	= ln;
	size_t lo	= ln;
	size_t le;

	while (ln)
	{
		le = isANSIescSequence (sz, ln);
		if (le)
		{
			rt -= le;
			ln -= le;
			if (ln)
				memmove (sz, sz + le, ln);
		} else
		{
			++ sz;
			-- ln;
		}
	};
	if (rt < lo)
		sz [0] = ASCII_NUL;
	return rt;
}

#ifdef STRANSI_BUILD_TEST_FNCT
	bool stransi_test_fnct (void)
	{
		bool	b = true;
		char	sz [1024];

		b &= 0 == isANSIescSequence ("A normal text", USE_STRLEN);
		b &= 1 == isANSIescSequence ("\x1B", 1);
		b &= 2 == isANSIescSequence ("\x1B[", 2);
		b &= LEN_ANSI_RESET == isANSIescSequence (STR_ANSI_RESET, LEN_ANSI_RESET);
		
		b &= 3 == removeANSIescSequences ("ABC", 3);
		strcpy (sz, "ABC\x1B");
		b &= 3 == removeANSIescSequences (sz, 4);
		ubf_expect_bool_AND (b, !memcmp ("ABC", sz, 4));
		strcpy (sz, "ABC\x1B[");
		b &= 3 == removeANSIescSequences (sz, 5);
		ubf_expect_bool_AND (b, !memcmp ("ABC", sz, 4));
		strcpy (sz, STR_ANSI_FGCOL_BRIGHT_BLACK "ABC" STR_ANSI_FGCOL_BRIGHT_BLACK);
		b &= 3 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("ABC", sz, 4));
		strcpy (sz, STR_ANSI_FGCOL_BRIGHT_BLACK "ABC" STR_ANSI_FGCOL_BRIGHT_BLACK "ABC");
		b &= 6 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("ABCABC", sz, 7));
		strcpy (sz, "\0x1B\0x1B\0x1B\0x1B\0x1B\0x1B\0x1B\0x1B\0x1B\0x1B");
		b &= 0 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("", sz, 1));
		strcpy (sz, "[");
		b &= 1 == removeANSIescSequences (sz, 1);
		ubf_expect_bool_AND (b, !memcmp ("[", sz, 2));
		strcpy (sz, "\033[n;nH");							// "n" is not a number.
		b &= 3 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp (";nH", sz, 4));
		strcpy (sz, "\033[9999;8888H");
		b &= 0 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("", sz, 1));
		strcpy (sz, "\033[111122223333444455557777888899990000;111122223333444455557777888899990000H");
		b &= 0 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("", sz, 1));
		strcpy (sz, "ABC\033[1K");
		b &= 3 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("ABC", sz, 4));
		strcpy (sz, "\033[?25hABC");
		b &= 3 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("ABC", sz, 4));
		strcpy (sz, "ABC[ABC");
		b &= 7 == removeANSIescSequences (sz, USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("ABC[ABC", sz, 8));


		return b;
	}
#endif
