/****************************************************************************************

	File:		platform.h
	Why:		Determines the target OS (platform) and build type;
				also includes OS specific headers.
	OS:			-
	Author:		Thomas
	Created:	2024-07-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-07-10	Thomas			Created.

****************************************************************************************/

/*
	The OS_IS_ definitions provide the target operating system, for instance OS_IS_LINUX.
	The PLATFORM_IS_ definitions provide the platform, for instance PLATFORM_IS_POSIX or
	PLATFORM_IS_WINDOWS.
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

#ifndef U_PLATFORM_H
#define U_PLATFORM_H

#include <limits.h>
#include <inttypes.h>

// Detect AIX.
#ifdef _AIX
	#ifndef OS_IS_AIX
	#define OS_IS_AIX
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Android.
#ifdef __ANDROID__
	#ifndef OS_IS_ANDROID
	#define OS_IS_ANDROID
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Linux.
#ifdef __gnu_linux__
	#ifndef OS_IS_LINUX
	#define OS_IS_LINUX
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Apple OSes.
//	See for instance
//	https://github.com/xybp888/iOS-SDKs/blob/master/iPhoneOS13.0.sdk/usr/include/TargetConditionals.h .
#if defined (__APPLE__) && defined (__MACH__)
	#include <TargetConditionals.h>
	#if defined (TARGET_OS_IPHONE) && defined (TARGET_OS_SIMULATOR) == 1
		/// iOS in simulator
		#ifndef OS_IS_IOS
		#define OS_IS_IOS
		#endif
	#elif TARGET_OS_IPHONE == 1
		// iOS on iPhone, iPad, etc.
		#ifndef OS_IS_IOS
		#define OS_IS_IOS
		#endif
	#elif TARGET_OS_MAC == 1
		// OSX.
		#ifndef OS_IS_OSX
		#define OS_IS_OSX
		#endif
	#endif
	#ifndef OS_IS_MACOS
	#define OS_IS_MACOS
	#endif
	#ifndef PLATFORM_IS_POSIX
	#define PLATFORM_IS_POSIX
	#endif
#endif

// Detect Windows.
#ifdef _WIN32
	#ifndef OS_IS_WINDOWS
	#define OS_IS_WINDOWS
	#endif
	#ifndef PLATFORM_IS_WINDOWS
	#define PLATFORM_IS_WINDOWS
	#endif
	#include <crtdbg.h>
#endif

#ifdef QT_DEBUG
	#ifndef _DEBUG
	#define _DEBUG
	#endif
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif

#ifdef DEBUG
	#ifndef _DEBUG
	#define _DEBUG
	#endif
#endif

#ifdef _DEBUG
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif

#if defined (__GNUC__)
	#ifdef NDEBUG
		#ifdef _DEBUG
		#undef _DEBUG
		#endif
		#ifdef DEBUG
		#undef DEBUG
		#endif
	#else
		#ifndef _DEBUG
		#define _DEBUG
		#endif
		#ifndef DEBUG
		#define DEBUG
		#endif
	#endif
#endif

// The Windows _ASSERT() macro.
//	See https://msdn.microsoft.com/en-us/library/ezb1wyez.aspx on how to use these macros.
//	The Wikipedia article https://en.wikipedia.org/wiki/Assert.h explains the Unix/Linux version.
#ifndef _ASSERT
	#ifdef DEBUG
		#define _ASSERT(x) assert(x)
	#else
		#define _ASSERT(ignore) ((void)0)
	#endif
#endif
#ifndef ASSERT
	#ifdef DEBUG
		#define ASSERT(x) _ASSERT(x)
	#else
		#define ASSERT(ignore) ((void)0)
	#endif
#endif

// We expect that CHAR_BIT is 8.
#if CHAR_BIT != 8
#   error Platforms with CHAR_BIT != 8 are not supported
#endif

// The directory separator.
#ifndef UBF_DIR_SEP
	#ifndef UBF_WIN_DIR_SEP
		#define UBF_WIN_DIR_SEP			'\\'
		#define UBF_WIN_DIR_SEP_STR		"\\"
	#endif
	#ifndef UBF_PSX_DIR_SEP
		#define UBF_PSX_DIR_SEP			'/'
		#define UBF_PSX_DIR_SEP_STR		"/"
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		#define UBF_DIR_SEP				UBF_WIN_DIR_SEP
		#define UBF_WRONG_DIR_SEP		UBF_PSX_DIR_SEP
		#define UBF_DIR_SEP_STR			UBF_WIN_DIR_SEP_STR
		#define UBF_WRONG_DIR_SEP_STR	UBF_PSX_DIR_SEP_STR
	#else
		#define UBF_DIR_SEP				UBF_PSX_DIR_SEP
		#define UBF_WRONG_DIR_SEP		UBF_WIN_DIR_SEP
		#define UBF_DIR_SEP_STR			UBF_PSX_DIR_SEP_STR
		#define UBF_WRONG_DIR_SEP_STR	UBF_WIN_DIR_SEP_STR
	#endif
#endif

// NUL character.
#ifndef ASCII_NUL
#define ASCII_NUL			'\0'
#endif
// End of Text.
#ifndef ASCII_ETX
#define ASCII_ETX			'\3'
#endif
// End of Transmission.
#ifndef ASCII_EOT
#define ASCII_EOT			'\4'
#endif
// TAB (tabulator).
#ifndef ASCII_TAB
#define ASCII_TAB			'\x09'
#endif
#ifndef ASCII_VT
#define ASCII_VT			'\x0B'
#endif
#ifndef ASCII_CR
#define ASCII_CR			'\x0D'
#endif
#ifndef ASCII_CR_STR
#define ASCII_CR_STR		"\x0D"
#endif
#ifndef ASCII_LF
#define ASCII_LF			'\x0A'
#endif
#ifndef ASCII_LF_STR
#define ASCII_LF_STR		"\x0A"
#endif
#ifndef ASCII_CRLF_STR
#define ASCII_CRLF_STR		"\x0D\x0A"
#endif
#ifndef ASCII_CR_VAL
#define ASCII_CR_VAL		(0x0D)
#endif
#ifndef ASCII_LF_VAL
#define ASCII_LF_VAL		(0x0A)
#endif
// End of File, CTRL-Z or SUB.
#ifndef ASCII_SUB
#define ASCII_SUB			'\x1A'
#endif
#ifndef ASCII_SPC
#define ASCII_SPC			'\x20'
#endif
#ifndef ASCII_SLASH
#define ASCII_SLASH			'/'
#endif
#ifndef ASCII_BACKSLASH
#define ASCII_BACKSLASH		'\\'
#endif

// Wrapper macro for function isdigit (). Note that isdigit () on some platforms
//	(for instance Windows) aborts if the character is outside a uint8_t range. That's why
//	we're casting it to an unsigned char.
//	See
//	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/isdigit-iswdigit-isdigit-l-iswdigit-l?view=vs-2019 .
#ifdef __cplusplus
	#define ubf_isdigit(c)								\
				(isdigit (static_cast<unsigned char>(c)))
#else
	#define ubf_isdigit(c)								\
				(isdigit ((unsigned char) c))
#endif
// Wrapper macro for function isalpha (). Note that isalpha () on some platforms
//	(for instance Windows) aborts if the character is outside a uint8_t range. That's why
//	we're casting it to an unsigned char.
#ifdef __cplusplus
	#define ubf_isalpha(c)								\
				(isalpha (static_cast<unsigned char>(c)))
#else
	#define ubf_isalpha(c)								\
				(isalpha ((unsigned char) c))
#endif

// Test for lower and upper case letters.
#define ubf_is_lower_case_letter(c)						\
	((unsigned char) c > 'a' - 1 && (unsigned char) c < 'z' + 1)
#define ubf_is_upper_case_letter(c)						\
	((unsigned char) c > 'A' - 1 && (unsigned char) c < 'Z' + 1)

/*
	ubf_isdirseparator
*/
#ifdef __cplusplus
	#define ubf_isdirseparator(c)						\
			(											\
					UBF_WIN_DIR_SEP == (c)				\
				||	UBF_PSX_DIR_SEP == (c)				\
			)
