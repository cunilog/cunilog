/****************************************************************************************

	File:		CompressFile.h
	Why:		Module to compress a file on different platforms.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-10-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-17	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#ifndef U_COMPRESS_FILE_H
#define U_COMPRESS_FILE_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./platform.h"
		#include "./externC.h"

		#if defined (OS_IS_WINDOWS)
			#include "./CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)
		
		#endif

	#else

		#include "./../pre/platform.h"
		#include "./../pre/externC.h"

		#if defined (OS_IS_WINDOWS)
			#include "./Windows/CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)
		
		#endif

	#endif

#endif

EXTERN_C_BEGIN

/*
	enfilecompressresult

	Return values for the compression check functions.
*/
enum enfilecompressresult
{
	fscompress_compressed,
	fscompress_uncompressed,
	fscompress_error
};
typedef enum enfilecompressresult enfilecompressresult;

/*
	IsFileCompressedByName

	Returns true if the file is already compressed, false if it isn't.
*/
#ifdef DEBUG
	enfilecompressresult IsFileCompressedByName (const char *szFilename);
#else
	#if defined (OS_IS_WINDOWS)
		#define IsFileCompressedByName(fn)				\
			IsFileNTFSCompressedByName (fn)
	#elif defined (OS_IS_LINUX)
		#define IsFileCompressedByName(fn)				\
			(false)
	#endif
#endif

/*
	FScompressFileByName

	Compresses the file szFilename and returns true on success, false otherwise.
*/
bool FScompressFileByName (const char *szFilename)
;

EXTERN_C_END

#endif														// Of #ifndef U_COMPRESS_FILE_H.
