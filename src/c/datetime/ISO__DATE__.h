/****************************************************************************************

	File		ISO__DATE__.h
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

#ifndef ISO__DATE__H
#define ISO__DATE__H

#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

#ifndef LEN_ISO8601DATE
#define LEN_ISO8601DATE						(10)				// "YYYY-MM-DD"
#endif
#ifndef SIZ_ISO8601DATE
#define SIZ_ISO8601DATE						(LEN_ISO8601DATE + 1)
#endif

#ifndef LEN_ISO8601DATETIMESTAMP_NO_OFFS
#define LEN_ISO8601DATETIMESTAMP_NO_OFFS	(19)				// "YYYY-MM-DD hh:mm:ss"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMP_NO_OFFS	(LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1)
#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef _ISO_DATE_
#define _ISO_DATE_						"_ISO_DATE_"
#endif

EXTERN_C_BEGIN

/*
	szBuild_ISO__DATE__

	Returns the build date in ISO 8601 format, like "2024-10-30".

	The function is only re-entrant after it returned from its first invocation.
*/
const char *szBuild_ISO__DATE__ (void);
TYPEDEF_FNCT_PTR (const char *, szBuild_ISO__DATE__) (void);

/*
	szBuild_ISO__TIME__

	Returns the build time, like "16:20:14". This function/macro only exists for
	completeness, because the predefinded macro __TIME__ serves the very same
	purpose, which is in fact precisely what the function/macro returns.
*/
#if defined (DEBUG) && !defined (CUNILOG_BUILD_SHARED_LIBRARY)
	const char *szBuild_ISO__TIME__ (void);
#else
	#define szBuild_ISO__TIME__()	__TIME__
#endif

/*
	szBuild_ISO__DATE__TIME__

	Returns the build date and time in ISO 8601 format, like "2024-10-30 23:59:01".
	Note that ISO 8601 requires a 'T' between date and time, while this function
	puts a blank (space, ' ') in its place instead.

	The function is only re-entrant after it returned from its first invocation, or
	after the function szBuild_ISO__DATE__ () has been called.
*/
const char *szBuild_ISO__DATE__TIME__ (void);
TYPEDEF_FNCT_PTR (const char *, szBuild_ISO__DATE__TIME__) (void);

/*
	replace_ISO_DATE_

	Replaces all occurrences of "_ISO_DATE_" in sz with the build date in ISO 8601
	format, like "2024-10-30". Note that the two strings have the same length, hence
	the replacement(s) won't change the length of sz.
	
	The parameter len can be (size_t) -1, in which case the function calls strlen ()
	to obtain it. For convenience, the macro USE_STRLEN is defined as ((size_t) -1).

	The function returns the amount of replacements carried out.

	The function is only re-entrant after it returned from its first invocation, or
	after the function szBuild_ISO__DATE__ () has been called.
*/
size_t replace_ISO_DATE_ (char *sz, size_t len);
TYPEDEF_FNCT_PTR (size_t, replace_ISO_DATE_) (char *sz, size_t len);

EXTERN_C_END

#endif														// Of #ifndef ISO__DATE__H.
