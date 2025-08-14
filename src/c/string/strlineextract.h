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

#ifndef U_STRLINEEXTRACT_H
#define U_STRLINEEXTRACT_H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

enum enStrlineExtractCharSet
{
		EN_STRLINEEXTRACT_UTF8
	,	EN_STRLINEEXTRACT_UTF16								// Not supported yet.
};

/*
	The members pchStartMultiCommentStr and pchEndMultiCommentStr point to string arrays that
	define the start and end of a block comment (multi-line comment). The member
	nMultiCommentStr holds the amount of array elements. Both arrays need to have the same
	amount of elements, and nMultiCommentStr must be precisely this value. Both arrays
	can be set to NULL if nMultiCommentStr is 0. No multi-line (block) comments are accepted
	in this case.
*/
typedef struct strlineconf
{
	enum enStrlineExtractCharSet	CharacterSet;			// Specifies the used character set.
															//	Currently, only
															//	EN_STRLINEEXTRACT_UTF8 is
															//	supported.
	size_t							tabSize;				// The width of a TAB character.
															//	Currently not used/supported.
	char							**pchLineCommentStr;	// Pointer to an array of strings, in
															//	UTF-8, containing line comment
															//	characters. If this is NULL, no
															//	line comments are accepted.
	size_t							nLineCommentStr;		// Size of the array of strings
															//	pchLineCommentStr points to.
															//	Must be 0 if pchLineCommentStr
															//	is NULL. If this is 0, no line
															//	comments are accepted.
	// Start and end multi-line comments characters.
	char							**pchStartMultiCommentStr;
	char							**pchEndMultiCommentStr;
	size_t							nMultiCommentStr;
	#ifdef DEBUG
		bool						bInitialised;
	#endif
} STRLINECONF;

/*
	STRLINEINF

	The structure passed on to the callback function.
*/
typedef struct strlineinf
{
	void				*pStart;							// Pointer to the first character
															//	of a line that is not a white
															//	space character.
	size_t				lnLength;							// Length of a line, not counting
															//	ending white space characters
															//	or new line control codes.
	size_t				lineNumber;							// The line number within the buffer.
															//	First line is 1.
	size_t				charNumber;							// The position of pStart within
															//	a line. 1 = first column/character.
	size_t				absPosition;						// Position within the entrie buffer.
															//	1 = first position/character.
	void				*pCustom;							// Can be used by the caller.
	#ifdef DEBUG
		bool			bInitialised;
	#endif
} STRLINEINF;

/*
	User callback function.

	Should return true for every line processed. When this function returns false,
	the functions StrLineExtract () or StrLineExtractU8 () return too, and return the amount
	of times the callback function has been invoked.
*/
typedef bool (*StrLineExtractCallback) (STRLINEINF *psli);

/*
	InitSTRLINECONFforUBFL

	Initialises the STRLINECONF structure pc points to for UBFL language translation
	file single and multi-line (block) comments and a tab size of 4. Character set is UTF-8
	(EN_STRLINEEXTRACT_UTF8).
	
	In addition to C/C++ multi (block) and single line comments, UBFL language translation
	files also accept the following characters as the start of a line comment:
	"#", ";", "+", "-", "!".
	Their multi (block) and single line comment characters are therefore suitable for some
	scripting languages.
*/
void InitSTRLINECONFforUBFL (STRLINECONF *pc)
;

/*
	InitSTRLINECONFforC
	
	Initialises the STRLINECONF structure pc points to for C/C++ lines and multi-line
	comments and a tab size of 4. Character set is UTF-8 (EN_STRLINEEXTRACT_UTF8).
*/
void InitSTRLINECONFforC (STRLINECONF *pc);

/*
	SanityCheckMultiComments

	Performs a simple sanity check on the string arrays that define the multi/block comments.
	This function is NOT a replacement for the caller to ensure the comments and their amounts
	are correct! It is the responsibility of the caller to ensure the members
	pchStartMultiCommentStr, pchEndMultiCommentStr, and nMultiCommentStr are initialised
	correctly.

	The function returns true if the sanity check is passed, false if not.
*/
bool SanityCheckMultiComments (STRLINECONF *pc);

