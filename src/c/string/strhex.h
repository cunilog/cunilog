/****************************************************************************************

	File:		strhex.h
	Why:		Functions for hexadecimal digits.
	OS:			C99
	Author:		Thomas
	Created:	2020-03-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-03-07	Thomas			Created. Functions have been moved from ubfsecure.c/h into
							 this module and renamed (without the "secure" part in them).

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

#ifndef U_STR_HEX_H
#define U_STR_HEX_H

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

EXTERN_C_BEGIN

// Minimum string length and size to hold an 8 bit hexadecimal number in ASCII.
#ifndef UBF_HEX8_STRLEN
#define UBF_HEX8_STRLEN				(2)
#endif
#ifndef UBF_HEX8_STRSIZ
#define UBF_HEX8_STRSIZ				(UBF_HEX8_STRLEN + 1)
#endif
// Minimum string length and size to hold a 16 bit hexadecimal number in ASCII.
#ifndef UBF_HEX16_STRLEN
#define UBF_HEX16_STRLEN			(4)
#endif
#ifndef UBF_HEX16_STRSIZ
#define UBF_HEX16_STRSIZ			(UBF_HEX16_STRLEN + 1)
#endif
// Minimum string length and size to hold a 32 bit hexadecimal number in ASCII.
#ifndef UBF_HEX32_STRLEN
#define UBF_HEX32_STRLEN			(8)
#endif
#ifndef UBF_HEX32_STRSIZ
#define UBF_HEX32_STRSIZ			(UBF_HEX32_STRLEN + 1)
#endif
// Minimum string length and size to hold a 64 bit hexadecimal number in ASCII.
#ifndef UBF_HEX64_STRLEN
#define UBF_HEX64_STRLEN			(16)
#endif
#ifndef UBF_HEX64_STRSIZ
#define UBF_HEX64_STRSIZ			(UBF_HEX64_STRLEN + 1)
#endif

// We can as well have SIZE_T_MAX because it seems more natural/reasonable.
#ifndef SIZE_T_MAX
#define SIZE_T_MAX	SIZE_MAX
#endif

// Error codes.
#define UBF_INVALID_HEX_CHAR		((unsigned char) -1)
#define UBF_INVALID_OCT_CHAR		((unsigned char) -1)
#define UBF_INVALID_BIN_CHAR		((unsigned char) -1)

// The maximum amount of hexadecimal ASCII digits for
#define UINT16_ASCII_HEX_DIGITS			 (4)
#define UINT32_ASCII_HEX_DIGITS			 (8)
#define UINT64_ASCII_HEX_DIGITS			(16)

/*
	ubf_is_octal_digit

	Returns or evaluates to TRUE if c contains an ASCII digit between 0 and 7, FALSE
	otherwise.
*/
#define ubf_is_octal_digit_macro(c)						\
		((unsigned char) (c) >= '0' && (unsigned char) (c) <= '7')
#ifdef DEBUG
	bool ubf_is_octal_digit (char c);
#else
    #define ubf_is_octal_digit(c)	ubf_is_octal_digit_macro (c)
#endif

/*
	ubf_is_hex_digit

	Returns or evaluates to true if c contains an ASCII hexadecimal digit, false
	otherwise. Hexadecimal digits are the decimal digits 0 to 9, plus the the letters
	A to F.
*/
#define ubf_is_hex_digit_macro(c)						\
(														\
		((unsigned char) (c) >= '0' && (unsigned char) (c) <= '9')\
	||	((unsigned char) (c) >= 'A' && (unsigned char) (c) <= 'F')\
	||	((unsigned char) (c) >= 'a' && (unsigned char) (c) <= 'f')\
)
#ifdef DEBUG
	bool ubf_is_hex_digit (char c);
#else
	#define ubf_is_hex_digit(c)		ubf_is_hex_digit_macro (c)
#endif

/*
	ubf_value_of_ASCII_hex
	
	Returns the value of the hexadecimal character in c. The function returns
	UBF_INVALID_HEX_CHAR, which is defined as (unsigned char) -1 if c does not
	contain a valid hexadecimal character.
	
	Valid hexadecimal characters are the digits "0" to "9", and the letters
	"A" to "F" or "a" to "f".
	"0" returns 0.
	"1" returns 1.
	...
	"9" returns 9.
	"A" returns 10.
	...
	"F" returns 15.
	"a" returns 10.
	...
	"f" returns 15.
	Anything else returns UBF_INVALID_HEX_CHAR, which is defined as (unsigned char) -1.
*/
#define ubf_value_of_ASCII_hex_macro(c)					\
	(													\
		(unsigned char) (c) >= '0' && (unsigned char) (c) <= '9' ? (unsigned char) (c) - '0' :\
		(unsigned char) (c) >= 'a' && (unsigned char) (c) <= 'f' ? (unsigned char) (c) - 'a' + 10 :\
		(unsigned char) (c) >= 'A' && (unsigned char) (c) <= 'F' ? (unsigned char) (c) - 'A' + 10 :\
		UBF_INVALID_HEX_CHAR							\
	)
