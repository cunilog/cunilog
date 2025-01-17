/****************************************************************************************

	File:		strcustomfmt.c
	Why:		Functions for user-defined format specifiers.
	OS:			C99
	Author:		Thomas
	Created:	2024-12-26

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-12-26	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strcustomfmt.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./memstrstr.h"
		#include "./ubfdebug.h"
		#include "./unref.h"
	#else
		#include "./../mem/memstrstr.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../pre/unref.h"
	#endif

#endif

/*
	This function does NOT set *pidx when it returns NULL (when no custom format specifier can
	be found). Debug versions set *pidx to (size_t) -1 in this case, which hopefully causes an access
	violation somewhere in the caller. So, when you call this function, check for (size_t) -1 with
	an assertion, like:

	size_t idx;
	const char *cc = strcustomfmtFindNextCust (&idx, ...);
	ubf_assert ((size_t) -1 != idx);

	If you use your own assertion macro(s), make sure this isn't done in release versions to avoid
	undefined behaviour. Check the return value first! If the function returns NULL, *pidx is NOT
	set!
*/
static inline const char *strcustomfmtFindNextCust (size_t *pidx, SSTRCUSTFMTBASE *pb, const char *cust, size_t len)
{
	ubf_assert_non_NULL	(pidx);
	ubf_assert_non_NULL	(pb);
	ubf_assert_non_NULL	(cust);
	ubf_assert			((size_t) -1 != len);

	size_t	idx;
	
	while (len)
	{
		idx = 0;
		while (idx < pb->n)
		{
			ubf_assert_non_NULL	(pb->psstrcustfmt [idx].ccFormatSpecifier);
			ubf_assert_non_0	(pb->psstrcustfmt [idx].ccFormatSpecifier [0]);
			ubf_assert_non_0	(pb->psstrcustfmt [idx].lenFormatSpecifier);
			ubf_assert			(USE_STRLEN != pb->psstrcustfmt [idx].lenFormatSpecifier);

			if (len >= pb->psstrcustfmt [idx].lenFormatSpecifier)
			{
				if (!memcmp (cust, pb->psstrcustfmt [idx].ccFormatSpecifier, pb->psstrcustfmt [idx].lenFormatSpecifier))
				{
					*pidx = idx;
					return cust;
				}
			}
			++ idx;
		}
		++ cust;
		-- len;
	}
	#ifdef DEBUG
		*pidx = (size_t) -1;
	#endif
	return NULL;
}

static inline size_t getStringLength (const char *cc, size_t len)
{
	return USE_STRLEN == len ? strlen (cc) : len;
}

size_t strcustomfmtGetRqSizeCustVA (SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, va_list ap)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (cust);

	void		*v;
	size_t		idx;

	size_t		len = getStringLength (cust, lenCust);
	size_t		ret = len;
	const char	*cp = cust;
	const char	*cc	= strcustomfmtFindNextCust (&idx, pb, cust, len);
	while (cc)
	{
		ubf_assert_non_NULL	(pb->psstrcustfmt [idx].ccFormatSpecifier);
		ubf_assert_non_0	(pb->psstrcustfmt [idx].ccFormatSpecifier [0]);
		ubf_assert_non_0	(pb->psstrcustfmt [idx].lenFormatSpecifier);
		ubf_assert			(USE_STRLEN != pb->psstrcustfmt [idx].lenFormatSpecifier);

		v	= va_arg (ap, void *);
		len	-= pb->psstrcustfmt [idx].lenFormatSpecifier;
		cp	+= cc - cp + pb->psstrcustfmt [idx].lenFormatSpecifier;
		ret	-= pb->psstrcustfmt [idx].lenFormatSpecifier;
		ret	+= pb->psstrcustfmt [idx].getRqSize (v, &pb->psstrcustfmt [idx]);
		cc	= strcustomfmtFindNextCust (&idx, pb, cp, len);
	}
	return ret;
}

size_t strcustomfmtGetRqSizeCust (SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, ...)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (cust);

	va_list ap;
	va_start (ap, cust);
	size_t ret = strcustomfmtGetRqSizeCustVA (pb, lenCust, cust, ap);
	va_end (ap);

	return ret;
}