/*
	StrLineExtractU8

	The actual UTF-8 line extractor, which is called by StrLineExtract () depending
	on the CharacterSet member of the STRLINECONF structure. Debug versions assert that
	this member is EN_STRLINEEXTRACT_UTF8.

	See descrption of StrLineExtract () for details.

	The function returns how many times the callback function has been invoked,
	which can be 0.
*/
unsigned int StrLineExtractU8	(
				char					*pBuf,
				size_t					lenBuf,
				STRLINECONF				*pConf,
				StrLineExtractCallback	cb,
				void					*pCustom
								)
;

/*
	StrLineExtract

	The entry function for the line extractor. It calls the callback function for each
	extracted line. The STRLINECONF structure pConf points to controls how lines are
	extracted while line and block (multi-line) comments are ignored. Each extracted
	line is stripped of leading and trailing white space before it is passed on to the
	callback function cb points to. The callback function receives a pointer to a STRLINEINF
	structure that contains a pointer to the line buffer, its length, and a few other
	parameters, like for instance the line number.

	Call InitSTRLINECONFforC () to configure the STRLINECONF structure for C-style
	line and block comments, call InitSTRLINECONFforUBFL () to initialise the structure
	for UBFL language file line and multi-line comments, or use either function as an
	example to roll your own.

	pBuf			A pointer to the buffer that contains the data of which lines are
					to be extracted. This buffer does not have to be NUL-terminated
					unless lenBuf is set to USE_STRLEN.

	lenBuf			The length of the buffer, in characters. This can be USE_STRLEN,
					in which case the function obtains the length of pBuf by calling
					strlen () on it. For any other value, the buffer does not need to
					be NUL-terminated.

	pConf			A pointer to an initialised STRLINECONF structure. The caller fills
					this structure to control the function. If this parameter is NULL,
					the function uses its own STRLINECONF structure and calls
					InitSTRLINECONFforUBFL () for it before it is used.

	cb				A pointer to a StrLineExtractCallback () callback function. This
					function is called for each extracted line. The function is passed
					an STRLINEINF structure with some information. The callback function
					returns true for each line processed. When the function returns
					false StrLineExtract returns too, returning the amount of times
					the callback function has been called so far.

	pCustom			An arbitrary pointer passed on to the callback function through
					the pCustom member of the STRLINEINF structure.

	When the function succeeds, it returns how many times the callback function has been
	invoked, which can be 0.
	
	If the function fails, the return value is UINT_MAX. The function can only fail if
	the number of start and end block comment characters are not identical. You can
	call SanityCheckMultiComments () beforehand to ensure the function is not going to
	fail.
*/
unsigned int StrLineExtract	(
				void					*pBuf,
				size_t					lenBuf,
				STRLINECONF				*pConf,
				StrLineExtractCallback	cb,
				void					*pCustom
							)
;

/*
	strlineextractRemoveLeadingWhiteSpace

	Returns a pointer inside szLine with leading white space removed. The parameter pLen
	points to contains the new length without the white space.
*/
const char *strlineextractRemoveLeadingWhiteSpace (size_t *pLen, const char *szLine, size_t lnLine)
;

/*
	strlineextractIsOpenQuote

	Returns the 1-based index of an open quote or 0 if szLine doesn't start with an open
	quote. The returned 1-based index can be passed to the function
	strlineextractIsCloseQuote () as the parameter idxCloseQuote1based if it is greater
	than 0.
*/
unsigned int strlineextractIsOpenQuote	(
		const char		*szLine,			size_t			lnLine,
		unsigned int	nQuotes,
		const char		**pszOpenQuotes
										)
;

