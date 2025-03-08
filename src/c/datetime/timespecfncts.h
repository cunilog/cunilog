/****************************************************************************************

	File:		timespecfncts.h
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

#ifndef TIMESPECFNCTS_H
#define TIMESPECFNCTS_H

#include <stdbool.h>
#include <time.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		//#include "./ubf_date_and_time.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		//#include "./../datetime/ubf_date_and_time.h"
	#endif

	#ifdef PLATFORM_IS_WINDOWS
		#include <Windows.h>
	#endif

	#ifdef PLATFORM_IS_POSIX
		#include <time.h>
		#include <unistd.h>
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
	
	All functions here expect that the values of the struct timespec have
	been retrieved with clock_gettime () with a clk_id parameter of either
	CLOCK_MONOTONIC,
	CLOCK_MONOTONIC_COARSE, or
	CLOCK_BOOTTIME.
	
	See http://man7.org/linux/man-pages/man2/clock_gettime.2.html for more
	information on the clock_gettime () system call.
	
	All functions here only deal with timespans, not with absolute time
	values.
*/

// Test function.
#ifndef TIMESPECFNCTS_BUILD_TEST
#define TIMESPECFNCTS_BUILD_TEST
#endif

BEGIN_C_DECLS

/*
	TIMESPEC_INIT_ZERO
	
	Initialiser for a struct timeval.
*/
#define TIMESPEC_INIT_ZERO	{0,0}

/*
	timespec_from_ULONGLONG
	
	Converts the value ullValue from a FILETIME ULONGLONG to the struct
	timespec ts points to. Only relative timespans are computed correctly.
*/
void timespec_from_ULONGLONG (struct timespec *ts, ULONGLONG ullDiff);

/*
	ULONGLONG_from_timespec
	
	Retrieves the value of ts as a FILETIME ULONGLONG. The returned
	value is adjusted correctly for the Windows FILETIME epoch.
	
	If the epoch adjustment is not required, the function
	ULONGLONG_from_timespec_rel () can be called instead.
*/
ULONGLONG ULONGLONG_from_timespec (struct timespec *ts);

/*
	ULONGLONG_from_timespec_rel
	
	Retrieves the value of ts as a FILETIME ULONGLONG. Only relative
	timespans are computed correctly.
	
	To get an absolute value, add 116444736000000000 to the return value,
	which is the difference between the FILETIME and the Unix epoch, or
	use the function ULONGLONG_from_timespec () instead.
*/
ULONGLONG ULONGLONG_from_timespec_rel (struct timespec *ts);

/*
	timespec_substract_ULONGLONG
	
	Substracts the value (ULONGLONG FILETIME) ullValue from the struct
	timespec ts points to.
*/
bool timespec_substract_ULONGLONG (struct timespec *ts, ULONGLONG ullDiff);

/*
	timespec_testfunction

	The function to test the other functions.
*/
#ifdef TIMESPECFNCTS_BUILD_TEST
	bool timespec_testfunction (void);
#else
	#define timespec_testfunction()
#endif

END_C_DECLS

#endif															// End of #ifndef TIMESPECFNCTS_H.
