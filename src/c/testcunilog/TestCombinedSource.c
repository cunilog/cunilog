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

#include "./TestCombinedSource.h"
#include "./../combined/cunilog_combined.h"
#include "./CunilogTestFncts.h"

const char	ccLogsFolder []	= STR_LOGS_FOLDER;
size_t		lnLogsFolder	= sizeof (ccLogsFolder) - 1;

#define ourLogText(txt)	logTextU8_static (txt)

int main (int argc, char *argv [])
{
	UNREFERENCED_PARAMETER (argc);
	UNREFERENCED_PARAMETER (argv);

	bool b = true;

	cunilog_puts ("Testing Cunilog...");
	cunilog_puts ("");

	CunilogTestFnctStartTestToConsole ("Basic internal tests...");
	b &= test_cunilog ();
	ubf_assert_true (b);
	CunilogTestFnctResultToConsole (b);

	b = CunilogTestFunction	(
			ccLogsFolder, lnLogsFolder, STR_HELLO_FROM_EXE
							);

	return b ? EXIT_SUCCESS : EXIT_FAILURE;	
}
