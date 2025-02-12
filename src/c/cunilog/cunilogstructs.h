/****************************************************************************************

	File:		cunilogstructs.h
	Why:		Structures for cunilog.
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

#ifndef CUNILOGSTRUCTS_H
#define CUNILOGSTRUCTS_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./SingleBits.h"
		#include "./ubf_times.h"
		#include "./membuf.h"
		#include "./bulkmalloc.h"
		#include "./VectorC.h"
		#include "./platform.h"
		#include "./strintuint.h"
		#include "./strnewline.h"
		#include "./strhexdump.h"
		#include "./dbgcountandtrack.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/SingleBits.h"
		#include "./../datetime/ubf_times.h"
		#include "./../mem/membuf.h"
		#include "./../mem/bulkmalloc.h"
		#include "./../mem/VectorC.h"
		#include "./../pre/platform.h"
		#include "./../string/strintuint.h"
		#include "./../string/strnewline.h"
		#include "./../string/strhexdump.h"
		#include "./../dbg/dbgcountandtrack.h"
	#endif

#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
//#define CUNILOG_BUILD_SINGLE_THREADED_ONLY
#endif

#ifdef OS_IS_WINDOWS
	#include <Windows.h>
#else
	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		#include <semaphore.h>
		#include <pthread.h>
	#endif
#endif

/*
	Build options.

	CUNILOG_BUILD_SINGLE_THREADED_ONLY			Builds for a single-threaded application only.
												Code for other types than unilogSingleThreaded
												won't be built.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef CUNILOG_BUILD_MULTI_THREADED
	#error Either CUNILOG_BUILD_SINGLE_THREADED_ONLY or CUNILOG_BUILD_MULTI_THREADED can be defined but not both.
	#endif
	#ifdef CUNILOG_BUILD_MULTI_PROCESSES
	#error Only CUNILOG_BUILD_SINGLE_THREADED_ONLY or UNILOG_BUILD_MULTI_PROCESSES can be defined but not both.
	#endif
#endif
/*
	Currently not planned.

#ifdef CUNILOG_BUILD_MULTI_THREADED
	#ifdef CUNILOG_BUILD_MULTI_PROCESSES
	#error Only CUNILOG_BUILD_MULTI_THREADED or CUNILOG_BUILD_MULTI_PROCESSES can be defined but not both.
	#endif
#endif
#ifdef CUNILOG_BUILD_MULTI_PROCESSES
#endif
*/

BEGIN_C_DECLS

/*
	The constants for the log file extension. We got this in UTF-8
	(szCunilogLogFileNameExtension) and Windows UTF-16 (wcCunilogLogFileNameExtension).
	The constant lenCunilogLogFileNameExtension is the length in characters (not octets!).
*/
extern const char		*szCunilogLogFileNameExtension;			// ".log"
extern const wchar_t	*wcCunilogLogFileNameExtension;			// ".log"
extern const size_t		lenCunilogLogFileNameExtension;			// ".log"
extern const size_t		sizCunilogLogFileNameExtension;

/*
	enum unilogtype

	Specifies the application type of a cunilog target and how processing events is
	protected. These values are valid for a single target.
	Applications however can in theory work with an arbitrary number of targets, even if
	the targets are configured differently.


	cunilogSingleThreaded

	Only a single thread from one instance of the current application can safely write out
	logging information. Cunilog does not apply any concurrency protection.
	Writing logging information from more than a single thread, another instance of the
	same application, or from a different application is not supported and resulta in data
	corruption and application crashes. In a best case it may only lead to unusable
	logging information.

	Every logging function blocks as it executes the list of processors before returning.


	cunilogSingleThreadedSeparateLoggingThread

	Identical to cunilogSingleThreaded but the application must be built with multi-threading
	support. The process of writing out logging information (i.e. executing the list of
	processors) takes place in a separate thread.
	Calling logging functions from more than a single thread, another instance of the
	same application, or from a different application is not supported and results in
	data corruption and application crashes. In a best case it may only lead to unusable
	logging information.
	
	However, due to how this is currently implemented, some of these restrictions do not apply
	right now because cunilogSingleThreadedSeparateLoggingThread is actually identical to
	unilogMultiThreadedSeparateLoggingThread. Since this might and most likely will change in
	future versions of the software, use cunilogMultiThreadedSeparateLoggingThread to be safe.


	cunilogMultiThreaded

	Multiple threads from a single instance of the current application can safely write out
	logging information. Cunilog provides necessary concurrency protection for this case but
	does not protect logging information from being overwritten/destroyed by other processes.
	Any logging function called from any thread blocks as it works its way through the list of
	processors before releasing its lock and returning.


	cunilogMultiThreadedSeparateLoggingThread

	Identical to cunilogMultiThreaded but the process of writing out logging information (i.e.
	executing the list of processors) takes place in its own thread. Logging functions do
	not block. This is the preferred mode for most multi-threaded applications.


	cunilogMultiProcesses

	Logging information is fully protected and can be written from different threads as well
	as from different processes.
*/
enum cunilogtype
{
		cunilogSingleThreaded
	,	cunilogSingleThreadedSeparateLoggingThread
	,	cunilogMultiThreaded
	,	cunilogMultiThreadedSeparateLoggingThread
	,	cunilogMultiProcesses
	// Do not add anything below this line.
	,	cunilogTypeAmountEnumValues							// Used for table sizes.
	// Do not add anything below cunilogTypeAmountEnumValues.
};