#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_hex (const char c);
#else
	#define ubf_value_of_ASCII_hex(c)	ubf_value_of_ASCII_hex_macro (c)
#endif

/*
	ubf_value_of_ASCII_oct
	
	Returns the value of the octal character in c. The function returns
	UBF_INVALID_OCT_CHAR, which is defined as (unsigned char) -1 if c does
	not contain a valid octal character ('0', '1', '2', '3', '4', '5', '6',
	or '7').
*/
#define ubf_value_of_ASCII_oct_macro(c)					\
	(													\
			(unsigned char) (c) >= '0'					\
		&&	(unsigned char) (c) <= '7'					\
		?	(unsigned char) (c) - '0'					\
		:	UBF_INVALID_OCT_CHAR						\
	)
#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_oct (const char c);
#else
	#define ubf_value_of_ASCII_oct(c)	ubf_value_of_ASCII_oct_macro (c)
#endif

/*
	ubf_octet_from_hex
	
	Reads up to two hexadecimal characters from chHx and writes the resulting
	binary octet to the location o points to.
	
	The function expects that it can read up to two characters from chHx.
	It does not perform a NUL check.
		
	The function returns the amount of hexadecimal characters that were
	read and used from the location chHx points to to produce the octet
	stored at o, which can be either 0 (if the first character is not a hex
	character), 1 (if only the first character is a hexadecimal character),
	or 2 (if both characters are hexadecimal).
*/
size_t ubf_octet_from_hex (unsigned char *o, const char *chHx);

/*
	ubf_octet_from_oct
	
	Reads up to three octal characters from chOc and writes the resulting
	binary octet (byte) to the location o points to.
	
	Valid octal bytes start at 000 (0d) up to 377 (255d, FFh). The function
	does not consume anything above octet boundary. For instance, an input
	of "477" would consume the first two characters ("47") only because the
	octal number 477 requires more than a single octet to be stored.
	
	The function returns the amount of octal characters consumed to produce
	the value that is written to the location o points to.
*/
size_t ubf_octet_from_oct (unsigned char *o, const char *chOc);

/*
	ubf_octet_from_bin
	
	Reads up to 8 binary characters from chOb and writes the resulting
	binary octet (byte) to the location o points to.
	
	Valid binary characters are '0' and '1'. The function does not consume
	anything above byte boundary.
	
	The function returns the amount of binary digits consumed to produce
	the value that is written to the location o points to.
*/
size_t ubf_octet_from_bin (unsigned char *o, const char *chOb);

/*
	ubf_uint16_from_hex

	Returns a 16 bit unsigned integer read from its hexadecimal ASCII
	representation chHx16 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx16
	and used to create the 16 bit unsigned value stored at the location pui16
	points to. If chHx16 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui16 points
	to.
	
	The pointer to the target value pui16 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.
	
	The function consumes a maximum of 4 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint16_from_hex (uint16_t *pui16, const char *chHx16)
;

/*
	ubf_uint32_from_hex
	
	Returns a 32 bit unsigned integer read from its hexadecimal ASCII
	representation chHx32 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx32
	and used to create the 32 bit unsigned value stored at the location pui32
	points to. If chHx32 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui32 points
	to.
	
	The pointer to the target value pui32 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.

	The function consumes a maximum of 8 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint32_from_hex (uint32_t *pui32, const char *chHx32)
;

/*
	ubf_uint64_from_hex
	
	Returns a 64 bit unsigned integer read from its hexadecimal ASCII
	representation chHx64 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx64
	and used to create the 64 bit unsigned value stored at the location pui64
	points to. If chHx64 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui64 points
	to.
	
	The pointer to the target value pui64 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.

	The function consumes a maximum of 16 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint64_from_hex (uint64_t *pui64, const char *chHx64)
;

/*
	uint64_from_hex_str

	Returns the value of the hexadecimal string hexstr points to as a uint64_t. The
	function does not check for an overrun. Processing stops at the first character in
	hexstr that is not a hexadecimal character. Both, upper and lower-case characters
	are accepted.

	Examples:						Return value
	"12345"							-> 12345
	"A"								-> 10
	"228"							-> 552
	"ax"							-> 10
	"g"								-> 0
	""								-> 0
*/
uint64_t uint64_from_hex_str (const char *hexstr);

