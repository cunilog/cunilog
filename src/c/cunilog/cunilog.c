/****************************************************************************************

	File:		cunilog.c
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

#include <stdbool.h>
#include <stdarg.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./cunilog.h"
	#include "./cunilogerrors.h"
	#include "./cunilogevtcmds.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	
		#include "./ubf_date_and_time.h"
		#include "./ubfdebug.h"
		#include "./ArrayMacros.h"
		#include "./membuf.h"
		#include "./check_utf8.h"
		#include "./ubfcharscountsandchecks.h"
		#include "./stransi.h"
		#include "./strfilesys.h"
		#include "./strintuint.h"
		#include "./strhexdump.h"
		#include "./strmembuf.h"
		#include "./strisabsolutepath.h"
		#include "./strnewline.h"
		#include "./CompressFile.h"
		#include "./ExeFileName.h"
		#include "./UserHome.h"
		
		#if defined (PLATFORM_IS_WINDOWS)
			#include "./WinAPI_U8.h"
			#include "./WinAPI_ReadDirFncts.h"
		#elif defined (PLATFORM_IS_POSIX)
			#include "./PsxCompressFile.h"
			#include "./PsxReadDirFncts.h"
			#include "./PsxTrash.h"
			#include "./PsxHome.h"
		#endif
		
		#include "./unref.h"
		
	#else
	
		#include "./../datetime/ubf_date_and_time.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../pre/ArrayMacros.h"
		#include "./../mem/membuf.h"
		#include "./../string/check_utf8.h"
		#include "./../string/ubfcharscountsandchecks.h"
		#include "./../string/stransi.h"
		#include "./../string/strfilesys.h"
		#include "./../string/strintuint.h"
		#include "./../string/strhexdump.h"
		#include "./../string/strmembuf.h"
		#include "./../string/strisabsolutepath.h"
		#include "./../string/strnewline.h"
		#include "./../string/strwildcards.h"
		#include "./../OS/CompressFile.h"
		#include "./../OS/ExeFileName.h"
		#include "./../OS/UserHome.h"
		
		#if defined (PLATFORM_IS_WINDOWS)
			#include "./../OS/Windows/WinAPI_U8.h"
			#include "./../OS/Windows/WinAPI_ReadDirFncts.h"
		#elif defined (PLATFORM_IS_POSIX)
			#include "./../OS/POSIX/PsxCompressFile.h"
			#include "./../OS/POSIX/PsxReadDirFncts.h"
			#include "./../OS/POSIX/PsxTrash.h"
			#include "./../OS/POSIX/PsxHome.h"
		#endif
		
		#include "./../pre/unref.h"
		
	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	#include <errno.h>
	#include <unistd.h>
#endif

static CUNILOG_TARGET CUNILOG_TARGETstatic;
CUNILOG_TARGET *pCUNILOG_TARGETstatic	= &CUNILOG_TARGETstatic;

/*
	Copy from the structure header cunilogstructs.h to avoid switching between code and header
	during development. Can/could be deleted when finalised.

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

*/

/*
	Our default static pData structures for our standard processors.
*/
/*
CUNILOG_LOGFILE			defcuppLogFile						=
	CUNILOG_INIT_DEF_CUNILOG_LOGFILE ();
CUNILOG_ROTATION_DATA	defcuppRotatorRenameLogfiles		=
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES
		();
CUNILOG_ROTATION_DATA	defcuppRotatorFS_compress			=
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_FS_COMPRESS
		(CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED);
CUNILOG_ROTATION_DATA	defcuppRotatorMove_to_recycle_bin	=
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN
		(CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED);
CUNILOG_ROTATION_DATA	defcuppRotatorDelete				=
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_DELETE
		(CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED);
*/
/*
	Our default processors. Only used for our static CUNILOG_TARGET structure.
*/
/*
CUNILOG_PROCESSOR		defcuppEcho							=
	CUNILOG_INIT_DEF_ECHO_PROCESSOR;
CUNILOG_PROCESSOR		defcuppUpdateLogfileName			=
	CUNILOG_INIT_DEF_UPDATELOGFILENAME_PROCESSOR;
CUNILOG_PROCESSOR		defcuppWriteToLogfile				=
	CUNILOG_INIT_DEF_WRITETTOLOGFILE_PROCESSOR		(&defcuppLogFile);
CUNILOG_PROCESSOR		defcuppFlushLogFile					=
	CUNILOG_INIT_DEF_FLUSHLOGFILE_PROCESSOR;
CUNILOG_PROCESSOR		defcuppRotateLogfilesRename			=
	CUNILOG_INIT_DEF_RENAMELOGFILES_PROCESSOR		(&defcuppRotatorRenameLogfiles);
CUNILOG_PROCESSOR		defcuppRotateLogfilesFScompress		=
	CUNILOG_INIT_DEF_LOGFILESFSCOMPRESS_PROCESSOR	(&defcuppRotatorFS_compress);
CUNILOG_PROCESSOR		defcuppRotateLogfilesMoveToTrash	=
	CUNILOG_INIT_DEF_LOGFILESMOVETOTRASH_PROCESSOR	(&defcuppRotatorMove_to_recycle_bin);
*/
// The list with the processors.
/*
CUNILOG_PROCESSOR	*defcupp [] =
{
	&defcuppEcho,											// Writes to console.
	&defcuppUpdateLogfileName,								// Updates the date/timestamp within
															//	the log file's name.
	&defcuppWriteToLogfile,									// Writes out to log file.
	&defcuppFlushLogFile,									// Flushes the log file.
	&defcuppRotateLogfilesRename,							// Rename the log files.
	&defcuppRotateLogfilesFScompress,						// Rotates the log files.
	&defcuppRotateLogfilesMoveToTrash						// Rotates the log files.
};
*/

CUNILOG_PROCESSOR **CreateCopyCUNILOG_PROCESSORs (CUNILOG_PROCESSOR *cps [], unsigned int n)
{
	ubf_assert_non_NULL	(cps);
	ubf_assert_non_NULL	(cps [0]);
	ubf_assert_non_0	(n);

	// First we calculate the required space for the copy. An alignment of
	//	CUNILOG_POINTER_ALIGNMENT may prevent a cache miss or two.

	// Space for the array of pointers to processors, plus the actual processors.
	size_t stTot = ALIGNED_SIZE (n * sizeof (CUNILOG_PROCESSOR *), CUNILOG_POINTER_ALIGNMENT);
	stTot += n * ALIGNED_SIZE (sizeof (CUNILOG_PROCESSOR), CUNILOG_POINTER_ALIGNMENT);

	// Space for the pData members.
	unsigned int u;
	for (u = 0; u < n; ++ u)
	{
		switch (cps [u]->task)
		{
			case cunilogProcessWriteToLogFile:
				/* The CUNILOG_LOGFILE structure now belongs to the target.
				stTot += ALIGNED_SIZE (sizeof (CUNILOG_LOGFILE), CUNILOG_POINTER_ALIGNMENT);
				*/
				break;
			case cunilogProcessRotateLogfiles:
				stTot += ALIGNED_SIZE (sizeof (CUNILOG_ROTATION_DATA), CUNILOG_POINTER_ALIGNMENT);
				break;
			case cunilogProcessCustomProcessor:
				stTot += ALIGNED_SIZE (sizeof (CUNILOG_CUSTPROCESS), CUNILOG_POINTER_ALIGNMENT);
				break;
			default:
				break;
		}
	}

	CUNILOG_PROCESSOR **cpn = ubf_malloc (stTot);
	if (cpn)
	{
		unsigned char *p = (unsigned char *) cpn;
		// We leave space for the array of pointers.
		p += ALIGNED_SIZE (n * sizeof (CUNILOG_PROCESSOR *), CUNILOG_POINTER_ALIGNMENT);

		for (u = 0; u < n; ++ u)
		{
			memcpy (p, cps [u], sizeof (CUNILOG_PROCESSOR));
			cpn [u] = (CUNILOG_PROCESSOR *) p;
			p += ALIGNED_SIZE (sizeof (CUNILOG_PROCESSOR), CUNILOG_POINTER_ALIGNMENT);

			switch (cps [u]->task)
			{
				case cunilogProcessWriteToLogFile:
					/* The CUNILOG_LOGFILE structure now belongs to the target.
					memcpy (p, cps [u]->pData, sizeof (CUNILOG_LOGFILE));
					cpn [u]->pData = p;
					p += ALIGNED_SIZE (sizeof (CUNILOG_LOGFILE), CUNILOG_POINTER_ALIGNMENT);
					*/
					break;
				case cunilogProcessRotateLogfiles:
					memcpy (p, cps [u]->pData, sizeof (CUNILOG_ROTATION_DATA));
					cpn [u]->pData = p;
					p += ALIGNED_SIZE (sizeof (CUNILOG_ROTATION_DATA), CUNILOG_POINTER_ALIGNMENT);
					break;
				case cunilogProcessCustomProcessor:
					memcpy (p, cps [u]->pData, sizeof (CUNILOG_CUSTPROCESS));
					cpn [u]->pData = p;
					p += ALIGNED_SIZE (sizeof (CUNILOG_CUSTPROCESS), CUNILOG_POINTER_ALIGNMENT);
					break;
				default:
					break;
			}
		}
	}
	return cpn;
}

void *DoneCopyCUNILOG_PROCESSORs (CUNILOG_PROCESSOR *cps [])
{
	ubf_assert_non_NULL (cps);

	ubf_free (cps);
	return NULL;
}

CUNILOG_PROCESSOR **CreateNewDefaultProcessors (unsigned int *pn)
{
	// The return value is useless without knowing the amount of processors.
	ubf_assert_non_NULL (pn);

	/*
		We simply place default processors on the stack andcreate a copy of them on the heap.
	*/
	// Our pData structures.
	CUNILOG_ROTATION_DATA	stkcuppRotatorRenameLogfiles		=
		CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES
			();
	CUNILOG_ROTATION_DATA	stkcuppRotatorFS_compress			=
		CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_FS_COMPRESS
			(CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED);
	CUNILOG_ROTATION_DATA	stkcuppRotatorMove_to_recycle_bin	=
		CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN
			(CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED);
	/*
	CUNILOG_ROTATION_DATA	stkcuppRotatorDelete				=
		CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_DELETE
			(CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED);
	*/
	// The processors.
	CUNILOG_PROCESSOR		stkcuppEcho							=
		CUNILOG_INIT_DEF_ECHO_PROCESSOR;
	CUNILOG_PROCESSOR		stkcuppUpdateLogfileName			=
		CUNILOG_INIT_DEF_UPDATELOGFILENAME_PROCESSOR;
	CUNILOG_PROCESSOR		stkcuppWriteToLogfile				=
		CUNILOG_INIT_DEF_WRITETTOLOGFILE_PROCESSOR;
	CUNILOG_PROCESSOR		stkcuppFlushLogFile					=
		CUNILOG_INIT_DEF_FLUSHLOGFILE_PROCESSOR;
	CUNILOG_PROCESSOR		stkcuppRotateLogfilesRename			=
		CUNILOG_INIT_DEF_RENAMELOGFILES_PROCESSOR		(&stkcuppRotatorRenameLogfiles);
	CUNILOG_PROCESSOR		stkcuppRotateLogfilesFScompress		=
		CUNILOG_INIT_DEF_LOGFILESFSCOMPRESS_PROCESSOR	(&stkcuppRotatorFS_compress);
	CUNILOG_PROCESSOR		stkcuppRotateLogfilesMoveToTrash	=
		CUNILOG_INIT_DEF_LOGFILESMOVETOTRASH_PROCESSOR	(&stkcuppRotatorMove_to_recycle_bin);

	// The list with the processors.
	CUNILOG_PROCESSOR	*stkcupp [] =
	{
		&stkcuppEcho,											// Writes to console.
		&stkcuppUpdateLogfileName,								// Updates the date/timestamp within
																//	the log file's name.
		&stkcuppWriteToLogfile,									// Writes out to log file.
		&stkcuppFlushLogFile,									// Flushes the log file.
		&stkcuppRotateLogfilesRename,							// Rename the log files.
		&stkcuppRotateLogfilesFScompress,						// Rotates the log files.
		&stkcuppRotateLogfilesMoveToTrash						// Rotates the log files.
	};

	unsigned int n = ARRAYSIZE (stkcupp);
	CUNILOG_PROCESSOR **cps = CreateCopyCUNILOG_PROCESSORs (stkcupp, n);
	if (cps)
		*pn = n;
	return cps;
}

size_t arrLengthTimeStampFromPostfix [] =					// [unilogPostfixAmountEnumValues]
{
	/* cunilogPostfixNone					*/		0
	/* cunilogPostfixMinute					*/	,	LEN_ISO8601DATEHOURANDMINUTE
	/* cunilogPostfixMinuteT				*/	,	LEN_ISO8601DATEHOURANDMINUTE
	/* cunilogPostfixHour					*/	,	LEN_ISO8601DATEANDHOUR
	/* cunilogPostfixHourT					*/	,	LEN_ISO8601DATEANDHOUR
	/* cunilogPostfixDay					*/	,	LEN_ISO8601DATE
	/* cunilogPostfixWeek					*/	,	LEN_ISO8601YEARANDWEEK
	/* cunilogPostfixMonth					*/	,	LEN_ISO8601YEARANDMONTH
	/* cunilogPostfixYear					*/	,	LEN_ISO8601YEAR
													// Space for "." + UNIT64.
	/* cunilogPostfixDotNumberMinutely		*/	,	1 + UBF_UINT64_LEN
	/* cunilogPostfixDotNumberHourly		*/	,	1 + UBF_UINT64_LEN
	/* cunilogPostfixDotNumberDaily			*/	,	1 + UBF_UINT64_LEN
	/* cunilogPostfixDotNumberWeekly		*/	,	1 + UBF_UINT64_LEN
	/* cunilogPostfixDotNumberMonthly		*/	,	1 + UBF_UINT64_LEN
	/* cunilogPostfixDotNumberYearly		*/	,	1 + UBF_UINT64_LEN
};

#ifdef DEBUG
	size_t lenDateTimeStampFromPostfix (enum cunilogpostfix postfix)
	{
		ubf_assert (0 <= postfix);
		ubf_assert (postfix < cunilogPostfixAmountEnumValues);

		return arrLengthTimeStampFromPostfix [postfix];
	}
#endif

/*
	Note the wildcard mask for "YYYY-MM-DD HH_MI" (cunilogPostfixMinute) and
	"YYYY-MM-DDTHH_MI" (cunilogPostfixMinuteT). Hours and minutes are separated by an
	underscore instead of a colon.
*/
const char *arrPostfixWildcardMask []	=		// [cunilogPostfixAmountEnumValues]
{
	"",											// cunilogPostfixNone
	"\?\?\?\?-\?\?-\?\? \?\?_\?\?",				// cunilogPostfixMinute					"YYYY-MM-DD HH_MI".
	"\?\?\?\?-\?\?-\?\?T\?\?_\?\?",				// cunilogPostfixMinuteT				"YYYY-MM-DDTHH_MI".
	"\?\?\?\?-\?\?-\?\? \?\?",					// cunilogPostfixHour					"YYYY-MM-DD HH".
	"\?\?\?\?-\?\?-\?\?T\?\?",					// cunilogPostfixHourT					"YYYY-MM-DDTHH".
	"\?\?\?\?-\?\?-\?\?",						// cunilogPostfixDay					"YYYY-MM-DD".
	"\?\?\?\?-W\?\?",							// cunilogPostfixWeek					"YYYY-Wnn".
	"\?\?\?\?-\?\?",							// cunilogPostfixMonth					"YYYY-MM".
	"\?\?\?\?"									// cunilogPostfixYear					"YYYY".
	"",											// cunilogPostfixDotNumberMinutely
	"",											// cunilogPostfixDotNumberHourly
	"",											// cunilogPostfixDotNumberDaily
	"",											// cunilogPostfixDotNumberWeekly
	"",											// cunilogPostfixDotNumberMonthly
	""											// cunilogPostfixDotNumberYearly
};

#ifdef DEBUG
	const char *postfixMaskFromLogPostfix (enum cunilogpostfix postfix)
	{
		ubf_assert (postfix >= 0);
		ubf_assert (postfix < cunilogPostfixAmountEnumValues);

		return arrPostfixWildcardMask [postfix];
	}
#endif

static void noPostfix (char *sz, UBF_TIMESTAMP ts)
{
	UNUSED_PARAMETER (sz);
	UNUSED_PARAMETER (ts);
}

/*
	This should be:
	
	void (*obtainTimeStampAsString [unilogPostfixAmountEnumValues]) (char *, UBF_TIMESTAMP) =
	
	But then we wouldn't be able to check for a mismatch at runtime.
*/
void (*obtainTimeStampAsString []) (char *, UBF_TIMESTAMP) =
{
	/* cunilogPostfixNone					*/		noPostfix
	/* cunilogPostfixMinute					*/	,	ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_
	/* cunilogPostfixMinuteT				*/	,	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_
	/* cunilogPostfixHour					*/	,	ISO8601DateAndHour_from_UBF_TIMESTAMPc
	/* cunilogPostfixHourT					*/	,	ISO8601TDateAndHour_from_UBF_TIMESTAMPc
	/* cunilogPostfixDay					*/	,	ISO8601Date_from_UBF_TIMESTAMPc
	/* cunilogPostfixWeek					*/	,	ISO8601YearAndWeek_from_UBF_TIMESTAMPc
	/* cunilogPostfixMonth					*/	,	ISO8601YearAndMonth_from_UBF_TIMESTAMPc
	/* cunilogPostfixYear					*/	,	ISO8601Year_from_UBF_TIMESTAMPc
	/* cunilogPostfixDotNumberMinutely		*/	,	noPostfix
	/* cunilogPostfixDotNumberHourly		*/	,	noPostfix
	/* cunilogPostfixDotNumberDaily			*/	,	noPostfix
	/* cunilogPostfixDotNumberWeekly		*/	,	noPostfix
	/* cunilogPostfixDotNumberMonthly		*/	,	noPostfix
	/* cunilogPostfixDotNumberYearly		*/	,	noPostfix
};

#ifdef DEBUG
	void obtainDateAndTimeStamp (char *szWhere, UBF_TIMESTAMP ts, enum cunilogpostfix postfix)
	{
		ubf_assert_non_NULL (szWhere);
		ubf_assert (postfix >= 0);
		ubf_assert (postfix < cunilogPostfixAmountEnumValues);

		obtainTimeStampAsString [postfix] (szWhere, ts);
	}
#else
	#define obtainDateAndTimeStamp(sw, ts, pfx)			\
		obtainTimeStampAsString [(pfx)] ((sw), (ts))
#endif

#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define needsOrHasLocker() (false)
#else
	#define needsOrHasLocker(put)						\
		(!(cunilogSingleThreaded == (put)->culogType))
#endif

#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define canBenefitFromSpincount() (false)
#else
	#define canBenefitFromSpincount(put)											\
		(																			\
				(cunilogSingleThreadedSeparateLoggingThread	== (put)->culogType)	\
			||	(cunilogMultiThreadedSeparateLoggingThread	== (put)->culogType)	\
		)
#endif

#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define hasSeparateLoggingThread() (false)
#else
	#define hasSeparateLoggingThread(put)						\
		canBenefitFromSpincount (put)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef PLATFORM_IS_WINDOWS
		static inline void InitCriticalSection (CUNILOG_TARGET *put)
		{
			if (canBenefitFromSpincount (put))
			{
				#ifdef OS_IS_WINDOWS_XP
					InitializeCriticalSectionAndSpinCount	(
						&put->cl.cs,
						CUNILOG_WINDOWS_CRITICAL_SECTION_SPIN_COUNT
															);
				#else
					InitializeCriticalSectionEx	(
						&put->cl.cs,
						CUNILOG_WINDOWS_CRITICAL_SECTION_SPIN_COUNT,
						CRITICAL_SECTION_NO_DEBUG_INFO
												);
				#endif
			} else
			{
				InitializeCriticalSection (&put->cl.cs);
			}
		}
	#else
		static inline void InitCriticalSection (CUNILOG_TARGET *put)
		{
			pthread_mutex_init (&put->cl.mt, NULL);
			/*
			if (canBenefitFromSpincount (put))
				pthread_mutex_init (&put->cl.mt, NULL);
			else
				pthread_mutex_init (&put->cl.mt, NULL);
			*/
		}
	#endif
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline void InitCUNILOG_LOCKER (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (needsOrHasLocker (put))
		{
			InitCriticalSection (put);
		}
		#ifdef DEBUG
			put->cl.bInitialised = true;
		#endif
	}
#else
	#define InitCUNILOG_LOCKER(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline void EnterCUNILOG_LOCKER (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (needsOrHasLocker (put));
		#ifdef DEBUG
			ubf_assert_true (put->cl.bInitialised);
		#endif

		#ifdef OS_IS_WINDOWS
			EnterCriticalSection (&put->cl.cs);
		#else
			pthread_mutex_lock (&put->cl.mt);
		#endif
		cunilogSetDebugQueueLocked (put);
	}
#else
	#define EnterCUNILOG_LOCKER(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef PLATFORM_IS_WINDOWS
		static inline void LeaveCUNILOG_LOCKER (CUNILOG_TARGET *put)
		{
			ubf_assert_non_NULL (put);
			ubf_assert (needsOrHasLocker (put));
			#ifdef DEBUG
				ubf_assert_true (put->cl.bInitialised);
			#endif

			LeaveCriticalSection (&put->cl.cs);
			cunilogClrDebugQueueLocked (put);
		}
	#else
		static inline void LeaveCUNILOG_LOCKER (CUNILOG_TARGET *put)
		{
			ubf_assert_non_NULL (put);
			ubf_assert (needsOrHasLocker (put));
			#ifdef DEBUG
				ubf_assert_true (put->cl.bInitialised);
			#endif

			pthread_mutex_unlock (&put->cl.mt);
			cunilogClrDebugQueueLocked (put);
		}
	#endif
#else
	#define LeaveCUNILOG_LOCKER(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef OS_IS_WINDOWS
		static inline void DestroyCriticalSection (CUNILOG_TARGET *put)
		{
			DeleteCriticalSection (&put->cl.cs);
		}
	#else
		static inline void DestroyCriticalSection (CUNILOG_TARGET *put)
		{
			pthread_mutex_destroy (&put->cl.mt);
		}
	#endif
#endif
		
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline void DoneCUNILOG_LOCKER (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		#ifdef DEBUG
			ubf_assert_true (put->cl.bInitialised);
		#endif

		if (needsOrHasLocker (put))
			DestroyCriticalSection (put);
		#ifdef DEBUG
			put->cl.bInitialised = false;
		#endif
	}
#else
	#define DoneCUNILOG_LOCKER(x)
#endif

void InitSCUNILOGNPI (SCUNILOGNPI *pni)
{
	ubf_assert_non_NULL (pni);

	initSMEMBUF (&pni->smbRotMask);
	pni->lenRotMask			= 0;
	pni->nIgnoredTotal		= 0;
	pni->pNextVecCunilogFls	= NULL;
}

void DoneSCUNILOGNPI (SCUNILOGNPI *pni)
{
	ubf_assert_non_NULL (pni);

	if (isUsableSMEMBUF (&pni->smbRotMask))
		doneSMEMBUF (&pni->smbRotMask);
}

/*
	ObtainCurrentWorkingDirectoy

	Returns the current working directory with an ending forward or backslash as
	an SMEMBUF. Should probably go in its own module at some point as it certainly
	does not belong here.

	The function returns the amount of characters it has written to the buffer of
	the SMEMBUF structure, not including a terminating NUL character.
*/
static size_t ObtainCurrentWorkingDirectoy (SMEMBUF *mb)
{
	ubf_assert_non_NULL (mb);
	ubf_assert (isInitialisedSMEMBUF (mb));

	size_t	r = 0;

	#if defined (PLATFORM_IS_WINDOWS)

		WCHAR wc [1];
		DWORD dw = GetCurrentDirectoryW (1, wc);
		WCHAR *pw = malloc (sizeof (WCHAR) * dw + sizeof (WCHAR));
		if (pw)
		{
			DWORD dn = GetCurrentDirectoryW (dw, pw);
			ubf_assert (dn);
			ubf_assert (dn < dw);
			if (dn)
			{
				int rq = reqUTF8sizeFromUTF16wchars (dn);
				growToSizeSMEMBUF (mb, rq);
				if (isUsableSMEMBUF (mb))
				{
					int n = UTF8_from_WinU16 (mb->buf.pch, rq, pw);
					if (n)
					{
						mb->buf.pch [n - 1]	= '\\';
						mb->buf.pch [n]		= '\0';
					}
					r = n;
				}
			}
			free (pw);
		}

	#elif defined (PLATFORM_IS_POSIX)

		size_t	siz		= 32;
		char	*pr		= NULL;
		bool	rtry	= true;

		while (rtry)
		{
			growToSizeSMEMBUF (mb, siz + 1);
			if (isUsableSMEMBUF (mb))
			{
				pr = getcwd (mb->buf.pch, siz);
				if (pr)
				{
					size_t l = strlen (pr);
					pr [l]		= '/';
					pr [l + 1]	= '\0';
					r = l + 1;
					rtry = false;
				} else
				{
					if (ERANGE == errno)
						siz += 32;
					else
						rtry = false;
				}
			}
		}

	#else

		#error Not supported!

	#endif

	return r;
}

static size_t ObtainRelativeLogPathBase (SMEMBUF *mb, enCunilogRelPath relLogPath)
{
	switch (relLogPath)
	{
		#ifdef DEBUG
		case cunilogPath_isAbsolute:
			ubf_assert_msg (false, "This should have been caught before we got here");
			// Hopefully this causes an access violation/segmentation fault.
			return CUNILOG_SIZE_ERROR;
		#endif
		case cunilogPath_relativeToExecutable:
			return ObtainPathFromExecutableModule (mb);
		case cunilogPath_relativeToCurrentDir:
			return ObtainCurrentWorkingDirectoy (mb);
		case cunilogPath_relativeToHomeDir:
			return ObtainUserHomeDirectoy (mb);
	}
	return 0;
}

