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

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	
		#include "./ubf_date_and_time.h"
		#include "./ubfdebug.h"
		#include "./ArrayMacros.h"
		#include "./membuf.h"
		#include "./check_utf8.h"
		#include "./ubfcharscountsandchecks.h"
		#include "./strfilesys.h"
		#include "./strintuint.h"
		#include "./strhexdump.h"
		#include "./strmembuf.h"
		#include "./strisabsolutepath.h"
		#include "./strnewline.h"
		#include "./CompressFile.h"
		#include "./ExeFileName.h"
		
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
		#include "./../string/strfilesys.h"
		#include "./../string/strintuint.h"
		#include "./../string/strhexdump.h"
		#include "./../string/strmembuf.h"
		#include "./../string/strisabsolutepath.h"
		#include "./../string/strnewline.h"
		#include "./../string/strwildcards.h"
		#include "./../OS/CompressFile.h"
		#include "./../OS/ExeFileName.h"
		
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

static SCUNILOGTARGET SCUNILOGTARGETstatic;
SCUNILOGTARGET *pSCUNILOGTARGETstatic	= &SCUNILOGTARGETstatic;

/*
	Copy from the structure header cunilogstructs.h to avoid switching between code and header
	during development. Can/could be deleted when finalised.

typedef struct cunilog_processor
{
	void						*pSCUNILOGTARGET;			// Pointer to the SCUNILOGTARGET
															//	structure.
	enum cunilogprocesstask		task;						// What to apply.
	enum cunilogprocesstype		thrtype;					// When to apply (theshold type).
	uint64_t					thr;						// Required value of cur before this
															//	processor is applied/run.
	uint64_t					cur;						// The current value.
	void						*pData;						// Pointer to processor-specific data.
	uint64_t					uiOpts;						// Option flags. See OPT_CUNPROC_
															//	definitions below.
} CUNILOG_PROCESSOR;

*/

/*
	Our default pData structures for our standard processors.
*/
CUNILOG_LOGFILE			stdcuppLogFile;

CUNILOG_ROTATION_DATA	stdcuppRotatorFS_compress =
{
	cunilogrotationtask_FScompressLogfiles,
	2, 0, CUNILOG_MAX_ROTATE_AUTO,
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,
	NULL,
	CUNILOG_ROTATOR_FLAG_NONE
};

CUNILOG_ROTATION_DATA	stdcuppRotatorMove_to_recycle_bin =
{
	cunilogrotationtask_MoveToRecycleBinLogfiles,
	3, 0, CUNILOG_MAX_ROTATE_AUTO,
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,
	NULL,
	CUNILOG_ROTATOR_FLAG_NONE
};

CUNILOG_ROTATION_DATA	stdcuppRotatorDelete =
{
	cunilogrotationtask_DeleteLogfiles,
	4, 0, CUNILOG_MAX_ROTATE_AUTO,
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,
	NULL,
	CUNILOG_ROTATOR_FLAG_NONE
};

/*
	Our standard processors. Only used for our static SCUNILOGTARGET structure.
*/
CUNILOG_PROCESSOR	stdcuppEcho	=
{
	cunilogProcessEchoToConsole,
	cunilogProcessAppliesTo_nAlways,
	0, 0,
	NULL,
	OPT_CUNPROC_FORCE_NEXT
};
CUNILOG_PROCESSOR	stdcuppUpdateLogfileName =
{
	cunilogProcessUpdateLogFileName,
	cunilogProcessAppliesTo_nAlways,
	0, 0,
	NULL,
	OPT_CUNPROC_FORCE_NEXT
};
CUNILOG_PROCESSOR	stdcuppWriteToLogfile =
{
	cunilogProcessWriteToLogFile,
	cunilogProcessAppliesTo_nAlways,
	0, 0,
	&stdcuppLogFile,
	OPT_CUNPROC_NONE
};
CUNILOG_PROCESSOR	stdcuppFlushLogFile =
{
	cunilogProcessFlushLogFile,
	cunilogProcessAppliesTo_Auto,
	0, 0,
	&stdcuppLogFile,
	OPT_CUNPROC_FORCE_NEXT
};
CUNILOG_PROCESSOR	stdcuppRotateLogfilesFScompress =
{
	cunilogProcessRotateLogfiles,
	cunilogProcessAppliesTo_Auto,
	0, 0,
	&stdcuppRotatorFS_compress,
	OPT_CUNPROC_NONE | OPT_CUNPROC_AT_STARTUP
};
CUNILOG_PROCESSOR	stdcuppRotateLogfilesMoveToTrash =
{
	cunilogProcessRotateLogfiles,
	cunilogProcessAppliesTo_Auto,
	0, 0,
	&stdcuppRotatorMove_to_recycle_bin,
	OPT_CUNPROC_NONE | OPT_CUNPROC_AT_STARTUP
};
CUNILOG_PROCESSOR	*stdcupp [] =
{
	&stdcuppEcho,											// Writes to console.
	&stdcuppUpdateLogfileName,								// Updates the date/timestamp within
															//	the log file's name.
	&stdcuppWriteToLogfile,									// Writes out to log file.
	&stdcuppFlushLogFile,									// Flushes the log file.
	&stdcuppRotateLogfilesFScompress,						// Rotates the log files.
	&stdcuppRotateLogfilesMoveToTrash						// Rotates the log files.
};

#ifdef DEBUG
	void InitCUNILOG_PROCESSOR	(
			CUNILOG_PROCESSOR				*cup,
			enum cunilogprocesstask			task,
			enum cunilogprocessfrequency	freq,
			uint64_t						thrs
								)
	{
		ubf_assert_non_NULL (cup);
		cup->task	= task;
		cup->freq	= freq;
		cup->thr	= thrs;
		cup->cur	= 0;
		cup->pData	= NULL;
		cup->uiOpts	= OPT_CUNPROC_NONE;
	}
#endif

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
	/* cunilogPostfixDotNumberDescending	*/	,	0
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
	"",											// cunilogPostfixDotNumberDescending
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
	/* cunilogPostfixDotNumberDescending	*/	,	noPostfix
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
		static inline void InitCriticalSection (SCUNILOGTARGET *put)
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
		static inline void InitCriticalSection (SCUNILOGTARGET *put)
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
	static inline void InitCUNILOG_LOCKER (SCUNILOGTARGET *put)
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
	static inline void EnterCUNILOG_LOCKER (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (needsOrHasLocker (put));
		ubf_assert_true (put->cl.bInitialised);

		#ifdef OS_IS_WINDOWS
			EnterCriticalSection (&put->cl.cs);
		#else
			pthread_mutex_lock (&put->cl.mt);
		#endif
	}
#else
	#define EnterCUNILOG_LOCKER(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef PLATFORM_IS_WINDOWS
		static inline void LeaveCUNILOG_LOCKER (SCUNILOGTARGET *put)
		{
			ubf_assert_non_NULL (put);
			ubf_assert (needsOrHasLocker (put));
			ubf_assert_true (put->cl.bInitialised);

			LeaveCriticalSection (&put->cl.cs);
		}
	#else
		static inline void LeaveCUNILOG_LOCKER (SCUNILOGTARGET *put)
		{
			ubf_assert_non_NULL (put);
			ubf_assert (needsOrHasLocker (put));
			ubf_assert_true (put->cl.bInitialised);

			pthread_mutex_unlock (&put->cl.mt);
		}
	#endif
#else
	#define LeaveCUNILOG_LOCKER(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef OS_IS_WINDOWS
		static inline void DestroyCriticalSection (SCUNILOGTARGET *put)
		{
			DeleteCriticalSection (&put->cl.cs);
		}
	#else
		static inline void DestroyCriticalSection (SCUNILOGTARGET *put)
		{
			pthread_mutex_destroy (&put->cl.mt);
		}
	#endif
