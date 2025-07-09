/****************************************************************************************

	File:		stransi.h
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

#ifndef U_STRANSI_H
#define U_STRANSI_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdarg.h>
	#include <stdbool.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

/*
	Reset.
*/
#define STR_ANSI_RESET					"\033[0m"
#define SIZ_ANSI_RESET					(sizeof (STR_ANSI_RESET))
#define LEN_ANSI_RESET					(SIZ_ANSI_RESET - 1)

/*
	Coulrs only. These are not ANSI escape sequences on their own and cannot be used
	as such!
*/
#define STR_ANSI_STDCOL_BLACK			"30m"
#define STR_ANSI_STDCOL_RED				"31m"
#define STR_ANSI_STDCOL_GREEN			"32m"
#define STR_ANSI_STDCOL_YELLOW			"33m"
#define STR_ANSI_STDCOL_BLUE			"34m"
#define STR_ANSI_STDCOL_MAGENTA			"35m"
#define STR_ANSI_STDCOL_CYAN			"36m"
#define STR_ANSI_STDCOL_WHITE			"37m"

/*
	Normal foreground colours.
*/
#define STR_ANSI_FGCOL_BLACK			"\033[30m"
#define SIZ_ANSI_FGCOL_BLACK			(sizeof (STR_ANSI_FGCOL_BLACK))
#define LEN_ANSI_FGCOL_BLACK			(SIZ_ANSI_FGCOL_BLACK - 1)

#define STR_ANSI_FGCOL_RED				"\033[31m"
#define SIZ_ANSI_FGCOL_RED				(sizeof (STR_ANSI_FGCOL_RED))
#define LEN_ANSI_FGCOL_RED				(SIZ_ANSI_FGCOL_RED - 1)

#define STR_ANSI_FGCOL_GREEN			"\033[32m"
#define SIZ_ANSI_FGCOL_GREEN			(sizeof (STR_ANSI_FGCOL_GREEN))
#define LEN_ANSI_FGCOL_GREEN			(SIZ_ANSI_FGCOL_GREEN - 1)

#define STR_ANSI_FGCOL_YELLOW			"\033[33m"
#define SIZ_ANSI_FGCOL_YELLOW			(sizeof (STR_ANSI_FGCOL_YELLOW))
#define LEN_ANSI_FGCOL_YELLOW			(SIZ_ANSI_FGCOL_YELLOW - 1)

#define STR_ANSI_FGCOL_BLUE				"\033[34m"
#define SIZ_ANSI_FGCOL_BLUE				(sizeof (STR_ANSI_FGCOL_BLUE))
#define LEN_ANSI_FGCOL_BLUE				(SIZ_ANSI_FGCOL_BLUE - 1)

#define STR_ANSI_FGCOL_MAGENTA			"\033[35m"
#define SIZ_ANSI_FGCOL_MAGENTA			(sizeof (STR_ANSI_FGCOL_MAGENTA))
#define LEN_ANSI_FGCOL_MAGENTA			(SIZ_ANSI_FGCOL_MAGENTA - 1)

#define STR_ANSI_FGCOL_CYAN				"\033[36m"
#define SIZ_ANSI_FGCOL_CYAN				(sizeof (STR_ANSI_FGCOL_CYAN))
#define LEN_ANSI_FGCOL_CYAN				(SIZ_ANSI_FGCOL_CYAN - 1)

#define STR_ANSI_FGCOL_WHITE			"\033[37m"
#define SIZ_ANSI_FGCOL_WHITE			(sizeof (STR_ANSI_FGCOL_WHITE))
#define LEN_ANSI_FGCOL_WHITE			(SIZ_ANSI_FGCOL_WHITE - 1)

/*
	Bright foreground colours.

	Note that bright black is grey.
*/
#define STR_ANSI_FGCOL_BRIGHT_BLACK		"\033[90m"
#define SIZ_ANSI_FGCOL_BRIGHT_BLACK		(sizeof (STR_ANSI_FGCOL_BRIGHT_BLACK))
#define LEN_ANSI_FGCOL_BRIGHT_BLACK		(SIZ_ANSI_FGCOL_BRIGHT_BLACK - 1)