/*
	uint64_from_dec_or_hex_str

	Returns the value of the decimal or hexadecimal string decorhex points to as a
	uint64_t. Processing stops at the first character in decorhex that is not a digit
	or a hexadecimal character. A hexadeximal number is expected to start with "0x"
	or "0X", otherwise the number is assumed to be a decimal number and treated
	accordingly, for instance "0A" would return 0.

	Examples:						Return value
	"0A"							-> 0
	"0xA"							-> 10
	"55"							-> 55
*/
uint64_t uint64_from_dec_or_hex_str (const char *decorhex);

/*
	ubf_hex2bin
	
	This is our own version of Libsodium's sodium_hex2bin () function.
	
	The function expects a hexadecimal ASCII string in hex_input with hex_len octets/
	characters and writes the binary version of it to bin_output. The parameter
	bin_maxlen specifies the size of the buffer bin_output points to.
	
	Note that each octet written to bin_output requires two hexadecimal ASCII digits
	read from hex_input. This means that
	a) hex_len must be an even number, and
	b) bin_maxlen must be at least hex_len/2 if the input is supposed to be fully
	converted.
	
	The function stops converting when it encounters a character in hex_input that
	is not a valid hexadecimal ASCII digit ("0" to "9", "A" to "F", or "a" to "f").

	The function returns the amount of octets written to bin_output at the address
	pbin_len points to, provided it is not NULL.
	
	Note that if the binary output is interpreted as a multi-octet number this
	number will be in big-endian notation, since this function converts octet by
	octet in the order of the hexadecimal input.

	Returns TRUE on success, FALSE if it fails. The function returns FALSE if
	hex_len is not an even number, as this would not allow for a conversion. If
	pbin_len is not NULL, the function writes the amount of bytes written to
	bin_output to this address. It does this independent of the function's return
	value of TRUE or FALSE.
*/
bool ubf_hex2bin	(
			unsigned char		*bin_output,					// The output.
			const size_t		bin_maxlen,						// Length of the output buffer,
																//	in octets (bytes).
			const char			*hex_input,						// The input in hexadecimal
																//	ASCII representation.
			const size_t		hex_len,						// Length of the input buffer,
																//	in octets (bytes).
			size_t *const		pbin_len						// The amount of bytes written.
                   )
;

/*
	asc_hex_from_octet
	asc_hex_from_octet_lower

	Writes the two characters representing the hexadecimal notation of the byte/octet
	(8 bit data word) ui to the location pc points to. The function writes exactly two
	ASCII characters to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_octet (char *pc, uint8_t ui)
;
void asc_hex_from_octet_lower (char *pc, uint8_t ui)
;

/*
	URI_encode_hex_from_octet

	Writes a percent character ("%") plus two characters representing the hexadecimal notation
	of the byte/octet (8 bit data word) ui to the location pc points to. The function writes
	exactly three ASCII characters to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void URI_encode_hex_from_octet (char *pc, uint8_t ui)
;
void URI_encode_hex_from_octet_lower (char *pc, uint8_t ui)
;

/*
	asc_hex_from_word

	Writes the four characters representing the hexadecimal notation of the 16 bit data word
	ui to the location pc points to. The function writes exactly four ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_word (char *pc, uint16_t ui)
;
void asc_hex_from_word_lower (char *pc, uint16_t ui)
;

/*
	asc_hex_from_dword

	Writes the 8 characters representing the hexadecimal notation of the 32 bit data
	ui to the location pc points to. The function writes exactly 8 ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_dword (char *pc, uint32_t ui)
;
void asc_hex_from_dword_lower (char *pc, uint32_t ui)
;

/*
	asc_hex_from_qword

	Writes the 16 characters representing the hexadecimal notation of the 64 bit data
	ui to the location pc points to. The function writes exactly 16 ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_qword (char *pc, uint64_t ui)
;
void asc_hex_from_qword_lower (char *pc, uint64_t ui)
;

/*
	asc_bin_from_octet

	Writes the 8 characters representing the binary notation of the byte/octet
	(8 bit data word) ui to the location pc points to. The function writes exactly 8
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_octet (char *pc, uint8_t ui)
;

/*
	asc_bin_from_word

	Writes the 16 characters representing the binary notation of the 16 bit data
	word ui to the location pc points to. The function writes exactly 16
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_word (char *pc, uint16_t ui)
;

/*
	asc_bin_from_dword

	Writes the 32 characters representing the binary notation of the 32 bit data
	word ui to the location pc points to. The function writes exactly 32
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_dword (char *pc, uint32_t ui)
;

/*
	ubf_hex_from_octet

	Returns the hexadecimal ASCII notation of ui in chResult. It is expected that the
	buffer chResult points to is at least 3 characters (including the terminating NUL
	character) long.
	Byte 0 is for the ASCII character of the MSB nibble (tetrade). Values are from '0'
	to 'F'.
	Byte 1 is for the ASCII character of the LSB nibble (tetrade). Values are from '0'
	to 'F'.
	Byte 2 is overwritten with a NUL byte to terminate the result.
*/
void ubf_hex_from_octet (char *chResult, uint8_t ui);