static inline void storeNonFormatSpecifiers (char **buf, size_t *siz, const char *txt, size_t len)
{
	ubf_assert_non_NULL (buf);
	ubf_assert_non_NULL (*buf);
	ubf_assert_non_NULL (siz);

	memcpy (*buf, txt, len);
	*buf += len;
	*siz -= len;
}

size_t strcustomfmtStoreDataCustVA (char *strBuf, size_t sizBuf, SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, va_list ap)
{
	ubf_assert_non_NULL (strBuf);
	ubf_assert_non_0	(sizBuf);
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (cust);

	void *v;
	size_t		idx;

	size_t		s;
	char		*cb = strBuf;
	size_t		sb	= sizBuf;
	size_t		len = getStringLength (cust, lenCust);
	size_t		ret = len;
	const char	*cp = cust;
	const char	*cc = strcustomfmtFindNextCust (&idx, pb, cust, len);
	while (cc)
	{
		ubf_assert_non_NULL	(pb->psstrcustfmt [idx].ccFormatSpecifier);
		ubf_assert_non_0	(pb->psstrcustfmt [idx].ccFormatSpecifier [0]);
		ubf_assert_non_0	(pb->psstrcustfmt [idx].lenFormatSpecifier);
		ubf_assert			(USE_STRLEN != pb->psstrcustfmt [idx].lenFormatSpecifier);

		v	= va_arg (ap, void *);
		len	-= pb->psstrcustfmt [idx].lenFormatSpecifier;
		storeNonFormatSpecifiers (&cb, &sb, cp, cc - cp);
		len	-= cc - cp;
		cp	+= cc - cp + pb->psstrcustfmt [idx].lenFormatSpecifier;
		ret	-= pb->psstrcustfmt [idx].lenFormatSpecifier;
		s	= pb->psstrcustfmt [idx].storeData (cb, sb, v, &pb->psstrcustfmt [idx]);
		ret	+= s;
		cb	+= s;
		sb	-= s;
		cc	= strcustomfmtFindNextCust (&idx, pb, cp, len);
	}
	if (len)
	{
		memcpy (cb, cp, len);
		cb += len;
	}
	*cb = ASCII_NUL;
	return ret;
}

size_t strcustomfmtStoreDataCust (char *strBuf, size_t sizBuf, SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, ...)
{
	ubf_assert_non_NULL (strBuf);
	ubf_assert_non_0	(sizBuf);
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (cust);

	va_list ap;
	va_start (ap, cust);
	size_t ret = strcustomfmtStoreDataCustVA (strBuf, sizBuf, pb, lenCust, cust, ap);
	va_end (ap);
	return ret;
}

