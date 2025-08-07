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
		#include "./ISO__DATE__.h"
		#include "./ubf_date_and_time.h"
		#include "./cunilog.h"
		#include "./unref.h"
		#include "./memstrstr.h"
		#include "./stransi.h"
		#include "./strcustomfmt.h"
		#include "./strfilesys.h"
		#include "./strhex.h"
		#include "./strlineextract.h"
		#include "./strwildcards.h"
		#include "./check_utf8.h"
		#include "./ProcessHelpers.h"
		#include "./testProcesHelper.h"

		// Required for the tests.
		#include "./ubfdebug.h"

		#ifdef PLATFORM_IS_WINDOWS
			#include "./WinAPI_ReadDirFncts.h"
			#include "./WinAPI_U8_Test.h"
		#else

		#endif
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../cunilog/cunilog.h"
		#include "./../datetime/ISO__DATE__.h"
		#include "./../datetime/ubf_date_and_time.h"
		#include "./../pre/unref.h"
		#include "./../mem/memstrstr.h"
		#include "./../string/stransi.h"
		#include "./../string/strcustomfmt.h"
		#include "./../string/strfilesys.h"
		#include "./../string/strhex.h"
		#include "./../string/strlineextract.h"
		#include "./../string/strwildcards.h"
		#include "./../string/check_utf8.h"
		#include "./../OS/ProcessHelpers.h"
		#include "./../testcunilog/testProcesHelper.h"

		// Required for the tests.
		#include "./../dbg/ubfdebug.h"

		#ifdef PLATFORM_IS_WINDOWS
			#include "./../OS/Windows/WinAPI_ReadDirFncts.h"
			#include "./../OS/Windows/WinAPI_U8_Test.h"
		#else

		#endif
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

	if (bResult)
		cunilog_puts_sev (cunilogEvtSeverityNoneWarn, "\tUntested/Test not built");
	else
	{
		cunilog_puts_sev (cunilogEvtSeverityNoneFail, "\tFail");
		ubf_assert (false);
	}

}

