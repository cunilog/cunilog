/****************************************************************************************

	File:		ubf_time.h
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
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This module deals with our own timestamp formats. UBF_TIMESTAMP is a
	64 bit unsigned type and can and should be used whenever a timestamp is
	required. A UBF_TIMESTAMP can be extracted to a SUBF_TIMESTRUCT for
	accessing its members.
	
	This module is included by ubf_data_and_time.h. So, if you include that
	file you don't need to include this one separately.
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

#ifndef U_UBF_TIME_H_INCLUDED
#define U_UBF_TIME_H_INCLUDED

/*
#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#include "./ubf_type_definitions.h"
#else
	#include "./../OS/ubf_type_definitions.h"
#endif
*/

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _WIN32
	#ifndef OS_IS_WINDOWS
	#define OS_IS_WINDOWS
	#endif
	#include <Windows.h>
#else
	#include <time.h>
	#include <sys/timeb.h>
#endif

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)	(P) = (P);
#endif
#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER(x) (void)(x)
#endif

/*
	Time intervals valid for values in FILETIME structures.
*/
#ifndef FT_D_NANOSECOND
#define FT_D_NANOSECOND ((ULONGLONG) 100)						/* This is 1/100! */
#endif
#ifndef FT_MICROSECOND
#define FT_MICROSECOND ((ULONGLONG) 10)
#endif
#ifndef FT_MILLISECOND
#define FT_MILLISECOND ((ULONGLONG) 10000)
#endif
#ifndef FT_SECOND
#define FT_SECOND ((ULONGLONG) 10000000)
#endif
#ifndef FT_MINUTE
#define FT_MINUTE (60 * FT_SECOND)
#endif
#ifndef FT_HOUR
#define FT_HOUR   (60 * FT_MINUTE)
#endif
#ifndef FT_DAY
#define FT_DAY    (24 * FT_HOUR)
#endif

