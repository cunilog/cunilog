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
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	1. Create a CUNILOG_TARGET structure and initialise it. Use either your own structure
		or create a new one with CreateNewSUNILOGTARGET () or InitOrCreateSUNILOGTARGET ().
		Or use the internal structure of this module with InitSUNILOGTARGETstatic () instead.
		The latter is most likely what you want.

	2. Use the logging functions repeatedly as you please. Depending on the member unilogType
		of the CUNILOG_TARGET structure, you might do this from a single or multiple
		threads.

	4. When not required anymore, probably just before the application exits, call
		ShutdownCUNILOG_TARGET () or ShutdownCUNILOG_TARGETstatic, depending on the structure
		you used. Call DoneSUNILOGTARGET () on the the CUNILOG_TARGET structure afterwards,
		or call DoneSUNILOGTARGETstatic () if the internal structure was used.

		Example for internal static structure:

--- Begin example in Using.md ---
// Application start

CUNILOG_TARGET *put = InitCUNILOG_TARGETstatic	(
			"logs", 4,
			"MyApp", USE_STRLEN,
			cunilogPath_relativeToHomeDir,
			cunilogMultiThreadedSeparateLoggingThread
						);
if (NULL == put)
{
	// InitCUNILOG_TARGETstatic () failed.
	exit (EXIT_FAILURE);
}

// Use the log...static () family of functions and macros for logging.
logTextU8_static ("A simple line to go in the logfile.");
logTextU8l_static ("Another line.", 13);
logTextU8l_static ("And another one.", USE_STRLEN);

// Just before the application exists shut down the logging target and deallocate
//	its resources.
ShutdownCUNILOG_TARGETstatic ();		// Blocks until the queue is empty.
DoneCUNILOG_TARGETstatic ();
--- End of example in Using.md ---

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
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

	#include "./cunilogversion.h"
	#include "./cunilogstructs.h"

#endif

// To build the test functions.
/*
#ifndef CUNILOG_BUILD_TEST_FNCTS
#define CUNILOG_BUILD_TEST_FNCTS
#endif
*/

// Inserts function calls to output the current files list. Sometimes used for debugging.
#ifndef CUNILOG_BUILD_DEBUG_OUTPUT_FILES_LIST
//#define CUNILOG_BUILD_DEBUG_OUTPUT_FILES_LIST
#endif

// Inserts checks for the queue locker. For obvious reasons, this can't work reliably
//	and was only used for initial tests.
#ifndef CUNILOG_BUILD_DEBUG_TEST_LOCKER
//#define CUNILOG_BUILD_DEBUG_TEST_LOCKER
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


/*
	Memory alignments. Use 16 octets/bytes for 64 bit platforms.
	Use CUNILOG_DEFAULT_ALIGNMENT for structures and CUNILOG_POINTER_ALIGNMENT
	for pointers.
	Also, see https://learn.microsoft.com/en-us/cpp/build/reference/zp-struct-member-alignment?view=msvc-170 .
*/
#if defined (_M_X64)
	#ifndef CUNILOG_DEFAULT_ALIGNMENT
	#define CUNILOG_DEFAULT_ALIGNMENT	(16)
	#endif
#else
	#ifndef CUNILOG_DEFAULT_ALIGNMENT
	#define CUNILOG_DEFAULT_ALIGNMENT	(8)
	#endif
#endif
#if defined (_M_X64)
	#ifndef CUNILOG_POINTER_ALIGNMENT
	#define CUNILOG_POINTER_ALIGNMENT	(8)
	#endif
#else
	#ifndef CUNILOG_POINTER_ALIGNMENT
	#define CUNILOG_POINTER_ALIGNMENT	(8)
	#endif
#endif


// Our standard size for error messages on the stack.
#ifndef CUNILOG_STD_MSG_SIZE
#define CUNILOG_STD_MSG_SIZE			(256)
#endif

// Our standard size for bulk memory allocations.
#ifndef CUNILOG_STD_BULK_ALLOC_SIZE
#define CUNILOG_STD_BULK_ALLOC_SIZE		(4096 - sizeof (SBULKMEMBLOCK))
#endif

// The size we're going to expand the vector containing the names of logfiles.
#ifndef CUNILOG_STD_VECT_EXP_SIZE
#define CUNILOG_STD_VECT_EXP_SIZE		(128)
#endif

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

// The default rotation thresholds in debug and release versions.
#ifdef CUNILOG_DEBUG_USE_TEST_ROTATOR_VALUES

	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED	(2)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED		(3)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED		(4)
	#endif

#else

	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED	(10)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED		(100)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED		(100)
	#endif

#endif

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
	The pointer to the module's internal static CUNILOG_TARGET structure.
	The _static versions of the logging functions operate on this structure.
*/
CUNILOG_DLL_IMPORT extern CUNILOG_TARGET *pCUNILOG_TARGETstatic;

/*
	Functions
*/

/*
	CreateCopyCUNILOG_PROCESSORs

	Creates a copy of the array of pointers to CUNILOG_PROCESSOR structures with n processors.
	The copy contains a copy of the array of pointers to the structures, a copy of the
	structures themselves, and a copy of all pData members. This is as deep as the function
	goes.

	The copy is created as a single memory block, hence can be deallocated again with a single
	call to ubf_free (). However, for consistency it is recommended to call
	DoneCopyCUNILOG_PROCESSORs () on the returned memory block.

	The function returns a pointer to the allocated memory block where the copy of the array
	of pointers to CUNILOG_PROCESSOR structures can be found, including all CUNILOG_PROCESSOR
	structures and their pData structures. It returns NULL if the heap allocation fails.
*/
CUNILOG_PROCESSOR **CreateCopyCUNILOG_PROCESSORs (CUNILOG_PROCESSOR *cps [], unsigned int n);
TYPEDEF_FNCT_PTR (CUNILOG_PROCESSOR **, CreateCopyCUNILOG_PROCESSORs)
	(CUNILOG_PROCESSOR *cps [], unsigned int n);

/*
	DoneCopyCUNILOG_PROCESSORs

	Destroys a copy of CUNILOG_PROCESSORs created with CreateCopyCUNILOG_PROCESSORs ().
	The parameter cps must not be NULL.
	
	The function is literally just a wrapper for ubf_free () and always returns NULL.
*/
void *DoneCopyCUNILOG_PROCESSORs (CUNILOG_PROCESSOR *cps []);
TYPEDEF_FNCT_PTR (void *, DoneCopyCUNILOG_PROCESSORs) (CUNILOG_PROCESSOR *cps []);

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
	TYPEDEF_FNCT_PTR (void, CunilogSetConsoleTo) (culogconcp cp);
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
	CunilogEnableANSI
	CunilogDisableANSI
	CunilogIsANSIenabled

	Enable or disable the Windows console for ANSI escape sequences,
	or check if the Windows console is configured for ANSI escape sequences.

	Note that these functions configure the Windows console only. They have
	no influence on what Cunilog sends/writes to the console.

	The functions return true on success, false otherwise.
	
	The function CunilogIsANSIenabled () returns true if ANSI escape sequences are
	enabled, false if not. On POSIX, CunilogIsANSIenabled () always evaluates to
	true.
