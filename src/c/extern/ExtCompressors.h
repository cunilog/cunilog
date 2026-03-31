/****************************************************************************************

	File:		ExtCompressors.h
	Why:		Interface module/unit for external compressors.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-01	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This module is an interface for external compressors/external compression libraries.
	This implies that when this module is used, the application may need to be linked to
	additional external libraries.
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024-2026 Thomas

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

#ifndef U_EXTCOMPRESSORS_H
#define U_EXTCOMPRESSORS_H

// Quick test.
#ifndef EXTCOMPRESSORS_BUILD_TEST_FNCT
//#define EXTCOMPRESSORS_BUILD_TEST_FNCT
#endif

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

// Buffer sizes are physical sector sizes multiplied by this constant.
#ifndef EXTCOMPRESSORS_DEF_SECT_FACTOR
#define EXTCOMPRESSORS_DEF_SECT_FACTOR		(2048)
#endif

// The default sector size if no other value could be retrieved.
#ifndef EXTCOMPRESSORS_DEF_SECT_SIZE
#define EXTCOMPRESSORS_DEF_SECT_SIZE		(512)
#endif

/*
	Memory alignments. Use 16 octets/bytes for 64 bit platforms.
	Use CUNILOG_DEFAULT_ALIGNMENT for structures and CUNILOG_POINTER_ALIGNMENT
	for pointers.
	Also, see https://learn.microsoft.com/en-us/cpp/build/reference/zp-struct-member-alignment?view=msvc-170 .
*/
#if defined (_M_X64)
	#ifndef CUNILOG_DEFAULT_ALIGNMENT
	#define CUNILOG_DEFAULT_ALIGNMENT	(16)
	#endif
#else
	#ifndef CUNILOG_DEFAULT_ALIGNMENT
	#define CUNILOG_DEFAULT_ALIGNMENT	(8)
	#endif
#endif
#if defined (_M_X64)
	#ifndef CUNILOG_POINTER_ALIGNMENT
	#define CUNILOG_POINTER_ALIGNMENT	(8)
	#endif
#else
	#ifndef CUNILOG_POINTER_ALIGNMENT
	#define CUNILOG_POINTER_ALIGNMENT	(8)
	#endif
#endif

EXTERN_C_BEGIN

enum encprrmve
{
	encompress_dont_delete_source,							// Don't touche the source file.
	encompress_delete_source_file							// Delete the source file after
															//	compressing/deflating.
};

/*
	extCompressFile

	Compresses (deflates) the uncompressed file szInflatedFile. For details on the
	algorithm, see https://deepwiki.com/madler/zlib/4.1-deflate-algorithm .

	The parameter lnInflatedFile specifies the length of szInflatedFile.
	If lnInflatedFile is USE_STRLEN, the function obtrains the length of
	the file name via a call to strlen (szInflatedFile).

	The parameter pphysicalSectorSize is a pointer to a uint32_t that is set to the
	physical sector size of the volume the log file as well as the deflated/compressed
	gzip file reside. If this pointer is NULL, or if it points to a value of 0, the
	function obtains the physical sector size implicitely. If pphysicalSectorSize is not
	NULL but points to a value of 0, the function obtains the physical sector size and
	stores it at the address pphysicalSectorSize points to. The caller can then re-use
	the pointer pphysicalSectorSize for consecutive calls so that the function does not
	have to obtain the physical sector size via expensive Windows API calls.

	The parameter compressOrDelete specifies whether the source file should be removed
	after it has been deflated/compressed or not. Removing the file offers a "move-into-
	the-gzip" semantic.

	The function returns true on success, false otherwise.
*/
bool extCompressFile	(
		const char		*szInflatedFile,
		size_t			lnInflatedFile,
		uint32_t		*pphysicalSectorSize,
		enum encprrmve	compressOrDelete
						)
;

/*
	testExtCompressors

	Test function.
*/
#ifdef EXTCOMPRESSORS_BUILD_TEST_FNCT
	bool testExtCompressors (void);
#else
	#define testExtCompressors()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_EXTCOMPRESSORS_H.
