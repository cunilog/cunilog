/****************************************************************************************

	File		CompressNTFS_U8.h
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

#ifndef COMPRESSNTFS_U8
#define COMPRESSNTFS_U8

#ifdef _WIN32

#include <stdbool.h>
#include <Windows.h>

#ifdef	__cplusplus
	extern "C"	{
#endif

/*
	CompressFileNTFS_U8ExLong
	
	Compresses or uncompresses the file in chFileName. The function calls
	CreateFileU8long () to open the file, meaning it supports very long
	paths. Filename restrictions apply, for instance path navigators ("../")
	are not supported by this function. See
	https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
	for more information. Use CompressFileNTFS_U8Ex () to support path
	navigators.
	
	usState can be:
	0 = COMPRESSION_FORMAT_NONE
	1 = COMPRESSION_FORMAT_DEFAULT
	2 = COMPRESSION_FORMAT_LZNT1
	
	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8ExLong (const char *chFileName, USHORT usState);

/*
	CompressFileNTFS_U8Ex
	
	Compresses or uncompresses the file in chFileName. The function calls
	CreateFileU8 () to open the file, meaning it does not support very long
	paths but the filename can contain path navigators ("../".
	
	usState can be:
	0 = COMPRESSION_FORMAT_NONE
	1 = COMPRESSION_FORMAT_DEFAULT
	2 = COMPRESSION_FORMAT_LZNT1
	
	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8Ex (const char *chFileName, USHORT usState);

/*
	CompressFileNTFS_U8long
	
	Compresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8ExLong ().

	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8long (const char *chFileName);

/*
	CompressFileNTFS_U8
	
	Compresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8Ex ().

	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8 (const char *chFileName);

/*
	UnCompressFileNTFS_U8long
	
	Uncompresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8ExLong ().

	Returns true on success, false otherwise.
*/
bool UnCompressFileNTFS_U8long (const char *chFileName);

/*
	UnCompressFileNTFS_U8
	
	Uncompresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8Ex ().

	Returns true on success, false otherwise.
*/
bool UnCompressFileNTFS_U8 (const char *chFileName);

/*
	enntfscompressresult

	Return values for the compression check functions.
*/
enum enntfscompressresult
{
	ntfscompress_compressed,
	ntfscompress_uncompressed,
	ntfscompress_error
};
typedef enum enntfscompressresult enntfscompressresult;

/*
	IsFileNTFSCompressedByName
	IsFileNTFSCompressedByHandle

	The functions return ntfscompress_compressed if the given file is NTFS compressed. They
	return ntfscompress_uncompressed if the file is not compressed.
	
	On error, for instance if the file doesn't exist, the functions return ntfscompress_error.
	You can call GetLastError () to obtain more details about why the functions failed.
*/
enntfscompressresult IsFileNTFSCompressedByName (const char *szFileName);
enntfscompressresult IsFileNTFSCompressedByHandle (HANDLE hFile);

#ifdef	__cplusplus
				}
#endif

#endif															// Of #ifdef _WIN32

#endif															// Of #ifndef COMPRESSNTFS_U8.