#endif
		
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline void DoneCUNILOG_LOCKER (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert_true (put->cl.bInitialised);

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

/*
	ObtainUserHomeDirectoy

	Obtains the user's home directory with an ending forward or backward slash as an
	SMEMBUF. It returns the length of the path excluding the terminating NUL character.

	This function should probably go in its own module at some point.
*/
static size_t ObtainUserHomeDirectoy (SMEMBUF *mb)
{
	ubf_assert_non_NULL (mb);
	ubf_assert (isInitialisedSMEMBUF (mb));

	size_t	r = 0;

	#if defined (PLATFORM_IS_WINDOWS)

		HANDLE hToken = 0;
		OpenProcessToken (GetCurrentProcess(), TOKEN_QUERY, &hToken );
		DWORD dw = 0;
		GetUserProfileDirectoryU8 (hToken, NULL, &dw);
		growToSizeSMEMBUF (mb, (size_t) dw + 1);
		if (isUsableSMEMBUF (mb))
		{
			bool b = GetUserProfileDirectoryU8 (hToken, mb->buf.pch, &dw);
			if (b && dw > 1)
			{
				// This check is normally not required since we actually already
				//	know that the profile folder comes without a directory separator.
				//	This function is only called from the initialiser and therefore not a
				//	hot path.
				if ('\\' != mb->buf.pch [dw - 2])
				{
					++ dw;
					mb->buf.pch [dw - 2] = '\\';
					mb->buf.pch [dw - 1] = '\0';
				}
				ubf_assert ('\0' == mb->buf.pch [dw - 1]);
				r = (size_t) dw - 1;
			}
		}

	#elif defined (PLATFORM_IS_POSIX)

		size_t lnH;
		const char *szH = UserHomeDirectoryPOSIX (&lnH);
		// Same here: This check is normally not required since we actually already
		//	know that the profile folder comes without a directory separator.
		//	This function is only called from the initialiser and therefore not a
		//	hot path.
		if (lnH && '/' != szH [lnH])
		{
			r = SMEMBUFfromStrReserveBytes (mb, szH, lnH + 1, 1) - 1;
			if (r)
			{
				mb->buf.pch [lnH]		= '/';
				mb->buf.pch [lnH + 1]	= '\0';
				++ r;
			}
		} else
			r = SMEMBUFfromStr (mb, szH, lnH + 1) - 1;

	#else

		#error Not supported!

	#endif

	return r;
}

static size_t ObtainRelativeLogPathBase (SMEMBUF *mb, enCunilogRelLogPath relLogPath)
{
	switch (relLogPath)
	{
		#ifdef DEBUG
		case cunilogLogPath_isAbsolute:
			ubf_assert_msg (false, "This should have been caught before we got here");
			// Hopefully this causes an access violation/segmentation fault.
			return CUNILOG_SIZE_ERROR;
		#endif
		case cunilogLogPath_relativeToExecutable:
			return ObtainPathFromExecutableModule (mb);
		case cunilogLogPath_relativeToCurrentDir:
			return ObtainCurrentWorkingDirectoy (mb);
		case cunilogLogPath_relativeToHomeDir:
			return ObtainUserHomeDirectoy (mb);
	}
	return 0;
}

static bool ObtainLogPathFromArgument	(
				SMEMBUF						*smlp,
				size_t						*lnlp,
				const char					*szLogPath,
				size_t						len,
				enCunilogRelLogPath			relLogPath
										)
{
	ubf_assert_non_NULL (smlp);
	ubf_assert_non_NULL (lnlp);
	ubf_assert_non_NULL (szLogPath);
	ubf_assert_non_0 (len);
	ubf_assert (isInitialisedSMEMBUF (smlp));

	SMEMBUF b	= SMEMBUF_INITIALISER;
	size_t	ln	= len;

	if (is_absolute_path_l (szLogPath, ln))
	{
		if (!isDirSep (szLogPath [ln - 1]))
		{
			if (SMEMBUFfromStrReserveBytes (&b, szLogPath, ln, 2))
			{
				b.buf.pch [ln] = UBF_DIR_SEP;
				++ ln;
				b.buf.pch [ln] = ASCII_NUL;
			}
		} else
		{
			SMEMBUFfromStr (&b, szLogPath, ln);
		}
	} else
	{	// The path is relative. It cannot be absolute.
		if (cunilogLogPath_isAbsolute == relLogPath)
		{
			#ifndef CUNILOG_BUILD_TEST_FNCTS
				ubf_assert_msg	(
					false,
					"szLogPath cannot be relative or NULL if cunilogLogPath_isAbsolute is given"
								);
			#endif
			return false;
		}
		SMEMBUF	t	= SMEMBUF_INITIALISER;
		size_t	lp	= ObtainRelativeLogPathBase (&t, relLogPath);
		ln = lp + len;
		if (!isDirSep (szLogPath [len - 1]))
		{
			growToSizeSMEMBUF (&b, ln + 1);
			if (isUsableSMEMBUF (&b))
			{
				copySMEMBUF (&b, &t);
				memcpy (b.buf.pch + lp, szLogPath, len);
				b.buf.pch [lp + len] = UBF_DIR_SEP;
				++ ln;
			}
		} else
		{
			growToSizeSMEMBUF (&b, ln);
			if (isUsableSMEMBUF (&b))
				memcpy (b.buf.pch + lp, szLogPath, len);
		}
		doneSMEMBUF (&t);
	}
	str_correct_dir_separators (b.buf.pch, ln);
	str_remove_path_navigators (b.buf.pch, &ln);
	copySMEMBUFsiz (smlp, &b, ln + 1);							// NUL-terminated.
	doneSMEMBUF (&b);
	*lnlp = ln;													// The length of the destination.
	return true;
}

char *CreateLogPathInSUNILOGTARGET	(
		SCUNILOGTARGET *put, const char *szLogPath, size_t len, enCunilogRelLogPath relLogPath
									)
{
	ubf_assert_non_NULL (put);

	initSMEMBUF (&put->mbLogPath);
	if (szLogPath)
	{
		ubf_assert (0 != len);

		bool b;
		b = ObtainLogPathFromArgument	(
				&put->mbLogPath, &put->lnLogPath, szLogPath, len, relLogPath
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
		if (cunilogLogPath_isAbsolute == relLogPath)
			return NULL;

		// No path given. We use the path specified with relLogPath.
		put->lnLogPath = ObtainRelativeLogPathBase (&put->mbLogPath, relLogPath);
	}
	put->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED;
	return put->mbLogPath.buf.pch;
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

char *CreateAppNameInSUNILOGTARGET (SCUNILOGTARGET *put, const char *szAppName, size_t len)
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

/*
	Probably not required, or maybe only as an example.

CUNILOG_PROCESSOR **NewStandardProcessors (SCUNILOGTARGET *put, unsigned int *pn)
{
	ubf_assert_non_NULL (put);

	CUNILOG_PROCESSOR **pp	= malloc (3 * sizeof (CUNILOG_PROCESSOR *));

	if (pp)
	{
		// Echo (output) to console.
		unsigned int ui = 0;
		pp [ui] = malloc (sizeof (CUNILOG_PROCESSOR));
		if (pp [ui])
		{
			pp [ui]->pSCUNILOGTARGET = put;
			pp [ui]->task		= cunilogProcessEchoToConsole;
			pp [ui]->thrtype	= cunilogProcessAppliesTo_nAlways;
			pp [ui]->thr		= 0;
			pp [ui]->cur		= 0;
			pp [ui]->pData		= NULL;
			pp [ui]->uiOpts		= OPT_CUNPROC_NONE;
			pp [ui]->uiOpts	|= OPT_CUNPROC_FORCE_NEXT | OPT_CUNPROC_ALLOCATED;
		}
		// Update the name of the logfile.
		++ ui;
		pp [ui] = malloc (sizeof (CUNILOG_PROCESSOR));
		if (pp [ui])
		{
			pp [ui]->pSCUNILOGTARGET = put;
			pp [ui]->task		= cunilogProcessUpdateLogFileName;
			pp [ui]->thrtype	= cunilogProcessAppliesTo_nAlways;
			pp [ui]->thr		= 0;
			pp [ui]->cur		= 0;
			pp [ui]->pData		= NULL;
			pp [ui]->uiOpts		= OPT_CUNPROC_NONE;
			pp [ui]->uiOpts	|= OPT_CUNPROC_ALLOCATED;
		}
		// Write to log file.
		++ ui;
		pp [ui] = malloc (sizeof (CUNILOG_PROCESSOR));
		if (pp [ui])
		{
			pp [ui]->pSCUNILOGTARGET = put;
			pp [ui]->task		= cunilogProcessWriteToLogFile;
			pp [ui]->thrtype	= cunilogProcessAppliesTo_nAlways;
			pp [ui]->thr		= 0;
			pp [ui]->cur		= 0;
			pp [ui]->pData		= NULL;
			pp [ui]->uiOpts		= OPT_CUNPROC_NONE;
			pp [ui]->uiOpts	|= OPT_CUNPROC_ALLOCATED;
		}
		// Flush log file.
		++ ui;
		pp [ui] = malloc (sizeof (CUNILOG_PROCESSOR));
		if (pp [ui])
		{
			pp [ui]->pSCUNILOGTARGET = put;
			pp [ui]->task		= cunilogProcessFlushLogFile;
			pp [ui]->thrtype	= cunilogProcessAppliesTo_HourChanged;
			pp [ui]->thr		= 0;
			pp [ui]->cur		= 0;
			pp [ui]->pData		= NULL;
			pp [ui]->uiOpts		= OPT_CUNPROC_NONE;
			pp [ui]->uiOpts	|= OPT_CUNPROC_FORCE_NEXT | OPT_CUNPROC_ALLOCATED;
		}
		// This is the last one.
		++ ui;
		if (pn)
			*pn = ui;
	}
	return pp;
}
*/

static inline enum cunilogprocessfrequency defaultFrequencyFromPostfix (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	switch (put->culogPostfix)
	{
		case cunilogPostfixNone:
			return cunilogProcessAppliesTo_nAlways;
		case cunilogPostfixMinute:
		case cunilogPostfixMinuteT:
			return cunilogProcessAppliesTo_MinuteChanged;
		case cunilogPostfixHour:
		case cunilogPostfixHourT:
			return cunilogProcessAppliesTo_HourChanged;
		case cunilogPostfixDay:
			return cunilogProcessAppliesTo_DayChanged;
		case cunilogPostfixWeek:
			return cunilogProcessAppliesTo_WeekChanged;
		case cunilogPostfixMonth:
			return cunilogProcessAppliesTo_MonthChanged;
		case cunilogPostfixYear:
			return cunilogProcessAppliesTo_YearChanged;
		case cunilogPostfixAmountEnumValues:
			ubf_assert_msg (false, "Illegal value");
			return cunilogProcessAppliesTo_nAlways;
	}
	return cunilogProcessAppliesTo_nAlways;
}

static inline void correctDefaultFrequency (CUNILOG_PROCESSOR *cp, SCUNILOGTARGET *put)
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

static inline void defaultFrequenciesAndMaxToRotate (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(put->cprocessors);
	ubf_assert_non_0	(put->nprocessors);

	CUNILOG_PROCESSOR		*cp;
	CUNILOG_ROTATION_DATA	*prPrev				= NULL;
	CUNILOG_ROTATION_DATA	*prCurr;

	unsigned int n = 0;
	while (n < put->nprocessors)
	{
		cp = put->cprocessors [n];
		correctDefaultFrequency (cp, put);
		if (cunilogProcessRotateLogfiles == cp->task)
		{
			prCurr = cp->pData;
			if (prPrev)
			{
				if (CUNILOG_MAX_ROTATE_AUTO == prPrev->nMaxToRotate)
					prPrev->nMaxToRotate = prCurr->nIgnore;
			}
			prPrev = prCurr;
		}
		++ n;
	}
}

static void prepareProcessors (SCUNILOGTARGET *put, CUNILOG_PROCESSOR **cp, unsigned int np)
{
	ubf_assert_non_NULL (put);

	if (NULL == cp || 0 == np)
	{
		put->cprocessors = stdcupp;
		put->nprocessors = GET_ARRAY_LEN (stdcupp);
	} else
	{
		/*
			This was originally for testing but is not required here. We'll provide the caller
			with an option to dynamically allocate standard processors at a later time.

		put->cprocessors = NewStandardProcessors (put, &put->nprocessors);
		if (put->cprocessors)
			cunilogSetProcessorsAllocated (put);
		*/

		// The caller obviously provided processors.
		//setProcessorsSCUNILOGTARGET (put, cp, np);
		put->cprocessors = cp;
		put->nprocessors = np;
	}
	defaultFrequenciesAndMaxToRotate (put);
}

static void prepareSCUNILOGTARGETinitFilenameBuffers (SCUNILOGTARGET *put, size_t lnTotal)
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

static bool prepareSCUNILOGTARGETforLogging (SCUNILOGTARGET *put)
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
	size_t lnUnderscore		= lnRoomForStamp ? 1 : 0;			// The underscore that separates
																//	the appname from the timestamp.
	ubf_assert (lnRoomForStamp <= LEN_ISO8601DATEHOURANDMINUTE);

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
	prepareSCUNILOGTARGETinitFilenameBuffers (put, lnTotal);

	if (isUsableSMEMBUF (&put->mbLogfileName) && isUsableSMEMBUF (&put->mbLogFileMask))
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

		// Create name of the found file.
		copySMEMBUF (&put->mbFilToRotate, &put->mbLogPath);

		initSMEMBUFtoSize (&put->mbLogEventLine, CUNILOG_INITIAL_EVENTLINE_SIZE);
		if (isUsableSMEMBUF (&put->mbLogEventLine))
			cunilogSetEvtLineAllocated (put);
		cunilogSetTargetInitialised (put);
		return true;
	} else
	{
		put->szDateTimeStamp = NULL;
		ubf_assert_non_NULL (put->szDateTimeStamp);
		return false;
	}
}

static bool hasSCUNILOGTARGETqueue (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	return	(
					cunilogSingleThreadedSeparateLoggingThread	== put->culogType
				||	cunilogMultiThreadedSeparateLoggingThread	== put->culogType
			);
}

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool InitSCUNILOGTARGETqueuesemaphore (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (hasSCUNILOGTARGETqueue (put))
		{
			#ifdef OS_IS_WINDOWS
				// See
				//	https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createsemaphorew .
				put->sm.hSemaphore = CreateSemaphoreW (NULL, 0, MAXLONG, NULL);
				return NULL != put->sm.hSemaphore;
			#else
				int i = sem_init (&put->sm.tSemaphore, 0, 0);
				ubf_assert (0 == i);
				return 0 == i;
			#endif
		}
		// If no semaphore is required, not creating it is seen as success.
		return true;
	}
#else
	#define InitSCUNILOGTARGETqueuesemaphore(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void DoneSCUNILOGTARGETqueuesemaphore (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (hasSCUNILOGTARGETqueue (put))
		{
			#ifdef OS_IS_WINDOWS
				CloseHandle (put->sm.hSemaphore);
				put->sm.hSemaphore = NULL;
			#else
				int i = sem_destroy (&put->sm.tSemaphore);
				ubf_assert (0 == i);
				UNREFERENCED_PARAMETER (i);
			#endif
		}
	}
#else
	#define DoneSCUNILOGTARGETqueuesemaphore(x)
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static bool InitSCUNILOGTARGETqueue (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (hasSCUNILOGTARGETqueue (put))
		{
			put->qu.first	= NULL;
			put->qu.last	= NULL;
			put->qu.num		= 0;
		}
		// If no semaphore is required, not creating it is seen as success.
		return true;
	}
#else
	#define InitSCUNILOGTARGETqueue(x)
#endif

static bool StartSeparateLoggingThread_ifNeeded (SCUNILOGTARGET *put)
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
static inline void InitSCUNILOGTARGETdumpstructs (SCUNILOGTARGET *put)
{
	UNUSED (put);

	ubf_assert_non_NULL (put);

	//put->psdump = NULL;
}

static inline void initSCUNILOGTARGEToptionFlags (SCUNILOGTARGET *put, runProcessorsOnStartup rp)
{
	ubf_assert_non_NULL (put);
	ubf_assert	(
						cunilogRunProcessorsOnStartup		== rp
					||	cunilogDontRunProcessorsOnStartup	== rp
				);

	put->uiOpts = CUNILOGTARGET_NO_FLAGS;
	if (cunilogRunProcessorsOnStartup == rp)
		cunilogSetRunAllProcessorsOnStartup (put);
}

static inline void initFilesListInSCUNILOGTARGET (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	vec_init (&put->fls);
	InitSBULKMEM (&put->sbm, CUNILOG_STD_BULK_ALLOC_SIZE);

	// Note that we do not allocate any bulk memory here yet. If for instance the caller
	//	hasn't provided a rotation processor we may not even need one.
}

static inline void initPrevTimestamp (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	size_t lenPostfixStamp = lenDateTimeStampFromPostfix (put->culogPostfix);
	memset (put->cPrevDateTimeStamp, 0, lenPostfixStamp);
}

#ifdef PLATFORM_IS_POSIX
	// The plain logging folder name is not used on Windows. It is only required
	//	for opendir () on POSIX. This might change in the future as I can imagine
	//	that some custom processor might also benefit from it.
	static void InitSCUNILOGTARGETmbLogFold (SCUNILOGTARGET *put)
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
	#define InitSCUNILOGTARGETmbLogFold(x)
#endif

static inline bool initCommonMembersAndPrepareSCUNILOGTARGET (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	str_remove_path_navigators (put->mbLogPath.buf.pch, &put->lnLogPath);
	put->errorCB = NULL;
	InitSCUNILOGNPI							(&put->scuNPI);
	DBG_INIT_CNTTRACKER						(put->evtLineTracker);
	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		put->nPendingNoRotEvts				= 0;
		put->nPausedEvents					= 0;
	#endif
	put->dumpWidth							= enDataDumpWidth16;
	initPrevTimestamp						(put);
	InitSCUNILOGTARGETmbLogFold				(put);
	InitSCUNILOGTARGETdumpstructs			(put);
	InitCUNILOG_LOCKER						(put);
	InitSCUNILOGTARGETqueuesemaphore		(put);
	InitSCUNILOGTARGETqueue					(put);
	initFilesListInSCUNILOGTARGET			(put);
	StartSeparateLoggingThread_ifNeeded		(put);
	return prepareSCUNILOGTARGETforLogging	(put);
}

