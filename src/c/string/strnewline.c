/****************************************************************************************

	File:		strnewline.c
	Why:		New line functions.
	OS:			C99
	Author:		Thomas
	Created:	2022-04-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-04-11	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	For build options, see header file.
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

#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strnewline.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ArrayMacros.h"
		#include "./platform.h"
		#include "./ubfdebug.h"
		#include "./memstrstr.h"
	#else
		#include "./../pre//ArrayMacros.h"
		#include "./../pre/platform.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/memstrstr.h"
	#endif

#endif

unsigned int strIsNewLine (char *ch, size_t stLen, size_t *stJump)
{	/* New line found?
		A new line is found when:
		<CR>		(0x0D)
		<CR><LF>	(0x0D)(0x0A)
		<LF>		(0x0A)
		This counts as two new lines (a single LF and a single CR):
		<LF><CR>	(0x0A)(0x0D)
	*/
	size_t				st;
	unsigned int		uiRet	= 0;

	if (ch && *ch)
	{
	
		#ifdef DEBUG
			// This was used to find the bug with the wrong line numbers. Thomas, 2018-10-29.
			//#define UBF_LANG_TEXTS_TEST_LINE_NUMBERS
			#ifdef UBF_LANG_TEXTS_TEST_LINE_NUMBERS
				char		chDbg [32];
			#endif
		#endif
	
		st = (size_t) -1 == stLen ? strlen (ch) : stLen;
	
		#ifdef DEBUG
			#ifdef UBF_LANG_TEXTS_TEST_LINE_NUMBERS
			if (st > 20 && uiLineCount)
			{
				memcpy (chDbg, ch, 31);
				chDbg [31] = '\0';
				printf ("Line %u, \"%s\"\n", *uiLineCount, chDbg);
			}
			#endif
		#endif
	
		if	(
					st > 1
				&&	ASCII_CR_VAL	==	(unsigned char) ch [0]
				&&	ASCII_LF_VAL	==	(unsigned char) ch [1]
			)
		{
			++ uiRet;
			if (stJump)
				*stJump			= 2;
			return true;
		}
		if	((unsigned char) ch [0] == ASCII_LF_VAL || (unsigned char) ch [0] == ASCII_CR_VAL)
		{
			++ uiRet;
			if (stJump)
				*stJump			= 1;
			return true;
		}
	}
	if (stJump)
		*stJump					= 0;
	return uiRet;
}

size_t strIsLineEndings (char *ch, size_t stLen, size_t *stJump)
{
	ubf_assert_non_NULL (ch);

	size_t	j	= 0;
	size_t	r	= 0;
	int		e;
	size_t	l;

	stLen = USE_STRLEN == stLen ? strlen (ch) : stLen;

	while (stLen)
	{
		e = 0;
		while (cunilogNewLineAmountEnumValues > e)
		{
			l = lnLineEnding (e);
			if (stLen >= l && !memcmp (ch, ccLineEnding (e), l))
			{
				++ r;
				j			+= l;
				ch			+= l;
				stLen		-= l;
				break;
			}
			++ e;
		}
		if (cunilogNewLineAmountEnumValues == e)
		{	// Not found.
			break;
		}
	}
	if (stJump)
		*stJump = j;
	return r;
}

/*
	This should be:

	static const char *aszCunilogNewLine [unilogNewLineAmountEnumValues - 1] =

	But we want to check the amount of elements at runtime.
*/
#if defined (CUNILOG_NEWLINE_POSIX_ONLY)
	static const char *aszLineEndings [] =
	{
			"\n",				// 0 = cunilogNewLineSystem
			"\n",				// 1 = cunilogNewLinePOSIX
	};
	size_t lenLineEndings [] =
	{
			1,					// 0 = cunilogNewLineSystem		"\n"
			1,					// 1 = cunilogNewLinePOSIX		"\n"
	};
#elif defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	static const char *aszLineEndings [] =
	{
			"\r\n",				// 0 = cunilogNewLineSystem
			"\r\n",				// 1 = cunilogNewLineWindows
	};
	size_t lenLineEndings [] =
	{
			2,					// 0 = cunilogNewLineSystem		"\r\n"
			2,					// 1 = cunilogNewLineWindows	"\r\n"
	};
