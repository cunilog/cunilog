/****************************************************************************************

	File:		strintuint.c
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


	The functions ubf_itoa (), ubf_n_itoa10 (), ubf_str_from_uint16 (), ubf_str_from_int64 (),
	and ubf_str_from_uint64 () are (c) Lukas Chmela and derived from the versions at
	http://www.strudel.org.uk/itoa/ :

	* C++ version 0.4 char* style "itoa":
	* Written by Lukas Chmela
	* Released under GPLv3.

*/

#ifdef _WIN32
	#ifdef USE_WINDOWS_NATIVE_HEAP_FUNCTIONS
		#ifndef DONT_USE_UBF_TYPE_DEFINITIONS
		#define DONT_USE_UBF_TYPE_DEFINITIONS

			int our_own_inline_isdigit (int c)
			{
				return c >= '0' && c <= '9';
			}

			#ifndef isdigit
			#define isdigit(c)		our_own_inline_isdigit (c)
			#endif

		#endif
	#endif
#endif

#include <ctype.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strintuint.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfmem.h"
		#include "./Warnings.h"
		#include "./ubfdebug.h"
	#else
		#include "./../mem/ubfmem.h"
		#include "./../pre/Warnings.h"

			//#ifndef UBF_UBFDEBUG_USE_CURR_DIR - Obsolete/not used anymore.
		#include "./../dbg/ubfdebug.h"
	#endif
#endif

#ifdef UBF_BUILD_STRINTUINT_TEST
	#include <stdio.h>
#endif

#ifdef UBUILD_C_ITO_ALPHABET_IN_HERE
	char	c_ito_alphabet []	=
		"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
#endif

/*
	See http://www.strudel.org.uk/itoa/ .
	2018-04-09, Thomas.
*/
/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukas Chmela
 * Released under GPLv3.

 */
