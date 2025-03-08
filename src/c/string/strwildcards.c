/****************************************************************************************

	File:		strwildcards.h
	Why:		Wildcard functions
	OS:			C99.
	Author:		Thomas
	Created:	2022-03-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-21	Thomas			Created.

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

	#include "./strwildcards.h"
	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./memstrstr.h"
		#include "./Warnings.h"
	#else
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/memstrstr.h"
		#include "./../pre/Warnings.h"
	#endif

#endif

const char *wildCardFileName (size_t *plen, const char *ccPath)
{
	ubf_assert (NULL != ccPath);

	// Must not be NULL and not be an empty string.
	if (ccPath && ccPath [0])
	{
		size_t		stPath		= strlen (ccPath);
		const char	*ccEnd		= NULL;
		
		// Must not end with a directory separator.
		ubf_assert (0 < stPath);							// Not supported.
		ubf_assert ('\\' != ccPath [stPath - 1]);			// Not supported.
		ubf_assert ('/' != ccPath [stPath - 1]);			// Not supported.
		if (strchr (ccPath, '*') || strchr (ccPath, '\?') || ':' == ccPath [stPath - 1])
		{	// According to
			//	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew ,
			//	only the filename can contain wildcard characters.
			ccEnd = strrchr (ccPath, '\\');
			if (NULL == ccEnd)
				ccEnd = strrchr (ccPath, '/');
			if (NULL == ccEnd)
			{
				ccEnd = strrchr (ccPath, ':');
				if (ccEnd)
				{	// Jump over the directory separator.
					++ ccEnd;
				}
			}
			ubf_assert (NULL != ccEnd);
			ubf_assert (ccEnd > ccPath);
			stPath -= ccEnd - ccPath;
			if (plen)
				*plen = stPath;
			return ccEnd;
		}
	}
	if (plen)
		*plen = 0;
	return NULL;
}

size_t lenPathWithoutWildcardFileName (const char *ccPath)
{
	const char	*cc;
	size_t		stL;
	size_t		stW;
	size_t		stRet	= 0;
	
	ubf_assert (NULL != ccPath);
	if (ccPath && ccPath [0])
	{
		stL = strlen (ccPath);
		cc = wildCardFileName (&stW, ccPath);
		if (cc && stW)
			stRet = stL - stW;
		else
			stRet = stL;
	}
	return stRet;
}

static inline const char *nextPathSeparator (const char *str, size_t *idx, size_t len)
{
	ubf_assert_non_NULL (str);
	ubf_assert_non_NULL (idx);

	while (len && '/' != str [*idx] && '\\' != str [*idx])
	{
		-- len;
		++ *idx;
	}
	return (len && ('/' == str [*idx] || '\\' == str [*idx]) ? str + *idx : NULL);
}

static inline const char *nextCharOrPathSeparator (const char *str, size_t *idx, char c, size_t len)
{
	ubf_assert_non_NULL (str);
	ubf_assert_non_NULL (idx);

	while (len && '/' != str [*idx] && '\\' != str [*idx] && c != str [*idx])
	{
		-- len;
		++ *idx;
	}
	return (len && ('/' == str [*idx] || '\\' == str [*idx] || c == str [*idx]) ? str + *idx : NULL);
}

static inline const char *nextChar (const char *str, size_t *idx, char c, size_t len)
{
	ubf_assert_non_NULL (str);
	ubf_assert_non_NULL (idx);

	while (len && c != str [*idx])
	{
		-- len;
		++ *idx;
	}
	return (len && c == str [*idx] ? str + *idx : NULL);
}

enum hasGlobCharAfterStar
{
	en_globCharAfterStar,
	en_globDepleted,
	en_globCharAfterDoubleStar,
	en_globDoubleCharDepleted
};
typedef enum hasGlobCharAfterStar enGl;

static inline enGl globCharAfterStar (char *c, size_t *g, const char *ccGlob, size_t *lnGlob)
{
	ubf_assert_non_NULL (c);
	ubf_assert_non_NULL (g);
	ubf_assert_non_NULL (lnGlob);

	++ *g;

	if (*g < *lnGlob && '*' == ccGlob [*g])
	{
		++ *g;

		while (*g < *lnGlob)
		{
			*c = ccGlob [*g];
			if ('*' != *c)
				return en_globCharAfterDoubleStar;
			++ *g;
		}
		return en_globDoubleCharDepleted;
	}

	while (*g < *lnGlob)
	{
		*c = ccGlob [*g];
		if ('*' != *c)
			return en_globCharAfterStar;
		++ *g;
	}
	return en_globDepleted;
}

/*
	Comparison function or macro.
*/
#ifdef STRWILDCARDS_CHARSEQUAL_FNCT
	// For easier debugging.
	static inline bool charsEqual (char c1, char c2)
	{
		if ('/' == c1 && '\\' == c2)
			return true;
		if ('\\' == c1 && '/' == c2)
			return true;
		if (c1 == c2)
			return true;
		return false;
	}
