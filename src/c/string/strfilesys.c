/****************************************************************************************

	File:		strfilesys.c
	Why:		File system string functions.
	OS:			C99.
	Author:		Thomas
	Created:	2023-05-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-27	Thomas			Created.

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

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strfilesys.h"
	#include "./ubfcharscountsandchecks.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./memstrstr.h"
		#include "./ubfdebug.h"
		#include "./platform.h"
		#include "./Warnings.h"
		#include "./strisabsolutepath.h"
	#else
		#include "./../mem/memstrstr.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../pre/platform.h"
		#include "./../pre/Warnings.h"
		#include "./../string/strisabsolutepath.h"
	#endif

#endif

size_t str_correct_dir_separators (char *str, size_t len)
{
	size_t	n;
	size_t	r	= 0;
	
	len = (size_t) -1 == len ? strlen (str) : len;
	for (n = 0; n < len; ++ n)
	{
		if (isWrongDirectorySeparator (str [n]))
		{
			str [n] = UBF_DIR_SEP;
			++ r;
		}
	}
	return r;
}

/*
	Original (most likely slower) function.

	static char		cNavWin [4] 	= {'.','.', UBF_WIN_DIR_SEP, 0};
	static char		cNavUnx [4] 	= {'.','.', UBF_PSX_DIR_SEP, 0};
	static size_t	lenNav		= sizeof (cNavWin) - 1;

	char *str_find_path_navigator (char *szString, size_t lnString)
	{
		char *chW = memstrstr (szString, lnString, cNavWin, lenNav);
		char *chU = memstrstr (szString, lnString, cNavUnx, lenNav);
		return chW && chU ? (chW < chU ? chW : chU) : (chW ? chW : chU);
	}
*/

static char		cDoubleDot [2]		= {'.', '.'};
const size_t	lenNav				= 3;

DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

char *str_find_path_navigator (char *szString, size_t lnString)
{
	ubf_assert_non_NULL (szString);
	ubf_assert (USE_STRLEN != lnString);					// Not supported in this function.

	char *szNavigator;

	while ((szNavigator = memstrstr (szString, lnString, cDoubleDot, 2)))
	{
		lnString -= szNavigator - szString;
		if (lnString > 2)
		{
			if ('/' == szNavigator [2] || '\\' == szNavigator [2])
				return szNavigator;
			szString = szNavigator + 1;
			-- lnString;
		} else
			return NULL;
	}
	return NULL;
}

size_t str_remove_path_navigators (char *chPath, size_t *pLen)
{
	ubf_assert_non_NULL (chPath);

	size_t		replaced		= 0;
	char		*ch;
	char		*chL;
	char		*chM;
	char		c;
	size_t		mov;
	size_t		len;
	
	size_t lnPath = pLen && SUBF_STRING_USE_STRLEN != *pLen ? *pLen : strlen (chPath);
	ubf_assert (0 < lnPath);
	if (lnPath > 4)											// Minimum is "a/../" (5).
	{	
		char *chS = chPath;
		size_t lnLeft = lnPath;
		if (':' == chS [1])
		{	// Windows "C:".
			ubf_assert (2 <= lnLeft);
			chS		+= 2;
			lnLeft	-= 2;
		}
		c = *chS;
		// Search for the first character that is neither a period nor a slash.
		while (lnLeft && ('.' == c || ubf_isdirseparator (c)))
		{
			++ chS;
			-- lnLeft;
			c = *chS;
		}
		chM = chS;
		while ((ch = str_find_path_navigator (chS, lnLeft)))
		{
			chL = ch;										// "../".
			if (chL > chM + 1)
				chL -= 2;									// "x/../".
			else
				break;
			while (chL >= chS && !ubf_isdirseparator (*chL))
				-- chL;
			++ chL;
			mov = lnPath - (size_t) (ch + lenNav - chPath);
			len = (size_t) (lenNav + ch - chL);
			if (lnPath >= len)
			{
				memmove (chL, ch + lenNav, mov);
				lnPath -= len;
				lnLeft -= len;
				++ replaced;
			}
		}
	}
	if (replaced)
		chPath [lnPath] = '\0';
	if (pLen)
		*pLen = lnPath;
	return replaced;
}