#define STR_ANSI_FGCOL_GREY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define SIZ_ANSI_FGCOL_GREY				(sizeof (STR_ANSI_FGCOL_GREY))
#define LEN_ANSI_FGCOL_GREY				(SIZ_ANSI_FGCOL_GREY - 1)

#define STR_ANSI_FGCOL_GRAY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define SIZ_ANSI_FGCOL_GRAY				(sizeof (STR_ANSI_FGCOL_GRAY))
#define LEN_ANSI_FGCOL_GRAY				(SIZ_ANSI_FGCOL_GRAY - 1)

#define STR_ANSI_FGCOL_BRIGHT_RED		"\033[91m"
#define SIZ_ANSI_FGCOL_BRIGHT_RED		(sizeof (STR_ANSI_FGCOL_BRIGHT_RED))
#define LEN_ANSI_FGCOL_BRIGHT_RED		(SIZ_ANSI_FGCOL_BRIGHT_RED - 1)

#define STR_ANSI_FGCOL_BRIGHT_GREEN		"\033[92m"
#define SIZ_ANSI_FGCOL_BRIGHT_GREEN		(sizeof (STR_ANSI_FGCOL_BRIGHT_GREEN))
#define LEN_ANSI_FGCOL_BRIGHT_GREEN		(SIZ_ANSI_FGCOL_BRIGHT_GREEN - 1)

#define STR_ANSI_FGCOL_BRIGHT_YELLOW	"\033[93m"
#define SIZ_ANSI_FGCOL_BRIGHT_YELLOW	(sizeof (STR_ANSI_FGCOL_BRIGHT_YELLOW))
#define LEN_ANSI_FGCOL_BRIGHT_YELLOW	(SIZ_ANSI_FGCOL_BRIGHT_YELLOW - 1)

#define STR_ANSI_FGCOL_BRIGHT_BLUE		"\033[94m"
#define SIZ_ANSI_FGCOL_BRIGHT_BLUE		(sizeof (STR_ANSI_FGCOL_BRIGHT_BLUE))
#define LEN_ANSI_FGCOL_BRIGHT_BLUE		(SIZ_ANSI_FGCOL_BRIGHT_BLUE - 1)

#define STR_ANSI_FGCOL_BRIGHT_MAGENTA	"\033[95m"
#define SIZ_ANSI_FGCOL_BRIGHT_MAGENTA	(sizeof (STR_ANSI_FGCOL_BRIGHT_MAGENTA))
#define LEN_ANSI_FGCOL_BRIGHT_MAGENTA	(SIZ_ANSI_FGCOL_BRIGHT_MAGENTA - 1)

#define STR_ANSI_FGCOL_BRIGHT_CYAN		"\033[96m"
#define SIZ_ANSI_FGCOL_BRIGHT_CYAN		(sizeof (STR_ANSI_FGCOL_BRIGHT_CYAN))
#define LEN_ANSI_FGCOL_BRIGHT_CYAN		(SIZ_ANSI_FGCOL_BRIGHT_CYAN - 1)

#define STR_ANSI_FGCOL_BRIGHT_WHITE		"\033[97m"
#define SIZ_ANSI_FGCOL_BRIGHT_WHITE		(sizeof (STR_ANSI_FGCOL_BRIGHT_WHITE))
#define LEN_ANSI_FGCOL_BRIGHT_WHITE		(SIZ_ANSI_FGCOL_BRIGHT_WHITE - 1)

/*
	Background colours.

	Note that bright black is grey.
*/
#define STR_ANSI_BGCOL_BLACK			"\033[40m"
#define STR_ANSI_BGCOL_RED				"\033[41m"
#define STR_ANSI_BGCOL_GREEN			"\033[42m"
#define STR_ANSI_BGCOL_YELLOW			"\033[43m"
#define STR_ANSI_BGCOL_BLUE				"\033[44m"
#define STR_ANSI_BGCOL_MAGENTA			"\033[45m"
#define STR_ANSI_BGCOL_CYAN				"\033[46m"
#define STR_ANSI_BGCOL_WHITE			"\033[47m"