// Lengths and sizes. Lengths exclude and sizes include a terminating NUL
//	character.
#ifndef LEN_ISO8601WEEK
#define LEN_ISO8601WEEK						(3)					// "Wnn"
#endif
#ifndef SIZ_ISO8601WEEK
#define SIZ_ISO8601WEEK						(LEN_ISO8601WEEK + 1)
#endif
#ifndef LEN_ISO8601YEAR
#define LEN_ISO8601YEAR						(4)					// "YYYY"
#endif
#ifndef SIZ_ISO8601YEAR
#define SIZ_ISO8601YEAR						(LEN_ISO8601YEAR + 1)
#endif
#ifndef LEN_ISO8601YEARANDMONTH
#define LEN_ISO8601YEARANDMONTH				(7)					// "YYYY-MM"
#endif
#ifndef SIZ_ISO8601YEARANDMONTH
#define SIZ_ISO8601YEARANDMONTH				(LEN_ISO8601YEARANDMONTH + 1)
#endif
#ifndef LEN_ISO8601YEARANDWEEK
#define LEN_ISO8601YEARANDWEEK				(8)					// "YYYY-Wnn"
#endif
#ifndef SIZ_ISO8601YEARANDWEEK
#define SIZ_ISO8601YEARANDWEEK				(LEN_ISO8601YEARANDWEEK + 1)
#endif
#ifndef LEN_ISO8601SHORTDATE
#define LEN_ISO8601SHORTDATE				(8)					// "YYYYMMDD"
#endif
#ifndef SIZ_ISO8601SHORTDATE
#define SIZ_ISO8601SHORTDATE				(LEN_ISO8601SHORTDATE + 1)
#endif
#ifndef LEN_ISO8601DATE
#define LEN_ISO8601DATE						(10)				// "YYYY-MM-DD"
#endif
#ifndef SIZ_ISO8601DATE
#define SIZ_ISO8601DATE						(LEN_ISO8601DATE + 1)
#endif
#ifndef LEN_ISO8601DATEANDHOUR
#define LEN_ISO8601DATEANDHOUR				(13)				// "YYYY-MM-DD HH"
#endif
#ifndef SIZ_ISO8601DATEANDHOUR
#define SIZ_ISO8601DATEANDHOUR				(LEN_ISO8601DATEANDOUR + 1)
#endif
#ifndef LEN_ISO8601DATEHOURANDMINUTE
#define LEN_ISO8601DATEHOURANDMINUTE		(16)				// "YYYY-MM-DD HH:MI"
#endif
#ifndef SIZ_ISO8601DATEHOURANDMINUTE
#define SIZ_ISO8601DATEHOURANDMINUTE		(LEN_ISO8601DATEHOURANDMINUTE + 1)
#endif
#ifndef LEN_ISO8601SHORTDATEHOURSONLY
#define LEN_ISO8601SHORTDATEHOURSONLY		(11)				// "YYYYMMDDTHH"
#endif
#ifndef SIZ_ISO8601SHORTDATEHOURSONLY
#define SIZ_ISO8601SHORTDATEHOURSONLY		(LEN_ISO8601SHORTDATEHOURSONLY + 1)
#endif
#ifndef LEN_ISO8601SHORTDATEHOURSMINS
#define LEN_ISO8601SHORTDATEHOURSMINS		(13)				// "YYYYMMDDTHHMI"
#endif
#ifndef SIZ_ISO8601SHORTDATEHOURSMINS
#define SIZ_ISO8601SHORTDATEHOURSMINS		(LEN_ISO8601SHORTDATEHOURSMINS + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMELOCAL
#define	LEN_ISO8601SHORTDATETIMELOCAL		(15)				// "YYYYMMDDTHHMISS"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMELOCAL
#define	SIZ_ISO8601SHORTDATETIMELOCAL		(LEN_ISO8601SHORTDATETIMELOCAL + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIME
#define	LEN_ISO8601SHORTDATETIME			(16)				// "YYYYMMDDTHHMISSZ"
#endif
#ifndef SIZ_ISO8601SHORTDATETIME
#define	SIZ_ISO8601SHORTDATETIME			(LEN_ISO8601SHORTDATETIME + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMP_NO_OFFS
#define LEN_ISO8601DATETIMESTAMP_NO_OFFS	(19)				// "YYYY-MM-DD hh:mm:ss"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMP_NO_OFFS	(LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMS								// "YYYYMMDDTHHMISS.misZ"
#define	LEN_ISO8601SHORTDATETIMEMS			(20)
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMS								// "YYYYMMDDTHHMISS.misZ"
#define	SIZ_ISO8601SHORTDATETIMEMS			(LEN_ISO8601SHORTDATETIMEMS)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMSOFFSH
#define	LEN_ISO8601SHORTDATETIMEMSOFFSH		(22)				// "YYYYMMDDTHHMISS.mis+HH"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMSOFFSH
#define	SIZ_ISO8601SHORTDATETIMEMSOFFSH		(LEN_ISO8601SHORTDATETIMEMSOFFSH + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMSUS
#define	LEN_ISO8601SHORTDATETIMEMSUS		(23)				// "YYYYMMDDTHHMISS.mis000Z"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMSUS
#define	SIZ_ISO8601SHORTDATETIMEMSUS		(LEN_ISO8601SHORTDATETIMEMSUS + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS_NO_OFFS
#define LEN_ISO8601DATETIMESTAMPMS_NO_OFFS	(23)				// "YYYY-MM-DD hh:mm:ss.xxx"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPMS_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMPMS_NO_OFFS	(LEN_ISO8601DATETIMESTAMPMS_NO_OFFS + 1)
#endif
#ifndef LEN_ISO8601SHORTDATETIMEMSUSOFFSH
#define	LEN_ISO8601SHORTDATETIMEMSUSOFFSH	(25)				// "YYYYMMDDTHHMISS.mis000+HH"
#endif
#ifndef SIZ_ISO8601SHORTDATETIMEMSUSOFFSH
#define	SIZ_ISO8601SHORTDATETIMEMSUSOFFSH	(LEN_ISO8601SHORTDATETIMEMSUSOFFSH + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMP								// "YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMP			(25)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP								// "YYYY-MM-DD HH:MI:SS+01:00"
#define SIZ_ISO8601DATETIMESTAMP			(LEN_ISO8601DATETIMESTAMP + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPU8C								// "YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMPU8C			(25 + 6)			//	Each colon is 3 octets.
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPU8C								// "YYYY-MM-DD HH:MI:SS+01:00"
#define SIZ_ISO8601DATETIMESTAMPU8C			(LEN_ISO8601DATETIMESTAMPU8C + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMP_HOL							// "1YYYY-MM-DD HH:MI:SS+01:00"
#define LEN_ISO8601DATETIMESTAMP_HOL		(26)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_HOL							// "1YYYY-MM-DD HH:MI:SS+01:00"
#define SIZ_ISO8601DATETIMESTAMP_HOL		(LEN_ISO8601DATETIMESTAMP_HOL + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS								// "YYYY-MM-DD HH:MI:SS.000+01:00"
#define LEN_ISO8601DATETIMESTAMPMS			(29)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPMS								// "YYYY-MM-DD HH:MI:SS.000+01:00"
#define SIZ_ISO8601DATETIMESTAMPMS			(LEN_ISO8601DATETIMESTAMPMS + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPUS								// "YYYY-MM-DD HH:MI:SS.000000+01:00"
#define LEN_ISO8601DATETIMESTAMPUS			(32)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPUS								// "YYYY-MM-DD HH:MI:SS.000000+01:00"
#define SIZ_ISO8601DATETIMESTAMPUS			(LEN_ISO8601DATETIMESTAMPUS + 1)
#endif
#ifndef LEN_ISO8601DATETIMESTAMPMS_HOL							// "1YYYY-MM-DD HH:MI:SS.000+01:00"
#define LEN_ISO8601DATETIMESTAMPMS_HOL		(30)
#endif
#ifndef SIZ_ISO8601DATETIMESTAMPMS_HOL							// "1YYYY-MM-DD HH:MI:SS.000+01:00"
#define SIZ_ISO8601DATETIMESTAMPMS_HOL		(LEN_ISO8601DATETIMESTAMPMS_HOL + 1)
#endif

