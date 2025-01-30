/****************************************************************************************

	Project:	Cunilog
	File:		testwinunicode.c
	Why:		
	OS:			
	Autor:		Thomas
	Created:	2025-01-30
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-30	Thomas			Created.

****************************************************************************************/

/*
	This code is public domain.
*/

#include "./../combined/cunilog_combined.h"
#include "./testwinunicode.h"

void wmain (void)
{

	CunilogSetConsoleToUTF8 ();

	SCUNILOGTARGET	*put;

	put = InitSCUNILOGTARGETstatic	(
			STR_LOGS_FOLDER, USE_STRLEN,
			NULL, 0,
			cunilogLogPath_relativeToExecutable, cunilogSingleThreaded
									);
	if (!put)
		return;

	logTextU8_static ("");
	logTextU8_static ("----------");
	logTextU8_static (STR_HELLO_FROM_EXE);
	logTextU8_static ("A simple line to go in the logfile.");

	logTextWU16_static (L"This one's in UTF-16 (\u0158), which should be an \"R\" with a flipped roof.");

	ShutdownSCUNILOGTARGETstatic ();
	DoneSCUNILOGTARGETstatic ();
}
