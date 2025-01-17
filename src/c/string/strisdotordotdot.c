/****************************************************************************************

	File:		strisdotordotdot.c
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strisdotordotdot.h"

#endif

#ifdef OS_IS_WINDOWS
	bool isDotOrDotDotW (wchar_t *wcPath)
	{	// Identify "." and ".." entries.
		return
				L'.' == wcPath [0]
			&&	(
						L'\0' == wcPath [1]
					||	(L'.' == wcPath [1] && L'\0' == wcPath [2])
				)
			? true : false;
	}
#endif

bool isDotOrDotDotU8 (char *cPath)
{	// Identify "." and ".." entries.
	return
			'.' == cPath [0]
		&&	(
					'\0' == cPath [1]
				||	('.' == cPath [1] && '\0' == cPath [2])
			)
		? true : false;
}
