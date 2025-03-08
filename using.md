
# Using Cunilog

## Building and linking

This brief introduction assumes that you either add the two combined source code files
__cunilog_combined.h__ and __cunilog_combined.c__ in folder __src/c/combined__
to your project and compile them as part of it, or that you build libcunilog, link your application to it, and only add __cunilog_combined.h__ to your project.

Another option would be that you add all files separately but this might be a bit more work.

Details and differences between the available build and link options can be found on page [Building Cunilog](building.md)

## Interface

Include __cunilog_combined.h__ to access Cunilog's interface.
All necessary constants, enumerations, functions, macros, and structures should be
readily accessible from C and C++. There's currently (January 2025) no bindings
for other languages.

## Logging

We assume that you only intend to log/write to a single log file, from a
single process, but possibly from different threads. Cunilog supports writing
to different log files or writing to the same log file from different processes
but we won't cover those cases in this brief introduction.

Example for using the internal static structure:
```C
// Application start

SCUNILOGTARGET *put = InitSUNILOGTARGETstatic	(
			"logs", 4,
			"MyApp", USE_STRLEN,
			cunilogLogPath_relativeToHomeDir,
			cunilogMultiThreadedSeparateLoggingThread
						);
if (NULL == put)
{
	// InitSUNILOGTARGETstatic () failed.
	exit (EXIT_FAILURE);
}

// Use the log...static () family of functions and macros for logging.
logTextU8_static ("A simple line to go in the logfile.");
logTextU8l_static ("Another line.", 13);
logTextU8l_static ("And another one.", USE_STRLEN);

// Just before the application exists shut down logging and deallocate its resources.
ShutdownSCUNILOGTARGETstatic ();		// Blocks until the queue is empty.
DoneSUNILOGTARGETstatic ();
```

Here's the signature of the InitSUNILOGTARGETstatic () function:
```C
/*
	InitSCUNILOGTARGETstatic

	Simplified version of InitSCUNILOGTARGETstaticEx ().

	szLogPath	The path where the log files are written to. This can either be an
			absolute or a relative path. If the path is relative, it is assumed to
			be relative to what the enumeration parameter relLogPath specifies.
			If this parameter is NULL, the function picks a folder according to
			what the enumeration parameter relLogPath specifies, or the function
			fails.
			This string does not have to be NUL-terminated if lenLogPath is given
			correctly and not as (size_t) -1 (or USE_STRLEN).

	lenLogPath	The length of szLogPath. If this parameter is (size_t) -1, the function
			calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
			(size_t) -1. If this parameter is 0, the function uses the executable
			module's path.

	szAppName	The name of the application. This is the part of the log file's name
			before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
			If this parameter is NULL, the function uses the executable module's name.
			The string does not need to be NUL-terminated if lenAppName holds the
			correct length.

	lenAppName	The length of szApplication. If this parameter is (size_t) -1, the
			function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
			as (size_t) -1.
			If this parameter is 0, the function uses the executable module's name.

	relLogPath	One of the values in the enCunilogRelLogPath enumeration that specify
			the base path if szLogPath is either relative or NULL. If szLogPath is
			relative, the path is relative to
			cunilogLogPath_relativeToExecutable (the executable file),
			cunilogLogPath_relativeToCurrentDir (the current directory), or
			cunilogLogPath_relativeToHomeDir (the user's home directory).
			See cunilogstructs.h for details.
			The value of this parameter is ignored if szLogPath is an absolute
			path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
			relative path or NULL, the function fails.

	type		The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
			If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
			ignored and implicitely set to cunilogSingleThreaded.

	The function returns a pointer to the internal SCUNILOGTARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneSCUNILOGTARGETstatic () to free the structure's resources.
*/
SCUNILOGTARGET *InitSCUNILOGTARGETstatic
(
	  const char			*szLogPath	// Path to the logging information.
	, size_t			lenLogPath	// Length of szLogPath
	, const char			*szApplication	// Application name.
	, size_t			lenApplication	// Length of szApplication.
	, enCunilogRelLogPath		relLogPath	// Rel. to home, exe, or current dir.
	, enum cunilogtype		type
)
;
```
