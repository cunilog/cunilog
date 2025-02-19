/****************************************************************************************

	File:		cunilog.h
	Why:		Interface functions for cunilog.
	OS:			C99.
	Author:		Thomas
	Created:	2022-10-05

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-10-05	Thomas			Created.

****************************************************************************************/

/*
	1. Create a SCUNILOGTARGET structure and initialise it. Use either your own structure
		or create a new one with CreateNewSUNILOGTARGET () or InitOrCreateSUNILOGTARGET ().
		Or use the internal structure of this module with InitSUNILOGTARGETstatic () instead.
		The latter is most likely what you want.

	2. Use the logging functions repeatedly as you please. Depending on the member unilogType
		of the SCUNILOGTARGET structure, you might do this from a single or multiple
		threads.

	4. When not required anymore, probably just before the application exits, call
		ShutdownSCUNILOGTARGET () or ShutdownSCUNILOGTARGETstatic, depending on the structure
		you used. Call DoneSUNILOGTARGET () on the the SCUNILOGTARGET structure afterwards,
		or call DoneSUNILOGTARGETstatic () if the internal structure was used.

		Example for internal static structure:

		// Application start
		InitSUNILOGTARGETstatic (...);

		// Use the log...static () family of functions and macros for logging.
		logTextU8_static (...);

		// Just before the application exists shut down logging and deallocate its resources.
		ShutdownSCUNILOGTARGETstatic ();
		DoneSUNILOGTARGETstatic ();
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024, 2025 Thomas

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify,
	merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be included in all copies
	or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef CUNILOG_H
#define CUNILOG_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../pre/externC.h"
	#endif

	#include "./cunilogversion.h"
	#include "./cunilogstructs.h"

#endif

// To build the test functions.
#ifndef CUNILOG_BUILD_TEST_FNCTS
#define CUNILOG_BUILD_TEST_FNCTS
#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

// Failure return value for (size_t).
#ifndef CUNILOG_SIZE_ERROR
#define CUNILOG_SIZE_ERROR				((size_t) -1)
#endif

#ifndef CUNILOG_UNKNOWN_ERROR
#define CUNILOG_UNKNOWN_ERROR			(-1)
#endif

// Value of member nMaxToRotate of a CUNILOG_ROTATION_DATA structure to be obtained
//	during initialisation.
#ifndef CUNILOG_MAX_ROTATE_AUTO
#define CUNILOG_MAX_ROTATE_AUTO			(UINT64_MAX)
#endif

// Memory alignments. Use 16 octets/bytes for 64 bit platforms.
#if defined (_WIN64) || defined (__x86_64__)
	#define CUNILOG_DEFAULT_ALIGNMENT	(16)
#else
	#define CUNILOG_DEFAULT_ALIGNMENT	(8)
#endif

// Our standard size for error messages on the stack.
#define CUNILOG_STD_MSG_SIZE			(256)

// Our standard size for bulk memory allocations.
#define CUNILOG_STD_BULK_ALLOC_SIZE		(4096 - sizeof (SBULKMEMBLOCK))

// The size we're going to expand the vector containing the names of logfiles.
#define CUNILOG_STD_VECT_EXP_SIZE		(128)

// The stack/heap threshold for the ...sfmt type logging functions.
#ifndef CUNILOG_DEFAULT_SFMT_SIZE
#define CUNILOG_DEFAULT_SFMT_SIZE		(256)
#endif

/*
	The default initial size of an event line. Note that this is not the space for the text
	but rather the entire line, including timestamp etc. If you know in advance that your
	texts (including stamp etc) are going to be longer you may override this with a higher
	value to possibly save some initial heap reallocations.

	This value must be greater than 0.
*/
#ifndef CUNILOG_INITIAL_EVENTLINE_SIZE
#define CUNILOG_INITIAL_EVENTLINE_SIZE			(256)
#endif

#if CUNILOG_INITIAL_EVENTLINE_SIZE <= 0
	#error CUNILOG_INITIAL_EVENTLINE_SIZE must be greater than zero
#endif

/*
	The default initial size of an event line that contains ANSI colour codes for severity
	levels plus the event line itself.
	If you know in advance that your texts (including stamp etc) are going to be longer you
	may override this with a higher value to possibly save some initial heap reallocations.
	The default is CUNILOG_INITIAL_EVENTLINE_SIZE.

	This value must be greater than 0.

	If you don't need coloured console output for severity levels you can switch it off by
	defining CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR or CUNILOG_BUILD_WITHOUT_CONSOLE_COLOR.
*/
#ifdef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOR
	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#define CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#endif
#endif
#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#ifndef CUNILOG_INITIAL_COLEVENTLINE_SIZE
	#define CUNILOG_INITIAL_COLEVENTLINE_SIZE		(CUNILOG_INITIAL_EVENTLINE_SIZE)
	#endif
	#if CUNILOG_INITIAL_COLEVENTLINE_SIZE <= 0
		#error CUNILOG_INITIAL_COLEVENTLINE_SIZE must be greater than zero
	#endif
#endif

// Literally an arbitray character. This is used to find buffer overruns in debug
//	versions.
#ifndef CUNILOG_DEFAULT_DBG_CHAR
#define CUNILOG_DEFAULT_DBG_CHAR		'\x17'
#endif

// The spin count for the critical section on Windows.
#ifndef CUNILOG_WINDOWS_CRITICAL_SECTION_SPIN_COUNT
#define CUNILOG_WINDOWS_CRITICAL_SECTION_SPIN_COUNT		(5000)
#endif

