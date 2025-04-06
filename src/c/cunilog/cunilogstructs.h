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
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
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

#ifndef CUNILOGSTRUCTS_H
#define CUNILOGSTRUCTS_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./cunilogdefs.h"
	#include "./cunilogerrors.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./DLLimport.h"
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
		#include "./../pre/DLLimport.h"
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

/*
	If we're building a Windows DLL we got to turn all our features on.
	Otherwise we'd have to maintain different .def files depending on the build
	options defined.
*/
#ifdef CUNILOG_BUILD_SHARED_LIBRARY

	#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#undef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#undef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	#undef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	#undef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	#undef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	#endif

#endif


BEGIN_C_DECLS

/*
	The constants for the log file extension. We got this in UTF-8
	(szCunilogLogFileNameExtension) and Windows UTF-16 (wcCunilogLogFileNameExtension).
	The constant lenCunilogLogFileNameExtension is the length in characters (not octets!).
*/
CUNILOG_DLL_IMPORT extern const char		*szCunilogLogFileNameExtension;			// ".log"
CUNILOG_DLL_IMPORT extern const wchar_t		*wcCunilogLogFileNameExtension;			// ".log"
CUNILOG_DLL_IMPORT extern const size_t		lenCunilogLogFileNameExtension;			// ".log"
CUNILOG_DLL_IMPORT extern const size_t		sizCunilogLogFileNameExtension;

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
	as from different processes. This is currently not supported and hasn't been implemented
	yet.
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
	,	cunilogPostfixDotNumberMinutely						// ".<number>", rotation every minute.
	,	cunilogPostfixDotNumberHourly						// ".<number>", rotation every hour.
	,	cunilogPostfixDotNumberDaily
	,	cunilogPostfixDotNumberWeekly
	,	cunilogPostfixDotNumberMonthly
	,	cunilogPostfixDotNumberYearly
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

	Carries out the actual write operation to the logfile. The member pData must be NULL.
	If the file doesn't exist yet it is created and opened for writing. If the logfile exists,
	it is opened for writing. The file is closed when no longer required.


	cunilogProcessFlushLogFile

	Flushes the logfile. The member pData must be NULL.


	cunilogProcessRotateLogfiles
	
	A logfile rotator. The member pDate points to a CUNILOG_ROTATION_DATA structure that
	contains details about the rotation.


	cunilogProcessCustomProcessor

	A custom processor. The member pData points to a CUNILOG_CUSTPROCESS structure that
	contains a pointer to a callback function to carry out the actual task of the processor.


	cunilogProcessTargetRedirector

	Redirects to another target. The member pData points to a fully initialised CUNILOG_TARGET
	structure to which events are redirectred to. After the redirection further processing
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