/*
	This is a horrible date/time format. Although it should be banned from this planet, it is
	widely used in webservers. See for instance https://en.wikipedia.org/wiki/Common_Log_Format .

	"[10/Oct/2000:13:55:36 -0700]"
*/
#ifndef LEN_NCSA_COMMON_LOG_DATETIME							// "[10/Oct/2000:13:55:36 -0700]"
#define LEN_NCSA_COMMON_LOG_DATETIME		(28)
#endif
#ifndef SIZ_NCSA_COMMON_LOG_DATETIME							// "[10/Oct/2000:13:55:36 -0700]"
#define SIZ_NCSA_COMMON_LOG_DATETIME		(LEN_NCSA_COMMON_LOG_DATETIME + 1)
#endif

#ifndef NUM_MS_IN_SECOND
#define NUM_MS_IN_SECOND					(1000)
#endif
#ifndef NUM_MS_IN_MINUTE
#define NUM_MS_IN_MINUTE					(60 * NUM_MS_IN_SECOND)
#endif
#ifndef NUM_MS_IN_HOUR
#define NUM_MS_IN_HOUR						(60 * NUM_MS_IN_MINUTE)
#endif
#ifndef NUM_MS_IN_DAY
#define NUM_MS_IN_DAY						(24 * NUM_MS_IN_HOUR)
#endif

// Android.
#ifdef OS_IS_ANDROID
	#include <sys/types.h>
	#include <sys/time.h>
    struct timeb
    {
        time_t         time;
        unsigned short millitm;
        short          timezone;
        short          dstflag;
    };
	//#include <sys/timeb.h>
	#include <time.h>
#endif

// IOS.
#ifdef OS_IS_IOS
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <time.h>
#endif

// Linux.
#ifdef OS_IS_LINUX
    #include <sys/types.h>
	#include <sys/timeb.h>
    #include <sys/time.h>
    #include <time.h>
#endif

// OSX.
#ifdef OS_IS_OSX
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <time.h>
#endif

// Unix.
#ifdef OS_IS_UNIX
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <time.h>
#endif

// Windows.
#ifdef OS_IS_WINDOWS
	#include <time.h>
	#include <sys/timeb.h>
	// Windows doesn't know gmtime_r () but it has gmtime_s () with swapped parameters.
	#define gmtime_r(a,b)		gmtime_s(b, a)
	#define localtime_r(a,b)	localtime_s(b, a)
	#define timeb				_timeb
	// Note that ftime () is actually deprecated on POSIX.
	#define ftime(t)			_ftime(t)
#endif

