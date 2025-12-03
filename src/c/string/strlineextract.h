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
	The module provides a simple line extractor for various purposes.
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

	#include "./strlineextractstructs.h"

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
	Our default string parameters for single and multi-line comments, open
	and closing quotes, equality signs, and section start and end strings.
*/
extern const char	*ccCulStdLineCComment	[];
extern unsigned int	nCulStdLineCComment;

extern const char	*ccCulStdLineUComment	[];
extern unsigned int	nCulStdLineUComment;

extern const char	*ccCulStdBegMultComment	[];
extern const char	*ccCulStdEndMultComment	[];
extern unsigned int	nccCulStdMultComment;

extern const char	*ccCulStdOpenQuotes		[];
extern const char	*ccCulStdClosQuotes		[];
extern unsigned int	nCulStdQuotes;

extern const char	*ccCulStdEqualSigns		[];
extern unsigned int	nCulStdEquals;

extern char			*ccCulStdStrtSection	[];
extern char			*ccCulStdExitSection	[];
extern unsigned int	nCulStdSections;

// Additional strings or characters that are recognised as white space.
extern char			*ccCulStdExtraWhiteSpc	[];
extern unsigned int	nCulStdExtraWhiteSpc;

/*
	
*/
typedef struct sculmltstrings
{
	const char		**ccLineComments;
	unsigned int	nLineComments;

	const char		**ccBegMultiComments;
	const char		**ccEndMultiComments;
	unsigned int	nMultiComments;

	const char		**ccOpenQuotes;
	const char		**ccClosQuotes;
	unsigned int	nQuotes;

	const char		**ccEquals;
	unsigned int	nEquals;

	char			**ccStrtSections;
	char			**ccExitSections;
	unsigned int	nSections;

	const char		**ccExtraWhiteSpc;
	unsigned int	nExtraWhiteSpc;
} SCULMLTSTRINGS;

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
	const char						**pchLineCommentStr;	// Pointer to an array of strings, in
															//	UTF-8, containing line comment
															//	characters. If this is NULL, no
															//	line comments are accepted.
	size_t							nLineCommentStr;		// Size of the array of strings
															//	pchLineCommentStr points to.
															//	Must be 0 if pchLineCommentStr
															//	is NULL. If this is 0, no line
															//	comments are accepted.
	// Start and end multi-line comments characters.
	const char						**pchStartMultiCommentStr;
	const char						**pchEndMultiCommentStr;
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
	const char			*szStart;							// Pointer to the first character
															//	of a line that is not a white
															//	space character.
	size_t				lnLength;							// Length of a line, not counting
															//	ending white space characters
															//	or new line control codes.
	size_t				lineNumber;							// The line number within the buffer.
															//	First line is 1.
	size_t				charNumber;							// The position of pStart within
															//	a line. 1 = first column/character.
	size_t				absPosition;						// Position within the entire buffer.
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
	InitSCULMLTSTRINGSforUBFL
	InitSCULMLTSTRINGSforC

	Initialisation functions for a SCULMLTSTRINGS structure, either for C or for UBFL
	language translation file single and block comments.
*/
void InitSCULMLTSTRINGSforUBFL (SCULMLTSTRINGS *psmls);
void InitSCULMLTSTRINGSforC (SCULMLTSTRINGS *psmls);

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
				const char				*pBuf,
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
	callback function cb points to. Lines only consisting of comments (single and multi)
	are stripped. Multi-line comments that start and end on a single line are stripped
	only when they appear before any significant character. They are not removed anywhere
	else, since the function does not know the syntax the caller deems valid.

	The callback function receives a pointer to a STRLINEINF structure that contains a
	pointer to the line buffer, its length, and a few other parameters, like for
	instance the line number.

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
					false, StrLineExtract returns too, returning the amount of times
					the callback function has been called so far.

	pCustom			An arbitrary pointer passed on to the callback function through
					the pCustom member of the STRLINEINF structure.

	When the function succeeds, it returns how many times the callback function has been
	invoked, which can be 0. If the function fails, the return value is UINT_MAX.
*/
unsigned int StrLineExtract	(
				const void				*pBuf,
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
	strlineextractIsOpenString

	Returns the 1-based index of an opening string if szLine starts with it,
	or 0 if szLine doesn't start with an opening string.
	The returned 1-based index can be passed to the function
	strlineextractIsCloseString () as the parameter idxCloseString1based if it is greater
	than 0.
*/
unsigned int strlineextractIsOpenString	(
		const char		*szLine,			size_t			lnLine,
		unsigned int	nOpenStrings,		const char		**pszOpenStrings
										)
;

/*
	strlineextractIsCloseString

	Returns true if szLine starts with the closing string that has the 1-based index
	idxCloseString1based. The parameter idxCloseString1based is the return value of the
	function strlineextractIsOpenString (), but not 0. Do not call this function if
	strlineextractIsOpenString () returned 0.
*/
bool strlineextractIsCloseString	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszCloseStrings,
		unsigned int	idxCloseString1based
								)