bool ubf_correct_directory_separators_str	(
			char			*chPath,
			size_t			*cunilog_restrict plenPath,
			size_t			*cunilog_restrict pReps
											)
{
	size_t			stRet	= 0;
	size_t			st;
	size_t			stLen;
	char			*ch		= chPath;
	char			ds [3]	= {UBF_DIR_SEP, UBF_DIR_SEP, 0};	// Double separator.
	
	ubf_assert (NULL != chPath);
	if (chPath)
	{
		st = plenPath
				 ? (SUBF_STRING_USE_STRLEN == *plenPath ? strlen (chPath) : *plenPath)
				 : strlen (chPath);
		ubf_assert (0 < st);
		if (st)
		{
			stLen = st;
			while (st --)
			{	// Replace all directory separators of the wrong platform. On POSIX
				//	platforms the backslash is replaced by a forward slash, and on Windows
				//	platforms it is the other way round.
				if (UBF_WRONG_DIR_SEP == *ch)
				{
					*ch = UBF_DIR_SEP;
					++ stRet;
				}
				++ ch;
			}
			// Remove duplicate separators. We're not going to touch the first double
			//	slash of "\\server\share".
			if (st > 2)
			{
				ch = chPath + 2;
				while ((ch = strstr (ch, ds)))
				{
					-- stLen;
					memmove (ch, ch + 1, chPath + stLen - ch);
					++ stRet;
				}
			}
			if (plenPath)
				*plenPath = stLen;
			if (pReps)
				*pReps = stRet;
			return true;
		}
	}
	return false;
}

DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

void ubf_change_directory_separators (char *szPath, size_t len, const char newSeparator)
{
	size_t	l = (size_t) -1 == len ? strlen (szPath) : len;
	size_t	i;
	
	for (i = 0; i < l; ++i)
	{
		if (is_directory_separator (szPath [i]))
			szPath [i] = newSeparator;
	}
}

size_t ubf_len_with_last_directory_separator (const char *szPath, size_t len)
{
	size_t	l = (size_t) -1 == len ? strlen (szPath) : len;
	
	if (szPath)
	{
		if (l)
		{
			while (l --)
			{
				if (is_directory_separator (szPath [l]))
					return l + 1;
			}
		}
		// This actually only applies to Windows. A colon can also be a separator in case of
		//	"C:file.ext". Although this is actually not a real absolute path, we allow it here.
		if (2 <= l && ubf_isalpha (szPath [0]) && ':' == szPath [1])
			return 2;
	}
	return 0;
}

size_t str_remove_last_dir_separator (const char *str, size_t len)
{
	len = str ? (USE_STRLEN == len ? strlen (str) : len) : 0;
	if (len)
	{
		if (is_path_separator (str [len - 1]))
			-- len;
	}
	return len;
}