#else
	#define charsEqual(c1, c2)							\
		(												\
				(c1 == c2)								\
			||	('/' == c1 && '\\' == c2)				\
			||	('\\' == c1 && '/' == c2)				\
		)
#endif

// Neither r nor p are uninitialised.
DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED ()
DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED ()

static inline const char *handleGlobStars	(
							bool *r,
							size_t *s, size_t *g,
							const char *ccStri, size_t *lnStri,
							const char *ccGlob, size_t *lnGlob
											)
{
	char		c;
	//const char	*p = NULL;									// Init to NULL to silence warning.
	const char	*p;												// Nah!
	enGl		gl;

	gl = globCharAfterStar (&c, g, ccGlob, lnGlob);
	ubf_assert	(
						en_globCharAfterStar		== gl
					||	en_globDepleted				== gl
					||	en_globCharAfterDoubleStar	== gl
					||	en_globDoubleCharDepleted	== gl
				);
	switch (gl)
	{
		case en_globCharAfterDoubleStar:
			p = nextChar (ccStri, s, c, *lnStri - *s);
			*r = false;
			break;
		case en_globDoubleCharDepleted:
			p = NULL;
			*r = true;
			break;
		case en_globCharAfterStar:
			p = nextCharOrPathSeparator (ccStri, s, c, *lnStri - *s);
			*r = false;
			break;
		case en_globDepleted:
			p = nextPathSeparator (ccStri, s, *lnStri - *s);
			*r = true;
			break;
	}
	return p;
}

static inline bool globMatchInt (const char *ccStri, size_t *lnStri, const char *ccGlob, size_t *lnGlob)
{
	size_t		s		= 0;
	size_t		g		= 0;
	bool		r;
	const char *p;

	while (s < *lnStri && g < *lnGlob)
	{
		switch (ccGlob [g])
		{
			case '\?':
				break;
			case '*':
				p = handleGlobStars (&r, &s, &g, ccStri, lnStri, ccGlob, lnGlob);
				if (NULL == p)
					return r;
				break;
			default:
				if (!charsEqual (ccStri [s], ccGlob [g]))
					return false;
				break;
		}
		++ s;
		++ g;
	}
	return s - *lnStri == g - *lnGlob;
}

DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED ()
DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED ()

bool globMatch (const char *ccStri, size_t lnStri, const char *ccGlob, size_t lnGlob)
{
	lnStri = USE_STRLEN == lnStri ? strlen (ccStri) : lnStri;
	lnGlob = USE_STRLEN == lnGlob ? strlen (ccGlob) : lnGlob;

	if (lnGlob)
	{
		if (lnStri)
			return globMatchInt (ccStri, &lnStri, ccGlob, &lnGlob);
		return false;
	}
	return true;
}