*/
#ifdef PLATFORM_IS_WINDOWS
	bool CunilogEnableANSI	(void);
	TYPEDEF_FNCT_PTR (bool, CunilogEnableANSI)	(void);
	bool CunilogDisableANSI	(void);
	TYPEDEF_FNCT_PTR (bool, CunilogDisableANSI)	(void);
	bool CunilogIsANSIenabled (void);
	TYPEDEF_FNCT_PTR (bool, CunilogIsANSIenabled) (void);
#else
	#define CunilogEnableANSI()
	#define CunilogDisableANSI()
	#define CunilogIsANSIenabled() (true)
#endif

/*
	CunilogGetEnv

	Wrapper function for getenv () on Windows and secure_getenv () on POSIX.
*/
char *CunilogGetEnv (const char *szName);
TYPEDEF_FNCT_PTR (char *, CunilogGetEnv) (const char *szName);

/*
	Cunilog_Have_NO_COLOR

	Returns true if the environment variable NO_COLOR exists and has a value (is not empty).
	See https://no-color.org/ for the specification.

	The function checks the environment variable NO_COLOR every time it is called. It is
	therefore recommended to call the function only when really required, for example at the
	start of an application, and store its return value in a variable.
*/
bool Cunilog_Have_NO_COLOR (void);
TYPEDEF_FNCT_PTR (bool, Cunilog_Have_NO_COLOR) (void);

/*
	CunilogGetAbsPathFromAbsOrRelPath

	Obtains an absolute path from a relative path. The parameter absOrRelPath specifies
	to what a relative path is relative to.

	The function adds a forward or backward slash to the buffer psmb points to, as it
	assumes the parameters are paths, not filenames. However, the function also works
	with paths to filenames but since it adds a slash the caller needs to remove this
	manually, for example by overwriting it with an ASCII_NUL character.

	psmb			A pointer to an SMEMBUF structure whose buffer receives the absolut
					path.

	plmb			A pointer to a size_t that receives the length of the buffer.

	szAbsOrRelPath	The path. Can be relative or absolute.

	lnAbsOrRelPath	Its length as would be retrieved by strlen (). Can be USE_STRLEN,
					in which case the function calls strlen (szAbsOrRelPath) to obtain
					it.

	absOrRelPath	An enum that specifies what the path is relative to. The the enum
					enCunilogRelPath for possible values.
*/
bool CunilogGetAbsPathFromAbsOrRelPath	(
		SMEMBUF				*psmb,
		size_t				*plmb,
		const char			*szAbsOrRelPath,
		size_t				lnAbsOrRelPath,
		enCunilogRelPath	absOrRelPath
										)
;
TYPEDEF_FNCT_PTR (bool, CunilogGetAbsPathFromAbsOrRelPath)
								(
		SMEMBUF				*psmb,
		size_t				*plmb,
		const char			*szAbsOrRelPath,
		size_t				lnAbsOrRelPath,
		enCunilogRelPath	absOrRelPath
								)
;

// This seems to be useful.
#define requiresCUNILOG_TARGETseparateLoggingThread(p)	\
(														\
		cunilogSingleThreadedSeparateLoggingThread	== (p)->culogType\
	||	cunilogMultiThreadedSeparateLoggingThread	== (p)->culogType\
)

/*
	InitCUNILOG_TARGETex

	Initialises an existing CUNILOG_TARGET structure.

	Parameters

	put					A pointer to an CUNILOG_TARGET structure that holds all required
						parameters. The function does not create a copy of this structure and
						therefore it must be available/accessible until DoneSUNILOGTARGET ()
						and ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () are called on
						it. In other words the structure is required to either be static or is
						created as an automatic structure in main ().
						The function InitCUNILOG_TARGETstatic () uses the module's internal static
						structure.

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

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

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
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
CUNILOG_TARGET *InitCUNILOG_TARGETex
(
	  CUNILOG_TARGET			*put				// Must not be NULL.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGETex)
(
	  CUNILOG_TARGET			*put				// Must not be NULL.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
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
	InitCUNILOG_TARGET

	Simplified version of InitCUNILOG_TARGETex ().
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	CUNILOG_TARGET *InitCUNILOG_TARGET
	(
		  CUNILOG_TARGET			*put				// Must not be NULL.
		, const char				*szLogPath			// Path to the logging information.
		, size_t					lenLogPath			// Length of szLogPath
		, const char				*szAppName			// Application name.
		, size_t					lenAppName			// Length of szApplication.
		, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
		, enum cunilogtype			type
	)
	;
	TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGET)
	(
		  CUNILOG_TARGET			*put				// Must not be NULL.
		, const char				*szLogPath			// Path to the logging information.
		, size_t					lenLogPath			// Length of szLogPath
		, const char				*szAppName			// Application name.
		, size_t					lenAppName			// Length of szApplication.
		, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
		, enum cunilogtype			type
	)
	;
#else
	#define InitCUNILOG_TARGET(put,						\
				szLogPath,	lenLogPath,					\
				szAppName,	lenAppName,					\
				relLogPath,								\
				type)									\
				InitCUNILOG_TARGETex	(				\
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
	CreateNewCUNILOG_TARGET

	Creates a new CUNILOG_TARGET structure on the heap and initialises it.

	Parameters

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

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

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
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
	block that holds enough space for the CUNILOG_TARGET structure as well as szLogPath and
	szAppName.

	If the function succeeds it returns a pointer to a valid SUNILOGTARGET structure.
	If the function fails, the return value is NULL.
*/
CUNILOG_TARGET *CreateNewCUNILOG_TARGET
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, CreateNewCUNILOG_TARGET)
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
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
	InitOrCreateCUNILOG_TARGET

	Initialises an existing CUNILOG_TARGET structure or creates a new one on the heap.

	If put is NULL, the function calls CreateNewCUNILOG_TARGET () and returns a pointer
	to the newly allocated and initialised CUNILOG_TARGET structure.
	
	If put is not NULL, the function initialises it and returns put by calling
	InitCUNILOG_TARGET () on it. If put is not NULL, the function does not create a copy of
	this structure. The caller therefore must ensure that it is available/accessible until
	DoneCUNILOG_TARGET () and ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () are called
	on it, i.e. that the structure is either static or is created as an automatic structure
	in main ().

	If the cuProcessorList parameter is not NULL, the function does not create a copy of
	this list and therefore must be available/accessible until DoneCUNILOG_TARGET () and
	ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () are called on it. In other
	words the list is required to either reside on the heap, is static, or is created
	as automatic in main ().

	The function returns NULL if it fails.

	Call DoneCUNILOG_TARGET () when done with the structure, independent of whether it
	has been created on the heap or provided as the parameter psu.
