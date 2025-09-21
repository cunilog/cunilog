/****************************************************************************************

	File:		FileMembuf.h
	Why:		File functions for SMEMBUF structures.
	OS:			C99
	Author:		Thomas
	Created:	2025-09-18

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-09-18	Thomas			Created.

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

#ifndef U_FILEMEMBUF_H
#define U_FILEMEMBUF_H

#include <stdbool.h>

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

// This value is returned in case of an error.
#ifndef READFILESMEMBUF_ERROR
#define READFILESMEMBUF_ERROR			((size_t) -1)
#endif

// The maximum filesize that can be read from disk to memory with this module.
#ifndef READFILESMEMBUF_MAX_FSIZE
#define READFILESMEMBUF_MAX_FSIZE		(20 * 1024 * 1024)	// 20 MiB.
#endif

EXTERN_C_BEGIN

/*
	ReadFileSMEMBUF

	Reads the file named szFileName into the buffer of the SMEMBUF structure pmb points
	to. The SMEMBUF structure must have been initialised properly before this function
	is called.

	The buffer of the SMEMBUF structure pmb points to is NUL-terminated. In fact, the
	function writes two NUL octets to ensure it can also be used to read UTF-16 files.

	The function returns the amount of octets/bytes written to the buffer, not including
	the terminating NUL character.
*/
size_t ReadFileSMEMBUF (SMEMBUF *pmb, const char *szFileName)
;

/*
	test_FileMembuf

	Test function for the module.
	returns true on success, false otherwise.
*/
#ifdef FILEMEMBUF_BUILD_TEST_FNCT
	bool test_FileMembuf (void);
#else
	#define test_FileMembuf()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifdef U_FILEMEMBUF_H.
