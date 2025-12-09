/****************************************************************************************

	File:		ubf_date_and_time.h
	Why:		Functions for handling date and time.
	OS:			Windows NT Ver. 4.0/2000/XP/Vista/7/8...
	Author:		Thomas
	Created:	2016-11-02
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2016-11-02	Thomas			Created.
2017-06-09	Thomas			Definition of FILETIME moved to ubf_type_definitions.h.
2017-08-29	Thomas			Function GetISO8601DateTimeStampT () added.
2019-08-13	Thomas			Underscore character removed from time interval names.

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

#ifndef U_UBF_DATETIME_H_INCLUDED
#define U_UBF_DATETIME_H_INCLUDED

/*
#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#include "./ubf_type_definitions.h"
#else
	#include "./../OS/ubf_type_definitions.h"
#endif
*/

#include <time.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubf_times.h"
	
	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./restrict.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/restrict.h"
	#endif

#endif

#ifdef _DEBUG
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif

/* Already defined in ubf_times.h.
// Lengths.
#ifndef LEN_ISO8601DATETIMESTAMPMS_NO_OFFS
#define LEN_ISO8601DATETIMESTAMPMS_NO_OFFS	24					// "YYYY-MM-DD hh:mm:ss.xxx"
#endif
#ifndef LEN_ISO8601DATETIMESTAMP								// "YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMP			26
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS								// "YYYY-MM-DD HH:MI:SS.000+01:00"
#define LEN_ISO8601DATETIMESTAMPMS			30
#endif
*/

/*
	ULONGLONGfromFILETIME	macro
	FILETIMEtoULONGLONG		macro
	
	Retrieves the contents of the FILETIME structure as a ULONGLONG
	(unsigned __int64, uint64_t).
	
	Usage:
	ui64Result = ULONGLONGfromFILETIME (ft);
	ui64Result = FILETIMEtoULONGLONG (ft);
*/
#ifndef ULONGLONGfromFILETIME
#define ULONGLONGfromFILETIME(x)((((ULONGLONG) (x).dwHighDateTime) << 32) + (x).dwLowDateTime)
#endif
#ifndef FILETIMEtoULONGLONG
#define FILETIMEtoULONGLONG ULONGLONGfromFILETIME
#endif

/*
	FILETIMEfromULONGLONG	macro
	ULONGLONGtoFILETIME		macro
	
	Copies the high and low values of a ULONGLONG (unsigned __int64)
	into the high and low double words of a FILETIME structure.
	
	Usage:
	FILETIMEfromULONGLONG (ftResult, ui64);
	ULONGLONGtoFILETIME (ftResult, ui64);
*/
#ifndef FILETIMEfromULONGLONG
#define FILETIMEfromULONGLONG(f,u)											\
			(f).dwHighDateTime	= (uint32_t) (u >> 32 & 0x00000000FFFFFFFF);	\
			(f).dwLowDateTime	= (uint32_t) (u & 0x00000000FFFFFFFF)
#endif
#ifndef ULONGLONGtoFILETIME
#define ULONGLONGtoFILETIME FILETIMEfromULONGLONG
#endif

#ifndef GetReadableTimeSpanFromFILETIME
#define GetReadableTimeSpanFromFILETIME	GetReadableTimeSpanFILETIME
#endif

/*
	Macros to set TIMEVAL values.

	Examples:

	TIMEVAL		tv;
	SET_pTIMEVAL_S		(&tv, 10);
	SET_TIMEVAL_S		(tv, 10);

	These macros set one member of the structure to the provided value. The other member is set
	to 0.
	
	SET_pTIMEVAL_S		(&tv,	10);							// Set timeout to 10 seconds.
	SET_TIMEVAL_S		(tv,	10);							// Set timeout to 10 seconds.
	SET_pTIMEVAL_US		(&tv,	100);							// Set timeout to 100 microseconds.
	SET_TIMEVAL_US		(tv,	100);							// Set timeout to 100 microseconds.
	SET_pTIMEVAL_MS		(&tv,	1000);							// Set timeout to 1 second
																//	(1000 milliseconds).
	SET_TIMEVAL_MS		(tv,	1000);							// Set timeout to 1 second
																//	(1000 milliseconds).
	SET_pTIMEVAL_NS 	(&tv,	1000);							// Set timeout to 1 microsecond
																//	(1000 nanoseconds).
	SET_TIMEVAL_NS		(tv,	1000);							// Set timeout to 1 microsecond
																//	(1000 nanoseconds).
*/
#define SET_pTIMEVAL_S(t,vs)	(t)->tv_sec	= vs;	(t)->tv_usec	= 0
#define SET_TIMEVAL_S(t,vs)		(t).tv_sec	= vs;	(t).tv_usec		= 0
#define SET_pTIMEVAL_US(t,us)	(t)->tv_sec	= 0;	(t)->tv_usec	= (us * 1000)
#define SET_TIMEVAL_US(t,us)	(t).tv_sec	= 0;	(t).tv_usec		= (us * 1000)
#define SET_pTIMEVAL_MS(t,ms)	(t)->tv_sec	= 0;	(t)->tv_usec	= (ms * 1000 * 1000)
#define SET_TIMEVAL_MS(t,ms)	(t).tv_sec	= 0;	(t).tv_usec		= (ms * 1000 * 1000)
#define SET_pTIMEVAL_NS(t,ns)	(t)->tv_sec	= 0;	(t)->tv_usec	= ns
#define SET_TIMEVAL_NS(t,ns)	(t).tv_sec	= 0;	(t).tv_usec		= ns

/*
	Macros for the TIMSPEC structure.

	Examples:

	TIMESPEC	tc;

	SET_pTIMESPEC_MINS	(&tc, 2);								// 2 minutes.
	SET_TIMESPEC_MINS	(tc, 2);								// 2 minutes.
*/
#define SET_pTIMESPEC_MINS(t,mins)	(t)->tv_sec = (mins) * 60;	(t)->tv_nsec = 0
#define SET_TIMESPEC_MINS(t,mins)	(t).tv_sec = (mins) * 60;	(t).tv_nsec = 0