bool GetAbsPathFromAbsOrRelPath	(
		SMEMBUF				*psmb,
		size_t				*plmb,
		const char			*szAbsOrRelPath,
		size_t				lnAbsOrRelPath,
		enCunilogRelPath	absOrRelPath
								)
{
	ubf_assert_non_NULL (psmb);
	ubf_assert_non_NULL (szAbsOrRelPath);
	ubf_assert_non_0	(lnAbsOrRelPath);
	ubf_assert			(isInitialisedSMEMBUF (psmb));

	SMEMBUF b		= SMEMBUF_INITIALISER;
	lnAbsOrRelPath	= USE_STRLEN == lnAbsOrRelPath ? strlen (szAbsOrRelPath) : lnAbsOrRelPath;
	size_t	ln		= lnAbsOrRelPath;

	if (is_absolute_path_l (szAbsOrRelPath, ln))
	{
		if (!isDirSep (szAbsOrRelPath [ln - 1]))
		{
			if (SMEMBUFfromStrReserveBytes (&b, szAbsOrRelPath, ln, 2))
			{
				b.buf.pch [ln] = UBF_DIR_SEP;
				++ ln;
				b.buf.pch [ln] = ASCII_NUL;
			}
		} else
		{
			SMEMBUFfromStr (&b, szAbsOrRelPath, ln);
		}
	} else
	{	// The path is relative. It cannot be absolute.
		if (cunilogPath_isAbsolute == absOrRelPath)
			return false;
		SMEMBUF	t	= SMEMBUF_INITIALISER;
		size_t	lp	= ObtainRelativeLogPathBase (&t, absOrRelPath);
		ln = lp + lnAbsOrRelPath;
		if (!isDirSep (szAbsOrRelPath [lnAbsOrRelPath - 1]))
		{
			growToSizeSMEMBUF (&b, ln + 1);
			if (isUsableSMEMBUF (&b))
			{
				copySMEMBUF (&b, &t);
				memcpy (b.buf.pch + lp, szAbsOrRelPath, lnAbsOrRelPath);
				b.buf.pch [lp + lnAbsOrRelPath] = UBF_DIR_SEP;
				++ ln;
			}
		} else
		{
			growToSizeSMEMBUF (&b, ln);
			if (isUsableSMEMBUF (&b))
				memcpy (b.buf.pch + lp, szAbsOrRelPath, lnAbsOrRelPath);
		}
		doneSMEMBUF (&t);
	}
	str_correct_dir_separators (b.buf.pch, ln);
	str_remove_path_navigators (b.buf.pch, &ln);
	copySMEMBUFsiz (psmb, &b, ln + 1);						// NUL-terminated.
	doneSMEMBUF (&b);
	if (plmb)
		*plmb = ln;											// The length of the destination.
	return true;
}

char *createLogPathInCUNILOG_TARGET	(
		CUNILOG_TARGET *put, const char *szLogPath, size_t len, enCunilogRelPath relLogPath
									)
{
	ubf_assert_non_NULL (put);

	initSMEMBUF (&put->mbLogPath);
	if (szLogPath)
	{
		ubf_assert (0 != len);

		bool b;

		// The function only fails if szLogPath is NULL or relative but cunilogLogPath_isAbsolute
		//	has been given.
		b = GetAbsPathFromAbsOrRelPath	(
				&put->mbLogPath, &put->lnLogPath, szLogPath, len, relLogPath
										);
		if (!b)
		{
			SetCunilogError	(
				put->error,
				CUNILOG_ERROR_ABS_OR_REL_PATH, CUNILOG_SYSTEM_ERROR_NOT_SUPPORTED
							);
			return NULL;
		}
	} else
	{
		// If szLogPath is NULL its length should be 0.
		ubf_assert_0 (len);

		// Cannot be absolute.
		if (cunilogPath_isAbsolute == relLogPath)
		{
			SetCunilogError	(
				put->error,
				CUNILOG_ERROR_ABS_OR_REL_PATH, CUNILOG_SYSTEM_ERROR_NOT_SUPPORTED
							);
			return NULL;
		}

		// No path given. We use the path specified with relLogPath.
		put->lnLogPath = ObtainRelativeLogPathBase (&put->mbLogPath, relLogPath);
		if (CUNILOG_SIZE_ERROR == put->lnLogPath)
		{
			SetCunilogError (put->error, 
				CUNILOG_ERROR_PATH_BASE,
				CUNILOG_SYSTEM_ERROR_BUFFER_OVERFLOW
							);
			return NULL;
		}
		if (0 == put->lnLogPath)
		{
			SetCunilogError	(
				put->error,
				CUNILOG_ERROR_PATH_BASE,
				CUNILOG_SYSTEM_ERROR_NOT_SUPPORTED
							);
			return NULL;
		}
	}
	put->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED;
	return put->mbLogPath.buf.pch;
}

char *CreateLogPath_smb	(
		SMEMBUF *psmb, size_t *psiz, const char *szLogPath, size_t len, enCunilogRelPath relLogPath
						)
{
	ubf_assert_non_NULL (psmb);
	ubf_assert_non_NULL (psiz);

	if (szLogPath)
	{
		ubf_assert (0 != len);

		bool b;
		b = GetAbsPathFromAbsOrRelPath	(
				psmb, psiz, szLogPath, len, relLogPath
										);
		// The function only fails if szLogPath is NULL or relative but cunilogLogPath_isAbsolute
		//	has been given.
		if (!b)
			return NULL;
	} else
	{
		// If szLogPath is NULL its length should be 0.
		ubf_assert_0 (len);

		// Cannot be absolute.
		if (cunilogPath_isAbsolute == relLogPath)
			return NULL;

		// No path given. We use the path specified with relLogPath.
		*psiz = ObtainRelativeLogPathBase (psmb, relLogPath);
	}
	return psmb->buf.pch;
}

static inline const char *RemoveSlashesFromStart (const char *szAppName, size_t *plen)
{
	ubf_assert_non_NULL (plen);
	ubf_assert_non_NULL (szAppName);
	ubf_assert_non_0 (*plen);

	while (*plen && isDirectorySeparator (szAppName [0]))
	{
		*plen		-= 1;
		szAppName	+= 1;
	}
	return szAppName;
}

char *createAppNameInCUNILOG_TARGET (CUNILOG_TARGET *put, const char *szAppName, size_t len)
{
	ubf_assert_non_NULL (put);

	initSMEMBUF (&put->mbAppName);
	if (szAppName && len)
	{
		size_t l = len;
		szAppName = RemoveSlashesFromStart (szAppName, &l);
		ubf_assert_non_NULL (szAppName);
		ubf_assert_non_0 (l);

		if (szAppName && l)
		{
			SMEMBUFfromStr (&put->mbAppName, szAppName, l);
			str_correct_dir_separators (put->mbAppName.buf.pch, l);
			put->lnAppName = l;
		} else
			return NULL;
	} else
	{
		put->lnAppName = ObtainAppNameFromExecutableModule (&put->mbAppName);
		if (0 == put->lnAppName)
			return NULL;
	}
	put->uiOpts |= CUNILOGTARGET_APPNAME_ALLOCATED;
	return put->mbAppName.buf.pch;
}

enum cunilogprocessfrequency frequencyTbl [cunilogPostfixAmountEnumValues] =
{
	/* cunilogPostfixNone				*/			cunilogProcessAppliesTo_nAlways
	/* cunilogPostfixMinute				*/		,	cunilogProcessAppliesTo_MinuteChanged
	/* cunilogPostfixMinuteT			*/		,	cunilogProcessAppliesTo_MinuteChanged
	/* cunilogPostfixHour				*/		,	cunilogProcessAppliesTo_HourChanged
	/* cunilogPostfixHourT				*/		,	cunilogProcessAppliesTo_HourChanged
	/* cunilogPostfixDay				*/		,	cunilogProcessAppliesTo_DayChanged
	/* cunilogPostfixWeek				*/		,	cunilogProcessAppliesTo_WeekChanged
	/* cunilogPostfixMonth				*/		,	cunilogProcessAppliesTo_MonthChanged
	/* cunilogPostfixYear				*/		,	cunilogProcessAppliesTo_YearChanged
	/* cunilogPostfixDotNumberMinutely	*/		,	cunilogProcessAppliesTo_MinuteChanged
	/* cunilogPostfixDotNumberHourly	*/		,	cunilogProcessAppliesTo_HourChanged
	/* cunilogPostfixDotNumberDaily		*/		,	cunilogProcessAppliesTo_DayChanged
	/* cunilogPostfixDotNumberWeekly	*/		,	cunilogProcessAppliesTo_WeekChanged
	/* cunilogPostfixDotNumberMonthly	*/		,	cunilogProcessAppliesTo_MonthChanged
	/* cunilogPostfixDotNumberYearly	*/		,	cunilogProcessAppliesTo_YearChanged
};

static inline enum cunilogprocessfrequency defaultFrequencyFromPostfix (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert			(0 <= put->culogPostfix);
	ubf_assert			(cunilogPostfixAmountEnumValues > put->culogPostfix);

	return frequencyTbl [put->culogPostfix];
}

static inline void correctDefaultFrequency (CUNILOG_PROCESSOR *cp, CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(put->cprocessors);
	ubf_assert_non_0	(put->nprocessors);
	ubf_assert_non_NULL	(cp);

	if (cunilogProcessAppliesTo_Auto == cp->freq)
	{
		switch (cp->task)
		{
			case cunilogProcessNoOperation:
			case cunilogProcessEchoToConsole:
			case cunilogProcessUpdateLogFileName:
			case cunilogProcessWriteToLogFile:
			case cunilogProcessCustomProcessor:
				cp->freq = cunilogProcessAppliesTo_nAlways;
				break;
			case cunilogProcessFlushLogFile:
			case cunilogProcessRotateLogfiles:
				cp->freq = defaultFrequencyFromPostfix (put);
				break;
			case cunilogProcessAmountEnumValues:
				ubf_assert_msg (false, "Illegal value");
				break;
		}
	}
}

static inline bool hasDotNumberPostfix (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	return	(
					cunilogPostfixDotNumberMinutely	<= put->culogPostfix
				&&	cunilogPostfixDotNumberYearly	>= put->culogPostfix
			);
}

static inline void defaultProcessorParameters (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(put->cprocessors);
	ubf_assert_non_0	(put->nprocessors);

	CUNILOG_PROCESSOR		*cp;
	CUNILOG_ROTATION_DATA	*prPrev				= NULL;
	CUNILOG_ROTATION_DATA	*prCurr;
	//CUNILOG_LOGFILE			*pLF				= NULL;

	unsigned int n = 0;
	while (n < put->nprocessors)
	{
		cp = put->cprocessors [n];
		correctDefaultFrequency (cp, put);
		switch (cp->task)
		{
			case cunilogProcessRotateLogfiles:
				if (hasDotNumberPostfix (put))
				{	// For this rotator the trick with remembering how many files we've
					//	had so far doesn't work. However, we need to sort the retrieved
					//	files list with active dot number sorting.
					cunilogTargetSetFSneedsSorting	(put);
					cunilogTargetSetNumberSorting	(put);
				} else
				{
					prCurr = cp->pData;
					if (prPrev && CUNILOG_MAX_ROTATE_AUTO == prPrev->nMaxToRotate)
						prPrev->nMaxToRotate = prCurr->nIgnore;
					prPrev = prCurr;
				}
				break;
			case cunilogProcessWriteToLogFile:
				ubf_assert_NULL (cp->pData);
				/*
				pLF = cp->pData;
				*/
				break;
			case cunilogProcessFlushLogFile:
				ubf_assert_NULL (cp->pData);
				/*	Now belongs to the target.
				// If we abort here, the caller has supplied a cunilogProcessFlushLogFile
				//	processor without supplying a cunilogProcessWriteToLogFile processor
				//	first.
				ubf_assert_non_NULL (pLF);
				if (NULL == cp->pData)
					cp->pData = pLF;
				*/
				break;
		}
		++ n;
	}
}

static inline void zeroProcessors (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	put->cprocessors	= NULL;
	put->nprocessors	= 0;
}

static void DoneCUNILOG_TARGETprocessors (CUNILOG_TARGET *put);

/*
	In the target initialisers zeroProcessors () must be called before prepareProcessors ().
*/
static bool prepareProcessors (CUNILOG_TARGET *put, CUNILOG_PROCESSOR **cp, unsigned int np)
{
	ubf_assert_non_NULL		(put);

	// The caller does not wish default processors. The function
	//	ConfigCUNILOG_TARGETprocessorList () must be called before the target is usable.
	if (put->uiOpts & CUNILOGTARGET_NO_DEFAULT_PROCESSORS)
	{
		ubf_assert_NULL		(put->cprocessors);
		ubf_assert_0		(put->nprocessors);
		return true;
	}

	/*
	if (put->cprocessors && put->nprocessors)
	{
		DoneCUNILOG_TARGETprocessors (put);
	}
	*/

	if (NULL == cp || 0 == np)
	{
		ubf_assert (NULL == cp);
		ubf_assert (0 == np);

		put->cprocessors = CreateNewDefaultProcessors (&put->nprocessors);
		if (put->cprocessors)
			cunilogSetProcessorsAllocated (put);
		else
		{
			SetCunilogSystemError (put->error, CUNILOG_ERROR_HEAP_ALLOCATION);
			return false;
		}
	} else
	{
		put->cprocessors = cp;
		put->nprocessors = np;
	}
	defaultProcessorParameters (put);
	return true;
}

static void prepareCUNILOG_TARGETinitFilenameBuffers (CUNILOG_TARGET *put, size_t lnTotal)
{
	ubf_assert_non_NULL (put);

	initSMEMBUFtoSize (&put->mbLogfileName, lnTotal);		// The actual log file.
	if (isUsableSMEMBUF (&put->mbLogfileName))
		cunilogSetLogFileAllocated (put);
	initSMEMBUFtoSize (&put->mbLogFileMask, lnTotal);		// Mask for logfile rotation.
	if (isUsableSMEMBUF (&put->mbLogFileMask))
		cunilogSetLogFileMaskAllocated (put);
	initSMEMBUFtoSize (&put->mbFilToRotate, lnTotal);
	if (isUsableSMEMBUF (&put->mbFilToRotate))
		cunilogSetFileToRotateAllocated (put);
}

static bool prepareCUNILOG_TARGETforLogging (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	// A little helper for debugging.
	/*
	if (cunilogPostfixDotNumberDescending == put->culogPostfix)
	{
		size_t lnAfterDotLog = 0;
	}
	*/

	size_t lnRoomForStamp	= lenDateTimeStampFromPostfix (put->culogPostfix);
	size_t lnUnderscore;

	// The underscore that separates the appname from the timestamp.switch (put->culogPostfix)
	switch (put->culogPostfix)
	{
		case cunilogPostfixDotNumberMinutely:	lnUnderscore = 0;						break;
		default:								lnUnderscore = lnRoomForStamp ? 1 : 0;	break;
	}
	// The longest one is cunilogPostfixDotNumberDescending.
	ubf_assert (lnRoomForStamp <= UBF_UINT64_LEN + 1);

	size_t lnTotal;
	lnTotal = put->lnLogPath + put->lnAppName + lnUnderscore;

	// The pointer to the ASCII timestamp within the filename allows us to later update only
	//	the timestamp within the log file's name. We add this index/length to the filename
	//	further down to get its position.
	size_t idxStamp = lnTotal;
	lnTotal += lnRoomForStamp
				+ lenCunilogLogFileNameExtension
				+ 1;	// A terminating NUL character so that we can use the log file's
						//	name directly in OS APIs.
	prepareCUNILOG_TARGETinitFilenameBuffers (put, lnTotal);
	bool bUsablembs =		isUsableSMEMBUF (&put->mbLogfileName)
						&&	isUsableSMEMBUF (&put->mbLogFileMask)
						&&	isUsableSMEMBUF (&put->mbLogFileMask);
	if (bUsablembs)
	{
		// Remember the position of the timestamp for quick and easy update.
		put->szDateTimeStamp = put->mbLogfileName.buf.pch + idxStamp;

		char *szWrite = put->mbLogfileName.buf.pch;
		memcpy (szWrite, put->mbLogPath.buf.pch, put->lnLogPath);
		szWrite += put->lnLogPath;
		memcpy (szWrite, put->mbAppName.buf.pch, put->lnAppName);
		szWrite += put->lnAppName;

		if (lnUnderscore)
		{
			szWrite [0] = '_';
			szWrite += 1;
		}

		if (hasDotNumberPostfix (put))
		{
			memcpy (szWrite, szCunilogLogFileNameExtension, sizCunilogLogFileNameExtension);
			// Create the wildcard/search mask.
			copySMEMBUF (&put->mbLogFileMask, &put->mbLogfileName);
			// We go for "<logpath>/<appname>.log*". This needs to be tested on POSIX.
			#ifdef PLATFORM_IS_POSIX
				ubf_assert_msg (false, "File may not be correct for POSIX");
			#endif
			char *szAster =		put->mbLogFileMask.buf.pch
							+	(szWrite - put->mbLogfileName.buf.pch)
							+	lenCunilogLogFileNameExtension;
			memcpy (szAster , "*", 2);
		} else
		{
			szWrite += lnRoomForStamp;
			// Note that this memcpy () makes it NUL-terminated.
			memcpy (szWrite, szCunilogLogFileNameExtension, sizCunilogLogFileNameExtension);
			// Create the wildcard/search mask.
			copySMEMBUF (&put->mbLogFileMask, &put->mbLogfileName);
			memcpy	(
				put->mbLogFileMask.buf.pch + (put->szDateTimeStamp - put->mbLogfileName.buf.pcc),
				postfixMaskFromLogPostfix (put->culogPostfix),
				lenDateTimeStampFromPostfix (put->culogPostfix)
					);
			#ifdef PLATFORM_IS_POSIX
				// The function ForEachPsxDirEntry () returns every file and doesn't support a search
				//	mask. The callback function can use the szLogFileMask and its length to check if
				//	the returned filename fits the mask.
				put->szLogFileMask	= put->mbLogFileMask.buf.pch + put->lnLogPath;
				put->lnsLogFileMask	=		put->lnAppName
										+	lenDateTimeStampFromPostfix (put->culogPostfix)
										+	lenCunilogLogFileNameExtension
										+	lnUnderscore;
			#endif
		}

		// Create name of the found file.
		copySMEMBUF (&put->mbFilToRotate, &put->mbLogPath);

		ubf_assert (0 < CUNILOG_INITIAL_EVENTLINE_SIZE);
		initSMEMBUFtoSize (&put->mbLogEventLine, CUNILOG_INITIAL_EVENTLINE_SIZE);

		#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
			initSMEMBUFtoSize (&put->mbColEventLine, CUNILOG_INITIAL_COLEVENTLINE_SIZE);
		#endif

		cunilogSetTargetInitialised (put);
		return true;
	} else
	{
		SetCunilogSystemError (put->error, CUNILOG_ERROR_HEAP_ALLOCATION);
		put->szDateTimeStamp = NULL;
		ubf_assert_non_NULL (put->szDateTimeStamp);
		return false;
	}
}

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool InitCUNILOG_TARGETqueuesemaphore (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (HAS_CUNILOG_TARGET_A_QUEUE (put))
		{
			#ifdef OS_IS_WINDOWS
				// See
				//	https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createsemaphorew .
				put->sm.hSemaphore = CreateSemaphoreW (NULL, 0, MAXLONG, NULL);
				if (NULL == put->sm.hSemaphore)
					SetCunilogSystemError (put->error, CUNILOG_ERROR_SEMAPHORE);
				return NULL != put->sm.hSemaphore;
			#else
				int i = sem_init (&put->sm.tSemaphore, 0, 0);
				ubf_assert (0 == i);
				if (0 != i)
					SetCunilogSystemError (put->error, CUNILOG_ERROR_SEMAPHORE);
				return 0 == i;
			#endif
		}
		// If no semaphore is required, not creating it is seen as success.
		return true;
	}
#else
	#define InitCUNILOG_TARGETqueuesemaphore(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void DoneCUNILOG_TARGETqueuesemaphore (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (HAS_CUNILOG_TARGET_A_QUEUE (put))
		{
			#ifdef OS_IS_WINDOWS
				bool b = CloseHandle (put->sm.hSemaphore);
				ubf_assert_true (b);
				put->sm.hSemaphore = NULL;
			#else
				int i = sem_destroy (&put->sm.tSemaphore);
				ubf_assert (0 == i);
				UNREFERENCED_PARAMETER (i);
			#endif
		}
	}
#else
	#define DoneCUNILOG_TARGETqueuesemaphore(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static bool InitCUNILOG_TARGETqueue (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (HAS_CUNILOG_TARGET_A_QUEUE (put))
		{
			put->qu.first	= NULL;
			put->qu.last	= NULL;
			put->qu.num		= 0;
		}
		// If no semaphore is required, not creating it is seen as success.
		return true;
	}
#else
	#define InitCUNILOG_TARGETqueue(x)
#endif

static bool StartSeparateLoggingThread_ifNeeded (CUNILOG_TARGET *put)
;

#ifdef PLATFORM_IS_WINDOWS
	static culogconcp ourCunilogConsoleOutputCodePage = cunilogConsoleIsUninitialised;

	void CunilogSetConsoleTo (culogconcp cp)
	{
		ubf_assert	(
							cunilogConsoleIsUTF8	== cp
						||	cunilogConsoleIsUTF16	== cp
						||	cunilogConsoleIsNeither	== cp
					);

		switch (cp)
		{
			case cunilogConsoleIsUTF8:
				SetConsoleCodePageToUTF8 ();	break;
			case cunilogConsoleIsUTF16:
				WinSetStdinToUTF16 ();
				WinSetStdoutToUTF16 ();			break;
			case cunilogConsoleIsNeither:		break;
			default:
				SetConsoleCodePageToUTF8 ();	break;
		}
		ourCunilogConsoleOutputCodePage = cp;
	}
#endif

#ifdef PLATFORM_IS_WINDOWS
	enum enbANSIescapeSequencesEnabled
	{
		ansiEscapeSequsUninitialised,
		ansiEscapeSequsEnabled,
		ansiEscapeSequsDisabled
	};
	static bool bANSIescapeSequencesEnabled;

	bool CunilogEnableANSI (void)
	{
		HANDLE	hConsole	= GetStdHandle (STD_OUTPUT_HANDLE);
		DWORD	dwMode		= 0;

		if (INVALID_HANDLE_VALUE != hConsole)
		{
			if (GetConsoleMode (hConsole, &dwMode))
			{
				dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
				if (SetConsoleMode (hConsole, dwMode))
				{
					bANSIescapeSequencesEnabled = ansiEscapeSequsEnabled;
					return true;
				}
			}
		}
		return false;
	}

	bool CunilogDisableANSI (void)
	{
		HANDLE	hConsole	= GetStdHandle (STD_OUTPUT_HANDLE);
		DWORD	dwMode		= 0;

		if (INVALID_HANDLE_VALUE != hConsole)
		{
			if (GetConsoleMode (hConsole, &dwMode))
			{
				dwMode &= ~ ENABLE_VIRTUAL_TERMINAL_PROCESSING;
				if (SetConsoleMode (hConsole, dwMode))
				{
					bANSIescapeSequencesEnabled = ansiEscapeSequsDisabled;
					return true;
				}
			}
		}
		return false;
	}
	
	bool CunilogIsANSIenabled (void)
	{
		return ansiEscapeSequsEnabled == bANSIescapeSequencesEnabled;
	}

	static inline void CunilogEnableANSIifNotInitialised (void)
	{
		if (ansiEscapeSequsUninitialised == bANSIescapeSequencesEnabled)
			CunilogEnableANSI ();
	}
#endif

char *CunilogGetEnv (const char *szName)
{
	ubf_assert_non_NULL (szName);

	#if defined (PLATFORM_IS_WINDOWS)
		return getenv (szName);
	#elif defined (PLATFORM_IS_POSIX)
		return secure_getenv (szName);
	#elif
		#error Not supported
	#endif
}

bool Cunilog_Have_NO_COLOR (void)
{
	char *szNoCol = CunilogGetEnv ("NO_COLOR");
	return szNoCol && szNoCol [0];
}

#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	// This is the only type possible in a single-threaded environment.
	#define unilogTypeFromArgument(type)					\
				(cunilogSingleThreaded)
#else
	#define unilogTypeFromArgument(type)					\
				(type)
#endif

/*
	This function is not used anymore. The configurable hex dump is not supported
	anymore.
*/
static inline void InitCUNILOG_TARGETdumpstructs (CUNILOG_TARGET *put)
{
	UNUSED (put);

	ubf_assert_non_NULL (put);

	//put->psdump = NULL;
}

static inline void initCUNILOG_TARGEToptionFlags (CUNILOG_TARGET *put, runProcessorsOnStartup rp)
{
	ubf_assert_non_NULL (put);
	ubf_assert	(
						cunilogRunProcessorsOnStartup		== rp
					||	cunilogDontRunProcessorsOnStartup	== rp
				);

	put->uiOpts = CUNILOGTARGET_NO_FLAGS;
	if (cunilogRunProcessorsOnStartup == rp)
		cunilogSetRunAllProcessorsOnStartup (put);

	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
		cunilogSetUseColourForEcho (put);
	#endif
}

static inline void initFilesListInCUNILOG_TARGET (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	vec_init (&put->fls);
	InitSBULKMEM (&put->sbm, CUNILOG_STD_BULK_ALLOC_SIZE);

	// Note that we do not allocate any bulk memory here yet. If for instance the caller
	//	hasn't provided a rotation processor we may not even need one.
}

static inline void initPrevTimestamp (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	size_t lenPostfixStamp = lenDateTimeStampFromPostfix (put->culogPostfix);
	memset (put->cPrevDateTimeStamp, 0, lenPostfixStamp);
}

#ifdef PLATFORM_IS_POSIX
	// The plain logging folder name is not used on Windows. It is only required
	//	for opendir () on POSIX. This might change in the future as I can imagine
	//	that some custom processor might also benefit from it.
	static void InitCUNILOG_TARGETmbLogFold (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (isUsableSMEMBUF (&put->mbLogPath));
		ubf_assert (0 < put->lnLogPath);
		size_t lenLogp = put->lnLogPath - 1;
		ubf_assert (0 < lenLogp);

		ubf_assert	(
							'/'		== put->mbLogPath.buf.pch [lenLogp]
						||	'\\'	== put->mbLogPath.buf.pch [lenLogp]
					);

		initSMEMBUF (&put->mbLogFold);
		growToSizeSMEMBUF (&put->mbLogFold, put->lnLogPath);
		if (isUsableSMEMBUF (&put->mbLogFold))
		{
			memcpy (put->mbLogFold.buf.pch, put->mbLogPath.buf.pch, lenLogp);
			put->mbLogFold.buf.pch [lenLogp] = '\0';
			put->lnLogFold = lenLogp;
			return;
		}
		// We should never get here.
		ubf_assert (false);
		put->lnLogFold = 0;
	}