// This seems to make sense.
#define requiresSCUNILOGTARGETseparateLoggingThread(p) hasSCUNILOGTARGETqueue (p)

// The mode for opening the current logfile.
#ifdef PLATFORM_IS_WINDOWS
	#define CUNILOG_DEFAULT_OPEN_MODE	(FILE_APPEND_DATA)
	/*
		pl->hLogFile = CreateFileU8	(
						szLogFileName, GENERIC_WRITE,
						FILE_SHARE_DELETE | FILE_SHARE_READ,
						NULL, OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
									);
	*/
#else
	#define CUNILOG_DEFAULT_OPEN_MODE	"a"
#endif

EXTERN_C_BEGIN

/*
	The pointer to the module's internal static SCUNILOGTARGET structure.
	The _static versions of the logging functions operate on this structure.
*/
extern SCUNILOGTARGET *pSCUNILOGTARGETstatic;

/*
	Functions
*/

/*
	cunilog_puts
	cunilog_printf

	Our puts () that resolves to putsU8 () on Windows. These macros should only be
	used if the console is set to output in UTF-16.
*/
#ifdef PLATFORM_IS_WINDOWS
	#define cunilog_puts(t)	putsU8 (t)
	#define cunilog_printf(...) printfU8 (__VA_ARGS__)
#else
	#define cunilog_puts(t)	puts (t)
	#define cunilog_printf(...) printf (__VA_ARGS__)
#endif

/*
	InitCUNILOG_PROCESSOR

	Function/macro to initialise a CUNILOG_PROCESSOR structure. The data (pData) member
	is set to NULL and the member uiOpts to OPT_CUNPROC_NONE, which means no option flags
	are set. The caller is responsible for setting those members to their desired values
	afterwards.
*/
#ifdef DEBUG
	void InitCUNILOG_PROCESSOR	(
			CUNILOG_PROCESSOR				*cup,
			enum cunilogprocesstask			task,
			enum cunilogprocessfrequency	freq,
			uint64_t						thrs
								)
	;
#else
	#define InitCUNILOG_PROCESSOR(cup, task,				\
									type, thrs)				\
		ubf_assert_non_NULL (cup);							\
		(cup)->task		= task;								\
		(cup)->freq		= freq;								\
		(cup)->thr		= thrs;								\
		(cup)->cur		= 0;								\
		(cup)->pData	= NULL;								\
		(cup)->uiOpts	= OPT_CUNPROC_NONE;
#endif

/*
	Table with the length of the rotational date/timestamp.
*/
extern size_t arrLengthTimeStampFromPostfix [cunilogPostfixAmountEnumValues];

/*
	lenDateTimeStampFromRotation
	
	Returns the length of the timestamp of the current rotation.
*/
#ifdef DEBUG
	size_t lenDateTimeStampFromPostfix (enum cunilogpostfix postfix);
#else
	#define lenDateTimeStampFromPostfix(pfx)			\
		(arrLengthTimeStampFromPostfix [(pfx)])
#endif

/*
	Table with the rotation wildcard masks.
*/
extern const char *arrPostfixWildcardMask [cunilogPostfixAmountEnumValues];

/*
	postfixMaskFromLogPostfix
	
	Returns a string representing a file name wildcard mask for rotation that can be used
	to search for files, for instance a rotation with a value of unilogEveryMinute returns
	"????-??-?? ??:??".
*/
#ifdef DEBUG
	const char *postfixMaskFromLogPostfix (enum cunilogpostfix postfix);
#else
	#define postfixMaskFromLogPostfix(pfx)			\
		(arrPostfixWildcardMask [pfx])
#endif

/*
	CunilogSetConsoleTo

	Sets the console to UTF-8 or UTF-16 on Windows.
*/
#ifdef PLATFORM_IS_WINDOWS
	enum enclconsoleoutpCP
	{
			cunilogConsoleIsUninitialised
		,	cunilogConsoleIsUTF8
		,	cunilogConsoleIsUTF16
		,	cunilogConsoleIsNeither
	};
	typedef enum enclconsoleoutpCP culogconcp;

	void CunilogSetConsoleTo (culogconcp cp);
#endif

/*
	CunilogSetConsoleToUTF8
	CunilogSetConsoleToUTF16
	CunilogSetConsoleToNone

	Macros to set the console to UTF-8 or UTF-16 on Windows. They do nothing on POSIX.

	By default the echo/console output processor changes the Windows console input
	and output character sets/code pages to UTF-8 when invoked for the first time.
	Calling one of these functions beforehand explicitely sets the code pages/console
	character sets and prevents the echo/console output processor from changing them
	when a logging function that echoes to the console is called the first time.

	The function CunilogSetConsoleToNone () does not change the code pages/character
	sets for the attached console but simply prevents the Cunilog echo/console output
	processor from changing them when a logging function that writes to the console is
	called for the first time.
*/
#ifdef PLATFORM_IS_WINDOWS
	#define CunilogSetConsoleToUTF8()	CunilogSetConsoleTo (cunilogConsoleIsUTF8)
#else
	#define CunilogSetConsoleToUTF8()
#endif
#ifdef PLATFORM_IS_WINDOWS
	#define CunilogSetConsoleToUTF16()	CunilogSetConsoleTo (cunilogConsoleIsUTF16)
#else
	#define CunilogSetConsoleToUTF16()