void CunilogTestFnctNotRequiredToConsole (void)
{
	cunilog_puts_sev (cunilogEvtSeverityNonePass, "\tUntested because not required on this platform");
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
	static size_t stFlushLogFile;
	static size_t stRotateLogFile;

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
				if (0 == stFlushLogFile)
					CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
				else
					CunilogTestFnctResultToConsole (cup->thr == cup->cur);
				++ stFlushLogFile;
			} else
			if (CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking second threshold for cunilogProcessFlushLogFile...");
				CunilogTestFnctResultToConsole (cup->thr == cup->cur);
			}
			break;
		case cunilogProcessRotateLogfiles:
			if (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking initial threshold for cunilogProcessRotateLogfiles...");
				if (0 == stRotateLogFile)
					CunilogTestFnctResultToConsole (0 == cup->thr && 0 == cup->cur);
				else
					CunilogTestFnctResultToConsole (cup->thr == cup->cur);
				++ stRotateLogFile;
			} else
			if (CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE == error)
			{
				CunilogTestFnctStartTestToConsole ("Checking second threshold for cunilogProcessRotateLogfiles...");
				CunilogTestFnctResultToConsole (cup->thr == cup->cur);
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

errCBretval CunilogTestFnctErrCallback0002	(
						CUNILOG_ERROR		error,
						CUNILOG_PROCESSOR	*cup,
						CUNILOG_EVENT		*pev
											)
{
	UNUSED (pev);

	if (2 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessEchoToConsole == cup->task);
		CunilogTestFnctStartTestToConsole ("Before updating threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error);
		stTestState = 3;
		return cunilogErrCB_ignore;

		/*
			Note that there's no CUNILOG_ERROR_TEST_AFTER... callback, because
			cunilogProcessAppliesTo_nAlways returns from the threshold update function
			immediately and does not invoke it.
		*/
	}

	if (3 == stTestState)
	{
		CunilogTestFnctStartTestToConsole ("Next processor after echo...");
		CunilogTestFnctResultToConsole (cunilogProcessWriteToLogFile == cup->task);
		CunilogTestFnctStartTestToConsole ("Before updating threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error);
		stTestState = 4;
		CunilogTestFnctStartTestToConsole ("Next processor after writing to logfile...");
		return cunilogErrCB_ignore;
	}

	if (4 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessFlushLogFile == cup->task);
		CunilogTestFnctStartTestToConsole ("Before updating threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error);
		stTestState = 5;
		CunilogTestFnctStartTestToConsole ("Next processor after flushing logfile before threshold...");
		return cunilogErrCB_ignore;
	}

	if (5 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessFlushLogFile == cup->task);
		CunilogTestFnctStartTestToConsole ("After updating threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE == error);
		stTestState = 6;
		CunilogTestFnctStartTestToConsole ("Next processor after flushing logfile after threshold...");
		return cunilogErrCB_ignore;
	}

	if (6 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessRotateLogfiles == cup->task);
		CunilogTestFnctStartTestToConsole ("Before updating threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error);
		CunilogTestFnctStartTestToConsole ("Do we have rotation data?");
		CUNILOG_ROTATION_DATA *prd = cup->pData;
		CunilogTestFnctResultToConsole (NULL != prd);
		CunilogTestFnctStartTestToConsole ("Correct rotator...");
		CunilogTestFnctResultToConsole (cunilogrotationtask_RenameLogfiles == prd->tsk);
		stTestState = 7;
		CunilogTestFnctStartTestToConsole ("Next processor after renamer before threshold...");
		return cunilogErrCB_ignore;
	}

	if (7 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessRotateLogfiles == cup->task);
		CunilogTestFnctStartTestToConsole ("After updating threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE == error);
		CunilogTestFnctStartTestToConsole ("Do we have rotation data?");
		CUNILOG_ROTATION_DATA *prd = cup->pData;
		CunilogTestFnctResultToConsole (NULL != prd);
		CunilogTestFnctStartTestToConsole ("Correct rotator...");
		CunilogTestFnctResultToConsole (cunilogrotationtask_RenameLogfiles == prd->tsk);
		stTestState = 8;
		CunilogTestFnctStartTestToConsole ("Renaming...");
		return cunilogErrCB_ignore;
	}

	if (8 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessRotateLogfiles == cup->task);
		CunilogTestFnctStartTestToConsole ("Before rotator...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_BEFORE_ROTATOR == error);
		CunilogTestFnctStartTestToConsole ("Do we have rotation data?");
		CUNILOG_ROTATION_DATA *prd = cup->pData;
		CunilogTestFnctResultToConsole (NULL != prd);
		CunilogTestFnctStartTestToConsole ("Correct rotator...");
		CunilogTestFnctResultToConsole (cunilogrotationtask_RenameLogfiles == prd->tsk);
		stTestState = 9;
		//CunilogTestFnctStartTestToConsole ("Next processor after renamer after threshold...");
		return cunilogErrCB_ignore;
	}

	/*
		This is all we can check here because the other invocations depend on the state
		of the logging folder.
	*/

	// Test sequence point 1.
	//	We won't be called until sequence point 2.

	// Test sequence point 2.

	if (10 == stTestState)
	{
		CunilogTestFnctResultToConsole (cunilogProcessEchoToConsole == cup->task);
		CunilogTestFnctStartTestToConsole ("Echo processor before threshold...");
		CunilogTestFnctResultToConsole (CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE == error);
		stTestState = 11;
		return cunilogErrCB_ignore;

		/*
			Note that there's no CUNILOG_ERROR_TEST_AFTER... callback, because
			cunilogProcessAppliesTo_nAlways returns from the threshold update function
			immediately and does not invoke it.
		*/
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
	UNUSED (put);

	if (1 == stTestState)
	{
		switch (error)
		{
			case CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE:
				CunilogTestFnctStartTestToConsole ("Checking before threshold update...");
				break;
			case CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE:
				CunilogTestFnctStartTestToConsole ("Checking after threshold update...");
				break;
			case CUNILOG_ERROR_TEST_BEFORE_REQUIRES_NEW_LOGFILE:
				CunilogTestFnctStartTestToConsole ("Checking before requires new logfile...");
				break;
			case CUNILOG_ERROR_TEST_AFTER_REQUIRES_NEW_LOGFILE:
				CunilogTestFnctStartTestToConsole ("Checking after requires new logfile...");
				break;
			case CUNILOG_ERROR_TEST_BEFORE_ROTATOR:
				// Rotation is yearly, i.e. we must not be called.
				CunilogTestFnctStartTestToConsole ("Callback before rotator...");
				CunilogTestFnctResultToConsole (false);
				break;
			case CUNILOG_ERROR_TEST_AFTER_ROTATOR:
				// Rotation is yearly, i.e. we must not be called.
				CunilogTestFnctStartTestToConsole ("Callback after rotator...");
				CunilogTestFnctResultToConsole (false);
				break;
		}
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
		size_t		lnLogsFolder,
		const char *ccHello
							)
{
	bool b = true;

	CUNILOG_TARGET		*put;
	CUNILOG_PROCESSOR	*cup;

	cunilog_puts ("Starting Cunilog tests...");
	/*
		Was used for debugging.

	uint64_t uiBSN = 230;
	uint64_t uiBSNprev	= 244;
	cunilog_printf_sev (cunilogEvtSeverityFail, "Wrong BSN: %4.4" PRId64 " (expected: %4.4" PRId64 ")\n", uiBSN, uiBSNprev);
	*/

	/*
	cunilog_printf ("What?\n");
	cunilog_printf ("\nDone. %zu line(s) processed, %zu line(s) total.\n", 1, 5);
	cunilog_puts ("And again.");
	*/

	CunilogTestFnctStartTestToConsole ("Internal test of module stransi...");
	#ifdef STRANSI_BUILD_TEST_FNCT
		b &= stransi_test_fnct ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= stransi_test_fnct ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macros tested. Internal test of module stransi...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Internal test of module strlineextract...");
	#ifdef STRLINEEXTRACT_BUILD_TEST_FNCT
		b &= test_strlineextract ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= test_strlineextract ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macros tested. Internal test of module strlineextract...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Quick ISO date tests...");
	const char *szBld = szBuild_ISO__DATE__ ();
	ubf_expect_bool_AND (b, LEN_ISO8601DATE == strlen (szBld));
	szBld = szBuild_ISO__DATE__TIME__ ();
	ubf_expect_bool_AND (b, LEN_ISO8601DATETIMESTAMP_NO_OFFS == strlen (szBld));
	CunilogTestFnctResultToConsole (b);

	CunilogTestFnctStartTestToConsole ("Self-test module ubf_date_and_time and ubf_times...");
	#ifdef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
		b &= Test_ubf_times_functions ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= Test_ubf_times_functions ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module ubf_date_and_time and ubf_times...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Internal test of module WinAPI_U8...");
	#ifdef _WIN32
		#ifdef BUILD_TEST_WINAPI_U8_FNCT
			b &= Test_WinAPI_U8 ();
			CunilogTestFnctResultToConsole (b);
		#else
			b &= Test_WinAPI_U8 ();
			CunilogTestFnctResultToConsole (b);
			CunilogTestFnctStartTestToConsole ("Only macros tested. Internal test of module WinAPI_U8...");
			CunilogTestFnctDisabledToConsole (b);
		#endif
	#else
		CunilogTestFnctNotRequiredToConsole ();
	#endif

	CunilogTestFnctStartTestToConsole ("Internal test of module strnewline...");
	#ifdef STRNEWLINE_BUILD_TEST
		CunilogTestFnctResultToConsole (test_strnewline ());
	#else
		CunilogTestFnctDisabledToConsole (test_strnewline ());
	#endif

	CunilogTestFnctStartTestToConsole ("Internal test of module bulkmalloc...");
	#ifdef BUILD_BULKMALLOC_TEST_FUNCTIONS
		CunilogTestFnctResultToConsole (bulkmalloc_test_fnct ());
	#else
		CunilogTestFnctDisabledToConsole (bulkmalloc_test_fnct ());
	#endif

	CunilogTestFnctStartTestToConsole ("Internal test of module strintuint...");
	#ifdef UBF_BUILD_STRINTUINT_TEST
		b &= ubf_test_str_from_uint8 ();
		b &= ubf_test_str0 ();
		b &= Test_strintuint ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= ubf_test_str_from_uint8 ();
		b &= ubf_test_str0 ();
		b &= Test_strintuint ();
		// Each macro should expand to (true).
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macros tested. Internal test of module strintuint...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Internal test of module strhex...");
	#ifdef UBF_HEX_BUILD_TEST_FUNCTION
		b &= ubf_hex_test_function ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= ubf_hex_test_function ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macros tested. Internal test of module strintuint...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test module strcustomfmt...");
	#ifdef STRCUSTOMFMT_BUILD_TEST_FNCTS
		b &= TestStrCustomFmt ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= TestStrCustomFmt ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module strcustomfmt...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test module strwildcards...");
	#if STRWILDCARDS_BUILD_TEST_FNCT
		b &= strwildcards_test_function ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= strwildcards_test_function ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module strwildcards...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test module check_utf8...");
	#ifdef U_CHECK_UTF8_BUILD_TEST_FNCT
		b &= Check_utf8_test_function ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= Check_utf8_test_function ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module check_utf8...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test module ISO__DATE__...");
	#ifdef ISO_DATE_BUILD_TEST_FNCT
		b &= ISO_DATE_Test_function ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= ISO_DATE_Test_function ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module ISO__DATE__...");
	CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test module strfilesys...");
	#if BUILD_DEBUG_UBF_STRFILESYS_TESTS
		b &= ubf_test_ubf_strfilesys ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= ubf_test_ubf_strfilesys ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module strfilesys...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test module testProcesHelper...");
	#if TEST_PROCESS_HELPER_BUILD_TEST_FNCT
		b &= TestProcessHelperTestFnct ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= TestProcessHelperTestFnct ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module testProcesHelper...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Self-test of module ProcessHelpers...");
	#ifdef PROCESS_HELPERS_BUILD_TEST_FNCT
		b &= ProcessHelpersTestFnct ();
		CunilogTestFnctResultToConsole (b);
	#else
		b &= ProcessHelpersTestFnct ();
		CunilogTestFnctResultToConsole (b);
		CunilogTestFnctStartTestToConsole ("Only macro tested. Self-test module ProcessHelpers...");
		CunilogTestFnctDisabledToConsole (b);
	#endif

	CunilogTestFnctStartTestToConsole ("Testing directory reader...");
	#ifdef PLATFORM_IS_WINDOWS
		b &= ForEachDirectoryEntryMaskU8TestFnct ();
		#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
			CunilogTestFnctResultToConsole (b);
		#else
			CunilogTestFnctDisabledToConsole (b);
		#endif
	#else
		b = true;
		#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
			CunilogTestFnctDisabledToConsole (b);
		#else
			CunilogTestFnctDisabledToConsole (b);
		#endif
	#endif

	CunilogTestFnctStartTestToConsole ("Init static target with cunilogPostfixDotNumberYearly...");
	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDotNumberYearly,
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
	b &= cunilogPostfixDotNumberYearly == put->culogPostfix;
	b &= cunilogSingleThreaded == put->culogType;
	b &= !cunilogTargetHasRunProcessorsOnStartup (put) ? true : false;
	b &= !cunilogTargetHasShutdownInitiatedFlag (put) ? true : false;
	CunilogTestFnctResultToConsole (b);

	// We got no postfix. Check that this is correct.
	CunilogTestFnctStartTestToConsole ("Checking application name...");
	char *szName = memstrstr	(
		put->mbLogfileName.buf.pcc,	put->lnLogPath + put->lnAppName,
		put->mbAppName.buf.pcc,		put->lnAppName
								);
	szName += put->lnAppName;
	b &= '.' == szName [0];
	b &= 0 == memcmp (szName, szCunilogLogFileNameExtension, lenCunilogLogFileNameExtension);
	// Should be NUL-terminated.
	b &= 0 == memcmp (szName, szCunilogLogFileNameExtension, sizCunilogLogFileNameExtension);
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

	CunilogTestFnctStartTestToConsole ("Removing dummy event...");
	pev = DoneCUNILOG_EVENT (put, pev);
	CunilogTestFnctResultToConsole (NULL == pev);

	CunilogTestFnctStartTestToConsole ("Obtaining echo/console output processor...");
	cup = GetCUNILOG_PROCESSOR (put, cunilogProcessEchoToConsole, 0);
	CunilogTestFnctResultToConsole (NULL != cup && cunilogProcessEchoToConsole == cup->task);

	CunilogTestFnctStartTestToConsole ("Obtaining processor cunilogProcessUpdateLogFileName...");
	cup = GetCUNILOG_PROCESSOR (put, cunilogProcessUpdateLogFileName, 0);
	CunilogTestFnctResultToConsole (NULL != cup && cunilogProcessUpdateLogFileName == cup->task);

	CunilogTestFnctStartTestToConsole ("Obtaining rotation task cunilogrotationtask_RenameLogfiles...");
	cup = GetCUNILOG_PROCESSORrotationTask (put, cunilogrotationtask_RenameLogfiles, 0);
	CunilogTestFnctResultToConsole (NULL != cup);

	stTestState = 1;
	logTextU8_static ("cunilogPostfixDotNumberYearly");

	CunilogTestFnctStartTestToConsole ("Shutting down static target...");
	ShutdownCUNILOG_TARGETstatic ();
	b &= cunilogTargetHasShutdownCompleteFlag (put) ? true : false;
	CunilogTestFnctResultToConsole (b);

	CunilogTestFnctStartTestToConsole ("Destroying target...");
	put = DoneCUNILOG_TARGETstatic ();
	CunilogTestFnctResultToConsole (NULL == put);

	stTestState = 2;

	/*
		A standard sequence of:
		<appname>.log
		<appname>_YYYY-MM-DD hh:mi.log
	*/
	CunilogTestFnctStartTestToConsole ("New target to check LogPostfix...");
	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixLogMinute,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
										);
	CunilogTestFnctResultToConsole (NULL != put);
	if (NULL == put)
		return false;
	cunilogTargetSetAlwaysCallErrorCB (put);
	CunilogTestFnctStartTestToConsole ("Callback function set correctly...");
	ConfigCUNILOG_TARGETerrorCallbackFunction (put, CunilogTestFnctErrCallback0002);
	CunilogTestFnctResultToConsole (CunilogTestFnctErrCallback0002 == put->errorCB);
	// stTestState == 2 here.
	CunilogTestFnctStartTestToConsole ("Invokation of callback function...");
	logTextU8 (put, "cunilogPostfixLogMinute");
	ShutdownCUNILOG_TARGET (put);
	DoneCUNILOG_TARGET (put);

	// Test sequence point 1.

	CunilogTestFnctStartTestToConsole ("Creation of another simple target...");
	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixMinute,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
										);
	CunilogTestFnctResultToConsole (NULL != put);
	if (NULL == put)
		return false;
	logTextU8 (put, "Writing to another simple target. There's no callback function, by the way.");
	ShutdownCUNILOG_TARGET (put);
	DoneCUNILOG_TARGET (put);

	// Test sequence point 2.

	CunilogTestFnctStartTestToConsole ("Checking absolute path validation...");
	put = CreateNewCUNILOG_TARGET		(
				ccLogsFolder, lnLogsFolder,
				"MyApp", USE_STRLEN,
				cunilogPath_isAbsolute,
				cunilogSingleThreaded,
				cunilogPostfixDotNumberYearly,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
										);
	CunilogTestFnctResultToConsole (NULL == put);

	CunilogTestFnctStartTestToConsole ("Creating new target...");
	put = CreateNewCUNILOG_TARGET		(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDotNumberYearly,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
										);
	ubf_assert_non_NULL (put);
	CunilogTestFnctResultToConsole (NULL != put);

	CunilogTestFnctStartTestToConsole ("New target initislised...");
	CunilogTestFnctResultToConsole (cunilogIsTargetInitialised (put));


	CunilogTestFnctStartTestToConsole ("Do we have a path?");
	szAbsPath = GetAbsoluteLogPathCUNILOG_TARGET (put, &len);
	CunilogTestFnctResultToConsole (NULL != szAbsPath);

	cunilogTargetSetAlwaysCallErrorCB (put);
	ConfigCUNILOG_TARGETerrorCallbackFunction (put, CunilogTestFnctErrCallback0002);

	CunilogTestFnctStartTestToConsole ("Checking target members...");
	b &= NULL != put->cprocessors;
	b &= CunilogTestFnctErrCallback0002 == put->errorCB;
	b &= cunilogPostfixDotNumberYearly == put->culogPostfix;
	b &= cunilogSingleThreaded == put->culogType;
	b &= cunilogTargetHasRunProcessorsOnStartup (put) ? true : false;
	b &= !cunilogTargetHasShutdownInitiatedFlag (put) ? true : false;
	CunilogTestFnctResultToConsole (b);

	CunilogTestFnctStartTestToConsole ("Issuing test event... (nothing to test here)");
	CunilogTestFnctResultToConsole (true);
	b &= logTextU8 (put, "cunilogPostfixDotNumberYearly - Next level");
	CunilogTestFnctStartTestToConsole ("Test event issued.");
	CunilogTestFnctResultToConsole (b);

	CunilogTestFnctStartTestToConsole ("Shutting down target...");
	ShutdownCUNILOG_TARGET (put);
	b &= cunilogTargetHasShutdownCompleteFlag (put) ? true : false;
	CunilogTestFnctResultToConsole (b);

	DoneCUNILOG_TARGET (put);

	CunilogTestFnctStartTestToConsole ("Testing directory reader...");
	#ifdef PLATFORM_IS_WINDOWS
		b &= ForEachDirectoryEntryMaskU8TestFnct ();
		#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
			CunilogTestFnctResultToConsole (b);
		#else
			CunilogTestFnctDisabledToConsole (b);
		#endif
	#else
		b = true;
		#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
			CunilogTestFnctDisabledToConsole (b);
		#else
			CunilogTestFnctDisabledToConsole (b);
		#endif
	#endif

	//ASSERT (false);

	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
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

	logTextU8_static ("This one's in UTF-8 (\xC5\x98), which should be an \"R\" with a flipped roof (U+0158).");
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
