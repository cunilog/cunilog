/****************************************************************************************

	File:		strintuint.h
	Why:		Conversion functions between character strings and integers.
	OS:			C99.
	Author:		Thomas
	Created:	2019-08-28
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-08-28	Thomas			Created.

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


	The functions ubf_itoa (), ubf_n_itoa10 (), ubf_str_from_uint16 (), ubf_str_from_int64 (),
	and ubf_str_from_uint64 () are (c) Lukas Chmela and derived from the versions at
	http://www.strudel.org.uk/itoa/ :

	* C++ version 0.4 char* style "itoa":
	* Written by Lukas Chmela
	* Released under GPLv3.

*/

#ifndef U_STR_INT_UINT_INCLUDED
#define U_STR_INT_UINT_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../pre/platform.h"
	#endif
#endif

// Maximum lengths of unsigned and signed integer values in ASCII representation.
//	The definitions that end with _LEN specify the length excluding NUL, the ones
//	that end with _SIZE include the NUL terminator.
#ifndef UBF_INT8_LEN
#define UBF_INT8_LEN					(4)						// "-128"
// "1234" = 4.
#endif
#ifndef UBF_INT8_SIZE
#define UBF_INT8_SIZE					(4 + 1)					// "-128"
// "1234" = 4.
#endif
#ifndef UBF_INT16_LEN
#define UBF_INT16_LEN					(6)						// "-32768" = 6.
#endif
#ifndef UBF_INT16_SIZE
#define UBF_INT16_SIZE					(6 + 1)					// "-32768" = 6.
#endif
#ifndef UBF_INT32_LEN
#define UBF_INT32_LEN					(11)					// "-4294967296" = 11.
#endif
#ifndef UBF_INT32_SIZE
#define UBF_INT32_SIZE					(11 + 1)				// "-4294967296" = 11.
#endif
#ifndef UBF_INT64_LEN
#define UBF_INT64_LEN					(21)					// "+18446744073709551615".
// "+12345678901234567890" = 21.
#endif
#ifndef UBF_INT64_SIZE
#define UBF_INT64_SIZE					(21 + 1)				// "+18446744073709551615".
// "+12345678901234567890" = 21.
#endif
#ifndef UBF_UINT8_LEN
#define UBF_UINT8_LEN					(3)						// "255".
// "123" = 3.
#endif
#ifndef UBF_UINT8_SIZE
#define UBF_UINT8_SIZE					(3 + 1)					// "255".
// "123" = 3.
#endif
#ifndef UBF_UINT16_LEN
#define UBF_UINT16_LEN					(5)						// "65535".
// "12345" = 5.
#endif
#ifndef UBF_UINT16_SIZE
#define UBF_UINT16_SIZE					(5 + 1)					// "65535".
// "12345" = 5.
#endif
#ifndef UBF_UINT32_LEN
#define UBF_UINT32_LEN					(10)					// "4294967296";
// "1234567890" = 10.
#endif
#ifndef UBF_UINT32_SIZE
#define UBF_UINT32_SIZE					(10 + 1)				// "4294967296";
// "1234567890" = 10.
#endif
#ifndef UBF_UINT64_LEN
#define UBF_UINT64_LEN					(20)					// "18446744073709551615".
// "12345678901234567890" = 20.
#endif
#ifndef UBF_UINT64_SIZE
#define UBF_UINT64_SIZE					(20 + 1)				// "18446744073709551615".
// "12345678901234567890" = 20.
#endif

#ifndef ASCII_NUL
#define ASCII_NUL			'\0'
#endif

// Fall through comment used in switch () statements. See
//	https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wimplicit-fallthrough .
#if defined(_MSC_VER)
#ifndef UBF_FALLTHROUGH_HINT
#define UBF_FALLTHROUGH_HINT		/* FALLTHRU */
#endif
#else
#ifndef UBF_FALLTHROUGH_HINT
#define UBF_FALLTHROUGH_HINT						\
			__attribute__((fallthrough));
#endif
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef HAVE_C_ITO_ALPHABET
	#define HAVE_C_ITO_ALPHABET
	#define UBUILD_C_ITO_ALPHABET_IN_HERE
	extern char	c_ito_alphabet [];
#endif

/*
	Our version of itoa (). Taken from http://www.strudel.org.uk/itoa/ .
	It seems to be a very fast version.
*/
char *ubf_itoa (int value, char *result, int base);

