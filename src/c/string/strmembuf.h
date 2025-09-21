/****************************************************************************************

	File:		strmembuf.h
	Why:		String helper functions for SMEMBUF structures.
	OS:			C99
	Author:		Thomas
	Created:	2023-05-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-25	Thomas			Created.

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

#ifndef STRMEMBUF_H
#define STRMEMBUF_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./membuf.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../mem/membuf.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef STRMEMBUF_DEFAULT_ALIGNMENT
#define STRMEMBUF_DEFAULT_ALIGNMENT		(16)
#endif

EXTERN_C_BEGIN

/*
	SMEMBUFfromStrReserveBytes
	
	Duplicates str and fills the SMEMBUF structure pmb points to accordingly.
	If len is (size_t) -1, the function strlen () is used to obtain the length of str.
	The macro USE_STRLEN is defined as ((size_t) -1).
	The buffer the function allocates is len + reserve octets (bytes).
	The string in the buffer is always NUL-terminated.

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, which is len on success, or 0 when the heap allocation fails. The NUL
	terminator the function always writes is not included in the return value.
*/
size_t SMEMBUFfromStrReserveBytes (SMEMBUF *pmb, const char *str, size_t len, size_t reserve)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFfromStrReserveBytes) (SMEMBUF *pmb, const char *str, size_t len, size_t reserve)
;

/*
	SMEMBUFfromStr

	Duplicates str and fills the SMEMBUF structure pmb points to accordingly.
	If len is USE_STRLEN the function calls strlen () to obtain the string's length.
	A NUL terminator is written at the end of the buffer.

	If str is NULL, len must be 0. If len is 0, the function writes out a NUL-terminator
	only

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes, which is len on success,
	or 0 when the heap allocation fails.
*/
size_t SMEMBUFfromStr (SMEMBUF *pmb, const char *str, size_t len);
TYPEDEF_FNCT_PTR (size_t, SMEMBUFfromStr) (SMEMBUF *pmb, const char *str, size_t len);

/*
	SMEMBUFfromStrFmt_va

	Variadic version of SMEMBUFfromStr () that expects a va_list argument.

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes. It returns 0 when the
	heap allocation fails.
*/
size_t SMEMBUFfromStrFmt_va (SMEMBUF *pmb, const char *fmt, va_list ap)
;

/*
	SMEMBUFfromStrFmt

	Variadic version of SMEMBUFfromStr ().

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes. It returns 0 when the
	heap allocation fails.
*/
size_t SMEMBUFfromStrFmt (SMEMBUF *pmb, const char *fmt, ...)
;

/*
	SMEMBUFstrFromUINT64
	
	Converts the value of ui to a string and stores the result in the buffer of pmb.
	The string is NUL-terminated.
	
	The function returns the amount of octets/bytes written to the buffer of the SMEMBUF
	structure, not counting the NUL-terminator.
*/
size_t SMEMBUFstrFromUINT64 (SMEMBUF *pmb, uint64_t ui)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrFromUINT64) (SMEMBUF *pmb, uint64_t ui)
;

