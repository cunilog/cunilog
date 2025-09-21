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

const char		*ccCulStdLineCComment	[]	= {"//"};
unsigned int	nCulStdLineCComment			= GET_ARRAY_LEN (ccCulStdLineCComment);

const char		*ccCulStdLineUComment	[]	= {"//", "#", ";", "+", "-", "!"};
unsigned int	nCulStdLineUComment			= GET_ARRAY_LEN (ccCulStdLineUComment);

// These line comments are meant to be prededed by white space in the future.
//	Not implemented yet.
const char		*ccCulStdLineWSComment	[]	= {"#", ";", "!"};
unsigned int	nCulStdLineWSComment		= GET_ARRAY_LEN (ccCulStdLineWSComment);

const char		*ccCulStdBegMultComment	[]	= {"/*"};
const char		*ccCulStdEndMultComment	[]	= {"*/"};
unsigned int	nccCulStdMultComment		= GET_ARRAY_LEN (ccCulStdEndMultComment);

const char		*ccCulStdOpenQuotes		[]	= {"\"", "'", "[", "{"};
const char		*ccCulStdClosQuotes		[]	= {"\"", "'", "]", "}"};
unsigned int	nCulStdQuotes				= GET_ARRAY_LEN (ccCulStdOpenQuotes);

const char		*ccCulStdEqualSigns		[]	= {":=", "=", ":", "->", "<-"};
unsigned int	nCulStdEquals				= GET_ARRAY_LEN (ccCulStdEqualSigns);

char			*ccCulStdStrtSection	[]	= {"[", "{", "** "};
char			*ccCulStdExitSection	[]	= {"]", "}", " **"};
unsigned int	nCulStdSections				= GET_ARRAY_LEN (ccCulStdStrtSection);

void InitSTRLINEINF (STRLINEINF *pi, void *pCustom)
{
	ubf_assert_non_NULL (pi);

	// No initialisation in debug versions. We expect a slap in the face if we missed
	//	something.
	#ifndef DEBUG
		memset (pi, 0, sizeof (STRLINEINF));
	#endif

	pi->absPosition				= 1;
	pi->charNumber				= 0;
	pi->lineNumber				= 1;
	pi->pCustom					= pCustom;
	pi->szStart					= NULL;
	pi->lnLength				= 0;
	#ifdef DEBUG
		pi->bInitialised		= true;
	#endif
}

void InitSTRLINECONFforUBFL (STRLINECONF *pc)
{
	ubf_assert_non_NULL (pc);

	// No initialisation in debug versions. We expect a slap in the face if we missed
	//	something.
	#ifndef DEBUG
		memset (pc, 0, sizeof (STRLINECONF));
	#endif

	pc->CharacterSet			= EN_STRLINEEXTRACT_UTF8;
	pc->tabSize					= 4;
	pc->pchLineCommentStr		= ccCulStdLineUComment;
	pc->nLineCommentStr			= GET_ARRAY_LEN (ccCulStdLineUComment);
	pc->pchStartMultiCommentStr	= ccCulStdBegMultComment;
	pc->pchEndMultiCommentStr	= ccCulStdEndMultComment;
	pc->nMultiCommentStr		= GET_ARRAY_LEN (ccCulStdBegMultComment);
	#ifdef DEBUG
		pc->bInitialised		= true;
	#endif
}

void InitSTRLINECONFforC (STRLINECONF *pc)
{
	ubf_assert_non_NULL (pc);

	// No initialisation in debug versions. We expect a slap in the face if we missed
	//	something.
	#ifndef DEBUG
		memset (pc, 0, sizeof (STRLINECONF));
	#endif

	pc->CharacterSet			= EN_STRLINEEXTRACT_UTF8;
	pc->tabSize					= 4;
	pc->pchLineCommentStr		= ccCulStdLineCComment;
	pc->nLineCommentStr			= GET_ARRAY_LEN (ccCulStdLineCComment);
	pc->pchStartMultiCommentStr	= ccCulStdBegMultComment;
	pc->pchEndMultiCommentStr	= ccCulStdEndMultComment;
	pc->nMultiCommentStr		= GET_ARRAY_LEN (ccCulStdBegMultComment);
	#ifdef DEBUG
		pc->bInitialised		= true;
	#endif
}

