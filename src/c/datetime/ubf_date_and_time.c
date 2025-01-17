/****************************************************************************************

	File:		ubf_date_and_time.c
	Why:		Functions for handling date and time.
	OS:			Windows NT Ver. 4.0/2000/XP/Vista/7/8...
	Author:		Thomas
	Created:	2016-11-02
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2016-11-02	Thomas			Created.
2017-08-29	Thomas			Function GetISO8601DateTimeStampT () added.
2018-04-06	Thomas			Some calculations taken from Logtext's GetCurrentDateTimeText.c.
2019-08-13	Thomas			Updated to use the C99 printf () format specifiers.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#include <stdio.h>
#include <inttypes.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubf_date_and_time.h"
	#include "./../pre/unref.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./strintuint.h"
		#include "./ubfdebug.h"
	#else
		#include "./../string/strintuint.h"
		#include "./../dbg/ubfdebug.h"
	#endif

	#ifdef PLATFORM_IS_POSIX
		#include "./timespecfncts.h"
	#endif
#endif

void GetReadableTimeSpan			(
										char		*chBuf,
										size_t		stLen,
										ULONGLONG 	ullTime
									)
{
	ULONGLONG		ullDays;
	ULONGLONG		ullHours;
	ULONGLONG		ullMinutes;
	ULONGLONG		ullSeconds;
	ULONGLONG		ullMiSeconds;
	
	ubf_assert (chBuf != NULL);
	ubf_assert (stLen != 0);
	ullDays		 = ullTime / FT_DAY;
	ullTime		-= ullDays * FT_DAY;
	ullHours	 = ullTime / FT_HOUR;
	ullTime		-= ullHours * FT_HOUR;
	ullMinutes	 = ullTime / FT_MINUTE;
	ullTime		-= ullMinutes * FT_MINUTE;
	ullSeconds	 = ullTime / FT_SECOND;
	ullTime		-= ullSeconds * FT_SECOND;
	ullMiSeconds = ullTime / FT_MICROSECOND;
	// Example: "  7d 19:22:10.731322"
	snprintf (chBuf, stLen, "%" PRIu64 "d %2.2" PRIu64 ":%2.2" PRIu64 ":%2.2" PRIu64".%6.6" PRIu64,
			ullDays, ullHours, ullMinutes, ullSeconds, ullMiSeconds);
}

void GetReadableTimeSpanFILETIME	(
										char		*chBuf,
										size_t		stLen,
										FILETIME	ftTime
									)
{
	GetReadableTimeSpan (chBuf, stLen, ULONGLONGfromFILETIME (ftTime));
}

ULONGLONG GetSystemTimeAsULONGLONG (void)
{
	#ifdef OS_IS_ANDROID
		// See
		//	https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code .
		struct timespec		ts;
		
		clock_gettime (CLOCK_REALTIME, &ts);
		return ULONGLONG_from_timespec (&ts);
	#endif
	#ifdef OS_IS_IOS
		struct timespec		ts;
		
		clock_gettime (CLOCK_REALTIME, &ts);
		return ULONGLONG_from_timespec (&ts);
	#endif
	#ifdef OS_IS_LINUX
		struct timespec		ts;
		
		clock_gettime (CLOCK_REALTIME, &ts);
		return ULONGLONG_from_timespec (&ts);
	#endif
	#ifdef OS_IS_OSX
		struct timespec		ts;
		
		clock_gettime (CLOCK_REALTIME, &ts);
		return ULONGLONG_from_timespec (&ts);
	#endif
	#ifdef OS_IS_UNIX
		struct timespec		ts;
		
		clock_gettime (CLOCK_REALTIME, &ts);
		return ULONGLONG_from_timespec (&ts);
	#endif
	#ifdef OS_IS_WINDOWS
		// Windows has a single API GetSysteTimeAsFileTime () for this.
		//	See https://msdn.microsoft.com/en-us/library/windows/desktop/ms724397(v=vs.85).aspx .
		FILETIME		ft;

		GetSystemTimeAsFileTime (&ft);
		return ULONGLONGfromFILETIME(ft);
	#endif
}

ULONGLONG GetSystemTimeAsULONGLONGrel (void)
{
	#ifdef OS_IS_ANDROID
		// See
		//	https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code
		//	and http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
		struct timespec		ts;
		
		clock_gettime (CLOCK_MONOTONIC_COARSE, &ts);
		return ULONGLONG_from_timespec_rel (&ts);
	#endif
	#ifdef OS_IS_IOS
		// See
		//	https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code
		//	and http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
		struct timespec		ts;
		
		clock_gettime (CLOCK_MONOTONIC_COARSE, &ts);
		return ULONGLONG_from_timespec_rel (&ts);
	#endif
	#ifdef OS_IS_LINUX
		// See
		//	https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code
		//	and http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
		struct timespec		ts;
		
		clock_gettime (CLOCK_MONOTONIC_COARSE, &ts);
		return ULONGLONG_from_timespec_rel (&ts);
	#endif
	#ifdef OS_IS_OSX
		// See
		//	https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code
		//	and http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
		struct timespec		ts;
		
		clock_gettime (CLOCK_MONOTONIC_COARSE, &ts);
		return ULONGLONG_from_timespec_rel (&ts);
	#endif
	#ifdef OS_IS_UNIX
		// See
		//	https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code
		//	and http://man7.org/linux/man-pages/man2/clock_gettime.2.html .
		struct timespec		ts;
		
		clock_gettime (CLOCK_MONOTONIC_COARSE, &ts);
		return ULONGLONG_from_timespec_rel (&ts);
	#endif
	#ifdef OS_IS_WINDOWS
		// Windows has a single API GetSysteTimeAsFileTime () for this.
		//	See https://msdn.microsoft.com/en-us/library/windows/desktop/ms724397(v=vs.85).aspx .
		FILETIME		ft;

		GetSystemTimeAsFileTime (&ft);
		return ULONGLONGfromFILETIME(ft);
	#endif
}

#ifdef PLATFORM_IS_POSIX
	void GetSystemTimeAsFileTime (FILETIME *ft)
	{
		ubf_assert_non_NULL (ft);
	
		ULONGLONG ull = GetSystemTimeAsULONGLONG ();
		FILETIMEfromULONGLONG (*ft, ull);
	}
#endif

void SetFILETIMEtoZero (FILETIME *ft)
{
	ubf_assert_non_NULL (ft);
	
	ft->dwHighDateTime	= 0;
	ft->dwLowDateTime	= 0;
}

void SetFILETIMEtoMaxFILETIME (FILETIME *ft)
{
	ubf_assert_non_NULL (ft);
	
	ft->dwHighDateTime	= UINT32_MAX;
	ft->dwLowDateTime	= UINT32_MAX;
}

void cpyFILETIME (FILETIME *fttarget, FILETIME *ftsource)
{
	ubf_assert_non_NULL (fttarget);
	ubf_assert_non_NULL (ftsource);

	fttarget->dwHighDateTime	= ftsource->dwHighDateTime;
	fttarget->dwLowDateTime		= ftsource->dwLowDateTime;
}

int cmpFILETIME (FILETIME *ft1, FILETIME *ft2)
{
	if (ft1->dwHighDateTime	> ft2->dwHighDateTime)
		return 1;
	if (ft1->dwHighDateTime	< ft2->dwHighDateTime)
		return -1;
	if (ft1->dwLowDateTime	> ft2->dwLowDateTime)
		return 1;
	if (ft1->dwLowDateTime	< ft2->dwLowDateTime)
		return -1;
	return 0;
}

bool isFileTimeNotZero (FILETIME *ft)
{
	ubf_assert_non_NULL (ft);
	
	return ft->dwLowDateTime || ft->dwHighDateTime;
}

bool isFileTimeZero (FILETIME *ft)
{
	ubf_assert_non_NULL (ft);
	
	return (!ft->dwLowDateTime) && (!ft->dwHighDateTime);
}

// Renamed. 2019-11-30, Thomas.
//void UnixTimeToFileTime (time_t t, LPFILETIME pft)
void FILETIMEfromUnixTimeT (FILETIME *pft, time_t t)
{	// https://support.microsoft.com/en-gb/kb/167296

	LONGLONG ll;												// Note that LONGLONG is
																//	a 64-bit value.

	//ubf_assert_msg (8 == sizeof (t), "FILETIMEfromUnixTimeT () - size of time_t is not 8 octets (64 bit");
	/*
	if (8 != sizeof (t))
	{	// This applies to Android.
		ubf_debug_puts ("FILETIMEfromUnixTimeT () - size of time_t is not 8 octets (64 bit)");
	}
	*/
	// See
	//	https://docs.microsoft.com/en-us/windows/win32/sysinfo/converting-a-time-t-value-to-a-file-time
	switch (sizeof (time_t))
	{
		case 4:	// time_t is 32 bit.
				//ubf_assert_msg (FALSE, "FILETIMEfromUnixTimeT () - size of time_t is 4 octets (32 bit)");
				//ubf_debug_puts ("FILETIMEfromUnixTimeT () - size of time_t is 4 octets (32 bit)");
				#ifdef Int32x32To64
					ll = Int32x32To64 (t, 10000000) + 116444736000000000;
				#else
					ll = (t * 10000000) + 116444736000000000;
				#endif
				pft->dwLowDateTime = (uint32_t) ll;
				pft->dwHighDateTime = (uint32_t) (ll >> 32);
				break;
		case 8: // time_t is 64 bit.
				ll = (t * 10000000) + 116444736000000000;
				pft->dwLowDateTime = (uint32_t) ll;
				pft->dwHighDateTime = (uint32_t) (ll >> 32);
				break;
		default:
				ubf_assert_msg (false, "FILETIMEfromUnixTimeT () - incompatible/unexptected size of time_t");
				break;
	}
}