/*
	The postfix applied to the application name.

	Example:
	"MyApp" + "_" + "YYYY-MM-DD HH_MI"

	Postfixes are ascending by default, meaning that newer logfiles cantain
	higher dates/numbers. For numbers we allow a maximum width of 20 digits,
	which is enough for a uint64_t.
*/
enum cunilogpostfix
{
		cunilogPostfixNone
	,	cunilogPostfixMinute								// "YYYY-MM-DD HH_MI"	
	,	cunilogPostfixMinuteT								// "YYYY-MM-DDTHH_MI"
	,	cunilogPostfixHour									// "YYYY-MM-DD HH"
	,	cunilogPostfixHourT									// "YYYY-MM-DDTHH"
	,	cunilogPostfixDay									// "YYYY-MM-DD"
	,	cunilogPostfixDefault = cunilogPostfixDay
	,	cunilogPostfixWeek									// "YYYY-Wnn"
	,	cunilogPostfixMonth									// "YYYY-MM"
	,	cunilogPostfixYear									// "YYYY"
	,	cunilogPostfixDotNumberDescending					// ".<number>.
	// Do not add anything below this line.
	,	cunilogPostfixAmountEnumValues						// Used for table sizes.
	// Do not add anything below cunilogPostfixAmountEnumValues.
};

/*
	The possible processors. This is the member task of a CUNILOG_PROCESSOR structure.


	cunilogProcessNoOperation

	This is a dummy processor and does nothing.


	cunilogProcessEchoToConsole

	Echoes/outputs the event line to the console


	cunilogProcessUpdateLogFileName

	Updates the name of the logfile. This probably shouldn't be a processor but if no logfile
	is required, not having this processor can save a few CPU cycles.


	cunilogProcessWriteToLogFile

	Carries out the actual write operation to the logfile. The member pData points to a
	CUNILOG_LOGFILE structure. If the file doesn't exist yet it is created and opened for
	writing to it. If the logfile exists, it is opened for writing.


	cunilogProcessFlushLogFile

	Flushes the logfile. The member pData points to the same CUNILOG_LOGFILE structure the
	cunilogProcessWriteToLogFile processor points to.


	cunilogProcessRotateLogfiles
	
	A logfile rotator. The member pDate points to a CUNILOG_ROTATION_DATA structure that
	contains details about the rotation.


	cunilogProcessCustomProcessor

	A custom processor. The member pData points to a CUNILOG_CUSTPROCESS structure that
	contains a pointer to a callback function to carry out the actual task of the processor.


	cunilogProcessTargetRedirector

	Redirects to another target. The member pData points to a fully initialised SCUNILOGTARGET
	structure to which the event is redirectred to. After the redirection further processing
	within the current target is suppressed, meaning that this is the last processor.

	If pData is NULL, no redirection takes place and the remaining processors are worked
	through as usual. Since this is most likely not what the caller intended, a debug
	assertion expects pData not being NULL.
*/
enum cunilogprocesstask
{
		cunilogProcessNoOperation							// Does nothing.
	,	cunilogProcessEchoToConsole							// Echoes to console.
	,	cunilogProcessUpdateLogFileName						// Updates full path to logfile.
	,	cunilogProcessWriteToLogFile						// Writes to logfile.
	,	cunilogProcessFlushLogFile							// Flushes the logfile.
	,	cunilogProcessRotateLogfiles						// Rotates logfiles.
	,	cunilogProcessCustomProcessor						// An external/custom processor.
	,	cunilogProcessTargetRedirector						// Redirect to different target.
	,	cunilogProcessTargetFork							// Fork the event to another target.
	// Do not add anything below this line.
	,	cunilogProcessAmountEnumValues						// Used for table sizes.
	// Do not add anything below cunilogProcessAmountEnumValues.
};

enum cunilogprocessfrequency
{
		cunilogProcessAppliesTo_nEvents						// Threshold is incremented for
															//	each event.
	,	cunilogProcessAppliesTo_nOctets						// Threshold counts the amount of
															//	octets logged.
	,	cunilogProcessAppliesTo_nAlways						// Threshold does not apply; always
															//	processed.
	,	cunilogProcessAppliesTo_SecondChanged				// Processed whenever the second
															//	changes.
	,	cunilogProcessAppliesTo_MinuteChanged				// Processed whenever the minute
															//	changes.
	,	cunilogProcessAppliesTo_HourChanged					// Processed whenever the hour
															//	changes.
	,	cunilogProcessAppliesTo_DayChanged					// Processed whenever the day
															//	changes.
	,	cunilogProcessAppliesTo_WeekChanged					// Processed whenever the week
															//	changes.
	,	cunilogProcessAppliesTo_MonthChanged				// Processed whenever the month
															//	changes.
	,	cunilogProcessAppliesTo_YearChanged					// Processed whenever the year
															//	changes.
	,	cunilogProcessAppliesTo_Auto						// Picks frequency automatically.
};

typedef struct scunilogtarget SCUNILOGTARGET;
typedef struct cunilog_processor
{
	enum cunilogprocesstask			task;					// What to apply.
	enum cunilogprocessfrequency	freq;					// When to apply
															//	(frequency/theshold type).

	// Trigger threshold and its current value.
	uint64_t						thr;					// Required value of cur before this
															//	processor is applied/run.
	uint64_t						cur;					// The current counter value.

	void							*pData;					// Pointer to processor-specific data.
	uint64_t						uiOpts;					// Option flags. See OPT_CUNPROC_
															//	definitions below.
} CUNILOG_PROCESSOR;