#ifdef DEBUG
	void assertSaneParametersSCUNILOGTARGET	(
	  enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
	, enum cunilogpostfix		postfix
	, enum cunilogeventTSformat	unilogTSformat		// The format of an event timestamp.
	, enum enLineEndings		unilogNewLine
	, runProcessorsOnStartup	rp					// Run/don't run all processors instantly.
											)
	{
		ubf_assert (0 <= relLogPath);
		ubf_assert (cunilogLogPath_AmountEnumValues > relLogPath);
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
	#define assertSaneParametersSCUNILOGTARGET(rP, tpy, psf, ts, nl, rp)
#endif

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
{
	ubf_assert_non_NULL (put);
	assertSaneParametersSCUNILOGTARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	size_t			lnLogPath		= (size_t) -1 != lenLogPath	? lenLogPath : strlen (szLogPath);
	size_t			lnAppName		= (size_t) -1 != lenAppName	? lenAppName : strlen (szAppName);

	initSCUNILOGTARGEToptionFlags (put, rp);
	put->culogPostfix		= postfix;
	put->culogType			= unilogTypeFromArgument (type);
	put->unilogEvtTSformat	= unilogTSformat;
	put->unilogNewLine		= unilogNewLine;
	char *szLP = CreateLogPathInSUNILOGTARGET (put, szLogPath, lnLogPath, relLogPath);
	if (NULL == szLP && cunilogLogPath_isAbsolute == relLogPath)
	{
		#ifndef CUNILOG_BUILD_TEST_FNCTS
			ubf_assert_msg	(
				false,
				"szLogPath cannot be relative or NULL if cunilogLogPath_isAbsolute is given"
							);
		#endif
		return NULL;
	}
	CreateAppNameInSUNILOGTARGET (put, szAppName, lnAppName);
	prepareProcessors (put, cuProcessorList, nProcessors);
	return initCommonMembersAndPrepareSCUNILOGTARGET (put) ? put : NULL;
}

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
	{
		ubf_assert_non_NULL (put);
		ubf_assert (0 <= relLogPath);
		ubf_assert (cunilogLogPath_AmountEnumValues > relLogPath);
		ubf_assert (0 <= type);
		ubf_assert (cunilogTypeAmountEnumValues > type);

		SCUNILOGTARGET	*prt;

		prt = InitSCUNILOGTARGETex	(
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
{
	assertSaneParametersSCUNILOGTARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	SCUNILOGTARGET	*pu;							// Return value.
	size_t			lnUNILOGTARGET	= ALIGNED_SIZE (sizeof (SCUNILOGTARGET), CUNILOG_DEFAULT_ALIGNMENT);
	size_t			lnTotal			= lnUNILOGTARGET;
	size_t			lnLP;
	size_t			lnAP;
	SMEMBUF			logpath			= SMEMBUF_INITIALISER;
	SMEMBUF			appname			= SMEMBUF_INITIALISER;

	size_t			lnLogPath		= (size_t) -1 != lenLogPath	? lenLogPath : strlen (szLogPath);
	size_t			lnAppName		= (size_t) -1 != lenAppName	? lenAppName : strlen (szAppName);

	if (szLogPath && lnLogPath)
	{
		if (!isDirSep (szLogPath [lnLogPath -1]))
			lnLP = ALIGNED_SIZE (lnLogPath + 2, CUNILOG_DEFAULT_ALIGNMENT);
		else 
			lnLP = ALIGNED_SIZE (lnLogPath + 1, CUNILOG_DEFAULT_ALIGNMENT);
		lnTotal += lnLP;
	} else
	{	// No log path given.
		if (cunilogLogPath_isAbsolute == relLogPath)
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
		szLogPath = logpath.buf.pch;
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
		initSCUNILOGTARGEToptionFlags (pu, rp);
		pu->uiOpts |= CUNILOGTARGET_ALLOCATED;
		initSMEMBUF (&pu->mbLogPath);
		pu->mbLogPath.buf.pcc = (char *) pu + ALIGNED_SIZE (lnUNILOGTARGET, CUNILOG_DEFAULT_ALIGNMENT);
		memcpy (pu->mbLogPath.buf.pch, szLogPath, lnLogPath + 1);
		if (!isDirSep (szLogPath [lnLogPath -1]))
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
		prepareProcessors (pu, cuProcessorList, nProcessors);
		initCommonMembersAndPrepareSCUNILOGTARGET (pu);
	}
	if (isUsableSMEMBUF (&logpath))
		doneSMEMBUF (&logpath);
	if (isUsableSMEMBUF (&appname))
		doneSMEMBUF (&appname);
	return pu;
}

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
{
	assertSaneParametersSCUNILOGTARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	SCUNILOGTARGET	*pu;

	if (put)
	{
		pu = put;
		InitSCUNILOGTARGETex	(
			pu,
			szLogPath, lenLogPath, szAppName, lenAppName, relLogPath,
			type, postfix, cuProcessorList, nProcessors,
			unilogTSformat, unilogNewLine, rp
							);
	} else
	{
		pu = CreateNewSCUNILOGTARGET	(
				szLogPath, lenLogPath, szAppName, lenAppName, relLogPath,
				type, postfix, cuProcessorList, nProcessors, 
				unilogTSformat, unilogNewLine, rp
									);
	}
	if (pu && pu->mbAppName.buf.pch)
	{
	} else
	{
		pu = DoneSCUNILOGTARGET (pu);
	}
	return pu;
}

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
{
	assertSaneParametersSCUNILOGTARGET	(
		relLogPath, type, postfix, unilogTSformat, unilogNewLine, rp
										);

	return InitSCUNILOGTARGETex	(
		pSCUNILOGTARGETstatic, szLogPath, lenLogPath, szApplication, lenApplication, relLogPath,
		type, postfix, cuProcessorList, nProcessors, unilogTSformat, unilogNewLine, rp
								);
}

SCUNILOGTARGET *InitSCUNILOGTARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelLogPath		relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
{
	ubf_assert (0 <= relLogPath);
	ubf_assert (cunilogLogPath_AmountEnumValues > relLogPath);
	ubf_assert (0 <= type);
	ubf_assert (cunilogTypeAmountEnumValues > type);

	return InitSCUNILOGTARGETex	(
				pSCUNILOGTARGETstatic,
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

const char *getAbsoluteLogPathSCUNILOGTARGET (SCUNILOGTARGET *put, size_t *plen)
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

#ifdef DEBUG
	void configSCUNILOGTARGETcunilogpostfix (SCUNILOGTARGET *put, enum cunilogeventTSformat tsf)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= tsf);
		ubf_assert			(cunilogEvtTS_AmountEnumValues > tsf);

		put->unilogEvtTSformat = tsf;		
	}
#endif

#ifdef DEBUG
	void configSCUNILOGTARGETcunilognewline (SCUNILOGTARGET *put, newline_t nl)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= nl);
		ubf_assert			(cunilogNewLineAmountEnumValues > nl);

		put->unilogNewLine = nl;
	}
#endif

#ifdef DEBUG
	void configSCUNILOGTARGETrunProcessorsOnStartup (SCUNILOGTARGET *put, runProcessorsOnStartup rp)
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

#ifdef DEBUG
	void configSCUNILOGTARGETprocessorList	(
					SCUNILOGTARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	{
		ubf_assert_non_NULL	(put);

		prepareProcessors (put, cuProcessorList, nProcessors);
	}
#endif

void configSCUNILOGTARGETdisableTaskProcessors (SCUNILOGTARGET *put, enum cunilogprocesstask task)
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

void configSCUNILOGTARGETenableTaskProcessors (SCUNILOGTARGET *put, enum cunilogprocesstask task)
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

void configSCUNILOGTARGETdisableEchoProcessor (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL (put->cprocessors);

	configSCUNILOGTARGETdisableTaskProcessors (put, cunilogProcessEchoToConsole);
}

void configSCUNILOGTARGETenableEchoProcessor (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL (put->cprocessors);

	configSCUNILOGTARGETenableTaskProcessors (put, cunilogProcessEchoToConsole);
}

void EnterSCUNILOGTARGET (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	EnterCUNILOG_LOCKER (put);
}

void LeaveSCUNILOGTARGET (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	LeaveCUNILOG_LOCKER (put);
}

static void CloseCUNILOG_LOGFILEifOpen (CUNILOG_LOGFILE *cl)
{
	#ifdef OS_IS_WINDOWS
		if (cl->hLogFile)
		{
			CloseHandle (cl->hLogFile);
			cl->hLogFile = NULL;
		}
	#else
		if (cl->fLogFile)
		{
			fclose (cl->fLogFile);
			cl->fLogFile = 0;
		}
	#endif
}

static void DoneSCUNILOGTARGETprocessors (SCUNILOGTARGET *psu)
{
	ubf_assert_non_NULL (psu);

	unsigned int			np = psu->nprocessors;
	unsigned int			ui;
	CUNILOG_PROCESSOR		*cp;
	CUNILOG_ROTATION_DATA	*rt;

	for (ui = 0; ui < np; ++ ui)
	{
		cp = psu->cprocessors [ui];
		switch (cp->task)
		{
			case cunilogProcessNoOperation:
			case cunilogProcessEchoToConsole:
			case cunilogProcessUpdateLogFileName:
			case cunilogProcessFlushLogFile:
			case cunilogProcessCustomProcessor:
			case cunilogProcessTargetRedirector:
			case cunilogProcessAmountEnumValues:
				break;
			case cunilogProcessWriteToLogFile:
				CloseCUNILOG_LOGFILEifOpen (cp->pData);
				break;
			case cunilogProcessRotateLogfiles:
				rt = cp->pData;
				if (cunilogHasRotatorFlag_USE_MBSRCMASK (rt))
					doneSMEMBUF (&rt->mbSrcMask);
				if (cunilogHasRotatorFlag_USE_MBDSTFILE (rt))
					doneSMEMBUF (&rt->mbDstFile);
				break;
		}
	}

	if (cunilogIsProcessorsAllocated (psu))
	{
		for (ui = 0; ui < np; ++ ui)
		{
			cp = psu->cprocessors [ui];
			free (cp);
		}
	}
}

/*
	This function is a no-op.
*/
static void DoneSCUNILOGTARGETpsdump (SCUNILOGTARGET *psu)
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

static void DoneSCUNILOGTARGETmembers (SCUNILOGTARGET *put)
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
	if (cunilogIsEvtLineAllocated (put))
		freeSMEMBUF (&put->mbLogEventLine);
	DoneSCUNILOGNPI (&put->scuNPI);
	DoneCUNILOG_LOCKER (put);
	DoneSCUNILOGTARGETqueuesemaphore (put);
	vec_deinit (&put->fls);
	DoneSBULKMEM (&put->sbm);
	DoneSCUNILOGTARGETpsdump (put);
}

SCUNILOGTARGET *DoneSCUNILOGTARGET (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);
	ubf_assert (cunilogIsTargetInitialised (put));

	DoneSCUNILOGTARGETprocessors (put);
	DoneSCUNILOGTARGETmembers (put);
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
}
;
*/
const char *EventSeverityTexts []	=
{
	/*	 0	*/	"",
	/*	 1	*/	"   ",
	/*	 2	*/	"EMG",
	/*	 3	*/	"NTC",
	/*	 4	*/	"INF",
	/*	 5	*/	"MSG",
	/*	 6	*/	"WRN",
	/*	 7	*/	"ERR",
	/*	 8	*/	"FAI",
	/*	 9	*/	"CRI",
	/*	10	*/	"FTL",
	/*	11	*/	"DBG",
	/*	12	*/	"TRC",
	/*	13	*/	"DET",
	/*	14	*/	"ILG"
};

static inline const char *unilogTextFromEventSeverity (enum cunilogeventseverity evSeverity)
{
	// Check consistency between unilogstruct.h and the declarations here.
	ubf_assert (0 == cunilogEvtSeverityNone);
	ubf_assert (1 == cunilogEvtSeverityBlanks);
	ubf_assert (2 == cunilogEvtSeverityEmergency);
	ubf_assert (3 == cunilogEvtSeverityNotice);
	ubf_assert (4 == cunilogEvtSeverityInfo);
	ubf_assert (5 == cunilogEvtSeverityMessage);
	ubf_assert (6 == cunilogEvtSeverityWarning);
	ubf_assert (7 == cunilogEvtSeverityError);
	ubf_assert (8 == cunilogEvtSeverityFail);
	ubf_assert (9 == cunilogEvtSeverityCritical);
	ubf_assert (10 == cunilogEvtSeverityFatal);
	ubf_assert (11 == cunilogEvtSeverityDebug);
	ubf_assert (12 == cunilogEvtSeverityTrace);
	ubf_assert (13 == cunilogEvtSeverityDetail);
	ubf_assert (13 == cunilogEvtSeverityVerbose);
	ubf_assert (14 == cunilogEvtSeverityIllegal);
	ubf_assert (cunilogEvtSeverityIllegal > evSeverity);

	ubf_assert (0 == strlen (EventSeverityTexts [cunilogEvtSeverityNone]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityBlanks]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityEmergency]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityNotice]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityInfo]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityMessage]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityWarning]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityError]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityFail]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityCritical]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityFatal]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityDebug]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityTrace]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityDetail]));
	ubf_assert (3 == strlen (EventSeverityTexts [cunilogEvtSeverityVerbose]));

	return EventSeverityTexts [evSeverity];
}