void InitSCULMLTSTRINGSforUBFL (SCULMLTSTRINGS *psmls)
{
	ubf_assert_non_NULL (psmls);

	// No initialisation in debug versions. We expect a slap in the face if we missed
	//	something.
	#ifndef DEBUG
		memset (psmls, 0, sizeof (SCULMLTSTRINGS));
	#endif

	psmls->ccLineComments		= ccCulStdLineUComment;
	psmls->nLineComments		= nCulStdLineUComment;
	psmls->ccBegMultiComments	= ccCulStdBegMultComment;
	psmls->ccEndMultiComments	= ccCulStdEndMultComment;
	psmls->nMultiComments		= nccCulStdMultComment;
	psmls->ccOpenQuotes			= ccCulStdOpenQuotes;
	psmls->ccClosQuotes			= ccCulStdClosQuotes;
	psmls->nQuotes				= nCulStdQuotes;
	psmls->ccEquals				= ccCulStdEqualSigns;
	psmls->nEquals				= nCulStdEquals;
	psmls->ccStrtSections		= ccCulStdStrtSection;
	psmls->ccExitSections		= ccCulStdExitSection;
	psmls->nSections			= nCulStdSections;
}

void InitSCULMLTSTRINGSforC (SCULMLTSTRINGS *psmls)
{
	ubf_assert_non_NULL (psmls);

	// No initialisation in debug versions. We expect a slap in the face if we missed
	//	something.
	#ifndef DEBUG
		memset (psmls, 0, sizeof (SCULMLTSTRINGS));
	#endif

	psmls->ccLineComments		= ccCulStdLineCComment;
	psmls->nLineComments		= nCulStdLineCComment;
	psmls->ccBegMultiComments	= ccCulStdBegMultComment;
	psmls->ccEndMultiComments	= ccCulStdEndMultComment;
	psmls->nMultiComments		= nccCulStdMultComment;
	psmls->ccOpenQuotes			= ccCulStdOpenQuotes;
	psmls->ccClosQuotes			= ccCulStdClosQuotes;
	psmls->nQuotes				= nCulStdQuotes;
	psmls->ccEquals				= ccCulStdEqualSigns;
	psmls->nEquals				= nCulStdEquals;
	psmls->ccStrtSections		= ccCulStdStrtSection;
	psmls->ccExitSections		= ccCulStdExitSection;
	psmls->nSections			= nCulStdSections;
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
			ubf_assert_non_NULL	(pc->pchStartMultiCommentStr [n]);
			ubf_assert			(strlen (pc->pchStartMultiCommentStr [n]));
			ubf_assert_non_NULL (pc->pchEndMultiCommentStr [n]);
			ubf_assert			(strlen (pc->pchEndMultiCommentStr [n]));
			if	(
						NULL == pc->pchStartMultiCommentStr [n]
					||	NULL == pc->pchEndMultiCommentStr [n]
					||	0 == strlen (pc->pchStartMultiCommentStr [n])
					||	0 == strlen (pc->pchEndMultiCommentStr [n])
				)
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
	ubf_assert (USE_STRLEN != l);

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
unsigned int isStartMultiLineComment (const char *pb, size_t lb, STRLINECONF *pc)
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
bool isEndMultiLineComment (const char *pb, size_t lb, STRLINECONF *pc, unsigned int uMCn)
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
void nextLine (const char **pb, size_t *pl, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pl);
	ubf_assert_non_NULL (pi);

	const char		*ch	= *pb;
	size_t			nls	= 0;
	size_t			jmp	= 0;
	size_t			l	= *pl;

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
bool swallowLineComment (const char **pb, size_t *pl, STRLINECONF *pc, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pc);
	ubf_assert_non_NULL (pi);

	unsigned int n	= 0;

	if (pc->nLineCommentStr)
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
bool swallowMultiComment (const char **pb, size_t *pl, STRLINECONF *pc, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pl);
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
bool swallowEmptyAndWhiteSpaceLines (const char **pb, size_t *pl, STRLINEINF *pi)
{
	ubf_assert_non_NULL (pb);
	ubf_assert_non_NULL (*pb);
	ubf_assert_non_NULL (pl);
	ubf_assert_non_NULL (pi);
	
	size_t	nls;
	size_t	jmp;
	bool	bRet	= false;
	
	while (*pl)
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
	return bRet;
}

/*
	Returns the new length of pb when trailing white space is removed.
*/
size_t getLengthTrailingWhiteSpaceRemoved (const char *pb, size_t l)
{
	ubf_assert_non_NULL	(pb);
	ubf_assert			(0 < l);

	while (l && isWhiteSpace (pb [l - 1]))
	{
		-- l;
	}
	return l;
}

/*
	Returns the length of a line.
*/
size_t getLineLength (const char *pb, size_t lb) //, STRLINECONF *pc)
{
	ubf_assert_non_NULL (pb);

	size_t		nls		= 0;
	size_t		jmp;
	const char	*p		= pb;
	size_t		r		= 0;

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
				const char				*pBuf,
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

	#ifdef DEBUG
		if (!SanityCheckMultiComments (pConf))
			return UINT_MAX;
	#endif

	STRLINEINF			sLineInfo;
	bool				cbRet;
	bool				b;

	if (pBuf)
	{
		InitSTRLINEINF (&sLineInfo, pCustom);
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
				sLineInfo.szStart		= pBuf;
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
				const void				*pBuf,
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
			return UINT_MAX;
	}
	return 0;
}

const char *strlineextractRemoveLeadingWhiteSpace (size_t *pLen, const char *szLine, size_t lnLine)
{
	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;
	while (lnLine && isWhiteSpace (szLine [0]))
	{
		++ szLine;
		-- lnLine;
	}
	if (pLen)
		*pLen = lnLine;
	return szLine;
}

#ifdef _MSC_VER
#pragma warning (disable: 4706)									// Assignment within conditional expression.
#endif

const char *strlineextractRemoveWhiteSpaceAndComments	(
				size_t *pLen,
				const char *szLine,			size_t lnLine,
				SCULMLTSTRINGS				*pslms
														)
{
	ubf_assert_non_NULL	(pslms);

	unsigned int	ui;

	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;
	while (lnLine)
	{
		while (lnLine && isWhiteSpace (szLine [0]))
		{
			++ szLine;
			-- lnLine;
		}
		if (lnLine)
		{
			if (strlineextractIsOpenString (szLine, lnLine, pslms->nLineComments, pslms->ccLineComments))
			{	// Consume the rest.
				szLine += lnLine;
				lnLine = 0;
			}
			if (ui = strlineextractIsOpenString (szLine, lnLine, pslms->nMultiComments, pslms->ccBegMultiComments))
			{
				size_t lnOpn = strlen (pslms->ccBegMultiComments [ui - 1]);
				szLine += lnOpn;
				lnLine -= lnOpn;
				while (lnLine)
				{
					if (strlineextractIsCloseString (szLine, lnLine, pslms->ccEndMultiComments, ui))
					{
						size_t lnCls = strlen (pslms->ccEndMultiComments [ui - 1]);
						szLine += lnCls;
						lnLine -= lnCls;
						break;
					} else
					{
						++ szLine;
						-- lnLine;
					}
				}
			}
		}
	}
	if (pLen)
		*pLen = lnLine;
	return szLine;
}

#ifdef _MSC_VER
#pragma warning (default: 4706)									// Assignment within conditional expression.
#endif

unsigned int strlineextractIsOpenString	(
		const char		*szLine,			size_t			lnLine,
		unsigned int	nOpenStrings,		const char		**pszOpenStrings
										)
{
	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;

	for (unsigned int q = 0; q < nOpenStrings; ++ q)
	{
		ubf_assert (strlen (pszOpenStrings [q]));
		if (cmpBufStartsWith (szLine, lnLine, pszOpenStrings [q]))
			return q + 1;
	}
	return 0;
}

bool strlineextractIsCloseString	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszCloseStrings,
		unsigned int	idxCloseString1based
								)
{
	ubf_assert_non_0	(idxCloseString1based);
	ubf_assert_non_NULL	(pszCloseStrings);
	ubf_assert_non_NULL	(*pszCloseStrings);

	-- idxCloseString1based;
	return cmpBufStartsWith (szLine, lnLine, pszCloseStrings [idxCloseString1based]);
}

