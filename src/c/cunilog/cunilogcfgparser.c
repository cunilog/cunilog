/****************************************************************************************

	File:		cunilogcfgparser.c
	Why:		Simple configuration parser.
	OS:			C99
	Author:		Thomas
	Created:	2024-11-28
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-28	Thomas			Created.

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

#include <stdbool.h>

#ifdef CUNILOG_BUILD_CFG_PARSER

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "cunilogcfgparser.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./unref.h"
		#include "./ubfdebug.h"
		#include "./memstrstr.h"
		#include "./ubfmem.h"
		#include "./strlineextract.h"
		#include "./strnewline.h"
	#else
		#include "./../pre/unref.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/memstrstr.h"
		#include "./../mem/ubfmem.h"
		#include "./../string/strlineextract.h"
		#include "./../string/strnewline.h"
	#endif

#endif

/*
	Example from https://github.com/vstakhov/libucl:

	param = value;
	section {
		param = value;
		param1 = value1;
		flag = true;
		number = 10k;
		time = 0.2s;
		string = "something";
		subsection {
			host = {
				host = "hostname";
				port = 900;
			}
			host = {
				host = "hostname";
				port = 901;
			}
		}
	}

	To parse this file, we:
	(1)	Ignore white space, single-line comments ("#", "//"), and multi-line comments ("/*...").
	(2) Take all other characters to be part of a key/variable name until...
	(3)	...one or more equality characters (":", "=", "{") is/are found.
	(4) Fill the value with anything that's not white space until a colon appears or the line ends.
*/

void initCUNILOGCFGPARSERSTATUS (CUNILOGCFGPARSERSTATUS *ps, char *szCfg, size_t len)
{
	ubf_assert_non_NULL (ps);
	ubf_assert_non_NULL (szCfg);
	ubf_assert_non_0 (len);

	ps->szCfg				= szCfg;
	ps->lnCfg				= len;
	ps->litNum				= 0;
	ps->mulCom				= 0;
	ps->linNum				= 0;
	ps->colNum				= 0;
}

static void initSCUNILOGCFGNODE (SCUNILOGCFGNODE *pc)
{
	ubf_assert_non_NULL (pc);

	memset (pc, 0, sizeof (SCUNILOGCFGNODE));
}

static SCUNILOGCFGNODE *newSCUNILOGCFGNODEfromExisting (SCUNILOGCFGNODE *pExisting)
{
	ubf_assert_non_NULL (pExisting);

	SCUNILOGCFGNODE *new = malloc (sizeof (SCUNILOGCFGNODE));
	if (new)
		memcpy (new, pExisting, sizeof (SCUNILOGCFGNODE));
	return new;
}

static bool ignoreLineComment (CUNILOGCFGPARSERSTATUS *ps)
{
	ubf_assert_non_NULL (ps);
	ubf_assert_non_NULL (ps->szCfg);

	if (ps->lnCfg > 1 && '/' == ps->szCfg [0] && '/' == ps->szCfg [1])
	{
		ps->szCfg += 2;
		ps->lnCfg -= 2;

		size_t o = 0;

		while (ps->lnCfg && 0 == strIsLineEndings (ps->szCfg, ps->lnCfg, &o))
		{
			++ ps->szCfg;
			-- ps->lnCfg;
		}
		if (o)
		{
			ps->szCfg += o - 1;
			ps->lnCfg -= o - 1;
			return true;
		}
		if (ps->lnCfg)
		{
			ps->szCfg -= 1;
			ps->lnCfg -= 1;
			return true;
		}
	}
	return false;
}

static bool ignoreMultiLineComment (CUNILOGCFGPARSERSTATUS *ps)
{
	ubf_assert_non_NULL (ps);
	ubf_assert_non_NULL (ps->szCfg);
	ubf_assert_0 (ps->mulCom);

	/*
		Note that we do currently not support nested multi-line comments.
	*/
	if (ps->lnCfg > 1 && '/' == ps->szCfg [0] && '*' == ps->szCfg [1])
	{
		ps->szCfg	+= 2;
		ps->lnCfg	-= 2;
		++ ps->mulCom;

		char *sz = memstrstr (ps->szCfg, ps->lnCfg, "*/", 2);
		if (sz)
		{
			ps->lnCfg = sz - ps->szCfg;
			ps->szCfg = sz + 1;
			-- ps->mulCom;
			return true;
		} else
		{
			// That's a syntax error. No closing multi-line comment found.
			ubf_assert (false);
		}
	}
	return false;
}