/*
	Bright background colours.

	Note that bright black is grey.
*/
#define STR_ANSI_BGCOL_BRIGHT_BLACK		"\033[100m"
#define STR_ANSI_BGCOL_GREY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_BGCOL_GRAY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_BGCOL_BRIGHT_RED		"\033[101m"
#define STR_ANSI_BGCOL_BRIGHT_GREEN		"\033[102m"
#define STR_ANSI_BGCOL_BRIGHT_YELLOW	"\033[103m"
#define STR_ANSI_BGCOL_BRIGHT_BLUE		"\033[104m"
#define STR_ANSI_BGCOL_BRIGHT_MAGENTA	"\033[105m"
#define STR_ANSI_BGCOL_BRIGHT_CYAN		"\033[106m"
#define STR_ANSI_BGCOL_BRIGHT_WHITE		"\033[107m"

/*
#define STR_ANSI_TEXT_REGULAR			"\033[0;31m"
#define STR_ANSI_TEXT_BOLD				"\033[1;31m"
#define STR_ANSI_TEXT_LOWINTENSITY		"\033[2;31m"
#define STR_ANSI_TEXT_ITALIC			"\033[3;31m"
#define STR_ANSI_TEXT_UNDERLINE			"\033[4;31m"
#define STR_ANSI_TEXT_BLINKING			"\033[5;31m"
#define STR_ANSI_TEXT_REVERSE			"\033[6;31m"
#define STR_ANSI_TEXT_BACKGROUND		"\033[7;31m"
#define STR_ANSI_TEXT_INVISIBLE			"\033[8;31m"
*/

EXTERN_C_BEGIN

typedef struct stransicoloursequence
{
	char	*szColSequence;
	size_t	lnColSequence;
} STRANSICOLOURSEQUENCE;


/*
	isANSIescSequence

	Checks if the character sequence starting at sz with length ln is an ANSI
	escape sequence.

	The Wikipedia article https://en.wikipedia.org/wiki/ANSI_escape_code has been used
	as the basis to determine if sz is an ANSI escape sequence:

	https://en.wikipedia.org/wiki/ANSI_escape_code#Control_Sequence_Introducer_commands

	"For Control Sequence Introducer, or CSI, commands, the ESC [ (written as \e[, \x1b[
	or \033[ in several programming languages) is followed by any number (including none)
	of "parameter bytes" in the range 0x30-0x3F (ASCII 0-9:;<=>?), then by any number of
	"intermediate bytes" in the range 0x20-0x2F (ASCII space and !"#$%&'()*+,-./), then
	finally by a single "final byte" in the range 0x40-0x7E (ASCII @A-Z[\]^_`a-z{|}~)"

	The function returns the amount of characters belonging to the escape sequence,
	or 0, if sz does not start with an ANSI escape sequence. It never returns a
	value greater than ln.

	The function's purpose is not the ensure that an ANSI escape sequence is syntactically
	correct. Its purpose is rather to identify sequences for removal. For instance, the
	function returns 1 for a single ESC character (1Bh), and 2 for ESC + "[", but both
	are not on their own valid ANSI escape sequences.

	The parameter ln can be USE_STRLEN, in which case the function calls strlen () on sz
	to determine its length.
*/
size_t isANSIescSequence (const char *sz, size_t ln)
;

/*
	removeANSIescSequences

	Removes all ANSI escape sequences from sz and returns its new length.

	The function calls isANSIescSequence () to determine whether an ANSI escape sequence
	should be removed or not. If at leas one ANSI escape sequence has been found at replaced,
	then the function NUL-terminates sz even if it hasn't been NUL-terminated before the
	call.

	The parameter ln can be USE_STRLEN, in which case the function calls strlen () on sz
	to determine its length.

	The return value is the length of the string sz after all found ANSI escape sequences
	have been removed.
*/
size_t removeANSIescSequences (char *sz, size_t ln)
;

/*
	stransi_test_fnct

	Function to test the module.
*/
#ifdef STRANSI_BUILD_TEST_FNCT
	bool stransi_test_fnct (void);
#else
	#define stransi_test_fnct()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_STRANSI_H.
