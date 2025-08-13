/****************************************************************************************

	File:		strlineextract.h
	Why:		Line extractor.
	OS:			C99.
	Author:		Thomas
	Created:	2022-03-31

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-31	Thomas			Created.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strlineextract.h"
	#include "./strnewline.h"
	#include "./ubfcharscountsandchecks.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./ArrayMacros.h"
		#include "./unref.h"
		#ifdef STRLINEEXTRACT_BUILD_TEST_FNCT
			#include "./strmembuf.h"
		#endif
	#else
		#include "./../dbg/ubfdebug.h"
		#include "./../pre/ArrayMacros.h"
		#include "./../pre/unref.h"
		#ifdef STRLINEEXTRACT_BUILD_TEST_FNCT
			#include "./../string/strmembuf.h"
		#endif
	#endif

#endif

void InitSTRLINEINF (STRLINEINF *pi, void *pCustom)
{
	ubf_assert_non_NULL (pi);

	pi->absPosition				= 1;
	pi->charNumber				= 0;
	pi->lineNumber				= 0;
	pi->pCustom					= pCustom;
	pi->pStart					= NULL;
	pi->lnLength				= 0;
	#ifdef DEBUG
		pi->bInitialised		= true;
	#endif
}

char *ccCLineComment []	= {"//"};
char *ccULineComment []	= {"//", "#", ";", "+", "-", "!"};
char *ccSMultComment [] = {"/*"};
char *ccEMultComment [] = {"*/"};

void InitSTRLINECONFforUBFL (STRLINECONF *pc)
{
	ubf_assert_non_NULL (pc);
	pc->CharacterSet			= EN_STRLINEEXTRACT_UTF8;
	pc->tabSize					= 4;
	pc->pchLineCommentStr		= ccULineComment;
	pc->nLineCommentStr			= GET_ARRAY_LEN (ccULineComment);
	pc->pchStartMultiCommentStr	= ccSMultComment;
	pc->pchEndMultiCommentStr	= ccEMultComment;
	pc->nMultiCommentStr		= GET_ARRAY_LEN (ccSMultComment);
	#ifdef DEBUG
		pc->bInitialised		= true;
	#endif
}

void InitSTRLINECONFforC (STRLINECONF *pc)
{
	ubf_assert_non_NULL (pc);
	pc->CharacterSet			= EN_STRLINEEXTRACT_UTF8;
	pc->tabSize					= 4;
	pc->pchLineCommentStr		= ccCLineComment;
	pc->nLineCommentStr			= GET_ARRAY_LEN (ccCLineComment);
	pc->pchStartMultiCommentStr	= ccSMultComment;
	pc->pchEndMultiCommentStr	= ccEMultComment;
	pc->nMultiCommentStr		= GET_ARRAY_LEN (ccSMultComment);
	#ifdef DEBUG
		pc->bInitialised		= true;
	#endif
}
/*
	Checks that every start of a multi-line comment has a partner string
	in the array that contains the end of multi-line comments.
*/
bool SanityCheckMultiComments (STRLINECONF *pc)
{
	ubf_assert_non_NULL (pc);

	if (0 == pc->nMultiCommentStr)
		return true;
	if (pc && pc->pchStartMultiCommentStr && pc->pchEndMultiCommentStr)
	{
		size_t		n;

		for (n = 0; n < pc->nMultiCommentStr; ++ n)
		{	// Each start of a multi-line comment needs an end of a multi-line comment.
			ubf_assert_non_NULL (pc->pchStartMultiCommentStr [n]);
			ubf_assert_non_NULL (pc->pchEndMultiCommentStr [n]);
			if (NULL == pc->pchStartMultiCommentStr [n] || NULL == pc->pchEndMultiCommentStr [n])
				return false;
		}
		return true;
	}
	return false;
}

/*
	Returns true if the buffer p points to starts with the NUL terminated string
	sz. The parameter l is the length of the buffer p.

	Returns false if p is NULL.
	Returns false if l is 0.
	Returns false if sz is NULL or has no length.
*/
bool cmpBufStartsWith (const char *p, size_t l, const char *sz)
{
	ubf_assert (NULL != p);
	ubf_assert (NULL != sz);

	size_t	lc	= sz ? strlen (sz) : 0;
	if (p && lc && l && l >= lc)
	{
		return 0 == memcmp (p, sz, lc);
	}
	return false;
}