static char *usableString (SCUNILOGCFGNODE *pn, CUNILOGCFGPARSERSTATUS *ps, CUNILOGCFGERR *pErr)
{
	ubf_assert_non_NULL (pn);
	ubf_assert_non_NULL (ps);

	UNUSED (pErr);
	UNUSED (pn);

	char *sret	= NULL;

	if (ps->szCfg)
	{
		char	c;

		while (ps->lnCfg)
		{
			c = *ps->szCfg;
			switch (c)
			{
				case ' ':
				case '\t':
				case '\v':
					break;
				default:
					if (ignoreLineComment (ps))
					{} else
					if (ignoreMultiLineComment (ps))
					{} else
					if (!sret && ps->lnCfg)
					{
						sret = ps->szCfg;
						return sret;
					}
			}
			if (ps->lnCfg)
			{
				++ ps->szCfg;
				-- ps->lnCfg;
			}
		}
	}
	return NULL;
}

static void rememberEnclosing (CUNILOGCFGPARSERSTATUS *ps)
{
	ubf_assert_non_NULL (ps);
	ubf_assert_non_NULL (ps->szCfg);
	ubf_assert_non_0 (ps->lnCfg);

	// Is the string enclosed in quotes/brackets etc?
	char e = *ps->szCfg;
	switch (e)
	{
		case '{':
		case '[':
		case '"':
		case '\'':
			ps->litChr = e;
			break;
		default:
			ps->litChr = 0;
			break;
	}
	++ ps->szCfg;
	-- ps->lnCfg;
}

static size_t lenUsableString (SCUNILOGCFGNODE *pn, CUNILOGCFGPARSERSTATUS *ps, CUNILOGCFGERR *pErr)
{
	ubf_assert_non_NULL (ps);

	UNUSED (pn);
	UNUSED (pErr);

	size_t		r		= 0;
	bool		bQuote	= '\''	== ps->litChr || '"' == ps->litChr;
	bool		bCurl	= '{' == ps->litChr;
	bool		bSquare	= '[' == ps->litChr;
	bool		bOpen	= bCurl || bSquare;

	if (ps->szCfg && ps->lnCfg)
	{
		char	c;
		char	*start = ps->szCfg;

		rememberEnclosing (ps);
		while (ps->lnCfg)
		{
			c = *ps->szCfg;
			if (ps->litChr)
			{
				if (c == ps->litChr)
				{
					if (bQuote)
					{
						r = ps->szCfg - start;
						return r;
					} else
					if (bOpen)
						++ ps->litNum;
				} else
				if (bCurl && '}' == c)
				{
					if (ps->litNum)
						++ ps->litNum;
					else
					{
						r = ps->szCfg - start;
						return r;
					}
				} else
				if (bSquare && ']' == c)
				{
				}
			} else
			{

			}
			++ ps->szCfg;
			-- ps->lnCfg;
		}
	}
	return r;
}

SCUNILOGCFGNODE *ParseCunilogConfigData (SCUNILOGCFGNODE *pParent, char *szConfigData, size_t lenData, CUNILOGCFGERR *pErr)
{
	SCUNILOGCFGNODE			node;
	CUNILOGCFGPARSERSTATUS	stat;

	initCUNILOGCFGPARSERSTATUS (&stat, szConfigData, lenData);

	node.pParent		= pParent;
	node.pChildren		= NULL;
	node.nChildren		= SCUNILOGCFGNODE_LINKED_LIST;
	node.pNext			= NULL;
	
	node.szKeyName		= usableString		(&node, &stat, pErr);
	node.lenKeyName		= lenUsableString	(&node, &stat, pErr);
	node.val.szValue	= usableString		(&node, &stat, pErr);
	node.lenValue		= lenUsableString	(&node, &stat, pErr);

	return newSCUNILOGCFGNODEfromExisting (&node);
}