bool strlineextractKeyOrValue	(
		const char		**cunilog_restrict pszKeyOrVal,	size_t	*plnKeyOrVal,	// Out.
		const char		**cunilog_restrict pszEqual,	size_t	*plnEqual,		// Out.
		unsigned int	*pidxEqual1based,										// Out.
		const char		*szLine,						size_t	lnLine,			// In.
		SCULMLTSTRINGS	*psmlt													// In.
								)
{
	ubf_assert_non_NULL	(pszKeyOrVal);
	ubf_assert_non_NULL	(plnKeyOrVal);
	ubf_assert_non_NULL	(szLine);
	ubf_assert_non_0	(lnLine);
	ubf_assert_non_NULL	(psmlt);
	ubf_assert_non_NULL	(psmlt->ccOpenQuotes);
	ubf_assert_non_NULL	(psmlt->ccClosQuotes);

	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;
	if (pszEqual)			*pszEqual			= NULL;
	if (plnEqual)			*plnEqual			= 0;
	if (pidxEqual1based)	*pidxEqual1based	= 0;

	size_t	newLnLine;
	szLine = strlineextractRemoveLeadingWhiteSpace (&newLnLine, szLine, lnLine);
	lnLine = newLnLine;

	const char *szRet;
	const char *szEnd;
	unsigned int uQuote = strlineextractIsOpenString (szLine, lnLine, psmlt->nQuotes, psmlt->ccOpenQuotes);
	if (uQuote)
	{
		size_t lnOpenQuote = strlen (psmlt->ccOpenQuotes [uQuote - 1]);
		szLine += lnOpenQuote;
		lnLine -= lnOpenQuote;
		szRet = szLine;
		while (lnLine)
		{
			if (strlineextractIsCloseString (szLine, lnLine, psmlt->ccClosQuotes, uQuote))
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
					&&	!strlineextractIsEqual (szLine, lnLine, psmlt->nEquals, psmlt->ccEquals)
				)
			{
				szEnd = szLine;
			}
			++ szLine;
			-- lnLine;
			unsigned int ui1 = strlineextractIsEqual (szLine, lnLine, psmlt->nEquals, psmlt->ccEquals);
			if (ui1)
			{	// Return the position of the equality sign found and the remaining length
				//	of the line and its 1-based index. This way the caller doesn't need to
				//	parse white space up until after the equality sign again, since its
				//	length can be obtained via the 1-based index - 1.
				if (pszEqual)			*pszEqual			= szLine;
				if (plnEqual)			*plnEqual			= lnLine;
				if (pidxEqual1based)	*pidxEqual1based	= ui1;
				break;
			}
		}
		if (szEnd)
			szLine = szEnd + 1;
		*plnKeyOrVal = szLine - szRet;
		*pszKeyOrVal = szRet;
		return true;
	}
}