#ifdef __cplusplus
	extern "C" {
#endif

// If we haven't got the timespec struct, define it here.
#if defined OS_IS_WINDOWS && defined _CRT_NO_TIME_T
	// See http://pubs.opengroup.org/onlinepubs/7908799/xsh/time.h.html .
    struct timespec
    {
        time_t tv_sec;  // Seconds - >= 0
        long   tv_nsec; // Nanoseconds - [0, 999999999]
    };
#else
	//typedef struct timeval TIMEVAL
#endif
typedef struct timespec TIMESPEC;

/*
	GetReadableTimeSpan
	
	Returns the value of ullTime in a readable format in chBuf.
	The smallest value returned is 1 us (microsecond).
	
	Parameters
	----------
	
	chBuf			A pointer to the buffer that receives the output.
	stLen			The length of chBuf in bytes. It includes the terminating
					NUL character.
	ullTime			A ULONGLONG (unsignded __int64) value that contains
					the timespan. It is expected that the value has been
					converted from a FILETIME structure.
					
	Remarks
	-------
	
	The return buffer contains the value of ullTime in a readable format.
	The format is "nnnd hh:mm:ss.mssuss".
	nnn				The amount of days the timespan covers.
	hh				The amount of remaining hours.
	mm				The amount of remaining minutes.
	ss				The amount of remaining seconds.
	mss				The amount of remaining milliseconds.
	uss				The amount of remainind microseconds.
	Example: "  7d 19:22:10.731322"
	
	If the buffer is too small to hold the value of ullTime in a readable
	format it is truncated but still terminated with a NUL character.
*/
void GetReadableTimeSpan			(
										char		*chBuf,
										size_t		stLen,
										ULONGLONG 	ullTime
									)
;

/*
	GetReadableTimeSpanFILETIME
	GetReadableTimeSpanFromFILETIME macro
	
	This function is identical to GetReadableTimeSpan () with the difference that the
	input parameter is a FILETIME structure.
*/
void GetReadableTimeSpanFILETIME	(
										char		*chBuf,
										size_t		stLen,
										FILETIME	ftTime
									)
;

/*
	GetSystemTimeAsULONGLONG
	
	Retrieves the current date and time (system time) as a Windows FILETIME
	ULONGLONG.
	
	On Windows it retrieves the system time as FILETIME with a call to
	GetSystemTimeAsFileTime () and converts it to an unsigned long integer
	(64 bit) ULONGLONG.
	
	On POSIX systems it calls clock_gettime () with a clock ID of CLOCK_REALTIME
	and then calls ULONGLONG_from_timespec () to retrieve the time as a ULONGLONG.
	The function ULONGLONG_from_timespec () adds the difference between the Unix
	epoch and the Windows FILETIME epoch before returning, which is
	116444736000000000. This makes results retrieved on Windows compatible with
	results retrieved on POSIX systems.
	
	If no absolute time is required it is faster on POSIX platforms to use
	GetSystemTimeAsULONGLONGrel () instead. There is no difference on Windows
	between these two functions.
	
	The function returns the time as FILETIME ULONGLONG, which is the amount
	of 100 nanoseconds ticks since the FILETIME epoch. The FILETIME epoch starts
	on 1601-01-01. See
	https://docs.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-filetime
	for more information.
*/									
ULONGLONG GetSystemTimeAsULONGLONG (void);

/*
	GetSystemTimeAsULONGLONGrel
	
	Retrieves a relative FILETIME value as a ULONGLONG that can be used for time
	measurements.

	On Windows it retrieves the system time as FILETIME with a call to
	GetSystemTimeAsFileTime () and converts it to an unsigned long integer
	(64 bit) ULONGLONG.

	On POSIX systems it calls clock_gettime () with a clock ID of CLOCK_MONOTONIC_COARSE,
	if available, and then calls ULONGLONG_from_timespec_rel () to retrieve the time
	as a ULONGLONG. On systems that do not support a CLOCK_MONOTONIC_COARSE clock the
	function uses CLOCK_MONOTONIC.
	
	The function does not add the difference between the Unix epoch and the Windows
	FILETIME epoch before returning. This makes results retrieved by this function
	on Windows incompatible with results retrieved on POSIX systems.
	
	On POSIX platforms the function is a faster alternative to
	GetSystemTimeAsULONGLONG () when a relative time is sufficient. On Windows the
	function is identical to GetSystemTimeAsULONGLONG ().
	
	The function returns a FILETIME ULONGLONG which is not adjusted to the Windows
	epoch but suitable for relative measurements. On Windows the return value is
	correctly adjusted to the Windows epoch but in order to retain compatibility
	between platforms it should only be used for relative time measurements.
*/
ULONGLONG GetSystemTimeAsULONGLONGrel (void);

/*
	GetSystemTimeAsFileTime
	
	Implementation of the Windows API GetSystemTimeAsFileTime () to make it available
	on POSIX. See
	https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtimeasfiletime
	for details.
*/
#ifdef PLATFORM_IS_POSIX
	void GetSystemTimeAsFileTime (FILETIME *ft);
#endif

/*
	SUBSTRUCT_ULONGLONG_FROM_ULONGLONG
	
	Substracts u2 from u1 provided that u1 is greater or equal to u2.
	If this is not the case the macro sets u1 to (ULONGLONG) -1 to
	signal the underflow.
*/
#define SUBSTRUCT_ULONGLONG_FROM_ULONGLONG(u1, u2)		\
	(((u1) >= (u2)) ? ((u1) - (u2)) : ((ULONGLONG) -1))

/*
	SetFILETIMEtoZero

	Zeros all members of the FILETIME ft.
*/
void SetFILETIMEtoZero (FILETIME *ft);

/*
	SETFILETIMETOZERO
	
	Wrapper macro for SetFILETIMEtoZero () to dereference the pointer to the FILETIME
	structure.
*/
#define SETFILETIMETOZERO(ft)	\
			SetFILETIMEtoZero (&(ft))

/*
	SetFILETIMEtoMaxFILETIME

	Sets both double words of the given FILETIME structure to the max value
	of (-1).
*/
void SetFILETIMEtoMaxFILETIME (FILETIME *ft);

/*
	cpyFILETIME
	
	Copies the contents of the FILETIME structure ftsource into fttarget.
*/
void cpyFILETIME (FILETIME *cunilog_restrict fttarget, FILETIME *cunilog_restrict ftsource);

/*
	CPYFILETIME
	
	Convenience wrapper for cpyFILETIME () that adds references to the FILETIME
	parameters.
*/
#define CPYFILETIME(ft1, ft2)							\
	cpyFILETIME (&(ft1), &(ft2))
	
/*
	cmpFILETIME
	
	Compares the FILETIME structure ft1 with the FILETIME structure ft2.
	
	The function returns 0, if both structures are identical, 1 if ft1 is
	greater than ft2, and -1 if ft1 is smaller than ft2.
*/
int cmpFILETIME (FILETIME *cunilog_restrict ft1, FILETIME *cunilog_restrict ft2);

/*
	CMPFILETIME
	
	Wrapper for cmpFILETIME () to add references to the FILETIME parameters.
*/
#define CMPFILETIME(ft1, ft2)							\
	cmpFILETIME (&(ft1), &(ft2))
	
/*
	isFileTimeNotZero

	Returns true if either part (member) of the FILETIME structure ft is not 0, false
	otherwise.
*/
bool isFileTimeNotZero (FILETIME *ft);

/*
	isFileTimeZero

	Returns true if both members of the FILETIME structure ft are 0, false otherwise.
*/
bool isFileTimeZero (FILETIME *ft);

/*
	ISFILETIMEZERO
	
	Convenience wrapper macro for isFileTimeZero () to dereference the pointer to the
	FILETIME structure.
*/
#define ISFILETIMEZERO(ft)	\
			isFileTimeZero ((&ft))
/*
	FILETIMEfromUnixTimeT
	FILETIMEfromUnixTime
	UnixTimeToFILETIME

	Converts a time_t value to a FILETIME.
	
	Note that this function was called UnixTimeToFileTime () previously
	and that the parameters have been swapped. Target parameter is now
	the first parameter with the time_t second.
*/
//void UnixTimeToFileTime (time_t t, LPFILETIME pft);
void FILETIMEfromUnixTimeT (FILETIME *pft, time_t t);
// We want a compilation error if the old name is used.
#define UnixTimeToFileTime(t,pft)						\
	Error - UnixTimeToFileTime () has been renamed to FILETIMEfromUnixTimeT ()\
	Note that the parameters have also been swapped!
#define UnixTimeToFILETIME(pft, f)						\
	FILETIMEfromUnixTimeT ((pft), (f))
#define FILETIMEfromUnixTime(pft, f)						\
	FILETIMEfromUnixTimeT ((pft), (f))

/*
 *	POSIX systems do not have this structure.
*/
#ifndef _WIN32
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif

/*
*/
void UnixTimeToSystemTime (time_t t, LPSYSTEMTIME pst);

/*
	FileTime_to_POSIX
	
	Converts the FILETIME ft to Unix/POSIX time (or Unix or POSIX epoch). See
	https://en.wikipedia.org/wiki/Unix_time
	
	The function returns the FILETIME parameter ft converted to Unix/POSIX.
*/
LONGLONG FileTime_to_POSIX (FILETIME ft);

/*
	GetISO8601Date

	Retrieves the current local date in ISO 8601 format. The buffer chISO8601 points
	to must be at least SIZ_ISO8601DATE octets long.

	Example of returned string: "YYYY-MM-DD"
*/
void GetISO8601Date (char *chISO8601Date);

/*
	GetISO8601Week_s

	Retrieves the current local date as a string in ISO 8601 format. The buffer
	chISO8601Week points to must be at least SIZ_ISO8601WEEK octets long.
	The function calls snprintf () to compile the output string and might therefore
	be slightly slower than GetISO8601Week_c ().

	Example of returned string: "YYYY-W04"
*/
void GetISO8601Week_s (char *chISO8601Week);

/*
	GetISO8601Week_c

	Retrieves the current local date as a string in ISO 8601 format. The buffer
	chISO8601Week points to must be at least SIZ_ISO8601WEEK octets long.
	The function does not call snprintf () and might therefore be a slightly faster
	alternative to GetISO8601Week_s ().

	Example of returned string: "YYYY-W04"
*/
void GetISO8601Week_c (char *chISO8601Week);

/*
	GetISO8601Week

	Wrapper macro for GetISO8601Week_c ().
*/
#define GetISO8601Week(sz)								\
			GetISO8601Week_c (sz)

/*
	Retrieves the current date/time as a text of the
	International Standard ISO 8601 format:
	YYYY-MM-DD HH:MI:SS +/-TDIF
	The buffer chISO8601DateTimeStamp points to must be at least
	SIZ_ISO8601DATETIMESTAMP bytes long.

	Example return values:	YYYY-MM-DD HH:MI:SS+01:00
							YYYY-MM-DD HH:MI:SS-04:00
							2017-08-29 21:39:10+01:00

	See https://www.cl.cam.ac.uk/~mgk25/iso-time.html and https://en.wikipedia.org/wiki/ISO_8601
	for good summaries.
*/
void GetISO8601DateTimeStamp (char *chISO8601DateTimeStamp);

/*
	storeU8ModifierLetterColon
	storeU8ModifierLetterColon0

	These functions store a modifier letter colon (see https://www.compart.com/en/unicode/U+A789)
	at the address sz points to.

	The function storeU8ModifierLetterColon () stores only the UTF-8 codepoint for the
	modifier letter colon, i.e. writes exactly 3 octets (bytes). It does not write a NUL terminator.

	The function storeU8ModifierLetterColon0 () stores the UTF-8 codepoint for the
	modifier letter colon plus a NUL terminator, i.e. writes exactly 4 octets (bytes).
*/
void storeU8ModifierLetterColon (char *sz);
void storeU8ModifierLetterColon0 (char *sz);

/*
	Retrieves the current date/time as a text of the
	International Standard ISO 8601 format:
	YYYY-MM-DD HH:MI:SS +/-TDIF
	
	Instead of a colon (":"), the modifier letter colon is inserted to make
	the string compatible with NTFS, the native file system of Windows.
	See https://www.compart.com/en/unicode/U+A789 and
	https://www.unicode-symbol.com/u/A789.html .

	The buffer chISO8601DateTimeStamp points to must be at least
	SIZ_ISO8601DATETIMESTAMPU8C bytes long.

	Example return values:	YYYY-MM-DD HH:MI:SS+01:00
							YYYY-MM-DD HH:MI:SS-04:00
							2017-08-29 21:39:10+01:00

	Note that each colon character (the so-called modifier letter colon) is 3 octets
	(bytes) long instead of one. For the purpose of this comment, the text above contains
	normal colons, though.

	See https://www.cl.cam.ac.uk/~mgk25/iso-time.html and https://en.wikipedia.org/wiki/ISO_8601
	for good summaries.
*/
void GetISO8601DateTimeStampU8colon (char *chISO8601DateTimeStampU8c);

/*
	GetISO8601DateTimeStampT
	
	The function is identical to GetISO8601DateTimeStamp (), which retrieves the
	current date/time as a text of the International Standard ISO 8601 format,
	with the exception that GetISO8601DateTimeStampT () inserts the 'T' character
	referred to by the standard. The buffer chISO8601DateTimeStamp points to must be
	at least SIZ_ISO8601DATETIMESTAMP bytes long.

	Example return values:	YYYY-MM-DDTHH:MI:SS+01:00
							YYYY-MM-DDTHH:MI:SS-04:00
							2017-08-29T21:39:10+01:00
							
	While it is easier for a human to read an ISO 8601 date/time containing a
	blank (or space) character (' ', ASCII 20h, 32d) instead of a capital 'T',
	some applications might require precise conformity to the standard.
*/
void GetISO8601DateTimeStampT (char *chISO8601DateTimeStamp);

/*
	GetISO8601DateTimeStampMS

	Returns the current date/time in ISO 8601 format.
	2008-10-23 10:44:42.012+01:00

	Retrieves the current date/time as a text of the
	International Standard ISO 8601 format:
	YYYY-MM-DD HH:MI:SS.mis+/-TDIF
	yyyy-mm-dd hh:mi:ss.mis+01:00

	Example: YYYY-MM-DD HH:MI:SS.125+01:00
	         YYYY-MM-DD HH:MI:SS.490-04:00

	The string chISODateTime must hold enough space for 29 characters + NUL. The constant
	SIZ_ISO8601DATETIMESTAMPMS can be used for this length.
	
*/
void GetISO8601DateTimeStampMS (char *chISO8601DateTimeStampMS);

/*
	GetISO8601DateTimeStampMST
	
	The function calls GetISO8601DateTimeStampMS () to obtain an ISO 8601 date and timestamp,
	including milliseconds and offset, then inserts the 'T' the standard requires.

	The buffer chISO8601DateTimeStampMS points to must be at least SIZ_ISO8601DATETIMESTAMPMS
	octets long.
*/
void GetISO8601DateTimeStampMST (char *chISO8601DateTimeStampMS);

/*
	ubf_get_system_time
	
	Returns the system time (in UTC) as a FILETIME structure.
*/
void ubf_get_system_time (FILETIME *ft);

/*
	UBF_GET_SYSTEM_TIME

	Convenience macro to dereference the pointer parameter of ubf_get_system_time ().
*/
#define UBF_GET_SYSTEM_TIME(t)	\
			ubf_get_system_time (&(t))
/*
	ubf_get_local_time
	
	Returns the local time as a FILETIME structure.
*/
//void ubf_get_local_time (FILETIME *ft);

/*
	UBF_GET_LOCAL_TIME

	Convenience macro to dereference the pointer parameter of ubf_get_local_time ().
*/
/* Maybe this function is not required.
#define UBF_GET_LOCAL_TIME(t)	\
			ubf_get_local_time (&(t))
*/

/*
	ubf_get_system_time_ULONGLONG

	Returns the system time as ULONGLONG in the buffer pulltime points to.
*/
void ubf_get_system_time_ULONGLONG (ULONGLONG *pulltime);

/*
	UBF_GET_SYSTEM_TIME_ULONGLONG

	Convenience wrapper macro for ubf_get_system_time_ULONGLONG () to dereference the
	parameter.
*/
#define UBF_GET_SYSTEM_TIME_ULONGLONG(l)	\
			ubf_get_system_time_ULONGLONG (&(l))

/*
	ubf_get_system_time_ULONGLONG_rel
	
	Returns the relative system time as ULONGLONG in the buffer pulltime
	points to by calling GetSystemTimeAsULONGLONG_rel ().
*/
void ubf_get_system_time_ULONGLONG_rel (ULONGLONG *pulltime);

/*
	UBF_GET_SYSTEM_TIME_ULONGLONG_REL

	Convenience wrapper macro for ubf_get_system_time_ULONGLONG_rel () to dereference the
	parameter.
*/
#define UBF_GET_SYSTEM_TIME_ULONGLONG_REL(l)	\
			ubf_get_system_time_ULONGLONG_rel (&(l))

/*
	clock_gettime

	Dodgy implementation of the clock_gettime () API on Linux/Unix derivatives for
	Windows. See https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
	and https://linux.die.net/man/3/clock_gettime . For us, this function is good enough
	at the moment since we're not using high precisions. It is fast and simple.
	http://www.catb.org/esr/time-programming/ shows that clock_gettime () is part of
	POSIX, hence should be available on all supported platforms.
*/
#ifdef UBF_WINDOWS
	int clock_gettime (int iclk_id, struct timespec *spec);
#endif

/*
	Parameters for clock_gettime (). We only support CLOCK_REALTIME and CLOCK_MONOTONIC.
	These are again for Windows only since Unix/Linux platforms should come with them
	natively. Their values here have been made up by me (2017-10-02, Thomas) and have
	nothing to do with their values in time.h on Linux/Unix platforms.
*/
#ifdef OS_IS_WINDOWS
	#ifndef CLOCK_REALTIME
	#define CLOCK_REALTIME		0
	#endif
	#ifndef CLOCK_MONOTONIC
	#define CLOCK_MONOTONIC		1
	#endif
#endif

// The coarse clock IDs on POSIX systems. See
//	http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE			CLOCK_REALTIME
#endif
#ifndef CLOCK_MONOTONIC_COARSE
#define CLOCK_MONOTONIC_COARSE			CLOCK_MONOTONIC
#endif

/*
	IsLeapYear

	Returns true if the year in Y is a leap year, false otherwise.

	Excerpt from https://en.wikipedia.org/wiki/Leap_year :

	"Every year that is exactly divisible by four is a leap year, except for years that are
	exactly divisible by 100, but these centurial years are leap years if they are exactly
	divisible by 400. For example, the years 1700, 1800, and 1900 are not leap years, but
	the years 1600 and 2000 are."
*/
bool IsLeapYear (uint32_t uiYear);

/*
	GetISO8601DayOfYear

	Returns the day number of the day of year y, month m, and day of month d.
*/
uint32_t GetISO8601DayOfYear (uint32_t y, uint8_t m, uint8_t d);

/*
	GetISO8601Jan1WeekDay
*/
uint8_t GetISO8601Jan1WeekDay (uint32_t Y);

/*
	GetISO8601WeekDay
*/
uint32_t GetISO8601WeekDay (uint32_t y, uint8_t m, uint8_t d);

/*
	GetISO8601WeekNumberFromDate
	
	Returns the ISO 8601 week number for the given date. The parameter
	aY points to a uint32_t variable in which the function stores the year
	number which may have been adjusted to y + 1. The caller is advised
	to always work with this returned year.
*/
uint8_t GetISO8601WeekNumberFromDate (uint32_t y, uint8_t m, uint8_t d, uint32_t *aY);

/*
	HasMonth28Days
	
	Returns true if the month m has 28 days. In addition to the month, this
	function requires the year to determine if it is a leap year.

	Note that this function had year y and month m swapped before 2025-07-15.
*/
bool HasMonth28Days (uint32_t y, uint8_t m);

/*
	HasMonth29Days
	
	Returns true if the month m has 29 days. In addition to the month, this
	function requires the year to determine if it is a leap year.

	Note that this function had year y and month m swapped before 2025-07-15.
*/
bool HasMonth29Days (uint32_t y, uint8_t m);

/*
	HasMonth30Days
	
	Returns true if the month m has 30 days.
*/
bool HasMonth30Days (uint8_t m);

/*
	HasMonth31Days
	
	Returns true if the month m has 31 days.
*/
bool HasMonth31Days (uint8_t m);

/*
	DaysInMonth
	
	Returns the number of days within month m of year y.
*/
uint8_t DaysInMonth (uint32_t y, uint8_t m);

/*
	_DayOfWeek
	
	Returns the day of the week starting with 0 == Sunday, 1 == Monday, etc.
	The original version of this function has been taken from
	https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Implementation-dependent_methods
	(Tomohiko Sakamoto).
	
	The year must be > 1752, at least in the UK. See
	https://en.wikipedia.org/wiki/Old_Style_and_New_Style_dates for more details.
	
	Use the function DayOfWeek () to obtain the weekday according to ISO 8601
	where 0 == Monday, 1 == Tuesday, ..., 6 == Sunday.
*/
uint8_t _DayOfWeek (uint32_t y, uint8_t m, uint8_t d);

/*
	DayOfWeek
	
	Returns the day of the week according to ISO 8601 weekday ordering, starting with
	0 == Monday, 1 == Tuesday, ..., 6 == Sunday.

	The year must be > 1752, at least in the UK, since the function calls _DayOfWeek ()
	to obtain the day of week and adjusts it to an ISO 8601 weekday.
*/
uint8_t DayOfWeek (uint32_t y, uint8_t m, uint8_t d);

/*
	FILETIME_to_ISO8601

	Writes an array of characters in ISO 8601 format to chISO from the FILETIME structure
	ft points to. Since a FILETIME structure does not contain an offset to UTC, the
	output has the format "YYYY-MM-DD hh:mm:ss.xxx" and does not include an offset. The
	buffer chISO points to is expected to be at least SIZ_ISO8601DATETIMESTAMPMS_NO_OFFS
	bytes long.
	
	The function has never been implemented.
*/
void FILETIME_to_ISO8601 (char *chISO, FILETIME *ft);

/*
	IsBuildYearOrNewer_UBF_TIMESTAMP

	Returns true if the UBF_TIMESTAMP pts points to is reasonably recent
	and seems legit. Reasonably recent means at least from the year the function
	BuildYear_uint64 () returns, which is the compilation/build year of this
	module. All values are checked against their maximum ranges. The function
	does not check if the given date/timestamp exists. For instance, the
	function returns true for 2021-02-31 if the module was compiled in
	2021. It would return false for 2021-02-31 if the module was compiled
	in 2022.
*/
bool IsBuildYearOrNewer_UBF_TIMESTAMP (UBF_TIMESTAMP *pts);

/*
	ValuesWithinLimits_SUBF_TIMESTRUCT

	Returns true if all values of the SUBF_TIMESTRUCT ts points to are
	within the limits, false otherwise. The function does not check whether the
	date/timestamp is valid/exists. For instance, the function returns true for
	2021-02-31, which is not a valid date because it does not exist.
*/
bool ValuesWithinLimits_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *ts);