static inline size_t requiredEventSeverityChars (cueventseverity sev)
{
	// "" or "INF" + " ".
	return cunilogEvtSeverityNone == sev ? 0 : 3 + 1;
}

static inline size_t writeEventSeverity (char *szOut, cueventseverity sev)
{
	ubf_assert_non_NULL (szOut);

	if (cunilogEvtSeverityNone != sev)
	{
		memcpy (szOut, unilogTextFromEventSeverity (sev), 3);
		szOut [3] = ' ';
		return 3 + 1;
	}
	return 0;
}

static inline size_t requiredFullstopChars (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);

	return cunilogIsEventAutoFullstop (pev) ? 1 : 0;
};

static inline size_t writeFullStop (char *szOut, SCUNILOGEVENT *pev)
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

static inline size_t eventLenNewline (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);

	return lnLineEnding (pev->pSCUNILOGTARGET->unilogNewLine);
}

static inline enum enLineEndings eventLineEnding (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);

	return pev->pSCUNILOGTARGET->unilogNewLine;
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

static inline size_t requiredEvtLineTimestampAndSeverityLength (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);

	size_t	r;

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " ".
	r = evtTSFormats [pev->pSCUNILOGTARGET->unilogEvtTSformat].len;
	// "WRN" + " "
	r += requiredEventSeverityChars (pev->evSeverity);

	return r;
}

static inline size_t requiredEventLineSizeU8 (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	ubf_assert (cunilogEvtTypeNormalText == pev->evType);

	size_t	r;

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " " + "WRN" + " ".
	r = requiredEvtLineTimestampAndSeverityLength (pev);
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// Actual data.
	r += pev->lenDataToLog;
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// "."
	r += requiredFullstopChars (pev);
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// CR + LF max.
	r += eventLenNewline (pev);
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// Terminating NUL.
	r += 1;
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	return r;
}

/*
	writeEventLineFromSUNILOGEVENTU8

	The caller is responsible for szEventLine to point to a buffer big enough to hold the
	event line. The function requiredEventLineSize () obtains this size.
*/
static size_t writeEventLineFromSUNILOGEVENTU8 (char *szEventLine, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (szEventLine);
	ubf_assert_non_NULL (pev);
	ubf_assert (cunilogEvtTypeNormalText == pev->evType);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised (pev->pSCUNILOGTARGET));

	char	*szOrg = szEventLine;

	DBG_RESET_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker);

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " " (see table above).
	evtTSFormats [pev->pSCUNILOGTARGET->unilogEvtTSformat].fnc (szEventLine, pev->stamp);
	//ISO8601_from_UBF_TIMESTAMP (szEventLine, pue->stamp);

	szEventLine += evtTSFormats [pev->pSCUNILOGTARGET->unilogEvtTSformat].len;
	szEventLine += writeEventSeverity (szEventLine, pev->evSeverity);
	DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, szEventLine - szOrg);

	memcpy (szEventLine, pev->szDataToLog, pev->lenDataToLog);
	szEventLine += pev->lenDataToLog;
	DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, szEventLine - szOrg);

	szEventLine += writeFullStop (szEventLine, pev);
	DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, szEventLine - szOrg);

	// We've reserved space for a new line character sequence in requiredEventLineSizeU8 ()
	//	but we're not going to add this here yet. Instead, we NUL-terminate. This simply lets
	//	us call puts (). We'll add the new line sequence later in the processor that writes
	//	to the logfile.

	// The NUL byte is useful for OS API functions.
	szEventLine [0] = ASCII_NUL;
	return szEventLine - szOrg;
}

/*
static bool obtainValidSCUNILOGDUMPinSCUNILOGTARGET (SCUNILOGTARGET *put)
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
						SCUNILOGEVENT		*pev
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

	SCUNILOGTARGET *put = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (put);

	size_t	r;

	/*
		Timestamp + Type + caption, etc.
	*/

	// "YYYY-MM-DD HH:MI:SS.000+01:00" + " " + "WRN" + " ".
	r = requiredEvtLineTimestampAndSeverityLength (pev);
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// The width of the caption length.
	size_t ui			= widthOfCaptionLengthFromCunilogEventType (pev->evType);
	// Its actual length. This needs to be added to our return value.
	size_t lenCaption	= readCaptionLengthFromData (pev->szDataToLog, ui);
	*pDumpData			= pev->szDataToLog + ui + lenCaption;
	*width				= ui;
	*len				= lenCaption;
	r += lenCaption;
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// "."
	r += requiredFullstopChars (pev);
	// New line.
	r += eventLenNewline (pev);
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// Actual dump data size. Includes NUL terminator.
	size_t sizHexDmp = hxdmpRequiredSize (pev->lenDataToLog, put->dumpWidth, eventLineEnding (pev));
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, sizHexDmp);
	r += sizHexDmp;
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// ASCII TAB.
	++ r;

	// To be considered in the future:
	//	It would be faster to just always reserve UBF_UINT64_LEN octets instead of
	//	performing the uint -> ASCII transformation.
	char cDmpOctets [UBF_UINT64_SIZE];
	//r += ubf_str_from_uint64 (cDmpOctets, pev->lenDataToLog);
	ubf_str__from_uint64 (cDmpOctets, 10, pev->lenDataToLog);
	r += 10;
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	r += lnSummaryOctets;
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	// New line.
	r += eventLenNewline (pev);
	DBG_TRACK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, r);

	#ifdef DEBUG
		++ r;												// Space for a debug marker.
	#endif

	return r;
}

static size_t createDumpEventLineFromSUNILOGEVENT (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	ubf_assert (isInitialisedSMEMBUF (&pev->pSCUNILOGTARGET->mbLogEventLine));
	ubf_assert	(
						cunilogEvtTypeHexDumpWithCaption8	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption16	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption32	== pev->evType
					||	cunilogEvtTypeHexDumpWithCaption64	== pev->evType
				);

	SCUNILOGTARGET *put = pev->pSCUNILOGTARGET;
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
		szOut += writeEventSeverity (szOut, pev->evSeverity);
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, szOut - szOrg);

		// Caption.
		memcpy (szOut, pev->szDataToLog + captionWidth, captionLen);
		szOut += captionLen;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, szOut - szOrg);

		// "." + new line.
		size_t lenNewLine = eventLenNewline (pev);
		szOut += writeFullStop (szOut, pev);
		memcpy (szOut, ccLineEnding (eventLineEnding (pev)), lenNewLine);
		szOut += lenNewLine;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, szOut - szOrg);

		put->lnLogEventLine = szOut - szOrg;
		char *szHexDmpOut = szOut;
		size_t sizHx = hxdmpWriteHexDump	(
						szHexDmpOut, pDumpData, pev->lenDataToLog,
						put->dumpWidth, put->unilogNewLine
											);
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, sizHx + 1);
		ubf_assert (CUNILOG_DEFAULT_DBG_CHAR == put->mbLogEventLine.buf.pch [lenTotal]);
		put->lnLogEventLine += sizHx;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, put->lnLogEventLine + 1);

		szOut = szHexDmpOut + sizHx;
		szOut [0] = ASCII_TAB;
		++ szOut;
		++ put->lnLogEventLine;

		//size_t lnOctets = ubf_str_from_uint64 (szOut, pev->lenDataToLog);
		size_t lnOctets = 10;
		ubf_str__from_uint64 (szOut, 10, pev->lenDataToLog);
		put->lnLogEventLine += lnOctets;
		ubf_assert (CUNILOG_DEFAULT_DBG_CHAR == put->mbLogEventLine.buf.pch [lenTotal]);
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, put->lnLogEventLine + 1);

		szOut += lnOctets;
		memcpy (szOut, scSummaryOctets, lnSummaryOctets + 1);
		put->lnLogEventLine += lnSummaryOctets;
		DBG_TRACK_CHECK_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker, put->lnLogEventLine + 1);

		return put->lnLogEventLine;
	}
	return CUNILOG_SIZE_ERROR;
}

static size_t createU8EventLineFromSUNILOGEVENT (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	ubf_assert (isInitialisedSMEMBUF (&pev->pSCUNILOGTARGET->mbLogEventLine));
	ubf_assert (cunilogEvtTypeNormalText == pev->evType);

	size_t requiredEvtLineSize;

	requiredEvtLineSize = requiredEventLineSizeU8 (pev);
	growToSizeSMEMBUF64aligned (&pev->pSCUNILOGTARGET->mbLogEventLine, requiredEvtLineSize);
	if (isUsableSMEMBUF (&pev->pSCUNILOGTARGET->mbLogEventLine))
	{
		pev->pSCUNILOGTARGET->lnLogEventLine =
			writeEventLineFromSUNILOGEVENTU8 (pev->pSCUNILOGTARGET->mbLogEventLine.buf.pch, pev);
		return pev->pSCUNILOGTARGET->lnLogEventLine;
	}
	return CUNILOG_SIZE_ERROR;
}

static size_t createEventLineFromSUNILOGEVENT (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	ubf_assert (isInitialisedSMEMBUF (&pev->pSCUNILOGTARGET->mbLogEventLine));

	DBG_RESET_CNTTRACKER (pev->pSCUNILOGTARGET->evtLineTracker);

	switch (pev->evType)
	{
		case cunilogEvtTypeHexDumpWithCaption8:
		case cunilogEvtTypeHexDumpWithCaption16:
		case cunilogEvtTypeHexDumpWithCaption32:
		case cunilogEvtTypeHexDumpWithCaption64:
			return createDumpEventLineFromSUNILOGEVENT	(pev);
		case cunilogEvtTypeNormalText:
			return createU8EventLineFromSUNILOGEVENT	(pev);
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

static SCUNILOGEVENT *CreateSCUNILOGEVENTandData	(
					SCUNILOGTARGET				*put,
					cueventseverity				sev,
					const char					*ccCapt,
					size_t						lenCapt,
					cueventtype					type,
					const char					*ccData,
					size_t						siz
													)
{
	ubf_assert_non_NULL	(put);
	ubf_assert_non_NULL	(ccData);
	ubf_assert			(USE_STRLEN != siz);
	ubf_assert			(0 <= type);
	ubf_assert			(cunilogEvtTypeAmountEnumValues > type);

	size_t			wl		= widthOfCaptionLengthFromCunilogEventType (type);
	ubf_assert (wl || 0 == lenCapt);						// If 0 == wl we can't have a caption.
	size_t			aln		= ALIGNED_SIZE (sizeof (SCUNILOGEVENT), CUNILOG_DEFAULT_ALIGNMENT);
	size_t			ln		= aln + wl + lenCapt + siz;
	SCUNILOGEVENT	*pev	= ubf_malloc (ln);

	if (pev)
	{
		unsigned char *pData = (unsigned char *) pev + aln;
		FillSCUNILOGEVENT	(
			pev, put,
			CUNILOGEVENT_ALLOCATED,
			LocalTime_UBF_TIMESTAMP (),
			sev, type,
			pData, siz, ln
							);
		if (wl)
		{
			storeCaptionLength (&pData, wl, lenCapt);
			memcpy (pData, ccCapt, lenCapt);
			pData += lenCapt;
		}
		memcpy (pData, ccData, siz);
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

SCUNILOGEVENT *CreateSCUNILOGEVENT_Data		(
					SCUNILOGTARGET				*put,
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

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENTandData	(
							put, sev, ccCapt, lenCapt,
							cunilogEventTypeFromLength (lenCapt),
							ccData, siz
													);
	return pev;
}

SCUNILOGEVENT *CreateSCUNILOGEVENT_Text		(
					SCUNILOGTARGET				*put,
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

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENTandData	(
							put, sev, NULL, 0, cunilogEvtTypeNormalText,
							ccText, len
													);
	return pev;
}

SCUNILOGEVENT *CreateSUNILOGEVENT_W	(
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

SCUNILOGEVENT *DuplicateSCUNILOGEVENT (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);

	size_t size;

	if (pev->sizEvent)
		size = pev->sizEvent;
	else
		size = sizeof (SCUNILOGEVENT);
	SCUNILOGEVENT *pnev = ubf_malloc (size);
	if (pnev)
	{
		memcpy (pnev, pev, size);
		cunilogSetEventAllocated (pnev);
	}
	return pnev;
}

SCUNILOGEVENT *DoneSCUNILOGEVENT (SCUNILOGTARGET *put, SCUNILOGEVENT *pev)
{
	if (NULL == put || put == pev->pSCUNILOGTARGET)
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

void cunilogInvokeErrorCallback (int64_t error, CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);

	if (CUNILOG_UNKNOWN_ERROR == error)
	{
		#ifdef PLATFORM_IS_WINDOWS
			error = GetLastError ();
		#else
			error = errno;
		#endif
	}

	if (pev->pSCUNILOGTARGET->errorCB)
	{
		errCBretval rv = pev->pSCUNILOGTARGET->errorCB (error, cup, pev);
		ubf_assert (0 <= rv);
		ubf_assert (cunilogErrCB_AmountEnumValues > rv);

		switch (rv)
		{
			case cunilogErrCB_next_processor:
				break;
			case cunilogErrCB_next_event:
				cunilogSetEventStopProcessing (pev);
				break;

			// To do!!!
			case cunilogErrCB_shutdown:
				ubf_assert (false);
				break;

			// To do!!!
			// Default is to cancel the target.
			case cunilogErrCB_cancel:
			default:
				ubf_assert (false);
				break;
		}
	}
}

/*
	The dummy/no-operation processor.
*/
static bool cunilogProcessNoneFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
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

		if (len)
		{
			switch (ourCunilogConsoleOutputCodePage)
			{
				case cunilogConsoleIsUTF8:		return puts		(szOutput);
				case cunilogConsoleIsUTF16:		return putsU8	(szOutput);
				case cunilogConsoleIsNeither:	return puts		(szOutput);
				default:						return puts		(szOutput);
			}
		} else
		{
			switch (ourCunilogConsoleOutputCodePage)
			{
				case cunilogConsoleIsUTF8:		return puts		("");
				case cunilogConsoleIsUTF16:		return putsU8	("");
				case cunilogConsoleIsNeither:	return puts		("");
				default:						return puts		("");
			}
		}
	}
#endif

static bool cunilogProcessEchoFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	UNREFERENCED_PARAMETER (cup);
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);

	if (cunilogIsNoEcho (pev->pSCUNILOGTARGET))
		return true;

	// The actual task of this processor: Echo the event line.
	//	Note that we can rely on the following conditions here:
	//		- The line to output is NUL-terminated.
	//		- It only consists of printable characters.
	//		- The length of the event line has been stored correctly.
	//		- If we require a lock, we have it already.

	int ips;
	#ifdef PLATFORM_IS_WINDOWS
		ips = cunilogPutsWin	(
				pev->pSCUNILOGTARGET->mbLogEventLine.buf.pch,
				pev->pSCUNILOGTARGET->lnLogEventLine
								);
	#else
		if (pev->pSCUNILOGTARGET->lnLogEventLine)
			ips = puts (pev->pSCUNILOGTARGET->mbLogEventLine.buf.pch);
		else
			ips = puts ("");
	#endif
	if (EOF == ips)
	{	// "Bad file descriptor" might not be the best error here but what's better?
		ubf_assert_msg (false, "Error writing to stdout.");
		cunilogInvokeErrorCallback (EBADF, cup, pev);
	}
	return true;
}

static bool cunilogProcessUpdateLogFileNameFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	UNREFERENCED_PARAMETER (cup);
	ubf_assert_non_NULL (pev);
	
	SCUNILOGTARGET	*put = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (put);

	#ifdef DEBUG
		char *sz = put->mbLogfileName.buf.pch;
		UNREFERENCED_PARAMETER (sz);
	#endif

	size_t lenPostfixStamp = lenDateTimeStampFromPostfix (put->culogPostfix);
	memcpy (put->cPrevDateTimeStamp, put->szDateTimeStamp, lenPostfixStamp);

	obtainDateAndTimeStamp (put->szDateTimeStamp, pev->stamp, put->culogPostfix);
	put->szDateTimeStamp [lenPostfixStamp] = '.';
	return true;
}

