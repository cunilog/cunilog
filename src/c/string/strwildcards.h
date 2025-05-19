/****************************************************************************************

	File:		strwildcards.h
	Why:		Wildcard functions
	OS:			C99.
	Author:		Thomas
	Created:	2022-03-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-21	Thomas			Created.

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

#ifndef STRWILDCARDS_H
#define STRWILDCARDS_H

#include <stdbool.h>
#include <inttypes.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./restrict.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/restrict.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

/*
	Test function in debug versions only (default).
*/
#ifdef DEBUG
	#ifndef STRWILDCARDS_BUILD_TEST_FNCT
	//#define STRWILDCARDS_BUILD_TEST_FNCT
	#endif
#endif

EXTERN_C_BEGIN

/*
	wildCardFileName
	
	Obtains the last part of a path if it contains wildcard characters.
	
	The function returns the filename, preceeded by a directory separator, of a path that
	contains wildcard characters and optionally, with parameter plen, its length. If no
	wildcard filename can be found, the function returns NULL. If the function returns
	NULL, and plen is not NULL, the address plen points to is set to 0.
	
	Examples:
	
	ccPath					returns		plen
	"C:\*.*"				"\*.*"		4
	"C:\test\*.tx?"			"\*.tx?"	6
*/
const char *wildCardFileName (size_t *plen, const char *ccPath)
;

/*
	lenPathWithoutWildcardFileName
	
	Returns the length of the path that ends with a wildcard filename, including the
	directory separator.
	
	ccPath					returns
	"C:\*.*"				3
	"C:\test\*.tx?"			8
	"C:*.*"					2
	"C:\test"				7			There are no wildcards.
*/
size_t lenPathWithoutWildcardFileName (const char *ccPath)
;

/*
	matchWildcardPattern
	matchWildcardPatternW

	Note that the function has been renamed from globMatch () to matchWildcardPattern ().

	The function matchWildcardPattern () expects UTF-8 strings while the function
	matchWildcardPatternW () is its wide string version. The length parameters for
	matchWildcardPatternW () are in UTF-16 characters, not octets/bytes. Whenever
	this comment block mentions "octet" or "octets", for matchWildcardPatternW () this
	means "UTF-16 16 bit word" or "UTF-16 16 bit words".

	The function compares ccStri with length lnStri against the glob pattern (a string
	that can contain wildcard characters) ccGlob with length lnGlob. It is not a replacement
	for fnmatch () (https://www.man7.org/linux/man-pages/man3/fnmatch.3.html) and does
	not support any type of regular expression. It is a simple helper function that filters
	for a file mask when enumerating the contents of a directory.

	The string parameter ccStri is not meant to contain wildcard characters. The string
	parameter ccGlob can contain wildard characters.

	The length arguments lnStri and lnGlob can have the value USE_STRLEN, which is (size_t)
	-1, in which case the length in question is obtained via a call to strlen (). For
	matchWildcardPatternW (), the length is obtained via a call to wcslen ().

	Both, ccStri and ccGlob, can contain NUL characters if lnStri and lnGlob are provided,
	i.e. are not USE_STRLEN.

	Unless a length is USE_STRLEN, the function does not read from the buffers beyond their
	length parameters. This means that if a length value is 0 nothing will ever be read from
	the string buffer. In the examples below the buffer in these cases is shown as "" but
	could as well be NULL or any other arbitrary value.

	The buffers ccStri and ccGlob must not point to the same memory location and must not
	overlap.

	The function returns true if ccStri matches the pattern ccGlob points to, false if not.

	If both lengths are 0, the function treats this as a match and returns true. If lnStri
	is 0 but lnGlob is not, the function in this case assumes that a match is impossible and
	returns false. If lnGlob is 0, this is treated as a match against anything, and the
	function returns true independent of the value of lnStri or the contents of ccStri.

	Match rules for the glob pattern ccGlob:
	- The comparison is case-sensitive. "A" does not match "a" and vice versa.
	- A single question mark ("?") matches a single octet in ccStri including path
		separators ("/" or "\").
	- An asterisk ("*") matches zero or more octets but not path separators ("/" or "\").
	- Two or more asterisks ("**", "***", "****", etc.) match zero or more octets including
		path separators ("/" or "\").
	- The path separators (forward and backward, "/" and "\") are treated as equal and
		therefore match each other.
	- A question mark ("?") after two or more asterisks ("**", "***", "****", etc.) never
		matches, because the asterisks will have consumed the string entirely. To match
		a minimum amount of characters, place the question mark(s) first. For instance,
		use "?**123" to match "0123" but not "123".
	
	ccStri		lnStri		ccGlob		lnGlob			return
	""			0			""			0				true
	"a"			1			""			0				true
	"a"			1			"a"			1				true
	"a/b/c"		5			"a\*"		3				false				See (1) below.
	"a\b\c"		5			"a\*\*"		5				true				See (1) below.
	"/"			1			"\"			1				true				See (1) below.
	"/home/usr" USE_STRLEN	"\*?usr"	6				true				See (1) below.
	"1/2/3"		5			"1?2?3"		5				true				See (2) below.
	"/1"		2			"?**"		3				true				See (3) below.

	Some explanations/help:
	In the above examples, strings are not C literals as backslashes are not escaped.
	(1) The function treats forward slashes and backslashes as being identical characters.
	(2) A question mark also matches a path separator.
	(3) Since two or more asterisks followed by a question mark never match, place the
		question mark first to match a minimum of a single character: "?**"

	See function strwildcards_test_function () for a more complete list of expectations.
*/
bool matchWildcardPattern	(
		const char		*cunilog_restrict ccStri,	size_t lnStri,
		const char		*cunilog_restrict ccGlob,	size_t lnGlob
							)
;
bool matchWildcardPatternW	(
		const wchar_t	*cunilog_restrict ccStri,	size_t lnStri,
		const wchar_t	*cunilog_restrict ccGlob,	size_t lnGlob
							)
;

/*
	strwildcards_test_function

	Test function for the module.
*/
#ifdef STRWILDCARDS_BUILD_TEST_FNCT
	bool strwildcards_test_function (void);
#else
	#define strwildcards_test_function() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRWILDCARDS_H.
