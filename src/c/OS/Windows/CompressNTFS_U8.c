/****************************************************************************************

	File		CompressNTFS_U8.c
	Why:		Performs NTFS compression.
	OS:			Windows
	Created:	2020-12-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-06	Thomas			Created.

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

#ifdef _WIN32

#include <windows.h>
#ifdef _MSC_VER
	#include <crtdbg.h>
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./CompressNTFS_U8.h"
	#include "./WinAPI_U8.h"

#endif

#ifndef UNICODE
	#error This module can only be used in Windows applications compiled for unicode
#endif

static bool DeviceIoControlNTFScompression (HANDLE hFile, USHORT usState)
{
	DWORD		dwBytesReturned;
	bool		bResult;

	bResult = DeviceIoControl	(
					hFile,						// Handle to file or directory
					FSCTL_SET_COMPRESSION,		// dwIoControlCode
					&usState,					// Input buffer
					sizeof (USHORT),			// Size of input buffer
					NULL,						// lpOutBuffer
					0,							// nOutBufferSize
					&dwBytesReturned,			// Number of bytes returned
					NULL						// OVERLAPPED structure
								);
	return bResult;
}

bool CompressFileNTFS_U8ExLong (const char *chFileName, USHORT usState)
{	// Compress or uncompress theFossil_Commit given file.
	//
	//	usState can be:
	//	0 = COMPRESSION_FORMAT_NONE
	//	1 = COMPRESSION_FORMAT_DEFAULT
	//	2 = COMPRESSION_FORMAT_LZNT1
	//
	//  Returns TRUE if successful, FALSE if an error occurred.
	//

	HANDLE		hFile;
	bool		bResult;

	hFile = CreateFileU8long	(
					chFileName,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_DELETE + FILE_SHARE_READ + FILE_SHARE_WRITE,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL + FILE_FLAG_SEQUENTIAL_SCAN,
					NULL		
								);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwErr = GetLastError ();
		UNREFERENCED_PARAMETER (dwErr);
		return false;
	}
	bResult = DeviceIoControlNTFScompression (hFile, usState);
	if (!CloseHandle (hFile))
		return false;
	return (bResult);
}

bool CompressFileNTFS_U8Ex (const char *chFileName, USHORT usState)
{	// Compress or uncompress the given file.
	//
	//	usState can be:
	//	0 = COMPRESSION_FORMAT_NONE
	//	1 = COMPRESSION_FORMAT_DEFAULT
	//	2 = COMPRESSION_FORMAT_LZNT1
	//
	//  Returns TRUE if successful, FALSE if an error occurred.
	//

	HANDLE		hFile;
	bool		bResult;

	hFile = CreateFileU8		(
					chFileName,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_DELETE + FILE_SHARE_READ + FILE_SHARE_WRITE,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL + FILE_FLAG_SEQUENTIAL_SCAN,
					NULL		
								);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwErr = GetLastError ();
		UNREFERENCED_PARAMETER (dwErr);
		return false;
	}
	bResult = DeviceIoControlNTFScompression (hFile, usState);
	if (!CloseHandle (hFile))
		return false;
	return (bResult);
}

bool CompressFileNTFS_U8long (const char *chFileName)
{
	return (CompressFileNTFS_U8ExLong (chFileName, COMPRESSION_FORMAT_DEFAULT));
}

bool CompressFileNTFS_U8 (const char *chFileName)
{
	return (CompressFileNTFS_U8Ex (chFileName, COMPRESSION_FORMAT_DEFAULT));
}

bool UnCompressFileNTFS_U8long (const char *chFileName)
{
	return (CompressFileNTFS_U8ExLong (chFileName, COMPRESSION_FORMAT_NONE));
}

bool UnCompressFileNTFS_U8 (const char *chFileName)
{
	return (CompressFileNTFS_U8Ex (chFileName, COMPRESSION_FORMAT_NONE));
}

enntfscompressresult IsFileNTFSCompressedByName (const char *szFileName)
{
	DWORD dwAtts = GetFileAttributesU8 (szFileName);
	
	if (INVALID_FILE_ATTRIBUTES != dwAtts)
	{
		return (dwAtts & FILE_ATTRIBUTE_COMPRESSED) ? ntfscompress_compressed : ntfscompress_uncompressed;
	}
	return ntfscompress_error;
}

enntfscompressresult IsFileNTFSCompressedByHandle (HANDLE hFile)
{
	BY_HANDLE_FILE_INFORMATION	bh;

	if (GetFileInformationByHandle (hFile, &bh))
	{
		return (bh.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) ? ntfscompress_compressed : ntfscompress_uncompressed;
	}
	return ntfscompress_error;
}

#endif														// Of #ifdef _WIN32.
