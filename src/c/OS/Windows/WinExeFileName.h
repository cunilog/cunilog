/****************************************************************************************

	File:		WinExeFileName.h
	Why:		Obtains the name of the executable.
	OS:			Windows.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

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

#ifndef WIN_EXEFILENAME_H
#define WIN_EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

#ifdef DEBUG
	#ifndef EXEFILENAME_MALLOC_BLOCKSIZE
	#define EXEFILENAME_MALLOC_BLOCKSIZE		(32)
	#endif
#else
	#ifndef EXEFILENAME_MALLOC_BLOCKSIZE
	#define EXEFILENAME_MALLOC_BLOCKSIZE		(256)
	#endif
#endif

EXTERN_C_BEGIN

#ifdef OS_IS_WINDOWS

/*
	WinObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t WinObtainExecutableModuleName (SMEMBUF *mb)
;

/*
	WinObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path or ".exe" filename extension.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "C:/temp/app.exe" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t WinObtainAppNameFromExecutableModule (SMEMBUF *mb)
;

/*
	WinObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
size_t WinObtainPathFromExecutableModule (SMEMBUF *mb)
;

#endif														// Of #ifdef OS_IS_WINDOWS.

EXTERN_C_END

#endif														// Of #ifndef WIN_EXEFILENAME_H.
