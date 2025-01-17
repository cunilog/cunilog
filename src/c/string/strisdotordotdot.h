/****************************************************************************************

	File:		strisdotordotdot.h
	Why:		Checks for "." and ".." file/folder names.
	OS:			C99.
	Author:		Thomas
	Created:	2022-05-18

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-05-18	Thomas			Created.

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

#ifndef STRISDOTORDOTDOT_H
#define STRISDOTORDOTDOT_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	isDotOrDotDotW

	Returns true if the path wcPath points to is "." or "..", false otherwise.
*/
#ifdef OS_IS_WINDOWS
	bool isDotOrDotDotW (wchar_t *wcPath);
#endif

/*
	isDotOrDotDotU8

	UTF-8 version of isDotOrDotDotW (). Returns true if the path cPath points to
	is "." or "..", false otherwise.
*/
bool isDotOrDotDotU8 (char *cPath);

EXTERN_C_END

#endif														// Of #ifndef STRISDOTORDOTDOT_H.
