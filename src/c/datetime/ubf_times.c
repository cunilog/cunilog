/****************************************************************************************

	File:		ubf_time.c
	Why:		Contains structures and functions to work with UBF_TIMESTAMP
				and SUBF_TIMESTRUCT structures.
	OS:			C99.
	Author:		Thomas
	Created:	2018-03-29
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2018-03-29	Thomas			Created.
2020-09-23	Thomas			Extended.
2021-01-01	Thomas			Format of UBF_TIMESTAMP changed. The old one had a few
							 issues.
							 
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

// Function ftime ():
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubf_times.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
	#else
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

#ifdef _MSC_VER
#pragma warning (disable: 4996)									// MSVC says some functions are unsafe.
#endif

UBF_TIMESTAMP UBF_TIMESTAMP_OFFSET_BITS (SUBF_TIMESTRUCT *ts)
{
	UBF_TIMESTAMP			s;

	ubf_assert_non_NULL (ts);

	/*
		Specification from 2021-01-01:

		Bit 76543210
			3210|||.	UTC offset in hours
				0||.	1: UTC offset is negative
				 ||.	0: UTC offset is positive
				 0|.	1: UTC offset + 30 minutes
				  |.	0: UTC offset unchanged
				  0.	1: UTC offset + 15 minutes
						0: UTC offset unchanged
	*/
	s = ts->uOffsetHours;
	s <<= 4;
	s |= ts->bOffsetNegative ? 0x08 : 0;
	switch (ts->uOffsetMinutes)
	{	// Can be: 0, 15, 30, and 45.
	case 0:
		break;
	case 15:
		s |= 0x02;												// Bit 0.
		break;
	case 30:
		s |= 0x04;												// Bit 1.
		break;
	case 45:
		s |= 0x06;												// Bit 0 and 1.
		break;
	default:
		ubf_assert (false);
	}
	return s;
}

void SUBF_TIMESTRUCT_to_UBF_TIMESTAMP (UBF_TIMESTAMP *t, SUBF_TIMESTRUCT *ts)
{
	ubf_assert (NULL != t);
	ubf_assert (NULL != ts);
	ubf_assert (ts->uMicrosecond < 1000);
	ubf_assert (ts->uMillisecond < 1000);

	UBF_TIMESTAMP			s;

	s = UBF_TIMESTAMP_OFFSET_BITS (ts);
	s |= UBF_TIMESTAMP_MICROSECOND_BITS (ts);
	s |= UBF_TIMESTAMP_MILLISECOND_BITS (ts);
	s |= UBF_TIMESTAMP_SECOND_BITS (ts);
	s |= UBF_TIMESTAMP_MINUTE_BITS (ts);
	s |= UBF_TIMESTAMP_HOUR_BITS (ts);
	s |= UBF_TIMESTAMP_DAY_BITS (ts);
	s |= UBF_TIMESTAMP_MONTH_BITS (ts);
	s |= UBF_TIMESTAMP_YEAR_BITS (ts);
	*t = s;
}

#ifdef OS_IS_ANDROID
	#ifdef BUILD_ANDROID_FTIME_HERE
		// See https://github.com/01org/android-bluez-bionic/blob/master/libc/bionic/ftime.c .
		//	Without this we'll get an "undefined reference to ftime" further down.

		/*
		 * Copyright (C) 2008 The Android Open Source Project
		 * All rights reserved.
		 *
		 * Redistribution and use in source and binary forms, with or without
		 * modification, are permitted provided that the following conditions
		 * are met:
		 *  * Redistributions of source code must retain the above copyright
		 *    notice, this list of conditions and the following disclaimer.
		 *  * Redistributions in binary form must reproduce the above copyright
		 *    notice, this list of conditions and the following disclaimer in
		 *    the documentation and/or other materials provided with the
		 *    distribution.
		 *
		 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
		 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
		 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
		 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
		 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
		 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
		 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
		 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
		 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		 * SUCH DAMAGE.
		 */

		int ftime (struct timeb *tb)
		{
			struct timeval  tv;
			struct timezone tz;
	
			if (gettimeofday (&tv, &tz) < 0)
				return -1;
	
			tb->time    = tv.tv_sec;
			tb->millitm = (tv.tv_usec + 500) / 1000;
	
			if (tb->millitm == 1000) {
				++tb->time;
				tb->millitm = 0;
			}
			tb->timezone = (short) tz.tz_minuteswest;
			tb->dstflag  = (short) tz.tz_dsttime;
	
			return 0;
		}
	#endif
#endif