/*
	UBF_TIMESTAMP_to_SUBF_TIMESTRUCT

	Converts the UBF_TIMESTAMP to a SUBF_TIMESTRUCT and stores it at the memory
	ts points to.

	The macro SUBF_TIMESTRUCT_from_UBF_TIMESTAMP() is provided for parameter
	consistency with its name, which is function (target, source).

	The function returns true on success, false otherwise.
*/
bool UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *ts, UBF_TIMESTAMP t);

#define SUBF_TIMESTRUCT_from_UBF_TIMESTAMP(ts, ut)		\
			UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (ts, ut)

/*
	SUBF_TIMESTRUCT_to_ISO8601
	ISO8601_from_SUBF_TIMESTRUCT

	Writes an array of characters in ISO 8601 format to chISO from the SUBF_TIMESTRUCT
	pts points to. Since a SUBF_TIMESTRUCT structure contains an offset to UTC,
	the output has the format "YYYY-MM-DD HH:MI:SS.000+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMPMS, or LEN_ISO8601DATETIMESTAMPMS + 1, bytes long, which
	includes a terminating NUL byte.
*/
void SUBF_TIMESTRUCT_to_ISO8601 (char *chISO, SUBF_TIMESTRUCT *pts);

#define ISO8601_from_SUBF_TIMESTRUCT(i, p)				\
	SUBF_TIMESTRUCT_to_ISO8601((i), (p))

