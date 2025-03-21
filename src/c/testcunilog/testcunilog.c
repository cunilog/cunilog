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

// For testing.
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

bool testV (SCUNILOGTARGET *put, char *sz, ...)
{
	va_list ap;

	va_start (ap, sz);
	bool b = logTextU8vfmt (put, sz, ap);
	va_end (ap);
	return b;
}

int main (int argc, char *argv [])
{
	UNREFERENCED_PARAMETER (argc);
	UNREFERENCED_PARAMETER (argv);

	//CunilogSetConsoleToUTF16 ();
	//CunilogSetConsoleToNone ();

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
		End of tests.
	*/

	//ubf_assert (false);

	bool			b		= test_cunilog ();
	ubf_assert_true (b);

	SCUNILOGTARGET	*put;

	put = InitSCUNILOGTARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogLogPath_relativeToExecutable,
				cunilogMultiThreadedSeparateLoggingThread,
				cunilogPostfixDotNumberDescending,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
									);

	logTextU8_static ("cunilogPostfixDotNumberDescending");

	ShutdownSCUNILOGTARGETstatic ();
	DoneSCUNILOGTARGETstatic ();


	put = InitSCUNILOGTARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogLogPath_relativeToExecutable,
				cunilogMultiThreadedSeparateLoggingThread,
				cunilogPostfixMinute,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
									);

	//configSCUNILOGTARGETdisableEchoProcessor (put);
	UNREFERENCED_PARAMETER (put);
	//b &= SetLogPrioritySCUNILOGTARGET (put, cunilogPrioIdle);
	ubf_assert_true (b);

	logTextU8_static ("");
	logTextU8_static ("----------");
	logTextU8_static (STR_HELLO_FROM_EXE);
	logTextU8_static ("A simple line to go in the logfile.");
	logTextU8fmt_static ("Log folder: %s", GetAbsoluteLogPathSCUNILOGTARGET_static (NULL));
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
	PauseLogSCUNILOGTARGETstatic ();
	cunilog_puts ("Sleeping (1)...");
	Sleep (2000);
	n = 1000;
	while (n --)
	{
		logTextU8_static ("Another simple line to go in the logfile (second batch).");
	}
	cunilog_puts ("Sleeping (2)...");
	Sleep (2000);
	ResumeLogSCUNILOGTARGETstatic ();

	logTextU8_static ("This one's in UTF-16 (\xC5\x98), which should be an \"R\" with a flipped roof.");
	testV (put, "Hello %i", 20);
	logTextU8sev_static (cunilogEvtSeverityDebug, "This is a debug message");
	logTextU8sev_static (cunilogEvtSeverityCritical, "This is a critical message");
	ChangeSCUNILOGTARGETuseColourForEcho_static (false);
	logTextU8sev_static (cunilogEvtSeverityCritical, "This is also a critical message");
	ChangeSCUNILOGTARGETlogPriority_static (cunilogPrioBelowNormal);
	ChangeSCUNILOGTARGETlogPriority_static (cunilogPrioNormal);
	ChangeSCUNILOGTARGETuseColourForEcho_static (true);
	logTextU8sev_static (cunilogEvtSeverityCritical, "This is another critical message");

	logTextU8sev_static (cunilogEvtSeverityNonePass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityNoneFail, "This is a bad one");
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeSCUNILOGTARGETeventSeverityFormatType (pSCUNILOGTARGETstatic, cunilogEvtSeverityTypeChars3InBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeSCUNILOGTARGETeventSeverityFormatType (pSCUNILOGTARGETstatic, cunilogEvtSeverityTypeChars5InBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeSCUNILOGTARGETeventSeverityFormatType (pSCUNILOGTARGETstatic, cunilogEvtSeverityTypeChars9InBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	ChangeSCUNILOGTARGETeventSeverityFormatType (pSCUNILOGTARGETstatic, cunilogEvtSeverityTypeChars5InTightBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	logTextU8sev_static (cunilogEvtSeverityNone, "None");
	logTextU8sev_static (cunilogEvtSeverityBlanks, "Blanks");
	ChangeSCUNILOGTARGETeventSeverityFormatType (pSCUNILOGTARGETstatic, cunilogEvtSeverityTypeChars9InTightBrackets);
	logTextU8sev_static (cunilogEvtSeverityPass, "This is a good one");
	logTextU8sev_static (cunilogEvtSeverityFail, "This is a bad one");
	logTextU8sev_static (cunilogEvtSeverityNone, "None");
	logTextU8sev_static (cunilogEvtSeverityBlanks, "Blanks");

	logTextU8c_static ("This text only goes to the console");
	logTextU8_static ("This one doesn't");

	/*
	Sleep (2000);
	puts (STR_ANSI_FGCOL_BRIGHT_GREEN "This is the text we test the attributes with." STR_ANSI_RESET);
	*/

	/*
	Sleep (2000);
	puts ("This one's in UTF-16 (\xC5\x98), which should be an \"R\" with a flipped roof.");
	*/

	//CancelSCUNILOGTARGETstatic ();
	ShutdownSCUNILOGTARGETstatic ();
	DoneSCUNILOGTARGETstatic ();

	return b ? EXIT_SUCCESS : EXIT_FAILURE;	
}