/*
	Option flags for the uiOpts member of a CUNILOG_PROCESSOR structure.
*/
#define OPT_CUNPROC_NONE				(0)
#define OPT_CUNPROC_FORCE_NEXT			SINGLEBIT64 (0)		// Carry on with the next processor
															//	even if this one has not been
															//	processed.
#define OPT_CUNPROC_AT_STARTUP			SINGLEBIT64 (1)		// Executes the processor on startup
															//	by ignoring cunilogprocesstype.
															//	The flag is then cleared.
#define OPT_CUNPROC_ALLOCATED			SINGLEBIT64 (2)		// This processor has been allocated
															//	on the heap and needs to be freed.
#define OPT_CUNPROC_DATA_ALLOCATED		SINGLEBIT64	(3)		// The pData member has been allocated
															//	on the heap and needs to be freed.
#define OPT_CUNPROC_DISABLED			SINGLEBIT64 (4)		// The processor is disabled, i.e.
															//	prevented from being processed.
															//	Carries on with the next processor
															//	unconditionally, just like
															//	OPT_CUNPROC_FORCE_NEXT.

/*
	Macros for some flags.
*/

#define optCunProcHasOPT_CUNPROC_AT_STARTUP(v)			\
	((v) & OPT_CUNPROC_AT_STARTUP)
#define optCunProcClrOPT_CUNPROC_AT_STARTUP(v)			\
	((v) &= ~ OPT_CUNPROC_AT_STARTUP)

#define optCunProcHasOPT_CUNPROC_DISABLED(v)			\
	((v) & OPT_CUNPROC_DISABLED)
#define optCunProcSetOPT_CUNPROC_DISABLED(v)			\
	((v) |= OPT_CUNPROC_DISABLED)
#define optCunProcClrOPT_CUNPROC_DISABLED(v)			\
	((v) &= ~ OPT_CUNPROC_DISABLED)

/*
	A pData structure for a unilogProcessWriteToLogFile or a unilogProcessFlushLogFile processor.
*/
typedef struct cunilog_logfile
{
	#ifdef OS_IS_WINDOWS
		HANDLE			hLogFile;
	#else
		FILE			*fLogFile;
	#endif
} CUNILOG_LOGFILE;

enum cunilogrotationtask
{
		cunilogrotationtask_None							// Ignored. No operation.
	,	cunilogrotationtask_FScompressLogfiles				// Compress logfiles with the help
															//	of the file system.
	,	cunilogrotationtask_MoveToRecycleBinLogfiles
	,	cunilogrotationtask_DeleteLogfiles
};

/*
	A pData structure for a unilogProcessRotateLogfiles processor.
*/
typedef struct cunilog_rotation_data
{
	enum cunilogrotationtask	tsk;						// The task to carry out.
	uint64_t					nIgnore;					// Amount of files/objects/artefacts
															//	to ignore.
	uint64_t					nCnt;						// Counter for nIgnore.
	uint64_t					nMaxToRotate;				// Don't rotate more than this.
															//	Ignored when 0.

	// Source and destiantion path names. Probably not required, at least with NTFS compression.
	SMEMBUF						mbSrcMask;					// Search mask. Only used when
															//	CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK
															//	set. See option flags below.
	SMEMBUF						mbDstFile;					// Name of file to rotate (destination
															//	file name). Only used when
															//	CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE
															//	set. See option flags below.
	SCUNILOGTARGET				*plogSCUNILOGTARGET;		// Pointer to a logging target.
															//	If this is NULL, the processor's
															//	target is logged to, without
															//	rotation.
	uint64_t					uiFlgs;						// Option flags. See below.
} CUNILOG_ROTATION_DATA;

/*
	CUNILOG_ROTATION_DATA option flags.
*/
#define CUNILOG_ROTATOR_FLAG_NONE							(0)

// Used by some rotators to distinguish if they need further initialisation.
#define CUNILOG_ROTATOR_FLAG_INITIALISED		SINGLEBIT64 (0)

// The rotator makes use of the mbSrcMask member. Without this flag, the rotator uses the
//	member mbLogFileMask of the SCUNILOGTARGET structure.
#define CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK		SINGLEBIT64 (1)

// The rotator makes use of the mbDstFile member. Without this flag, the rotator uses the
//	member mbFilToRotate of the SCUNILOGTARGET structure
#define CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE		SINGLEBIT64 (2)

