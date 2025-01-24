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

// Literally an arbitray character. This is used to find buffer overruns in debug
//	versions.
#ifndef CUNILOG_DEFAULT_DBG_CHAR
#define CUNILOG_DEFAULT_DBG_CHAR		'\x17'
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
	The pointer to the module's internal static SCUNILOGTARGET structure and a pointer to it.
	The _static versions of the logging functions operate on this structure.
*/
extern SCUNILOGTARGET *pSCUNILOGTARGETstatic;

/*
	Funcitons
*/

/*
	cunilog_puts

	Our puts () that resolves to putsU8 () on Windows.
*/
#ifdef PLATFORM_IS_WINDOWS
	#define cunilog_puts(t)	putsU8 (t);
#else
	#define cunilog_puts(t)	puts (t);
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
	InitSCUNILOGTARGET

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

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify the
						base path if szLogPath is either relative or NULL. If szLogPath is relative,
						the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory),
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be NULL
						if no cunilog processors apart from the standard processors are required.
						If this parameter is not NULL, the function does not create a copy of
						this list and therefore must be available/accessible until
						DoneSUNILOGTARGET () and ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET () are called on it. In other words the list is
						required to either reside on the heap, static, or is created as
						automatic in main ().

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
SCUNILOGTARGET *InitSCUNILOGTARGET
(
	  SCUNILOGTARGET			*put				// Must not be NULL.
	, const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szAppName			// Application name.
	, size_t					lenAppName			// Length of szApplication.
	, enCunilogRelLogPath		relLogPath
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

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify the
						base path if szLogPath is either relative or NULL. If szLogPath is relative,
						the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory),
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be NULL
						if no cunilog processors apart from the standard processors are required.
						If this parameter is not NULL, the function does not create a copy of
						this list and therefore must be available/accessible until
						DoneSUNILOGTARGET () and ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET () are called on it. In other words the list is
						required to either reside on the heap, is static, or is created as
						automatic in main ().

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
	, enCunilogRelLogPath		relLogPath
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
	, enCunilogRelLogPath		relLogPath
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

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify the
						base path if szLogPath is either relative or NULL. If szLogPath is relative,
						the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory),
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.
						If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this parameter is
						ignored and implicitely set to unilogSingleThreaded.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be NULL
						if no cunilog processors apart from the standard processors are required.
						If this parameter is not NULL, the function does not create a copy of
						this list and therefore must be available/accessible until
						DoneSUNILOGTARGET () and ShutdownSCUNILOGTARGET () or
						CancelSCUNILOGTARGET () are called on it. In other words the list is
						required to either reside on the heap, is static, or is created as
						automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either unilogRunProcessorsOnStartup or
						unilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to the internal SCUNILOGTARGET cunilognewlinestructure upon success,
	NULL otherwise.

	Call DoneSCUNILOGTARGETstatic () to free the structures resources.
*/
SCUNILOGTARGET *InitSCUNILOGTARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelLogPath		relLogPath
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
	DoneSCUNILOGTARGET

	Deallocates all resources of the SCUNILOGTARGET put points to. After a structure has been
	processed by this function, none of the logging functions can be called on it anymore, but
	it could however be re-used by initialising it again.

	Before calling this function, call ShutdownSCUNILOGTARGET () or CancelSCUNILOGTARGET ()
	first to either process or discard it's event queue.

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
SCUNILOGTARGET *DoneSCUNILOGTARGETstatic (void)
;

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
*/
void ShutdownSCUNILOGTARGET (SCUNILOGTARGET *put);

/*
	ShutdownSCUNILOGTARGETstatic

	Calls ShutdownSCUNILOGTARGET () on the internal static SUNILOGSTRUCT structure.
	This function should be called just before DoneSUNILOGTARGETstatic ();
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.
*/
void ShutdownSCUNILOGTARGETstatic (void);

/*
	CancelSCUNILOGTARGET

	Empties the logging queue for the SCUNILOGTARGET put without processing its events.
	The events currently in the queue are discarded. Logging functions called afterwards
	for this SCUNILOGTARGET structure fail and return false.

	The function waits for an existing separate logging thread to exit.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.
*/
void CancelSCUNILOGTARGET (SCUNILOGTARGET *put);

