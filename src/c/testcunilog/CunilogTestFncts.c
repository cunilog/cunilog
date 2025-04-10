/****************************************************************************************

	File:		CunilogTestFncts.c
	Why:		Actual test functions for cunilog.
	OS:			C99
	Author:		Thomas
	Created:	2025-04-02
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-04-02	Thomas			Created.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./CunilogTestFncts.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./cunilog.h"
		#include "./unref.h"

		// Required for the tests.
		#include "./ubfdebug.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../cunilog/cunilog.h"
		#include "./../pre/unref.h"

		// Required for the tests.
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

void CunilogTestFnctStartTestToConsole (const char *ccTestText)
{
	ubf_assert_non_NULL (ccTestText);

	cunilog_printf (ccTestText);
}

void CunilogTestFnctResultToConsole (bool bResult)
{
	if (bResult)
		cunilog_puts_sev (cunilogEvtSeverityNonePass, "\tPass");
	else
	{
		cunilog_puts_sev (cunilogEvtSeverityNoneFail, "\tFail");
		ubf_assert (false);
	}
}

void CunilogTestFnctDisabledToConsole (bool bResult)
{
	UNUSED (bResult);

	cunilog_puts_sev (cunilogEvtSeverityNoneWarn, "\tUntested/Test not built");

}

static bool testV (CUNILOG_TARGET *put, char *sz, ...)
{
	va_list ap;

	va_start (ap, sz);
	bool b = logTextU8vfmt (put, sz, ap);
	va_end (ap);
	return b;
}

static size_t	stTestState;

errCBretval CunilogTestFnctTestInitialThreshold (CUNILOG_ERROR error, CUNILOG_PROCESSOR *cup)
{
	ubf_assert_non_NULL (cup);

	//cunilog_printf ("Task: %d.\n", cup->task);

	switch (cup->task)
	{
		case cunilogProcessNoOperation:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessNoOperation...");
			CunilogTestFnctResultToConsole (true);
			break;
		case cunilogProcessEchoToConsole:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessEchoToConsole...");
			CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			break;
		case cunilogProcessUpdateLogFileName:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessUpdateLogFileName...");
			CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			break;
		case cunilogProcessWriteToLogFile:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessWriteToLogFile...");
			CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			break;
		case cunilogProcessFlushLogFile:
			if (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessFlushLogFile...");
				CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			} else
			if (CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking second threshold for cunilogProcessFlushLogFile...");
				CunilogTestFnctResultToConsole (0 == cup->thr && 1 == cup->cur);
			}
			break;
		case cunilogProcessRotateLogfiles:
			if (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessRotateLogfiles...");
				CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			} else
			if (CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking second threshold for cunilogProcessRotateLogfiles...");
				CunilogTestFnctResultToConsole (0 == cup->thr && 1 == cup->cur);
			}
			break;
		case cunilogProcessCustomProcessor:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessCustomProcessor...");
			CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			break;
		case cunilogProcessTargetRedirector:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessTargetRedirector...");
			CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			break;
		case cunilogProcessTargetFork:
			CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessTargetFork...");
			CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
			break;
		default:
			CunilogTestFnctStartTestToConsole ("Checking for illegal processor..."); 
			CunilogTestFnctResultToConsole (false);
	}
	return cunilogErrCB_ignore;
}

errCBretval CunilogTestFnctErrCallback	(
						CUNILOG_ERROR		error,
						CUNILOG_PROCESSOR	*cup,
						CUNILOG_EVENT		*pev
										)
{
	if (0 == stTestState)
	{
		stTestState = 1;
		return cunilogErrCB_cancel;
	}

	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

	CUNILOG_TARGET *put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	if (1 == stTestState)
	{
		CunilogTestFnctStartTestToConsole ("Checking before or after threshold update...");
		CunilogTestFnctResultToConsole	(
						CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE		== error
					||	CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE		== error
					||	CUNILOG_ERROR_TEST_BEFORE_REQUIRES_NEW_LOGFILE	== error
					||	CUNILOG_ERROR_TEST_AFTER_REQUIRES_NEW_LOGFILE	== error
										);
		CunilogTestFnctTestInitialThreshold (error, cup);
	}

	switch (error)
	{
		case CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE:
			break;
		case CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE:
			break;
		case CUNILOG_ERROR_TEST_BEFORE_REQUIRES_NEW_LOGFILE:
			break;
		case CUNILOG_ERROR_TEST_AFTER_REQUIRES_NEW_LOGFILE:
			break;
	}
	return cunilogErrCB_ignore;
}

bool CunilogTestFunction	(
		const char *ccLogsFolder,
		size_t					lnLogsFolder,
		const char *ccHello
)
{
	bool b = true;

	CUNILOG_TARGET *put;

	cunilog_puts ("Starting Cunilog tests...");

	CunilogTestFnctStartTestToConsole ("Internal test of module strnewline...");
	#ifdef STRNEWLINE_BUILD_TEST
	CunilogTestFnctResultToConsole (test_strnewline ());
	#else
	CunilogTestFnctDisabledToConsole (test_strnewline ());
	#endif

	CunilogTestFnctStartTestToConsole ("Init static target with cunilogPostfixDotNumberMinutely...");
	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDotNumberMinutely,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogDontRunProcessorsOnStartup
	);
	CunilogTestFnctResultToConsole (NULL != put);
	if (NULL == put)
		return false;

	CunilogTestFnctStartTestToConsole ("Target initislised...");
	CunilogTestFnctResultToConsole (cunilogIsTargetInitialised (put));

	CunilogTestFnctStartTestToConsole ("Checking target members...");
	b &= pCUNILOG_TARGETstatic == put;
	b &= NULL != put->cprocessors;
	b &= NULL == put->errorCB;
	b &= cunilogPostfixDotNumberMinutely == put->culogPostfix;
	b &= cunilogSingleThreaded == put->culogType;
	b &= !cunilogHasRunAllProcessorsOnStartup (put);
	b &= !cunilogIsShutdownTarget (put);
	CunilogTestFnctResultToConsole (b);

	CunilogTestFnctStartTestToConsole ("Test state...");
	CunilogTestFnctResultToConsole (0 == stTestState);

	CunilogTestFnctStartTestToConsole ("Checking path...");
	size_t len;
	const char *szAbsPath = GetAbsoluteLogPathCUNILOG_TARGET (put, &len);
	CunilogTestFnctResultToConsole (NULL != put && szAbsPath && len > 1);

	cunilogTargetSetAlwaysCallErrorCB (put);
	ConfigCUNILOG_TARGETerrorCallbackFunction (put, CunilogTestFnctErrCallback);
	CunilogTestFnctStartTestToConsole ("Checcking callback function...");
	CunilogTestFnctResultToConsole (CunilogTestFnctErrCallback == put->errorCB);
	CunilogTestFnctStartTestToConsole ("Invoking callback function...");
	stTestState = 0;
	errCBretval er = put->errorCB (0, NULL, NULL);
	CunilogTestFnctResultToConsole (1 == stTestState && cunilogErrCB_cancel == er);

	CunilogTestFnctStartTestToConsole ("Creating dummy event...");
	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, cunilogEvtSeverityNone, "ABD\n", USE_STRLEN);
	if (pev)
	{
		b &= NULL != pev;
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Checking event members...");
		b &= cunilogEvtSeverityNone == pev->evSeverity;
		b &= cunilogEvtTypeNormalText == pev->evType;
		// "\n" removed.
		b &= 3 == pev->lenDataToLog;
		b &= 0 == memcmp (pev->szDataToLog, "ABD", 3);
		b &= NULL == pev->next;
		b &= put == pev->pCUNILOG_TARGET;
		b &= 3 + ALIGNED_SIZE (sizeof (CUNILOG_EVENT), CUNILOG_DEFAULT_ALIGNMENT) == pev->sizEvent;
		CunilogTestFnctResultToConsole (b);
	} else
		CunilogTestFnctResultToConsole (false);

	stTestState = 1;
	logTextU8_static ("cunilogPostfixDotNumberDescending");
	Sleep (5000);
	stTestState = 2;

	ShutdownCUNILOG_TARGETstatic ();
	DoneCUNILOG_TARGETstatic ();

	put = CreateNewCUNILOG_TARGET		(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogMultiThreadedSeparateLoggingThread,
				cunilogPostfixMinute,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
										);
	ubf_assert_non_NULL (put);
	szAbsPath = GetAbsoluteLogPathCUNILOG_TARGET (put, &len);

	ShutdownCUNILOG_TARGET (put);
	DoneCUNILOG_TARGET (put);


	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogMultiThreadedSeparateLoggingThread,
				cunilogPostfixMinute,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
									);

	//configCUNILOG_TARGETdisableEchoProcessor (put);
	UNREFERENCED_PARAMETER (put);
	//b &= SetLogPriorityCUNILOG_TARGET (put, cunilogPrioIdle);
	ubf_assert_true (b);

	logTextU8_static ("");
	logTextU8_static ("----------");
	logTextU8_static (ccHello);
	logTextU8_static ("A simple line to go in the logfile.");
	logTextU8fmt_static ("Log folder: %s", GetAbsoluteLogPathCUNILOG_TARGET_static (NULL));
	char *cData = "ABCDEFGasdfuiolnaoelasdfuaelhaerodclleahcoelandielacsserooot";
	char *bData = "ABCDEF\0Gasdfuiolnaoelasdfuaelhaerodclleahcoelandielacsserooot";
	logHexDumpU8sevl_static (cunilogEvtSeverityWarning, cData, 15, "Caption", USE_STRLEN);
	logHexDumpU8sevl_static (cunilogEvtSeverityNone, cData, 4, "Caption", USE_STRLEN);
	logHexDumpU8sevl_static (cunilogEvtSeverityWarning, cData, 4, "Caption", USE_STRLEN);
	logHexDumpU8sevl_static (cunilogEvtSeverityWarning, cData, 16, "Caption", USE_STRLEN);
	logHexDumpU8sevl_static (cunilogEvtSeverityWarning, cData, 17, "Caption", USE_STRLEN);
	logHexDumpU8sevl_static (cunilogEvtSeverityWarning, cData, strlen (cData), "Caption", USE_STRLEN);
	logHexDump_static (cData, 20);
	logHexOrText_static (bData, 6);
	logHexOrText_static (bData, 12);

	uint64_t	n = 1000;
	while (n --)
	{
		logTextU8_static ("Another simple line to go in the logfile (first batch).");
	}
	PauseLogCUNILOG_TARGETstatic ();
	cunilog_puts ("Sleeping (1)...");
	Sleep (2000);
	n = 1000;
	while (n --)
	{
		logTextU8_static ("Another simple line to go in the logfile (second batch).");
	}
	cunilog_puts ("Sleeping (2)...");
	Sleep (2000);
	ResumeLogCUNILOG_TARGETstatic ();

	logTextU8_static ("This one's in UTF-16 (\xC5\x98), which should be an \"R\" with a flipped roof.");
	testV (put, "Hello %i", 20);
	logTextU8sev_static (cunilogEvtSeverityDebug, "This is a debug message");
	logTextU8sev_static (cunilogEvtSeverityCritical, "This is a critical message");
	ChangeCUNILOG_TARGETuseColourForEcho_static (false);
	logTextU8sev_static (cunilogEvtSeverityCritical, "This is also a critical message");
	ChangeCUNILOG_TARGETlogPriority_static (cunilogPrioBelowNormal);
	ChangeCUNILOG_TARGETlogPriority_static (cunilogPrioNormal);
	ChangeCUNILOG_TARGETuseColourForEcho_static (true);
	logTextU8sev_static (cunilogEvtSeverityCritical, "This is another critical message");

	logTextU8sev_static (cunilogEvtSeverityNonePass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityNoneFail, "This is a bad one");
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeCUNILOG_TARGETeventSeverityFormatType (pCUNILOG_TARGETstatic, cunilogEvtSeverityTypeChars3InBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeCUNILOG_TARGETeventSeverityFormatType (pCUNILOG_TARGETstatic, cunilogEvtSeverityTypeChars5InBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeCUNILOG_TARGETeventSeverityFormatType (pCUNILOG_TARGETstatic, cunilogEvtSeverityTypeChars9InBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeCUNILOG_TARGETeventSeverityFormatType (pCUNILOG_TARGETstatic, cunilogEvtSeverityTypeChars5InTightBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	logTextU8sev_static (cunilogEvtSeverityNone, "None");
	logTextU8sev_static (cunilogEvtSeverityBlanks, "Blanks");
	ChangeCUNILOG_TARGETeventSeverityFormatType (pCUNILOG_TARGETstatic, cunilogEvtSeverityTypeChars9InTightBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	logTextU8sev_static (cunilogEvtSeverityNone, "None");
	logTextU8sev_static (cunilogEvtSeverityBlanks, "Blanks");

	logTextU8c_static ("This text only goes to the console");
	logTextU8_static ("This one doesn't");
	logTextU8cfmt_static ("There's %d bugs.", 200);
	logTextU8cfmt_static ("A string: %s", "who knows?");
	
	SMEMBUF smb = SMEMBUF_INITIALISER;
	logTextU8smbfmt_static (&smb, "Another string is \"%s\"", "String");

	/*
	Sleep (2000);
	puts (STR_ANSI_FGCOL_BRIGHT_GREEN "This is the text we test the attributes with." STR_ANSI_RESET);
	*/

	/*
	Sleep (2000);
	puts ("This one's in UTF-16 (\xC5\x98), which should be an \"R\" with a flipped roof.");
	*/

	//CancelCUNILOG_TARGETstatic ();
	ShutdownCUNILOG_TARGETstatic ();
	DoneCUNILOG_TARGETstatic ();


	return b;
}