/*
	Android doesn't seem to support ftime (), at least not all versions.
*/
#ifdef OS_IS_ANDROID
	#ifndef HAVE_ANDROID_FTIME
		int ftime (struct timeb *tb);
		#define HAVE_ANDROID_FTIME
		#define BUILD_ANDROID_FTIME_HERE
	#endif
#endif

EXTERN_C_BEGIN

/*
	Our representation of a timestamp. Experimental.
	
	The timestamp is either the local time containing an offset to UTC
	or the time in UTC. When one of the offset bits is set (1) the time
	is assumed to be a local time containing an offset and converted
	to UTC whenever UTC is required.
	If no offset is given (bit 0...7 cleared) the time is assumed to 
	be in UTC and converted whenever the local time is required.
	
	The size of a UBF_TIMESTAMP is 64 bit (uint64_t). A value of 0
	is identical to no time. A value of (uint64_t) -1 denotes infinity.

	Unit	Values required	-> ~ 2^?		~  n bits
	-------------------------------------------------
	Year	2000..3023		-> ~ 1024		~ 10 bits
	Month	1..12			-> ~ 16			~  4 bits
	Day		1..31			-> ~ 32			~  5 bits
	Hour	0..23			-> ~ 32			~  5 bits
	Minute	0..59			-> ~ 64			~  6 bits
	Second	0..59			-> ~ 64			~  6 bits
	ms		0..999			-> ~ 1024		~ 10 bits
	us		0..999			-> ~ 1024		~ 10 bits
	ns		0..999			-> ~ 1024		~ 10 bits
	Offset	0..14			-> ~ 16			~  4 bits

	Bit reference starting from 2021-01-01:
	---------------------------------------
	
    6666555555555544444444443333333333222222222211111111110000000000
    3210987654321098765432109876543210987654321098765432109876543210
    I        ||     I               I               I           |  I
    I       I||     I       I       I       I       I       I   |  I
    7654321076543210765432107654321076543210765432107654321076543210
             ||	                        |         |         |   |  x	unused 
             ||                         |         9876543210|   |		us
             ||	                        9876543210..........|...|...	ms
             ||	                  543210....................|...|...	s
             ||	  	        543210..........................|...|...	min
             ||	  	   43210................................|...|...	h
             ||	  43210.....................................|...|...	day
             |3210..........................................|...|...	month
    9876543210..............................................|...|...	year
                                                            3210|||.	UTC offset in hours
                                                                0||.	1: UTC offset is negative
                                                                 ||.	0: UTC offset is positive 
                                                                 0|.	1: UTC offset + 30 minutes
                                                                  |.	0: UTC offset unchanged
                                                                  0.	1: UTC offset + 15 minutes
                                                                        0: UTC offset unchanged
    
	Microseconds (us) can have a value from 0 to 999. In binary, this is from
	0000000000 (  0 decimal) to 
	1111100111 (999 decimal).
	The same applies to milliseconds (ms).
	
	According to https://en.wikipedia.org/wiki/List_of_UTC_time_offsets, time offsets
	range from -12 (west) to 14 (east). Most timezones are at full hours but there are
	some exceptions. Our structure can add 30 and/or 15 minutes if required. This covers
	the 15, 30, and 45 minutes exceptions.
*/
#ifndef HAVE_UBF_TIMESTAMP
	typedef	uint64_t				UBF_TIMESTAMP;				// A timestamp in host byte order.
	typedef uint64_t				UBF_TIMESTAMPN;				// A timestamp in network order.
	#define is_infinity_UBF_TIMESTAMP(pt)				\
				((uint64_t) -1 == *(pt))
	#define IS_INFINITY_UBF_TIMESTAMP(t)				\
				((uint64_t) -1 == t))
	typedef struct subf_timestruct
	{
		unsigned int	uYear;									// Year: 0 == 2000, 1023 = 3023.
		unsigned int	uMonth;									// Month: 1..12.
		unsigned int	uDay;									// Day: 1..31.
		unsigned int	uHour;									// Hour: 0..24.
		unsigned int	uMinute;								// Minute: 0..59.
		unsigned int	uSecond;								// Second: 0..59.
		unsigned int	uMillisecond;							// Millisecond: 0..999.
		unsigned int	uMicrosecond;							// Microsecond: 0..999.
		unsigned int	uOffsetHours;							// The offset to UTC in hours.
		unsigned int	uOffsetMinutes;							// Additional minutes to UTC offset.
		bool			bOffsetNegative;						// UTC offset is negative.
	} SUBF_TIMESTRUCT;
	#define HAVE_UBF_TIMESTAMP