/*
	ubf_n_itoa10

	This is an itoa () function that returns the amount of bytes written to result and
	uses a base of 10.
*/
size_t ubf_n_itoa10 (int value, char *result);

/*
	ubf_str0_from_59max

	Copies the resulting ASCII representation of the value ui59m, which can have values
	between 0 and 59, to the buffer result points to. This buffer must therefore have a
	size of at least two octets/bytes.

	The actual range of ui59m can be from 0 to 61, and the lookup table is big enough.
	See https://en.cppreference.com/w/c/chrono/tm for more details.
	"Range allows for a positive leap second. Two leap seconds in the same minute are
	not allowed (the C89 range 0..61 was a defect)."
	The lookup table holds 62 values (0 to 61) to avoid issues with C89 compilers.

	The function does not add a NUL-terminator to result, nor does it return a value.
	It always writes exactly two bytes to result. For example, if ui59m is 26, the
	function writes the non-NUL-terminated string "26" to result.
	The caller is responsible for ensuring that the function is not called with any
	values of ui59m greater than 59.

	The function's purpose is to return ASCII representations of minutes, seconds,
	months, hours, days in a month, week numbers, or any unsigned integer of up to 59 very
	quickly through an indexed table.

	If the returned string is required to be NUL-terminated, use ubf_str0_from_59max_n ()
	instead.

*/
#ifdef DEBUG
	void ubf_str0_from_59max (char *result, uint8_t ui59m);
#else
	extern char c_0_to_59_str0 [62][2];
	#define ubf_str0_from_59max(r,u)	memcpy (r, c_0_to_59_str0 [u], 2)
#endif

/*
	ubf_str0_from_59max_n

	The function or macro is identical to ubf_str0_from_59max () but does add a NUL-
	terminator.

	Copies the resulting ASCII representation of the value ui59m, which can have values
	between 0 and 59, to the buffer result points to. This buffer must therefore have a
	size of at least three octets/bytes since the function adds a NUL-terminator to result.

	The function's purpose is to return ASCII representations of minutes, seconds,
	months, hours, days in a month, week numbers, or any unsigned integer of up to 59 very
	quickly through a lookup table.
*/
#ifdef DEBUG
	void ubf_str0_from_59max_n (char *result, uint8_t ui59m);
#else
	#define ubf_str0_from_59max_n(r,u)					\
		memcpy (r, c_0_to_59_str0 [u], 2);				\
		r [2] = '\0'
#endif

/*
	ubf_str_from_uint8
	
	Returns an ASCII representation of the value of ui8, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT8_SIZE octets long.

	The function returns the amount of decimal digits written to result, not
	counting the terminating NUL character.
*/
size_t ubf_str_from_uint8 (char *result, uint8_t ui8);

/*
	ubf_str_from_uint16
	
	Returns an ASCII representation of the value of ui16, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT16_SIZE bytes long.

	The function returns the amount of decimal digits written to result, which
	does not include the terminating NUL character.
*/
size_t ubf_str_from_uint16 (char *result, uint16_t ui16);

/*
	ubf_str0_from_uint16

	Returns an ASCII representation with leading zeroes of the value of ui16,
	in decimal (base 10). The buffer result points to must be at least digits + 1
	octets/bytes long.

	The parameter dgts cannot be 0.

	The function is identical to ubf_str_from_uint16 but writes leading zeroes to
	the buffer result points to. The parameter digits specifies the total amount
	of digits for the result, which should be any value between 1 and UBF_UINT16_LEN,
	which is 5. Values for digits greater than UBF_UINT16_LEN always produce leading
	zeroes only for the range between UBF_UINT16_LEN + 1 and digits because the
	value of ui16 can never become big enough to fill this area with any other
	number.

	The function returns the amount of digits written to result, not counting
	leading zeros, and also not counting a terminating NUL, or STR0_NOT_ENOUGH_DIGITS
	if the value of ui16 cannot be represented in the specified amount of digits.
	
	If the value of digits is not big enough to hold the ASCII
	representation of the value ui16, the function fills result up to digits
	numerical digits from the right and returns (size_t) -1, which is defined as
	STR0_NOT_ENOUGH_DIGITS.
	
	Note that the buffer result points to must be at least one octet larger
	than digits to hold a terminating NUL character. It is recommended to use a
	buffer size of UBF_UINT16_SIZE, which is UBF_UINT16_LEN + 1 for the NUL
	character.
*/
size_t ubf_str0_from_uint16 (char *result, size_t digits, uint16_t ui16);