void UnixTimeToSystemTime (time_t t, LPSYSTEMTIME pst)
{	// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx and
	//	http://www.cplusplus.com/reference/ctime/tm/ for a comparison of the two structures.

	#ifdef UBF_WINDOWS
		FILETIME ft;

		FILETIMEfromUnixTime (&ft, t);
		FileTimeToSystemTime (&ft, pst);
	#else
		// Everything else should be POSIX compatible.
		struct tm	tM;

		gmtime_r (&t, &tM);										// Won't adjust for local time.
		pst->wMilliseconds	= 0;								// Copy the members.
		pst->wSecond		= (uint16_t) tM.tm_sec;
		pst->wMinute		= (uint16_t) tM.tm_min;
		pst->wHour			= (uint16_t) tM.tm_hour;
		pst->wDay			= (uint16_t) tM.tm_mday;
		pst->wMonth			= (uint16_t) tM.tm_mon		+ 1;
		pst->wYear			= (uint16_t) tM.tm_year;
		pst->wDayOfWeek		= (uint16_t) tM.tm_wday;
	#endif
}

LONGLONG FileTime_to_POSIX (FILETIME ft)
{
	LARGE_INTEGER	date;
	LARGE_INTEGER	adjust;
	
	#ifdef UBF_WINDOWS
		date.HighPart	= (LONG) ft.dwHighDateTime;
		date.LowPart	= ft.dwLowDateTime;
	#else
		date.u.HighPart	= ft.dwHighDateTime;
		date.u.LowPart	= ft.dwLowDateTime;
	#endif
	// 100-nanoseconds = milliseconds * 10000
	adjust.QuadPart = 11644473600000 * 10000;
	// removes the diff between 1970 and 1601
	date.QuadPart -= adjust.QuadPart;
	// converts back from 100-nanoseconds to seconds
	return date.QuadPart / 10000000;
}

void GetISO8601Date (char *chISO8601Date)
{
	struct tm	tmRes;
	time_t		t;
	size_t		st;

	#ifdef _DEBUG
		int		i;

		// Write to the entire buffer to see if it fails with an access violation.
		for (i = 0; i < SIZ_ISO8601DATE; i ++)
		{
			chISO8601Date [i] = '\xFF';
		}
		chISO8601Date [SIZ_ISO8601DATE - 1] = '\xFF';
	#endif

	time (&t);													// Retrieves the times in UTC on Windows.
	localtime_r (&t, &tmRes);									// Adjust for local time.
	//gmtime_r (&t, &tmRes);									// Won't adjust for local time.
	st = strftime (chISO8601Date, SIZ_ISO8601DATE,
				"%Y-%m-%d", &tmRes);
	ubf_assert (st > 0 && st < SIZ_ISO8601DATE);
	UNUSED_PARAMETER (st);
}

void GetISO8601Week_s (char *chISO8601Week)
{
	struct tm		tmRes;
	time_t			t;
	unsigned int	week;
	uint32_t		newYear;

	time (&t);													// Retrieves the times in UTC on Windows.
	localtime_r (&t, &tmRes);									// Adjust for local time.
	week = GetISO8601WeekNumberFromDate (tmRes.tm_year + 1900, tmRes.tm_mon + 1, tmRes.tm_mday, &newYear);
	snprintf (chISO8601Week, SIZ_ISO8601YEARANDWEEK, "%4.4u-W%2.2u", (unsigned int) newYear, week);
}

void GetISO8601Week_c (char *chISO8601Week)
{
	struct tm		tmRes;
	time_t			t;
	unsigned int	week;
	uint32_t		newYear;

	time (&t);													// Retrieves the times in UTC on Windows.
	localtime_r (&t, &tmRes);									// Adjust for local time.
	week = GetISO8601WeekNumberFromDate (tmRes.tm_year + 1900, tmRes.tm_mon + 1, tmRes.tm_mday, &newYear);
	/*
	snprintf (chISO8601Week, SIZ_ISO8601YEARANDWEEK, "%4.4u-W%2.2u", (unsigned int) newYear, week);
	*/
	ubf_str0_from_uint16 (chISO8601Week, 4, (uint16_t) newYear);
	chISO8601Week += 4;
	*chISO8601Week ++ = '-';
	*chISO8601Week ++ = 'W';
	ubf_str0_from_59max (chISO8601Week, (uint8_t) week);
	chISO8601Week += 2;
	*chISO8601Week= '\0';
}

void GetISO8601DateTimeStamp (char *chISO8601DateTimeStamp)
{	// Retrieves the current date/time as a text in the
	// International Standard ISO 8601 format:
	// YYYY-MM-DD HH:MI:SS +/-TDIF
	//
	// Example: YYYY-MM-DD HH:MI:SS+01:00
	//          YYYY-MM-DD HH:MI:SS-04:00
	//
	// This code should work on Unix/Linux platforms and on Windows. See the definition of the
	//	gmtime_r () and localtime_r () macros in the header file. Windows only got the gmtime_s ()
	//	and localtime_s () APIs with swapped parameters.

	struct tm	tmRes;
	time_t		t;
	size_t		st;

	#ifdef _DEBUG
		int		i;

		// Write to the entire buffer to see if it fails with an access violation.
		for (i = 0; i < SIZ_ISO8601DATETIMESTAMP; i ++)
		{
			chISO8601DateTimeStamp [i] = '\xFF';
		}
		chISO8601DateTimeStamp [SIZ_ISO8601DATETIMESTAMP - 1] = '\xFF';
	#endif

	time (&t);													// Retrieves the times in UTC on Windows.
	localtime_r (&t, &tmRes);									// Adjust for local time.
	//gmtime_r (&t, &tmRes);									// Won't adjust for local time.
	st = strftime (chISO8601DateTimeStamp, SIZ_ISO8601DATETIMESTAMP,
				"%Y-%m-%d %H:%M:%S%z", &tmRes);
	/*	The correct ISO 8601 implementation requires a "T" between date and time. We're not using this
		 notation.
			st = strftime (chISO8601DateTimeStamp, SIZ_ISO8601DATETIMESTAMP,
						"%Y-%m-%dT%H:%M:%S%z", &tmRes);
	*/
	ubf_assert (st > 0 && st < SIZ_ISO8601DATETIMESTAMP);
	UNUSED_PARAMETER (st);
	// We got the offset as "-0000" or "+1000", but we want the offset with a colon between hours and minutes.
	chISO8601DateTimeStamp [24] = chISO8601DateTimeStamp [23];
	chISO8601DateTimeStamp [23] = chISO8601DateTimeStamp [22];
	chISO8601DateTimeStamp [22] = ':';
	chISO8601DateTimeStamp [25] = '\0';
	// PicoC (and probably other implementations too) produces a "-" instead of "+"
	//	when the offset is 0.
	if	(
			'0' == chISO8601DateTimeStamp [20]	&&
			'0' == chISO8601DateTimeStamp [21]	&&
			'0' == chISO8601DateTimeStamp [23]	&&
			'0' == chISO8601DateTimeStamp [24]	&&
			'-' == chISO8601DateTimeStamp [19]
		)
		chISO8601DateTimeStamp [19] = '+';
}

void GetISO8601DateTimeStampT (char *chISO8601DateTimeStamp)
{
	GetISO8601DateTimeStamp (chISO8601DateTimeStamp);
	chISO8601DateTimeStamp [10] = 'T';
}

#ifdef _MSC_VER
#pragma warning (disable: 4996)									// MSVC says some functions are unsafe.
#endif

