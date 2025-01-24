/****************************************************************************************

	File:		ubfcharscountsandchecks.h
	Why:		Character counting and check routines
	OS:			C99
	Author:		Thomas
	Created:	2020-08-31
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-08-31	Thomas			Created.

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

#ifndef UBFCHARSCOUNTSANDCHECKS
#define UBFCHARSCOUNTSANDCHECKS

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

/*
	The defintion for unknown string lengths. Functions taking this value for a length
	call strlen () to obtain the correct length.
*/
#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif
#ifndef SUBF_STRING_UNKNOWN_LENGTH
#define SUBF_STRING_UNKNOWN_LENGTH			USE_STRLEN
#endif
#ifndef SUBF_STRING_LENGTH_UNKNOWN
#define SUBF_STRING_LENGTH_UNKNOWN			USE_STRLEN
#endif
#ifndef SUBF_STRING_USE_STRLEN
#define SUBF_STRING_USE_STRLEN				USE_STRLEN
#endif

EXTERN_C_BEGIN

/*
	ubf_is_printable_ASCII

	Returns true if the value of c is greater than 0x1F and lower than 0x7F.
	A character counts as printable if it is within the range from SPC (20h, 32d) to '~'
	(7Eh, 126d), in which case the function returns true.
	
	The macro/function returns false if the octet in c is outside this range.
*/
#ifdef DEBUG
	bool ubf_is_printable_ASCII (char c);
#else
	// From SPC (20h, 32d) to '~' (7Eh, 126d).
	#define ubf_is_printable_ASCII(c)					\
		((unsigned char) c > 0x1F && (unsigned char) c < 0x7F)
#endif

/*
	str_has_only_printable_ASCII

	Returns true if sz only contains printable ASCII characters.
*/
bool str_has_only_printable_ASCII (const char *sz, size_t len)
;

/*
	ubf_is_letter
	
	Returns true if the character in c is >= 'A' and <= 'Z' or >= 'a' and <= 'z',
	false otherwise. The function is identical to the standard C function isalpha (),
	which is defined as ubf_isalpha () in platform.h.
*/
#ifdef DEBUG
	bool ubf_is_letter (char c);
#else
	#define ubf_is_letter(c)	ubf_isalpha(c)
#endif

/*
	ubf_is_letter_until
	
	Returns a pointer that points after the first occurrance of c in ch, provided that all
	characters before this first occurrance are letters, determined by invokations of
	ubf_is_letter () for each character.
	
	The function returns NULL if the string in c contains anything but letters or if c
	could not be found.
*/
char *ubf_is_letter_until (char *ch, char c);

/*
	ubf_is_special
	
	Macro that evaluates to TRUE if the character c is not a letter and not a numerical
	digit. In other words, it evaluates to TRUE if the character c is a special character.
*/
#define ubf_is_special(c)								\
	(													\
			!ubf_is_letter	(c)							\
		&&	!ubf_isdigit	(c)							\
	)

/*
	isWhiteSpace

	Returns true if c is white space. CR, LF, and FF do not count as white space.
*/
#ifdef DEBUG
	bool isWhiteSpace (char c);
#else
	#define isWhiteSpace(c)								\
		(			UBF_SPC			== (c)				\
				||	UBF_TAB			== (c)				\
				||	UBF_VT			== (c)				\
		)
#endif

/*
	isDirectorySeparator
	isDirSep

	Evaluates to true if c is a directory separator, which can be either a forward
	or a backward slash.
*/
#ifdef DEBUG
	bool isDirectorySeparator (char c);
#else
	#define isDirectorySeparator(c)						\
		('/' == (c) || '\\' == (c))
#endif
#define isDirSep(c)			isDirectorySeparator (c)

/*
	isWrongDirectorySeparator
	isWrongDirSep
	
	Evaluates to true if c is the wrong directory separator. The wrong directory separator
	on Windows systems is the forward slash ("/"), on POSIX systems the backslash ("\").
*/
#ifdef DEBUG
	bool isWrongDirectorySeparator (char c);
#else
	#define isWrongDirectorySeparator(c)				\
		(UBF_WRONG_DIR_SEP == c)
#endif
#define isWrongDirSep(c)	isWrongDirectorySeparator (c)

/*
	ubf_count_numerical_digits
	
	Returns the amount of numerical digits (between '0' and '9') within the character string
	cc points to. The string cc points to is required to be NUL-terminated.
*/
size_t ubf_count_numerical_digits (const char *cc);

/*
	ubf_count_starts_with_numerical_digits_up_to
	
	Returns the amount of numerical digits (between '0' and '9') the character string
	cc points starts with, up to len characters/octets.
*/
size_t ubf_count_starts_with_numerical_digits_up_to (const char *cc, size_t len);

/*
	ubf_count_special_characters
	
	Returns the amount of special characters in the string cc points to. Special characters
	for this function are characters that are neither upper or lower case letters nor numerical
	digits.
*/
size_t ubf_count_special_characters (const char *cc);

/*
	ubf_count_char

	Counts how many times c occurs in cc and returns this number.
*/
size_t ubf_count_char (const char *cc, char c);

/*
	ubf_obtain_strlen
	STRLENSZ

	Returns the length of the NUL-terminated or non-NUL-terminated string sz.

	- If sz is NULL, the function returns 0.
	- If providedLength is (size_t) -1, the function returns strlen (sz). This requires sz to
		be NUL-terminated.
	- For any other value of providedLength, the function or macro returns providedLength.
		This should be the length of sz without the NUL-terminator, as would be obtained
		via strlen (sz) if sz was NUL-terminated.
*/
#ifdef DEBUG
	size_t ubf_obtain_strlen (const char *sz, size_t providedLength);
#else
	#define ubf_obtain_strlen(sz, len)					\
		(sz) ? (USE_STRLEN == (len) ? strlen (sz) : (len)) : 0
#endif
#define STRLENSZ(s, l)	ubf_obtain_strlen (s, l)

EXTERN_C_END

#endif															// Of UBFCHARSCOUNTSANDCHECKS.
