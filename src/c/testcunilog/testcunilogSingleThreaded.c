/****************************************************************************************

	File:		testcunilogSingleThreaded.c
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
	This code is public domain.
*/

#include "./testcunilogSingleThreaded.h"
#include "./../cunilog/cunilog.h"
#include "./../datetime/ISO__DATE__.h"
#include "./../dbg/ubfdebug.h"

#ifndef _WIN32
	#include <unistd.h>
	
	#ifndef Sleep
	#define Sleep(s)									\
		sleep ((s) / 1000)
	#endif
#endif

const char	ccLogsFolder []	= STR_LOGS_FOLDER;
size_t		lnLogsFolder	= sizeof (ccLogsFolder) - 1;

bool testV (CUNILOG_TARGET *put, char *sz, ...)
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

	//TestCunilogCfgParser ();
	test_strnewline ();
	test_strhexdump ();
	//Test_ubf_times_functions ();
	Test_strintuint ();
	//strwildcards_test_function ();
	//ubf_test_ubf_strfilesys ();
	const char *szBld = szBuild_ISO__DATE__ ();
	ubf_assert (LEN_ISO8601DATE == strlen (szBld));
	szBld = szBuild_ISO__DATE__TIME__ ();
	ubf_assert (LEN_ISO8601DATETIMESTAMP_NO_OFFS == strlen (szBld));
	//TestStrCustomFmt ();
	//TestPsxHome ();

	/*
		End of tests.
	*/

	//ubf_assert (false);

	bool			b		= test_cunilog ();
	ubf_assert_true (b);

	CUNILOG_TARGET	*put;

	put = InitCUNILOG_TARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDotNumberMinutely,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
									);

	logTextU8_static ("cunilogPostfixDotNumberMinutely");

	ShutdownCUNILOG_TARGETstatic ();
	DoneCUNILOG_TARGETstatic ();


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

	//configSCUNILOGTARGETdisableEchoProcessor (put);
	UNREFERENCED_PARAMETER (put);
	//b &= SetLogPrioritySCUNILOGTARGET (put, cunilogPrioIdle);
	ubf_assert_true (b);

	logTextU8_static ("");
	logTextU8_static ("----------");
	logTextU8_static (STR_HELLO_FROM_EXE);
	logTextU8_static ("A simple line to go in the logfile.");
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

	/*
	Sleep (2000);
	puts ("This one's in UTF-16 (\xC5\x98), which should be an \"R\" with a flipped roof.");
	*/

	//CancelSCUNILOGTARGETstatic ();
	ShutdownCUNILOG_TARGETstatic ();
	DoneCUNILOG_TARGETstatic ();

	return b ? EXIT_SUCCESS : EXIT_FAILURE;	
}
