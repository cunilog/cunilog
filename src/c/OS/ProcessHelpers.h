/****************************************************************************************

	File:		ProcessHelpers.h
	Why:		Functions for creating and handling processes.
	OS:			C99
	Author:		Thomas
	Created:	2025-06-05
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-06-05	Thomas			Created.

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

#ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS

#ifndef U_PROCESSHELPERS_H
#define U_PROCESSHELPERS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_WINDOWS
	//typedef cunilog_process_t
#else

#endif

#ifndef PRCHLPS_DEF_EXCESS_BUFFER
#define PRCHLPS_DEF_EXCESS_BUFFER		(256)
#endif

/*
	ProcessHelpersSetBufferSize

	Sets the default buffer size of the module. Default is PRCHLPS_DEF_EXCESS_BUFFER.

	The function returns the prvious default buffer size.
*/
size_t ProcessHelpersSetBufferSize (size_t bufsize);

/*
	Squeezes the executable's name plus all arguments in a single string.
	The executable's name is going to be the first argument.

	If bNoExeArg is true, no executable argument is written to the returned string.
	While pretty much standard in POSIX, some Windows applications don't like it when
	their first argument is the name of the executable. Set bNoExeArg to true for
	those applications; otherwise set it to false.
*/
char *CreateArgsList (const char *szExecutable, int argc, const char *argv [], bool bNoExeArg)
;

/*
	Callback function return values.

	enRunCmdRet_Continue			This is the default. The calling function carries
									on until the child process exits.
									CreateAndRunCmdProcessCaptureStdout () returns true.

	enRunCmdRet_Ignore				The callback function is not called again but the
									child process keeps running until it exits itself.
									CreateAndRunCmdProcessCaptureStdout () returns true.

	enRunCmdRet_Terminate			Terminate the child process.
									CreateAndRunCmdProcessCaptureStdout () returns true.

	enRunCmdRet_TerminateFail		Terminate the child process.
									CreateAndRunCmdProcessCaptureStdout () returns true.
*/
enum enRunCmdCallbackRetValue
{
	enRunCmdRet_Continue,									// No change/continue.
	enRunCmdRet_Terminate,									// Exit child process.
	enRunCmdRet_Ignore,										// Keep child process running
															//	but stop calling callback
															//	function for this stream.
	enRunCmdRet_TerminateFail
};
typedef enum enRunCmdRet enRCmdCBval;

/*
	Callback function for stdout andstderr.
*/
typedef enRCmdCBval rcmdOutCB (const char *szOutput, size_t lnOutput, void *pCustom);
/*
	Callback function for stdin.

	The parameter psmb points to an initialised but otherwise empty SMEMBUF structure.
	The buffer of this structure can be populated with data by the callback function.
	This data is forwarded/sent to the child process's input stream stdin.

	The address plnData points to must be set to the length of the data that should
	be sent to the child's stdin stream. If nothing needs to be sent to the child process's
	input stream, *plenData must be set to 0 by the callback function.

	For example, a callback function of type rcmdInpCB could send the command "exit\n"
	(note the "\n" to simulate the enter key) to the child process:

	enRCmdCBval cbInp (SMEMBUF *psmb, size_t *plnData, void *pCustom)
	{
		UNUSED (pCustom);

		*plnData = SMEMBUFfromStr (psmb, "exit\n", USE_STRLEN);
		return enRunCmdRet_Continue;
	}

*/
typedef enRCmdCBval rcmdInpCB (SMEMBUF *psmb, size_t *plnData, void *pCustom);

typedef struct srcmdCBs
{
	rcmdInpCB	*cbInp;
	rcmdOutCB	*cbOut;
	rcmdOutCB	*cbErr;
} SRCMDCBS;

