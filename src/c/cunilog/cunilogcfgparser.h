/****************************************************************************************

	File:		cunilogcfgparser.h
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
	Implements a simple config parser. Libucl (https://github.com/vstakhov/libucl) served as
	its base idea.

	The library couldn't be used for several reasons:
	- Too big and too feature-rich.
	- Doesn't support C++ style line comments (//).
	- Lots of error handling.

	Compared to libucl, this module is very simple.

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

	Each config entity is treated as a key/value pair, for instance:
	key = value;
	The semicolon at the end of a key/value pair is optional.
*/

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

#ifndef CUNILOGCFGPARSER_H
#define CUNILOGCFGPARSER_H

#ifdef CUNILOG_BUILD_CFG_PARSER

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		//#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		//#include "./../pre/platform.h"
	#endif

#endif

#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

EXTERN_C_BEGIN

typedef uint64_t	cunilogcfgopts;

#ifndef SCUNILOGCFGNODE_LINKED_LIST
#define SCUNILOGCFGNODE_LINKED_LIST		((size_t) -1)
#endif

enum scunilogcfgnode_valuetype
{
	scunilogval_pstring,
	scunilogval_pvoid,
	scunilogval_uint,										// No pointer.
	scunilogval_size										// No pointer.
};
typedef enum scunilogcfgnode_valuetype	scunilogvaltype;

/*
	A single config node.

	If nChildren is SCUNILOGCFGNODE_LINKED_LIST, pChildren points to a singly-linked list instead
	of an array.

	String values are stored NUL-terminated and lenValue is set to strlen (szValue), meaning that
	the size of the value data is lenValue + 1. For all other data lenValue is identical to the
	allocated size.
*/
typedef struct scunilogcfgnode
{
	struct scunilogcfgnode	*pParent;						// If NULL, this is the root.
	char					*szKeyName;
	size_t					lenKeyName;
	scunilogvaltype			valtype;
	union uval
	{
		char				*szValue;
		void				*pvValue;
		size_t				stValue;
		uint64_t			uiValue;
	} val;
	size_t					lenValue;
	struct scunilogcfgnode	*pChildren;
	size_t					nChildren;
	struct scunilogcfgnode	*pNext;							// NULL if nChildren is
															//	SCUNILOGCFGNODE_LINKED_LIST.
} SCUNILOGCFGNODE;

/*
	Errors that can be returned.
*/
enum cunilogcfgerrors
{
	cunilogcfgError,
	cunilogcfgErrorNoIdea
};
typedef enum cunilogcfgerrors	cunilogCfgError;

/*
	Structure to return a parse error.
*/
typedef struct cunilogcfgerr
{
	size_t					errLine;						// Line number, starts at 1.
	size_t					errColumn;						// Column, starts at 1.
	cunilogCfgError			err;							// Error code.
} CUNILOGCFGERR;

/*
	The parser status structure.
*/
typedef struct cunilogcfgparserstatus
{
	// Positions.
	char					*szCfg;							// Pointer to the next octet.
	size_t					lnCfg;							// Remaining length in octets.
	size_t					linNum;							// Line number; starts at 1.
	size_t					colNum;							// Column number; starts at 1.

	// Current status.
	char					litChr;							// First and last octet of a literal.
	size_t					litNum;							// Amount of open literals.
	size_t					mulCom;							// Amount of open multi-line comments.

	// Error.
	CUNILOGCFGERR			cfgErr;
} CUNILOGCFGPARSERSTATUS;

/*
	ParseCunilogRootConfigData

	Parses the config data szConfigData points to up to a length of lenData and returns a
	newly allocated SCUNILOGCFGNODE root structure.

	In case of an error the function returns NULL and fills the members of the CUNILOGCFGERR
	structure pErr points to accordingly to provide some clue about the nature of the error.
*/
SCUNILOGCFGNODE *ParseCunilogRootConfigData (char *szConfigData, size_t lenData, CUNILOGCFGERR *pErr)
;

/*
	DoneCunilogRootConfigData

	Deallocates the resources used by the SCUNILOGCFGNODE root structure cfg points to.
*/
void DoneCunilogRootConfigData (SCUNILOGCFGNODE *cfg)
;

/*
	TestCunilogCfgParser

	Test function for the module.
*/
#ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT
	bool TestCunilogCfgParser (void);
#else
	#define TestCunilogCfgParser()
#endif

EXTERN_C_END

#else
	#define TestCunilogCfgParser()
#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER.

#endif														// Of #ifndef CUNILOGCFGPARSER_H.
