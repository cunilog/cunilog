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
		#include "./ubfcharscountsandchecks.h"
	#else
		#include "./../pre/unref.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/memstrstr.h"
		#include "./../mem/ubfmem.h"
		#include "./../string/strlineextract.h"
		#include "./../string/strnewline.h"
		#include "./../string/ubfcharscountsandchecks.h"
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
	nKeys			Used to count the number of key with values during the first iteration.
					The memory block to store the section and key/value pair structures
					is then allocated accordingly.
	nValues			Used to count the number of values.
	uiCurrSection	Used to identify the section we're currently in. For a new section,
					this value must be incremented first.
	uiCurrKeyVal	Used to identify the key/value pair we're currently in. For a new
					key/value pair, this value must be incremented first.
*/
typedef struct snsectionsandkeyvals
{
	SCULMLTSTRINGS			*psmls;
	unsigned int			nSects;
	unsigned int			nKeys;
	unsigned int			nValues;
	SCUNILOGINI				*pCunilogIni;
	unsigned int			uiCurrSection;
	unsigned int			uiCurrentKey;
	unsigned int			uiCurrValue;
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
	const char	*szTail;
	size_t		lnTail;
	bool bIsSctn = strlineextractSection		(
						&szSection, &lnSection, psli->szStart, psli->lnLength,
						pkvs->psmls,
						strlineextract_accept_white_space_and_comments,
						&szTail, &lnTail
												);
	const char		*szKey;
	size_t			lnKey;
	unsigned int	nVals		= 0;
	if (bIsSctn)
	{
		++ pkvs->nSects;
		// Allow for: "[Section] key = value".
		if (NULL == szTail)
			return true;
		ubf_assert_non_0 (lnTail);
	} else
	{
		szTail = psli->szStart;
		lnTail = psli->lnLength;
	}
	nVals = strlineextractKeyAndValues	(
						&szKey, &lnKey, NULL, NULL,
						NULL, 0, szTail, lnTail,
						pkvs->psmls
										);
	if (nVals)
	{
		++ pkvs->nKeys;
		pkvs->nValues += nVals;

		// We obviously have key/value pairs that don't belong to a section.
		//	In this case we're going to create a section without a name as dummy.
		//	Since an empty name ("") is possible to configure, this name is going
		//	to be NULL.
		if (0 == pkvs->nSects)
			++ pkvs->nSects;

		return true;
	}

	++ pkvs->nKeys;
	return true;
}

static void storeSectionMembers	(
		SNSECTIONSANDKEYVALS	*pkvs,
		const char				*szSection,			size_t lnSection
								)
{
	// The first time this rolls over from UINT_MAX to 0.
	++ pkvs->uiCurrSection;
	ONLY_IN_DEBUG (-- pkvs->nSects);

	// Make it clear to the compiler that we do not care about padding.
	memset (&pkvs->pCunilogIni->pSections [pkvs->uiCurrSection], 0, sizeof (SCUNILOGINISECTION));
	pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].szSectionName	= szSection;
	pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].lnSectionName	= lnSection;
	pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].pKeyValues		= NULL;
	pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].nKeyValues		= 0;

	ubf_assert (UINT_MAX > pkvs->uiCurrSection);
}