static bool cunilogOpenLogFile (CUNILOG_LOGFILE *pl, const char *szLogFileName)
{
	#ifdef PLATFORM_IS_WINDOWS
		pl->hLogFile = CreateFileU8	(
						szLogFileName, CUNILOG_DEFAULT_OPEN_MODE,
						FILE_SHARE_DELETE | FILE_SHARE_READ,
						NULL, OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
									);
		return NULL != pl->hLogFile && INVALID_HANDLE_VALUE != pl->hLogFile;
	#else
		// We always (and automatically) append.
		pl->fLogFile = fopen (szLogFileName, CUNILOG_DEFAULT_OPEN_MODE);
		return NULL != pl->fLogFile;
	#endif
}

/*
	Closes the previous file and opens the new one.
*/
static bool cunilogOpenNewLogFile (CUNILOG_LOGFILE *pl, const char *szLogFileName)
{
	#ifdef OS_IS_WINDOWS
		CloseHandle (pl->hLogFile);
		return cunilogOpenLogFile (pl, szLogFileName);
	#else
		fclose (pl->fLogFile);
		return cunilogOpenLogFile (pl, szLogFileName);
	#endif
}

static inline bool requiresOpenLogFile (CUNILOG_LOGFILE *pl)
{
	#ifdef OS_IS_WINDOWS
		return NULL == pl->hLogFile || INVALID_HANDLE_VALUE == pl->hLogFile;
	#else
		return NULL == pl->fLogFile;
	#endif
}

static inline bool requiresNewLogFile (SCUNILOGTARGET *put)
{
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

static bool cunilogWriteDataToLogFile (CUNILOG_LOGFILE *pl, char *pData, size_t lnData, enum enLineEndings nl)
{
	#ifdef OS_IS_WINDOWS
		DWORD dwWritten;
		DWORD toWrite = addNewLineToLogEventLine (pData, lnData, nl) & 0xFFFFFFFF;
		// The file has been opened with FILE_APPEND_DATA, i.e. we don't need to
		//	seek ourselves.
		//LARGE_INTEGER	z = {0, 0};
		//SetFilePointerEx (pl->hLogFile, z, NULL, FILE_END);
		bool b = WriteFile (pl->hLogFile, pData, toWrite, &dwWritten, NULL);
		return b;
	#else
		long lToWrite = (long) addNewLineToLogEventLine (pData, lnData, nl);
		// See https://www.man7.org/linux/man-pages/man3/fopen.3.html .
		//	A call "fseek (pl->fLogFile, (long) 0, SEEK_END);" is not required
		//	because we opened the file in append mode.
		size_t st = fwrite (pData, 1, lToWrite, pl->fLogFile);
		return st == lnData;
	#endif
}

static bool cunilogProcessWriteToLogFileFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);

	SCUNILOGTARGET	*put = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (put);
	ubf_assert (isUsableSMEMBUF (&put->mbLogfileName));

	if (cunilogHasDontWriteToLogfile (put))
		return true;

	CUNILOG_LOGFILE	*pl	= cup->pData;
	ubf_assert_non_NULL (pl);

	if (isUsableSMEMBUF (&put->mbLogfileName))
	{
		if (requiresOpenLogFile (pl))
		{
			if (!cunilogOpenLogFile (pl, put->mbLogfileName.buf.pcc))
				cunilogInvokeErrorCallback (CUNILOG_UNKNOWN_ERROR, cup, pev);
		} else
		if (requiresNewLogFile (put))
		{
			if (!cunilogOpenNewLogFile (pl, put->mbLogfileName.buf.pcc))
				cunilogInvokeErrorCallback (CUNILOG_UNKNOWN_ERROR, cup, pev);
		}
		if	(
				!cunilogWriteDataToLogFile	(
					pl, put->mbLogEventLine.buf.pch, put->lnLogEventLine, put->unilogNewLine
											)
			)
				cunilogInvokeErrorCallback (CUNILOG_UNKNOWN_ERROR, cup, pev);
	}
	return true;
}

static bool cunilogProcessFlushFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	SCUNILOGTARGET	*put = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (put);
	
	if (cunilogHasDontWriteToLogfile (put))
		return true;

	CUNILOG_LOGFILE *pcl = cup->pData;

	#ifdef OS_IS_WINDOWS
		if (!FlushFileBuffers (pcl->hLogFile))
			cunilogInvokeErrorCallback (CUNILOG_UNKNOWN_ERROR, cup, pev);
	#else
		if (0 != fflush (pcl->fLogFile))
			cunilogInvokeErrorCallback (CUNILOG_UNKNOWN_ERROR, cup, pev);
	#endif
	return true;
}

static bool cunilogProcessEventSingleThreaded (SCUNILOGEVENT *pev);
static bool enqueueAndTriggerSeparateLoggingThread (SCUNILOGEVENT *pev);

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY

	static inline void IncrementPendingNoRotationEvents (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		++ put->nPendingNoRotEvts;
		//printf ("%" PRIu64 "\n", put->nPendingNoRotEvts);
	}
	static inline void DecrementPendingNoRotationEvents (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		-- put->nPendingNoRotEvts;
		//printf ("%" PRIu64 "\n", put->nPendingNoRotEvts);
	}
#else
	#define IncrementPendingNoRotationEvents(put)
	#define DecrementPendingNoRotationEvents(put)
#endif

static bool logFromInsideRotatorTextU8fmt (SCUNILOGTARGET *put, const char *fmt, ...)
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
		prd->plogSCUNILOGTARGET == NULL		-> Log to current SCUNILOGTARGET (put) but
												without rotation (because we currently *are*
												within a rotation).
		prd->plogSCUNILOGTARGET == put		-> Bug, as this should be NULL.
		prd->plogSCUNILOGTARGET == <Anything else>
											-> Log to this SCUNILOGTARGET normally.
	*/
	ubf_assert (put != prd->plogSCUNILOGTARGET);
	if (prd->plogSCUNILOGTARGET && put != prd->plogSCUNILOGTARGET)
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

		SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Text (put, cunilogEvtSeverityNone, szTxtToLog, len);
		ubf_assert_non_NULL (pev);
		if (pev)
		{
			cunilogSetEventNoRotation (pev);
			#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
				if (hasSCUNILOGTARGETqueue (put))
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
	static void GetTextForLastError (char *szErrMsg)
	{
		ubf_assert_non_NULL (szErrMsg);

		// Note that we expect a buffer of CUNILOG_STD_MSG_SIZE octets.
		DWORD dwError = GetLastError ();
		GetWinErrorTextU8 (szErrMsg, CUNILOG_STD_MSG_SIZE, dwError);
	}
#else
	static void GetTextForLastError (char *szErrMsg)
	{
		ubf_assert_non_NULL (szErrMsg);

		char szErr [] = "\"Not implemented\"";
		memcpy (szErrMsg, szErr, sizeof (szErr));
	}
#endif

static void FileSystemCompressLogfile (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	bool b;
	char szErr [CUNILOG_STD_MSG_SIZE];
	
	enfilecompressresult	cmprRes = IsFileCompressedByName (put->mbFilToRotate.buf.pch);
	switch (cmprRes)
	{
		case fscompress_uncompressed:
			logFromInsideRotatorTextU8fmt	(
				put, "Initiating file system compression for file \"%s\"...\n",
				put->mbFilToRotate.buf.pch
											);
			b = FScompressFileByName (put->mbFilToRotate.buf.pch);
			if (b)
			{
				logFromInsideRotatorTextU8fmt	(
					put, "File system compression for file \"%s\" initiated.\n",
				put->mbFilToRotate.buf.pch
												);
			} else
			{
				GetTextForLastError (szErr);
				logFromInsideRotatorTextU8fmt	(
					put,
					"Error %s while attempting to initiate file system compression for file \"%s\".\n",
					szErr, put->mbFilToRotate.buf.pch
										);
			}
			break;
		case fscompress_compressed:
			break;
		case fscompress_error:
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt	(
				put,
				"Error %s while attempting to check file system compression for file \"%s\".\n",
				szErr, put->mbFilToRotate.buf.pch
									);
			break;
	}
}

#if defined (OS_IS_WINDOWS) && defined (HAVE_SHELLAPI)

	static void MoveFileToRecycleBinWin (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		logFromInsideRotatorTextU8fmt (put, "Moving obsolete logfile \"%s\" to recycle bin...\n", put->mbFilToRotate.buf.pch);
		bool b = MoveToRecycleBinU8 (put->mbFilToRotate.buf.pch);
		if (b)
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" moved to recycle bin.\n", put->mbFilToRotate.buf.pch);
		} else
		{
			char szErr [CUNILOG_STD_MSG_SIZE];
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt (put, "Error %s while attempting to move obsolete logfile \"%s\" to recycle bin.\n", szErr, put->mbFilToRotate.buf.pch);
		}
	}

#elif OS_IS_MACOS

	#include "./../OS/Apple/TrashCan.h"

	// Our wrapper.
	static void MoveFileToRecycleBinMac (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		logFromInsideRotatorTextU8fmt (put, "Moving obsolete logfile \"%s\" to recycle bin...\n", put->mbFilToRotate.buf.pch);
		if (LIBTRASHCAN_SUCCESS == trashcan_soft_delete_apple (put->mbFilToRotate.buf.pch))
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" moved to recycle bin.\n", put->mbFilToRotate.buf.pch);
		} else
		{
			logFromInsideRotatorTextU8fmt (put, "Error while attempting to move obsolete logfile \"%s\" to recycle bin.\n", put->mbFilToRotate.buf.pch);
		}
	}

#elif defined (OS_IS_LINUX)

	static void MoveFileToRecycleBinLnx (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		logFromInsideRotatorTextU8fmt (put, "Moving obsolete logfile \"%s\" to recycle bin...\n", put->mbFilToRotate.buf.pch);
		bool b = MoveFileToTrashPOSIX (put->mbFilToRotate.buf.pch);
		if (b)
		{
			logFromInsideRotatorTextU8fmt (put, "Obsolete logfile \"%s\" moved to recycle bin.\n", put->mbFilToRotate.buf.pch);
		} else
		{
			char szErr [CUNILOG_STD_MSG_SIZE];
			GetTextForLastError (szErr);
			logFromInsideRotatorTextU8fmt (put, "Error %s while attempting to move obsolete logfile \"%s\" to recycle bin.\n", szErr, put->mbFilToRotate.buf.pch);
		}
	}

#else

	#error To do!!!

#endif

