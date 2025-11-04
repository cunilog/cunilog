/****************************************************************************************

	File:		cunilogprocess.h
	Why:		Cunilog wrapper for module ProcessHelpers.
	OS:			C99
	Author:		Thomas
	Created:	2025-11-02
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-11-02	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Cunilog wrapper for module ProcessHelpers.
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

#ifndef U_CUNILOGPROCESS_H
#define U_CUNILOGPROCESS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./cunilog.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ProcessHelpers.h"
	#else
		#include "./../OS/ProcessHelpers.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

EXTERN_C_BEGIN

/*
	RunCunilogProcessWithTarget

	This function will probably not be implemented, as its functionality is already
	covered by RunCunilogProcessWithTargets ().

	Creates and runs a process and directs its output for stdout and stderr to the
	CUNILOG_TARGET pctStdoutStderr points to.

*/
/*
bool RunCunilogProcessWithTarget	(
		CUNILOG_TARGET			*pctStdoutStderr,
		cueventseverity			sevStdout,
		cueventseverity			sevStderr,
		const char				*szExecutable,
		const char				*szCmdLine,
		const char				*szWorkingDir,
		uint64_t				uiChildExitTimeout,			// Time in ms to wait for the child to
															//	exit/terminate.
		int						*pExitCode					// Exit code of process.
									)
;
*/

/*
	RunCunilogProcessWithTargets

	Creates and runs a process and directs its output for stdout to the CUNILOG_TARGET
	pctStdout points to and stderr to the CUNILOG_TARGET pctStderr points to.

	pctStdout			The CUNILOG_TARGET that receives output that goes to stdout.

	sevStdout			The severity the output is sent to the target with.

	pctStderr			The CUNILOG_TARGET that receives output that goes to stderr.

	sevStderr			The severity with which the output is sent to the target.

	szExecutable		The full path to the executable module for the child process.

	szCmdLine			Additonal arguments for the child process.

	szWorkingDir		The working directory for the child process.

	pExitCode			A pointer to an integer that receives the exit code of the
						child process.

	If pctStdout and pctStderr point to the same target, it is advised to distinguish
	stdout from stderr by using different severity values.

	The function returns true if the process could be created and executed. It returns
	false if this fails.
*/
bool RunCunilogProcessWithTargets	(
		CUNILOG_TARGET			*pctStdout,
		cueventseverity			sevStdout,
		CUNILOG_TARGET			*pctStderr,
		cueventseverity			sevStderr,
		const char				*szExecutable,
		const char				*szCmdLine,
		const char				*szWorkingDir,
		int						*pExitCode					// Exit code of process.
									)
;

EXTERN_C_END

#endif														// Of #ifndef U_CUNILOGPROCESS_H.

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