*/
CUNILOG_TARGET *InitOrCreateCUNILOG_TARGET
(
	  CUNILOG_TARGET			*put				// If NULL, a new structure is allocated.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitOrCreateCUNILOG_TARGET)
(
	  CUNILOG_TARGET			*put				// If NULL, a new structure is allocated.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
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
	InitCUNILOG_TARGETstaticEx
	
	Initialises the internal CUNILOG_TARGET structure. If the _static versions of the logging
	functions are used, an application must call this function before any of these functions
	are called.
	
	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

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

	relLogPath			One of the values in the enCunilogRelPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogPath_relativeToExecutable (the executable file),
						cunilogPath_relativeToCurrentDir (the current directory), or
						cunilogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
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

	The function returns a pointer to the internal CUNILOG_TARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneCUNILOG_TARGETstatic () to free the structure's resources.
*/
CUNILOG_TARGET *InitCUNILOG_TARGETstaticEx
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, CUNILOG_PROCESSOR			**cuProcessorList	// One or more post-processors.
	, unsigned int				nProcessors			// Number of processors.
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
)
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGETstaticEx)
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
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
	InitCUNILOG_TARGETstatic

	Simplified version of InitCUNILOG_TARGETstaticEx ().

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

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

	relLogPath			One of the values in the enCunilogRelPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogPath_relativeToExecutable (the executable file),
						cunilogPath_relativeToCurrentDir (the current directory), or
						cunilogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.

	The function returns a pointer to the internal CUNILOG_TARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneCUNILOG_TARGETstatic () to free the structure's resources.
*/
CUNILOG_TARGET *InitCUNILOG_TARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGETstatic)
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
;

/*
	MoveCUNILOG_TARGETqueueToFrom

	Moves the queue of the target putFrom to target putTo.
	The function requires that both targets have a queue. It fails if this is not
	the case.

	The function returns true on success, false otherwise.
*/
bool MoveCUNILOG_TARGETqueueToFrom	(
		CUNILOG_TARGET *cunilog_restrict putTo,
		CUNILOG_TARGET *cunilog_restrict putFrom
									)
;
TYPEDEF_FNCT_PTR (bool, MoveCUNILOG_TARGETqueueToFrom)
(
		CUNILOG_TARGET *cunilog_restrict putTo,
		CUNILOG_TARGET *cunilog_restrict putFrom
);

/*
	HAS_CUNILOG_TARGET_A_QUEUE

	Macro to check if a CUNILOG_TARGET structure has an event quueue.
*/
#define HAS_CUNILOG_TARGET_A_QUEUE(put)					\
(														\
		cunilogSingleThreadedSeparateLoggingThread	== put->culogType\
	||	cunilogMultiThreadedSeparateLoggingThread	== put->culogType\
	||	cunilogSingleThreadedQueueOnly				== put->culogType\
	||	cunilogMultiThreadedQueueOnly				== put->culogType\
)

/*
	GetAbsoluteLogPathCUNILOG_TARGET

	Returns the absolute path to the folder logfiles are written to, including a directory
	separator. If plen is not NULL, the function returns the length of the path at the address
	plen points to. This is the value strlen () would return.

	The last character of the returned path is a directory separator, which is a backslash
	on Windows and a forward slash on all other systems.

	The function returns NULL if it fails. In this case it will not have changed the address
	plen points to.
*/
const char *GetAbsoluteLogPathCUNILOG_TARGET (CUNILOG_TARGET *put, size_t *plen);
TYPEDEF_FNCT_PTR (const char *, GetAbsoluteLogPathCUNILOG_TARGET)
	(CUNILOG_TARGET *put, size_t *plen);

/*
	GetAbsoluteLogPathCUNILOG_TARGET_static

	Calls GetAbsoluteLogPathCUNILOG_TARGET () to obtain the absolute path to the folder
	logfiles for the internal static CUNILOG_TARGET structure are written to.
*/
const char *GetAbsoluteLogPathCUNILOG_TARGET_static (size_t *plen);
TYPEDEF_FNCT_PTR (const char *, GetAbsoluteLogPathCUNILOG_TARGET_static)
	(size_t *plen);

/*
	GetCUNILOG_PROCESSOR

	Returns a pointer to the nth processor that performs processing task task.
	If n is 0, the function finds the first processor of task task, if it is
	1, it returns the second procossor of task task.
	Returns NULL if a processor for task task does not exist or if n is higher
	than the number of task processors - 1. For instance, if a processor list
	only contains one echo processor, and if n = 1, the function returns NULL.

	For example, to obtain the echo processor:
	CUNILOG_PROCESSOR *cup = GetCUNILOG_PROCESSOR	(
								put, cunilogProcessEchoToConsole, 0
													);
*/
CUNILOG_PROCESSOR *GetCUNILOG_PROCESSOR	(
						CUNILOG_TARGET				*put,
						enum cunilogprocesstask		task,
						unsigned int				n
										)
;
TYPEDEF_FNCT_PTR (CUNILOG_PROCESSOR *, GetCUNILOG_PROCESSOR)
										(
						CUNILOG_TARGET				*put,
						enum cunilogprocesstask		task,
						unsigned int				n
										)
;

/*
	GetCUNILOG_PROCESSORrotationTask

	Returns a pointer to the nth rotation processor that performs rotation task rot.
	If n is 0, the function finds the first rotation processor of task rot, if it is
	1, it returns the second rotation procossor of task rot.
	Returns NULL if a rotation processor for task rot does not exist or if n is higher
	than the number of this type of ratation processors - 1. For instance, if a processor
	list only contains one cunilogrotationtask_MoveToTrashLogfiles rotation processor,
	and if n = 1, the function returns NULL.

	For example, to obtain a pointer to the rotation processor that moves files to the
	recycle bin/trash:
	CUNILOG_PROCESSOR *cup = GetCUNILOG_PROCESSORrotationTask	(
								put, cunilogrotationtask_MoveToTrashLogfiles, 0
																);
*/
CUNILOG_PROCESSOR *GetCUNILOG_PROCESSORrotationTask	(
						CUNILOG_TARGET				*put,
						enum cunilogrotationtask	rot,
						unsigned int				n
													)
;

