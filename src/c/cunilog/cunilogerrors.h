/****************************************************************************************

	File		cunilogerrors.h
	Why:		Cunilog return and error codes.
	OS:			C99
	Created:	2025-04-03

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-04-03	Thomas			Created.

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

#ifndef U_CUNILOGERRORS_H
#define U_CUNILOGERRORS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdbool.h>
	#include <inttypes.h>

	//

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		//#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		//#include "./../mem/ubfmem.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	#include <errno.h>
#endif

/*
	System error codes
*/

#if defined (PLATFORM_IS_WINDOWS)

	#define CUNILOG_SYSTEM_ERROR_SUCCESS			ERROR_SUCCESS
	#define CUNILOG_SYSTEM_ERROR_NOT_SUPPORTED		ERROR_NOT_SUPPORTED
	#define CUNILOG_SYSTEM_ERROR_BUFFER_OVERFLOW	ERROR_BUFFER_OVERFLOW

#elif defined (PLATFORM_IS_POSIX)

	#define CUNILOG_SYSTEM_ERROR_SUCCESS			(0)
	#define CUNILOG_SYSTEM_ERROR_NOT_SUPPORTED		ENOTSUP
	#define CUNILOG_SYSTEM_ERROR_BUFFER_OVERFLOW	EOVERFLOW

#elif

	#error Not supported

#endif

/*
	Cunilog error codes.
*/

/*
	Success/no error.
*/
#define CUNILOG_NO_ERROR							(0)

#define CUNILOG_ERROR_OPENING_LOGFILE				(1)
#define CUNILOG_ERROR_WRITING_LOGFILE				(2)
#define CUNILOG_ERROR_FLUSHING_LOGFILE				(3)

/*
	Mismatch between an absolute or relative path.
*/
#define CUNILOG_ERROR_ABS_OR_REL_PATH				(4)

// The base for a path could not be obtained.
#define CUNILOG_ERROR_PATH_BASE						(5)

// A heap allocation failed/out of memory error.
#define CUNILOG_ERROR_HEAP_ALLOCATION				(6)

#define CUNILOG_ERROR_SEMAPHORE						(7)
#define CUNILOG_ERROR_APPNAME						(8)
#define CUNILOG_ERROR_SEPARATE_LOGGING_THREAD		(9)
#define CUNILOG_ERROR_RENAMING_LOGFILE				(10)

#define CUNILOG_ERROR_FIRST_UNUSED_ERROR			(5000)

/*
	Error codes only used when CUNILOG_BUILD_WITH_TEST_ERRORCB
	defined.
*/
#define CUNILOG_ERROR_TEST_BEFORE_THRESHOLD_UPDATE		(CUNILOG_ERROR_FIRST_UNUSED_ERROR + 1)
#define CUNILOG_ERROR_TEST_AFTER_THRESHOLD_UPDATE		(CUNILOG_ERROR_FIRST_UNUSED_ERROR + 2)
#define CUNILOG_ERROR_TEST_BEFORE_REQUIRES_NEW_LOGFILE	(CUNILOG_ERROR_FIRST_UNUSED_ERROR + 3)
#define CUNILOG_ERROR_TEST_AFTER_REQUIRES_NEW_LOGFILE	(CUNILOG_ERROR_FIRST_UNUSED_ERROR + 4)
#define CUNILOG_ERROR_TEST_BEFORE_ROTATOR				(CUNILOG_ERROR_FIRST_UNUSED_ERROR + 5)
#define CUNILOG_ERROR_TEST_AFTER_ROTATOR				(CUNILOG_ERROR_FIRST_UNUSED_ERROR + 6)

EXTERN_C_BEGIN

/*
	CUNILOG_ERROR

					Windows								POSIX
	------------+-----------------------------------+------------------------------------
	Bit	 0...31	|	A DWORD containing a Windows	|	A 32 bit int containing a POSIX
				|	error code						|	error code
				|
				|	Use the macro CunilogSystemError() to obtain this error code.
				|
	------------+-----------------------------------+------------------------------------
	Bit 32...63	|	One of the CUNILOG_ constants above
				|	Use the macro CunilogCunilogError() to obtain it.
	------------+------------------------------------------------------------------------
	
*/
typedef uint64_t	CUNILOG_ERROR;


#define CunilogSystemError(err)							\
			((err) & 0x00000000FFFFFFFF)

#define CunilogCunilogError(err)							\
			(((err) >> 32) & 0x00000000FFFFFFFF)

/*
	SetCunilogError

	Macro to set a CUNILOG_ERROR variable.

	errvar		The name of the CUNILOG_ERROR variable that receives the final
				error code, consisting of a Cunilog error code and a system error code.
	cerr		One of the CUNILOG_ERROR_ constants above.
	serr		System error code. This is either a DWORD on Windows or an int32_t on
				POSIX.
*/
#define SetCunilogError(put, cerr, serr)					\
	do													\
	{													\
		((put)->error) = (CUNILOG_ERROR)(cerr) << 32;		\
		((put)->error) += (unsigned)(serr);				\
	} while (0)

/*
	SetCunilogSystemError

	Same as SetCunilogError() but obtains the system error implicitely.	
*/
#if defined (PLATFORM_IS_WINDOWS)

	#define SetCunilogSystemError(put, cerr)				\
	do													\
	{													\
		((put)->error) = (CUNILOG_ERROR)(cerr) << 32;		\
		((put)->error) += (unsigned) GetLastError ();		\
	} while (0)
	
#elif defined (PLATFORM_IS_POSIX)

	#define SetCunilogSystemError(put, cerr)				\
	do													\
	{													\
		((put)->error) = (CUNILOG_ERROR)(cerr) << 32;		\
		((put)->error) += (unsigned) errno;				\
	} while (0)
	
#elif

	#error Not supported

#endif

#define ResetCunilogError(put)							\
			SetCunilogError ((put), CUNILOG_NO_ERROR, CUNILOG_SYSTEM_ERROR_SUCCESS)

EXTERN_C_END

#endif														// Of #ifndef U_CUNILOGERRORS_H.
