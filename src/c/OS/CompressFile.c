/****************************************************************************************

	File:		CompressFile.c
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./CompressFile.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./ubfdebug.h"
		#include "./platform.h"
		#include "./unref.h"

	#else

		#include "./../dbg/ubfdebug.h"
		#include "./../pre/platform.h"
		#include "./../pre/unref.h"

	#endif

#endif

#ifdef DEBUG
	enfilecompressresult IsFileCompressedByName (const char *szFilename)
	{
		#if defined (OS_IS_WINDOWS)

			enfilecompressresult r = IsFileNTFSCompressedByName (szFilename);
			ubf_assert (fscompress_compressed	== ntfscompress_compressed);
			ubf_assert (fscompress_uncompressed	== ntfscompress_uncompressed);
			ubf_assert (fscompress_error		== ntfscompress_error);
			return r;

		#elif defined (OS_IS_LINUX)

			UNUSED (szFilename);
			return fscompress_error;
			
		#endif

	}
#endif

bool FScompressFileByName (const char *szFilename)
{
	#if defined (OS_IS_WINDOWS)

		return CompressFileNTFS_U8 (szFilename);

	#elif defined (OS_IS_LINUX)
	
		UNUSED (szFilename);
		return false;
		
	#endif
}
