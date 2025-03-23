/****************************************************************************************

	File:		strfilesys.h
	Why:		File system string functions.
	OS:			C99.
	Author:		Thomas
	Created:	2023-05-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-27	Thomas			Created.

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

#ifndef STRFILESYS_H
#define STRFILESYS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./restrict.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/restrict.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	is_directory_separator

	Macro to check if c is a directory separator.
*/
#ifndef is_directory_separator
#define is_directory_separator(c)						\
			(UBF_WIN_DIR_SEP == c || UBF_PSX_DIR_SEP == c)
#endif

/*
	str_find_path_navigator
	
	Returns a pointer to the first path navigator found in szString, or NULL if
	szString does not contain any path navigators. A path navigator is "../" on
	POSIX platforms and "..\" on Windows. The function treats both as equally
	valid on either platform and returns a pointer to the first one found.

	Note that this function does NOT support USE_STRLEN, which is (size_t) -1
	for the parameter lnString. The length MUST be specified appropriately.
*/
char *str_find_path_navigator (char *szString, size_t lnString)
;

/*
	str_remove_path_navigators
	remove_path_navigators_str
	
	Removes relative path navigators from chPath. The macro remove_path_navigators_str()
	is a redefinition of the function str_remove_path_navigators (). Relative path
	navigators consist of two periods followed by a slash, which is a forward slash on
	Unix/Linux platforms and a backward slash on Windows. The function recognises both
	types of path navigators.

	Relative path navigator
	"../"					Unix/Linux/Android/iOS/...
	"..\", escaped "..\\"	Windows

	Parameters

	chPath			A pointer to a string that contains the path with
					relative path navigators. This parameter cannot be NULL.

	pLen			A pointer to a size_t that contains the length of the string in
					chPath, not counting a NUL terminator. If this parameter is NULL,
					the function calls strlen (chPath) to obtain the length of the string
					chPath points to. If this parameter points to a size_t variable with a
					value of USE_STRLEN, which is (size_t) -1, the function calls
					strlen (chPath) too. If this parameter points to a size_t variable that
					contains a length other than USE_STRLEN, the parameter chPath does not
					need to be NUL-terminated.
					On return, the function updates the value with the new length of the path
					after relative path navigators have been removed, provided that pLen is
					not NULL.
					
	Examples - chPath as input on the left, chPath changed as output on the right:
	"../../test1/test2/test3/../../file.ext"	->	"../../test1/file.ext"
	"../../../1/2/3/4/5/6/7/../f.ext"			->	"../../../1/2/3/4/5/6/f.ext"
	"C:this is a test/test1/test2/../file.ext"	->	"C:this is a test/test1/file.ext"
	"/1/2/3/4/../../../../f.e"					->	"/f.e"
	"1/../f"									->	"f"
	"../f"										->	"../f"
	"1/2/../../f"								->	"f"
	"1/2/../../../f"							->	"../f"

	The function returns the amount of relative path navigators that were removed by the
	function. If pLen is not NULL, the function returns the new length in this size_t value
	after all relative path navigators have been removed.

	If path navigators have been removed, the function adds a NUL terminator to chPath since
	the string always shrinks in this case and at least several byte of additional space are
	made available. If no replacement occurs, the function does not change the buffer chPath
	points to.
*/
size_t str_remove_path_navigators (char *chPath, size_t *pLen);
#define remove_path_navigators_str(chPath,pLen)	str_remove_path_navigators (chPath, pLen)

/*
	ubf_correct_directory_separators_str
	
	The function replaces all directory separators with the correct directory separator
	of the host system before it removes all duplicate separators apart from the first
	two forward/backward slashes in a UNC path ("//server/share" or "\\server\share").
	
	chPath			Pointer to the path in which directory separators should be
					corrected.
	plenPath		Pointer to a value that specifies the length of the path chPath
					points to, excluding a terminating NUL character. If this parameter
					is NULL or points to a value of (size_t) -1, which is USE_STRLEN, the
					function uses strlen (chPath) to obtain its length.
	pReps			Pointer to a size_t that receives the amount of
					replacements the function has performed. This parameter can be NULL
					if this information is not needed.
	
	The function returns true on success, false when it fails. The amount of adjustments
	made is returned at the address pReps points to, i.e the amount of path
	separators replaced or removed, provided pReps is not NULL. If stPath is not NULL,
	the function returns the new length, excluding a terminating NUL, at the address it
	points to. The function returns false when chPath is NULL, in which case debug
	versions abort. The function also returns false when *pstPath is 0. Debug versions
	abort in this case too.
*/
bool ubf_correct_directory_separators_str	(
			char			*chPath,
			size_t			*cunilog_restrict plenPath,
			size_t			*cunilog_restrict pReps
											)
;

/*
	ubf_change_directory_separators
	
	Changes all directory separators ('/' and '\\') to newSeparator. Note that newSeparator
	can be any character that fits in a char.
*/
void ubf_change_directory_separators (char *szPath, size_t len, char newSeparator);

/*
	ubf_len_with_last_directory_separator
	
	Returns the length of szPath that includes the last directory separator,
	or 0 if sz does not contain any directory separators.
	
	"/home/file"	-> 6, which would be the same as strlen ("/home/");
	"/"				-> 1, which would be the same as strlen ("/");
	"home"			-> 0, which would be the same as strlen ("");
	"C:\\dir"		-> 3, which would be the same as strlen ("C:\\");
	
	In Windows, although "C:file.ext" is actually the current path of the current
	process on the C: drive, the function accepts this as an absolute path for a file,
	but only if the first character of szPath is a letter and the second character is
	a colon, and no other directory separator can be found:
	"C:file.ext"	-> 2, which would be the same as strlen ("C:");
	
	If szPath is NULL, the function returns 0.
*/
size_t ubf_len_with_last_directory_separator (const char *szPath, size_t len);

/*
	str_correct_dir_separators
	
	Corrects the directory separators in str.
	
	The function returns the amount of directory separators replaced.
*/
size_t str_correct_dir_separators (char *str, size_t len)
;

/*
	ubf_test_ubf_strfilesys
	
	Tests this module.
*/
#ifdef BUILD_DEBUG_UBF_STRFILESYS_TESTS
	bool ubf_test_ubf_strfilesys (void);
#else
	#define ubf_test_ubf_strfilesys()
#endif

EXTERN_C_END

#endif // STRFILESYS_H
