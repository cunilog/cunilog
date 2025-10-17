/****************************************************************************************

	File:		strlineextractstructs.h
	Why:		Config file structures.
	OS:			C99.
	Author:		Thomas
	Created:	2025-10-08

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-10-08	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The module provides the config file structures for various purposes.
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

#ifndef U_CUNILOGCFGSTRUCTS_H
#define U_CUNILOGCFGSTRUCTS_H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	The structures for ini files.
*/
// An array of ini values. Each key can have several values.
typedef struct scuniloginivalues
{
	const char				*szValue;						// Value of a multi-value key.
	size_t					lnValue;						// Its length.
} SCUNILOGINIVALUES;

// A key with its values.
typedef struct scuniloginikeyandvalues
{
	const char				*szKeyName;
	size_t					lnKeyName;

	SCUNILOGINIVALUES		*pValues;						// A key can have multiple values.
	unsigned int			nValues;
} SCUNILOGINIKEYANDVALUES;

// A section.
typedef struct scuniloginisection
{
	const char				*szSectionName;
	size_t					lnSectionName;
	SCUNILOGINIKEYANDVALUES	*pKeyValuePairs;
	unsigned int			nKeyValuePairs;
} SCUNILOGINISECTION;

// The ini file itself.
typedef struct scunilogini
{
	char					*buf;
	SCUNILOGINISECTION		*pIniSections;
	unsigned int			nIniSections;					// Number of sections. A "non-section"
															//	also counts as section.

	SCUNILOGINIKEYANDVALUES	*pKeyValuePairs;				// All key/value pairs. Multiple values
															//	are possible.
	unsigned int			nKeyValuePairs;

	SCUNILOGINIVALUES		*pValues;						// All values that belong to keys.
	unsigned int			nValues;

	// Parse error.
	size_t					errLineNumber;					// The line number within the buffer.
															//	First line is 1.
	size_t					errCharNumber;					// The position of pStart within
															//	a line. 1 = first column/character.
	size_t					errAbsPosition;					// Position within the entire buffer.
															//	1 = first position/character.
	bool					bParseFail;
} SCUNILOGINI;
/*
	End of structures for ini files.
*/


EXTERN_C_END

#endif														// Of #ifndef U_CUNILOGCFGSTRUCTS_H.