void GetISO8601DateTimeStampMS (char *chISO8601DateTimeStampMS)
{
	time_t			t_time;
	struct	tm		*stime;
	int				i_adjustment_hours;
	int				i_adjustment_mins;
	unsigned short	ms;
	
	#ifdef PLATFORM_IS_WINDOWS
		struct	timeb	timebuffer;
		_ftime (&timebuffer);
		// Retrieve offset to UTC.
		//  The value is given in minutes by _ftime.
		// Some tests:
		// timebuffer.timezone = 200;
		// timebuffer.timezone = -200;
		// timebuffer.timezone = 60;
		// timebuffer.timezone = -60;
		i_adjustment_hours = timebuffer.timezone / 60;
		i_adjustment_mins  = timebuffer.timezone % 60;
		ms = timebuffer.millitm;
	#else
		struct timeval	tv;
		struct timezone	tz;
		gettimeofday (&tv, &tz);
		i_adjustment_hours	= tz.tz_minuteswest / 60;
		i_adjustment_mins	= tz.tz_minuteswest % 60;
		ms = tv.tv_usec + 500 / 1000;
	#endif

	// Unfortunately it is counted by moving westward, which
	//  is still not the proper notation. Turn it.
	if (i_adjustment_hours != 0)
		i_adjustment_hours-= (2 * i_adjustment_hours);

	if (i_adjustment_mins < 0)
		i_adjustment_mins-=  (2 * i_adjustment_mins);
	//printf ("Time offset: %2.2d:%2.2d\n", i_adjustment_hours, i_adjustment_mins);

	time (&t_time);
	stime = localtime (&t_time);
	
	// Adjust daylight saving time (DST) value.
	//  DST automatically implies +1 hour (+01:00).
	if (stime->tm_isdst > 0) i_adjustment_hours++;
    
	// Store the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	sprintf (chISO8601DateTimeStampMS, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%3.3d+%2.2d:%2.2d",
    stime->tm_year + 1900,
	stime->tm_mon + 1,
    stime->tm_mday,
    stime->tm_hour,
    stime->tm_min,
	stime->tm_sec,
	ms,
	i_adjustment_hours,
	i_adjustment_mins);
}

#ifdef _MSC_VER
#pragma warning (default: 4996)									// MSVC says some functions are unsafe.
#endif

void GetISO8601DateTimeStampMST (char *chISO8601DateTimeStampMS)
{
	GetISO8601DateTimeStampMS (chISO8601DateTimeStampMS);
	chISO8601DateTimeStampMS [10] = 'T';
}

void ubf_get_system_time (FILETIME *ft)
{
	#ifdef OS_IS_ANDROID
		// Assuming that Android supports POSIX.
		time_t		t;

		time (&t);
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef OS_IS_IOS
		// Assuming that iOS supports POSIX.
		time_t		t;

		time (&t);
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef OS_IS_LINUX
		time_t		t;

		time (&t);
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef OS_IS_OSX
		// Assuming that OSX supports POSIX.
		time_t		t;

		time (&t);
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef OS_IS_UNIX
		time_t		t;

		time (&t);
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef OS_IS_WINDOWS
		/*	Windows has a single API GetSysteTimeAsFileTime () for this.
			See https://msdn.microsoft.com/en-us/library/windows/desktop/ms724397(v=vs.85).aspx .
		*/
		GetSystemTimeAsFileTime (ft);
	#endif
}

/* Maybe we don't need this function at all. 2018-12-30, Thomas.
void ubf_get_local_time (FILETIME *ft)
{	// This is still the system time on Linux/Unix platforms.
	#ifdef UBF_ANDROID
		// Assuming that Android supports POSIX.
		struct tm	tmRes;
		time_t		t;

		time (&t);
		localtime_r (&t, &tmRes);								// Adjust for local time.
		// Very old Android NDKs don't know this function.
		//t = timegm (&tmRes);									// Convert back by assuming we got UTC.
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef UBF_IOS
		// Assuming that iOS supports POSIX.
		struct tm	tmRes;
		time_t		t;

		time (&t);
		localtime_r (&t, &tmRes);								// Adjust for local time.
		t = timegm (&tmRes);									// Convert back by assuming we got UTC.
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef UBF_LINUX
        // Assuming that Linux can handle POSIX.
        struct tm	tmRes;
        time_t		t;

        time (&t);
        localtime_r (&t, &tmRes);								// Adjust for local time.
        t = timegm (&tmRes);									// Convert back by assuming we got UTC.
		FILETIMEfromUnixTimeT (ft, t);
    #endif
	#ifdef UBF_OSX
		// Assuming that OSX supports POSIX.
		struct tm	tmRes;
		time_t		t;

		time (&t);
		localtime_r (&t, &tmRes);								// Adjust for local time.
		t = timegm (&tmRes);									// Convert back by assuming we got UTC.
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef UBF_UNIX
		struct tm	tmRes;
		time_t		t;

		time (&t);
		localtime_r (&t, &tmRes);								// Adjust for local time.
		t = timegm (&tmRes);									// Convert back by assuming we got UTC.
		FILETIMEfromUnixTimeT (ft, t);
	#endif
	#ifdef UBF_WINDOWS
		SYSTEMTIME	st;
		
		GetLocalTime (&st);
		SystemTimeToFileTime (&st, ft);
	#endif
}
*/

void ubf_get_system_time_ULONGLONG (ULONGLONG *pulltime)
{
	ubf_assert (NULL != pulltime);
	*pulltime = GetSystemTimeAsULONGLONG ();
}

void ubf_get_system_time_ULONGLONG_rel (ULONGLONG *pulltime)
{
	ubf_assert (NULL != pulltime);
	*pulltime = GetSystemTimeAsULONGLONGrel ();
}

// This function is only required on Windows. See https://linux.die.net/man/3/clock_gettime
//	for more information. The function has been taken from
//	https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows .
#ifdef OS_IS_WINDOWS
	int clock_gettime (int iclk_id, struct timespec *spec)
	{
		int64_t		wintime;
	
		#ifdef _DEBUG
			switch (iclk_id)
			{	// These are the clock types we support.
				case CLOCK_REALTIME:
				case CLOCK_MONOTONIC:
					break;
				default:
					ubf_assert (FALSE);
			}
		#else
			UNREFERENCED_PARAMETER (iclk_id);
		#endif
		GetSystemTimeAsFileTime ((FILETIME *) &wintime);
		wintime			-= 116444736000000000;					// 1601-01-01 to 1970-01-01.
		spec->tv_sec	= wintime / 10000000;					// Seconds.
		spec->tv_nsec	= wintime % 10000000 * 100;				// Nano seconds.
		return 0;												// Always return success.
	}
#endif

bool IsLeapYear (uint32_t Y)
{	// Implements (2) and (3). See below.
	return (((Y % 4 == 0) && (Y % 100 != 0)) || (Y % 400 == 0)) ? true : false;
}

