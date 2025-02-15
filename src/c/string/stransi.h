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
#ifndef STR_ANSI_RESET
#define STR_ANSI_RESET					"\033[0m"
#define SIZ_ANSI_RESET					(sizeof (STR_ANSI_RESET))
#define LEN_ANSI_RESET					(SIZ_ANSI_RESET - 1)
#endif

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
#ifndef STR_ANSI_FGCOL_BLACK
#define STR_ANSI_FGCOL_BLACK			"\033[30m"
#define STR_ANSI_FGCOL_RED				"\033[31m"
#define STR_ANSI_FGCOL_GREEN			"\033[32m"
#define STR_ANSI_FGCOL_YELLOW			"\033[33m"
#define STR_ANSI_FGCOL_BLUE				"\033[34m"
#define STR_ANSI_FGCOL_MAGENTA			"\033[35m"
#define STR_ANSI_FGCOL_CYAN				"\033[36m"
#define STR_ANSI_FGCOL_WHITE			"\033[37m"
#endif

/*
	Bright foreground colours.

	Note that bright black is grey.
*/
#ifndef STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_FGCOL_BRIGHT_BLACK		"\033[90m"
#define STR_ANSI_FGCOL_GREY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_FGCOL_GRAY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_FGCOL_BRIGHT_RED		"\033[91m"
#define STR_ANSI_FGCOL_BRIGHT_GREEN		"\033[92m"
#define STR_ANSI_FGCOL_BRIGHT_YELLOW	"\033[93m"
#define STR_ANSI_FGCOL_BRIGHT_BLUE		"\033[94m"
#define STR_ANSI_FGCOL_BRIGHT_MAGENTA	"\033[95m"
#define STR_ANSI_FGCOL_BRIGHT_CYAN		"\033[96m"
#define STR_ANSI_FGCOL_BRIGHT_WHITE		"\033[97m"
#endif

/*
	Background colours.

	Note that bright black is grey.
*/
#ifndef STR_ANSI_BGCOL_BLACK
#define STR_ANSI_BGCOL_BLACK			"\033[40m"
#define STR_ANSI_BGCOL_RED				"\033[41m"
#define STR_ANSI_BGCOL_GREEN			"\033[42m"
#define STR_ANSI_BGCOL_YELLOW			"\033[43m"
#define STR_ANSI_BGCOL_BLUE				"\033[44m"
#define STR_ANSI_BGCOL_MAGENTA			"\033[45m"
#define STR_ANSI_BGCOL_CYAN				"\033[46m"
#define STR_ANSI_BGCOL_WHITE			"\033[47m"
#endif

/*
	Bright background colours.

	Note that bright black is grey.
*/
#ifndef STR_ANSI_BGCOL_BRIGHT_BLACK
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
#endif

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

EXTERN_C_END

#endif														// Of #ifndef U_STRANSI_H.
