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

	Copyright (c) 2024-2026 Thomas

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

/*
	For testing only.
*/
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
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, CUNILOG_BUILD_SINGLE_THREADED_QUEUE
	can be defined additionally to provide a target queue. This enables some queue functions.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_QUEUE
//#define CUNILOG_BUILD_SINGLE_THREADED_QUEUE
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
	#define CUNILOG_DEFAULT_OPEN_MODE	(O_WRONLY | O_APPEND | O_CREAT | O_LARGEFILE)
#endif

BEGIN_C_DECLS

/*
	The constants for the log file extensions.
*/
CUNILOG_DLL_IMPORT extern const char	szCunilogLogFileNameExtension	[];
CUNILOG_DLL_IMPORT extern const size_t	lenCunilogLogFileNameExtension;
#define sizCunilogLogFileNameExtension	(lenCunilogLogFileNameExtension + 1)
CUNILOG_DLL_IMPORT extern const char	szCunilogGzpFileNameExtension	[];
CUNILOG_DLL_IMPORT extern const size_t	lenCunilogGzpFileNameExtension;
#define sizCunilogGzpFileNameExtension	(lenCunilogGzpFileNameExtension + 1)

/*
	enum cunilogtype

	Specifies the application type of a cunilog target and how processing events is
	protected. These values are valid for a single target.
	Applications however can in theory work with an arbitrary number of targets.


	cunilogSingleThreaded

	Only a single thread from one instance of the current application can safely write out
	logging information. Cunilog does not apply any concurrency protection.
	Writing logging information from more than a single thread is not supported and results
	in data corruption and/or application crashes. In a best case it may only lead to unusable
	logging information.

	Every logging function blocks as it executes the list of processors before returning.

	This is the most rudimentary type. If this is the only target type required,
	CUNILOG_BUILD_SINGLE_THREADED_ONLY can be defined to disable all other types.


	cunilogSingleThreadedSeparateLoggingThread

	Identical to cunilogSingleThreaded but the application must be built with multi-threading
	support. The process of writing out logging information (i.e. executing the list of
	logging processors) takes place in a separate thread.
	Calling logging functions from more than a single thread is not supported and results in
	data corruption and application crashes. In a best case it may only lead to unusable
	logging information.
	
	However, due to how this is currently implemented, some of these restrictions do not apply
	right now because cunilogSingleThreadedSeparateLoggingThread is actually identical to
	cunilogMultiThreadedSeparateLoggingThread. Since this might and most likely will change in
	future versions of the software, use cunilogMultiThreadedSeparateLoggingThread to be safe.


	cunilogSingleThreadedQueueOnly

	This type is also single-threaded and identical to cunilogSingleThreaded with the
	exception that it doesn't write out anything. No logging processors are created nor
	executed. Events are accumulated in a singly-linked event list instead.

	This is meant as a replacement target when the real target is not available (yet). For
	instance, an application might choose to read some parameters of the logging target from
	a configuration file or obtain these parameters through other means, maybe from
	command-line arguments. This means the actual logging target can only be created once
	these parameters are available. You can use a cunilogSingleThreadedQueueOnly or a
	cunilogMultiThreadedQueueOnly target as a dummy target to log to until the real target
	can be created with the correct parameters. After the real target has been created,
	the entire queue can then be moved over to it, and no event is lost. Use the function
	MoveCUNILOG_TARGETqueueToFrom () to move the queue to the final target.


	cunilogMultiThreaded

	Multiple threads can safely write out logging information. Cunilog provides necessary
	concurrency protection. Any logging function called from any thread blocks as it works
	its way through the list of processors before releasing its lock and returning.


	cunilogMultiThreadedSeparateLoggingThread

	Identical to cunilogMultiThreaded but the process of writing out logging information (i.e.
	executing the list of processors) takes place in its own thread. Logging functions do
	not block. This is the preferred mode for most multi-threaded applications.


	cunilogMultiThreadedQueueOnly

	This is a mix of cunilogSingleThreadedQueueOnly, cunilogMultiThreaded, and
	cunilogMultiThreadedSeparateLoggingThread. This type doesn't write out anything. No logging
	processors are executed or even created. Events are instead accumulated in a singly-linked
	event list. The difference to cunilogSingleThreadedQueueOnly is that a target of type
	cunilogMultiThreadedQueueOnly can be logged to from several threads because the list is
	protected by a mutex (POSIX) or critical section object (Windows).

*/
enum cunilogtype
{
		cunilogSingleThreaded
	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	,	cunilogSingleThreadedSeparateLoggingThread
	,	cunilogSingleThreadedQueueOnly
	,	cunilogMultiThreaded
	,	cunilogMultiThreadedSeparateLoggingThread
	,	cunilogMultiThreadedQueueOnly
	//,	cunilogMultiProcesses
	#endif
	// Do not add anything below this line.
	,	cunilogTypeAmountEnumValues							// Used for table sizes.
	// Do not add anything below cunilogTypeAmountEnumValues.
};

