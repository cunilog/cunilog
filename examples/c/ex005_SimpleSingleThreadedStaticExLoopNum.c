/****************************************************************************************

	File:		Example file for Cunilog
	Why:		Example file for Cunilog
	OS:			C99.
	Author:		Thomas
	Created:	2026-03-23

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2026-03-23	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This code is in the public domain.
*/

#include "../../src/c/combined/cunilog_combined.h"

int main (int argc, char *argv[])
{
	CUNILOG_TARGET		*ct;
	SMEMBUF				mbAppName	= SMEMBUF_INITIALISER;
	ObtainAppNameFromExecutableModule (&mbAppName);
	
	const char			*szAppName	= mbAppName.buf.pcc;
	
	/*
		Use the ...Ex () function to allow for more options.

		The postfix cunilogPostfixDotNumberMinutely is the most
		inefficient way to rotate log files, as the entire list requires
		to be renamed with every rotation.
	*/
	ct = InitCUNILOG_TARGETstaticEx	(
			"../../logs",	USE_STRLEN,
			szAppName,		USE_STRLEN,
			cunilogPath_relativeToExecutable,
			cunilogSingleThreaded,
			cunilogPostfixDotNumberMinutely,	// A new .number every minute.
			NULL, 0,							// Use standard processors.
			cunilogEvtTS_Default,
			cunilogNewLineSystem,
			cunilogRunProcessorsOnStartup
									);
	if (NULL == ct)
	{
		cunilog_puts_sev_fmtpy	(
			cunilogEvtSeverityError, cunilogEvtSeverityFormatChars9InTightBrackets,
			"InitCUNILOG_TARGETstatic ()."
								);
		return EXIT_FAILURE;
	}
	
	unsigned int ui = 0;
	while (ui < 10000)
	{
		if (0 == ui % 10)
			logTextU8sfmtsev_static (cunilogEvtSeverityWarning, "This could be a warning.");
		else
			logTextU8fmt_static ("This is event number %d.", ui);
		Sleep_s (1);
		
		++ui;
	}
}
