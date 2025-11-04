/****************************************************************************************

	File:		cunilogprocess.c
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./cunilog.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./ProcessHelpers.h"
		#include "./unref.h"
	#else
		#include "./../dbg/ubfdebug.h"
		#include "./../OS/ProcessHelpers.h"
		#include "./../pre/unref.h"
	#endif

#endif

/*
	This function will probably not be implemented, as its functionality is already
	covered by RunCunilogProcessWithTargets ().

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
{
	UNUSED (pctStdoutStderr);
	UNUSED (sevStdout);
	UNUSED (sevStderr);
	UNUSED (szExecutable);
	UNUSED (szCmdLine);
	UNUSED (szWorkingDir);
	UNUSED (uiChildExitTimeout);
	UNUSED (pExitCode);

	return false;
}
*/

typedef struct culgProcStdpCstm
{
	CUNILOG_TARGET				*pCTstdout;
	CUNILOG_TARGET				*pCTstderr;
	cueventseverity				sevStdout;
	cueventseverity				sevStderr;
} CULGPROCSTDPCSTM;

enRCmdCBval stdoutCallback (SRUNCMDCBINF *pInf, char *szOutput, size_t lnOutput, void *pCustom)
{
	UNUSED (pInf);

	CULGPROCSTDPCSTM *pcst = pCustom;
	if (pcst->pCTstdout)
		logTextU8sevl (pcst->pCTstdout, pcst->sevStdout, szOutput, lnOutput);
	return enRunCmdRet_Continue;
}

enRCmdCBval stderrCallback (SRUNCMDCBINF *pInf, char *szOutput, size_t lnOutput, void *pCustom)
{
	UNUSED (pInf);

	CULGPROCSTDPCSTM *pcst = pCustom;
	if (pcst->pCTstderr)
		logTextU8sevl (pcst->pCTstderr, pcst->sevStderr, szOutput, lnOutput);
	return enRunCmdRet_Continue;
}

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
{
	SRCMDCBS scbs;
	memset (&scbs, 0, sizeof (scbs));
	scbs.cbOut = stdoutCallback;
	scbs.cbErr = stderrCallback;

	uint16_t uiCallbackFlags	= RUNCMDPROC_CALLB_STDOUT
								| RUNCMDPROC_CALLB_STDERR;
	uint64_t uiChildExitTimeout	= 5000;

	CULGPROCSTDPCSTM cust;
	cust.pCTstdout = pctStdout;
	cust.pCTstderr = pctStderr;
	cust.sevStdout = sevStdout;
	cust.sevStderr = sevStderr;

	bool bRun = CreateAndRunCmdProcessCapture	(
					szExecutable, szCmdLine, szWorkingDir,
					&scbs, enRunCmdHow_OneLine, uiCallbackFlags,
					&cust, uiChildExitTimeout,
					pExitCode
												);
	return bRun;
}

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
