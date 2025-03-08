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

EXTERN_C_BEGIN

/*
	SMEMBUFfromStr
	
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

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes, which is len on success,
	or 0 when the heap allocation fails.
*/
size_t SMEMBUFfromStr (SMEMBUF *pmb, const char *str, size_t len);
TYPEDEF_FNCT_PTR (size_t, SMEMBUFfromStr) (SMEMBUF *pmb, const char *str, size_t len);

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

EXTERN_C_END

#endif // STRMEMBUF_H
