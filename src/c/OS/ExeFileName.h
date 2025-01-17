/****************************************************************************************

	File:		ExeFileName.h
	Why:		Obtains the name of the executable.
				This is the platform-independent abstraction module for the Windows
				module WinExeFileName and the POSIX module PsxExeFileName.
	OS:			C99/Windows/POSIX.
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

#ifndef EXEFILENAME_H
#define EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../pre/platform.h"
	#endif

	#ifdef OS_IS_WINDOWS
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./WinExeFileName.h"
		#else
			#include "./Windows/WinExeFileName.h"
		#endif
	#else
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./PsxExeFileName.h"
		#else
			#include "./POSIX/PsxExeFileName.h"
		#endif
	#endif

#endif

EXTERN_C_BEGIN

/*
	ObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainExecutableModuleName(mb)				\
		WinObtainExecutableModuleName (mb)
#else
	#define ObtainExecutableModuleName(mb)				\
		PsxObtainExecutableModuleName (mb)
#endif

/*
	ObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path or ".exe" filename extension.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "C:/temp/app.exe" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainAppNameFromExecutableModule(mb)		\
		WinObtainAppNameFromExecutableModule (mb)
#else
	#define ObtainAppNameFromExecutableModule(mb)		\
		PsxObtainAppNameFromExecutableModule (mb)
#endif

/*
	ObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainPathFromExecutableModule(mb)			\
		WinObtainPathFromExecutableModule (mb)
#else
	#define ObtainPathFromExecutableModule(mb)			\
		PsxObtainPathFromExecutableModule (mb)
#endif

EXTERN_C_END

#endif														// Of #ifndef EXEFILENAME_H.