#ifdef STRWILDCARDS_BUILD_TEST_FNCT
	bool strwildcards_test_function (void)
	{
		bool b = true;

		/*
			Note that in C99 a question mark can either be escaped (as in "\?") or
			stand alone (as in "?"). See C99 standard, 6.4.4.4 and 6.4.5.
			Some of the tests below escape it, others don't.
		*/
		ubf_expect_bool_AND (b, true	== globMatch ("a", 0, "b", 0));
		ubf_expect_bool_AND (b, true	== globMatch ("abc", 0, "b", 0));
		ubf_expect_bool_AND (b, true	== globMatch ("a", 1, "b", 0));
		ubf_expect_bool_AND (b, false	== globMatch ("a", 1, "b", 1));
		ubf_expect_bool_AND (b, true	== globMatch ("a", 1, "a", 1));
		ubf_expect_bool_AND (b, true	== globMatch ("a/b/c", USE_STRLEN, "\?/\?/\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("abc", 3, "a*", 2));
		ubf_expect_bool_AND (b, true	== globMatch ("abc", 3, "*bc", 3));
		ubf_expect_bool_AND (b, true	== globMatch ("abc", 3, "a*c", 3));
		ubf_expect_bool_AND (b, false	== globMatch ("abc", 3, "a*d", 3));
		ubf_expect_bool_AND (b, false	== globMatch ("abc", 3, "d*d", 3));
		ubf_expect_bool_AND (b, true	== globMatch ("abc", 3, "*", 1));
		ubf_expect_bool_AND (b, false	== globMatch ("abc", 3, "d", 1));
		ubf_expect_bool_AND (b, true	== globMatch ("abc", 3, "*x", 1));
		ubf_expect_bool_AND (b, false	== globMatch ("abc", 3, "*x", 2));
		ubf_expect_bool_AND (b, true	== globMatch ("a/b/c", USE_STRLEN, "*\\*\\*", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("a/b/c", USE_STRLEN, "*\\b\\c", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("a/b/c", USE_STRLEN, "*\\d\\e", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("a/b/c", USE_STRLEN, "a\\b\\e", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("a/b/c", USE_STRLEN, "a\\b\\c", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("a/b/c", USE_STRLEN, "a\\*\\*", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("a/b/c", USE_STRLEN, "a\\*", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("abcdef", USE_STRLEN, "a\?c*f", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("abcdef", USE_STRLEN, "a\?c*fx", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("0123456789", USE_STRLEN, "0123456789", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("0123456789", USE_STRLEN, "0123\?56789", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("0123\0""456789", 11, "0123\0""\?56789", 11));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/home/user", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/home/use\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/home/us\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/home/u\?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/home/\?\?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/home\?\?\?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/hom\?\?\?\?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/h*/user", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/user", USE_STRLEN, "/h*/usxr", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/*/us*r", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/user", USE_STRLEN, "/*/us*x", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/user", USE_STRLEN, "/*/us*\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/*/us**", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/**", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/***", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/****", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/*****", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/user", USE_STRLEN, "/*/\?*", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"/*\?usr", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/usr", USE_STRLEN,	"/*\?/usr", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"/*\?*", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"/*?*", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"\?*\?*", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"\?*\?\?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"\\*\\\?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"/?\?\?\?/?\?\?", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"?home?usr", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN,	"?h*m*?u*r", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/usr", USE_STRLEN, "/**x", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/**sr", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/**r", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/**usr", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/***r", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/****r", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/*****r", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/usr", USE_STRLEN, "/*****b", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/usr", USE_STRLEN, "/*********************b", USE_STRLEN));
		ubf_expect_bool_AND (b, true	== globMatch ("/home/usr", USE_STRLEN, "/*********************r", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/home/usr", USE_STRLEN, "/**?", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/", USE_STRLEN, "/*?", USE_STRLEN));
		ubf_expect_bool_AND (b, false	== globMatch ("/", USE_STRLEN, "/**?", USE_STRLEN));

		return b;
	}
#endif