#endif
#ifdef PLATFORM_IS_WINDOWS
	#define CunilogSetConsoleToNone()	CunilogSetConsoleTo (cunilogConsoleIsNeither)
#else
	#define CunilogSetConsoleToNone()
#endif

/*
	InitSCUNILOGTARGETex

	Initialises an existing SCUNILOGTARGET structure.

	Parameters

	put					A pointer to an SCUNILOGTARGET structure that holds all required
						parameters. The function does not create a copy of this structure and
						therefore it must be available/accessible until DoneSUNILOGTARGET ()
						and ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () are called on
						it. In other words the structure is required to either be static or is
						created as an automatic structure in main ().
						The function InitSCUNILOGTARGETstatic () uses the module's internal static
						structure.

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory), or
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either cunilogRunProcessorsOnStartup or
						cunilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to puz on success, NULL otherwise.
*/
SCUNILOGTARGET *InitSCUNILOGTARGETex
(
	  SCUNILOGTARGET			*put				// Must not be NULL.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	InitSCUNILOGTARGET

	Simplified version of InitSCUNILOGTARGETex ().
*/
#ifdef DEBUG
	SCUNILOGTARGET *InitSCUNILOGTARGET
	(
		  SCUNILOGTARGET			*put				// Must not be NULL.
		, const char				*szLogPath			// Path to the logging information.
		, size_t					lenLogPath			// Length of szLogPath
		, const char				*szAppName			// Application name.
		, size_t					lenAppName			// Length of szApplication.
		, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
		, enum cunilogtype			type
	)
	;
#else
	#define InitSCUNILOGTARGET(put,						\
				szLogPath,	lenLogPath,					\
				szAppName,	lenAppName,					\
				relLogPath,								\
				type)									\
				InitSCUNILOGTARGETex	(				\
					(put),								\
					(szLogPath), (lenLogPath),			\
					(szAppName), (lenAppName),			\
					(relLogPath),						\
					(type),								\
					cunilogPostfixDefault,				\
					NULL, 0,							\
					cunilogEvtTS_Default,				\
					cunilogNewLineDefault,				\
					cunilogRunProcessorsOnStartup		\
										)
#endif

/*
	CreateNewSCUNILOGTARGET

	Creates a new SCUNILOGTARGET structure on the heap and initialises it.

	Parameters

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory), or
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either unilogRunProcessorsOnStartup or
						unilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	For performance reasons and to simplify data handling, the function allocates a single memory
	block that holds enough space for the SCUNILOGTARGET structure as well as szLogPath and
	szAppName.

	If the function succeeds it returns a pointer to a valid SUNILOGTARGET structure.
	If the function fails, the return value is NULL.
*/
SCUNILOGTARGET *CreateNewSCUNILOGTARGET
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	InitOrCreateSCUNILOGTARGET

	Initialises an existing SCUNILOGTARGET structure or creates a new one on the heap.

	If put is NULL, the function calls CreateNewSCUNILOGTARGET () and returns a pointer
	to the newly allocated and initialised SCUNILOGTARGET structure.
	
	If put is not NULL, the function initialises it and returns put by calling
	InitSCUNILOGTARGET () on it. If put is not NULL, the function does not create a copy of
	this structure. The caller therefore must ensure that it is available/accessible until
	DoneSCUNILOGTARGET () and ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () are called
	on it, i.e. that the structure is either static or is created as an automatic structure
	in main ().

	If the cuProcessorList parameter is not NULL, the function does not create a copy of
	this list and therefore must be available/accessible until DoneSCUNILOGTARGET () and
	ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () are called on it. In other
	words the list is required to either reside on the heap, is static, or is created
	as automatic in main ().

	The function returns NULL if it fails.

	Call DoneSCUNILOGTARGET () when done with the structure, independent of whether it
	has been created on the heap or provided as the parameter psu.
*/
SCUNILOGTARGET *InitOrCreateSCUNILOGTARGET
(
	  SCUNILOGTARGET			*put				// If NULL, a new structure is allocated.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	InitSCUNILOGTARGETstaticEx
	
	Initialises the internal SCUNILOGTARGET structure. If the _static versions of the logging
	functions are used, an application must call this function before any of these functions
	are called.
	
	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory), or
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either cunilogRunProcessorsOnStartup or
						cunilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to the internal SCUNILOGTARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneSCUNILOGTARGETstatic () to free the structure's resources.
*/
SCUNILOGTARGET *InitSCUNILOGTARGETstaticEx
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;

/*
	InitSCUNILOGTARGETstatic

	Simplified version of InitSCUNILOGTARGETstaticEx ().

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to the executable module. If this parameter is NULL, the
						function uses the executable module's path. This string does not have to
						be NUL-terminated if lenLogPath is given correctly and not as (size_t)
						-1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory), or
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to cunilogSingleThreaded.

	The function returns a pointer to the internal SCUNILOGTARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneSCUNILOGTARGETstatic () to free the structure's resources.
*/
SCUNILOGTARGET *InitSCUNILOGTARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
;

/*
	GetAbsoluteLogPathSCUNILOGTARGET

	Returns the absolute path to the folder logfiles are written to, including a directory
	separator. If plen is not NULL, the function returns the length of the path at the address
	plen points to. This is the value strlen () would return.

	The last character of the returned path is a directory separator, which is a backslash
	on Windows and a forward slash on all other systems.

	The function returns NULL if it fails. In this case it will not have changed the address
	plen points to.
*/
const char *GetAbsoluteLogPathSCUNILOGTARGET (SCUNILOGTARGET *put, size_t *plen)
;