/*
	ConfigCUNILOG_TARGETerrorCallbackFunction

	Sets the error callback function of the specified Cunilog target put points to.
*/
#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	void ConfigCUNILOG_TARGETerrorCallbackFunction (CUNILOG_TARGET *put, cunilogErrCallback errorCB);
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETerrorCallbackFunction)
		(CUNILOG_TARGET *put, cunilogErrCallback errorCB);
#else
	#define ConfigCUNILOG_TARGETerrorCallbackFunction(put, errorCB)
#endif

/*
	ConfigCUNILOG_TARGETeventStampFormat

	Sets the member unilogEvtTSformat of the CUNILOG_TARGET structure put points to to the
	value of tsf.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETeventStampFormat (CUNILOG_TARGET *put, enum cunilogeventTSformat tsf)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETeventStampFormat)
		(CUNILOG_TARGET *put, enum cunilogeventTSformat tsf);
#else
	#define ConfigCUNILOG_TARGETeventStampFormat(put, f)	\
				(put)->unilogEvtTSformat = (f)
#endif

/*
	ConfigCUNILOG_TARGETrunProcessorsOnStartup

	Sets the flag CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP of the uiOpts member of the
	CUNILOG_TARGET structure put points to according to the value of the runProcessorsOnStartup
	enumeration rp.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETrunProcessorsOnStartup (CUNILOG_TARGET *put, runProcessorsOnStartup rp)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETrunProcessorsOnStartup)
		(CUNILOG_TARGET *put, runProcessorsOnStartup rp);
#else
	#define ConfigCUNILOG_TARGETrunProcessorsOnStartup(put, rp)	\
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
	ConfigCUNILOG_TARGETcunilognewline

	Sets the member unilogNewLine of the CUNILOG_TARGET structure put points to to the
	value of nl.

	This function should only be called directly after the target has been initialised and
	before any of the logging functions has been called unless
	CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETcunilognewline (CUNILOG_TARGET *put, newline_t nl);
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETcunilognewline)
		(CUNILOG_TARGET *put, newline_t nl);
#else
	#define ConfigCUNILOG_TARGETcunilognewline(put, nl)			\
		(put)->unilogNewLine = (nl)
#endif

/*
	ConfigCUNILOG_TARGETeventSeverityFormatType

	Sets the format type of event severities for the target structure put. It
	sets the member evSeverityType of the CUNILOG_TARGET structure put to the
	value of eventSeverityFormatType.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETeventSeverityFormatType	(
			CUNILOG_TARGET				*put,
			cueventsevfmtpy				eventSeverityFormatType
														)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETeventSeverityFormatType)
														(
			CUNILOG_TARGET				*put,
			cueventsevfmtpy				eventSeverityFormatType
														)
	;
#else
	#define ConfigCUNILOG_TARGETeventSeverityFormatType(put, evstpy)	\
		(put)->evSeverityType = (evstpy)
#endif

/*
	ConfigCUNILOG_TARGETuseColourForEcho

	Switches on/off using colours for console output depending on event severity level.

	The NO_COLOR suggestion at https://no-color.org/ recommends that this function is
	called after checking the environment variable NO_COLOR first:
	ConfigCUNILOG_TARGETuseColourForEcho (target, !Cunilog_Have_NO_COLOR ());
*/
#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ConfigCUNILOG_TARGETuseColourForEcho (CUNILOG_TARGET *put, bool bUseColour)
		;
		TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETuseColourForEcho)
			(CUNILOG_TARGET *put, bool bUseColour);
	#else
		#define ConfigCUNILOG_TARGETuseColourForEcho(put, b)	\
			if (bUseColour)										\
				cunilogSetUseColourForEcho (put);				\
			else												\
				cunilogClrUseColourForEcho (put)
	#endif
#endif

/*
	ConfigCUNILOG_TARGETprocessorList

	Sets the processors for a CUNILOG_TARGET struture.

	Parameters

	put					A pointer to a CUNILOG_TARGET structure for which the processors
						are set.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETprocessorList	(
					CUNILOG_TARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETprocessorList)
											(
					CUNILOG_TARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	;
#else
	#define ConfigCUNILOG_TARGETprocessorList(put,		\
				cup, n)									\
				prepareProcessors (put, cuProcessorList, nProcessors)
#endif

/*
	ConfigCUNILOG_TARGETdisableTaskProcessors
	ConfigCUNILOG_TARGETenableTaskProcessors

	Disables/enables processors for task task.
*/
void ConfigCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);
void ConfigCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);

TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETdisableTaskProcessors)
	(CUNILOG_TARGET *put, enum cunilogprocesstask task);
TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETenableTaskProcessors)
	(CUNILOG_TARGET *put, enum cunilogprocesstask task);

/*
	ConfigCUNILOG_TARGETdisableEchoProcessor
	ConfigCUNILOG_TARGETenableEchoProcessor

	Disables/enables echo (console output) processors. Echo or console output processors
	are processors whose task is cunilogProcessEchoToConsole.
*/
void ConfigCUNILOG_TARGETdisableEchoProcessor	(CUNILOG_TARGET *put);
void ConfigCUNILOG_TARGETenableEchoProcessor	(CUNILOG_TARGET *put);

TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETdisableEchoProcessor)	(CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETenableEchoProcessor)	(CUNILOG_TARGET *put);

/*
	EnterCUNILOG_TARGET
	LockCUNILOG_TARGET

	LeaveCUNILOG_TARGET
	UnlockCUNILOG_TARGET

	EnterCUNILOG_TARGETstatic
	LockCUNILOG_TARGETstatic

	LockCUNILOG_TARGETstatic
	UnlockCUNILOG_TARGETstatic

	Interface functions/macros to lock (enter) and unlock (leave) the critical section or
	mutex of the singly-linked events list of the CUNILOG_TARGET structure put points to.
	The ...static versions lock and unlock the internal static CUNILOG_TARGET structure.

	Since Cunilog provides several means of accessing the events list of a CUNILOG_TARGET
	structure, and since it handles the events list internally, these functions/macros are most
	likely not required and should probably not be used.

	Note that these functions/macros do NOT lock or unlock access to the CUNILOG_TARGET
	structure's members. They are merely for locking and unlocking the singly-linked list
	containing the events to log.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, these macros/functions do nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void EnterCUNILOG_TARGET (CUNILOG_TARGET *put);
	void LeaveCUNILOG_TARGET (CUNILOG_TARGET *put);
	#define LockCUNILOG_TARGET(put)						\
				EnterCUNILOG_TARGET (put)
	#define UnlockCUNILOG_TARGET(put)					\
				LeaveCUNILOG_TARGET (put)
	#define EnterCUNILOG_TARGETstatic()					\
				LeaveCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	#define LeaveCUNILOG_TARGETstatic()					\
				EnterCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	#define LockCUNILOG_TARGETstatic()					\
				EnterCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	#define UnlockCUNILOG_TARGETstatic()				\
				LeaveCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	
	TYPEDEF_FNCT_PTR (void, EnterCUNILOG_TARGET) (CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (void, LeaveCUNILOG_TARGET) (CUNILOG_TARGET *put);
#else
	#define EnterCUNILOG_TARGET(put)
	#define LeaveCUNILOG_TARGET(put)
	#define LockCUNILOG_TARGET(put)
	#define UnlockCUNILOG_TARGET(put)
	#define EnterCUNILOG_TARGETstatic()
	#define LeaveCUNILOG_TARGETstatic()
	#define LockCUNILOG_TARGETstatic()
	#define UnlockCUNILOG_TARGETstatic()
#endif

/*
	DoneCUNILOG_TARGET

	Deallocates all resources of the CUNILOG_TARGET put points to. After a structure has been
	processed by this function, none of the logging functions can be called on it anymore, but
	it could however be re-used by initialising it again.

	Before calling this function, call ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET ()
	first to either process or discard the target's event queue.

	The function always returns NULL.
*/
CUNILOG_TARGET *DoneCUNILOG_TARGET (CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, DoneCUNILOG_TARGET) (CUNILOG_TARGET *put);