#else
	#define InitCUNILOG_TARGETmbLogFold(x)
#endif

static inline void cunilogInitCUNILOG_LOGFILE (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	#ifdef OS_IS_WINDOWS
		put->logfile.hLogFile = NULL;
	#else
		put->logfile.fLogFile = NULL;
	#endif
}

static inline bool cunilogOpenLogFile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert			(isInitialisedSMEMBUF (&put->mbLogfileName));

	#ifdef PLATFORM_IS_WINDOWS
		put->logfile.hLogFile = CreateFileU8	(
						put->mbLogfileName.buf.pcc,
						CUNILOG_DEFAULT_OPEN_MODE,
						FILE_SHARE_DELETE | FILE_SHARE_READ,
						NULL, OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
									);
		return NULL != put->logfile.hLogFile && INVALID_HANDLE_VALUE != put->logfile.hLogFile;
	#else
		// We always (and automatically) append.
		put->logfile.fLogFile = fopen (put->mbLogfileName.buf.pcc, CUNILOG_DEFAULT_OPEN_MODE);
		return NULL != put->logfile.fLogFile;
	#endif
}

static inline void cunilogCloseCUNILOG_LOGFILEifOpen (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	#ifdef OS_IS_WINDOWS
		if (put->logfile.hLogFile)
		{
			CloseHandle (put->logfile.hLogFile);
			put->logfile.hLogFile = NULL;
		}
	#else
		if (put->logfile.fLogFile)
		{
			fclose (put->logfile.fLogFile);
			put->logfile.fLogFile = NULL;
		}
	#endif
}

static inline bool initCommonMembersAndPrepareCUNILOG_TARGET (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	put->error								= CUNILOG_NO_ERROR;
	str_remove_path_navigators (put->mbLogPath.buf.pch, &put->lnLogPath);
	#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
		put->errorCB						= NULL;
	#endif
	InitSCUNILOGNPI							(&put->scuNPI);
	DBG_INIT_CNTTRACKER						(put->evtLineTracker);
	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		put->nPendingNoRotEvts				= 0;
		put->nPausedEvents					= 0;
	#endif
	put->dumpWidth							= enDataDumpWidth16;
	put->evSeverityType						= cunilogEvtSeverityTypeDefault;
	initPrevTimestamp						(put);
	InitCUNILOG_TARGETmbLogFold				(put);
	InitCUNILOG_TARGETdumpstructs			(put);
	InitCUNILOG_LOCKER						(put);
	InitCUNILOG_TARGETqueuesemaphore		(put);
	InitCUNILOG_TARGETqueue					(put);
	initFilesListInCUNILOG_TARGET			(put);
	cunilogInitCUNILOG_LOGFILE						(put);
	bool b;
	b = StartSeparateLoggingThread_ifNeeded	(put);
	if (b)
	{
		ResetCunilogError (put->error);
		return prepareCUNILOG_TARGETforLogging	(put);
	}
	return false;
}

#ifdef DEBUG
	void assertSaneParametersCUNILOG_TARGET	(
	  enCunilogRelPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
											)
	{
		ubf_assert (0 <= relLogPath);
		ubf_assert (cunilogPath_XAmountEnumValues > relLogPath);
		ubf_assert (0 <= type);
		ubf_assert (cunilogTypeAmountEnumValues > type);
		ubf_assert (0 <= postfix);
		ubf_assert (cunilogPostfixAmountEnumValues >= postfix);
		ubf_assert (0 <= unilogTSformat);
		ubf_assert (cunilogEvtTS_AmountEnumValues > unilogTSformat);
		ubf_assert (0 <= unilogNewLine);
		ubf_assert (cunilogNewLineAmountEnumValues > unilogNewLine);
		ubf_assert (0 <= rp);
		ubf_assert (cunilogRunProcessors_AmountEnumValues > rp);
	}
#else
	#define assertSaneParametersCUNILOG_TARGET(rP, tpy, psf, ts, nl, rp)
#endif

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
{
	ubf_assert_non_NULL (put);
	assertSaneParametersCUNILOG_TARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	size_t			lnLogPath		= (size_t) -1 != lenLogPath	? lenLogPath : strlen (szLogPath);
	size_t			lnAppName		= (size_t) -1 != lenAppName	? lenAppName : strlen (szAppName);

	initCUNILOG_TARGEToptionFlags (put, rp);
	put->culogPostfix		= postfix;
	put->culogType			= unilogTypeFromArgument (type);
	put->unilogEvtTSformat	= unilogTSformat;
	put->unilogNewLine		= unilogNewLine;

	// The function sets put->error for us.
	char *szLP = createLogPathInCUNILOG_TARGET (put, szLogPath, lnLogPath, relLogPath);
	if (NULL == szLP && cunilogPath_isAbsolute == relLogPath)
	{
		SetCunilogError	(
			put->error, CUNILOG_ERROR_ABS_OR_REL_PATH, CUNILOG_SYSTEM_ERROR_NOT_SUPPORTED
						);
		return NULL;
	}
	char *sz = createAppNameInCUNILOG_TARGET (put, szAppName, lnAppName);
	if (NULL == sz)
	{
		SetCunilogSystemError (put->error, CUNILOG_ERROR_APPNAME);
		return NULL;
	}
	zeroProcessors (put);
	bool b = prepareProcessors (put, cuProcessorList, nProcessors);
	if (b)
	{
		return initCommonMembersAndPrepareCUNILOG_TARGET (put) ? put : NULL;
	} else
		return false;
}

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
	{
		ubf_assert_non_NULL (put);
		ubf_assert (0 <= relLogPath);
		ubf_assert (cunilogPath_XAmountEnumValues > relLogPath);
		ubf_assert (0 <= type);
		ubf_assert (cunilogTypeAmountEnumValues > type);

		CUNILOG_TARGET	*prt;

		prt = InitCUNILOG_TARGETex	(
				put,
				szLogPath,	lenLogPath,
				szAppName,	lenAppName,
				relLogPath,
				type,
				cunilogPostfixDefault,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
									);
		return prt;
	}
#endif

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
{
	assertSaneParametersCUNILOG_TARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	//_ASSERT (false);

	CUNILOG_TARGET	*pu;							// Return value.
	size_t			lnUNILOGTARGET	= ALIGNED_SIZE (sizeof (CUNILOG_TARGET), CUNILOG_DEFAULT_ALIGNMENT);
	size_t			lnTotal			= lnUNILOGTARGET;
	size_t			lnLP;
	size_t			lnAP;
	SMEMBUF			logpath			= SMEMBUF_INITIALISER;
	SMEMBUF			appname			= SMEMBUF_INITIALISER;

	size_t			lnLogPath		= (size_t) -1 != lenLogPath	? lenLogPath : strlen (szLogPath);
	size_t			lnAppName		= (size_t) -1 != lenAppName	? lenAppName : strlen (szAppName);

	if (szLogPath && lnLogPath)
	{
		size_t ln;
		char *szLP = CreateLogPath_smb (&logpath, &ln, szLogPath, lnLogPath, relLogPath);

		ubf_assert_non_NULL (szLP);
		UNUSED (szLP);

		lnLogPath = ln;
		if (!isDirSep (logpath.buf.pch [ln -1]))
			lnLP = ALIGNED_SIZE (ln + 2, CUNILOG_DEFAULT_ALIGNMENT);
		else 
			lnLP = ALIGNED_SIZE (ln + 1, CUNILOG_DEFAULT_ALIGNMENT);
		lnTotal += lnLP;
	} else
	{	// No log path given.
		if (cunilogPath_isAbsolute == relLogPath)
		{
			#ifndef CUNILOG_BUILD_TEST_FNCTS
				ubf_assert_msg	(
					false,
					"szLogPath cannot be relative or NULL if cunilogLogPath_isAbsolute is given"
								);
			#endif
			return NULL;
		}
		lnLogPath = ObtainRelativeLogPathBase (&logpath, relLogPath);
		ubf_assert_non_0 (lnLogPath);
		lnLP = ALIGNED_SIZE (lnLogPath + 1, CUNILOG_DEFAULT_ALIGNMENT);
		lnTotal += lnLP;
	}
	if (szAppName && lnAppName)
	{
		lnAP = ALIGNED_SIZE (lnAppName + 1, CUNILOG_DEFAULT_ALIGNMENT);
		lnTotal += lnAP;
	} else
	{	// No application name given.
		lnAppName = ObtainAppNameFromExecutableModule (&appname);
		ubf_assert_non_0 (lnAppName);
		szAppName = appname.buf.pch;
		lnAP = ALIGNED_SIZE (lnAppName + 1, CUNILOG_DEFAULT_ALIGNMENT);
		lnTotal += lnAP;
	}
	pu = ubf_malloc (lnTotal);
	if (pu)
	{
		initCUNILOG_TARGEToptionFlags (pu, rp);
		pu->uiOpts |= CUNILOGTARGET_ALLOCATED;
		initSMEMBUF (&pu->mbLogPath);
		pu->mbLogPath.buf.pcc = (char *) pu + ALIGNED_SIZE (lnUNILOGTARGET, CUNILOG_DEFAULT_ALIGNMENT);
		memcpy (pu->mbLogPath.buf.pch, logpath.buf.pch, lnLogPath + 1);
		if (!isDirSep (logpath.buf.pch [lnLogPath -1]))
		{
			pu->mbLogPath.buf.pch [lnLogPath]		= UBF_DIR_SEP;
			pu->mbLogPath.buf.pch [lnLogPath + 1]	= ASCII_NUL;
			pu->mbLogPath.size						= lnLogPath + 2;
			pu->lnLogPath							= lnLogPath + 1;
		} else
		{
			pu->mbLogPath.size						= lnLogPath + 1;
			pu->lnLogPath							= lnLogPath;
		}
		str_correct_dir_separators (pu->mbLogPath.buf.pch, lnLogPath);
		pu->mbAppName.buf.pch = pu->mbLogPath.buf.pch + lnLP;
		memcpy (pu->mbAppName.buf.pch, szAppName, lnAppName);
		str_correct_dir_separators (pu->mbAppName.buf.pch, lnAppName);
		pu->mbAppName.size		= lnAppName;
		pu->lnAppName			= lnAppName;
		pu->culogPostfix		= postfix;
		pu->culogType			= unilogTypeFromArgument (type);
		pu->unilogEvtTSformat	= unilogTSformat;
		pu->unilogNewLine		= unilogNewLine;
		zeroProcessors (pu);
		prepareProcessors (pu, cuProcessorList, nProcessors);
		initCommonMembersAndPrepareCUNILOG_TARGET (pu);
	}
	if (isUsableSMEMBUF (&logpath))
		doneSMEMBUF (&logpath);
	if (isUsableSMEMBUF (&appname))
		doneSMEMBUF (&appname);
	return pu;
}

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
{
	assertSaneParametersCUNILOG_TARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	CUNILOG_TARGET	*pu;

	if (put)
	{
		pu = put;
		InitCUNILOG_TARGETex	(
			pu,
			szLogPath, lenLogPath, szAppName, lenAppName, relLogPath,
			type, postfix, cuProcessorList, nProcessors,
			unilogTSformat, unilogNewLine, rp
							);
	} else
	{
		pu = CreateNewCUNILOG_TARGET	(
				szLogPath, lenLogPath, szAppName, lenAppName, relLogPath,
				type, postfix, cuProcessorList, nProcessors, 
				unilogTSformat, unilogNewLine, rp
									);
	}
	if (pu && pu->mbAppName.buf.pch)
	{
	} else
	{
		pu = DoneCUNILOG_TARGET (pu);
	}
	return pu;
}

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
{
	assertSaneParametersCUNILOG_TARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	return InitCUNILOG_TARGETex	(
		pCUNILOG_TARGETstatic, szLogPath, lenLogPath, szApplication, lenApplication, relLogPath,
		type, postfix, cuProcessorList, nProcessors, unilogTSformat, unilogNewLine, rp
								);
}

CUNILOG_TARGET *InitCUNILOG_TARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
{
	ubf_assert (0 <= relLogPath);
	ubf_assert (cunilogPath_XAmountEnumValues > relLogPath);
	ubf_assert (0 <= type);
	ubf_assert (cunilogTypeAmountEnumValues > type);

	return InitCUNILOG_TARGETex	(
				pCUNILOG_TARGETstatic,
				szLogPath,		lenLogPath,
				szApplication,	lenApplication,
				relLogPath,
				type,
				cunilogPostfixDefault,
				NULL, 0,
				cunilogEvtTS_Default,
				cunilogNewLineDefault,
				cunilogRunProcessorsOnStartup
								);
}

const char *GetAbsoluteLogPathCUNILOG_TARGET (CUNILOG_TARGET *put, size_t *plen)
{
	ubf_assert_non_NULL	(put);
	ubf_assert (cunilogIsTargetInitialised (put));

	if (cunilogIsTargetInitialised (put) && isUsableSMEMBUF (&put->mbLogPath))
	{
		if (plen)
			*plen = put->lnLogPath;
		return put->mbLogPath.buf.pcc;
	}
	return NULL;
}

const char *GetAbsoluteLogPathCUNILOG_TARGET_static (size_t *plen)
{
	ubf_assert_non_NULL	(pCUNILOG_TARGETstatic);
	ubf_assert (cunilogIsTargetInitialised (pCUNILOG_TARGETstatic));

	return GetAbsoluteLogPathCUNILOG_TARGET (pCUNILOG_TARGETstatic, plen);
}

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETcunilogpostfix (CUNILOG_TARGET *put, enum cunilogeventTSformat tsf)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= tsf);
		ubf_assert			(cunilogEvtTS_AmountEnumValues > tsf);

		put->unilogEvtTSformat = tsf;		
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETcunilognewline (CUNILOG_TARGET *put, newline_t nl)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= nl);
		ubf_assert			(cunilogNewLineAmountEnumValues > nl);

		put->unilogNewLine = nl;
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETeventSeverityFormatType	(
			CUNILOG_TARGET				*put,
			cueventsevfmtpy				eventSeverityFormatType
														)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (eventSeverityFormatType > 0);
		ubf_assert (eventSeverityFormatType <= cunilogEvtSeverityTypeChars9InBrackets);

		put->evSeverityType = eventSeverityFormatType;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ConfigCUNILOG_TARGETuseColourForEcho (CUNILOG_TARGET *put, bool bUseColour)
		{
			ubf_assert_non_NULL (put);

			if (bUseColour)
				cunilogSetUseColourForEcho (put);
			else
				cunilogClrUseColourForEcho (put);
		}
	#endif
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETrunProcessorsOnStartup (CUNILOG_TARGET *put, runProcessorsOnStartup rp)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(
									cunilogRunProcessorsOnStartup		== rp
								||	cunilogDontRunProcessorsOnStartup	== rp
							);

		switch (rp)
		{
			case cunilogRunProcessorsOnStartup:
				cunilogSetRunAllProcessorsOnStartup (put);
				break;
			case cunilogDontRunProcessorsOnStartup:
				cunilogClrRunAllProcessorsOnStartup (put);
				break;
			default:
				cunilogSetRunAllProcessorsOnStartup (put);
				break;
		}
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETprocessorList	(
					CUNILOG_TARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	{
		ubf_assert_non_NULL	(put);

		prepareProcessors (put, cuProcessorList, nProcessors);
	}
#endif

/*
	This function has a declaration in cunilogevtcmds.c too. If its signature changes,
	please don't forget to change it there too.
*/
void ConfigCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL (put->cprocessors);

	unsigned int n = 0;
	while (n < put->nprocessors)
	{
		if (task == put->cprocessors [n]->task)
			optCunProcSetOPT_CUNPROC_DISABLED (put->cprocessors [n]->uiOpts);
		-- n;
	}
}

/*
	This function has a declaration in cunilogevtcmds.c too. If its signature changes,
	please don't forget to change it there too.
*/
void ConfigCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL (put->cprocessors);

	unsigned int n = 0;
	while (n < put->nprocessors)
	{
		if (task == put->cprocessors [n]->task)
			optCunProcClrOPT_CUNPROC_DISABLED (put->cprocessors [n]->uiOpts);
		-- n;
	}
}

/*
	This function has a declaration in cunilogevtcmds.c too. If its signature changes,
	please don't forget to change it there too.
*/
void ConfigCUNILOG_TARGETdisableEchoProcessor (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL (put->cprocessors);

	ConfigCUNILOG_TARGETdisableTaskProcessors (put, cunilogProcessEchoToConsole);
}

/*
	This function has a declaration in cunilogevtcmds.c too. If its signature changes,
	please don't forget to change it there too.
*/
void ConfigCUNILOG_TARGETenableEchoProcessor (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL (put->cprocessors);

	ConfigCUNILOG_TARGETenableTaskProcessors (put, cunilogProcessEchoToConsole);
}

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void EnterCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		EnterCUNILOG_LOCKER (put);
	}

	void LeaveCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		LeaveCUNILOG_LOCKER (put);
	}
#endif

static void DoneCUNILOG_TARGETprocessors (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	unsigned int				np = put->nprocessors;
	unsigned int				ui;
	CUNILOG_PROCESSOR			*cp;
	union
	{
		CUNILOG_ROTATION_DATA	*prd;
		CUNILOG_CUSTPROCESS		*up;
	} upCust;

	for (ui = 0; ui < np; ++ ui)
	{
		cp = put->cprocessors [ui];
		switch (cp->task)
		{
			case cunilogProcessNoOperation:
			case cunilogProcessEchoToConsole:
			case cunilogProcessUpdateLogFileName:
			case cunilogProcessFlushLogFile:
				break;
			case cunilogProcessCustomProcessor:
				upCust.up = cp->pData;
				if (upCust.up->procDone)
					upCust.up->procDone (cp);
				break;
			case cunilogProcessTargetRedirector:
			case cunilogProcessAmountEnumValues:
				break;
			case cunilogProcessWriteToLogFile:
				cunilogCloseCUNILOG_LOGFILEifOpen (put);
				break;
			case cunilogProcessRotateLogfiles:
				upCust.prd = cp->pData;
				if (cunilogHasRotatorFlag_USE_MBSRCMASK (upCust.prd))
				{
					doneSMEMBUF (&upCust.prd->mbSrcMask);
					cunilogClrRotatorFlag_USE_MBSRCMASK (upCust.prd);
				}
				if (cunilogHasRotatorFlag_USE_MBDSTFILE (upCust.prd))
				{
					doneSMEMBUF (&upCust.prd->mbDstFile);
					cunilogClrRotatorFlag_USE_MBDSTFILE (upCust.prd);
				}
				break;
		}
	}

	if (cunilogIsProcessorsAllocated (put))
	{
		ubf_free (put->cprocessors);
		zeroProcessors (put);
		cunilogClrProcessorsAllocated (put);
	}
}

/*
	This function is a no-op.
*/
static void DoneCUNILOG_TARGETpsdump (CUNILOG_TARGET *psu)
{
	UNUSED (psu);

	ubf_assert_non_NULL (psu);

	/*
	SCUNILOGDUMP *pd = psu->psdump;
	if (pd)
	{
		if (pd->dump_prs)
			ubf_free (pd->dump_prs);
		if (pd->dump_sns)
			ubf_free (pd->dump_sns);
	}
	*/
}

static void DoneCUNILOG_TARGETmembers (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsLogPathAllocated (put))
		freeSMEMBUF (&put->mbLogPath);
	if (cunilogIsAppNameAllocated (put))
		freeSMEMBUF (&put->mbAppName);
	if (cunilogIsLogFileAllocated (put))
		freeSMEMBUF (&put->mbLogfileName);
	if (cunilogIsLogFileMaskAllocated (put))
		freeSMEMBUF (&put->mbLogFileMask);
	if (cunilogIsFileToRotateAllocated (put))
		freeSMEMBUF (&put->mbFilToRotate);

	freeSMEMBUF (&put->mbLogEventLine);

	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
		freeSMEMBUF (&put->mbColEventLine);
	#endif

	DoneSCUNILOGNPI (&put->scuNPI);
	DoneCUNILOG_LOCKER (put);
	DoneCUNILOG_TARGETqueuesemaphore (put);
	vec_deinit (&put->fls);
	DoneSBULKMEM (&put->sbm);
	DoneCUNILOG_TARGETpsdump (put);
}

CUNILOG_TARGET *DoneCUNILOG_TARGET (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);
	ubf_assert (cunilogIsTargetInitialised (put));

	DoneCUNILOG_TARGETprocessors (put);
	DoneCUNILOG_TARGETmembers (put);
	if (cunilogIsTargetAllocated (put))
	{
		ubf_free (put);
	}
	return NULL;
}

/*
	Copy from cunilogstructs.h.

enum cunilogeventseverity
{
		cunilogEvtSeverityNone									//  0
	,	cunilogEvtSeverityNonePass								//  1
	,	cunilogEvtSeveriiyNoneFail								//  2
	,	cunilogEvtSeverityBlanks								//  3
	,	cunilogEvtSeverityEmergency								//	4
	,	cunilogEvtSeverityNotice								//	5
	,	cunilogEvtSeverityInfo									//  6
	,	cunilogEvtSeverityMessage								//  7
	,	cunilogEvtSeverityWarning								//  8
	,	cunilogEvtSeverityError									//  9
	,	cunilogEvtSeverityPass									// 10
	,	cunilogEvtSeverityFail									// 11
	,	cunilogEvtSeverityCritical								// 12
	,	cunilogEvtSeverityFatal									// 13
	,	cunilogEvtSeverityDebug									// 14
	,	cunilogEvtSeverityTrace									// 15
	,	cunilogEvtSeverityDetail								// 16
	,	cunilogEvtSeverityVerbose								// 17
	,	cunilogEvtSeverityIllegal								// 18
	// Do not add anything below this line.
	,	cunilogEvtSeverityXAmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityXAmountEnumValues.
};
*/
static const char *EventSeverityTexts3 [] =
{
		""				// cunilogEvtSeverityNone		 0
	,	""				// cunilogEvtSeverityNonePass	 1
	,	""				// cunilogEvtSevertiyNoneFail	 2
	,	""				// cunilogEvtSevertiyNoneWarn	 3
	,	"   "			// cunilogEvtSeverityBlanks		 4
	,	"EMG"			// cunilogEvtSeverityEmergency	 5
	,	"NOT"			// cunilogEvtSeverityNotice		 6
	,	"INF"
	,	"MSG"
	,	"WRN"
	,	"ERR"
	,	"PAS"			// cunilogEvtSeverityPass		11
	,	"FAI"
	,	"CRI"
	,	"FTL"
	,	"DBG"
	,	"TRC"
	,	"DET"
	,	"VBS"
	,	"ILG"			// cunilogEvtSeverityIllegal	18
};
static const char *EventSeverityTexts5 [] =
{
		""				// cunilogEvtSeverityNone		 0
	,	""				// cunilogEvtSeverityNonePass	 1
	,	""				// cunilogEvtSevertiyNoneFail	 2
	,	""				// cunilogEvtSevertiyNoneWarn	 3
	,	"     "			// cunilogEvtSeverityBlanks		 4
	,	"EMRGY"			// cunilogEvtSeverityEmergency	 5
	,	"NOTE "			// cunilogEvtSeverityNotice		 6
	,	"INFO "
	,	"MESSG"
	,	"WARN "
	,	"ERROR"
	,	"PASS "			//cunilogEvtSeverityPass		11
	,	"FAIL "
	,	"CRIT "
	,	"FATAL"
	,	"DEBUG"
	,	"TRACE"
	,	"DETAI"
	,	"VERBO"
	,	"ILLEG"			// cunilogEvtSeverityIllegal	18
};
static const char *EventSeverityTexts5tgt [] =
{
		""				// cunilogEvtSeverityNone		 0
	,	""				// cunilogEvtSeverityNonePass	 1
	,	""				// cunilogEvtSevertiyNoneFail	 2
	,	""				// cunilogEvtSevertiyNoneWarn	 3
	,	""				// cunilogEvtSeverityBlanks		 4
	,	"EMRGY"			// cunilogEvtSeverityEmergency	 5
	,	"NOTE"			// cunilogEvtSeverityNotice		 6
	,	"INFO"
	,	"MESSG"
	,	"WARN"
	,	"ERROR"
	,	"PASS"			//cunilogEvtSeverityPass		11
	,	"FAIL"
	,	"CRIT"
	,	"FATAL"
	,	"DEBUG"
	,	"TRACE"
	,	"DETAI"
	,	"VERBO"
	,	"ILLEG"			// cunilogEvtSeverityIllegal	18
};
static const char *EventSeverityTexts9 [] =
{
		""				// cunilogEvtSeverityNone		 0
	,	""				// cunilogEvtSeverityNonePass	 1
	,	""				// cunilogEvtSevertiyNoneFail	 2
	,	""				// cunilogEvtSevertiyNoneWarn	 3
	,	"         "		// cunilogEvtSeverityBlanks		 4
	,	"EMERGENCY"		// cunilogEvtSeverityEmergency	 5
	,	"NOTICE   "		// cunilogEvtSeverityNotice		 6
	,	"INFO     "
	,	"MESSAGE  "
	,	"WARNING  "
	,	"ERROR    "
	,	"PASS     "		// cunilogEvtSeverityPass		11
	,	"FAIL     "
	,	"CRITICAL "
	,	"FATAL    "
	,	"DEBUG    "
	,	"TRACE    "
	,	"DETAIL   "
	,	"VERBOSE  "
	,	"ILLEGAL  "		// cunilogEvtSeverityIllegal	18
};
static const char *EventSeverityTexts9tgt [] =
{
		""				// cunilogEvtSeverityNone		 0
	,	""				// cunilogEvtSeverityNonePass	 1
	,	""				// cunilogEvtSevertiyNoneFail	 2
	,	""				// cunilogEvtSeverityBlanks		 3
	,	"EMERGENCY"		// cunilogEvtSeverityEmergency	 4
	,	"NOTICE"		// cunilogEvtSeverityNotice		 5
	,	"INFO"
	,	"MESSAGE"
	,	"WARNING"
	,	"ERROR"
	,	"PASS"			// cunilogEvtSeverityPass		10
	,	"FAIL"
	,	"CRITICAL"
	,	"FATAL"
	,	"DEBUG"
	,	"TRACE"
	,	"DETAIL"
	,	"VERBOSE"
	,	"ILLEGAL"		// cunilogEvtSeverityIllegal	17
};

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
STRANSICOLOURSEQUENCE evtSeverityColours [cunilogEvtSeverityXAmountEnumValues] =
{
		{"",	0}														// cunilogEvtSeverityNone		 0
	,	{STR_ANSI_FGCOL_BRIGHT_GREEN,	LEN_ANSI_FGCOL_BRIGHT_GREEN}	// cunilogEvtSeverityNonePass	 1
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSevertiyNoneFail	 2
	,	{STR_ANSI_FGCOL_BRIGHT_MAGENTA,	LEN_ANSI_FGCOL_BRIGHT_MAGENTA}	// cunilogEvtSeverityNoneWarn	 3
	,	{"",	0}														// cunilogEvtSeverityBlanks		 4
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSeverityEmergency	 5
	,	{"",	0}														// cunilogEvtSeverityNotice		 6
	,	{"",	0}														// cunilogEvtSeverityInfo		 7
	,	{"",	0}														// cunilogEvtSeverityMessage	 8
	,	{STR_ANSI_FGCOL_BRIGHT_MAGENTA,	LEN_ANSI_FGCOL_BRIGHT_MAGENTA}	// cunilogEvtSeverityWarning	 9
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSeverityError		10
	,	{STR_ANSI_FGCOL_BRIGHT_GREEN,	LEN_ANSI_FGCOL_BRIGHT_GREEN}	// cunilogEvtSeverityPass		11
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSeverityFail		12
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSeverityCritical	13
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSeverityFatal		14
	,	{"",	0}														// cunilogEvtSeverityDebug		15
	,	{"",	0}														// cunilogEvtSeverityTrace		16
	,	{"",	0}														// cunilogEvtSeverityDetail		17
	,	{"",	0}														// cunilogEvtSeverityVerbose	18
	,	{STR_ANSI_FGCOL_BRIGHT_RED,		LEN_ANSI_FGCOL_BRIGHT_RED}		// cunilogEvtSeverityIllegal	19
																		// cunilogEvtSeverityXAmountEnumValues
};
#endif

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	static inline size_t evtSeverityColoursLen (cueventseverity sev)
	{
		ubf_assert (0 <= sev);
		ubf_assert (sev < cunilogEvtSeverityXAmountEnumValues);

		size_t len = 0;
		len += evtSeverityColours [sev].lnColSequence;
		if (len)
			len += LEN_ANSI_RESET;
		return len;
	}