/*
	ConfigSCUNILOGTARGETcunilogpostfix

	Sets the member unilogEvtTSformat of the SCUNILOGTARGET structure put points to to the
	value of tsf.
*/
#ifdef DEBUG
	void ConfigSCUNILOGTARGETcunilogpostfix (SCUNILOGTARGET *put, enum cunilogeventTSformat tsf)
	;
#else
	#define ConfigSCUNILOGTARGETcunilogpostfix(put, f)	\
				(put)->unilogEvtTSformat = (f)
#endif

/*
	ConfigSCUNILOGTARGETrunProcessorsOnStartup

	Sets the flag CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP of the uiOpts member of the
	SCUNILOGTARGET structure put points to according to the value of the runProcessorsOnStartup
	enumeration rp.
*/
#ifdef DEBUG
	void ConfigSCUNILOGTARGETrunProcessorsOnStartup (SCUNILOGTARGET *put, runProcessorsOnStartup rp)
	;
#else
	#define ConfigSCUNILOGTARGETrunProcessorsOnStartup(put, rp)	\
		switch (rp)												\
		{														\
			case cunilogRunProcessorsOnStartup:					\
				cunilogSetRunAllProcessorsOnStartup (put);		\
				break;											\
			case cunilogDontRunProcessorsOnStartup:				\
				cunilogClrRunAllProcessorsOnStartup (put);		\
				break;											\
			default:											\
				cunilogSetRunAllProcessorsOnStartup (put);		\
				break;											\
		}
#endif

/*
	ConfigSCUNILOGTARGETcunilognewline

	Sets the member unilogNewLine of the SCUNILOGTARGET structure put points to to the
	value of nl.

	This function should only be called directly after the target has been initialised and
	before any of the logging functions has been called unless
	CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#ifdef DEBUG
	void ConfigSCUNILOGTARGETcunilognewline (SCUNILOGTARGET *put, newline_t nl)
	;
#else
	#define ConfigSCUNILOGTARGETcunilognewline(put, nl)			\
		(put)->unilogNewLine = (nl)
#endif

/*
	ConfigSCUNILOGTARGETeventSeverityFormatType

	Sets the format type of event severities for the target structure put. It
	sets the member evSeverityType of the SCUNILOGTARGET structure put to the
	value of eventSeverityFormatType.
*/
#ifdef DEBUG
	void ConfigSCUNILOGTARGETeventSeverityFormatType	(
			SCUNILOGTARGET				*put,
			cueventsevtpy				eventSeverityFormatType
														)
	;
#else
	#define ConfigSCUNILOGTARGETeventSeverityFormatType(put, evstpy)	\
		(put)->evSeverityType = (evstpy)
#endif

/*
	ConfigSCUNILOGTARGETuseColourForEcho

	Switches on/off using colours for console output depending on event severity level.
*/
#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#ifdef DEBUG
		void ConfigSCUNILOGTARGETuseColourForEcho (SCUNILOGTARGET *put, bool bUseColour)
		;
	#else
		#define ConfigSCUNILOGTARGETuseColourForEcho(put, b)	\
			if (bUseColour)										\
				cunilogSetUseColourForEcho (put);				\
			else												\
				cunilogClrUseColourForEcho (put)
	#endif
#endif

/*
	ConfigSCUNILOGTARGETprocessorList

	Sets the processors for a SCUNILOGTARGET struture.

	Parameters

	put					A pointer to a SCUNILOGTARGET structure for which the processors
						are set.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

*/
#ifdef DEBUG
	void ConfigSCUNILOGTARGETprocessorList	(
					SCUNILOGTARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	;
#else
	#define ConfigSCUNILOGTARGETprocessorList(put,		\
				cup, n)									\
				prepareProcessors (put, cuProcessorList, nProcessors)
#endif

/*
	ConfigSCUNILOGTARGETdisableTaskProcessors
	ConfigSCUNILOGTARGETenableTaskProcessors

	Disables/enables processors for task task.
*/
void ConfigSCUNILOGTARGETdisableTaskProcessors (SCUNILOGTARGET *put, enum cunilogprocesstask task);
void ConfigSCUNILOGTARGETenableTaskProcessors (SCUNILOGTARGET *put, enum cunilogprocesstask task);

/*
	ConfigSCUNILOGTARGETdisableEchoProcessor
	ConfigSCUNILOGTARGETenableEchoProcessor

	Disables/enables echo (console output) processors. Echo or console output processors
	are processors whose task is cunilogProcessEchoToConsole.
*/
void ConfigSCUNILOGTARGETdisableEchoProcessor (SCUNILOGTARGET *put);
void ConfigSCUNILOGTARGETenableEchoProcessor (SCUNILOGTARGET *put);