/*
	ubf_hex_from_word
	ubf_hex_from_uint16

	Returns the hexadecimal notation of the 16 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 5 characters long, which
	includes the terminating NUL character. The constant UBF_HEX16_STRSIZ can be used
	to determine this length, which is 4 + 1 octets.
*/
void ubf_hex_from_word (char *chResult, uint16_t ui);
#define ubf_hex_from_uint16(r,u)			\
			ubf_hex_from_word (r, u)

/*
	ubf_hex_from_dword
	ubf_hex_from_uint32

	Returns the hexadecimal notation of the 32 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 9 characters long, which
	includes the terminating NUL character. The constant UBF_HEX32_STRSIZ is defined as
	9 and can be utilised for this purpose.
*/
void ubf_hex_from_dword (char *chResult, uint32_t ui);
#define ubf_hex_from_uint32(r,u)			\
			ubf_hex_from_dword (r, u)

/*
	ubf_hex_from_qword
	ubf_hex_from_uint64

	Returns the hexadecimal notation of the 64 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 17 characters long, which
	includes the terminating NUL character. The constant UBF_HEX64_STRSIZ is defined as
	being this length, including the NUL character.
*/
void ubf_hex_from_qword (char *chResult, uint64_t ui);
#define ubf_hex_from_uint64(r,u)			\
			ubf_hex_from_qword (r, u)

/*
	asc_hex_zero_from_qword

	Returns the hexadecimal notation of the 64 bit unsigned integer ui in the buffer
	chResult points to. The parameter stWidthResult restricts or extends the width of the
	result, beginning from the right side, excluding a terminating NUL character.

	The function is identical to asc_hex_zero_from_qword () except that it does not write
	a terminating NUL character.
*/
void asc_hex_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui)
;

/*
	ubf_hex_str_zero_from_qword
	
	Returns the hexadecimal notation of the 64 bit unsigned integer ui in the buffer
	chResult points to. The parameter stWidthResult restricts or extends the width of the
	result, beginning from the right side, excluding a terminating NUL character. To use
	chResult as a standard C string it must hold space for at least stWidthResult
	characters plus an additional NUL character, hence the buffer chResult points to must
	always provide space for at least stWidthResult + 1 octets (bytes).
	
	Examples:
	
	ui		stWidthResult	chResult
	----------------------------------------
	65535	4				"FFFF"
	16		2				"10"
	16		1				"0"
	65535	5				"0FFFF"
	65535	10				"000000FFFF"
	65535	2				"FF"
	
	int main(void)
	{
		char		ch [1024];
		int			i;
		
		for (i = 0; i <= 30; i ++)
		{
			ubf_hex_str_zero_from_qword (ch, i, 5);
			printf ("i: %d, \"%s\", len = %zu\n", i, ch, strlen (ch));
		}
		return 0;
	}

	i: 0, "", len = 0
	i: 1, "5", len = 1
	i: 2, "05", len = 2
	i: 3, "005", len = 3
	i: 4, "0005", len = 4
	i: 5, "00005", len = 5
	i: 6, "000005", len = 6
	i: 7, "0000005", len = 7
	i: 8, "00000005", len = 8
	i: 9, "000000005", len = 9
	i: 10, "0000000005", len = 10
	i: 11, "00000000005", len = 11
	i: 12, "000000000005", len = 12
	i: 13, "0000000000005", len = 13
	i: 14, "00000000000005", len = 14
	i: 15, "000000000000005", len = 15
	i: 16, "0000000000000005", len = 16
	i: 17, "00000000000000005", len = 17
	i: 18, "000000000000000005", len = 18
	i: 19, "0000000000000000005", len = 19
	i: 20, "00000000000000000005", len = 20
	i: 21, "000000000000000000005", len = 21
	i: 22, "0000000000000000000005", len = 22
	i: 23, "00000000000000000000005", len = 23
	i: 24, "000000000000000000000005", len = 24
	i: 25, "0000000000000000000000005", len = 25
	i: 26, "00000000000000000000000005", len = 26
	i: 27, "000000000000000000000000005", len = 27
	i: 28, "0000000000000000000000000005", len = 28
	i: 29, "00000000000000000000000000005", len = 29
	i: 30, "000000000000000000000000000005", len = 30
	
*/
void ubf_hex_str_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui);