// The lookup table for GetISO8601DayOfYear ().
static uint32_t m_Month [12] =
{
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

uint32_t GetISO8601DayOfYear (uint32_t Y, uint32_t M, uint32_t D)
{	// Implements (4). See below.
	uint32_t DayOfYearNumber;
	
	ubf_assert (0 < M);
	ubf_assert (13 > M);
	DayOfYearNumber = D + m_Month [M - 1];
	/*
	if (IsLeapYear (Y) && M > 2)
		DayOfYearNumber += 1;
	*/
	DayOfYearNumber += IsLeapYear (Y) && M > 2 ? 1 : 0;
	return DayOfYearNumber;
}

uint32_t GetISO8601Jan1WeekDay (uint32_t Y)
{	// Implements (5). See below.
	uint32_t YY, C, G;
	
	YY = (Y - 1) % 100;
	C = (Y - 1) - YY;
	G = YY + (YY / 4);
	return (1 + (((((C / 100) % 4) * 5) + G) % 7));
}

uint32_t GetISO8601WeekDay (uint32_t Y, uint32_t M, uint32_t D)
{	// Implements (6). See below. This function is not used.
	uint32_t	H;
	
	H = GetISO8601DayOfYear (Y, M, D) + (GetISO8601Jan1WeekDay (Y) - 1);
	return (1 + ((H -1) % 7));
}

uint32_t GetISO8601WeekNumberFromDate (uint32_t Y, uint32_t M, uint32_t D, uint32_t *aY)
{
/*
	Implementation of http://personal.ecu.edu/mccartyr/ISOwdALG.txt:

    Algorithm for Converting Gregorian Dates to ISO 8601 Week Date
                            (Y2K  Compliant)
                           Rick McCarty, 1999

                     From: Gregorian Year-Month-Day
                 To: ISO YearNumber-WeekNumber-Weekday 

ISO 8601 specifies that Week 01 of the year is the week containing
the first Thursday; Monday is Weekday 1, Sunday is Weekday 7;
WeekNumber requires two digits (W01, W02, etc.; "W" is optional)

Algorithm Conventions:
   "/" = integer division, discard remainder  (5/2 = 2)
   "%" = modulus, keep only remainder    (5%2 = 1)
   "&" = concatenation   ("W" & 12 = "W12")
   "!=" = unequal   (7 != 8  is true)
   "+=" = add right value to left variable,
             if F = 3, then (F += 4) yields F = 7
   "-=" = subtract right value from left variable

1. Convert input to Y M D
   Y = Year     (full specification; input 98 = year 0098)
		(Y must be larger than -1)
   M = Month    (1 through 12)
   D = Day      (1 through 31)
2. Find if Y is LeapYear
   if (Y % 4 = 0  and  Y % 100 != 0) or Y % 400 = 0
      then
         Y is LeapYear
      else
         Y is not LeapYear
3. Find if Y-1 is LeapYear
4. Find the DayOfYearNumber for Y M D
   Mnth[1] = 0    Mnth[4] = 90    Mnth[7] = 181   Mnth[10] = 273
   Mnth[2] = 31   Mnth[5] = 120   Mnth[8] = 212   Mnth[11] = 304
   Mnth[3] = 59   Mnth[6] = 151   Mnth[9] = 243   Mnth[12] = 334
   DayOfYearNumber = D + Mnth[M]
   if Y is LeapYear and M > 2
      then
         DayOfYearNumber += 1
5. Find the Jan1Weekday for Y (Monday=1, Sunday=7)
   YY = (Y-1) % 100
   C = (Y-1) - YY
   G = YY + YY/4
   Jan1Weekday = 1 + (((((C / 100) % 4) x 5) + G) % 7)
6. Find the Weekday for Y M D
   H = DayOfYearNumber + (Jan1Weekday - 1)
   Weekday = 1 + ((H -1) % 7)
7. Find if Y M D falls in YearNumber Y-1, WeekNumber 52 or 53
   if DayOfYearNumber <= (8-Jan1Weekday) and Jan1Weekday > 4
      then
         YearNumber = Y - 1 
         if Jan1Weekday = 5 or (Jan1Weekday = 6 and Y-1 is LeapYear)
            then
               WeekNumber = 53
            else 
               WeekNumber = 52
      else 
         YearNumber = Y
8. Find if Y M D falls in YearNumber Y+1, WeekNumber 1
   if YearNumber = Y
      then
         if Y is LeapYear
            then 
               I = 366
               else
               I = 365
         if (I - DayOfYearNumber) < (4 - Weekday)
            then
               YearNumber = Y + 1
               WeekNumber = 1
9. Find if Y M D falls in YearNumber Y, WeekNumber 1 through 53
   if YearNumber = Y
      then
         J = DayOfYearNumber + (7 - Weekday) + (Jan1Weekday -1)
         WeekNumber = J / 7
         if Jan1Weekday > 4
               WeekNumber -= 1
10. Output ISO Week Date:
   if WeekNumber < 10
      then
         WeekNumber = "0" & WeekNumber  (WeekNumber requires 2 digits)
   Print: YearNumber & "-" & WeekNumber & "-" & Weekday    (Optional: "-W" & WeekNumber)
*/

	bool		bLeapYear;										// Is Y a leapyear?
	bool		bPLeapYear;										// Is Y - 1 a leapyear?
	uint32_t	DayOfYearNumber;								// The number of the day of the year.
	uint32_t	Jan1Weekday;									// Which day is Jan 1?
	uint32_t	Weekday;										// The day of the week (Y, M, D).
	uint32_t	WeekNumber;										// The calendar week number.
	uint32_t	YearNumber;										// Y for calculations.
	long	I;													// How many days a year has.

	// (1) comes in as parameters Y, M, and D.

	// (2):
	bLeapYear = IsLeapYear (Y);

	// (3).
	bPLeapYear = IsLeapYear (Y - 1);
	
	// (4).
	DayOfYearNumber = GetISO8601DayOfYear (Y, M, D);

	// (5).
	Jan1Weekday = GetISO8601Jan1WeekDay (Y);

	// (6).
	Weekday = 1 + ((DayOfYearNumber + (Jan1Weekday - 1) - 1) % 7);

	// Disables the compiler warning that the variable is potentially uninitialised.
	WeekNumber = 0;

	// (7).
	if (DayOfYearNumber <= (8 - Jan1Weekday) && Jan1Weekday > 4)
	{
		YearNumber = Y - 1;
		if (Jan1Weekday == 5 || (Jan1Weekday == 6 && bPLeapYear))
			WeekNumber = 53;
		else 
			WeekNumber = 52;
	} else 
		YearNumber = Y;

	// (8).
	if (YearNumber == Y)
	{
		if (bLeapYear)
			I = 366;
		else
			I = 365;
		if (((int32_t) I - (int32_t) DayOfYearNumber) < ((int32_t) 4 - (int32_t) Weekday))
		{
			YearNumber = Y + 1;
			WeekNumber = 1;
		}
	}
	if (aY)						// Return the corrected (adjusted) year number so that
		*aY = YearNumber;		//  the caller can use it.
	// Note that this year number does not need to be identical to the default year
	//  number. It can be Y - 1.

	// (9).
	if (YearNumber == Y)
	{
		WeekNumber = (DayOfYearNumber + (7 - Weekday) + (Jan1Weekday - 1)) / 7;
		if (Jan1Weekday > 4)
			WeekNumber -= 1;
	}

	// (10).
	//  Not required in C.

	return WeekNumber;
}

bool HasMonth28Days (uint8_t m, uint32_t y)
{
	ubf_assert (m > 0);
	ubf_assert (m < 12 + 1);
	return 2 == m && !IsLeapYear (y) ? true : false;
}

bool HasMonth29Days (uint8_t m, uint32_t y)
{
	ubf_assert (m > 0);
	ubf_assert (m < 12 + 1);
	return 2 == m && IsLeapYear (y) ? true : false;
}

// The lookup table for HasMonth30Days ().
bool m_30days [] = { 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };

bool HasMonth30Days (uint8_t m)
{
	ubf_assert (m > 0);
	ubf_assert (m < 12 + 1);
	return m_30days [m - 1];
}

// The lookup table for HasMonth31Days ().
bool m_31days [] = { 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 };

bool HasMonth31Days (uint8_t m)
{
	ubf_assert (m > 0);
	ubf_assert (m < 12 + 1);
	return m_30days [m - 1];
}

uint8_t DaysInMonth (uint8_t m, uint32_t y)
{
	return HasMonth28Days (m, y) ? 28 : (HasMonth30Days (m) ? 30 : 31);
}

int _DayOfWeek (int y, int m, int d)
{	// See https://stackoverflow.com/questions/6054016/c-program-to-find-day-of-week-given-date
	//	and
	//	https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Implementation-dependent_methods
	//	(Tomohiko Sakamoto).
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	
	ubf_assert (   0 < m);
	ubf_assert (  13 > m);
	ubf_assert (1752 > y);										// In the U.K.
	ubf_assert (   0 < d);
	ubf_assert (  32 > d);
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int DayOfWeek (int y, int m, int d)
{
	int dow = _DayOfWeek (y, m, d);								// 0 == Sunday.
	return dow ? ++ dow : 6;									// 0 == Monday, 6 == Sunday.
}

void FILETIME_to_ISO8601 (char *chISO, FILETIME *ft)
{
	UNREFERENCED_PARAMETER (chISO);
	UNREFERENCED_PARAMETER (ft);
	ubf_assert (false);
}

bool IsBuildYearOrNewer_UBF_TIMESTAMP (UBF_TIMESTAMP *pts)
{
	ubf_assert (NULL != pts);

	UBF_TIMESTAMP	u	= *pts;
	bool			bRet;

	bRet =	UBF_TIMESTAMP_YEAR			(u) >= BuildYear_uint64 ();	// Year.
	bRet &=	UBF_TIMESTAMP_MONTH			(u) > 0;					// Month lowest.
	bRet &=	UBF_TIMESTAMP_MONTH			(u) < 13;					// Month highest.
	bRet &=	UBF_TIMESTAMP_DAY			(u) > 0;					// Day lowest.
	bRet &=	UBF_TIMESTAMP_DAY			(u) < 32;					// Day highest.
	bRet &=	UBF_TIMESTAMP_HOUR			(u) < 24;					// Hour highest.
	bRet &= UBF_TIMESTAMP_MINUTE		(u) < 60;					// Minute highest.
	bRet &= UBF_TIMESTAMP_SECOND		(u) < 60;					// Second highest.
	bRet &=	UBF_TIMESTAMP_MILLISECOND	(u) < 1000;					// Millisecond highest.
	bRet &=	UBF_TIMESTAMP_MICROSECOND	(u) < 1000;					// Microsecond highest.
	return bRet;
}

bool ValuesWithinLimits_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *ts)
{
	ubf_assert_non_NULL (ts);

	return	(
					ts->uYear	> 1999
				&&	ts->uYear	< 3023
				&&	ts->uMonth	> 0
				&&	ts->uMonth	< 13
				&&	ts->uDay	> 0
				&&	ts->uDay	< 32
				&&	ts->uMinute	< 60
				&&	ts->uHour	< 24
				&&	ts->uSecond	< 60
			);
}

bool UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *ts, UBF_TIMESTAMP t)
{
	ubf_assert_non_NULL (ts);

	ts->uOffsetHours	= UBF_TIMESTAMP_OFFSETHOURS (t);
	/*
	ts->uOffsetMinutes	= 0;
	if (t & 0x04)											// Bit 2 (0100).
		ts->uOffsetMinutes += 30;
	if (t & 0x02)											// Bit 1 (0010).
		ts->uOffsetMinutes += 15;
	*/
	ts->uOffsetMinutes	= UBF_TIMESTAMP_OFFSETMINUTES (t);
	ts->bOffsetNegative = UBF_TIMESTAMP_OFFSETNEGATIVE (t) ? true : false;
	ts->uYear			= UBF_TIMESTAMP_YEAR (t);
	ts->uMonth			= UBF_TIMESTAMP_MONTH (t);
	ts->uDay			= UBF_TIMESTAMP_DAY (t);
	ts->uHour			= UBF_TIMESTAMP_HOUR (t);
	ts->uMinute			= UBF_TIMESTAMP_MINUTE (t);
	ts->uSecond			= UBF_TIMESTAMP_SECOND (t);
	ts->uMillisecond	= UBF_TIMESTAMP_MILLISECOND (t);
	ts->uMicrosecond	= UBF_TIMESTAMP_MICROSECOND (t);
	return ValuesWithinLimits_SUBF_TIMESTRUCT (ts);
}