/*
	EnterSCUNILOGTARGET
	LockSCUNILOGTARGET

	LeaveSCUNILOGTARGET
	UnlockSCUNILOGTARGET

	EnterSCUNILOGTARGETstatic
	LockSCUNILOGTARGETstatic

	LockSCUNILOGTARGETstatic
	UnlockSCUNILOGTARGETstatic

	Interface functions/macros to lock (enter) and unlock (leave) the critical section or
	mutex of the singly-linked events list of the SCUNILOGTARGET structure put points to.
	The ...static versions lock and unlock the internal static SCUNILOGTARGET structure.

	Since Cunilog provides several means of accessing the events list of a SCUNILOGTARGET
	structure, and since it handles the events list internally, these functions/macros are most
	likely not required and should probably not be used.

	Note that these functions/macros do NOT lock or unlock access to the SCUNILOGTARGET
	structure's members. They are merely for locking and unlocking the singly-linked list
	containing the events to log.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, these macros/functions do nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void EnterSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
	void LeaveSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
	#define LockSCUNILOGTARGET(put)						\
				EnterSCUNILOGTARGET (put)
	#define UnlockSCUNILOGTARGET(put)					\
				LeaveSCUNILOGTARGET (put)
	#define EnterSCUNILOGTARGETstatic()					\
				LeaveSCUNILOGTARGET (pSCUNILOGTARGETstatic)
	#define LeaveSCUNILOGTARGETstatic()					\
				EnterSCUNILOGTARGET (pSCUNILOGTARGETstatic)
	#define LockSCUNILOGTARGETstatic()					\
				EnterSCUNILOGTARGET (pSCUNILOGTARGETstatic)
	#define UnlockSCUNILOGTARGETstatic()				\
				LeaveSCUNILOGTARGET (pSCUNILOGTARGETstatic)
#else
	#define EnterSCUNILOGTARGET(put)
	#define LeaveSCUNILOGTARGET(put)
	#define LockSCUNILOGTARGET(put)
	#define UnlockSCUNILOGTARGET(put)
	#define EnterSCUNILOGTARGETstatic()
	#define LeaveSCUNILOGTARGETstatic()
	#define LockSCUNILOGTARGETstatic()
	#define UnlockSCUNILOGTARGETstatic()
#endif

/*
	DoneSCUNILOGTARGET

	Deallocates all resources of the SCUNILOGTARGET put points to. After a structure has been
	processed by this function, none of the logging functions can be called on it anymore, but
	it could however be re-used by initialising it again.

	Before calling this function, call ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET ()
	first to either process or discard the target's event queue.

	The function always returns NULL.
*/
SCUNILOGTARGET *DoneSCUNILOGTARGET (SCUNILOGTARGET *put)
;

/*
	DoneSCUNILOGTARGETstatic
	
	Deallocates all resources of the internal static SCUNILOGTARGET structure by calling
	DoneSCUNILOGTARGET () on it.

	The function always returns NULL.
*/
#define DoneSCUNILOGTARGETstatic()						\
			DoneSCUNILOGTARGET (pSCUNILOGTARGETstatic)

/*
	ShutdownSCUNILOGTARGET

	Blocks further logging by forcing all logging functions to return false. It then waits
	for the events of the current queue to be processed and returns after an existing separate
	logging thread has exited.

	Logging events that are produced by currently executing logging functions themselves are
	not blocked until the queue is empty. This means internal non-rotating events like
	"Deleting file..." etc. are still processed until none are left.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, meaning that only further logging is blocked and logging functions called
	afterwards return false.

	This function should be called just before DoneSCUNILOGTARGET ().

	The function returns true on success, false otherwise.
*/
bool ShutdownSCUNILOGTARGET (SCUNILOGTARGET *put);