#elif defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	static const char *aszLineEndings [] =
	{
		#ifdef PLATFORM_IS_WINDOWS
			"\r\n",				// 0 = cunilogNewLineSystem
		#else
			"\n",				// 0 = cunilogNewLineSystem
		#endif
			"\n",				// 1 = cunilogNewLinePOSIX
			"\r\n",				// 2 = cunilogNewLineWindows
	};
	size_t lenLineEndings [] =
	{
		#ifdef PLATFORM_IS_WINDOWS
			2,					// 0 = cunilogNewLineSystem		"\r\n"
		#else
			1,					// 0 = cunilogNewLineSystem		"\n"
		#endif
			1,					// 1 = cunilogNewLinePOSIX		"\n"
			2,					// 2 = cunilogNewLineWindows	"\r\n"
	};
#else
	static const char *aszLineEndings [] =
	{
		#ifdef PLATFORM_IS_WINDOWS
			"\r\n",				// 0 = cunilogNewLineSystem
		#else
			"\n",				// 0 = cunilogNewLineSystem
		#endif
			"\n",				// 1 = cunilogNewLinePOSIX
			"\r\n",				// 2 = cunilogNewLineWindows
			"\r"				// 3 = cunilogNewLineApple
		,	"\n\r"				// 4 = cunilogNewLineRISCOS
		,	"\0x1E"				// 5 = cunilogNewLineQNXbef4
		,	"\0x15"				// 6 = cunilogNewLineIBMzOS
		,	"\0xC2\0x85"		// 7 = cunilogNewLineNEL
		,	"\0xE2\0x80\0xA8"	// 8 = cunilogNewLineLS
		,	"\0xE2\0x80\0xA9"	// 9 = cunilogNewLinePS
	};
	size_t lenLineEndings [] =
	{
		#ifdef PLATFORM_IS_WINDOWS
			2,					// 0 = cunilogNewLineSystem		"\r\n"
		#else
			1,					// 0 = cunilogNewLineSystem		"\n"
		#endif
			1,					// 1 = cunilogNewLinePOSIX		"\n"
			2,					// 2 = cunilogNewLineWindows	"\r\n"
			1					// 3 = cunilogNewLineApple		"\r"
		,	2					// 4 = cunilogNewLineRISCOS		"\n\r"
		,	1					// 5 = cunilogNewLineQNXbef4	"\0x1E"
		,	1					// 6 = cunilogNewLineIBMzOS		"\0x15"
		,	2					// 7 = cunilogNewLineNEL		"\0xC2\0x85"
		,	3					// 8 = cunilogNewLineLS			"\0xE2\0x80\0xA8"
		,	3					// 9 = cunilogNewLinePS			"\0xE2\0x80\0xA9"
	};
#endif

const char *ccLineEnding (newline_t nl)
{
	ubf_assert (nl >= 0);
	ubf_assert (nl < cunilogNewLineAmountEnumValues);

	return aszLineEndings [nl];
}

size_t lnLineEnding (newline_t nl)
{
	ubf_assert (nl >= 0);
	ubf_assert (nl < cunilogNewLineAmountEnumValues);

	return lenLineEndings [nl];
}

const char *szLineEnding (newline_t nl, size_t *pln)
{
	ubf_assert (nl >= 0);
	ubf_assert (nl < cunilogNewLineAmountEnumValues);
	ubf_assert_non_NULL (pln);

	*pln = lenLineEndings [nl];
	return aszLineEndings [nl];
}

#ifdef STRNEWLINE_BUILD_TEST
	void test_strnewline (void)
	{
		ubf_assert (GET_ARRAY_LEN (aszLineEndings)				==	cunilogNewLineAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (lenLineEndings)				==	cunilogNewLineAmountEnumValues);

		size_t			st;
		size_t			us;
		char			sz [1024];

		strcpy (sz, "\r\n\r");
		us = strIsLineEndings (sz, strlen (sz), &st);
		ubf_assert (2 == us);
		strcpy (sz, "\na");
		us = strIsLineEndings (sz, strlen (sz), &st);
		ubf_assert (1 == us);
	}
#endif
