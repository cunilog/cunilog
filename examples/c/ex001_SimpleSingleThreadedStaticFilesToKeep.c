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
2026-03-24	Thomas			Created.

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
		This example demonstrates how to use the simple target initialiser
		InitCUNILOG_TARGETstatic () and change the processors afterwards.
		
		The preferred way to do this, however, it to create the processors
		first and then initialise the target with InitCUNILOG_TARGETstaticEx ().
	*/
	ct = InitCUNILOG_TARGETstatic	(
			"../../logs",	USE_STRLEN,
			szAppName,		USE_STRLEN,
			cunilogPath_relativeToExecutable,
			cunilogSingleThreaded
									);
	if (NULL == ct)
	{
		cunilog_puts_sev_fmtpy	(
			cunilogEvtSeverityError, cunilogEvtSeverityPrfxChars9InTightBrackets,
			"InitCUNILOG_TARGETstatic ()."
								);
		return EXIT_FAILURE;
	}
	
	/*
		We want to keep 3 logfiles uncompressed and 5 compressed.
		For this, we'll have to create new processors and configure them accordingly.
		No logging function must have been called at this point.
	*/

	// Destroy target's current processors.
	DoneCUNILOG_TARGETprocessors (ct);
	
	// Create new processors.
	unsigned int nprocessors;
	CUNILOG_PROCESSOR **processors = CreateNewDefaultProcessors (&nprocessors);
	if (NULL == processors)
	{
		cunilog_puts_sev_fmtpy	(
			cunilogEvtSeverityError, cunilogEvtSeverityPrfxChars9InTightBrackets,
			"CreateNewDefaultProcessors ()."
								);
								
		// Not required in this example but recommended.
		DoneCopyCUNILOG_PROCESSORs (processors);
		DoneCUNILOG_TARGET_static ();
		
		return EXIT_FAILURE;
	}
	
	// Keep 3 logfiles uncompressed and 5 compressed.
	ConfigCUNILOG_PROCESSORnLogFiles (processors, nprocessors, 3, 5);
	
	// Attach our new processors to the target.
	ConfigCUNILOG_TARGETprocessorList (ct, processors, nprocessors);
	
	// Create the "logs" folder, if it doesn't exist.
	CunilogCreateAllFolders (ct->mbLogPath.buf.pcc, USE_STRLEN);

	unsigned int ui = 1;
	unsigned int mx = 1000;
	while (mx + 1 > ui)
	{
		logTextU8fmt_static ("This is event number %u. We still got %u more to go.", ui, mx - ui);
		Sleep_s (1);
		++ui;
	}
	// Not required in this example but recommended.
	DoneCUNILOG_TARGET_static ();
	DoneCopyCUNILOG_PROCESSORs (processors);
}
