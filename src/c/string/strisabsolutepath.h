/****************************************************************************************

	File:		strabsolutepath.h
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

#ifndef STRISABSOLUTEPATH_H
#define STRISABSOLUTEPATH_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

EXTERN_C_BEGIN

/*
	is_absolute_path_unix
	is_absolute_path_unx
	
	Returns or evaluates to true if the string chPath points to is an absolute Unix/Linux path,
	false if it is not. An absolute Unix/Linux path starts with a forward slash
	("/").

	The buffer chPath (in debug versions) or p (in release versions) points to must be at least
	one octet/byte long.
*/
#ifdef DEBUG
	bool is_absolute_path_unix (const char *chPath);
#else
	#define is_absolute_path_unix(p)					\
			('/' == (p)[0])
#endif
#define is_absolute_path_unx(p)							\
			is_absolute_path_unix (p)

/*
	is_unc_path

	Evaluates to true if the NUL-terminated string p is a UNC path
	like "\\host\path" or "//host/path". The buffer p points to must
	be NUL-terminated.
*/
#define is_unc_path(p)									\
			(											\
					(									\
							'\\' == (p)[0]				\
						&&	'\\' == (p)[1]				\
					)									\
				||	(									\
							'/' == (p)[0]				\
						&&	'/' == (p)[1]				\
					)									\
			)

/*
	is_absolute_drive_path

	Evaluates to true if the NUL-terminated string p is a typical Windows drive path
	like "X:\" or "X:/". The buffer p points to must be NUL-terminated.
*/
#define is_absolute_drive_path(p)						\
			(											\
					isalpha ((p)[0])					\
				&&	':' == (p)[1]						\
				&&	('\\' == (p)[2]	||	'/' == (p)[2])	\
			)

#define is_drive_path(p)								\
	error "Macro obsolete. Use is_full_drive_path() instead"

/*
	is_absolute_path_win
	is_absolute_path_windows
	
	Returns true if the string chPath points to is an absolute Windows path,
	false otherwise. An absolute Windows path either starts with two consecutive
	slashes (forward or backward) or starts with a drive letter and a colon
	sequence.
	
	Note that the function does not accept a mix of starting forward and backward
	slashes like "/\" or "\/". The function returns false in these cases.
*/
bool is_absolute_path_win (const char *chPath);
#define is_absolute_path_windows(p)						\
			is_absolute_path_win (p)

/*
	is_absolute_path
	
	Returns true if the path is an absolute path on either Windows or Unix/Linux.
	
	This is a function in debug versions, a macro in release versions.
	The function/macro calls is_absolute_path_unix () and is_absolute_path_win ().
*/
#ifdef DEBUG
	bool is_absolute_path (const char *chPath);
#else
	#define is_absolute_path(p)							\
		(												\
				is_absolute_path_unix	(p)				\
			||	is_absolute_path_win	(p)				\
		)

#endif

/*
	is_absolute_path_unix_l

	Returns or evaluates to true if len is greater than 0 and the first character
	chPath points to is a forward slash.

	This is a function in debug versions, a macro in release versions.
*/
#ifdef DEBUG
	bool is_absolute_path_unix_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_unix_l(p, l)				\
		(l && '/' == (p)[0])
#endif

/*
	is_absolute_path_win_l

	Returns or evaluates to true if chPath either points to a Windows UNC path or
	a full drive path. UNC paths start with two backslashes. A full drive path starts
	with a drive letter, a colon, and a backslash.

	The parameter len specifies the length of the buffer chPath points to.

	This is a function in debug versions, a macro in release versions.
*/
#ifdef DEBUG
	bool is_absolute_path_win_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_win_l(p, l)				\
		(												\
				(l > 1 && is_unc_path (p))				\
			||	(l > 2 && is_absolute_drive_path (p))	\
		)
#endif

/*
	is_absolute_path_l

	Returns true if the path is an absolute path on either Windows or Unix/Linux.

	The parameter len specifies the length of the buffer chPath points to.

	This is a function in debug versions, a macro in release versions.
	The function/macro calls is_absolute_path_unix_l () and is_absolute_path_win_l ().
*/
#ifdef DEBUG
	bool is_absolute_path_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_l(p, l)					\
		(												\
				is_absolute_path_unix_l (p, l)			\
			||	is_absolute_path_win_l (p, l)			\
		)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRISABSOLUTEPATH_H.