/*
	ShutdownSCUNILOGTARGETstatic

	Calls ShutdownSCUNILOGTARGET () on the internal static SUNILOGSTRUCT structure.
	This function should be called just before DoneSUNILOGTARGETstatic ();
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
#define ShutdownSCUNILOGTARGETstatic()					\
			ShutdownSCUNILOGTARGET (pSCUNILOGTARGETstatic)

/*
	CancelSCUNILOGTARGET

	Empties the logging queue for the SCUNILOGTARGET put without processing its events.
	The events currently in the queue are discarded. Logging functions called afterwards
	for this SCUNILOGTARGET structure fail and return false.

	The function waits for an existing separate logging thread to exit.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
bool CancelSCUNILOGTARGET (SCUNILOGTARGET *put);

/*
	CancelSCUNILOGTARGETstatic

	Calls CancelSCUNILOGTARGET () on the internal static SUNILOGSTRUCT structure.
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
#define CancelSCUNILOGTARGETstatic ()					\
			CancelSCUNILOGTARGET (pSCUNILOGTARGETstatic)

/*
	SetLogPrioritySCUNILOGTARGET

	Sets the priority of the separate logging thread that belongs to the specified
	SCUNILOGTARGET structure put points to.
	
	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file),
	although they are not really nice values as the priority is applied to the separate
	logging thread only.
	Neither the table nor this function have been tested to ensure the approximations
	for POSIX are accurate.

	Windows systems support cunilogPrioBeginBackground and cunilogPrioEndBackground. These
	values change the separate logging thread's priority to THREAD_MODE_BACKGROUND_BEGIN and
	THREAD_MODE_BACKGROUND_END respectively. See
	https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority
	for details.
	Since directly comparable functionality is not available on POSIX,
	cunilogPrioBeginBackground is identical to cunilogPrioIdle, which sets the thread priority
	value to 19, and cunilogPrioEndBackground is identical to a value of 0, which means normal
	priority. See https://www.man7.org/linux/man-pages/man3/pthread_setschedprio.3.html .

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the SCUNILOGTARGET structure doesn't
	have a separate logging thread, the function returns true. Whether the function
	returns success or failure depends on the system call that sets the priority. The
	function also returns false if the value for prio is invalid.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool SetLogPrioritySCUNILOGTARGET (SCUNILOGTARGET *put, cunilogprio prio)
	;
#else
	#define SetLogPrioritySCUNILOGTARGET(put, prio) (true)
#endif

/*
	SetLogPrioritySCUNILOGTARGETstatic

	Sets the priority of the separate logging thread that belongs to the internal static
	SCUNILOGTARGET structure.

	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file).
	Neither the table nor this function have been tested to ensure the approximations
	are accurate.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the SCUNILOGTARGET structure doesn't
	have a separate logging thread, the function returns true.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define SetLogPrioritySCUNILOGTARGETstatic (prio)	\
				SetLogPrioritySCUNILOGTARGET (pSCUNILOGTARGETstatic, prio)
#else
	#define SetLogPrioritySCUNILOGTARGETstatic(put, prio) (true)
#endif

/*
	PauseLogSCUNILOGTARGET

	Pauses/suspends logging to the SCUNILOGTARGET structure put points to while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogSCUNILOGTARGET () to resume the separate logging thread.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
#else
	#define PauseLogSCUNILOGTARGET(put)
#endif

/*
	PauseLogSCUNILOGTARGETstatic

	Pauses/suspends logging to the internal SCUNILOGTARGET structure while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogSCUNILOGTARGETstatic () to resume the separate logging thread again.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define PauseLogSCUNILOGTARGETstatic()				\
		PauseLogSCUNILOGTARGET (pSCUNILOGTARGETstatic)
#else
	#define PauseLogSCUNILOGTARGETstatic()
#endif

/*
	ResumeLogSCUNILOGTARGET

	Resumes logging to the SCUNILOGTARGET structure put points to after a call to
	PauseLogSCUNILOGTARGET () and triggers it for each queued event since
	PauseLogSCUNILOGTARGET () was called.

	The function returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogSCUNILOGTARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
#else
	#define ResumeLogSCUNILOGTARGET(put)
#endif

/*
	ResumeLogSCUNILOGTARGETstatic

	Resumes logging to the internal SCUNILOGTARGET structure after a call to
	PauseLogSCUNILOGTARGET () and triggers it for each queued event since
	PauseLogSCUNILOGTARGET () was called.

	The macro returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogSCUNILOGTARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define ResumeLogSCUNILOGTARGETstatic()			\
				ResumeLogSCUNILOGTARGET (pSCUNILOGTARGETstatic)
#else
	#define ResumeLogSCUNILOGTARGETstatic()		(0)
#endif

/*
	CreateSCUNILOGEVENT_Data

	Allocates a buffer that points to a new event structure SCUNILOGEVENT plus data,
	initialises it with the function parameters, and returns a pointer to the newly
	created and initialised structure and data buffer. The event is written out as binary
	data.

	Note that you can NOT use USE_STRLEN as the parameter siz.

	The function returns false if it fails.
*/
SCUNILOGEVENT *CreateSCUNILOGEVENT_Data	(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz,
					const char					*ccCapt,
					size_t						lenCapt
											)
;