#else
	#define evtSeverityColoursLen(sev) (0)
#endif

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	static inline void cpyEvtSeverityColour (char **sz, cueventseverity sev)
	{
		ubf_assert_non_NULL	(sz);
		ubf_assert_non_NULL	(*sz);
		ubf_assert			(0 <= sev);
		ubf_assert			(sev < cunilogEvtSeverityXAmountEnumValues);

		if (evtSeverityColours [sev].lnColSequence)
		{
			memcpy (*sz, evtSeverityColours [sev].szColSequence, evtSeverityColours [sev].lnColSequence);
			*sz += evtSeverityColours [sev].lnColSequence;
		}
	}
	static inline void cpyRstEvtSeverityColour (char **sz, cueventseverity sev)
	{
		if (evtSeverityColours [sev].lnColSequence)
		{
			memcpy (*sz, STR_ANSI_RESET, LEN_ANSI_RESET);
			*sz += LEN_ANSI_RESET;
		}
	}
#else
	#define cpyEvtSeverityColour(s, sev)
	#define cpyRstEvtSeverityColour(s)
#endif

static inline size_t requiredEventSeverityChars (cueventseverity sev, cueventsevfmtpy tpy)
{
	// "" or "INF" + " ".
	if (cunilogEvtSeverityBlanks > sev)
			return 0;
	switch (tpy)
	{														// The + 1 is for a space character.
		case cunilogEvtSeverityTypeChars3:					return 3 + 1;
		case cunilogEvtSeverityTypeChars5:					return 5 + 1;
		case cunilogEvtSeverityTypeChars9:					return 9 + 1;
		case cunilogEvtSeverityTypeChars3InBrackets:		return 2 + 3 + 1;
		case cunilogEvtSeverityTypeChars5InBrackets:		return 2 + 5 + 1;
		case cunilogEvtSeverityTypeChars9InBrackets:		return 2 + 9 + 1;
		case cunilogEvtSeverityTypeChars5InTightBrackets:	return 2 + 5 + 1;
		case cunilogEvtSeverityTypeChars9InTightBrackets:	return 2 + 9 + 1;
	}
	ubf_assert_msg (false, "Internal error! We should never get here!");
	return 0;
}

static inline size_t writeEventSeverity (char *szOut, cueventseverity sev, cueventsevfmtpy tpy)
{
	ubf_assert_non_NULL (szOut);
	ubf_assert (0 <= sev);
	ubf_assert (cunilogEvtSeverityXAmountEnumValues > sev);

	if (cunilogEvtSeverityBlanks > sev)
			return 0;

	size_t len;

	switch (tpy)
	{
		case cunilogEvtSeverityTypeChars3:					// "EMG"
			memcpy (szOut, EventSeverityTexts3 [sev], 3);
			szOut [3] = ' ';
			return 3 + 1;
		case cunilogEvtSeverityTypeChars5:					// "EMRGY"
			memcpy (szOut, EventSeverityTexts5 [sev], 5);
			szOut [5] = ' ';
			return 5 + 1;
		case cunilogEvtSeverityTypeChars9:					// "EMERGENCY"
			memcpy (szOut, EventSeverityTexts9 [sev], 9);
			szOut [9] = ' ';
			return 9 + 1;
		case cunilogEvtSeverityTypeChars3InBrackets:		// "[EMG]"
			*szOut ++ = '[';
			memcpy (szOut, EventSeverityTexts3 [sev], 3);
			memcpy (szOut + 3, "] ", 2);
			return 2 + 3 + 1;
		case cunilogEvtSeverityTypeChars5InBrackets:		// "[FAIL ]"
			*szOut ++ = '[';
			memcpy (szOut, EventSeverityTexts5 [sev], 5);
			memcpy (szOut + 5, "] ", 2);
			return 2 + 5 + 1;
		case cunilogEvtSeverityTypeChars9InBrackets:		// "[FAIL     ]"
			*szOut ++ = '[';
			memcpy (szOut, EventSeverityTexts9 [sev], 9);
			memcpy (szOut + 9, "] ", 2);
			return 2 + 9 + 1;
		case cunilogEvtSeverityTypeChars5InTightBrackets:
			len = strlen (EventSeverityTexts5tgt [sev]);
			ubf_assert (len <= 5);
			*szOut ++ = '[';
			memcpy (szOut, EventSeverityTexts5tgt [sev], len);
			memcpy (szOut + len, "] ", 2);
			memset (szOut + len + 2, ' ', 5 - len);
			return 2 + 5 + 1;
		case cunilogEvtSeverityTypeChars9InTightBrackets:
			len = strlen (EventSeverityTexts9tgt [sev]);
			ubf_assert (len <= 9);
			*szOut ++ = '[';
			memcpy (szOut, EventSeverityTexts9tgt [sev], len);
			memcpy (szOut + len, "] ", 2);
			memset (szOut + len + 2, ' ', 9 - len);
			return 2 + 9 + 1;
	}
	ubf_assert_msg (false, "Internal error! We should never get here!");
	return 0;
}

static inline size_t requiredFullstopChars (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);

	return cunilogIsEventAutoFullstop (pev) ? 1 : 0;
};

static inline size_t writeFullStop (char *szOut, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (szOut);
	ubf_assert_non_NULL (pev);

	if (cunilogIsEventAutoFullstop (pev))
	{
		if (pev->lenDataToLog && '.' != pev->szDataToLog [pev->lenDataToLog - 1])
		{
			szOut [0] = '.';
			return 1;
		}
	}
	return 0;
}

static inline size_t eventLenNewline (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

	return lnLineEnding (pev->pCUNILOG_TARGET->unilogNewLine);
}

static inline enum enLineEndings eventLineEnding (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

	return pev->pCUNILOG_TARGET->unilogNewLine;
}

static inline void evtTSFormats_unilogEvtTS_ISO8601 (char *chISO, UBF_TIMESTAMP ts)
{
	ISO8601_from_UBF_TIMESTAMPc (chISO, ts);
	chISO [LEN_ISO8601DATETIMESTAMPMS]		= ' ';
}

static inline void evtTSFormats_unilogEvtTS_ISO8601T (char *chISO, UBF_TIMESTAMP ts)
{
	ISO8601T_from_UBF_TIMESTAMPc (chISO, ts);
	chISO [LEN_ISO8601DATETIMESTAMPMS]		= ' ';
}

static inline void evtTSFormats_unilogEvtTS_ISO8601_3spc (char *chISO, UBF_TIMESTAMP ts)
{
	ISO8601_from_UBF_TIMESTAMPc (chISO, ts);
	chISO [LEN_ISO8601DATETIMESTAMPMS]		= ' ';
	chISO [LEN_ISO8601DATETIMESTAMPMS + 1]	= ' ';
	chISO [LEN_ISO8601DATETIMESTAMPMS + 2]	= ' ';
}

static inline void evtTSFormats_unilogEvtTS_ISO8601T_3spc (char *chISO, UBF_TIMESTAMP ts)
{
	ISO8601T_from_UBF_TIMESTAMPc (chISO, ts);
	chISO [LEN_ISO8601DATETIMESTAMPMS]		= ' ';
	chISO [LEN_ISO8601DATETIMESTAMPMS + 1]	= ' ';
	chISO [LEN_ISO8601DATETIMESTAMPMS + 2]	= ' ';
}

static inline void evtTSFormats_unilogEvtTS_NCSADT (char *chNCSADT, UBF_TIMESTAMP ts)
{
	NCSADATETIME_from_UBF_TIMESTAMP (chNCSADT, ts);
}

/*
	Structure for the event timestamp table.
	First member is the length that'll be written; second member is a pointer to the
	function that is going to write this out.
*/
typedef struct seventTSformats
{
	size_t			len;									// Required length.
	void			(*fnc) (char *, UBF_TIMESTAMP);			// Function pointer.
} SeventTSformats;

SeventTSformats evtTSFormats [cunilogEvtTS_AmountEnumValues] =
{
		{	// unilogEvtTS_ISO8601
			LEN_ISO8601DATETIMESTAMPMS + 1,
			evtTSFormats_unilogEvtTS_ISO8601				// "YYYY-MM-DD HH:MI:SS.000+01:00 ".
		}
	,	{	// unilogEvtTS_ISO8601T
			LEN_ISO8601DATETIMESTAMPMS + 1,
			evtTSFormats_unilogEvtTS_ISO8601T				// "YYYY-MM-DDTHH:MI:SS.000+01:00 ".
		}
	,	{	// unilogEvtTS_ISO8601_3spc
			LEN_ISO8601DATETIMESTAMPMS + 3,
			evtTSFormats_unilogEvtTS_ISO8601_3spc			// "YYYY-MM-DD HH:MI:SS.000+01:00   ".
		}
	,	{	// unilogEvtTS_ISO8601T_3spc
			LEN_ISO8601DATETIMESTAMPMS + 3,
			evtTSFormats_unilogEvtTS_ISO8601T_3spc			// "YYYY-MM-DDTHH:MI:SS.000+01:00   ".
		}
	,	{	// cunilogEvtTS_NCSADT
			LEN_NCSA_COMMON_LOG_DATETIME + 1,				// "[10/Oct/2000:13:55:36 -0700] ".
			evtTSFormats_unilogEvtTS_NCSADT
		}
};

static inline size_t requiredEvtLineTimestampAndSeverityLength (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

	size_t	r;

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " ".
	r = evtTSFormats [pev->pCUNILOG_TARGET->unilogEvtTSformat].len;
	// "WRN" + " "
	r += requiredEventSeverityChars (pev->evSeverity, pev->pCUNILOG_TARGET->evSeverityType);

	return r;
}

static inline size_t requiredEventLineSizeU8 (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	ubf_assert (cunilogEvtTypeNormalText == pev->evType);

	size_t	r;

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " " + "WRN" + " ".
	r = requiredEvtLineTimestampAndSeverityLength (pev);
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// Actual data.
	r += pev->lenDataToLog;
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// "."
	r += requiredFullstopChars (pev);
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// CR + LF max.
	r += eventLenNewline (pev);
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// Terminating NUL.
	r += 1;
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	return r;
}

/*
	writeEventLineFromSUNILOGEVENTU8

	The caller is responsible for szEventLine to point to a buffer big enough to hold the
	event line. The function requiredEventLineSize () obtains this size.
*/
static size_t writeEventLineFromSUNILOGEVENTU8 (char *szEventLine, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (szEventLine);
	ubf_assert_non_NULL (pev);
	ubf_assert (cunilogEvtTypeNormalText == pev->evType);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised (pev->pCUNILOG_TARGET));

	char	*szOrg = szEventLine;

	DBG_RESET_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker);

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " " (see table above).
	evtTSFormats [pev->pCUNILOG_TARGET->unilogEvtTSformat].fnc (szEventLine, pev->stamp);
	//ISO8601_from_UBF_TIMESTAMP (szEventLine, pue->stamp);

	szEventLine += evtTSFormats [pev->pCUNILOG_TARGET->unilogEvtTSformat].len;
	szEventLine += writeEventSeverity (szEventLine, pev->evSeverity, pev->pCUNILOG_TARGET->evSeverityType);
	DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, szEventLine - szOrg);

	memcpy (szEventLine, pev->szDataToLog, pev->lenDataToLog);
	szEventLine += pev->lenDataToLog;
	DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, szEventLine - szOrg);

	szEventLine += writeFullStop (szEventLine, pev);
	DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, szEventLine - szOrg);

	// We've reserved space for a new line character sequence in requiredEventLineSizeU8 ()
	//	but we're not going to add this here yet. Instead, we NUL-terminate. This simply lets
	//	us call puts (). We'll add the new line sequence later in the processor that writes
	//	to the logfile.

	// The NUL byte is useful for OS API functions.
	szEventLine [0] = ASCII_NUL;
	return szEventLine - szOrg;
}

/*
static bool obtainValidSCUNILOGDUMPinCUNILOG_TARGET (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	if (NULL == put->psdump)
	{
		put->psdump = ubf_malloc (sizeof (SCUNILOGDUMP));
		SCUNILOGDUMP *pd = put->psdump;
		if (pd)
		{
			pd->dump_prs = ubf_malloc (sizeof (SHEX_DUMP_PARS));
			pd->dump_sns = ubf_malloc (sizeof (SHEX_DUMP_SAN));
			if (pd->dump_prs && pd->dump_sns)
			{
				ubf_data_dump_def_SUBF_DUMP_PARS (pd->dump_prs);
				SHEX_DUMP_SAN *ps = pd->dump_sns;
				ps->bInitialised = false;
				return true;
			} else
			{
				if (NULL != pd->dump_prs)
					ubf_free (pd->dump_prs);
				if (NULL != pd->dump_sns)
					ubf_free (pd->dump_sns);
				pd->dump_prs = NULL;
				pd->dump_sns = NULL;
			}
		}
		return false;
	} else
		return true;
}
*/

static inline size_t widthOfCaptionLengthFromCunilogEventType (cueventtype type)
{
	switch (type)
	{
		case cunilogEvtTypeNormalText:				return 0;
		case cunilogEvtTypeCommand:					return 0;
		case cunilogEvtTypeHexDumpWithCaption8:		return 1;
		case cunilogEvtTypeHexDumpWithCaption16:	return 2;
		case cunilogEvtTypeHexDumpWithCaption32:	return 4;
		case cunilogEvtTypeHexDumpWithCaption64:	return 8;
		default:									return 0;
	}
}

static size_t readCaptionLengthFromData (unsigned char *pData, size_t ui)
{
	uint8_t			ui8;
	uint16_t		ui16;
	uint32_t		ui32;
	uint64_t		ui64;
	size_t			lnRet;

	switch (ui)
	{
		case 0:	lnRet = 0;									break;
		case 1:	memcpy (&ui8, pData, ui);	lnRet = ui8;	break;
		case 2:	memcpy (&ui16, pData, ui);	lnRet = ui16;	break;
		case 4:	memcpy (&ui32, pData, ui);	lnRet = ui32;	break;
		case 8:	
				ubf_assert_msg (false, "Really??? A caption length of more than 4 GiB??");
				memcpy (&ui64, pData, ui);
				lnRet = (size_t) ui64;						break;
		default:
				ubf_assert_msg (false, "Bug");
				lnRet = 0;									break;
	}
	return lnRet;
}

static char		scSummaryOctets []	= " octets/bytes.";
static size_t	lnSummaryOctets		= sizeof (scSummaryOctets) - 1;

static inline size_t requiredEventLineSizeHexDump	(
						unsigned char		**pDumpData,
						size_t				*width,
						size_t				*len,
						CUNILOG_EVENT		*pev
													)
{
	ubf_assert_non_NULL (pev);
	ubf_assert	(
						cunilogEvtTypeHexDumpWithCaption8	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption16	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption32	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption64	== pev->evType
				);
	ubf_assert_non_NULL (pDumpData);
	ubf_assert_non_NULL (width);
	ubf_assert_non_NULL (len);

	CUNILOG_TARGET *put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	size_t	r;

	/*
		Timestamp + Type + caption, etc.
	*/

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " " + "WRN" + " ".
	r = requiredEvtLineTimestampAndSeverityLength (pev);
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// The width of the caption length.
	size_t ui			= widthOfCaptionLengthFromCunilogEventType (pev->evType);
	// Its actual length. This needs to be added to our return value.
	size_t lenCaption	= readCaptionLengthFromData (pev->szDataToLog, ui);
	*pDumpData			= pev->szDataToLog + ui + lenCaption;
	*width				= ui;
	*len				= lenCaption;
	r += lenCaption;
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// "."
	r += requiredFullstopChars (pev);
	// New line.
	r += eventLenNewline (pev);
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// Actual dump data size. Includes NUL terminator.
	size_t sizHexDmp = hxdmpRequiredSize (pev->lenDataToLog, put->dumpWidth, eventLineEnding (pev));
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, sizHexDmp);
	r += sizHexDmp;
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// ASCII TAB.
	++ r;

	// To be considered in the future:
	//	It would be faster to just always reserve UBF_UINT64_LEN octets instead of
	//	performing the uint -> ASCII transformation.
	char cDmpOctets [UBF_UINT64_SIZE];
	//r += ubf_str_from_uint64 (cDmpOctets, pev->lenDataToLog);
	ubf_str__from_uint64 (cDmpOctets, 10, pev->lenDataToLog);
	r += 10;
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	r += lnSummaryOctets;
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	// New line.
	r += eventLenNewline (pev);
	DBG_TRACK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, r);

	#ifdef DEBUG
		++ r;												// Space for a debug marker.
	#endif

	return r;
}

static size_t createDumpEventLineFromSUNILOGEVENT (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	ubf_assert (isInitialisedSMEMBUF (&pev->pCUNILOG_TARGET->mbLogEventLine));
	ubf_assert	(
						cunilogEvtTypeHexDumpWithCaption8	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption16	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption32	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption64	== pev->evType
				);

	CUNILOG_TARGET *put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	unsigned char	*pDumpData;
	size_t			captionWidth;
	size_t			captionLen;
	size_t lenTotal = requiredEventLineSizeHexDump (&pDumpData, &captionWidth, &captionLen, pev);
	// pDumpData				Points to the data to dump.
	// pev->lenDataToLog		Its length.

	growToSizeSMEMBUF64aligned (&put->mbLogEventLine, lenTotal);
	if (isUsableSMEMBUF (&put->mbLogEventLine))
	{
		#ifdef DEBUG
			put->mbLogEventLine.buf.pch [lenTotal] = CUNILOG_DEFAULT_DBG_CHAR;
		#endif
		char *szOut = put->mbLogEventLine.buf.pch;
		char *szOrg = szOut;

		// Timestamp + severity.
		evtTSFormats [put->unilogEvtTSformat].fnc (szOut, pev->stamp);
		szOut += evtTSFormats [put->unilogEvtTSformat].len;
		szOut += writeEventSeverity (szOut, pev->evSeverity, put->evSeverityType);
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, szOut - szOrg);

		// Caption.
		memcpy (szOut, pev->szDataToLog + captionWidth, captionLen);
		szOut += captionLen;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, szOut - szOrg);

		// "." + new line.
		size_t lenNewLine = eventLenNewline (pev);
		szOut += writeFullStop (szOut, pev);
		memcpy (szOut, ccLineEnding (eventLineEnding (pev)), lenNewLine);
		szOut += lenNewLine;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, szOut - szOrg);

		put->lnLogEventLine = szOut - szOrg;
		char *szHexDmpOut = szOut;
		size_t sizHx = hxdmpWriteHexDump	(
						szHexDmpOut, pDumpData, pev->lenDataToLog,
						put->dumpWidth, put->unilogNewLine
											);
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, sizHx + 1);
		ubf_assert (CUNILOG_DEFAULT_DBG_CHAR == put->mbLogEventLine.buf.pch [lenTotal]);
		put->lnLogEventLine += sizHx;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, put->lnLogEventLine + 1);

		szOut = szHexDmpOut + sizHx;
		szOut [0] = ASCII_TAB;
		++ szOut;
		++ put->lnLogEventLine;

		//size_t lnOctets = ubf_str_from_uint64 (szOut, pev->lenDataToLog);
		size_t lnOctets = 10;
		ubf_str__from_uint64 (szOut, 10, pev->lenDataToLog);
		put->lnLogEventLine += lnOctets;
		ubf_assert (CUNILOG_DEFAULT_DBG_CHAR == put->mbLogEventLine.buf.pch [lenTotal]);
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, put->lnLogEventLine + 1);

		szOut += lnOctets;
		memcpy (szOut, scSummaryOctets, lnSummaryOctets + 1);
		put->lnLogEventLine += lnSummaryOctets;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker, put->lnLogEventLine + 1);

		return put->lnLogEventLine;
	}
	return CUNILOG_SIZE_ERROR;
}

static size_t createU8EventLineFromSUNILOGEVENT (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	ubf_assert (isInitialisedSMEMBUF (&pev->pCUNILOG_TARGET->mbLogEventLine));
	ubf_assert (cunilogEvtTypeNormalText == pev->evType);

	size_t requiredEvtLineSize;

	requiredEvtLineSize = requiredEventLineSizeU8 (pev);
	growToSizeSMEMBUF64aligned (&pev->pCUNILOG_TARGET->mbLogEventLine, requiredEvtLineSize);
	if (isUsableSMEMBUF (&pev->pCUNILOG_TARGET->mbLogEventLine))
	{
		pev->pCUNILOG_TARGET->lnLogEventLine =
			writeEventLineFromSUNILOGEVENTU8 (pev->pCUNILOG_TARGET->mbLogEventLine.buf.pch, pev);
		return pev->pCUNILOG_TARGET->lnLogEventLine;
	}
	return CUNILOG_SIZE_ERROR;
}

static size_t createEventLineFromSUNILOGEVENT (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	ubf_assert (isInitialisedSMEMBUF (&pev->pCUNILOG_TARGET->mbLogEventLine));

	DBG_RESET_CNTTRACKER (pev->pCUNILOG_TARGET->evtLineTracker);

	switch (pev->evType)
	{
		case cunilogEvtTypeNormalText:
			return createU8EventLineFromSUNILOGEVENT	(pev);
	#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
		case cunilogEvtTypeCommand:
			ubf_assert_msg (false, "Cunilog bug! This function is not to be called in this case!");
			break;
	#endif
		case cunilogEvtTypeHexDumpWithCaption8:
		case cunilogEvtTypeHexDumpWithCaption16:
		case cunilogEvtTypeHexDumpWithCaption32:
		case cunilogEvtTypeHexDumpWithCaption64:
			return createDumpEventLineFromSUNILOGEVENT	(pev);
		default:
			break;
	}
	return CUNILOG_SIZE_ERROR;
}

/*
	Not to be called with 0 == ui.
*/
static inline void storeCaptionLength (unsigned char **pData, size_t ui, size_t lenCapt)
{
	ubf_assert_non_NULL (pData);
	ubf_assert_non_NULL (*pData);
	ubf_assert_non_0	(ui);

	uint8_t			ui8;
	uint16_t		ui16;
	uint32_t		ui32;
	uint64_t		ui64;

	switch (ui)
	{
		/*
		// We're not being called for 0 == ui.
		case 0:
			ubf_assert_msg (false, "Must be a bug!");
			return;
		*/
		case 1:
			ui8 = (uint8_t) (lenCapt & 0xFF);
			memcpy (*pData, &ui8, ui);
			break;
		case 2:
			ui16 = (uint16_t) (lenCapt & 0xFFFF);
			memcpy (*pData, &ui16, ui);
			break;
		case 4:
			ui32 = (uint32_t) (lenCapt & 0xFFFFFFFF);
			memcpy (*pData, &ui32, ui);
			break;
		case 8:
			ubf_assert_msg (false, "Really??? A caption length of more than 4 GiB??");
			ui64 = (uint64_t) lenCapt;
			memcpy (*pData, &ui64, ui);
			break;
		default:
			ubf_assert_msg (false, "Must be a bug!");
			break;
	}
	*pData += ui;
}