/*
	ISO8601_from_UBF_TIMESTAMPs

	Writes an array of characters in ISO 8601 format to chISO from the UBF_TIMESTAMP
	ts. Instead of the ISO 8601 date and time separator ("T") this functions inserts a
	space for easier human readability. Since a UBF_TIMESTAMP timestamp contains an offset
	to UTC, the output has the format "YYYY-MM-DD HH:MI:SS.000+01:00", which includes the
	offset to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMPMS, or LEN_ISO8601DATETIMESTAMPMS + 1, bytes long, which
	includes a terminating NUL byte.

	If a fully ISO 8601 compliant representation is required, the function
	ISO8601T_from_UBF_TIMESTAMP () returns the same string but with the correct
	date and time separator ("T"), i.e. "YYYY-MM-DDTHH:MI:SS.000+01:00".
*/
void ISO8601_from_UBF_TIMESTAMPs (char *chISO, UBF_TIMESTAMP ts);

/*
	This macro should be made obsolete. 2024-08-13, Thomas.

	2025-02-01: Made obsolete.
*/
#define UBF_TIMESTAMP_to_ISO8601(i, t)				\
	Should cause a compiler error: "Macro UBF_TIMESTAMP_to_ISO8601() obsolete. Use ISO8601_from_UBF_TIMESTAMP()"
	//ISO8601_from_UBF_TIMESTAMP ((i), (t))
	

