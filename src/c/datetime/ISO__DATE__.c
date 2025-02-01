/****************************************************************************************

	File		ISO__DATE__.c
	Why:		Predefined macros __DATE__ and __TIME__ in ISO 8601 format.
	OS:			C99
	Created:	2024-10-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-29	Thomas			Created.

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

#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ISO__DATE__.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfmem.h"
		#include "./memstrstr.h"
		#include "./Warnings.h"
		#include "./ubfdebug.h"
	#else
		#include "./../mem/ubfmem.h"
		#include "./../mem/memstrstr.h"
		#include "./../pre/Warnings.h"
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

// This is what the preprocessor gives us. See
//	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html and
//	https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170 .
//	__DATE__: "Jan 14 2012".
//	__TIME__: "23:59:01".
static const char cc__DATE__ [] = __DATE__;
static const char cc__TIME__ [] = __TIME__;

#ifdef NEED_CCDTMNTHS
const char ccdtMnths [12][4] =
		{"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
#endif

static const char *ccDigMns [12] =	{
			"01",  "02",  "03",  "04",  "05",  "06",  "07",  "08",  "09",  "10",  "11",  "12"
									};

static char szISO__DATE__ [SIZ_ISO8601DATE];

const char *szBuild_ISO__DATE__ (void)
{
	ubf_assert (11	== strlen (cc__DATE__));

	/*
		if (szISO__DATE__ [0])
			return szISO__DATE__;

		In case of race condition in multi-threaded applications, this is probably
		a more appropriate check:
	*/
	if (szISO__DATE__ [LEN_ISO8601DATE - 1])
		return szISO__DATE__;

	int m;
	for (m = 0; m < 12; ++ m)
	{
		if (!memcmp (ccdtMnths [m], cc__DATE__, 3))
			break;
	}
	// Year, like "2024".
	memcpy (szISO__DATE__, cc__DATE__ + 7, 4);
	szISO__DATE__ [4] = '-';
	// Month, like "10".
	memcpy (szISO__DATE__ + 5, ccDigMns [m], 2);
	szISO__DATE__ [7] = '-';
	// Day, like "30".
	memcpy (szISO__DATE__ + 8, cc__DATE__ + 4, 2);
	// The predefined macro __DATE__ places a space before the day.
	//	We however want a '0'.
	if (' ' == *(szISO__DATE__ + 8))
		szISO__DATE__ [8] = '0';
	szISO__DATE__ [LEN_ISO8601DATE] = '\0';
	return szISO__DATE__;
}

#ifdef DEBUG
	const char *szBuild_ISO__TIME__ (void)
	{
		ubf_assert (8 == strlen (cc__TIME__));

		return cc__TIME__;
	}
#endif

static char szISO__DATE__TIME__ [SIZ_ISO8601DATETIMESTAMP_NO_OFFS];

const char *szBuild_ISO__DATE__TIME__ (void)
{
	ubf_assert (11	== strlen (cc__DATE__));
	ubf_assert (8	== strlen (cc__TIME__));

	/*
		if (szISO__DATE__TIME__ [0])
			return szISO__DATE__TIME__;

		In case of race condition in multi-threaded applications, this is probably
		a more appropriate check:
	*/
	if (szISO__DATE__TIME__ [SIZ_ISO8601DATETIMESTAMP_NO_OFFS - 1])
		return szISO__DATE__TIME__;
	
	szBuild_ISO__DATE__ ();
	memcpy (szISO__DATE__TIME__, szISO__DATE__, LEN_ISO8601DATE);
	szISO__DATE__TIME__ [LEN_ISO8601DATE] = ' ';
	memcpy (szISO__DATE__TIME__ + LEN_ISO8601DATE + 1, cc__TIME__, 9);
	return szISO__DATE__TIME__;
}

DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

size_t replace_ISO_DATE_ (char *sz, size_t len)
{
	szBuild_ISO__DATE__ ();

	size_t l = USE_STRLEN == len ? strlen (sz) : len;
	if (LEN_ISO8601DATE > l)
		return 0;

	size_t	r		= 0;
	char	*check	= sz;
	char	*found;

	while ((found = memstrstr (check, l, "_ISO_DATE_", LEN_ISO8601DATE)))
	{
		memcpy (found, szISO__DATE__, LEN_ISO8601DATE);
		check = found + LEN_ISO8601DATE;
		if (check + LEN_ISO8601DATE < sz + l)
		{
			l -= check - sz;
			++ r;
		} else
			break;
	}
	return r;
}

DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()