#else
	#define ubf_isdirseparator(c)						\
			(											\
					UBF_WIN_DIR_SEP == (c)				\
				||	UBF_PSX_DIR_SEP == (c)				\
			)
#endif

// The type ssize_t. See https://github.com/vlm/asn1c/issues/159 .
#ifdef _MSC_VER
	#ifndef HAVE_SSIZE_T
	#define HAVE_SSIZE_T
		#include <basetsd.h>
		typedef SSIZE_T ssize_t;
	#endif
#endif

// Typical Windows types.
#ifndef OS_IS_WINDOWS
	#ifndef ULONGLONG
	#define ULONGLONG	uint64_t
	#endif
	#ifndef LONGLONG
	#define LONGLONG	int64_t
	#endif
	#ifndef DWORD
	#define DWORD		uint32_t
	#endif
	#ifndef WORD
	#define WORD		uint16_t
	#endif
	#ifndef BYTE
	#define BYTE		uint8_t
	#endif
	
	#ifndef _FILETIME_
	typedef struct _FILETIME {
		DWORD dwLowDateTime;
		DWORD dwHighDateTime;
	} FILETIME, *PFILETIME, *LPFILETIME;
	#define _FILETIME_
	#endif
#endif

// The LARGE_INTEGER type. This has been taken from winnt.h.
#ifndef OS_IS_WINDOWS
	typedef long LONG;
	#if defined(MIDL_PASS)
	typedef struct _LARGE_INTEGER {
	#else // MIDL_PASS
	typedef union _LARGE_INTEGER {
		struct
		{
			DWORD LowPart;
			LONG HighPart;
		} DUMMYSTRUCTNAME;
		struct
		{
			DWORD LowPart;
			LONG HighPart;
		} u;
	#endif //MIDL_PASS
		LONGLONG QuadPart;
	} LARGE_INTEGER;
	// See https://msdn.microsoft.com/en-us/library/windows/desktop/aa383742(v=vs.85).aspx .
	typedef union _ULARGE_INTEGER
	{
		struct
		{
			DWORD LowPart;
			DWORD HighPart;
		} DUMMYSTRUCTNAME;
		struct
		{
			DWORD LowPart;
			DWORD HighPart;
		} u;
		ULONGLONG QuadPart;
	} ULARGE_INTEGER, *PULARGE_INTEGER;
#endif

#if defined (PLATFORM_IS_WINDOWS)
	#define Sleep_s(s)			Sleep (s * 1000)
	#define Sleep_ms(mseconds)	Sleep (mseconds)
#elif defined (PLATFORM_IS_POSIX)
	#define Sleep_s(s)			sleep (s)
	// The function usleep () expects microseconds.
	#define Sleep_ms(ms)		usleep (ms * 1000)
	#define Sleep(ms)			usleep (ms * 1000)
#endif

#endif														// Of #ifndef U_PLATFORM_H.