/*
	ubf_str_from_int64

	Returns an ASCII representation of the value of i64, in decimal (base 10). The
	buffer result points to must be at least UBF_INT64_LEN bytes long.

	The function returns the amount of characters written to result, not counting
	the terminating NUL character.
*/
size_t ubf_str_from_int64 (char *result, int64_t i64);

/*
	ubf_str_to_int64

	Obtains a signed 64 bit integer of the ASCII string chStr in the address pi points
	to. The function stops at the first character that is not a numerical digit. However,
	chStr may start with an ASCII '+' or an ASCII '-' character. If pi is not NULL, the
	result of the conversion is returned at the memory location pi points to. For a
	function that is more picky and returns an error if chStr contains non-numerical
	characters, see ubf_int64_from_str ().

	The function returns the amount of characters used up for the conversion.
*/
size_t ubf_str_to_int64 (const char *chStr, int64_t *pi);

/*
	ubf_std_int64_from_str
	
	Wrapper macro for ubf_str_to_int64 () that reverses the order of its parameters
	and provides an API that is more standardised.
*/
#define ubf_std_int64_from_str(pi, pS)					\
	ubf_str_to_int64 (pS, pi)

/*
	ubf_str_from_uint64

	Returns an ASCII representation of the value of ui64, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT64_SIZE bytes long, which is
	UBF_UINT64_LEN + 1, or 21.

	The function returns the amount of digits written to result, not counting the
	terminating NUL character.
*/
size_t ubf_str_from_uint64 (char *result, uint64_t ui64);

#ifndef STR0_NOT_ENOUGH_DIGITS
#define STR0_NOT_ENOUGH_DIGITS	((size_t) -1)
#endif

/*
	ubf_str0_from_uint64

	Returns an ASCII representation with leading zeroes of the value of ui64,
	in decimal (base 10). The buffer result points to must be at least digits + 1
	octets/bytes long.

	The parameter dgts cannot be 0.

	The function is identical to ubf_str_from_uint64 but writes leading zeroes to
	the buffer result points to. The parameter digits specifies the total amount
	of digits for the result, which should be any value between 1 and UBF_UINT64_LEN,
	which is 20. Values for dgts greater than UBF_UINT64_LEN always produce leading
	zeroes only for the range between UBF_UINT64_LEN + 1 and digits because the
	value of ui64 can never become big enough to fill this area with any other
	number.

	The function returns the amount of digits written to result, not counting
	leading zeros, and also not counting a terminating NUL, or STR0_NOT_ENOUGH_DIGITS
	if the value of ui64 cannot be represented in the specified amount of digits.
	
	If the value of digits is not big enough to hold the ASCII
	representation of the value ui64, the function fills result up to digits
	numerical digits from the right and returns (size_t) -1, which is defined as
	STR0_NOT_ENOUGH_DIGITS.
	
	Note that the buffer result points to must be at least one octet larger
	than digits to hold a terminating NUL character. It is recommended to use a
	buffer size of UBF_UINT64_SIZE, which is UBF_UINT64_LEN + 1 for the NUL
	character.
*/
size_t ubf_str0_from_uint64 (char *result, size_t digits, uint64_t ui64);

/*
	ubf_uint64_from_str

	Obtains an unsigned 64 bit integer of the ASCII string chStr in ui. The conversion
	stops at the first white space or any character that is not a valid decimal digit.
	Additionally, the string chStr may start with an ASCII '+' character. If ui is not
	NULL, the result of the conversion is returned at the memory location ui points to.
	If ui is NULL, the result of the conversion is not stored but all checks are
	performed and the result value indicates success or failure. If chStr is NULL the
	function treats it as an emptry string, with the result of the conversion being 0.
	If chStr starts with an ASCII '-' or any other non-numeric character the function
	treats it as an empty string/number, which means 0 is returned.

	The function returns TRUE if the conversion was successful, FALSE otherwise. The
	conversion fails if chStr contains a number that is greater than UINT64_MAX.
	
	If the amount of characters consumed by the function is required, or if the
	amount of characters to be processed needs to be restricted, use
	ubf_uint64_from_str_n () instead.
*/
bool ubf_uint64_from_str (uint64_t *ui, const char *chStr);