/*
	CreateSCUNILOGEVENT_Text

	This is the text version of CreateSCUNILOGEVENT_Data (). If the string ccText is
	NUL-terminated len can be set to USE_STRLEN, and the function calls strlen () to
	obtain its length.
*/
SCUNILOGEVENT *CreateSCUNILOGEVENT_Text		(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;

/*
	DuplicateSCUNILOGEVENT

	Creates a copy of the event pev on the heap. If the event has a size other than
	sizeof (SCUNILOGEVENT) this is taken into consideration. The target of the newly
	created event is identical to the target of the event pev points to.

	Call DoneSCUNILOGEVENT () to destroy it.

	The function returns a pointer to a newly allocated event, which is an exact copy
	of pev apart from that the newly allocated event has the option flag CUNILOGEVENT_ALLOCATED
	set regardless of whether this flag was present in pev.
*/
SCUNILOGEVENT *DuplicateSCUNILOGEVENT (SCUNILOGEVENT *pev)
;

/*
	DoneSCUNILOGEVENT

	Destroys an SUNILOGEVENT structure including all its resources if the event belongs
	to target put. If put is NULL the event is destroyed regardless.

	The function always returns NULL.
*/
SCUNILOGEVENT *DoneSCUNILOGEVENT (SCUNILOGTARGET *put, SCUNILOGEVENT *pev)
;

/*
	Logging functions.
	==================
*/

/*
	logEv

	Writes out the event pev points to to the logging target put points to. The function
	only sets the pSCUNILOGTARGET member of the SCUNILOGEVENT structure and calls
	cunilogProcessOrQueueEvent () on it.

	Returns true on success, false otherwise. The function fails after ShutdownSCUNILOGTARGET ()
	or CancelSCUNILOGTARGET () have been called on the SCUNILOGTARGET structure put points to.
*/
bool logEv (SCUNILOGTARGET *put, SCUNILOGEVENT *pev);

/*
	logEv_static

	Macro wrapper for the static version of logEv () that uses the module's internal static
	structure and does not require a pointer to a SCUNILOGTARGET structure as their first
	parameter.
*/
#define logEv_static(pev)	logEv (pSCUNILOGTARGETstatic, (pev))

/*
	The functions expect an SCUNILOGTARGET structure as their first parameter.
	The _static macros use the module's internal static structure and do not require
	a pointer to a SCUNILOGTARGET structure as their first parameter. If you only intend to
	write to a single logfile, the _static macros are ideal.

	The logText functions or macros expect text output.
	The logHexDump functions expect text and binary data to output a hex dump with the text
	as caption.

	The logHexDump () function outputs a hex dump. The function logHexOrText () examines the
	provided data and treats it either as ASCII or binary data for a hex dump. The function
	logHexOrTextU8 () also accepts UTF-8 as text and creates a hex dump if the data to output
	contains invalid UTF-8.

	The functions without a severity use severity level/severity type cunilogEvtSeverityNone.
	Functions containing sev in their names accept a severity type.

	Functions that have U8 in their names are for UTF-8, the ones with a WU16 are intended for
	Windows UTF-16 encoding. On POSIX systems the WU16 functions are not available.

	Function names with an l accept a length parameter for the text's length, in octets/bytes.
	You can use USE_STRLEN for this parameter, in which case the text buffer's length is obtained
	via a call to strlen () and the string needs to be NUL-terminated. NUL-termination is not
	required otherwise. Note that the length parameter denotes the length of the text, in octets,
	not its size, and also not in characters. The text "abc" has a length of 3 but a size of 4
	octets, which includes the NUL-terminator. UTF-8 characters can have up to 4 octets/bytes.
	Cunilog writes out only UTF-8 but doesn't actually understand its encoding.

	The vfmt versions are variadic functions/macros that expect a va_list argument.

	The fmt versions offer variadic functionality like printf () does. The function
	logTextU8fmt () uses an additional memory allocation and deallocation internally. The sfmt
	type functions like logTextU8sfmt () attempt to use the stack for the fmt output if less
	than CUNILOG_DEFAULT_SFMT_SIZE bytes are required. Otherwise the heap is used.
	
	Function names containing a "q" (for quick) do not invoke any rotation processors.

	The functions logTextU8smbfmtsev () and logTextU8smbfmt () additionally expect an
	initialised parameter structure of type SMEMBUF. The SMEMBUF structure can be re-used
	for consecutive calls. Within the same thread this can save memory allocations if the
	functions are called several times. Example:

	SMEMBUF smb = SMEMBUF_INITIALISER;
	logTextU8smbfmt_static (&smb, "Text to log");
	logTextU8smbfmt_static (&smb, "Another text to log");
	doneSMEMBUF (&smb);

	All functions return true on success, false otherwise. Functions may for instance fail if
	a memory allocation fails or if a separate logging thread failed to start.
	They also fail after ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET () have been called
	on the SCUNILOGTARGET structure put points to.
*/
bool logTextU8sevl			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8sevlq			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8sev			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8sevq			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8l				(SCUNILOGTARGET *put, const char *ccText, size_t len);
bool logTextU8lq			(SCUNILOGTARGET *put, const char *ccText, size_t len);
bool logTextU8				(SCUNILOGTARGET *put, const char *ccText);
bool logTextU8q				(SCUNILOGTARGET *put, const char *ccText);
bool logTextU8vfmt			(SCUNILOGTARGET *put, const char *fmt, va_list ap);
bool logTextU8fmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8qvfmt			(SCUNILOGTARGET *put, const char *fmt, va_list ap);
bool logTextU8qfmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8svfmt			(SCUNILOGTARGET *put, const char *fmt, va_list ap);
bool logTextU8sfmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sqvfmt		(SCUNILOGTARGET *put, const char *fmt, va_list ap);
bool logTextU8sqfmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8svfmtsev		(SCUNILOGTARGET *put, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8sfmtsev		(SCUNILOGTARGET *put, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbvfmtsev	(SCUNILOGTARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8smbfmtsev		(SCUNILOGTARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbvfmt		(SCUNILOGTARGET *put, SMEMBUF *smb, const char *fmt, va_list ap);
bool logTextU8smbfmt		(SCUNILOGTARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logHexDumpU8sevl		(SCUNILOGTARGET *put, cueventseverity sev, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDumpU8l			(SCUNILOGTARGET *put, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDump				(SCUNILOGTARGET *put, const void *pBlob, size_t size);
bool logHexDumpq			(SCUNILOGTARGET *put, const void *pBlob, size_t size);
bool logHexOrText			(SCUNILOGTARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt);
bool logHexOrTextq			(SCUNILOGTARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt);
bool logHexOrTextU8			(SCUNILOGTARGET *put, const void *szHexOrTxtU8, size_t lenHexOrTxtU8);

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16sevl		(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len);
bool logTextWU16sev			(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText);
bool logTextWU16l			(SCUNILOGTARGET *put, const wchar_t *cwText, size_t len);
bool logTextWU16			(SCUNILOGTARGET *put, const wchar_t *cwText);
#endif

#define logTextU8sevl_static(v, t, l)	logTextU8sevl		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextU8sevlq_static(v, t, l)	logTextU8sevlq		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextU8sev_static(v, t)		logTextU8sevl		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8sevq_static(v, t)		logTextU8sevq		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8l_static(t, l)			logTextU8l			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextU8lq_static(t, l)		logTextU8lq			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextU8_static(t)				logTextU8l			(pSCUNILOGTARGETstatic, (t), USE_STRLEN)
#define logTextU8q_static(t)			logTextU8lq			(pSCUNILOGTARGETstatic, (t), USE_STRLEN)
#define logTextU8fmt_static(...)		logTextU8fmt		(pSCUNILOGTARGETstatic, __VA_ARGS__)
#define logTextU8sfmt_static(...)		logTextU8sfmt		(pSCUNILOGTARGETstatic, __VA_ARGS__)
#define logTextU8sfmtsev_static(s, ...)	logTextU8sfmtsev	(pSCUNILOGTARGETstatic, (s), __VA_ARGS__)
#define logTextU8smbfmtsev_static(s, m, ...)			\
										logTextU8smbfmtsev	(pSCUNILOGTARGETstatic, (s), (m), __VA_ARGS__)
#define logTextU8smbfmt_static(m, ...)	logTextU8smbfmt		(pSCUNILOGTARGETstatic, (m), __VA_ARGS__)
#define logHexDumpU8sevl_static(s, d, n, c, l)			\
										logHexDumpU8sevl	(pSCUNILOGTARGETstatic, (s), (d), (n), (c), (l))
#define logHexDumpU8l_static(d, n, c,					\
			l)							logHexDumpU8l		(pSCUNILOGTARGETstatic, (d), (n), (c), (l))
#define logHexDump_static(d, s)			logHexDump			(pSCUNILOGTARGETstatic, (d), (s))
#define logHexOrText_static(d, s)		logHexOrText		(pSCUNILOGTARGETstatic, (d), (s))
#define logHexOrTextU8_static(d, s)		logHexOrTextU8		(pSCUNILOGTARGETstatic, (d), (s))

#ifdef PLATFORM_IS_WINDOWS
#define logTextWU16sevl_static(v, t, l)	logTextWU16sevl		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextWU16sev_static(v, t)		logTextWU16sevl		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextWU16l_static(t, l)		logTextWU16l		(pSCUNILOGTARGETstatic, (t), (l))
#define logTextWU16_static(t)			logTextWU16l		(pSCUNILOGTARGETstatic, (t), USE_STRLEN);
#endif

/*
	ChangeSCUNILOGTARGETuseColourForEcho
	ChangeSCUNILOGTARGETuseColorForEcho
	ChangeSCUNILOGTARGETuseColourForEcho_static
	ChangeSCUNILOGTARGETuseColorForEcho_static

	Creates and queues an event that changes the colour output of event severity
	types. A value of false for bUseColour disables coloured output. A value of true
	switches it on.

	The _static versions of the function/macros use the internal static SCUNILOGTARGET
	structure.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeSCUNILOGTARGETuseColourForEcho (SCUNILOGTARGET *put, bool bUseColour)
	;
	#define ChangeSCUNILOGTARGETuseColourForEcho_static(bc)	\
				ChangeSCUNILOGTARGETuseColourForEcho (pSCUNILOGTARGETstatic, (bc))
	#define ChangeSCUNILOGTARGETuseColorForEcho(p, bc)		\
				ChangeSCUNILOGTARGETuseColourForEcho ((p), (bc))
	#define ChangeSCUNILOGTARGETuseColorForEcho_static(bc)	\
				ChangeSCUNILOGTARGETuseColourForEcho (pSCUNILOGTARGETstatic, (bc))
#endif

/*
	ChangeSCUNILOGTARGETcunilognewline
	ChangeSCUNILOGTARGETcunilognewline_static

	Creates and queues an event that changes the member unilogNewLine of the SCUNILOGTARGET
	structure put points to to the value of nl.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeSCUNILOGTARGETcunilognewline (SCUNILOGTARGET *put, newline_t nl)
	;
	#define ChangeSCUNILOGTARGETcunilognewline_static(nl)	\
				ChangeSCUNILOGTARGETcunilognewline (pSCUNILOGTARGETstatic, (nl))
#endif

/*
	The version as text, its year, and as a 64 bit number.
	Currently still unsupported.
*/
extern const char		ccCunilogVersionText [];
extern const char		ccCunilogVersionYear [];
extern const uint64_t	uiCunilogVersion;

/*
	cunilogCheckVersion

	Compares the version of cunilog.c with the version of cunilogversion.h and returns
	the result of the comparison.

	-1		The version of cunilog.c is less than the one in cunilogversion.h.
	0		The version of cunilog.c is identical to the one in cunilogversion.h.
	1		The version of cunilog.c is greater than the one in cunilogversion.h.

	When cunilog is built as a static library, an application includes cunilog_combined.h
	only. This function/macro ensures that the static library and cunilog_combined.h (actually:
	cunilogversion.h) fit together.

	The function aborts in debug versions. In release builds it merely returns the result
	of the comparison.

	Example:

	if (0 != cunilogCheckVersion ())
	{
		puts ("Version of cunilog_combined.h and libcunilog different.");
		return EXIT_FAILURE;
	}
*/
#define CUNILOG_VERSION_HDR							\
(		((uint64_t) CUNILOG_VERSION_MAJOR	<< 48)	\
	|	((uint64_t) CUNILOG_VERSION_MINOR	<< 32)	\
	|	((uint64_t) CUNILOG_VERSION_SUB		<< 16)	\
	|	((uint64_t) CUNILOG_VERSION_BUILD)			\
)
int cunilogCheckVersionIntChk (uint64_t cunilogHdrVersion);
#define cunilogCheckVersion() cunilogCheckVersionIntChk (CUNILOG_VERSION_HDR)

/*
	Tests
	=====
*/
#ifdef CUNILOG_BUILD_TEST_FNCTS
	bool test_cunilog (void);
#else
	#define cunilog()
#endif

EXTERN_C_END

#endif														// Of #ifndef CUNILOG_H.