#endif

/*
	HasTimeOffset_UBF_TIMESTAMP
	HasNoTimeOffset_UBF_TIMESTAMP
	IsUTC_UBF_TIMESTAMP
	IsNotUTC_UBF_TIMESTAMP
	
	Macros to determine whether a UBF_TIMESTAMP is a UTC timestamp or a local time.
*/
#define HasTimeOffset_UBF_TIMESTAMP(ut)					\
	(ut & 0x7F)
#define HasNoTimeOffset_UBF_TIMESTAMP(ut)				\
	(0 == ut & 0x7F)
#define IsUTC_UBF_TIMESTAMP(ut)							\
	(0 == ut & 0x7F)
#define IsNotUTC_UBF_TIMESTAMP(ut)						\
	(ut & 0x7F)

/*
	IsUTC_SUBF_TIMESTRUCT
	IsNotUTC_SUBF_TIMESTRUCT
	
	Macros to determine whether a SUBF_TIMESTRUCT is in UTC or local time.
*/
#define IsUTC_SUBF_TIMESTRUCT(ts)						\
	((ts)->uOffsetHours || (ts)->uOffsetMinutes)
#define IsNotUTC_SUBF_TIMESTRUCT(ts)					\
	(!((ts)->uOffsetHours || (ts)->uOffsetMinutes))
	
/*
	UBF_TIMESTAMP_OFFSET_BITS

	Returns the bits that need to be set in a UBF_TIMESTAMP date/time stamp for the time
	offset in the SUBF_TIMESTRUCT structure ts points to.
*/
UBF_TIMESTAMP UBF_TIMESTAMP_OFFSET_BITS (SUBF_TIMESTRUCT *ts);

/*
	Macros to obtain the bits required to set in a UBF_TIMESTAMP date/time stamp for the
	different values from a SUBF_TIMESTRUCT structure.
*/
#define UBF_TIMESTAMP_MICROSECOND_BITS(ts)				\
	(((UBF_TIMESTAMP) (ts)->uMicrosecond) << 8)

#define UBF_TIMESTAMP_MILLISECOND_BITS(ts)				\
	(((UBF_TIMESTAMP) (ts)->uMillisecond) << 18)

#define UBF_TIMESTAMP_SECOND_BITS(ts)					\
	(((UBF_TIMESTAMP) (ts)->uSecond) << 28)

#define UBF_TIMESTAMP_MINUTE_BITS(ts)					\
	(((UBF_TIMESTAMP) (ts)->uMinute) << 34)

#define UBF_TIMESTAMP_HOUR_BITS(ts)						\
	(((UBF_TIMESTAMP) (ts)->uHour) << 40)

#define UBF_TIMESTAMP_DAY_BITS(ts)						\
	(((UBF_TIMESTAMP) (ts)->uDay) << 45)

#define UBF_TIMESTAMP_MONTH_BITS(ts)					\
	(((UBF_TIMESTAMP) (ts)->uMonth) << 50)

#define UBF_TIMESTAMP_YEAR_BITS(ts)						\
	((((UBF_TIMESTAMP) (ts)->uYear) - 2000) << 54)

/*
	SET_UBF_TIMESTAMP_OFFSET_BITS

	This macro clears the UBF_TIMESTAMP first. It must therefore be called before
	any of the other SET_UBF_TIMESTAMP_ macros below.

	UBF_TIMESTAMP		uts
	offset hours		oh
	offset minutes		om
	bool				bn		(offset negative yes/no)

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
#define SET_UBF_TIMESTAMP_OFFSET_BITS(uts, oh, om, bn)	\
	(uts) = oh;											\
	(uts) <<= 4;										\
	(uts) |= bn ? 0x08 : 0;								\
	switch (om)											\
	{													\
		case 0:											\
			break;										\
		case 15:										\
			(uts) |= 0x02;								\
			break;										\
		case 30:										\
			(uts) |= 0x04;								\
			break;										\
		case 45:										\
			(uts) |= 0x06;								\
			break;										\
		default:										\
			ubf_assert (false);							\
	}

/*
	Macros to set the bits required to for a UBF_TIMESTAMP date/time stamp for the
	different values.

	The macro SET_UBF_TIMESTAMP_OFFSET_BITS() above must be called first.
*/
#define SET_UBF_TIMESTAMP_MICROSECOND_BITS(us)			\
	((UBF_TIMESTAMP) (us) << 8)