;

/*
	strlineextractIsEqual

	Wrapper for strlineextractIsOpenString (), because the function name looks
	odd when we check for an equality sign.
*/
#define strlineextractIsEqual(lne, len, nO, pS)			\
	strlineextractIsOpenString (lne, len, nO, pS)

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
	these quotes are treated as normal characters.

	The extracted key is not NUL-terminated, since it is only a pointer to a buffer,
	and its length, inside the original buffer szLine points to.

	Leading and trailing white space, if any, is ignored.

	Parameters
	----------

	pszKeyOrVal		A pointer that receives the start address of the key or value, depending
					on whether an equality string is encountered. If an equality string is
					enountered towards the right side of the line, the returned pointer is
					a key, otherwise it's a value. This parameter cannot be NULL. This
					returned string is not NUL-terminated, because it is just a pointer
					within the buffer szLine.

	plnKeyOrVal		A pointer to a size_t that receives the length of the key or value
					returned in the parameter pszKeyOrVal. This parameter must not be NULL.

	pszEqual		If an equality string is encountered, this is a pointer to it. Otherwise
					it receives NULL. If a non-NULL address is returned, the paramter
					pszKeyOrVal points to a key. If it receives NULL, pszKeyOrVal points
					to a value.

	plnEqual		If an equals string is encountered, this is a pointer to the full length
					of the remaining string. Otherwise it receives 0.
					Note that this is *not* the length of the equality string itself, and
					that this return value differs from the one with the same name of the
					function strlineextractKeyAndValues ().

	pidxEqual1based	A pointer to a size_t that receives the 1-based index of the equality
					string found. If pszKeyOrVal points to a value, the function sets this
					value to 0.

	szLine			A pointer to the buffer that contains the "key = value" string.

	lnLine			The length of szLine. If this parameter is USE_STRLEN, the function
					obtains it with strlen (szLine).


	The following parameters have been replaced with the SCULMLTSTRINGS structure psmlt:

	nQuotes			The amount of quote strings. See parameters szOpenQuotes and
					szClosQuotes below. If this value is 0, no quotes are recognised.

	pszOpenQuotes	A pointer to an array of NUL-terminated strings recognised as opening
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszClosQuotes	A pointer to an array of NUL-terminated strings recognised as closing
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszEquals		A pointer to an array of NUL-terminated strings recognised as equality
					characters/strings. The parameter nEquals specifies the number of
					stings/elements in this array. If this parameter is NULL, the function
					fails and returns false.

	nEquals			The number of strings that are recognised as equality signs pointed
					to by the parameter pszEquals. If this parameter is 0, the function is
					bound to fail and return false, as a key/value pair cannot be identified
					without at least one accepted equality sign character or string that
					separates key and value.

*/
bool strlineextractKeyOrValue	(
		const char		**cunilog_restrict pszKeyOrVal,	size_t	*plnKeyOrVal,	// Out.
		const char		**cunilog_restrict pszEqual,	size_t	*plnEqual,		// Out.
		unsigned int	*pidxEqual1based,										// Out.
		const char		*szLine,						size_t	lnLine,			// In.
		SCULMLTSTRINGS	*psmlt													// In.
								)
;