SCUNILOGCFGNODE *ParseCunilogRootConfigData (char *szConfigData, size_t lenData, CUNILOGCFGERR *pErr)
{
	SCUNILOGCFGNODE *root;

	root = ParseCunilogConfigData (NULL, szConfigData, lenData, pErr);
	return root;
}

void DoneCunilogRootConfigData (SCUNILOGCFGNODE *cfg)
{
	UNUSED (cfg);

	ubf_assert_non_NULL (cfg);
}

/*
	nSects			Used to count the number of sections during the first iteration.
					The memory block to store the section and key/value pair structures
					is then allocated accordingly.
	nKeyVs			Used to count the number of key/value pairs during the first iteration.
					The memory block to store the section and key/value pair structures
					is then allocated accordingly.

	uiCurrSection	Used to identify the section we're currently in. For a new section,
					this value must be incremented first.
	uiCurrKeyVal	Used to identify the key/value pair we're currently in. For a new
					key/value pair, this value must be incremented first.
*/
typedef struct snsectionsandkeyvals
{
	SCULMLTSTRINGS			*psmls;
	unsigned int			nSects;
	unsigned int			nKeyVs;
	SCUNILOGINI				*pCunilogIni;
	unsigned int			uiCurrSection;
	unsigned int			uiCurrKeyVal;
} SNSECTIONSANDKEYVALS;

/*
	Counts the amount of sections and key/value pairs.
*/
static bool createCreateSCUNILOGINI_count_cb (STRLINEINF *psli)
{
	ubf_assert_non_NULL	(psli);
	ubf_assert_non_NULL	(psli->pCustom);
	ubf_assert_non_0	(psli->lnLength);

	SNSECTIONSANDKEYVALS *pkvs = (SNSECTIONSANDKEYVALS *) psli->pCustom;
	ubf_assert_non_NULL (pkvs);
	ubf_assert_non_NULL (pkvs->psmls);

	const char	*szSection;
	size_t		lnSection;
	bool bIsSctn = strlineextractSection		(
						&szSection, &lnSection, psli->szStart, psli->lnLength,
						pkvs->psmls,
						strlineextract_accept_white_space_and_comments
												);
	if (bIsSctn)
	{
		++ pkvs->nSects;
		return true;
	}
	const char	*szKey;
	size_t		lnKey;
	const char	*szVal;
	size_t		lnVal;
	bool bIsKeyV = strlineextractKeyAndValue	(
						&szKey, &lnKey, &szVal, &lnVal, psli->szStart, psli->lnLength,
						pkvs->psmls
												);
	if (bIsKeyV)
	{
		++ pkvs->nKeyVs;

		// We obviously have key/value pairs that don't belong to a section.
		//	In this case we're going to create a section without a name as dummy.
		//	Since an empty name ("") is possible to configure, this name is going
		//	to be NULL.
		if (0 == pkvs->nSects)
			++ pkvs->nSects;

		return true;
	}

	// Should never be reached.
	ubf_assert (false);
	return false;
}

static void storeSectionMembers	(
		SNSECTIONSANDKEYVALS	*pkvs,
		const char				*szSection,			size_t lnSection
								)
{
	++ pkvs->uiCurrSection;
	// Make it clear to the compiler that we do not care about padding.
	memset (&pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection], 0, sizeof (SCUNILOGINISECTION));
	pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].szSectionName		= szSection;
	pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].lnSectionName		= lnSection;
	pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].pKeyValuePairs	= NULL;
	pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].nKeyValuePairs	= 0;
}

static void storeKeyValueMembers	(
		SNSECTIONSANDKEYVALS	*pkvs,
		const char				*szKey,			size_t lnKey,
		const char				*szVal,			size_t lnVal
									)
{
	++ pkvs->uiCurrKeyVal;
	// The assignments cover the entire structure.
	//memset (&pkvs->pCunilogIni->pKeyValuePairs [pkvs->uiCurrKeyVal], 0, sizeof (SCUNILOGINIKEYVALUE));
	pkvs->pCunilogIni->pKeyValuePairs [pkvs->uiCurrKeyVal].szKeyName		= szKey;
	pkvs->pCunilogIni->pKeyValuePairs [pkvs->uiCurrKeyVal].lnKeyName		= lnKey;
	pkvs->pCunilogIni->pKeyValuePairs [pkvs->uiCurrKeyVal].szValue			= szVal;
	pkvs->pCunilogIni->pKeyValuePairs [pkvs->uiCurrKeyVal].lnValue			= lnVal;
	++ pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].nKeyValuePairs;
}

