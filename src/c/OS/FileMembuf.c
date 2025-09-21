/****************************************************************************************

	File:		FileMembuf.c
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

#include <stdio.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./FileMembuf.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
		#include "./ubfdebug.h"
		#include "./membuf.h"
		#include "./ubfmem.h"
		#include "./strisabsolutepath.h"
		#include "./strfilesys.h"
		#ifdef PLATFORM_IS_WINDOWS
			#include "./WinAPI_U8.h"
		#endif
		#include "./unref.h"
	#else
		#include "./../pre/platform.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/membuf.h"
		#include "./../mem/ubfmem.h"
		#include "./../string/strisabsolutepath.h"
		#include "./../string/strfilesys.h"
		#ifdef PLATFORM_IS_WINDOWS
			#include "./../OS/Windows/WinAPI_U8.h"
		#endif
		#include "./../pre/unref.h"
	#endif

#endif

static inline HANDLE CreateFileWin (const char *szFileName)
{
	HANDLE h;
	if (is_absolute_path (szFileName))
	{
		h = CreateFileU8long	(
						szFileName,
						GENERIC_READ,
						FILE_SHARE_DELETE + FILE_SHARE_READ + FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL + FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
								);
	} else
	{
		h = CreateFileU8		(
						szFileName,
						GENERIC_READ,
						FILE_SHARE_DELETE + FILE_SHARE_READ + FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL + FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
								);
	}
	return h;
}

size_t ReadFileSMEMBUF (SMEMBUF *pmb, const char *szFileName)
{
	ubf_assert_non_NULL (pmb);
	ubf_assert_non_NULL (szFileName);

	size_t stRet = READFILESMEMBUF_ERROR;

	#if defined (PLATFORM_IS_WINDOWS)

		HANDLE h = CreateFileWin (szFileName);
		if (INVALID_HANDLE_VALUE == h)
			return stRet;

		LARGE_INTEGER s;
		if (GetFileSizeEx (h, &s))
		{
			if (READFILESMEMBUF_MAX_FSIZE >= s.QuadPart)
			{
				if (growToSizeSMEMBUF (pmb, ((size_t) s.QuadPart) + 2))
				{
					DWORD dwRead;
					if (ReadFile (h, pmb->buf.pch, (DWORD) s.QuadPart, &dwRead, NULL) && s.QuadPart == dwRead)
					{
						pmb->buf.pch [s.QuadPart]		= ASCII_NUL;
						pmb->buf.pch [s.QuadPart + 1]	= ASCII_NUL;
						stRet = (size_t) s.QuadPart;
					}
				}
			}
		}
		CloseHandle (h);
		return stRet;

	#elif defined (PLATORM_IS_POSIX)

		FILE *h = fopen (szFileName, "rb");
		if (NULL == h)
			return stRet;
		fseek (h, 0L, SEEK_END);
		long s = ftell(fp);
		if (READFILESMEMBUF_MAX_FSIZE >= s)
		{
			if (growToSizeSMEMBUF (pmb, s + 2))
			{
				size_t stRead = fread (1, s, pmb->buf.pch, h);
				if (stRead == s)
				{
					pmb->buf.pch [s]		= ASCII_NUL;
					pmb->buf.pch [s + 1]	= ASCII_NUL;
					stRet = s;
				}
			}
		}
		fclose (h);
		return stRet;
	#endif
}

#ifdef FILEMEMBUF_BUILD_TEST_FNCT
	bool test_FileMembuf (void)
	{
		bool b = true;

		SMEMBUF smb	= SMEMBUF_INITIALISER;
		// We expect this to fail.
		size_t st = ReadFileSMEMBUF (&smb, "asfasdfasdfasfasdfasdfsaf");
		ubf_assert_bool_AND (b, READFILESMEMBUF_ERROR == st);

		return b;
	}
#endif
