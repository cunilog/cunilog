/****************************************************************************************

	File:		strnewline.h
	Why:		New line functions.
	OS:			C99
	Author:		Thomas
	Created:	2022-04-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-04-11	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This module supports the following build options:


	CUNILOG_NEWLINE_POSIX_ONLY
	
	Only POSIX line endings (LF) are supported. The enumeration values for other line endings
	are removed by the preprocessor.


	CUNILOG_NEWLINE_WINDOWS_ONLY

	Only Windows (CRLF) line endings are supported. The enumeration values for other line
	endings are removed by the preprocessor.


	CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY

	Only POSIX (LF) and Windows (CRLF) line endings are supported. The enumeration values
	for other line endings are removed by the preprocessor. Since June 2025, this is the
	default and does not need to be defined anymore.


	CUNILOG_NEWLINE_EXTENDED

	All line endings supported are recognised. Overrides all other line ending definitions.
	When CUNILOG_NEWLINE_EXTENDED is defined, three more definitions are implicitely defined
	as well to allow for conditional builds:
	CUNILOG_NEWLINE_POSIX, CUNILOG_NEWLINE_WINDOWS, and CUNILOG_NEWLINE_POSIX_AND_WINDOWS

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

// Used for testing the definitions.
//#define CUNILOG_NEWLINE_WINDOWS_ONLY

#ifndef STRNEWLINE_H
#define STRNEWLINE_H

// For quick checks.
//#define CUNILOG_NEWLINE_EXTENDED

/*
	Correct the definitions. This also sets priorities and overrides of the definitions.
*/
#if !defined (CUNILOG_NEWLINE_POSIX_ONLY) && !defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#endif
#endif
#if defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	#ifdef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#endif
	#ifdef CUNILOG_NEWLINE_WINDOWS_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX
	#define CUNILOG_NEWLINE_POSIX
	#endif
	#ifndef CUNILOG_NEWLINE_WINDOWS
	#define CUNILOG_NEWLINE_WINDOWS
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#endif
#endif
#if defined (CUNILOG_NEWLINE_POSIX_ONLY) && defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#endif
#endif
#ifdef CUNILOG_NEWLINE_EXTENDED
	#ifdef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#endif
	#ifdef CUNILOG_NEWLINE_WINDOWS_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#endif
	#ifdef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#undef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX
	#define CUNILOG_NEWLINE_POSIX
	#endif
	#ifndef CUNILOG_NEWLINE_WINDOWS
	#define CUNILOG_NEWLINE_WINDOWS
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#endif
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

/*
	The maximum length of a line ending in this module, and its size including NUL.
*/
#ifndef MAX_LEN_LINE_ENDING
#define MAX_LEN_LINE_ENDING				(3)
#endif
#ifndef MAX_SIZ_LINE_ENDING
#define MAX_SIZ_LINE_ENDING				(1 + MAX_LEN_LINE_ENDING)
#endif

EXTERN_C_BEGIN

/*
	newline_t

	Represents a new line.

	Recommended is unilogNewLineDefault.

	The value cunilogNewLineSystem uses the operating system/platform default, which is
	currently cunilogNewLineWindows (CRLF) in Windows and cunilogNewLinePOSIX (LF) for every
	other platform.

	The value cunilogNewLineDefault used to be cunilogNewLineSystem to ensure logfiles
	could be opened with Notepad on Windows systems, but since newer versions of Notepad
	(Windows 10 and newer) can perfectly display files that have POSIX line endings, the
	default is now cunilogNewLinePOSIX to save one octet per event line. Use
	cunilogNewLineWindows or cunilogNewLineSystem if textual logfiles need to be opened/
	viewed with Notepad for Windows versions before Windows 10, or if they are opened/
	viewed/processed later with any other application that can't cope with POSIX line
	endings.
*/
#if defined (CUNILOG_NEWLINE_POSIX_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX		= cunilogNewLineSystem	// LF only.
		,	cunilogNewLineDefault	= cunilogNewLinePOSIX
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLineWindows	= cunilogNewLineSystem	// CR + LF.
		,	cunilogNewLineDefault	= cunilogNewLineWindows
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		,	cunilogNewLineWindows							// CR + LF.
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#else
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		,	cunilogNewLineWindows							// CR + LF.
		,	cunilogNewLineApple								// CR only.
		,	cunilogNewLineRISCOS							// LF + CR.
		,	cunilogNewLineQNXbef4							// RS (1Eh)
		,	cunilogNewLineIBMzOS							// EBCDIC NL (15h)
		,	cunilogNewLineNEL								// Unicode newline NEL (U+0085)
		,	cunilogNewLineLS								// Unicode line separator LS (U+2028)
		,	cunilogNewLinePS								// Unicode paragraph separator PS
															//	(U+2029)
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#endif
typedef enum enLineEndings	newline_t;

