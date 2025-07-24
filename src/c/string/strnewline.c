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

/*
	This should be:

	static const char *aszCunilogNewLine [unilogNewLineAmountEnumValues - 1] =

	But we want to check the amount of elements at runtime.
*/
#if defined (CUNILOG_NEWLINE_POSIX_ONLY)
	const char *aszLineEndings [] =
	{
			"\n"				// 0 = cunilogNewLineSystem
	};
	size_t lenLineEndings [] =
	{
			1					// 0 = cunilogNewLineSystem		"\n"
	};
#elif defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	const char *aszLineEndings [] =
	{
			"\r\n"				// 0 = cunilogNewLineSystem
	};
	size_t lenLineEndings [] =
	{
			2,					// 0 = cunilogNewLineSystem		"\r\n"
	};
#elif defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	const char *aszLineEndings [] =
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
	const char *aszLineEndings [] =
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

#ifdef DEBUG
	const char *ccLineEnding (newline_t nl)
	{
		ubf_assert (nl >= 0);
		ubf_assert (nl < cunilogNewLineAmountEnumValues);

		return aszLineEndings [nl];
	}
#endif

#ifdef DEBUG
	size_t lnLineEnding (newline_t nl)
	{
		ubf_assert (nl >= 0);
		ubf_assert (nl < cunilogNewLineAmountEnumValues);

		return lenLineEndings [nl];
	}
#endif

const char *szLineEnding (newline_t nl, size_t *pln)
{
	ubf_assert (nl >= 0);
	ubf_assert (nl < cunilogNewLineAmountEnumValues);
	ubf_assert_non_NULL (pln);

	*pln = lenLineEndings [nl];
	return aszLineEndings [nl];
}

#ifdef STRNEWLINE_FORCE_ORG_STRISNEWLINE
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
#endif

size_t strIsLineEndings (const char *ch, size_t stLen, size_t *stJump)
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

char *strFirstLineEnding (const char *ch, size_t len)
{
	int		e;
	size_t	l;

	len = USE_STRLEN == len ? strlen (ch) : len;

	while (len)
	{
		e = 0;
		while (cunilogNewLineAmountEnumValues > e)
		{
			l = lnLineEnding (e);
			if (len >= l && !memcmp (ch, ccLineEnding (e), l))
				return (char *) ch;
			++ e;
		}
		++ ch;
		-- len;
	}
	return NULL;
}

char *strFirstLineEnding_l (const char *ch, size_t len, size_t *plLE)
{
	int		e;
	size_t	l;

	len = USE_STRLEN == len ? strlen (ch) : len;

	while (len)
	{
		e = 0;
		while (cunilogNewLineAmountEnumValues > e)
		{
			l = lnLineEnding (e);
			if (len >= l && !memcmp (ch, ccLineEnding (e), l))
			{
				if (plLE)
					*plLE = l;
				return (char *) ch;
			}
			++ e;
		}
		++ ch;
		-- len;
	}
	return NULL;
}

char *strPrevLineEnding_l (const char *ch, size_t len, size_t strtIdx, size_t *plLE)
{
	int		e;
	size_t	l;

	len = USE_STRLEN == len ? strlen (ch) : len;
	if (strtIdx >= len || !len)
		return NULL;

	char *szStart = (char *) ch + strtIdx;

	while (szStart >= ch)
	{
		e = 0;
		while (cunilogNewLineAmountEnumValues > e)
		{
			l = lnLineEnding (e);
			if (strtIdx >= l && !memcmp (szStart - l, ccLineEnding (e), l))
			{
				if (plLE)
					*plLE = l;
				return szStart - l;
			}
			++ e;
		}
		-- szStart;
		-- strtIdx;
	}
	return NULL;
}

size_t strRemoveLineEndingsFromEnd (const char *sz, size_t len)
{
	ubf_assert_non_NULL (sz);

	int		i;
	size_t	ln	= USE_STRLEN == len ? strlen (sz) : len;

	do
	{
		len = ln;
		i	= 0;
		while (ln && i < cunilogNewLineAmountEnumValues)
		{
			if (ln >= lenLineEndings [i])
				if (!memcmp (sz + ln - lenLineEndings [i], aszLineEndings [i], lenLineEndings [i]))
				{
					ln -= lenLineEndings [i];
					break;
				}
			++ i;
		}
	} while (len != ln);
	return ln;
}