/*
	ISO8601_from_UBF_TIMESTAMPc

	The function is identical to ISO8601_from_UBF_TIMESTAMP () but does not use snprintf (),
	which means it is faster than ISO8601_from_UBF_TIMESTAMP ().
*/
void ISO8601_from_UBF_TIMESTAMPc (char *chISO, UBF_TIMESTAMP ts);

/*
	ISO8601_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601_from_UBF_TIMESTAMP(c,t)				\
		ISO8601_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601_from_UBF_TIMESTAMP(c,t)			\
		ISO8601_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601T_from_UBF_TIMESTAMPs

	Writes an array of characters in ISO 8601 format to chISO from the UBF_TIMESTAMP
	ts. Since a UBF_TIMESTAMP timestamp contains an offset to UTC,
	the output has the format "YYYY-MM-DDTHH:MI:SS.000+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMPMS, or LEN_ISO8601DATETIMESTAMPMS + 1, bytes long, which
	includes a terminating NUL byte.

	This function inserts the fully compliant date and time separator, which is a capital
	"T". The function ISO8601_from_UBF_TIMESTAMP () produces an identical result but
	replaces the T with a more human readable space character.
*/
void ISO8601T_from_UBF_TIMESTAMPs (char *chISO, UBF_TIMESTAMP ts);