/*
	The array with the line endings and the array with their lengths.
*/
const char	*aszLineEndings	[];
size_t		lenLineEndings	[];

/*
	ccLineEnding

	Returns the line ending for nl. Note that szLineEnding () also returns
	its length.
*/
#ifdef DEBUG
	const char *ccLineEnding (newline_t nl);
#else
	#define ccLineEnding(nl)	aszLineEndings [nl]
#endif

/*
	lnLineEnding

	Returns the length of the line ending nl. The value does not include the NUL
	terminator.
*/
#ifdef DEBUG
	size_t lnLineEnding (newline_t nl);
#else
	#define lnLineEnding(nl)	lenLineEndings [nl]
#endif

/*
	szLineEnding

	Returns the line ending and its length. The length does not include the NUL
	terminator.
*/
const char *szLineEnding (newline_t nl, size_t *pln);

/*
	strIsNewLine

	Since 2024-11-29 this function is considered deprecated. Use strIsLineEndings () instead.
	Note that strIsLineEndings () returns a size_t instead of an unsigned int.

	Since 2025-06-25 this function is not built anymore by default. It is instead a wrapper
	macro for strIsLineEndings (). Define STRNEWLINE_FORCE_ORG_STRISNEWLINE to build and use
	this function instead of strIsLineEndings ().

	Checks if ch points to one or more newline markers. The function returns the amount of
	new lines found, 0 if ch does not point to a new line marker.

	See https://en.wikipedia.org/wiki/Newline .
	
	For our implementation, a new line is found when:
		<CR>		(0x0D)
		<CR><LF>	(0x0D)(0x0A)
		<LF>		(0x0A)
		This counts as two new lines (a single CR and a single LF):
		<LF><CR>	(0x0A)(0x0D)

	Parameters:
	ch					A pointer to the character string to be checked.
						Since stJump stores the amount of bytes that make up the
						newline marker, if the caller increments ch by stJump the
						new value of ch points to the first byte after the newline
						marker.
	stLen				Length of the character string in octets, not including
						a terminating NUL character.  If this parameter is (size_t) -1,
						the function obtains the length with a call to strlen (ch).
	stJump				A pointer to the amount of octets in the new line phrase
						returned by the function. The caller can for instance use
						this information to increment the pointer to the character
						string in order to jump over the new line marker. If
						stJump is NULL, this parameter is ignored.
						Possible return values:
						stJump = 0			The found byte is not part of a newline
											marker.
						stJump = 1			A single <CR> (carriage return) was found
											or a single <LF> was found.
						stJump = 2			A <CR><LF> pair was found.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.
*/
#ifdef STRNEWLINE_FORCE_ORG_STRISNEWLINE
	unsigned int strIsNewLine (char *ch, size_t stLen, size_t *stJump);
#else
	#define strIsNewLine(sz, ln, pj)					\
		(unsigned int) strIsLineEndings (sz, ln, pj)
#endif

