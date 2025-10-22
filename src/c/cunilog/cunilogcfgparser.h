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
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Implements a simple config parser. The Windows ini file format
	(https://en.wikipedia.org/wiki/INI_file) served as its base. Notable differences
	include support for C++-style multi-line comments, C-style comments, arbitrary
	quotes, and white space.
	
	Section names and key names are case-sensitive by default.


	Not implemented yet:

	In the future, an implementation similar to a config file reader/parser for Libucl
	(https://github.com/vstakhov/libucl) is planned too.

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

#ifndef CUNILOGCFGPARSER_H
#define CUNILOGCFGPARSER_H

#ifdef CUNILOG_BUILD_CFG_PARSER

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./restrict.h"
		//#include "./platform.h"
		#include "./strlineextractstructs.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/restrict.h"
		//#include "./../pre/platform.h"
		#include "./../string/strlineextractstructs.h"
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
	CreateSCUNILOGINI

	Parses the ini buffer szIniBuf points to with length of lnIniBuf. If lnIniBuf is
	USE_STRLEN, the function uses strlen () to obtain it. Otherwise, the buffer does not
	need to be NUL-terminated.

	The structure pCunilogIni receives the structure data of the ini buffer. Use one of the
	CunilogGetIni... () functions to obtain data from it.

	The function returns true on success, false otherwise. When the function returns false,
	the members errLineNumber, errCharNumber, and errAbsPosition of the SCUNILOGINI structure
	pCunilogIni point to contain the position at which the buffer couldn't be parsed.
	Additionally, the boolean bParseFail is set to true.

	The caller does not need to initialise the SCUNILOGINI structure pCunilogIni points
	to beforehand.
*/
bool CreateSCUNILOGINI (SCUNILOGINI *pCunilogIni, const char *szIniBuf, size_t lnIniBuf)
;

/*
	DoneSCUNILOGINI

	Frees the resources taken by the SCUNILOGINI structure pCunilogIni points to.
	
	After this function has been called on the structure, none of the
	CunilogGetIni... () functions can be used on it anymore until it is initialised again
	with CreateSCUNILOGINI ().
*/
void DoneSCUNILOGINI (SCUNILOGINI *pCunilogIni)
;

/*
	CunilogGetIniValuesFromKey

	pValues			A pointer to an array of SCUNILOGINIVALUES structures that receives
					the values of szKey.

	szSection		The name of the section the key belongs to. Keys do not necessarily
					belong to a section. To obtain a key that is not part of a section,
					set szSection to NULL and lnSection to 0.

	lnSection		The length of the section name szSection. Use USE_STRLEN for the
					function to call strlen (szSection). Otherwise the name does not
					need to be NUL-terminated.

	szKey			The name of the key whose first value is to be retrieved. This parameter
					cannot be NULL.

	lnKey			The length of the key name. If USE_STRLEN, the function uses strlen ()
					to obtain it. Otherwise the name does not need to be NUL-terminated.

	pCunilogIni		A pointer to an SCUNILOGINI structure. The structure must have been
					initialised with CreateSCUNILOGINI ().

	The function returns the amount of values the key szKey of section szSection contains.
	If the section or key cannot be found, the function returns 0.
*/
unsigned int CunilogGetIniValuesFromKey		(
				SCUNILOGINIVALUES	**pValues,
				const char			*cunilog_restrict szSection,	size_t	lnSection,
				const char			*cunilog_restrict szKey,		size_t	lnKey,
				SCUNILOGINI			*pCunilogIni
											)
;

/*
	CunilogGetIniValuesFromKey_ci

	This function is identical to CunilogGetIniValuesFromKey () but is case-insensitive
	for the parameters szSection and szKey.
*/
unsigned int CunilogGetIniValuesFromKey_ci	(
				SCUNILOGINIVALUES	**pValues,
				const char			*cunilog_restrict szSection,	size_t	lnSection,
				const char			*cunilog_restrict szKey,		size_t	lnKey,
				SCUNILOGINI			*pCunilogIni
											)
;

/*
	CunilogGetFirstIniValueFromKey

	Retrieves the first value of a key that belongs to section szSection.

	pLen			A pointer to a size_t that receives the length of the returned string.
					If this parameter is NULL, the function does not provide the length
					of the returned string. Note that the string value the function
					returns is not NUL-terminated, hence it is not recommended to set this
					parameter to NULL.

	szSection		The name of the section the key belongs to. Keys do not necessarily
					belong to a section. To obtain a key that is not part of a section,
					set szSection to NULL and lnSection to 0.

	lnSection		The length of the section name szSection. Use USE_STRLEN for the
					function to call strlen (szSection). Otherwise the name does not
					need to be NUL-terminated.

	szKey			The name of the key whose first value is to be retrieved. This parameter
					cannot be NULL.

	lnKey			The length of the key name. If USE_STRLEN, the function uses strlen ()
					to obtain it. Otherwise the name does not need to be NUL-terminated.

	pCunilogIni		A pointer to an SCUNILOGINI structure. The structure must have been
					initialised with CreateSCUNILOGINI ().

	The function returns a pointer to the first value of the key, without quotation markers.
	This string is not NUL-terminated. If pLen is not NULL, the function provides the length
	of the returned string at the address it points to.

	The function returns NULL if the key does not exist. When the function returns NULL,
	the address pLen points to is not changed.
*/
const char *CunilogGetFirstIniValueFromKey		(
				size_t			*pLen,
				const char		*cunilog_restrict szSection,	size_t	lnSection,
				const char		*cunilog_restrict szKey,		size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
												)
;

/*
	CunilogGetFirstIniValueFromKey_ci

	This function is identical to CunilogGetFirstIniValueFromKey () but is case-insensitive
	for the parameters szSection and szKey.
*/
const char *CunilogGetFirstIniValueFromKey_ci	(
				size_t			*pLen,
				const char		*cunilog_restrict szSection,	size_t	lnSection,
				const char		*cunilog_restrict szKey,		size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
												)
;

/*
	TestCunilogCfgParser

*/
#ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT
	bool TestCunilogCfgParser (void);
#else
	#define TestCunilogCfgParser()
#endif

#else
	#define TestCunilogCfgParser()
#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER.

EXTERN_C_END

#endif														// Of #ifndef CUNILOGCFGPARSER_H.