/*
	ubf_uint64_from_str_n
	
	The function is similar to ubf_uint64_from_str () but only processes chStr
	up to nLen bytes/characters and returns the amount of characters consumed
	and used up for the value stored in ui by the function. The returned value
	includes an optional preceeding '+' if the parameter s is enUintFromStrAllowPlus.
	
	If nLen should not be used, pass (size_t) -1 to the function. The function
	then stops when the NUL terminator is encountered.
	
	The function returns the amount of octets consumed from chStr.
*/
enum enUintFromStrN
{
	enUintFromStrDontAllowPlus,									// No '+' allowed.
	enUintFromStrAllowPlus										// Allow preceding '+'.
};
size_t ubf_uint64_from_str_n (uint64_t *ui, const char *chStr, size_t nLen, enum enUintFromStrN s);

/*
	ubf_std_uint64_from_str
	
	Wrapper macro for ubf_uint64_from_str_n () that provides an API that is more
	standardised.
*/
#define ubf_std_uint64_from_str(pui, pStr)				\
	ubf_uint64_from_str_n (pui, pStr, (size_t) -1,		\
			enUintFromStrAllowPlus)
	
/*
	ubf_int64_from_str

	Obtains a signed 64 bit integer of the ASCII string chStr in the address pi points
	to. All possible checks are performed. The string in chStr must not contain white
	space or any character that is not a valid decimal digit. However, chStr may start
	with an ASCII '+' or an ASCII '-' character. If pi is not NULL, the result of the
	conversion is returned at the memory location pi points to. If pi is NULL, the result
	of the conversion is not stored but all checks are performed and the result value
	indicates success or failure. If chStr is NULL the function treats it as an emptry
	string, with the result of the conversion being 0. For a function that stops at the
	first non-numerical digit, see ubf_str_to_int64 ().

	The function returns TRUE if the conversion was successful, FALSE otherwise. The
	conversion fails if chStr contains a number that is greater than INT64_MAX or
	smaller than INT64_MIN. It also fails if chStr contains any character that is not a
	digit, and not a '+', or a '-' as its first character.
*/
bool ubf_int64_from_str (int64_t *pi, const char *chStr);

/*
	ubf_uint16_from_str
	ubf_ushort_from_str

	Returns an unsigned 16 bit integer (uint16_t) of the ASCII string chStr in the
	address pu points to. The function calls ubf_uint64_from_str () to obtain the result.
	If pus is NULL, the return value of the function indicates the success or failure of
	the conversion without returning the actual result of the conversion. The biggest
	number that can be successfully converted to a uint16_t is USHRT_MAX, which is
	usually 0xFFFF.

	A return value of TRUE means the conversion was successful. If the function returns
	FALSE the conversion was unsuccessful. The function returns TRUE if the conversion
	was successful but due to pus being NULL the result of it could not be returned to
	the caller.
*/
bool ubf_uint16_from_str (uint16_t *pus, const char *chStr);
#define ubf_ushort_from_str(a,b)					\
			ubf_uint16_from_str (a, b)
/*
	ubf_strd_from_uint64

	Returns the decimal representation of u64 in ASCII. The buffer chStr points to must
	be at least UBF_UINT64_STRLEN bytes long. For a function with identical functionality
	but that returns the bytes written to the result, see ubf_str_from_uint64 (). Unlike
	ubf_str_from_uint64 (), the function ubf_strd_from_uint64 () calls the library
	routine snprintf () to perform the conversion but discards its return value.
	
	Note that this function is around 4 times slower than ubf_str_from_uint64 (). It is
	therefore disabled.
*/
//void ubf_strd_from_uint64 (char *chStr, uint64_t u64);
#define ubf_strd_from_uint64(s,u)						\
		error Function ubf_strd_from_uint64 () is obsolete. Use ubf_str_from_uint64. See comment.

/*
	Test function builds.
*/
#ifdef DEBUG
	#ifndef UBF_BUILD_STRINTUINT_TEST
	#define UBF_BUILD_STRINTUINT_TEST
	#endif
#endif
#ifdef UBF_BUILD_STRINTUINT_TEST
	bool ubf_test_str_from_uint8 (void);
	bool ubf_test_str0 (void);
	bool Test_strintuint (void);
#else
	#define ubf_test_str_from_uint8()		(true)
	#define ubf_test_str0()					(true)
	#define Test_strintuint()				(true)
#endif


#ifdef __cplusplus
	}
#endif

#endif															// End of U_STR_INT_UINT_INCLUDED.