/*
	Note that ccData can be NULL for event type cunilogEvtTypeCommand,
	in which case a buffer of siz octets is reserved but not initialised!
*/
static CUNILOG_EVENT *CreateCUNILOG_EVENTandData	(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccCapt,
					size_t						lenCapt,
					cueventtype					type,
					const char					*ccData,
					size_t						siz
													)
{
	ubf_assert_non_NULL	(put);
	if (ccData)
		ubf_assert (cunilogEvtTypeCommand != type && NULL != ccData);
	else
		ubf_assert (cunilogEvtTypeCommand == type && NULL == ccData);
	ubf_assert			(USE_STRLEN != siz);
	ubf_assert			(0 <= type);
	ubf_assert			(cunilogEvtTypeAmountEnumValues > type);

	size_t			wl		= widthOfCaptionLengthFromCunilogEventType (type);
	ubf_assert (wl || 0 == lenCapt);						// If 0 == wl we can't have a caption.
	size_t			aln		= ALIGNED_SIZE (sizeof (CUNILOG_EVENT), CUNILOG_DEFAULT_ALIGNMENT);
	size_t			ln		= aln + wl + lenCapt + siz;
	CUNILOG_EVENT	*pev	= ubf_malloc (ln);

	if (pev)
	{
		unsigned char *pData = (unsigned char *) pev + aln;
		
		if	(	
					cunilogHasEnqueueTimestamps	(put)
				&&	HAS_CUNILOG_TARGET_A_QUEUE	(put)
			)
		{
			FillCUNILOG_EVENT	(
				pev, put,
				CUNILOGEVENT_ALLOCATED,
				0,
				sev, type,
				pData, siz, ln
								);
		} else
		{
			FillCUNILOG_EVENT	(
				pev, put,
				CUNILOGEVENT_ALLOCATED,
				LocalTime_UBF_TIMESTAMP (),
				sev, type,
				pData, siz, ln
								);
		}
		if (wl)
		{
			storeCaptionLength (&pData, wl, lenCapt);
			memcpy (pData, ccCapt, lenCapt);
			pData += lenCapt;
		}
		if (ccData)
			memcpy (pData, ccData, siz);
		else
			ubf_assert (cunilogEvtTypeCommand == type);
	}
	return pev;
}

static inline cueventtype cunilogEventTypeFromLength (size_t len)
{
	ubf_assert (USE_STRLEN != len);

	if (len < UINT8_MAX)
		return cunilogEvtTypeHexDumpWithCaption8;
	if (len < UINT16_MAX)
		return cunilogEvtTypeHexDumpWithCaption16;
	if (len < UINT32_MAX)
		return cunilogEvtTypeHexDumpWithCaption32;
	ubf_assert_msg (false, "Really??? A caption length of more than 4 GiB??");
	return cunilogEvtTypeHexDumpWithCaption64;
}

CUNILOG_EVENT *CreateCUNILOG_EVENT_Data		(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz,
					const char					*ccCapt,
					size_t						lenCapt
											)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(ccData);
	ubf_assert (USE_STRLEN != siz);

	if (ccCapt)
		lenCapt = USE_STRLEN == lenCapt ? strlen (ccCapt) : lenCapt;
	else
		lenCapt = 0;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENTandData	(
							put, sev, ccCapt, lenCapt,
							cunilogEventTypeFromLength (lenCapt),
							ccData, siz
													);
	return pev;
}

CUNILOG_EVENT *CreateCUNILOG_EVENT_Text		(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
{
	ubf_assert_non_NULL (put);
	ubf_assert_non_NULL (ccText);

	len = USE_STRLEN == len ? strlen (ccText) : len;

	while (len && ('\n' == ccText [len - 1] || '\r' == ccText [len - 1]))
		-- len;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENTandData	(
							put, sev, NULL, 0, cunilogEvtTypeNormalText,
							ccText, len
													);
	return pev;
}

CUNILOG_EVENT *CreateSUNILOGEVENT_W	(
					cueventseverity		sev,
					size_t				lenDataW
									)
{
	UNREFERENCED_PARAMETER (sev);
	UNREFERENCED_PARAMETER (lenDataW);

	//return CreateSUNILOGSTRUCT_U8 (evType, lenDataW * sizeof (wchar_t));
	ubf_assert (false);
	return NULL;
}

CUNILOG_EVENT *DuplicateCUNILOG_EVENT (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);

	size_t size;

	if (pev->sizEvent)
		size = pev->sizEvent;
	else
		size = sizeof (CUNILOG_EVENT);
	CUNILOG_EVENT *pnev = ubf_malloc (size);
	if (pnev)
	{
		memcpy (pnev, pev, size);
		cunilogSetEventAllocated (pnev);
	}
	return pnev;
}

CUNILOG_EVENT *DoneCUNILOG_EVENT (CUNILOG_TARGET *put, CUNILOG_EVENT *pev)
{
	if (NULL == put || put == pev->pCUNILOG_TARGET)
	{
		if (pev->szDataToLog && cunilogIsEventDataAllocated (pev))
		{
			ubf_free (pev->szDataToLog);
		}
		if (cunilogIsEventAllocated (pev))
		{
			ubf_free (pev);
		}
	}
	return NULL;
}

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline CUNILOG_EVENT *DequeueAllCUNILOG_EVENTs (CUNILOG_TARGET *put);
#endif

#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	void cunilogSetTargetErrorAndInvokeErrorCallback	(
				int64_t cunilog_error, CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev
														)
	{
		ubf_assert_non_NULL (cup);
		ubf_assert_non_NULL (pev);
		ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

		#ifdef PLATFORM_IS_WINDOWS
			DWORD syserror = GetLastError ();
		#else
			int32_t syserror = errno;
		#endif
		SetCunilogError (pev->pCUNILOG_TARGET->error, cunilog_error, syserror);

		if (pev->pCUNILOG_TARGET->errorCB)
		{
			errCBretval rv = pev->pCUNILOG_TARGET->errorCB (pev->pCUNILOG_TARGET->error, cup, pev);
			ubf_assert (0 <= rv);
			ubf_assert (cunilogErrCB_AmountEnumValues > rv);

			CUNILOG_EVENT *pve;
			CUNILOG_EVENT *nxt;

			switch (rv)
			{
				case cunilogErrCB_next_processor:
					break;
				case cunilogErrCB_next_event:
					cunilogSetEventStopProcessing (pev);
					break;
				case cunilogErrCB_shutdown:
					cunilogSetShutdownTarget (pev->pCUNILOG_TARGET);
					break;
				case cunilogErrCB_cancel:
					cunilogSetShutdownTarget (pev->pCUNILOG_TARGET);
					#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
						pve = DequeueAllCUNILOG_EVENTs (pev->pCUNILOG_TARGET);
						while (pve)
						{
							nxt = pve->next;
							DoneCUNILOG_EVENT (NULL, pve);
							pve = nxt;
						}
					#endif
					break;
				default:
					ubf_assert (false);
					break;
			}
		}
	}
#else
	#define cunilogInvokeErrorCallback(error, cup, pev)
#endif

/*
	The dummy/no-operation processor.
*/
static bool cunilogProcessNoneFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	UNREFERENCED_PARAMETER (cup);
	UNREFERENCED_PARAMETER (pev);

	return true;
}

#ifdef PLATFORM_IS_WINDOWS
	static inline int cunilogPutsWin (const char *szOutput, size_t len)
	{
		if (cunilogConsoleIsUninitialised == ourCunilogConsoleOutputCodePage)
			CunilogSetConsoleTo (cunilogConsoleIsUTF8);
		CunilogEnableANSIifNotInitialised ();

		if (len)
		{	// This function expects a NUL-terminated string.
			ubf_assert (strlen (szOutput) == len);
			ubf_assert (ASCII_NUL == szOutput [len]);

			switch (ourCunilogConsoleOutputCodePage)
			{
				case cunilogConsoleIsUTF8:		return puts					(szOutput);
				case cunilogConsoleIsUTF16:		return putsU8toU16stdout	(szOutput);
				case cunilogConsoleIsNeither:	return puts					(szOutput);
				default:						return puts					(szOutput);
			}
		} else
		{
			switch (ourCunilogConsoleOutputCodePage)
			{
				case cunilogConsoleIsUTF8:		return puts					("");
				case cunilogConsoleIsUTF16:		return putsU8toU16stdout	("");
				case cunilogConsoleIsNeither:	return puts					("");
				default:						return puts					("");
			}
		}
	}
#endif

#ifdef PLATFORM_IS_WINDOWS
	static inline int cunilogPrintWin (const char *szOutput, size_t len)
	{
		if (cunilogConsoleIsUninitialised == ourCunilogConsoleOutputCodePage)
			CunilogSetConsoleTo (cunilogConsoleIsUTF8);
		CunilogEnableANSIifNotInitialised ();

		if (len)
		{	// This function expects a NUL-terminated string.
			ubf_assert (strlen (szOutput) == len);
			ubf_assert (ASCII_NUL == szOutput [len]);

			switch (ourCunilogConsoleOutputCodePage)
			{
				case cunilogConsoleIsUTF8:		return printf				(szOutput);
				case cunilogConsoleIsUTF16:		return fprintfU8toU16stream	(stdout, szOutput);
				case cunilogConsoleIsNeither:	return printf				(szOutput);
				default:						return printf				(szOutput);
			}
		} else
		{
			switch (ourCunilogConsoleOutputCodePage)
			{
				case cunilogConsoleIsUTF8:		return printf				("");
				case cunilogConsoleIsUTF16:		return fprintfU8toU16stream	(stdout, "");
				case cunilogConsoleIsNeither:	return printf				("");
				default:						return printf				("");
			}
		}
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	static inline void cunilogFillColouredEchoEvtLine	(
							char				**pszToOutput,
							size_t				*plnToOutput,
							CUNILOG_EVENT		*pev
														)
	{
		ubf_assert_non_NULL (pszToOutput);
		ubf_assert_non_NULL (plnToOutput);
		ubf_assert_non_NULL (pev);
		// Includes LEN_ANSI_RESET too.
		size_t	lnThisColour	= evtSeverityColoursLen (pev->evSeverity);

		if	(
					cunilogHasUseColourForEcho (pev->pCUNILOG_TARGET)
				&&	lnThisColour
			)
		{
			size_t	lnEvtLine		= pev->pCUNILOG_TARGET->lnLogEventLine;
			size_t	lnColEcho		= lnThisColour
									+ lnEvtLine
									;

			growToSizeSMEMBUF (&pev->pCUNILOG_TARGET->mbColEventLine, lnColEcho + 1);
			if (isUsableSMEMBUF (&pev->pCUNILOG_TARGET->mbColEventLine))
			{
				ubf_assert	(
									strlen (pev->pCUNILOG_TARGET->mbLogEventLine.buf.pch)
								==	pev->pCUNILOG_TARGET->lnLogEventLine
							);
				char *sz = pev->pCUNILOG_TARGET->mbColEventLine.buf.pch;
				cpyEvtSeverityColour (&sz, pev->evSeverity);
				memcpy (sz, pev->pCUNILOG_TARGET->mbLogEventLine.buf.pch, lnEvtLine);
				sz += lnEvtLine;
				cpyRstEvtSeverityColour (&sz, pev->evSeverity);
				*sz = ASCII_NUL;
				pev->pCUNILOG_TARGET->lnColEventLine = lnColEcho;
				*pszToOutput = pev->pCUNILOG_TARGET->mbColEventLine.buf.pch;
				*plnToOutput = lnColEcho;
				return;
			}
		}
		*pszToOutput = pev->pCUNILOG_TARGET->mbLogEventLine.buf.pch;
		*plnToOutput = pev->pCUNILOG_TARGET->lnLogEventLine;
	}
#endif

static bool cunilogProcessEchoFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	UNREFERENCED_PARAMETER (cup);
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

	if (cunilogIsNoEcho (pev->pCUNILOG_TARGET) || cunilogHasEventNoEcho (pev))
		return true;

	// The actual task of this processor: Echo the event line.
	//	Note that we can rely on the following conditions here:
	//		- The line to output is NUL-terminated.
	//		- It only consists of printable characters.
	//		- The length of the event line has been stored correctly.
	//		- If we require a lock, we have it already.

	int		ips;
	char	*szToOutput;
	size_t	lnToOutput;

	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
		cunilogFillColouredEchoEvtLine (&szToOutput, &lnToOutput, pev);
	#else
		szToOutput = pev->pCUNILOG_TARGET->mbLogEventLine.buf.pch;
		lnToOutput = pev->pCUNILOG_TARGET->lnLogEventLine;
	#endif

	#ifdef PLATFORM_IS_WINDOWS
		ips = cunilogPutsWin (szToOutput, lnToOutput);
	#else
		if (lnToOutput)
			ips = puts (szToOutput);
		else
			ips = puts ("");
	#endif
	if (EOF == ips)
	{	// "Bad file descriptor" might not be the best error here but what's better?
		ubf_assert_msg (false, "Error writing to stdout.");
		cunilogSetTargetErrorAndInvokeErrorCallback (EBADF, cup, pev);
	}
	return true;
}

static bool cunilogProcessUpdateLogFileNameFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{	UNREFERENCED_PARAMETER (cup);
	ubf_assert_non_NULL (pev);
	
	CUNILOG_TARGET	*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	#ifdef DEBUG
		char *sz = put->mbLogfileName.buf.pch;
		UNREFERENCED_PARAMETER (sz);
	#endif

	size_t lenPostfixStamp;

	switch (put->culogPostfix)
	{
		case cunilogPostfixDotNumberMinutely:
		case cunilogPostfixDotNumberHourly:
		case cunilogPostfixDotNumberDaily:
		case cunilogPostfixDotNumberWeekly:
		case cunilogPostfixDotNumberMonthly:
		case cunilogPostfixDotNumberYearly:
			return true;

		default:
			lenPostfixStamp = lenDateTimeStampFromPostfix (put->culogPostfix);
			ubf_assert (LEN_ISO8601DATEHOURANDMINUTE >= lenPostfixStamp);
			memcpy (put->cPrevDateTimeStamp, put->szDateTimeStamp, lenPostfixStamp);
			obtainDateAndTimeStamp (put->szDateTimeStamp, pev->stamp, put->culogPostfix);
			put->szDateTimeStamp [lenPostfixStamp] = '.';
			return true;
	}
}

/*
	Closes the previous file and opens the new one.
*/
static inline bool cunilogOpenNewLogFile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert			(isInitialisedSMEMBUF (&put->mbLogfileName));

	#ifdef OS_IS_WINDOWS
		CloseHandle (put->logfile.hLogFile);
		return cunilogOpenLogFile (put);
	#else
		fclose (put->logfile.fLogFile);
		return cunilogOpenLogFile (put);
	#endif
}

static inline bool requiresOpenLogFile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

#ifdef OS_IS_WINDOWS
		return NULL == put->logfile.hLogFile || INVALID_HANDLE_VALUE == put->logfile.hLogFile;
	#else
		return NULL == put->logfile.fLogFile;
	#endif
}

static inline bool requiresNewLogFile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	return memcmp	(
		put->cPrevDateTimeStamp, put->szDateTimeStamp,
		lenDateTimeStampFromPostfix (put->culogPostfix)
					);
}

static inline size_t addNewLineToLogEventLine (char *pData, size_t lnData, enum enLineEndings nl)
{	// At least one octet has been reserved for a newline character, and one
	//	for NUL, hence we're definitely safe to write 2 more octets.
	size_t len;
	const char *cc = szLineEnding (nl, &len);
	ubf_assert (len <= 2);
	memcpy (pData + lnData, cc, len + 1);
	return lnData + len;
}

static bool cunilogWriteDataToLogFile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	char				*pData	= put->mbLogEventLine.buf.pch;
	size_t				lnData	= put->lnLogEventLine;
	enum enLineEndings	nl		= put->unilogNewLine;

	#ifdef OS_IS_WINDOWS
		DWORD dwWritten;
		DWORD toWrite = addNewLineToLogEventLine (pData, lnData, nl) & 0xFFFFFFFF;
		// The file has been opened with FILE_APPEND_DATA, i.e. we don't need to
		//	seek ourselves.
		//	LARGE_INTEGER	z = {0, 0};
		//	SetFilePointerEx (pl->hLogFile, z, NULL, FILE_END);
		bool b = WriteFile (put->logfile.hLogFile, pData, toWrite, &dwWritten, NULL);
		pData [lnData] = ASCII_NUL;
		return b;
	#else
		long lToWrite = (long) addNewLineToLogEventLine (pData, lnData, nl);
		// See https://www.man7.org/linux/man-pages/man3/fopen.3.html .
		//	A call "fseek (pl->fLogFile, (long) 0, SEEK_END);" is not required
		//	because we opened the file in append mode.
		size_t st = fwrite (pData, 1, lToWrite, put->logfile.fLogFile);
		pData [lnData] = ASCII_NUL;
		return st == lnData;
	#endif
}

static bool cunilogProcessWriteToLogFileFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

	CUNILOG_TARGET	*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);
	ubf_assert (isUsableSMEMBUF (&put->mbLogfileName));

	if (cunilogHasDontWriteToLogfile (put))
		return true;

	/*
	CUNILOG_LOGFILE	*pl	= cup->pData;
	ubf_assert_non_NULL (pl);
	*/

	if (isUsableSMEMBUF (&put->mbLogfileName))
	{
		if (requiresOpenLogFile (put))
		{
			if (!cunilogOpenLogFile (put))
				cunilogSetTargetErrorAndInvokeErrorCallback (CUNILOG_ERROR_OPENING_LOGFILE, cup, pev);
		} else
		if (requiresNewLogFile (put))
		{
			if (!cunilogOpenNewLogFile (put))
				cunilogSetTargetErrorAndInvokeErrorCallback (CUNILOG_ERROR_OPENING_LOGFILE, cup, pev);
		}
		if (!cunilogWriteDataToLogFile (put))
				cunilogSetTargetErrorAndInvokeErrorCallback (CUNILOG_ERROR_WRITING_LOGFILE, cup, pev);
	}
	return true;
}

static bool cunilogProcessFlushFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	CUNILOG_TARGET	*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);
	
	if (cunilogHasDontWriteToLogfile (put))
		return true;

	#ifdef OS_IS_WINDOWS
		if (!FlushFileBuffers (put->logfile.hLogFile))
			cunilogSetTargetErrorAndInvokeErrorCallback (CUNILOG_ERROR_FLUSHING_LOGFILE, cup, pev);
	#else
		if (0 != fflush (put->logfile.fLogFile))
			cunilogInvokeErrorCallback (CUNILOG_ERROR_FLUSHING_LOGFILE, cup, pev);
	#endif
	return true;
}

static bool cunilogProcessEventSingleThreaded (CUNILOG_EVENT *pev);
static bool enqueueAndTriggerSeparateLoggingThread (CUNILOG_EVENT *pev);

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY

	static inline void IncrementPendingNoRotationEvents (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		++ put->nPendingNoRotEvts;
		//printf ("%" PRIu64 "\n", put->nPendingNoRotEvts);
	}
	static inline void DecrementPendingNoRotationEvents (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		-- put->nPendingNoRotEvts;
		//printf ("%" PRIu64 "\n", put->nPendingNoRotEvts);
	}
#else
	#define IncrementPendingNoRotationEvents(put)
	#define DecrementPendingNoRotationEvents(put)
#endif

static bool logFromInsideRotatorTextU8fmt (CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	size_t		len;
	bool		bRet = false;

	// We're supposed to be inside a rotator. This means we should have a
	//	CUNILOG_ROTATOR_ARGS structure set in our target. It also means
	//	we should have a cunilog processor. Its pData member points to a
	//	rotation data structure. Anything else is a bug.
	ubf_assert_non_NULL (put->prargs);
	ubf_assert_non_NULL (put->prargs->cup);
	ubf_assert_non_NULL (put->prargs->cup->pData);

	CUNILOG_ROTATION_DATA	*prd = put->prargs->cup->pData;
	ubf_assert_non_NULL (prd);

	/*
		prd->plogCUNILOG_TARGET == NULL		-> Log to current CUNILOG_TARGET (put) but
												without rotation (because we currently *are*
												within a rotation).
		prd->plogCUNILOG_TARGET == put		-> Bug, as this should be NULL.
		prd->plogCUNILOG_TARGET == <Anything else>
											-> Log to this CUNILOG_TARGET normally.
	*/
	ubf_assert (put != prd->plogCUNILOG_TARGET);
	if (prd->plogCUNILOG_TARGET && put != prd->plogCUNILOG_TARGET)
	{
		va_start (ap, fmt);
		bRet = logTextU8vfmt (put, fmt, ap);
		va_end (ap);
		return bRet;
	}

	va_start (ap, fmt);
	len = (size_t) vsnprintf (NULL, 0, fmt, ap);
	va_end (ap);

	char *szTxtToLog = ubf_malloc (len + 1);
	if (szTxtToLog)
	{
		va_start (ap, fmt);
		vsnprintf (szTxtToLog, len + 1, fmt, ap);
		va_end (ap);

		CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, cunilogEvtSeverityNone, szTxtToLog, len);
		ubf_assert_non_NULL (pev);
		if (pev)
		{
			cunilogSetEventNoRotation (pev);
			#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
				if (HAS_CUNILOG_TARGET_A_QUEUE (put))
				{
					IncrementPendingNoRotationEvents (put);
					enqueueAndTriggerSeparateLoggingThread (pev);
					bRet = true;
				} else
			#endif
					bRet = cunilogProcessEventSingleThreaded (pev);
		}
		ubf_free (szTxtToLog);
	}
	return bRet;
}

#ifdef OS_IS_WINDOWS
	static DWORD GetTextForLastError (char *szErrMsg)
	{
		ubf_assert_non_NULL (szErrMsg);

		// Note that we expect a buffer of CUNILOG_STD_MSG_SIZE octets.
		DWORD dwError = GetLastError ();
		GetWinErrorTextU8 (szErrMsg, CUNILOG_STD_MSG_SIZE, dwError);
		return dwError;
	}
#else
	static int GetTextForLastError (char *szErrMsg)
	{
		ubf_assert_non_NULL (szErrMsg);

		char szErr [] = "\"Not implemented\"";
		memcpy (szErrMsg, szErr, sizeof (szErr));
		return -1;
	}
#endif

/*
	Increments the dot number part of a filename, i.e. ".1234".
	Can also be "", which is the case for the original file.
	Assumes that there's always enough space available to write out
	the incremented value.

	Like:
	"file.log"		-> ""
	"file.log.1"	-> ".1"
	"file.log.2"	-> ".2"
	"file.log.900"	-> ".900"

	Returns the new length of the dot number part, including the dot.
*/
static inline size_t incrementDotNumberName (char *sz)
{
	ubf_assert_non_NULL	(sz);
	ubf_assert_non_0	(sz [0]);

	if ('.' == sz [0])
	{
		++ sz;
		uint64_t	ui = 0;;
		ubf_uint64_from_str (&ui, sz);
		++ ui;
		size_t written = ubf_str_from_uint64 (sz, ui);
		++ written;											// The '.'
		return written;
	} else
	{
		++ sz;
		memcpy (sz, ".1", 3);
		return 2;
	}
}

static inline char *findDotNumberPart (size_t *pln, CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (pln);
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(put->prargs);

	CUNILOG_ROTATION_DATA	*prd = put->prargs->cup->pData;

	// Obtain the dot number part.
	size_t ln = put->stFilToRotate - 1;
	-- ln;
	while (ln)
	{
		if (!isdigit (prd->mbDstFile.buf.pch [ln]))
			break;
		-- ln;
	}
	char *sz = prd->mbDstFile.buf.pch + ln;
	*pln = ln;
	return sz;
}

static inline void copyDotNumberToFLS (CUNILOG_TARGET *put, size_t nLen, size_t oLen)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(put->prargs);

	CUNILOG_ROTATOR_ARGS	*prg = put->prargs;
	CUNILOG_ROTATION_DATA	*prd = put->prargs->cup->pData;

	char		*szDst;
	const char	*ccSrc;

	if (nLen > oLen)
	{
		char	*sz	= put->fls.data [prg->idx].chFilename;
		size_t	ln	= put->fls.data [prg->idx].stFilename - oLen + nLen;
		put->fls.data [prg->idx].chFilename = GetAlignedMemFromSBULKMEMgrow (&put->sbm, ln);
		char *szFls = put->fls.data [prg->idx].chFilename;
		if (NULL == szFls)
		{	// Bulk memory allocation failed. There's not much we can do.
			ubf_assert_msg (false, "Bulk memory allocation failed");
			return;
		}
		memcpy (szFls, sz, put->fls.data [prg->idx].stFilename);
		put->fls.data [prg->idx].stFilename = ln;

		// Since the new vector entry is empty, we also need to copy the NUL terminator.
		++ nLen;
	}

	szDst	=	put->fls.data [prg->idx].chFilename
			+	put->lnAppName
			+	lenCunilogLogFileNameExtension;

	ccSrc	=	prd->mbDstFile.buf.pcc
			+	put->lnLogPath
			+	put->lnAppName
			+	lenCunilogLogFileNameExtension;
	memcpy (szDst, ccSrc, nLen);
}

static void cunilogRenameLogfile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(put->prargs);
	ubf_assert_non_NULL	(put->prargs->cup);
	ubf_assert_non_NULL	(put->prargs->cup->pData);
	ubf_assert			(isInitialisedSMEMBUF (&put->mbFilToRotate));
	ubf_assert_non_0	(put->stFilToRotate);
	ubf_assert_non_0	(1 < put->stFilToRotate);
	
	if (!hasDotNumberPostfix (put))
		return;

	//CUNILOG_ROTATOR_ARGS	*prg = put->prargs;
	CUNILOG_ROTATION_DATA	*prd = put->prargs->cup->pData;

	if (!cunilogHasRotatorFlag_USE_MBDSTFILE (prd))
	{
		initSMEMBUFtoSize	(
			&prd->mbDstFile,
			put->stFilToRotate + lenDateTimeStampFromPostfix (put->culogPostfix)
							);
		cunilogSetRotatorFlag_USE_MBDSTFILE (prd);
	}
	growToSizeSMEMBUF	(
		&prd->mbDstFile,
		put->stFilToRotate + lenDateTimeStampFromPostfix (put->culogPostfix)
						);
	if (isUsableSMEMBUF (&prd->mbDstFile))
	{
		memcpy (prd->mbDstFile.buf.pch, put->mbFilToRotate.buf.pch, put->stFilToRotate);

		size_t ln;
		char *sz = findDotNumberPart (&ln, put);

		// Either ".log.<number>" orr "g" from ".log".
		ubf_assert ('.' == sz [0] || 'g' == sz [0]);
		bool bLogfileNeedsClosing = 'g' == sz [0];

		size_t ol = put->stFilToRotate - 1 - ln;
		size_t nl = incrementDotNumberName (sz);
		copyDotNumberToFLS (put, nl, ol);

		bool bMoved;

		#ifdef PLATFORM_IS_WINDOWS
			if (bLogfileNeedsClosing)
				cunilogCloseCUNILOG_LOGFILEifOpen (put);
			bMoved = MoveFileU8long (put->mbFilToRotate.buf.pch, prd->mbDstFile.buf.pcc);
			if (bLogfileNeedsClosing)
			{
				if (requiresOpenLogFile (put))
				{
					if (!cunilogOpenLogFile (put))
					{
						SetCunilogSystemError (put->error, CUNILOG_ERROR_OPENING_LOGFILE);
						cunilogSetTargetErrorAndInvokeErrorCallback	(
							CUNILOG_ERROR_OPENING_LOGFILE,
							put->prargs->cup, put->prargs->pev
																	);
					}
				}
			}
			if (bMoved)
			{
				logFromInsideRotatorTextU8fmt	(
					put, "File \"%s\" moved/renamed to \"%s\".",
					put->mbFilToRotate.buf.pcc,
					prd->mbDstFile.buf.pcc
												);
			} else
			{
				char szErr [CUNILOG_STD_MSG_SIZE];
				DWORD dwErr = GetTextForLastError (szErr);

				logFromInsideRotatorTextU8fmt	(
					put,
					"Error %s while attempting to move file \"%s\" to \"%s\".",
					szErr, put->mbFilToRotate.buf.pcc, prd->mbDstFile.buf.pcc
												);
				SetCunilogError (put->error, CUNILOG_ERROR_RENAMING_LOGFILE, dwErr);
			}
		#else
			bMoved = false;
		#endif
	}
}