/*
	Assigns sections and key/value pairs.
*/
static bool createCreateSCUNILOGINI_assgn_cb (STRLINEINF *psli)
{
	ubf_assert_non_NULL	(psli);
	ubf_assert_non_NULL	(psli->pCustom);
	ubf_assert_non_0	(psli->lnLength);

	SNSECTIONSANDKEYVALS *pkvs = (SNSECTIONSANDKEYVALS *) psli->pCustom;
	ubf_assert_non_NULL (pkvs);
	ubf_assert_non_NULL (pkvs->psmls);

	const char	*szSection;
	size_t		lnSection;
	bool bIsSctn = strlineextractSection		(
						&szSection, &lnSection, psli->szStart, psli->lnLength,
						pkvs->psmls,
						strlineextract_accept_white_space_and_comments
												);
	if (bIsSctn)
	{
		ONLY_IN_DEBUG (-- pkvs->nSects);
		storeSectionMembers (pkvs, szSection, lnSection);
		return true;
	}
	const char	*szKey;
	size_t		lnKey;
	const char	*szVal;
	size_t		lnVal;
	bool bIsKeyV = strlineextractKeyAndValue	(
						&szKey, &lnKey, &szVal, &lnVal, psli->szStart, psli->lnLength,
						pkvs->psmls
												);
	if (bIsKeyV)
	{
		ONLY_IN_DEBUG (-- pkvs->nKeyVs);
		if (UINT_MAX == pkvs->uiCurrSection)
		{
			ONLY_IN_DEBUG (-- pkvs->nSects);
			storeSectionMembers (pkvs, NULL, 0);
		}
		ubf_assert (UINT_MAX > pkvs->uiCurrSection);
		storeKeyValueMembers (pkvs, szKey, lnKey, szVal, lnVal);
		if (NULL == pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].pKeyValuePairs)
		{
			pkvs->pCunilogIni->pIniSections [pkvs->uiCurrSection].pKeyValuePairs =
				&pkvs->pCunilogIni->pKeyValuePairs [pkvs->uiCurrKeyVal];
		}
		return true;
	}

	// Should never be reached.
	ubf_assert (false);
	return false;
}

bool CreateSCUNILOGINI (SCUNILOGINI *pCunilogIni, const char *szIniBuf, size_t lnIniBuf)
{
	ubf_assert_non_NULL (pCunilogIni);
	ubf_assert_non_NULL	(szIniBuf);
	ubf_assert_non_0	(lnIniBuf);

	memset (pCunilogIni, 0, sizeof (SCUNILOGINI));
	lnIniBuf = USE_STRLEN == lnIniBuf ? strlen (szIniBuf) : lnIniBuf;

	STRLINECONF	cnf;
	InitSTRLINECONFforUBFL (&cnf);

	SCULMLTSTRINGS			smls;
	InitSCULMLTSTRINGSforC (&smls);
	SNSECTIONSANDKEYVALS	kvs;
	kvs.psmls			= &smls;
	kvs.nSects			= 0;
	kvs.nKeyVs			= 0;
	kvs.pCunilogIni		= pCunilogIni;

	// These overflow to 0 when incremented the first time.
	kvs.uiCurrSection	= UINT_MAX;							// Idx of next section to use.
	kvs.uiCurrKeyVal	= UINT_MAX;							// Idx of next key/val to use.

	// First, count all sections and keys for us to allocate the correct array sizes.
	unsigned int nLines;
	nLines = StrLineExtract (szIniBuf, lnIniBuf, &cnf, createCreateSCUNILOGINI_count_cb, &kvs);

	size_t stTotal		= 0;
	size_t stSections	= 0;
	if (kvs.nSects || kvs.nKeyVs)
	{
		stSections	=	ALIGNED_SIZE ((sizeof (SCUNILOGINISECTION)	* kvs.nSects), 8);
		stTotal		+=	stSections;
		stTotal		+=	ALIGNED_SIZE ((sizeof (SCUNILOGINIKEYVALUE)	* kvs.nKeyVs), 8);
		pCunilogIni->buf = ubf_malloc (stTotal);

		if (pCunilogIni->buf)
		{
			if (kvs.nSects)
			{
				pCunilogIni->pIniSections = (SCUNILOGINISECTION *) pCunilogIni->buf;
				if (pCunilogIni->pIniSections)
					pCunilogIni->nIniSections = kvs.nSects;
			}
			if (kvs.nKeyVs)
			{
				pCunilogIni->pKeyValuePairs = (SCUNILOGINIKEYVALUE *) (pCunilogIni->buf + stSections);
				if (pCunilogIni->pKeyValuePairs)
					pCunilogIni->nKeyValuePairs = kvs.nKeyVs;
			}

			// Then, fill the arrays.
			nLines = StrLineExtract (szIniBuf, lnIniBuf, &cnf, createCreateSCUNILOGINI_assgn_cb, &kvs);

			// Debug versions decrement these all the way to 0.
			ubf_assert_0 (kvs.nSects);
			ubf_assert_0 (kvs.nKeyVs);

			return true;
		}
	}
	return false;
}

