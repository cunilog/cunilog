/****************************************************************************************

	File		testProcesHelper.h
	Why:		Test for module ProcesHelper.
	OS:			C99
	Created:	2025-07-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-07-25	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The purpose of this module is to provide a playground for testing the function
	CreateAndRunCmdProcessCapture () in module ProcessHelper.
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

#ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS

#ifndef U_TEST_PROCESS_HELPER_H
#define U_TEST_PROCESS_HELPER_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		//#include "./restrict.h"
	#else
		#include "./../pre/externC.h"
		//#include "./../pre/restrict.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	Arguments and commands.
*/
extern const char *szTstPrsHlpsExitcode;					// Argument is an int.
extern const char *szTstPrsHlpsInput;						// Argument is an int,
															//	which specifies the amount
															//	of lines to read from stdin.
															//	Each line is echoed back to
															//	stdout.
extern const char *szTstPrsHlpsOutput;						// Argument is three ints:
															//	Seed, amount lines, and max
															//	line length.
															//	Random output goes to stdout.

/*
	Internal test function for this module.
*/
#ifdef TEST_PROCESS_HELPER_BUILD_TEST_FNCT
	bool TestProcessHelperTestFnct (void);
#else
	#define TestProcessHelperTestFnct()	(true)
#endif


EXTERN_C_END

#endif														// Of #ifndef U_TEST_PROCESS_HELPER_H.

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