static void assignKeyValsToSection (SNSECTIONSANDKEYVALS *pkvs, unsigned int nVals)
{
	if (NULL == pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].pKeyValues)
	{
		pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].pKeyValues =
			&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey];

		ubf_assert (pkvs->pCunilogIni->nSections	> pkvs->uiCurrSection);
		ubf_assert (pkvs->pCunilogIni->nKeyValues	> pkvs->uiCurrentKey);
		pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].nValues = 0;
	}
	pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].pValues =
		&pkvs->pCunilogIni->pValues [pkvs->uiCurrValue];
	pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].nValues = nVals;
	++ pkvs->pCunilogIni->pSections [pkvs->uiCurrSection].nKeyValues;
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
	const char	*szTail;
	size_t		lnTail;
	bool bIsSctn = strlineextractSection		(
						&szSection, &lnSection, psli->szStart, psli->lnLength,
						pkvs->psmls,
						strlineextract_accept_white_space_and_comments,
						&szTail, &lnTail
												);
	unsigned int	nVals		= 0;
	if (bIsSctn)
	{
		storeSectionMembers (pkvs, szSection, lnSection);
		// Allow for: "[Section] key = value".
		if (NULL == szTail)
			return true;
		ubf_assert_non_0 (lnTail);
	} else
	{
		szTail = psli->szStart;
		lnTail = psli->lnLength;
	}
	
	// Note that instead of pkvs->nValues we could afford a UINT_MAX as well,
	//	because everything has been allocated with the required sizes already.
	nVals = strlineextractKeyAndValues	(
				&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].szKeyName,
				&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].lnKeyName,
				&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].szEqualsSign,
				&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].lnEqualsSign,
				&pkvs->pCunilogIni->pValues [pkvs->uiCurrValue],
				pkvs->nValues,
				szTail, lnTail,
				pkvs->psmls
										);
	if (nVals)
	{
		ONLY_IN_DEBUG (-- pkvs->nKeys);
		ONLY_IN_DEBUG (pkvs->nValues -= nVals);
		if (UINT_MAX == pkvs->uiCurrSection)
		{
			storeSectionMembers (pkvs, NULL, 0);
		}
		assignKeyValsToSection (pkvs, nVals);
		pkvs->uiCurrValue += nVals;
		++ pkvs->uiCurrentKey;
		return true;
	}

	bool b = strlineextractKeyOrValue	(
				&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].szKeyName,
				&pkvs->pCunilogIni->pKeyValues [pkvs->uiCurrentKey].lnKeyName,
				NULL, NULL, NULL,
				szTail, lnTail,
				pkvs->psmls
										);
	assignKeyValsToSection (pkvs, 0);
	++ pkvs->uiCurrentKey;
	ONLY_IN_DEBUG (-- pkvs->nKeys);
	ubf_assert_TRUE (b);
	return b;
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
	memset (&kvs, 0, sizeof (SNSECTIONSANDKEYVALS));
	kvs.psmls			= &smls;
	kvs.nSects			= 0;
	kvs.nKeys			= 0;
	kvs.nValues			= 0;
	kvs.pCunilogIni		= pCunilogIni;

	kvs.uiCurrSection	= UINT_MAX;							// Idx of next section to use.
	kvs.uiCurrentKey	= 0;								// Idx of next key/val to use.
	kvs.uiCurrValue		= 0;								// Idx of next value to use.

	// First, count all sections and keys for us to allocate the correct array sizes.
	unsigned int nLines;
	nLines = StrLineExtract (szIniBuf, lnIniBuf, &cnf, createCreateSCUNILOGINI_count_cb, &kvs);

	// Note that we can't have values without keys, that we also can't have keys without
	//	at least one section, but we can have sections without keys. This is why the most
	//	efficient check here is for sections.
	if (kvs.nSects)
	{
		size_t stTotal;
		size_t stSections;
		size_t stKeyAnVls;

		stSections	=	ALIGNED_SIZE ((sizeof (SCUNILOGINISECTION)		* kvs.nSects),	8);
		stTotal		=	stSections;
		stTotal		+=	ALIGNED_SIZE ((sizeof (SCUNILOGINIKEYANDVALUES)	* kvs.nKeys),	8);
		stKeyAnVls	=	stTotal;
		stTotal		+=	ALIGNED_SIZE ((sizeof (SCUNILOGINIVALUES)		* kvs.nValues),	8);
		pCunilogIni->buf = ubf_malloc (stTotal);

		if (pCunilogIni->buf)
		{
			if (kvs.nSects)
			{	// The array with the sections is at the start of the buffer.
				pCunilogIni->pSections	= (SCUNILOGINISECTION *)		pCunilogIni->buf;
				pCunilogIni->nSections	= kvs.nSects;
			}
			if (kvs.nKeys)
			{	// Keys come after the sections.
				pCunilogIni->pKeyValues	= (SCUNILOGINIKEYANDVALUES *)	(pCunilogIni->buf + stSections);
				pCunilogIni->nKeyValues	= kvs.nKeys;
			}
			if (kvs.nValues)
			{	// Values are stored after the keys.
				pCunilogIni->pValues		= (SCUNILOGINIVALUES *)			(pCunilogIni->buf + stKeyAnVls);
				pCunilogIni->nValues		= kvs.nValues;
			}

			// Then, fill the arrays.
			nLines = StrLineExtract (szIniBuf, lnIniBuf, &cnf, createCreateSCUNILOGINI_assgn_cb, &kvs);

			// Debug versions decrement these all the way to 0.
			ubf_assert_0 (kvs.nSects);
			ubf_assert_0 (kvs.nKeys);
			ubf_assert_0 (kvs.nValues);

			return true;
		}
	}
	return false;
}