/*
	Compares the section names szA and szB and returns true, if they're identical.
	Also returns true if both are NULL.
*/
static bool equalSectionNames	(
				const char *cunilog_restrict szSA, size_t lnSA,
				const char *cunilog_restrict szSB, size_t lnSB
								)
{
	if (szSA && szSB && lnSA == lnSB)
	{
		if (lnSA)
			return !memcmp (szSA, szSB, lnSA);
		else
			return true;
	} else
	if (NULL == szSA && NULL == szSB)
	{
		return true;
	}
	return false;
}

const char *CunilogGetIniValueFromKey	(
				size_t			*pLen,
				const char		*cunilog_restrict szSection,	size_t	lnSection,
				const char		*cunilog_restrict szKey,		size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
										)
{
	ubf_assert_non_NULL	(pCunilogIni);

	lnSection	= USE_STRLEN == lnSection	? strlen (szSection)	: lnSection;
	lnKey		= USE_STRLEN == lnKey		? strlen (szKey)		: lnKey;

	if (0 == lnKey)
		return NULL;

	unsigned int uiS;
	for (uiS = 0; uiS < pCunilogIni->nIniSections; ++ uiS)
	{
		if	(
				equalSectionNames	(
					szSection, lnSection,
					pCunilogIni->pIniSections [uiS].szSectionName,
					pCunilogIni->pIniSections [uiS].lnSectionName
									)
			)
		{
			unsigned int uiK;
			for (uiK = 0; uiK < pCunilogIni->pIniSections [uiS].nKeyValuePairs; ++ uiK)
			{
				if (lnKey == pCunilogIni->pIniSections [uiS].pKeyValuePairs [uiK].lnKeyName)
				{
					if (!memcmp (szKey, pCunilogIni->pIniSections [uiS].pKeyValuePairs->szKeyName, lnKey))
					{
						if (*pLen)
							*pLen = pCunilogIni->pIniSections [uiS].pKeyValuePairs->lnValue;
						return pCunilogIni->pIniSections [uiS].pKeyValuePairs->szValue;
					}
				}
			}
		}
	}
	return NULL;
}

void DoneSCUNILOGINI (SCUNILOGINI *pCunilogIni)
{
	ubf_assert_non_NULL (pCunilogIni);

	if (pCunilogIni->buf)
		ubf_free (pCunilogIni->buf);
}

#ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT
	bool TestCunilogCfgParser (void)
	{
		bool	b = true;

		SCUNILOGCFGNODE			node;
		CUNILOGCFGPARSERSTATUS	stat;
		CUNILOGCFGERR			err;
		char					*sz;

		stat.mulCom				= 0;

		stat.szCfg				= " //";
		stat.lnCfg				= 3;
		sz = usableString (&node, &stat, &err);
		ubf_expect_bool_AND (b, NULL == sz);

		stat.szCfg = " //  \na";
		stat.lnCfg = 7;
		sz = usableString (&node, &stat, &err);
		ubf_expect_bool_AND (b, !memcmp ("a", stat.szCfg, 1));

		stat.szCfg = " /* x */ a";
		stat.lnCfg = 10;
		sz = usableString (&node, &stat, &err);
		ubf_expect_bool_AND (b, !memcmp ("a", stat.szCfg, 1));

		stat.szCfg = " /* x */ a = 5";
		stat.lnCfg = 14;
		sz = usableString (&node, &stat, &err);
		ubf_expect_bool_AND (b, !memcmp ("a = 5", stat.szCfg, 5));

		stat.szCfg = " //\n/* x */ a = 5";
		stat.lnCfg = 17;
		sz = usableString (&node, &stat, &err);
		ubf_expect_bool_AND (b, !memcmp ("a = 5", stat.szCfg, 5));
		ubf_expect_bool_AND (b, 0 == stat.mulCom);

		char szIni [2048];
		strcpy (szIni,
			"/*\n"
			"This is an example ini file. \n"
			"*/\n"
			"\n"
			"      [Section 01]     /* Comment */    \n"
			"\n"
			"    Key01 = Value 01     \n"
			"\n"
			"Key02                = \"This is value 02\"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"  Key03\t\t = We are still in Section 01.           \n"
			"\t\t\t\t\t        // Comment       \n"
			"\n"
			"\n"
			"[Section 02]\n"
			"\n"
			"    S02Key01 = Value S01K01     \n"
			"    S02Key02 = Value S01K02     \n"
			"    S02Key03 = Value S01K03__x  \n"
			"    S02Key04 = Value S01K04__xy     \n"
			"\n"
				);

		SCUNILOGINI ci;
		bool b1;
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 2 == ci.nIniSections);
		ubf_expect_bool_AND (b, 7 == ci.nKeyValuePairs);
		ubf_expect_bool_AND (b, 10 == ci.pIniSections [0].lnSectionName);
		ubf_expect_bool_AND (b, 3 == ci.pIniSections [0].nKeyValuePairs);
		ubf_expect_bool_AND (b, 10 == ci.pIniSections [1].lnSectionName);
		ubf_expect_bool_AND (b, 4 == ci.pIniSections [1].nKeyValuePairs);
		ubf_expect_bool_AND (b, !memcmp ("Section 01]", ci.pIniSections [0].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Section 02]", ci.pIniSections [1].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Key01 ",							ci.pKeyValuePairs [0].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ",						ci.pKeyValuePairs [0].szValue, 9));
		ubf_expect_bool_AND (b, !memcmp ("Key02 ",							ci.pKeyValuePairs [1].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("This is value 02\"",				ci.pKeyValuePairs [1].szValue, 17));
		ubf_expect_bool_AND (b, !memcmp ("Key03\t",							ci.pKeyValuePairs [2].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("We are still in Section 01. ",	ci.pKeyValuePairs [2].szValue, 28));
		ubf_expect_bool_AND (b, !memcmp ("S02Key01 ",						ci.pKeyValuePairs [3].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K01 ",					ci.pKeyValuePairs [3].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key02 ",						ci.pKeyValuePairs [4].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K02 ",					ci.pKeyValuePairs [4].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key03 ",						ci.pKeyValuePairs [5].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K03__x ",				ci.pKeyValuePairs [5].szValue, 16));
		ubf_expect_bool_AND (b, !memcmp ("S02Key04 ",						ci.pKeyValuePairs [6].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K04__xy ",				ci.pKeyValuePairs [6].szValue, 17));
		DoneSCUNILOGINI (&ci);

		// Now we got one out-of-section key/value pair.
		strcpy	(szIni,
			"/*\n"
			"This is another example ini file. \n"
			"*/\n"
			"       ! Note that this is a comment.\n"
			"       + This is also a comment.\n"
			"       ; This is also a comment.\n"
			" \t\t  \n"
			" Key00 = Value00; This is not a comment. It belongs to the value.\n"
			"\n"
			"      [Section 01]     /* Comment */    \n"
			"\n"
			"    Key01 = Value 01     \n"
			"\n"
			"Key02                = \"This is value 02\"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"  Key03\t\t = We are still in Section 01.           \n"
			"\t\t\t\t\t        // Comment       \n"
			"\n"
			"\n"
			"[Section 02_]\n"
			"\n"
			"    S02Key01 = Value S01K01     \n"
			"    S02Key02 = Value S01K02     \n"
			"    S02Key03 = Value S01K03__x  \n"
			"    S02Key04 = Value S01K04__xy     \n"
			"\n"
			// Future extension where line comment markers require to be prededed by white space.
			//	At the moment, the value extends to the end of the line. 
			" S02Key05 = Value05 ; This is a comment. It does not belong to the value.\n"
			"\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 3 == ci.nIniSections);
		ubf_expect_bool_AND (b, 9 == ci.nKeyValuePairs);
		ubf_expect_bool_AND (b, 0	== ci.pIniSections [0].lnSectionName);
		ubf_expect_bool_AND (b, 10	== ci.pIniSections [1].lnSectionName);
		ubf_expect_bool_AND (b, 11	== ci.pIniSections [2].lnSectionName);
		ubf_expect_bool_AND (b, NULL == ci.pIniSections [0].szSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 01]", ci.pIniSections [1].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Section 02_]", ci.pIniSections [2].szSectionName, 12));
		ubf_expect_bool_AND	(b,
			!memcmp ("Key00 ", ci.pKeyValuePairs [0].szKeyName, 6)
							);
		ubf_expect_bool_AND	(b,
			!memcmp ("Value00; This is not a comment. It belongs to the value.", ci.pKeyValuePairs [0].szValue, 56)
							);
		ubf_expect_bool_AND (b, !memcmp ("Key01 ",							ci.pKeyValuePairs [1].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ",						ci.pKeyValuePairs [1].szValue, 9));
		ubf_expect_bool_AND (b, !memcmp ("Key02 ",							ci.pKeyValuePairs [2].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("This is value 02\"",				ci.pKeyValuePairs [2].szValue, 17));
		ubf_expect_bool_AND (b, !memcmp ("Key03\t",							ci.pKeyValuePairs [3].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("We are still in Section 01. ",	ci.pKeyValuePairs [3].szValue, 28));
		ubf_expect_bool_AND (b, !memcmp ("S02Key01 ",						ci.pKeyValuePairs [4].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K01 ",					ci.pKeyValuePairs [4].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key02 ",						ci.pKeyValuePairs [5].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K02 ",					ci.pKeyValuePairs [5].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key03 ",						ci.pKeyValuePairs [6].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K03__x ",				ci.pKeyValuePairs [6].szValue, 16));
		ubf_expect_bool_AND (b, !memcmp ("S02Key04 ",						ci.pKeyValuePairs [7].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K04__xy ",				ci.pKeyValuePairs [7].szValue, 17));

		/* This is meant as a future extension where white space is required before some line comment
			strings to allow for "test!" without interpreting the exclamation mark as the start of a
			line comment. In "test !" on the other hand the exclamation mark is a line comment marker.
		ubf_expect_bool_AND (b, !memcmp ("S02Key05 ",						ci.pKeyValuePairs [8].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value05 ",						ci.pKeyValuePairs [8].szValue, 8));
		ubf_expect_bool_AND (b, 5 == ci.pKeyValuePairs [8].lnValue);
		*/

		const char	*szValue;
		size_t		len = 4711;
		szValue = CunilogGetIniValueFromKey (&len, "Section 01", USE_STRLEN, "Key01", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 4711 != len);
		ubf_expect_bool_AND (b, 8 == len);
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ", szValue, 9));

		// Retrieves a key that does not have a section.
		len = 4712;
		szValue = CunilogGetIniValueFromKey (&len, NULL, 0, "Key00", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 4712 != len);
		ubf_expect_bool_AND (b, 56 == len);
		ubf_expect_bool_AND (b, !memcmp ("Value00; This is not a comment. It belongs to the value.", szValue, 56));

		DoneSCUNILOGINI (&ci);

		return b;
	}
#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT.

#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER.