void SUBF_TIMESTRUCT_to_ISO8601 (char *chISO, SUBF_TIMESTRUCT *pts)
{
	ubf_assert (NULL != chISO);
	ubf_assert (NULL != pts);
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	// YYYY-MM-DD HH:MI:SS.000+01:00
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%3.3d+%2.2d:%2.2d",
		pts->uYear,
		pts->uMonth,
		pts->uDay,
		pts->uHour,
		pts->uMinute,
		pts->uSecond,
		pts->uMillisecond,
		pts->uOffsetHours,
		pts->uOffsetMinutes
				);
	if (pts->bOffsetNegative)									// Offset is negative.
		chISO [23] = '-';
}

/*
void UBF_TIMESTAMP_to_ISO8601 (char *chISO, UBF_TIMESTAMP ts)
{
	SUBF_TIMESTRUCT		t;

	ubf_assert (NULL != chISO);
	UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (&t, ts);					// Convert the structure.
	SUBF_TIMESTRUCT_to_ISO8601 (chISO, &t);
}
*/

void ISO8601_from_UBF_TIMESTAMP_s (char *chISO, UBF_TIMESTAMP ts)
{
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	// YYYY-MM-DD HH:MI:SS.000+01:00
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u %2.2u:%2.2u:%2.2u.%3.3u+%2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts),
		(unsigned int) UBF_TIMESTAMP_SECOND (ts),
		(unsigned int) UBF_TIMESTAMP_MILLISECOND (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETHOURS (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETMINUTES (ts)
				);
	if (UBF_TIMESTAMP_OFFSETNEGATIVE (ts))						// Offset is negative.
		chISO [23] = '-';
}

void ISO8601_from_UBF_TIMESTAMP_c (char *chISO, UBF_TIMESTAMP ts)
{
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	// YYYY-MM-DD HH:MI:SS.000+01:00
	/*
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u %2.2u:%2.2u:%2.2u.%3.3u+%2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts),
		(unsigned int) UBF_TIMESTAMP_SECOND (ts),
		(unsigned int) UBF_TIMESTAMP_MILLISECOND (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETHOURS (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETMINUTES (ts)
				);
	*/

	ubf_str0_from_uint16 (chISO, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISO += 4;
	*chISO ++ = '-';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISO += 2;
	*chISO ++ = '-';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISO += 2;
	*chISO ++ = ' ';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_HOUR (ts));
	chISO += 2;
	*chISO ++ = ':';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_MINUTE (ts));
	chISO += 2;
	*chISO ++ = ':';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_SECOND (ts));
	chISO += 2;
	*chISO ++ = '.';
	ubf_str0_from_uint16 (chISO, 3, (unsigned int) UBF_TIMESTAMP_MILLISECOND (ts));
	chISO += 3;
	*chISO ++ = '+';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_OFFSETHOURS (ts));
	chISO += 2;
	*chISO ++ = ':';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_OFFSETMINUTES (ts));
	chISO += 2;
	*chISO = '\0';

	if (UBF_TIMESTAMP_OFFSETNEGATIVE (ts))						// Offset is negative.
		chISO [23] = '-';
}

void ISO8601T_from_UBF_TIMESTAMP_s (char *chISO, UBF_TIMESTAMP ts)
{
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	// YYYY-MM-DD HH:MI:SS.000+01:00
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2uT%2.2u:%2.2u:%2.2u.%3.3u+%2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts),
		(unsigned int) UBF_TIMESTAMP_SECOND (ts),
		(unsigned int) UBF_TIMESTAMP_MILLISECOND (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETHOURS (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETMINUTES (ts)
				);
	if (UBF_TIMESTAMP_OFFSETNEGATIVE (ts))						// Offset is negative.
		chISO [23] = '-';
}

void ISO8601T_from_UBF_TIMESTAMP_c (char *chISO, UBF_TIMESTAMP ts)
{
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	// YYYY-MM-DD HH:MI:SS.000+01:00
	/*
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2uT%2.2u:%2.2u:%2.2u.%3.3u+%2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts),
		(unsigned int) UBF_TIMESTAMP_SECOND (ts),
		(unsigned int) UBF_TIMESTAMP_MILLISECOND (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETHOURS (ts),
		(unsigned int) UBF_TIMESTAMP_OFFSETMINUTES (ts)
				);
	*/

	ubf_str0_from_uint16 (chISO, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISO += 4;
	*chISO ++ = '-';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISO += 2;
	*chISO ++ = '-';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISO += 2;
	*chISO ++ = 'T';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_HOUR (ts));
	chISO += 2;
	*chISO ++ = ':';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_MINUTE (ts));
	chISO += 2;
	*chISO ++ = ':';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_SECOND (ts));
	chISO += 2;
	*chISO ++ = '.';
	ubf_str0_from_uint16 (chISO, 3, (unsigned int) UBF_TIMESTAMP_MILLISECOND (ts));
	chISO += 3;
	*chISO ++ = '+';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_OFFSETHOURS (ts));
	chISO += 2;
	*chISO ++ = ':';
	ubf_str0_from_59max (chISO, (unsigned int) UBF_TIMESTAMP_OFFSETMINUTES (ts));
	chISO += 2;
	*chISO= '\0';

	if (UBF_TIMESTAMP_OFFSETNEGATIVE (ts))						// Offset is negative.
		chISO [23] = '-';
}

void ISO8601Date_from_UBF_TIMESTAMP (char *chISODateOnly, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd
	// YYYY-MM-DD
	snprintf	(
		chISODateOnly, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts)
				);
}