static void cunilogFileSystemCompressLogfile (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	bool b;
	char szErr [CUNILOG_STD_MSG_SIZE];
	
	enfilecompressresult	cmprRes = IsFileCompressedByName (put->mbFilToRotate.buf.pch);
	switch (cmprRes)
	{
		case fscompress_uncompressed:
			logFromInsideRotatorTextU8fmt	(
				put, "Initiating file system compression for file \"%s\"...",
				put->mbFilToRotate.buf.pcc
											);
			b = FScompressFileByName (put->mbFilToRotate.buf.pcc);
			if (b)
			{
				logFromInsideRotatorTextU8fmt	(
					put, "File system compression for file \"%s\" initiated.",
				put->mbFilToRotate.buf.pcc
												);
			} else
			{
				GetTextForLastError (szErr);
				logFromInsideRotatorTextU8fmt	(
					put,
					"Error %s while attempting to initiate file system compression for file \"%s\".",
					szErr, put->mbFilToRotate.buf.pcc
										);
			}
			break;
		case fscompress_compressed:
			break;
		case fscompress_error:
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt	(
				put,
				"Error %s while attempting to check file system compression for file \"%s\".",
				szErr, put->mbFilToRotate.buf.pcc
									);
			break;
	}
}

#if defined (OS_IS_WINDOWS) && defined (HAVE_SHELLAPI)

	static void MoveFileToRecycleBinWin (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		logFromInsideRotatorTextU8fmt	(
			put, "Moving obsolete logfile \"%s\" to recycle bin...", put->mbFilToRotate.buf.pcc
										);
		bool b = MoveToRecycleBinU8 (put->mbFilToRotate.buf.pcc);
		if (b)
		{
			logFromInsideRotatorTextU8fmt	(
				put, "Obsolete logfile \"%s\" moved to recycle bin.", put->mbFilToRotate.buf.pcc
											);
		} else
		{
			char szErr [CUNILOG_STD_MSG_SIZE];
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt	(
				put,
				"Error %s while attempting to move obsolete logfile \"%s\" to recycle bin.", szErr, put->mbFilToRotate.buf.pcc
											);
		}
	}

#elif OS_IS_MACOS

	#include "./../OS/Apple/TrashCan.h"

	// Our wrapper.
	static void MoveFileToRecycleBinMac (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		logFromInsideRotatorTextU8fmt (put, "Moving obsolete logfile \"%s\" to recycle bin...\n", put->mbFilToRotate.buf.pcc);
		if (LIBTRASHCAN_SUCCESS == trashcan_soft_delete_apple (put->mbFilToRotate.buf.pcc))
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" moved to recycle bin.\n", put->mbFilToRotate.buf.pcc);
		} else
		{
			logFromInsideRotatorTextU8fmt (put, "Error while attempting to move obsolete logfile \"%s\" to recycle bin.\n", put->mbFilToRotate.buf.pcc);
		}
	}

#elif defined (OS_IS_LINUX)

	static void MoveFileToRecycleBinLnx (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		logFromInsideRotatorTextU8fmt (put, "Moving obsolete logfile \"%s\" to recycle bin...\n", put->mbFilToRotate.buf.pcc);
		bool b = MoveFileToTrashPOSIX (put->mbFilToRotate.buf.pcc);
		if (b)
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" moved to recycle bin.\n", put->mbFilToRotate.buf.pcc);
		} else
		{
			char szErr [CUNILOG_STD_MSG_SIZE];
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt (put, "Error %s while attempting to move obsolete logfile \"%s\" to recycle bin.\n", szErr, put->mbFilToRotate.buf.pcc);
		}
	}

#else

	#error To do!!!

#endif

/*
	Platform-independent wrapper function.
*/
static inline void cunilogMoveFileToRecycleBin (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	#if defined (OS_IS_WINDOWS) && defined (HAVE_SHELLAPI)
		MoveFileToRecycleBinWin (put);
	#elif defined (OS_IS_MACOS)
		MoveFileToRecycleBinMac (put);
	#elif defined (OS_IS_LINUX)
		MoveFileToRecycleBinLnx (put);
	#else
		#error Not implemented yet!
	#endif
}

#ifdef PLATFORM_IS_WINDOWS
	static void cunilogDeleteObsoleteLogfile (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
	
		logFromInsideRotatorTextU8fmt (put, "Deleting obsolete logfile \"%s\"...\n", put->mbFilToRotate.buf.pch);
		bool b = DeleteFileU8 (put->mbFilToRotate.buf.pch);
		if (b)
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" deleted.\n", put->mbFilToRotate.buf.pch);
		} else
		{
			char szErr [CUNILOG_STD_MSG_SIZE];
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt (put, "Error %s while attempting to delete obsolete logfile \"%s\".\n", szErr, put->mbFilToRotate.buf.pch);
		}
	}
#endif

#ifdef PLATFORM_IS_POSIX
	static void DeleteObsoleteLogfile (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
	
		logFromInsideRotatorTextU8fmt (put, "Deleting obsolete logfile \"%s\"...\n", put->mbFilToRotate.buf.pch);
		int i = unlink (put->mbFilToRotate.buf.pch);
		if (0 == i)
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" deleted.\n", put->mbFilToRotate.buf.pch);
		} else
		{
			logFromInsideRotatorTextU8fmt (put, "Error %d while attempting to delete obsolete logfile \"%s\".\n", errno, put->mbFilToRotate.buf.pch);
		}
	}
#endif

static void performActualRotation (CUNILOG_ROTATOR_ARGS *prg)
{
	ubf_assert_non_NULL (prg);

	CUNILOG_PROCESSOR		*cup = prg->cup;
	ubf_assert_non_NULL (cup);
	CUNILOG_ROTATION_DATA	*prd = cup->pData;
	ubf_assert_non_NULL (prd);
	CUNILOG_EVENT			*pev = prg->pev;
	ubf_assert_non_NULL	(pev);
	CUNILOG_TARGET			*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	// Now the target knows exactly which rotator it is working on.
	put->prargs = prg;

	switch (prd->tsk)
	{
		case cunilogrotationtask_None:
			// This is a bug. We're normally not called in this case. See function
			//	cunilogProcessRotateLogfiles ().
			ubf_assert (false);
			break;
		case cunilogrotationtask_RenameLogfiles:
			cunilogRenameLogfile (put);
			break;
		case cunilogrotationtask_FScompressLogfiles:
			cunilogFileSystemCompressLogfile (put);
			break;
		case cunilogrotationtask_MoveToRecycleBinLogfiles:
			cunilogMoveFileToRecycleBin (put);
			break;
		case cunilogrotationtask_DeleteLogfiles:
			cunilogDeleteObsoleteLogfile (put);
			break;
	}

	// We're not in a rotator anymore.
	put->prargs = NULL;
}

static void prepareU8fullFileNameToRotate (CUNILOG_ROTATOR_ARGS *prg)
{
	ubf_assert_non_NULL (prg);
	CUNILOG_EVENT			*pev = prg->pev;
	ubf_assert_non_NULL (pev);
	CUNILOG_TARGET			*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	growToSizeSMEMBUF (&put->mbFilToRotate, put->lnLogPath + prg->siz);
	if (isUsableSMEMBUF (&put->mbFilToRotate))
	{
		memcpy (put->mbFilToRotate.buf.pch + put->lnLogPath, prg->nam, prg->siz);
		put->stFilToRotate = put->lnLogPath + prg->siz;
	}
}

static inline int cmpflsnums (const char *sz1, size_t l1, const char *sz2, size_t l2)
{
	const char *szo1 = sz1;
	const char *szo2 = sz2;

	while (szo1 [0] == szo2 [0])
	{
		++ szo1;
		-- l1;
		++ szo2;
		-- l2;
	}
	if (l1 || l2)
	{
		// The shorter the higher up.
		if (l1 < l2)
			return -1;
		if (l1 > l2)
			return 1;
		if (isdigit (szo1 [0]) && isdigit (szo2 [0]))
		{
			uint64_t	ui1;
			uint64_t	ui2;

			//printf ("%s - %s\n", szo1, szo2);
			ubf_uint64_from_str (&ui1, szo1);
			ubf_uint64_from_str (&ui2, szo2);
			if (ui1 == ui2)
				return 0;
			// "file.1" is greater than "file.2".
			return ui1 > ui2 ? 1 : -1;
		}
	}
	return 0;
}

/*
	Compare functions for vec_sort ().
*/
static int flscmp_dotnum (const void *p1, const void *p2)
{
	const CUNILOG_FLS	*fls1 = p1;
	const CUNILOG_FLS	*fls2 = p2;
	int					r = 0;

	ubf_assert_non_0 (fls1->stFilename);
	ubf_assert_non_0 (fls2->stFilename);

	r = cmpflsnums (fls1->chFilename, fls1->stFilename - 1, fls2->chFilename, fls2->stFilename - 1);
	return r;
}

static int flscmp_default (const void *p1, const void *p2)
{
	const CUNILOG_FLS	*fls1 = p1;
	const CUNILOG_FLS	*fls2 = p2;
	int					r = 0;

	ubf_assert_non_0 (fls1->stFilename);
	ubf_assert_non_0 (fls2->stFilename);

	if (fls1->stFilename == fls2->stFilename)
	{
		r = memcmp (fls1->chFilename, fls2->chFilename, fls1->stFilename - 1);
		return r;
	}
	if (fls1->stFilename < fls2->stFilename)
	{	
		r = memcmp (fls1->chFilename, fls2->chFilename, fls1->stFilename - 1);
		return r ? r : -1;
	}
	if (fls1->stFilename > fls2->stFilename)
	{
		r = memcmp (fls1->chFilename, fls2->chFilename, fls2->stFilename - 1);
		return r ? r : 1;
	}
	return r;
}

static inline bool needReverseFLS (CUNILOG_TARGET *put, CUNILOG_PROCESSOR *cup)
{
	ubf_assert_non_NULL (put);
	ubf_assert_non_NULL (cup);

	CUNILOG_ROTATION_DATA	*prd = cup->pData;
	
	bool bRet;
	bRet = cunilogTargetHasNumberSorting (put) && cunilogrotationtask_RenameLogfiles != prd->tsk;
	return bRet;
}

/*
	On NTFS, files are returned in descending alphabetical order.

	This means it is enough to just reverse the order, i.e. start with the last
	file first and walk downwards, and this is what prapareLogfilesListAndRotate ()
	does.
	
	Other file systems may also return files in descending alphabetical order,
	but on file systems that return the files randomly we got to sort the vector
	first. If sorting descending alphabetically is required, we expect the target option
	flag CUNILOGTARGET_FS_NEEDS_SORTING.

	For the dot number postfix we need to sort in any case.
*/
static inline void sortLogfilesList (CUNILOG_TARGET *put, CUNILOG_PROCESSOR *cup)
{
	if (cunilogTargetHasFSneedsSorting (put))
	{
		if (cunilogTargetHasNumberSorting (put))
			vec_sort (&put->fls, flscmp_dotnum);
		else
			vec_sort (&put->fls, flscmp_default);
	}

	// The processor may need the files in reverse order.

	bool bFLSreversedRequired = needReverseFLS (put, cup);
	if (bFLSreversedRequired)
	{
		if (!cunilogTargetHasFLSreversed (put))
		{
			vec_reverse (&put->fls);
			cunilogTargetSetFLSreversed (put);
		}
	} else
	{
		if (cunilogTargetHasFLSreversed (put))
		{
			vec_reverse (&put->fls);
			cunilogTargetClrFLSreversed (put);
		}
	}
}

static void prapareLogfilesListAndRotate (CUNILOG_ROTATOR_ARGS *prg)
{
	ubf_assert_non_NULL (prg);
	CUNILOG_EVENT			*pev = prg->pev;
	ubf_assert_non_NULL (pev);
	CUNILOG_TARGET			*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);
	CUNILOG_PROCESSOR		*cup = prg->cup;
	ubf_assert_non_NULL (cup);
	CUNILOG_ROTATION_DATA	*prd = cup->pData;
	ubf_assert_non_NULL (prd);

	sortLogfilesList (put, cup);

	size_t iFiles = put->fls.length;
	uint64_t nToIgnore = prd->nIgnore + put->scuNPI.nIgnoredTotal;
	uint64_t nMaxToRot =		CUNILOG_MAX_ROTATE_AUTO - nToIgnore <= prd->nMaxToRotate
							?	prd->nMaxToRotate
							:	nToIgnore + prd->nMaxToRotate;
	/*
	while (iFiles --)
	{
		puts (put->fls.data [iFiles].chFilename);
	}
	iFiles = put->fls.length;
	*/

	while (iFiles --)
	{
		//puts (put->fls.data [iFiles].chFilename);
		++ prd->nCnt;
		if (prd->nCnt > nToIgnore)
		{
			if (prd->nCnt <= nMaxToRot)
			{
				prg->nam = put->fls.data [iFiles].chFilename;
				prg->siz = put->fls.data [iFiles].stFilename;
				prg->idx = iFiles;
				prepareU8fullFileNameToRotate (prg);
				performActualRotation (prg);
			} else
				return;
		} else
		{	// This tells the next rotation processor how many we've ignored already.
			++ put->scuNPI.nIgnoredTotal;
		}
	}
}

/*
	Returns true if the logfile name ends with ".log" or ".log.<number>".
*/
static inline bool endsLogFileNameWithDotNumber (CUNILOG_FLS *pfls)
{
	ubf_assert_non_NULL	(pfls);
	ubf_assert_non_NULL	(pfls->chFilename);
	ubf_assert_non_0	(pfls->stFilename);

	size_t o = pfls->stFilename;
	size_t d = 0;

	if (o > lenCunilogLogFileNameExtension + 1)
	{
		o -= 2;												// NULL and 0 index.
		while (o && isdigit (pfls->chFilename [o]))
		{
			-- o;
			++ d;
		}
		if (d)
		{
			if (o && '.' == pfls->chFilename [o])
			{
				-- o;
				++ d;
			}
		}
		char *szfn = pfls->chFilename + pfls->stFilename - sizCunilogLogFileNameExtension - d;
		if (o > lenCunilogLogFileNameExtension)
		{
			return	0 == memcmp	(
							szCunilogLogFileNameExtension,
							szfn,
							lenCunilogLogFileNameExtension
								);
		}
	}
	return false;
}

#if defined (PLATFORM_IS_WINDOWS)
	static bool obtainLogfilesListToRotateCallbackWin (SRDIRONEENTRYSTRUCT *psdE)
	{
		ubf_assert_non_NULL (psdE);
		CUNILOG_TARGET			*put = psdE->pCustom;
		ubf_assert_non_NULL (put);

		char	szU8FileNameOnly [UTF8_MAX_PATH];

		CUNILOG_FLS	fls;
		// Note that the return value of UTF8_from_WinU16 () already includes a NUL terminator.
		fls.stFilename = UTF8_from_WinU16 (szU8FileNameOnly, UTF8_MAX_PATH, psdE->pwfd->cFileName);
		fls.chFilename = szU8FileNameOnly;
		if (hasDotNumberPostfix (put) && !endsLogFileNameWithDotNumber (&fls))
			return true;
		fls.chFilename = GetAlignedMemFromSBULKMEMgrow (&put->sbm, fls.stFilename);
		ubf_assert_non_NULL (fls.chFilename);
		if (fls.chFilename)
		{
			memcpy (fls.chFilename, szU8FileNameOnly, fls.stFilename);
			if (0 == put->fls.capacity)
			{
				if (-1 == vec_reserve (&put->fls, CUNILOG_STD_VECT_EXP_SIZE))
					return false;
			}
			vec_push (&put->fls, fls);
		}
		return true;
	}
#elif defined (PLATFORM_IS_POSIX)
	static bool obtainLogfilesListToRotateCallbackPsx (SONEDIRENT *pod)
	{
		ubf_assert_non_NULL (pod);
		CUNILOG_TARGET			*put = pod->pCustom;
		ubf_assert_non_NULL (put);

		CUNILOG_FLS fls;
		fls.stFilename = strlen (pod->dirEnt->d_name) + 1;
		if	(
				globMatch	(
					pod->dirEnt->d_name, fls.stFilename - 1,
					put->szLogFileMask, put->lnsLogFileMask
							)
			)
		{
			fls.chFilename = GetAlignedMemFromSBULKMEMgrow (&put->sbm, fls.stFilename);
			ubf_assert_non_NULL (fls.chFilename);
			if (fls.chFilename)
			{
				memcpy (fls.chFilename, pod->dirEnt->d_name, fls.stFilename);
				if (0 == put->fls.capacity)
				{
					if (-1 == vec_reserve (&put->fls, CUNILOG_STD_VECT_EXP_SIZE))
						return false;
				}
				vec_push (&put->fls, fls);
			}
		}
		return true;
	}
#endif

#if defined (PLATFORM_IS_WINDOWS)
	static void obtainLogfilesListToRotateWin (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		//logNoRotationTextU8fmt (put, "Test for the internal log output (Windows)");

		uint64_t n;
		n = ForEachDirectoryEntryU8	(
				put->mbLogFileMask.buf.pcc,					// Search mask.
				obtainLogfilesListToRotateCallbackWin, put, NULL
									);
		UNREFERENCED_PARAMETER (n);
	}
#elif defined (PLATFORM_IS_POSIX)
	static void obtainLogfilesListToRotatePsx (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		//logNoRotationTextU8fmt (put, "Test for the internal log output (POSIX)");

		uint64_t n;
		n = ForEachPsxDirEntry	(
				put->mbLogFold.buf.pcc,						// Directory name.
				obtainLogfilesListToRotateCallbackPsx, put, NULL
								);
		UNREFERENCED_PARAMETER (n);
	}
#endif

static inline void obtainLogfilesListToRotate (CUNILOG_TARGET *put)
{
	ubf_assert_non_NULL (put);

	#if defined (PLATFORM_IS_WINDOWS)
		obtainLogfilesListToRotateWin (put);
	#elif defined (PLATFORM_IS_POSIX)
		obtainLogfilesListToRotatePsx (put);
	#endif
	cunilogTargetClrFLSreversed (put);
}

static bool cunilogProcessRotateLogfilesFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	
	if (cunilogHasEventNoRotation (pev))
		return true;

	CUNILOG_TARGET			*put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);
	CUNILOG_ROTATION_DATA	*prd = cup->pData;
	ubf_assert_non_NULL (prd);

	// Reset.
	vec_clear (&put->fls);
	EmptySBULKMEM (&put->sbm);
	prd->nCnt = 0;

	CUNILOG_ROTATOR_ARGS	args;
	args.cup = cup;
	args.pev = pev;

	switch (prd->tsk)
	{
		case cunilogrotationtask_None:
			break;
		case cunilogrotationtask_RenameLogfiles:
		case cunilogrotationtask_FScompressLogfiles:
		case cunilogrotationtask_MoveToRecycleBinLogfiles:
		case cunilogrotationtask_DeleteLogfiles:
			obtainLogfilesListToRotate (put);
			prapareLogfilesListAndRotate (&args);
			break;
	}
	return true;
}

/*
	The custom processor. Its pData member is a pointer to a CUNILOG_CUSTPROCESS structure,
	which has two members: pData for custom data and the function pointer procFnc, which
	is the actual custom processor function.
*/
static bool cunilogProcessCustomProcessorFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	
	#ifdef DEBUG
		CUNILOG_TARGET	*put = pev->pCUNILOG_TARGET;
		ubf_assert_non_NULL (put);
	#endif

	CUNILOG_CUSTPROCESS	*pcu = cup->pData;
	ubf_assert_non_NULL (pcu);
	ubf_assert_non_NULL (pcu->procFnct);
	return pcu->procFnct (cup, pev);
}

/*
	The redirector processor. The event is redirected to a different CUNILOG_TARGET,
	to which the pData member points to. When the event is redirected, the remaining
	processors of the current target are ignored.

	If pData is NULL, no redirection takes place and the remaining processors are worked
	through as usual. Since this is most likely not what the caller intended, a debug
	assertion expects pData not being NULL.
*/
static bool cunilogProcessTargetRedirectorFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);

	CUNILOG_TARGET *put = cup->pData;
	ubf_assert_non_NULL (put);

	if (put)
	{
		logEv (put, pev);
		return false;
	}
	return true;
}

static bool cunilogProcessTargetForkFnct (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);

	CUNILOG_TARGET *put = cup->pData;
	ubf_assert_non_NULL (put);

	if (put)
	{
		CUNILOG_EVENT *pnev = DuplicateCUNILOG_EVENT (pev);
		if (pnev)
		{
			logEv (put, pev);
		}
	}
	return true;
}

/*
static void cunilogProcessNotSupported (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	
	CUNILOG_TARGET	*pta = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (pta);

	ubf_assert_msg (false, "Not supported yet!");
}
*/

