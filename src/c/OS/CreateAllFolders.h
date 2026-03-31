/****************************************************************************************

	File:		CreateAllFolders.h
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

#ifndef U_CREATEALLFOLDERS_H
#define U_CREATEALLFOLDERS_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./platform.h"
		#include "./externC.h"

		#if defined (PLATFORM_IS_WINDOWS)

		#elif defined (PLATFORM_IS_POSIX)
		
		#endif

	#else

		#include "./../pre/platform.h"
		#include "./../pre/externC.h"

		#if defined (PLATFORM_IS_WINDOWS)

		#elif defined (PLATFORM_IS_POSIX)
		
		#endif

	#endif

#endif

EXTERN_C_BEGIN

/*!
	CunilogCreateAllFolders

	Creates all folders in szPath and returns true on success, false otherwise.
	Success means that the path either has been created by the function or that
	it existed already prior to invoking the function.

	The parameter lnPath is the length of szPath. If it is USE_STRLEN, the function
	retrieves its length via a call to strlen (), in which case szPath must be
	NUL-terminated.

	The parameter szPath must be an absolute path.
*/
bool CunilogCreateAllFolders (const char *szPath, size_t lnPath);

/*!
	CunilogCreateAllFoldersRelative

	Creates all folders in szPath and returns true on success, false otherwise.
	Success means that the path either has been created by the function or that
	it existed already prior to invoking the function.

	The parameter lnPath is the length of szPath. If it is USE_STRLEN, the function
	retrieves its length via a call to strlen (), in which case szPath must be
	NUL-terminated.

	The parameter szPath can be a relative path that is relative to szAbsolute.
*/
bool CunilogCreateAllFoldersRelative (const char *szPath, size_t lnPath, const char *szAbsolute);

EXTERN_C_END

#endif														// Of #ifndef U_CREATEALLFOLDERS_H.