size_t smb_absolute_path_from_relative_path	(
			SMEMBUF		*pmbAbsolute,
			const char *cunilog_restrict	szRelative,		size_t	lnRelative,
			const char *cunilog_restrict	szReference,	size_t	lnReference
											)
{
	ubf_assert_non_NULL	(pmbAbsolute);
	ubf_assert			(isInitialisedSMEMBUF (pmbAbsolute));
	ubf_assert_non_NULL	(szRelative);
	ubf_assert_non_NULL	(szReference);

	lnRelative	= USE_STRLEN == lnRelative	? strlen (szRelative)	: lnRelative;
	lnReference	= USE_STRLEN == lnReference	? strlen (szReference)	: lnReference;
	ubf_assert_non_0	(lnRelative);
	ubf_assert_non_0	(lnReference);

	/*
	ubf_assert (!isDirectorySeparator (szRelative [0]));
	ubf_assert (!is_absolute_path_l (szRelative, lnRelative));
	*/

	size_t ln = 0;
	if (is_absolute_path_l (szRelative, lnRelative))
	{
		growToSizeSMEMBUF (pmbAbsolute, lnRelative + 1);
		if (isUsableSMEMBUF (pmbAbsolute))
		{
			memcpy (pmbAbsolute->buf.pch, szRelative, lnRelative);
			pmbAbsolute->buf.pch [lnRelative] = ASCII_NUL;
			ln = lnReference;
			str_remove_path_navigators (pmbAbsolute->buf.pch, &ln);
		}
	} else
	{
		growToSizeSMEMBUF (pmbAbsolute, lnReference + lnRelative + 2);
		if (isUsableSMEMBUF (pmbAbsolute))
		{
			memcpy (pmbAbsolute->buf.pch, szReference, lnReference);
			if (!isDirectorySeparator (szReference [lnReference - 1]))
				pmbAbsolute->buf.pch [lnReference ++] = UBF_DIR_SEP;
			memcpy (pmbAbsolute->buf.pch + lnReference, szRelative, lnRelative);
			ln = lnReference + lnRelative;
			pmbAbsolute->buf.pch [ln] = ASCII_NUL;
			str_remove_path_navigators (pmbAbsolute->buf.pch, &ln);
		}
	}
	return ln;
}


