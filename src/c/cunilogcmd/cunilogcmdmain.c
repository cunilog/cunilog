/****************************************************************************************

	File:		cunilogcmdmain.c
	Why:		Main entry point of cunilogcmd.
	OS:			C99.
	Author:		Thomas
	Created:	2024-08-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-11	Thomas			Created.

****************************************************************************************/

#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#include "./cunilog_combined.h"
#else
	#include "./../combined/cunilog_combined.h"
#endif

#include "./cunilogcmdmain.h"

	char	cHelpMessage [] =

			CUNILOG_PROGRAM_NAME " - " CUNILOG_PROGRAM_DESCR " " CUNILOG_VERSION_STRING " - built "_ISO_DATE_" "__TIME__"\n"
			"\n"
#ifdef _DEBUG
			"*** Debug version ***\n\n"
#endif
			//"Contact: " PROGRAM_EMAIL "\n\n"
			"Invocation:\n"
			CUNILOG_PROGRAM_NAME " [<path>/]<appname> [<params>] <text to log>\n"
			CUNILOG_PROGRAM_NAME " ?                                   Displays this help text\n"
			CUNILOG_PROGRAM_NAME " /?                                  Displays this help text\n"
			CUNILOG_PROGRAM_NAME " [-]h[elp]                           Displays this help text\n"
			CUNILOG_PROGRAM_NAME " [-]inst[all]   configfile <params>  Installs the service\n"
			CUNILOG_PROGRAM_NAME " [-]unins[tall] configfile <params>  Uninstalls/removes the service\n"
			CUNILOG_PROGRAM_NAME " [-]rem[ove]    configfile <params>  Uninstalls/removes the service\n"
			CUNILOG_PROGRAM_NAME " [-]del[ete]    configfile <params>  Uninstalls/removes the service\n"
			CUNILOG_PROGRAM_NAME " [-]deb[ug]     configfile <params>  Run as console app for debugging\n"
			CUNILOG_PROGRAM_NAME " [-]con[sole]   configfile <params>  Run as console app for debugging\n"
			"\n"
			"<params>:\n"
			"\t/A            Sets service start type to automatic.\n"
			"\t/AD           Sets service start type to automatic delayed.\n"
			"\t/S            Starts the service after installation.\n"
			"\t/U:<username> Uses this account instead of the local system\n"
			"\t              account.\n"
			"\t/P:<password> Password for account <username>.\n"
			"\t/RunOnce      Only processes every task once and then\n"
			"\t              exits.\n"
			"\t/v            Verbose output\n";

	char	cServiceDispatcherMsg [] =
			"\nStartServiceCtrlDispatcher being called.\n"
			"This may take several seconds.  Please wait.\n";


	char	cStartMessage [] =
			"*** " CUNILOG_PROGRAM_DESCR " (start up) " CUNILOG_VERSION_STRING " - built "_ISO_DATE_" "__TIME__" ***";

	char	cStartErrorMessage []	=
			"Error: Service start failed.";
	

int cunilog_main (int argc, char *argv [])
{
	replace_ISO_DATE_ (cHelpMessage, USE_STRLEN);

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_IS_WINDOWS
	void main (void)
	{
		AttachConsole (ATTACH_PARENT_PROCESS);
		SetConsoleCodePageToUTF8 ();

		// The command-line arguments.
		int			nArgs;									// Amount of arguments.
		WCHAR		**wcArgs = CmdLineArgsW (&nArgs);		// Array of arguments.
		/*
			We don't want the executable argument. This is slightly complicated
			on Windows since it could be missing already, depending on how the
			executable was invoked.
		*/
		SwallowExeArgumentW (&nArgs, &wcArgs);				// Suppress the executable.
		/*
			The variable nArgs now contains the amount of arguments with the executable
			argument removed.
			The array wcArgs [0] ... wcArgs [nArgs - 1] are the arguments (command-line
			parameters), with the parameter (argument) that points to the executable removed.
		*/

		// We captured the command-line arguments in UTF-16 to not lose characters.
		//	However, we want everything in UTF-8.
		char **args = AllocU8ArgsFromWinU16 (nArgs, wcArgs);
		int r = cunilog_main (nArgs, args);
		ExitProcess (r);
	}
#else
	int main (int argc, char *argv [])
	{
		/*
			We don't want the executable argument.
			This is so much easier on POSIX.
		*/
		if (argc)
		{
			++ argv;
			-- argc;
		}
		return cunilog_main (argc, argv);
	}
#endif