/*
	Returns the index of the found start of a multi-line comment + 1, or 0 if pb does not
	start with the start of a multi-line comment.
*/
unsigned int isStartMultiLineComment (char *pb, size_t lb, STRLINECONF *pc)
{
	ubf_assert (NULL != pb);
	ubf_assert (NULL != pc);

	unsigned int n;

	if (pc && pc->pchStartMultiCommentStr)
	{
		for (n = 0; n < pc->nMultiCommentStr; ++ n)
		{
			if (cmpBufStartsWith (pb, lb, pc->pchStartMultiCommentStr [n]))
				return n + 1;
		}
	}
	return 0;
}

/*
	Returns true if pb starts with the end string of the multi-line comment uMCn
	refers to. The parameter uMCn is the index of the start of a multi-line comment + 1
	as returned by isStartMultiLineComment ().
*/
bool isEndMultiLineComment (char *pb, size_t lb, STRLINECONF *pc, unsigned int uMCn)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (pc);
	ubf_assert (0 < uMCn);
	
	if (pc && pc->pchEndMultiCommentStr && uMCn && pc->nMultiCommentStr >= uMCn)
	{
		return cmpBufStartsWith (pb, lb, pc->pchEndMultiCommentStr [uMCn - 1]);
	}
	return false;
}

/*
	Steps pb on to the next line and updates the STRLINEINF structure pi points
	to as it goes along.
*/
void nextLine (char **pb, size_t *pl, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pl);
	ubf_assert_non_NULL (pi);

	char		*ch	= *pb;
	size_t		nls	= 0;
	size_t		jmp	= 0;
	size_t		l	= *pl;

	while (l && 0 == (nls = strIsLineEndings (ch, l, &jmp)))
	{
		-- l;
		++ ch;
		++ pi->absPosition;
	}
	if (nls)
	{
		l	-= jmp;
		ch	+= jmp;
		pi->absPosition += jmp;
		pi->charNumber = 1;
	}
	*pl = l;
	*pb = ch;
	pi->lineNumber += nls;
}

/*
	Swallows single-line comments up to the next line. Returns true if a line
	comment was swallowed.
*/
bool swallowLineComment (char **pb, size_t *pl, STRLINECONF *pc, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pc);
	ubf_assert_non_NULL (pi);

	unsigned int n	= 0;

	if (pc && pc->nLineCommentStr)
	{
		for (n = 0; n < pc->nLineCommentStr; ++ n)
		{
			if (cmpBufStartsWith (*pb, *pl, pc->pchLineCommentStr [n]))
			{
				nextLine (pb, pl, pi);
				// *pb should now point to the first character of a new line.
				return true;
			}
		}
	}
	return false;
}

/*
	Swallows a multi-line/block comment. Returns true when a block comment was swallowed.
*/
bool swallowMultiComment (char **pb, size_t *pl, STRLINECONF *pc, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pc);
	ubf_assert_non_NULL (pi);

	unsigned int	idx;
	size_t			l;
	size_t			nls;
	size_t			jmp;

	if (0 < (idx = isStartMultiLineComment (*pb, *pl, pc)))
	{
		l = strlen (pc->pchStartMultiCommentStr [idx - 1]);
		*pb += l;
		*pl -= l;
		++ pi->absPosition;
		while (*pl && **pb)
		{
			if (isEndMultiLineComment (*pb, *pl, pc, idx))
			{
				l = strlen (pc->pchEndMultiCommentStr [idx - 1]);
				*pb += l;
				*pl -= l;
				++ pi->absPosition;
				return true;
			} else
			{
				nls = strIsLineEndings (*pb, *pl, &jmp);
				if (nls)
				{
					pi->lineNumber	+= nls;
					pi->absPosition	+= jmp;
					pi->charNumber = 1;
					*pb += jmp;
					*pl -= jmp;
				} else
				{
					*pb += 1;
					*pl -= 1;
					++ pi->absPosition;
				}
			}
		}
		ubf_assert_msg (false, "Error: End of block comment missing.");
	}
	return false;
}

