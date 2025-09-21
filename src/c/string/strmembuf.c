/****************************************************************************************

	File:		strmembuf.c
	Why:		String helper functions for SMEMBUF structures.
	OS:			C99
	Author:		Thomas
	Created:	2023-05-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-25	Thomas			Created.

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

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./strfilesys.h"
		#include "./strintuint.h"
		#include "./strmembuf.h"
		#include "./membuf.h"
		#include "./ubfmem.h"
		#include "./ubfdebug.h"
		#ifdef PLATFORM_IS_WINDOWS
			#include "./WinAPI_U8.h"
		#endif
		#include "./unref.h"
	#else
		#include "./strfilesys.h"
		#include "./strintuint.h"
		#include "./strmembuf.h"
		#include "./../mem/membuf.h"
		#include "./../mem/ubfmem.h"
		#include "./../dbg/ubfdebug.h"
		#ifdef PLATFORM_IS_WINDOWS
			#include "./../OS/Windows/WinAPI_U8.h"
		#endif
		#include "./../pre/unref.h"
	#endif

#endif

size_t SMEMBUFfromStrReserveBytes (SMEMBUF *pmb, const char *str, size_t len, size_t reserve)
{
	ubf_assert_non_NULL (pmb);
	ubf_assert_non_NULL (str);
	ubf_assert_non_0 (len);

	size_t l = USE_STRLEN == len ? strlen (str) : len;
	size_t lstr = l;
	l += reserve;
	
	growToSizeSMEMBUF (pmb, l + 1);
	if (isUsableSMEMBUF (pmb))
	{
		memcpy (pmb->buf.pch, str, lstr);
		pmb->buf.pch [lstr] = ASCII_NUL;
		return lstr;
	}
	return 0;
}

size_t SMEMBUFfromStr (SMEMBUF *pmb, const char *str, size_t len)
{
	ubf_assert_non_NULL (pmb);

	size_t l = USE_STRLEN == len ? strlen (str) : len;
	growToSizeSMEMBUF (pmb, l + 1);
	if (isUsableSMEMBUF (pmb))
	{
		if (l)
			memcpy (pmb->buf.pch, str, l);
		pmb->buf.pch [l] = ASCII_NUL;
		return l;
	}
	return 0;
}

size_t SMEMBUFfromStrFmt_va (SMEMBUF *pmb, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (pmb);

	int i = vsnprintf (NULL, 0, fmt, ap);
	if (i < 0)
		return 0;

	size_t l = (size_t) i;
	if (growToSizeSMEMBUF (pmb, l + 1))
	{
		vsnprintf (pmb->buf.pch, l + 1, fmt, ap);
		return l;
	}
	return 0;
}

size_t SMEMBUFfromStrFmt (SMEMBUF *pmb, const char *fmt, ...)
{
	ubf_assert_non_NULL (pmb);

	va_list ap;
	va_start (ap, fmt);
	size_t r = SMEMBUFfromStrFmt_va (pmb, fmt, ap);
	va_end (ap);

	return r;
}

size_t SMEMBUFstrFromUINT64 (SMEMBUF *pmb, uint64_t ui)
{
	ubf_assert_non_NULL (pmb);
	
	char asc [UBF_UINT64_SIZE];
	size_t l = ubf_str_from_uint64 (asc, ui);
	return SMEMBUFfromStr (pmb, asc, l);
}

size_t SMEMBUFstrconcatReserve (SMEMBUF *pmb, size_t len, char *str, size_t lenstr, size_t reserve)
{
	ubf_assert_non_NULL	(pmb);
	ubf_assert			(isInitialisedSMEMBUF (pmb));

	len		= USE_STRLEN == len		? strlen (pmb->buf.pcc)	: len;
	lenstr	= USE_STRLEN == lenstr	? strlen (str)			: lenstr;

	if (str && lenstr)
	{
		if (pmb->size > len + lenstr)
		{	// Both strings fit in the current buffer.
			memcpy (pmb->buf.pch + len, str, lenstr);
			len += lenstr;
			pmb->buf.pch [len] = ASCII_NUL;
		} else
		{	// The current buffer is too small.
			size_t st = ALIGNED_SIZE (len + lenstr + 1 + reserve, STRMEMBUF_DEFAULT_ALIGNMENT);
			char *sz = ubf_malloc (st);
			if (sz)
			{
				memcpy (sz, pmb->buf.pch, len);
				memcpy (sz + len, str, lenstr);
				len += lenstr;
				sz [len] = ASCII_NUL;
				ubf_free (pmb->buf.pch);
				pmb->buf.pch	= sz;
				pmb->size		= st;
			} else
			{	// Heap allocation failed.
				doneSMEMBUF (pmb);
				len = 0;
			}
		}
	}
	return len;
}

size_t SMEMBUFstrconcat (SMEMBUF *pmb, size_t len, char *str, size_t lenstr)
{
	ubf_assert_non_NULL	(pmb);

	return SMEMBUFstrconcatReserve (pmb, len, str, lenstr, 0);
}

#ifdef PLATFORM_IS_WINDOWS
	size_t SMEMBUFstrconcatW (SMEMBUF *pmb, size_t len, wchar_t *wstr, size_t lenwstr)
	{
		ubf_assert_non_NULL	(pmb);
		ubf_assert			(sizeof (WCHAR) == sizeof (wchar_t));

		char	str [WINAPI_U8_HEAP_THRESHOLD];
		char	*pstr;

		len		= USE_STRLEN ? strlen (pmb->buf.pcc)	: len;
		lenwstr	= USE_STRLEN ? wcslen (wstr)			: lenwstr;
		ubf_assert (lenwstr < INT_MAX);

		pstr = AllocU8fromWinU16orUseThresholdl (str, wstr, lenwstr);
		size_t lStr = strlen (pstr);
		size_t lRet = SMEMBUFstrconcat (pmb, len, pstr, lStr);
		DoneU8fromWinU16orUseThreshold (pstr, str);
		return lRet;
	}
#endif

size_t SMEMBUFstrconcatpaths (SMEMBUF *pmb, size_t len, char *strPath, size_t lenPath)
{
	ubf_assert_non_NULL	(pmb);
	ubf_assert			(isInitialisedSMEMBUF (pmb));

	len		= USE_STRLEN == len ? strlen (pmb->buf.pcc) : len;
	lenPath	= USE_STRLEN == lenPath ? strlen (strPath) : lenPath;

	if (len)
	{	// We got something in pmb's buffer.
		if (lenPath)
		{
			if (is_path_separator (strPath [0]))
			{	// We only remove a single path separator.
				++ strPath;
				-- lenPath;
			}
			if (!is_path_separator (pmb->buf.pcc [len  - 1]))
			{
				size_t stTot = len + 1 + lenPath + 1;
				if (growToSizeRetainSMEMBUF (pmb, stTot))
				{
					pmb->buf.pch [len] = UBF_DIR_SEP;
					memcpy (pmb->buf.pch + len + 1, strPath, lenPath);
					pmb->buf.pch [stTot - 1] = ASCII_NUL;
					return stTot - 1;
				}
			} else
			{
				size_t stTot = len + lenPath + 1;
				if (growToSizeRetainSMEMBUF (pmb, stTot))
				{
					memcpy (pmb->buf.pch + len, strPath, lenPath);
					pmb->buf.pch [stTot - 1] = ASCII_NUL;
					return stTot - 1;
				}
			}
		} else
			return len;
	} else
	{	// Buffer is empty.
		return SMEMBUFfromStr (pmb, strPath, lenPath);
	}
	return 0;
}

bool SMEMBUFstrStartsWithStr (SMEMBUF *pmb, size_t len, const char *str, size_t lenStr)
{
	ubf_assert_non_NULL	(pmb);

	len		= USE_STRLEN == len		?	strlen (pmb->buf.pcc)	: len;
	lenStr	= USE_STRLEN == lenStr	?	strlen (str)			: lenStr;

	if (len < lenStr)
		return false;

	return !memcmp (pmb->buf.pcc, str, lenStr);
}

bool SMEMBUFstrEndsWithStr (SMEMBUF *pmb, size_t len, const char *str, size_t lenStr)
{
	ubf_assert_non_NULL	(pmb);

	len		= USE_STRLEN == len		?	strlen (pmb->buf.pcc)	: len;
	lenStr	= USE_STRLEN == lenStr	?	strlen (str)			: lenStr;

	if (len < lenStr)
		return false;

	return !memcmp (pmb->buf.pcc + len - lenStr, str, lenStr);
}

#ifdef STRMEMBUF_BUILD_TEST_FNCT
	bool test_strmembuf (void)
	{
		bool	b = true;
		size_t	st;

		SMEMBUF smb = SMEMBUF_INITIALISER;
		st = SMEMBUFstrFromUINT64 (&smb, 0);
		ubf_expect_bool_AND (b, 1 == st);
		ubf_expect_bool_AND (b, !memcmp ("0", smb.buf.pcc, 2));
		st = SMEMBUFstrFromUINT64 (&smb, 1);
		ubf_expect_bool_AND (b, 1 == st);
		ubf_expect_bool_AND (b, !memcmp ("1", smb.buf.pcc, 2));

		// Functions SMEMBUFstrFromUINT64 () and SMEMBUFstrconcat () together.
		st = SMEMBUFstrFromUINT64 (&smb, 99999);
		ubf_expect_bool_AND (b, 5 == st);
		ubf_expect_bool_AND (b, !memcmp ("99999", smb.buf.pcc, 6));
		st = SMEMBUFstrconcatReserve (&smb, USE_STRLEN, "11111", 5, 5);
		ubf_expect_bool_AND (b, 10 == st);
		ubf_expect_bool_AND (b, !memcmp ("9999911111", smb.buf.pcc, 11));
		ubf_expect_bool_AND (b, 15 <= smb.size);

		st = SMEMBUFfromStr (&smb, "123", 3);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("123", smb.buf.pcc, 4));
		st = SMEMBUFstrconcatReserve (&smb, 3, NULL, 0, 0);
		ubf_expect_bool_AND (b, !memcmp ("123", smb.buf.pcc, 4));
		ubf_expect_bool_AND (b, 3 == st);

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		st = SMEMBUFfromStr (&smb, "123", 3);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("123", smb.buf.pcc, 4));
		st = SMEMBUFstrconcatReserve (&smb, 3, "4", 1, 0);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, !memcmp ("1234", smb.buf.pcc, 5));

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		st = SMEMBUFfromStr (&smb, "123", 3);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("123", smb.buf.pcc, 4));
		st = SMEMBUFstrconcat (&smb, 3, NULL, 0);
		ubf_expect_bool_AND (b, !memcmp ("123", smb.buf.pcc, 4));
		ubf_expect_bool_AND (b, 3 == st);

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		// Edge cases.
		st = SMEMBUFfromStr (&smb, NULL, 0);
		ubf_expect_bool_AND (b, 0 == st);
		st = SMEMBUFstrconcatpaths (&smb, 0, "file.txt", USE_STRLEN);
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, !memcmp ("file.txt", smb.buf.pcc, 9));

		st = SMEMBUFfromStr (&smb, "path", 4);
		ubf_expect_bool_AND (b, 4 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "", USE_STRLEN);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, !memcmp ("path", smb.buf.pcc, 5));

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		st = SMEMBUFfromStr (&smb, "path1", 5);
		ubf_expect_bool_AND (b, 5 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "path2", USE_STRLEN);
		ubf_expect_bool_AND (b, 11 == st);
		ubf_expect_bool_AND (b, !memcmp ("path1\\path2", smb.buf.pcc, 12));

		st = SMEMBUFfromStr (&smb, "p1", 2);
		ubf_expect_bool_AND (b, 2 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "p2", USE_STRLEN);
		ubf_expect_bool_AND (b, 5 == st);
		ubf_expect_bool_AND (b, !memcmp ("p1\\p2", smb.buf.pcc, 6));

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		st = SMEMBUFfromStr (&smb, "p1", 2);
		ubf_expect_bool_AND (b, 2 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "p2", USE_STRLEN);
		ubf_expect_bool_AND (b, 5 == st);
		ubf_expect_bool_AND (b, !memcmp ("p1\\p2", smb.buf.pcc, 6));

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		// Funciton inserts platform separator.
		st = SMEMBUFfromStr (&smb, "p1", 2);
		ubf_expect_bool_AND (b, 2 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "\\p2", USE_STRLEN);
		ubf_expect_bool_AND (b, 5 == st);
		#ifdef PLATFORM_IS_WINDOWS
			ubf_expect_bool_AND (b, !memcmp ("p1\\p2", smb.buf.pcc, 6));
		#else
			ubf_expect_bool_AND (b, !memcmp ("p1/p2", smb.buf.pcc, 6));
		#endif

		doneSMEMBUF (&smb);
		initSMEMBUF (&smb);

		st = SMEMBUFfromStr (&smb, "p1", 2);
		ubf_expect_bool_AND (b, 2 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "/p2", USE_STRLEN);
		ubf_expect_bool_AND (b, 5 == st);
		#ifdef PLATFORM_IS_WINDOWS
			ubf_expect_bool_AND (b, !memcmp ("p1\\p2", smb.buf.pcc, 6));
		#else
			ubf_expect_bool_AND (b, !memcmp ("p1/p2", smb.buf.pcc, 6));
		#endif

		// Function retains the separator found in the buffer.
		st = SMEMBUFfromStr (&smb, "p1/", 3);
		ubf_expect_bool_AND (b, 3 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "/p2", USE_STRLEN);
		ubf_expect_bool_AND (b, 5 == st);
		ubf_expect_bool_AND (b, !memcmp ("p1/p2", smb.buf.pcc, 6));

		st = SMEMBUFfromStr (&smb, "1", 1);
		ubf_expect_bool_AND (b, 1 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, "2", USE_STRLEN);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("1\\2", smb.buf.pcc, 4));

		st = SMEMBUFfromStr (&smb, NULL, 0);
		ubf_expect_bool_AND (b, 0 == st);
		st = SMEMBUFstrconcatpaths (&smb, USE_STRLEN, NULL, 0);
		ubf_expect_bool_AND (b, 0 == st);

		// Empty UNC path.
		st = SMEMBUFfromStr (&smb, "\\\\", USE_STRLEN);
		ubf_expect_bool_AND (b, 2 == st);
		st = SMEMBUFstrconcatpaths (&smb, 2, "file.txt", USE_STRLEN);
		ubf_expect_bool_AND (b, 10 == st);
		ubf_expect_bool_AND (b, !memcmp ("\\\\file.txt", smb.buf.pcc, 11));

		// Longer UNC path.
		st = SMEMBUFfromStr (&smb, "\\\\server", USE_STRLEN);
		ubf_expect_bool_AND (b, 8 == st);
		st = SMEMBUFstrconcatpaths (&smb, 8, "file.txt", USE_STRLEN);
		ubf_expect_bool_AND (b, 17 == st);
		ubf_expect_bool_AND (b, !memcmp ("\\\\server\\file.txt", smb.buf.pcc, 18));

		st = SMEMBUFfromStrFmt (&smb, "A%sC", "B");
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("ABC", smb.buf.pcc, 4));

		st = SMEMBUFfromStr (&smb, "123", 3);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("123", smb.buf.pcc, 4));
		st = SMEMBUFstrconcatW (&smb, USE_STRLEN, L"456", USE_STRLEN);
		ubf_expect_bool_AND (b, 6 == st);
		ubf_expect_bool_AND (b, !memcmp ("123456", smb.buf.pcc, 7));

		st = SMEMBUFfromStr (&smb, NULL, 0);
		ubf_expect_bool_AND (b, 0 == st);
		ubf_expect_bool_AND (b, !memcmp ("", smb.buf.pcc, 1));
		st = SMEMBUFstrconcatW (&smb, USE_STRLEN, L"456", USE_STRLEN);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, !memcmp ("456", smb.buf.pcc, 4));

		st = SMEMBUFfromStr (&smb, NULL, 0);
		ubf_expect_bool_AND (b, 0 == st);
		bool b1 = SMEMBUFstrStartsWithStr (&smb, st, "A", 1);
		ubf_expect_bool_AND (b, false == b1);
		b1 = SMEMBUFstrEndsWithStr (&smb, st, "A", 1);
		ubf_expect_bool_AND (b, false == b1);
		st = SMEMBUFfromStr (&smb, "ABCD", USE_STRLEN);
		ubf_expect_bool_AND (b, 4 == st);
		b1 = SMEMBUFstrStartsWithStr (&smb, st, "A", 1);
		ubf_expect_bool_AND (b, true == b1);
		b1 = SMEMBUFstrEndsWithStr (&smb, st, "A", 1);
		ubf_expect_bool_AND (b, false == b1);
		b1 = SMEMBUFstrStartsWithStr (&smb, st, "D", 1);
		ubf_expect_bool_AND (b, false == b1);
		b1 = SMEMBUFstrEndsWithStr (&smb, st, "D", 1);
		ubf_expect_bool_AND (b, true == b1);
		st = SMEMBUFfromStr (&smb, "ABCD", USE_STRLEN);
		ubf_expect_bool_AND (b, 4 == st);
		b1 = SMEMBUFstrStartsWithStr (&smb, st, "BC", USE_STRLEN);
		ubf_expect_bool_AND (b, false == b1);
		b1 = SMEMBUFstrEndsWithStr (&smb, st, "BC", USE_STRLEN);
		ubf_expect_bool_AND (b, false == b1);
		b1 = SMEMBUFstrStartsWithStr (&smb, st, "AB", USE_STRLEN);
		ubf_expect_bool_AND (b, true == b1);
		b1 = SMEMBUFstrEndsWithStr (&smb, st, "CD", USE_STRLEN);
		ubf_expect_bool_AND (b, true == b1);


		return b;
	}
#endif
