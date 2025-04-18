/****************************************************************************************

	File:		testcunilog.c
	Why:		Test application for cunilog.
	OS:			C99.
	Author:		Thomas
	Created:	2024-07-09

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-07-09	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This code is public domain.
*/

#include "./testcunilog.h"
#include "./../cunilog/cunilog.h"
#include "./CunilogTestFncts.h"

// For testing here.
#include "./../datetime/ISO__DATE__.h"
#include "./../datetime/ubf_date_and_time.h"
#include "./../dbg/ubfdebug.h"
#include "./../string/stransi.h"
#include "./../string/strfilesys.h"
#include "./../string/strhexdump.h"
#include "./../string/strintuint.h"
#include "./../string/strnewline.h"
#include "./../string/strwildcards.h"
#include "./../cunilog/cunilogcfgparser.h"
#include "./../string/strcustomfmt.h"
#include "./../OS/POSIX/PsxHome.h"

#ifndef _WIN32
	#include <unistd.h>
	
	#ifndef Sleep
	#define Sleep(s)									\
		sleep ((s) / 1000)
	#endif
#endif

#ifdef PLATFORM_IS_WINDOWS
	#include "./../OS/Windows/WinAPI_U8.h"
#endif

const char	ccLogsFolder []	= STR_LOGS_FOLDER;
size_t		lnLogsFolder	= sizeof (ccLogsFolder) - 1;

int main (int argc, char *argv [])
{
	UNREFERENCED_PARAMETER (argc);
	UNREFERENCED_PARAMETER (argv);

	//CunilogSetConsoleToUTF16 ();
	//CunilogSetConsoleToNone ();

	bool b = true;

	cunilog_puts ("Testing Cunilog...");
	cunilog_puts ("");

	CunilogTestFnctStartTestToConsole ("Basic internal tests...");
	b &= test_cunilog ();
	#ifdef CUNILOG_BUILD_TEST_FNCTS
		ubf_assert_true (b);
		CunilogTestFnctResultToConsole (b);
	#else
		CunilogTestFnctDisabledToConsole (b);
	#endif


	/*
		Tests.
	*/

	TestCunilogCfgParser ();
	test_strnewline ();
	test_strhexdump ();
	Test_ubf_times_functions ();
	Test_strintuint ();
	strwildcards_test_function ();
	ubf_test_ubf_strfilesys ();
	const char *szBld = szBuild_ISO__DATE__ ();
	ubf_assert (LEN_ISO8601DATE == strlen (szBld));
	szBld = szBuild_ISO__DATE__TIME__ ();
	ubf_assert (LEN_ISO8601DATETIMESTAMP_NO_OFFS == strlen (szBld));
	TestStrCustomFmt ();
	TestPsxHome ();

	/*
	cunilog_printf_sev_fmtpy (cunilogEvtSeverityBlanks, cunilogEvtSeverityTypeChars3, "cunilog_printf_sev_fmtpy ()");
	cunilog_printf_sev (cunilogEvtSeverityBlanks, "cunilog_printf_sev ()");
	cunilog_printf ("This is from cunilog_printf ()");
	cunilog_printf ("And so is this.\n");
	cunilog_printf_sev (cunilogEvtSeverityNonePass, "Pass ");
	cunilog_printf_sev (cunilogEvtSeverityNoneFail, "Fail ");
	cunilog_printf_sev (cunilogEvtSeverityNonePass, "Pass ");
	cunilog_printf_sev (cunilogEvtSeverityNonePass, "Pass again\n");
	cunilog_puts ("Output");
	cunilog_puts_sev (cunilogEvtSeverityCritical, "Not good.");
	cunilog_puts_sev_fmtpy_l (cunilogEvtSeverityFatal, cunilogEvtSeverityTypeChars5, "Not good either", USE_STRLEN);
	cunilog_puts_sev (cunilogEvtSeverityNonePass, "Pass ");
	cunilog_puts_sev (cunilogEvtSeverityNoneFail, "Fail ");
	*/

	/*
		End of tests.
	*/

	//ubf_assert (false);

	b = CunilogTestFunction	(
			ccLogsFolder, lnLogsFolder, STR_HELLO_FROM_EXE
							);

	return b ? EXIT_SUCCESS : EXIT_FAILURE;	
}
