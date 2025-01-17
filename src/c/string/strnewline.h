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
	This module supports the following build options:


	CUNILOG_NEWLINE_POSIX_ONLY
	
	Only POSIX line endings (LF) are supported. The enumeration values for other line endings
	are removed by the preprocessor.


	CUNILOG_NEWLINE_WINDOWS_ONLY

	Only Windows (CRLF) line endings are supported. The enumeration values for other line
	endings are removed by the preprocessor.


	CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY

	Only POSIX (LF) and Windows (CRLF) line endings are supported. The enumeration values
	for other line endings are removed by the preprocessor.
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

/*
	Correct the definitions. This also sets priorities and overrides of the definitions.
*/
#if defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
#endif
#if defined (CUNILOG_NEWLINE_POSIX_ONLY) && defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
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

EXTERN_C_BEGIN

/*
	strIsNewLine

	Checks if ch points to one or more newline markers. The function returns the amount of
	new lines found, 0 if ch does not point to a new line marker.

	Since 2024-11-29 this function is considered deprecated. Use strIsLineEndings () instead.
	The function might be made obsolete in the future.

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
unsigned int strIsNewLine (char *ch, size_t stLen, size_t *stJump);

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
						Possible return values:
						stJump = 0			The found byte is not part of a newline
											marker.
						stJump = 1			A single <CR> (carriage return) was found
											or a single <LF> was found.
						stJump = 2			A <CR><LF> pair was found.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.
*/
size_t strIsLineEndings (char *ch, size_t stLen, size_t *stJump)
;

/*
	newline_t

	Represents a new line.

	Recommended is unilogNewLineDefault.

	The value cunilogNewLineSystem uses the operating system/platform default, which is
	currently cunilogNewLineWindows (CRLF) in Windows and cunilogNewLinePOSIX (LF) for every
	other system.

	The value cunilogNewLineDefault used to be cunilogNewLineSystem to ensure logfiles
	could be opened with Notepad on Windows systems but since newer versions of Notepad
	(Windows 10 and newer) can perfectly display files that have POSIX line endings, the
	default is now cunilogNewLinePOSIX to save one octet per event line. Use
	cunilogNewLineWindows or cunilogNewLineSystem if textual logfiles need to be opened/
	viewed with Notepad for Windows versions before Windows 10.
*/
#if defined (CUNILOG_NEWLINE_POSIX_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLineWindows							// CR + LF.
		,	cunilogNewLineDefault = cunilogNewLineWindows
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
		,	cunilogNewLinePS								// Unicode paragraph separator PS (U+2029)
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#endif
typedef enum enLineEndings	newline_t;

/*
	ccLineEnding

	Returns the line ending for nl. Note that szLineEnding () also returns
	its length.
*/
const char *ccLineEnding (newline_t nl);

/*
	lnLineEnding

	Returns the length of the line ending nl. The value does not include the NUL
	terminator.
*/
size_t lnLineEnding (newline_t nl);

/*
	szLineEnding

	Returns the line ending and its length. The length does not include the NUL
	terminator.
*/
const char *szLineEnding (newline_t, size_t *pln)
;

/*
	lnLineEnding

	Returns the length of the string that represents the line ending nl.
	The returned value is the length of the string excluding a NUL terminator.
*/
size_t lnLineEnding (newline_t nl);

#ifdef DEBUG
	#ifndef STRNEWLINE_BUILD_TEST
	#define STRNEWLINE_BUILD_TEST
	#endif
#endif

/*
	Test function.
*/
#ifdef STRNEWLINE_BUILD_TEST
	void test_strnewline (void);
#else
	#define test_strnewline()
#endif

EXTERN_C_END

#endif														// Of #ifndef STRNEWLINE_H.