/*
	CancelSCUNILOGTARGETstatic

	Calls CancelSCUNILOGTARGET () on the internal static SUNILOGSTRUCT structure.
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.
*/
void CancelSCUNILOGTARGETstatic (void);

/*
	SetLogPrioritySCUNILOGTARGET

	Sets the priority of the separate logging thread that belongs to the specified
	SCUNILOGTARGET structure put points to.
	
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
	bool SetLogPrioritySCUNILOGTARGET (SCUNILOGTARGET *put, cunilogprio prio)
	;
#else
	#define SetLogPrioritySCUNILOGTARGET(p, p)	(true)
#endif

/*
	SetLogPrioritySCUNILOGTARGETstatic

	Sets the priority of the separate logging thread that belongs to internal static
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
	bool SetLogPrioritySCUNILOGTARGETstatic (cunilogprio prio)
	;
#else
	#define SetLogPrioritySCUNILOGTARGETstatic(p, p)	(true)
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
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
#else
	define PauseLogSCUNILOGTARGET(p)
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
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogSCUNILOGTARGETstatic (void)
	;
#else
	define PauseLogSCUNILOGTARGETstatic(p)
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
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	;
#else
	define ResumeLogSCUNILOGTARGET (p)
#endif

/*
	ResumeLogSCUNILOGTARGETstatic

	Resumes logging to the internal SCUNILOGTARGET structure after a call to
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
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogSCUNILOGTARGETstatic (void)
	;
#else
	define ResumeLogSCUNILOGTARGETstatic (p)
#endif

/*
	CreateSCUNILOGEVENT_Data

	Allocates a buffer that points to a new event structure SCUNILOGEVENT plus data, initialises
	it with the function parameters, and returns a pointer to the newly created and initialised
	structure and data buffer. The event is written out as binary data.

	Note that you can NOT use USE_STRLEN as the parameter siz.

	The function returns false if it fails.
*/
SCUNILOGEVENT *CreateSCUNILOGEVENT_Data	(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccCapt,
					size_t						lenCapt,
					const char					*ccData,
					size_t						siz
											)
;

