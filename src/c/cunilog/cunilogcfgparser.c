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
		#include "./ubfdebug.h"
		#include "./memstrstr.h"
		#include "./ubfmem.h"
		#include "./strnewline.h"
	#else
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/memstrstr.h"
		#include "./../mem/ubfmem.h"
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

bool ignoreLineComment (CUNILOGCFGPARSERSTATUS *ps)
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

bool ignoreMultiLineComment (CUNILOGCFGPARSERSTATUS *ps)
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

char *usableString (SCUNILOGCFGNODE *pn, CUNILOGCFGPARSERSTATUS *ps, CUNILOGCFGERR *pErr)
{
	ubf_assert_non_NULL (pn);
	ubf_assert_non_NULL (ps);

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

size_t lenUsableString (SCUNILOGCFGNODE *pn, CUNILOGCFGPARSERSTATUS *ps, CUNILOGCFGERR *pErr)
{
	ubf_assert_non_NULL (ps);

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
	ubf_assert_non_NULL (cfg);
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

		return b;
	}
#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT.

#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER.
