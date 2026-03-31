/****************************************************************************************

	File:		CreateAllFolders.c
	Why:		Module to create an entire path with all subfolders.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2026-03-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2026-03-25	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./CreateAllFolders.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./ubfdebug.h"
		#include "./platform.h"

		#if defined (PLATFORM_IS_WINDOWS)

			#include "./WinAPI_U8.h"

		#elif defined (PLATFORM_IS_POSIX)

		#elif

			#error "Not supported"

		#endif

	#else

		#include "./../dbg/ubfdebug.h"
		#include "./../pre/platform.h"

		#if defined (PLATFORM_IS_WINDOWS)

			#include "./Windows/WinAPI_U8.h"

		#elif defined (PLATFORM_IS_POSIX)

		#elif

			#error "Not supported"

		#endif

	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	static bool CreateAllFoldersPsx (const char *szPath, size_t lnPath)
	{
		if (path == NULL || *path == '\0')
			return true;

		char *tempPath = strdup (path);
		if (tempPath == NULL) {
			return -1;
		}

		size_t len = strlen(tempPath);
		// Remove trailing slash if present (but keep root "/")
		if (len > 1 && tempPath[len - 1] == '/') {
			tempPath[len - 1] = '\0';
		}

		for (char *p = tempPath + 1; *p != '\0'; p++) {
			if (*p == '/') {
				*p = '\0';
				if (mkdir(tempPath, 0755) != 0) {
					if (errno != EEXIST) {
						free(tempPath);
						return -1;
					}
				}
				*p = '/';
			}
		}

		// Create the final directory
		if (mkdir(tempPath, 0755) != 0) {
			if (errno != EEXIST) {
				free(tempPath);
				return -1;
			}
		}

		free(tempPath);
		return 0;
	}
#endif

bool CunilogCreateAllFolders (const char *szPath, size_t lnPath)
{
	UNREFERENCED_PARAMETER (lnPath);

	#if defined (PLATFORM_IS_WINDOWS)

		return CreateAllFoldersU8 (szPath, lnPath, NULL);

	#elif defined (PLATFORM_IS_POSIX)

		return CreateAllFoldersPsx (szPath, lnPath);

	#elif

		#error "Not supported"

	#endif

}

bool CunilogCreateAllFoldersRelative (const char *szPath, size_t lnPath, const char *szAbsolute)
{
	UNREFERENCED_PARAMETER (szPath);
	UNREFERENCED_PARAMETER (lnPath);
	UNREFERENCED_PARAMETER (szAbsolute);

	ubf_assert_msg (false, "Carry on here!");

	return false;
}