/*
	CreateSCUNILOGEVENT_Text

	This is the text version of CreateSCUNILOGEVENTwithData (). If the string ccText is
	NUL-terminated a value of USE_STRLEN for len can be used.
*/
SCUNILOGEVENT *CreateSCUNILOGEVENT_Text		(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;

/*
	DoneSCUNILOGEVENT

	Destroys an SUNILOGEVENT structure including all its resources.

	The function always returns NULL.
*/
SCUNILOGEVENT *DoneSCUNILOGEVENT (SCUNILOGEVENT *pev)
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
	This function is called by all logging functions.

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

	The logBinary () function outputs
	a hex dump. The function logBinOrTextU8 () examines the provided data and treats it either
	as UTF-8 text or binary data for a hex dump.

	The functions without a severity use severity level/severity type cunilogEvtSeverityNone.
	Functions containing sev in their names accept a severity type.

	Functions that have U8 in their names are for UTF-8, the ones with a W are intended for
	Windows UTF-16 encoding.

	Functions ending in l accept a length parameter for the text's length, in octets/bytes. You
	can use USE_STRLEN for this parameter, in which case the text buffer's length is obtained
	via a call to strlen () and the string needs to be NUL-terminated. NUL-termination is not
	required otherwise. Note that the length parameter denotes the length of the text, in octets,
	not its size, and also not in characters. The text "abc" has a length of 3 but a size of 4
	octets, which includes the NUL-terminator. UTF-8 characters can have up to 4 octets/bytes.
	Cunilog writes out only UTF-8 but doesn't actually understand its encoding.

	The fmt versions offer variadic functionality like printf () does. The function
	logTextU8fmt () uses an additional memory allocation and deallocation internally. The sfmt
	type functions like logTextU8sfmt () use the stack for the fmt output if less than
	CUNILOG_DEFAULT_SFMT_SIZE bytes are required. Otherwise the heap is used.
	
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
bool logTextWsevl			(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len);
bool logTextU8sev			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText);
bool logTextWsev			(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText);
bool logTextU8l				(SCUNILOGTARGET *put, const char *ccText, size_t len);
bool logTextU8ql			(SCUNILOGTARGET *put, const char *ccText, size_t len);
bool logTextWl				(SCUNILOGTARGET *put, const wchar_t *cwText, size_t len);
bool logTextU8				(SCUNILOGTARGET *put, const char *ccText);
bool logTextU8q				(SCUNILOGTARGET *put, const char *ccText);
bool logTextW				(SCUNILOGTARGET *put, const wchar_t *cwText);
bool logTextU8fmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8qfmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sfmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sqfmt			(SCUNILOGTARGET *put, const char *fmt, ...);
bool logTextU8sfmtsev		(SCUNILOGTARGET *put, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbfmtsev		(SCUNILOGTARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbfmt		(SCUNILOGTARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logHexDumpU8sevl		(SCUNILOGTARGET *put, cueventseverity sev, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDumpU8l			(SCUNILOGTARGET *put, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDump				(SCUNILOGTARGET *put, const void *pBlob, size_t size);
bool logHexOrText			(SCUNILOGTARGET *put, const void *szText, size_t lenOrSize);
bool logHexOrTextU8			(SCUNILOGTARGET *put, const void *szU8TextOrBin, size_t lenOrSize);

#define logTextU8tsevl_static(v, t, l)	logTextU8sevl		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextWsevl_static(v, t, l)	logTextWsevl		(pSCUNILOGTARGETstatic, (v), (t), (l))
#define logTextU8sev_static(v, t)		logTextU8sevl		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextWsev_static(v, t)		logTextWsevl		(pSCUNILOGTARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8l_static(t, l)			logTextU8l			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextU8ql_static(t, l)		logTextU8ql			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextWl_static(t, l)			logTextWl			(pSCUNILOGTARGETstatic, (t), (l))
#define logTextU8_static(t)				logTextU8l			(pSCUNILOGTARGETstatic, (t), USE_STRLEN)
#define logTextU8q_static(t)			logTextU8ql			(pSCUNILOGTARGETstatic, (t), USE_STRLEN)
#define logTextW_static(t)				logTextW			(pSCUNILOGTARGETstatic, (t));
#define logTextU8fmt_static(...)		logTextU8fmt		(pSCUNILOGTARGETstatic, __VA_ARGS__)
#define logTextU8sfmt_static(...)		logTextU8sfmt		(pSCUNILOGTARGETstatic, __VA_ARGS__)
#define logTextU8sfmtsev_static(s, ...)	logTextU8sfmtsev	(pSCUNILOGTARGETstatic, (s), __VA_ARGS__)
#define logTextU8smbfmtsev_static(s, m, ...)			\
										logTextU8smbfmtsev	(pSCUNILOGTARGETstatic, (s), (m), __VA_ARGS__)
#define logTextU8smbfmt_static(m, ...)	logTextU8smbfmt		(pSCUNILOGTARGETstatic, (m), __VA_ARGS__)
#define logHexDumpU8sevl_static(s, d,					\
			n, c, l)									\
										logHexDumpU8sevl	(pSCUNILOGTARGETstatic, (s), (d), (n), (c), (l))
#define logHexDumpU8l_static(d, n, c,					\
			l)							logHexDumpU8l		(pSCUNILOGTARGETstatic, (d), (n), (c), (l))
#define logHexDump_static(d, s)			logHexDump			(pSCUNILOGTARGETstatic, (d), (s))
#define logHexOrTextU8_static(d, s)		logHexOrTextU8		(pSCUNILOGTARGETstatic, (d), (s))

/*
	The version as text, its year, and as a 64 bit number.
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
	only. This function ensures that the static library and cunilog_combined.h (actually:
	cunilogversion.h) fit together.

	The function aborts in debug versions. In release builds it merely returns the result
	of the comparison.
*/
/*
#define CUNILOG_VERSION_HDR							\
(		((uint64_t) CUNILOG_VERSION_MAJOR	<< 48)	\
	|	((uint64_t) CUNILOG_VERSION_MINOR	<< 32)	\
	|	((uint64_t) CUNILOG_VERSION_SUB		<< 16)	\
	|	((uint64_t) CUNILOG_VERSION_BUILD)			\
)
*/
#define CUNILOG_VERSION_HDR	((uint64_t) CUNILOG_VERSION_BUILD)
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