/*
	Platform-independent wrapper function.
*/
static inline void cuMoveFileToRecycleBin (SCUNILOGTARGET *put)
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
	static void DeleteObsoleteLogfile (SCUNILOGTARGET *put)
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
	static void DeleteObsoleteLogfile (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
	
		logNoRotationTextU8fmt (put, "Deleting obsolete logfile \"%s\"...\n", put->mbFilToRotate.buf.pch);
		int i = unlink (put->mbFilToRotate.buf.pch);
		if (0 == i)
		{
			logNoRotationTextU8fmt (put, "Obsolete logfile \"%s\" deleted.\n", put->mbFilToRotate.buf.pch);
		} else
		{
			logNoRotationTextU8fmt (put, "Error %d while attempting to delete obsolete logfile \"%s\".\n", errno, put->mbFilToRotate.buf.pch);
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
	SCUNILOGEVENT			*pev = prg->pev;
	ubf_assert_non_NULL	(pev);
	SCUNILOGTARGET			*put = pev->pSCUNILOGTARGET;
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
		case cunilogrotationtask_FScompressLogfiles:
			FileSystemCompressLogfile (put);
			break;
		case cunilogrotationtask_MoveToRecycleBinLogfiles:
			cuMoveFileToRecycleBin (put);
			break;
		case cunilogrotationtask_DeleteLogfiles:
			DeleteObsoleteLogfile (put);
			break;
	}

	// We're not in a rotator anymore.
	put->prargs = NULL;
}

static void prepareU8fullFileNameToRotate (CUNILOG_ROTATOR_ARGS *prg)
{
	ubf_assert_non_NULL (prg);
	SCUNILOGEVENT			*pev = prg->pev;
	ubf_assert_non_NULL (pev);
	SCUNILOGTARGET			*put = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (put);

	growToSizeSMEMBUF (&put->mbFilToRotate, put->lnLogPath + prg->siz);
	if (isUsableSMEMBUF (&put->mbFilToRotate))
	{
		memcpy (put->mbFilToRotate.buf.pch + put->lnLogPath, prg->nam, prg->siz);
	}
}

/*
	Compare function for vec_sort ().
*/
static int flscmp (const void *p1, const void *p2)
{
	const CUNILOG_FLS	*fls1 = p1;
	const CUNILOG_FLS	*fls2 = p2;
	int					r = 0;

	if (fls1->stFilename == fls2->stFilename)
	{
		r = memcmp (fls1->chFilename, fls2->chFilename, fls1->stFilename - 1);
		return r;
	}
	// We should never get here. That's a bug, misconfiguration, or someone inserted
	//	a unicode character manually.
	ubf_assert (false);
	if (fls1->stFilename < fls2->stFilename)
	{	
		ubf_assert (false);
		r = memcmp (fls1->chFilename, fls2->chFilename, fls1->stFilename - 1);
	}
	if (fls1->stFilename > fls2->stFilename)
	{
		ubf_assert (false);
		r = memcmp (fls1->chFilename, fls2->chFilename, fls2->stFilename - 1);
	}
	return r;
}

static void prapareLogfilesListAndRotate (CUNILOG_ROTATOR_ARGS *prg)
{
	ubf_assert_non_NULL (prg);
	SCUNILOGEVENT			*pev = prg->pev;
	ubf_assert_non_NULL (pev);
	SCUNILOGTARGET			*put = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (put);
	CUNILOG_PROCESSOR		*cup = prg->cup;
	ubf_assert_non_NULL (cup);
	CUNILOG_ROTATION_DATA	*prd = cup->pData;
	ubf_assert_non_NULL (prd);

	/*
		On NTFS, files are returned in descending alphabetical order.
		This means it's enough to just reverse the order, i.e. start with the last
		file first and walk downwards. This may also be true for other file systems,
		though on file systems that return the files randomly we got to sort the vector
		first.
	*/
	if (cunilogIsFSneedsSorting (put))
		vec_sort (&put->fls, flscmp);
	size_t iFiles = put->fls.length;
	uint64_t nToIgnore = prd->nIgnore + put->scuNPI.nIgnoredTotal;
	uint64_t nMaxToRot =		CUNILOG_MAX_ROTATE_AUTO - nToIgnore <= prd->nMaxToRotate
							?	prd->nMaxToRotate
							:	nToIgnore + prd->nMaxToRotate;
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

#if defined (PLATFORM_IS_WINDOWS)
	static bool obtainLogfilesListToRotateCallbackWin (SRDIRONEENTRYSTRUCT *psdE)
	{
		ubf_assert_non_NULL (psdE);
		SCUNILOGTARGET			*put = psdE->pCustom;
		ubf_assert_non_NULL (put);

		char	szU8FileNameOnly [UTF8_MAX_PATH];

		CUNILOG_FLS	fls;
		// Note that the return value of UTF8_from_WinU16 () already includes a NUL terminator.
		fls.stFilename = UTF8_from_WinU16 (szU8FileNameOnly, UTF8_MAX_PATH, psdE->pwfd->cFileName);
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
		SCUNILOGTARGET			*put = pod->pCustom;
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
	static void obtainLogfilesListToRotateWin (SCUNILOGTARGET *put)
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
	static void obtainLogfilesListToRotatePsx (SCUNILOGTARGET *put)
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

static inline void obtainLogfilesListToRotate (SCUNILOGTARGET *put)
{
	ubf_assert_non_NULL (put);

	#if defined (PLATFORM_IS_WINDOWS)
		obtainLogfilesListToRotateWin (put);
	#elif defined (PLATFORM_IS_POSIX)
		obtainLogfilesListToRotatePsx (put);
	#endif
}

static bool cunilogProcessRotateLogfilesFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	
	if (cunilogHasEventNoRotation (pev))
		return true;

	SCUNILOGTARGET			*put = pev->pSCUNILOGTARGET;
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
static bool cunilogProcessCustomProcessorFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	
	#ifdef DEBUG
		SCUNILOGTARGET	*put = pev->pSCUNILOGTARGET;
		ubf_assert_non_NULL (put);
	#endif

	CUNILOG_CUSTPROCESS	*pcu = cup->pData;
	ubf_assert_non_NULL (pcu);
	ubf_assert_non_NULL (pcu->procFnc);
	return pcu->procFnc (cup, pev);
}

/*
	The redirector processor. The event is redirected to a different SCUNILOGTARGET,
	to which the pData member points to. When the event is redirected, the remaining
	processors of the current target are ignored.

	If pData is NULL, no redirection takes place and the remaining processors are worked
	through as usual. Since this is most likely not what the caller intended, a debug
	assertion expects pData not being NULL.
*/
static bool cunilogProcessTargetRedirectorFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);

	SCUNILOGTARGET *put = cup->pData;
	ubf_assert_non_NULL (put);

	if (put)
	{
		logEv (put, pev);
		return false;
	}
	return true;
}

static bool cunilogProcessTargetForkFnct (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);

	SCUNILOGTARGET *put = cup->pData;
	ubf_assert_non_NULL (put);

	if (put)
	{
		SCUNILOGEVENT *pnev = DuplicateSCUNILOGEVENT (pev);
		if (pnev)
		{
			logEv (put, pev);
		}
	}
	return true;
}

/*
static void cunilogProcessNotSupported (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	
	SCUNILOGTARGET	*pta = pev->pSCUNILOGTARGET;
	ubf_assert_non_NULL (pta);

	ubf_assert_msg (false, "Not supported yet!");
}
*/

/*
	Queue functions.
*/

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline size_t nToTrigger (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (cunilogIsPaused (put))
		{
			++ put->nPausedEvents;
			return 0;
		} else
		{	// Only the current event requires a trigger. The value of nPausedEvents
			//	should have been zeroed out by ResumeLogSCUNILOGTARGET ().
			ubf_assert_0 (put->nPausedEvents);
			return 1;
		}
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	// Returns how many times the semaphore must be triggered to empty the queue.
	static inline size_t EnqueueSCUNILOGEVENT (SCUNILOGEVENT *pev)
	{
		ubf_assert_non_NULL (pev);

		SCUNILOGTARGET	*put = pev->pSCUNILOGTARGET;
		ubf_assert_non_NULL (put);
		ubf_assert (hasSCUNILOGTARGETqueue (put));

		size_t r;

		EnterCUNILOG_LOCKER (put);
		if (put->qu.first)
		{
			SCUNILOGEVENT *l	= put->qu.last;
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
	queue with DequeueAllSCUNILOGEVENTs ().
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	static inline SCUNILOGEVENT *DequeueSCUNILOGEVENT (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (hasSCUNILOGTARGETqueue (put));

		SCUNILOGEVENT	*pev	= NULL;

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
	static inline SCUNILOGEVENT *DequeueAllSCUNILOGEVENTs (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (hasSCUNILOGTARGETqueue (put));

		SCUNILOGEVENT	*pev	= NULL;
		SCUNILOGEVENT	*last;

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
	static inline void triggerSCUNILOGEVENTloggingThread (SCUNILOGTARGET *put, size_t releaseCount)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (hasSCUNILOGTARGETqueue (put));
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
	static bool SepLogThreadWaitForEvents (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (hasSCUNILOGTARGETqueue (put));

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
	SEPARATE_LOGGING_THREAD_RETURN_TYPE SeparateLoggingThread (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);
		ubf_assert (hasSCUNILOGTARGETqueue (put));

		while (SepLogThreadWaitForEvents (put))
		{
			SCUNILOGEVENT *pev = DequeueAllSCUNILOGEVENTs (put);
			SCUNILOGEVENT *pnx;
			while (pev)
			{	// Remember the next pointer because pev is going to be destroyed
				//	by DoneSUNILOGEVENT ().
				pnx = pev->next;
				cunilogProcessEventSingleThreaded (pev);
				DoneSCUNILOGEVENT (put, pev);
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
	static bool StartSeparateLoggingThread_ifNeeded (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (requiresSCUNILOGTARGETseparateLoggingThread (put))
		{
			#ifdef OS_IS_WINDOWS
				HANDLE h = CreateThread (NULL, 0, SeparateLoggingThread, put, 0, NULL);
				ubf_assert_non_NULL (h);
				put->th.hThread = h;
				return NULL != h;
			#else
				put->th.tThread = 0;
				int i = pthread_create (&put->th.tThread, NULL, (void * (*)(void *)) SeparateLoggingThread, put);
				ubf_assert_0 (i);
				return 0 == i;
			#endif
		}
		// If the separate logging thread is not required, this is considered success.
		return true;
	}
#else
	static bool StartSeparateLoggingThread_ifNeeded (SCUNILOGTARGET *put)
	{
		UNUSED (put);

		return true;
	}
#endif

static void cunilogUpdateCurrentValue (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);

	switch (cup->freq)
	{
		case cunilogProcessAppliesTo_nEvents:
			++ cup->cur;
			break;
		case cunilogProcessAppliesTo_nOctets:
			cup->cur += pev->lenDataToLog;
			break;
		case cunilogProcessAppliesTo_nAlways:
			break;
		case cunilogProcessAppliesTo_SecondChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS;
			break;
		case cunilogProcessAppliesTo_MinuteChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS;
			break;
		case cunilogProcessAppliesTo_HourChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS;
			break;
		case cunilogProcessAppliesTo_DayChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS;
			break;
		case cunilogProcessAppliesTo_WeekChanged:
			cup->cur = (pev->stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS)
					 + 	GetISO8601WeekNumberFromDate (
							UBF_TIMESTAMP_YEAR	(pev->stamp),
							UBF_TIMESTAMP_MONTH	(pev->stamp),
							UBF_TIMESTAMP_DAY	(pev->stamp),
							NULL
													);
			break;
		case cunilogProcessAppliesTo_MonthChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS;
			break;
		case cunilogProcessAppliesTo_YearChanged:
			cup->cur = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS;
			break;
		case cunilogProcessAppliesTo_Auto:
			ubf_assert_msg (false, "Illegal value");
			break;
	}
}

static bool thresholdReached (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (cup);
	ubf_assert_non_NULL (pev);
	ubf_assert (sizeof (uint64_t) == sizeof (UBF_TIMESTAMP));

	bool bRet = false;

	switch (cup->freq)
	{
		case cunilogProcessAppliesTo_nEvents:
		case cunilogProcessAppliesTo_nOctets:
			bRet = cup->cur >= cup->thr;
			cup->cur = bRet ? 0 : cup->cur;
			break;
		case cunilogProcessAppliesTo_nAlways:
			return true;
		case cunilogProcessAppliesTo_SecondChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			cup->thr = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS;
			break;
		case cunilogProcessAppliesTo_MinuteChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			cup->thr = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS;
			break;
		case cunilogProcessAppliesTo_HourChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			cup->thr = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS;
			break;
		case cunilogProcessAppliesTo_DayChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			cup->thr = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS;
			break;
		case cunilogProcessAppliesTo_WeekChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			// We keep the year and the week number.
			cup->thr = (pev->stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS)
					 +
						GetISO8601WeekNumberFromDate (
							UBF_TIMESTAMP_YEAR	(pev->stamp),
							UBF_TIMESTAMP_MONTH	(pev->stamp),
							UBF_TIMESTAMP_DAY	(pev->stamp),
							NULL
													);
			break;
		case cunilogProcessAppliesTo_MonthChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			cup->thr = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS;
			break;
		case cunilogProcessAppliesTo_YearChanged:
			bRet = 0 < cup->thr && cup->cur != cup->thr;
			cup->thr = pev->stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS;
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
		bRet = true;
	}

	return bRet;
}

static bool (*pickAndRunProcessor [cunilogProcessAmountEnumValues]) (CUNILOG_PROCESSOR *cup, SCUNILOGEVENT *pev) =
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
	Returns true for further processing by the caller.
*/
static bool cunilogProcessProcessor (SCUNILOGEVENT *pev, CUNILOG_PROCESSOR *cup)
{
	ubf_assert_non_NULL	(pev);
	ubf_assert_non_NULL	(cup);
	ubf_assert_non_NULL	(pev->pSCUNILOGTARGET);
	ubf_assert			(cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));

	// If the processor is disabled we move on to the next one unconditionally.
	if (optCunProcHasOPT_CUNPROC_DISABLED (cup->uiOpts))
		return true;

	cunilogUpdateCurrentValue (cup, pev);
	if	(
				thresholdReached (cup, pev)
			||	cunilogHasRunAllProcessorsOnStartup (pev->pSCUNILOGTARGET)
		)
	{
		// True tells the caller to carry on with the next processor.
		bool bNext =		pickAndRunProcessor [cup->task] (cup, pev)
						&&	!cunilogHasEventStopProcessing (pev);
		return bNext;
	}

	// Tells the caller not to bother with the next processor unless bForceNext is true
	//	or the caller explicitely wants us to run all processors on startup.
	return OPT_CUNPROC_FORCE_NEXT & cup->uiOpts || cunilogHasRunAllProcessorsOnStartup (pev->pSCUNILOGTARGET);
}

static void cunilogProcessProcessors (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET->cprocessors);

	pev->pSCUNILOGTARGET->scuNPI.nIgnoredTotal = 0;
	cunilogClrEventStopProcessing (pev);

	unsigned int ui = 0;
	while (ui < pev->pSCUNILOGTARGET->nprocessors)
	{
		bool b = cunilogProcessProcessor (pev, pev->pSCUNILOGTARGET->cprocessors [ui]);
		if (!b)
			break;
		++ ui;
	}

	if (cunilogHasRunAllProcessorsOnStartup (pev->pSCUNILOGTARGET))
		cunilogClrRunAllProcessorsOnStartup (pev->pSCUNILOGTARGET);
}

static bool cunilogProcessEventSingleThreaded (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));

	// Event command flag for shutting down the separate logging thread.
	if (cunilogIsEventShutdown (pev))
	{
		cunilogSetShutdownTarget (pev->pSCUNILOGTARGET);
		DoneSCUNILOGEVENT (NULL, pev);
		// The shutdown event has been processed. We treat this as being success.
		return true;
	}

	size_t	eventLineSize = createEventLineFromSUNILOGEVENT (pev);
	if (CUNILOG_SIZE_ERROR != eventLineSize)
	{
		cunilogProcessProcessors (pev);
		if (cunilogHasEventNoRotation (pev))
			DecrementPendingNoRotationEvents (pev->pSCUNILOGTARGET);
		return true;
	}
	return false;
}

static bool enqueueAndTriggerSeparateLoggingThread (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		size_t n = EnqueueSCUNILOGEVENT (pev);
		if (n)
			triggerSCUNILOGEVENTloggingThread (pev->pSCUNILOGTARGET, n);
		return n > 0;
	#else
		return cunilogProcessEventSingleThreaded (pev);
	#endif
}

static bool cunilogProcessEventSingleThreadedSeparateLoggingThread (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));

	return enqueueAndTriggerSeparateLoggingThread (pev);
}

static bool cunilogProcessEventMultiThreaded (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));

	EnterCUNILOG_LOCKER (pev->pSCUNILOGTARGET);
	bool b = cunilogProcessEventSingleThreaded (pev);
	LeaveCUNILOG_LOCKER (pev->pSCUNILOGTARGET);
	return b;
}