/*
	Macros for some checking, setting, and clearing some of the flags above.
*/
#define cunilogHasRotatorFlag_USE_MBSRCMASK(pt)			\
	((pt)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogSetRotatorFlag_USE_MBSRCMASK(pt)			\
	((pt)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogClrRotatorFlag_USE_MBSRCMASK(pt)			\
	((pt)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)

#define cunilogHasRotatorFlag_USE_MBDSTFILE(pt)			\
	((pt)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogSetRotatorFlag_USE_MBDSTFILE(pt)			\
	((pt)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogClrRotatorFlag_USE_MBDSTFILE(pt)			\
	((pt)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	typedef struct cunilog_locker
	{
		#ifdef OS_IS_WINDOWS
			CRITICAL_SECTION	cs;
		#else
			pthread_mutex_t		mt;
		#endif
		#ifdef DEBUG
			bool				bInitialised;
		#endif
	} CUNILOG_LOCKER;

	typedef struct cunilog_semaphore
	{
		#ifdef OS_IS_WINDOWS
			HANDLE				hSemaphore;
		#else
			sem_t				tSemaphore;
		#endif
	} CUNILOG_SEMAPHORE;

	typedef struct cunilog_thread
	{
		#ifdef OS_IS_WINDOWS
			HANDLE				hThread;
		#else
			pthread_t			tThread;
		#endif
	} CUNILOG_THREAD;

	typedef struct scunilogevent SCUNILOGEVENT;
	typedef struct cunilog_queue_base
	{
		SCUNILOGEVENT			*first;						// First event.
		SCUNILOGEVENT			*last;						// Last event.
		size_t					num;						// Current amount of queue
															//	elements.
	} CUNILOG_QUEUE_BASE;
#endif

/*
	Textual representations of date/timestamp formats for an event/event line.
	The default is ""YYYY-MM-DD HH:MI:SS.000+01:00", followed by a space character.
	The value unilogEvtTS_ISO8601T follows the ISO 8601 specification by separating
	date and time with a 'T'.

	The value cunilogEvtTS_ISO8601_3spc adds 3 spaces instead of one, and so does the
	value cunilogEvtTS_ISO8601T_3spc but with a 'T' between date and time.

	Value cunilogEvtTS_NCSADT denotes a terribly hugly date/timestamp format webservers
	introduced just after the dinosaurs went extinct 66 million years ago. Worst part of
	this bit of history is probably that the date/timestamp is not the first column of an
	event line. See Common Log Format (https://en.wikipedia.org/wiki/Common_Log_Format)
	for details on the scope of the horror.
*/
enum cunilogeventTSformat
{
		cunilogEvtTS_ISO8601								// "YYYY-MM-DD HH:MI:SS.000+01:00 "
	,	cunilogEvtTS_Default		= cunilogEvtTS_ISO8601
	,	cunilogEvtTS_ISO8601T								// "YYYY-MM-DDTHH:MI:SS.000+01:00 "
	,	cunilogEvtTS_ISO8601_3spc							// "YYYY-MM-DD HH:MI:SS.000+01:00   "
	,	cunilogEvtTS_ISO8601T_3spc							// "YYYY-MM-DDTHH:MI:SS.000+01:00   "
	,	cunilogEvtTS_NCSADT									// "[10/Oct/2000:13:55:36 -0700] "
	// Do not add anything below this line.
	,	cunilogEvtTS_AmountEnumValues						// Used for table sizes.
	// Do not add anything below cunilogEvtTS_AmountEnumValues.
};

enum cunilogRunProcessorsOnStartup
{
		cunilogRunProcessorsOnStartup
	,	cunilogDontRunProcessorsOnStartup
	// Do not add anything below this line.
	,	cunilogRunProcessors_AmountEnumValues				// Used for table sizes.
	// Do not add anything below cunilogRunProcessors_AmountEnumValues.
};
typedef enum cunilogRunProcessorsOnStartup runProcessorsOnStartup;

/*
	SCUNILOGDUMP

	Holds the parameter structures for binary/octal/decimal/hex dumps.
*/
typedef struct scunilogdump
{
	void		*dump_prs;									// Pointer to a SHEX_DUMP_SAN structure.
	void		*dump_sns;									// Pointer to a SHEX_DUMP_SAN structure.
	SMEMBUF		mbDumpHeader;
	size_t		lnDumpHeader;
} SCUNILOGDUMP;

/*
	Structure for the vector that holds the filenames.
	A single char * would probably do if no length information is required.
*/
typedef struct cunilog_fls
{
	char	*chFilename;
	size_t	stFilename;
} CUNILOG_FLS;
typedef vec_t(CUNILOG_FLS) vec_cunilog_fls;

/*
	Base folder for a relative path or path if no log path at all is given.

	These are the possible enumeration values of the parameter relLogPath of the
	SCUNILOGTARGET initialisation functions.

	cunilogLogPath_isAbsolute

	The parameter szLogPath cannot be NULL, and it cannot be a relative path.


	cunilogLogPath_relativeToExecutable
	
	If szLogPath is a relative path, the path is assumed to be relative to the path of
	the executable file. If szLogPath is NULL, the path of the executable file is used.


	cunilogLogPath_relativeToCurrentDir

	If szLogPath is a relative path, the path is assumed to be relative to the current
	working directory. If szLogPath is NULL, the current working directory is used.
	The current working directory is obtained by the SCUNILOGTARGET initialisation functions
	and stays constant during the lifetime of this SCUNILOGTARGET. It is therefore safe for
	the application to change this directory any time after the initialisation function
	returned. Or, an application could set the current working directory to the desired
	szLogPath, call an SCUNILOGTARGET initialisation function with szLogPath set to NULL.


	cunilogLogPath_relativeToHomeDir

	If szLogPath is a relative path, the path is assumed to be relative to the current user's
	home folder. If szPath is NULL, the user's home directory is used.
*/
enum cunilogRelLogPath
{
		cunilogLogPath_isAbsolute
	,	cunilogLogPath_relativeToExecutable
	,	cunilogLogPath_relativeToCurrentDir
	,	cunilogLogPath_relativeToHomeDir
	// Do not add anything below this line.
	,	cunilogLogPath_AmountEnumValues						// Used for sanity checks.
	// Do not add anything below unilogRotationAmountEnumValues.
};
typedef enum cunilogRelLogPath enCunilogRelLogPath;

/*
	Structure to leave some information for the next processor.
*/
typedef struct scunilognpi
{
	SMEMBUF							smbRotMask;				// File search mask/glob pattern the
															//	next processor should use to
															//	enumerate files. Only required for
															//	rotators.
	size_t							lenRotMask;				// The length, excluding NUL, of
															//	smbRotMask; If this is 0,
															//	smbRotMask is unused/uninitialised.
	uint64_t						nIgnoredTotal;			// Ignored so far. Only if lenRotMask
															//	is 0.
	vec_cunilog_fls					*pNextVecCunilogFls;	// The next file to process. If this
															//	is NULL, the next rotator
															//	needs to start from scratch.
} SCUNILOGNPI;


/*
	Possible return values of the error/fail callback function.

	cunilogErrCB_next_processor			The error/fail callback function is called again for
										the next processor that fails, even for the same event.

	cunilogErrCB_next_event				The error/fail callback function is called again if the
										next event fails. It is not called for failing
										processors of this event.

	cunilogErrCB_shutdown				The Cunilog target is shutdown.

	cunilogErrCB_cancel					The Cunilog target is cancelled.
*/
enum enErrCBretval
{
		cunilogErrCB_next_processor
	,	cunilogErrCB_next_event
	,	cunilogErrCB_shutdown
	,	cunilogErrCB_cancel
	// Do not add anything below this line.
	,	cunilogErrCB_AmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogErrCB_AmountEnumValues.
};
typedef enum enErrCBretval errCBretval;

/*
	Error/fail callback function.
*/
typedef errCBretval (*cunilogErrCallback) (int64_t error, CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev);

typedef struct cunilog_rotator_args CUNILOG_ROTATOR_ARGS;

/*
	SUNILOGTARGET

	The base config structure for using cunilog. Do not alter any of its members directly.
	Always use the functions provided to alter its members.
*/
typedef struct scunilogtarget
{
	enum cunilogtype				culogType;
	enum cunilogpostfix				culogPostfix;
	uint64_t						uiOpts;
	SMEMBUF							mbLogPath;				// The logging folder/path to logfiles.
															//	On Windows, its last character is a
															//	backslash. On POSIX, its last character
															//	is a forward slash.
	size_t							lnLogPath;				// Its length excl. NUL terminator.
	SMEMBUF							mbAppName;				// Plain application name. Not NUL-terminated.
	size_t							lnAppName;				// Its length.
	#ifdef PLATFORM_IS_POSIX
		SMEMBUF						mbLogFold;				// The logging folder/path to logfiles.
															//	Same as mbLogPath but NUL-terminated
															//	and without slash at the end.
		size_t						lnLogFold;				// Its length exl. NUL terminator.
	#endif
	SMEMBUF							mbLogfileName;			// Path and name of current log file.
	char							*szDateTimeStamp;		// Points inside mbLogfileName.buf.pch.
	char							cPrevDateTimeStamp [LEN_ISO8601DATEHOURANDMINUTE];
	SMEMBUF							mbLogFileMask;			// The search mask for log files.
	#ifdef PLATFORM_IS_POSIX
		// Required for platforms that cannot return a directory listing with a search mask
		//	but return every file instead. The callback function then compares each returned
		//	filename with this mask/glob pattern.
		char						*szLogFileMask;			// Points inside mbLogFileMask to the
															//	application name plus stamp plus ".log".
		size_t						lnsLogFileMask;			// Its length.
	#endif
	SMEMBUF							mbFilToRotate;			// The file obtained by the cb function.
	SMEMBUF							mbLogEventLine;			// Buffer that holds the event line.
	size_t							lnLogEventLine;			// The current length of the event line.
	DBG_DEFINE_CNTTRACKER(evtLineTracker)					// Tracker for the size of the event
															//	line.

	SCUNILOGNPI						scuNPI;					// Information for the next processor.
	CUNILOG_PROCESSOR				**cprocessors;
	unsigned int					nprocessors;

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		CUNILOG_LOCKER				cl;						// Locker for events queue.
		CUNILOG_SEMAPHORE			sm;						// Semaphore for event queue.
		CUNILOG_QUEUE_BASE			qu;						// The actual event queue.
		CUNILOG_THREAD				th;						// The separate logging thread.

		size_t						nPendingNoRotEvts;		// Amount of currently pending non-
															//	rotation events.

		size_t						nPausedEvents;			// Amount of events queued because
															//	the logging thread is/was paused.
	#endif
	enum cunilogeventTSformat		unilogEvtTSformat;		// The format of an event timestamp.
	enum enLineEndings				unilogNewLine;
	SBULKMEM						sbm;					// Bulk memory block.
	vec_cunilog_fls					fls;					// The vector with str pointers to
															//	the files to rotate within sbm.
	// We're not using the configurable dump anymore.
	//SCUNILOGDUMP					*psdump;				// Holds the dump parameters.
	ddumpWidth						dumpWidth;

	cunilogErrCallback				errorCB;				// Error/fail callback function.
	CUNILOG_ROTATOR_ARGS			*prargs;				// Current rotator arguments.
} SCUNILOGTARGET;

/*
	The default initial size of an event line. Note that this is not the space for the text
	but rather the entire line, including timestamp etc. If you know in advance that your
	texts (including stamp etc) are going to be longer you may override this with a higher
	value to possibly save some initial heap reallocations.
*/
#ifndef CUNILOG_INITIAL_EVENTLINE_SIZE
#define CUNILOG_INITIAL_EVENTLINE_SIZE			(256)
#endif

/*
	Option flags for the uiOpts member of a SCUNILOGTARGET structure.
*/

// The initialiser.
#define CUNILOGTARGET_NO_FLAGS					(0)

// Event queue is shutting down or has shut down already.
//	This flags prevents further logging.
#define CUNILOGTARGET_SHUTDOWN					SINGLEBIT64 (0)

// Separate logging thread has shut down.
#define CUNILOGTARGET_HAS_SHUT_DOWN				SINGLEBIT64 (1)

// The structure has been allocated on the heap. This is for DoneSUNILOGTARGET ()
//	to deallocate it.
#define CUNILOGTARGET_ALLOCATED					SINGLEBIT64 (2)

// The filename of the log file has been allocated on the heap.
#define CUNILOGTARGET_LOGPATH_ALLOCATED			SINGLEBIT64 (3)

// The application name has been allocated on the heap.
#define CUNILOGTARGET_APPNAME_ALLOCATED			SINGLEBIT64 (4)

// The entire path plus name of the logfile has been allocated on the heap.
#define CUNILOGTARGET_LOGFILE_ALLOCATED			SINGLEBIT64 (5)

// The file mask.
#define CUNILOGTARGET_LOGF_MASK_ALLOCATED		SINGLEBIT64 (6)

// The (complete) filename of the file to rotate.
#define CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED	SINGLEBIT64 (7)

// The single event line.
#define CUNILOGTARGET_EVTLINE_ALLOCATED			SINGLEBIT64 (8)

// The array of pointers to processors.
#define CUNILOGTARGET_PROCESSORS_ALLOCATED		SINGLEBIT64 (9)

// Run all processors on startup, independent of their individual flags.
#define CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP	SINGLEBIT64 (10)

// The filesystem that holds the log files doesn't return filenames in
//	descending alphabetic order.
#define CUNILOGTARGET_FS_NEEDS_SORTING			SINGLEBIT64 (11)

// The separate logging thread, if one exists, is paused.
#define CUNILOGTARGET_PAUSED					SINGLEBIT64 (12)

// Debug versions ensure that one of the initialisation functions has been called.
#ifdef DEBUG
	#define CUNILOGTARGET_INITIALISED			SINGLEBIT64 (13)
	#define cunilogSetTargetInitialised(pt)				\
			((pt)->uiOpts |= CUNILOGTARGET_INITIALISED)
	#define cunilogIsTargetInitialised(pt)				\
			((pt)->uiOpts & CUNILOGTARGET_INITIALISED)
#else
	#define cunilogSetTargetInitialised(pt)	(true)
	#define cunilogIsTargetInitialised(pt)	(true)
#endif

// The echo/console output processor is skipped.
#define CUNILOGTARGET_NO_ECHO					SINGLEBIT64 (14)

// The processor that writes to the logfile is skipped.
#define CUNILOGTARGET_DONT_WRITE_TO_LOGFILE		SINGLEBIT64 (15)

/*
	Macros for some flags.
*/
#define cunilogSetShutdownTarget(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_SHUTDOWN)
#define cunilogIsShutdownTarget(pt)						\
	((pt)->uiOpts & CUNILOGTARGET_SHUTDOWN)

#define cunilogSetTargetHasShutdown(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_HAS_SHUT_DOWN)
#define cunilogIsTargetHasShutdown(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_HAS_SHUT_DOWN)

#define cunilogSetTargetAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_ALLOCATED)
#define cunilogIsTargetAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_ALLOCATED)

#define cunilogSetLogPathAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED)
#define cunilogIsLogPathAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_LOGPATH_ALLOCATED)

#define cunilogSetAppNameAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_APPNAME_ALLOCATED)
#define cunilogIsAppNameAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_APPNAME_ALLOCATED)

#define cunilogSetLogFileAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_LOGFILE_ALLOCATED)
#define cunilogIsLogFileAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_LOGFILE_ALLOCATED)

#define cunilogSetLogFileMaskAllocated(pt)				\
	((pt)->uiOpts |= CUNILOGTARGET_LOGF_MASK_ALLOCATED)
#define cunilogIsLogFileMaskAllocated(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_LOGF_MASK_ALLOCATED)

#define cunilogSetFileToRotateAllocated(pt)				\
	((pt)->uiOpts |= CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)
#define cunilogIsFileToRotateAllocated(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)

#define cunilogSetEvtLineAllocated(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_EVTLINE_ALLOCATED)
#define cunilogIsEvtLineAllocated(pt)					\
	((pt)->uiOpts & CUNILOGTARGET_EVTLINE_ALLOCATED)

#define cunilogSetProcessorsAllocated(pt)				\
	((pt)->uiOpts |= CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogClrProcessorsAllocated(pt)				\
	((pt)->uiOpts &= ~ CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogIsProcessorsAllocated(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_PROCESSORS_ALLOCATED)

#define cunilogHasRunAllProcessorsOnStartup(pt)			\
	((pt)->uiOpts & CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogClrRunAllProcessorsOnStartup(pt)			\
	((pt)->uiOpts &= ~ CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogSetRunAllProcessorsOnStartup(pt)			\
	((pt)->uiOpts |= CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)

#define cunilogIsFSneedsSorting(pt)						\
	((pt)->uiOpts & CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogClrFSneedsSorting(pt)					\
	((pt)->uiOpts &= ~ CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogSetFSneedsSorting(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_FS_NEEDS_SORTING)

#define cunilogIsPaused(pt)								\
	((pt)->uiOpts & CUNILOGTARGET_PAUSED)
#define cunilogClrPaused(pt)							\
	((pt)->uiOpts &= ~ CUNILOGTARGET_PAUSED)
#define cunilogSetPaused(pt)							\
	((pt)->uiOpts |= CUNILOGTARGET_PAUSED)

#define cunilogIsNoEcho(pt)								\
	((pt)->uiOpts & CUNILOGTARGET_NO_ECHO)
#define cunilogClrNoEcho(pt)							\
	((pt)->uiOpts &= ~ CUNILOGTARGET_NO_ECHO)
#define cunilogSetNoEcho(pt)							\
	((pt)->uiOpts |= CUNILOGTARGET_NO_ECHO)

#define cunilogHasDontWriteToLogfile(pt)				\
	((pt)->uiOpts & CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogClrNoWriteToLogfile(pt)					\
	((pt)->uiOpts &= ~ CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogSetNoWriteToLogfile(pt)					\
	((pt)->uiOpts |= CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)


/*
	Event severities.

	If changed, please update the copy in the comments of cunilog.c too.
*/
enum cunilogeventseverity
{
		cunilogEvtSeverityNone									//  0
	,	cunilogEvtSeverityBlanks								//  1
	,	cunilogEvtSeverityEmergency								//	2
	,	cunilogEvtSeverityNotice								//	3
	,	cunilogEvtSeverityInfo									//  4
	,	cunilogEvtSeverityMessage								//  5
	,	cunilogEvtSeverityWarning								//  6
	,	cunilogEvtSeverityError									//  7
	,	cunilogEvtSeverityFail									//  8
	,	cunilogEvtSeverityCritical								//  9
	,	cunilogEvtSeverityFatal									// 10
	,	cunilogEvtSeverityDebug									// 11
	,	cunilogEvtSeverityTrace									// 12
	,	cunilogEvtSeverityDetail								// 13
	,	cunilogEvtSeverityVerbose = cunilogEvtSeverityDetail	// 13
	,	cunilogEvtSeverityIllegal								// 14
};
typedef enum cunilogeventseverity cueventseverity;

enum cunilogeventtype
{
		cunilogEvtTypeNormalText							// Normal UTF-8 text.

		/*
			Caption + hex dump.The number specifies the bit width of the caption's length.
			The caption text follows its length. The caption is not NUL-terminated.
			Member lenDataToLog only counts the amount of data to dump out, excluding
			caption and its length.
		*/
	,	cunilogEvtTypeHexDumpWithCaption8					// Caption length is 8 bit.
	,	cunilogEvtTypeHexDumpWithCaption16					// Caption length is 16 bit.
	,	cunilogEvtTypeHexDumpWithCaption32					// Caption length is 32 bit.
	,	cunilogEvtTypeHexDumpWithCaption64					// Caption length is 64 bit.
	// Do not add anything below this line.
	,	cunilogEvtTypeAmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogEvtTypeAmountEnumValues.
};
typedef enum cunilogeventtype cueventtype;

/*
	SCUNILOGEVENT

	A logging event structure.

	Note that if the data is dump data, szDataToLog points to a length field of between 1
	and 8 octets, followed by a caption text without NUL, and this again followed by the
	actual dump data. The member lenDataToLog contains the length of the actual dump data
	*only*,. i.e. neither length field nor caption text count towards lenDataToLog.
*/
typedef struct scunilogevent
{
	SCUNILOGTARGET				*pSCUNILOGTARGET;			// The event's target/destination.
	uint64_t					uiOpts;						// Option flags.
	UBF_TIMESTAMP				stamp;						// Its date/timestamp.
	unsigned char				*szDataToLog;				// Data to log.
	size_t						lenDataToLog;				// Its length, not NUL-terminated.

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		struct scunilogevent	*next;
	#endif
	cueventseverity				evSeverity;
	cueventtype					evType;						// The event's type of data.
	size_t						sizEvent;					// The total allocated size of the
															//	event. If 0, the size is the size
															//	of the structure.
} SCUNILOGEVENT;

/*
	FillSCUNILOGEVENT

	Macro to fill a SCUNILOGEVENT structure. Note that the structure doesn't have a
	->next member if CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define FillSCUNILOGEVENT(pev, pt,					\
				opts, dts, sev, tpy, dat, len, siz)		\
		(pev)->pSCUNILOGTARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len;			\
		(pev)->evSeverity				= sev;			\
		(pev)->evType					= tpy;			\
		(pev)->sizEvent					= siz
#else
	#define FillSCUNILOGEVENT(pev, pt,					\
				opts, dts, sev, tpy, dat, len, siz)		\
		(pev)->pSCUNILOGTARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len;			\
		(pev)->next						= NULL;			\
		(pev)->evSeverity				= sev;			\
		(pev)->evType					= tpy;			\
		(pev)->sizEvent					= siz
#endif

/*
	Member uiOpts of a SCUNILOGEVENT structure.
*/

#define CUNILOGEVENT_NO_FLAGS			(0)

// The structure has been allocated on the heap. This is for DoneSUNILOGEVENT ()
//	to deallocate it.
#define CUNILOGEVENT_ALLOCATED			SINGLEBIT64 (0)

// The data has been allocated. This is also for DoneSUNILOGEVENT ().
#define CUNILOGEVENT_DATA_ALLOCATED		SINGLEBIT64 (1)

// Shuts down logging.
#define CUNILOGEVENT_SHUTDOWN			SINGLEBIT64 (2)

// Cancels outstanding events and shuts down logging.
// Unused/obsolete.
//#define CUNILOGEVENT_CANCEL				SINGLEBIT64 (3)

// The data is to be written out as a binary dump.
//	Replaced by cueventtype.
//#define CUNILOGEVENT_AS_HEXDUMP			SINGLEBIT64 (4)

// Add fullstop automatically.
#define CUNILOGEVENT_AUTO_FULLSTOP		SINGLEBIT64 (5)

// No rotation for this event. This is very fast/quick logging.
//	It is also used for internal logging.
#define CUNILOGEVENT_NOROTATION			SINGLEBIT64 (6)

// Suppresses the remaining processors.
#define CUNILOGEVENT_STOP_PROCESSING	SINGLEBIT64	(7)

// Macros to set and check flags.
#define cunilogSetEventAllocated(pue)					\
	((pue)->uiOpts |= CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventAllocated(pue)					\
	((pue)->uiOpts & CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventDataAllocated(pue)				\
	((pue)->uiOpts & CUNILOGEVENT_DATA_ALLOCATED)
#define cunilogSetEventShutdown(pue)					\
	((pue)->uiOpts |= CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventShutdown(pue)						\
	((pue)->uiOpts & CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventCancel(pue)						\
	((pue)->uiOpts & CUNILOGEVENT_CANCEL)

/* Replaced by cueventtype.
#define cunilogSetEventHexdump(pue)						\
	((pue)->uiOpts |= CUNILOGEVENT_AS_HEXDUMP)
#define cunilogIsEventHexdump(pue)						\
	((pue)->uiOpts & CUNILOGEVENT_AS_HEXDUMP)
*/

#define cunilogSetEventAutoFullstop(pue)				\
	((pue)->uiOpts |= CUNILOGEVENT_AUTO_FULLSTOP)
#define cunilogIsEventAutoFullstop(pue)					\
	((pue)->uiOpts & CUNILOGEVENT_AUTO_FULLSTOP)

#define cunilogHasEventNoRotation(pue)					\
	((pue)->uiOpts & CUNILOGEVENT_NOROTATION)
#define cunilogSetEventNoRotation(pue)					\
	((pue)->uiOpts |= CUNILOGEVENT_NOROTATION)

#define cunilogSetEventStopProcessing(pev)				\
	((pev)->uiOpts |= CUNILOGEVENT_STOP_PROCESSING)
#define cunilogClrEventStopProcessing(pev)				\
	((pev)->uiOpts &= ~ CUNILOGEVENT_STOP_PROCESSING)
#define cunilogHasEventStopProcessing(pev)				\
	((pev)->uiOpts & CUNILOGEVENT_STOP_PROCESSING)

/*
	Return type of the separate logging thread.
*/
#ifdef OS_IS_WINDOWS
	#define SEPARATE_LOGGING_THREAD_RETURN_TYPE			\
			DWORD WINAPI
#else
	#define SEPARATE_LOGGING_THREAD_RETURN_TYPE			\
			void *
#endif

/*
	Return values of the separate logging thread.
*/
#ifdef OS_IS_WINDOWS
	#define SEPARATE_LOGGING_THREAD_RETURN_SUCCESS		\
			(EXIT_SUCCESS)
	#define SEPARATE_LOGGING_THREAD_RETURN_FAILURE		\
			(EXIT_FAILURE)
#else
	#define SEPARATE_LOGGING_THREAD_RETURN_SUCCESS		\
			((void *) EXIT_SUCCESS)
	#define SEPARATE_LOGGING_THREAD_RETURN_FAILURE		\
			((void *) EXIT_FAILURE)
#endif

/*
	Parameter structure for rotator processor.
*/
typedef struct cunilog_rotator_args
{
	CUNILOG_PROCESSOR		*cup;
	SCUNILOGEVENT			*pev;
	char					*nam;							// Name of file to rotate.
	size_t					siz;							// Its size, incl. NUL.
} CUNILOG_ROTATOR_ARGS;

/*
	A callback function of a custom processor.
*/
typedef bool (*pfCustProc) (CUNILOG_PROCESSOR *, SCUNILOGEVENT *);

/*
	A pData structure for a unilogProcessCustomProcessor (custom/external) processor.
*/
typedef struct cunilog_custprocess
{
	void			*pData;
	pfCustProc		procFnc;
} CUNILOG_CUSTPROCESS;

/*
	The priority levels of the separate logging thread.

	When changing this enum, please also update the comment in cunilog.c.
*/
enum enCunilogLogPriority
{
	cunilogPrioNormal,
	cunilogPrioBelowNormal,
	cunilogPrioLow,
	cunilogPrioIdle,
	cunilogPrioBeginBackground,
	cunilogPrioEndBackground,
	// Do not insert enum values below this line.
	cunilogPrioAmountEnumValues
};
typedef enum enCunilogLogPriority	cunilogprio;

/*
	An element of the array with the files.
*/
typedef struct cunilogfilename
{
	const char	*szFilename;
	size_t		stLen;
} CUNILOGFILENAME;

END_C_DECLS

#endif														// Of #ifndef CUNILOGSTRUCTS_H.