/*
	Returns true when white space or a new line was swallowed.
*/
bool swallowEmptyAndWhiteSpaceLines (char **pb, size_t *pl, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pl);
	ubf_assert_non_NULL (pi);
	
	size_t	nls;
	size_t	jmp;
	bool	bRet	= false;
	
	if (pb && *pb && pl && pi)
	{
		while (*pb && *pl)
		{
			char	c;
			
			c = **pb;
			if (isWhiteSpace (c))
			{
				*pb += 1;
				*pl -= 1;
				++ pi->absPosition;
				++ pi->charNumber;
				bRet = true;
			} else
				break;
		}
		nls = strIsLineEndings (*pb, *pl, &jmp);
		if (nls)
		{
			pi->lineNumber	+= nls;
			pi->absPosition	+= jmp;
			*pb += jmp;
			*pl -= jmp;
			bRet = true;
		}
	}
	return bRet;
}

/*
	Returns the new length of pb when trailing white space is removed.
*/
size_t getLengthTrailingWhiteSpaceRemoved (char *pb, size_t l)
{
	ubf_assert_non_NULL (pb);
	ubf_assert (0 < l);

	while (l && isWhiteSpace (pb [l - 1]))
	{
		-- l;
	}
	return l;
}

/*
	Returns the length of a line.
*/
size_t getLineLength (char *pb, size_t lb) //, STRLINECONF *pc)
{
	ubf_assert_non_NULL (pb);

	size_t	nls		= 0;
	size_t	jmp;
	char	*p		= pb;
	size_t	r		= 0;

	while (*p && lb && 0 == (nls = strIsLineEndings (p, lb, &jmp)))
	{
		++ p;
		-- lb;
	}
	if (nls || 0 == lb)
	{
		r = p - pb;
		// Comment out the following line if trailing white space should not be removed.
		//	This should probably be configurable in the future.
		r = getLengthTrailingWhiteSpaceRemoved (pb, r);
	}
	return r;
}

/*
	The UTF-8 payload line extractor.
*/
unsigned int StrLineExtractU8	(
				char					*pBuf,
				size_t					lenBuf,
				STRLINECONF				*pConf,
				StrLineExtractCallback	cb,
				void					*pCustom
								)
{
	unsigned int		uiRet	= 0;						// Return value; counts how often
															//	the callback function has been
															//	called.

	ubf_assert_non_NULL (pConf);

	lenBuf = USE_STRLEN == lenBuf ? strlen (pBuf) : lenBuf;

	// This is the only character set we support at the moment.
	ubf_assert (EN_STRLINEEXTRACT_UTF8 == pConf->CharacterSet);

	if (!SanityCheckMultiComments (pConf))
		return UINT_MAX;

	STRLINEINF			sLineInfo;
	bool				cbRet;
	bool				b;

	if (pBuf)
	{
		InitSTRLINEINF (&sLineInfo, pCustom);
		sLineInfo.lineNumber = 1;						// Line 1 unless buffer empty.
		while (lenBuf)
		{
			do
			{
				b = swallowLineComment (&pBuf, &lenBuf, pConf, &sLineInfo);
				b |= swallowMultiComment (&pBuf, &lenBuf, pConf, &sLineInfo);
				b |= swallowEmptyAndWhiteSpaceLines (&pBuf, &lenBuf, &sLineInfo);
			} while (b);
			if (lenBuf)
			{
				// We now got a single line.
				sLineInfo.lnLength		= getLineLength (pBuf, lenBuf); //, pConf);
				sLineInfo.pStart		= pBuf;
				sLineInfo.charNumber	= 0;			// Currently not supported.
				if (cb)
				{
					cbRet = (*cb) (&sLineInfo);
					++ uiRet;
					if (!cbRet)
						break;
				}
				pBuf	+= sLineInfo.lnLength;
				lenBuf	-= sLineInfo.lnLength;
			}
		}
	}
	return uiRet;
}