static bool cunilogProcessEventMultiThreadedSeparateLoggingThread (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL						(pev);
	ubf_assert_non_NULL						(pev->pSCUNILOGTARGET);
	ubf_assert (cunilogIsTargetInitialised	(pev->pSCUNILOGTARGET));

	return enqueueAndTriggerSeparateLoggingThread (pev);
}

static bool cunilogProcessOrQueueEventMultiProcesses (SCUNILOGEVENT *pev)
{
	UNREFERENCED_PARAMETER (pev);
	ubf_assert_msg (false, "Not implemented yet.");
	return false;
}

static bool (*cunilogProcOrQueueEvt [cunilogTypeAmountEnumValues]) (SCUNILOGEVENT *pev) =
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
static bool cunilogProcessOrQueueEvent (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);

	SCUNILOGTARGET *put = pev->pSCUNILOGTARGET;
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
	static void WaitForEndOfSeparateLoggingThread (SCUNILOGTARGET *put)
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
	static SCUNILOGEVENT scueShutdown =
	{
		NULL, CUNILOGEVENT_SHUTDOWN, 0, cunilogEvtSeverityNone, cunilogEvtTypeNormalText,
		NULL, 0, 0
	};
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool queueShutdownEvent (SCUNILOGTARGET *put)
	{
		SCUNILOGEVENT *pev = DuplicateSCUNILOGEVENT (&scueShutdown);
		if (pev)
		{
			pev->pSCUNILOGTARGET = put;
			cunilogSetEventAllocated (pev);
			cunilogProcessOrQueueEvent (pev);
			return true;
		}
		return false;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool ShutdownSCUNILOGTARGET (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (hasSCUNILOGTARGETqueue (put))
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
	bool ShutdownSCUNILOGTARGET (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		cunilogSetShutdownTarget (put);
		return true;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool CancelSCUNILOGTARGET (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		if (hasSCUNILOGTARGETqueue (put))
		{
			cunilogSetShutdownTarget (put);

			// Empty the queue. While this would actually not be required here, it can
			//	speed up things significantly (well, maybe a few cycles) with busy queues as
			//	it takes some burden off the separate logging thread.
			SCUNILOGEVENT *pev = DequeueAllSCUNILOGEVENTs (put);
			SCUNILOGEVENT *nxt;
			while (pev)
			{
				nxt = pev->next;
				DoneSCUNILOGEVENT (NULL, pev);
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
	bool CancelSCUNILOGTARGET (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		cunilogSetShutdownTarget (put);
		return true;
	}
#endif

/*
	Copied from cunilog.h.

enum enCunilogLogPriority
{
	cunilogPrioNormal,
	cunilogPrioBelowNormal,
	cunilogPrioLow,
	cunilogPrioIdle,
	// Do not insert enum values below this line.
	cunilogPrioInvalid
};
*/

#ifdef OS_IS_WINDOWS
	int icuWinPrioTable [cunilogPrioAmountEnumValues] =
	{
			/* cunilogPrioNormal			*/	THREAD_PRIORITY_NORMAL
		,	/* cunilogPrioBelowNormal		*/	THREAD_PRIORITY_BELOW_NORMAL
		,	/* cunilogPrioLow				*/	THREAD_PRIORITY_LOWEST
		,	/* cunilogPrioIdle				*/	THREAD_PRIORITY_IDLE
		,	/* cunilogPrioBeginBackground	*/	THREAD_MODE_BACKGROUND_BEGIN
		,	/* cunilogPrioEndBackground		*/	THREAD_MODE_BACKGROUND_END
	};
#else
	// These values haven't been tested yet! I (Thomas) just made them up in
	//	the hope they might do well enough.
	int icuPsxPrioTable [cunilogPrioAmountEnumValues] =
	{
			/* cunilogPrioNormal			*/	0
		,	/* cunilogPrioBelowNormal		*/	5
		,	/* cunilogPrioLow				*/	10
		,	/* cunilogPrioIdle				*/	19
		,	/* cunilogPrioBeginBackground	*/	19
		,	/* cunilogPrioEndBackground		*/	0
	};
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef OS_IS_WINDOWS
		static bool SetWinLogPriority (SCUNILOGTARGET *put, int prio)
		{
			ubf_assert_non_NULL (put);
			ubf_assert_non_NULL (put->th.hThread);
			ubf_assert (INVALID_HANDLE_VALUE != put->th.hThread);

			if (put->th.hThread && INVALID_HANDLE_VALUE != put->th.hThread)
			{
				return SetThreadPriority (put->th.hThread, prio);
			}
			return false;
		}
	#else
		static bool SetPsxLogPriority (SCUNILOGTARGET *put, int prio)
		{	// See https://man7.org/linux/man-pages/man3/pthread_setschedprio.3.html .
			return 0 == pthread_setschedprio (put->th.tThread, prio);
		}
	#endif
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	bool SetLogPrioritySCUNILOGTARGET (SCUNILOGTARGET *put, cunilogprio prio)
	{
		ubf_assert_non_NULL	(put);
		ubf_assert			(0 <= prio);
		ubf_assert			(prio < cunilogPrioAmountEnumValues);

		if (hasSeparateLoggingThread (put))
		{
			if (0 <= prio && cunilogPrioAmountEnumValues > prio)
			{
				#ifdef PLATFORM_IS_WINDOWS
					return SetWinLogPriority (put, icuWinPrioTable [prio]);
				#else
					return SetPsxLogPriority (put, icuPsxPrioTable [prio]);
				#endif
			} else
				return false;
		}
		return true;
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		EnterCUNILOG_LOCKER (put);
		cunilogSetPaused (put);
		LeaveCUNILOG_LOCKER (put);
	}
#endif

#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogSCUNILOGTARGET (SCUNILOGTARGET *put)
	{
		ubf_assert_non_NULL (put);

		size_t n;

		EnterCUNILOG_LOCKER (put);
		cunilogClrPaused (put);
		n = put->nPausedEvents;
		put->nPausedEvents = 0;
		LeaveCUNILOG_LOCKER (put);

		triggerSCUNILOGEVENTloggingThread (put, n);
		return n;
	}
#endif

/*
	User logging functions.
*/

bool logEv (SCUNILOGTARGET *put, SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (put);
	ubf_assert_non_NULL (pev);
	ubf_assert (cunilogIsTargetInitialised (put));

	if (cunilogIsShutdownTarget (put))
		return false;

	pev->pSCUNILOGTARGET = put;
	return cunilogProcessOrQueueEvent (pev);
}

bool logTextU8sevl			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Text (put, sev, ccText, len);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logTextU8sevlq			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Text (put, sev, ccText, len);
	if (pev)
	{
		cunilogSetEventNoRotation (pev);
		return cunilogProcessOrQueueEvent (pev);
	}
	return false;
}

bool logTextU8sev			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText)
{
	return logTextU8sevl (put, sev, ccText, USE_STRLEN);
}

bool logTextU8sevq			(SCUNILOGTARGET *put, cueventseverity sev, const char *ccText)
{
	return logTextU8sevlq (put, sev, ccText, USE_STRLEN);
}

bool logTextU8l				(SCUNILOGTARGET *put, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Text (put, cunilogEvtSeverityNone, ccText, len);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logTextU8lq			(SCUNILOGTARGET *put, const char *ccText, size_t len)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Text (put, cunilogEvtSeverityNone, ccText, len);
	if (pev)
	{
		cunilogSetEventNoRotation (pev);
		return cunilogProcessOrQueueEvent (pev);
	}
	return false;
}

bool logTextU8				(SCUNILOGTARGET *put, const char *ccText)
{
	return logTextU8l (put, ccText, USE_STRLEN);
}

bool logTextU8q				(SCUNILOGTARGET *put, const char *ccText)
{
	return logTextU8lq (put, ccText, USE_STRLEN);
}

bool logTextU8vfmt			(SCUNILOGTARGET *put, const char *fmt, va_list ap)
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

bool logTextU8fmt			(SCUNILOGTARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	size_t		l;

	va_start (ap, fmt);
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);
	va_end (ap);

	char *ob = ubf_malloc (l + 1);
	if (ob)
	{
		va_start (ap, fmt);
		vsnprintf (ob, l + 1, fmt, ap);
		va_end (ap);

		bool b = logTextU8l (put, ob, l);
		ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8qvfmt			(SCUNILOGTARGET *put, const char *fmt, va_list ap)
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

bool logTextU8qfmt			(SCUNILOGTARGET *put, const char *fmt, ...)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	va_list		ap;
	size_t		l;

	va_start (ap, fmt);
	l = (size_t) vsnprintf (NULL, 0, fmt, ap);
	va_end (ap);

	char *ob = ubf_malloc (l + 1);
	if (ob)
	{
		va_start (ap, fmt);
		vsnprintf (ob, l + 1, fmt, ap);
		va_end (ap);

		bool b = logTextU8lq (put, ob, l);
		ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8svfmt			(SCUNILOGTARGET *put, const char *fmt, va_list ap)
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

bool logTextU8sfmt			(SCUNILOGTARGET *put, const char *fmt, ...)
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

		bool b = logTextU8l (put, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8sqvfmt		(SCUNILOGTARGET *put, const char *fmt, va_list ap)
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

bool logTextU8sqfmt			(SCUNILOGTARGET *put, const char *fmt, ...)
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

		bool b = logTextU8lq (put, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8svfmtsev		(SCUNILOGTARGET *put, cueventseverity sev, const char *fmt, va_list ap)
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

bool logTextU8sfmtsev		(SCUNILOGTARGET *put, cueventseverity sev, const char *fmt, ...)
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

		bool b = logTextU8sevl (put, sev, ob, l);
		if (ob != cb) ubf_free (ob);
		return b;
	}
	return false;
}

bool logTextU8smbvfmtsev	(SCUNILOGTARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, va_list ap)
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

bool logTextU8smbfmtsev		(SCUNILOGTARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, ...)
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

			bool b = logTextU8sevl (put, sev, smb->buf.pch, l);
			return b;
		}
	}
	return false;
}

bool logTextU8smbvfmt		(SCUNILOGTARGET *put, SMEMBUF *smb, const char *fmt, va_list ap)
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

			bool b = logTextU8l (put, smb->buf.pch, l);
			return b;
		}
	}
	return false;
}