/*
	strlineextractKeyAndValues

	Extracts a key and its values from szLine with length lnLine. If lnLine is USE_STRLEN,
	the function calls strlen (szLine) to obtain it.

	Parameters
	----------

	pszKey			A pointer that receives the start address of the key. This parameter
					cannot be NULL. This returned string is not NUL-terminated, because it
					is just a pointer within the buffer szLine.

	plnKey			A pointer to a size_t that receives the length of the key. This parameter
					must not be NULL.

	pszEquals		A pointer that receives the start address of the equality string.
					This is a pointer to the element of the equals string array that was
					found, not a pointer to within szLine. This string is NUL-terminated.

	plnEquals		A pointer that receives the length of the equality string. Note that
					this is different from the return value with the same name of the
					function strlineextractKeyOrValue ().

	pValues			A pointer to an array of SCUNILOGINIVALUE structures that receive the
					start address of the value(s) and their lengths.
					If this parameter is NULL, the function returns the amount of elements
					required to retrieve all values.
					Note that the strings of the SCUNILOGINIVALUE structures are not
					NUL-terminated, as they are only pointers to within the buffer of szLine.

	nVls			The amount of elements pValues points to. The function returns the amount
					of values found, independent of nVls.

	plnVls			A pointer to an array of size_t values that receive the length of the
					value strings. This parameter cannot be NULL.

	szLine			A pointer to the buffer that contains the "key = value" string.

	lnLine			The length of szLine. If this parameter is USE_STRLEN, the function
					obtains it with strlen (szLine).

	The following parameters have been replaced with the SCULMLTSTRINGS structure psmlt:

	nQuotes			The amount of quote strings. See parameters szOpenQuotes and
					szClosQuotes below. If this value is 0, no quotes are recognised.

	pszOpenQuotes	A pointer to an array of NUL-terminated strings recognised as opening
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszClosQuotes	A pointer to an array of NUL-terminated strings recognised as closing
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszEquals		A pointer to an array of NUL-terminated strings recognised as equality
					characters/strings. The parameter nEquals specifies the number of
					stings/elements in this array. If this parameter is NULL, the function
					fails and returns false.

	nEquals			The number of strings that are recognised as equality signs pointed
					to by the parameter pszEquals. If this parameter is 0, the function is
					bound to fail and return false, as a key/value pair cannot be identified
					without at least one accepted equality sign character or string that
					separates key and value.

	The function returns the amount of values extracted if a key and at least one value
	could be extracted from the line, which may include empty strings for the values but
	not for the key. The function returns 0 if no key/value combination could be extracted
	or if szLine is NULL or lnLine is 0.
*/
unsigned int strlineextractKeyAndValues	(
		const char		**cunilog_restrict	pszKey,		size_t	*plnKey,	// Out.
		const char		**cunilog_restrict	pszEqual,	size_t	*plnEqual,	// Out.
		SCUNILOGINIVALUE					*pValues,
		unsigned int						nValues,
		const char		*cunilog_restrict	szLine,	size_t	lnLine,			// In.
		SCULMLTSTRINGS	*psmlt												// In.
										)
;

enum en_strlineextract_white_space
{
	strlineextract_accept_white_space_and_comments,
	strlineextract_accept_leading_and_trailing_white_space,
	strlineextract_accept_leading_white_space,
	strlineextract_accept_trailing_white_space,
	strlineextract_reject_white_space
};
typedef enum en_strlineextract_white_space en_strlineextract_ws;

/*
	strlineextractSection

	Extracts the name of a section from the line szLine with length lnLine.
	If lnLine is USE_STRLEN, the function calls strlen (szLine) to obtain it.

	Parameters
	----------

	pszSec			A pointer that receives the start address of the section name. This
					parameter cannot be NULL. This returned string is not NUL-terminated,
					because it is just a pointer within the buffer szLine.

	plnSec			A pointer to a size_t that receives the length of the section name.
					This parameter must not be NULL.

	szLine			A pointer to the buffer that contains the "[section]" string.

	lnLine			The length of szLine. If this parameter is USE_STRLEN, the function
					obtains it with strlen (szLine).

	psmlt			A pointer to an SCULMLTSTRINGS structure. The following members are
					expected and used by the function:

					nSections			The amount of opening/starting and closing/exiting
										section strings. This value cannot be 0, as it
										wouldn't make sense to call the function without
										any declarations for section starts and exits.

					ccStrtSections		An array of strings that specify accepted section
										starts. The amount of strings in this array is
										specified by the member nSections.

					ccExitSections		An array of strings that secify accepted section
										ends/exits. The amount of elements in this array is
										given by the member nSections.

					Additionally, if ws is strlineextract_accept_white_space_and_comments,
					the following members are expected and used by the function:

					ccLineComments		An array of strings that serve as the start of a line
										comment.

					nLineComments		The size of the ccLineComments array.

					ccBegMultiComments	An array of strings that contain the starts of
										block comments.

					ccEndMultiComments	An array of strings the contain the ends of block
										comments.

					nMultiComments		The amounts of opening/starting and closing/ending
										block comment strings.

	ws				One of the values of the enum en_strlineextract_white_space to
					determine if and what kind of white space is accepted/permitted or
					rejected. If white space is encountered that doesn't fit this value,
					the function fails and returns false.

	pszTail			A pointer to a tail string, if any; NULL if no tail.

	plnTail			A pointer to the length of the tail, if any. The function writes 0
					to this address if there is no tail.

	The function returns true if a section name could be extracted from the line. It
	returns false, if for example a closing/exiting section string is missing.
	The function also returns false if szLine is NULL or lnLine is 0.

	If a section name is found but there's still remaining data left, the function
	returns true and sets the value pointed to by pszTail and plnTail to the remaining
	tail data and its length. This also applies to data that is rejected, for instance,
	if ws is strlineextract_reject_white_space and there's white space left, this white
	space is returned as remaining tail, and the return value of the function is true.

	If the function returns false, the output values are undefined.
*/
bool strlineextractSection	(
		const char				**cunilog_restrict pszSec,	size_t	*plnSec,
		const char				*cunilog_restrict szLine,	size_t	lnLine,
		SCULMLTSTRINGS			*psmlt,
		en_strlineextract_ws	ws,
		const char				**cunilog_restrict pszTail,	size_t	*plnTail
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
