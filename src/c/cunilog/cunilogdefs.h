/****************************************************************************************

	File:		cunilogdefs.h
	Why:		Required definitions for Cunilog to build.
	OS:			-
	Author:		Thomas
	Created:	2024-11-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-06	Thomas			Created.

****************************************************************************************/

/*
	The definitions in this module are required for Cunilog to build.
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

#ifndef U_CUNILOGDEFS_H
#define U_CUNILOGDEFS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

/*
	Suppresses the MSVC warnings for strcpy (), memcpy (), etc.
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	//#warning _CRT_SECURE_NO_WARNINGS should be defined for Cunilog to build.
	#endif
#endif

/*
	Wildcard support
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef HAVE_STRWILDCARDS
	#define HAVE_STRWILDCARDS
	#endif
#endif

/*
	For MoveToRecycleBinU8 ().
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef HAVE_SHELLAPI
	#define HAVE_SHELLAPI
	#endif
#endif

/*
	For GetDefaultUserProfileDirectoryU8 ().
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef HAVE_USERENV
	#define HAVE_USERENV
	#endif
#endif


#endif														// Of #ifndef U_CUNILOGDEFS_H.