/*
	Queue functions.
*/

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline size_t nToTrigger (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (cunilogHasDebugQueueLocked (put));

		if (cunilogTargetIsPaused (put))
		{
			++ put->nPausedEvents;
			return 0;
		} else
		{	// Only the current event requires a trigger. The value of nPausedEvents
			//	should have been zeroed out by ResumeLogCUNILOG_TARGET ().
			ubf_assert_0 (put->nPausedEvents);
			return 1;
		}
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	// Returns how many times the semaphore must be triggered to empty the queue.
	static inline size_t EnqueueCUNILOG_EVENT (CUNILOG_EVENT *pev)
	{
		ubf_assert_non_NULL (pev);
		ubf_assert_non_NULL (pev->pCUNILOG_TARGET);

		CUNILOG_TARGET	*put = pev->pCUNILOG_TARGET;
		ubf_assert (HAS_CUNILOG_TARGET_A_QUEUE (put));

		size_t r;

		EnterCUNILOG_LOCKER (put);

		// In this case it's more of an enqueuing date/timestamp than a creation date/timestamp.
		if (0 == pev->stamp)
		{
			pev->stamp = LocalTime_UBF_TIMESTAMP ();
			ubf_assert_msg (false, "Actually not implemented yet");
		}
		ubf_assert_non_0 (pev->stamp);

		if (put->qu.first)
		{
			CUNILOG_EVENT *l	= put->qu.last;
			ubf_assert_non_NULL (l);
			ubf_assert_NULL (l->next);
			l->next				= pev;
			put->qu.last		= pev;
			put->qu.num			+= 1;
		} else
		{
			put->qu.first		= pev;
			put->qu.last		= pev;
			put->qu.num			= 1;
		}
		r = nToTrigger (put);
		LeaveCUNILOG_LOCKER (put);
		return r;
	}
#endif

/*
	We expect the caller to process the returned event only. However,
	for consistency, i.e. to hide the rest of the queue from the caller,
	the member ->next of the returned event is set to NULL.
	This is to ensure the caller won't try to iterate further to the next
	event accidentally.

	This function is currently not used because we always empty the entire
	queue with DequeueAllCUNILOG_EVENTs ().
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline CUNILOG_EVENT *DequeueCUNILOG_EVENT (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (HAS_CUNILOG_TARGET_A_QUEUE (put));

		CUNILOG_EVENT	*pev	= NULL;

		EnterCUNILOG_LOCKER (put);
		if (put->qu.first)
		{
			ubf_assert_non_0 (put->qu.num);

			pev				= put->qu.first;
			put->qu.first	= pev->next;
			pev->next		= NULL;
			put->qu.num		-= 1;
		} else
		{
			ubf_assert_0	(put->qu.num);
			ubf_assert_NULL	(put->qu.last);
		}
		LeaveCUNILOG_LOCKER (put);
		return pev;
	}
#endif

/*
	We expect the caller to process the returned event and all its successors
	until the end of the list. The member ->next of the last element of the
	singly-linked list of events is NULL.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline CUNILOG_EVENT *DequeueAllCUNILOG_EVENTs (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (HAS_CUNILOG_TARGET_A_QUEUE (put));

		CUNILOG_EVENT	*pev	= NULL;
		CUNILOG_EVENT	*last;

		EnterCUNILOG_LOCKER (put);
		if (put->qu.first)
		{
			ubf_assert_non_0 (put->qu.num);

			pev				= put->qu.first;
			last			= put->qu.last;
			ubf_assert_NULL (last->next);

			// The queue is now empty. The caller is required to process
			//	all returned events.
			put->qu.first	= NULL;
			put->qu.last	= NULL;
			put->qu.num		= 0;
		} else
		{
			ubf_assert_0	(put->qu.num);
			ubf_assert_NULL	(put->qu.last);
		}
		LeaveCUNILOG_LOCKER (put);
		return pev;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline void triggerCUNILOG_EVENTloggingThread (CUNILOG_TARGET *put, size_t releaseCount)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (HAS_CUNILOG_TARGET_A_QUEUE (put));
		ubf_assert (0 < releaseCount);						// Caller's responsibility.

		#ifdef OS_IS_WINDOWS
			LONG lPrevCount;
			LONG relCount = (long) releaseCount;
			bool b = ReleaseSemaphore (put->sm.hSemaphore, relCount, &lPrevCount);
			UNREFERENCED_PARAMETER (b);
			#ifdef DEBUG
				ubf_assert_true (b);
				if (false == b)
				{
					char szMsg [CUNILOG_STD_MSG_SIZE];
					GetTextForLastError (szMsg);
					szMsg [0] = szMsg [0];					// To have something to step to.
				}
			#endif
		#else
			int i;
			while (releaseCount)
			{
				i = sem_post (&put->sm.tSemaphore);
				ubf_assert (0 == i);
				-- releaseCount;
			}
			UNREFERENCED_PARAMETER (i);
		#endif
	}
#endif

/*
	The calling thread loops as long as we return true. The calling thread exits
	when we return false.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static bool SepLogThreadWaitForEvents (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (HAS_CUNILOG_TARGET_A_QUEUE (put));

		#ifdef OS_IS_WINDOWS
			DWORD dw = WaitForSingleObject (put->sm.hSemaphore, INFINITE);
			ubf_assert (WAIT_OBJECT_0 == dw);
			return WAIT_OBJECT_0 == dw;
		#else
			int i = sem_wait (&put->sm.tSemaphore);
			ubf_assert (0 == i);
			return 0 == i;
		#endif
	}
#endif

/*
	The separate logging thread.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	SEPARATE_LOGGING_THREAD_RETURN_TYPE SeparateLoggingThread (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (HAS_CUNILOG_TARGET_A_QUEUE (put));

		while (SepLogThreadWaitForEvents (put))
		{
			CUNILOG_EVENT *pev = DequeueAllCUNILOG_EVENTs (put);
			CUNILOG_EVENT *pnx;
			while (pev)
			{	// Remember the next pointer because pev is going to be destroyed
				//	by DoneSUNILOGEVENT ().
				pnx = pev->next;
				cunilogProcessEventSingleThreaded (pev);
				DoneCUNILOG_EVENT (put, pev);
				pev = pnx;
			}
			if (cunilogIsShutdownTarget (put) && 0 == put->nPendingNoRotEvts )
				goto ExitSeparateLoggingThread;
		}
	ExitSeparateLoggingThread:
		cunilogSetTargetHasShutdown (put);
		return SEPARATE_LOGGING_THREAD_RETURN_SUCCESS;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static bool StartSeparateLoggingThread_ifNeeded (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (requiresCUNILOG_TARGETseparateLoggingThread (put))
		{
			#ifdef OS_IS_WINDOWS
				HANDLE h = CreateThread (NULL, 0, SeparateLoggingThread, put, 0, NULL);
				ubf_assert_non_NULL (h);
				if (NULL == h)
					SetCunilogSystemError (put->error, CUNILOG_ERROR_SEPARATE_LOGGING_THREAD);
				put->th.hThread = h;
				return NULL != h;
			#else
				put->th.tThread = 0;
				int i = pthread_create (&put->th.tThread, NULL, (void * (*)(void *)) SeparateLoggingThread, put);
				ubf_assert_0 (i);
				if (0 != i)
					SetCunilogSystemError (put->error, CUNILOG_ERROR_SEPARATE_LOGGING_THREAD);
				return 0 == i;
			#endif
		}
		// If the separate logging thread is not required, this is considered success.
		return true;
	}
#else
	static bool StartSeparateLoggingThread_ifNeeded (CUNILOG_TARGET *put)
	{
		UNUSED (put);

		return true;
	}
#endif

static inline bool updateThresholdForAppliesToTimes (CUNILOG_PROCESSOR *cup)
{
	ubf_assert_non_NULL (cup);

	bool bRet = cup->thr && cup->cur > cup->thr;
	if (0 == cup->thr || cup->cur > cup->thr)
	{
		cup->thr = cup->cur;
	}
	return bRet;
}

static inline bool updateCurrentValueAndIsThresholdReached	(
								CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev
																	)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	ubf_assert (sizeof (uint64_t) == sizeof (UBF_TIMESTAMP));

	bool bRet = false;

	switch (cup->freq)
	{
		case cunilogProcessAppliesTo_nEvents:
			++ cup->cur;
			bRet = cup->cur >= cup->thr;
			cup->thr = bRet ? 0 : cup->cur;
			break;
		case cunilogProcessAppliesTo_nOctets:
			cup->cur += pev->lenDataToLog;
			bRet = cup->cur >= cup->thr;
			cup->thr = bRet ? 0 : cup->cur;
			break;
		case cunilogProcessAppliesTo_nAlways:
			return true;
		case cunilogProcessAppliesTo_SecondChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS;
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_MinuteChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS;
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_HourChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS;
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_DayChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS;
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_WeekChanged:
			cup->cur = (pev->stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS)
					 + 	GetISO8601WeekNumberFromDate (
							UBF_TIMESTAMP_YEAR	(pev->stamp),
							UBF_TIMESTAMP_MONTH	(pev->stamp),
							UBF_TIMESTAMP_DAY	(pev->stamp),
							NULL
													);
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_MonthChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS;
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_YearChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS;
			bRet = updateThresholdForAppliesToTimes (cup);
			break;
		case cunilogProcessAppliesTo_Auto:
			ubf_assert_msg (false, "Illegal value");
			bRet = true;
			break;
	}

	// The flag OPT_CUNPROC_AT_STARTUP tells us to run the processor in any case.
	if (optCunProcHasOPT_CUNPROC_AT_STARTUP (cup->uiOpts))
	{
		optCunProcClrOPT_CUNPROC_AT_STARTUP (cup->uiOpts);
		return true;
	}

	// The same applies to the target.
	if (cunilogHasRunAllProcessorsOnStartup (pev->pCUNILOG_TARGET))
		return true;

	return bRet;
}

static bool (*pickAndRunProcessor [cunilogProcessAmountEnumValues]) (CUNILOG_PROCESSOR *cup, CUNILOG_EVENT *pev) =
{
	/* cunilogProcessNoOperation		*/		cunilogProcessNoneFnct
	/* cunilogProcessEchoToConsole		*/	,	cunilogProcessEchoFnct
	/* cunilogProcessUpdateLogFileName	*/	,	cunilogProcessUpdateLogFileNameFnct
	/* cunilogProcessWriteToLogFile		*/	,	cunilogProcessWriteToLogFileFnct
	/* cunilogProcessFlush				*/	,	cunilogProcessFlushFnct
	/* cunilogProcessRotateLogfiles		*/	,	cunilogProcessRotateLogfilesFnct
	/* cunilogProcessCustomProcessor	*/	,	cunilogProcessCustomProcessorFnct
	/* cunilogProcessTargetRedirector	*/	,	cunilogProcessTargetRedirectorFnct
	/* cunilogProcessTargetFork			*/	,	cunilogProcessTargetForkFnct
};

/*
	This function ensures that the decision on running the next processor is made
	according to the correct priorities.
*/
static inline bool cancelOrCarryOnWithNextProcessor	(
				bool bRetProcessor, CUNILOG_EVENT *pev, CUNILOG_PROCESSOR *cup
													)
{
	ubf_assert_non_NULL	(pev);
	ubf_assert_non_NULL	(cup);
	ubf_assert_non_NULL	(pev->pCUNILOG_TARGET);
	ubf_assert			(cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	// This is an echo-only event. There's no need to carry on with the other processors
	//	if we just ran the echo/console/terminal output processor.
	if (cunilogHasEventEchoOnly (pev) && cunilogProcessEchoToConsole == cup->task)
		return false;

	// An error callback function told us to stop here. The remaining processors are
	//	not run.
	if (cunilogHasEventStopProcessing (pev))
		return false;

	// The processor has the OPT_CUNPROC_FORCE_NEXT flag set.
	if (OPT_CUNPROC_FORCE_NEXT & cup->uiOpts)
		return true;

	// This is the first time processors run, and the caller wants us to run them all
	//	on startup.
	if (cunilogHasRunAllProcessorsOnStartup (pev->pCUNILOG_TARGET))
		return true;

	// Now the current processor decides if the next processor is allowed to run.
	 return bRetProcessor;
}

/*
	Returns true for further processing by the caller.
*/
static inline bool cunilogProcessProcessor (CUNILOG_EVENT *pev, CUNILOG_PROCESSOR *cup)
{
	ubf_assert_non_NULL	(pev);
	ubf_assert_non_NULL	(cup);
	ubf_assert_non_NULL	(pev->pCUNILOG_TARGET);
	ubf_assert			(cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	// If the processor is disabled we move on to the next one unconditionally.
	if (optCunProcHasOPT_CUNPROC_DISABLED (cup->uiOpts))
		return true;

	if (cunilogHasEventEchoOnly (pev) && cunilogProcessEchoToConsole != cup->task)
		return true;

	bool bRetProc = true;
	if	(updateCurrentValueAndIsThresholdReached (cup, pev))
	{
		// True tells the caller to carry on with the next processor.
		bRetProc = pickAndRunProcessor [cup->task] (cup, pev);
	}
	
	return cancelOrCarryOnWithNextProcessor (bRetProc, pev, cup);
}

static void cunilogProcessProcessors (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET->cprocessors);

	pev->pCUNILOG_TARGET->scuNPI.nIgnoredTotal = 0;
	cunilogClrEventStopProcessing (pev);

	unsigned int ui = 0;
	while (ui < pev->pCUNILOG_TARGET->nprocessors)
	{
		bool b = cunilogProcessProcessor (pev, pev->pCUNILOG_TARGET->cprocessors [ui]);
		if (!b)
			break;
		++ ui;
	}

	if (cunilogHasRunAllProcessorsOnStartup (pev->pCUNILOG_TARGET))
		cunilogClrRunAllProcessorsOnStartup (pev->pCUNILOG_TARGET);
}

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	static bool cunilogProcessEvtCommand (CUNILOG_EVENT *pev)
	{
		ubf_assert (pev->lenDataToLog >= sizeof (enum cunilogEvtCmd));
		#ifdef DEBUG
			enum cunilogEvtCmd cmd;
			memcpy (&cmd, pev->szDataToLog, sizeof (enum cunilogEvtCmd));
			ubf_assert (0 <= cmd);
			ubf_assert (cunilogCmdConfigXAmountEnumValues > cmd);
		#endif
		culCmdChangeCmdConfigFromCommand (pev);
		DoneCUNILOG_EVENT (NULL, pev);
		return true;
	}
#endif

static bool cunilogProcessEventSingleThreaded (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	// Event command flag for shutting down the separate logging thread.
	if (cunilogIsEventShutdown (pev))
	{
		cunilogSetShutdownTarget (pev->pCUNILOG_TARGET);
		DoneCUNILOG_EVENT (NULL, pev);
		// The shutdown event has been processed. We treat this as being success.
		return true;
	}

	#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
		if (cunilogEvtTypeCommand == pev->evType)
			return cunilogProcessEvtCommand (pev);
	#endif

	size_t	eventLineSize = createEventLineFromSUNILOGEVENT (pev);
	if (CUNILOG_SIZE_ERROR != eventLineSize)
	{
		cunilogProcessProcessors (pev);
		if (cunilogHasEventNoRotation (pev))
			DecrementPendingNoRotationEvents (pev->pCUNILOG_TARGET);
		return true;
	}
	return false;
}

static bool enqueueAndTriggerSeparateLoggingThread (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		size_t n = EnqueueCUNILOG_EVENT (pev);
		if (n)
			triggerCUNILOG_EVENTloggingThread (pev->pCUNILOG_TARGET, n);
		return n > 0;
	#else
		return cunilogProcessEventSingleThreaded (pev);
	#endif
}

static bool cunilogProcessEventSingleThreadedSeparateLoggingThread (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	return enqueueAndTriggerSeparateLoggingThread (pev);
}

static bool cunilogProcessEventMultiThreaded (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	EnterCUNILOG_LOCKER (pev->pCUNILOG_TARGET);
	bool b = cunilogProcessEventSingleThreaded (pev);
	LeaveCUNILOG_LOCKER (pev->pCUNILOG_TARGET);
	return b;
}

static bool cunilogProcessEventMultiThreadedSeparateLoggingThread (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pCUNILOG_TARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pCUNILOG_TARGET));

	return enqueueAndTriggerSeparateLoggingThread (pev);
}

static bool cunilogProcessOrQueueEventMultiProcesses (CUNILOG_EVENT *pev)
{
	UNREFERENCED_PARAMETER (pev);
	ubf_assert_msg (false, "Not implemented yet.");
	return false;
}

static bool (*cunilogProcOrQueueEvt [cunilogTypeAmountEnumValues]) (CUNILOG_EVENT *pev) =
{
	/* cunilogSingleThreaded				*/		cunilogProcessEventSingleThreaded
	/* cunilogSingleThreadedSeparateThread	*/	,	cunilogProcessEventSingleThreadedSeparateLoggingThread
	/* cunilogMultiThreaded					*/	,	cunilogProcessEventMultiThreaded
	/* cunilogMultiThreadedSeparateThread	*/	,	cunilogProcessEventMultiThreadedSeparateLoggingThread
	/* cunilogMultiProcesses				*/	,	cunilogProcessOrQueueEventMultiProcesses
};

/*
	Called by the logging functions.
*/
static bool cunilogProcessOrQueueEvent (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);

	CUNILOG_TARGET *put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);
	ubf_assert (cunilogIsTargetInitialised (put));

	// Sanity check for the type.
	ubf_assert (put->culogType >= 0);
	ubf_assert (put->culogType < cunilogTypeAmountEnumValues);

	#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		// This is the only one possible in a single-threaded environment.
		ubf_assert (cunilogSingleThreaded == put->culogType);
	#endif

	return cunilogProcOrQueueEvt [put->culogType] (pev);
}

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static void WaitForEndOfSeparateLoggingThread (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

	#ifdef OS_IS_WINDOWS
			ubf_assert_non_NULL (put->th.hThread);
			DWORD dw = WaitForSingleObject (put->th.hThread, INFINITE);
			UNREFERENCED_PARAMETER (dw);
			ubf_assert (WAIT_OBJECT_0 == dw);
		#else
			ubf_assert_non_0 (put->th.tThread);
			void *threadRetValue;
			int i = pthread_join (put->th.tThread, &threadRetValue);
			UNREFERENCED_PARAMETER (threadRetValue);
			ubf_assert (0 == i);
		#endif
	}
#else
	#define WaitForEndOfSeparateLoggingThread()
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static CUNILOG_EVENT scueShutdown =
	{
		NULL, CUNILOGEVENT_SHUTDOWN, 0,						// Up to stamp.
		NULL, 0,											// Up to lenDataToLog
		NULL,												// Member *next.
		cunilogEvtSeverityNone, cunilogEvtTypeNormalText,
		0													// Member sizEvent.
	};
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool queueShutdownEvent (CUNILOG_TARGET *put)
	{
		CUNILOG_EVENT *pev = DuplicateCUNILOG_EVENT (&scueShutdown);
		if (pev)
		{
			pev->pCUNILOG_TARGET = put;
			cunilogSetEventAllocated (pev);
			pev->stamp = 1;
			cunilogProcessOrQueueEvent (pev);
			return true;
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool ShutdownCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (HAS_CUNILOG_TARGET_A_QUEUE (put))
		{
			if (queueShutdownEvent (put))
			{
				WaitForEndOfSeparateLoggingThread (put);
				return true;
			}
			return false;
		}
		return true;
	}
#else
	bool ShutdownCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		cunilogSetShutdownTarget (put);
		return true;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool CancelCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (HAS_CUNILOG_TARGET_A_QUEUE (put))
		{
			cunilogSetShutdownTarget (put);

			// Empty the queue. While this would actually not be required here, it can
			//	speed up things significantly (well, maybe a few cycles) with busy queues as
			//	it takes some burden off the separate logging thread.
			CUNILOG_EVENT *pev = DequeueAllCUNILOG_EVENTs (put);
			CUNILOG_EVENT *nxt;
			while (pev)
			{
				nxt = pev->next;
				DoneCUNILOG_EVENT (NULL, pev);
				pev = nxt;
			}

			// Queue the shutdown command for the separate logging thread and wait
			//	for it to end.
			if (queueShutdownEvent (put))
			{
				WaitForEndOfSeparateLoggingThread (put);
				return true;
			}
			return false;
		}
		return true;
	}
#else
	bool CancelCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		cunilogSetShutdownTarget (put);
		return true;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		EnterCUNILOG_LOCKER (put);
		cunilogTargetSetPaused (put);
		LeaveCUNILOG_LOCKER (put);
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogCUNILOG_TARGET (CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL (put);

		size_t n;

		EnterCUNILOG_LOCKER (put);
		cunilogTargetClrPaused (put);
		n = put->nPausedEvents;
		put->nPausedEvents = 0;
		LeaveCUNILOG_LOCKER (put);

		triggerCUNILOG_EVENTloggingThread (put, n);
		return n;
	}
#endif

/*
	User logging functions.
*/

bool logEv (CUNILOG_TARGET *put, CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (put);
	ubf_assert_non_NULL (pev);
	ubf_assert (cunilogIsTargetInitialised (put));

	if (cunilogIsShutdownTarget (put))
		return false;

	pev->pCUNILOG_TARGET = put;
	return cunilogProcessOrQueueEvent (pev);
}

bool logTextU8sevl			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, sev, ccText, len);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logTextU8sevlq			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, sev, ccText, len);
	if (pev)
	{
		cunilogSetEventNoRotation (pev);
		return cunilogProcessOrQueueEvent (pev);
	}
	return false;
}

bool logTextU8sev			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText)
{
	return logTextU8sevl (put, sev, ccText, USE_STRLEN);
}

bool logTextU8sevq			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText)
{
	return logTextU8sevlq (put, sev, ccText, USE_STRLEN);
}

bool logTextU8l				(CUNILOG_TARGET *put, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, cunilogEvtSeverityNone, ccText, len);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logTextU8lq			(CUNILOG_TARGET *put, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, cunilogEvtSeverityNone, ccText, len);
	if (pev)
	{
		cunilogSetEventNoRotation (pev);
		return cunilogProcessOrQueueEvent (pev);
	}
	return false;
}

bool logTextU8				(CUNILOG_TARGET *put, const char *ccText)
{
	return logTextU8l (put, ccText, USE_STRLEN);
}

bool logTextU8q				(CUNILOG_TARGET *put, const char *ccText)
{
	return logTextU8lq (put, ccText, USE_STRLEN);
}

bool logTextU8vfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	char *ob = ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);
		bool b = logTextU8l (put, ob, l);
		ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8fmt			(CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8vfmt (put, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8qvfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	char *ob = ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);
		bool b = logTextU8lq (put, ob, l);
		ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8qfmt			(CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8qvfmt (put, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8svfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;

	char		cb [CUNILOG_DEFAULT_SFMT_SIZE];
	char		*ob;

	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	ob = l < CUNILOG_DEFAULT_SFMT_SIZE ? cb : ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);

		bool b = logTextU8l (put, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8sfmt			(CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8svfmt (put, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8sqvfmt		(CUNILOG_TARGET *put, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;

	char		cb [CUNILOG_DEFAULT_SFMT_SIZE];
	char		*ob;

	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	ob = l < CUNILOG_DEFAULT_SFMT_SIZE ? cb : ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);
		bool b = logTextU8lq (put, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8sqfmt			(CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8sqfmt (put, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8svfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;

	char		cb [CUNILOG_DEFAULT_SFMT_SIZE];
	char		*ob;

	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	ob = l < CUNILOG_DEFAULT_SFMT_SIZE ? cb : ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);

		bool b = logTextU8sevl (put, sev, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8sfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8svfmtsev (put, sev, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8smbvfmtsev	(CUNILOG_TARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);
	ubf_assert (isInitialisedSMEMBUF (smb));

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	growToSizeSMEMBUF (smb, l + 1);
	if (isUsableSMEMBUF (smb))
	{
		if (smb->buf.pch)
		{
			vsnprintf (smb->buf.pch, l + 1, fmt, ap);

			bool b = logTextU8sevl (put, sev, smb->buf.pch, l);
			return b;
		}
	}
	return false;
}

bool logTextU8smbfmtsev		(CUNILOG_TARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);
	ubf_assert (isInitialisedSMEMBUF (smb));

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8smbvfmtsev (put, smb, sev, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8smbvfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);
	ubf_assert (isInitialisedSMEMBUF (smb));

	if (cunilogIsShutdownTarget (put))
		return false;

	return logTextU8smbvfmtsev (put, smb, cunilogEvtSeverityNone, fmt, ap);
}

bool logTextU8smbfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);
	ubf_assert (isInitialisedSMEMBUF (smb));

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8smbvfmt (put, smb, fmt, ap);
	va_end (ap);

	return b;
}

bool logHexDumpU8sevl		(CUNILOG_TARGET *put, cueventseverity sev, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Data (put, sev, pBlob, size, ccCaption, lenCaption);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logHexDumpU8l			(CUNILOG_TARGET *put, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Data	(
							put, cunilogEvtSeverityNone, pBlob, size,
							ccCaption, lenCaption
													);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logHexDump				(CUNILOG_TARGET *put, const void *pBlob, size_t size)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Data	(
							put, cunilogEvtSeverityNone, pBlob,
							size, NULL, 0
													);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logHexDumpq			(CUNILOG_TARGET *put, const void *pBlob, size_t size)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Data	(
							put, cunilogEvtSeverityNone, pBlob,
							size, NULL, 0
													);
	if (pev)
	{
		cunilogSetEventNoRotation (pev);
		return cunilogProcessOrQueueEvent (pev);
	}
	return false;
}

bool logHexOrText			(CUNILOG_TARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	if (str_has_only_printable_ASCII (szHexOrTxt, lenHexOrTxt))
		return logTextU8l (put, szHexOrTxt, lenHexOrTxt);

	return logHexDump (put, szHexOrTxt, lenHexOrTxt);
}

bool logHexOrTextq			(CUNILOG_TARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	if (str_has_only_printable_ASCII (szHexOrTxt, lenHexOrTxt))
		return logTextU8lq (put, szHexOrTxt, lenHexOrTxt);

	return logHexDumpq (put, szHexOrTxt, lenHexOrTxt);
}

bool logHexOrTextU8			(CUNILOG_TARGET *put, const void *szHexOrTxtU8, size_t lenHexOrTxtU8)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	if (c_check_utf8 (szHexOrTxtU8, lenHexOrTxtU8))
		return logTextU8l (put, szHexOrTxtU8, lenHexOrTxtU8);

	return logHexDump (put, szHexOrTxtU8, lenHexOrTxtU8);
}

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16sevl			(CUNILOG_TARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len)
{
	ubf_assert_non_NULL (put);
	
	if (cunilogIsShutdownTarget (put))
		return false;

	char s8 [CUNILOG_STD_MSG_SIZE * 4];
	char *p8;

	len = USE_STRLEN == len ? wcslen (cwText) : len;
	ubf_assert (len <= INT_MAX);
	if (len > INT_MAX)
		return false;

	int il = (int) len;
	if (0 == il)
		return logTextU8sevl (put, sev, "", 0);

	int siz = reqUTF8sizel (cwText, il);

	// Case already covered above.
	ubf_assert_non_0 (siz);

	if (siz < CUNILOG_STD_MSG_SIZE * 4)
		p8 = s8;
	else
		p8 = ubf_malloc ((size_t) siz + 1);
	if (p8)
	{
		UTF8_from_WinU16l (p8, siz, cwText, il);
		if (ASCII_NUL == p8 [siz])
			-- siz;
		bool b = logTextU8sevl (put, sev, p8, siz);

		if (p8 != s8)
			ubf_free (p8);

		return b;
	}
	return false;
}
#endif

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16sev			(CUNILOG_TARGET *put, cueventseverity sev, const wchar_t *cwText)
{
	ubf_assert_non_NULL (put);
	
	if (cunilogIsShutdownTarget (put))
		return false;

	char s8 [CUNILOG_STD_MSG_SIZE * 4];
	char *p8;

	int siz = reqUTF8size (cwText);

	// We always need at least space for a NUL terminator, hence siz can actually never
	//	be 0 here.
	ubf_assert_non_0 (siz);

	if (siz <= CUNILOG_STD_MSG_SIZE * 4)
		p8 = s8;
	else
		p8 = malloc (siz);
	if (p8)
	{
		UTF8_from_WinU16 (p8, siz, cwText);
		if (ASCII_NUL == p8 [siz])
			-- siz;
		bool b = logTextU8sevl (put, sev, p8, siz);

		if (p8 != s8)
			free (p8);

		return b;
	}
	return false;
}
#endif

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16l				(CUNILOG_TARGET *put, const wchar_t *cwText, size_t len)
{
	ubf_assert_non_NULL (put);
	
	if (cunilogIsShutdownTarget (put))
		return false;

	return logTextWU16sevl (put, cunilogEvtSeverityNone, cwText, len);
}
#endif

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16				(CUNILOG_TARGET *put, const wchar_t *cwText)
{
	ubf_assert_non_NULL (put);
	
	if (cunilogIsShutdownTarget (put))
		return false;

	return logTextWU16sev (put, cunilogEvtSeverityNone, cwText);
}
#endif

bool logTextU8csevl			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	CUNILOG_EVENT *pev = CreateCUNILOG_EVENT_Text (put, sev, ccText, len);
	if (pev)
	{
		cunilogSetEventEchoOnly (pev);
		return cunilogProcessOrQueueEvent (pev);
	}
	return false;
}

bool logTextU8csev			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText)
{
	ubf_assert_non_NULL (put);

	return logTextU8csevl (put, sev, ccText, USE_STRLEN);
}

bool logTextU8cl			(CUNILOG_TARGET *put, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	return logTextU8csevl (put, cunilogEvtSeverityNone, ccText, len);
}

bool logTextU8c				(CUNILOG_TARGET *put, const char *ccText)
{
	ubf_assert_non_NULL (put);

	return logTextU8csevl (put, cunilogEvtSeverityNone, ccText, USE_STRLEN);
}

bool logTextU8cvfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	char *ob = ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);
		bool b = logTextU8cl (put, ob, l);
		ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8cfmt			(CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	bool		b;

	va_start (ap, fmt);
	b = logTextU8cvfmt (put, fmt, ap);
	va_end (ap);

	return b;
}

bool logTextU8csfmt			(CUNILOG_TARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	size_t		l;

	char		cb [CUNILOG_DEFAULT_SFMT_SIZE];
	char		*ob;

	va_start (ap, fmt);
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);
	va_end (ap);

	ob = l < CUNILOG_DEFAULT_SFMT_SIZE ? cb : ubf_malloc (l + 1);
	if (ob)
	{
		va_start (ap, fmt);
		vsnprintf (ob, l + 1, fmt, ap);
		va_end (ap);

		bool b = logTextU8cl (put, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8csmbvfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);
	ubf_assert (isInitialisedSMEMBUF (smb));

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;

	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	growToSizeSMEMBUF (smb, l + 1);
	if (isUsableSMEMBUF (smb))
	{
		if (smb->buf.pch)
		{
			vsnprintf (smb->buf.pch, l + 1, fmt, ap);

			bool b = logTextU8cl (put, smb->buf.pch, l);
			return b;
		}
	}
	return false;
}

bool logTextU8csmbfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);
	ubf_assert (isInitialisedSMEMBUF (smb));

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	size_t		l;

	va_start (ap, fmt);
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);
	va_end (ap);

	growToSizeSMEMBUF (smb, l + 1);
	if (isUsableSMEMBUF (smb))
	{
		if (smb->buf.pch)
		{
			va_start (ap, fmt);
			vsnprintf (smb->buf.pch, l + 1, fmt, ap);
			va_end (ap);

			bool b = logTextU8cl (put, smb->buf.pch, l);
			return b;
		}
	}
	return false;
}