#define SET_UBF_TIMESTAMP_MILLISECOND_BITS(ms)			\
	((UBF_TIMESTAMP) (ms) << 18)

#define SET_UBF_TIMESTAMP_SECOND_BITS(s)				\
	((UBF_TIMESTAMP) (s) << 28)

#define SET_UBF_TIMESTAMP_MINUTE_BITS(mi)				\
	((UBF_TIMESTAMP) (mi) << 34)

#define SET_UBF_TIMESTAMP_HOUR_BITS(h)					\
	((UBF_TIMESTAMP) (h) << 40)

#define SET_UBF_TIMESTAMP_DAY_BITS(d)					\
	((UBF_TIMESTAMP) (d) << 45)

#define SET_UBF_TIMESTAMP_MONTH_BITS(mo)				\
	((UBF_TIMESTAMP) (mo) << 50)

#define SET_UBF_TIMESTAMP_YEAR_BITS(y)					\
	(((UBF_TIMESTAMP) (y) - 2000) << 54)

/*
	Macros to extract the binary date in a UBF_TIMESTAMP.
*/
#define UBF_TIMESTAMP_OFFSETHOURS(u)					\
	(((u) & 0xF0) >> 4)											// 1111 0000

/*
	0000		0
	0010		15
	0100		30
	0110		45
*/
#define UBF_TIMESTAMP_OFFSETMINUTES(u)					\
	(((u) & 0x04) && ((u) & 0x02)) ? 45 : ((u) & 0x04) ? 30 : ((u) & 0x02) ? 15 : 0

#define UBF_TIMESTAMP_OFFSETNEGATIVE(u)					\
	((u) & 0x08)

#define UBF_TIMESTAMP_MICROSECOND(u)					\
	(((u) >> 8) & 0x3FF)

#define UBF_TIMESTAMP_MILLISECOND(u)					\
	(((u) >> 18) & 0x3FF)

#define UBF_TIMESTAMP_SECOND(u)							\
	(((u) >> 28) & 0x3F)

#define UBF_TIMESTAMP_MINUTE(u)							\
	(((u) >> 34) & 0x3F)

#define UBF_TIMESTAMP_HOUR(u)							\
	(((u) >> 40) & 0x1F)

#define UBF_TIMESTAMP_DAY(u)							\
	(((u) >> 45) & 0x1F)

#define UBF_TIMESTAMP_MONTH(u)							\
	(((u) >> 50) & 0x0F)

#define UBF_TIMESTAMP_YEAR(u)							\
	((((u) >> 54) & 0x3FF) + 2000)

/*
	Preservation bit masks.
*/
#define UBF_TIMESTAMP_KEEP_OFFSET_BITS				(0xF7)
#define UBF_TIMESTAMP_KEEP_FROM_SECOND_BITS			(0xFFFFFFFFF0000000)
#define UBF_TIMESTAMP_KEEP_FROM_MINUTE_BITS			(0xFFFFFFFC00000000)
#define UBF_TIMESTAMP_KEEP_FROM_HOUR_BITS			(0xFFFFFF0000000000)
#define UBF_TIMESTAMP_KEEP_FROM_DAY_BITS			(0xFFFFE00000000000)
#define UBF_TIMESTAMP_KEEP_FROM_MONTH_BITS			(0xFFFC000000000000)
#define UBF_TIMESTAMP_KEEP_FROM_YEAR_BITS			(0xFFC0000000000000)

/*
	SUBF_TIMESTRUCT_to_UBF_TIMESTAMP
	UBF_TIMESTAMP_from_UBF_TIMESTRUCT

	Converts the SUBF_TIMESTRUCT ts points to into the UBF_TIMESTAMP t points
	to. Since a UBF_TIMESTAMP always references an offset to UTC, debug versions
	abort when the member bLocalTime of the SUBF_TIMESTRUCT ts points to is true.

	The macro UBF_TIMESTAMP_from_SUBF_TIMESTRUCT() is provided for parameter
	consistency with its name, which is function (target, source).
*/
void SUBF_TIMESTRUCT_to_UBF_TIMESTAMP (UBF_TIMESTAMP * t, SUBF_TIMESTRUCT * ts);