/*
	This macro should be made obsolete. 2024-08-13, Thomas.

	2025-02-01: Made obsolete.
*/
#define UBF_TIMESTAMP_to_ISO8601T(i, t)				\
	Should cause a compiler error: "Macro UBF_TIMESTAMP_to_ISO8601T() obsolete. Use ISO8601T_from_UBF_TIMESTAMP()"
	//ISO8601T_from_UBF_TIMESTAMP ((i), (t))

/*
	ISO8601T_from_UBF_TIMESTAMPc

	The function is identical to ISO8601T_from_UBF_TIMESTAMP () but does not use snprintf (),
	which means it is much faster than ISO8601T_from_UBF_TIMESTAMP ().
*/
void ISO8601T_from_UBF_TIMESTAMPc (char *chISO, UBF_TIMESTAMP ts);

/*
	ISO8601T_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601T_from_UBF_TIMESTAMP(c,t)			\
		ISO8601T_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601T_from_UBF_TIMESTAMP(c,t)			\
		ISO8601T_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601Date_from_UBF_TIMESTAMPs

	Saves the NUL-terminated date of the UBF_TIMESTAMP ts in the buffer chISODateOnly
	points to. The buffer must have a size of at least SIZ_ISO8601DATE octets.

	Example of returned string: "YYYY-MM-DD"
*/
void ISO8601Date_from_UBF_TIMESTAMPs (char *chISODateOnly, UBF_TIMESTAMP ts);

/*
	ISO8601Date_from_UBF_TIMESTAMPc

	The function is identical to ISO8601Date_from_UBF_TIMESTAMP () but does not use snprintf (),
	which means it is faster than ISO8601Date_from_UBF_TIMESTAMP ().
*/
void ISO8601Date_from_UBF_TIMESTAMPc (char *chISODateOnly, UBF_TIMESTAMP ts);