unsigned int StrLineExtract	(
				void					*pBuf,
				size_t					lenBuf,
				STRLINECONF				*pConf,
				StrLineExtractCallback	cb,
				void					*pCustom
							)
{
	ubf_assert_non_NULL (pBuf);

	// Default STRLINECONF.
	STRLINECONF			conf;
	InitSTRLINECONFforUBFL (&conf);

	STRLINECONF			*pC		= pConf ? pConf : &conf;
	switch (pC->CharacterSet)
	{
		case EN_STRLINEEXTRACT_UTF8:
			return StrLineExtractU8 (pBuf, lenBuf, pC, cb, pCustom);
		case EN_STRLINEEXTRACT_UTF16:
			ubf_assert_msg (false, "Not implemented.");
			return 0;
	}
	return 0;
}

char *ccSdOpenQuotes []	= {"\"", "'", "[", "{"};
char *ccSdClosQuotes []	= {"\"", "'", "]", "}"};
char *ccSdEqualSigns [] = {":=", "=", ":", "->", "<-"};

/*
	strlineextractIsOpenQuote

	Returns the index of an open quote or 0 if szLine doesn't start with an open
	quote.
*/
unsigned int strlineextractIsOpenQuote	(
		const char		*szLine,			size_t			lnLine,
		unsigned int	nQuotes,
		const char		**pszOpenQuotes
										)
{
	for (unsigned int q = 0; q < nQuotes; ++ q)
	{
		if (cmpBufStartsWith (szLine, lnLine, pszOpenQuotes [q]))
			return q;
	}
	return 0;
}

static unsigned int strlineextractIsCloseQuote	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszCloseQuotes,
		unsigned int	idxCloseQuote
												)
{
	return cmpBufStartsWith (szLine, lnLine, pszCloseQuotes [idxCloseQuote]);
}

bool strlineextractIsEqual	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszEquals,		unsigned int	nEquals
							)
{
	for (unsigned int q = 0; q < nEquals; ++ q)
	{
		if (cmpBufStartsWith (szLine, lnLine, pszEquals [q]))
			return true;
	}
	return false;
}

/*
	Extracts a key or a value by taking quotations, if any, into consideration.
	The key or value is extracted without quotes. If no quotes are encountered,
	the key or value is extracted up to the last character before white space
	before an equality sign, or, if no equality sign is found, up to the last
	character before white space.
	
	If the key or value is quoted, the key or value inside the quotes is extracted.
	The function fails (returns false) if no closing quote is found.
*/
bool strlineextractKeyOrValue	(
		const char		**pszKeyOrVal,		size_t			*plnKeyOrVal,
		const char		*szLine,			size_t			lnLine,
		unsigned int	nQuotes,
		const char		**pszOpenQuotes,
		const char		**pszClosQuotes,
		const char		**pszEquals,		unsigned int	nEquals
								)
{
	ubf_assert_non_NULL	(pszKeyOrVal);
	ubf_assert_non_NULL	(plnKeyOrVal);
	ubf_assert_non_NULL	(szLine);
	ubf_assert_non_0	(lnLine);
	ubf_assert			(!isWhiteSpace (szLine [0]));

	lnLine = USE_STRLEN ? strlen (szLine) : lnLine;
	const char *szRet;
	const char *szEnd;
	unsigned int uQuote = strlineextractIsOpenQuote (szLine, lnLine, nQuotes, pszOpenQuotes);
	if (uQuote)
	{
		size_t lnOpenQuote = strlen (pszOpenQuotes [uQuote]);
		szLine += lnOpenQuote;
		lnLine -= lnOpenQuote;
		szRet = szLine;
		while (lnLine)
		{
			size_t uClose = strlineextractIsCloseQuote (szLine, lnLine, pszClosQuotes, uQuote);
			if (uClose)
			{
				*plnKeyOrVal = szLine - szRet;
				*pszKeyOrVal = szRet;
				return true;
			}
			++ szLine;
			-- lnLine;
		}
		// No closing quote. The key or value is incomplete.
		return false;
	} else
	{
		szRet = szLine;
		szEnd = NULL;
		while (lnLine)
		{
			if	(
						!isWhiteSpace (szLine [0])
					&&	!strlineextractIsEqual (szLine, lnLine, pszEquals, nEquals)
				)
			{
				szEnd = szLine;
			}
			++ szLine;
			-- lnLine;
			if (strlineextractIsEqual (szLine, lnLine, pszEquals, nEquals))
				break;
		}
		if (szEnd)
			szLine = szEnd + 1;
		*plnKeyOrVal = szLine - szRet;
		*pszKeyOrVal = szRet;
		return true;
	}
}

