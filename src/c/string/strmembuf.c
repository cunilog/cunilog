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

#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./strintuint.h"
		#include "./strmembuf.h"
		#include "./membuf.h"
		#include "./ubfmem.h"
		#include "./ubfdebug.h"
	#else
		#include "./strintuint.h"
		#include "./strmembuf.h"
		#include "./../mem/membuf.h"
		#include "./../mem/ubfmem.h"
		#include "./../dbg/ubfdebug.h"
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
	ubf_assert_non_NULL (str);
	ubf_assert_non_0 (len);

	size_t l = USE_STRLEN == len ? strlen (str) : len;
	growToSizeSMEMBUF (pmb, l + 1);
	if (isUsableSMEMBUF (pmb))
	{
		memcpy (pmb->buf.pch, str, l);
		pmb->buf.pch [l] = ASCII_NUL;
		return l;
	}
	return 0;
}

size_t SMEMBUFstrFromUINT64 (SMEMBUF *pmb, uint64_t ui)
{
	ubf_assert_non_NULL (pmb);
	
	char asc [UBF_UINT64_SIZE];
	size_t l = ubf_str_from_uint64 (asc, ui);
	return SMEMBUFfromStr (pmb, asc, l);
}