/*
	DoneCUNILOG_TARGETstatic
	
	Deallocates all resources of the internal static CUNILOG_TARGET structure by calling
	DoneCUNILOG_TARGET () on it.

	The function always returns NULL.
*/
#define DoneCUNILOG_TARGETstatic()						\
			DoneCUNILOG_TARGET (pCUNILOG_TARGETstatic)

/*
	ShutdownCUNILOG_TARGET

	Blocks further logging by forcing all logging functions to return false. It then waits
	for the events of the current queue to be processed and returns after an existing separate
	logging thread has exited.

	Logging events that are produced by currently executing logging functions themselves are
	not blocked until the queue is empty. This means internal non-rotating events like
	"Deleting file..." etc. are still processed until none are left.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, meaning that only further logging is blocked and logging functions called
	afterwards return false.

	This function should be called just before DoneCUNILOG_TARGET ().

	The function returns true on success, false otherwise.
*/
bool ShutdownCUNILOG_TARGET (CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (bool, ShutdownCUNILOG_TARGET) (CUNILOG_TARGET *put);

/*
	ShutdownCUNILOG_TARGETstatic

	Calls ShutdownCUNILOG_TARGET () on the internal static CUNILOG_TARGET structure.
	This function should be called just before DoneCUNILOG_TARGETstatic ();
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
#define ShutdownCUNILOG_TARGETstatic()					\
			ShutdownCUNILOG_TARGET (pCUNILOG_TARGETstatic)

/*
	CancelCUNILOG_TARGET

	Empties the logging queue for the CUNILOG_TARGET put without processing its events.
	The events currently in the queue are discarded. Logging functions called afterwards
	for this CUNILOG_TARGET structure fail and return false.

	The function waits for an existing separate logging thread to exit.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
bool CancelCUNILOG_TARGET (CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (bool, CancelCUNILOG_TARGET) (CUNILOG_TARGET *put);

/*
	CancelCUNILOG_TARGETstatic

	Calls CancelCUNILOG_TARGET () on the internal static SUNILOGSTRUCT structure.
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
#define CancelCUNILOG_TARGETstatic ()					\
			CancelCUNILOG_TARGET (pCUNILOG_TARGETstatic)

/*
	PauseLogCUNILOG_TARGET

	Pauses/suspends logging to the CUNILOG_TARGET structure put points to while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogCUNILOG_TARGET () to resume the separate logging thread.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogCUNILOG_TARGET (CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (void, PauseLogCUNILOG_TARGET) (CUNILOG_TARGET *put);
#else
	#define PauseLogCUNILOG_TARGET(put)
#endif

/*
	PauseLogCUNILOG_TARGETstatic

	Pauses/suspends logging to the internal CUNILOG_TARGET structure while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogCUNILOG_TARGETstatic () to resume the separate logging thread again.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define PauseLogCUNILOG_TARGETstatic()				\
		PauseLogCUNILOG_TARGET (pCUNILOG_TARGETstatic)
#else
	#define PauseLogCUNILOG_TARGETstatic()
#endif

/*
	ResumeLogCUNILOG_TARGET

	Resumes logging to the CUNILOG_TARGET structure put points to after a call to
	PauseLogCUNILOG_TARGET () and triggers it for each queued event since
	PauseLogCUNILOG_TARGET () was called.

	The function returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogCUNILOG_TARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogCUNILOG_TARGET (CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (size_t, ResumeLogCUNILOG_TARGET) (CUNILOG_TARGET *put);
#else
	#define ResumeLogCUNILOG_TARGET(put)
#endif

/*
	ResumeLogCUNILOG_TARGETstatic

	Resumes logging to the internal CUNILOG_TARGET structure after a call to
	PauseLogCUNILOG_TARGET () and triggers it for each queued event since
	PauseLogCUNILOG_TARGET () was called.

	The macro returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogCUNILOG_TARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define ResumeLogCUNILOG_TARGETstatic()			\
				ResumeLogCUNILOG_TARGET (pCUNILOG_TARGETstatic)
#else
	#define ResumeLogCUNILOG_TARGETstatic()		(0)
#endif

/*
	CreateCUNILOG_EVENT_Data

	Allocates a buffer that points to a new event structure CUNILOG_EVENT plus data,
	initialises it with the function parameters, and returns a pointer to the newly
	created and initialised structure and data buffer. The event is written out as binary
	data, which results in a hex dump.

	Note that you can NOT use USE_STRLEN as the parameter siz.

	The function returns false if it fails.
*/
CUNILOG_EVENT *CreateCUNILOG_EVENT_Data	(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz,
					const char					*ccCapt,
					size_t						lenCapt
											)
;
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, CreateCUNILOG_EVENT_Data)
(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz,
					const char					*ccCapt,
					size_t						lenCapt
											)
;

/*
	CreateCUNILOG_EVENT_Text

	This is the text version of CreateCUNILOG_EVENT_Data (). If the string ccText is
	NUL-terminated len can be set to USE_STRLEN, and the function calls strlen () to
	obtain its length.
*/
CUNILOG_EVENT *CreateCUNILOG_EVENT_Text		(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, CreateCUNILOG_EVENT_Text)
											(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;

/*
	CreateCUNILOG_EVENT_TextTS

	This function is identical to CreateCUNILOG_EVENT_Text () but expects the timestamp
	for the event in the additional UBF_TIMESTAMP parameter ts.
*/
CUNILOG_EVENT *CreateCUNILOG_EVENT_TextTS		(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len,
					UBF_TIMESTAMP				ts
											)
;
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, CreateCUNILOG_EVENT_TextTS)
											(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len,
					UBF_TIMESTAMP				ts
											)