bool strlineextractKeyAndValue	(
		const char		**cunilog_restrict pszKey,	size_t	*plnKey,		// Out.
		const char		**cunilog_restrict pszVal,	size_t	*plnVal,		// Out.
		const char		*cunilog_restrict szLine,	size_t	lnLine,			// In.
		SCULMLTSTRINGS	*psmlt												// In.
							)
{
	if (NULL == szLine)
		return false;
	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;
	if (0 == lnLine)
		return false;

	ubf_assert_non_NULL (pszKey);
	ubf_assert_non_NULL (plnKey);
	ubf_assert_non_NULL (pszVal);
	ubf_assert_non_NULL (plnVal);
	ubf_assert_non_NULL (psmlt);

	/*
	if (NULL == pszEquals || 0 == nEquals)
		return false;
	*/

	const char		*szEqual;
	size_t			lnEqual;
	unsigned int	idxEqual1;
	bool b = strlineextractKeyOrValue	(
				pszKey,		plnKey,
				&szEqual,	&lnEqual, &idxEqual1,
				szLine,		lnLine,
				psmlt
										);
	if (!b)
		return false;

	// We're expecting a key/value pair like "key = value". That's not possible without
	//	an equality sign.
	if (0 == idxEqual1)
		return false;

	size_t lenOurFoundEqual = strlen (psmlt->ccEquals [idxEqual1 - 1]);
	szEqual += lenOurFoundEqual;
	ubf_assert (0 < lnEqual);
	ubf_assert (lnEqual >= lenOurFoundEqual);
	lnEqual -= lenOurFoundEqual;

	// From now on we don't care about equality strings. We accept
	//	"key = value = value = value", with the value being "value = value = value".
	b = strlineextractKeyOrValue		(
				pszVal,		plnVal,
				NULL, NULL, NULL,
				szEqual,	lnEqual,
				psmlt
										);
	if (!b)
		return false;

	return true;
}

