/****************************************************************************************

	File:		PsxTrash.h
	Why:		Handles the trash can for POSIX.
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
	The name of this module is actually slightly wrong as it isn't really POSIX.
	It tries to follow the XDG specification
	(https://specifications.freedesktop.org/trash-spec/latest/)
	on trash (https://specifications.freedesktop.org/trash-spec/latest/).
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

#ifndef U_PSX_TRASH_H
#define U_PSX_TRASH_H

#ifdef OS_IS_LINUX

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

EXTERN_C_BEGIN

/*
	MoveFileToTrashPOSIX

	Moves the file named in szFilename to the trash bin/can on POSIX according to the
	XDG specification. See
	https://specifications.freedesktop.org/trash-spec/latest/ for details.

	The path of szFilename can neither be relative nor can it contain path navigators
	("../"). It must be a corrected absolute path.
*/
bool MoveFileToTrashPOSIX (const char *szFilename);

EXTERN_C_END

#endif														// Of #ifdef OS_IS_LINUX.

#endif														// Of #ifndef U_PSX_TRASH_H.