#ifdef STRNEWLINE_BUILD_TEST
	bool test_strnewline (void)
	{
		ubf_assert (GET_ARRAY_LEN (aszLineEndings)				==	cunilogNewLineAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (lenLineEndings)				==	cunilogNewLineAmountEnumValues);

		bool			b			= true;
		size_t			st;
		size_t			us;
		char			sz [1024];
		char			*sr;

		#ifdef CUNILOG_NEWLINE_POSIX_ONLY

			strcpy (sz, "\r\n\r");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 0 == us);
			ubf_expect_bool_AND (b, 0 == st);

			strcpy (sz, "\n\r");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 1 == us);
			ubf_expect_bool_AND (b, 1 == st);

			strcpy (sz, "\n\n\n");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 3 == us);
			ubf_expect_bool_AND (b, 3 == st);

		#endif

		#ifdef CUNILOG_NEWLINE_EXTENDED

			strcpy (sz, "\r\n\r");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_assert (2 == us);
			b &= 2 == us;

			strcpy (sz, "ABC\r\n");
			sr = strFirstLineEnding (sz, USE_STRLEN);
			ubf_expect_bool_AND (b, !memcmp (sr, "\r\n", 3));

			strcpy (sz, "\r\n\r");
			us = strRemoveLineEndingsFromEnd (sz, strlen (sz));
			ubf_assert (0 == us);
			b &= 0 == us;

			strcpy (sz, "ABC\r\n\r");
			us = strRemoveLineEndingsFromEnd (sz, strlen (sz));
			ubf_assert (3 == us);
			b &= 3 == us;

			strcpy (sz, "A\rBC\r\n\r");
			us = strRemoveLineEndingsFromEnd (sz, strlen (sz));
			ubf_assert (4 == us);
			b &= 4 == us;

		#endif

		#ifdef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY

			strcpy (sz, "\n\n\nABC");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 3 == us);
			ubf_expect_bool_AND (b, 3 == st);

			strcpy (sz, "\r\n\r\n\r\nABC");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 3 == us);
			ubf_expect_bool_AND (b, 6 == st);

			strcpy (sz, "\r\n\r");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 1 == us);
			ubf_expect_bool_AND (b, 2 == st);

			strcpy (sz, "\na");
			us = strIsLineEndings (sz, strlen (sz), &st);
			ubf_expect_bool_AND (b, 1 == us);

			strcpy (sz, "ABC\r\n");
			sr = strFirstLineEnding (sz, USE_STRLEN);
			ubf_expect_bool_AND (b, !memcmp (sr, "\r\n", 3));

			strcpy (sz, "ABC\r\n");
			st = 0;
			sr = strFirstLineEnding_l (sz, USE_STRLEN, &st);
			ubf_expect_bool_AND (b, !memcmp (sr, "\r\n", 3));
			ubf_expect_bool_AND (b, 2 == st);

			st = 3;
			sr = strFirstLineEnding_l (sz, USE_STRLEN, &st);
			ubf_expect_bool_AND (b, !memcmp (sr, "\r\n", 3));
			ubf_expect_bool_AND (b, 2 == st);

			strcpy (sz, "ABC\r\n1234\r\nLine3\n");
			// Nothing to be found.
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 400, NULL);
			ubf_expect_bool_AND (b, NULL == sr);
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 2, NULL);
			ubf_expect_bool_AND (b, NULL == sr);
			sr = strPrevLineEnding_l (sz, USE_STRLEN, strlen (sz), &st);
			ubf_expect_bool_AND (b, NULL == sr);
			st = 4711;										// The function shouldn't change this.
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 2, &st);
			ubf_expect_bool_AND (b, NULL == sr);
			ubf_expect_bool_AND (b, 4711 == st);			// Still unchanged?
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 6, &st);
			ubf_expect_bool_AND (b, sz + 3 == sr);
			ubf_expect_bool_AND (b, !memcmp (sz + 3, sr, 15));
			ubf_expect_bool_AND (b, 2 == st);
			sr = strPrevLineEnding_l (sz, USE_STRLEN, strlen (sz) - 1, &st);
			ubf_expect_bool_AND (b, sz + 9 == sr);
			ubf_expect_bool_AND (b, !memcmp (sz + 9, sr, 9));
			ubf_expect_bool_AND (b, 2 == st);
			st = 0;
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 9, &st);
			ubf_expect_bool_AND (b, sz + 3 == sr);
			ubf_expect_bool_AND (b, !memcmp (sz + 3, sr, 15));
			ubf_expect_bool_AND (b, 2 == st);
			st = 0;
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 5, &st);
			ubf_expect_bool_AND (b, sz + 3 == sr);
			ubf_expect_bool_AND (b, 2 == st);
			sr = strPrevLineEnding_l (sz, USE_STRLEN, 4, &st);
			ubf_expect_bool_AND (b, NULL == sr);

			strcpy (sz, "ABC\r\r\n");
			sr = strFirstLineEnding (sz, USE_STRLEN);
			ubf_expect_bool_AND (b, !memcmp (sr, "\r\n", 3));

			strcpy (sz, "\r\n\r");
			us = strRemoveLineEndingsFromEnd (sz, strlen (sz));
			ubf_expect_bool_AND (b, 3 == us);
			ubf_expect_bool_AND (b, !memcmp (sz, "\r\n\r", 4));

			strcpy (sz, "ABC\r\n\r");
			us = strRemoveLineEndingsFromEnd (sz, strlen (sz));
			ubf_expect_bool_AND (b, 6 == us);
			ubf_expect_bool_AND (b, !memcmp (sz, "ABC\r\n\r", 7));

		#endif

		return b;
	}
#endif