char* ubf_itoa (int value, char* result, int base)
{
	// check that the base is valid
	if (base < 2 || base > 36) { *result = ASCII_NUL; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = c_ito_alphabet [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = ASCII_NUL;
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

size_t ubf_n_itoa10 (int value, char* result)
{
	char* ptr	= result, *ptr1 = result, tmp_char;
	int			tmp_value;
	char		*r;

	do {
		tmp_value = value;
		value /= 10;
		*ptr++ = c_ito_alphabet [35 + (tmp_value - value * 10)];
	} while ( value );
	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	r = ptr;
	*ptr-- = ASCII_NUL;
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return ((size_t) (r - result));
}

DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR ()

char c_0_to_59_str0 [62][2] =
{
		"00", "01", "02", "03", "04", "05", "06", "07", "08", "09"
	,	"10", "11", "12", "13", "14", "15", "16", "17", "18", "19"
	,	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29"
	,	"30", "31", "32", "33", "34", "35", "36", "37", "38", "39"
	,	"40", "41", "42", "43", "44", "45", "46", "47", "48", "49"
	,	"50", "51", "52", "53", "54", "55", "56", "57", "58", "59"

	/*
		See https://en.cppreference.com/w/c/chrono/tm .
		"Range allows for a positive leap second. Two leap seconds in the same minute are
		not allowed (the C89 range 0..61 was a defect)."
	*/
	,	"60", "61"
};

DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR ()

#ifdef DEBUG
	void ubf_str0_from_59max (char *result, uint8_t ui59s)
	{
		ubf_assert (ui59s < 62);

		memcpy (result, c_0_to_59_str0 [ui59s], 2);
	}
#endif

#ifdef DEBUG
	void ubf_str0_from_59max_n (char *result, uint8_t ui59s)
	{
		ubf_assert (ui59s < 62);

		memcpy (result, c_0_to_59_str0 [ui59s], 2);
		result [2] = '\0';
	}
#endif

size_t ubf_str_from_uint8 (char *result, uint8_t ui8)
{
	uint16_t	t;
	size_t		s			= 1;
	char		*res		= result;
	
	memset (res, '0', 3);
	t = ui8;
	if (ui8 >= 100)
	{
		ui8 /= 100;
		*res++ = c_ito_alphabet [35 + ui8];
		t -= ui8 * 100;
		ui8 = t % 100;
		s = 3;
		if (ui8 >= 10)
		{
			ui8 /= 10;
			*res++ = c_ito_alphabet [35 + ui8];
			t -= ui8 * 10;
			ui8 = t % 10;
			if (ui8)
				*res++ = c_ito_alphabet [35 + ui8];
		} else
		if (ui8)
		{
			++ res;
			*res++ = c_ito_alphabet [35 + ui8];
		}
	} else
	if (ui8 >= 10)
	{
		ui8 /= 10;
		*res++ = c_ito_alphabet [35 + ui8];
		t -= ui8 * 10;
		ui8 = t % 10;
		s = 2;
		if (ui8)
			*res++ = c_ito_alphabet [35 + ui8];
	} else
	if (ui8)
		*res++ = c_ito_alphabet [35 + ui8];
	result [s] = ASCII_NUL;
	return s;
}

size_t ubf_str_from_uint16 (char *result, uint16_t ui16)
{
	char*		ptr			= result, *ptr1 = result, tmp_char;
	uint16_t	tmp_value;
	char		*r;

	do {
		tmp_value = ui16;
		ui16 /= 10;
		*ptr++ = c_ito_alphabet [35 + (tmp_value - ui16 * 10)];
	} while (ui16);
	r = ptr;
	*ptr-- = ASCII_NUL;
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return ((size_t) (r - result));
}

/*
	Based on
	https://github.com/bminor/newlib/blob/master/newlib/libc/stdlib/utoa.c .

	This version is ~ 10 % slower.
*/

static const char szdigits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

size_t ubf_str_from_uint16_2 (char *result, uint16_t ui16)
{

	int i, j;
	unsigned remainder;
	char c;
  
	/* Check base is supported. */
	/*
		Our base is always 10.
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}  
	*/

	/* Convert to string. Digits are in reverse order.  */
	i = 0;
	do 
	{
		remainder = ui16 % 10;
		result[i++] = szdigits[remainder];
		ui16 = ui16 /10;
	} while (ui16 != 0);  
	result[i] = '\0'; 
  
	size_t r = i;

	/* Reverse string.  */
	for (j = 0, i--; j < i; j++, i--)
	{
		c = result[j];
		result[j] = result[i];
		result[i] = c; 
	}       
  
  return r;
}

size_t ubf_str0_from_uint16 (char *result, size_t digits, uint16_t ui16)
{
	ubf_assert_non_0 (digits);

	char	cResult [UBF_UINT16_SIZE];
	size_t	st;

	st = ubf_str_from_uint16 (cResult, ui16);
	if (st < digits)
	{
		memset (result, '0', digits - st);
		memcpy (result + digits - st, cResult, st);
	} else
	if (st == digits)
	{	// No leading zeroes due to st == digits.
		memcpy (result, cResult, st);
	} else
	//if (st > digits)										// Only this option left.
	{
		memcpy (result, cResult + st - digits, digits);
		st = STR0_NOT_ENOUGH_DIGITS;
	}
	result [digits] = ASCII_NUL;
	return st;
}

size_t ubf_str_from_int64 (char *result, int64_t i64)
{
	char* ptr	= result, *ptr1 = result, tmp_char;
	int64_t		tmp_value;
	char		*r;

	do {
		tmp_value = i64;
		i64 /= 10;
		*ptr++ = c_ito_alphabet [35 + (tmp_value - i64 * 10)];
	} while ( i64 );
	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	r = ptr;
	*ptr-- = ASCII_NUL;
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return ((size_t) (r - result));
}

size_t ubf_str_from_uint64 (char *result, uint64_t ui64)
{
	char*		ptr			= result, *ptr1 = result, tmp_char;
	uint64_t	tmp_value;
	char		*r;

	do {
		tmp_value = ui64;
		ui64 /= 10;
		*ptr++ = c_ito_alphabet [35 + (tmp_value - ui64 * 10)];
	} while (ui64);
	r = ptr;
	*ptr-- = ASCII_NUL;
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return ((size_t) (r - result));
}

size_t ubf_str0_from_uint64 (char *result, size_t digits, uint64_t ui64)
{
	ubf_assert_non_0 (digits);

	char	cResult [UBF_UINT64_SIZE];
	size_t	st;
	
	st = ubf_str_from_uint64 (cResult, ui64);
	if (st < digits)
	{
		memset (result, '0', digits - st);
		memcpy (result + digits - st, cResult, st);
	} else
	if (st == digits)
	{	// No leading zeroes due to st == digits.
		memcpy (result, cResult, st);
	} else
	//if (st > digits)										// Only this option left.
	{
		memcpy (result, cResult + st - digits, digits);
		st = STR0_NOT_ENOUGH_DIGITS;
	}
	result [digits] = ASCII_NUL;
	return st;
}

size_t ubf_str__from_uint64 (char *result, size_t digits, uint64_t ui64)
{
	ubf_assert_non_0 (digits);

	char	cResult [UBF_UINT64_SIZE];
	size_t	st;
	
	st = ubf_str_from_uint64 (cResult, ui64);
	if (st < digits)
	{
		memset (result, ' ', digits - st);
		memcpy (result + digits - st, cResult, st);
	} else
	if (st == digits)
	{	// No leading zeroes due to st == digits.
		memcpy (result, cResult, st);
	} else
	//if (st > digits)										// Only this option left.
	{
		memcpy (result, cResult + st - digits, digits);
		st = STR0_NOT_ENOUGH_DIGITS;
	}
	result [digits] = ASCII_NUL;
	return st;
}

#ifdef UBF_BUILD_STR0_FROM_UINT64_TEST
	void ubf_test_str0_from_uint64 (void)
	{
		char		c [UBF_UINT64_LEN + 1];						// Needs room for a NUL.
		UBF_DEF_GUARD_VAR (v, "012345");
		uint64_t	u;
		size_t		s;
		
		// Check our definitions first.
		ubf_assert (UBF_UINT8_SIZE == UBF_UINT8_LEN + 1);
		ubf_assert (UBF_UINT16_SIZE == UBF_UINT16_LEN + 1);
		ubf_assert (UBF_UINT32_SIZE == UBF_UINT32_LEN + 1);
		ubf_assert (UBF_UINT64_SIZE == UBF_UINT64_LEN + 1);
		u = 0;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (1 == s);
		u = 9;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (1 == s);
		u = 10;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (2 == s);
		u = 100;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (3 == s);
		u = 999;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (3 == s);
		u = 9999;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (4 == s);
		u = 1000000;
		s = ubf_str_from_int64 (c, u);
		ubf_assert (7 == s);
		u = 0;
		s = ubf_str0_from_uint64 (c, 0, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (0 == s);
		//assert (false);
		u = 10;
		s = ubf_str0_from_uint64 (c, 2, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (2 == s);
		ubf_assert (!memcmp (c, "10", 3));
		u = 100;
		s = ubf_str0_from_uint64 (c, 3, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (3 == s);
		ubf_assert (!memcmp (c, "100", 4));
		u = 100;
		s = ubf_str0_from_uint64 (c, 5, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (3 == s);
		ubf_assert (!memcmp (c, "00100", 6));
		u = 99;
		s = ubf_str0_from_uint64 (c, 10, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (2 == s);
		ubf_assert (!memcmp (c, "0000000099", 11));
		u = 9999;
		s = ubf_str0_from_uint64 (c, UBF_UINT64_LEN, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (4 == s);
		ubf_assert (!memcmp (c, "00000000000000009999", 11));
		u = 9999;
		// Too short.
		s = ubf_str0_from_uint64 (c, 2, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (STR0_NOT_ENOUGH_DIGITS == s);
		//ubf_assert (!memcmp (c, "0000000099", 11));

		// The 16 bit version.
		s = ubf_str0_from_uint16 (c, 10, 3000);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_assert (4 == s);
		ubf_assert (!memcmp (c, "0000003000", 10));
	}
#endif

bool ubf_uint64_from_str (uint64_t *ui, const char *chStr)
{
	uint64_t			u				= 0;
	const unsigned char	*ch;
	unsigned char		c;

	ch = (const unsigned char *) chStr;
	if (ch)
	{
		c = *ch;
		if ('+' == c)
		{
			ch ++;
			c = *ch;
		}
		while (c)
		{
			if (!isdigit (c))
				break;
			c -= '0';
			if (u > UINT64_MAX / 10)
				return false;
			u *= 10;
			if (u > UINT64_MAX - c)
				return false;
			u += c;
			ch ++;
			c = *ch;
		}
	}
	if (ui)
		*ui = u;
	return true;
}

size_t ubf_uint64_from_str_n (uint64_t *ui, const char *chStr, size_t nLen, enum enUintFromStrN s)
{
	uint64_t			u				= 0;
	const unsigned char	*ch;
	unsigned char		c;
	size_t				r				= 0;

	ch = (const unsigned char *) chStr;
	if (ch)
	{
		c = *ch;
		if ('+' == c && enUintFromStrAllowPlus == s)
		{
			ch ++;
			c = *ch;
			++ r;
		}
		while (c && nLen)
		{
			if (!isdigit (c))
				break;
			c -= '0';
			if (u > UINT64_MAX / 10)
				return r;
			u *= 10;
			if (u > UINT64_MAX - c)
				return r;
			u += c;
			ch ++;
			c = *ch;
			++ r;
			-- nLen;
		}
	}
	if (ui)
		*ui = u;
	return r;
}

bool is_number_str_l (const char *str, size_t len)
{
	len = USE_STRLEN == len ? strlen (str) : len;

	for (size_t st = 0; st < len; ++ st)
	{
		if (!ubf_isdigit (str [st]))
			return false;
	}
	return true;
}

bool ubf_int64_from_str (int64_t *pi, const char *chStr)
{
	int64_t				i				= 0;
	const unsigned char	*ch;
	unsigned char		c;
	bool				bneg			= false;

	ch = (const unsigned char *) chStr;
	if (ch)
	{
		c = *ch;
		switch (c)
		{
		case '-':
			bneg = true;
			// Falls through. See
			//	https://developers.redhat.com/blog/2017/03/10/wimplicit-fallthrough-in-gcc-7/ .
			UBF_FALLTHROUGH_HINT
		case '+':
			++ ch;
			c = *ch;
			break;
		default:
			break;
		}
		while (c)
		{
			if (!isdigit (c))
				return false;
			c -= '0';
			if (bneg)
			{
				if (i < INT64_MIN / 10)
					return false;
				i *= 10;
				if (i < INT64_MIN + c)
					return false;
				i -= c;
			} else
			{
				if (i > INT64_MAX / 10)
					return false;
				i *= 10;
				if (i > INT64_MAX - c)
					return false;
				i += c;
			}
			ch ++;
			c = *ch;
		}
	}
	if (pi)
		*pi = i;
	return true;
}

size_t ubf_str_to_int64 (const char *chStr, int64_t *pi)
{
	int64_t				i				= 0;
	const unsigned char	*ch;
	unsigned char		c;
	bool				bneg			= false;
	//size_t				r				= 0;

	ch = (const unsigned char *) chStr;
	if (ch)
	{
		c = *ch;
		switch (c)
		{
		case '-':
			bneg = true;
			// Falls through. See
			//	https://developers.redhat.com/blog/2017/03/10/wimplicit-fallthrough-in-gcc-7/ .
			UBF_FALLTHROUGH_HINT
		case '+':
			ch ++;
			c = *ch;
			break;
		default:
			break;
		}
		while (c)
		{
			if (!isdigit (c))
				break;
			c -= '0';
			if (bneg)
			{
				if (i < INT64_MIN / 10)
					break;
				i *= 10;
				if (i < INT64_MIN + c)
					break;
				i -= c;
			} else
			{
				if (i > INT64_MAX / 10)
					break;
				i *= 10;
				if (i > INT64_MAX - c)
					break;
				i += c;
			}
			ch ++;
			//r ++;
			c = *ch;
		}
	}
	if (pi)
		*pi = i;
	return (size_t) (ch - (const unsigned char *) chStr);
}

bool ubf_uint16_from_str (uint16_t *pus, const char *chStr)
{
	uint64_t		ui;
	uint16_t		us;

	if (ubf_uint64_from_str (&ui, chStr))
	{
		if (ui > USHRT_MAX)
			return false;
		us = (uint16_t) (ui & USHRT_MAX);
		if (pus)
			*pus = us;
		return true;
	}
	return false;
}

/*
	This function takes 4 (!) times longer than ubf_str_from_uint64 (). Test code can be
	found below the function.
	
void ubf_strd_from_uint64 (char *chStr, uint64_t u64)
{
	// C99.
	ubf_assert (UBF_UINT64_STRLEN > 20);							// Just in case.
	snprintf (chStr, UBF_UINT64_STRLEN, "%"PRIu64, u64);
	ubf_assert ('\0' != chStr [0]);								// Just in case.
}

	// Speed test for the functions ubf_str_from_uint64 () and ubf_strd_from_uint64 ().
	ULONGLONG	ullStart;
	ULONGLONG	ullEnd;
	char szTimeSpan [128];
	uint64_t uTest = 2000000;
	char szUINT64 [1024];
	ubf_get_system_time_ULONGLONG (&ullStart);
	for (uint64_t u = uTest; u; u --)
	{
		ubf_strd_from_uint64 (szUINT64, u);
	}
	ubf_get_system_time_ULONGLONG (&ullEnd);
	GetReadableTimeSpan (szTimeSpan, 128, ullEnd - ullStart);
	ubf_debug_printf ("Function test ubf_strd_from_uint64 (): %s.", szTimeSpan);
	ubf_get_system_time_ULONGLONG (&ullStart);
	for (uint64_t u = uTest; u; u --)
	{
		ubf_str_from_uint64 (szUINT64, u);
	}
	ubf_get_system_time_ULONGLONG (&ullEnd);
	GetReadableTimeSpan (szTimeSpan, 128, ullEnd - ullStart);
	ubf_debug_printf ("Function test ubf_str_from_uint64 () : %s.", szTimeSpan);
	ubf_get_system_time_ULONGLONG (&ullStart);
	for (uint64_t u = uTest; u; u --)
	{
		ubf_strd_from_uint64 (szUINT64, u);
	}
	ubf_get_system_time_ULONGLONG (&ullEnd);
	GetReadableTimeSpan (szTimeSpan, 128, ullEnd - ullStart);
	ubf_debug_printf ("Function test ubf_strd_from_uint64 (): %s.", szTimeSpan);
	ubf_get_system_time_ULONGLONG (&ullStart);
	for (uint64_t u = uTest; u; u --)
	{
		ubf_str_from_uint64 (szUINT64, u);
	}
	ubf_get_system_time_ULONGLONG (&ullEnd);
	GetReadableTimeSpan (szTimeSpan, 128, ullEnd - ullStart);
	ubf_debug_printf ("Function test ubf_str_from_uint64 () : %s.", szTimeSpan);
*/

#ifdef UBF_BUILD_STRINTUINT_TEST
	bool ubf_test_str_from_uint8 (void)
	{
		char			res [UBF_UINT8_SIZE];
		char			ref [32];
		size_t			s;
		bool			b = true;
		unsigned int	u;
		
		s = ubf_str_from_uint8 (res, 100);
		s = ubf_str_from_uint8 (res, 200);

		for (u = 0; u < 256; ++u)
		{
			/* Used for debugging.
			if (10 == u)
				ASSERT (false);
			if (100 == u)
				ASSERT (false);
			if (110 == u)
				ASSERT (false);
			if (200 == u)
				ASSERT (false);
			*/
			snprintf (ref, 32, "%u", u);
			s = ubf_str_from_uint8 (res, (uint8_t) u);
			if (10 > u)
			{
				b &= 1 == s;
				ubf_assert (true == b);
			} else
			if (100 > u)
			{
				b &= 2 == s;
				ubf_assert (true == b);
			} else
			{
				b &= 3 == s;
				ubf_assert (true == b);
			}
			b &= !memcmp (res, ref, s + 1);
			ubf_assert (true == b);
		}
		return b;
	}

	bool ubf_test_str0 (void)
	{
		bool		b = true;
		char		c [UBF_UINT64_LEN + 1];						// Needs room for a NUL.
		UBF_DEF_GUARD_VAR (v, "012345");
		uint64_t	u;
		size_t		s;

		// Check our definitions first.
		ubf_assert (UBF_UINT8_SIZE == UBF_UINT8_LEN + 1);
		ubf_assert (UBF_UINT16_SIZE == UBF_UINT16_LEN + 1);
		ubf_assert (UBF_UINT32_SIZE == UBF_UINT32_LEN + 1);
		ubf_assert (UBF_UINT64_SIZE == UBF_UINT64_LEN + 1);
		u = 0;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 1 == s);
		b = 1 == s;
		u = 9;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 1 == s);
		b &= 1 == s;
		u = 10;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 2 == s);
		u = 100;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 3 == s);
		u = 999;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 3 == s);
		u = 9999;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 4 == s);
		u = 1000000;
		s = ubf_str_from_int64 (c, u);
		ubf_expect_bool_AND (b, 7 == s);
		u = 0;
		s = ubf_str0_from_uint64 (c, 1, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 1 == s);
		//assert (false);
		u = 10;
		s = ubf_str0_from_uint64 (c, 2, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 2 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "10", 3));
		u = 100;
		s = ubf_str0_from_uint64 (c, 3, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 3 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "100", 4));
		u = 100;
		s = ubf_str0_from_uint64 (c, 5, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 3 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "00100", 6));
		u = 99;
		s = ubf_str0_from_uint64 (c, 10, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 2 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "0000000099", 11));
		u = 9999;
		s = ubf_str0_from_uint64 (c, UBF_UINT64_LEN, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 4 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "00000000000000009999", 11));
		u = 9999;
		// Too short.
		s = ubf_str0_from_uint64 (c, 2, u);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, STR0_NOT_ENOUGH_DIGITS == s);
		//ubf_assert (!memcmp (c, "0000000099", 11));

		s = ubf_str0_from_uint64 (c, 10, 3000);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 4 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "0000003000", 11));

		s = ubf_str0_from_uint64 (c, 10, 200);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 3 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "0000000200", 11));

		s = ubf_str0_from_uint64 (c, 3, 555);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 3 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "555", 4));

		s = ubf_str0_from_uint64 (c, 2, 200);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, STR0_NOT_ENOUGH_DIGITS == s);
		ubf_expect_bool_AND (b, !memcmp (c, "00", 3));

		s = ubf_str0_from_uint64 (c, 3, 1999);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, STR0_NOT_ENOUGH_DIGITS == s);
		ubf_expect_bool_AND (b, !memcmp (c, "999", 3));

		// The 16 bit version.
		s = ubf_str0_from_uint16 (c, 10, 3000);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 4 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "0000003000", 11));

		s = ubf_str0_from_uint16 (c, 10, 200);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 3 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "0000000200", 11));

		s = ubf_str0_from_uint16 (c, 3, 555);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, 3 == s);
		ubf_expect_bool_AND (b, !memcmp (c, "555", 4));

		s = ubf_str0_from_uint16 (c, 2, 200);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, STR0_NOT_ENOUGH_DIGITS == s);
		ubf_expect_bool_AND (b, !memcmp (c, "00", 3));

		s = ubf_str0_from_uint16 (c, 3, 1999);
		UBF_CHK_GUARD_VAR (v, "012345");
		ubf_expect_bool_AND (b, STR0_NOT_ENOUGH_DIGITS == s);
		ubf_expect_bool_AND (b, !memcmp (c, "999", 3));

		// Min.
		ubf_str0_from_59max (c, 0);
		ubf_expect_bool_AND (b, !memcmp (c, "00", 2));
		ubf_str0_from_59max (c, 61);
		ubf_expect_bool_AND (b, !memcmp (c, "61", 2));
		// NUL-terminated.
		ubf_str0_from_59max_n (c, 0);
		ubf_expect_bool_AND (b, !memcmp (c, "00", 3));
		// Max.
		ubf_str0_from_59max_n (c, 61);
		ubf_expect_bool_AND (b, !memcmp (c, "61", 3));

		ubf_expect_bool_AND (b, is_number_str_l ("0", 1));
		ubf_expect_bool_AND (b, is_number_str_l ("1", 1));
		ubf_expect_bool_AND (b, is_number_str_l ("2", 1));
		ubf_expect_bool_AND (b, is_number_str_l ("9", 1));
		ubf_expect_bool_AND (b, is_number_str_l ("10", 2));
		ubf_expect_bool_AND (b, !is_number_str_l ("abcd", 4));
		ubf_expect_bool_AND (b, is_number_str_l ("000000000000000000000000000000000000000000000000000000000000", USE_STRLEN));
		ubf_expect_bool_AND (b, is_number_str_l ("111111111111111111111111111111111111111111111111111111111111", USE_STRLEN));
		ubf_expect_bool_AND (b, is_number_str_l ("999999999999999999999999999999999999999999999999999999999999", USE_STRLEN));
		ubf_expect_bool_AND (b, is_number_str_l ("1234abc", 4));
		ubf_expect_bool_AND (b, !is_number_str_l ("1234abc", 5));

		char sz [256];
		size_t st1 = ubf_str_from_uint64 (sz, 10);
		ubf_expect_bool_AND (b, 2 == st1);
		ubf_expect_bool_AND (b, !memcmp ("10", sz, 3));
		st1 = ubf_str_from_uint64 (sz, 0);
		ubf_expect_bool_AND (b, 1 == st1);
		ubf_expect_bool_AND (b, !memcmp ("0", sz, 2));
		st1 = ubf_str_from_uint64 (sz, 7842);
		ubf_expect_bool_AND (b, 4 == st1);
		ubf_expect_bool_AND (b, !memcmp ("7842", sz, 5));

		return b;
	}

	bool Test_strintuint (void)
	{
		bool b = ubf_test_str_from_uint8 ();
		ubf_assert_true (b);
		b &= ubf_test_str0 ();
		return b;
	}
#endif