bool strlineextractKeyValue	(
		const char		*szKey,				size_t			*plnKey,
		const char		*szVal,				size_t			*plnVal,
		const char		*szLine,			size_t			lnLine,
		unsigned int	nQuotes,
		const char		**pszOpenQuotes,
		const char		**pzClosQuotes,
		const char		**pszEquals,		unsigned int	nEquals
							)
{
	if (NULL == szLine)
		return false;
	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;
	if (0 == lnLine)
		return false;

	#ifdef DEBUG
		UNUSED (nQuotes);
		UNUSED (pszOpenQuotes);
		UNUSED (pzClosQuotes);
		UNUSED (pszEquals);
		UNUSED (nEquals);
	#endif

	ubf_assert_non_NULL (szKey);
	ubf_assert_non_NULL (plnKey);
	ubf_assert_non_NULL (szVal);
	ubf_assert_non_NULL (plnVal);

	// No white space is allowed at the start of szLine. White space must be
	//	removed before the function is called.
	ubf_assert (' '		!= szLine [0]);
	ubf_assert ('\b'	!= szLine [0]);
	ubf_assert ('\t'	!= szLine [0]);
	ubf_assert ('\v'	!= szLine [0]);
	ubf_assert ('\f'	!= szLine [0]);
	ubf_assert (!isWhiteSpace (szLine [0]));

	szKey = szLine;

	return false;
}

