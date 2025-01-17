/****************************************************************************************

	File:		timespecfncts.c
	Why:		Functions and macros that deal with struct timespec.
	OS:			POSIX/C99.
	Author:		Thomas
	Created:	2019-12-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-12-10	Thomas			Created.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./timespecfncts.h"
	#include "./ubf_times.h"
	#include "./ubf_date_and_time.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./../dbg/ubfdebug.h"
	#else
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

/*
	The differences between the timeval and timespec structures:
	
	struct timeval {
		long    tv_sec;
		long    tv_usec;										// Microseconds.
	};
	
	struct timespec {
		long    tv_sec;
		long    tv_nsec;										// Nanoseconds.
	};
*/

void timespec_from_ULONGLONG (struct timespec *ts, ULONGLONG ullDiff)
{
	ULONGLONG	ull;
	
	ubf_assert (NULL != ts);
	ull = ullDiff % FT_SECOND;
	// Everything smaller than a second is now in ull.
	//	We need the value in nanosecons (ns). 1 us = 1000 ns.
	//	FILETIME stores the amount in 100 ns intervals.
	ts->tv_nsec	= (long) (ull * 100);
	// The seconds go to the seconds member.
	ts->tv_sec	= (long long) ullDiff / (long long) FT_SECOND;
}

ULONGLONG ULONGLONG_from_timespec (struct timespec *ts)
{
	ULONGLONG	ull;
	
	ubf_assert (NULL != ts);
	ull =	(ULONGLONG) ts->tv_sec * FT_SECOND;
	ull +=	(ULONGLONG) ts->tv_nsec / FT_D_NANOSECOND;
	ull +=	116444736000000000;
	return ull;
}

ULONGLONG ULONGLONG_from_timespec_rel (struct timespec *ts)
{
	ULONGLONG	ull;
	
	ubf_assert (NULL != ts);
	ull =	(ULONGLONG) ts->tv_sec * FT_SECOND;
	ull +=	(ULONGLONG) ts->tv_nsec / FT_D_NANOSECOND;
	return ull;
}

bool timespec_substract_ULONGLONG (struct timespec *ts, ULONGLONG ullDiff)
{
	struct timespec		pv;
	bool				bFits	= true;
	
	timespec_from_ULONGLONG (&pv, ullDiff);
	if (ts->tv_sec >= pv.tv_sec)
	{
		ts->tv_sec -= pv.tv_sec;
	} else
	{
		ts->tv_sec = 0;
		bFits = false;
	}
	if (ts->tv_nsec >= pv.tv_nsec)
	{
		ts->tv_nsec -= pv.tv_nsec;
	} else
	{
		ts->tv_nsec = 0;
		bFits = false;
	}
	return bFits;
}

#ifdef TIMESPECFNCTS_BUILD_TEST
	bool timespec_testfunction (void)
	{
		struct timespec		ts		= TIMESPEC_INIT_ZERO;
		ULONGLONG			ul1;
		ULONGLONG			ul2;
		bool				bRet	= false;
		
		ubf_assert (0 == ts.tv_sec);
		ubf_assert (0 == ts.tv_nsec);
		
		ubf_get_system_time_ULONGLONG (&ul1);
		Sleep_s (1);											// 1 second.
		ubf_get_system_time_ULONGLONG (&ul2);
		ubf_assert (ul2 > ul1);
		timespec_from_ULONGLONG (&ts, ul2 - ul1);
		ubf_assert (1		== ts.tv_sec);						// Should have 1 second.
		ubf_assert (20000000	> ts.tv_nsec);					// Will most likely have
																//	something between 20 000 000
																//	and 0.
		ubf_get_system_time_ULONGLONG (&ul1);
		Sleep_ms (500);											// 500 ms.
		ubf_get_system_time_ULONGLONG (&ul2);
		ubf_assert (ul2 > ul1);
		timespec_from_ULONGLONG (&ts, ul2 - ul1);
		ubf_assert (0		== ts.tv_sec);						// Should have 0 seconds.
		ubf_assert (600000000	> ts.tv_nsec);					// Will most likely be
																//	something between 600000000
																//	and 0, depending on the
																//	granularity. On Windows
																//	it's a bit more than
																//	500 million
																//	(500000000).
		return bRet;
	}
#endif