/*
	Compares the section names szA and szB and returns true, if they're identical.
	Also returns true if both are NULL.
*/
static bool equalSectionNames		(
				const char *szSA, size_t lnSA,
				const char *szSB, size_t lnSB
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

/*
	The case-insensitive version.
*/
static bool equalSectionNames_ci	(
				const char *szSA, size_t lnSA,
				const char *szSB, size_t lnSB
									)
{
	if (szSA && szSB && lnSA == lnSB)
	{
		if (lnSA)
			return !memcmp_ci (szSA, szSB, lnSA);
		else
			return true;
	} else
	if (NULL == szSA && NULL == szSB)
	{
		return true;
	}
	return false;
}

enum enGetValsCaseSensitivity
{
	enVlsCaseInsensitive,
	enVlsCaseSensitiveSection,
	enVlsCaseSensitiveSectionAndKey,
	enVlsCaseSensitiveKey
};

static bool areSectionNamesEqual	(
				const char *szS1,	size_t	lnS1,
				const char *szS2,	size_t	lnS2,
				enum enGetValsCaseSensitivity	cs		
									)
{
		if (enVlsCaseSensitiveSection == cs || enVlsCaseSensitiveSectionAndKey == cs)
			return equalSectionNames	(szS1, lnS1, szS2, lnS2);
		else
			return equalSectionNames_ci	(szS1, lnS1, szS2, lnS2);
}

/*
	The caller has to ensure that szK1 and szK2 point to buffers of equal lengths.
*/
static bool areKeyNamesEqual		(
				const char *szK1,
				const char *szK2,
				size_t							len,
				enum enGetValsCaseSensitivity	cs		
									)
{
	if (enVlsCaseSensitiveKey == cs || enVlsCaseSensitiveSectionAndKey == cs)
		return 0 == memcmp		(szK1, szK2, len);
	else
		return 0 == memcmp_ci	(szK1, szK2, len);
}

static unsigned int CunilogGetIniValuesFromKey_int	(
				SCUNILOGINIVALUES				**pValues,
				const char						*szSection,		size_t	lnSection,
				const char						*szKey,			size_t	lnKey,
				SCUNILOGINI						*pCunilogIni,
				enum enGetValsCaseSensitivity	cs		
													)
{
	ubf_assert_non_NULL	(pCunilogIni);

	lnSection	= USE_STRLEN == lnSection	? strlen (szSection)	: lnSection;
	lnKey		= USE_STRLEN == lnKey		? strlen (szKey)		: lnKey;

	if (0 == lnKey)
		return 0;

	size_t uiS;
	for (uiS = 0; uiS < pCunilogIni->nSections; ++ uiS)
	{
		bool bSectionsEqual = areSectionNamesEqual	(
				szSection, lnSection,
				pCunilogIni->pSections [uiS].szSectionName,
				pCunilogIni->pSections [uiS].lnSectionName,
				cs
													);
		if (bSectionsEqual)
		{
			size_t uiK;
			for (uiK = 0; uiK < pCunilogIni->pSections [uiS].nKeyValues; ++ uiK)
			{
				if (lnKey == pCunilogIni->pSections [uiS].pKeyValues [uiK].lnKeyName)
				{
					const char *szKS = pCunilogIni->pSections [uiS].pKeyValues [uiK].szKeyName;
					if (areKeyNamesEqual (szKey, szKS, lnKey, cs))
					{
						if (pValues)
							*pValues = pCunilogIni->pSections [uiS].pKeyValues [uiK].pValues;
						return pCunilogIni->pSections [uiS].pKeyValues [uiK].nValues;
					}
				}
			}
		}
	}
	return 0;
}

unsigned int CunilogGetIniValuesFromKey		(
				SCUNILOGINIVALUES	**pValues,
				const char			*szSection,		size_t	lnSection,
				const char			*szKey,			size_t	lnKey,
				SCUNILOGINI			*pCunilogIni
											)
{
	ubf_assert_non_NULL	(pCunilogIni);

	return CunilogGetIniValuesFromKey_int	(
				pValues,
				szSection,	lnSection,
				szKey,		lnKey,
				pCunilogIni,
				enVlsCaseSensitiveSectionAndKey
											);
}

unsigned int CunilogGetIniValuesFromKey_ci	(
				SCUNILOGINIVALUES	**pValues,
				const char			*szSection,		size_t	lnSection,
				const char			*szKey,			size_t	lnKey,
				SCUNILOGINI			*pCunilogIni
											)
{
	ubf_assert_non_NULL	(pCunilogIni);

	return CunilogGetIniValuesFromKey_int	(
				pValues,
				szSection,	lnSection,
				szKey,		lnKey,
				pCunilogIni,
				enVlsCaseInsensitive
											);
}

const char *CunilogGetFirstIniValueFromKey		(
				size_t			*pLen,
				const char		*szSection,			size_t	lnSection,
				const char		*szKey,				size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
												)
{
	ubf_assert_non_NULL	(pCunilogIni);

	SCUNILOGINIVALUES *pvals;
	unsigned int n = CunilogGetIniValuesFromKey_int	(
						&pvals,
						szSection,		lnSection,
						szKey,			lnKey,
						pCunilogIni,
						enVlsCaseSensitiveSectionAndKey
													);
	if (n)
	{
		if (pLen)
			*pLen = pvals->lnValue;
		return pvals->szValue;
	}
	if (pLen)
		*pLen = 0;
	return NULL;
}

const char *CunilogGetFirstIniValueFromKey_ci	(
				size_t			*pLen,
				const char		*szSection,			size_t	lnSection,
				const char		*szKey,				size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
												)
{
	ubf_assert_non_NULL	(pCunilogIni);

	SCUNILOGINIVALUES *pvals;
	unsigned int n = CunilogGetIniValuesFromKey_int	(
						&pvals,
						szSection,		lnSection,
						szKey,			lnKey,
						pCunilogIni,
						enVlsCaseInsensitive
													);
	if (n)
	{
		if (pLen)
			*pLen = pvals->lnValue;
		return pvals->szValue;
	}
	if (pLen)
		*pLen = 0;
	return NULL;
}

static bool CunilogIniKeyExists_int	(
				const char		*szSection,			size_t	lnSection,
				const char		*szKey,				size_t	lnKey,
				SCUNILOGINI		*pCunilogIni,
				enum enGetValsCaseSensitivity	cs		
									)
{
	ubf_assert_non_NULL	(pCunilogIni);

	lnSection	= USE_STRLEN == lnSection	? strlen (szSection)	: lnSection;
	lnKey		= USE_STRLEN == lnKey		? strlen (szKey)		: lnKey;

	if (0 == lnKey)
		return false;

	size_t uiS;
	for (uiS = 0; uiS < pCunilogIni->nSections; ++ uiS)
	{
		bool bSectionsEqual = areSectionNamesEqual	(
				szSection, lnSection,
				pCunilogIni->pSections [uiS].szSectionName,
				pCunilogIni->pSections [uiS].lnSectionName,
				cs
													);
		if (bSectionsEqual)
		{
			size_t uiK;
			for (uiK = 0; uiK < pCunilogIni->pSections [uiS].nKeyValues; ++ uiK)
			{
				if (lnKey == pCunilogIni->pSections [uiS].pKeyValues [uiK].lnKeyName)
				{
					const char *szKS = pCunilogIni->pSections [uiS].pKeyValues [uiK].szKeyName;
					if (areKeyNamesEqual (szKey, szKS, lnKey, cs))
						return true;
				}
			}
		}
	}
	return false;
}

bool CunilogIniKeyExists	(
				const char		*szSection,			size_t	lnSection,
				const char		*szKey,				size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
							)
{
	return CunilogIniKeyExists_int	(
			szSection, lnSection, szKey, lnKey, pCunilogIni,
			enVlsCaseSensitiveSectionAndKey
									);
}

bool CunilogIniKeyExists_ci	(
				const char		*szSection,			size_t	lnSection,
				const char		*szKey,				size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
							)
{
	return CunilogIniKeyExists_int	(
			szSection, lnSection, szKey, lnKey, pCunilogIni,
			enVlsCaseInsensitive
									);
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

		ubf_expect_bool_AND (b, !memcmp_ci (NULL, NULL, 0));
		ubf_expect_bool_AND (b, !memcmp_ci ("abc", "ABC", 3));
		ubf_expect_bool_AND (b, !memcmp_ci ("ABC", "abc", 3));
		ubf_expect_bool_AND (b, -1 == memcmp_ci ("aBc", "abd", 3));
		ubf_expect_bool_AND (b, 1 ==  memcmp_ci ("aBd", "abc", 3));
		ubf_expect_bool_AND (b, !memcmp_ci ("SECtIOn 01", "Section 01", 10));

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
		SCUNILOGINI ci;
		bool b1;

		strcpy (szIni,
				"[section]   \n"
				"[k] = length is short  \n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_assert_bool_AND (b, 1 == ci.nSections);
		ubf_assert_bool_AND (b, 1 == ci.nKeyValues);

		strcpy (szIni,
				"[section]   \n"
				"\"key 1 \" = colour is green\n"
				"[key 2] = length is short  \n"
				"{key 3 } = colour is green \n"
				"{key 4 } = length is short \n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 4 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 4 == ci.nValues);
		ubf_expect_bool_AND (b, !memcmp ("colour is green", ci.pValues [0].szValue, ci.pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("length is short", ci.pValues [1].szValue, ci.pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("colour is green", ci.pValues [2].szValue, ci.pValues [2].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("length is short", ci.pValues [3].szValue, ci.pValues [3].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("colour is green", ci.pKeyValues [0].pValues [0].szValue, ci.pKeyValues [0].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("length is short", ci.pKeyValues [1].pValues [0].szValue, ci.pKeyValues [1].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("colour is green", ci.pKeyValues [2].pValues [0].szValue, ci.pKeyValues [2].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("length is short", ci.pKeyValues [3].pValues [0].szValue, ci.pKeyValues [3].pValues [0].lnValue));
		DoneSCUNILOGINI (&ci);

		strcpy (szIni,
				"[section]\n"
				" key  = value1, value2, value3\n"
				" key2 = value1, value2, value3\n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 2 == ci.nValues);
		ubf_expect_bool_AND (b, !memcmp ("value1, value2, value3", ci.pValues [0].szValue, ci.pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("value1, value2, value3", ci.pValues [1].szValue, ci.pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("value1, value2, value3", ci.pKeyValues [0].pValues [0].szValue, ci.pKeyValues [0].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("value1, value2, value3", ci.pKeyValues [1].pValues [0].szValue, ci.pKeyValues [1].pValues [0].lnValue));
		DoneSCUNILOGINI (&ci);

		// Used for service tasks.
		strcpy	(szIni, " [Section 03] mkey = [S01][S02][S03]\n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, 1 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 03", ci.pSections [0].szSectionName, 10));
		ubf_expect_bool_AND (b, 1 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, !memcmp ("mkey", ci.pKeyValues [0].szKeyName, ci.pKeyValues [0].lnKeyName));
		unsigned int nVals;
		unsigned int nVls2;
		SCUNILOGINIVALUES *pVals;
		SCUNILOGINIVALUES *pVls2;
		nVals = CunilogGetIniValuesFromKey (&pVals, NULL, 0, "mkey", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 == nVals);
		nVals = CunilogGetIniValuesFromKey (&pVals, "Section 03", USE_STRLEN, "mkey", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 < nVals);
		ubf_expect_bool_AND (b, 3 == nVals);
		ubf_expect_bool_AND (b, 3 == pVals [0].lnValue);
		ubf_expect_bool_AND (b, 3 == pVals [1].lnValue);
		ubf_expect_bool_AND (b, 3 == pVals [2].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("S01]", pVals [0].szValue, 4));
		ubf_expect_bool_AND (b, 3 == pVals [0].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("S02]", pVals [1].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S03]", pVals [2].szValue, 4));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			" [Section 03] \n"
			" mkey = [S01][S02][S03]\n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, 1 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 03", ci.pSections [0].szSectionName, 10));
		ubf_expect_bool_AND (b, 1 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, !memcmp ("mkey", ci.pKeyValues [0].szKeyName, ci.pKeyValues [0].lnKeyName));
		nVals = CunilogGetIniValuesFromKey (&pVals, NULL, 0, "mkey", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 == nVals);
		nVals = CunilogGetIniValuesFromKey (&pVals, "Section 03", USE_STRLEN, "mkey", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 < nVals);
		ubf_expect_bool_AND (b, 3 == nVals);
		ubf_expect_bool_AND (b, 3 == pVals [0].lnValue);
		ubf_expect_bool_AND (b, 3 == pVals [1].lnValue);
		ubf_expect_bool_AND (b, 3 == pVals [2].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("S01]", pVals [0].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S02]", pVals [1].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S03]", pVals [2].szValue, 4));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			" [Section 03] \n"
			" mkey = 'S01' 'S02' 'S03' \n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, 1 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 03", ci.pSections [0].szSectionName, 10));
		ubf_expect_bool_AND (b, 1 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, !memcmp ("mkey", ci.pKeyValues [0].szKeyName, ci.pKeyValues [0].lnKeyName));
		nVals = CunilogGetIniValuesFromKey		(&pVals, NULL, 0, "mkey", USE_STRLEN, &ci);
		nVls2 = CunilogGetIniValuesFromKey_ci	(&pVls2, NULL, 0, "mKEy", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 == nVals);
		ubf_expect_bool_AND (b, 0 == nVls2);
		nVals = CunilogGetIniValuesFromKey		(&pVals, "Section 03", USE_STRLEN, "mkey", USE_STRLEN, &ci);
		nVls2 = CunilogGetIniValuesFromKey_ci	(&pVls2, "SectioN 03", USE_STRLEN, "MkEy", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 < nVals);
		ubf_expect_bool_AND (b, 0 < nVls2);
		ubf_expect_bool_AND (b, 3 == nVals);
		ubf_expect_bool_AND (b, 3 == nVls2);

		ubf_expect_bool_AND (b, &pVals [0] == &pVls2 [0]);
		ubf_expect_bool_AND (b, &pVals [1] == &pVls2 [1]);
		ubf_expect_bool_AND (b, &pVals [2] == &pVls2 [2]);

		ubf_expect_bool_AND (b, 3 == pVals [0].lnValue);
		ubf_expect_bool_AND (b, 3 == pVals [1].lnValue);
		ubf_expect_bool_AND (b, 3 == pVals [2].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("S01'", pVals [0].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S02'", pVals [1].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S03'", pVals [2].szValue, 4));

		ubf_expect_bool_AND (b, 3 == pVls2 [0].lnValue);
		ubf_expect_bool_AND (b, 3 == pVls2 [1].lnValue);
		ubf_expect_bool_AND (b, 3 == pVls2 [2].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("S01'", pVls2 [0].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S02'", pVls2 [1].szValue, 4));
		ubf_expect_bool_AND (b, !memcmp ("S03'", pVls2 [2].szValue, 4));

		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			" [Section 01] \n"
			" key 03 = value 3 // Comment.\n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, 1 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 01", ci.pSections [0].szSectionName, 10));
		ubf_expect_bool_AND (b, 1 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, !memcmp ("key 03", ci.pKeyValues [0].szKeyName, ci.pKeyValues [0].lnKeyName));
		nVals = CunilogGetIniValuesFromKey (&pVals, NULL, 0, "mkey", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 == nVals);
		nVals = CunilogGetIniValuesFromKey (&pVals, "Section 01", USE_STRLEN, "key 03", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 0 < nVals);
		ubf_expect_bool_AND (b, 1 == nVals);
		ubf_expect_bool_AND (b, 7 == pVals [0].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("value 3 ", pVals [0].szValue, 8));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			" [Section 03] \n"
			" mkey = [S01][S02][S03]\n"
			" nkey = [T01][T02][T03]\n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 03", ci.pSections [0].szSectionName, 10));
		ubf_expect_bool_AND (b, 2 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [1].nValues);
		ubf_expect_bool_AND (b, !memcmp ("mkey", ci.pKeyValues [0].szKeyName, ci.pKeyValues [0].lnKeyName));
		ubf_expect_bool_AND (b, !memcmp ("nkey", ci.pKeyValues [1].szKeyName, ci.pKeyValues [1].lnKeyName));
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [0].pValues [0].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [0].pValues [1].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [0].pValues [2].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [1].pValues [0].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [1].pValues [1].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [1].pValues [2].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("S01", ci.pKeyValues [0].pValues [0].szValue, ci.pKeyValues [0].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("S02", ci.pKeyValues [0].pValues [1].szValue, ci.pKeyValues [0].pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("S03", ci.pKeyValues [0].pValues [2].szValue, ci.pKeyValues [0].pValues [2].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("T01", ci.pKeyValues [1].pValues [0].szValue, ci.pKeyValues [1].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("T02", ci.pKeyValues [1].pValues [1].szValue, ci.pKeyValues [1].pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("T03", ci.pKeyValues [1].pValues [2].szValue, ci.pKeyValues [1].pValues [2].lnValue));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			" [Section NNN] \n"
			" mkey	= [A01][A02_][A03__]\n"
			" nkey2	= [T01][T02_][T03__]\n"
			" [Section OO] \n"
			" mkey	= [B01] [B02_] [B03__]\n"
			" nkey2	= [C01] [C02_] [C03__]\n");
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 2 == ci.nSections);
		ubf_expect_bool_AND (b, 4 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 11 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, 10 == ci.pSections [1].lnSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section NNN", ci.pSections [0].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Section OO", ci.pSections [1].szSectionName, 10));
		ubf_expect_bool_AND (b, 2 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].pKeyValues [1].nValues);
		ubf_expect_bool_AND (b, 2 == ci.pSections [1].nKeyValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [1].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, 3 == ci.pSections [1].pKeyValues [1].nValues);
		ubf_expect_bool_AND (b, 4 == ci.pKeyValues [0].lnKeyName);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [1].lnKeyName);
		ubf_expect_bool_AND (b, !memcmp ("mkey", ci.pKeyValues [0].szKeyName, ci.pKeyValues [0].lnKeyName));
		ubf_expect_bool_AND (b, !memcmp ("nkey2", ci.pKeyValues [1].szKeyName, ci.pKeyValues [1].lnKeyName));
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [0].pValues [0].lnValue);
		ubf_expect_bool_AND (b, 4 == ci.pKeyValues [0].pValues [1].lnValue);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [0].pValues [2].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [1].pValues [0].lnValue);
		ubf_expect_bool_AND (b, 4 == ci.pKeyValues [1].pValues [1].lnValue);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [1].pValues [2].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [2].pValues [0].lnValue);
		ubf_expect_bool_AND (b, 4 == ci.pKeyValues [2].pValues [1].lnValue);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [2].pValues [2].lnValue);
		ubf_expect_bool_AND (b, 3 == ci.pKeyValues [3].pValues [0].lnValue);
		ubf_expect_bool_AND (b, 4 == ci.pKeyValues [3].pValues [1].lnValue);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [3].pValues [2].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("A01",		ci.pKeyValues [0].pValues [0].szValue, ci.pKeyValues [0].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("A02_",	ci.pKeyValues [0].pValues [1].szValue, ci.pKeyValues [0].pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("A03__",	ci.pKeyValues [0].pValues [2].szValue, ci.pKeyValues [0].pValues [2].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("T01",		ci.pKeyValues [1].pValues [0].szValue, ci.pKeyValues [1].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("T02_",	ci.pKeyValues [1].pValues [1].szValue, ci.pKeyValues [1].pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("T03__",	ci.pKeyValues [1].pValues [2].szValue, ci.pKeyValues [1].pValues [2].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("B01",		ci.pKeyValues [2].pValues [0].szValue, ci.pKeyValues [0].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("B02_",	ci.pKeyValues [2].pValues [1].szValue, ci.pKeyValues [0].pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("B03__",	ci.pKeyValues [2].pValues [2].szValue, ci.pKeyValues [0].pValues [2].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("C01",		ci.pKeyValues [3].pValues [0].szValue, ci.pKeyValues [1].pValues [0].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("C02_",	ci.pKeyValues [3].pValues [1].szValue, ci.pKeyValues [1].pValues [1].lnValue));
		ubf_expect_bool_AND (b, !memcmp ("C03__",	ci.pKeyValues [3].pValues [2].szValue, ci.pKeyValues [1].pValues [2].lnValue));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
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

		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, 2 == ci.nSections);
		ubf_expect_bool_AND (b, 7 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 7 == ci.nValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, 3 == ci.pSections [0].nKeyValues);
		ubf_expect_bool_AND (b, 10 == ci.pSections [1].lnSectionName);
		ubf_expect_bool_AND (b, 4 == ci.pSections [1].nKeyValues);
		ubf_expect_bool_AND (b, !memcmp ("Section 01]", ci.pSections [0].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Section 02]", ci.pSections [1].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Key01 ",							ci.pKeyValues [0].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ",						ci.pValues [0].szValue, 9));
		ubf_expect_bool_AND (b, !memcmp ("Key02 ",							ci.pKeyValues [1].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("This is value 02\"",				ci.pValues [1].szValue, 17));
		ubf_expect_bool_AND (b, !memcmp ("Key03\t",							ci.pKeyValues [2].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("We are still in Section 01. ",	ci.pValues [2].szValue, 28));
		ubf_expect_bool_AND (b, !memcmp ("S02Key01 ",						ci.pKeyValues [3].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K01 ",					ci.pValues [3].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key02 ",						ci.pKeyValues [4].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K02 ",					ci.pValues [4].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key03 ",						ci.pKeyValues [5].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K03__x ",				ci.pValues [5].szValue, 16));
		ubf_expect_bool_AND (b, !memcmp ("S02Key04 ",						ci.pKeyValues [6].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K04__xy ",				ci.pValues [6].szValue, 17));
		ubf_expect_bool_AND (b, ci.pSections [0].pKeyValues == ci.pKeyValues);
		ubf_expect_bool_AND (b, &ci.pSections [0].pKeyValues [1] == &ci.pKeyValues [1]);
		DoneSCUNILOGINI (&ci);

		// Now we got one out-of-section key/value pair.
		memset (&ci, 255, sizeof (SCUNILOGINI));
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
			"\n"
			"\n"
			" [Section 03]"
			"\r"
			"\r"
			// Used for service tasks.
			" mkey = [S01] [S02] [S03]\n"
			"\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		// Note that we got "Key00 = Value00" before the first section. This means we got
		//	an additional "non-section", which is a section without a name. Our
		//	ci.nIniSections is therefore one greater than the real amount of sections.
		ubf_expect_bool_AND (b, 4 == ci.nSections);
		ubf_expect_bool_AND (b, 10 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0	== ci.pSections [0].lnSectionName);
		ubf_expect_bool_AND (b, 10	== ci.pSections [1].lnSectionName);
		ubf_expect_bool_AND (b, 11	== ci.pSections [2].lnSectionName);
		ubf_expect_bool_AND (b, 10	== ci.pSections [3].lnSectionName);
		ubf_expect_bool_AND (b, NULL == ci.pSections [0].szSectionName);
		ubf_expect_bool_AND (b, !memcmp ("Section 01]", ci.pSections [1].szSectionName, 11));
		ubf_expect_bool_AND (b, !memcmp ("Section 02_]", ci.pSections [2].szSectionName, 12));
		ubf_expect_bool_AND (b, !memcmp ("Section 03]", ci.pSections [3].szSectionName, 11));
		ubf_expect_bool_AND	(b,
			!memcmp ("Key00 ", ci.pKeyValues [0].szKeyName, 6)
							);
		ubf_expect_bool_AND	(b,
			!memcmp ("Value00; This is not a comment. It belongs to the value.", ci.pValues [0].szValue, 56)
							);
		ubf_expect_bool_AND (b, !memcmp ("Key01 ",							ci.pKeyValues [1].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ",						ci.pValues [1].szValue, 9));
		ubf_expect_bool_AND (b, !memcmp ("Key02 ",							ci.pKeyValues [2].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("This is value 02\"",				ci.pValues [2].szValue, 17));
		ubf_expect_bool_AND (b, !memcmp ("Key03\t",							ci.pKeyValues [3].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("We are still in Section 01. ",	ci.pValues [3].szValue, 28));
		ubf_expect_bool_AND (b, !memcmp ("S02Key01 ",						ci.pKeyValues [4].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K01 ",					ci.pValues [4].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key02 ",						ci.pKeyValues [5].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K02 ",					ci.pValues [5].szValue, 13));
		ubf_expect_bool_AND (b, !memcmp ("S02Key03 ",						ci.pKeyValues [6].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K03__x ",				ci.pValues [6].szValue, 16));
		ubf_expect_bool_AND (b, !memcmp ("S02Key04 ",						ci.pKeyValues [7].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value S01K04__xy ",				ci.pValues [7].szValue, 17));

		/* This is meant as a future extension where white space is required before some line comment
			strings to allow for "test!" without interpreting the exclamation mark as the start of a
			line comment. In "test !", on the other hand the exclamation mark is a line comment marker.
		ubf_expect_bool_AND (b, !memcmp ("S02Key05 ",						ci.pKeyValuePairs [8].szKeyName, 9));
		ubf_expect_bool_AND (b, !memcmp ("Value05 ",						ci.pKeyValuePairs [8].szValue, 8));
		ubf_expect_bool_AND (b, 5 == ci.pKeyValuePairs [8].lnValue);
		*/

		const char	*szValue;
		size_t		len = 4711;
		szValue = CunilogGetFirstIniValueFromKey (&len, "Section 01", USE_STRLEN, "Key01", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 4711 != len);
		ubf_expect_bool_AND (b, 8 == len);
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ", szValue, 9));

		// Case-insensitive for section and key.
		len = 4711;
		szValue = CunilogGetFirstIniValueFromKey_ci (&len, "SECtIOn 01", USE_STRLEN, "KEY01", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 4711 != len);
		ubf_expect_bool_AND (b, 8 == len);
		ubf_expect_bool_AND (b, !memcmp ("Value 01 ", szValue, 9));

		// Retrieves a key that does not have a section.
		len = 4712;
		szValue = CunilogGetFirstIniValueFromKey	(&len, NULL, 0, "Key00", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 4712 != len);
		ubf_expect_bool_AND (b, 56 == len);
		ubf_expect_bool_AND (b, !memcmp ("Value00; This is not a comment. It belongs to the value.", szValue, 56));

		// Case-insensitive for section and key.
		len = 4712;
		szValue = CunilogGetFirstIniValueFromKey_ci	(&len, NULL, 0, "KEY00", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, 4712 != len);
		ubf_expect_bool_AND (b, 56 == len);
		ubf_expect_bool_AND (b, !memcmp ("Value00; This is not a comment. It belongs to the value.", szValue, 56));


		pVals = NULL;
		nVals = CunilogGetIniValuesFromKey		(&pVals, NULL, 0, "Key00", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, NULL != pVals);
		ubf_expect_bool_AND (b, 0 < nVals);
		ubf_expect_bool_AND (b, 1 == nVals);
		ubf_expect_bool_AND (b, 56 == pVals->lnValue);
		ubf_expect_bool_AND (b, NULL != pVals->szValue);
		ubf_expect_bool_AND (b, !memcmp ("Value00; This is not a comment. It belongs to the value.", pVals->szValue, 56));

		pVals = NULL;
		//ci.pIniSections [0].pKeyValuePairs[0].pValues [0].szValue
		nVals = CunilogGetIniValuesFromKey_ci	(&pVals, NULL, 0, "KEY00", USE_STRLEN, &ci);
		ubf_expect_bool_AND (b, NULL != pVals);
		ubf_expect_bool_AND (b, 0 < nVals);
		ubf_expect_bool_AND (b, 1 == nVals);
		ubf_expect_bool_AND (b, 56 == pVals->lnValue);
		ubf_expect_bool_AND (b, NULL != pVals->szValue);
		ubf_expect_bool_AND (b, !memcmp ("Value00; This is not a comment. It belongs to the value.", pVals->szValue, 56));

		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"    \n"
			"/*\n"
			"    Comment. \n"
			"*/\n"
			"[S]\n"
			" arr = '1', '2', '3', '4', \n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 4 == ci.nValues);
		ubf_expect_bool_AND (b, 1 == ci.pValues [2].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [3].lnValue);
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"    \n"
			"/*\n"
			"    Comment. \n"
			"*/\n"
			"[S]\n"
			" arr = '1', /* Comment in the middle */ '2', '3', '4', \n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 4 == ci.nValues);
		ubf_expect_bool_AND (b, 1 == ci.pValues [0].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [1].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [2].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [3].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("1'", ci.pValues [0].szValue, ci.pValues [0].lnValue + 1));
		ubf_expect_bool_AND (b, !memcmp ("2'", ci.pValues [1].szValue, ci.pValues [1].lnValue + 1));
		ubf_expect_bool_AND (b, !memcmp ("3'", ci.pValues [2].szValue, ci.pValues [2].lnValue + 1));
		ubf_expect_bool_AND (b, !memcmp ("4'", ci.pValues [3].szValue, ci.pValues [3].lnValue + 1));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"    \n"
			"/*\n"
			"    Comment. \n"
			"*/\n"
			"[S]\n"
			" [arr] = '1', /* Comment in the middle */ '2', '3', '4', \n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, !memcmp ("S]", ci.pSections [0].szSectionName, 2));
		ubf_expect_bool_AND (b, 1 == ci.nKeyValues);
		ubf_expect_bool_AND (b, !memcmp ("arr]", ci.pKeyValues [0].szKeyName, 4));
		ubf_expect_bool_AND (b, !memcmp ("=", ci.pKeyValues [0].szEqualsSign, 1));
		ubf_expect_bool_AND (b, 4 == ci.nValues);
		ubf_expect_bool_AND (b, 1 == ci.pValues [0].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [1].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [2].lnValue);
		ubf_expect_bool_AND (b, 1 == ci.pValues [3].lnValue);
		ubf_expect_bool_AND (b, !memcmp ("1'", ci.pValues [0].szValue, ci.pValues [0].lnValue + 1));
		ubf_expect_bool_AND (b, !memcmp ("2'", ci.pValues [1].szValue, ci.pValues [1].lnValue + 1));
		ubf_expect_bool_AND (b, !memcmp ("3'", ci.pValues [2].szValue, ci.pValues [2].lnValue + 1));
		ubf_expect_bool_AND (b, !memcmp ("4'", ci.pValues [3].szValue, ci.pValues [3].lnValue + 1));
		DoneSCUNILOGINI (&ci);

		// Values only.
		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"[Section]\n"
			" /* Comment */v1 /* Comment */ \n"
			" /* Comment */v2 /* Comment */\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, !memcmp ("Section]", ci.pSections [0].szSectionName, 8));
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0 == ci.nValues);
		ubf_expect_bool_AND (b, 2 == ci.pKeyValues [0].lnKeyName);
		ubf_expect_bool_AND (b, 2 == ci.pKeyValues [1].lnKeyName);
		ubf_expect_bool_AND (b, !memcmp ("v1 ", ci.pKeyValues [0].szKeyName, 3));
		ubf_expect_bool_AND (b, !memcmp ("v2 ", ci.pKeyValues [1].szKeyName, 3));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"[Section]\n"
			" key 1\n"
			" key 2_\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, !memcmp ("Section]", ci.pSections [0].szSectionName, 8));
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0 == ci.nValues);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [0].lnKeyName);
		ubf_expect_bool_AND (b, 6 == ci.pKeyValues [1].lnKeyName);
		ubf_expect_bool_AND (b, !memcmp ("key 1", ci.pKeyValues [0].szKeyName, 5));
		ubf_expect_bool_AND (b, !memcmp ("key 2_", ci.pKeyValues [1].szKeyName, 6));

		size_t ln;
		const char *csz = CunilogGetFirstIniValueFromKey	(
								&ln, "Section", USE_STRLEN, "key 2_", USE_STRLEN,
								&ci
															);
		UNUSED (csz);
		ubf_expect_bool_AND (b, NULL == csz);
		ubf_expect_bool_AND (b, 0 == ln);
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "key 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "Key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY_1", USE_STRLEN, &ci));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"[Section] key 1\n"
			" key 2_\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, !memcmp ("Section]", ci.pSections [0].szSectionName, 8));
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0 == ci.nValues);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [0].lnKeyName);
		ubf_expect_bool_AND (b, 6 == ci.pKeyValues [1].lnKeyName);
		ubf_expect_bool_AND (b, !memcmp ("key 1", ci.pKeyValues [0].szKeyName, 5));
		ubf_expect_bool_AND (b, !memcmp ("key 2_", ci.pKeyValues [1].szKeyName, 6));
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "Key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY_1", USE_STRLEN, &ci));
		DoneSCUNILOGINI (&ci);

		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"[Section] [key 1]\n"
			" key 2_\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, !memcmp ("Section]", ci.pSections [0].szSectionName, 8));
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0 == ci.nValues);
		ubf_expect_bool_AND (b, 5 == ci.pKeyValues [0].lnKeyName);
		ubf_expect_bool_AND (b, 6 == ci.pKeyValues [1].lnKeyName);
		ubf_expect_bool_AND (b, !memcmp ("key 1", ci.pKeyValues [0].szKeyName, 5));
		ubf_expect_bool_AND (b, !memcmp ("key 2_", ci.pKeyValues [1].szKeyName, 6));
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "Key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY_1", USE_STRLEN, &ci));
		DoneSCUNILOGINI (&ci);

		// These are sections.
		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"[Section] \n"
			" [key 1]\n"
			" [key 2_]\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 3 == ci.nSections);
		ubf_expect_bool_AND (b, 0 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0 == ci.nValues);
		ubf_expect_bool_AND (b, !memcmp ("Section]",	ci.pSections [0].szSectionName, 8));
		ubf_expect_bool_AND (b, !memcmp ("key 1]",		ci.pSections [1].szSectionName, 6));
		ubf_expect_bool_AND (b, !memcmp ("key 2_]",		ci.pSections [2].szSectionName, 7));
		// These are sections, not keys.
		ubf_expect_bool_AND (b, !CunilogIniKeyExists ("Section", USE_STRLEN, "key 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists ("Section", USE_STRLEN, "key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "Key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY_1", USE_STRLEN, &ci));
		DoneSCUNILOGINI (&ci);

		// Add equals signs to ensure the keys are not understood as sections.
		memset (&ci, 255, sizeof (SCUNILOGINI));
		strcpy	(szIni,
			"[Section] \n"
			" [key 1]	=\n"
			" [key 2_]	=\n"
				);
		b1 = CreateSCUNILOGINI (&ci, szIni, USE_STRLEN);
		ubf_assert_true (b1);
		ubf_expect_bool_AND (b, b1);
		ubf_expect_bool_AND (b, 1 == ci.nSections);
		ubf_expect_bool_AND (b, 2 == ci.nKeyValues);
		ubf_expect_bool_AND (b, 0 == ci.nValues);
		ubf_expect_bool_AND (b, !memcmp ("Section]",	ci.pSections [0].szSectionName, 8));
		ubf_expect_bool_AND (b, !memcmp ("key 1]",		ci.pSections [0].pKeyValues [0].szKeyName, 6));
		ubf_expect_bool_AND (b, !memcmp ("key 2_]",		ci.pSections [0].pKeyValues [1].szKeyName, 7));
		ubf_expect_bool_AND (b, 0 == ci.pSections [0].pKeyValues [0].nValues);
		ubf_expect_bool_AND (b, 0 == ci.pSections [0].pKeyValues [1].nValues);
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists ("Section", USE_STRLEN, "key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY 1", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, CunilogIniKeyExists_ci ("Section", USE_STRLEN, "Key 2_", USE_STRLEN, &ci));
		ubf_expect_bool_AND (b, !CunilogIniKeyExists_ci ("Section", USE_STRLEN, "kEY_1", USE_STRLEN, &ci));
		DoneSCUNILOGINI (&ci);


		return b;
	}
#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT.

#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER.