;

/*
	DuplicateCUNILOG_EVENT

	Creates a copy of the event pev on the heap. If the event has a size other than
	sizeof (CUNILOG_EVENT) this is taken into consideration. The target of the newly
	created event is identical to the target of the event pev points to.

	Call DoneCUNILOG_EVENT () to destroy it.

	The function returns a pointer to a newly allocated event, which is an exact copy
	of pev apart from that the newly allocated event has the option flag CUNILOGEVENT_ALLOCATED
	set regardless of whether this flag was present in pev.
*/
CUNILOG_EVENT *DuplicateCUNILOG_EVENT (CUNILOG_EVENT *pev);
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, DuplicateCUNILOG_EVENT) (CUNILOG_EVENT *pev);

/*
	DoneCUNILOG_EVENT

	Destroys an SUNILOGEVENT structure including all its resources if the event belongs
	to target put. If put is NULL the event is destroyed regardless.

	The function always returns NULL.
*/
CUNILOG_EVENT *DoneCUNILOG_EVENT (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, DoneCUNILOG_EVENT) (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);

/*
	Logging functions.
	==================
*/

/*
	logEv

	Writes out the event pev points to to the logging target put points to. The function
	only sets the pCUNILOG_TARGET member of the CUNILOG_EVENT structure and calls
	cunilogProcessOrQueueEvent () on it.

	Returns true on success, false otherwise. The function fails after ShutdownCUNILOG_TARGET ()
	or CancelCUNILOG_TARGET () have been called on the CUNILOG_TARGET structure put points to.
*/
bool logEv (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);
TYPEDEF_FNCT_PTR (bool, logEv) (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);


/*
	logEv_static

	Macro wrapper for the static version of logEv () that uses the module's internal static
	structure and does not require a pointer to a CUNILOG_TARGET structure as their first
	parameter.
*/
#define logEv_static(pev)	logEv (pCUNILOG_TARGETstatic, (pev))