typedef struct CUNILOG_TARGET CUNILOG_TARGET;
typedef struct cunilog_processor
{
	enum cunilogprocesstask			task;					// What to apply.
	enum cunilogprocessfrequency	freq;					// When to apply
															//	(frequency/theshold type).

	// Trigger threshold and its current value. These are 0-indexed.
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
	This probably shouldn't be a structure but leaves room for possible extensions.
*/
typedef struct cunilog_logfile
{
	#ifdef OS_IS_WINDOWS
		HANDLE			hLogFile;
	#else
		FILE			*fLogFile;
	#endif
} CUNILOG_LOGFILE;

/*
	Note that
	cunilogrotationtask_MoveToTrashLogfiles			and
	cunilogrotationtask_MoveToRecycleBinLogfiles	are identical to accomodate for
	Linux or Windows naming preference.
*/
enum cunilogrotationtask
{
		cunilogrotationtask_None							// Ignored. No operation.
	,	cunilogrotationtask_RenameLogfiles					// Rotates by renaming files.
	,	cunilogrotationtask_FScompressLogfiles				// Compress logfiles with the help
															//	of the file system.
	,	cunilogrotationtask_MoveToTrashLogfiles
	,	cunilogrotationtask_MoveToRecycleBinLogfiles = cunilogrotationtask_MoveToTrashLogfiles
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
	CUNILOG_TARGET				*plogCUNILOG_TARGET;		// Pointer to a logging target.
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
//	member mbLogFileMask of the CUNILOG_TARGET structure.
#define CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK		SINGLEBIT64 (1)

// The rotator makes use of the mbDstFile member. Without this flag, the rotator uses the
//	member mbFilToRotate of the CUNILOG_TARGET structure
#define CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE		SINGLEBIT64 (2)

/*
	Macros for checking, setting, and clearing some of the flags above.
*/
#define cunilogHasRotatorFlag_USE_MBSRCMASK(prd)		\
	((prd)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogSetRotatorFlag_USE_MBSRCMASK(prd)		\
	((prd)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogClrRotatorFlag_USE_MBSRCMASK(prd)		\
	((prd)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)

#define cunilogHasRotatorFlag_USE_MBDSTFILE(prd)		\
	((prd)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogSetRotatorFlag_USE_MBDSTFILE(prd)		\
	((prd)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogClrRotatorFlag_USE_MBDSTFILE(prd)		\
	((prd)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)


// Value of member nMaxToRotate of a CUNILOG_ROTATION_DATA structure to be obtained
//	during initialisation.
#ifndef CUNILOG_MAX_ROTATE_AUTO
#define CUNILOG_MAX_ROTATE_AUTO			(UINT64_MAX)
#endif

/*
	Initialisers for CUNILOG_ROTATION_DATA structures.

	Note that
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_TRASH()			and
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN()	are identical.
*/
/*
	
*/
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES()\
{														\
	cunilogrotationtask_RenameLogfiles,					\
	0, 0, CUNILOG_MAX_ROTATE_AUTO,						\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}

/*
	Argument k is the amount of logfiles to keep/not touch.
*/
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_FS_COMPRESS(k)\
{														\
	cunilogrotationtask_FScompressLogfiles,				\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_TRASH(k)\
{														\
	cunilogrotationtask_MoveToTrashLogfiles,			\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN(k)\
{														\
	cunilogrotationtask_MoveToRecycleBinLogfiles,		\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_DELETE(k)\
{														\
	cunilogrotationtask_DeleteLogfiles,					\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}

/*
	Initialisers for processor tasks.
*/
#define CUNILOG_INIT_DEF_ECHO_PROCESSOR					\
{														\
	cunilogProcessEchoToConsole,						\
	cunilogProcessAppliesTo_nAlways,					\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
#define CUNILOG_INIT_DEF_UPDATELOGFILENAME_PROCESSOR	\
{														\
	cunilogProcessUpdateLogFileName,					\
	cunilogProcessAppliesTo_nAlways,					\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
/*
	Argument plf is a pointer to a CUNILOG_LOGFILE structure.
*/
#define CUNILOG_INIT_DEF_WRITETTOLOGFILE_PROCESSOR		\
{														\
	cunilogProcessWriteToLogFile,						\
	cunilogProcessAppliesTo_nAlways,					\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_NONE									\
}
#define CUNILOG_INIT_DEF_FLUSHLOGFILE_PROCESSOR			\
{														\
	cunilogProcessFlushLogFile,							\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_RenameLogfiles. Such a structure can
	be initialised with the CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES()
	macro.
*/
#define CUNILOG_INIT_DEF_RENAMELOGFILES_PROCESSOR(p)	\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),							\
	OPT_CUNPROC_NONE | OPT_CUNPROC_AT_STARTUP			\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_FScompressLogfiles. Such a structure can
	be initialised with the CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_FS_COMPRESS()
	macro.
*/
#define CUNILOG_INIT_DEF_LOGFILESFSCOMPRESS_PROCESSOR(p)\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),							\
	OPT_CUNPROC_NONE | OPT_CUNPROC_AT_STARTUP			\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_MoveToRecycleBinLogfiles.
*/
#define CUNILOG_INIT_DEF_LOGFILESMOVETOTRASH_PROCESSOR(p)\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),												\
	OPT_CUNPROC_NONE | OPT_CUNPROC_AT_STARTUP			\
}


/*
	FillCUNILOG_PROCESSOR

	Function/macro to initialise a CUNILOG_PROCESSOR structure. The data (pData) member
	is set to NULL and the member uiOpts to OPT_CUNPROC_NONE, which means no option flags
	are set. The caller is responsible for setting those members to their desired values
	afterwards.
*/
#define FillCUNILOG_PROCESSOR(cup, task,				\
								freq, thrs)				\
	ubf_assert_non_NULL (cup);							\
	(cup)->task		= task;								\
	(cup)->freq		= freq;								\
	(cup)->thr		= thrs;								\
	(cup)->cur		= 0;								\
	(cup)->pData	= NULL;								\
	(cup)->uiOpts	= OPT_CUNPROC_NONE;

#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	typedef struct CUNILOG_EVENT CUNILOG_EVENT;
#else
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

	typedef struct CUNILOG_EVENT CUNILOG_EVENT;
	typedef struct cunilog_queue_base
	{
		CUNILOG_EVENT			*first;						// First event.
		CUNILOG_EVENT			*last;						// Last event.
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
	Base folder for a relative path or path if no path at all is given.

	These are the possible enumeration values of the parameter relLogPath of the
	CUNILOG_TARGET initialisation functions.

	cunilogPath_isAbsolute

	The path parameter cannot be NULL, and it cannot be a relative path.


	cunilogPath_relativeToExecutable
	
	If path is a relative path, it is assumed to be relative to the path of
	the executable file. If the path is NULL, the path of the executable file is used.


	cunilogPath_relativeToCurrentDir

	If the path parameter is a relative path, the path is assumed to be relative to the
	current working directory. If path is NULL, the current working directory is used.
	The current working directory is obtained by the CUNILOG_TARGET initialisation functions
	and stays constant during the lifetime of this CUNILOG_TARGET. It is therefore safe for
	the application to change this directory any time after the initialisation function
	returned. Or, an application could set the current working directory to the desired
	szLogPath, call an CUNILOG_TARGET initialisation function with szLogPath set to NULL.


	cunilogPath_relativeToHomeDir

	If path is a relative path, the path is assumed to be relative to the current user's
	home folder. If path is NULL, the user's home directory is used.
*/
enum cunilogRelPath
{
		cunilogPath_isAbsolute
	,	cunilogPath_relativeToExecutable
	,	cunilogPath_relativeToCurrentDir
	,	cunilogPath_relativeToHomeDir
	// Do not add anything below this line.
	,	cunilogPath_XAmountEnumValues						// Used for sanity checks.
	// Do not add anything below unilogRotationAmountEnumValues.
};
typedef enum cunilogRelPath enCunilogRelPath;

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

#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	/*
		Possible return values of the error/fail callback function.

		cunilogErrCB_next_processor			The current processor is cancelled and the next
											processor is going to be processed. The error/fail
											callback function is called again for the next
											processor that fails, even for the same event.

		cunilogErrCB_next_event				The current event is cancelled. No other processors
											are run.

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
	typedef errCBretval (*cunilogErrCallback)	(
						CUNILOG_ERROR				error,
						CUNILOG_PROCESSOR			*cup,
						CUNILOG_EVENT				*pev
												);
#endif

typedef struct cunilog_rotator_args CUNILOG_ROTATOR_ARGS;

/*
	The type/format of an event severity level.
*/
enum cunilogeventseveritytpy
{
		cunilogEvtSeverityTypeChars3							// "EMG", "DBG"... (default).
	,	cunilogEvtSeverityTypeDefault = cunilogEvtSeverityTypeChars3
	,	cunilogEvtSeverityTypeChars5							// "EMRGY", "DEBUG"...
	,	cunilogEvtSeverityTypeChars9							// "EMERGENCY", "DEBUG    "...
	,	cunilogEvtSeverityTypeChars3InBrackets					// "[EMG]", "[DBG]"...
	,	cunilogEvtSeverityTypeChars5InBrackets					// "[EMRGY]", "[DEBUG]"...
	,	cunilogEvtSeverityTypeChars9InBrackets					// "[EMERGENCY]", "[DEBUG    ]"...
	,	cunilogEvtSeverityTypeChars5InTightBrackets				// "[FAIL] "...
	,	cunilogEvtSeverityTypeChars9InTightBrackets				// "[DEBUG]    "...
	// Do not add anything below this line.
	,	cunilogEvtSeverityTypeXAmountEnumValues					// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityTypeXAmountEnumValues.
};
typedef enum cunilogeventseveritytpy cueventsevfmtpy;

/*
	SUNILOGTARGET

	The base config structure for using cunilog. Do not alter any of its members directly.
	Always use the functions provided to alter its members.
*/
typedef struct CUNILOG_TARGET
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
	size_t							stFilToRotate;			// Its length including the NUL terminator.
	SMEMBUF							mbLogEventLine;			// Buffer that holds the event line.
	size_t							lnLogEventLine;			// The current length of the event line.

	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
		SMEMBUF						mbColEventLine;			// Buffer that holds the coloured
															//	event line.
		size_t						lnColEventLine;			// The current length of the coloured
															//	event line.
	#endif

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
	newline_t						unilogNewLine;
	CUNILOG_LOGFILE					logfile;
	SBULKMEM						sbm;					// Bulk memory block.
	vec_cunilog_fls					fls;					// The vector with str pointers to
															//	the files to rotate within sbm.
	// We're not using the configurable dump anymore.
	//SCUNILOGDUMP					*psdump;				// Holds the dump parameters.
	ddumpWidth						dumpWidth;

	cueventsevfmtpy					evSeverityType;			// Format of the event severity.

	CUNILOG_ERROR					error;
	#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
		cunilogErrCallback			errorCB;				// Error/fail callback function.
	#endif
	CUNILOG_ROTATOR_ARGS			*prargs;				// Current rotator arguments.
} CUNILOG_TARGET;

/*
	Internal option flags for the uiOpts member of a CUNILOG_TARGET structure.
	These should not be changed by callers/users.
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

// The array of pointers to processors.
#define CUNILOGTARGET_PROCESSORS_ALLOCATED		SINGLEBIT64 (8)

// Run all processors on startup, independent of their individual flags.
#define CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP	SINGLEBIT64 (9)

// The filesystem that holds the log files doesn't return filenames in
//	descending alphabetic order.
#define CUNILOGTARGET_FS_NEEDS_SORTING			SINGLEBIT64 (10)

// The "file.log.1" (dot number postfix) requires this.
#define CUNILOGTARGET_NEEDS_NUMBER_SORTING		SINGLEBIT64 (11)

// The elements of the member fls (a vecotr) are in reversed order.
#define CUNILOGTARGET_FLS_REVERSED				SINGLEBIT64 (12)

// The separate logging thread, if one exists, is paused.
#define CUNILOGTARGET_PAUSED					SINGLEBIT64 (13)

// Debug versions ensure that one of the initialisation function has been called.
#ifdef DEBUG
	#define CUNILOGTARGET_INITIALISED			SINGLEBIT64 (14)
	#define cunilogSetTargetInitialised(pt)				\
			((pt)->uiOpts |= CUNILOGTARGET_INITIALISED)
	#define cunilogIsTargetInitialised(pt)				\
			((pt)->uiOpts & CUNILOGTARGET_INITIALISED)
#else
	#define cunilogSetTargetInitialised(pt)	(true)
	#define cunilogIsTargetInitialised(pt)	(true)
#endif

// Debug flag when the queue is locked. To be removed in the future.
#define CUNILOGTARGET_DEBUG_QUEUE_LOCKED		SINGLEBIT64 (20)


/*
	Public option flags for the uiOpts member of a CUNILOG_TARGET structure.
	Flags callers/users can change/use.
*/

// Tells the initialiser function(s) not to allocate/assign default processors.
//	The target is not ready when this option flag is used. The function
//	ConfigCUNILOG_TARGETprocessorList () must be called before the target
//	is usable.
#define CUNILOGTARGET_NO_DEFAULT_PROCESSORS		SINGLEBIT64 (32)

/*
	By default, timestamps are created when an event is created.With this bit set,
	timestamps are created when they are enqueued. This ensures that events that
	are enqueued later have a newer timestamp but also locks the queue much longer
	because the timestamp is obtained during this process. Without this flag,
	timestamps are created when the event is created, and outside the lock.
*/
#define CUNILOGTARGET_ENQUEUE_TIMESTAMPS		SINGLEBIT64 (33)

// The echo/console output processor is skipped.
#define CUNILOGTARGET_NO_ECHO					SINGLEBIT64 (34)

// The processor that writes to the logfile is skipped.
#define CUNILOGTARGET_DONT_WRITE_TO_LOGFILE		SINGLEBIT64 (35)

// Colour information should be used.
#define CUNILOGTARGET_USE_COLOUR_FOR_ECHO		SINGLEBIT64 (36)

/*
	Macros for some flags.
*/
#define cunilogSetShutdownTarget(put)					\
	((put)->uiOpts |= CUNILOGTARGET_SHUTDOWN)
#define cunilogIsShutdownTarget(put)					\
	((put)->uiOpts & CUNILOGTARGET_SHUTDOWN)

#define cunilogSetTargetHasShutdown(put)				\
	((put)->uiOpts |= CUNILOGTARGET_HAS_SHUT_DOWN)
#define cunilogIsTargetHasShutdown(put)					\
	((pt)->uiOpts & CUNILOGTARGET_HAS_SHUT_DOWN)

#define cunilogSetTargetAllocated(put)					\
	((put)->uiOpts |= CUNILOGTARGET_ALLOCATED)
#define cunilogIsTargetAllocated(put)					\
	((put)->uiOpts & CUNILOGTARGET_ALLOCATED)

#define cunilogSetLogPathAllocated(put)					\
	((put)->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED)
#define cunilogIsLogPathAllocated(put)					\
	((put)->uiOpts & CUNILOGTARGET_LOGPATH_ALLOCATED)

#define cunilogSetAppNameAllocated(put)					\
	((put)->uiOpts |= CUNILOGTARGET_APPNAME_ALLOCATED)
#define cunilogIsAppNameAllocated(put)					\
	((put)->uiOpts & CUNILOGTARGET_APPNAME_ALLOCATED)

#define cunilogSetLogFileAllocated(put)					\
	((put)->uiOpts |= CUNILOGTARGET_LOGFILE_ALLOCATED)
#define cunilogIsLogFileAllocated(put)					\
	((put)->uiOpts & CUNILOGTARGET_LOGFILE_ALLOCATED)

#define cunilogSetLogFileMaskAllocated(put)				\
	((put)->uiOpts |= CUNILOGTARGET_LOGF_MASK_ALLOCATED)
#define cunilogIsLogFileMaskAllocated(put)				\
	((put)->uiOpts & CUNILOGTARGET_LOGF_MASK_ALLOCATED)

#define cunilogSetFileToRotateAllocated(put)			\
	((put)->uiOpts |= CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)
#define cunilogIsFileToRotateAllocated(put)				\
	((put)->uiOpts & CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)

#define cunilogSetProcessorsAllocated(put)				\
	((put)->uiOpts |= CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogClrProcessorsAllocated(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogIsProcessorsAllocated(put)				\
	((put)->uiOpts & CUNILOGTARGET_PROCESSORS_ALLOCATED)

#define cunilogHasRunAllProcessorsOnStartup(put)		\
	((put)->uiOpts & CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogClrRunAllProcessorsOnStartup(put)		\
	((put)->uiOpts &= ~ CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogSetRunAllProcessorsOnStartup(put)		\
	((put)->uiOpts |= CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)

#define cunilogTargetHasFSneedsSorting(put)				\
	((put)->uiOpts & CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogTargetClrFSneedsSorting(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogTargetSetFSneedsSorting(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FS_NEEDS_SORTING)

#define cunilogTargetHasNumberSorting(put)				\
	((put)->uiOpts & CUNILOGTARGET_NEEDS_NUMBER_SORTING)
#define cunilogTargetClrNumberSorting(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_NEEDS_NUMBER_SORTING)
#define cunilogTargetSetNumberSorting(put)				\
	((put)->uiOpts |= CUNILOGTARGET_NEEDS_NUMBER_SORTING)

#define cunilogTargetHasFLSreversed(put)				\
	((put)->uiOpts & CUNILOGTARGET_FLS_REVERSED)
#define cunilogTargetClrFLSreversed(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FLS_REVERSED)
#define cunilogTargetSetFLSreversed(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FLS_REVERSED)

#define cunilogTargetIsPaused(put)						\
	((put)->uiOpts & CUNILOGTARGET_PAUSED)
#define cunilogTargetClrPaused(put)						\
	((put)->uiOpts &= ~ CUNILOGTARGET_PAUSED)
#define cunilogTargetSetPaused(put)						\
	((put)->uiOpts |= CUNILOGTARGET_PAUSED)

#define cunilogIsNoEcho(put)							\
	((put)->uiOpts & CUNILOGTARGET_NO_ECHO)
#define cunilogClrNoEcho(put)							\
	((put)->uiOpts &= ~ CUNILOGTARGET_NO_ECHO)
#define cunilogSetNoEcho(put)							\
	((put)->uiOpts |= CUNILOGTARGET_NO_ECHO)

#define cunilogHasDontWriteToLogfile(put)				\
	((put)->uiOpts & CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogClrNoWriteToLogfile(put)					\
	((put)->uiOpts &= ~ CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogSetNoWriteToLogfile(put)					\
	((put)->uiOpts |= CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#ifndef cunilogHasUseColourForEcho
		#define cunilogHasUseColourForEcho(put)			\
			((put)->uiOpts & CUNILOGTARGET_USE_COLOUR_FOR_ECHO)
	#endif
	#ifndef cunilogClrUseColourForEcho
		#define cunilogClrUseColourForEcho(put)			\
			((put)->uiOpts &= ~ CUNILOGTARGET_USE_COLOUR_FOR_ECHO)
	#endif
	#ifndef cunilogSetUseColourForEcho
		#define cunilogSetUseColourForEcho(put)			\
			((put)->uiOpts |= CUNILOGTARGET_USE_COLOUR_FOR_ECHO)
	#endif
#endif

#if defined (DEBUG) && !defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY)
	#define cunilogHasDebugQueueLocked(put)				\
		((put)->uiOpts & CUNILOGTARGET_DEBUG_QUEUE_LOCKED)
	#define cunilogClrDebugQueueLocked(put)				\
		((put)->uiOpts &= ~ CUNILOGTARGET_DEBUG_QUEUE_LOCKED)
	#define cunilogSetDebugQueueLocked(put)				\
		((put)->uiOpts |= CUNILOGTARGET_DEBUG_QUEUE_LOCKED)
#else
	#define cunilogHasDebugQueueLocked(put)	(true)
	#define cunilogClrDebugQueueLocked(put)
	#define cunilogSetDebugQueueLocked(put)
#endif

#define cunilogHasEnqueueTimestamps(put)				\
	((put)->uiOpts & CUNILOGTARGET_ENQUEUE_TIMESTAMPS)
#define cunilogClrEnqueueTimestamps(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_ENQUEUE_TIMESTAMPS)
#define cunilogSetEnqueueTimestamps(put)				\
	((put)->uiOpts |= CUNILOGTARGET_ENQUEUE_TIMESTAMPS)


/*
	Event severities.

	If changed, please update the copy in the comments of cunilog.c too.
*/
enum cunilogeventseverity
{
		cunilogEvtSeverityNone									//  0
	,	cunilogEvtSeverityNonePass								//  1
	,	cunilogEvtSeverityNoneFail								//  2
	,	cunilogEvtSeverityNoneWarn								//  3
	,	cunilogEvtSeverityBlanks								//  4
	,	cunilogEvtSeverityEmergency								//	5
	,	cunilogEvtSeverityNotice								//	6
	,	cunilogEvtSeverityInfo									//  7
	,	cunilogEvtSeverityMessage								//  8
	,	cunilogEvtSeverityWarning								//  9
	,	cunilogEvtSeverityError									// 10
	,	cunilogEvtSeverityPass									// 11
	,	cunilogEvtSeverityFail									// 12
	,	cunilogEvtSeverityCritical								// 13
	,	cunilogEvtSeverityFatal									// 14
	,	cunilogEvtSeverityDebug									// 15
	,	cunilogEvtSeverityTrace									// 16
	,	cunilogEvtSeverityDetail								// 17
	,	cunilogEvtSeverityVerbose								// 18
	,	cunilogEvtSeverityIllegal								// 19
	// Do not add anything below this line.
	,	cunilogEvtSeverityXAmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityXAmountEnumValues.
};
typedef enum cunilogeventseverity cueventseverity;

enum cunilogeventtype
{
		cunilogEvtTypeNormalText							// Normal UTF-8 text.
	,	cunilogEvtTypeCommand								// Event is config/command event.

		/*
			Caption + hex dump. The number specifies the bit width of the caption's length.
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
	CUNILOG_EVENT

	A logging event structure.

	Note that if the data is dump data, szDataToLog points to a length field of between 1
	and 8 octets, followed by a caption text without NUL, and this again followed by the
	actual dump data. The member lenDataToLog contains the length of the actual dump data
	*only*,. i.e. neither length field nor caption text count towards lenDataToLog.
*/
typedef struct CUNILOG_EVENT
{
	CUNILOG_TARGET				*pCUNILOG_TARGET;			// The event's target/destination.
	uint64_t					uiOpts;						// Option flags.
	UBF_TIMESTAMP				stamp;						// Its date/timestamp.
	unsigned char				*szDataToLog;				// Data to log.
	size_t						lenDataToLog;				// Its length, not NUL-terminated.

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		struct CUNILOG_EVENT	*next;
	#endif
	cueventseverity				evSeverity;
	cueventtype					evType;						// The event's type of data.
	size_t						sizEvent;					// The total allocated size of the
															//	event. If 0, the size is the size
															//	of the structure.
} CUNILOG_EVENT;

/*
	FillCUNILOG_EVENT

	Macro to fill a CUNILOG_EVENT structure. Note that the structure doesn't have a
	->next member if CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define FillCUNILOG_EVENT(pev, pt,					\
				opts, dts, sev, tpy, dat, len, siz)		\
		(pev)->pCUNILOG_TARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len;			\
		(pev)->evSeverity				= sev;			\
		(pev)->evType					= tpy;			\
		(pev)->sizEvent					= siz
#else
	#define FillCUNILOG_EVENT(pev, pt,					\
				opts, dts, sev, tpy, dat, len, siz)		\
		(pev)->pCUNILOG_TARGET			= pt;			\
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
	Member uiOpts of a CUNILOG_EVENT structure.
*/

#define CUNILOGEVENT_NO_FLAGS			(0)

// The structure has been allocated on the heap. This is for DoneSUNILOGEVENT ()
//	to deallocate it.
#define CUNILOGEVENT_ALLOCATED			SINGLEBIT64 (0)

// The data has been allocated. This is also for DoneSUNILOGEVENT ().
#define CUNILOGEVENT_DATA_ALLOCATED		SINGLEBIT64 (1)

// Shuts down logging.
#define CUNILOGEVENT_SHUTDOWN			SINGLEBIT64 (2)

// Suppresses echo/console output processor.
#define CUNILOGEVENT_NO_ECHO			SINGLEBIT64 (3)

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

// Only process the echo processor. All others are suppressed.
#define CUNILOGEVENT_ECHO_ONLY			SINGLEBIT64 (8)

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

#define cunilogSetEventNoEcho(pev)						\
	((pev)->uiOpts |= CUNILOGEVENT_NO_ECHO)
#define cunilogClrEventNoEcho(pev)						\
	((pev)->uiOpts &= ~ CUNILOGEVENT_NO_ECHO)
#define cunilogHasEventNoEcho(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_NO_ECHO)

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

#define cunilogSetEventEchoOnly(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_ECHO_ONLY)
#define cunilogClrEventEchoOnly(pev)					\
	((pev)->uiOpts &= ~ CUNILOGEVENT_ECHO_ONLY)
#define cunilogHasEventEchoOnly(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_ECHO_ONLY)

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
	A callback function of a custom/user defined processor.
*/
typedef bool (*pfCustProc) (CUNILOG_PROCESSOR *, CUNILOG_EVENT *);

/*
	Callback function for cleaning up a custom/user defined processor.
*/
typedef void (*pfDoneProc) (CUNILOG_PROCESSOR *);

/*
	A pData structure for a unilogProcessCustomProcessor (custom/user/external) processor.

	Members:

	pCust			Pointer to a data structure provided and used by the caller. Cunilog
					does not access this value. To access this member from a callback function,
					cast the pData member of the CUNILOG_PROCESSOR structure to a pointer
					to a CUNILOG_CUSTPROCESS structure.
	procFnct		Pointer to a custom/user function provided by the caller that handles
					the processor. This member cannot be NULL.
	procDone		Pointer to a function that is called when the processor is destroyed.
					This member can be NULL if this custom (or user/external) processor
					does not require cleanup code.

	Note that there's no callback function for initialisation. If dynamic initialisation is
	required, it is recommended to initialise pCust to NULL and initialise the custom data
	structure within the first call to procFnct.
*/
typedef struct cunilog_customprocess
{
	void			*pCust;
	pfCustProc		procFnct;
	pfDoneProc		procDone;
} CUNILOG_CUSTPROCESS;

/*
	Parameter structure for a rotator processor.
*/
typedef struct cunilog_rotator_args
{
	CUNILOG_PROCESSOR		*cup;
	CUNILOG_EVENT			*pev;
	char					*nam;							// Name of file to rotate.
	size_t					siz;							// Its size, incl. NUL.
	size_t					idx;							// Vector index of curr file.
} CUNILOG_ROTATOR_ARGS;

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
