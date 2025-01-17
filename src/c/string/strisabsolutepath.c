/****************************************************************************************

	File:		strabsolutepath.c
	Why:		String functions for absolute/relative paths.
	OS:			C99
	Author:		Thomas
	Created:	2021-07-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

****************************************************************************************/

/*
	The functions in this module do not use any file system functions.
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

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strisabsolutepath.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
	#else
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

#ifdef DEBUG
	bool is_absolute_path_unix (const char *chPath)
	{
		ubf_assert_non_NULL (chPath);

		return '/' == chPath [0];
	}
#endif

bool is_absolute_path_win (const char *chPath)
{
	ubf_assert_non_NULL (chPath);

	return is_unc_path (chPath) || is_absolute_drive_path (chPath);
}

#ifdef DEBUG
	bool is_absolute_path (const char *chPath)
	{
		ubf_assert_non_NULL (chPath);

		return (is_absolute_path_unix (chPath) || is_absolute_path_win (chPath));
	}
#endif

#ifdef DEBUG
	bool is_absolute_path_unix_l (const char *chPath, size_t len)
	{
		ubf_assert_non_NULL (chPath);
		ubf_assert ((size_t) -1 != len);

		return len && '/' == chPath [0];
	}
#endif

#ifdef DEBUG
	bool is_absolute_path_win_l (const char *chPath, size_t len)
	{
		ubf_assert_non_NULL (chPath);
		ubf_assert ((size_t) -1 != len);

		return (len > 1 && is_unc_path (chPath)) || ((len > 2) && is_absolute_drive_path (chPath));
	}
#endif

#ifdef DEBUG
	bool is_absolute_path_l (const char *chPath, size_t len)
	{
		ubf_assert_non_NULL (chPath);
		ubf_assert ((size_t) -1 != len);

		return (is_absolute_path_unix_l (chPath, len) || is_absolute_path_win_l (chPath, len));
	}
#endif