#ifdef STRLINEEXTRACT_BUILD_TEST_FNCT
	#define STRLINEEXTRACT_TEST_STRING_NUM		(10)

	typedef struct strlinextcstm
	{
		size_t	n;
		char	*strs	[STRLINEEXTRACT_TEST_STRING_NUM];	// To test the extracted strings.
		size_t	sts		[STRLINEEXTRACT_TEST_STRING_NUM];	// Lengths of extracted strings.
	} STRLINEXTCSTM;

	bool ourLinextractCB (STRLINEINF *psli)
	{
		ubf_assert_non_NULL (psli);

		STRLINEXTCSTM	*plex	= psli->pCustom;
		char			*szLine	= psli->pStart;
		size_t			lnLine	= psli->lnLength;


		ubf_assert (plex->n < STRLINEEXTRACT_TEST_STRING_NUM);
		plex->strs [plex->n] = strdup_l (szLine, lnLine);
		++ plex->n;

		return true;
	}

	bool test_strlineextract (void)
	{
		bool b = true;

		STRLINECONF		conf;
		InitSTRLINECONFforUBFL (&conf);
		ubf_expect_bool_AND (b, SanityCheckMultiComments (&conf));
		InitSTRLINECONFforC (&conf);
		ubf_expect_bool_AND (b, SanityCheckMultiComments (&conf));

		char sz [1024];
		char *ch;
		strcpy (sz, "This is a string.");
		ubf_expect_bool_AND (b, false == cmpBufStartsWith ("ABC", 0, ""));
		ubf_expect_bool_AND (b, false == cmpBufStartsWith (sz, 0, ""));
		ubf_expect_bool_AND (b, false == cmpBufStartsWith (sz, strlen (sz), ""));
		ubf_expect_bool_AND (b, true == cmpBufStartsWith (sz, strlen (sz), "This"));
		ubf_expect_bool_AND (b, true == cmpBufStartsWith (sz, strlen (sz), "This is"));
		ubf_expect_bool_AND (b, true == cmpBufStartsWith (sz, strlen (sz), "This is a string."));
		ubf_expect_bool_AND (b, true == cmpBufStartsWith (sz, 5, "This "));

		unsigned int ui;
		strcpy (sz, "/*");
		ui = isStartMultiLineComment (sz, 2, &conf);
		ubf_expect_bool_AND (b, 1 == ui);
		sz [0] = '.';
		ui = isStartMultiLineComment (sz, 2, &conf);
		ubf_expect_bool_AND (b, 0 == ui);
		strcpy (sz, "/* Text between */");
		ui = isStartMultiLineComment (sz, strlen (sz), &conf);
		ubf_expect_bool_AND (b, 1 == ui);
		bool br = isEndMultiLineComment (sz, 2, &conf, ui);
		ch = sz + 2;
		while (*ch != '*')
			++ ch;
		br = isEndMultiLineComment (sz, strlen (sz), &conf, ui);
		ubf_expect_bool_AND (b, false == br);
		br = isEndMultiLineComment (ch, 2, &conf, ui);
		ubf_expect_bool_AND (b, true == br);

		STRLINEINF	inf;
		InitSTRLINEINF (&inf, (void *) 73);
		ubf_expect_bool_AND (b, (void *) 73 == inf.pCustom);

		STRLINEXTCSTM	cust;
		cust.n = 0;
		for (size_t ux = 0; ux < STRLINEEXTRACT_TEST_STRING_NUM; ++ ux)
		{
			cust.strs	[ux] = NULL;
			cust.sts	[ux]	= 0;
		}

		char *szTst =	"; 12345\n"
						"First line\n"
						"/*\n"
						"A text.\n"
						"*/\n"
						"   \t   ABCDEFG\n"
						"/*\n"
						"A text.\n"
						"*/\n"
						;
		InitSTRLINECONFforUBFL (&conf);
		inf.pCustom = &cust;
		size_t n = 0;
		StrLineExtract (szTst, USE_STRLEN, &conf, ourLinextractCB, &cust);
		ubf_expect_bool_AND (b, 2 == cust.n);
		ubf_expect_bool_AND (b, !memcmp ("First line", cust.strs [n ++], 10));
		ubf_expect_bool_AND (b, !memcmp ("ABCDEFG", cust.strs [n ++], 7));

		for (size_t ux = 0; ux < STRLINEEXTRACT_TEST_STRING_NUM; ++ ux)
		{
			if (cust.strs [ux])
				ubf_free (cust.strs [ux]);
			cust.strs	[ux] = NULL;
			cust.sts	[ux]	= 0;
		}

		const char	*szKey	= NULL;
		size_t		lnKey	= 0;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key=Val", 7, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 0 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 7;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key=Val", 7, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 7 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key", 3, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key ", 3, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key ", 4, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key  ", 3, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key  ", 5, 0, NULL, NULL, ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key\t\t\t\t     ", USE_STRLEN, 0, NULL, NULL,
				ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key\t\t\t\t     =  jjjj", USE_STRLEN, 0, NULL, NULL,
				ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "Key number 1\t\t\t\t     =  jjjj", USE_STRLEN, 0, NULL, NULL,
				ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 12 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key number 1", szKey, 12));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, "[Key number 1]\t\t\t\t     =  jjjj", USE_STRLEN,
				GET_ARRAY_LEN (ccSdOpenQuotes), ccSdOpenQuotes, ccSdClosQuotes,
				ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 12 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key number 1", szKey, 12));

		szKey = NULL;
		lnKey = 4000;
		// Should fail because missing closing quote.
		//	The parameters szKey and lnKey should not change.
		b &= !strlineextractKeyOrValue	(
				&szKey, &lnKey, "[Key number 1\t\t\t\t     =  jjjj", USE_STRLEN,
				GET_ARRAY_LEN (ccSdOpenQuotes), ccSdOpenQuotes, ccSdClosQuotes,
				ccSdEqualSigns, GET_ARRAY_LEN (ccSdEqualSigns)
										);
		ubf_expect_bool_AND (b, 4000 == lnKey);
		ubf_expect_bool_AND (b, NULL == szKey);

		return b;
	}
#endif