/*
	strlineextractIsCloseQuote

	Returns true if szLine starts with the closing quote that has the 1-based index
	idxCloseQuote1based. The parameter idxCloseQuote1based is the return value of the
	function strlineextractIsOpenQuote (), but not 0. Do not call this function if
	strlineextractIsOpenQuote () returned 0.
*/
bool strlineextractIsCloseQuote	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszCloseQuotes,
		unsigned int	idxCloseQuote1based
								)
;

/*
	strlineextractIsEqual

	Returns the 1-based index of the string pointer in pszEquals,
	if szLine starts with any of the equality characters specified
	in pszEquals.

	The function returns 0 if szLine does not start with any of the equality
	character strings in pszEquals.
*/
unsigned int strlineextractIsEqual	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszEquals,		unsigned int	nEquals
									)
;

/*
	strlineextractKeyOrValue

	Extracts a key or a value by taking quotations, if any, into consideration.
	The key or value is extracted without quotes. If no quotes are encountered,
	the key or value is extracted up to the last character before white space
	before an equality sign, or, if no equality sign is found, up to the last
	character before white space.
	
	If the key or value is quoted, the key or value inside the quotes is extracted.
	The function fails (returns false) if no closing quote is found.

	If a key or value doesn't start with an opening quote but contains quotes,
	the quotes are treated as normal characters.

	The extracted key is not NUL-terminated, since it is only a pointer to a buffer,
	and its length, inside the original buffer szLine points to.

	Leading white space, if any, is ignored.
*/
bool strlineextractKeyOrValue	(
		const char		**pszKeyOrVal,		size_t			*plnKeyOrVal,	// Out.
		const char		**pszEqual,			size_t			*plnEqual,		// Out.
		unsigned int	*pidxEqual1based,									// Out.
		const char		*szLine,			size_t			lnLine,			// In.
		unsigned int	nQuotes,											// In.
		const char		**pszOpenQuotes,									// In.
		const char		**pszClosQuotes,									// In.
		const char		**pszEquals,		unsigned int	nEquals			// In.
								)
;

/*
	strlineextractKeyAndValue

	Extracts a key and value from szLine with length lnLine. If lnLine is USE_STRLEN,
	the function calls strlen (szLine) to obtain it.

	Parameters

	pszKey			A pointer that receives the start address of the key. This parameter
					cannot be NULL.

	plnKey			A pointer to a size_t that receives the length of the key. This parameter
					must not be NULL.

	pszVal			A pointer that receives the start address of the value. This
					parameter cannot be NULL.

	lnVal			A pointer to a size_t that receives the length of the value. This
					parameter cannot be NULL.

	pszOpenQuotes	A pointer to an array of NUL-terminated strings recognised as opening
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszClosQuotes	A pointer to an array of NUL-terminated strings recognised as closing
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	nQuotes			The amount of quote strings. See parameters szOpenQuotes and
					szClosQuotes above. If this value is 0, no quotes are recognised.

	pszEquals		A pointer to an array of NUL-terminated strings recognised as equality
					characters/strings. The parameter nEquals specifies the number of
					stings/elements in this array.

	The function returns true if a key and a value could be extracted from the line,
	which includes an empty string for the value but not for the key. The function
	returns false if szLine is NULL or lnLine is 0.
*/
bool strlineextractKeyAndValue	(
		const char		**pszKey,			size_t			*plnKey,
		const char		**pszVal,			size_t			*plnVal,
		const char		*szLine,			size_t			lnLine,
		unsigned int	nQuotes,
		const char		**pszOpenQuotes,
		const char		**pszClosQuotes,
		const char		**pszEquals,		unsigned int	nEquals
								)
;

/*
	test_strlineextract

	Function that tests the module. Returns true if all tests have been completed
	successfully, false otherwise.
*/
#ifdef STRLINEEXTRACT_BUILD_TEST_FNCT
	bool test_strlineextract (void);
#else
	#define test_strlineextract()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_STRLINEEXTRACT_H.