bool logTextU8csvfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, va_list ap)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	size_t		l;

	char		cb [CUNILOG_DEFAULT_SFMT_SIZE];
	char		*ob;

	l = (size_t) vsnprintf (NULL, 0, fmt, ap);

	ob = l < CUNILOG_DEFAULT_SFMT_SIZE ? cb : ubf_malloc (l + 1);
	if (ob)
	{
		vsnprintf (ob, l + 1, fmt, ap);

		bool b = logTextU8csevl (put, sev, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8csfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	size_t		l;

	char		cb [CUNILOG_DEFAULT_SFMT_SIZE];
	char		*ob;

	va_start (ap, fmt);
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);
	va_end (ap);

	ob = l < CUNILOG_DEFAULT_SFMT_SIZE ? cb : ubf_malloc (l + 1);
	if (ob)
	{
		va_start (ap, fmt);
		vsnprintf (ob, l + 1, fmt, ap);
		va_end (ap);

		bool b = logTextU8csevl (put, sev, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	static inline CUNILOG_EVENT *CreateCUNILOG_EVENTforCommand (CUNILOG_TARGET *put, enum cunilogEvtCmd cmd)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= cmd);
		ubf_assert			(cunilogCmdConfigXAmountEnumValues > cmd);

		size_t rs = culCmdRequiredSize (cmd);
		ubf_assert (CUNILOG_CMD_INVALID_SIZE != rs);

		if (CUNILOG_CMD_INVALID_SIZE != rs)
		{
			CUNILOG_EVENT *pev = CreateCUNILOG_EVENTandData	(
									put, cunilogEvtSeverityNone,
									NULL, 0,
									cunilogEvtTypeCommand, NULL,
									rs
															);
			return pev;
		}
		return NULL;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETuseColourForEcho (CUNILOG_TARGET *put, bool bUseColour)
	{
		CUNILOG_EVENT *pev = CreateCUNILOG_EVENTforCommand (put, cunilogCmdConfigUseColourForEcho);
		if (pev)
		{
			culCmdStoreCmdConfigUseColourForEcho (pev->szDataToLog, bUseColour);
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETcunilognewline (CUNILOG_TARGET *put, newline_t nl)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= nl);
		ubf_assert			(cunilogNewLineAmountEnumValues > nl);

		CUNILOG_EVENT *pev = CreateCUNILOG_EVENTforCommand (put, cunilogCmdConfigCunilognewline);
		if (pev)
		{
			culCmdStoreCmdConfigCunilognewline (pev->szDataToLog, nl);
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= task);
		ubf_assert			(cunilogProcessAmountEnumValues > task);

		CUNILOG_EVENT *pev = CreateCUNILOG_EVENTforCommand (put, cunilogCmdConfigDisableTaskProcessors);
		if (pev)
		{
			culCmdStoreCmdConfigEnableTaskProcessors (pev->szDataToLog, task);
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= task);
		ubf_assert			(cunilogProcessAmountEnumValues > task);

		CUNILOG_EVENT *pev = CreateCUNILOG_EVENTforCommand (put, cunilogCmdConfigEnableTaskProcessors);
		if (pev)
		{
			culCmdStoreCmdConfigEnableTaskProcessors (pev->szDataToLog, task);
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETdisableEchoProcessor	(CUNILOG_TARGET *put)
	{
		ubf_assert_non_NULL	(put);

		enum cunilogEvtCmd	cmd		= cunilogCmdConfigDisableEchoProcessor;
		CUNILOG_EVENT		*pev	= CreateCUNILOG_EVENTforCommand (put, cmd);
		if (pev)
		{
			memcpy (pev->szDataToLog, &cmd, sizeof (cmd));
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETenableEchoProcessor	(CUNILOG_TARGET *put)
	{
		enum cunilogEvtCmd	cmd		= cunilogCmdConfigEnableEchoProcessor;
		CUNILOG_EVENT		*pev	= CreateCUNILOG_EVENTforCommand (put, cmd);
		if (pev)
		{
			memcpy (pev->szDataToLog, &cmd, sizeof (cmd));
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	bool ChangeCUNILOG_TARGETeventSeverityFormatType (CUNILOG_TARGET *put, cueventsevfmtpy sevTpy)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= sevTpy);
		ubf_assert			(cunilogEvtSeverityTypeXAmountEnumValues > sevTpy);

		CUNILOG_EVENT *pev = CreateCUNILOG_EVENTforCommand	(
								put, cunilogCmdConfigEventSeverityFormatType
															);
		if (pev)
		{
			culCmdStoreConfigEventSeverityFormatType (pev->szDataToLog, sevTpy);
			return cunilogProcessOrQueueEvent (pev);
		}
		return false;
	}
#endif
#endif

#if !defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY) && !defined (CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS)
	bool ChangeCUNILOG_TARGETlogPriority (CUNILOG_TARGET *put, cunilogprio prio)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= prio);
		ubf_assert			(prio < cunilogPrioAmountEnumValues);

		if (hasSeparateLoggingThread (put))
		{
			CUNILOG_EVENT *pev = CreateCUNILOG_EVENTforCommand (put, cunilogCmdConfigSetLogPriority);
			if (pev)
			{
				culCmdStoreConfigLogThreadPriority (pev->szDataToLog, prio);
				return cunilogProcessOrQueueEvent (pev);
			}
			return false;
		}
		return true;
	}
#endif

bool CunilogChangeCurrentThreadPriority (cunilogprio prio)
{
	ubf_assert			(0 <= prio);
	ubf_assert			(prio < cunilogPrioAmountEnumValues);

	if (0 <= prio && prio < cunilogPrioAmountEnumValues)
	{
		return culCmdSetCurrentThreadPriority (prio);
	}
	return false;
}

int cunilog_printf_sev_fmtpy_vl	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		va_list				ap
)
{
	ubf_assert_non_NULL (format);

	size_t lenRequired = evtSeverityColoursLen (sev);
	lenRequired += requiredEventSeverityChars (sev, sftpy);

	int			iReq;

	iReq = vsnprintf (NULL, 0, format, ap);
	if (iReq < 0)
		return iReq;
	lenRequired += iReq;

	int		iRet = -1;
	char	szToPrint [WINAPI_U8_HEAP_THRESHOLD];
	char	*pzToPrint;

	if (lenRequired < WINAPI_U8_HEAP_THRESHOLD)
		pzToPrint = szToPrint;
	else
		pzToPrint = ubf_malloc (lenRequired + 1);

	if (pzToPrint)
	{
		char *pz = pzToPrint;
		cpyEvtSeverityColour (&pz, sev);
		size_t st = writeEventSeverity (pz, sev, sftpy);
		pz += st;
		iReq = vsnprintf (pz, lenRequired + 1, format, ap);
		if (iReq < 0)
			goto Leave;
		pz += iReq;
		cpyRstEvtSeverityColour (&pz, sev);
		pz [0] = ASCII_NUL;

		#ifdef PLATFORM_IS_WINDOWS
			iRet = cunilogPrintWin (pzToPrint, lenRequired);
		#else
			if (lenRequired)
				iRet = printf (pz);
			else
				iRet = printf ("");
		#endif
	}

	Leave:
	if (pzToPrint && pzToPrint != szToPrint)
		ubf_free (pzToPrint);
	return iRet;
}

int cunilog_printf_sev_fmtpy	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		...
								)
{
	ubf_assert_non_NULL (format);

	int			iRet		= -1;
	va_list		args;

	va_start	(args, format);
	iRet = cunilog_printf_sev_fmtpy_vl (sev, sftpy, format, args);
	va_end		(args);

	return iRet;
}

int cunilog_printf_sev			(
		cueventseverity		sev,
		const char			*format,
		...
								)
{
	ubf_assert_non_NULL (format);

	int			iRet		= -1;
	va_list		args;

	va_start	(args, format);
	iRet = cunilog_printf_sev_fmtpy_vl (sev, cunilogEvtSeverityTypeDefault, format, args);
	va_end		(args);

	return iRet;
}

int cunilog_printf				(
		const char			*format,
		...
								)
{
	ubf_assert_non_NULL (format);

	int			iRet		= -1;
	va_list		args;

	va_start	(args, format);
	iRet = cunilog_printf_sev_fmtpy_vl (cunilogEvtSeverityNone, cunilogEvtSeverityTypeDefault, format, args);
	va_end		(args);

	return iRet;
}

int cunilog_puts_sev_fmtpy_l	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8,
		size_t				len
								)
{
	ubf_assert_non_NULL (strU8);

	if (NULL == strU8)
		return EOF;

	len = USE_STRLEN == len ? strlen (strU8) : len;
	size_t lenRequired = evtSeverityColoursLen (sev);
	lenRequired += requiredEventSeverityChars (sev, sftpy);
	lenRequired += len;

	int		iRet = EOF;
	char	szToPrint [WINAPI_U8_HEAP_THRESHOLD];
	char	*pzToPrint;

	if (lenRequired < WINAPI_U8_HEAP_THRESHOLD)
		pzToPrint = szToPrint;
	else
		pzToPrint = ubf_malloc (lenRequired + 1);		// Max. length of newline is 3.

	if (pzToPrint)
	{
		char *pz = pzToPrint;
		cpyEvtSeverityColour (&pz, sev);
		size_t st = writeEventSeverity (pz, sev, sftpy);
		pz += st;
		memcpy (pz, strU8, len);
		pz += len;
		cpyRstEvtSeverityColour (&pz, sev);
		pz [0] = ASCII_NUL;

		#ifdef PLATFORM_IS_WINDOWS
			iRet = cunilogPutsWin (pzToPrint, lenRequired);
		#else
			if (lenRequired)
				iRet = puts (pz);
			else
				iRet = puts ("");
		#endif

		if (pzToPrint != szToPrint)
			ubf_free (pzToPrint);
	}

	return iRet;
}

int cunilog_puts_sev_fmtpy		(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8
								)
{
	ubf_assert_non_NULL (strU8);

	return cunilog_puts_sev_fmtpy_l (sev, sftpy, strU8, USE_STRLEN);
}

int cunilog_puts_sev			(
		cueventseverity		sev,
		const char			*strU8
								)
{
	ubf_assert_non_NULL (strU8);

	return cunilog_puts_sev_fmtpy_l (sev, cunilogEvtSeverityTypeDefault, strU8, USE_STRLEN);
}

int cunilog_puts				(
		const char			*strU8
								)
{
	ubf_assert_non_NULL (strU8);

	return cunilog_puts_sev_fmtpy_l	(
				cunilogEvtSeverityNone, cunilogEvtSeverityTypeDefault, strU8, USE_STRLEN
									);
}

const uint64_t	uiCunilogVersion	=		((uint64_t) CUNILOG_VERSION_MAJOR	<< 48)
										|	((uint64_t) CUNILOG_VERSION_MINOR	<< 32)
										|	((uint64_t) CUNILOG_VERSION_SUB		<< 16)
										|	((uint64_t) CUNILOG_VERSION_BUILD);

int cunilogCheckVersionIntChk (uint64_t cunilogHdrVersion)
{
	ubf_assert_non_0 (cunilogHdrVersion);
	ubf_assert_msg	(
		uiCunilogVersion == cunilogHdrVersion,
		"Version mismatch libcunilog. If built as static library, the library doesn't match cunilog_combined.h"
					);

	if (uiCunilogVersion == cunilogHdrVersion)
		return 0;
	if (uiCunilogVersion > cunilogHdrVersion)
		return 1;
	//if (uiCunilogVersion < cunilogHdrVersion)
		return -1;
}

#ifdef CUNILOG_BUILD_TEST_FNCTS
	bool test_cunilog (void)
	{
		CUNILOG_TARGET	*pt;
		bool			bRet	= true;

		//ASSERT (false);

		// Ensure we haven't forgotten to fill the arrays/jump tables.
		ubf_assert (GET_ARRAY_LEN (arrLengthTimeStampFromPostfix)	==	cunilogPostfixAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (arrPostfixWildcardMask)			==	cunilogPostfixAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (obtainTimeStampAsString)			==	cunilogPostfixAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (cunilogProcOrQueueEvt)			==	cunilogTypeAmountEnumValues);

		ubf_assert (GET_ARRAY_LEN (EventSeverityTexts3)				==	cunilogEvtSeverityXAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (EventSeverityTexts5)				==	cunilogEvtSeverityXAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (EventSeverityTexts9)				==	cunilogEvtSeverityXAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (evtSeverityColours)				==	cunilogEvtSeverityXAmountEnumValues);

		// Check that the length assignments are correct.
		ubf_assert (LEN_ISO8601DATEHOURANDMINUTE	== lenDateTimeStampFromPostfix (cunilogPostfixMinute));
		ubf_assert (LEN_ISO8601DATEANDHOUR			== lenDateTimeStampFromPostfix (cunilogPostfixHour));
		ubf_assert (LEN_ISO8601DATE					== lenDateTimeStampFromPostfix (cunilogPostfixDay));
		ubf_assert (LEN_ISO8601DATE					== lenDateTimeStampFromPostfix (cunilogPostfixDefault));
		ubf_assert (LEN_ISO8601YEARANDWEEK			== lenDateTimeStampFromPostfix (cunilogPostfixWeek));
		ubf_assert (LEN_ISO8601YEARANDMONTH			== lenDateTimeStampFromPostfix (cunilogPostfixMonth));
		ubf_assert (LEN_ISO8601YEAR					== lenDateTimeStampFromPostfix (cunilogPostfixYear));

		/*
			Check consistency between unilogstruct.h and the declarations in this code file.
		*/

		ubf_assert ( 0 == cunilogEvtSeverityNone);
		ubf_assert ( 1 == cunilogEvtSeverityNonePass);
		ubf_assert ( 2 == cunilogEvtSeverityNoneFail);
		ubf_assert ( 3 == cunilogEvtSeverityNoneWarn);
		ubf_assert ( 4 == cunilogEvtSeverityBlanks);
		ubf_assert ( 5 == cunilogEvtSeverityEmergency);
		ubf_assert ( 6 == cunilogEvtSeverityNotice);
		ubf_assert ( 7 == cunilogEvtSeverityInfo);
		ubf_assert ( 8 == cunilogEvtSeverityMessage);
		ubf_assert ( 9 == cunilogEvtSeverityWarning);
		ubf_assert (10 == cunilogEvtSeverityError);
		ubf_assert (11 == cunilogEvtSeverityPass);
		ubf_assert (12 == cunilogEvtSeverityFail);
		ubf_assert (13 == cunilogEvtSeverityCritical);
		ubf_assert (14 == cunilogEvtSeverityFatal);
		ubf_assert (15 == cunilogEvtSeverityDebug);
		ubf_assert (16 == cunilogEvtSeverityTrace);
		ubf_assert (17 == cunilogEvtSeverityDetail);
		ubf_assert (18 == cunilogEvtSeverityVerbose);
		ubf_assert (19 == cunilogEvtSeverityIllegal);
		ubf_assert (20 == cunilogEvtSeverityXAmountEnumValues);

		ubf_assert (0 == strlen (EventSeverityTexts3 [cunilogEvtSeverityNone]));
		ubf_assert (0 == strlen (EventSeverityTexts3 [cunilogEvtSeverityNonePass]));
		ubf_assert (0 == strlen (EventSeverityTexts3 [cunilogEvtSeverityNoneFail]));
		ubf_assert (0 == strlen (EventSeverityTexts3 [cunilogEvtSeverityNoneWarn]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityBlanks]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityEmergency]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityNotice]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityInfo]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityMessage]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityWarning]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityError]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityPass]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityFail]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityCritical]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityFatal]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityDebug]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityTrace]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityDetail]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityVerbose]));
		ubf_assert (3 == strlen (EventSeverityTexts3 [cunilogEvtSeverityIllegal]));

		ubf_assert (0 == strlen (EventSeverityTexts5 [cunilogEvtSeverityNone]));
		ubf_assert (0 == strlen (EventSeverityTexts5 [cunilogEvtSeverityNonePass]));
		ubf_assert (0 == strlen (EventSeverityTexts5 [cunilogEvtSeverityNoneFail]));
		ubf_assert (0 == strlen (EventSeverityTexts5 [cunilogEvtSeverityNoneWarn]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityBlanks]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityEmergency]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityNotice]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityInfo]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityMessage]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityWarning]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityError]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityPass]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityFail]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityCritical]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityFatal]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityDebug]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityTrace]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityDetail]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityVerbose]));
		ubf_assert (5 == strlen (EventSeverityTexts5 [cunilogEvtSeverityIllegal]));

		ubf_assert (0 == strlen (EventSeverityTexts9 [cunilogEvtSeverityNone]));
		ubf_assert (0 == strlen (EventSeverityTexts9 [cunilogEvtSeverityNonePass]));
		ubf_assert (0 == strlen (EventSeverityTexts9 [cunilogEvtSeverityNoneFail]));
		ubf_assert (0 == strlen (EventSeverityTexts9 [cunilogEvtSeverityNoneWarn]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityBlanks]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityEmergency]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityNotice]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityInfo]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityMessage]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityWarning]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityError]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityPass]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityFail]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityCritical]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityFatal]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityDebug]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityTrace]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityDetail]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityVerbose]));
		ubf_assert (9 == strlen (EventSeverityTexts9 [cunilogEvtSeverityIllegal]));

		#ifdef OS_IS_LINUX
			bool bTrash = MoveFileToTrashPOSIX ("/home/thomas/FS/OAN/Thomas/cunilog/logs/testcunilog_2024-11-05 20_14.log");
			ubf_assert_false (bTrash);
		#endif

		/*
			Static.
		*/
		pt = InitCUNILOG_TARGETstaticEx	(
					NULL,		0,
					"Unilog",	USE_STRLEN,
					cunilogPath_relativeToHomeDir,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pCUNILOG_TARGETstatic	== pt);
		ubf_assert (pCUNILOG_TARGETstatic	== &CUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== CUNILOG_TARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== CUNILOG_TARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default	== CUNILOG_TARGETstatic.unilogEvtTSformat);
		ubf_assert (6 == CUNILOG_TARGETstatic.lnAppName);
		ubf_assert (!memcmp (CUNILOG_TARGETstatic.mbAppName.buf.pch, "Unilog", CUNILOG_TARGETstatic.lnAppName));

		size_t lnAbsLogPath;
		const char *szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGETstatic ();

		pt = InitCUNILOG_TARGETstaticEx	(
					NULL,				0,
					"////sub/Unilog",	USE_STRLEN,
					cunilogPath_relativeToHomeDir,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pCUNILOG_TARGETstatic	== pt);
		ubf_assert (pCUNILOG_TARGETstatic	== &CUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== CUNILOG_TARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== CUNILOG_TARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default	== CUNILOG_TARGETstatic.unilogEvtTSformat);
		ubf_assert (10 == CUNILOG_TARGETstatic.lnAppName);
		#ifdef PLATFORM_IS_WINDOWS
			ubf_assert (!memcmp (CUNILOG_TARGETstatic.mbAppName.buf.pch, "sub\\Unilog", CUNILOG_TARGETstatic.lnAppName));
		#else
			ubf_assert (!memcmp (CUNILOG_TARGETstatic.mbAppName.buf.pch, "sub/Unilog", CUNILOG_TARGETstatic.lnAppName));
		#endif

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGETstatic ();

		pt = InitCUNILOG_TARGETstaticEx	(
					NULL,		0,
					"Unilog",	USE_STRLEN,
					cunilogPath_relativeToCurrentDir,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pCUNILOG_TARGETstatic	== pt);
		ubf_assert (pCUNILOG_TARGETstatic	== &CUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== CUNILOG_TARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== CUNILOG_TARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default	== CUNILOG_TARGETstatic.unilogEvtTSformat);
		ubf_assert (6 == CUNILOG_TARGETstatic.lnAppName);
		ubf_assert (!memcmp (CUNILOG_TARGETstatic.mbAppName.buf.pch, "Unilog", CUNILOG_TARGETstatic.lnAppName));

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGETstatic ();

		pt = InitCUNILOG_TARGETstaticEx	(
					"C:/temp",	USE_STRLEN,
					"Unilog",	USE_STRLEN,
					cunilogPath_relativeToExecutable,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pCUNILOG_TARGETstatic	== pt);
		ubf_assert (pCUNILOG_TARGETstatic	== &CUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== CUNILOG_TARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== CUNILOG_TARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default		== CUNILOG_TARGETstatic.unilogEvtTSformat);
		// Size is 8 + NUL.
		ubf_assert (9 == CUNILOG_TARGETstatic.mbLogPath.size);
		ubf_assert	(
				!memcmp	(
					CUNILOG_TARGETstatic.mbLogPath.buf.pch,
					"C:" UBF_DIR_SEP_STR "temp" UBF_DIR_SEP_STR ASCII_NUL_STR,
					CUNILOG_TARGETstatic.mbLogPath.size
						)
					);
		ubf_assert	(
				// "C:\\temp\\Unilog".
				!memcmp	(
					CUNILOG_TARGETstatic.mbLogfileName.buf.pch,
					"C:" UBF_DIR_SEP_STR "temp" UBF_DIR_SEP_STR "Unilog",
					CUNILOG_TARGETstatic.mbLogPath.size + CUNILOG_TARGETstatic.lnAppName - 1
						)
					);
		ubf_assert (6 == CUNILOG_TARGETstatic.lnAppName);
		// Should be NUL-terminated.
		ubf_assert (!memcmp (CUNILOG_TARGETstatic.mbAppName.buf.pch, "Unilog", CUNILOG_TARGETstatic.lnAppName + 1));

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGETstatic ();

		pt = InitCUNILOG_TARGETstaticEx	(
					"../temp",	USE_STRLEN,
					"Unilog",	USE_STRLEN,
					cunilogPath_relativeToExecutable,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup

										);
		ubf_assert (pCUNILOG_TARGETstatic == pt);
		ubf_assert (pCUNILOG_TARGETstatic	== &CUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== CUNILOG_TARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay				== CUNILOG_TARGETstatic.culogPostfix);
		ubf_assert (6 == CUNILOG_TARGETstatic.lnAppName);
		ubf_assert (!memcmp (CUNILOG_TARGETstatic.mbAppName.buf.pch, "Unilog", CUNILOG_TARGETstatic.lnAppName + 1));

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGETstatic ();

		/*
			Dynamic.
		*/
		pt = CreateNewCUNILOG_TARGET (
				NULL, 0,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
									);
		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);
		DoneCUNILOG_TARGET (pt);

		pt = InitOrCreateCUNILOG_TARGET	(
				NULL,
				NULL, 0,
				"Unilog", 6,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
										);

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGET (pt);

		pt = InitOrCreateCUNILOG_TARGET	(
				NULL,
				"C:/Temp", 7,
				"Unilog", 6,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
										);
		ubf_assert_non_NULL (pt);
		ubf_assert (pt != pCUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== pt->culogType);
		ubf_assert (cunilogPostfixDay				== pt->culogPostfix);
		ubf_assert (9 == pt->mbLogPath.size);				// "C:/Temp/" + NUL.
		ubf_assert	(
				!memcmp	(
					pt->mbLogPath.buf.pch,
					"C:" UBF_DIR_SEP_STR "Temp" UBF_DIR_SEP_STR ASCII_NUL_STR,
					pt->mbLogPath.size
						)
					);
		ubf_assert	(
				// "C:\\Temp\\Unilog".
				!memcmp	(
					pt->mbLogfileName.buf.pch,
					"C:" UBF_DIR_SEP_STR "Temp" UBF_DIR_SEP_STR "Unilog_",
					pt->lnLogPath + pt->lnAppName + 1
						)
					);
		ubf_assert (6 == pt->lnAppName);
		ubf_assert (!memcmp (pt->mbAppName.buf.pch, "Unilog", pt->lnAppName));

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGET (pt);

		// Should fail.
		CUNILOG_TARGET	cut;
		CUNILOG_TARGET	*put;
		put = InitCUNILOG_TARGET	(
				&cut,
				"temp",		USE_STRLEN,
				"OurApp",	USE_STRLEN,
				cunilogPath_isAbsolute,
				cunilogMultiThreaded
									);
		ubf_assert_NULL (put);
		ubf_assert (CUNILOG_ERROR_ABS_OR_REL_PATH == CunilogCunilogError (cut.error));

		/*
			Application name from executable name.
		*/
		pt = InitOrCreateCUNILOG_TARGET	(
				NULL,
				"C:/Temp", 7,
				NULL, 0,
				cunilogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
										);
		SMEMBUF mb;
		initSMEMBUF (&mb);
		ObtainAppNameFromExecutableModule (&mb);
		ubf_assert (!memcmp (pt->mbAppName.buf.pch, mb.buf.pch, strlen (mb.buf.pch)));
		ubf_assert_non_NULL (pt);
		ubf_assert (pt != pCUNILOG_TARGETstatic);
		ubf_assert (cunilogSingleThreaded	== pt->culogType);
		ubf_assert (cunilogPostfixDay		== pt->culogPostfix);
		ubf_assert (9 == pt->mbLogPath.size);
		ubf_assert (8 == pt->lnLogPath);
		ubf_assert	(
				!memcmp	(
					pt->mbLogPath.buf.pch,
					"C:" UBF_DIR_SEP_STR "Temp" UBF_DIR_SEP_STR ASCII_NUL_STR,
					pt->mbLogPath.size
						)
					);

		szAbsLogPath = GetAbsoluteLogPathCUNILOG_TARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneCUNILOG_TARGET (pt);

		return bRet;
	}
#endif