/*
	The functions expect an CUNILOG_TARGET structure as their first parameter.
	The _static macros use the module's internal static structure and do not require
	a pointer to a CUNILOG_TARGET structure as their first parameter. If you only intend to
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

	Functions whose name contains a c only output to the console. Other processors are simply
	ignored.

	Function names with an l accept a length parameter for the text's length, in octets/bytes.
	You can use USE_STRLEN for this parameter, in which case the text buffer's length is obtained
	via a call to strlen () and the string needs to be NUL-terminated. NUL-termination is not
	required otherwise. Note that the length parameter denotes the length of the text, in octets,
	not its size, and also not in characters. The text "abc" has a length of 3 but a size of 4
	octets, which includes the NUL-terminator. UTF-8 characters can have up to 4 octets/bytes.
	Cunilog writes out only UTF-8 but doesn't actually understand its encoding.

	Functions ending in ts expect the timestamp of the event in an additional UBF_TIMESTAMP
	parameter.

	The vfmt versions are variadic functions/macros that expect a va_list argument. Note that
	these functions/macros are normal logging functions and do not compose the output and write
	to a buffer provided by the caller like standard library functions vsnprintf () and family
	would.

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
	They also fail after ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () have been called
	on the CUNILOG_TARGET structure put points to.
*/
bool logTextU8sevl			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8sevlts		(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8sevlq			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8sevlqts		(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8sev			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8sevq			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8l				(CUNILOG_TARGET *put, const char *ccText, size_t len);
bool logTextU8lts			(CUNILOG_TARGET *put, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8lq			(CUNILOG_TARGET *put, const char *ccText, size_t len);
bool logTextU8lqts			(CUNILOG_TARGET *put, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8				(CUNILOG_TARGET *put, const char *ccText);
bool logTextU8q				(CUNILOG_TARGET *put, const char *ccText);
bool logTextU8vfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8fmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8qvfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8qfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8svfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8sfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8sqvfmt		(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8sqfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8svfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8sfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbvfmtsev	(CUNILOG_TARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8smbfmtsev		(CUNILOG_TARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbvfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, va_list ap);
bool logTextU8smbfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logHexDumpU8sevl		(CUNILOG_TARGET *put, cueventseverity sev, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDumpU8l			(CUNILOG_TARGET *put, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDump				(CUNILOG_TARGET *put, const void *pBlob, size_t size);
bool logHexDumpq			(CUNILOG_TARGET *put, const void *pBlob, size_t size);
bool logHexOrText			(CUNILOG_TARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt);
bool logHexOrTextq			(CUNILOG_TARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt);
bool logHexOrTextU8			(CUNILOG_TARGET *put, const void *szHexOrTxtU8, size_t lenHexOrTxtU8);

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16sevl		(CUNILOG_TARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len);
bool logTextWU16sev			(CUNILOG_TARGET *put, cueventseverity sev, const wchar_t *cwText);
bool logTextWU16l			(CUNILOG_TARGET *put, const wchar_t *cwText, size_t len);
bool logTextWU16			(CUNILOG_TARGET *put, const wchar_t *cwText);
#endif

// Console output only. No other processors are invoked.
bool logTextU8csevl			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8csev			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8cl			(CUNILOG_TARGET *put, const char *ccText, size_t len);
bool logTextU8c				(CUNILOG_TARGET *put, const char *ccText);
bool logTextU8cvfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8cfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8csfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8csmbvfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, va_list ap);
bool logTextU8csmbfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logTextU8csvfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8csfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, ...);

#define logTextU8sevl_static(v, t, l)	logTextU8sevl		(pCUNILOG_TARGETstatic, (v), (t), (l))
#define logTextU8sevlts_static(v, t, l, ts)				\
										logTextU8sevlts		(pCUNILOG_TARGETstatic, (v), (t), (l), (ts))
#define logTextU8sevlq_static(v, t, l)	logTextU8sevlq		(pCUNILOG_TARGETstatic, (v), (t), (l))
#define logTextU8sev_static(v, t)		logTextU8sevl		(pCUNILOG_TARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8sevq_static(v, t)		logTextU8sevq		(pCUNILOG_TARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8l_static(t, l)			logTextU8l			(pCUNILOG_TARGETstatic, (t), (l))
#define logTextU8lts_static(t, l, ts)	logTextU8lts		(pCUNILOG_TARGETstatic, (t), (l), (ts))
#define logTextU8lq_static(t, l)		logTextU8lq			(pCUNILOG_TARGETstatic, (t), (l))
#define logTextU8lqts_static(t, l, ts)	logTextU8lqts		(pCUNILOG_TARGETstatic, (t), (l), (ts))
#define logTextU8_static(t)				logTextU8l			(pCUNILOG_TARGETstatic, (t), USE_STRLEN)
#define logTextU8q_static(t)			logTextU8lq			(pCUNILOG_TARGETstatic, (t), USE_STRLEN)
#define logTextU8fmt_static(...)		logTextU8fmt		(pCUNILOG_TARGETstatic, __VA_ARGS__)
#define logTextU8qvfmt_static(t, ap)	logTextU8qvfmt		(pCUNILOG_TARGETstatic, (t), (ap))
#define logTextU8qfmt_static(...)		logTextU8qfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__)
#define logTextU8sqvfmt_static(t, ap)	logTextU8sqvfmt		(pCUNILOG_TARGETstatic, (t), (ap));
#define logTextU8sfmt_static(...)		logTextU8sfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__)
#define logTextU8sfmtsev_static(s, ...)	logTextU8sfmtsev	(pCUNILOG_TARGETstatic, (s), __VA_ARGS__)
#define logTextU8smbfmtsev_static(s, m, ...)			\
										logTextU8smbfmtsev	(pCUNILOG_TARGETstatic, (s), (m), __VA_ARGS__)
#define logTextU8smbfmt_static(m, ...)	logTextU8smbfmt		(pCUNILOG_TARGETstatic, (m), __VA_ARGS__)
#define logHexDumpU8sevl_static(s, d, n, c, l)			\
										logHexDumpU8sevl	(pCUNILOG_TARGETstatic, (s), (d), (n), (c), (l))
#define logHexDumpU8l_static(d, n, c,					\
			l)							logHexDumpU8l		(pCUNILOG_TARGETstatic, (d), (n), (c), (l))
#define logHexDump_static(d, s)			logHexDump			(pCUNILOG_TARGETstatic, (d), (s))
#define logHexOrText_static(d, s)		logHexOrText		(pCUNILOG_TARGETstatic, (d), (s))
#define logHexOrTextU8_static(d, s)		logHexOrTextU8		(pCUNILOG_TARGETstatic, (d), (s))

#ifdef PLATFORM_IS_WINDOWS
#define logTextWU16sevl_static(v, t, l)	logTextWU16sevl		(pCUNILOG_TARGETstatic, (v), (t), (l))
#define logTextWU16sev_static(v, t)		logTextWU16sevl		(pCUNILOG_TARGETstatic, (v), (t), USE_STRLEN)
#define logTextWU16l_static(t, l)		logTextWU16l		(pCUNILOG_TARGETstatic, (t), (l))
#define logTextWU16_static(t)			logTextWU16l		(pCUNILOG_TARGETstatic, (t), USE_STRLEN);
#endif

// Console output only. No other processors are invoked.
#define logTextU8csevl_static(s, t, l)	logTextU8csevl		(pCUNILOG_TARGETstatic, (s), (t), (l));
#define logTextU8csev_static(s, t)		logTextU8csev		(pCUNILOG_TARGETstatic, (s), (t));
#define logTextU8cl_static(t, l)		logTextU8cl			(pCUNILOG_TARGETstatic, (t), (l));
#define logTextU8c_static(t)			logTextU8c			(pCUNILOG_TARGETstatic, (t));
#define logTextU8cvfmt_static(t, ap)	logTextU8cvfmt		(pCUNILOG_TARGETstatic, (t), (ap));
#define logTextU8cfmt_static(...)		logTextU8cfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__);
#define logTextU8csfmt_static(...)		logTextU8csfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__);
#define logTextU8csmbvfmt_static(m, t, ap)				\
										logTextU8csmbvfmt	(pCUNILOG_TARGETstatic, (m), (t), (ap));
#define logTextU8csmbfmt_static(m, ...)	logTextU8csmbfmt	(pCUNILOG_TARGETstatic, (m), __VA_ARGS__);
#define logTextU8csvfmtsev_static(s, t, ap)				\
										logTextU8csvfmtsev	(pCUNILOG_TARGETstatic, (s), (t), (ap));
#define logTextU8csfmtsev_static(s, ...)				\
										logTextU8csfmtsev	(pCUNILOG_TARGETstatic, (s), __VA_ARGS__);

/*	ChangeCUNILOG_TARGETuseColourForEcho
	ChangeCUNILOG_TARGETuseColorForEcho
	ChangeCUNILOG_TARGETuseColourForEcho_static
	ChangeCUNILOG_TARGETuseColorForEcho_static

	Creates and queues an event that changes the colour output of event severity
	types. A value of false for bUseColour disables coloured output. A value of true
	switches it on.

	The _static versions of the function/macros use the internal static CUNILOG_TARGET
	structure.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETuseColourForEcho (CUNILOG_TARGET *put, bool bUseColour)
	;
	#define ChangeCUNILOG_TARGETuseColourForEcho_static(bc)	\
				ChangeCUNILOG_TARGETuseColourForEcho (pCUNILOG_TARGETstatic, (bc))
	#define ChangeCUNILOG_TARGETuseColorForEcho(p, bc)		\
				ChangeCUNILOG_TARGETuseColourForEcho ((p), (bc))
	#define ChangeCUNILOG_TARGETuseColorForEcho_static(bc)	\
				ChangeCUNILOG_TARGETuseColourForEcho (pCUNILOG_TARGETstatic, (bc))
#endif

/*
	ChangeCUNILOG_TARGETcunilognewline
	ChangeCUNILOG_TARGETcunilognewline_static

	Creates and queues an event that changes the member unilogNewLine of the CUNILOG_TARGET
	structure put points to to the value of nl.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETcunilognewline (CUNILOG_TARGET *put, newline_t nl)
	;
	#define ChangeCUNILOG_TARGETcunilognewline_static(nl)	\
				ChangeCUNILOG_TARGETcunilognewline (pCUNILOG_TARGETstatic, (nl))
#endif

/*
	ChangeCUNILOG_TARGETdisableTaskProcessors
	ChangeCUNILOG_TARGETenableTaskProcessors

	The functions return true if the event was queued successfully, false otherwise.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);
	bool ChangeCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);

	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETdisableTaskProcessors) (CUNILOG_TARGET *put, enum cunilogprocesstask task);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETenableTaskProcessors) (CUNILOG_TARGET *put, enum cunilogprocesstask task);
#endif

/*
	ChangeCUNILOG_TARGETdisableEchoProcessor
	ChangeCUNILOG_TARGETenableEchoProcessor

	The functions return true if the event was queued successfully, false otherwise.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETdisableEchoProcessor	(CUNILOG_TARGET *put);
	bool ChangeCUNILOG_TARGETenableEchoProcessor	(CUNILOG_TARGET *put);

	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETdisableEchoProcessor)	(CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETenableEchoProcessor)	(CUNILOG_TARGET *put);
#endif

/*
	ChangeCUNILOG_TARGETeventSeverityFormatType

	Queues an event to set the format type of event severities for the target structure put.
	It sets the member evSeverityType of the CUNILOG_TARGET structure put to the
	value of eventSeverityFormatType.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	bool ChangeCUNILOG_TARGETeventSeverityFormatType (CUNILOG_TARGET *put, cueventsevfmtpy sevTpy);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETeventSeverityFormatType)
		(CUNILOG_TARGET *put, cueventsevfmtpy sevTpy);
#endif
#endif

/*
	ChangeCUNILOG_TARGETlogPriority

	Queues an event to set the priority of the separate logging thread that belongs to the
	specified CUNILOG_TARGET structure put points to.
	
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY or CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS are defined,
	this is a macro that evaluates to true.

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

	The priority of the separate logging thread can only be lowered. The highest priority is
	cunilogPrioNormal.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the CUNILOG_TARGET structure doesn't
	have a separate logging thread, the function returns true. The function returns false if the
	value for prio is invalid.
*/
#if !defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY) && !defined (CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS)
	bool ChangeCUNILOG_TARGETlogPriority (CUNILOG_TARGET *put, cunilogprio prio);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETlogPriority) (CUNILOG_TARGET *put, cunilogprio prio);
#else
	#define ChangeCUNILOG_TARGETlogPriority(put, prio) (true)
#endif

/*
	ChangeCUNILOG_TARGETlogPriority_static

	Sets the priority of the separate logging thread that belongs to the internal static
	CUNILOG_TARGET structure.

	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file).
	Neither the table nor this function have been tested to ensure the approximations
	are accurate.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the CUNILOG_TARGET structure doesn't
	have a separate logging thread, the function returns true.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define ChangeCUNILOG_TARGETlogPriority_static(prio)	\
				ChangeCUNILOG_TARGETlogPriority (pCUNILOG_TARGETstatic, prio)
#else
	#define ChangeCUNILOG_TARGETlogPriority_static(prio) (true)
#endif

/*
	CunilogChangeCurrentThreadPriority

	Sets the priority of the current thread.

	This is a platform-independent way of changing the current thread's priority.

	The function returns true on success, false otherwise.
*/
bool CunilogChangeCurrentThreadPriority (cunilogprio prio);
TYPEDEF_FNCT_PTR (bool, CunilogChangeCurrentThreadPriority) (cunilogprio prio);

/*
	cunilogSetDefaultPrintEventSeverityFormatType

	Sets the default event severity format type that is used by the cunilog_printf...
	and cunilog_puts... type functions (see below).

*/
void cunilogSetDefaultPrintEventSeverityFormatType (cueventsevfmtpy fmtpy);
TYPEDEF_FNCT_PTR (void, cunilogSetDefaultPrintEventSeverityFormatType) (cueventsevfmtpy fmtpy);

/*
	cunilogUseColourForOutput

	Coloured output for the cunilog_printf... and cunilog_puts... type funcitons (see
	below).

	Configures whether ANSI escape sequences are inserted in the output to enable colours.
	The default is true, meaning that by default event severities are sent to the console
	with ANSI escape colour sequences enabled.
*/
void cunilogUseColourForOutput (bool bUseColour);
TYPEDEF_FNCT_PTR (void, cunilogUseColourForOutput) (bool bUseColour);

/*
	cunilog_printf_sev_fmtpy_vl
	cunilog_printf_sev_fmtpy
	cunilog_printf_sev
	cunilog_printf
	cunilog_puts_sev_fmtpy_l
	cunilog_puts_sev_fmtpy
	cunilog_puts_sev_l
	cunilog_puts_sev
	cunilog_puts_l
	cunilog_puts

	The Cunilog printf () and puts () functions.

	The _sev_fmtpy_vl versions expect a severity, a serverity format type, and a va_list
	argument. The _sev_fmtpy versions expect a severity and a severity format type while
	the _sev versions expect a severity only.

	The _l functions expect a length parameter. The value USE_STRLEN can be provided instead
	of the length, in which case these functions use strlen () to obtain it.

	None of these functions abide by the NO_COLOR standard (see https://no-color.org/).
	To make an application NO_COLOR complient, guard them with the return value of
	Cunilog_Have_NO_COLOR ().

	bool bUserWantsColour = !Cunilog_Have_NO_COLOR ();		// At application start.

	if (bUserWantsColour)
		cunilogUseColourForOutput (true);
	else
		cunilogUseColourForOutput (false);

	Or, simpler, since the default is to use ANSI escape colours:

	if (Cunilog_Have_NO_COLOR ())
		cunilogUseColourForOutput (false);

	The functions cunilog_printf () and cunilog_puts () are replacements for the standard
	library functions printf () and puts () respectively. These functions honour Cunilog's
	console settings functions CunilogSetConsoleToUTF8 (), CunilogSetConsoleToUTF16 (),
	and CunilogSetConsoleToNone () on Windows, and its default output severity format functions
	cunilogSetDefaultPrintEventSeverityFormatType (), and cunilogUseColourForOutput ().

*/
int cunilog_printf_sev_fmtpy_vl	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		va_list				ap
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf_sev_fmtpy_vl)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		va_list				ap
								)
;


int cunilog_printf_sev_fmtpy	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		...
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf_sev_fmtpy)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		...
								)
;


int cunilog_printf_sev			(
		cueventseverity		sev,
		const char			*format,
		...
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf_sev)
								(
		cueventseverity		sev,
		const char			*format,
		...
								)
;

int cunilog_printf				(
		const char			*format,
		...
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf)
								(
		const char			*format,
		...
								)
;

int cunilog_puts_sev_fmtpy_l	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8,
		size_t				len
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev_fmtpy_l)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8,
		size_t				len
								)
;

int cunilog_puts_sev_fmtpy		(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev_fmtpy)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8
								)
;


int cunilog_puts_sev_l			(
		cueventseverity		sev,
		const char			*strU8,
		size_t				len
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev_l)
								(
		cueventseverity		sev,
		const char			*strU8,
		size_t				len
								)
;

int cunilog_puts_sev			(
		cueventseverity		sev,
		const char			*strU8
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev)
								(
		cueventseverity		sev,
		const char			*strU8
								)
;

int cunilog_puts_l				(
		const char			*strU8,
		size_t				len
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_l)
								(
		const char			*strU8,
		size_t				len
								)
;

int cunilog_puts				(
		const char			*strU8
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts)
								(
		const char			*strU8
								)
;

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
	#define test_cunilog()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef CUNILOG_H.