/*
	ISO8601Date_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601Date_from_UBF_TIMESTAMP(c,t)			\
		ISO8601Date_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601Date_from_UBF_TIMESTAMP(c,t)			\
		ISO8601Date_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601YearAndWeek_from_UBF_TIMESTAMPs

	Retrieves the date/time stamp ts as a NUL-terminated string in ISO 8601 format. The buffer
	chISO8601Week points to must be at least SIZ_ISO8601YEARANDWEEK octets long.

	Example of returned string: "YYYY-W04"
*/
void ISO8601YearAndWeek_from_UBF_TIMESTAMPs (char *chISO8601YearAndWeek, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndWeek_from_UBF_TIMESTAMPc

	Identical to ISO8601YearAndWeek_from_UBF_TIMESTAMP () but does not call snprintf (),
	which means it might be slightly faster.

	Example of returned string: "YYYY-W04"
*/
void ISO8601YearAndWeek_from_UBF_TIMESTAMPc (char *chISO8601YearAndWeek, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndWeek_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601YearAndWeek_from_UBF_TIMESTAMP(c,t)	\
		ISO8601YearAndWeek_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601YearAndWeek_from_UBF_TIMESTAMP(c,t)	\
		ISO8601YearAndWeek_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601DateAndHour_from_UBF_TIMESTAMPs

	Retrieves the date/time stamp in ts as a NUL-terminated string in ISO 8601 that contains the
	date and the hour. The buffer chISODateAndHour points to must be at least
	SIZ_ISO8601DATEANDHOUR octets long.

	The function does not take an offset into consideration and might therefore
	result in an hour value that is perceived as being incorrect (although it is not).

	Example of returned string: "YYYY-MM-DD 18"
*/
void ISO8601DateAndHour_from_UBF_TIMESTAMPs (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601DateAndHour_from_UBF_TIMESTAMPc

	The function is identical to ISO8601DateAndHour_from_UBF_TIMESTAMP () but does not
	call snprintf (), which means it is faster than ISO8601DateAndHour_from_UBF_TIMESTAMP ().
*/
void ISO8601DateAndHour_from_UBF_TIMESTAMPc (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601DateAndHour_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601DateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateAndHour_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601DateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateAndHour_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601TDateAndHour_from_UBF_TIMESTAMPs

	The function is identical to ISO8601DateAndHour_from_UBF_TIMESTAMPs () but inserts
	a "T" instead of a space between date and time.
*/
void ISO8601TDateAndHour_from_UBF_TIMESTAMPs (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601TDateAndHour_from_UBF_TIMESTAMPc

	The function is identical to ISO8601DateAndHour_from_UBF_TIMESTAMPc () but inserts
	a "T" instead of a space between date and time.
*/
void ISO8601TDateAndHour_from_UBF_TIMESTAMPc (char *chISODateAndHour, UBF_TIMESTAMP ts);

/*
	ISO8601TDateAndHour_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601TDateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateAndHour_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601TDateAndHour_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateAndHour_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMPs

	Retrieves the date/time stamp in ts as a NUL-terminated string in ISO 8601 that contains the
	date, hour, and minute. The buffer chISODateHourAndMinute points to must be at least
	SIZ_ISO8601DATEHOURANDMINUTE octets long.

	The function does not take an offset into consideration and might therefore
	result in an hour value that is perceived as being incorrect (although it is not).

	Example of returned string: "2023-11-16 09:47"
*/
void ISO8601DateHourAndMinute_from_UBF_TIMESTAMPs (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMPc

	The function is identical to ISO8601DateHourAndMinute_from_UBF_TIMESTAMP () but does not call
	snprintf. It is therefore much faster.
*/
void ISO8601DateHourAndMinute_from_UBF_TIMESTAMPc (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601DateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateHourAndMinute_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601DateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601DateHourAndMinute_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_

	Retrieves the date/time stamp in ts as a NUL-terminated string in ISO 8601 that contains the
	date, hour, and minute. Hour and minute are separated by an underscore instead of a colon
	in order to use it in filenames on Windows.
	The buffer chISODateHourAndMinute points to must be at least SIZ_ISO8601DATEHOURANDMINUTE
	octets long.

	The function does not take an offset into consideration and might therefore
	result in an hour value that is perceived as being incorrect (although it is not).

	Example of returned string: "2023-11-16 09_47"
*/
void ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_ (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMPs

	The function is identical to ISO8601DateHourAndMinute_from_UBF_TIMESTAMPs () but inserts
	a "T" instead of a space between date and time.

	Example of returned string: "2023-11-16T09:47"
*/
void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMPs (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMPc

	The function is identical to ISO8601DateHourAndMinute_from_UBF_TIMESTAMPc () but inserts
	a "T" instead of a space between date and time.

	Example of returned string: "2023-11-16T09:47"
*/
void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMPc (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP

	Wrapper macro to switch between the _s or the _c version of the function. The
	_s version uses snprintf () to compile the result string while the _c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateHourAndMinute_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP(c,t)	\
		ISO8601TDateHourAndMinute_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_

	Retrieves the date/time stamp in ts as a NUL-terminated string in ISO 8601 that contains the
	date, hour, and minute. Hour and minute are separated by an underscore instead of a colon
	in order to use it in filenames on Windows. Date and time are separated by a "T".
	The buffer chISODateHourAndMinute points to must be at least SIZ_ISO8601DATEHOURANDMINUTE
	octets long.

	The function does not take an offset into consideration and might therefore
	result in an hour value that is perceived as being incorrect (although it is not).

	Example of returned string: "2023-11-16T09_47"
*/
void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_ (char *chISODateHourAndMinute, UBF_TIMESTAMP ts);

/*
	ISO8601Year_from_UBF_TIMESTAMPs

	Returns the year extracted from ts as "YYYY" as a NUL-terminated string. The buffer
	chYear points to must be at least SIZ_ISO8601YEAR octets big.
*/
void ISO8601Year_from_UBF_TIMESTAMPs (char *chYear, UBF_TIMESTAMP ts);

/*
	ISO8601Year_from_UBF_TIMESTAMPc

	The function is identical to ISO8601Year_from_UBF_TIMESTAMPs () but is slightly faster
	since it does not not call snprintf ().

	Returns the year extracted from ts as "YYYY" as a NUL-terminated string. The buffer
	chYear points to must be at least SIZ_ISO8601YEAR octets big.
*/
void ISO8601Year_from_UBF_TIMESTAMPc (char *chYear, UBF_TIMESTAMP ts);

/*
	ISO8601Year_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601Year_from_UBF_TIMESTAMP(c,t)	\
		ISO8601Year_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601Year_from_UBF_TIMESTAMP(c,t)	\
		ISO8601Year_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	ISO8601YearAndMonth_from_UBF_TIMESTAMPs

	Returns the extracted year and month as "YYYY-MM". The buffer pointed to by
	chISOYearAndMonth must be at least SIZ_ISO8601YEARANDMONTH bytes long. The returned
	string is NUL-terminated.
*/
void ISO8601YearAndMonth_from_UBF_TIMESTAMPs (char *chISOYearAndMonth, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndMonth_from_UBF_TIMESTAMPc

	The function is identical to ISO8601YearAndMonth_from_UBF_TIMESTAMP () but is faster
	because it does not call snprintf ().
*/
void ISO8601YearAndMonth_from_UBF_TIMESTAMPc (char *chISOYearAndMonth, UBF_TIMESTAMP ts);

/*
	ISO8601YearAndMonth_from_UBF_TIMESTAMP

	Wrapper macro to switch between the s or the c version of the function. The
	s version uses snprintf () to compile the result string while the c version
	doesn't.
*/
#ifdef UBF_DATE_AND_TIME_USE_SPRINTF
	#define ISO8601YearAndMonth_from_UBF_TIMESTAMP(c,t)	\
		ISO8601YearAndMonth_from_UBF_TIMESTAMPs (c, t)
#else
	#define ISO8601YearAndMonth_from_UBF_TIMESTAMP(c,t)	\
		ISO8601YearAndMonth_from_UBF_TIMESTAMPc (c, t)
#endif

/*
	A quick note regarding the "...to..." functions:

	Our premise is to follow the memcpy () or strcpy () principle of storing output at
	the address a function's/macro's first parameter points to. The "...to..." functions/
	macros contradict this premise and will therefore be made deprecated/obsolte in the
	future. The "...from..." versions are the ones to focus on.

	Over time more and more of these function names will be changed.
*/

/*
	UBF_TIMESTAMP_to_ISO8601_Holocene
	ISO8601_Holocene_from_UBF_TIMESTAMP

	Identical to UBF_TIMESTAMP_to_ISO8601 () but returns the timestamp in the
	Holocene format. See https://en.wikipedia.org/wiki/Holocene_calendar .
	The buffer chISO points to must be at least SIZ_ISO8601DATETIMESTAMPMS_HOL
	long. This includes a terminating NUL byte.
*/
void UBF_TIMESTAMP_to_ISO8601_Holocene (char *chISO, UBF_TIMESTAMP ts);

#define ISO8601_Holocene_from_UBF_TIMESTAMP(i, ts)		\
	UBF_TIMESTAMP_to_ISO8601_Holocene ((i), (ts))

/*
	SUBF_TIMESTRUCT_to_ISO8601_no_ms
	ISO8601_no_ms_from_SUBF_TIMESTRUCT

	Writes an array of characters in ISO 8601 format to chISO from the SUBF_TIMESTRUCT
	t points to but without milliseconds. Since a SUBF_TIMESTRUCT contains an offset to UTC,
	the output has the format "YYYY-MM-DD HH:MI:SS+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMP bytes long.
*/
void SUBF_TIMESTRUCT_to_ISO8601_no_ms (char *chISO, SUBF_TIMESTRUCT *t)
;

#define ISO8601_no_ms_from_SUBF_TIMESTRUCT(i, t)		\
	SUBF_TIMESTRUCT_to_ISO8601_no_ms ((i), (t))

/*
	UBF_TIMESTAMP_to_ISO8601_no_ms

	Writes an array of characters in ISO 8601 format to chISO from the UBF_TIMESTAMP
	ts but without milliseconds. Since a UBF_TIMESTAMP timestamp contains an offset to UTC,
	the output has the format "YYYY-MM-DD HH:MI:SS+01:00", which includes the offset
	to UTC. The buffer chISO points to is therefore expected to be at least
	SIZ_ISO8601DATETIMESTAMP bytes long.

	The function first converts the UBF_TIMESTAMP ts into a SUBF_TIMESTRUCT structure,
	then calls SUBF_TIMESTRUCT_to_ISO8601_no_ms ().
*/
void UBF_TIMESTAMP_to_ISO8601_no_ms (char *chISO, UBF_TIMESTAMP ts);


/*
	UBF_TIMESTAMP_from_ISO8601_no_ms_Holocene

	Identical to UBF_TIMESTAMP_to_ISO8601_no_ms () but returns the timestamp
	in the Holocene format, which is 10000 years greater than the ISO8601
	timestamp. See https://en.wikipedia.org/wiki/Holocene_calendar for more information.
	The buffer chISO must have space for at least SIZ_ISO8601DATETIMESTAMP_HOL
	octets. This number includes the terminating NUL character.
*/
void ISO8601_from_UBF_TIMESTAMP_no_ms_Holocene (char *chISO, UBF_TIMESTAMP ts);

/*
	To be deprecated/made obsolete in the future.
*/
#define UBF_TIMESTAMP_to_ISO8601_no_ms_Holocene(c, t)	\
	UBF_TIMESTAMP_from_ISO8601_no_ms_Holocene ((c), (t))

/*
	NCSADATETIME_from_UBF_TIMESTAMP

	Obtains an NCSA date/timestamp from the UBF_TIMESTAMP structure ts.
	The timestamp follows the date/time format of the Common Log Format. See
	https://en.wikipedia.org/wiki/Common_Log_Format for more details.

	The buffer szncsadtim points to must be at least SIZ_NCSA_COMMON_LOG_DATETIME long, which
	includes a terminating NUL character.

	The function does not check if the UBF_TIMESTAMP ts contains a valid date.

	"[10/Oct/2000:13:55:36 -0700]"
*/
void NCSADATETIME_from_UBF_TIMESTAMP (char *szncsadtim, UBF_TIMESTAMP ts)
;

/*
	MS_from_SUBF_TIMESTRUCT

	Returns the amount of milliseconds of the time of the SUBF_TIMESTRUCT pts points
	to. The date is not taken into account, and neither is an offset.
*/
uint64_t MS_from_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts);

/*
	GetLocalTime_ISO8601T_noMSnoOffs

	Returns the current local date and time in ISO 8601 format, excluding milliseconds
	and excluding a timezone.

	The buffer szISO points to must be at least LEN_ISO8601DATETIMESTAMP_NO_OFFS octets/bytes
	long. The function does not NUL-terminate the string. It writes out exactly
	LEN_ISO8601DATETIMESTAMP_NO_OFFS octets/bytes. For an identical function that does
	NUL-terminate the string, see GetLocalDateTime_ISO8601T_noMSnoOffs_n () below.

	"YYYY-MM-DDThh:mm:ss"
*/
void GetLocalDateTime_ISO8601T_noMSnoOffs (char *szISO)
;

/*
	GetLocalDateTime_ISO8601T_noMSnoOffs_n

	Returns the current local date and time in ISO 8601 format, excluding milliseconds
	and excluding a timezone.

	The buffer szISO points to must be at least SIZ_ISO8601DATETIMESTAMP_NO_OFFS, which is
	LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1 octets/bytes long. The function writes out exactly
	SIZ_ISO8601DATETIMESTAMP_NO_OFFS octets/bytes. For an identical function that does
	not write a NUL terminator, see GetLocalDateTime_ISO8601T_noMSnoOffs () below.

	"YYYY-MM-DDThh:mm:ss"
*/
void GetLocalDateTime_ISO8601T_noMSnoOffs_n (char *szISO)
;

/*
	BuildYear_uint64

	Returns the compilation year of the module (when it is compiled) as an unsigned
	16 bit integer. It uses the C/C++ default preprocessor macro __DATE__ to obtain
	this year.
*/
uint64_t BuildYear_uint64 (void);

/*
	BuildYear_uint32

	Returns the compilation year of the module (when it is compiled) as an unsigned
	32 bit integer. The function calls YearOfBuilduint64 and shortens its result
	to a uint32_t.
*/
uint32_t BuildYear_uint32 (void);

/*
	BuildYear_uint16

	Returns the compilation year of the module (when it is compiled) as an unsigned
	16 bit integer. The function calls YearOfBuilduint64 and shortens its result
	to a uint16_t.
*/
uint16_t BuildYear_uint16 (void);

/*
	is_datetimestampformat_l

	Checks if the string str might be a date/timestamp.

	The function only checks if digits are where they should be. It does not carry out
	any sanity check on the date/timestamp itself. This means "0000-00-00" is a valid
	date/timestamp, and the function returns true in this case.

	The function is actually just a wrapper for is_datetimestampformat_l_store_corrected ()
	that calls it with the parameter corr set to NULL.
*/
bool is_datetimestampformat_l (const char *str, size_t len);

/*
	is_datetimestampformat_l_store_corrected

	The function is identical to is_datetimestampformat_l () but additionally stores
	the corrected format in the buffer corr points to.

	The buffer corr points to can either be NULL, in which case the function is identical
	to is_datetimestampformat_l (), or it must point to a buffer of at least
	SIZ_ISO8601DATETIMESTAMPMS_NO_OFFS octets/bytes to store the result of the correction
	in the format "YYYY-MM-DD hh:mm:ss.xxx", or shorter if not all the information is
	provided in str.

	Note that the ISO 'T' date/time separator is replaced by a space charcter in corr.
	The caller can only rely on something useful being in corr when the function returns
	true.
*/
bool is_datetimestampformat_l_store_corrected (char *corr, const char *str, size_t len);

/*
	FormattedMilliseconds

	Copies the time value in uiTimeInMilliseconds as a formatted string to the
	buffer chFormatted points to.

	The output copied to chFormatted is "hh:mm:ss.mis", where hh are the hours,
	mm the minutes, ss the seconds, and mis the remaining milliseconds. The
	caller is responsible for providing a buffer of at least 13 octets (bytes),
	which is defined by FORMATTEDMILLISECONDS_SIZE.

	The function returns true if the value of uiTimeInMilliseconds was written
	to the buffer chFormatted points to. The function returns false if the value
	does not fit in a maximum of 99 hours, 59 minutes, 59 seconds, and 999
	milliseconds. When the function returns false nothing is written to
	chFormatted.
*/
#define FORMATTEDMILLISECONDS_SIZE		(13)
#define FORMATTEDMILLISECONDS_LEN		(FORMATTEDMILLISECONDS_SIZE - 1)
bool FormattedMilliseconds (char *chFormatted, const uint64_t uiTimeInMilliseconds);

#ifdef DEBUG
	#ifndef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
	#define UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
	#endif
#endif

#ifndef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
//#define UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
#endif

/*
	TestFormattedMilliseconds

	Test function.
*/
#ifdef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
		bool Test_ubf_times_functions (void);
#else
		#define Test_ubf_times_functions()	(true)
#endif


#ifdef __cplusplus
	}
#endif

#endif															// Of U_UBF_DATETIME_H_INCLUDED.