void GetSystemTime_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts)
{
	ubf_assert (NULL != pts);
	
	unsigned short	ms;

	#ifdef PLATFORM_IS_WINDOWS
		struct	timeb	timebuffer;
		_ftime (&timebuffer);
		ms = timebuffer.millitm;
	#else
		struct timeval	tv;
		struct timezone	tz;
		gettimeofday (&tv, &tz);
		ms = (tv.tv_usec + 500) / 1000;
	#endif

	time_t t_time;
	time (&t_time);
	struct tm stime;
	gmtime_r (&t_time, &stime);
	
	pts->uYear				= (unsigned int) stime.tm_year + 1900;
	pts->uMonth				= (unsigned int) stime.tm_mon + 1;
	pts->uDay				= (unsigned int) stime.tm_mday;
	pts->uHour				= (unsigned int) stime.tm_hour;
	pts->uMinute			= (unsigned int) stime.tm_min;
	pts->uSecond			= (unsigned int) stime.tm_sec;
	pts->uMillisecond		= ms;
	pts->uMicrosecond		= 0;
	pts->uOffsetHours		= 0;
	pts->uOffsetMinutes		= 0;
	pts->bOffsetNegative	= false;
}

void GetSystemTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut)
{
	SUBF_TIMESTRUCT			ts;

	GetSystemTime_SUBF_TIMESTRUCT (&ts);
	SUBF_TIMESTRUCT_to_UBF_TIMESTAMP (ut, &ts);
}

void GetLocalTime_SUBF_TIMESTRUCT_psx (SUBF_TIMESTRUCT *pts)
{
	int				i_adjustment_hours;
	int				i_adjustment_mins;
	unsigned short	ms;
	bool			bOffsetNegative = false;

	#ifdef PLATFORM_IS_WINDOWS
		struct	timeb	timebuffer;
		_ftime (&timebuffer);
		if (timebuffer.timezone < 0)
		{
			bOffsetNegative = true;
			timebuffer.timezone *= -1;
		}
		i_adjustment_hours = timebuffer.timezone / 60;
		i_adjustment_mins  = timebuffer.timezone % 60;
		ms = timebuffer.millitm;
	#else
		struct timeval	tv;
		struct timezone	tz;
		gettimeofday (&tv, &tz);
		if (tz.tz_minuteswest < 0)
		{
			bOffsetNegative = true;
			tz.tz_minuteswest *= -1;
		}
		i_adjustment_hours	= tz.tz_minuteswest / 60;
		i_adjustment_mins	= tz.tz_minuteswest % 60;
		ms = (tv.tv_usec + 500) / 1000;
	#endif

	time_t t_time;
	time (&t_time);
	struct tm *stime;
	stime = localtime (&t_time);
	
	// Adjust daylight saving time (DST) value.
	//  DST automatically implies +1 hour (+01:00).
	if (stime->tm_isdst > 0) i_adjustment_hours++;
    
	// Store the output for date/time including milliseconds.
	// yyyy-mm-dd hh:mi:ss.mis+01:00
	pts->uYear				= (unsigned int) stime->tm_year + 1900;
	pts->uMonth				= (unsigned int) stime->tm_mon + 1;
	pts->uDay				= (unsigned int) stime->tm_mday;
	pts->uHour				= (unsigned int) stime->tm_hour;
	pts->uMinute			= (unsigned int) stime->tm_min;
	pts->uSecond			= (unsigned int) stime->tm_sec;
	pts->uMillisecond		= ms;
	pts->uMicrosecond		= 0;
	pts->uOffsetHours		= (unsigned int) i_adjustment_hours;
	pts->uOffsetMinutes		= (unsigned int) i_adjustment_mins;
	pts->bOffsetNegative	= bOffsetNegative;
}

/*
	This function is very slow!
*/
#ifdef _WIN32
	void GetLocalTime_SUBF_TIMESTRUCT_win (SUBF_TIMESTRUCT *pts)
	{
		//_ASSERT (FALSE);
		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx .
		SYSTEMTIME						st;
		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms725481(v=vs.85).aspx .
		TIME_ZONE_INFORMATION			tzi;
		// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/timezoneapi/ns-timezoneapi-dynamic_time_zone_information .
		//DYNAMIC_TIME_ZONE_INFORMATION	tdi;
		LONG							lBias;					// UTC = local time + bias
																//	(in minutes).
	
		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms724390(v=vs.85).aspx .
		//GetSystemTime (&st);
		GetLocalTime (&st);
		pts->uYear				= (unsigned int) st.wYear;
		pts->uMonth				= (unsigned int) st.wMonth;
		pts->uDay				= (unsigned int) st.wDay;
		pts->uHour				= (unsigned int) st.wHour;
		pts->uMinute			= (unsigned int) st.wMinute;
		pts->uSecond			= (unsigned int) st.wSecond;
		pts->uMillisecond		= (unsigned int) st.wMilliseconds;
		pts->uMicrosecond		= 0;
		// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-gettimezoneinformation .
		DWORD	dwTZ;
		dwTZ = GetTimeZoneInformation (&tzi);
		// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-getdynamictimezoneinformation .
		//	We're ok with GetTimeZoneInformation () and don't need this.
		//GetDynamicTimeZoneInformation (&tdi);
		lBias = tzi.Bias;										// Note that the bias is negative
																//	for positive offsets.
		// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-gettimezoneinformation .
		if (TIME_ZONE_ID_DAYLIGHT == dwTZ)
		{
			lBias += tzi.DaylightBias;		
		}
		if (lBias <= 0)											// Note: 0 is positive.
		{
			lBias *= -1;
			pts->bOffsetNegative = FALSE;
		} else
		{
			pts->bOffsetNegative = TRUE;
		}
		pts->uOffsetHours		= (unsigned int) lBias / 60;
		pts->uOffsetMinutes		= lBias % 60;
	}