/*
	strIsLineEndings

	Checks if ch points to one or more newline markers/line endings. The function returns
	the amount of consecutive line endings encountered, or 0 if ch does not point to at
	least one.

	The function is similar to strIsNewLine () but treats all possible line endings
	of the enum enLineEndings as line endings, and counts them accordingly.

	Parameters:
	ch					A pointer to the character string to be checked.
						Since stJump stores the amount of octets that make up the
						newline marker(s), if the caller increments ch by stJump the
						new value of ch points to the first byte after the encountered
						line endings.
	stLen				Length of the character string in octets, not including
						a terminating NUL character.  If this parameter is (size_t) -1,
						the function obtains the length with a call to strlen (ch).
	stJump				A pointer to the amount of octets of consecutive line endings
						returned by the function. The caller can for instance use
						this information to increment the pointer to the character
						string in order to jump over new line markers.
						If not required, this parameter can be NULL.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.

	Note that the current implementation of this function does not recognise RiscOS
	line endings (LF + CR) correctly, as it finds a POSIX line ending (LF only) first,
	and then an Apple line ending (CR only), and therefore identifies two consecutive
	line endings instead of a single RiscOS line ending. If/when an implementation of
	this function is required that identifies RiscOS line endings correctly, it will
	have to be updated/implemented first.
*/
size_t strIsLineEndings (const char *ch, size_t stLen, size_t *stJump)
;

/*
	strFirstLineEnding

	Finds and returns a pointer to the first line ending in the buffer ch points to,
	or returns NULL if no line ending could be found.

	The function reads up to len octets/bytes from ch. If len is USE_STRLEN, the function
	calls strlen (ch) to obtain it. The parameter ch can be NULL if len is 0.
*/
char *strFirstLineEnding (const char *ch, size_t len);

/*
	strFirstLineEnding_l

	The function is identical to strFirstLineEnding () but additionally returns the length
	of the line ending encountered. The parameter plLE can be NULL, in which case the
	length of the line ending is not returned. if no line ending is found, the size_t
	plLE points to is not touched.

	If len is USE_STRLEN, the function calls strlen (ch) to obtain it.
	The parameter ch can be NULL if len is 0.

	If no line ending is found, the function returns NULL.
*/
char *strFirstLineEnding_l (const char *ch, size_t len, size_t *plLE);

/*
	strPrevLineEnding_l

	The function is identical to strFirstLineEnding_l () but searches for the first line
	ending before ch + strtIdx, i.e. the previous line ending. The length of the found line
	ending is returned at the address plLE points to, unless plLE is NULL.

	If len is USE_STRLEN, the function calls strlen (ch) to obtain it.
	The parameter len or, if USE_STRLEN, the obtained length, must be greater or equal to
	strtIdx. The function searches backwards (towards the first character in ch) from
	ch + strtIdx down to ch for the line ending.

	The parameter ch can be NULL if len is 0.

	If no line ending is found, the function returns NULL. If strtIdx >= len, the function
	returns NULL. When the function returns NULL, the address plLE points to is set to 0.
*/
char *strPrevLineEnding_l (const char *ch, size_t len, size_t strtIdx, size_t *plLE);

/*
	strRemoveLineEndingsFromEnd

	Removes line endings from the right side of sz.
	
	The string parameter cannot be NULL but the function does not check this.

	The parameter len specifies the length of sz. The string does not have to be
	NUL-terminated.

	If len is USE_STRLEN, the function calls strlen () on sz. Note that sz must be
	NUL-terminated in this case.

	The function returns the new length of sz, which excludes the found line endings.
*/
size_t strRemoveLineEndingsFromEnd (const char *sz, size_t len);


#ifdef DEBUG
	#ifndef STRNEWLINE_BUILD_TEST
	#define STRNEWLINE_BUILD_TEST
	#endif
#endif

/*
	Test function.
*/
#ifdef STRNEWLINE_BUILD_TEST
	bool test_strnewline (void);
#else
	#define test_strnewline()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRNEWLINE_H.