#ifdef STRCUSTOMFMT_BUILD_TEST_FNCTS

	size_t ourReqSize (void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT)
	{
		UNUSED (pSSTRCUSTFMT);

		if (pCustFmtArg)
		{
			return 4;
		} else
		{
			return 10;
		}
	}

	size_t ourStoData (char *szBuf, size_t len, void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT)
	{
		UNUSED (len);
		UNUSED (pSSTRCUSTFMT);

		if (pCustFmtArg)
		{
			memcpy (szBuf, "ABCD", 4);
			return 4;
		} else
		{
			memcpy (szBuf, "0123456789", 10);
			return 10;
		}
	}

	// Size to remember.
	size_t size2;

	size_t theSize2 (void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT)
	{
		ubf_assert_non_NULL (pCustFmtArg);
		ubf_assert_non_NULL (pSSTRCUSTFMT);

		const char *ccCustomFormatArgumentExpanded = pCustFmtArg;
		size2 = strlen (ccCustomFormatArgumentExpanded) + 1;
		SSTRCUSTFMT *p = pSSTRCUSTFMT;
		p->pCustom = &size2;
		return size2 - 1;
	}

	size_t theData2 (char *szBuf, size_t len, void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT)
	{
		ubf_assert_non_NULL (pCustFmtArg);
		ubf_assert_non_NULL (pSSTRCUSTFMT);

		const char *ccCustomFormatArgumentExpanded = pCustFmtArg;
		SSTRCUSTFMT *p = pSSTRCUSTFMT;
		size_t size = *(size_t *)p->pCustom;
		size_t s2 = strlen (ccCustomFormatArgumentExpanded) + 1;
		ubf_assert (s2 == size);
		ubf_assert (s2 <= len);
		memcpy (szBuf, ccCustomFormatArgumentExpanded, s2);
		return size - 1;
	}

	void TestStrCustomFmt (void)
	{
		SSTRCUSTFMTBASE	b;
		SSTRCUSTFMT		f [3];

		// Format specifiers only for now.
		f [0].ccFormatSpecifier		= "{a}";
		f [0].lenFormatSpecifier	= 3;
		f [1].ccFormatSpecifier		= "#1";
		f [1].lenFormatSpecifier	= 2;
		f [2].ccFormatSpecifier		= "{x}";
		f [2].lenFormatSpecifier	= 3;

		b.psstrcustfmt				= f;
		b.n							= 3;

		const char	*cc;
		size_t		idx;

		cc = strcustomfmtFindNextCust (&idx, &b, "{v}", 3);
		ubf_assert_NULL (cc);
		cc = strcustomfmtFindNextCust (&idx, &b, "{a}", 3);
		ubf_assert (!memcmp ("{a}", cc, 4));
		cc = strcustomfmtFindNextCust (&idx, &b, "   ", 3);
		ubf_assert_NULL (cc);
		cc = strcustomfmtFindNextCust (&idx, &b, "#1", 2);
		ubf_assert (!memcmp ("#1", cc, 2));

		// Let's check the callback functions.
		f [0].getRqSize				= ourReqSize;
		f [0].storeData				= ourStoData;
		size_t s1 = strcustomfmtGetRqSizeCust (&b, 3, "{a}", NULL);
		char ch [256];
		size_t s2 = strcustomfmtStoreDataCust (ch, 256, &b, 3, "{a}", NULL);
		ubf_assert (s1 == s2);
		ubf_assert (!memcmp (ch, "0123456789", 10));

		// A bit more complicated.
		f [1].getRqSize				= ourReqSize;
		f [1].storeData				= ourStoData;
		memset (ch, 0, 256);
		char	x = 0;
		s1 = strcustomfmtGetRqSizeCust (&b, USE_STRLEN, "None {a} // #1, {a}xxx", NULL, &x, NULL);
		s2 = strcustomfmtStoreDataCust (ch, 256, &b, USE_STRLEN, "None {a} // #1, {a}xxx", NULL, &x, NULL);
		ubf_assert (s1 == s2);
		ubf_assert (!memcmp (ch, "None 0123456789 // ABCD, 0123456789xxx", 39));

		// Note that the spec says that space for a NUL terminator is required, hence s1 + 1.
		s1 = strcustomfmtGetRqSizeCust (&b, USE_STRLEN, "None {a} // #1, {a}xxx", NULL, &x, NULL);
		s2 = strcustomfmtStoreDataCust (ch, s1 + 1, &b, USE_STRLEN, "None {a} // #1, {a}xxx", NULL, &x, NULL);
		ubf_assert (s1 == s2);
		ubf_assert (!memcmp (ch, "None 0123456789 // ABCD, 0123456789xxx", 39));

		f [2].getRqSize = theSize2;
		f [2].storeData = theData2;
		s1 = strcustomfmtGetRqSizeCust (&b, USE_STRLEN,	"This is our {x}.", "custom format expanded");
		s2 = strcustomfmtStoreDataCust (ch, s1 + 1, &b, USE_STRLEN, "This is our {x}.", "custom format expanded");
		ubf_assert (s1 == s2);
		ubf_assert (!memcmp (ch, "This is our custom format expanded.", 36));

		// Empty. The spec says that even if the length is 0 there's still one octet for a
		//	NUL terminator.
		memset (ch, 0, 256);
		s1 = strcustomfmtGetRqSizeCust (&b, USE_STRLEN, "", NULL, &x, NULL);
		s2 = strcustomfmtStoreDataCust (ch, 256, &b, USE_STRLEN, "", NULL, &x, NULL);
		ubf_assert (s1 == s2);
		s1 = strcustomfmtGetRqSizeCust (&b, 0, "", NULL, &x, NULL);
		s2 = strcustomfmtStoreDataCust (ch, 256, &b, 0, "", NULL, &x, NULL);
		ubf_assert (s1 == s2);

	}

#endif														// Of #ifdef STRCUSTOMFMT_BUILD_TEST_FNCTS.
