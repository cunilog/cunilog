/****************************************************************************************

	File:		restrict.h
	Why:		Provides the keyword "cunilog_restrict", which is the C99 "restrict"
				keyword.
	OS:			As many compilers and platforms as required.
	Author:		Thomas
	Created:	2025-03-23

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-03-23	Thomas			Created.

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

#ifndef U_CUNILOG_RESTRICT_H
#define U_CUNILOG_RESTRICT_H

#if __STDC_VERSION__ >= 199901L

	/*
		C99 compiler. The restrict keyword is available.
		See https://en.wikipedia.org/wiki/C99 .
	*/
	#define cunilog_restrict	restrict

#elif defined (__clang__)

	/*
		See https://clang.llvm.org/docs/LanguageExtensions.html .
		Clang also supports __restrict.
	*/
	#define cunilog_restrict	__restrict__

#elif defined (__GNUC__)

	/*
		See https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html .
		Also supports __restrict.
	*/
	#define cunilog_restrict	__restrict__

#elif defined (__INTEL_COMPILER)

	/*
		Requires -restrict option. See
		https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/restrict-qrestrict.html
		for details.
	*/
	#define cunilog_restrict	restrict

#elif defined (_MSC_VER)

	/*
		MSVC 2015 and later. See
		https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170 .
	*/
	#define cunilog_restrict	__restrict

#elif

	/*
		Not available.
	*/
	#define cunilog_restrict

#endif

#endif														// Of #ifndef U_CUNILOG_RESTRICT_H.