bool logTextU8smbfmt		(SCUNILOGTARGET *put, SMEMBUF *smb, const char *fmt, ...)
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

			bool b = logTextU8l (put, smb->buf.pch, l);
			return b;
		}
	}
	return false;
}

bool logHexDumpU8sevl		(SCUNILOGTARGET *put, cueventseverity sev, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Data (put, sev, pBlob, size, ccCaption, lenCaption);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logHexDumpU8l			(SCUNILOGTARGET *put, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Data	(
							put, cunilogEvtSeverityNone, pBlob, size,
							ccCaption, lenCaption
													);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logHexDump				(SCUNILOGTARGET *put, const void *pBlob, size_t size)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Data	(
							put, cunilogEvtSeverityNone, pBlob,
							size, NULL, 0
													);
	return pev && cunilogProcessOrQueueEvent (pev);
}

bool logHexDumpq			(SCUNILOGTARGET *put, const void *pBlob, size_t size)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	SCUNILOGEVENT *pev = CreateSCUNILOGEVENT_Data	(
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

bool logHexOrText			(SCUNILOGTARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	if (str_has_only_printable_ASCII (szHexOrTxt, lenHexOrTxt))
		return logTextU8l (put, szHexOrTxt, lenHexOrTxt);

	return logHexDump (put, szHexOrTxt, lenHexOrTxt);
}

bool logHexOrTextq			(SCUNILOGTARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	if (str_has_only_printable_ASCII (szHexOrTxt, lenHexOrTxt))
		return logTextU8lq (put, szHexOrTxt, lenHexOrTxt);

	return logHexDumpq (put, szHexOrTxt, lenHexOrTxt);
}

bool logHexOrTextU8			(SCUNILOGTARGET *put, const void *szHexOrTxtU8, size_t lenHexOrTxtU8)
{
	ubf_assert_non_NULL (put);

	if (cunilogIsShutdownTarget (put))
		return false;

	if (c_check_utf8 (szHexOrTxtU8, lenHexOrTxtU8))
		return logTextU8l (put, szHexOrTxtU8, lenHexOrTxtU8);

	return logHexDump (put, szHexOrTxtU8, lenHexOrTxtU8);
}

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16sevl			(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len)
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
bool logTextWU16sev			(SCUNILOGTARGET *put, cueventseverity sev, const wchar_t *cwText)
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
bool logTextWU16l				(SCUNILOGTARGET *put, const wchar_t *cwText, size_t len)
{
	ubf_assert_non_NULL (put);
	
	if (cunilogIsShutdownTarget (put))
		return false;

	return logTextWU16sevl (put, cunilogEvtSeverityNone, cwText, len);
}
#endif

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16				(SCUNILOGTARGET *put, const wchar_t *cwText)
{
	ubf_assert_non_NULL (put);
	
	if (cunilogIsShutdownTarget (put))
		return false;

	return logTextWU16sev (put, cunilogEvtSeverityNone, cwText);
}
#endif


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
		SCUNILOGTARGET	*pt;
		bool			bRet	= true;

		//ASSERT (false);

		// Ensure we haven't forgotten to fill the arrays/jump tables.
		ubf_assert (GET_ARRAY_LEN (arrLengthTimeStampFromPostfix)	==	cunilogPostfixAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (arrPostfixWildcardMask)			==	cunilogPostfixAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (obtainTimeStampAsString)			==	cunilogPostfixAmountEnumValues);
		ubf_assert (GET_ARRAY_LEN (cunilogProcOrQueueEvt)			==	cunilogTypeAmountEnumValues);

		// Check that the length assignments are correct.
		ubf_assert (LEN_ISO8601DATEHOURANDMINUTE	== lenDateTimeStampFromPostfix (cunilogPostfixMinute));
		ubf_assert (LEN_ISO8601DATEANDHOUR			== lenDateTimeStampFromPostfix (cunilogPostfixHour));
		ubf_assert (LEN_ISO8601DATE					== lenDateTimeStampFromPostfix (cunilogPostfixDay));
		ubf_assert (LEN_ISO8601DATE					== lenDateTimeStampFromPostfix (cunilogPostfixDefault));
		ubf_assert (LEN_ISO8601YEARANDWEEK			== lenDateTimeStampFromPostfix (cunilogPostfixWeek));
		ubf_assert (LEN_ISO8601YEARANDMONTH			== lenDateTimeStampFromPostfix (cunilogPostfixMonth));
		ubf_assert (LEN_ISO8601YEAR					== lenDateTimeStampFromPostfix (cunilogPostfixYear));

		#ifdef OS_IS_LINUX
			bool bTrash = MoveFileToTrashPOSIX ("/home/thomas/FS/OAN/Thomas/cunilog/logs/testcunilog_2024-11-05 20_14.log");
			ubf_assert_false (bTrash);
		#endif

		/*
			Static.
		*/
		pt = InitSCUNILOGTARGETstaticEx	(
					NULL,		0,
					"Unilog",	USE_STRLEN,
					cunilogLogPath_relativeToHomeDir,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pSCUNILOGTARGETstatic	== pt);
		ubf_assert (pSCUNILOGTARGETstatic	== &SCUNILOGTARGETstatic);
		ubf_assert (cunilogSingleThreaded	== SCUNILOGTARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== SCUNILOGTARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default	== SCUNILOGTARGETstatic.unilogEvtTSformat);
		ubf_assert (6 == SCUNILOGTARGETstatic.lnAppName);
		ubf_assert (!memcmp (SCUNILOGTARGETstatic.mbAppName.buf.pch, "Unilog", SCUNILOGTARGETstatic.lnAppName));

		size_t lnAbsLogPath;
		const char *szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGETstatic ();

		pt = InitSCUNILOGTARGETstaticEx	(
					NULL,				0,
					"////sub/Unilog",	USE_STRLEN,
					cunilogLogPath_relativeToHomeDir,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pSCUNILOGTARGETstatic	== pt);
		ubf_assert (pSCUNILOGTARGETstatic	== &SCUNILOGTARGETstatic);
		ubf_assert (cunilogSingleThreaded	== SCUNILOGTARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== SCUNILOGTARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default	== SCUNILOGTARGETstatic.unilogEvtTSformat);
		ubf_assert (10 == SCUNILOGTARGETstatic.lnAppName);
		#ifdef PLATFORM_IS_WINDOWS
			ubf_assert (!memcmp (SCUNILOGTARGETstatic.mbAppName.buf.pch, "sub\\Unilog", SCUNILOGTARGETstatic.lnAppName));
		#else
			ubf_assert (!memcmp (SCUNILOGTARGETstatic.mbAppName.buf.pch, "sub/Unilog", SCUNILOGTARGETstatic.lnAppName));
		#endif

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGETstatic ();

		pt = InitSCUNILOGTARGETstaticEx	(
					NULL,		0,
					"Unilog",	USE_STRLEN,
					cunilogLogPath_relativeToCurrentDir,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pSCUNILOGTARGETstatic	== pt);
		ubf_assert (pSCUNILOGTARGETstatic	== &SCUNILOGTARGETstatic);
		ubf_assert (cunilogSingleThreaded	== SCUNILOGTARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== SCUNILOGTARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default	== SCUNILOGTARGETstatic.unilogEvtTSformat);
		ubf_assert (6 == SCUNILOGTARGETstatic.lnAppName);
		ubf_assert (!memcmp (SCUNILOGTARGETstatic.mbAppName.buf.pch, "Unilog", SCUNILOGTARGETstatic.lnAppName));

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGETstatic ();

		pt = InitSCUNILOGTARGETstaticEx	(
					"C:/temp",	USE_STRLEN,
					"Unilog",	USE_STRLEN,
					cunilogLogPath_relativeToExecutable,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0,
					cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup
										);
		ubf_assert (pSCUNILOGTARGETstatic	== pt);
		ubf_assert (pSCUNILOGTARGETstatic	== &SCUNILOGTARGETstatic);
		ubf_assert (cunilogSingleThreaded	== SCUNILOGTARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay		== SCUNILOGTARGETstatic.culogPostfix);
		ubf_assert (cunilogEvtTS_Default		== SCUNILOGTARGETstatic.unilogEvtTSformat);
		// Size is 8 + NUL.
		ubf_assert (9 == SCUNILOGTARGETstatic.mbLogPath.size);
		ubf_assert	(
				!memcmp	(
					SCUNILOGTARGETstatic.mbLogPath.buf.pch,
					"C:" UBF_DIR_SEP_STR "temp" UBF_DIR_SEP_STR ASCII_NUL_STR,
					SCUNILOGTARGETstatic.mbLogPath.size
						)
					);
		ubf_assert	(
				// "C:\\temp\\Unilog".
				!memcmp	(
					SCUNILOGTARGETstatic.mbLogfileName.buf.pch,
					"C:" UBF_DIR_SEP_STR "temp" UBF_DIR_SEP_STR "Unilog",
					SCUNILOGTARGETstatic.mbLogPath.size + SCUNILOGTARGETstatic.lnAppName - 1
						)
					);
		ubf_assert (6 == SCUNILOGTARGETstatic.lnAppName);
		// Should be NUL-terminated.
		ubf_assert (!memcmp (SCUNILOGTARGETstatic.mbAppName.buf.pch, "Unilog", SCUNILOGTARGETstatic.lnAppName + 1));

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGETstatic ();

		pt = InitSCUNILOGTARGETstaticEx	(
					"../temp",	USE_STRLEN,
					"Unilog",	USE_STRLEN,
					cunilogLogPath_relativeToExecutable,
					cunilogSingleThreaded,
					cunilogPostfixDay,
					NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
					cunilogDontRunProcessorsOnStartup

										);
		ubf_assert (pSCUNILOGTARGETstatic == pt);
		ubf_assert (pSCUNILOGTARGETstatic	== &SCUNILOGTARGETstatic);
		ubf_assert (cunilogSingleThreaded	== SCUNILOGTARGETstatic.culogType);
		ubf_assert (cunilogPostfixDay				== SCUNILOGTARGETstatic.culogPostfix);
		ubf_assert (6 == SCUNILOGTARGETstatic.lnAppName);
		ubf_assert (!memcmp (SCUNILOGTARGETstatic.mbAppName.buf.pch, "Unilog", SCUNILOGTARGETstatic.lnAppName + 1));

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGETstatic ();

		/*
			Dynamic.
		*/
		pt = CreateNewSCUNILOGTARGET (
				NULL, 0,
				NULL, 0,
				cunilogLogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
									);
		DoneSCUNILOGTARGET (pt);

		pt = InitOrCreateSCUNILOGTARGET	(
				NULL,
				NULL, 0,
				"Unilog", 6,
				cunilogLogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
										);

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGET (pt);

		pt = InitOrCreateSCUNILOGTARGET	(
				NULL,
				"C:/Temp", 7,
				"Unilog", 6,
				cunilogLogPath_relativeToExecutable,
				cunilogSingleThreaded,
				cunilogPostfixDay,
				NULL, 0, cunilogEvtTS_Default, cunilogNewLineSystem,
				cunilogDontRunProcessorsOnStartup
										);
		ubf_assert_non_NULL (pt);
		ubf_assert (pt != pSCUNILOGTARGETstatic);
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

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGET (pt);

		// Should fail.
		SCUNILOGTARGET	cut;
		SCUNILOGTARGET	*put;
		put = InitSCUNILOGTARGET	(
				&cut,
				"temp",		USE_STRLEN,
				"OurApp",	USE_STRLEN,
				cunilogLogPath_isAbsolute,
				cunilogMultiThreaded
									);
		ubf_assert_NULL (put);

		/*
			Application name from executable name.
		*/
		pt = InitOrCreateSCUNILOGTARGET	(
				NULL,
				"C:/Temp", 7,
				NULL, 0,
				cunilogLogPath_relativeToExecutable,
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
		ubf_assert (pt != pSCUNILOGTARGETstatic);
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

		szAbsLogPath = getAbsoluteLogPathSCUNILOGTARGET (pt, &lnAbsLogPath);
		ubf_assert_non_NULL (szAbsLogPath);
		ubf_assert_non_0 (lnAbsLogPath);
		ubf_assert_0 (szAbsLogPath [lnAbsLogPath]);

		DoneSCUNILOGTARGET (pt);

		return bRet;
	}
#endif