void ISO8601Date_from_UBF_TIMESTAMP_c (char *chISODateOnly, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd
	// YYYY-MM-DD
	/*
	snprintf	(
		chISODateOnly, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts)
				);
	*/
	ubf_str0_from_uint16 (chISODateOnly, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISODateOnly += 4;
	*chISODateOnly ++ = '-';
	ubf_str0_from_59max (chISODateOnly, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISODateOnly += 2;
	*chISODateOnly ++ = '-';
	ubf_str0_from_59max (chISODateOnly, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISODateOnly += 2;
	*chISODateOnly= '\0';
}

void ISO8601YearAndWeek_from_UBF_TIMESTAMP_s (char *chISO8601YearAndWeek, UBF_TIMESTAMP ts)
{
	unsigned int	week;
	uint32_t		newYear;

	week = GetISO8601WeekNumberFromDate	(
		UBF_TIMESTAMP_YEAR (ts), UBF_TIMESTAMP_MONTH (ts), UBF_TIMESTAMP_DAY (ts), &newYear
										);
	snprintf (chISO8601YearAndWeek, SIZ_ISO8601YEARANDWEEK, "%4.4u-W%2.2u", (unsigned int) newYear, week);
}

void ISO8601YearAndWeek_from_UBF_TIMESTAMP_c (char *chISO8601YearAndWeek, UBF_TIMESTAMP ts)
{
	unsigned int	week;
	uint32_t		newYear;

	week = GetISO8601WeekNumberFromDate	(
		UBF_TIMESTAMP_YEAR (ts), UBF_TIMESTAMP_MONTH (ts), UBF_TIMESTAMP_DAY (ts), &newYear
										);
	ubf_str0_from_uint16 (chISO8601YearAndWeek, 4, (uint16_t) newYear);
	chISO8601YearAndWeek += 4;
	*chISO8601YearAndWeek ++ = '-';
	*chISO8601YearAndWeek ++ = 'W';
	ubf_str0_from_59max (chISO8601YearAndWeek, (uint8_t) week);
	chISO8601YearAndWeek += 2;
	*chISO8601YearAndWeek= '\0';
}

void ISO8601DateAndHour_from_UBF_TIMESTAMP_s (char *chISODateAndHour, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH
	snprintf	(
		chISODateAndHour, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u %2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts)
				);
}

void ISO8601DateAndHour_from_UBF_TIMESTAMP_c (char *chISODateAndHour, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH
	/*
	snprintf	(
		chISODateAndHour, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u %2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts)
				);
	*/

	ubf_str0_from_uint16 (chISODateAndHour, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISODateAndHour += 4;
	*chISODateAndHour ++ = '-';
	ubf_str0_from_59max (chISODateAndHour, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISODateAndHour += 2;
	*chISODateAndHour ++ = '-';
	ubf_str0_from_59max (chISODateAndHour, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISODateAndHour += 2;
	*chISODateAndHour ++ = ' ';
	ubf_str0_from_59max (chISODateAndHour, (unsigned int) UBF_TIMESTAMP_HOUR (ts));
	chISODateAndHour += 2;
	*chISODateAndHour= '\0';
}

void ISO8601TDateAndHour_from_UBF_TIMESTAMP_s (char *chISODateAndHour, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH
	snprintf	(
		chISODateAndHour, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2uT%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts)
				);
}

void ISO8601TDateAndHour_from_UBF_TIMESTAMP_c (char *chISODateAndHour, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH

	ubf_str0_from_uint16 (chISODateAndHour, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISODateAndHour += 4;
	*chISODateAndHour ++ = '-';
	ubf_str0_from_59max (chISODateAndHour, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISODateAndHour += 2;
	*chISODateAndHour ++ = '-';
	ubf_str0_from_59max (chISODateAndHour, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISODateAndHour += 2;
	*chISODateAndHour ++ = 'T';
	ubf_str0_from_59max (chISODateAndHour, (unsigned int) UBF_TIMESTAMP_HOUR (ts));
	chISODateAndHour += 2;
	*chISODateAndHour= '\0';
}

void ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_s (char *chISODateHourAndMinute, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH
	snprintf	(
		chISODateHourAndMinute, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u %2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts)
				);
}

void ISO8601DateHourAndMinute_from_UBF_TIMESTAMP_c (char *chISODateHourAndMinute, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH
	/*
	snprintf	(
		chISODateHourAndMinute, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2u %2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts)
				);
	*/

	ubf_str0_from_uint16 (chISODateHourAndMinute, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISODateHourAndMinute += 4;
	*chISODateHourAndMinute ++ = '-';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute ++ = '-';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute ++ = ' ';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_HOUR (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute ++ = ':';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_MINUTE (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute= '\0';
}

void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_s (char *chISODateHourAndMinute, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH
	snprintf	(
		chISODateHourAndMinute, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u-%2.2uT%2.2u:%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts),
		(unsigned int) UBF_TIMESTAMP_DAY (ts),
		(unsigned int) UBF_TIMESTAMP_HOUR (ts),
		(unsigned int) UBF_TIMESTAMP_MINUTE (ts)
				);
}

void ISO8601TDateHourAndMinute_from_UBF_TIMESTAMP_c (char *chISODateHourAndMinute, UBF_TIMESTAMP ts)
{
	// yyyy-mm-dd hh
	// YYYY-MM-DD HH

	ubf_str0_from_uint16 (chISODateHourAndMinute, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISODateHourAndMinute += 4;
	*chISODateHourAndMinute ++ = '-';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute ++ = '-';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_DAY (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute ++ = 'T';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_HOUR (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute ++ = ':';
	ubf_str0_from_59max (chISODateHourAndMinute, (unsigned int) UBF_TIMESTAMP_MINUTE (ts));
	chISODateHourAndMinute += 2;
	*chISODateHourAndMinute= '\0';
}

void ISO8601Year_from_UBF_TIMESTAMP (char *chYear, UBF_TIMESTAMP ts)
{
	// YYYY
	snprintf	(
		chYear, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u", (unsigned int) UBF_TIMESTAMP_YEAR (ts)
				);
}

void ISO8601Year_from_UBF_TIMESTAMP_c (char *chYear, UBF_TIMESTAMP ts)
{
	// YYYY
	ubf_str0_from_uint16 (chYear, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
}

void ISO8601YearAndMonth_from_UBF_TIMESTAMP (char *chISOYearAndMonth, UBF_TIMESTAMP ts)
{
	// yyyy-mm
	// YYYY-MM
	snprintf	(
		chISOYearAndMonth, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts)
				);
}

void ISO8601YearAndMonth_from_UBF_TIMESTAMP_c (char *chISOYearAndMonth, UBF_TIMESTAMP ts)
{
	// yyyy-mm
	// YYYY-MM
	/*
	snprintf	(
		chISOYearAndMonth, SIZ_ISO8601DATETIMESTAMPMS,
		"%4.4u-%2.2u",
		(unsigned int) UBF_TIMESTAMP_YEAR (ts),
		(unsigned int) UBF_TIMESTAMP_MONTH (ts)
				);
	*/

	ubf_str0_from_uint16 (chISOYearAndMonth, 4, (unsigned int) UBF_TIMESTAMP_YEAR (ts));
	chISOYearAndMonth += 4;
	*chISOYearAndMonth ++ = '-';
	ubf_str0_from_59max (chISOYearAndMonth, (unsigned int) UBF_TIMESTAMP_MONTH (ts));
	chISOYearAndMonth += 2;
	*chISOYearAndMonth= '\0';
}

void UBF_TIMESTAMP_to_ISO8601_Holocene (char *chISO, UBF_TIMESTAMP ts)
{
	SUBF_TIMESTRUCT		t;

	ubf_assert (NULL != chISO);
	UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (&t, ts);					// Convert the structure.
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	// YYYY-MM-DD HH:MI:SS.000+01:00
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMPMS_HOL,
		"%5.5d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%3.3d+%2.2d:%2.2d",
		t.uYear + 10000,
		t.uMonth,
		t.uDay,
		t.uHour,
		t.uMinute,
		t.uSecond,
		t.uMillisecond,
		t.uOffsetHours,
		t.uOffsetMinutes
				);
	if (t.bOffsetNegative)										// Offset is negative.
		chISO [24] = '-';
}

void SUBF_TIMESTRUCT_to_ISO8601_no_ms (char *chISO, SUBF_TIMESTRUCT *t)
{
	ubf_assert (NULL != chISO);
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss+01:00
	// YYYY-MM-DD HH:MI:SS+01:00
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMP,
		"%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d+%2.2d:%2.2d",
		t->uYear,
		t->uMonth,
		t->uDay,
		t->uHour,
		t->uMinute,
		t->uSecond,
		t->uOffsetHours,
		t->uOffsetMinutes
				);
	if (t->bOffsetNegative)										// Offset is negative.
		chISO [19] = '-';
}

void UBF_TIMESTAMP_to_ISO8601_no_ms (char *chISO, UBF_TIMESTAMP ts)
{
	SUBF_TIMESTRUCT		t;

	ubf_assert (NULL != chISO);
	UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (&t, ts);					// Convert the structure.
	SUBF_TIMESTRUCT_to_ISO8601_no_ms (chISO, &t);
}

void UBF_TIMESTAMP_to_ISO8601_no_ms_Holocene (char *chISO, UBF_TIMESTAMP ts)
{
	SUBF_TIMESTRUCT		t;

	ubf_assert (NULL != chISO);
	UBF_TIMESTAMP_to_SUBF_TIMESTRUCT (&t, ts);					// Convert the structure.
	// Stores the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss+01:00
	// YYYY-MM-DD HH:MI:SS+01:00
	snprintf	(
		chISO, SIZ_ISO8601DATETIMESTAMP_HOL,
		"%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d+%2.2d:%2.2d",
		t.uYear + 10000,
		t.uMonth,
		t.uDay,
		t.uHour,
		t.uMinute,
		t.uSecond,
		t.uOffsetHours,
		t.uOffsetMinutes
				);
	if (t.bOffsetNegative)										// Offset is negative.
		chISO [20] = '-';
}

uint64_t MS_from_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts)
{
	uint64_t	uiRet;

	ubf_assert (NULL != pts);
	uiRet = pts->uMillisecond;
	uiRet += (uint64_t) pts->uSecond	* NUM_MS_IN_SECOND;
	uiRet += (uint64_t) pts->uMinute	* NUM_MS_IN_MINUTE;
	uiRet += (uint64_t) pts->uHour		* NUM_MS_IN_HOUR;
	return uiRet;
}

void GetLocalDateTime_ISO8601T_noMSnoOffs (char *szISO)
{
	time_t t_time;
	time (&t_time);
	struct tm *stime;
	stime = localtime (&t_time);
	
	// Store the output for date/time:
	// yyyy-mm-ddThh:mi:ss
	ubf_str_from_uint16 (szISO,			(uint16_t) stime->tm_year + 1900);
	szISO [4] = '-';
	ubf_str0_from_59max (szISO + 5,		(uint8_t) stime->tm_mon + 1);
	szISO [7] = '-';
	ubf_str0_from_59max (szISO + 8,		(uint8_t) stime->tm_mday);
	szISO [10] = 'T';
	ubf_str0_from_59max (szISO + 11,	(uint8_t) stime->tm_hour);
	szISO [13] = ':';
	ubf_str0_from_59max (szISO + 14,	(uint8_t) stime->tm_min);
	szISO [16] = ':';
	ubf_str0_from_59max (szISO + 17,	(uint8_t) stime->tm_sec);
}

void GetLocalDateTime_ISO8601T_noMSnoOffs_n (char *szISO)
{
	time_t t_time;
	time (&t_time);
	struct tm *stime;
	stime = localtime (&t_time);
	
	// Store the output for date/time:
	// yyyy-mm-ddThh:mi:ss
	ubf_str_from_uint16 (szISO,			(uint16_t) stime->tm_year + 1900);
	szISO [4] = '-';
	ubf_str0_from_59max (szISO + 5,		(uint8_t) stime->tm_mon + 1);
	szISO [7] = '-';
	ubf_str0_from_59max (szISO + 8,		(uint8_t) stime->tm_mday);
	szISO [10] = 'T';
	ubf_str0_from_59max (szISO + 11,	(uint8_t) stime->tm_hour);
	szISO [13] = ':';
	ubf_str0_from_59max (szISO + 14,	(uint8_t) stime->tm_min);
	szISO [16] = ':';
	ubf_str0_from_59max (szISO + 17,	(uint8_t) stime->tm_sec);
	//GetLocalDateTime_ISO8601T_noMSnoOffs (szISO);
	szISO [19] = '\0';
}

uint64_t BuildYear_uint64 (void)
{
	const char	*ccDate = __DATE__;
	uint64_t	u64year;

	ubf_uint64_from_str_n (&u64year, ccDate + 7, 4, enUintFromStrDontAllowPlus);
	return u64year;
}

uint16_t BuildYear_uint16 (void)
{
	return BuildYear_uint64 () & 0xFFFF;
}

bool FormattedMilliseconds (char *chFormatted, const uint64_t uiTimeInMilliseconds)
{
	uint64_t	uHours;
	uint64_t	uMinutes;
	uint64_t	uSeconds;
	uint64_t	uMilliseconds;
	uint64_t	uH = 1000 * 3600;								// Hours.
	uint64_t	uM = 1000 * 60;									// Minutes.

	uHours			= uiTimeInMilliseconds / uH;
	uMilliseconds	= uiTimeInMilliseconds - (uHours * uH);
	uMinutes		= uMilliseconds / uM;
	uMilliseconds	-= uMinutes * uM;
	uSeconds		= uMilliseconds / 1000;
	uMilliseconds	-= uSeconds * 1000;
	//if (uHours <= 99 && uMinutes <= 59 && uSeconds <= 59 && uMilliseconds <= 999)
	if (uHours < 100)
	{
		//sprintf (chFormatted, "%2.2" PRIu64 ":%2.2" PRIu64 ":%2.2" PRIu64 ".%3.3" PRIu64,
		//	uHours, uMinutes, uSeconds, uMilliseconds);
		// This is faster:
		char	*ch		= chFormatted;
		ubf_str0_from_uint64 (ch, 2, uHours);
		ch += 2;
		ch [0] = ':';
		ch ++;
		ubf_str0_from_uint64 (ch, 2, uMinutes);
		ch += 2;
		ch [0] = ':';
		ch ++;
		ubf_str0_from_uint64 (ch, 2, uSeconds);
		ch += 2;
		ch [0] = '.';
		ch ++;
		ubf_str0_from_uint64 (ch, 3, uMilliseconds);
		return true;
	}
	return false;
}

#ifdef UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
	void Test_ubf_times_functions (void)
	{
		char			ch [FORMATTEDMILLISECONDS_SIZE];
		UBF_DEF_GUARD_VAR (var, "0123456789");
		uint64_t		u;
		bool			b;
		UBF_TIMESTAMP	ut;
		UBF_TIMESTAMP	ut2;
		SUBF_TIMESTRUCT	ts;
		char			cOut [1024];

		GetSystemTime_UBF_TIMESTAMP (&ut);
		ubf_assert (IsBuildYearOrNewer_UBF_TIMESTAMP (&ut));

		u = 1000;
		while (u --)
		{
			GetSystemTime_UBF_TIMESTAMP (&ut);
			SUBF_TIMESTRUCT_from_UBF_TIMESTAMP (&ts, ut);
			UBF_TIMESTAMP_from_SUBF_TIMESTRUCT (&ut2, &ts);
			ubf_assert (ut == ut2);
			GetLocalTime_UBF_TIMESTAMP (&ut);
			SUBF_TIMESTRUCT_from_UBF_TIMESTAMP (&ts, ut);
			UBF_TIMESTAMP_from_SUBF_TIMESTRUCT (&ut2, &ts);
			ubf_assert (ut == ut2);
		}

		// Create our own timestamp.
		//	2022-11-04 16:20:07.400
		ts.uYear				= 2022;
		ts.uMonth				= 11;
		ts.uDay					= 4;
		ts.uHour				= 16;
		ts.uMinute				= 20;
		ts.uSecond				= 7;
		ts.uMillisecond			= 400;
		ts.uMicrosecond			= 500;
		ts.uOffsetHours			= 8;
		ts.uOffsetMinutes		= 30;
		ts.bOffsetNegative		= false;
		//ASSERT (false);
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		// 84h = 8 for uOffsetHours, 4 for 30 offset minutes.
		ubf_assert (0x84 == ut);
		ts.uOffsetHours			= 1;
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		// 14h = 1 for uOffsetHours, 4 for 30 offset minutes.
		ubf_assert (0x14 == ut);
		u = UBF_TIMESTAMP_OFFSETMINUTES (ut);
		ubf_assert (30 == u);
		ts.uOffsetHours			= 0;
		ts.uOffsetMinutes		= 45;
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		u = UBF_TIMESTAMP_OFFSETMINUTES (ut);
		ubf_assert (45 == u);
		ts.uOffsetMinutes		= 15;
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		u = UBF_TIMESTAMP_OFFSETMINUTES (ut);
		ubf_assert (15 == u);
		ts.uOffsetMinutes		= 0;
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		u = UBF_TIMESTAMP_OFFSETMINUTES (ut);
		ubf_assert (0 == u);

		ts.uOffsetHours			= 8;
		ts.uOffsetMinutes		= 30;
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		ut |= UBF_TIMESTAMP_YEAR_BITS (&ts);
		ut |= UBF_TIMESTAMP_MONTH_BITS (&ts);
		ut |= UBF_TIMESTAMP_DAY_BITS (&ts);
		ut |= UBF_TIMESTAMP_HOUR_BITS (&ts);
		ut |= UBF_TIMESTAMP_MINUTE_BITS (&ts);
		ut |= UBF_TIMESTAMP_SECOND_BITS (&ts);
		ut |= UBF_TIMESTAMP_MILLISECOND_BITS (&ts);
		ut |= UBF_TIMESTAMP_MICROSECOND_BITS (&ts);
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		uint32_t uYear;
		uint32_t uWeek = GetISO8601WeekNumberFromDate (ts.uYear, ts.uMonth, ts.uDay, &uYear);
		UNUSED_PARAMETER (uWeek);
		ubf_assert (44 == uWeek);
		ubf_assert (2022 == uYear);
		ISO8601YearAndWeek_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-W44", SIZ_ISO8601YEARANDWEEK));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601Year_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601Year_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601DateAndHour_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601DateAndHour_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16:20:07.400+08:30", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16:20:07.400+08:30", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601YearAndWeek_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-W44", SIZ_ISO8601YEARANDWEEK));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601YearAndWeek_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-W44", SIZ_ISO8601YEARANDWEEK));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601YearAndMonth_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11", SIZ_ISO8601YEARANDMONTH));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601YearAndMonth_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11", SIZ_ISO8601YEARANDMONTH));

		// The same again but with a negative offset of 45 minutes.
		ts.uOffsetHours			= 8;
		ts.uOffsetMinutes		= 45;
		ts.bOffsetNegative		= true;
		ut = UBF_TIMESTAMP_OFFSET_BITS (&ts);
		ut |= UBF_TIMESTAMP_YEAR_BITS (&ts);
		ut |= UBF_TIMESTAMP_MONTH_BITS (&ts);
		ut |= UBF_TIMESTAMP_DAY_BITS (&ts);
		ut |= UBF_TIMESTAMP_HOUR_BITS (&ts);
		ut |= UBF_TIMESTAMP_MINUTE_BITS (&ts);
		ut |= UBF_TIMESTAMP_SECOND_BITS (&ts);
		ut |= UBF_TIMESTAMP_MILLISECOND_BITS (&ts);
		ut |= UBF_TIMESTAMP_MICROSECOND_BITS (&ts);
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601Year_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601Year_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601DateAndHour_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601DateAndHour_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16:20:07.400-08:45", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-11-04 16:20:07.400-08:45", SIZ_ISO8601YEAR));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601YearAndWeek_from_UBF_TIMESTAMP (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-W44", SIZ_ISO8601YEARANDWEEK));
		memset (cOut, 0, SIZ_ISO8601DATETIMESTAMPMS);
		ISO8601YearAndWeek_from_UBF_TIMESTAMP_c (cOut, ut);
		ubf_assert (!memcmp (cOut, "2022-W44", SIZ_ISO8601YEARANDWEEK));

		u = 0;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "00:00:00.000", FORMATTEDMILLISECONDS_SIZE));
		u = 500;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "00:00:00.500", FORMATTEDMILLISECONDS_SIZE));
		u = 999;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "00:00:00.999", FORMATTEDMILLISECONDS_SIZE));
		u = 1999;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "00:00:01.999", FORMATTEDMILLISECONDS_SIZE));
		u = 59999;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "00:00:59.999", FORMATTEDMILLISECONDS_SIZE));
		u = 50 * 1000 * 3600;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "50:00:00.000", FORMATTEDMILLISECONDS_SIZE));
		u = 99 * 1000 * 3600;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "99:00:00.000", FORMATTEDMILLISECONDS_SIZE));
		u = (99 * 1000 * 3600) + (1000 * 59);
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "99:00:59.000", FORMATTEDMILLISECONDS_SIZE));
		u = (99 * 1000 * 3600) + (1000 * 59 * 60) + (1000 * 59);
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "99:59:59.000", FORMATTEDMILLISECONDS_SIZE));
		u = (99 * 1000 * 3600) + (1000 * 59 * 60) + (1000 * 59) + 999;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (true == b);
		ubf_assert (!memcmp (ch, "99:59:59.999", FORMATTEDMILLISECONDS_SIZE));
		// Should cause an overflow and lead to a return value of FALSE.
		u = (99 * 1000 * 3600) + (1000 * 59 * 60) + (1000 * 59) + 999 + 1;
		b = FormattedMilliseconds (ch, u);
		UBF_TST_GUARD_VAR (var, "0123456789");
		ubf_assert (false == b);
		// Should not have been touched by the function due to it returning FALSE.
		ubf_assert (!memcmp (ch, "99:59:59.999", FORMATTEDMILLISECONDS_SIZE));

		// Test bit constants.
		UBF_TIMESTAMP	stamp;
		UBF_TIMESTAMP	maskd;
		GetLocalTime_UBF_TIMESTAMP (&stamp);
		uint64_t uio1 = UBF_TIMESTAMP_OFFSETMINUTES (stamp);
		uint64_t uio2 = UBF_TIMESTAMP_OFFSETMINUTES (stamp & UBF_TIMESTAMP_KEEP_OFFSET_BITS);
		ubf_assert (uio1 == uio2);
		uio1 = UBF_TIMESTAMP_OFFSETHOURS (stamp);
		uio2 = UBF_TIMESTAMP_OFFSETHOURS (stamp & UBF_TIMESTAMP_KEEP_OFFSET_BITS);
		ubf_assert (uio1 == uio2);
		uio1 = UBF_TIMESTAMP_SECOND (stamp);
		uio2 = UBF_TIMESTAMP_SECOND (stamp & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS);
		ubf_assert (uio1 == uio2);
		uio1 = UBF_TIMESTAMP_MINUTE (stamp);
		uio2 = UBF_TIMESTAMP_MINUTE (stamp & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS);
		ubf_assert (uio1 == uio2);
		maskd = stamp & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS;
		ubf_assert_0 (UBF_TIMESTAMP_SECOND (maskd & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS));
		uio1 = UBF_TIMESTAMP_HOUR (stamp);
		uio2 = UBF_TIMESTAMP_HOUR (stamp & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS);
		ubf_assert (uio1 == uio2);
		maskd = stamp & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS;
		ubf_assert_0 (UBF_TIMESTAMP_SECOND (maskd & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_MINUTE (maskd & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS));
		uio1 = UBF_TIMESTAMP_DAY (stamp);
		uio2 = UBF_TIMESTAMP_DAY (stamp & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS);
		ubf_assert (uio1 == uio2);
		maskd = stamp & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS;
		ubf_assert_0 (UBF_TIMESTAMP_SECOND (maskd & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_MINUTE (maskd & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_HOUR (maskd & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS));
		uio1 = UBF_TIMESTAMP_MONTH (stamp);
		uio2 = UBF_TIMESTAMP_MONTH (stamp & UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS);
		ubf_assert (uio1 == uio2);
		maskd = stamp & UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS;
		ubf_assert_0 (UBF_TIMESTAMP_SECOND (maskd & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_MINUTE (maskd & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_HOUR (maskd & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_DAY (maskd & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS));
		uio1 = UBF_TIMESTAMP_YEAR (stamp);
		uio2 = UBF_TIMESTAMP_YEAR (stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS);
		ubf_assert (uio1 == uio2);
		maskd = stamp & UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS;
		ubf_assert_0 (UBF_TIMESTAMP_SECOND (maskd & UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_MINUTE (maskd & UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_HOUR (maskd & UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_DAY (maskd & UBF_TIMESTAMP_KEEP_FROM_DAY_BITS));
		ubf_assert_0 (UBF_TIMESTAMP_MONTH (maskd & UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS));

		char sz1 [1024];
		char sz2 [1024];

		GetISO8601Week_s (sz1);
		GetISO8601Week_c (sz2);
		if (memcmp (sz1, sz2, SIZ_ISO8601WEEK))
		{	// We assume the test ran just the moment the week number changed.
			GetISO8601Week_s (sz1);
			GetISO8601Week_c (sz2);
			ubf_assert (!memcmp (sz1, sz2, SIZ_ISO8601WEEK));
		} else
		{
			ubf_assert (!memcmp (sz1, sz2, SIZ_ISO8601WEEK));
		}

		UBF_TIMESTAMP	tt;
		ULONGLONG		u1;
		ULONGLONG		u2;
		UNUSED_PARAMETER (u2);
		UNUSED (u1);

		tt = LocalTime_UBF_TIMESTAMP ();
		u1 = GetSystemTimeAsULONGLONG ();

		char szTS1 [SIZ_ISO8601DATETIMESTAMPMS];
		char szTS2 [SIZ_ISO8601DATETIMESTAMPMS];
		
		ISO8601_from_UBF_TIMESTAMP	(szTS1, tt);
		ISO8601_from_UBF_TIMESTAMP_c	(szTS2, tt);
		ubf_assert (!memcmp (szTS1, szTS2, SIZ_ISO8601DATETIMESTAMPMS));

		tt = LocalTime_UBF_TIMESTAMP ();
		ISO8601T_from_UBF_TIMESTAMP  (szTS1, tt);
		ISO8601T_from_UBF_TIMESTAMP_c (szTS2, tt);
		ubf_assert (!memcmp (szTS1, szTS2, SIZ_ISO8601DATETIMESTAMPMS));

		char szISO_1 [SIZ_ISO8601DATETIMESTAMP_NO_OFFS];
		char szISO_2 [SIZ_ISO8601DATETIMESTAMP_NO_OFFS];
		szISO_1 [LEN_ISO8601DATETIMESTAMP_NO_OFFS] = 'X';
		GetLocalDateTime_ISO8601T_noMSnoOffs	(szISO_1);
		GetLocalDateTime_ISO8601T_noMSnoOffs_n	(szISO_2);
		if (memcmp (szISO_1, szISO_2, LEN_ISO8601DATETIMESTAMP_NO_OFFS))
		{	// Hit during a second change.
			GetLocalDateTime_ISO8601T_noMSnoOffs	(szISO_1);
			GetLocalDateTime_ISO8601T_noMSnoOffs_n	(szISO_2);
		}
		ubf_assert_0 (memcmp (szISO_1, szISO_2, LEN_ISO8601DATETIMESTAMP_NO_OFFS));
		ubf_assert ('X'		== szISO_1 [LEN_ISO8601DATETIMESTAMP_NO_OFFS]);
		ubf_assert ('\0'	== szISO_2 [LEN_ISO8601DATETIMESTAMP_NO_OFFS]);

		// Timings.
		/*
			We found that the psx function is twice as fast as the win version.
		*/
		/*
		u1 = GetSystemTimeAsULONGLONG ();
		unsigned int ui;
		for (ui = 0; ui < 10000000; ++ ui)
		{
			tt = LocalTime_UBF_TIMESTAMP ();
		}
		u2 = GetSystemTimeAsULONGLONG ();
		char timespan [128];
		GetReadableTimeSpan (timespan, 128, u2 - u1);
		puts (timespan);
		puts ("");
		*/

		//UBF_TIMESTAMP	tt;
		//ULONGLONG		u1;
		//ULONGLONG		u2;

		/*
		// Timing.
		unsigned int ui;
		unsigned int uiIts = 1000000000;
		uiIts = 100000000;
		//unsigned int uiIts = 100;
		char timespan [128];

		u1 = GetSystemTimeAsULONGLONG ();
		for (ui = 0; ui < uiIts; ++ ui)
		{
			ISO8601_from_UBF_TIMESTAMP_s	(szTS1, tt);
		}
		u2 = GetSystemTimeAsULONGLONG ();
		GetReadableTimeSpan (timespan, 128, u2 - u1);
		puts (timespan);
		puts ("");

		u1 = GetSystemTimeAsULONGLONG ();
		for (ui = 0; ui < uiIts; ++ ui)
		{
			ISO8601_from_UBF_TIMESTAMP_c	(szTS1, tt);
		}
		u2 = GetSystemTimeAsULONGLONG ();
		GetReadableTimeSpan (timespan, 128, u2 - u1);
		puts (timespan);
		puts ("");
		*/

		/*
			This takes around 1:30, which is 90 seconds, i.e. around 90 ns per iteration.
			This test was to find out whether it's worth using ns for the timestamp.

		UBF_TIMESTAMP tsp;
		UBF_TIMESTAMP t2 = 0;
		uint64_t uits1 = 1000000000;
		uint64_t ux;
		uits1 = 1000000000;
		//unsigned int uiIts = 100;
		char timespan [128];

		u1 = GetSystemTimeAsULONGLONG ();
		for (ux = 0; ux < uits1; ++ ux)
		{
			GetLocalTime_UBF_TIMESTAMP (&tsp);
			t2 += tsp;
		}
		u2 = GetSystemTimeAsULONGLONG ();
		GetReadableTimeSpan (timespan, 128, u2 - u1);
		puts (timespan);
		puts ("");
		printf ("%" PRId64, t2);
		exit (0);
		*/

	}
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4996)									// MSVC says some sprintf is unsafe.
#endif
