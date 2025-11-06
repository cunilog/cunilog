/****************************************************************************************

	File:		PsxExeFileName.h
	Why:		Obtains the name of the executable.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-14

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-14	Thomas			Created.

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

#ifndef PSX_EXEFILENAME_H
#define PSX_EXEFILENAME_H

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

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	PsxObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t PsxObtainExecutableModuleName (SMEMBUF *mb)
;

/*
	PsxObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "/temp/app" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t PsxObtainAppNameFromExecutableModule (SMEMBUF *mb)
;

/*
	PsxObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
size_t PsxObtainPathFromExecutableModule (SMEMBUF *mb)
;

/*
	DonePsxExecutableModule

	Frees the resources allocated by this module.
*/
void DonePsxExecutableModule (void);


#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef PSX_EXEFILENAME_H.