#define UBF_TIMESTAMP_from_SUBF_TIMESTRUCT(ut, ts)		\
			SUBF_TIMESTRUCT_to_UBF_TIMESTAMP ((ut), (ts))

/*
	GetSystemTime_SUBF_TIMESTRUCT
	
	Returns the system time as a SUBF_TIMESTRUCT. The system time is in UTC.
	The returned SUBF_TIMESTRUCT does not contain a time offset.
*/
void GetSystemTime_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts);

/*
	GetSystemTime_UBF_TIMESTAMP

	Returns the system time as a UBF_TIMESTAMP. The system time is in UTC.
	The returned SUBF_TIMESTAMP contains no time offset.
	
	The function calls GetSystemTime_SUBF_TIMESTRUCT () to obtain the system time,
	then calls SUBF_TIMESTRUCT_to_UBF_TIMESTAMP () on the obtained time.
*/
void GetSystemTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut);

/*
	GETSYSTEMTIME_UBF_TIMESTAMP

	Wrapper macro for GetSystemTime_UBF_TIMESTAMP () to reference the
	UBF_TIMESTAMP parameter t.
*/
#define GETSYSTEMTIME_UBF_TIMESTAMP(t)					\
	GetSystemTime_UBF_TIMESTAMP (&(t))

/*
	GetSystemTimeAsUBF_TIMESTAMP

	Returns the system time as a UBF_TIMESTAMP. The system time is in UTC.
	The returned SUBF_TIMESTAMP contains no time offset.
	
	The function calls GetSystemTime_SUBF_TIMESTRUCT () to obtain the system time,
	then calls SUBF_TIMESTRUCT_to_UBF_TIMESTAMP () on the obtained time.
*/
UBF_TIMESTAMP GetSystemTimeAsUBF_TIMESTAMP (void);

/*
	GetLocalTime_SUBF_TIMESTRUCT
	
	Returns the local time as a SUBF_TIMESTRUCT. The local time is the system
	time (UTC) with an offset.
	
	Local time - offset = system time
*/
#ifdef DEBUG
	void GetLocalTime_SUBF_TIMESTRUCT (SUBF_TIMESTRUCT *pts);
#else
	// The POSIX version is twice as fast here as the Windows
	//	version in debug versions and three times as fast in
	//	release builds.
	void GetLocalTime_SUBF_TIMESTRUCT_psx (SUBF_TIMESTRUCT *pts);

	#define GetLocalTime_SUBF_TIMESTRUCT(p)				\
		GetLocalTime_SUBF_TIMESTRUCT_psx (pts)
#endif

/*
	GetLocalTime_UBF_TIMESTAMP

	Returns the local time as a UBF_TIMESTAMP. The timestamp contains the offset
	to UTC.
	
	Local time - offset = system time
*/
void GetLocalTime_UBF_TIMESTAMP (UBF_TIMESTAMP *ut);

/*
	GETLOCALTIME_UBF_TIMESTAMP

	Wrapper macro for GETLOCALTIME_UBF_TIMESTAMP () to reference the
	UBF_TIMESTAMP parameter t.
*/
#define GETLOCALTIME_UBF_TIMESTAMP(t)					\
	GetLocalTime_UBF_TIMESTAMP (&(t))

/*
	SystemTime_UBF_TIMESTAMP

	Returns the system time as a UBF_TIMESTAMP. The system time is in UTC.
	The returned SUBF_TIMESTAMP contains no time offset.
*/
UBF_TIMESTAMP SystemTime_UBF_TIMESTAMP (void)
;

/*
	LocalTime_UBF_TIMESTAMP

	Returns the local time as a UBF_TIMESTAMP. The local time is the system
	time (UTC) with an offset.
	
	Local time - offset = system time
*/
UBF_TIMESTAMP LocalTime_UBF_TIMESTAMP (void)
;


EXTERN_C_END

#endif															// End of U_UBF_TIME_H_INCLUDED.