/*
	The postfix applied to the application name.

	Example for cunilogPostfixMinute:
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

	// Current/active logfile has no postfix, but less recent ones have.
	//	"file.log", "file_YYYY-MM-DD HH_MI.log", etc.
	,	cunilogPostfixLogMinute
	,	cunilogPostfixLogMinuteT
	,	cunilogPostfixLogHour
	,	cunilogPostfixLogHourT
	,	cunilogPostfixLogDay
	,	cunilogPostfixLogWeek
	,	cunilogPostfixLogMonth
	,	cunilogPostfixLogYear

	//	"file.log", "file.log.1", "file.log.2", etc.
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


	cunilogProcessOutputToConsole

	Outputs the event line to the console.


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
	,	cunilogProcessOutputToConsole						// Outputs to console.
	,	cunilogProcessUpdateLogFileName						// Updates full path to logfile.
	,	cunilogProcessWriteToLogFile						// Writes to logfile.
	,	cunilogProcessFlushLogFile							// Flushes the logfile.
	,	cunilogProcessRotateLogfiles						// Rotates logfiles.
	,	cunilogProcessCustomProcessor						// An external/custom processor.
	,	cunilogProcessTargetRedirector						// Redirect to different target.
	,	cunilogProcessTargetFork							// Fork the event to another target.
	// Do not add anything below this line.
	,	cunilogProcessXAmountEnumValues						// Used for table sizes.
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
*/
typedef struct cunilog_logfile
{
	#ifdef OS_IS_WINDOWS
		HANDLE		hLogFile;
	#else
		int			fd;
	#endif
	uint32_t		chunkSize;
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
	,	cunilogrotationtask_CompressLogfiles				// Compress logfiles.
	,	cunilogrotationtask_MoveToTrashLogfiles
	,	cunilogrotationtask_MoveToRecycleBinLogfiles = cunilogrotationtask_MoveToTrashLogfiles
	,	cunilogrotationtask_DeleteLogfiles

	// Do not add anything below this line.
	,	cunilogrotationtask_XAmountEnumValues				// Used for table sizes.
	// Do not add anything below cunilogrotationtask_XAmountEnumValues.
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

	// Pointer to a logging target used for rotational (internal) events.
	CUNILOG_TARGET				*plogCUNILOG_TARGET;		//	If this is NULL, the processor's
															//	own target is logged to, without
															//	rotation. Should not point to the
															//	processor's own target.

	/*
		For rotator cunilogrotationtask_CompressLogfiles, physical sector size.
		Currently unused for other rotators.
	*/
	uint64_t					uiData;

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
	Bit 32 - 39 for rotator cunilogrotationtask_CompressLogfiles determine the compression
	method. They're still available for other rotators.

	Bit 32 - 39	(8 bits)		Compresson method.

	Value (binary)	Value (dec)	Value (hex)
	----------------------------------------------------------------------------------------
	00000000		0			0h			Default compression method. On Windows and
											NTFS, this is NTFS compression. The filename
											extension does not change.

											If the file system is not NTFS, Gzip compression
											is used. Compressed (deflated) files have a .gz
											filename extension.

											On all other platforms, Gzip compression is used.
											Compressed (deflated) files will have a filename
											extension of .gz.

	00000001		1			1h			NTFS compression method on Windows. No attempt
											is made to pick an alternative compression
											method.

	00000010		2			2h			Gzip compression (.gz files), independent of
											platform (operating system) and file system.

	00000011		3			3h			Reserved compression method. Not supported yet.

*/
enum enClgCmprsMtd
{
	cunilogComprMethodDefault		= 0,
	cunilogComprMethodNTFS			= 1,
	cunilogComprMethodGzip			= 2
};
// Mask to clear the compression flags.
#define CUNILOG_ROTATOR_COMPRESS_CLEAR			((uint64_t)(0xFFFFFF00FFFFFFFF))
// Obtain the compression method.
#define CUNILOG_ROTATOR_COMPRESS_OBTAIN			((uint64_t)(0x000000FF00000000))
// The amounts of bits to shift.
#define CUNILOG_ROTATOR_COMPRESS_SHIFT			(32)
#define CUNILOG_ROTATOR_COMPRESS_DEFAULT		(0)
#define CUNILOG_ROTATOR_COMPRESS_NTFSCOMP		SINGLEBIT64 (32)
#define CUNILOG_ROTATOR_COMPRESS_GZIPCOMP		SINGLEBIT64 (33)
// Macro to check if compression method is mthd.
#define cunilogHasRotator_CompressionMethod(prd, mthd)	\
	(													\
			(mthd)										\
		==	((uint64_t) ((prd)->uiFlgs & CUNILOG_ROTATOR_COMPRESS_OBTAIN)) >> CUNILOG_ROTATOR_COMPRESS_SHIFT	\
	)
// Macro to check if compression method is cunilogComprMethodGzip.
#define cunilogHasRotator_COMPRESS_GZIPCOMP(prd)		\
	cunilogHasRotator_CompressionMethod (prd, cunilogComprMethodGzip)
// Macro to set compression method to mthd.
#define cunilogSetRotator_CompressionMethod(prd, mthd)	\
		(prd)->uiFlgs &= CUNILOG_ROTATOR_COMPRESS_CLEAR;							\
		(prd)->uiFlgs |= (uint64_t) (mthd) << CUNILOG_ROTATOR_COMPRESS_SHIFT		\
// Macro to set compression method to cunilogComprMethodNTFS.
#define cunilogSetRotator_COMPRESS_NTFSCOMP(prd)		\
	cunilogSetRotator_CompressionMethod (prd, cunilogComprMethodNTFS)
// Macro to set compression method to cunilogComprMethodGzip.
#define cunilogSetRotator_COMPRESS_GZIPCOMP(prd)		\
	cunilogSetRotator_CompressionMethod (prd, cunilogComprMethodGzip)

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
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES \
{														\
	cunilogrotationtask_RenameLogfiles,					\
	0, 0, CUNILOG_MAX_ROTATE_AUTO,						\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL, 0,											\
	CUNILOG_ROTATOR_FLAG_NONE							\
}

/*
	Argument k is the amount of logfiles to keep/not touch.
*/
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_COMPRESS(k)\
{														\
	cunilogrotationtask_CompressLogfiles,				\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL, 0,											\
	CUNILOG_ROTATOR_COMPRESS_DEFAULT					\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_TRASH(k)\
{														\
	cunilogrotationtask_MoveToTrashLogfiles,			\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL, 0,											\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN(k)\
{														\
	cunilogrotationtask_MoveToRecycleBinLogfiles,		\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL, 0,											\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_DELETE(k)\
{														\
	cunilogrotationtask_DeleteLogfiles,					\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL, 0,											\
	CUNILOG_ROTATOR_FLAG_NONE							\
}

/*
	Initialisers for processor tasks.
*/
#define CUNILOG_INIT_DEF_COUT_PROCESSOR					\
{														\
	cunilogProcessOutputToConsole,						\
	cunilogProcessAppliesTo_nAlways,					\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
#define CUNILOG_INIT_DEF_UPDATELOGFILENAME_PROCESSOR	\
{														\
	cunilogProcessUpdateLogFileName,					\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
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
	(p),												\
	OPT_CUNPROC_NONE									\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_FScompressLogfiles. Such a structure can
	be initialised with the CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_COMPRESS()
	macro.
*/
#define CUNILOG_INIT_DEF_LOGFILESFSCOMPRESS_PROCESSOR(p)\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),												\
	OPT_CUNPROC_NONE									\
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
	OPT_CUNPROC_NONE									\
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
		#ifdef CUNILOG_BUILD_DEBUG_TEST_LOCKER
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
	const char	*chFilename;
	size_t		stFilename;
} CUNILOG_FLS;
typedef vec_t(CUNILOG_FLS) vec_cunilog_fls;

/*!
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
	/*!
		Possible return values of the error/fail callback function.

		cunilogErrCB_ignore					Just carry on as if nothing happened.			

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
			cunilogErrCB_ignore
		,	cunilogErrCB_next_processor
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

/*!
	The type/format/prefix of an event severity.
*/
enum cunilogeventseverityformat
{
		cunilogEvtSeverityFormatChars3							// "EMG", "DBG"... (default).
	,	cunilogEvtSeverityFormatChars5							// "EMRGY", "DEBUG"...
	,	cunilogEvtSeverityFormatChars9							// "EMERGENCY", "DEBUG    "...
	,	cunilogEvtSeverityFormatChars3InBrackets				// "[EMG]", "[DBG]"...
	,	cunilogEvtSeverityFormatChars5InBrackets				// "[EMRGY]", "[DEBUG]"...
	,	cunilogEvtSeverityFormatChars9InBrackets				// "[EMERGENCY]", "[DEBUG    ]"...
	,	cunilogEvtSeverityFormatChars5InTightBrackets			// "[FAIL] "...
	,	cunilogEvtSeverityFormatChars9InTightBrackets			// "[DEBUG]    "...
	// Do not add anything below this line.
	,	cunilogEvtSeverityFormatXAmountEnumValues				// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityTypeXAmountEnumValues.
};
typedef enum cunilogeventseverityformat cueventseverityformat;

/*!
	The default event severity type.
*/
extern cueventseverityformat cunilogEvtSeverityFormatDefault;

/*!
	Default ANSI escape colour output for the cunilog_puts... and cunilog_printf...
	type functions.
*/
extern bool bUseCunilogDefaultOutputColour;

/*!
	The severity mask. Each bit denotes one of the cunilogEvtSeverity... values.
	Bit 0 is cunilogEvtSeverityNone, etc.
	Every event's severity level is checked against this mask. If a bit is 1, the
	event is processed. If a bit is 0, the event creation is refused and logging
	functions with this severity fail (return false).
*/
typedef uint32_t			evtsevmask_t;
#define MAX_EVTSEVMASK		UINT32_MAX;						// To set all bits to 1.

/*!
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
	SMEMBUF							mbLogFileMask;			// The search mask for log files. It
															//	does not include the path.
	size_t							lnLogFileMask;			// Its length.
	SMEMBUF							*pmbCurLogFileMask;		// Pointer to the current search mask.
	SMEMBUF							lnCurLogFileMask;		// Its length.
	SMEMBUF							mbFilToRotate;			// The file obtained by the cb function.
	size_t							lnFilToRotate;			// Its length excluding the NUL terminator.
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

	#if defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY) && defined (CUNILOG_BUILD_SINGLE_THREADED_QUEUE)
		// Single-threaded with queue.
		CUNILOG_QUEUE_BASE			qu;						// The actual event queue.
	#elif defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY)
		// Single-threaded (no queue).
	#else
		// Multi-threade (locker, queue, separate thread).
		CUNILOG_LOCKER				cl;						// Locker for events queue.
		CUNILOG_SEMAPHORE			sm;						// Semaphore for event queue.
		CUNILOG_QUEUE_BASE			qu;						// The actual event queue.
		CUNILOG_THREAD				th;						// The separate logging thread.

		size_t						nPendingNoRotEvts;		// Amount of currently pending
															//	internal non-rotation events.

		size_t						nPausedEvents;			// Amount of events queued because
															//	the logging thread is/was paused.
	#endif

	enum cunilogeventTSformat		unilogEvtTSformat;		// The format of an event timestamp.
	newline_t						culogNewLine;
	CUNILOG_LOGFILE					logfile;
	SBULKMEM						sbm;					// Bulk memory block.
	vec_cunilog_fls					fls;					// The vector with str pointers to
															//	the files to rotate within sbm.
	// We're not using the configurable dump anymore.
	//SCUNILOGDUMP					*psdump;				// Holds the dump parameters.
	ddumpWidth						dumpWidth;

	cueventseverityformat				severityPrefix;			// Format of the event severity.
	volatile evtsevmask_t			severityEvtMask;

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
#define CUNILOGTARGET_SHUTDOWN_INITIATED		SINGLEBIT64 (0)

// Separate logging thread has shut down.
#define CUNILOGTARGET_SHUTDOWN_COMPLETE			SINGLEBIT64 (1)

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

// The array of pointers to processors is allocated on the heap.
#define CUNILOGTARGET_PROCESSORS_ALLOCATED		SINGLEBIT64 (8)

// Run all processors on startup, independent of their individual flags.
//	This flag overwrites the CUNILOGEVENT_NOROTATION flag of the first
//	event after startup. Otherwise the rotation processors would not run.
#define CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP	SINGLEBIT64 (9)

// The filesystem that holds the log files doesn't return filenames in
//	descending alphabetic order.
#define CUNILOGTARGET_FS_NEEDS_SORTING			SINGLEBIT64 (10)

#define CUNILOGTARGET_FLS_IS_SORTED				SINGLEBIT64 (11)

// The "file.log.1" (dot number postfix) requires this.
//#define CUNILOGTARGET_NEEDS_NUMBER_SORTING		SINGLEBIT64 (12)

// The elements of the member fls (a vecotr) are in reversed order.
#define CUNILOGTARGET_FLS_REVERSED				SINGLEBIT64 (13)

// The separate logging thread, if one exists, is paused.
#define CUNILOGTARGET_PAUSED					SINGLEBIT64 (14)

// Debug versions ensure that one of the initialisation function has been called.
#ifdef DEBUG
	#define CUNILOGTARGET_INITIALISED			SINGLEBIT64 (15)
	#define cunilogSetTargetInitialised(put)				\
			((put)->uiOpts |= CUNILOGTARGET_INITIALISED)
	#define cunilogIsTargetInitialised(put)				\
			((put)->uiOpts & CUNILOGTARGET_INITIALISED)
#else
	#define cunilogSetTargetInitialised(put)	(true)
	#define cunilogIsTargetInitialised(put)		(true)
#endif

// The callback function errorCB is called as often as possible,
//	even when there's no error. Used for tests.
//	Requires CUNILOG_BUILD_WITH_TEST_ERRORCB.
//	Ignored when CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
//	is defined.
//	Error code is usually one of the CUNILOG_ERROR_TEST_ definitions
//	in cunilogerrors.h.
#define CUNILOGTARGET_ALWAYS_CALL_ERRORCB		SINGLEBIT64 (16)

// Debug flag when the queue is locked. To be removed in the future.
#define CUNILOGTARGET_DEBUG_QUEUE_LOCKED		SINGLEBIT64 (20)

#define cunilogTargetSetShutdownInitiatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_SHUTDOWN_INITIATED)
#define cunilogTargetHasShutdownInitiatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_SHUTDOWN_INITIATED)

#define cunilogTargetSetShutdownCompleteFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_SHUTDOWN_COMPLETE)
#define cunilogTargetHasShutdownCompleteFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_SHUTDOWN_COMPLETE)

#define cunilogTargetSetTargetAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_ALLOCATED)
#define cunilogTargetHasTargetAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_ALLOCATED)

#define cunilogTargetSetLogPathAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED)
#define cunilogTargetHasLogPathAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_LOGPATH_ALLOCATED)

#define cunilogTargetSetAppNameAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_APPNAME_ALLOCATED)
#define cunilogTargetHasAppNameAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_APPNAME_ALLOCATED)

#define cunilogTargetSetLogFileAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_LOGFILE_ALLOCATED)
#define cunilogTargetHasLogFileAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_LOGFILE_ALLOCATED)

#define cunilogTargetSetLogFileMaskAllocatedFlag(put)	\
	((put)->uiOpts |= CUNILOGTARGET_LOGF_MASK_ALLOCATED)
#define cunilogTargetHasLogFileMaskAllocatedFlag(put)	\
	((put)->uiOpts & CUNILOGTARGET_LOGF_MASK_ALLOCATED)

#define cunilogTargetSetFileToRotateAllocatedFlag(put)	\
	((put)->uiOpts |= CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)
#define cunilogTargetHasFileToRotateAllocatedFlag(put)	\
	((put)->uiOpts & CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)

#define cunilogTargetSetProcessorsAllocatedFlag(put)	\
	((put)->uiOpts |= CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogTargetClrProcessorsAllocatedFlag(put)	\
	((put)->uiOpts &= ~ CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogTargetHasProcessorsAllocatedFlag(put)	\
	((put)->uiOpts & CUNILOGTARGET_PROCESSORS_ALLOCATED)

#define cunilogTargetHasRunProcessorsOnStartup(put)		\
	((put)->uiOpts & CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogTargetClrRunProcessorsOnStartup(put)		\
	((put)->uiOpts &= ~ CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogTargetSetRunProcessorsOnStartup(put)		\
	((put)->uiOpts |= CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)

#define cunilogTargetHasFSneedsSorting(put)				\
	((put)->uiOpts & CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogTargetClrFSneedsSorting(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogTargetSetFSneedsSorting(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FS_NEEDS_SORTING)

#define cunilogTargetHasFLSisSorted(put)				\
	((put)->uiOpts & CUNILOGTARGET_FLS_IS_SORTED)
#define cunilogTargetClrFLSisSorted(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FLS_IS_SORTED)
#define cunilogTargetSetFLSisSorted(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FLS_IS_SORTED)

/*
#define cunilogTargetHasNumberSorting(put)				\
	((put)->uiOpts & CUNILOGTARGET_NEEDS_NUMBER_SORTING)
#define cunilogTargetClrNumberSorting(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_NEEDS_NUMBER_SORTING)
#define cunilogTargetSetNumberSorting(put)				\
	((put)->uiOpts |= CUNILOGTARGET_NEEDS_NUMBER_SORTING)
*/

#define cunilogTargetHasFLSreversed(put)				\
	((put)->uiOpts & CUNILOGTARGET_FLS_REVERSED)
#define cunilogTargetClrFLSreversed(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FLS_REVERSED)
#define cunilogTargetSetFLSreversed(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FLS_REVERSED)

#define cunilogTargetHasIsPaused(put)					\
	((put)->uiOpts & CUNILOGTARGET_PAUSED)
#define cunilogTargetClrIsPaused(put)					\
	((put)->uiOpts &= ~ CUNILOGTARGET_PAUSED)
#define cunilogTargetSetIsPaused(put)					\
	((put)->uiOpts |= CUNILOGTARGET_PAUSED)

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

#define cunilogTargetHasAlwaysCallErrorCB(put)			\
	((put)->uiOpts & CUNILOGTARGET_ALWAYS_CALL_ERRORCB)
#define cunilogTargetClrAlwaysCallErrorCB(put)			\
	((put)->uiOpts &= ~ CUNILOGTARGET_ALWAYS_CALL_ERRORCB)
#define cunilogTargetSetAlwaysCallErrorCB(put)			\
	((put)->uiOpts |= CUNILOGTARGET_ALWAYS_CALL_ERRORCB)


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

// The console output processor is skipped.
#define CUNILOGTARGET_NO_COUT					SINGLEBIT64 (34)

// The processor that writes to the logfile is skipped.
#define CUNILOGTARGET_DONT_WRITE_TO_LOGFILE		SINGLEBIT64 (35)

// Colour information should be used.
#define CUNILOGTARGET_USE_COLOUR_FOR_COUT		SINGLEBIT64 (36)

/*
	Macros for public/user/caller flags.
*/
#define cunilogHasTargetNoCout(put)						\
	((put)->uiOpts & CUNILOGTARGET_NO_COUT)
#define cunilogClrTargetNoCout(put)						\
	((put)->uiOpts &= ~ CUNILOGTARGET_NO_COUT)
#define cunilogSetTargetNoCout(put)						\
	((put)->uiOpts |= CUNILOGTARGET_NO_COUT)

#define cunilogHasDontWriteToLogfile(put)				\
	((put)->uiOpts & CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogClrNoWriteToLogfile(put)					\
	((put)->uiOpts &= ~ CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogSetNoWriteToLogfile(put)					\
	((put)->uiOpts |= CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#ifndef cunilogTargetHasUseColourForCout
		#define cunilogTargetHasUseColourForCout(put)	\
			((put)->uiOpts & CUNILOGTARGET_USE_COLOUR_FOR_COUT)
	#endif
	#ifndef cunilogTargetClrUseColourForCout
		#define cunilogTargetClrUseColourForCout(put)	\
			((put)->uiOpts &= ~ CUNILOGTARGET_USE_COLOUR_FOR_COUT)
	#endif
	#ifndef cunilogTargetSetUseColourForCout
		#define cunilogTargetSetUseColourForCout(put)	\
			((put)->uiOpts |= CUNILOGTARGET_USE_COLOUR_FOR_COUT)
	#endif
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
		cunilogEvtSeverityNone								//  0
	,	cunilogEvtSeverityNonePass							//  1
	,	cunilogEvtSeverityNoneFail							//  2
	,	cunilogEvtSeverityNoneWarn							//  3
	,	cunilogEvtSeverityBlanks							//  4
	,	cunilogEvtSeverityEmergency							//	5
	,	cunilogEvtSeverityNotice							//	6
	,	cunilogEvtSeverityInfo								//  7
	,	cunilogEvtSeverityOutput							//  8
	,	cunilogEvtSeverityMessage							//  9
	,	cunilogEvtSeverityWarning							// 10
	,	cunilogEvtSeverityError								// 11
	,	cunilogEvtSeverityPass								// 12
	,	cunilogEvtSeverityFail								// 13
	,	cunilogEvtSeverityCritical							// 14
	,	cunilogEvtSeverityFatal								// 15
	,	cunilogEvtSeverityDebug								// 16
	,	cunilogEvtSeverityTrace								// 17
	,	cunilogEvtSeverityDetail							// 18
	,	cunilogEvtSeverityVerbose							// 19
	,	cunilogEvtSeverityIllegal							// 20
	,	cunilogEvtSeveritySyntax							// 21
	// Do not add anything below this line.
	,	cunilogEvtSeverityXAmountEnumValues					// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityXAmountEnumValues.
};
typedef enum cunilogeventseverity cueventseverity;

enum cunilogeventtype
{
		cunilogEvtTypeNormalText							// Normal UTF-8 text.
	,	cunilogEvtTypeControlCode							// Code only, no timestamp etc.
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
	cueventseverity				evSeverity;					// The event's severity level.
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
#define CUNILOGEVENT_ALLOCATED					SINGLEBIT64 (0)

// The data has been allocated. This is also for DoneSUNILOGEVENT ().
#define CUNILOGEVENT_DATA_ALLOCATED				SINGLEBIT64 (1)

// Shuts down logging.
#define CUNILOGEVENT_SHUTDOWN					SINGLEBIT64 (2)

// Suppresses console output processor.
#define CUNILOGEVENT_NO_COUT					SINGLEBIT64 (3)

// This is an internal event. Internal events are generated
//	within processors.
#define CUNILOGEVENT_IS_INTERNAL				SINGLEBIT64 (4)

// Add fullstop automatically.
#define CUNILOGEVENT_AUTO_FULLSTOP				SINGLEBIT64 (5)

// No rotation for this event. This is very fast/quick logging.
//	It is also used for internal logging.
//	Note that this flag has no effect for the very first event
//	created when the target has CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP
//	set. The flag CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP forces
//	all processors, including rotation processors, to run
//	for the first event.
#define CUNILOGEVENT_NOROTATION					SINGLEBIT64 (6)

// Suppresses the remaining processors.
#define CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS\
												SINGLEBIT64	(7)

// Only process the console output processor. All others are suppressed.
#define CUNILOGEVENT_COUT_ONLY					SINGLEBIT64 (8)

// Macros to set and check flags.
#define cunilogSetEventAllocated(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventAllocated(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventDataAllocated(pev)				\
	((pev)->uiOpts & CUNILOGEVENT_DATA_ALLOCATED)

#define cunilogSetEventShutdown(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventShutdown(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventCancel(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_CANCEL)

#define cunilogSetEventNoCout(pev)						\
	((pev)->uiOpts |= CUNILOGEVENT_NO_COUT)
#define cunilogClrEventNoCout(pev)						\
	((pev)->uiOpts &= ~ CUNILOGEVENT_NO_COUT)
#define cunilogHasEventNoCout(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_NO_COUT)

#define cunilogSetEventInternal(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_IS_INTERNAL)
#define cunilogClrEventInternal(pev)					\
	((pev)->uiOpts &= ~ CUNILOGEVENT_IS_INTERNAL)
#define cunilogIsEventInternal(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_IS_INTERNAL)

#define cunilogSetEventAutoFullstop(pev)				\
	((pev)->uiOpts |= CUNILOGEVENT_AUTO_FULLSTOP)
#define cunilogIsEventAutoFullstop(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_AUTO_FULLSTOP)

#define cunilogHasEventNoRotation(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_NOROTATION)
#define cunilogSetEventNoRotation(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_NOROTATION)
#define cunilogClrEventNoRotation(pev)					\
	((pev)->uiOpts &= ~ CUNILOGEVENT_NOROTATION)

#define cunilogEventSetIgnoreRemainingProcessors(pev)	\
	((pev)->uiOpts |= CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS)
#define cunilogEventClrIgnoreRemainingProcessors(pev)	\
	((pev)->uiOpts &= ~ CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS)
#define cunilogEventHasIgnoreRemainingProcessors(pev)	\
	((pev)->uiOpts & CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS)

#define cunilogSetEventCoutOnly(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_COUT_ONLY)
#define cunilogClrEventCoutOnly(pev)					\
	((pev)->uiOpts &= ~ CUNILOGEVENT_COUT_ONLY)
#define cunilogHasEventCoutOnly(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_COUT_ONLY)

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
	const char				*nam;							// Name of file to rotate.
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