/*
	SMEMBUFstrconcatReserve

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the string str with a length of lenstr, storing the result in the SMEMBUF
	structure's buffer. Both length parameters, len and lenstr, can be USE_STRLEN. If precise
	lengths are given, the strings do not need to be NUL-terminated.
	
	If str is NULL, the parameter lenstr is ignored and the buffer of the SMEMBUF structure
	is not changed, i.e. if str is NULL or lenstr is 0, the function returns len without
	touching the buffer.

	The resulting string in the buffer of pmb is NUL-terminated.

	If the buffer of pmb needs reallocating, the buffer is made big enough to additionally
	hold at least reserve octets. Set reserve to 0 if no additional buffer space is needed.
	If the buffer of pmb is already big enough to hold the original string plus str plus
	a NUL terminator, its size is not changed and the parameter reserve ignored.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
size_t SMEMBUFstrconcatReserve (SMEMBUF *pmb, size_t len, char *str, size_t lenstr, size_t reserve)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcatReserve) (SMEMBUF *pmb, size_t len, char *str, size_t lenstr, size_t reserve);

/*
	SMEMBUFstrconcat

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the string str with a length of lenstr, storing the result in the SMEMBUF
	structure's buffer. Both length parameters, len and lenstr, can be USE_STRLEN. If precise
	lengths are given, the strings do not need to be NUL-terminated.
	
	If str is NULL, the parameter lenstr is ignored and the buffer of the SMEMBUF structure
	is not changed, i.e. if str is NULL or lenstr is 0, the function returns len without
	touching the buffer.

	The resulting string in the buffer of pmb is NUL-terminated.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
size_t SMEMBUFstrconcat (SMEMBUF *pmb, size_t len, char *str, size_t lenstr)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcat) (SMEMBUF *pmb, size_t len, char *str, size_t lenstr);

/*
	SMEMBUFstrconcatW

	This function is only available on Windows.

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the Windows UTF-16 string wstr with a length of lenwstr, storing the result
	in the SMEMBUF structure's buffer. Before the concatenation, wstr is converted to UTF-8.
	Both length parameters, len and lenwstr, can be USE_STRLEN. If precise lengths are given,
	the strings do not need to be NUL-terminated. The length parameter lenwstr is the length
	of wstr in 16-bit words, not octets/bytes.

	The resulting string in the buffer of pmb is NUL-terminated.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
#ifdef PLATFORM_IS_WINDOWS
	size_t SMEMBUFstrconcatW (SMEMBUF *pmb, size_t len, wchar_t *wstr, size_t lenwstr);
	TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcatW)
		(SMEMBUF *pmb, size_t len, wchar_t *wstr, size_t lenwstr);
#endif

/*
	SMEMBUFstrconcatpaths

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the string strPath with a length of lenPath, storing the result in the SMEMBUF
	structure's buffer. Both length parameters, len and lenPath, can be USE_STRLEN. If precise
	lengths are given, the strings do not need to be NUL-terminated.
	
	The function is identical to SMEMBUFstrconcat (), but assumes that both strings are either
	directories/paths or that the buffer of the SMEMBUF structure contains a path/directory
	and strPath is a filename. It concatenates the paths or path and filename correctly by
	removing/ignoring excess forward or backward slashes (path separators) at the end of
	the structure's buffer and from the start of strPath. Only single separators are removed.

	The function does not distinguish between POSIX and Windows path separators. Forward and
	backward slashes are treated identically, but if a directory separator is added by the
	function, it will be the correct directory separator for the current platform.

	The buffer of the SMEMBUF structure takes precedence over strPath, meaning that if the
	buffer does not end with a directory separator, one is appended. If strPath starts with
	a directory separator, it is removed. This may lead to a different separator being
	inserted than the one strPath originally contained, as the function always inserts the
	correct separator for the current platform, which is a forward slash ("/") on POSIX and a
	backslash ("\") on Windows.

	If the buffer of pmb is empty, strPath is copied unchanged, ignoring any slash/backslash
	it may contain. If lenPath is 0, or is deduced to be 0 via a call to strlen (), len is
	returned and the buffer not changed.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
size_t SMEMBUFstrconcatpaths (SMEMBUF *pmb, size_t len, char *strPath, size_t lenPath)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcatpaths) (SMEMBUF *pmb, size_t len, char *strPath, size_t lenPath);

/*
	SMEMBUFstrStartsWithStr
	SMEMBUFstrEndsWithStr

	The functions return true if the buffer of the SMEMBUF structure pmb points to starts
	with the string str of length lenStr. If len or lenStr is USE_STRLEN, the functions call
	strlen () to obtain the value in question.
*/
bool SMEMBUFstrStartsWithStr (SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);
bool SMEMBUFstrEndsWithStr (SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);
TYPEDEF_FNCT_PTR (bool, SMEMBUFstrStartsWithStr)
	(SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);
TYPEDEF_FNCT_PTR (bool, SMEMBUFstrEndsWithStr)
	(SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);

/*
	test_strmembuf

	Test function for the module.
	returns true on success, false otherwise.
*/
#ifdef STRMEMBUF_BUILD_TEST_FNCT
	bool test_strmembuf (void);
#else
	#define test_strmembuf()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifdef STRMEMBUF_H.