bool strlineextractSection	(
		const char				**cunilog_restrict pszSec,	size_t	*plnSec,
		const char				*cunilog_restrict szLine,	size_t	lnLine,
		SCULMLTSTRINGS			*psmlt,
		en_strlineextract_ws	ws
							)
{
	ubf_assert_non_NULL	(psmlt);
	ubf_assert_non_0	(psmlt->nSections);
	ubf_assert_non_NULL	(psmlt->ccStrtSections);
	ubf_assert_non_NULL	(psmlt->ccExitSections);

	if (NULL == szLine)
		return false;
	lnLine = USE_STRLEN == lnLine ? strlen (szLine) : lnLine;
	if (0 == lnLine)
		return false;

	bool bAcceptLeadWS =		strlineextract_accept_white_space_and_comments			== ws
							||	strlineextract_accept_leading_and_trailing_white_space	== ws
							||	strlineextract_accept_leading_white_space				== ws;

	bool bAcceptTraiWS =		strlineextract_accept_white_space_and_comments			== ws
							||	strlineextract_accept_leading_and_trailing_white_space	== ws
							||	strlineextract_accept_trailing_white_space				== ws;

	if (bAcceptLeadWS)
	{
		size_t	newLnLine;
		szLine = strlineextractRemoveLeadingWhiteSpace (&newLnLine, szLine, lnLine);
		lnLine = newLnLine;
	}

	const char *szRet;
	unsigned int uQuote = strlineextractIsOpenString (szLine, lnLine, psmlt->nSections, psmlt->ccStrtSections);
	if (uQuote)
	{
		size_t lnStartSection = strlen (psmlt->ccStrtSections [uQuote]);
		szLine += lnStartSection;
		lnLine -= lnStartSection;
		szRet = szLine;
		while (lnLine)
		{
			size_t uClose = strlineextractIsCloseString (szLine, lnLine, psmlt->ccExitSections, uQuote);
			if (uClose)
			{
				size_t lnExitSection = strlen (psmlt->ccExitSections [uQuote]);
				*plnSec = szLine - szRet;
				*pszSec = szRet;
				szLine += lnExitSection;
				lnLine -= lnExitSection;
				if (strlineextract_accept_white_space_and_comments == ws)
				{
					size_t	newLnLine;
					strlineextractRemoveWhiteSpaceAndComments (&newLnLine, szLine, lnLine, psmlt);
					lnLine = newLnLine;
				} else
				if (bAcceptTraiWS)
				{
					size_t	newLnLine;
					szLine = strlineextractRemoveLeadingWhiteSpace (&newLnLine, szLine, lnLine);
					lnLine = newLnLine;
				}
				return 0 == lnLine;
			}
			++ szLine;
			-- lnLine;
		}
		// No exit section string.
	}
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
		const char		*szLine	= psli->szStart;
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
		ui = strlineextractIsOpenString ("\"abc", USE_STRLEN, GET_ARRAY_LEN (ccCulStdOpenQuotes), ccCulStdOpenQuotes);
		ubf_expect_bool_AND (b, 0 < ui);

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
						" /* comment */ 1234\n"
						;
		InitSTRLINECONFforUBFL (&conf);
		inf.pCustom = &cust;
		size_t n = 0;
		StrLineExtract (szTst, USE_STRLEN, &conf, ourLinextractCB, &cust);
		ubf_expect_bool_AND (b, 3 == cust.n);
		ubf_expect_bool_AND (b, !memcmp ("First line", cust.strs [n ++], 10));
		ubf_expect_bool_AND (b, !memcmp ("ABCDEFG", cust.strs [n ++], 7));
		ubf_expect_bool_AND (b, !memcmp ("1234", cust.strs [n ++], 4));

		for (size_t ux = 0; ux < STRLINEEXTRACT_TEST_STRING_NUM; ++ ux)
		{
			if (cust.strs [ux])
				ubf_free (cust.strs [ux]);
			cust.strs	[ux] = NULL;
			cust.sts	[ux]	= 0;
		}

		size_t		lnResult = 9;
		const char *szResult = strlineextractRemoveLeadingWhiteSpace (&lnResult, "ABC", 3);
		ubf_expect_bool_AND (b, 9 != lnResult);
		ubf_expect_bool_AND (b, 3 == lnResult);
		ubf_expect_bool_AND (b, !memcmp ("ABC", szResult, 4));
		lnResult = 9;
		szResult = strlineextractRemoveLeadingWhiteSpace (&lnResult, " ABC", 4);
		ubf_expect_bool_AND (b, 9 != lnResult);
		ubf_expect_bool_AND (b, 3 == lnResult);
		ubf_expect_bool_AND (b, !memcmp ("ABC", szResult, 4));
		lnResult = 9;
		szResult = strlineextractRemoveLeadingWhiteSpace (&lnResult, " \tABC ", 6);
		ubf_expect_bool_AND (b, 9 != lnResult);
		ubf_expect_bool_AND (b, 4 == lnResult);
		ubf_expect_bool_AND (b, !memcmp ("ABC ", szResult, 5));
		szResult = strlineextractRemoveLeadingWhiteSpace (&lnResult, NULL, 0);
		ubf_expect_bool_AND (b, 9 != lnResult);
		ubf_expect_bool_AND (b, 0 == lnResult);
		ubf_expect_bool_AND (b, NULL == szResult);
		// Must not crash.
		lnResult = 9;
		szResult = strlineextractRemoveLeadingWhiteSpace (NULL, NULL, 0);
		ubf_expect_bool_AND (b, 9 == lnResult);
		ubf_expect_bool_AND (b, NULL == szResult);

		// Note that we do not fully initialise the structure here. We only
		//	prepare what we really need right now.
		SCULMLTSTRINGS	scmul;
		scmul.ccOpenQuotes			= ccCulStdOpenQuotes;
		scmul.ccClosQuotes			= ccCulStdClosQuotes;
		scmul.nQuotes				= nCulStdQuotes;
		scmul.ccEquals				= ccCulStdEqualSigns;
		scmul.nEquals				= nCulStdEquals;

		const char	*szKey	= NULL;
		size_t		lnKey	= 0;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key=Val", 7, &scmul
										);
		ubf_expect_bool_AND (b, 0 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 7;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key=Val", 7, &scmul
										);
		ubf_expect_bool_AND (b, 7 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		// Same again with leading white space.
		szKey = NULL;
		lnKey = 7;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"  \tKey=Val", 10, &scmul
										);
		ubf_expect_bool_AND (b, 7 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key", 3, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key ", 3, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key ", 4, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key  ", 3, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key  ", 5, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key\t\t\t\t     ", USE_STRLEN, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key\t\t\t\t     =  jjjj", USE_STRLEN, &scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key", szKey, 3));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"Key number 1\t\t\t\t     =  jjjj", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 4000 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 12 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key number 1", szKey, 12));

		szKey = NULL;
		lnKey = 4000;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"[Key number 1]\t\t\t\t     =  jjjj", USE_STRLEN,
				&scmul
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
				&szKey, &lnKey, NULL, NULL, NULL,
				"[Key number 1\t\t\t\t     =  jjjj", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 4000 == lnKey);
		ubf_expect_bool_AND (b, NULL == szKey);

		/*
			"If the key or value is quoted, the key or value inside the quotes is extracted.
			The function fails (returns false) if no closing quote is found."

			If a key or value doesn't start with an opening quote but contains quotes,
			these quotes are treated as normal characters.

			"The extracted key is not NUL-terminated, since it is only a pointer to a buffer,
			and its length, inside the original buffer szLine points to."
		*/
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"'Key number 1\t\t\t\t'     =  jjjj", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 16 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key number 1\t\t\t\t", szKey, 16));
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"'Key {number 1\t\t\t\t'     =  jjjj", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 17 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("Key {number 1\t\t\t\t'", szKey, 18));
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"'Key {number} 1\t\t\t\t'     =  jjjj", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 18 == lnKey);
		// The closing single quote must not have been overwritten.
		ubf_expect_bool_AND (b, !memcmp ("Key {number} 1\t\t\t\t'", szKey, 19));

		// Same again with leading white space.
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"\t\t\t   'Key {number} 1\t\t\t\t'     =  jjjj", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 18 == lnKey);
		// The closing single quote must not have been overwritten.
		ubf_expect_bool_AND (b, !memcmp ("Key {number} 1\t\t\t\t'", szKey, 19));

		// No equality strings. We should get the entire line excluding leading
		//	and trailing white space.
		scmul.nEquals				= 0;
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"  value = value = value  ", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 21 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("value = value = value", szKey, 21));
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"\t\t\t\t  \t \t   \t\t\t  value = value = value\t\t  ", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 21 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("value = value = value", szKey, 21));
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"value = value = value", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 21 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("value = value = value", szKey, 21));
		szKey = NULL;
		lnKey = 5555;
		b &= strlineextractKeyOrValue	(
				&szKey, &lnKey, NULL, NULL, NULL,
				"value = value = value'", USE_STRLEN,
				&scmul
										);
		ubf_expect_bool_AND (b, 5555 != lnKey);
		ubf_expect_bool_AND (b, NULL != szKey);
		ubf_expect_bool_AND (b, 22 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("value = value = value'", szKey, 22));

		scmul.nEquals = nCulStdEquals;
		char cBuf [1024];
		strcpy	(
			cBuf,
			"\t\t\t\t      key          =      value    \t"
				);
		const char	*szVal;
		size_t		lnVal;
		b &= strlineextractKeyAndValue	(
				&szKey, &lnKey,
				&szVal, &lnVal,
				cBuf, USE_STRLEN,
				&scmul
										);
		ubf_assert_true (b);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("key", szKey, 3));
		ubf_expect_bool_AND (b, 5 == lnVal);
		ubf_expect_bool_AND (b, !memcmp ("value", szVal, 5));

		strcpy	(
			cBuf,
			"\t\t\t\t      key          :=      value    \t"
				);
		b &= strlineextractKeyAndValue	(
				&szKey, &lnKey,
				&szVal, &lnVal,
				cBuf, USE_STRLEN,
				&scmul
										);
		ubf_assert_true (b);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("key", szKey, 3));
		ubf_expect_bool_AND (b, 5 == lnVal);
		ubf_expect_bool_AND (b, !memcmp ("value", szVal, 5));

		strcpy	(
			cBuf,
			"\t\t\t\t      key          ->      value    \t"
				);
		b &= strlineextractKeyAndValue	(
				&szKey, &lnKey,
				&szVal, &lnVal,
				cBuf, USE_STRLEN,
				&scmul
										);
		ubf_assert_true (b);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("key", szKey, 3));
		ubf_expect_bool_AND (b, 5 == lnVal);
		ubf_expect_bool_AND (b, !memcmp ("value", szVal, 5));

		// A second equality string belongs to the value.
		strcpy	(
			cBuf,
			"\t\t\t\t      key          ->->value    \t"
				);
		b &= strlineextractKeyAndValue	(
				&szKey, &lnKey,
				&szVal, &lnVal,
				cBuf, USE_STRLEN,
				&scmul
										);
		ubf_assert_true (b);
		ubf_expect_bool_AND (b, 3 == lnKey);
		ubf_expect_bool_AND (b, !memcmp ("key", szKey, 3));
		ubf_expect_bool_AND (b, 7 == lnVal);
		ubf_expect_bool_AND (b, !memcmp ("->value", szVal, 5));

		// Without equality signs the function fails.
		strcpy	(
			cBuf,
			"\t\t\t\t      key          =      value    \t"
				);
		scmul.nEquals = 0;
		b &= !strlineextractKeyAndValue	(
				&szKey, &lnKey,
				&szVal, &lnVal,
				cBuf, USE_STRLEN,
				&scmul
										);
		ubf_assert_true (b);

		strcpy	(
			cBuf,
			"\t\t\t\t      key          .      value    \t"
				);
		b &= !strlineextractKeyAndValue	(
				&szKey, &lnKey,
				&szVal, &lnVal,
				cBuf, USE_STRLEN,
				&scmul
										);
		ubf_assert_true (b);

		const char *szSect;
		size_t		lnSect;

		// Sections.
		InitSCULMLTSTRINGSforUBFL (&scmul);
		strcpy (cBuf, "   \t\t\t /* comment */   ");
		szSect = strlineextractRemoveWhiteSpaceAndComments (&lnSect, cBuf, USE_STRLEN, &scmul);
		ubf_expect_bool_AND (b, 0 == lnSect);

		strcpy	(
			cBuf,
			"[Section]"
				);
		szSect = NULL;
		lnSect = 55;
		b &= strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_reject_white_space
									);
		ubf_expect_bool_AND (b, 7 == lnSect);
		ubf_expect_bool_AND (b, !memcmp ("Section]", szSect, 8));
		szSect = NULL;
		lnSect = 55;
		b &= strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_leading_and_trailing_white_space
									);
		ubf_expect_bool_AND (b, 7 == lnSect);
		ubf_expect_bool_AND (b, !memcmp ("Section]", szSect, 8));
		szSect = NULL;
		lnSect = 55;
		strcpy	(
			cBuf,
			" [Section]"
				);
		b &= !strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_reject_white_space
									);
		szSect = NULL;
		lnSect = 55;
		strcpy	(
			cBuf,
			"[Section]   "
				);
		b &= !strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_reject_white_space
									);
		szSect = NULL;
		lnSect = 55;
		strcpy	(
			cBuf,
			"\t\t\t     [Section]    \t\t\t        "
				);
		b &= strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_leading_and_trailing_white_space
									);
		ubf_expect_bool_AND (b, 7 == lnSect);
		ubf_expect_bool_AND (b, !memcmp ("Section]", szSect, 8));
		strcpy	(
			cBuf,
			"\t\t\t     [Section]    =\t\t\t        "
				);
		b &= !strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_leading_and_trailing_white_space
									);
		strcpy	(
			cBuf,
			"\t\t\t     [Section]    \t\t\t    =    "
				);
		b &= !strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_leading_and_trailing_white_space
									);
		strcpy	(
			cBuf,
			"\t\t\t     [Section]    \t\t\t    ="
				);
		b &= !strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_leading_and_trailing_white_space
									);
		ubf_expect_true (b);

		// Invalid equality sign.
		strcpy	(
			cBuf,
			"  =     [Section]    \t\t\t    // Line comment"
				);
		b &= !strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_white_space_and_comments
									);

		strcpy	(
			cBuf,
			"  \t\t     [Section]    \t\t\t    // Line comment"
				);
		lnSect = 5555;
		b &= strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_white_space_and_comments
									);
		ubf_expect_bool_AND (b, 5555 != lnSect);
		ubf_expect_bool_AND (b, 7 == lnSect);
		ubf_expect_bool_AND (b, !memcmp ("Section]", szSect, 8));

		strcpy	(
			cBuf,
			"   [Section]  /* c */  // Line comment"
				);
		lnSect = 5555;
		b &= strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_white_space_and_comments
									);
		ubf_expect_bool_AND (b, 5555 != lnSect);
		ubf_expect_bool_AND (b, 7 == lnSect);
		ubf_expect_bool_AND (b, !memcmp ("Section]", szSect, 8));

		strcpy	(
			cBuf,
			"   \t\t\t\t[Section]/**/\t\t\t/**/\t\t  /**/  // Line comment"
				);
		lnSect = 5555;
		b &= strlineextractSection	(
				&szSect, &lnSect,
				cBuf, USE_STRLEN,
				&scmul,
				strlineextract_accept_white_space_and_comments
									);
		ubf_expect_bool_AND (b, 5555 != lnSect);
		ubf_expect_bool_AND (b, 7 == lnSect);
		ubf_expect_bool_AND (b, !memcmp ("Section]", szSect, 8));


		return b;
	}
#endif