/*
	Which callback functions to call and execeutable argument.
*/
#define RUNCMDPROC_CALLB_STDINP		(0x0001)				// Invoke callback for stdin.
#define RUNCMDPROC_CALLB_STDOUT		(0x0002)				// Invoke callback for stdout.
#define RUNCMDPROC_CALLB_STDERR		(0x0004)				// Invoke callback for stderr.
#define RUNCMDPROC_EXEARG_NOEXE		(0x0008)				// No exe argument in parameter
															//	list. See comments for function
															//	CreateArgsList () for details.
															//	This flag sets the parameter
															//	bNoExeArg of CreateArgsList ()
															//	to true.

/*
	Internal flags. Must not be utilised by callers.

	Note that RUNCMDPROC_CALLB_INTERR only exists for consistency. It is implied that if
	RUNCMDPROC_CALLB_INTOUT is not set, RUNCMDPROC_CALLB_INTERR is assumed. See function
	callOutCB () on how it is implemented.
*/
#define RUNCMDPROC_CALLB_INTOUT		(0x0100)				// Called for stdout.
#define RUNCMDPROC_CALLB_INTERR		(0x0200)				// Called for stderr. This flag only
															//	exists for consistency reasons.
															//	It is never checked.

/*
	How or when the callback functions are to be called.

	enRunCmdHow_AsIs		Called whenever data is available, meaning it might arrive in
							uncontrollable chunks. The data is not necessarily NUL-terminated.

	enRunCmdHow_AsIs0		Called whenever data is available, may arrive in uncontrollable
							chunks, but each chunk is always NUL-terminated.

	enRunCmdHow_OneLine		Called for complete lines only, and called once for each collected
							line. The data does not contain line endings but is always NUL-
							terminated. A value of 0 for the parameter lnData means an empty
							line has been encountered.

	enRunCmdHow_All			Called only once with the entire collected output of the process.
							The data is NUL-terminated. Never called with a length of 0.
*/
enum enRunCmdHowToCallCB
{
	enRunCmdHow_AsIs,										// Whenever data is available.
	enRunCmdHow_AsIs0,										// Same but NUL-terminated.
	enRunCmdHow_OneLine,									// Per complete line.
	enRunCmdHow_All											// Everything in one go.
															//	Buffer is NUL-terminated.
};
typedef enum enRunCmdHowToCallCB enRCmdCBhow;

/*
	CreateAndRunCmdProcessCapture

	Creates and runs a command-line process.
	
	The process's input (stdin) can be provided by a callback function, and its output (stdout
	and stderr) can be captured by callback functions.

	Parameters

	szExecutable		A NUL-terminated string with the path and name of the executable module
						of the command-line process.

	szCmdLine			The command-line arguments/parameters.

	szWorkingDir		The working directory/current directory of the command-line process.

	pCBs				A pointer to an SRCMDCBS structure that contains pointers to the
						callback functions.

	cbHow				Specifies how and when the callback functions are to be invoked by
						the function. See the enum enRunCmdHowToCallCB for a list of possible
						options.

	uiRCflags			Option flags.

	pCustom				An arbitrary pointer or value that is passed on to the callback
						functions.

	pExitCode			A pointer to an integer that receives the exit code of the child
						process. If the exit code is not required, this parameter can be
						NULL. If pExitCode is not NULL, the function sets the value to
						EXIT_FAILURE before it starts doing any work, and updates it later
						to the real exit code of the child process. On most platforms,
						EXIT_FAILURE has a value of 1.

*/
	bool CreateAndRunCmdProcessCapture	(
			const char				*szExecutable,
			const char				*szCmdLine,
			const char				*szWorkingDir,
			SRCMDCBS				*pCBs,
			enRCmdCBhow				cbHow,					// How to call the callback functions.
			uint16_t				uiRCflags,				// One or more of the RUNCMDPROC_
															//	flags.
			void					*pCustom,				// Passed on unchanged to callback
															//	functions.
			int						*pExitCode				// Exit code of process.
										)
;


/*
	ProcessHelpersTestFnct

*/
#ifdef PROCESS_HELPERS_BUILD_TEST_FNCT
	bool ProcessHelpersTestFnct (void);
#else
	#define ProcessHelpersTestFnct() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_PROCESSHELPERS_H.

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
