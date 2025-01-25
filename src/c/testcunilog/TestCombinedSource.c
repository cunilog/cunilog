/****************************************************************************************

	File		TestCombinedSource.c
	Why:		To test the combined source and header files.
	OS:			-
	Created:	2024-07-19

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-07-19	Thomas			Created.

****************************************************************************************/

#include "./../combined/cunilog_combined.h"
#include "./TestCombinedSource.h"

const char	ccLogsFolder []	= STR_LOGS_FOLDER;
size_t		lnLogsFolder	= sizeof (ccLogsFolder) - 1;

#define ourLogText(txt)	logTextU8_static (txt)

int main (void)
{
	SCUNILOGTARGET *put;
	put = InitSCUNILOGTARGETstaticEx	(
				ccLogsFolder, lnLogsFolder,
				NULL, 0,
				cunilogLogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDefault,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
										);
	if (!put)
	{
		puts ("InitSUNILOGTARGETstatic () failed.");
		return EXIT_FAILURE;
	}

	ourLogText ("A simple line to go in the logfile.");
	
	ShutdownSCUNILOGTARGETstatic ();
	DoneSCUNILOGTARGETstatic ();
}
