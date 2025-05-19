/****************************************************************************************

	File:		strhex.c
	Why:		Functions for hexadecimal digits.
	OS:			C99
	Author:		Thomas
	Created:	2020-03-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-03-07	Thomas			Created. Functions have been moved from ubfsecure.c/h into
							 this module.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./unref.h"
		#include "./Warnings.h"
		#include "./strhex.h"
		#include "./strintuint.h"
		#include "./ubfmem.h"
		#include "./ubfdebug.h"
	#else
		#include "./../pre/unref.h"
		#include "./../pre/Warnings.h"
		#include "./strhex.h"
		#include "./strintuint.h"
		#include "./../mem/ubfmem.h"
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

#ifdef DEBUG
	bool ubf_is_octal_digit (char c)
	{
		return ((unsigned char) c >= '0' && (unsigned char) c <= '7');
	}
#endif

#ifdef DEBUG
	bool ubf_is_hex_digit (char c)
	{
		return	(
					((unsigned char) c >= '0' && (unsigned char) c <= '9') ||
					((unsigned char) c >= 'A' && (unsigned char) c <= 'F') ||
					((unsigned char) c >= 'a' && (unsigned char) c <= 'f')
				);
	}
#endif

#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_hex (const char c)
	{
		unsigned char	uc	= (unsigned char) c;
		
		uc =	uc >= '0' && uc <= '9' ? uc - '0' :
				uc >= 'a' && uc <= 'f' ? uc - 'a' + 10 :
				uc >= 'A' && uc <= 'F' ? uc - 'A' + 10 :
				UBF_INVALID_HEX_CHAR;							// Error.
		return uc;
	}
#endif

#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_oct (const char c)
	{
		unsigned char	uc	= (unsigned char) c;
		
		return uc >= '0' && uc <= '7' ? uc - '0' : UBF_INVALID_OCT_CHAR;
	}
#endif

unsigned char ubf_value_of_ASCII_bin (const char c)
{
	unsigned char	uc	= (unsigned char) c;
	
	return '0' == uc || '1' == uc ? uc - '0' : UBF_INVALID_BIN_CHAR;
}

size_t ubf_octet_from_hex (unsigned char *o, const char *chHx)
{
	unsigned char	c1;
	unsigned char	c0;
	
	c1 = ubf_value_of_ASCII_hex (*chHx);
	++ chHx;
	if (UBF_INVALID_HEX_CHAR == c1)
	{
		return 0;
	}
	ubf_assert (0 == ('\xF0' & c1));
	c0 = ubf_value_of_ASCII_hex (*chHx);
	if (UBF_INVALID_HEX_CHAR == c0)
	{
		*o = c1;
		return 1;
	}
	c1 <<= 4;
	ubf_assert (0 == ('\xF0' & c0));
	c1 += c0;
	*o = c1;
	return 2;
}

size_t ubf_octet_from_oct (unsigned char *o, const char *chOc)
{
	unsigned char	c2;
	unsigned char	c1;
	unsigned char	c0;
	
	c2 = ubf_value_of_ASCII_oct (*chOc);
	++ chOc;
	if (UBF_INVALID_OCT_CHAR == c2)
	{
		return 0;
	}
	ubf_assert (0 == ('\xF8' & c2));
	c1 = ubf_value_of_ASCII_oct (*chOc);
	++ chOc;
	if (UBF_INVALID_OCT_CHAR == c1)
	{
		*o = c2;
		return 1;
	}
	ubf_assert (0 == ('\xF8' & c1));
	c2 <<= 3;
	c2 += c1;
	c0 = ubf_value_of_ASCII_oct (*chOc);
	if (UBF_INVALID_OCT_CHAR == c0)
	{
		*o = c2;
		return 2;
	}
	if (c2 << 3 <= 255 - c0)
	{
		ubf_assert (0 == ('\xF8' & c0));
		c2 <<= 3;
		c2 += c0;
		*o = c2;
		return 3;
	}
	*o = c2;
	return 2;
}

size_t ubf_octet_from_bin (unsigned char *o, const char *chOb)
{
	unsigned char	ucb	= 0;
	unsigned char	uct;
	unsigned int	ui	= 8;
	
	ubf_assert (1 == sizeof (unsigned char));
	while (ui)
	{
		uct = ubf_value_of_ASCII_bin (*chOb);
		++ chOb;
		if (UBF_INVALID_BIN_CHAR == uct)
			break;
		ucb <<= 1;
		ucb += uct;
		-- ui;
	}
	*o = ucb;
	return 8 - ui;
}

#ifdef _MSC_VER
#pragma warning (disable: 4706)									// Assignment within conditional expression.
#endif

size_t ubf_uint16_from_hex (uint16_t *pui16, const char *chHx16)
{
	size_t		stRet = 0;
	uint16_t	uiRet = 0;
	unsigned char	c = UBF_INVALID_HEX_CHAR;

	while	(
					stRet < UINT16_ASCII_HEX_DIGITS
				&&	(UBF_INVALID_HEX_CHAR != (c = ubf_value_of_ASCII_hex (chHx16 [stRet])))
			)
	{
		uiRet <<= 4;
		uiRet += c;
		++ stRet;
	}
	if (stRet && pui16)
		*pui16 = uiRet;
	return stRet;
}

size_t ubf_uint32_from_hex (uint32_t *pui32, const char *chHx32)
{
	size_t		stRet	= 0;
	uint32_t	uiRet	= 0;
	unsigned char	c	= UBF_INVALID_HEX_CHAR;
	
	while	(
					stRet < UINT32_ASCII_HEX_DIGITS
				&&	(UBF_INVALID_HEX_CHAR != (c = ubf_value_of_ASCII_hex (chHx32 [stRet])))
			)
	{
		uiRet <<= 4;
		uiRet += c;
		++ stRet;
	}
	if (stRet && pui32)
		*pui32 = uiRet;
	return stRet;
}

size_t ubf_uint64_from_hex (uint64_t *pui64, const char *chHx64)
{
	size_t		stRet	= 0;
	uint64_t	uiRet	= 0;
	unsigned char	c	= UBF_INVALID_HEX_CHAR;
	
	while	(
					stRet < UINT64_ASCII_HEX_DIGITS
				&&	(UBF_INVALID_HEX_CHAR != (c = ubf_value_of_ASCII_hex (chHx64 [stRet])))
			)
	{
		uiRet <<= 4;
		uiRet += c;
		++ stRet;
	}
	if (stRet && pui64)
		*pui64 = uiRet;
	return stRet;
}

uint64_t uint64_from_hex_str (const char *hexstr)
{
	uint64_t			u = 0;
	unsigned char		c;

	while ((c = (unsigned char) *hexstr ++))
	{
		if (c > '0' - 1 && c < '9' + 1)
		{
			c -= '0';
		} else
		if (c > 'a' - 1 && c < 'f' + 1)
		{
			c -= 'a';
			c += 10;
		} else
		if (c > 'A' - 1 && c < 'F' + 1)
		{
			c -= 'A';
			c += 10;
		}else
			return u;
		u <<= 4;
		u += c;
	}
	return u;
}

#ifdef _MSC_VER
#pragma warning (default: 4706)									// Assignment within conditional expression.
#endif

uint64_t uint64_from_dec_or_hex_str (const char *decorhex)
{
	uint64_t		ui;

	if (!strncmp (decorhex, "0x", 2) || !strncmp (decorhex, "0X", 2))
	{
		ui = uint64_from_hex_str (decorhex + 2);
	} else
	{
		ubf_uint64_from_str (&ui, decorhex);
	}
	return ui;
}

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
{
	const char				*read			= hex_input;
	unsigned char			*write			= bin_output;
	
	if (hex_len && 0 == (hex_len % 2))
	{	// The hexadecimal input string must be dividable by 2 since two hexadecimal
		//	digits are required per octet to write.
		unsigned char		cw;									// The octet to write.
		unsigned char		c;
		//size_t				bytes_max		= bin_maxlen;
		size_t				bytes_written	= 0;
		size_t				bytes_read		= hex_len;
		
		while (bin_maxlen && bytes_read > 1)
		{
			cw = ubf_value_of_ASCII_hex (read [0]);
			if (UBF_INVALID_HEX_CHAR == cw)
			{
				if (pbin_len)
					*pbin_len = bytes_written;
				return false;
			}
			cw <<= 4;											// This is the higher tetrade.
			c = ubf_value_of_ASCII_hex (read [1]);
			if (UBF_INVALID_HEX_CHAR == c)
			{
				if (pbin_len)
					*pbin_len = bytes_written;
				return false;
			}
			cw += c;											// This is the lower tetrade.
			*write = cw;
			read			+= 2;
			bytes_read		-= 2;
			//bytes_max		-= 2;
			bytes_written	+= 1;
			write			+= 1;
		}
		if (pbin_len)
			*pbin_len = bytes_written;
		return true;
	}
	if (pbin_len)
		*pbin_len = 0;
	return false;
}

// Used by the hex conversion functions. No NUL-terminator is stored.
DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR ()
static char				hexASCIIu [16]		= "0123456789ABCDEF";
static char				hexASCIIl [16]		= "0123456789abcdef";
DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR ()

void asc_hex_from_octet (char *pc, uint8_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIu [((ui & 0xF0) >> 4) & 0x0F];
	*pc		= hexASCIIu [((ui & 0x0F))];
}

void asc_hex_from_octet_lower (char *pc, uint8_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIl [((ui & 0xF0) >> 4) & 0x0F];
	*pc		= hexASCIIl [((ui & 0x0F))];
}

void URI_encode_hex_from_octet (char *pc, uint8_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++ = '%';
	*pc ++	= hexASCIIu [((ui & 0xF0) >> 4) & 0x0F];
	*pc		= hexASCIIu [((ui & 0x0F))];
}

void URI_encode_hex_from_octet_lower (char *pc, uint8_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++ = '%';
	*pc ++	= hexASCIIl [((ui & 0xF0) >> 4) & 0x0F];
	*pc		= hexASCIIl [((ui & 0x0F))];
}

void asc_hex_from_word (char *pc, uint16_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIu [((ui & 0xF000) >> 12) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0F00) >>  8) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00F0) >>  4) & 0x0F];
	*pc		= hexASCIIu [((ui & 0x000F))];
}

void asc_hex_from_word_lower (char *pc, uint16_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIl [((ui & 0xF000) >> 12) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0F00) >>  8) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00F0) >>  4) & 0x0F];
	*pc		= hexASCIIl [((ui & 0x000F))];
}

void asc_hex_from_dword (char *pc, uint32_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIu [((ui & 0xF0000000) >> 28) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0F000000) >> 24) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00F00000) >> 20) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x000F0000) >> 16) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0000F000) >> 12) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00000F00) >>  8) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x000000F0) >>  4) & 0x0F];
	*pc		= hexASCIIu [((ui & 0x0000000F))];
}

void asc_hex_from_dword_lower (char *pc, uint32_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIl [((ui & 0xF0000000) >> 28) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0F000000) >> 24) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00F00000) >> 20) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x000F0000) >> 16) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0000F000) >> 12) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00000F00) >>  8) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x000000F0) >>  4) & 0x0F];
	*pc		= hexASCIIl [((ui & 0x0000000F))];
}

void asc_hex_from_qword (char *pc, uint64_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIu [((ui & 0xF000000000000000) >> 60) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0F00000000000000) >> 56) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00F0000000000000) >> 52) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x000F000000000000) >> 48) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0000F00000000000) >> 44) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00000F0000000000) >> 40) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x000000F000000000) >> 36) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0000000F00000000) >> 32) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00000000F0000000) >> 28) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x000000000F000000) >> 24) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0000000000F00000) >> 20) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00000000000F0000) >> 16) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x000000000000F000) >> 12) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x0000000000000F00) >>  8) & 0x0F];
	*pc ++	= hexASCIIu [((ui & 0x00000000000000F0) >>  4) & 0x0F];
	*pc		= hexASCIIu [((ui & 0x000000000000000F))];
}

void asc_hex_from_qword_lower (char *pc, uint64_t ui)
{
	ubf_assert_non_NULL (pc);

	*pc ++	= hexASCIIl [((ui & 0xF000000000000000) >> 60) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0F00000000000000) >> 56) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00F0000000000000) >> 52) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x000F000000000000) >> 48) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0000F00000000000) >> 44) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00000F0000000000) >> 40) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x000000F000000000) >> 36) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0000000F00000000) >> 32) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00000000F0000000) >> 28) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x000000000F000000) >> 24) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0000000000F00000) >> 20) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00000000000F0000) >> 16) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x000000000000F000) >> 12) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x0000000000000F00) >>  8) & 0x0F];
	*pc ++	= hexASCIIl [((ui & 0x00000000000000F0) >>  4) & 0x0F];
	*pc		= hexASCIIl [((ui & 0x000000000000000F))];
}

// The binary ASCII texts from 0000 to 1111. No NUL-terminator is stored.
DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR ()
static char				binASCII [4 * 16] = "0000000100100011010001010110011110001001101010111100110111101111";
DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR ()

void asc_bin_from_octet (char *pc, uint8_t ui)
{
	ubf_assert_non_NULL (pc);

	memcpy (pc, &binASCII [((ui & 0xF0) >> 4) & 0x0F],		4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x0F))], 4);
}

void asc_bin_from_word (char *pc, uint16_t ui)
{
	ubf_assert_non_NULL (pc);

	memcpy (pc, &binASCII [((ui & 0xF000) >> 12) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x0F00) >>  8) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x00F0) >>  4) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x000F))],				4);
}

void asc_bin_from_dword (char *pc, uint32_t ui)
{
	ubf_assert_non_NULL (pc);

	memcpy (pc, &binASCII [((ui & 0xF0000000) >> 28) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x0F000000) >> 24) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x00F00000) >> 20) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x000F0000) >> 16) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x0000F000) >> 12) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x00000F00) >>  8) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x000000F0) >>  4) & 0x0F],	4);		pc += 4;
	memcpy (pc, &binASCII [((ui & 0x0000000F))],				4);
}


void ubf_hex_from_octet (char *chResult, uint8_t ui)
{
	char				*t		= chResult;

	ubf_assert (NULL != chResult);
	#ifdef DEBUG
		// Test for access violation in debug version.
		memset (chResult, UBF_ERROR_CHAR, 2 + 1);
	#endif
	// Looks a bit odd but provides all necessary steps.
	*t ++ = hexASCIIu [((ui & 0xF0) >> 4) & 0x0F];
	*t ++ = hexASCIIu [ui & 0x0F];
	*t = 0;
}

void ubf_hex_from_word (char *chResult, uint16_t ui)
{
	char				*t		= chResult;

	ubf_assert (NULL != chResult);
	#ifdef DEBUG
		// Test for access violation in debug version.
		memset (chResult, UBF_ERROR_CHAR, UBF_HEX64_STRSIZ);
	#endif
	*t ++ = hexASCIIu [((ui & 0xF000) >> 12) & 0x000F];
	*t ++ = hexASCIIu [((ui & 0x0F00) >>  8) & 0x000F];
	*t ++ = hexASCIIu [((ui & 0x00F0) >>  4) & 0x000F];
	*t ++ = hexASCIIu [ui & 0x000F];
	*t = 0;
}

void ubf_hex_from_dword (char *chResult, uint32_t ui)
{
	char				*t		= chResult;

	ubf_assert (NULL != chResult);
	#ifdef DEBUG
		// Test for access violation in debug version.
		memset (chResult, UBF_ERROR_CHAR, UBF_HEX32_STRSIZ);
	#endif
	*t ++ = hexASCIIu [((ui & 0xF0000000) >> 28) & 0x0000000F];
	*t ++ = hexASCIIu [((ui & 0x0F000000) >> 24) & 0x0000000F];
	*t ++ = hexASCIIu [((ui & 0x00F00000) >> 20) & 0x0000000F];
	*t ++ = hexASCIIu [((ui & 0x000F0000) >> 16) & 0x0000000F];
	*t ++ = hexASCIIu [((ui & 0x0000F000) >> 12) & 0x0000000F];
	*t ++ = hexASCIIu [((ui & 0x00000F00) >>  8) & 0x0000000F];
	*t ++ = hexASCIIu [((ui & 0x000000F0) >>  4) & 0x0000000F];
	*t ++ = hexASCIIu [ui & 0x0000000F];
	*t = 0;
}

void ubf_hex_from_qword (char *chResult, uint64_t ui)
{
	char				*t		= chResult;

	ubf_assert (NULL != chResult);
	#ifdef DEBUG
		// Test for access violation in debug version.
		memset (chResult, UBF_ERROR_CHAR, UBF_HEX64_STRSIZ);
	#endif
	*t ++ = hexASCIIu [((ui & 0xF000000000000000) >> 60) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x0F00000000000000) >> 56) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x00F0000000000000) >> 52) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x000F000000000000) >> 48) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x0000F00000000000) >> 44) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x00000F0000000000) >> 40) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x000000F000000000) >> 36) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x0000000F00000000) >> 32) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x00000000F0000000) >> 28) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x000000000F000000) >> 24) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x0000000000F00000) >> 20) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x00000000000F0000) >> 16) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x000000000000F000) >> 12) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x0000000000000F00) >>  8) & 0x000000000000000F];
	*t ++ = hexASCIIu [((ui & 0x00000000000000F0) >>  4) & 0x000000000000000F];
	*t ++ = hexASCIIu [ui & 0x000000000000000F];
	*t = 0;
}

void asc_hex_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui)
{
	char	chValue [UBF_HEX64_STRSIZ];
	char	*pVal	= chValue;

	if (stWidthResult)
	{
		asc_hex_from_qword (pVal, ui);
		if (stWidthResult > UBF_HEX64_STRLEN)
		{
			stWidthResult -= UBF_HEX64_STRLEN;
			memset (chResult, '0', stWidthResult);
			memcpy (chResult + stWidthResult, pVal, UBF_HEX64_STRLEN);
		} else
		if (stWidthResult < UBF_HEX64_STRLEN)
			memcpy (chResult, pVal + UBF_HEX64_STRLEN - stWidthResult, stWidthResult);
		else
			memcpy (chResult, pVal, stWidthResult + 1);
	}
}

void ubf_hex_str_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui)
{
	// Space for a 64 bit value in ASCII plus the memory debug header and footer.
	//char		chValue [UBFMEMDBG_CHARS (UBF_HEX64_STRSIZ)];
	char		chValue [UBF_HEX64_STRSIZ];
	char		*pVal;
	
	ubf_mem_init_ptr (chValue, UBF_HEX64_STRSIZ);
	pVal = ubf_mem_usr_ptr (chValue);
	
	if (stWidthResult)
	{
		ubf_hex_from_qword (pVal, ui);
		if (stWidthResult > UBF_HEX64_STRLEN)
		{
			stWidthResult -= UBF_HEX64_STRLEN;
			memset (chResult, '0', stWidthResult);
			memcpy (chResult + stWidthResult, pVal, UBF_HEX64_STRSIZ);
		} else
		if (stWidthResult < UBF_HEX64_STRLEN)
			memcpy (chResult, pVal + UBF_HEX64_STRLEN - stWidthResult, stWidthResult + 1);
		else
			memcpy (chResult, pVal, stWidthResult + 1);
	} else
		*chResult = '\0';
}

void ubf_hex_str_blank_from_qword (char *chResult, size_t stWidthResult, uint64_t ui)
{
	char		*ch;
	
	ubf_hex_str_zero_from_qword (chResult, stWidthResult, ui);
	ch = chResult;
	while ('0' == *ch)
	{
		*ch = ' ';
		++ ch;
	}
}

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
{
	size_t		written		= 0;

	if (len_cchex && cchex && 0 == (len_cchex % 4))
	{
		unsigned char	co [2];
		uint16_t		u16;
		const char		*cc		= cchex;
		size_t			lcc		= len_cchex;
		size_t			sw;
		bool			b;

		while (lcc)
		{
			b = ubf_hex2bin (co, 2, cc, 4, &sw);
			if (b)
			{
				if (max_u16result)
				{
					-- max_u16result;
					// Comes back as big endian but we don't know the endianness of the
					//	target plattform. Fix that here. First octet is the MSB, second
					//	octet is the LSB.
					u16 = (co [0] << 8) + co [1];				// Endianness of target platform.
					written	+= sw / 2;
					cc		+= 4;
					lcc		-= 4;
					if (u16result)
					{
						*u16result = u16;
						++ u16result;
					}
				} else
					break;
			} else
			{
				if (pU16written)
					*pU16written = written;
				return false;			
			}
		}
		if (pU16written)
			*pU16written = written;
		return true;		
	}
	if (pU16written)
		*pU16written = 0;
	return false;
}

void ubf_hex_simple_hash	(
				unsigned char	*pHash,		size_t	stLenHash,	// Hash and its length.
				const char		*pData,		size_t	stLenData	// Data and its length.
							)
{
	UNREFERENCED_PARAMETER (stLenHash);
	ubf_assert (32 == stLenHash);								// We expect a fixed length.
	ubf_assert (8 == sizeof (int64_t));							// We got to use this 4 times.
	
	int64_t			iHash	= 4711;
	signed char		c;
	size_t			size	= stLenData;
	const char		*p		= pData;
	
	while (size --)
	{
		c = (signed char) *p;
		iHash = c + (iHash << 6) + (iHash << 16) - iHash;
		++ p;
	}
	// The first 8 octets.
	memcpy (pHash, &iHash, sizeof (int64_t));
	size = stLenData / 2;
	p = pData;
	while (size --)
	{
		c = (signed char) *p;
		iHash = c + (iHash << 6) + (iHash << 16) - iHash;
		++ p;
	}
	// The second 8 octets.
	memcpy (pHash + sizeof (int64_t), &iHash, sizeof (int64_t));
	size = stLenData / 2;
	p = pData + size;
	while (size --)
	{
		c = (signed char) *p;
		iHash = c + (iHash << 6) + (iHash << 16) - iHash;
		++ p;
	}
	// The third 8 octets.
	memcpy (pHash + sizeof (int64_t) + sizeof (int64_t), &iHash, sizeof (int64_t));
	size = stLenData / 4;
	p = pData + (2 * size);
	while (size --)
	{
		c = (signed char) *p;
		iHash = c + (iHash << 6) + (iHash << 16) - iHash;
		++ p;
	}
	// The last (fourth) 8 octets.
	memcpy (pHash + sizeof (int64_t) + sizeof (int64_t) + sizeof (int64_t), &iHash, sizeof (int64_t));
}

#ifdef UBF_HEX_BUILD_TEST_FUNCTION
	bool ubf_hex_test_function (void)
	{
		bool			b			= true;					// Our return value.
		char			chT [32];
		unsigned char	o;
		size_t			st;

		ubf_expect_bool_AND (b, ubf_is_octal_digit ('0'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('0'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('1'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('2'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('3'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('4'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('5'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('6'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit ('7'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit ('8'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit ('9'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit ('A'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit ('Z'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit ('.'));
		
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('0'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('0'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('1'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('2'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('3'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('4'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('5'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('6'));
		ubf_expect_bool_AND (b, ubf_is_octal_digit_macro ('7'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit_macro ('8'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit_macro ('9'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit_macro ('A'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit_macro ('Z'));
		ubf_expect_bool_AND (b, !ubf_is_octal_digit_macro ('.'));
		
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('0'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('1'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('2'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('3'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('4'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('5'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('6'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('7'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('8'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('9'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('A'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('B'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('C'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('D'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('E'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('F'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('a'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('b'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('c'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('d'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('e'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit ('f'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit ('g'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit ('z'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit ('G'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit ('Z'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit ('.'));
		
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('0'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('1'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('2'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('3'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('4'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('5'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('6'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('7'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('8'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('9'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('A'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('B'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('C'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('D'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('E'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('F'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('a'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('b'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('c'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('d'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('e'));
		ubf_expect_bool_AND (b, ubf_is_hex_digit_macro ('f'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit_macro ('g'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit_macro ('z'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit_macro ('G'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit_macro ('Z'));
		ubf_expect_bool_AND (b, !ubf_is_hex_digit_macro ('.'));
		
		// Pretty much 100 % test coverage for the hexadecimal characters.
		ubf_expect_bool_AND (b,  0 == ubf_value_of_ASCII_hex ('0'));
		ubf_expect_bool_AND (b,  1 == ubf_value_of_ASCII_hex ('1'));
		ubf_expect_bool_AND (b,  2 == ubf_value_of_ASCII_hex ('2'));
		ubf_expect_bool_AND (b,  3 == ubf_value_of_ASCII_hex ('3'));
		ubf_expect_bool_AND (b,  4 == ubf_value_of_ASCII_hex ('4'));
		ubf_expect_bool_AND (b,  5 == ubf_value_of_ASCII_hex ('5'));
		ubf_expect_bool_AND (b,  6 == ubf_value_of_ASCII_hex ('6'));
		ubf_expect_bool_AND (b,  7 == ubf_value_of_ASCII_hex ('7'));
		ubf_expect_bool_AND (b,  8 == ubf_value_of_ASCII_hex ('8'));
		ubf_expect_bool_AND (b,  9 == ubf_value_of_ASCII_hex ('9'));
		ubf_expect_bool_AND (b, 10 == ubf_value_of_ASCII_hex ('a'));
		ubf_expect_bool_AND (b, 10 == ubf_value_of_ASCII_hex ('A'));
		ubf_expect_bool_AND (b, 11 == ubf_value_of_ASCII_hex ('b'));
		ubf_expect_bool_AND (b, 11 == ubf_value_of_ASCII_hex ('B'));
		ubf_expect_bool_AND (b, 12 == ubf_value_of_ASCII_hex ('c'));
		ubf_expect_bool_AND (b, 12 == ubf_value_of_ASCII_hex ('C'));
		ubf_expect_bool_AND (b, 13 == ubf_value_of_ASCII_hex ('d'));
		ubf_expect_bool_AND (b, 13 == ubf_value_of_ASCII_hex ('D'));
		ubf_expect_bool_AND (b, 14 == ubf_value_of_ASCII_hex ('e'));
		ubf_expect_bool_AND (b, 14 == ubf_value_of_ASCII_hex ('E'));
		ubf_expect_bool_AND (b, 15 == ubf_value_of_ASCII_hex ('f'));
		ubf_expect_bool_AND (b, 15 == ubf_value_of_ASCII_hex ('F'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex (' '));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex ('g'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex ('G'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex ('.'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex ('H'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex ('Z'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex ('\0'));

		ubf_expect_bool_AND (b,  0 == ubf_value_of_ASCII_hex_macro ('0'));
		ubf_expect_bool_AND (b,  1 == ubf_value_of_ASCII_hex_macro ('1'));
		ubf_expect_bool_AND (b,  2 == ubf_value_of_ASCII_hex_macro ('2'));
		ubf_expect_bool_AND (b,  3 == ubf_value_of_ASCII_hex_macro ('3'));
		ubf_expect_bool_AND (b,  4 == ubf_value_of_ASCII_hex_macro ('4'));
		ubf_expect_bool_AND (b,  5 == ubf_value_of_ASCII_hex_macro ('5'));
		ubf_expect_bool_AND (b,  6 == ubf_value_of_ASCII_hex_macro ('6'));
		ubf_expect_bool_AND (b,  7 == ubf_value_of_ASCII_hex_macro ('7'));
		ubf_expect_bool_AND (b,  8 == ubf_value_of_ASCII_hex_macro ('8'));
		ubf_expect_bool_AND (b,  9 == ubf_value_of_ASCII_hex_macro ('9'));
		ubf_expect_bool_AND (b, 10 == ubf_value_of_ASCII_hex_macro ('a'));
		ubf_expect_bool_AND (b, 10 == ubf_value_of_ASCII_hex_macro ('A'));
		ubf_expect_bool_AND (b, 11 == ubf_value_of_ASCII_hex_macro ('b'));
		ubf_expect_bool_AND (b, 11 == ubf_value_of_ASCII_hex_macro ('B'));
		ubf_expect_bool_AND (b, 12 == ubf_value_of_ASCII_hex_macro ('c'));
		ubf_expect_bool_AND (b, 12 == ubf_value_of_ASCII_hex_macro ('C'));
		ubf_expect_bool_AND (b, 13 == ubf_value_of_ASCII_hex_macro ('d'));
		ubf_expect_bool_AND (b, 13 == ubf_value_of_ASCII_hex_macro ('D'));
		ubf_expect_bool_AND (b, 14 == ubf_value_of_ASCII_hex_macro ('e'));
		ubf_expect_bool_AND (b, 14 == ubf_value_of_ASCII_hex_macro ('E'));
		ubf_expect_bool_AND (b, 15 == ubf_value_of_ASCII_hex_macro ('f'));
		ubf_expect_bool_AND (b, 15 == ubf_value_of_ASCII_hex_macro ('F'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro (' '));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro ('g'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro ('G'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro ('.'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro ('H'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro ('Z'));
		ubf_expect_bool_AND (b, UBF_INVALID_HEX_CHAR == ubf_value_of_ASCII_hex_macro ('\0'));

		// Let's do the same with the octal digits.
		ubf_expect_bool_AND (b,  0 == ubf_value_of_ASCII_oct ('0'));
		ubf_expect_bool_AND (b,  1 == ubf_value_of_ASCII_oct ('1'));
		ubf_expect_bool_AND (b,  2 == ubf_value_of_ASCII_oct ('2'));
		ubf_expect_bool_AND (b,  3 == ubf_value_of_ASCII_oct ('3'));
		ubf_expect_bool_AND (b,  4 == ubf_value_of_ASCII_oct ('4'));
		ubf_expect_bool_AND (b,  5 == ubf_value_of_ASCII_oct ('5'));
		ubf_expect_bool_AND (b,  6 == ubf_value_of_ASCII_oct ('6'));
		ubf_expect_bool_AND (b,  7 == ubf_value_of_ASCII_oct ('7'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct (' '));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('8'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('9'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('A'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('B'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('C'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('D'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('E'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('.'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('H'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('Z'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct ('\0'));
		
		ubf_expect_bool_AND (b,  0 == ubf_value_of_ASCII_oct_macro ('0'));
		ubf_expect_bool_AND (b,  1 == ubf_value_of_ASCII_oct_macro ('1'));
		ubf_expect_bool_AND (b,  2 == ubf_value_of_ASCII_oct_macro ('2'));
		ubf_expect_bool_AND (b,  3 == ubf_value_of_ASCII_oct_macro ('3'));
		ubf_expect_bool_AND (b,  4 == ubf_value_of_ASCII_oct_macro ('4'));
		ubf_expect_bool_AND (b,  5 == ubf_value_of_ASCII_oct_macro ('5'));
		ubf_expect_bool_AND (b,  6 == ubf_value_of_ASCII_oct_macro ('6'));
		ubf_expect_bool_AND (b,  7 == ubf_value_of_ASCII_oct_macro ('7'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro (' '));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('8'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('9'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('A'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('B'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('C'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('D'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('E'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('.'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('H'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('Z'));
		ubf_expect_bool_AND (b, UBF_INVALID_OCT_CHAR == ubf_value_of_ASCII_oct_macro ('\0'));
		
		// Binary.
		ubf_expect_bool_AND (b, 0 == ubf_value_of_ASCII_bin ('0'));
		ubf_expect_bool_AND (b, 1 == ubf_value_of_ASCII_bin ('1'));
		ubf_expect_bool_AND (b, UBF_INVALID_BIN_CHAR == ubf_value_of_ASCII_bin (' '));
		ubf_expect_bool_AND (b, UBF_INVALID_BIN_CHAR == ubf_value_of_ASCII_bin ('2'));
		ubf_expect_bool_AND (b, UBF_INVALID_BIN_CHAR == ubf_value_of_ASCII_bin ('\0'));
		
		strcpy (chT, "377");
		o = ubf_value_of_ASCII_oct (chT [0]);
		ubf_expect_bool_AND (b, 3 == o);
		st = ubf_octet_from_oct (&o, chT);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 255 == o);

		strcpy (chT, "400");
		o = ubf_value_of_ASCII_oct (chT [0]);
		ubf_expect_bool_AND (b, 4 == o);
		o = ubf_value_of_ASCII_oct (chT [1]);
		ubf_expect_bool_AND (b, 0 == o);
		st = ubf_octet_from_oct (&o, chT);
		ubf_expect_bool_AND (b, 2 == st);
		// 40o == 32d.
		ubf_expect_bool_AND (b, 32 == o);

		strcpy (chT, "401");
		o = ubf_value_of_ASCII_oct (chT [0]);
		ubf_expect_bool_AND (b, 4 == o);
		o = ubf_value_of_ASCII_oct (chT [1]);
		ubf_expect_bool_AND (b, 0 == o);
		o = ubf_value_of_ASCII_oct (chT [2]);
		ubf_expect_bool_AND (b, 1 == o);
		st = ubf_octet_from_oct (&o, chT);
		ubf_expect_bool_AND (b, 2 == st);
		// 40o == 32d. The "1" in "401" is already ignored due to octet boundary.
		ubf_expect_bool_AND (b, 32 == o);

		strcpy (chT, "477");
		o = ubf_value_of_ASCII_oct (chT [0]);
		ubf_expect_bool_AND (b, 4 == o);
		o = ubf_value_of_ASCII_oct (chT [1]);
		ubf_expect_bool_AND (b, 7 == o);
		o = ubf_value_of_ASCII_oct (chT [2]);
		ubf_expect_bool_AND (b, 7 == o);
		st = ubf_octet_from_oct (&o, chT);
		ubf_expect_bool_AND (b, 2 == st);
		// 47o == 39d.
		ubf_expect_bool_AND (b, 39 == o);

		strcpy (chT, "1110");
		o = ubf_value_of_ASCII_oct (chT [0]);
		ubf_expect_bool_AND (b, 1 == o);
		o = ubf_value_of_ASCII_oct (chT [1]);
		ubf_expect_bool_AND (b, 1 == o);
		o = ubf_value_of_ASCII_oct (chT [2]);
		ubf_expect_bool_AND (b, 1 == o);
		o = ubf_value_of_ASCII_oct (chT [3]);
		ubf_expect_bool_AND (b, 0 == o);
		st = ubf_octet_from_oct (&o, chT);
		ubf_expect_bool_AND (b, 3 == st);
		// 111o == 73d == 49h == "I".
		ubf_expect_bool_AND (b, 73 == o);
		
		st = ubf_octet_from_bin (&o, "0");
		ubf_expect_bool_AND (b, 1 == st);
		ubf_expect_bool_AND (b, 0 == o);
		st = ubf_octet_from_bin (&o, "1");
		ubf_expect_bool_AND (b, 1 == st);
		ubf_expect_bool_AND (b, 1 == o);
		st = ubf_octet_from_bin (&o, "01");
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 1 == o);
		st = ubf_octet_from_bin (&o, "10");
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 2 == o);
		st = ubf_octet_from_bin (&o, "11");
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 3 == o);
		st = ubf_octet_from_bin (&o, "100");
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 4 == o);
		st = ubf_octet_from_bin (&o, "101");
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 5 == o);
		st = ubf_octet_from_bin (&o, "110");
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 6 == o);
		st = ubf_octet_from_bin (&o, "111");
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 7 == o);
		st = ubf_octet_from_bin (&o, "1000");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 8 == o);
		st = ubf_octet_from_bin (&o, "1001");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 9 == o);
		st = ubf_octet_from_bin (&o, "1010");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 10 == o);
		st = ubf_octet_from_bin (&o, "1011");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 11 == o);
		st = ubf_octet_from_bin (&o, "1100");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 12 == o);
		st = ubf_octet_from_bin (&o, "1101");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 13 == o);
		st = ubf_octet_from_bin (&o, "1110");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 14 == o);
		st = ubf_octet_from_bin (&o, "1111");
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 15 == o);
		st = ubf_octet_from_bin (&o, "00000001");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 1 == o);
		st = ubf_octet_from_bin (&o, "000000001");				// Only 8 bits will be consumed.
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 0 == o);
		st = ubf_octet_from_bin (&o, "101010101");				// Only 8 bits will be consumed.
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 170 == o);
		st = ubf_octet_from_bin (&o, "00000010");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 2 == o);
		st = ubf_octet_from_bin (&o, "00000011");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 3 == o);
		st = ubf_octet_from_bin (&o, "00000100");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 4 == o);
		st = ubf_octet_from_bin (&o, "00010000");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 16 == o);
		st = ubf_octet_from_bin (&o, "00010001");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 17 == o);
		st = ubf_octet_from_bin (&o, "00100000");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 32 == o);
		st = ubf_octet_from_bin (&o, "00100001");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 33 == o);
		st = ubf_octet_from_bin (&o, "00100010");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 34 == o);
		st = ubf_octet_from_bin (&o, "00100011");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 35 == o);
		st = ubf_octet_from_bin (&o, "01000000");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 64 == o);
		st = ubf_octet_from_bin (&o, "10000000");
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, 128 == o);
		
		// UCS2UTF16bin_from_hex.
		uint16_t		bin [128];
		char			*hex;
		
		bool			b2;

		hex = "003100320033";
		ubf_expect_bool_AND (b, false == UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 0, &st));
		// Should come back false.
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 1, &st);
		ubf_expect_bool_AND (b, false == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 2, &st);
		ubf_expect_bool_AND (b, false == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 3, &st);
		ubf_expect_bool_AND (b, false == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 4, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 1 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 5, &st);
		ubf_expect_bool_AND (b, false == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 6, &st);
		ubf_expect_bool_AND (b, false == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 7, &st);
		ubf_expect_bool_AND (b, false == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 8, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 2 == st);
		b2 = UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 3 == st);
		b2 = UCS2UTF16bin_from_hex (bin, 0, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 0 == st);
		b2 = UCS2UTF16bin_from_hex (bin, 1, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 1 == st);
		ubf_expect_bool_AND (b, 0x31 == bin [0]);
		b2 = UCS2UTF16bin_from_hex (bin, 2, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 0x31 == bin [0]);
		ubf_expect_bool_AND (b, 0x32 == bin [1]);
		b2 = UCS2UTF16bin_from_hex (bin, 3, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 0x31 == bin [0]);
		ubf_expect_bool_AND (b, 0x32 == bin [1]);
		ubf_expect_bool_AND (b, 0x33 == bin [2]);
		b2 = UCS2UTF16bin_from_hex (bin, 4, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 0x31 == bin [0]);
		ubf_expect_bool_AND (b, 0x32 == bin [1]);
		ubf_expect_bool_AND (b, 0x33 == bin [2]);
		// "@AB";
		hex = "004000410042";
		b2 = UCS2UTF16bin_from_hex (bin, 4, hex, 12, &st);
		ubf_expect_bool_AND (b, true == b2);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 0x40 == bin [0]);
		ubf_expect_bool_AND (b, 0x41 == bin [1]);
		ubf_expect_bool_AND (b, 0x42 == bin [2]);
		
		// Tests for ubf_uint16_from_hex ().
		hex = "FFFF";
		uint16_t		ui16;
		uint32_t		ui32;
		uint64_t		ui64;
		
		ubf_expect_bool_AND (b, sizeof (uint16_t) == sizeof (wchar_t));
		st = ubf_uint16_from_hex (&ui16, hex);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 65535 == ui16);
		hex = "FF";
		st = ubf_uint16_from_hex (&ui16, hex);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 255 == ui16);
		hex = "10";
		st = ubf_uint16_from_hex (&ui16, hex);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 16 == ui16);
		hex = "100";
		st = ubf_uint16_from_hex (&ui16, hex);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 256 == ui16);
		hex = "FFF0";
		st = ubf_uint16_from_hex (&ui16, hex);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 65520 == ui16);
		hex = "";
		ui16 = 17;	// Should stay because no hex digit means the function should not
					//	change it.
		st = ubf_uint16_from_hex (&ui16, hex);
		ubf_expect_bool_AND (b, 0 == st);
		ubf_expect_bool_AND (b, 17 == ui16);
		
		unsigned char c;
		char ch [10];
		for (c = (unsigned char) '0'; c <= (unsigned char) '9'; c ++)
		{
			ch [0] = c;
			ch [1] = '\0';
			st = ubf_uint16_from_hex (&ui16, ch);
			ubf_expect_bool_AND (b, 1 == st);
			ubf_expect_bool_AND (b, (uint16_t) (c - (unsigned char) '0') == ui16);
		}
		for (c = (unsigned char) 'a'; c < (unsigned char) 'g'; c ++)
		{
			ch [0] = c;
			ch [1] = '\0';
			st = ubf_uint16_from_hex (&ui16, ch);
			ubf_expect_bool_AND (b, 1 == st);
			ubf_expect_bool_AND (b, (uint16_t) (10 + c - (unsigned char) 'a') == ui16);
		}
		for (c = (unsigned char) '0'; c <= (unsigned char) '9'; c ++)
		{
			ch [0] = c;
			ch [1] = '\0';
			st = ubf_uint32_from_hex (&ui32, ch);
			ubf_expect_bool_AND (b, 1 == st);
			ubf_expect_bool_AND (b, (uint32_t) (c - (unsigned char) '0') == ui32);
		}
		for (c = (unsigned char) 'a'; c < (unsigned char) 'g'; c ++)
		{
			ch [0] = c;
			ch [1] = '\0';
			st = ubf_uint64_from_hex (&ui64, ch);
			ubf_expect_bool_AND (b, 1 == st);
			ubf_expect_bool_AND (b, (uint64_t) (10 + (uint64_t) c - (unsigned char) 'a') == ui64);
		}
		
		hex = "FFFF";
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 65535 == ui32);
		hex = "FF";
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 255 == ui32);
		hex = "10";
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 16 == ui32);
		hex = "100";
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 256 == ui32);
		hex = "FFF0";
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 65520 == ui32);
		hex = "";
		ui32 = 17;	// Should stay because no hex digit means the function should not
					//	change it.
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 0 == st);
		ubf_expect_bool_AND (b, 17 == ui32);
		hex = "FFFFFFFF";
		st = ubf_uint32_from_hex (&ui32, hex);
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, UINT32_MAX == ui32);

		hex = "FFFF";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 65535 == ui64);
		hex = "FF";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 255 == ui64);
		hex = "10";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 2 == st);
		ubf_expect_bool_AND (b, 16 == ui64);
		hex = "100";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 3 == st);
		ubf_expect_bool_AND (b, 256 == ui64);
		hex = "FFF0";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 4 == st);
		ubf_expect_bool_AND (b, 65520 == ui64);
		hex = "";
		ui64 = 17;	// Should stay because no hex digit means the function should not
					//	change it.
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 0 == st);
		ubf_expect_bool_AND (b, 17 == ui64);
		hex = "FFFFFFFF";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 8 == st);
		ubf_expect_bool_AND (b, UINT32_MAX == ui64);
		hex = "FFFFFFFFFFFFFFFF";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 16 == st);
		ubf_expect_bool_AND (b, UINT64_MAX == ui64);
		hex = "FFFFFFFFFFFFFFF0";
		st = ubf_uint64_from_hex (&ui64, hex);
		ubf_expect_bool_AND (b, 16 == st);
		ubf_expect_bool_AND (b, UINT64_MAX - 15 == ui64);

		return b;
	}
#endif