#ifdef BUILD_DEBUG_UBF_STRFILESYS_TESTS
	bool ubf_test_ubf_strfilesys (void)
	{
		bool			bRet	= false;
		size_t			stLen;
		size_t			st;
		char			chPath [4096];
		size_t			i;
		bool			b		= true;
		size_t			stReps;
		char			*sz;
	
		ubf_assert ((size_t) -1 == SUBF_STRING_UNKNOWN_LENGTH);
		ubf_assert ((size_t) -1 == SUBF_STRING_USE_STRLEN);

		// Function str_find_path_navigator ().
		strcpy (chPath, "..");
		sz = str_find_path_navigator (chPath, 2);
		ubf_assert_NULL (sz);

		strcpy (chPath, "");
		sz = str_find_path_navigator (chPath, 0);
		ubf_assert_NULL (sz);

		strcpy (chPath, "ABC../");
		sz = str_find_path_navigator (chPath, 6);
		ubf_assert (sz == chPath + 3);

		strcpy (chPath, "abc..1..2..3..4..5");
		sz = str_find_path_navigator (chPath, 18);
		ubf_assert_NULL (sz);

	// Function ubf_correct_directory_separators_str ().
	#ifdef PLATFORM_IS_WINDOWS
		strcpy (chPath, "\\\\server\\share");
	#else
		strcpy (chPath, "//server/share");
	#endif
		// With (size_t) -1 and NULL. Both should behave identically.
		stLen = SUBF_STRING_USE_STRLEN;
		b &= ubf_correct_directory_separators_str (chPath, &stLen, &stReps);
		ubf_expect_TRUE (b);
		ubf_expect_bool_AND (b, 0 == stReps);
		b &= ubf_correct_directory_separators_str (chPath, NULL, &stReps);
		ubf_expect_bool_AND (b, 0 == stReps);
		// Number of replacements not returned.
		b &= ubf_correct_directory_separators_str (chPath, NULL, NULL);
		ubf_expect_TRUE (b);
		ubf_expect_bool_AND (b, 0 == stReps);
	#ifdef PLATFORM_IS_WINDOWS
		strcpy (chPath, "//server/share");
	#else
		strcpy (chPath, "\\\\server\\share");
	#endif
		st = strlen (chPath);
		stLen = SUBF_STRING_USE_STRLEN;
		b &= ubf_correct_directory_separators_str (chPath, &stLen, &stReps);
		ubf_expect_TRUE (b);
		ubf_expect_bool_AND (b, st == stLen);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, 3 == stReps);
	// Return value 5 because 4 wrong separators replaced + one duplicate.
	#ifdef PLATFORM_IS_WINDOWS
		strcpy (chPath, "//server//share");
	#else
		strcpy (chPath, "\\\\server\\\\share");
	#endif
		b = ubf_correct_directory_separators_str (chPath, NULL, &stReps);
		ubf_expect_TRUE (b);
		ubf_expect_bool_AND (b, 5 == stReps);
	
		// Function str_remove_path_navigators ().
		strcpy (chPath, "D:");
		i = str_remove_path_navigators (chPath, NULL);
		// Minimum length is 4.
		ubf_expect_bool_AND (b, 0 == i);
		// We can't test with a length of 0 as str_remove_path_navigators () asserts
		//	that the length is > 0.
		stLen = 1;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 0 == i);
		ubf_expect_bool_AND (b, 1 == stLen);

		strcpy (chPath, "D:\\path1\\path2");
		stLen = SUBF_STRING_UNKNOWN_LENGTH;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 0 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "D:\\path1\\path2", strlen (chPath)));

		strcpy (chPath, "D:\\path1\\..\\path2");
		stLen = SUBF_STRING_UNKNOWN_LENGTH;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 1 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "D:\\path2", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/p01/p02/p03/p04/../../pnew");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/p01/p02/pnew", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/p01/p02/p03nnnnnnnnnnnnnnnn/p04/../../pnew");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/p01/p02/pnew", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/p01/p02/p03nnnnnnnnnnnnnnnn/p04kkkkkkkkkkkkkkkkkkkkkkkkkkkkk/../../pnew");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/p01/p02/pnew", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/p01/p02/d/d/../../pnew");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/p01/p02/pnew", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/p01/p02/p03/p04/../../pnew/p05/p06/../p07/p08");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 3 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/p01/p02/pnew/p05/p07/p08", strlen (chPath)));

		// Cannot be resolved. Two path parts need to stay.
		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/p01/p02/p03/p04/../../../../../../p07/p08");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 4 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/../../p07/p08", strlen (chPath)));

		// Each part only 1 octet long.
		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/1/2/3/4/../../../7/8");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 3 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/1/7/8", strlen (chPath)));

		// Invalid navigators.
		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/1/2/3/4/./././7/8");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 0 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/1/2/3/4/./././7/8", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/1/2/3/4/././../7/8");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 1 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/1/2/3/4/./7/8", strlen (chPath)));

		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "/1/2/3/4/./../../7/8");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/1/2/3/7/8", strlen (chPath)));

		// With a Windows drive letter.
		stLen = SUBF_STRING_LENGTH_UNKNOWN;
		strcpy (chPath, "X:/1/2/3/4/./../../7/8");
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, strlen (chPath) == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "X:/1/2/3/7/8", strlen (chPath)));

		// Check NUL terminator.
		strcpy (chPath, "/1/2/../4/X");
		stLen = 10;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 1 == i);
		ubf_expect_bool_AND (b, 5 == stLen);
		ubf_assert (!memcmp (chPath, "/1/4/", 6));

		/*
			From the comments:

			"../../test1/test2/test3/../../file.ext"	->	"../../test1/file.ext"
			"../../../1/2/3/4/5/6/7/../f.ext"			->	"../../../1/2/3/4/5/6/f.ext"
			"C:this is a test/test1/test2/../file.ext"	->	"C:this is a test/test1/file.ext"
			"/1/2/3/4/../../../../f.e"					->	"/f.e"
			"1/../f"									->	"f"
			"../f"										->	"../f"
			"1/2/../../f"								->	"f"
			"1/2/../../../f"							->	"../f"
		*/
		strcpy (chPath, "../../test1/test2/test3/../../file.ext");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, 20 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "../../test1/file.ext", 21));

		strcpy (chPath, "../../../1/2/3/4/5/6/7/../f.ext");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 1 == i);
		ubf_expect_bool_AND (b, 26 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "../../../1/2/3/4/5/6/f.ext", 27));

		strcpy (chPath, "C:this is a test/test1/test2/../file.ext");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 1 == i);
		ubf_expect_bool_AND (b, 31 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "C:this is a test/test1/file.ext", 32));

		strcpy (chPath, "/1/2/3/4/../../../../f.e");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 4 == i);
		ubf_expect_bool_AND (b, 4 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/f.e", 5));

		strcpy (chPath, "1/../f");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 1 == i);
		ubf_expect_bool_AND (b, 1 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "f", 2));

		strcpy (chPath, "../f");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 0 == i);
		ubf_expect_bool_AND (b, 4 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "../f", 5));

		strcpy (chPath, "1/2/../../f");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, 1 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "f", 2));

		strcpy (chPath, "1/2/../../../f");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 2 == i);
		ubf_expect_bool_AND (b, 4 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "../f", 5));
		/*
			End of tests from the comments.
		*/

		// Nothing to resolve.
		strcpy (chPath, "/../");
		stLen = USE_STRLEN;
		i = str_remove_path_navigators (chPath, &stLen);
		ubf_expect_bool_AND (b, 0 == i);
		ubf_expect_bool_AND (b, 4 == stLen);
		ubf_expect_bool_AND (b, !memcmp (chPath, "/../", 5));

		st = ubf_len_with_last_directory_separator ("C:\\", USE_STRLEN);
		ubf_expect_bool_AND (b, 3 == st);
		st = ubf_len_with_last_directory_separator ("/home/file", USE_STRLEN);
		ubf_expect_bool_AND (b, 6 == st);
		st = ubf_len_with_last_directory_separator ("/", USE_STRLEN);
		ubf_expect_bool_AND (b, 1 == st);
		st = ubf_len_with_last_directory_separator ("Fridolin", USE_STRLEN);
		ubf_expect_bool_AND (b, 0 == st);
		st = ubf_len_with_last_directory_separator ("///", USE_STRLEN);
		ubf_expect_bool_AND (b, 3 == st);
		st = ubf_len_with_last_directory_separator ("///", 3);
		ubf_expect_bool_AND (b, 3 == st);
		st = ubf_len_with_last_directory_separator ("C:\\", 3);
		ubf_expect_bool_AND (b, 3 == st);
		st = ubf_len_with_last_directory_separator ("C:\\directory", USE_STRLEN);
		ubf_expect_bool_AND (b, 3 == st);
		st = ubf_len_with_last_directory_separator ("C:/file", USE_STRLEN);
		ubf_expect_bool_AND (b, 3 == st);
		st = ubf_len_with_last_directory_separator ("C:file", USE_STRLEN);
		ubf_expect_bool_AND (b, 2 == st);
		st = ubf_len_with_last_directory_separator ("C:file.ext", USE_STRLEN);
		ubf_expect_bool_AND (b, 2 == st);
	
		SMEMBUF smb = SMEMBUF_INITIALISER;
		size_t ln;
		ln = smb_absolute_path_from_relative_path (&smb, "../", USE_STRLEN, "C:/", USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("C:/../", smb.buf.pcc, 7));

		ln = smb_absolute_path_from_relative_path (&smb, "../", USE_STRLEN, "C:/folder", USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("C:/", smb.buf.pcc, 4));

		ln = smb_absolute_path_from_relative_path (&smb, "../", USE_STRLEN, "C:/folder/", USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("C:/", smb.buf.pcc, 4));

		ln = smb_absolute_path_from_relative_path (&smb, "/home", USE_STRLEN, "C:/folder/", USE_STRLEN);
		ubf_expect_bool_AND (b, !memcmp ("/home", smb.buf.pcc, 6));

		// Return the test result.
		bRet = b;
		return bRet;
	}
#endif
