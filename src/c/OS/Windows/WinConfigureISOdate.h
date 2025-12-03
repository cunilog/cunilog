/****************************************************************************************

	File:		WinConfigureISOdate.h
	Why:		Module to configure date and time format in the Windows registry.
	OS:			Windows.
	Author:		Thomas
	Created:	2025-11-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-11-17	Thomas			Created.

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

#ifndef U_WINCONFIGUREISODATE_H
#define U_WINCONFIGUREISODATE_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_U8.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../../pre/platform.h"
	#endif

	#ifdef BUILD_WINCONFIGUREISODATE_TEST
		//#include <stdio.h>
	#endif

#endif

#ifdef PLATFORM_IS_WINDOWS

BEGIN_C_DECLS

enum enISOregistry
{
	enISOregistryCurrentUser,
	enISOregistryAllUsers
};

/*
	setISO8601inRegistry

	Sets user or system-wide date and time format in the Windows registry.

	Returns true on success, false otherwise.
*/
bool setISO8601inRegistry (enum enISOregistry reg);

/*
	WinConfigureISOdateTestFnct

	Test function for the module. Not a real test function.
	Only invokes setISO8601inRegistry (enISOregistryCurrentUser);
*/
#ifdef BUILD_WINCONFIGUREISODATE_TEST
	bool WinConfigureISOdateTestFnct (void)
#else
	#define WinConfigureISOdateTestFnct() (true)
#endif

END_C_DECLS

#endif													// Of #ifdef PLATFORM_IS_WINDOWS.

#endif													// Of #ifndef U_WINCONFIGUREISODATE_H.