/*
	ubf_hex_str_blank_from_qword
	
	The function is identical to ubf_hex_str_zero_from_qword () with the exception
	that leading zeros are replaced by blanks (spaces, SPC, ASCII 32d, 20h).
*/
void ubf_hex_str_blank_from_qword (char *chResult, size_t stWidthResult, uint64_t ui);

/*
	UCS2UTF16bin_from_hex
	
	The function expects a hexadecimal ASCII input string that contains UCS-2 or UTF-16
	characters, represented as hexadecimal ASCII. It writes out the 16 bit characters
	to u16result, up to max_u16result characters.
	
	If u16result is NULL, the function does not write output but returns the amount of
	uint16_t that would have been written at the address pU16written points to, unless
	pU16written is also NULL. Note that the value of max_u16result is still taken into
	consideration in this case. So, in order to obtain the size of the required array
	of u16result, set max_u16result to a value greater than the expected size or to
	SIZE_T_MAX.
	
	size_t		required_size;
	UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, "00410042", 8, &required_size);
	// Amount of uint16_t required is now in required_size.
	required_size *= sizeof (uint16_t);							// In bytes/octets.
	
	The function fails if len_cchex is not dividable by 4, as each UCS-2 or UTF-16 16 bit
	data written to u16result requires four hexadecimal ASCII characters in the input
	string cchex. The function also fails when len_cchex is 0.
	
	cchex				u16result
	"0031"				31
	"00310032"			31, 32
	
	Note that the function does not terminate the buffer u16result points to with a NUL
	character unless the hexadecimal ASCII input string cchex ends with a character
	string of "0000", which is a NUL terminator in UCS-2/UTF-16.
	
	The function returns TRUE on success, FALSE otherwise. Independent of the function's
	return value the amount of uint16_t (16 bit) values written to u16result is returned
	at the address pU16written points to.
*/
bool UCS2UTF16bin_from_hex	(
			uint16_t			*u16result,						// The output as 16 bit UCS-2 or
																//	UTF-16.
			size_t				max_u16result,					// The size of the buffer
																//	u16result points to, in
																//	uint16_t (NOT octets).
			const char			*cchex,							// The input string consisting
																//	of hexadecimal ASCII characters,
																//	4 hexadecimal ASCII characters
																//	for each uint16_t (UCS-2 or
																//	UTF-16) written to u16result.
			size_t				len_cchex,						// The length of the input string,
																//	excluding NUL.
			size_t				*pU16written
							)
;

/*
	ubf_hex_simple_hash
	
	This is a very simple hash function. It is meant as a (pretty simplistic)
	stand-in for Libsodium's ubf_crypto_generichash () in its absense.
	
	Do not use this function in security-critical applications.
	Use ubf_crypto_generichash () if the hash is important.
	
	The length of the hash stLenHash is currently fixed at 32 octets.
*/
void ubf_hex_simple_hash	(
				unsigned char	*pHash,		size_t	stLenHash,	// Hash and its length.
				const char		*pData,		size_t	stLenData	// Data and its length.
							)
;

/*
	ubf_hex_test_function
	
	Test function. Tests the functions in this module.
*/
#ifdef DEBUG
	#ifndef UBF_HEX_BUILD_TEST_FUNCTION
	#define UBF_HEX_BUILD_TEST_FUNCTION
	#endif
#else
#endif
#ifdef UBF_HEX_BUILD_TEST_FUNCTION
	bool ubf_hex_test_function (void);
#else
	#define ubf_hex_test_function()	(true)
#endif

EXTERN_C_END

#endif															// End of #ifndef U_STR_HEX_H.
