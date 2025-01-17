/****************************************************************************************

	File:		PsxHome.h
	Why:		Obtains a user's home directory on POSIX.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-03

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-03	Thomas			Created.

****************************************************************************************/

/*
	Functions for retrieving username, user home directory, etc. on POSIX.
	
	This module/unit can also be included on Windows builds but does not provide
	any functionality.
*/

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

#ifndef U_PSX_HOME_H
#define U_PSX_HOME_H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	/*
	// See https://www.man7.org/linux/man-pages/man3/getpwnam.3.html .
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE
	#endif
	#ifndef _BSD_SOURCE
	#define _BSD_SOURCE
	#endif
	#ifndef _SVID_SOURCE
	#define _SVID_SOURCE
	#endif
	*/
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	InitPsxHome
	
	Initialises the module/unit. Calling this function is not required because all
	other functions initialise the module implicitely. The caller may save a few
	CPU cycles by calling this function first.
*/
bool InitPsxHome (void)
;

/*
	UserHomeDirectoryPOSIX

	Returns the current user's home folder. The optional parameter plen retrieves
	the length of the returned string, if not NULL.

	The function is only re-entrant after its first invocation.

	The function returns a pointer to a string that contains the name of the current
	user's home directory.
*/
const char *UserHomeDirectoryPOSIX (size_t *plen)
;

/*
	UserTrashFolder
	
	Returns a user's trash folder.
*/
const char *UserTrashFolder (size_t *plen)
;

EXTERN_C_END

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_BEGIN

#ifdef DEBUG
	#ifndef PSXHOME_BUILD_TEST_FNCT
	#define PSXHOME_BUILD_TEST_FNCT
	#endif
#endif

/*
	TestPsxHome
	
	Function to test this module/unit.
*/
#ifdef PLATFORM_IS_POSIX
	#ifdef PSXHOME_BUILD_TEST_FNCT
		bool TestPsxHome (void);
	#else
		#define TestPsxHome()	(true)
	#endif
#else
		#define TestPsxHome()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_PSX_HOME_H.