#endif

#ifdef DEBUG
	void GetLocalTime_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts)
	{
		ubf_assert (NULL != pts);
		if (pts)
		{
			#ifdef OS_IS_WINDOWS
				// The POSIX version is twice as fast here as the Windows
				//	version in debug versions and three times as fast in
				//	release builds.
				GetLocalTime_SUBF_TIMESTRUCT_psx (pts);
				//GetLocalTime_SUBF_TIMESTRUCT_win (pts);
			#else
				GetLocalTime_SUBF_TIMESTRUCT_psx (pts);
			#endif
		}
	}
#endif

/*
	Previously used.

	bool GetLocalTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut)
	{
		SUBF_TIMESTRUCT			ts;

		GetLocalTime_SUBF_TIMESTRUCT (&ts);
		return SUBF_TIMESTRUCT_to_UBF_TIMESTAMP (ut, &ts);
	}
*/

void GetLocalTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut)
{
	ubf_assert_non_NULL (ut);

	int				i_adjustment_hours;
	int				i_adjustment_mins;
	unsigned short	ms;
	bool			bOffsetNegative = false;

	#ifdef PLATFORM_IS_WINDOWS
		struct	timeb	timebuffer;
		_ftime (&timebuffer);
		if (timebuffer.timezone < 0)
		{
			bOffsetNegative = true;
			timebuffer.timezone *= -1;
		}
		i_adjustment_hours = timebuffer.timezone / 60;
		i_adjustment_mins  = timebuffer.timezone % 60;
		ms = timebuffer.millitm;
	#else
		struct timeval	tv;
		struct timezone	tz;
		gettimeofday (&tv, &tz);
		if (tz.tz_minuteswest < 0)
		{
			bOffsetNegative = true;
			tz.tz_minuteswest *= -1;
		}
		i_adjustment_hours	= tz.tz_minuteswest / 60;
		i_adjustment_mins	= tz.tz_minuteswest % 60;
		ms = (tv.tv_usec + 500) / 1000;
	#endif

	time_t t_time;
	time (&t_time);
	struct tm *stime;
	stime = localtime (&t_time);
	
	// Adjust daylight saving time (DST) value.
	//  DST automatically implies +1 hour (+01:00).
	if (stime->tm_isdst > 0) i_adjustment_hours++;
    
	SET_UBF_TIMESTAMP_OFFSET_BITS	(
		*ut, (UBF_TIMESTAMP) i_adjustment_hours, (UBF_TIMESTAMP) i_adjustment_mins, bOffsetNegative
									);
	*ut |= SET_UBF_TIMESTAMP_YEAR_BITS			((UBF_TIMESTAMP) stime->tm_year + 1900);
	*ut |= SET_UBF_TIMESTAMP_MONTH_BITS			((UBF_TIMESTAMP) stime->tm_mon + 1);
	*ut |= SET_UBF_TIMESTAMP_DAY_BITS			((UBF_TIMESTAMP) stime->tm_mday);
	*ut |= SET_UBF_TIMESTAMP_HOUR_BITS			((UBF_TIMESTAMP) stime->tm_hour);
	*ut |= SET_UBF_TIMESTAMP_MINUTE_BITS		((UBF_TIMESTAMP) stime->tm_min);
	*ut |= SET_UBF_TIMESTAMP_SECOND_BITS		((UBF_TIMESTAMP) stime->tm_sec);
	*ut |= SET_UBF_TIMESTAMP_MILLISECOND_BITS	((UBF_TIMESTAMP) ms);

	// Currently still unused.
	//*ut |= SET_UBF_TIMESTAMP_MICROSECOND_BITS (0);
}

UBF_TIMESTAMP SystemTime_UBF_TIMESTAMP (void)
{
	UBF_TIMESTAMP	dts;
	GetSystemTime_UBF_TIMESTAMP (&dts);
	return dts;
}

UBF_TIMESTAMP LocalTime_UBF_TIMESTAMP (void)
{
	UBF_TIMESTAMP	dts;
	GetLocalTime_UBF_TIMESTAMP (&dts);
	return dts;
}

/*
	A note about tests.

	Functions in this module (ubf_times) are tested by the test function in module ubf_date_and_time.c/h.

	Please do not place any code below. Please add code only above this comment block.
*/
