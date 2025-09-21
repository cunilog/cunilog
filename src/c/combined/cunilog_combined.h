/****************************************************************************************

	File:		head.h
	Why:		Provides the head of the combined cunilog.h header file.
	OS:			C99.
	Author:		Thomas
	Created:	2024-08-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-01	Thomas			Created.

****************************************************************************************/

#ifndef CUNILOG_USE_COMBINED_MODULE
#define CUNILOG_USE_COMBINED_MODULE
#endif

/*
	These definitions are only required for Windows but defining them
	unconditionally won't do any harm.
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef HAVE_STRWILDCARDS
#define HAVE_STRWILDCARDS
#endif
#ifndef HAVE_SHELLAPI
#define HAVE_SHELLAPI
#endif
#ifndef HAVE_USERENV
#define HAVE_USERENV
#endif
#ifndef HAVE_MEMBUF
#define HAVE_MEMBUF
#endif

/*
	Our include guard.
	The #endif is in bottom.h.
*/
#ifndef CUNILOG_COMBINED_INCLUDED
#define CUNILOG_COMBINED_INCLUDED
/****************************************************************************************

	Project:	cunilog
	File:		cunilogversion.h
	Why:		
	OS:			
	Autor:		Thomas
	Created:	2024-10-16
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-16	Thomas			Created.

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

#ifndef HAVE_CUNILOG_VERSION__H
#define HAVE_CUNILOG_VERSION__H

// Some constants.
#define CUNILOG_PROJECT_NAME	"cunilog"					// Name of the project.
#define CUNILOG_PROGRAM_NAME	"cunilog"					// The application's name.
#define CUNILOG_PROGRAM_EXE		CUNILOG_PROGRAM_NAME ".exe"
#define CUNILOG_PROGRAM_LIB		CUNILOG_PROGRAM_NAME ".lib"
#define CUNILOG_PROGRAM_DESCR	"Logging utility"			// Its description.
#define CUNILOG_PROGRAM_COMPANY "-"							// Company.
#define CUNILOG_PROGRAM_AUTHOR	"Thomas"					// Author.
#define CUNILOG_PROGRAM_EMAIL	"-"							// Email.

// Version numbers.
#define CUNILOG_VERSION_MAJOR	1							// Major version.
#define CUNILOG_VERSION_MINOR	0							// Minor version.
#define CUNILOG_VERSION_SUB		2							// Subversion for maintenance.
#define CUNILOG_VERSION_BUILD	9							// Build number.
#define CUNILOG_VERSION_YEAR	"2025"						// Copyright year.

#define VERSION_URL		"https://github.com/cunilog"

// Convert constants to strings using ANSI stringify operator.
#define STRINGIFY(x) #x

// Convert constants to strings while expanding macros.
//	This is actually a helper define to force macro expansion.
#define EXPANDSTRINGIFY(x) STRINGIFY(x)

// Version string for display on startup.
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR)
#if (CUNILOG_VERSION_SUB != 0)
#undef CUNILOG_VERSION_STRING
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) "." EXPANDSTRINGIFY(CUNILOG_VERSION_SUB)
#endif
#if (CUNILOG_VERSION_BUILD != 0)
#undef CUNILOG_VERSION_STRING
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) "." EXPANDSTRINGIFY(CUNILOG_VERSION_SUB) \
	"." EXPANDSTRINGIFY(CUNILOG_VERSION_BUILD)
#endif
// Version string for executable version information.
#define CUNILOG_VERSION_RESOURCE	EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) ", " \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) ", " EXPANDSTRINGIFY(CUNILOG_VERSION_SUB) \
	", " EXPANDSTRINGIFY(CUNILOG_VERSION_BUILD)

// Copyright notice in executable version information.
#define CUNILOG_VERSION_COPYRIGHT	"Copyright (C) " CUNILOG_VERSION_YEAR \
	", " CUNILOG_PROGRAM_AUTHOR

#endif															// Of #ifndef HAVE_CUNILOG_VERSION__H.
/****************************************************************************************

	File:		cunilogdefs.h
	Why:		Required definitions for Cunilog to build.
	OS:			-
	Author:		Thomas
	Created:	2024-11-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-06	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The definitions in this module are required for Cunilog to build.
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

#ifndef U_CUNILOGDEFS_H
#define U_CUNILOGDEFS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

/*
	Suppresses the MSVC warnings for strcpy (), memcpy (), etc.
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	//#warning _CRT_SECURE_NO_WARNINGS should be defined for Cunilog to build.
	#endif
#endif

/*
	Wildcard support
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef HAVE_STRWILDCARDS
	#define HAVE_STRWILDCARDS
	#endif
#endif

/*
	For MoveToRecycleBinU8 ().
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef HAVE_SHELLAPI
	#define HAVE_SHELLAPI
	#endif
#endif

/*
	For GetDefaultUserProfileDirectoryU8 ().
*/
#ifdef PLATFORM_IS_WINDOWS
	#ifndef HAVE_USERENV
	#define HAVE_USERENV
	#endif
#endif


#endif														// Of #ifndef U_CUNILOGDEFS_H.
/****************************************************************************************

	File		externC.h
	Why:		Macros for the "extern C" declarations.
	OS:			-
	Created:	2020-12-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-11	Thomas			Created. Copied from ubf_type_definitions.h.
2024-07-09	Thomas			Master version is now in folder cunilog.

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

#ifndef EXTERN_C_H
#define EXTERN_C_H

/*
	BEGIN_C_DECLS		END_C_DECLS
	EXTERN_C_BEGIN		EXTERN_C_END

	Lets C++ compilers know that this is C, not C++.

	Idea and original version nicked from
	https://code.woboq.org/userspace/glibc/misc/sys/cdefs.h.html#117 .

	Leading double underscores removed to get rid of compiler warnings.
	Two different flavours can be used: BEGIN_C_DECLS and END_C_DECLS,
	and EXTERN_C_BEGIN and EXTERN_C_END.
*/
// BEGIN_C_DECLS and END_C_DECLS.
#ifdef	__cplusplus
	#ifndef BEGIN_C_DECLS
	#define BEGIN_C_DECLS        extern "C"	{
	#endif
	#ifndef END_C_DECLS
	#define END_C_DECLS						}
	#endif
#else
	#ifndef BEGIN_C_DECLS
	#define BEGIN_C_DECLS
	#endif
	#ifndef END_C_DECLS
	#define END_C_DECLS
	#endif
#endif
// EXTERN_C_BEGIN and EXTERN_C_END.
#ifdef	__cplusplus
	#ifndef EXTERN_C_BEGIN
	#define EXTERN_C_BEGIN       extern "C"	{
	#endif
	#ifndef EXTERN_C_END
	#define EXTERN_C_END					}
	#endif
#else
	#ifndef EXTERN_C_BEGIN
	#define EXTERN_C_BEGIN
	#endif
	#ifndef EXTERN_C_END
	#define EXTERN_C_END
	#endif
#endif

#endif														// Of #ifndef EXTERN_C_H.
/****************************************************************************************

	File		DLLimport.h
	Why:		The definition for DLL imports for Windows
	OS:			Windows
	Created:	2025-02-20

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-20	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

#ifndef U_DLL_IMPORT_H
#define U_DLL_IMPORT_H

#if defined (_WIN32) && defined (CUNILOG_IMPORT_FROM_DLL)
	#define CUNILOG_DLL_IMPORT		__declspec(dllimport)
#else
	#define CUNILOG_DLL_IMPORT
#endif

#endif														// Of #ifndef U_DLL_IMPORT_H.
/****************************************************************************************

	File		functionptrtpydef.h
	Why:		Helper macros to create typedefs for function pointers.
	OS:			Windows
	Created:	2025-02-20

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-20	Thomas			Created.

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

#ifndef U_FUNCTIONPTRTPYDEF_H
#define U_FUNCTIONPTRTPYDEF_H

/*
	Prefix and postfix of function pointer typedefs when created with the macros
	TYPEDEF_FNCT_PTR() and TYPEDEF_FNCT_PTR_ARGS().
*/
#ifndef CUL_FNCTS_POINTER_PREFIX
#define CUL_FNCTS_POINTER_PREFIX	fncpt_
#endif
#ifndef CUL_FNCTS_POINTER_POSTFIX
#define CUL_FNCTS_POINTER_POSTFIX	_t
#endif

/*
	TYPEDEF_FNCT_PTR

	Creates a function pointer type definition.

	TYPEDEF_FNCT_PTR (bool, functionName);
		-> typedef bool (fncpt_functionName_t)
*/
#define TYPEDEF_FNCT_PTR(rettpy, fnctname)				\
			TYPEDEF_FNCT_PTR_	(						\
						rettpy, fnctname,				\
						CUL_FNCTS_POINTER_PREFIX,		\
						CUL_FNCTS_POINTER_POSTFIX		\
								)

#define TYPEDEF_FNCT_PTR_(rettpy, fnctname, prf, pof)	\
			TYPEDEF_FNCT_PTR__ (rettpy, fnctname, prf, pof)

#define TYPEDEF_FNCT_PTR__(rettpy, fnctname, prf, pof)	\
			typedef rettpy (*prf ## fnctname ## pof)

/*
	TYPEDEF_FNCT_PTR_ARGS

	Creates a function pointer type definition including its arguments.

	TYPEDEF_FNCT_PTR_ARGS (bool, functionName, int b);
		-> typedef bool (fncpt_functionName_t) (int b)
*/
#define TYPEDEF_FNCT_PTR_ARGS(rettpy, fnctname, ...)	\
			TYPEDEF_FNCT_PTR_ARGS_	(					\
						rettpy, fnctname,				\
						CUL_FNCTS_POINTER_PREFIX,		\
						CUL_FNCTS_POINTER_POSTFIX,		\
						__VA_ARGS__						\
									)

#define TYPEDEF_FNCT_PTR_ARGS_(rettpy, fnctname, prf, pof, ...)		\
			TYPEDEF_FNCT_PTR_ARGS__ (rettpy, fnctname, prf, pof, __VA_ARGS__)

#define TYPEDEF_FNCT_PTR_ARGS__(rettpy, fnctname, prf, pof, ...)	\
			typedef rettpy (*prf ## fnctname ## pof) (__VA_ARGS__)

#endif														// Of #ifndef U_FUNCTIONPTRTPYDEF_H.
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
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

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
#ifndef ASCII_NUL_STR
#define ASCII_NUL_STR		"\0"
#endif
// End of Text.
#ifndef ASCII_ETX
#define ASCII_ETX			'\3'
#endif
// End of Transmission.
#ifndef ASCII_EOT
#define ASCII_EOT			'\4'
#endif
#ifndef ASCII_BS
#define ASCII_BS			'\0x08'							// '\b'
#endif

// TAB (tabulator).
#ifndef ASCII_TAB
#define ASCII_TAB			'\x09'							// '\t'
#endif
#ifndef ASCII_VT
#define ASCII_VT			'\x0B'							// '\v'
#endif
#ifndef ASCII_FF
#define ASCII_FF			'\x0C'							// '\f'
#endif
#ifndef ASCII_CR
#define ASCII_CR			'\x0D'							// '\r'
#endif
#ifndef ASCII_CR_STR
#define ASCII_CR_STR		"\x0D"
#endif
#ifndef ASCII_LF
#define ASCII_LF			'\x0A'							// '\n'
#endif
#ifndef ASCII_LF_STR
#define ASCII_LF_STR		"\x0A"
#endif
#ifndef ASCII_CRLF_STR
#define ASCII_CRLF_STR		"\x0D\x0A"						// "\r\n"
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
#ifndef ASCII_ESC
#define	ASCII_ESC			'\x1B'
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
/****************************************************************************************

	File:		restrict.h
	Why:		Provides the keyword "cunilog_restrict", which is the C99 "restrict"
				keyword.
	OS:			As many compilers and platforms as required.
	Author:		Thomas
	Created:	2025-03-23

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-03-23	Thomas			Created.

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

#ifndef U_CUNILOG_RESTRICT_H
#define U_CUNILOG_RESTRICT_H

#if __STDC_VERSION__ >= 199901L

	/*
		C99 compiler. The restrict keyword is available.
		See https://en.wikipedia.org/wiki/C99 .
	*/
	#define cunilog_restrict	restrict

#elif defined (__clang__)

	/*
		See https://clang.llvm.org/docs/LanguageExtensions.html .
		Clang also supports __restrict.
	*/
	#define cunilog_restrict	__restrict__

#elif defined (__GNUC__)

	/*
		See https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html .
		Also supports __restrict.
	*/
	#define cunilog_restrict	__restrict__

#elif defined (__INTEL_COMPILER)

	/*
		Requires -restrict option. See
		https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/restrict-qrestrict.html
		for details.
	*/
	#define cunilog_restrict	restrict

#elif defined (_MSC_VER)

	/*
		MSVC 2015 and later. See
		https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170 .
	*/
	#define cunilog_restrict	__restrict

#elif

	/*
		Not available.
	*/
	#define cunilog_restrict

#endif

#endif														// Of #ifndef U_CUNILOG_RESTRICT_H.
/****************************************************************************************

	File:		ArrayMacros.h
	Why:		Macros for arrays and alignments. This header file does not have a code
				file.
	OS:			C99
	Author:		Thomas
	Created:	2022-03-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-27	Thomas			Created.

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

#ifndef HAVE_ARRAYMACROS_H
#define HAVE_ARRAYMACROS_H

#ifndef CUNILOG_USE_COMBINED_MODULE
	#include "./externC.h"
#endif

EXTERN_C_BEGIN

#ifndef UBF_TYPE_DEFINITIONS_INCL_H

#ifndef LENOFSTR
#define LENOFSTR(str) (sizeof (str) - 1)
#endif

// Some macros taken from
//	https://www.codeproject.com/Articles/567335/Essential-Macros-for-C-Programming .
// Number of elements in an array.
#ifndef GET_ARRAY_LEN
#define GET_ARRAY_LEN(arrayName) (sizeof (arrayName) / sizeof ((arrayName)[0]))
#endif
#ifndef UBF_GET_ARRAY_LEN
#define UBF_GET_ARRAY_LEN(arrayName)					\
			GET_ARRAY_LEN (arrayName)
#endif
#ifndef GET_ARRAY_MAX_IDX
#define GET_ARRAY_MAX_IDX(arrayName)					\
		((sizeof(arrayName) / sizeof ((arrayName)[0])) - 1)
#endif
// Aligns the supplied size to the specified PowerOfTwo
#ifndef ALIGN_SIZE
#define ALIGN_SIZE(sizeToAlign, PowerOfTwo)				\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif
#ifndef ALIGNED_SIZE
#define ALIGNED_SIZE(sizeToAlign, PowerOfTwo)			\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif
// Checks whether the supplied size is aligned to the specified PowerOfTwo
#ifndef IS_SIZE_ALIGNED
#define IS_SIZE_ALIGNED(sizeToTest, PowerOfTwo)			\
		(((sizeToTest) & ((PowerOfTwo) - 1)) == 0)
#endif
// Allocate the structure StructName.
#ifndef ALLOC_STRUCT
#define ALLOC_STRUCT(StructName) ((StructName *) ubf_malloc (sizeof (StructName)))
#endif

#endif														// Of #ifndef UBF_TYPE_DEFINITIONS_INCL_H.

EXTERN_C_END

#endif														// Of #ifndef HAVE_ARRAYMACROS_H.
/****************************************************************************************

	File:		Warnings.h
	Why:		Macros to disable/enable some warnings.
	OS:			C99
	Author:		Thomas
	Created:	2024-08-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-07	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

#ifdef _MSC_VER

	// Array is too small to include a terminating NUL.
	#ifndef DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()		\
		_Pragma ("warning (disable: 4295)")
	#endif

	#ifndef DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()		\
		_Pragma ("warning (default: 4295)")
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()	\
		_Pragma ("warning (disable: 4701)")
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()	\
		_Pragma ("warning (default: 4701)")
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()	\
		_Pragma ("warning (disable: 4703)")
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()	\
		_Pragma ("warning (default: 4703)")
	#endif

	// Assignment within conditional expression.
	#ifndef DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()	\
		_Pragma ("warning (disable: 4706)")
	#endif

	#ifndef DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()	\
		_Pragma ("warning (default: 4706)")
	#endif

#else

	// Array is too small to include a terminating NUL.
	#ifndef DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()
	#endif

	#ifndef DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()
	#endif

	// Assignment within conditional expression.
	#ifndef DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()
	#endif

	#ifndef DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()
	#endif

#endif														// Of #ifdef _MSC_VER.
/****************************************************************************************

	File:		SingleBits.h
	Why:		Macros for single bits.
	OS:			Platform independent
	Author:		Thomas
	Created:	2019-05-07

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-05-07	Thomas			Created.

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

#ifndef SINGLEBITS_H
#define SINGLEBITS_H

#define SINGLE_BIT(bitnum)									\
	(1 << bitnum)

#ifdef __cplusplus
	#define SINGLE_BIT_UINT32(bitnum)						\
		((static_cast<uint32_t>(1)) << bitnum)
#else
	#define SINGLE_BIT_UINT32(bitnum)						\
		(((uint32_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UINT64(bitnum)						\
		((static_cast<uint64_t>(1)) << bitnum)
#else
	#define SINGLE_BIT_UINT64(bitnum)						\
		(((uint64_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UINT64_NONE							\
		(static_cast<uint64_t>(0))
#else
	#define SINGLE_BIT_UINT64_NONE							\
		((uint64_t) 0)
#endif

// Short form of SINGLE_BIT_UINT64().
#ifdef __cplusplus
	#define SINGLEBIT64(bitnum)								\
		((static_cast<uint64_t>(1)) << bitnum)
#else
	#define SINGLEBIT64(bitnum)								\
		(((uint64_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLEBIT64_NONE								\
		(static_cast<uint64_t>(0))
#else
	#define SINGLEBIT64_NONE								\
		((uint64_t) 1)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UNSIGNED_INT(bitnum)					\
		((static_cast<unsigned int>(1)) << bitnum)
#else
	#define SINGLE_BIT_UNSIGNED_INT(bitnum)					\
		(((unsigned int) 1) << bitnum)
#endif

#define SetBit(val, bit)	(val | (1 << bit))					// Set.
#define ClrBit(val, bit)	(val & (~ (1 << bit)))				// Clear.
#define TglBit(val, bit)	(val ^ (1 << bit))					// Toggle.
#define HasBit(val, bit)	((val >> bit) & 1)					// Check.

#endif															// Of #ifndef SINGLEBITS_H.
/****************************************************************************************

	File:		unref.h
	Why:		Some macros for unreferenced parameters/arguments etc.
	OS:			-
	Author:		Thomas
	Created:	2024-09-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-23	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Include this file _after_ <Windows.h> or when <Windows.h> is not included at all,
	like for instance on POSIX.
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

#ifndef UNREF_H_INCLUDED
#define UNREF_H_INCLUDED

#ifndef CUNILOG_USE_COMBINED_MODULE

	// Unreferenced parameters. These come from winnt.h and other sources.
	#ifndef UNREFERENCED_PARAMETER
	#define UNREFERENCED_PARAMETER(P)			\
		{										\
			(P) = (P);							\
		}
	#endif
	#ifndef UNUSED_PARAMETER
	#define UNUSED_PARAMETER(x) (void)(x)
	#endif
	#ifndef UNUSED_PARAMETER2
	#define UNUSED_PARAMETER2(x,y) UNUSED_PARAMETER(x),UNUSED_PARAMETER(y)
	#endif

	#ifndef UNREFERENCED_LOCAL_VARIABLE
	#define UNREFERENCED_LOCAL_VARIABLE(V)		(V)
	#endif
	#ifndef DBG_UNREFERENCED_PARAMETER
	#define DBG_UNREFERENCED_PARAMETER(P)		(P)
	#endif
	#ifndef DBG_UNREFERENCED_LOCAL_VARIABLE
	#define DBG_UNREFERENCED_LOCAL_VARIABLE(V)	(V)
	#endif

#endif														// Of #ifndef CUNILOG_USE_COMBINED_MODULE.

#ifndef UNUSED
#define UNUSED(var) (void)(var)
#endif

#endif														// Of #ifndef UNREF_H_INCLUDED.
/****************************************************************************************

	File		membuf.h
	Why:		Helpers for memory buffers
	OS:			C99
	Created:	2022-05-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-05-11	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Module/unit that provides a simplistic buffer (SMEMBUF).
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

#ifndef U_MEMBUF_H
#define U_MEMBUF_H

#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./functionptrtpydef.h"
		#include "./restrict.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/functionptrtpydef.h"
		#include "./../pre/restrict.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifdef _DEBUG
	// Define DEBUG and undefine RELEASE.
	#ifndef DEBUG
	#define DEBUG
	#endif
	#ifndef UBF_DEBUG
	#define UBF_DEBUG
	#endif
	#ifdef	_RELEASE
	#undef	_RELEASE
	#endif
	#ifdef	RELEASE
	#undef	RELEASE
	#endif
	#ifdef	UBF_RELEASE
	#undef	UBF_RELEASE
	#endif
#endif

// Aligns the supplied size to the specified PowerOfTwo
#ifndef ALIGN_SIZE
#define ALIGN_SIZE(sizeToAlign, PowerOfTwo)				\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif
#ifndef ALIGNED_SIZE
#define ALIGNED_SIZE(sizeToAlign, PowerOfTwo)			\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif

EXTERN_C_BEGIN

/*
	The structure that holds the buffer and its length. It is meant to be a generic
	buffer. If a required type is missing, please feel free to add it.
*/
typedef struct smembuf
{
	union
	{
		void			*pvoid;
		char			*pch;
		const char      *pcc;
		signed char		*psc;
		unsigned char	*puc;
		size_t			*pst;
		uint64_t		*pu64;
	} buf;
	size_t				size;
	#ifdef DEBUG
		char			initComplete;
	#endif
} SMEMBUF;

/*
	initSMEMBUF

	Initialises the SMEMBUF structure p points to.
*/
#ifndef DEBUG
	#define initSMEMBUF(p)								\
		(p)->buf.pvoid		= NULL;						\
		(p)->size			= 0
#else
	#define initSMEMBUF(p)								\
		(p)->buf.pvoid		= NULL;						\
		(p)->size			= 0;						\
		(p)->initComplete	= 'A'
#endif

/*
	INITSMEMBUF

	Initialises the SMEMBUF structure s.
*/
#ifndef DEBUG
	#define INITSMEMBUF(s)								\
		(s).buf.pvoid		= NULL;						\
		(s).size			= 0
#else
	#define INITSMEMBUF(s)								\
		(s).buf.pvoid		= NULL;						\
		(s).size			= 0;						\
		(s).initComplete	= 'A'
#endif


/*
	SMEMBUF_INITIALISER
	SMEMBUF_INITIALIZER

	For automatic and static structures.
*/
#ifndef DEBUG
	#define SMEMBUF_INITIALISER							\
		{												\
			{NULL},										\
			0											\
		}
#else
	#define SMEMBUF_INITIALISER							\
		{												\
			{NULL},										\
			0,											\
			'A'											\
		}
#endif
// For the Muricans.
#define SMEMBUF_INITIALIZER	SMEMBUF_INITIALISER

/*
	initSMEMBUFtoSize

	Allocates a buffer size of s and initialises the structure.
*/
#ifndef DEBUG
	#define initSMEMBUFtoSize(p,s)						\
		(p)->buf.pvoid		= ubf_malloc (s);			\
		if ((p)->buf.pvoid)								\
			(p)->size		= s;						\
		else											\
			(p)->size		= 0
#else
	#define initSMEMBUFtoSize(p,s)						\
		(p)->buf.pvoid		= ubf_malloc (s);			\
		if ((p)->buf.pvoid)								\
			(p)->size		= s;						\
		else											\
			(p)->size		= 0;						\
		(p)->initComplete	= 'A';
#endif

/*
	setToSizeSMEMBUF

	Sets the size of the buffer of the SMEMBUF structure pb points to to exactly size siz,
	if it is not identical to size yet by calling ubf_realloc () or ubf_free () and
	ubf_malloc () on it. If the new size is smaller then the current one, ubf_realloc () is
	called to resize the buffer. In this case there's a good chance the current content of
	the buffer is preserved unless ubf_realloc () fails. When the parameter size is greater
	than the current size of the buffer, the function calls ubf_free () and ubf_malloc () to
	accommodate for the new size. The current content of the buffer is lost in this case.

	Note that this function reallocates or frees and newly allocates the buffer size every time
	the parameter siz is not exactly the size of the existing buffer, even if size is smaller
	and a reallocation would actually not be required to hold the intended data. Consider
	calling growToSizeSMEMBUF () instead, which only reallocates when the buffer is too small.
	
	The function returns a pointer to ps->buf.pvoid.
	
	If the function fails it calls doneSMEMBUF () on the structure to free its memory block and
	make it unusable. Check with isUsableSMEMBUF() if the structure can be used afterwards.
	Note that the functions returning a value unequal to NULL alone is not a reliable way of
	determining that the function succeeded.
*/
void *setToSizeSMEMBUF (SMEMBUF *pb, size_t siz);
TYPEDEF_FNCT_PTR (void *, setToSizeSMEMBUF) (SMEMBUF *pb, size_t siz);

/*
	growToSizeSMEMBUF

	Grows the buffer of the SMEMBUF structure pb points to to size siz via a call to
	ubf_realloc () and/or ubf_malloc () if it is smaller than siz. If the size is already at
	least siz the function does not change the buffer. In other words the buffer can only
	grow but never shrinks, which is what you most likely want.

	The current content of the buffer is not transferred to the new buffer and is therefore
	lost.

	The function returns a pointer to ps->buf.pvoid.
	
	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeSMEMBUF (SMEMBUF *pb, size_t siz);
TYPEDEF_FNCT_PTR (void *, growToSizeSMEMBUF) (SMEMBUF *pb, size_t siz);

/*
	growToSizeSMEMBUFreserve

	The function is identical to growToSizeSMEMBUF () but additionally reserves res bytes/
	octets when the buffer size is increased.

	The current content of the buffer is not transferred to the new buffer and is therefore
	lost.

	The function returns a pointer to ps->buf.pvoid.
	
	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeSMEMBUFreserve (SMEMBUF *pb, size_t siz, size_t res);
TYPEDEF_FNCT_PTR (void *, growToSizeSMEMBUFreserve) (SMEMBUF *pb, size_t siz, size_t res);

/*
	growToSizeSMEMBUF64aligned

	The function is identical to growToSizeSMEMBUF () but always aligns the size to
	64 octets/bytes.

	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeSMEMBUF64aligned (SMEMBUF *pb, size_t siz);
TYPEDEF_FNCT_PTR (void *, growToSizeSMEMBUF64aligned) (SMEMBUF *pb, size_t siz);

/*
	growToSizeRetainSMEMBUF

	Grows the buffer of the SMEMBUF structure pb points to to size siz.
	Unlike growToSizeSMEMBUF (), the contents of the existing buffer are
	retained, even if the memory block is new. The function is therefore
	similar to realloc ().

	The buffer never shrinks.

	If the function fails it calls doneSMEMBUF () on the structure to make it unusable.
	Check with isUsableSMEMBUF() if the structure can be used afterwards.
*/
void *growToSizeRetainSMEMBUF (SMEMBUF *pb, size_t siz);

/*
	freeSMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer but does not
	initialise it again with initSMEMBUF(). To re-use the structure, a call to
	initSMEMBUF() is required.

	Not to be called on structures that do not have any buffer allocated. The
	function or macro aborts in debug versions if no buffer has been allocated.
	Use freeSMEMBUFuncond () if this check is not desirable.

	This function/macro is probably a few CPU cycles faster than doneSMEMBUF ()
	for structures that won't be re-used.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void freeSMEMBUF (SMEMBUF *pb);
	TYPEDEF_FNCT_PTR (void, freeSMEMBUF) (SMEMBUF *pb);
#else
	#define freeSMEMBUF(pb)								\
		ubf_free ((pb)->buf.pvoid)
#endif

/*
	freeSMEMBUFuncond

	Deallocates the memory used by the SMEMBUF structure's buffer but does not
	initialise it again with initSMEMBUF(). To re-use the structure, a call to
	initSMEMBUF() is required.

	This function or macro does not abort in debug versions if the SMEMBUF structure
	doesn't have an allocated buffer.

	This function/macro is probably a few CPU cycles faster than doneSMEMBUF ()
	for structures that won't be re-used.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void freeSMEMBUFuncond (SMEMBUF *pb);
	TYPEDEF_FNCT_PTR (void, freeSMEMBUFuncond) (SMEMBUF *pb);
#else
	#define freeSMEMBUFuncond(pb)						\
		if ((pb)->buf.pvoid)							\
			ubf_free ((pb)->buf.pvoid)
#endif

/*
	doneSMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer and initialises it
	with initSMEMBUF() so that it can/could be re-used.

	Not to be called on structures that do not have any buffer allocated.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void doneSMEMBUF (SMEMBUF *pb);
	TYPEDEF_FNCT_PTR (void, doneSMEMBUF) (SMEMBUF *pb);
#else
	#define doneSMEMBUF(p)								\
		freeSMEMBUF (p);								\
		initSMEMBUF (p)
#endif

/*
	DONESMEMBUF

	Deallocates the memory used by the SMEMBUF structure's buffer and initialises it
	with initSMEMBUF() so that it can/could be re-used.

	Not to be called on structures that do not have any buffer allocated. The
	function or macro aborts in debug versions if no buffer has been allocated.
	Use doneSMEMBUFuncond () if this check is not desirable.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#define DONESMEMBUF(s) doneSMEMBUF (&(s))
#else
	#define DONESMEMBUF(s)								\
		freeSMEMBUF (&(s));								\
		INITSMEMBUF (s)
#endif

/*
	doneSMEMBUFuncond

	Deallocates the memory used by the SMEMBUF structure's buffer and initialises it
	with initSMEMBUF() so that it can/could be re-used.

	This function or macro does not abort in debug versions if the SMEMBUF structure
	doesn't have an allocated buffer.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void doneSMEMBUFuncond (SMEMBUF *pb);
	TYPEDEF_FNCT_PTR (void, doneSMEMBUFuncond) (SMEMBUF *pb);
#else
	#define doneSMEMBUFuncond(p)						\
		freeSMEMBUFuncond (p);							\
		initSMEMBUF (p)
#endif

/*
	isUsableSMEMBUF
	
	Evaluates to true if the structure has a buffer and a size. If the evaluation
	passes it can be assumed that a previous call to any of the functions or macros
	in this module/unit has passed and that the structure can be used safely
	afterwards with the set/agreed buffer size.
*/
#define isUsableSMEMBUF(pb)								\
	((pb)->buf.pvoid && (pb)->size)

/*
	isInitialisedSMEMBUF

	Evaluates to true in debug versions if the structure has been initialised. This may
	help find some bugs when a structure is not initialised before being used.
*/
#ifdef DEBUG
	#define isInitialisedSMEMBUF(pb)					\
		('A' == (pb)->initComplete)
#else
	#define isInitialisedSMEMBUF(pb)					\
		(true)
#endif

/*
	copySMEMBUF

	Copies the buffer of src into dst. The buffer size of dst does not shrink.

	The function does not return a value. Check with isUsableSMEMBUF (dst) to see if the
	copy operation was successful.
*/
void copySMEMBUF (SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src)
;
TYPEDEF_FNCT_PTR (void, copySMEMBUF)
	(SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src)
	;

/*
	copySMEMBUFsiz

	Copies the buffer of src into dst up to a size of siz. The buffer size of dst does
	not shrink. The function does not check if the buffer of src is big enough to copy
	siz bytes/octets. This is the responsibility of the caller.

	The function does not return a value. Check with isUsableSMEMBUF (dst) to see if the
	copy operation was successful.
*/
void copySMEMBUFsiz (SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src, size_t siz)
;
TYPEDEF_FNCT_PTR (void, copySMEMBUFsiz)
	(SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src, size_t siz)
	;

/*
	copySMEMBUFreserve

	Sets the buffer size of dst to src->size + reserve and copies the buffer of src to
	dst.

	The function does not return a value. Check with isUsableSMEMBUF (dst) to see if the
	copy operation was successful.
*/
void copySMEMBUFreserve	(
		SMEMBUF		*cunilog_restrict dst,
		SMEMBUF		*cunilog_restrict src,
		size_t		reserve
						)
;
TYPEDEF_FNCT_PTR (void, copySMEMBUFreserve)
						(
		SMEMBUF		*cunilog_restrict dst,
		SMEMBUF		*cunilog_restrict src,
		size_t		reserve
						)
;


EXTERN_C_END

#endif														// Of #ifndef U_MEMBUF_H.
/****************************************************************************************

	File		WinAPI_U8.h
	Why:		UTF-8 versions of many Windows APIs.
	OS:			Windows
	Created:	2020-12-13

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-13	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This is a simple module/unit that provides UTF-8 versions of some common Windows API
	calls.

	If you need a fully-fledged UTF-8 wrapper library for the Windows API, there's a neat
	library on Github (https://github.com/thpatch/win32_utf8) that may be better suitable
	than this module/unit. Due to its design, the win32_utf8 library is more flexible and
	much more complete but also slower. The main difference is that win32_utf8 always
	allocates buffers on the heap while this module here attempts to use stack-based buffers
	if possible.

	The purpose of this module here is to keep it small, simple, and fast. Only a small
	subset of the Windows API is supported. None of the Window system (GUI) functions are
	implemented.
	
	Most functions that work with files and/or folders exist in two versions: One for
	standard paths that allow for relative paths and paths that include path navigators
	("..\.."). These functions end in U8, as for instance in MoveFileU8 (). The other
	type of file and/or folder functions end in U8long, like for instance in
	MoveFileU8long (). These functions implicitely prepend path and filename parameters
	with a long filename prefix ("\\?\") but do not support relative paths or paths that
	contain navigators. See https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
	for details.
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

#ifndef WINDOWSU8_H
#define WINDOWSU8_H

#ifdef _WIN32

/*
	We do need the full header.

	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif
*/

#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./functionptrtpydef.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/functionptrtpydef.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	// We need this if the Microsoft compiler is not used.
	#include <assert.h>
#endif

#ifdef HAVE_NETAPI32
	#include <lmaccess.h>
	#include <Lm.h>
	pragma comment (lib, "Netapi32.lib")
#endif
#ifdef HAVE_SHELLAPI
	#include <shellapi.h>
	#pragma comment (lib, "Shell32.lib")
#endif

#ifdef HAVE_KERNEL32
	#include <tlhelp32.h>
	#pragma comment (lib, "Kernel32.lib")
#endif
#ifdef HAVE_ADVAPI32
	// See https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew .
	#include <Lmcons.h>
	#pragma comment (lib, "Advapi32.lib")
#endif
#ifdef HAVE_SHLWAPI
	#include <shlwapi.h>
	#pragma comment (lib, "Shlwapi.lib")
#endif
#ifdef HAVE_USERENV
	#include <UserEnv.h>
	 #pragma comment (lib, "Userenv.lib")
#endif


#ifndef UBF_MEM_NO_UBFMEM
	#ifndef CUNILOG_USE_COMBINED_MODULE
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./ubfmem.h"
		#else
			#include "./../../mem/ubfmem.h"
		#endif
	#endif
#else
	#include <stdlib.h>
	#define ubf_malloc(size)			malloc (size)
	#define ubf_calloc(n,s)				calloc (n, s)
	#define ubf_realloc(p,s)			realloc (p, s)
	#define ubf_strdup(s)				strdup (s)
	#define ubf_free(ptr)				free (ptr)
	#define ubf_free_accept_NULL(ptr)	free (ptr)
	#define ubf_memcpy(b,d,s,l)			memcpy (d, s, l)
	#define ubf_memmove(b,d,s,l)		memmove (d, s, l)
	#define ubf_memset(b,d,v,l)			memset (d, v, l)
	#define ubf_memcmp(b,p1,p2,l)		memcmp (p1, p2, l)
	#define ubf_mem_init_ptr(b,s)
	#define ubf_mem_usr_ptr(b)			(b)
	#define ubf_mem_chk_ptr(b)
	#define ubf_mem_chk_bse(b)
	#define ubf_mem_test_memdbg()
	#define ubf_mem_done()
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef HAVE_MEMBUF
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./membuf.h"
		#else
			#include "./../../mem/membuf.h"
		#endif
	#endif

#endif

EXTERN_C_BEGIN

#ifndef ASSERT
#define ASSERT(x)	_ASSERT(x)
#endif
#ifndef assert
#define assert(x)	_ASSERT(x)
#endif

#ifdef _DEBUG
	#ifndef DEBUG
	#define DEBUG
	#endif
#endif
#ifndef DEBUG
	#ifndef RELEASE
	#define RELEASE
	#endif
#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

extern WCHAR		wcLongFileNamePrefix [];					// "\\?\" prefix for very
																//	long filenames.
extern const char	ccLongFileNamePrefix [];					// The ASCII/UTF-8 version.
#define LENOFLONGFILENAMEPREFIX		(4)							// Its length, excluding
																//	the NUL-terminator.

// The threshold up to which buffers are placed on the stack as automatic
//	variables.
#ifdef BUILD_TEST_WINAPI_U8_FNCT
	#ifndef WINAPI_U8_HEAP_THRESHOLD
	#define WINAPI_U8_HEAP_THRESHOLD		(16)
	//#define WINAPI_U8_HEAP_THRESHOLD		(256)
	#endif
#else
	#ifndef WINAPI_U8_HEAP_THRESHOLD
	#define WINAPI_U8_HEAP_THRESHOLD		(1024)
	#endif
#endif

/*
	Implicit forward to backslash conversion. This was defined here for testing.
	If required/wanted, define WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH in the project.
*/
#ifndef WINAPIU8_DONT_CONVERT_FORWARD_TO_BACKSLASH
	#ifndef WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH
	//#define WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH
	#endif
#endif

/*
	reqUTF8sizeFromUTF16wchars
	
	Computes the maximum size, in octets (bytes), required by the UTF-8
	representation of a UTF-16 string with the amount of w UTF-16 characters.
	This macro can be used for buffer allocations.
	
	See https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings for more
	information.
	
	Excerpt:
	"UTF-8 requires 8, 16, 24 or 32 bits (one to four bytes) to encode a Unicode character,
	UTF-16 requires either 16 or 32 bits to encode a character, and UTF-32 always requires
	32 bits to encode a character. The first 128 Unicode code points, U+0000 to U+007F, used
	for the C0 Controls and Basic Latin characters and which correspond one-to-one to their
	ASCII-code equivalents, are encoded using 8 bits in UTF-8, 16 bits in UTF-16, and 32 bits
	in UTF-32.
	The next 1,920 characters, U+0080 to U+07FF (encompassing the remainder of almost all
	Latin-script alphabets, and also Greek, Cyrillic, Coptic, Armenian, Hebrew, Arabic, Syriac,
	Tāna and N'Ko), require 16 bits to encode in both UTF-8 and UTF-16, and 32 bits in UTF-32.
	For U+0800 to U+FFFF, i.e. the remainder of the characters in the Basic Multilingual Plane
	(BMP, plane 0, U+0000 to U+FFFF), which encompasses the rest of the characters of most of
	the world's living languages, UTF-8 needs 24 bits to encode a character, while UTF-16
	needs 16 bits and UTF-32 needs 32. Code points U+010000 to U+10FFFF, which represent
	characters in the supplementary planes (planes 1–16), require 32 bits in UTF-8, UTF-16
	and UTF-32."
	
	In other words, UTF-8 can require up to 1.5 * the size of UTF-16.
	
	Since this macro expects the amount of UTF-16 characters as its parameter, which is 2
	octets per character, it returns 2 * w + w.
*/
#define reqUTF8sizeFromUTF16wchars(w)					\
			(sizeof (WCHAR) * (w) + (w))

/*
	reqUTF16charsFromUTF8chars
	
	Computes the maximum size, in WCHARs, required by the UTF-16
	representation of a UTF-8 string with the amount of c UTF-8 octets.
	This macro can be used for buffer allocations.
	
	See https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings for more
	information.
	
	Since this macro expects the amount of UTF-8 octets as its parameter and returns
	the amount of required UTF-16 characters, which is 16 bits for each given octet,
	it returns exactly this amount, unchanged.
*/
#define reqUTF16charsFromUTF8chars(c)					\
			(c)

/*
	reqUTF16sizeFromUTF8chars
	
	Computes the maximum size, in octets (bytes), required by the UTF-16
	representation of a UTF-8 string with the amount of c UTF-8 octets.
	This macro can be used for buffer allocations.
	
	See https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings for more
	information.
	
	Since this macro expects the amount of UTF-8 octets as its parameter and returns
	the maximum amount of octets required by its UTF-8 representation, it returns
	2 * c.
*/
#define reqUTF16sizeFromUTF8chars(c)					\
			(sizeof (WCHAR) * (c))

/*
	reqUTF8size
	
	Returns the required size for the UTF-8 representation from the Windows
	UTF-16 string wcU16 points to.

	This is a function in debug versions and a macro in release builds.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int reqUTF8size (const WCHAR *wcU16);
	TYPEDEF_FNCT_PTR (int, reqUTF8size) (const WCHAR *wcU16);
#else
	#define reqUTF8size(wcU16)							\
		WideCharToMultiByte (CP_UTF8, 0, wcU16, -1, NULL, 0, NULL, NULL)
#endif

/*
	reqUTF8sizel

	Returns the required size for the UTF-8 representation from the Windows
	UTF-16 string wcU16 points to.

	This is a function in debug versions and a macro in release builds.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int reqUTF8sizel (const WCHAR *wcU16, int lenU16);
	TYPEDEF_FNCT_PTR (int, reqUTF8sizel) (const WCHAR *wcU16, int lenU16);
#else
	#define reqUTF8sizel(wcU16, lenU16)					\
		WideCharToMultiByte (CP_UTF8, 0, wcU16, lenU16, NULL, 0, NULL, NULL)
#endif

/*
	UTF8_from_WinU16
	
	Simplified invocation of WideCharToMultiByte () that converts from Windows
	UTF-16 to UTF8.

	This is a function in debug versions and a macro in release builds.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int UTF8_from_WinU16 (char *chU8, int sizeU8, const WCHAR *wcU16);
	TYPEDEF_FNCT_PTR (int, UTF8_from_WinU16) (char *chU8, int sizeU8, const WCHAR *wcU16);
#else
	#define UTF8_from_WinU16(chU8, sizeU8, wcU16)		\
		WideCharToMultiByte (CP_UTF8, 0, wcU16, -1, chU8, sizeU8, NULL, NULL)
#endif

/*
	UTF8_from_WinU16l

	Simplified invocation of WideCharToMultiByte () that converts from Windows
	UTF-16 to UTF8. The parameter lenU16 specifies the length of wcU16 and
	the UTF-16 string does not have to be NUL-terminated.

	This is a function in debug versions and a macro in release builds.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int UTF8_from_WinU16l (char *chU8, int sizeU8, const WCHAR *wcU16, int lenU16);
	TYPEDEF_FNCT_PTR (int, UTF8_from_WinU16l) (char *chU8, int sizeU8, const WCHAR *wcU16, int lenU16);
#else
	#define UTF8_from_WinU16l(chU8, sizeU8, wcU16,		\
				lenU16)									\
				WideCharToMultiByte (CP_UTF8, 0,		\
					wcU16, lenU16, chU8, sizeU8,		\
					NULL, NULL)
#endif

/*
	reqWinU16wchars
	
	Returns the required size for the Windows UTF-16 representation of the UTF-8
	string chU8 points to.

	This is a function in debug versions and a macro in release builds.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int reqWinU16wchars (const char *chU8);
	TYPEDEF_FNCT_PTR (int, reqWinU16wchars) (const char *chU8);
#else
	#define reqWinU16wchars(chU8)						\
		MultiByteToWideChar (CP_UTF8, 0, chU8, -1, NULL, 0)
#endif
#define reqWinU16size(chU8)								\
	error Function renamed to reqWinU16wchars () because it returns the amount of WCHARs required

/*
	WinU16_from_UTF8
	
	Simplified invocation of MultiByteToWideChar () that converts from UTF-8 to
	Windows UTF-16.
	
	This is a function in debug versions and a macro in release builds.

	2021-02-05: Function/macro renamed to make it clearer that it does NOT return the
	amount of bytes but the amount of WCHARs required.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int WinU16_from_UTF8 (WCHAR *wcU16, int sizeU16, const char *chU8);
	TYPEDEF_FNCT_PTR (int, WinU16_from_UTF8) (WCHAR *wcU16, int sizeU16, const char *chU8);
#else
	#define WinU16_from_UTF8(wcU16, sizeU16, chU8)		\
		MultiByteToWideChar (CP_UTF8, 0, chU8, -1, wcU16, sizeU16)
#endif

/*
	reqWinU16wcharsFileName

	Returns the required buffer size, in characters, for the wide character
	(Windows UTF-16) representation of the UTF-8 filename ccU8FileName points
	to plus the size in characters required to prepend this filename with a long
	filename prefix ("\\?\"), if it doesn't start with one yet.
	
	Call WinU16_from_UTF8_FileName () with a buffer the size of the return value
	of this function.
	
	2021-02-05: Function renamed to make it clearer that it does NOT return the
	amount of bytes but the amount of WCHARs required.
*/
int reqWinU16wcharsFileName (const char *ccU8FileName);
TYPEDEF_FNCT_PTR (int, reqWinU16wcharsFileName) (const char *ccU8FileName);
#define reqWinU16sizeFileName()							\
	error Function renamed to reqWinU16FileNameWCHARs () because it returns the amount of WCHARs required

/*
	HasLongFileNamePrefixW
	
	Returns or evaluates to TRUE if wcFileName starts with a long file name prefix,
	FALSE if not.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	BOOL HasLongFileNamePrefixW (const WCHAR *wcFileName);
	TYPEDEF_FNCT_PTR (BOOL, HasLongFileNamePrefixW) (const WCHAR *wcFileName);
#else
	#define HasLongFileNamePrefixW(wcfn)				\
		(!wcsncmp (wcfn, wcLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX))
#endif

/*
	HasLongFileNamePrefixU8
	
	Returns or evaluates to TRUE if ccFileName starts with a long file name prefix,
	FALSE if not.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	BOOL HasLongFileNamePrefixU8 (const char *ccFileName);
	TYPEDEF_FNCT_PTR (BOOL, HasLongFileNamePrefixU8) (const char *ccFileName);
#else
	#define HasLongFileNamePrefixU8(ccfn)				\
		(!strncmp (ccfn, ccLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX))
#endif

/*
	WinU16_from_UTF8_FileName
	
	Converts the UTF-8 filename ccU8FileName points to to its Windows UTF-16
	wide character representation. The function prepends a Windows long file name
	prefix ("\\?\") to wcU16FileName if ccU8FileName doesn't already contain one.
	
	Returns the number of characters written to wcU16FileName.
*/
int WinU16_from_UTF8_FileName (WCHAR *wcU16FileName, int sizeU16, const char *ccU8FileName);
TYPEDEF_FNCT_PTR (int, WinU16_from_UTF8_FileName) (WCHAR *wcU16FileName, int sizeU16, const char *ccU8FileName);

/*
	AllocWinU16_from_UTF8
	AllocWinU16_from_UTF8_00
	
	Allocates memory for the WCHAR representation of ccU8 and performs the conversion,
	returning a pointer to the UTF-8 string converted to a UTF-16 Windows wide-character
	string, or NULL if either ccU8 is NULL or the heap allocation fails.
	
	The caller is responsible for calling DoneWinU16 () on the returned pointer when it
	is not needed anymore to deallocate the memory block again.

	The function AllocWinU16_from_UTF8_00 () terminates the returned string with two NUL
	characters instead of one. Some Windows APIs require this, for instance, some members of
	a SHFILEOPSTRUCTW structure. See
	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shfileopstructw
	and check the members pFrom and pTo. Both need to be terminated with two NUL characters.
*/
WCHAR *AllocWinU16_from_UTF8 (const char *ccU8);
TYPEDEF_FNCT_PTR (WCHAR *, AllocWinU16_from_UTF8) (const char *ccU8);
WCHAR *AllocWinU16_from_UTF8_00 (const char *ccU8);
TYPEDEF_FNCT_PTR (WCHAR *, AllocWinU16_from_UTF8_00) (const char *ccU8);

/*
	AllocWinU16_from_UTF8_FileName
	
	Allocates memory for the WCHAR representation of ccU8 and performs the conversion,
	returning a pointer to the converted string at the address pwc points to, or NULL
	if either ccU8 is NULL or the heap allocation fails. The function assumes that
	ccU8FileName points to a file name and prepends the resulting wide character
	string with a long file name prefix if it is not provided in ccU8FileName.
	
	The caller is responsible for calling free () on the returned pointer when it
	is not needed anymore.
*/
WCHAR *AllocWinU16_from_UTF8_FileName (const char *ccU8FileName);
TYPEDEF_FNCT_PTR (WCHAR *, AllocWinU16_from_UTF8_FileName) (const char *ccU8FileName);

/*
	DoneWinU16
	
	This function/macro calls ubf_free () on the provided pointer pwc. It currently
	exists for aesthetic reasons only but this might change in the future if the
	allcoation method is changed.
	
	WCHAR *pwc = AllocWinU16_from_UTF8_FileName (L"Filename.ext");
	...
	DoneWinU16 (pwc);
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void DoneWinU16 (WCHAR *pwc);
	TYPEDEF_FNCT_PTR_ARGS (void, DoneWinU16, WCHAR *pwc);
#else
	#define DoneWinU16(p)								\
		if (p)											\
			ubf_free (p)
#endif

/*
	AllocU8_from_WinU16l

	Allocates memory for the UTF-8 representation of wc16 and performs the conversion,
	returning a pointer to the Windows UTF-16 string converted to UTF-8. The function
	never reads more than ln16 characters from wc16. It calls wcslen (wc16) if
	ln16 is USE_STRLEN. The maximum value for ln16 is INT_MAX - 1.

	The caller is responsible for calling DoneU8 () on the returned pointer when it
	is not needed anymore to deallocate the memory associated with it.

	The return value is a newly allocated buffer containing the string in wc16
	converted to UTF-8. The returned string is NUL-terminated. The function returns
	NULL if the heap allocation fails.
*/
char *AllocU8_from_WinU16l (const WCHAR *wc16, size_t ln16);
TYPEDEF_FNCT_PTR_ARGS (char *, AllocU8_from_WinU16l, const WCHAR *wc16, size_t ln16);

/*
	AllocU8_from_WinU16

	Allocates memory for the UTF-8 representation of wc16 and performs the conversion,
	returning a pointer to the Windows UTF-16 string converted to UTF-8, or NULL if
	either wc16 is NULL or the heap allocation fails. The returned buffer and string
	is NUL-terminated because this is also the requirement for the UTF-16 string wc16.
	
	The caller is responsible for calling DoneU8 () on the returned pointer when it
	is not needed anymore to deallocate the memory associated with it.
*/
char *AllocU8_from_WinU16 (const WCHAR *wc16);
TYPEDEF_FNCT_PTR_ARGS (char *, AllocU8_from_WinU16, const WCHAR *wc16);

/*
	AllocU8path_from_U8path_and_WinU16FileName
	
	Returns a pointer to a newly allocated buffer that consists of the UTF-8 path ccPath
	and the file or subfolder name wcFileName, which is in Windows UTF-16. The complete
	path is then copied into the buffer and returned to the caller.
	
	The caller is responsible for calling DoneU8 () on the returned pointer.
	
	The parameter ccPath is expected to contain a valid path that was passed to the
	Windows API function FindFirstFile (). It can therefore contain wildcards in the
	filename part. See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilea
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew
	for more information on this API.
	
	The parameter wcFileName is expected to contain a valid filename for the member
	cFileName of a WIN32_FIND_DATAW structure. See
	https://docs.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-win32_find_dataw
	for more information on this structure.
	
	Valid parameters:							Return value
	"D:\Test", L"file.ext"						"D:\\Test\\file.ext"
	"D:\Test*", L"file.ext"						"D:\\file.ext"
	"\\\\Server\share", L"file.ext"				"\\\\Server\\share\\file.ext"
	"\\\\Server\share*", L"file.ext"			"\\\\Server\\file.ext"

	To use this function, define HAVE_STRWILDCARDS and add string/strwildcards.c/h to
	the project.
*/
#ifdef HAVE_STRWILDCARDS
	char *AllocU8path_from_U8path_and_WinU16FileName (const char *ccPath, WCHAR *wcFileName);
	TYPEDEF_FNCT_PTR (char *, AllocU8path_from_U8path_and_WinU16FileName) (const char *ccPath, WCHAR *wcFileName);
#endif

/*
	U8pathSMEMBUF_from_U8path_and_WinU16FileName

	This function is identical to AllocU8path_from_U8path_and_WinU16FileName () but does
	not return a newly allocated buffer. Instead, it returns its result in an SMEMBUF structure
	that can be re-used for consecutive invokations and can therefore be much faster.

	Before the function is called, the caller must initialise the SMEMBUF structure pmbResult
	correctly, either with initSMEMBUF (), initSMEMBUFtoSize (), or by assigning it
	SMEMBUF_INITIALISER.

	After the function returns and the SMEMBUF structure is not required anymore, a call
	to doneSMEMBUF () or freeSMEMBUF () on it deallocates its buffer.

	To use this function, define HAVE_STRWILDCARDS and add string/strwildcards.c/h to
	the project. Additionally, define HAVE_MEMBUF and add mem/membuf.c/h to the project.

	The function returns true on success, false otherwise. The SMEMBUF structure can be
	re-used between calls to the function. When the function returns false, the SMEMBUF
	structure remains correctly initialised but the returned result is most likely not correct.
	Only when the function returns true is the SMEMBUF structure correctly filled.
*/
#if defined (HAVE_STRWILDCARDS) && defined (HAVE_MEMBUF)
	bool U8pathSMEMBUF_from_U8path_and_WinU16FileName	(
					SMEMBUF				*pmbResult,
					const char			*ccPath,
					size_t				lnPath,
					WCHAR				*wcFileName
														);
#endif

/*
	DoneU8
	
	This function/macro calls ubf_free () on the provided pointer pch. It currently
	exists for aesthetic reasons only but this might change in the future if the
	allcoation method is changed.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void DoneU8 (char *pch);
	TYPEDEF_FNCT_PTR (void, DoneU8) (char *pch);
#else
	#define DoneU8(p)									\
		if (p)											\
			ubf_free (p)
#endif

/*
	AllocWinU16fromU8orUseThreshold
	AllocWinU16fromU8orUseThreshold_00

	Converts the UTF-8 string pchU8 points to to its Windows UTF-16 representation.
	Returns a pointer to pwcStackVar if the required length of the Windows UTF-16
	representation of pchU8 fits in a UTF-16 string with WINAPI_U8_HEAP_THRESHOLD
	characters, including a terminating NUL character. It returns a newly allocated
	WCHAR * if the UTF-16 string does not fit in the buffer pointed to by
	pwcStackVar.
	
	The function returns a pointer to a UTF-16 string that contains the UTF-16
	representation of pchU8. The returned pointer is either pwcStackVar or a newly
	allocated memory block. The function returns NULL if pchU8 is NULL.
	
	Call DoneWinU16fromU8orUseThreshold () with the returned pointer and the same
	pwcStackVar variable to conditionally deallocate the buffer again.
	
	The function AllocWinU16fromU8orUseThreshold_00 () is identical to
	AllocWinU16fromU8orUseThreshold () with the exception that it terminates the
	returned string with two NUL characters instead of one. This is a requirement
	by some Windows APIs, for instance some members of a SHFILEOPSTRUCTW structure. See
	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shfileopstructw
	and check the members pFrom and pTo. Both need to be terminated with two NULs.

	Parameters:
	pwcStackVar		Pointer to a WCHAR array (WCHAR [WINAPI_U8_HEAP_THRESHOLD]).
	pchU8			The UTF-8 string to be converted to UTF-16.
	
	Example:
	
	void WindowsAPIfunctionU8 (const char *pszU8)
	{
		WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	*pwcFileName;
		
		pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, pszU8);
		// Call the Windows API with parameter pwcFileName.
		//	...
		DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	}
*/
WCHAR *AllocWinU16fromU8orUseThreshold (WCHAR *pwcStackVar, const char *pchU8);
TYPEDEF_FNCT_PTR (WCHAR *, AllocWinU16fromU8orUseThreshold) (WCHAR *pwcStackVar, const char *pchU8);
WCHAR *AllocWinU16fromU8orUseThreshold_00 (WCHAR *pwcStackVar, const char *pchU8);
TYPEDEF_FNCT_PTR (WCHAR *, AllocWinU16fromU8orUseThreshold_00) (WCHAR *pwcStackVar, const char *pchU8);

/*
	AllocWinU16fromU8orUseThresholdLongFileName
	
	The function is identical to AllocWinU16fromU8orUseThreshold () in principal but
	assumes that the parameter pchU8 is an absolute long filename without relative
	parts. It prepends the Windows UTF-16 representation with a long filename prefix.

	Call DoneWinU16fromU8orUseThreshold with the returned pointer and the same
	pwcStackVar variable to conditionally deallocate the buffer again.
*/
WCHAR *AllocWinU16fromU8orUseThresholdLongFileName (WCHAR *pwcStackVar, const char *pchU8);
TYPEDEF_FNCT_PTR (WCHAR *, AllocWinU16fromU8orUseThresholdLongFileName) (WCHAR *pwcStackVar, const char *pchU8);

/*
	DoneWinU16fromU8orUseThreshold
	
	Conditionally deallocates the memory allocated by
	AllocWinU16fromU8orUseThreshold () or
	AllocWinU16fromU8orUseThresholdLongFileName ().
	
	Does nothing if pwcHeapVar is NULL. Does nothing if pwcHeapVar points to
	pwcStackVar. In all other cases ubf_free () is called with pwcHeapVar as its
	parameter.

	Debug versions abort if one of the parameters is NULL. This would indicate
	a bug somewhere.
*/
void DoneWinU16fromU8orUseThreshold (WCHAR *pwcHeapVar, WCHAR *pwcStackVar);
TYPEDEF_FNCT_PTR (void, DoneWinU16fromU8orUseThreshold) (WCHAR *pwcHeapVar, WCHAR *pwcStackVar);

/*
	AllocU8fromWinU16orUseThresholdl

*/
char *AllocU8fromWinU16orUseThresholdl (char *pszStackVar, const WCHAR *pwcU16, size_t lnU16);
TYPEDEF_FNCT_PTR (char *, AllocU8fromWinU16orUseThresholdl)
	(char *pszStackVar, const WCHAR *pwcU16, size_t lnU16);

/*
	AllocU8fromWinU16orUseThreshold

	Converts the Windows UTF-16 string pwcU16 points to to its UTF-8 representation.
	Returns a pointer to pszStackVar if the required length of the UTF-8
	representation of pwcU16 fits in a UTF-8 string with WINAPI_U8_HEAP_THRESHOLD
	characters, including a terminating NUL character. It returns a newly allocated
	char * if the final UTF-8 string does not fit in the buffer pointed to by
	pszStackVar.
	
	The function returns a pointer to a UTF-8 string that contains the UTF-8
	representation of pwcU16. The returned pointer is either pszStackVar or a newly
	allocated memory block. The function returns NULL if pwcU16 is NULL.
	
	Call DoneU8fromWinU16orUseThreshold () with the returned pointer and the same
	pwcStackVar variable to conditionally deallocate the buffer again.
	
	Parameters:
	pwcStackVar		Pointer to a char array (char [WINAPI_U8_HEAP_THRESHOLD]).
	pwcU16			The UTF-16 string to be converted to UTF-8.
	
*/
char *AllocU8fromWinU16orUseThreshold (char *pszStackVar, const WCHAR *pwcU16);
TYPEDEF_FNCT_PTR (char *, AllocU8fromWinU16orUseThreshold)
	(char *pszStackVar, const WCHAR *pwcU16);

/*
	DoneU8fromWinU16orUseThreshold

	Conditionally deallocates the memory allocated by
	AllocU8fromWinU16orUseThreshold ().
	
	Does nothing if pwcHeapVar is NULL. Does nothing if pwcHeapVar points to
	pwcStackVar. In all other cases ubf_free () is called with pwcHeapVar as its
	parameter.

	Debug versions abort if one of the parameters is NULL. This would indicate
	a bug somewhere.
*/
void DoneU8fromWinU16orUseThreshold (char *pszHeapVar, char *pszStackVar);

/*
	AllocU8ArgsFromWinU16
	
	Returns an array of UTF-8 strings that have been created from the UTF-16
	array of strings argvw.
	
	To free the the allocated array again, call DoneU8Args ().
*/
char **AllocU8ArgsFromWinU16 (int argc, WCHAR *argvw []);
TYPEDEF_FNCT_PTR (char **, AllocU8ArgsFromWinU16) (int argc, WCHAR *argvw []);

/*
	DoneU8Args
	
	Deallocates the memory allocated by AllocU8ArgsFromWinU16 ().
*/
void DoneU8Args (int argc, char *args []);
TYPEDEF_FNCT_PTR (void, DoneU8Args) (int argc, char *args []);

/*
	CmdLineArgsW
	
	Retrieves an array of WCHAR with the command-line arguments. The function/
	macro is a wrapper for the Windows API function CommandLineToArgvW ().
	This is a function in debug versions, a macro in release builds.
	
	Define HAVE_SHELLAPI to use this function and link to Shell32.lib.
*/
#ifdef HAVE_SHELLAPI
	#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		WCHAR **CmdLineArgsW (int *nArgs);
		TYPEDEF_FNCT_PTR (WCHAR **, CmdLineArgsW) (int *nArgs);
	#else
		#define CmdLineArgsW(n)							\
			CommandLineToArgvW	(						\
				GetCommandLineW (), (n)					\
								)
	#endif
#endif

/*
	CopyFileU8

	UTF-8 version of the CopyFileW () Windows API. See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfilew
	for details.
*/
BOOL CopyFileU8(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
;
TYPEDEF_FNCT_PTR (BOOL, CopyFileU8)
(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
;

/*
	CopyFileU8long

	UTF-8 version of the CopyFileW () Windows API. See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfilew
	for details.

	The function adds long filename prefixes to the string parameters if they're not
	prefixed yet.
*/
BOOL CopyFileU8long(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
;
TYPEDEF_FNCT_PTR (BOOL, CopyFileU8long)
(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
;

/*
	CreateAllFoldersW

	Creates all folders in wcPath and returns TRUE on success, FALSE otherwise.
	Success means that the path either has been created by the function or that
	it existed already prior to invoking the function.
*/
BOOL CreateAllFoldersW (WCHAR *wcPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
TYPEDEF_FNCT_PTR (BOOL, CreateAllFoldersW) (WCHAR *wcPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateAllFoldersU8
	
	UTF-8 version of CreateAllFoldersW (). See above.
*/
BOOL CreateAllFoldersU8 (const char *szPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
TYPEDEF_FNCT_PTR (BOOL, CreateAllFoldersU8) (const char *szPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateDirectoryIfNotExistsW

	Calls CreateDirectoryW () to create a directory but also returns TRUE if
	the directory exists already.
*/
BOOL CreateDirectoryIfNotExistsW (WCHAR *wcDir, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateDirectoryOrExistsU8

	Calls CreateDirectoryU8 () to create a directory but also returns TRUE if
	the directory exists already.
*/
BOOL CreateDirectoryIfNotExistsU8 (const char *ccPathU8, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
TYPEDEF_FNCT_PTR (BOOL, CreateDirectoryIfNotExistsU8)
	(const char *ccPathU8, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/*
	CreateDirectoryU8
	
	UTF-8 version of CreateDirectoryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createdirectoryw
	for reference.
*/
BOOL CreateDirectoryU8(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
;
TYPEDEF_FNCT_PTR (BOOL, CreateDirectoryU8)
(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
;

/*
	CreateDirectoryU8long
	
	The function is identical to CreateDirectoryU8 () but allows lpPathNameU8 to be
	a very long path because it prepends a long filename prefix if required. Does not
	support relative elements.
*/
BOOL CreateDirectoryU8long(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
;
TYPEDEF_FNCT_PTR (BOOL, CreateDirectoryU8long)
(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
;

/*
	CreateEventU8
	
	UTF-8 version of the Windows API function CreateEventW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventw
	for more information.
*/
HANDLE CreateEventU8(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCSTR                lpName
)
;
TYPEDEF_FNCT_PTR (HANDLE, CreateEventU8)
(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCSTR                lpName
)
;

/*
	CreateEventExU8
	
	UTF-8 version of the Windows API function CreateEventExW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventexw
	for more information.
*/
HANDLE CreateEventExU8(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);
TYPEDEF_FNCT_PTR (HANDLE, CreateEventExU8)
(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);

/*
	CreateFileMappingU8
	
	UTF-8 version of CreateFileMappingW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-createfilemappingw
	for reference.
*/
HANDLE CreateFileMappingU8(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCSTR                lpName
)
;
TYPEDEF_FNCT_PTR (HANDLE, CreateFileMappingU8)
(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCSTR                lpName
)
;

/*
	CreateFileU8
	
	A UTF-8 version of CreateFileW (). Its parameters are identical to the ASCII version
	of CreateFile (), which is CreateFileA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew
	for more information.
	
	The return value of the function is the return value of CreateFileW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_HANDLE_VALUE.
*/
HANDLE CreateFileU8(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
;
TYPEDEF_FNCT_PTR (HANDLE, CreateFileU8)
(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
;

/*
	CreateFileU8long
	
	A UTF-8 version of CreateFileW (). Its parameters are identical to the ASCII version
	of CreateFile (), which is CreateFileA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew
	for more information.
	
	The function expects the filename in the parameter lpFileNameU8 and converts it
	from UTF-8 to the Windows UTF-16 character set (wide character set). Before invoking
	CreateFileW (), the function also prepends the UTF-16 version of the filename with
	a Windows long filename prefix ("\\?\") to support long filenames, unless the UTF-8
	filename already contains this prefix. This means that the function's length
	restriction for paths could be 32 767 characters.

	Since this function automatically prepends a long filename prefix it does not
	accept relative paths or ellipsis ("." or "..").
			
	The return value of the function is the return value of CreateFileW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_HANDLE_VALUE.
*/
HANDLE CreateFileU8long(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
;
TYPEDEF_FNCT_PTR (HANDLE, CreateFileU8long)
(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
;

/*
	STARTUPINFOW_from_STARTUPINFOA
	
	Converts a UTF-8 STARTUPINFOA structure to a Windows UTF-16 STARTUPINFOW
	structure. The function exists because Windows does not natively support
	UTF-8 strings in a STARTUPINFOA structure.

	Since the strings of the STARTUPINFOW structure are allocated on the heap,
	call DoneSTARTUPINFOW () on it when it is not required anymore to avoid
	memory leaks.
*/
void STARTUPINFOW_from_STARTUPINFOA (STARTUPINFOW *siw, STARTUPINFOA *sia);
TYPEDEF_FNCT_PTR (void, STARTUPINFOW_from_STARTUPINFOA) (STARTUPINFOW *siw, STARTUPINFOA *sia);

/*
	DoneSTARTUPINFOW
	
	Releases the allocated string members of STARTUPINFOW sturcture siw points
	to. The function STARTUPINFOW_from_STARTUPINFOA () allocates these strings.

	Call this function on STARTUPINFOW structures that have been filled by the
	function STARTUPINFOW_from_STARTUPINFOA () to avoid memory leaks.
*/
void DoneSTARTUPINFOW (STARTUPINFOW *siw);
TYPEDEF_FNCT_PTR (void, DoneSTARTUPINFOW) (STARTUPINFOW *siw);

/*
	CloseHandleAndInvalidate
	
	Calls CloseHandle on the HANDLE phHandle points to and sets it to
	INVALID_HANDLE_VALUE.
	
	The function returns the return value of the Windows API CloseHandle ().
*/
BOOL CloseHandleAndInvalidate (HANDLE *phHandle);
TYPEDEF_FNCT_PTR (BOOL, CloseHandleAndInvalidate) (HANDLE *phHandle);

/*
	CreateMutexU8
	
	UTF-8 version of the Windows API CreateMutexW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw
	for reference.

	The function returns the handle returned by CreateMutexW () or NULL if an error
	occurred.
*/
HANDLE CreateMutexU8(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  BOOL                  bInitialOwner,
  LPCSTR                lpName
)
;
TYPEDEF_FNCT_PTR (HANDLE, CreateMutexU8)
(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  BOOL                  bInitialOwner,
  LPCSTR                lpName
)
;


/*
	CreateMutexExU8
	
	UTF-8 version of the Windows API CreateMutexExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexexw
	for reference.

	The function returns the handle returned by CreateMutexExW () or NULL if an error
	occurred.
*/
HANDLE CreateMutexExU8(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);
TYPEDEF_FNCT_PTR (HANDLE, CreateMutexExU8)
(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);

/*
	CreatePipeOverlapped

	This is not a Windows API but rather a convenience function to create a pipe
	with overlapped handles. The two boolean parameters set the handle in question
	to overlapped when true. Otherwise, the function is identical to CreatePipe ().
	See
	https://learn.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-createpipe .

	The function utilises a modified version of MyCreatePipeEx (), originally found at
	http://www.davehart.net/remote/PipeEx.c . It has been taken from
	https://web.archive.org/web/20150125081922/http://www.davehart.net:80/remote/PipeEx.c
	and modified for UTF-16.
*/
BOOL CreatePipeOverlapped(
		PHANDLE					hReadPipe,
		bool					bOverlappedRead,
		PHANDLE					hWritePipe,
		bool					bOverlappedWrite,
		LPSECURITY_ATTRIBUTES	lpPipeAttributes,
		DWORD					nSize
);
TYPEDEF_FNCT_PTR (BOOL, CreatePipeOverlapped)(
		PHANDLE					hReadPipe,
		bool					bOverlappedRead,
		PHANDLE					hWritePipe,
		bool					bOverlappedWrite,
		LPSECURITY_ATTRIBUTES	lpPipeAttributes,
		DWORD					nSize
);

/*
	CreateProcessU8EnvW
	
	UTF-8 version of CreateProcessW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessw
	for reference.
	
	This function expects all parameters apart from lpEnvironment to be UTF-8 encoded.
	For lpEnvironment, the function expects a WCHAR block. Use CreateProcessU8 ()
	when the environment block is not NULL and should be UTF-8 encoded too.
*/
BOOL CreateProcessU8EnvW(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
)
;
TYPEDEF_FNCT_PTR (BOOL, CreateProcessU8EnvW)
(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
)
;

/*
	CreateProcessU8
	
	UTF-8 version of CreateProcessW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessw
	for reference.
	
	The function expects all parameters, including lpEnvironment, to be UTF-8 encoded.
	If lpEnvironment is not NULL, it creates a Windows UTF-16 encoded version of the
	environment by calling CreateWinU16EnvironmentFromU8 (), calls
	CreateProcessU8EnvW (), and finally deallocates the UTF-16 environment block again
	before it returns. If lpEnvironment is NULL the function calls CreateProcessW ()
	directly with a value of NULL for lpEnvironment.
*/
BOOL CreateProcessU8(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
)
;
TYPEDEF_FNCT_PTR (BOOL, CreateProcessU8)
(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
)
;

/*
	CreateSemaphoreU8
	
	UTF-8 version of CreateSemaphoreW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createsemaphorew
	for reference.

	The function returns the return value of the Windows API CreateSemaphoreW (),
	which is a handle to the semaphore or NULL if it fails.
*/
HANDLE CreateSemaphoreU8(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpNameU8
)
;
TYPEDEF_FNCT_PTR (HANDLE, CreateSemaphoreU8)
(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpNameU8
)
;

/*
	CreateServiceU8
	
	UTF-8 version of CreateServiceW ().
	See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicew .
	
	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
SC_HANDLE CreateServiceU8(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  LPCSTR    lpDisplayName,
  DWORD     dwDesiredAccess,
  DWORD     dwServiceType,
  DWORD     dwStartType,
  DWORD     dwErrorControl,
  LPCSTR    lpBinaryPathName,
  LPCSTR    lpLoadOrderGroup,
  LPDWORD   lpdwTagId,
  LPCSTR    lpDependencies,
  LPCSTR    lpServiceStartName,
  LPCSTR    lpPassword
)
;
TYPEDEF_FNCT_PTR (SC_HANDLE, CreateServiceU8)
(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  LPCSTR    lpDisplayName,
  DWORD     dwDesiredAccess,
  DWORD     dwServiceType,
  DWORD     dwStartType,
  DWORD     dwErrorControl,
  LPCSTR    lpBinaryPathName,
  LPCSTR    lpLoadOrderGroup,
  LPDWORD   lpdwTagId,
  LPCSTR    lpDependencies,
  LPCSTR    lpServiceStartName,
  LPCSTR    lpPassword
)
;
#endif

/*
	CreateWin16tringArrayFromU8
	
	Creates a Windows UTF-16 version of the UTF-8 string array pu8 points
	to on the heap and returns a pointer to it.
	
	Call DoneWin16StringArray () on the returned pointer when it is not
	required anymore to deallocate its resources.
*/
WCHAR **CreateWin16tringArrayFromU8 (const char **pu8, size_t numStrings);
TYPEDEF_FNCT_PTR (WCHAR **, CreateWin16tringArrayFromU8) (const char **pu8, size_t numStrings);


/*
	DoneWin16StringArray
	
	Deallocates the resources of a Windows UTF-16 string array created with
	CreateWin16tringArrayFromU8 ().
*/
void DoneWin16StringArray (WCHAR **pwcStringArray, size_t numStrings);
TYPEDEF_FNCT_PTR (void, DoneWin16StringArray) (WCHAR **pwcStringArray, size_t numStrings);

/*
	CreateWinU16EnvironmentFromU8
	
	Creates a Windows UTF-16 environment block from the given UTF-8 environment
	block. An environment block consists of continuous memory that contains
	single NUL terminated strings with the block terminated with an additional
	NUL.
	
	"Text\0"
	"Next text\0"
	"\0"
	
	The function returns a newly allocated memory block created from the UTF-8
	environment block szU8Environment points to.
	
	Call DoneWinU16Environment () to release the memory of the returned pointer
	again, which is a wrapper for free ().
*/
WCHAR *CreateWinU16EnvironmentFromU8 (const char *szU8Environment);
TYPEDEF_FNCT_PTR (WCHAR *, CreateWinU16EnvironmentFromU8) (const char *szU8Environment);

/*
	DoneWinU16Environment
	
	Deallocates the memory of the Windows UTF-8 environment block. Simple
	function that calls free () to look more consistent. This is a macro
	in release builds.
	
	WCHAR *pe = CreateWinU16EnvironmentFromU8 (szEnv);
	...
	DoneWinU16Environment (pe);
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void DoneWinU16Environment (WCHAR *wcEnvironment);
	TYPEDEF_FNCT_PTR (void, DoneWinU16Environment) (WCHAR *wcEnvironment);
#else
	#define DoneWinU16Environment(p)					\
		free (p)
#endif

/*
	DecryptFileU8
	
	UTF-8 version of DecryptFileW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-decryptfilew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL DecryptFileU8(
  LPCSTR lpFileName,
  DWORD  dwReserved
)
;
TYPEDEF_FNCT_PTR (BOOL, DecryptFileU8)
(
  LPCSTR lpFileName,
  DWORD  dwReserved
)
;
#endif

/*
	DeleteFileU8
	
	A UTF-8 version of the DeleteFileW () Windows API. See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-deletefilew
	for reference.
*/
BOOL DeleteFileU8(
  LPCSTR lpFileNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, DeleteFileU8)
(
  LPCSTR lpFileNameU8
)
;

/*
	DeleteFileU8long
	
	A UTF-8 version that supports long filenames of the DeleteFileW () Windows API. See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-deletefilew
	for reference.
	
	Since the function prepends the filename with a long filename prefix ("\\?\"),
	this version does not support paths that contain "." or ".." path components.
*/
BOOL DeleteFileU8long(
  LPCSTR lpFileNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, DeleteFileU8long)
(
  LPCSTR lpFileNameU8
)
;

/*
	EncryptFileU8
	
	UTF-8 version of EncryptFileW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-encryptfilew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL EncryptFileU8(
  LPCSTR lpFileNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, EncryptFileU8)
(
  LPCSTR lpFileNameU8
)
;
#endif

/*
	FileEncryptionStatusU8
	
	UTF-8 version of FileEncryptionStatusW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-fileencryptionstatusw
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL FileEncryptionStatusU8(
  LPCSTR  lpFileNameU8,
  LPDWORD lpStatus
)
;
TYPEDEF_FNCT_PTR (BOOL, FileEncryptionStatusU8)
(
  LPCSTR  lpFileNameU8,
  LPDWORD lpStatus
)
;
#endif

/*
	FileExists

	Returns TRUE if the given file exists and returns FALSE
	if it doesn't. It also returns FALSE if the given file name exists
	as a directory already.
	
	Note that the function cannot determine with absolute certainty that
	a file does not exists when it returns FALSE. The file could for
	instance be a network resource that is only temporarily not available.
*/
BOOL FileExistsU8 (const char *lpszFilenameU8);
TYPEDEF_FNCT_PTR (BOOL, FileExistsU8) (const char *lpszFilenameU8);

/*
	FileExistsU8long

	Returns TRUE if the given file exists and returns FALSE
	if it doesn't. It also returns FALSE if the given file name exists
	as a directory already.
	
	Note that the function cannot determine with absolute certainty that
	a file does not exists when it returns FALSE. The file could for
	instance be a network resource that is only temporarily not available.
	
	Since the function prepends the filename with a long filename prefix ("\\?\"),
	this version does not support paths that contain "." or ".." path components.
*/
BOOL FileExistsU8long (const char *lpszFilenameU8);
TYPEDEF_FNCT_PTR (BOOL, FileExistsU8long) (const char *lpszFilenameU8);

/*
	FileOrPathExists

	Returns TRUE if the given path or file name exists already and FALSE
	if it doesn't.

	Note that the function cannot determine with absolute certainty that
	a path does not exists when it returns FALSE. The file/directory could
	for instance be a network resource that is only temporarily not available.
*/
BOOL FileOrPathExistsU8 (const char *lpszFilenameU8);
TYPEDEF_FNCT_PTR (BOOL, FileOrPathExistsU8) (const char *lpszFilenameU8);
#define FileOrDirExistsU8(fn)	FileOrPathExistsU8 (fn)

/*
	FindFirstChangeNotificationU8
	
	A UTF-8 version of FindFirstChangeNotificationW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstchangenotificationw
	for more information.
*/
HANDLE FindFirstChangeNotificationU8(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
;
TYPEDEF_FNCT_PTR (HANDLE, FindFirstChangeNotificationU8)
(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
;

/*
	FindFirstChangeNotificationU8long
	
	A UTF-8 version of FindFirstChangeNotificationW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstchangenotificationw
	for more information.
	
	Before calling FindFirstChangeNotificationW () the function prepends a long filename
	prefix ("\\?\") if lpPathNameU8 doesn't have one already.
*/
HANDLE FindFirstChangeNotificationU8long(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
;
TYPEDEF_FNCT_PTR (HANDLE, FindFirstChangeNotificationU8long)
(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
;

/*
	FindFirstFileExU8
	
	A UTF-8 version of the Windows API function FindFirstFileExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
	for more information.

	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().
*/
HANDLE FindFirstFileExU8(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
;
TYPEDEF_FNCT_PTR (HANDLE, FindFirstFileExU8)
(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
;

/*
	FindFirstFileExU8long
	
	A UTF-8 version of the Windows API function FindFirstFileExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
	for more information.

	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	Before calling FindFirstFileExW () the function prepends a long filename
	prefix ("\\?\") if lpFileNameU8 doesn't start with one already. This means the function
	does not support relative paths.
*/
HANDLE FindFirstFileExU8long(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
;
TYPEDEF_FNCT_PTR (HANDLE, FindFirstFileExU8long)
(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
;

/*
	FindFirstFileU8
	
	A UTF-8 version of FindFirstFileW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew
	for more information.
	
	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	The function actually calls FindFirstFileExU8 (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
	for details. The search is case-sensitive and does not return 8.3 filenames.
*/
HANDLE FindFirstFileU8(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
;
TYPEDEF_FNCT_PTR (HANDLE, FindFirstFileU8)
(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
;

/*
	FindFirstFileU8long
	
	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	To continue with the next directory entry, call FindNextFileW (). There is no
	UTF-8 version called FindNextFileU8 ().

	Before calling FindFirstFileU8 () the function prepends a long filename
	prefix ("\\?\") if lpFileNameU8 doesn't start with one already. This means the function
	does not support relative paths.
*/
HANDLE FindFirstFileU8long(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
;
TYPEDEF_FNCT_PTR (HANDLE, FindFirstFileU8long)
(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
;

/*
	WIN32_FIND_DATAU8
	
	UTF-8 version of a WIN32_FIND_DATAW structure. Use
	WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW () to fill it.
	
	The member cAlternateFileName is not available.
	
	Note that UTF-8 encoded data stores between 1 and 4 octets per
	character. See https://en.wikipedia.org/wiki/UTF-8 for reference.
	MAX_PATH includes a NUL terminator, i.e. the precise value for
	UTF8_MAX_PATH would actually be 4 * MAX_PATH - 3.
*/
#ifndef UTF8_MAX_PATH
#define UTF8_MAX_PATH	(4 * MAX_PATH)
#endif
typedef struct win32_find_dataU8
{
	DWORD		dwFileAttributes;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		nFileSizeHigh;
	DWORD		nFileSizeLow;
	DWORD		dwReserved0;
	DWORD		dwReserved1;
	char		cFileName [UTF8_MAX_PATH];
	//WCHAR		cAlternateFileName[14];						// Not used.
	DWORD		dwFileType;
	DWORD		dwCreatorType;
	WORD		wFinderFlags;
} WIN32_FIND_DATAU8;

/*
	WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW
	
	Converts a WIN32_FIND_DATAW structure into a WIN32_FIND_DATAU8 structure.
	A WIN32_FIND_DATAU8 is version that uses UTF-8 for the cFileName member.
	
	Returns TRUE on success, FALSE otherwise. The function may return FALSE
	if the Windows UTF-16 filename does not fit in the UTF-8 cFileName
	member. See the definition of UTF8_MAX_PATH.
*/
void WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW (WIN32_FIND_DATAU8 *pwfdU8, WIN32_FIND_DATAW *pwfdW);
TYPEDEF_FNCT_PTR (void, WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW)
	(WIN32_FIND_DATAU8 *pwfdU8, WIN32_FIND_DATAW *pwfdW);

/*
	copyWIN32_FIND_DATAW
	
	Copies the entire WIN32_FIND_DATAW structure pwfdSrc points to to the structre
	pwfdDest points to.
*/
void copyWIN32_FIND_DATAW (WIN32_FIND_DATAW *pwfdDest, WIN32_FIND_DATAW *pwfdSrc);
TYPEDEF_FNCT_PTR (void, copyWIN32_FIND_DATAW)
	(WIN32_FIND_DATAW *pwfdDest, WIN32_FIND_DATAW *pwfdSrc);

/*
	copyWIN32_FIND_DATAU8

	Copies the entire WIN32_FIND_DATAU8 structure pu8fdSrc points to to the structre
	pu8fdDest points to.
*/
void copyWIN32_FIND_DATAU8 (WIN32_FIND_DATAU8 *pu8fdDest, WIN32_FIND_DATAU8 *pu8fdSrc);
TYPEDEF_FNCT_PTR (void, copyWIN32_FIND_DATAU8)
	(WIN32_FIND_DATAU8 *pu8fdDest, WIN32_FIND_DATAU8 *pu8fdSrc);

/*
	FindProcessByNameU8
	
	Returns a handle to the process szProcessName.
	
	Returns a handle to the process if the process exists, FALSE otherwise.
	If the function returns NULL, use GetLastError () to obtain more
	information. The function returns NULL and sets the last error to
	ERROR_FILE_NOT_FOUND if the process could not be found.

	To build this function, define HAVE_KERNEL32 and link to Kernel32.lib.
*/
#ifdef HAVE_KERNEL32
	HANDLE FindProcessByNameU8 (const char *szProcessName);
	TYPEDEF_FNCT_PTR (HANDLE, FindProcessByNameU8) (const char *szProcessName);
#endif

/*
	GetComputerNameExU8
	
	UTF-8 version of GetComputerNameExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getcomputernameexw
	for reference.
*/
BOOL GetComputerNameExU8(
  COMPUTER_NAME_FORMAT NameType,
  LPSTR                lpBuffer,
  LPDWORD              lpnSize
)
;
TYPEDEF_FNCT_PTR (BOOL, GetComputerNameExU8)
(
  COMPUTER_NAME_FORMAT NameType,
  LPSTR                lpBuffer,
  LPDWORD              lpnSize
)
;

/*
	GetComputerNameU8
	
	UTF-8 version of GetComputerNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamew
	for reference.
*/
BOOL GetComputerNameU8(
  LPSTR   lpBuffer,
  LPDWORD lpnSize
)
;
TYPEDEF_FNCT_PTR (BOOL, GetComputerNameU8)
(
  LPSTR   lpBuffer,
  LPDWORD lpnSize
)
;

/*
	GetEnvironmentVariableU8
	
	UTF-8 version of the Windows API GetEnvironmentVariableW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getenvironmentvariablew
	for more information.
*/
DWORD GetEnvironmentVariableU8(
  char		*szNameU8,
  char		*szOut,
  DWORD		nSize
)
;
TYPEDEF_FNCT_PTR (DWORD, GetEnvironmentVariableU8)
(
  char		*szNameU8,
  char		*szOut,
  DWORD		nSize
)
;

/*
	GetFileAttributesU8
	
	A UTF-8 version of GetFileAttributes (). Its parameters are identical to the ASCII
	version of GetFileAttributes (), which is GetFileAttributesA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
	for more information.
	
	The function expects the filename in the parameter lpFileNameU8 and converts it
	from UTF-8 to the Windows UTF-16 (UTF-2) character set before invoking
	GetFileAttributesW ().
	
	The return value of the function is the return value of GetFileAttributesW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_FILE_ATTRIBUTES.
*/
DWORD GetFileAttributesU8(
  LPCSTR lpFileNameU8
)
;
TYPEDEF_FNCT_PTR (DWORD, GetFileAttributesU8)
(
  LPCSTR lpFileNameU8
)
;

/*
	GetFileAttributesU8long
	
	A UTF-8 version of GetFileAttributes () that adds a long filename prefix ("\\?\") if not
	provided by the caller. The function does therefore not support relative paths.
	
	Its parameters are identical to the ASCII
	version of GetFileAttributes (), which is GetFileAttributesA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
	for more information.
	
	The function expects the filename in the parameter lpFileNameU8 and converts it
	from UTF-8 to the Windows UTF-16 (UTF-2) character set before invoking
	GetFileAttributesW ().
	
	The return value of the function is the return value of GetFileAttributesW () unless the
	conversion of lpFileNameU8 was not successful, in which case the function returns
	INVALID_FILE_ATTRIBUTES.
*/
DWORD GetFileAttributesU8long(
  LPCSTR lpFileNameU8
)
;
TYPEDEF_FNCT_PTR (DWORD, GetFileAttributesU8long)
(
  LPCSTR lpFileNameU8
)
;

/*
	GetFilePointerEx
	
	Obtains the current file pointer within a file and returns it at the location
	liCurrFilePointer points to.
	
	The function returns TRUE on success, FALSE otherwise.

	The function is implemented via a call to SetFilePointerEx (). See
	https://stackoverflow.com/questions/17707020/is-there-no-getfilepointerex-windows-api-function
	for more information.
*/
BOOL GetFilePointerEx (LARGE_INTEGER *liCurrFilePointer, HANDLE hFile);
TYPEDEF_FNCT_PTR (BOOL, GetFilePointerEx) (LARGE_INTEGER *liCurrFilePointer, HANDLE hFile);

/*
	GetFileSecurityU8
	
	UTF-8 version of the Windows API GetFileSecurityW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-getfilesecurityw
	for reference.
	
	To use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL GetFileSecurityU8(
		LPCSTR					lpFileName,
		SECURITY_INFORMATION	RequestedInformation,
		PSECURITY_DESCRIPTOR	pSecurityDescriptor,
		DWORD					nLength,
		LPDWORD					lpnLengthNeeded
)
;
TYPEDEF_FNCT_PTR (BOOL, GetFileSecurityU8)
(
		LPCSTR					lpFileName,
		SECURITY_INFORMATION	RequestedInformation,
		PSECURITY_DESCRIPTOR	pSecurityDescriptor,
		DWORD					nLength,
		LPDWORD					lpnLengthNeeded
)
;
#endif

/*
	Our filesystem types.
*/
enum en_wapi_fs_type
{
	FS_TYPE_ERROR,
	FS_TYPE_FAT,
	FS_TYPE_FAT32,
	FS_TYPE_NTFS
};

/*
	GetFileSystemType

	Returns the type of the file system of the specified root drive.
*/
enum en_wapi_fs_type GetFileSystemType (const char *chDriveRoot);
TYPEDEF_FNCT_PTR (enum en_wapi_fs_type, GetFileSystemType) (const char *chDriveRoot);

/*
	IsFileSystemFAT

	Returns or evaluates to TRUE if the file system of chDriveRoot is FAT.
*/
#if defined (DEBUG)
	BOOL IsFileSystemFAT (const char *chDriveRoot);
#else
	#define IsFileSystemFAT(drv)						\
		(FS_TYPE_FAT == GetFileSystemType (drv))
#endif

/*
	IsFileSystemFAT32

	Returns or evaluates to TRUE if the file system of chDriveRoot is FAT32.
*/
#if defined (DEBUG)
	BOOL IsFileSystemFAT32 (const char *chDriveRoot);
#else
	#define IsFileSystemFAT32(drv)						\
		(FS_TYPE_FAT32 == GetFileSystemType (drv))
#endif

/*
	IsFileSystemFATorFAT32

	Returns or evaluates to TRUE if the file system of chDriveRoot is either FAT or
	FAT32
*/
#ifdef DEBUG
	BOOL IsFileSystemFATorFAT32 (const char *chDriveRoot);
#else
	#define IsFileSystemFATorFAT32(drv)						\
		(IsFileSystemFAT32 (drv) || IsFileSystemFAT (drv))
#endif

/*
	IsFileSystemNTFS

	Returns or evaluates to TRUE if the file system of chDriveRoot is NTFS.
*/
#ifdef DEBUG
	BOOL IsFileSystemNTFS (const char *chDriveRoot);
#else
	#define IsFileSystemNTFS(drv)						\
		(FS_TYPE_NTFS == GetFileSystemType (drv))
#endif

/*
	GetNumberOfProcessesAttachedToConsole

	Returns the amount of processes attached to the current console.
*/
DWORD GetNumberOfProcessesAttachedToConsole (void);

/*
	IsOnlyProcessAttachedToConsole

	Returns true if the current process is the only process attached to the current
	console.
	
	In other words, the function returns true if for instance the process has been
	started by double-clicking on its icon from Windows Explorer, but returns false
	if it was started from the command-line.

	See https://devblogs.microsoft.com/oldnewthing/20160125-00/?p=92922 for more
	information.
*/
bool IsOnlyProcessAttachedToConsole (void);

/*
	GetFullPathNameU8
	
	UTF-8 version of GetFullPathNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamew
	for reference.
	
	Unlike GetFullPathNameW (), the function does not return the amount of characters
	but octets (bytes) it has written to lpBuffer, excluding the terminating NUL
	character. It also expects nBufferLength in octets instead of characters.
	
	Likewise, if the buffer is not big enough to hold the returned absolute path, the
	function returns the amount of octets (bytes) required to hold the returned path,
	including a terminating NUL character.
*/
DWORD GetFullPathNameU8(
  LPCSTR lpFileName,
  DWORD  nBufferLength,
  LPSTR  lpBuffer,
  LPSTR  *lpFilePart
)
;
TYPEDEF_FNCT_PTR (DWORD, GetFullPathNameU8)
(
  LPCSTR lpFileName,
  DWORD  nBufferLength,
  LPSTR  lpBuffer,
  LPSTR  *lpFilePart
)
;

/*
	GetModuleFileNameU8
	
	UTF-8 version of GetModuleFileNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew
	for reference.

	To build an assertion that the provided buffer is not too small, define
	GETMODULEFILENAMEU8_ASSERT_BUFFER_TOO_SMALL .
*/
DWORD GetModuleFileNameU8(
		HMODULE	hModule,
		LPSTR	lpFilenameU8,
		DWORD	nSize
)
;
TYPEDEF_FNCT_PTR (DWORD, GetModuleFileNameU8)
(
		HMODULE	hModule,
		LPSTR	lpFilenameU8,
		DWORD	nSize
)
;

/*
	GetModuleHandleU8
	
	UTF-8 version of GetModuleHandleW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlew
	for more info.
*/
HMODULE GetModuleHandleU8(
  LPCSTR lpModuleName
);
TYPEDEF_FNCT_PTR (HMODULE, GetModuleHandleU8)
(
  LPCSTR lpModuleName
);

/*
	GetPrivateProfileStringU8
	
	UTF-8 version of GetPrivateProfileStringW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getprivateprofilestringw
	for reference.
	
	Note that the return value of this function differs from the return value
	of GetPrivateProfileStringW (). The function does not return the number of
	characters but the number of octets written instead.
*/
DWORD GetPrivateProfileStringU8(
	LPCSTR lpAppName,
	LPCSTR lpKeyName,
	LPCSTR lpDefault,
	LPSTR  lpReturnedString,
	DWORD  nSize,
	LPCSTR lpFileName
)
;
TYPEDEF_FNCT_PTR (DWORD, GetPrivateProfileStringU8)
(
	LPCSTR lpAppName,
	LPCSTR lpKeyName,
	LPCSTR lpDefault,
	LPSTR  lpReturnedString,
	DWORD  nSize,
	LPCSTR lpFileName
)
;

/*
	GetSystemDirectoryU8

	UTF-8 version of GetSystemDirectoryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemdirectoryw
	for details.

	Note that the parameter uSize as well as the return value are in octets (bytes) rather than
	TCHARs.

	A typical directory returned by this function could be C:\Windows\System32.
*/
UINT GetSystemDirectoryU8(
	LPSTR	lpBuffer,
	UINT	uSize
);
TYPEDEF_FNCT_PTR (UINT, GetSystemDirectoryU8)
(
	LPSTR	lpBuffer,
	UINT	uSize
);

/*
	SystemDirectoryU8
	SystemDirectoryU8len
	DoneSystemDirectoryU8

	Obtain and keep a copy of the system directory, which is the folder retrieved by
	GetSystemDirectoryU8 ().

	The function SystemDirectoryU8 () obtains the path of the system directory (excluding
	a directory separator), while SystemDirectoryU8ln () obtains its length.

	You may call DoneSystemDirectoryU8 () to free the buffer that holds the path to the
	system directory. If DoneSystemDirectoryU8 () is not called before the application
	exits, the operating system reclaims the memory implicitely after the application
	has terminated.

	Since the system directory cannot change during the runtime of an application, and
	if the name of the system directory is required more than once, it is usually more
	efficient to call SystemDirectoryU8 () instead of GetSystemDirectoryU8 ().
*/
const char	*SystemDirectoryU8		(void);
size_t		SystemDirectoryU8len	(void);
void		DoneSystemDirectoryU8	(void);
TYPEDEF_FNCT_PTR (const char*,	SystemDirectoryU8)		(void);
TYPEDEF_FNCT_PTR (size_t,		SystemDirectoryU8len)	(void);
TYPEDEF_FNCT_PTR (void,			DoneSystemDirectoryU8)	(void);

/*
	GetSystemWindowsDirectoryU8

	UTF-8 version of the Windows API function GetSystemWindowsDirectoryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemwindowsdirectoryw
	for details.

	Note that the parameter uSize as well as the return value are in octets (bytes) rather than
	TCHARs.

	A typical directory returned by this function could be C:\Windows.
*/
UINT GetSystemWindowsDirectoryU8(
	LPSTR	lpBuffer,
	UINT	uSize
);
TYPEDEF_FNCT_PTR (UINT, GetSystemWindowsDirectoryU8)
(
	LPSTR	lpBuffer,
	UINT	uSize
);

/*
	SystemWindowsDirectoryU8
	SystemWindowsDirectoryU8len
	DoneSystemWindowsDirectoryU8

	Obtain and keep a copy of the shared Windows directory, which is the folder retrieved by
	GetSystemWindowsDirectoryU8 ().

	The function GetSystemWindowsDirectoryU8 () obtains the path of the shared Windows
	directory (excluding a directory separator), while SystemWindowsDirectoryU8len () obtains
	its length.

	You may call DoneSystemWindowsDirectoryU8 () to free the buffer that holds the path to the
	system directory. If DoneSystemWindowsDirectoryU8 () is not called before the application
	exits, the operating system reclaims the memory implicitely after the application
	has terminated.

	Since the shared Windows directory cannot change during the runtime of an application,
	and if the name of the system directory is required more than once, it is usually more
	efficient to call SystemWindowsDirectoryU8 () instead of GetSystemWindowsDirectoryU8 ().
*/
const char	*SystemWindowsDirectoryU8		(void);
size_t		SystemWindowsDirectoryU8len		(void);
void		DoneSystemWindowsDirectoryU8	(void);
TYPEDEF_FNCT_PTR (const char*,	SystemWindowsDirectoryU8)		(void);
TYPEDEF_FNCT_PTR (size_t,		SystemWindowsDirectoryU8len)	(void);
TYPEDEF_FNCT_PTR (void,			DoneSystemWindowsDirectoryU8)	(void);

/*
	GetUserNameU8
	
	UTF-8 version of GetUserNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew
	for more information.
	
	Note that the parameter pcbBuffer of this function differs from the version
	of GetUserNameW (). The function does not expect the number of characters at
	pcbBuffer but the size, in octets, of lpBuffer instead. Likewise, the function
	does not return the number of characters but the number of octets written to
	lpBuffer instead, which includes the terminating NUL character.
	
	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	BOOL GetUserNameU8(
	  LPSTR   lpBuffer,
	  LPDWORD pcbBuffer
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, GetUserNameU8)
	(
	  LPSTR   lpBuffer,
	  LPDWORD pcbBuffer
	)
	;
#endif

/*
	GetDefaultUserProfileDirectoryU8

	This function is untested!

	UTF-8 version of GetDefaultUserProfileDirectoryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/userenv/nf-userenv-getdefaultuserprofiledirectoryw
	for more information.

	Note that the parameter lpcchSize of this function differs from the version
	of GetDefaultUserProfileDirectoryU8 (). The function does not expect the number of
	characters at lpcchSize but the size, in octets, of lpProfileDirU8 instead. Likewise, the
	function does not return the number of characters but the number of octets written to
	lpProfileDirU8 instead, which includes the terminating NUL character.

	Define HAVE_USERENV to build this function and link to Userenv.lib.
*/
#ifdef HAVE_USERENV
	BOOL GetDefaultUserProfileDirectoryU8(
		LPSTR   lpProfileDirU8,
		LPDWORD lpcchSize
	);
	TYPEDEF_FNCT_PTR (BOOL, GetDefaultUserProfileDirectoryU8)
	(
		LPSTR   lpProfileDirU8,
		LPDWORD lpcchSize
	);
#endif

/*
	GetUserProfileDirectoryU8

	UTF-8 version of GetUserProfileDirectoryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/userenv/nf-userenv-getuserprofiledirectoryw
	for more information.

	Note that the parameter lpcchSize of this function differs from the version
	of GetUserProfileDirectoryW (). The function does not expect the number of
	characters at lpcchSize but the size, in octets, of lpProfileDirU8 instead. Likewise, the
	function does not return the number of characters but the number of octets written to
	lpProfileDirU8 instead, which includes the terminating NUL character.

	Define HAVE_USERENV to build this function and link to Userenv.lib.
*/
#ifdef HAVE_USERENV
	BOOL GetUserProfileDirectoryU8(
		HANDLE  hToken,
		LPSTR   lpProfileDirU8,
		LPDWORD lpcchSize
	);
	TYPEDEF_FNCT_PTR (BOOL, GetUserProfileDirectoryU8)
	(
		HANDLE  hToken,
		LPSTR   lpProfileDirU8,
		LPDWORD lpcchSize
	);
#endif

/*
	GetVolumeInformationU8
	
	A UTF-8 version of GetVolumeInformationW  (). Its parameters are identical to the
	ASCII version, which is GetVolumeInformationA (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationa
	and
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationw
	for more information.
	
	The function does currently not support the full set of functionality of
	GetVolumeInformationW (). The function expects the parameters lpVolumeNameBuffer
	to be NULL and nVolumeNameSize to be 0.
	
	The return value of the function is the return value of GetVolumeInformationW ().
*/
BOOL GetVolumeInformationU8(
  LPCSTR  lpRootPathName,
  LPSTR   lpVolumeNameBuffer,
  DWORD   nVolumeNameSize,
  LPDWORD lpVolumeSerialNumber,
  LPDWORD lpMaximumComponentLength,
  LPDWORD lpFileSystemFlags,
  LPSTR   lpFileSystemNameBuffer,
  DWORD   nFileSystemNameSize
)
;
TYPEDEF_FNCT_PTR (BOOL, GetVolumeInformationU8)
(
  LPCSTR  lpRootPathName,
  LPSTR   lpVolumeNameBuffer,
  DWORD   nVolumeNameSize,
  LPDWORD lpVolumeSerialNumber,
  LPDWORD lpMaximumComponentLength,
  LPDWORD lpFileSystemFlags,
  LPSTR   lpFileSystemNameBuffer,
  DWORD   nFileSystemNameSize
)
;

/*
	GetWinErrorTextU8
	
	Obtains a clear text message for the error code dwError. The error code is
	added to the text in parentheses and without line ending characters.
	
	The function returns TRUE on success, FALSE otherwise. A return value of
	FALSE usually means that a buffer size limit has been exceeded.
*/
BOOL GetWinErrorTextU8 (char *lpszBuf, DWORD dwSize, DWORD dwError);
TYPEDEF_FNCT_PTR (BOOL, GetWinErrorTextU8) (char *lpszBuf, DWORD dwSize, DWORD dwError);

/*
	InitiateSystemShutdownExU8

	UTF-8 version of the Windows API InitiateSystemShutdownExW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-initiatesystemshutdownexw
	for more information.

	To build and use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	BOOL InitiateSystemShutdownExU8(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwTimeout,
		BOOL   bForceAppsClosed,
		BOOL   bRebootAfterShutdown,
		DWORD  dwReason
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, InitiateSystemShutdownExU8)
	(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwTimeout,
		BOOL   bForceAppsClosed,
		BOOL   bRebootAfterShutdown,
		DWORD  dwReason
	)
	;
#endif
	
	/*
	InitiateShutdownU8

	UTF-8 version of the Windows API InitiateShutdownW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-initiateshutdownw
	for more information.

	To build and use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	DWORD InitiateShutdownU8(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwGracePeriod,
		DWORD  dwShutdownFlags,
		DWORD  dwReason
	)
	;
	TYPEDEF_FNCT_PTR (DWORD, InitiateShutdownU8)
	(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwGracePeriod,
		DWORD  dwShutdownFlags,
		DWORD  dwReason
	)
	;
#endif

enum en_is_cmd_argument
{
		EN_IS_CMD_ARG_ALLOW_DASH_OR_NO_DASH						// Allows "-Switch" and "Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_ONLY							// Only "-Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_DASH							// Only "--Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH					// Allows "--Switch" and "-Switch".
	,	EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH_OR_NO_DASH		// Allows double dash, no dash,
																//	and no dash at all.
	,	EN_IS_CMD_ARG_ALLOW_NO_DASH_ONLY						// Only without dash.
};

enum en_is_cmd_case_sensitive
{
		EN_IS_CMD_CASE_SENSITIVE
	,	EN_IS_CMD_CASE_INSENSITIVE
};

/*
	IsCmdArgumentSwitchW
	
	Compares the Windows UTF-16 text wcArgument points to with the Windows UTF-16
	text wcConstIs points to, which is expected to be a constant string. 
	The argument can be shortened down to at least nRelevant characters. The parameter
	enHow tells the function if single or double dashes before the actual switch
	are accepted or not.
	
	The function returns TRUE if the condition for the argument is met, FALSE if
	it is not met.
	
	Example:
	if (
			IsCmdArgumentSwitchW	(
				arg, L"doit", 2,
				EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH,
				EN_IS_CMD_CASE_IGNORE_CASE
							)
		)
	{
		// "-doit"			(EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH)
		// "--doit"			(EN_IS_CMD_ARG_ALLOW_DASH_DASH_OR_DASH)
		// "-do"			(nRelevant == 2)
		// "-Do"			(nRelevant == 2 and EN_IS_CMD_CASE_INSENSITIVE)
	}
*/
BOOL IsCmdArgumentSwitchW	(
			WCHAR							*wcArgument,
			const WCHAR						*wcConstIs,
			size_t							nRelevant,
			enum en_is_cmd_argument			enHow,
			enum en_is_cmd_case_sensitive	enCase
							)
;
TYPEDEF_FNCT_PTR (BOOL, IsCmdArgumentSwitchW)
							(
			WCHAR							*wcArgument,
			const WCHAR						*wcConstIs,
			size_t							nRelevant,
			enum en_is_cmd_argument			enHow,
			enum en_is_cmd_case_sensitive	enCase
							)
;

/*
	IsEqualUpToW
	
	Compares wc1 with wc2 where wc2 can be shorter but must be at least n characters
	long. The parameter cse sets the comparison to case-sensitive or case-insensitive.
	
	The idea of this function is to compare command-line argument switches without
	requiring the user to provide the full name of the switch.
	
	Example:
	
	Argument should be "delete", but we want to accept "del", "dele", and "delet" in
	upper or lower-case letters too but not "delicious".
	
	if (IsEqualUpToW (arg, "delete", 3, EN_IS_CMD_CASE_INSENSITIVE))
	{	// Accepted.
	}
*/
BOOL IsEqualUpToW	(
			const WCHAR						*wc1,				// Argument.
			const WCHAR						*wc2,				// What we expect.
			size_t							n,					// Minimum length that must fit.
			enum en_is_cmd_case_sensitive	cse
					)
;
TYPEDEF_FNCT_PTR (BOOL, IsEqualUpToW)
					(
			const WCHAR						*wc1,				// Argument.
			const WCHAR						*wc2,				// What we expect.
			size_t							n,					// Minimum length that must fit.
			enum en_is_cmd_case_sensitive	cse
					)
;

/*
	IsPathDirectoryU8
	
	Returns TRUE if the given path is a directory, FALSE otherwise. This is the
	UTF-8 version.
*/
BOOL IsPathDirectoryU8 (const char *szPath);
TYPEDEF_FNCT_PTR (BOOL, IsPathDirectoryU8) (const char *szPath);

/*
	IsPathDirectoryW
	
	Returns TRUE if the given path is a directory, FALSE otherwise. This is the
	Windows UTF-16 version.
*/
BOOL IsPathDirectoryW (const WCHAR *wcPath);
TYPEDEF_FNCT_PTR (BOOL, IsPathDirectoryW) (const WCHAR *wcPath);

/*
	LoadLibraryExU8

	UTF-8 version of the Windows API LoadLibraryW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryexw
	for more information.
*/
HMODULE LoadLibraryExU8(
	char	*szLibFileNameU8,
	HANDLE	hFile,
	DWORD	dwFlags
)
;
TYPEDEF_FNCT_PTR (HMODULE, LoadLibraryExU8)
(
	char	*szLibFileNameU8,
	HANDLE	hFile,
	DWORD	dwFlags
)
;

/*
	LoadLibraryU8

	UTF-8 version of the Windows API LoadLibraryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryw
	for more information.
*/
HMODULE LoadLibraryU8(
  char *chLibFileNameU8
)
;
TYPEDEF_FNCT_PTR (HMODULE, LoadLibraryU8)
(
  char *chLibFileNameU8
)
;

/*
	LookupAccountNameU8
	
	UTF-8 version of LookupAccountNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lookupaccountnamew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL LookupAccountNameU8(
  LPCSTR        lpSystemName,
  LPCSTR        lpAccountName,
  PSID          Sid,
  LPDWORD       cbSid,
  LPSTR         ReferencedDomainName,
  LPDWORD       cchReferencedDomainName,
  PSID_NAME_USE peUse
)
;
TYPEDEF_FNCT_PTR (BOOL, LookupAccountNameU8)
(
  LPCSTR        lpSystemName,
  LPCSTR        lpAccountName,
  PSID          Sid,
  LPDWORD       cbSid,
  LPSTR         ReferencedDomainName,
  LPDWORD       cchReferencedDomainName,
  PSID_NAME_USE peUse
)
;
#endif

/*
	LookupAccountSidU8
	
	UTF-8 version of LookupAccountSidW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lookupaccountsidw
	for more information.
	
	To use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
BOOL LookupAccountSidU8(
	LPCSTR        lpSystemNameU8,
	PSID          Sid,
	LPSTR         NameU8,
	LPDWORD       cchNameU8,
	LPSTR         ReferencedDomainNameU8,
	LPDWORD       cchReferencedDomainNameU8,
	PSID_NAME_USE peUse
)
;
TYPEDEF_FNCT_PTR (BOOL, LookupAccountSidU8)
(
	LPCSTR        lpSystemNameU8,
	PSID          Sid,
	LPSTR         NameU8,
	LPDWORD       cchNameU8,
	LPSTR         ReferencedDomainNameU8,
	LPDWORD       cchReferencedDomainNameU8,
	PSID_NAME_USE peUse
)
;
#endif

/*
	MessageBoxU8
	
	UTF-8 version of MessageBoxW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxw
	for reference.
	
	The function calls MessageBoxExU8 () with a wLanguageId parameter of 0, which uses
	the default system language.
	
	To build this function, link to User32.lib and define HAVE_USER32.
*/
#ifdef HAVE_USER32
int MessageBoxU8(
  HWND   hWnd,
  LPCSTR lpText,
  LPCSTR lpCaption,
  UINT   uType
)
;
TYPEDEF_FNCT_PTR (int, MessageBoxU8)
(
  HWND   hWnd,
  LPCSTR lpText,
  LPCSTR lpCaption,
  UINT   uType
)
;
#endif

/*
	MessageBoxExU8
	
	UTF-8 version of MessageBoxExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxexw
	for reference.
	
	To build this function, link to User32.lib and define HAVE_USER32.
*/
#ifdef HAVE_USER32
int MessageBoxExU8(
  HWND   hWnd,
  LPCSTR lpText,
  LPCSTR lpCaption,
  UINT   uType,
  WORD   wLanguageId
)
;
TYPEDEF_FNCT_PTR (int, MessageBoxExU8)
(
  HWND   hWnd,
  LPCSTR lpText,
  LPCSTR lpCaption,
  UINT   uType,
  WORD   wLanguageId
)
;
#endif

/*
	MaxiMiseThisConsoleWindow
	MaxiMizeThisConsoleWindow
	MaximiseThisConsoleWindow
	MaximizeThisConsoleWindow
	
	Maximises the console window of the current process, if it has one.
	
	The function returns TRUE if the current process has a console and the message
	to maximise it has been posted successfully. It returns FALSE if the message
	could not be posted or if the current process does not have a console window.
	
	To use this function, define HAVE_WINUSER and link to User32.lib.
*/
#ifdef HAVE_WINUSER
	BOOL MaxiMiseThisConsoleWindow (void);
	TYPEDEF_FNCT_PTR (BOOL, MaxiMiseThisConsoleWindow) (void);
	#define MaxiMizeThisConsoleWindow()						\
				MaxiMiseThisConsoleWindow ()
	#define MaximiseThisConsoleWindow()						\
				MaxiMiseThisConsoleWindow ()
	#define MaximizeThisConsoleWindow()						\
				MaxiMiseThisConsoleWindow ()
#endif

/*
	MiniMiseThisConsoleWindow
	MiniMizeThisConsoleWindow
	MinimiseThisConsoleWindow
	MinimizeThisConsoleWindow
	
	Minimises the console window of the current process, if it has one.
	
	The function returns TRUE if the current process has a console and the message
	to minimise it has been posted successfully. It returns FALSE if the message
	could not be posted or if the current process does not have a console window.
	
	To use this function, define HAVE_WINUSER and link to User32.lib.
*/
#ifdef HAVE_WINUSER
	BOOL MiniMiseThisConsoleWindow (void);
	TYPEDEF_FNCT_PTR (BOOL, MiniMiseThisConsoleWindow) (void);
	#define MiniMizeThisConsoleWindow()						\
				MiniMiseThisConsoleWindow ()
	#define MinimiseThisConsoleWindow()						\
				MiniMiseThisConsoleWindow ()
	#define MinimizeThisConsoleWindow()						\
				MiniMiseThisConsoleWindow ()
#endif

/*
	RestoreThisConsoleWindow

	Restores the console window of the current process, if it has one, meaning that
	the window is resized to its normal size.
	
	The function returns TRUE if the current process has a console and the message
	to restore it has been posted successfully. It returns FALSE if the message
	could not be posted or if the current process does not have a console window.
	
	To use this function, define HAVE_WINUSER and link to User32.lib.
*/
#ifdef HAVE_WINUSER
	BOOL RestoreThisConsoleWindow (void);
	TYPEDEF_FNCT_PTR (BOOL, RestoreThisConsoleWindow) (void);
#endif

/*
	UTF-8 version of MoveFileW ().
	See https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilew
	for details.
*/
BOOL MoveFileU8(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
);
TYPEDEF_FNCT_PTR (BOOL, MoveFileU8)
(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
);

/*
	MoveFileU8long
	
	UTF-8 version of MoveFileW () that supports long file names but not relative paths.
	The function prepends a long filename prefix to both parameters before passing them on
	to MoveFileW () if one is not already there.
	
	See https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilew
	for details.
*/
BOOL MoveFileU8long(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
);
TYPEDEF_FNCT_PTR (BOOL, MoveFileU8long)
(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
);

/*
	MoveFileExU8

	UTF-8 version of MoveFileExW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefileexw
	for more information.
*/
BOOL MoveFileExU8(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
;
TYPEDEF_FNCT_PTR (BOOL, MoveFileExU8)
(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
;

/*
	MoveFileExU8long

	UTF-8 version of MoveFileExW () that supports long file names but not relative paths.
	The function prepends a long filename prefix to both parameters before passing them on
	to MoveFileExW () if one is not already there. See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefileexw
	for more information.
*/
BOOL MoveFileExU8long(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
;
TYPEDEF_FNCT_PTR (BOOL, MoveFileExU8long)
(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
;

/*
	MoveFileWithProgressU8

	UTF-8 version of MoveFileWithProgressW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilewithprogressw
	for details.
*/
BOOL MoveFileWithProgressU8(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
;
TYPEDEF_FNCT_PTR (BOOL, MoveFileWithProgressU8)
(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
;

/*
	MoveFileWithProgressU8long

	UTF-8 version of MoveFileWithProgressW () that supports long file names but not relative
	paths. The function prepends a long filename prefix to both parameters before passing them
	on to MoveFileWithProgressW () if one is not already there. See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefilewithprogressw
	for details.
*/
BOOL MoveFileWithProgressU8long(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
;
TYPEDEF_FNCT_PTR (BOOL, MoveFileWithProgressU8long)
(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
;

/*
	MoveToRecycleBinU8
	MoveToRecycleBinW
	
	Moves the given file to the recycle bin. The function ending with U8 is the
	UTF-8 version while the function ending with W is the Windows UTF-16 version.

	The Windows API SHFileOperationW () requires that the filename is terninated
	with two consecutive NUL characters. While MoveToRecycleBinU8 () implicitely adds
	a second NUL terminator before it calls SHFileOperationW (), the function
	MoveToRecycleBinW () does not. The caller is responsible for providing a string
	that is NUL-terminated twice for the parameter wcFileName. See
	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shfileoperationw
	for more information.

	Returns TRUE on success, FALSE otherwise.
	
	Define #ifdef HAVE_SHELLAPI and link to Shell32.lib to build these functions.
*/
#ifdef HAVE_SHELLAPI
	BOOL MoveToRecycleBinU8 (const char *chFileName);
	TYPEDEF_FNCT_PTR (BOOL, MoveToRecycleBinU8) (const char *chFileName);
#endif
#ifdef HAVE_SHELLAPI
	BOOL MoveToRecycleBinW (const WCHAR *wcFileName);
	TYPEDEF_FNCT_PTR (BOOL, MoveToRecycleBinW) (const WCHAR *wcFileName);
#endif

/*
	NetUserEnumU8

	UTF-8 version of the NetUserEnum () Windows API.
	https://learn.microsoft.com/en-us/windows/win32/api/lmaccess/nf-lmaccess-netuserenum?redirectedfrom=MSDN

	To use this function, define HAVE_NETAPI32 and link to Netapi32.lib.
*/
#ifdef HAVE_NETAPI32
	NET_API_STATUS NET_API_FUNCTION NetUserEnumU8(
		LPCSTR  servernameU8,
		DWORD   level,
		DWORD   filter,
		LPBYTE  *bufptr,
		DWORD   prefmaxlen,
		LPDWORD entriesread,
		LPDWORD totalentries,
		PDWORD  resume_handle
	);
	TYPEDEF_FNCT_PTR (NET_API_STATUS NET_API_FUNCTION, NetUserEnumU8
	(
		LPCSTR  servernameU8,
		DWORD   level,
		DWORD   filter,
		LPBYTE  *bufptr,
		DWORD   prefmaxlen,
		LPDWORD entriesread,
		LPDWORD totalentries,
		PDWORD  resume_handle
	);
#endif

/*
	OpenEventU8

	UTF-8 version of OpenEventW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-openeventw
	for more information.
*/
HANDLE OpenEventU8(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
;
TYPEDEF_FNCT_PTR (HANDLE, OpenEventU8)
(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
;

/*
	OpenEventLogU8

	UTF-8 version of OpenEventLogW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openeventlogw
	for more information.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	HANDLE OpenEventLogU8(
		LPCSTR lpUNCServerNameU8,
		LPCSTR lpSourceNameU8
	)
	;
	TYPEDEF_FNCT_PTR (HANDLE, OpenEventLogU8)
	(
		LPCSTR lpUNCServerNameU8,
		LPCSTR lpSourceNameU8
	)
	;
#endif

/*
	ClearEventLogU8

	UTF-8 version of ClearEventLogW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-cleareventlogw
	for more information.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	BOOL ClearEventLogU8(
	  HANDLE  hEventLog,
	  LPCSTR lpBackupFileNameU8
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, ClearEventLogU8)
	(
	  HANDLE  hEventLog,
	  LPCSTR lpBackupFileNameU8
	)
	;
#endif

/*
	OpenFileMappingU8

	UTF-8 version of OpenFileMappingW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-openfilemappingw
	for details.
*/
HANDLE OpenFileMappingU8(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
;
TYPEDEF_FNCT_PTR (HANDLE, OpenFileMappingU8)
(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
;

/*
	OpenMutexU8

	UTF-8 version of OpenMutexW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-openmutexw
	for details.
*/
HANDLE OpenMutexU8(
  DWORD		dwDesiredAccess,
  BOOL		bInheritHandle,
  LPCSTR	lpNameU8
)
;
TYPEDEF_FNCT_PTR (HANDLE, OpenMutexU8)
(
  DWORD		dwDesiredAccess,
  BOOL		bInheritHandle,
  LPCSTR	lpNameU8
)
;

/*
	OpenSCManagerU8
	
	UTF-8 version of OpenSCManagerW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-openscmanagerw
	for reference.

	Return value
	
	If the function succeeds, the return value is a handle to the specified service
	control manager database.
	If the function fails, the return value is NULL. To get extended error information,
	call GetLastError ().

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	SC_HANDLE OpenSCManagerU8(
	  LPCSTR lpMachineName,
	  LPCSTR lpDatabaseName,
	  DWORD  dwDesiredAccess
	)
	;
	TYPEDEF_FNCT_PTR (SC_HANDLE, OpenSCManagerU8)
	(
	  LPCSTR lpMachineName,
	  LPCSTR lpDatabaseName,
	  DWORD  dwDesiredAccess
	)
	;
#endif

/*
	OpenServiceU8
	
	UTF-8 version of OpenServiceW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-openservicew
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	SC_HANDLE OpenServiceU8(
	  SC_HANDLE hSCManager,
	  LPCSTR    lpServiceName,
	  DWORD     dwDesiredAccess
	)
	;
	TYPEDEF_FNCT_PTR (SC_HANDLE, OpenServiceU8)
	(
	  SC_HANDLE hSCManager,
	  LPCSTR    lpServiceName,
	  DWORD     dwDesiredAccess
	)
	;
#endif

/*
	PathsEqualfromEndW

	Compares the executable and the argument from the end.

	Returns TRUE if the executable and the argument appear to name the same
	file.
*/
BOOL PathsEqualfromEndW (WCHAR *exe, WCHAR *arg);
TYPEDEF_FNCT_PTR (BOOL, PathsEqualfromEndW) (WCHAR *exe, WCHAR *arg);

/*
	PathIsUNCU8
	
	UTF-8 version of the Windows API PathIsUNCW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathisuncw
	for more information.
	
	To use this function, define HAVE_SHLWAPI and link to Shlwapi.lib.
*/
#ifdef HAVE_SHLWAPI
	BOOL PathIsUNCU8(
		LPSTR	pszPathU8
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, PathIsUNCU8)
	(
		LPSTR	pszPathU8
	)
	;
#endif

/*
	PathIsNetworkPathU8
	
	UTF-8 version of the Windows API PathIsNetworkPathW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathisnetworkpathw
	for more information.
	
	To use this function, define HAVE_SHLWAPI and link to Shlwapi.lib.
*/
#ifdef HAVE_SHLWAPI
	BOOL PathIsNetworkPathU8(
		LPSTR	pszPathU8
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, PathIsNetworkPathU8)
	(
		LPSTR	pszPathU8
	)
	;
#endif

/*
	PathFindNextComponentU8

	UTF-8 version of the Windows API PathFindNextComponenW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfindnextcomponentw
	for reference.

	To use this function, define HAVE_SHLWAPI. Linking to Shlwapi.lib is not required.
	Unlike PathFindNextComponenW (), this function is implemented directly in the code file and
	does not require linking to Shlwapi.lib. However, for compatibility reasons with
	PathFindNextComponenW (), it is recommended to define HAVE_SHLWAPI and link to Shlwapi.lib.
*/
#ifdef HAVE_SHLWAPI
	LPCSTR PathFindNextComponentU8(
		LPSTR pszPathU8
	)
	;
	TYPEDEF_FNCT_PTR (LPCSTR, PathFindNextComponentU8)
	(
		LPSTR pszPathU8
	)
	;
#endif

/*
	RegisterEventSourceU8
	
	UTF-8 version of RegisterEventSourceW ().
	See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registereventsourcew .
	
	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	HANDLE RegisterEventSourceU8(
	  LPCSTR lpUNCServerName,
	  LPCSTR lpSourceName
	)
	;
	TYPEDEF_FNCT_PTR (HANDLE, RegisterEventSourceU8)
	(
	  LPCSTR lpUNCServerName,
	  LPCSTR lpSourceName
	)
	;
#endif

/*
	RegisterServiceCtrlHandlerU8
	
	UTF-8 function of RegisterServiceCtrlHandlerW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-registerservicectrlhandlerw
	for reference.
	
	To use this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerU8(
	  LPCSTR             lpServiceName,
	  LPHANDLER_FUNCTION lpHandlerProc
	)
	;
	TYPEDEF_FNCT_PTR (SERVICE_STATUS_HANDLE, RegisterServiceCtrlHandlerU8)
	(
	  LPCSTR             lpServiceName,
	  LPHANDLER_FUNCTION lpHandlerProc
	)
	;
#endif

/*
	RegisterServiceCtrlHandlerExU8
	
	UTF-8 function of RegisterServiceCtrlHandlerExW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-registerservicectrlhandlerexw
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerExU8(
	  LPCSTR                lpServiceName,
	  LPHANDLER_FUNCTION_EX lpHandlerProc,
	  LPVOID                lpContext
	)
	;
	TYPEDEF_FNCT_PTR (SERVICE_STATUS_HANDLE, RegisterServiceCtrlHandlerExU8)
	(
	  LPCSTR                lpServiceName,
	  LPHANDLER_FUNCTION_EX lpHandlerProc,
	  LPVOID                lpContext
	)
	;
#endif

/*
	RemoveDirectoryU8
	
	UTF-8 version of RemoveDirectoryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-removedirectoryw
	for details.
*/
BOOL RemoveDirectoryU8(
	LPCSTR lpPathNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, RemoveDirectoryU8)
(
	LPCSTR lpPathNameU8
)
;

/*
	RemoveDirectoryU8long
	
	UTF-8 version of RemoveDirectoryW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-removedirectoryw
	for details.
	
	This function prepends a long filename prefix if one does not exist yet. Although
	very often quite convenient due to the removal of the path limit this renders the
	function unusable for relative paths. Use RemoveDirectoryU8 () if the path is
	relative or contains path climbers ("../").
*/
BOOL RemoveDirectoryU8long(
	LPCSTR lpPathNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, RemoveDirectoryU8long)
(
	LPCSTR lpPathNameU8
)
;

/*
	ReportEventU8
	
	UTF-8 version of the WinAPI function ReportEventW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-reporteventw
	for reference.

	Define HAVE_ADVAPI32 to build this function and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	BOOL ReportEventU8(
	  HANDLE hEventLog,
	  WORD   wType,
	  WORD   wCategory,
	  DWORD  dwEventID,
	  PSID   lpUserSid,
	  WORD   wNumStrings,
	  DWORD  dwDataSize,
	  LPCSTR *lpStrings,
	  LPVOID lpRawData
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, ReportEventU8)
	(
	  HANDLE hEventLog,
	  WORD   wType,
	  WORD   wCategory,
	  DWORD  dwEventID,
	  PSID   lpUserSid,
	  WORD   wNumStrings,
	  DWORD  dwDataSize,
	  LPCSTR *lpStrings,
	  LPVOID lpRawData
	)
	;
#endif

/*
	SetConsoleCodePageToANSI
	
	Calls SetConsoleCP () and SetConsoleOutputCP () with the parameter 1252
	to switch the console to ANSI Latin I (Western).
*/
void SetConsoleCodePageToANSI (void);
TYPEDEF_FNCT_PTR (void, SetConsoleCodePageToANSI) (void);

/*
	SetConsoleCodePageToUTF8
	
	Calls SetConsoleCP () and SetConsoleOutputCP () with the parameter CP_UTF8
	to switch the console to UTF-8.
*/
void SetConsoleCodePageToUTF8 (void);
TYPEDEF_FNCT_PTR (void, SetConsoleCodePageToUTF8) (void);

/*
	SetConsoleEnableANSI

	Calls GetConsoleMode () and SetConsoleMode to set the console mode flag
	ENABLE_VIRTUAL_TERMINAL_PROCESSING, which enables processing of ANSI escape
	sequences.
*/
bool SetConsoleEnableANSI (void);
TYPEDEF_FNCT_PTR (bool, SetConsoleEnableANSI) (void);

/*
	WinSetStdoutToUTF16

	Changes stdout to UTF-16. This is required to correctly display UTF-16 characters
	in a console window. See
	https://giodicanio.com/2023/06/01/how-to-print-unicode-text-to-the-windows-console-in-c-plus-plus/ .
	It really doesn't seem to work without this.

	The function returns the return value of _setmode ().
*/
int WinSetStdoutToUTF16 (void);
TYPEDEF_FNCT_PTR (int, WinSetStdoutToUTF16) (void);

/*
	WinSetStdinToUTF16

	Changes stdin to UTF-16. This is required to correctly expect UTF-16 characters
	from input in a console window. See
	https://giodicanio.com/2023/06/01/how-to-print-unicode-text-to-the-windows-console-in-c-plus-plus/ .
	It really doesn't seem to work without this.

	The function returns the return value of _setmode ().
*/
int WinSetStdinToUTF16 (void);
TYPEDEF_FNCT_PTR (int, WinSetStdinToUTF16) (void);

/*
	SetCurrentDirectoryU8
	
	UTF-8 version of SetCurrentDirectoryW ().
*/
BOOL SetCurrentDirectoryU8(
  const char *lpPathName
)
;
TYPEDEF_FNCT_PTR (BOOL, SetCurrentDirectoryU8)
(
  const char *lpPathName
)
;

/*
	SetCurrentDirectoryU8long
	
	UTF-8 version of SetCurrentDirectoryU8 () that supports long filenames but does
	not accept relative paths.
*/
BOOL SetCurrentDirectoryU8long(
  const char *lpPathNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, SetCurrentDirectoryU8long)
(
  const char *lpPathNameU8
)
;

/*
	SetFileAttributesU8
	
*/
DWORD SetFileAttributesU8(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
;
TYPEDEF_FNCT_PTR (DWORD, SetFileAttributesU8)
(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
;

/*
	SetFileAttributesU8long
	
*/
DWORD SetFileAttributesU8long(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
;
TYPEDEF_FNCT_PTR (DWORD, SetFileAttributesU8long)
(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
;

/*
	SetFileSecurityU8

	UTF-8 version of SetFileSecurityW (). See
	https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-setfilesecurityw
	for details.

	To use/build this function, define HAVE_ADVAPI32 and link to Advapi32.lib.
*/
#ifdef HAVE_ADVAPI32
	BOOL SetFileSecurityU8(
	  char					*lpFileNameU8,
	  SECURITY_INFORMATION	SecurityInformation,
	  PSECURITY_DESCRIPTOR	pSecurityDescriptor
	)
	;
	TYPEDEF_FNCT_PTR (BOOL, SetFileSecurityU8)
	(
	  char					*lpFileNameU8,
	  SECURITY_INFORMATION	SecurityInformation,
	  PSECURITY_DESCRIPTOR	pSecurityDescriptor
	)
	;
#endif

/*
	Action flags for TerminateProcessControlled ().
*/
#define TERMCHILDPROCCONTROLLED_CTRL_C			(0x0001)
#define TERMCHILDPROCCONTROLLED_CTRL_BREAK		(0x0002)
#define TERMCHILDPROCCONTROLLED_WM_CLOSE		(0x0004)
#define TERMCHILDPROCCONTROLLED_WM_QUIT			(0x0008)
#define TERMCHILDPROCCONTROLLED_TERMINATE		(0x0010)

/*
	Wait flags for TerminateProcessControlled ().
*/
#define TERMCHILDPROCCONTROLLED_WAIT_CTRL_C		(0x0100)
#define TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK	(0x0200)
#define TERMCHILDPROCCONTROLLED_WAIT_WM_CLOSE	(0x0400)
#define TERMCHILDPROCCONTROLLED_WAIT_WM_QUIT	(0x0800)
#define TERMCHILDPROCCONTROLLED_WAIT_TERMINATE	(0x1000)

/*
	TerminateProcessControlled

	Terminates the given process hProcess in a controlled manner. The function attempts
	to terminate the process in the following order:

	- Send CTRL-C to the process.
	- Send CTRL-Break to the process.
	- Post a WM_CLOSE message to all windows of the process.
	- Post a WM_QUITE message to all windows of the process.

	The parameter waitTime specifies the time in milliseconds the function waits after
	each attempt for the process to exit.

	The caller can control which of the above attempts is made but they cannot change
	the order of these attempts. The caller can further control if the function should
	wait after each of these attempts. For instance, to only attempt to terminate the
	process by sending it a CTRL-Break event, set uiFlags to
	TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK | TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK.
	This instructs the function to attempt a CTRL-Break and then wait waitTime
	milliseconds for the process to exit. Specify all flags for the attempts that should
	be made, and specify the additional TERMCHILDPROCCONTROLLED_WAIT_ flags to wait
	for the process to exit after the attempt in question.

	The function returns true if the process has exited within waitTime ms after each
	termination attempt. It returns false if the process has not exited within waitTime.

	Note that waitTime is waited for after each separate attempt to terminate the process.
	For instance, if you specify the flags TERMCHILDPROCCONTROLLED_CTRL_C to attempt
	sending CTRL-C and TERMCHILDPROCCONTROLLED_WAIT_CTRL_C to wait for its success, plus
	TERMCHILDPROCCONTROLLED_CTRL_BREAK and TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK to
	send CTRL-Break and wait for it to succeed, the function waits up to twice waitTime
	in case the first attempt (CTRL-C) is unsuccessful.
*/
bool TerminateProcessControlled (HANDLE hProcess, uint16_t uiFlags, DWORD waitTime);
TYPEDEF_FNCT_PTR (bool, TerminateProcessControlled) (HANDLE hProcess, uint16_t uiFlags, DWORD waitTime);

/*
	IsFirstArgumentExeArgumentW

	Returns TRUE if the function determined that the first argument in the argument
	list pargv points to is the name of the executable as required by POSIX systems
	but not for Windows applications.

	The function returns FALSE if it considers the first argument not being the
	name of the executable file.
*/
BOOL IsFirstArgumentExeArgumentW (int *pargc, WCHAR **pargv []);
TYPEDEF_FNCT_PTR (BOOL, IsFirstArgumentExeArgumentW) (int *pargc, WCHAR **pargv []);

/*
	SwallowExeArgumentW
	
	Examines the first element of the command-line argument list pargv points to
	and disposes of it if is an executable argument.

	Applications for POSIX systems require the first command-line argument (index 0)
	to be the path to the executable called. In Windows, this is optional. This
	function tries to identify if the first argument is the name of executable itself,
	and if it is disposes of it. This way an application can assume that the first
	argument it examines is the first argument it expects.

	The function returns TRUE if an exe argument has been swallowed, FALSE otherwise.
*/
BOOL SwallowExeArgumentW (int *pargc, WCHAR **pargv []);
TYPEDEF_FNCT_PTR (BOOL, SwallowExeArgumentW) (int *pargc, WCHAR **pargv []);

/*
	InsertExeArgumentIfMissingW

	Examines the first element of the command-line argument list pargv points to
	and inserts an executable argument as the first element if it is considered missing.

	The function returns pargv if the first argument of the argument list is the
	name of the executable. If the first argument is not the name of the executable,
	the function allocates a new argument list with the name of the executable inserted
	as the first element of the list, increments the value pargc points to, and returns
	a pointer to the newly allocated argument list with the name of the executable
	inserted.
	
	In the latter case the caller is responsible for deallocating the returned
	buffer, in the former case the caller must not deallocate it. However, deallocating
	should normally not be required since to allow the new argument list to  live throughout
	the application's lifetime, and when the software exits the operating system deallocates
	it automatically.

	WCHAR **argvWithExe = InsertExeArgumentIfMissingW (&argc, &argv)) == argv)
	{
		DoStuff ();
	} else
	{
		DoStuff ();
		free (argvWithExe);
	}
*/
WCHAR **InsertExeArgumentIfMissingW (int *pargc, WCHAR **pargv []);
TYPEDEF_FNCT_PTR (WCHAR **, InsertExeArgumentIfMissingW) (int *pargc, WCHAR **pargv []);

/*
	WNetGetUniversalNameU8

	UTF-8 version of the Windows API WNetGetUniversalNameW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winnetwk/nf-winnetwk-wnetgetuniversalnamew
	for reference.

	To use this function, define HAVE_MPR and link to Mpr.lib.
*/
#ifdef HAVE_MPR
	DWORD WNetGetUniversalNameU8(
		LPCSTR  lpLocalPathU8,
		DWORD   dwInfoLevel,
		LPVOID  lpBuffer,
		LPDWORD lpBufferSize
	)
	;
	TYPEDEF_FNCT_PTR (DWORD, WNetGetUniversalNameU8)
	(
		LPCSTR  lpLocalPathU8,
		DWORD   dwInfoLevel,
		LPVOID  lpBuffer,
		LPDWORD lpBufferSize
	)
	;
#endif

/*
	WritePrivateProfileStringU8
	
	UTF-8 function of the Windows API WritePrivateProfileStringW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-writeprivateprofilestringw
	for details.
*/
BOOL WritePrivateProfileStringU8(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8
)
;
TYPEDEF_FNCT_PTR (BOOL, WritePrivateProfileStringU8)
(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8
)
;

/*
	Only an example! The API does not support long filename prefixes!
	
	WritePrivateProfileStringU8long
	
	UTF-8 function of the Windows API WritePrivateProfileStringW (). See
	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-writeprivateprofilestringw
	for details.
	
	This function prepends the filename with a long filename prefix (if it doesn't have
	one yet) before it calls WritePrivateProfileStringW (). This means the parameter
	lpFileNameU8absolute must be an absolute path and not contain relative path components
	like ".\" and "..\".
*/
/*
BOOL WritePrivateProfileStringU8long(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8absolute
)
;
*/

/*
	vfprintfU8toU16stream

	UTF-8 version of vfprintf ().

	Should only be used if stream is set to UTF-16.
*/
int vfprintfU8toU16stream (FILE *stream, const char *format, va_list ap);
TYPEDEF_FNCT_PTR (int, vfprintfU8toU16stream) (FILE *stream, const char *format, va_list ap);

/*
	fprintfU8toU16stream

	UTF-8 version of fprintf ().
	
	Should only be used if stream is set to UTF-16.
*/
int fprintfU8toU16stream (FILE *stream, const char *format, ...);
TYPEDEF_FNCT_PTR (int, fprintfU8toU16stream) (FILE *stream, const char *format, ...);

/*
	printfU8toU16stdout

	UTF-8 version of printf (). See http://www.cplusplus.com/reference/cstdio/printf/ .
	
	Should only be used if Windows console output is set to UTF-16.
*/
#define printfU8toU16stdout(...) fprintfU8toU16stream (stdout, __VA_ARGS__)

/*
	putsU8toU16stdout

	UTF-8 version of puts (). See http://www.cplusplus.com/reference/cstdio/puts/ .
	
	Should only be used if Windows console output is set to UTF-16.
*/
int putsU8toU16stdout (const char *strU8);
TYPEDEF_FNCT_PTR (int, putsU8toU16stdout) (const char *strU8);


EXTERN_C_END

#endif															// Of #ifdef _WIN32.

#endif															// Of #ifndef WINDOWSU8_H.
/****************************************************************************************

	File		WinAPI_U8_Test.h
	Why:		Test module for WinAPI_U8.
	OS:			Windows
	Author:		Thomas
	Created:	2021-04-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-04-17	Thomas			Created.

****************************************************************************************/

#ifndef WINAPI_U8_TEST_H
#define WINAPI_U8_TEST_H

#ifdef _WIN32
	#ifndef CUNILOG_USE_COMBINED_MODULE

		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./WinAPI_U8.h"
		#else
			#include "./WinAPI_U8.h"
		#endif

	#endif
#endif

#ifdef _WIN32

EXTERN_C_BEGIN

/*
	Test_WinAPI_U8
	
	Test function for the WinAPI_U8 module.
*/
#ifdef BUILD_TEST_WINAPI_U8_FNCT
	bool Test_WinAPI_U8 (void);
#else
	#define Test_WinAPI_U8()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifdef _WIN32.

#endif														// Of #ifndef WINAPI_U8_TEST_H.
/****************************************************************************************

	File		WinAPI_ReadDirFncts.h
	Why:		Functions to read directory contents
	OS:			Windows
	Created:	2022-01-15

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-01-15	Thomas			Created.

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

#ifndef WINAPI_READDIRFNCTS_H
#define WINAPI_READDIRFNCTS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_U8.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef _WIN32

#ifndef HAVE_STRWILDCARDS
	#error This module requires HAVE_STRWILDCARDS to be defined and strwildcards.c/h
#endif

#ifndef WIN_READDIR_FNCTS_DEFAULT_MEM_ALIGNMENT
#define WIN_READDIR_FNCTS_DEFAULT_MEM_ALIGNMENT			(8)
#endif
#ifndef WIN_READDIR_FNCTS_DEFAULT_STACKVAR_THRSHLD
#define WIN_READDIR_FNCTS_DEFAULT_STACKVAR_THRSHLD		(64)
#endif
#ifndef WIN_READDIR_FNCTS_DEFAULT_MASK_THRSHLD
#define WIN_READDIR_FNCTS_DEFAULT_MASK_THRSHLD			(64)
#endif

/*
	Parameter u of the function ReadDirectoryEntriesSDIRW_WU8 ().
*/
enum enrdirentssdirw
{
	EN_READ_DIR_ENTS_SDIRW_UTF8,
	EN_READ_DIR_ENTS_SDIRW_UTF16
};

/*
	One singly-linked list element. Note the WIN32_FIND_DATAW member, which is in
	Windows UTF-16.
*/
typedef struct sDirW
{
	struct sDirW		*_next;
	WIN32_FIND_DATAW	wfdW;
} SDIRW;

/*
	The plinth (base) of an SDIRW singly-linked list.
*/
typedef struct sDirWplinth
{
	uint64_t				nElements;						// Amount of elements in the list.
	SDIRW					*_first;						// Pointer to the first element of the
															//	singly-linked list.
	SDIRW					**_array;						// Array of sorted pointers.
	union
	{
		void				*pstrPathWorU8;					// UTF-8 or UTF-16;
		char				*chPathU8;						// UTF-8.
		unsigned char		*ucPathU8;						// Unsigned UTF-8.
		WCHAR				*wcPathU8;						// UTF-16.
	} UTF8orUTF16;
	enum enrdirentssdirw	u;
} SDIRWPLINTH;

/*
	SRDIRONEENTRYSTRUCT

	The structure passed on to the ignore callback function.
*/
typedef struct srdirOneEntryStruct
{
	union
	{
		// Unchanged path provided by the caller.
		const void			*pstrPathWorU8;					// UTF-8 or UTF-16;
		const char			*chPathU8;						// UTF-8.
		const unsigned char	*ucPathU8;						// Unsigned UTF-8.
		const WCHAR			*wcPathU8;						// UTF-16.
	} UTF8orUTF16;
	enum enrdirentssdirw	u;								// Which union member?
	//size_t					

	WIN32_FIND_DATAW		*pwfd;
	void					*pCustom;

	// The file mask as provided by the caller.
	const char				*szFileMask;
	size_t					lnFileMask;						// Its length. Cannot be
															//	USE_STRLEN.

	// The folder plus search mask for FindFirstFileU8long ().
	SMEMBUF					mbSearchPath;					// "C:\\dir\*"
	size_t					lnSearchPath;

	// The full path, starting with chPathU8.
	SMEMBUF					mbFullPathU8;
	size_t					lnFullPathU8;
	size_t					lnInitPathU8;

	// Everything between szFullPathU8 and szFileNameU8.
	char					*szPathU8;
	size_t					lnPathU8;

	// The filename alone converted to UTF-8. Not all functions set these members.
	//	The function ForEachDirectoryEntryMaskU8 () sets both members.
	char					*szFileNameU8;
	size_t					stFileNameU8;
} SRDIRONEENTRYSTRUCT;

/*
	Callback function for ReadDirectoryEntriesSDIRW_WU8 () that returns TRUE
	for directory entries to be ignored.
*/
typedef BOOL (*IgnoreCondCB)(SRDIRONEENTRYSTRUCT *);

/*
	Callback function for memory allocations within ReadDirectoryEntriesSDIRW_WU8 ().
	The parameter is the size of the memory block to allocate.
*/
typedef void *(*RDEMallocCB)(size_t);

/*
	ReadDirectoryEntriesSDIRW_WU8_ex

	Reads the contents of a directory/folder and returns the first element of a
	singly-linked list of SDIRW structures.

	If pdwEntries is not NULL the function returns the amount of entries found/
	enumerated at the location it points to. This is the amount of list entries
	returned.

	To deallocate the memory used by the singly-linked list, the returned pointer
	can be passed on to the ReleaseDirectoryEntriesSDIRW () function, which
	releases the list.

	The parameter strPathWorU8 can either be in Windows UTF-16 encoding or UTF-8.
	The parameter u distinguishes the character set of this parameter. Set u to
	EN_READ_DIR_ENTS_SDIRW_UTF16 for the function to expect strPathWorU8 to be
	in UTF-16. Set u to EN_READ_DIR_ENTS_SDIRW_UTF8 for the function to treat the
	path name in UTF-8.

	Note that the parameter strPathWorU8 names the path of the directory whose
	entries are to be enumerated and that this parameter can either be in UTF-8 or
	UTF-16, depending on the parameter u, but the returned SDIRW elements hold
	the filenames in the WIN32_FIND_DATAW structure wfdW, which is always in
	Windows UTF-16.

	strPathWorU8	The path whose directory entries are to be retrieved. Can be
					UTF-8 or Windows UTF-16, depending on the paramter u.

	u				Specifies the character set of the parameter strPathWorU8
					(read as "string Path W or U8").
					EN_READ_DIR_ENTS_SDIRW_UTF8		-> strPathWorU8 is in UTF-8
					EN_READ_DIR_ENTS_SDIRW_UTF16	-> strPathWorU8 is in UTF-16

	pdwEntries		Pointer to the amount of singly-linked list entries the
					function created. If this is parameter is NULL the amount is
					not returned.

	pIgnore			Callback function that returns TRUE for each entry to be
					ignored. Entries for which this function returns FALSE are
					added to the singly-linked list. If this parameter is NULL,
					the default callback function
					ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition () will be
					called to determine whether an entry should be ignored or not.
					The default function ignores the entries ".", "..", and hidden
					and system files. See the definition of the function
					ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition () in the code
					file for reference.

	pCustom			A custom pointer argument passed on to the callback function
					pIgnore as the member pCustom of the SRDIRONEENTRYSTRUCT structure
					that can be used for custom data by the caller. This can be NULL
					if it is not required.

	pMalloc			A custom memory allocation function. Basically a replacement
					for malloc () or ubf_malloc (). If this parameter is NULL
					ubf_malloc () is used for allocating list elements.

	The function returns NULL if the directory is empty or if there is not enough
	space on the heap to allocate memory for all directory entries.

	In case of a heap error, the function sets *pdwEntries to (DWORD) -1, provided
	that pwdEntries is not NULL. It is therefore recommended to provide the
	parameter pdwEntries to distinguish between an empty folder and a heap error.
	Alternatively GetLastError () returns ERROR_NOT_ENOUGH_MEMORY as an indicator.
	When not enough space is available on the heap, the function releases already
	created list elements first.

	The caller is responsible for calling ReleaseDirectoryEntriesSDIRW () on the
	returned singly-linked liste when the data is not required anymore.
*/
SDIRW *ReadDirectoryEntriesSDIRW_WU8_ex	(
						void					*strPathWorU8,
						enum enrdirentssdirw	u,
						DWORD					*pdwEntries,
						IgnoreCondCB			pIgnore,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;

/*
	ReadDirectoryEntriesSDIRW_W
	ReadDirectoryEntriesSDIRW_U8

	These functions read the contents of a directory/folder and return the first
	element of a singly-linked list of SDIRW structures. They call
	ReadDirectoryEntriesSDIRW_WU8_ex () with the appropriate parameter for the
	character set of the path parameter. ReadDirectoryEntriesSDIRW_W () calls
	ReadDirectoryEntriesSDIRW_WU8_ex () with a parameter u of
	EN_READ_DIR_ENTS_SDIRW_UTF16 while ReadDirectoryEntriesSDIRW_U8 () calls it
	with a paramter u of EN_READ_DIR_ENTS_SDIRW_UTF8.

	Like ReadDirectoryEntriesSDIRW_WU8_ex (), if pdwEntries is not NULL the functions
	return the amount of entries found/enumerated at the location this parameter
	points to.

	To deallocate the memory used by the singly-linked list the returned pointer
	can be passed on to the ReleaseDirectoryEntriesSDIRW () function, which
	releases the list.

	Note that in case of the UTF-8 version of the function the parameter strPathU8
	uses the UTF-8 character set. This is in contrast to the returned SDIRW elements.
	The filenames in the WIN32_FIND_DATAW structure wfdW are in Windows UTF-16.
*/
SDIRW *ReadDirectoryEntriesSDIRW_W		(
						WCHAR					*wstrPath,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;
SDIRW *ReadDirectoryEntriesSDIRW_U8		(
						char					*strPathU8,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;

/*
	ReleaseDirectoryEntriesSDIRW

	Releases the singly-linked list swd points to from the heap. The function
	always returns NULL.

	Use ReleaseDirectoryEntriesSDIRW_cnt () instead to retrieve the amount of directory
	entries released.
*/
SDIRW *ReleaseDirectoryEntriesSDIRW (SDIRW *swd);

/*
	ReleaseDirectoryEntriesSDIRW_cntReleaseDirectoryEntriesSDIRW_cnt

	Releases the singly-linked list swd points to from the heap and returns the
	amount of list elements freed. Use the function ReleaseDirectoryEntriesSDIRW ()
	instead if the amount of list elements freed is not required.
*/
uint64_t ReleaseDirectoryEntriesSDIRW_cnt (SDIRW *swd);

/*
	The callback function for ForEachDirectoryEntryU8 ().

	The function ForEachDirectoryEntryU8 () stops when the callback function returns
	FALSE.
*/
/* Obsolete declaration.
typedef bool (*pForEachDirEntryU8) (SRDIRONEENTRYSTRUCT *psdE, void *pCustom);
*/
typedef bool (*pForEachDirEntryU8) (SRDIRONEENTRYSTRUCT *psdE);

/*
	ForEachDirectoryEntryU8_Ex
	ForEachDirectoryEntryU8

	Enumerates the UTF-8 directory strPathU8 points to and calls the callback
	function fedEnt for each found file or folder entry.

	The function ForEachDirectoryEntryU8_Ex () uses a re-usable SMEMBUF structure for its
	internal heap allocations while ForEachDirectoryEntryU8 () does not, which makes
	ForEachDirectoryEntryU8_Ex () slightly faster when a directory contains many subfolders.

	strPathU8			The path as a UTF-8 string. This parameter is passed on to
						the Windows API FindFirstFileW () as parameter lpFileName and can
						contain wildcard characters.

	fedEnt				Pointer to the callback function. The function is called
						for each found entry.

	pCustom				Pointer to custom data that is passed on to the callback
						function.

	*pnSubLevels		A pointer to an unsigned int variable that contains the
						amount of subfolder levels to enumerate. If this parameter
						is NULL or points to a value of 0, only the folder in strPathU8
						is processed. Any other number specifies the amount of
						subfolders to be enumerated by recursively calling this
						function. The function uses the variable to count its
						recursion levels. This means if it is not NULL and points
						to a value greater than 0, the function alters it for
						each subfolder level. Make sure the value is correct each
						time before the function is called.

	pmb                 Function ForEachDirectoryEntryU8_Ex () only: A pointer to an
                        initialised SMEMBUF structure the function uses as a buffer
						to store the path of the directory to process when it calls
						itself recursively (when pnSubLevels is neihter NULL nor points
						to a value of 0).
                        If there are many subfolders to process, this can reduce the
						amount of required heap allocations significantly. The caller is
						responsible for initialising the structure before the call and
						deallocating its resources again after the call.

	The function returns the amount of entries processed. Since the callback function
	is not called for the "." and ".." directory entries, these are not included in
	the return value.

	Since the function does not indicate when or if an error occurred, the caller is
	advised to check with a call to GetLastError () if the function succeeded. Do not check
	for ERROR_SUCCESS. The function buffers the system error returned either by FindFirstFileU8 ()
	or by the very last call to FindNextFileW () so that the caller does not see the system
	error code returned by FindClose (), which would be of no use.

	If no files can be found, the function is assumed to have succeeded when GetLastError ()
	returns ERROR_FILE_NOT_FOUND. In case at least one file or folder is found, the function
	is assumed to have succeeded when GetLastError () returns a value of ERROR_NO_MORE_FILES.
	Hence, expect ERROR_FILE_NOT_FOUND when the function's return value is 0, and
	ERROR_NO_MORE_FILES for return values greater than 0.

	See
	https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew and
	https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findnextfilew for
	more information.

	The function can return early if the callback function fedEnt returns false. In this case
	the error retrieved by GetLastError () is whatever the callback function set it to. For
	instance, the callback function could call SetLastError (ERROR_OPERATION_ABORTED) before
	it returns false and SetLastError (ERROR_SUCCESS) before it returns true. Upon return of
	ForEachDirectoryEntryU8 (), the caller could then check GetLastError () for
	ERROR_OPERATION_ABORTED, which means the callback function returned false, for
	ERROR_FILE_NOT_FOUND, which would indicate that no files were found, and for
	ERROR_NO_MORE_FILES, indicating success.
*/
#ifdef HAVE_MEMBUF
size_t ForEachDirectoryEntryU8_Ex	(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels,
				SMEMBUF                 *pmb
									)
;
#endif
size_t	ForEachDirectoryEntryU8		(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels
									)
;

/*
	ForEachDirectoryEntryMaskU8

	This function exists to provide better compatibilibty between Windows and POSIX.
	Folder and file mask are split into two parameters.

	strFolderU8			The folder for which the function is to retrieve the directory
						listing. The folder name may end with a forward or backslash.
						This must be an absolute path. The folder cannot be relative, i.e.
						cannot contain path navigators ("..\") unless they can be resolved
						entirely.

	lenFolderU8			The length of strFolderU8, excluding a terminating NUL character.
						This parameter can be USE_STRLEN, which causes the function to invoke
						strlen () on strFolderU8 to obtain its length.

	strFileMaskU8		The filename or mask for the files to call the callback function.
						It can contain wildcard characters to match the files for whom
						the callback function will be called.
						This parameter can be NULL, in which case the function calls the
						callback function on every single file found.
						This is not a simple "*" or "*.*" file mask as known from
						Windows or POSIX. See remarks below the parameter descriptions.

	lenFileMaskU8		The length of strFileMask, excluding a terminating NUL character.
						This parameter can be USE_STRLEN, which causes the function to invoke
						strlen () on strFileMask to obtain its length.
						The parameter is ignored if strFileMaskU8 is NULL.

	fedEnt				Pointer to the callback function. The function is called
						for each found entry.

	pCustom				Pointer to custom data that is passed on to the callback
						function.

	*pnSubLevels		A pointer to an unsigned int variable that contains the
						amount of subfolder levels to enumerate. If this parameter
						is NULL or points to a value of 0, only the folder in strPathU8
						is processed. Any other number specifies the amount of
						subfolders to be enumerated by recursively calling this
						function. The function uses the variable to count its
						recursion levels. This means if it is not NULL and points
						to a value greater than 0, the function alters it for
						each subfolder level. Make sure the value is correct each
						time before the function is called.

	The function reads a base directory, which is strFolderU8. It ignores the "." and ".."
	folders returned by the operating system but matches every other file or directory
	against strFileMaskU8. Matching starts with file or directory objects inside the folder
	strFolderU8, which is different from how operating systems and system utilities usually
	match wildcards and files or directories.

	If pnSubLevels is NULL or points to a value of 0, only files and folders (file objects)
	in strFolderU8 are matched, meaning known patterns like "???.txt" or "*" or "*.bmp"
	work as usual. However, since matching starts with file objects in strFolderU8,
	matching is different when pnSubLevels allows the function to climb further down a
	directory tree.

	<strFolderU8>/<objects in strFolderU8>/<more objects>
	.             ^
	.             !
	.             +-------- Matching against strFileMaskU8 starts here.

	If strFolderU8 is "/home/user", and the function should return text files in
	"/home/user/Downloads", strFileMaskU8 needs to be "Downloads/*.txt".
	If the function should return text files in any folder inside or below "/home/usr",
	strFileMaskU8 needs to be "**.txt".

	See description of the functions matchWildcardPattern () and/or matchWildcardPatternW ()
	in strwildcards.h on how patterns are created and matched.
*/
size_t ForEachDirectoryEntryMaskU8	(
				const char				*strFolderU8,
				size_t					lenFolderU8,
				const char				*strFileMaskU8,
				size_t					lenFileMaskU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels
									)
;

EXTERN_C_END

#ifndef CUNILOG_BUILD_READDIR_TESTFNCT
//#define CUNILOG_BUILD_READDIR_TESTFNCT
#endif

/*
	Tests.
*/
#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
	bool ForEachDirectoryEntryMaskU8TestFnct (void);
#else
	#define ForEachDirectoryEntryMaskU8TestFnct()	(true)
#endif

#endif														// Of #ifdef _WIN32.

#endif														// Of #ifndef WINAPI_READDIRFNCTS_H.
/****************************************************************************************

	File		CompressNTFS_U8.h
	Why:		Performs NTFS compression.
	OS:			Windows
	Created:	2020-12-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-12-06	Thomas			Created.

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

#ifndef COMPRESSNTFS_U8
#define COMPRESSNTFS_U8

#ifdef _WIN32

#include <stdbool.h>
#include <Windows.h>

#ifdef	__cplusplus
	extern "C"	{
#endif

/*
	CompressFileNTFS_U8ExLong
	
	Compresses or uncompresses the file in chFileName. The function calls
	CreateFileU8long () to open the file, meaning it supports very long
	paths. Filename restrictions apply, for instance path navigators ("../")
	are not supported by this function. See
	https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
	for more information. Use CompressFileNTFS_U8Ex () to support path
	navigators.
	
	usState can be:
	0 = COMPRESSION_FORMAT_NONE
	1 = COMPRESSION_FORMAT_DEFAULT
	2 = COMPRESSION_FORMAT_LZNT1
	
	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8ExLong (const char *chFileName, USHORT usState);

/*
	CompressFileNTFS_U8Ex
	
	Compresses or uncompresses the file in chFileName. The function calls
	CreateFileU8 () to open the file, meaning it does not support very long
	paths but the filename can contain path navigators ("../".
	
	usState can be:
	0 = COMPRESSION_FORMAT_NONE
	1 = COMPRESSION_FORMAT_DEFAULT
	2 = COMPRESSION_FORMAT_LZNT1
	
	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8Ex (const char *chFileName, USHORT usState);

/*
	CompressFileNTFS_U8long
	
	Compresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8ExLong ().

	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8long (const char *chFileName);

/*
	CompressFileNTFS_U8
	
	Compresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8Ex ().

	Returns true on success, false otherwise.
*/
bool CompressFileNTFS_U8 (const char *chFileName);

/*
	UnCompressFileNTFS_U8long
	
	Uncompresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8ExLong ().

	Returns true on success, false otherwise.
*/
bool UnCompressFileNTFS_U8long (const char *chFileName);

/*
	UnCompressFileNTFS_U8
	
	Uncompresses the file with the name chFileName points to by calling
	CompressFileNTFS_U8Ex ().

	Returns true on success, false otherwise.
*/
bool UnCompressFileNTFS_U8 (const char *chFileName);

/*
	enntfscompressresult

	Return values for the compression check functions.
*/
enum enntfscompressresult
{
	ntfscompress_compressed,
	ntfscompress_uncompressed,
	ntfscompress_error
};
typedef enum enntfscompressresult enntfscompressresult;

/*
	IsFileNTFSCompressedByName
	IsFileNTFSCompressedByHandle

	The functions return ntfscompress_compressed if the given file is NTFS compressed. They
	return ntfscompress_uncompressed if the file is not compressed.
	
	On error, for instance if the file doesn't exist, the functions return ntfscompress_error.
	You can call GetLastError () to obtain more details about why the functions failed.
*/
enntfscompressresult IsFileNTFSCompressedByName (const char *szFileName);
enntfscompressresult IsFileNTFSCompressedByHandle (HANDLE hFile);

#ifdef	__cplusplus
				}
#endif

#endif															// Of #ifdef _WIN32

#endif															// Of #ifndef COMPRESSNTFS_U8.
/****************************************************************************************

	File:		WinSharedMutex.h
	Why:		Implements a mutex for interprocess-locking.
	OS:			C99
	Author:		Thomas
	Created:	2021-02-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-02-23	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	See module shared_mutex in folder OS/POSIX.
	This module here is meant to be a compatible Windows version.
*/

/*
MIT License

Copyright (c) 2018 Oleg Yamnikov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifdef _WIN32

#ifndef W_SHARED_MUTEX_INCLUDED
#define W_SHARED_MUTEX_INCLUDED

#ifndef CUNILOG_USE_COMBINED_MODULE
	#include "./WinAPI_U8.h"
#endif


EXTERN_C_BEGIN

#ifdef PLATFORM_IS_WINDOWS

typedef struct ssharedmutext
{
	HANDLE		h;
	bool		bCreatedHere;
} *shared_mutex_t;

// Initialize a new shared mutex with given `name`. If a mutex
// with such name exists in the system, it will be loaded.
// Otherwise a new mutes will by created.
//
// In case of any error, it will be printed into the standard output
// and the returned structure will have `ptr` equal `NULL`.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** In case when the mutex appears to be uncreated,
// this function becomes *non-thread-safe*. If multiple threads
// call it at one moment, there occur several race conditions,
// in which one call might recreate another's shared memory
// object or rewrite another's pthread mutex in the shared memory.
// There is no workaround currently, except to run first
// initialization only before multi-threaded or multi-process
// functionality.
shared_mutex_t WinInitSharedMutex(const char *name);

// Close access to the shared mutex and free all the resources,
// used by the structure.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not destroy the mutex. The mutex would not
// only be available to other processes using it right now,
// but also to any process which might want to use it later on.
// For complete desctruction use `shared_mutex_destroy` instead.
//
// **NOTE:** It will not unlock locked mutex.
int WinCloseSharedMutex(shared_mutex_t mutex);

// Close and destroy shared mutex.
// Any open pointers to it will be invalidated.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not unlock locked mutex.
void WinDestroySharedMutex(shared_mutex_t mutex);

#endif															// Of #ifdef UBF_WINDOWS.

EXTERN_C_END

#endif															// Of #ifdef _WIN32

#endif															// W_SHARED_MUTEX_INCLUDED.
/****************************************************************************************

	File:		WinExeFileName.h
	Why:		Obtains the name of the executable.
	OS:			Windows.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

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

#ifndef WIN_EXEFILENAME_H
#define WIN_EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

#ifdef DEBUG
	#ifndef EXEFILENAME_MALLOC_BLOCKSIZE
	#define EXEFILENAME_MALLOC_BLOCKSIZE		(32)
	#endif
#else
	#ifndef EXEFILENAME_MALLOC_BLOCKSIZE
	#define EXEFILENAME_MALLOC_BLOCKSIZE		(256)
	#endif
#endif

EXTERN_C_BEGIN

#ifdef OS_IS_WINDOWS

/*
	WinObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t WinObtainExecutableModuleName (SMEMBUF *mb)
;

/*
	WinObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path or ".exe" filename extension.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "C:/temp/app.exe" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t WinObtainAppNameFromExecutableModule (SMEMBUF *mb)
;

/*
	WinObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
size_t WinObtainPathFromExecutableModule (SMEMBUF *mb)
;

#endif														// Of #ifdef OS_IS_WINDOWS.

EXTERN_C_END

#endif														// Of #ifndef WIN_EXEFILENAME_H.
/****************************************************************************************

	File:		PsxCompressFile.h
	Why:		Module to compress files on POSIX platforms.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-17	Thomas			Created.

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

#ifndef U_PSXCOMPRESS_FILE_H
#define U_PSXCOMPRESS_FILE_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX


#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef U_PSXCOMPRESS_FILE_H.
/****************************************************************************************

	File:		PsxExeFileName.h
	Why:		Obtains the name of the executable.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-14

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-14	Thomas			Created.

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

#ifndef PSX_EXEFILENAME_H
#define PSX_EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	PsxObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t PsxObtainExecutableModuleName (SMEMBUF *mb)
;

/*
	PsxObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "/temp/app" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
size_t PsxObtainAppNameFromExecutableModule (SMEMBUF *mb)
;

/*
	PsxObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
size_t PsxObtainPathFromExecutableModule (SMEMBUF *mb)
;

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef PSX_EXEFILENAME_H.
/****************************************************************************************

	File:		PsxReadDirFncts.h
	Why:		POSIX functions to read directory/folder contents.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-22

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-22	Thomas			Created.

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

#ifndef PSXREADDIRFNCTS_H
#define PSXREADDIRFNCTS_H

#include <stdbool.h>

#ifdef PLATFORM_IS_POSIX
	#include <dirent.h>
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"								// Currently actually not required.
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../mem/membuf.h"						// Currently actually not required.
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	The structure for the callback.
*/
typedef struct sonedirent
{
	struct dirent	*dirEnt;
	void			*pCustom;
} SONEDIRENT;

/*
	The callback function for ForEachPsxDirEntry ().

	The function ForEachPsxDirEntry () stops when the callback function returns
	FALSE.
*/
typedef bool (*pForEachPsxDirEntry) (SONEDIRENT *pod);

/*
	ForEachPsxDirEntry

*/
uint64_t ForEachPsxDirEntry	(
				const char				*strFolderName,
				pForEachPsxDirEntry		fedEnt,
				void					*pCustom,
				unsigned int			*pnSubLevels
							)
;

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_END

#endif														// Of #ifndef PSXREADDIRFNCTS_H.
/****************************************************************************************

	File:		PsxHome.h
	Why:		Obtains a user's home directory on POSIX.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-03

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-03	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Functions for retrieving username, user home directory, etc. on POSIX.
	
	This module/unit can also be included on Windows builds but does not provide
	any functionality.
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

#ifndef U_PSX_HOME_H
#define U_PSX_HOME_H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	/*
	// See https://www.man7.org/linux/man-pages/man3/getpwnam.3.html .
	#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE
	#endif
	#ifndef _BSD_SOURCE
	#define _BSD_SOURCE
	#endif
	#ifndef _SVID_SOURCE
	#define _SVID_SOURCE
	#endif
	*/
#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_POSIX

/*
	InitPsxHome
	
	Initialises the module/unit. Calling this function is not required because all
	other functions initialise the module implicitely. The caller may save a few
	CPU cycles by calling this function first.
*/
bool InitPsxHome (void)
;

/*
	UserHomeDirectoryPOSIX

	Returns the current user's home folder. The optional parameter plen retrieves
	the length of the returned string, if not NULL.

	The function is only re-entrant after its first invocation.

	The function returns a pointer to a string that contains the name of the current
	user's home directory.
*/
const char *UserHomeDirectoryPOSIX (size_t *plen)
;

/*
	UserTrashFolder
	
	Returns a user's trash folder.
*/
const char *UserTrashFolder (size_t *plen)
;

EXTERN_C_END

#endif														// Of #ifdef PLATFORM_IS_POSIX.

EXTERN_C_BEGIN

#ifdef DEBUG
	#ifndef PSXHOME_BUILD_TEST_FNCT
	#define PSXHOME_BUILD_TEST_FNCT
	#endif
#endif

/*
	TestPsxHome
	
	Function to test this module/unit.
*/
#ifdef PLATFORM_IS_POSIX
	#ifdef PSXHOME_BUILD_TEST_FNCT
		bool TestPsxHome (void);
	#else
		#define TestPsxHome()	(true)
	#endif
#else
		#define TestPsxHome()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_PSX_HOME_H.
/****************************************************************************************

	File:		PsxTrash.h
	Why:		Handles the trash can for POSIX.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-03

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-03	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The name of this module is actually slightly wrong as it isn't really POSIX.
	It tries to follow the XDG specification
	(https://specifications.freedesktop.org/trash-spec/latest/)
	on trash (https://specifications.freedesktop.org/trash-spec/latest/).
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

#ifndef U_PSX_TRASH_H
#define U_PSX_TRASH_H

#ifdef OS_IS_LINUX

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	MoveFileToTrashPOSIX

	Moves the file named in szFilename to the trash bin/can on POSIX according to the
	XDG specification. See
	https://specifications.freedesktop.org/trash-spec/latest/ for details.

	The path of szFilename can neither be relative nor can it contain path navigators
	("../"). It must be a corrected absolute path.
*/
bool MoveFileToTrashPOSIX (const char *szFilename);

EXTERN_C_END

#endif														// Of #ifdef OS_IS_LINUX.

#endif														// Of #ifndef U_PSX_TRASH_H.
/****************************************************************************************

	File:		PsxSharedMutex.h
	Why:		Implements a mutex for interprocess-locking.
	OS:			C99
	Author:		Thomas
	Created:	2021-02-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-02-23	Thomas			Created. See
							 https://gist.github.com/marcetcheverry/d2f62672ee98bf54bfad7b8bc0840616
							 and
							 https://gist.github.com/yamnikov-oleg/abf61cf96b4867cbf72d .

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Building requires linking with pthread and librt.
*/

/*
MIT License

Copyright (c) 2018 Oleg Yamnikov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef U_PSX_SHARED_MUTEX_H
#define U_PSX_SHARED_MUTEX_H

#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
		#include "./../../pre/functionptrtpydef.h"
	#endif

#endif


#ifdef PLATFORM_IS_POSIX

EXTERN_C_BEGIN

#include <sys/stat.h>

#include <pthread.h> // pthread_mutex_t, pthread_mutexattr_t,
                     // pthread_mutexattr_init, pthread_mutexattr_setpshared,
                     // pthread_mutex_init, pthread_mutex_destroy

// Structure of a shared mutex.
typedef struct shared_mutex_t {
  pthread_mutex_t *ptr; // Pointer to the pthread mutex and
                        // shared memory segment.
  int shm_fd;           // Descriptor of shared memory object.
  char* name;           // Name of the mutex and associated
                        // shared memory object.
  int created;          // Equals 1 (true) if initialization
                        // of this structure caused creation
                        // of a new shared mutex.
                        // Equals 0 (false) if this mutex was
                        // just retrieved from shared memory.
} shared_mutex_t;

// Initialize a new shared mutex with given `name`. If a mutex
// with such name exists in the system, it will be loaded.
// Otherwise a new mutes will by created.
//
// In case of any error, it will be printed into the standard output
// and the returned structure will have `ptr` equal `NULL`.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** In case when the mutex appears to be uncreated,
// this function becomes *non-thread-safe*. If multiple threads
// call it at one moment, there occur several race conditions,
// in which one call might recreate another's shared memory
// object or rewrite another's pthread mutex in the shared memory.
// There is no workaround currently, except to run first
// initialization only before multi-threaded or multi-process
// functionality.
shared_mutex_t PsxInitSharedMutex(const char *name, mode_t mode);

// Close access to the shared mutex and free all the resources,
// used by the structure.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not destroy the mutex. The mutex would not
// only be available to other processes using it right now,
// but also to any process which might want to use it later on.
// For complete desctruction use `shared_mutex_destroy` instead.
//
// **NOTE:** It will not unlock locked mutex.
int PsxCloseSharedMutex(shared_mutex_t mutex);

// Close and destroy shared mutex.
// Any open pointers to it will be invalidated.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not unlock locked mutex.
int PsxDestroySharedMutex(shared_mutex_t mutex);

EXTERN_C_END

#endif															// Of #ifdef PLATFORM_IS_POSIX.

#endif															// Of #ifndef U_PSX_SHARED_MUTEX_H.
/****************************************************************************************

	File:		TrashCan.h
	Why:		Trash can function for Apple devices.
	OS:			C99
	Author:		Robert Guetzkow; Thomas (wrapper module only)
	Created:	2024-10-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-21	Thomas			This wrapper module created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This module is mainly a wrapper for Robert Guetzkow's trashcan_soft_delete () function
	for Apple devices. See
	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .
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

/* MIT License
	*
	* Copyright (c) 2019 Robert Guetzkow
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	*
	* The above copyright notice and this permission notice shall be included in all
	* copies or substantial portions of the Software.
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	* SOFTWARE. 
	*/

// See	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .

#ifndef APPLE_TRASHCAN_H_INCL
#define APPLE_TRASHCAN_H_INCL

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef OS_IS_MACOS

#include <CoreFoundation/CoreFoundation.h>
#include <objc/runtime.h>
#include <objc/message.h>

#ifndef LIBTRASHCAN_ERROR
#define LIBTRASHCAN_ERROR	(0)
#endif
#ifndef LIBTRASHCAN_SUCCESS
#define LIBTRASHCAN_SUCCESS	(0)
#endif

EXTERN_C_BEGIN

/*
	trashcan_soft_delete_apple

	Robert Guetzkow's trashcan_soft_delete () function. See
	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .
*/
static int trashcan_soft_delete_apple (const char *path);

EXTERN_C_END

#endif														// Of #ifdef OS_IS_MACOS.

#endif														// Of #ifndef APPLE_TRASHCAN_H_INCL.
/****************************************************************************************

	File:		CompressFile.h
	Why:		Module to compress a file on different platforms.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-10-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-17	Thomas			Created.

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

#ifndef U_COMPRESS_FILE_H
#define U_COMPRESS_FILE_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./platform.h"
		#include "./externC.h"

		#if defined (OS_IS_WINDOWS)
			#include "./CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)
		
		#endif

	#else

		#include "./../pre/platform.h"
		#include "./../pre/externC.h"

		#if defined (OS_IS_WINDOWS)
			#include "./Windows/CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)
		
		#endif

	#endif

#endif

EXTERN_C_BEGIN

/*
	enfilecompressresult

	Return values for the compression check functions.
*/
enum enfilecompressresult
{
	fscompress_compressed,
	fscompress_uncompressed,
	fscompress_error
};
typedef enum enfilecompressresult enfilecompressresult;

/*
	IsFileCompressedByName

	Returns true if the file is already compressed, false if it isn't.
*/
#ifdef DEBUG
	enfilecompressresult IsFileCompressedByName (const char *szFilename);
#else
	#if defined (OS_IS_WINDOWS)
		#define IsFileCompressedByName(fn)				\
			IsFileNTFSCompressedByName (fn)
	#elif defined (OS_IS_LINUX)
		#define IsFileCompressedByName(fn)				\
			(false)
	#endif
#endif

/*
	FScompressFileByName

	Compresses the file szFilename and returns true on success, false otherwise.
*/
bool FScompressFileByName (const char *szFilename)
;

EXTERN_C_END

#endif														// Of #ifndef U_COMPRESS_FILE_H.
/****************************************************************************************

	File:		ExeFileName.h
	Why:		Obtains the name of the executable.
				This is the platform-independent abstraction module for the Windows
				module WinExeFileName and the POSIX module PsxExeFileName.
	OS:			C99/Windows/POSIX.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

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

#ifndef EXEFILENAME_H
#define EXEFILENAME_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../pre/platform.h"
	#endif

	#ifdef OS_IS_WINDOWS
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./WinExeFileName.h"
		#else
			#include "./Windows/WinExeFileName.h"
		#endif
	#else
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./PsxExeFileName.h"
		#else
			#include "./POSIX/PsxExeFileName.h"
		#endif
	#endif

#endif

EXTERN_C_BEGIN

/*
	ObtainExecutableModuleName

	Obtains the executables full path including its name. The caller is responsible for
	initialising the SMEMBUF structure beforehand.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainExecutableModuleName(mb)				\
		WinObtainExecutableModuleName (mb)
#else
	#define ObtainExecutableModuleName(mb)				\
		PsxObtainExecutableModuleName (mb)
#endif

/*
	ObtainAppNameFromExecutableModule

	Obtains the application's name only, i.e. without path or ".exe" filename extension.
	The caller is responsible for initialising the SMEMBUF structure beforehand.

	For an application "C:/temp/app.exe" the function sets mb to "app" and returns 3.

	The function returns the amount of octets (bytes) written to the SMEMBUF's buf
	member, not including the NUL terminator. If the function fails it returns 0.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainAppNameFromExecutableModule(mb)		\
		WinObtainAppNameFromExecutableModule (mb)
#else
	#define ObtainAppNameFromExecutableModule(mb)		\
		PsxObtainAppNameFromExecutableModule (mb)
#endif

/*
	ObtainPathFromExecutableModule

	Returns the path part of the application's executable module.
	On Windows, the last character of the returned path is usually a backslash.

	The function returns the amount of characters it placed in the structure's
	buffer excluding a terminating NUL. It returns 0 upon failure.
*/
#ifdef OS_IS_WINDOWS
	#define ObtainPathFromExecutableModule(mb)			\
		WinObtainPathFromExecutableModule (mb)
#else
	#define ObtainPathFromExecutableModule(mb)			\
		PsxObtainPathFromExecutableModule (mb)
#endif

/*
	TestExeFileNameFnct

	Tests this module. Returns true if successful.
*/
#ifdef CUNILOG_BUILD_EXEFILENAME_TEST_FNCT
	bool TestExeFileNameFnct (void);
#else
	#define TestExeFileNameFnct()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef EXEFILENAME_H.
/****************************************************************************************

	File:		FileMembuf.h
	Why:		File functions for SMEMBUF structures.
	OS:			C99
	Author:		Thomas
	Created:	2025-09-18

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-09-18	Thomas			Created.

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

#ifndef U_FILEMEMBUF_H
#define U_FILEMEMBUF_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./membuf.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../mem/membuf.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

// This value is returned in case of an error.
#ifndef READFILESMEMBUF_ERROR
#define READFILESMEMBUF_ERROR			((size_t) -1)
#endif

// The maximum filesize that can be read from disk to memory with this module.
#ifndef READFILESMEMBUF_MAX_FSIZE
#define READFILESMEMBUF_MAX_FSIZE		(20 * 1024 * 1024)	// 20 MiB.
#endif

EXTERN_C_BEGIN

/*
	ReadFileSMEMBUF

	Reads the file named szFileName into the buffer of the SMEMBUF structure pmb points
	to. The SMEMBUF structure must have been initialised properly before this function
	is called.

	The buffer of the SMEMBUF structure pmb points to is NUL-terminated. In fact, the
	function writes two NUL octets to ensure it can also be used to read UTF-16 files.

	The function returns the amount of octets/bytes written to the buffer, not including
	the terminating NUL character.
*/
size_t ReadFileSMEMBUF (SMEMBUF *pmb, const char *szFileName)
;

/*
	test_FileMembuf

	Test function for the module.
	returns true on success, false otherwise.
*/
#ifdef FILEMEMBUF_BUILD_TEST_FNCT
	bool test_FileMembuf (void);
#else
	#define test_FileMembuf()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifdef U_FILEMEMBUF_H.
/****************************************************************************************

	File:		ProcessHelpers.h
	Why:		Functions for creating and handling processes.
	OS:			C99
	Author:		Thomas
	Created:	2025-06-05
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-06-05	Thomas			Created.

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

#ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS

#ifndef U_PROCESSHELPERS_H
#define U_PROCESSHELPERS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef PLATFORM_IS_WINDOWS

	#include <Windows.h>

	typedef DWORD	cunilog_pid_t;

#else

	#include <unistd.h>

	typedef pid_t	cunilog_pid_t;

#endif

#ifndef PRCHLPS_DEF_EXCESS_BUFFER
#define PRCHLPS_DEF_EXCESS_BUFFER		(256)
#endif

/*
	ProcessHelpersSetBufferSize

	Sets the default buffer size of the module. Default is PRCHLPS_DEF_EXCESS_BUFFER.

	The function returns the prvious default buffer size.
*/
size_t ProcessHelpersSetBufferSize (size_t bufsize);

/*
	Squeezes the executable's name plus all arguments in a single string.
	The executable's name is going to be the first argument.

	If bNoExeArg is true, no executable argument is written to the returned string.
	While pretty much standard in POSIX, some Windows applications don't like it when
	their first argument is the name of the executable. Set bNoExeArg to true for
	those applications; otherwise set it to false.
*/
char *CreateArgsList (const char *szExecutable, int argc, const char *argv [], bool bNoExeArg)
;

typedef struct sruncmdcbinf
{
	const char			*szExecutable;						// As provided by the caller.
	size_t				lnExecutable;						// Its length.
	const char			*szArgsList;						// Arguments string.
	size_t				lnArgsList;							// Its length.
	const char			*szWorkingDir;
	size_t				lnWorkingDir;
	cunilog_pid_t		childProcessId;						// PID of the child.
	enum enRCmdCBval	rvHtb;								// Return value of heartbeat CB.
	uint64_t			uiChildExitTimeout;					// Time in ms to wait for the
															//	child to exit.
} SRUNCMDCBINF;

/*
	Callback function return values.

	enRunCmdRet_Continue			This is the default. The calling function carries
									on until the child process exits.
									CreateAndRunCmdProcessCapture () returns true.

	enRunCmdRet_Ignore				The callback function is not called again but the
									child process keeps running until it exits itself.
									CreateAndRunCmdProcessCapture () returns true.

	enRunCmdRet_Terminate			Terminate the child process.
									CreateAndRunCmdProcessCapture () returns true.

	enRunCmdRet_TerminateFail		Terminate the child process.
									CreateAndRunCmdProcessCapture () returns true.
*/
enum enRunCmdCallbackRetValue
{
	enRunCmdRet_Continue,									// No change/continue.
	enRunCmdRet_Terminate,									// Exit child process.
	enRunCmdRet_Ignore,										// Keep child process running
															//	but stop calling callback
															//	function for this stream.
	enRunCmdRet_TerminateFail
};
typedef enum enRunCmdCallbackRetValue enRCmdCBval;

/*
	Callback function for stdout and stderr.

	The argument szOutput contains a pointer to the data the child process sent to
	either stdout or stderr, depending on which callback function is called.

	The argument lnOutput contains the length of the data. If enRunCmdHow_AsIs is
	passed to CreateAndRunCmdProcessCapture () via the enum enRunCmdHowToCallCB,
	the data/text may not be NUL-terminated. Do not read beyond lnOutput in this case.
*/
typedef enRCmdCBval rcmdOutCB (SRUNCMDCBINF *pinf, char *szOutput, size_t lnOutput, void *pCustom);

/*
	Callback function for stdin.

	The parameter psmb points to an initialised but otherwise empty SMEMBUF structure.
	The buffer of this structure can be populated with data by the callback function.
	This data is forwarded/sent to the child process's input stream stdin.

	The address plnData points to must be set to the length of the data that will
	be sent to the child's stdin stream, excluding a terminating NUL character. If
	the value plnData points to is USE_STRLEN, the buffer of the SMEMBUF structure
	psmb points to must be NUL-terminated, and CreateAndRunCmdProcessCapture () calls
	strlen () on it to obtain its length.

	If nothing should be sent to the child process's input stream, *plenData must be set
	to 0 by the callback function.

	For example, a callback function of type rcmdInpCB could send the command "exit\n"
	(note the "\n" to simulate the enter key) to the child process:

	enRCmdCBval cbInp (SMEMBUF *psmb, size_t *plnData, void *pCustom)
	{
		UNUSED (pCustom);

		*plnData = SMEMBUFfromStr (psmb, "exit\n", USE_STRLEN);
		return enRunCmdRet_Continue;
	}

*/
typedef enRCmdCBval rcmdInpCB (SRUNCMDCBINF *pinf, SMEMBUF *psmb, size_t *plnData, void *pCustom);

typedef enRCmdCBval rcmdHtbCB (SRUNCMDCBINF *pinf, void *pCustom);

/*
	SRCMDCBS

	This structure contains pointers to the callback functions as well as the heartbeat
	interval in milliseconds (ms).
*/
typedef struct srcmdCBs
{
	rcmdInpCB	*cbInp;										// CB to provide stdin for child.
	rcmdOutCB	*cbOut;										// CB to receive stdout from child.
	rcmdOutCB	*cbErr;										// CB to receive stderr from child.
	rcmdHtbCB	*cbHtb;										// CB for heartbeat.
	uint64_t	uiHtbMS;									// Time interval in ms to call the
															//	heartbeat CB cbHtb.
} SRCMDCBS;

/*
	Which callback functions to call and execeutable argument.
*/
#define RUNCMDPROC_CALLB_STDINP		(0x0001)				// Invoke callback for stdin.
#define RUNCMDPROC_CALLB_STDOUT		(0x0002)				// Invoke callback for stdout.
#define RUNCMDPROC_CALLB_STDERR		(0x0004)				// Invoke callback for stderr.
#define RUNCMDPROC_CALLB_HEARTB		(0x0008)				// Invoke callback for heartbeat.
#define RUNCMDPROC_EXEARG_NOEXE		(0x0010)				// No exe argument in parameter
															//	list. See comments for function
															//	CreateArgsList () for details.
															//	This flag sets the parameter
															//	bNoExeArg of CreateArgsList ()
															//	to true.

/*
	Internal flags. Must not be utilised by callers.

	Note that RUNCMDPROC_CALLB_INTERR only exists for consistency. It is implied that if
	RUNCMDPROC_CALLB_INTOUT is not set, RUNCMDPROC_CALLB_INTERR is assumed. See function
	callOutCB () on how it is implemented.
*/
#define RUNCMDPROC_CALLB_INTOUT		(0x0100)				// Called for stdout.
#define RUNCMDPROC_CALLB_INTERR		(0x0200)				// Called for stderr. This flag only
															//	exists for consistency reasons.
															//	It is never checked.

/*
	How or when the callback functions are to be called.

	enRunCmdHow_AsIs		Called whenever data is available, meaning it might arrive in
							uncontrollable chunks. The data is not necessarily NUL-terminated.

	enRunCmdHow_AsIs0		Called whenever data is available, may arrive in uncontrollable
							chunks, but each chunk is always NUL-terminated.

	enRunCmdHow_OneLine		Called for complete lines only, and called once for each collected
							line. The data does not contain line endings but is always NUL-
							terminated. A value of 0 for the parameter lnData means an empty
							line has been encountered.

	enRunCmdHow_All			Called only once with the entire collected output of the process.
							The data is NUL-terminated. Never called with a length of 0.
*/
enum enRunCmdHowToCallCB
{
	enRunCmdHow_AsIs,										// Whenever data is available.
	enRunCmdHow_AsIs0,										// Same but NUL-terminated.
	enRunCmdHow_OneLine,									// Per complete line.
	enRunCmdHow_All											// Everything in one go.
															//	Buffer is NUL-terminated.
};
typedef enum enRunCmdHowToCallCB enRCmdCBhow;

/*
	CreateAndRunCmdProcessCapture

	Creates and runs a command-line process.
	
	The process's input (stdin) can be provided by a callback function, and its output (stdout
	and stderr) can be captured by callback functions.

	Parameters

	szExecutable		A NUL-terminated string with the path and name of the executable module
						of the command-line process.

	szCmdLine			The command-line arguments/parameters.

	szWorkingDir		The working directory/current directory of the command-line process.

	pCBs				A pointer to an SRCMDCBS structure that contains pointers to the
						callback functions and the heartbeat time interval.

	cbHow				Specifies how and when the callback functions are to be invoked by
						the function. See the enum enRunCmdHowToCallCB for a list of possible
						options.

	uiRCflags			Option flags.

	pCustom				An arbitrary pointer or value that is passed on to the callback
						functions.

	pExitCode			A pointer to an integer that receives the exit code of the child
						process. If the exit code is not required, this parameter can be
						NULL. If pExitCode is not NULL, the function sets the value to
						EXIT_FAILURE before it starts doing any work, and updates it later
						to the real exit code of the child process. On most platforms,
						EXIT_FAILURE has a value of 1.

*/
#if defined (PLATFORM_IS_WINDOWS)

	bool CreateAndRunCmdProcessCapture	(
			const char				*szExecutable,
			const char				*szCmdLine,
			const char				*szWorkingDir,
			SRCMDCBS				*pCBs,					// CB functions and heartbeat interval.
			enRCmdCBhow				cbHow,					// How to call the callback functions.
			uint16_t				uiRCflags,				// One or more of the RUNCMDPROC_
															//	flags.
			void					*pCustom,				// Passed on unchanged to callback
															//	functions.
			uint64_t				uiChildExitTimeout,		// Time in ms to wait for the child to
															//	exit/terminate.
			int						*pExitCode				// Exit code of process.
										)
;

#elif defined (PLATFORM_IS_POSIX)


#elif

	// Neither Windows nor POSIX.
	#error Not supported

#endif


/*
	ProcessHelpersTestFnct

*/
#ifdef PROCESS_HELPERS_BUILD_TEST_FNCT
	bool ProcessHelpersTestFnct (void);
#else
	#define ProcessHelpersTestFnct() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_PROCESSHELPERS_H.

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
/****************************************************************************************

	File:		SharedMutex.h
	Why:		Implements a mutex for interprocess-locking.
	OS:			C99
	Author:		Thomas
	Created:	2021-02-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-02-23	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
MIT License

Copyright (c) 2018 Oleg Yamnikov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef UBF_SHARED_MUTEX_H
#define UBF_SHARED_MUTEX_H

#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

#ifndef CUNILOG_USE_COMBINED_MODULE


	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ArrayMacros.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/ArrayMacros.h"
		#include "./../pre/platform.h"
	#endif

	#if defined (PLATFORM_IS_POSIX) && defined (PLATFORM_IS_WINDOWS)
		#error Only one platform can be defined
	#endif
	#ifdef PLATFORM_IS_POSIX
		#include "./POSIX/PsxSharedMutex.h"
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		#include "./Windows/WinSharedMutex.h"
	#endif

#endif

/*
	The prefix to make a kernel object global on Windows.
	For POSIX it is the prefix for a mutex ("/").
*/
#if defined (PLATFORM_IS_WINDOWS)
	#define UBF_SHARED_MUTEX_GLOBAL_PFX		"Global\\"
#elif defined (PLATFORM_IS_POSIX)
	#define UBF_SHARED_MUTEX_GLOBAL_PFX		"/"
#elif
	#error Not supported
#endif


#if defined (PLATFORM_IS_WINDOWS)
	// This should be 255.
	#ifndef NAME_MAX
	#define NAME_MAX	(MAX_PATH - 4)
	#endif
#elif defined (PLATFORM_IS_POSIX)
	#ifndef NAME_MAX
	#define NAME_MAX	(255)
	#endif
#endif

#ifndef NAME_MAX
	#error NAME_MAX not defined
#endif

EXTERN_C_BEGIN

// Initialize a new shared mutex with given `name`. If a mutex
// with such name exists in the system, it will be loaded.
// Otherwise a new mutes will by created.
//
// In case of any error, it will be printed into the standard output
// and the returned structure will have `ptr` equal `NULL`.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** In case when the mutex appears to be uncreated,
// this function becomes *non-thread-safe*. If multiple threads
// call it at one moment, there occur several race conditions,
// in which one call might recreate another's shared memory
// object or rewrite another's pthread mutex in the shared memory.
// There is no workaround currently, except to run first
// initialization only before multi-threaded or multi-process
// functionality.
/*
	2021-02-24, Thomas
	
	The parameter name must not contain any forward or backward slashes.
	In Linux, the name is automatically prepended a forward slash.
	In Windows, the name is automatically prepended a global namespace
	identifier ("Global\"). See
	https://docs.microsoft.com/en-us/windows/win32/termserv/kernel-object-namespaces
	for information.
*/
shared_mutex_t InitSharedMutex (const char *name);

// Close access to the shared mutex and free all the resources,
// used by the structure.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not destroy the mutex. The mutex would not
// only be available to other processes using it right now,
// but also to any process which might want to use it later on.
// For complete desctruction use `shared_mutex_destroy` instead.
//
// **NOTE:** It will not unlock locked mutex.
int CloseSharedMutex (shared_mutex_t mutex);

// Close and destroy shared mutex.
// Any open pointers to it will be invalidated.
//
//
// **NOTE:** It will not unlock locked mutex.
void DestroySharedMutex(shared_mutex_t mutex);

/*
	EnterSharedMutex
	LeaveSharedMutex

	These functions return true on success, false otherwise.
*/
bool EnterSharedMutex (shared_mutex_t mutex);
bool LeaveSharedMutex (shared_mutex_t mutex);

/*
	WeCreatedSharedMutex

	Returns true if this instance/process created the shared mutex.
*/
bool HaveWeCreatedSharedMutex (shared_mutex_t mutex);

EXTERN_C_END

#endif															// Of #ifndef SHAREDMUTEX_H.
/****************************************************************************************

	File:		UserHome.h
	Why:		User home directory functions.
	OS:			C99.
	Author:		Thomas
	Created:	2025-03-03
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-03-03	Thomas			Created.

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

#ifndef U_USERHOME_H
#define U_USERHOME_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	ObtainUserHomeDirectoy

	Obtains the user's home directory with an ending forward or backward slash as an
	SMEMBUF. Whether the function adds a forward or backward slash depends on the platform.
	
	The SMEMBUF structure mb points to must be initialised before the function is called.

	The function returns the length of the path excluding the terminating NUL character.

	The function returns 0 when it fails.
*/
size_t ObtainUserHomeDirectoy (SMEMBUF *mb);

EXTERN_C_END

#endif														// Of #ifndef U_USERHOME_H.
/****************************************************************************************

	File:		ExtCompressors.h
	Why:		Interface module/unit for external compressors.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-01	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This module is an interface for external compressors/external compression libraries.
	This implies that when this module is used, the application requires to be linked to
	additional external libraries.
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

#ifndef U_EXTCOMPRESSORS_H
#define U_EXTCOMPRESSORS_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

	#include "./platform.h"

		#if defined (OS_IS_WINDOWS)
			//#include "./CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)

	#endif

	#else

		#include "./../pre/platform.h"

		#if defined (OS_IS_WINDOWS)
			//#include "./Windows/CompressNTFS_U8.h"
		#elif defined (OS_IS_LINUX)

		#endif

	#endif

#endif


#endif														// Of #ifndef U_EXTCOMPRESSORS_H.
/****************************************************************************************

	File:		ubfdebug.h
	Why:		Contains debugging functions.
	OS:			Windows/POSIX
	Author:		Thomas
	Created:	2017-10-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2017-10-24	Thomas			Created.
2018-05-26	Thomas			Compiler warning Linux/Android fixed by changing
							 the loop variable from int to unsigned int.
2019-08-24	Thomas			Module OS/ubf_debug.c/h should be obsolete now.

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

#ifndef U_UBF_DEBUG_DEB_H_INCLUDED
#define U_UBF_DEBUG_DEB_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	#include <assert.h>
#endif

/*
	Below are the macros that turn on the functions listed in the comments on the right-
	hand side of the macro definitions.
*/
#ifndef UBF_DEBUG_HEX_DUMP
//#define UBF_DEBUG_HEX_DUMP									// When defined, enables
																//	ubf_debug_hex_dump ().
#endif
#ifdef UBF_DEBUG_NO_HEX_DUMP
	#undef UBF_DEBUG_HEX_DUMP
#endif

// When defined, enables ubf_debug_printf () and ubf_debug_puts ().
#ifdef DEBUG
	#ifndef UBF_DEBUG_USE_PRINTF
	#define UBF_DEBUG_USE_PRINTF
	#endif
#endif

// When defined, uses our output abort functions. If not, a simple
//	ABORT() macro is used. It is not recommended to uncomment this
//	definition. Rather define UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
//	in the development environment or project file.
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#ifndef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#define UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#endif
#endif
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#ifdef UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
		#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#undef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#endif
	#endif
#endif

#ifndef UBF_DEBUG_MSG_STRLEN
#define UBF_DEBUG_MSG_STRLEN		(4096)
#endif

// The character used to identify buffer overruns and uninitialised areas. Can (and
//	should) be used as a general filler for debug purposes.
#ifndef UBF_ERROR_CHAR
#define UBF_ERROR_CHAR	'\x55'
#endif
#ifndef UBF_ERROR_CINT
#define UBF_ERROR_CINT	0x55
#endif

EXTERN_C_BEGIN

/*
	Macros to check if all members of a structure or union have been initialised.
	Check to see if we forgot to initialise a member. This is important when more
	members are added later.
	
	UBF_DEBUG_CHECK_STRUCT_DECLARATION()
	
	Sets the character used to initialise the structure before the real initialisation
	takes place.
	
	UBF_DEBUG_CHECK_STRUCT_ASSERTION()
	
	Checks if there are any octets within the structure's memory block that haven't been
	initialised by testing that no byte contains the character set with the macro
	UBF_DEBUG_CHECK_STRUCT_DECLARATION().
	
	
	Example:
	
	typedef struct structname
	{
		int		i1;
		int		i2;
		int		i3;
		int		i4;
		int		in;
	} STRUCTNAME;
	
	void test (void)
	{
		STRUCTNAME		sn;
		
		UBF_DEBUG_CHECK_STRUCT_DECLARATION (&sn, STRUCTNAME, 0x0D);
		sn.i1 = 1;
		sn.i2 = 2;
		//...
		sn.in = -1;
		UBF_DEBUG_CHECK_STRUCT_ASSERTION (&sn, STRUCTNAME);
	}
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(pstructure, typestruct, c)				\
		unsigned int	uStructCheck;													\
		unsigned char	*chStructCheck;													\
		unsigned char	cStructCheck		= (c);										\
		memset ((pstructure), (c), sizeof (typestruct))
#else
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(c)
#endif
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)						\
		chStructCheck = (char *) (pstructure);											\
		for (uStructCheck = 0; uStructCheck < sizeof (typestruct); uStructCheck ++)		\
		{																				\
			if (*chStructCheck == cStructCheck)											\
				_ASSERT (false);														\
			++ chStructCheck;															\
		}
#else
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)
#endif

/*
	UBF_DEBUG_CHECK_CALLED_ONLY_ONCE
	
	Macro to check that the function using it is only invoked once. Useful for
	initialisation functions.
	
	UBF_DEBUG_CHECK_RESET_ONLY_ONCE
	
	Resets the flag. Useful to check that a function that is not re-entrant is
	not called again before the previous instance has returned.
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)	\
		static bool	flagname;							\
		ubf_assert (!flagname);							\
		flagname = TRUE
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)	\
		flagname = FALSE
#else
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)
#endif

/*
	UBF_DEFINE_GUARD_VAR										// Define guard variable.
	UBF_CHECK_GUARD_VAR											// Check/test guard variable.
	UBF_DEF_GUARD_VAR											// Define guard variable.
	UBF_TST_GUARD_VAR											// Check/test guard variable.
	UBF_CHK_GUARD_VAR											// Check/test guard variable.
	
	Macros to define and to check guard variables. The variable defined is of
	type char []. These macros can help find buffer overruns.
	
	Examples:
	
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	The following example checks for an overrun of the array:
	
	int		i [105];
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	...
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	If data is written beyond the array's memory location testvar is overwritten,
	at least on some platforms.
	Test data is defined with UBF_DEFINE_GUARD_VAR().
	The macro UBF_CHECK_GUARD_VAR() determines if the test variable's content has
	been destroyed.
*/
#ifdef DEBUG
	#ifndef UBF_DEFINE_GUARD_VAR
	#define UBF_DEFINE_GUARD_VAR(var, value)			\
		char	var [] = #value
	#endif
	#ifndef UBF_CHECK_GUARD_VAR
	#define UBF_CHECK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_DEF_GUARD_VAR
	#define UBF_DEF_GUARD_VAR(var, value)				\
		char	var [] = #value
	#endif
	#ifndef UBF_TST_GUARD_VAR
	#define UBF_TST_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_CHK_GUARD_VAR
	#define UBF_CHK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
#else
	#define UBF_DEFINE_GUARD_VAR(var, value)
	#define UBF_CHECK_GUARD_VAR(var, value)
	#define UBF_DEF_GUARD_VAR(var, value)
	#define UBF_TST_GUARD_VAR(var, value)
	#define UBF_CHK_GUARD_VAR(var, value)
#endif

/*
	ubf_debug_assert

	Outputs the message only if the assertion doesn't pass.
	
	ubf_debug_assert_pass

	Outputs the message chDebugMessage and then implements an _ASSERT () with bAssert.

	Use the macro UBF_DEBUG_ASSERT() or ubf_assert_msg() to fill in __FILE__ and __LINE__
	for the parameters chFilePath and uiLineNum. Both macros are identical. See
	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html for an explanation
	of the __FILE__ and __LINE__ macros. The macro ubf_assert () is probably what should
	be used as often as possible.

	In release versions these are macros that expand to nothing.
	
	It is recommended to use the ubf_assert() macro, which expects one parameter only. It
	stringifies this parameter for the output text. Since this is sometimes not possible
	due to the limitations of the preprocessor's stringify operator, or it's not
	desirable if condition and message text should differ, the macro ubf_assert_msg() can
	be used.

	Examples:

	// All these lines have the same or similar functionality:
	ubf_debug_assert (a > b, "a > b", __FILE__, __LINE__);
	UBF_DEBUG_ASSERT (a > b, "a > b", __FILE__, __LINE__);
	ubf_assert (a > b);
	ubf_assert_msg (a > b, "a > b");
	
	Explanation and further notes:
	
	Although assert () on Windows and Linux works great, it does exactly what the
	documentation says on Android: it aborts. No message, no information on where
	it stopped, nor why.
	
	ubf_assert (a > b) is a replacement for assert (). It displays a message with
	the assertion before it aborts.
	
	ubf_assert_msg (a > b, "Arbitrary message") is a replacement for assert () that
	outputs "Arbitrary message" when the assertion fails instead of the actual
	assertion.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	// Debug version.
	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ubf_debug_assert		(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert(b, c, p, n)			\
			ASSERT (b)
	#endif
	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ubf_debug_assert_pass	(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert_pass(b, c, p, n)		\
			ASSERT (b)
	#endif
	#ifndef UBF_DEBUG_ASSERT
	#define UBF_DEBUG_ASSERT(b)							\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert
	#define ubf_assert(b)								\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_msg
	#define ubf_assert_msg(b,m)							\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_message
	#define ubf_assert_message(b,m)						\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_pass
	#define ubf_assert_pass(b)							\
				ubf_debug_assert_pass ((b), #b, __FILE__, __LINE__)
	#endif
	/*
		ubf_assert_Android
		
		Prints the message on Android but is a simple _ASSERT() on other platforms. That's
		because the application simply dies with an _ASSERT() on Android.
	*/
	#ifdef OS_IS_ANDROID
		#define ubf_assert_Android(b)					\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
		#define ubf_assert_Android_msg(b,m)				\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Android(b)					\
				_ASSERT (b)
		#define ubf_assert_Android_msg(b,m)				\
				_ASSERT (b)
	#endif
	/*
		ubf_assert_Linux
		
		Prints the message on Linux but is a simple _ASSERT() on other platforms.
	*/
	#ifdef OS_IS_LINUX
		#define ubf_assert_Linux(b)						\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
		#define ubf_assert_Linux_msg(b,m)				\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Linux(b)						\
				_ASSERT (b)
		#define ubf_assert_Linux_msg(b, m)				\
				_ASSERT (b)
	#endif
#else
	// Release version.
	#define ubf_debug_assert(b,m,f,l)
	#define ubf_debug_assert_pass(b,m,f,l)
	#define UBF_DEBUG_ASSERT(b)
	#define ubf_assert(b)
	#define ubf_assert_msg(b,m)
	#define ubf_assert_message(b,m)
	#define ubf_assert_pass(b)
	#ifdef UBF_ANDROID
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#else
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#endif
	#ifdef UBF_LINUX
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#else
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#endif
#endif

/*
	ubf_debug_fill_mem

	Fills the memory mem points to with UBF_ERROR_CHAR, which is 55h, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem (void *mem, size_t len);
#else
	#define ubf_debug_fill_mem(m,l)
#endif

/*
	ubf_debug_check_mem
	
	Assert that a memory block consists of UBF_ERROR_CHAR octets.
*/
#ifdef DEBUG
	void ubf_debug_check_mem (char *mem, size_t len);
#else
	#define ubf_debug_check_mem(m, l)
#endif

/*
	ubf_debug_fill_mem_with

	Fills the memory mem points to with the value of c, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem_with (void *mem, char c, size_t len);
#else
	#define ubf_debug_fill_mem_with(m, c, l)
#endif

/*
	ubf_debug_check_mem_with

	Assert that a memory block consists of len octets filled with c.
*/
#ifdef DEBUG
	void ubf_debug_check_mem_with (char *mem, char c, size_t len);
#else
	#define ubf_debug_check_mem_with(m, c, l)
#endif

/*
	ubf_debug_hex_dump
	
	Calls ubf_data_dump_puts () in ubfdump.c if UBF_DEBUG_HEX_DUMP is defined.
	If UBF_DEBUG_HEX_DUMP is not defined, the function is expanded to a no-operation.
*/
#ifdef UBF_DEBUG_HEX_DUMP
	void ubf_debug_hex_dump (const char *chOutput, size_t stOutput);
#else
	#define ubf_debug_hex_dump(ch,st)
#endif

/*
	ubf_debug_printf
	ubf_debug_puts
	
	Debug versions of printf () and puts (). To make these calls no-operations (empty)
	macros, undefine UBF_DEBUG_USE_PRINTF. In release versions they are empty definitions.
*/
#ifdef UBF_DEVICE_GUI
	#ifdef DEBUG
		void ubf_debug_printf (const char *format, ...);
		void ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
	#ifdef UBF_DEBUG_USE_PRINTF
		#undef UBF_DEBUG_USE_PRINTF
	#endif
#else
	#ifdef UBF_DEBUG_USE_PRINTF
		int ubf_debug_printf (const char *format, ...);
		int ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
#endif

// Debug sleep. Sleeps in debug versions (milliseconds) but not in release builds.
#ifdef DEBUG
	#define ubf_debug_sleep_ms(s)			ubf_sleep_ms (s)
#else
	#define ubf_debug_sleep_ms(s)
#endif

// Macros to abort in debug versions.
#ifdef DEBUG
	#define DEBUGABORT()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORTDEBUG()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORT()			ASSERT (false)
#else
	#define DEBUGABORT()
	#define DBGABORT()
	#define ABORTDEBUG()
	#define DBGABORT()
	#define ABORT()
#endif

/*
	ubf_expect_bool_AND
	ubf_assert_bool_AND

	Macro to binary AND an expectation. Useful in test functons.

	bool	bOk		= TRUE;
	int		a		= 0;
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 3 == a);
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 6 == a);
	ubf_assert_true (bOk);
*/
#define ubf_expect_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))
#define ubf_assert_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))

/*
	ubf_expect_bool_AND_0
	ubf_assert_bool_AND_0

	Macro to binary AND an expectation to be 0.
*/
#define ubf_expect_bool_AND_0(b, expectation)			\
			(b) &= (0 == (expectation));				\
			ubf_assert (0 == (expectation))
#define ubf_assert_bool_AND_0(b, expectation)			\
			(b) &= (0 == (expectation));				\
			ubf_assert (0 == (expectation))

/*
	ubf_assert_TRUE
	ubf_assert_FALSE
	ubf_expect_TRUE
	ubf_expect_FALSE
	ubf_assert_true
	ubf_expect_true
	ubf_assert_false
	ubf_expect_false

	Macros that assert that the provided boolean is either TRUE or FALSE.
*/
#define ubf_assert_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_expect_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_assert_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_expect_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_assert_true(b)								\
			ubf_assert (true == (b))
#define ubf_expect_true(b)								\
			ubf_assert (true == (b))
#define ubf_assert_false(b)								\
			ubf_assert (false == (b))
#define ubf_expect_false(b)								\
			ubf_assert (false == (b))


/*
	ubf_assert_NULL
	ubf_expect_NULL
	ubf_assert_not_NULL
	ubf_expect_not_NULL
	ubf_assert_non_NULL
	ubf_expect_non_NULL

	Macros that assert that the provided pointer is either NULL or non-NULL.
*/
#define ubf_assert_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_expect_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_assert_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_assert_non_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_non_NULL(p)							\
			ubf_assert (NULL != (p))

/*
	ubf_assert_0
	ubf_expect_0
	ubf_assert_non_0
	ubf_expect_non_0
	ubf_assert_zero
	ubf_expect_zero
	ubf_assert_non_zero
	ubf_expect_non_zero

	Macros that assert that the parameter expression evaluates to zero or
	non-zero.
*/
#define ubf_assert_0(v)									\
			ubf_assert (0 == (v))
#define ubf_expect_0(v)									\
			ubf_assert (0 == (v))
#define ubf_assert_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_expect_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_assert_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_expect_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_assert_non_zero(v)							\
			ubf_assert (0 != (v))
#define ubf_expect_non_zero(v)							\
			ubf_assert (0 != (v))

/*
	ONLY_IN_DEBUG

	Emits the given code only in debug versions.
*/
#ifdef DEBUG
	#define ONLY_IN_DEBUG(code)							\
				code;
#else
	#define ONLY_IN_DEBUG(code)
#endif

EXTERN_C_END

#endif															// Of U_UBF_DEBUG_DEB_H_INCLUDED.
/****************************************************************************************

	File:		dbgcountandtrack.h
	Why:		Simple counter debug module
	OS:			-
	Author:		Thomas
	Created:	2025-01-22

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-22	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This is a simple module to track a counter.
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

#ifndef U_DBGCOUNTANDTRACK_H
#define U_DBGCOUNTANDTRACK_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef	__cplusplus
	extern "C"	{
#endif

#ifndef DBGCOUNTANDRACK_MAX_STRING
#define DBGCOUNTANDRACK_MAX_STRING		(128)
#endif

#ifndef DBGCOUNTANDTRACK_RESERVE_NUM
#define DBGCOUNTANDTRACK_RESERVE_NUM	(32)
#endif

#ifdef DEBUG
	typedef struct sdbgcountandtrack
	{
		size_t				value;
		char				cSourceFileName	[DBGCOUNTANDRACK_MAX_STRING];
		char				cFunctionName	[DBGCOUNTANDRACK_MAX_STRING];
		unsigned int		uiLine;
	} SDBGCOUNTANDTRACK;
#endif

#ifdef DEBUG
	typedef struct sdbgtracker
	{
		SDBGCOUNTANDTRACK	*trackers;
		size_t				n;								// Next index to write to.
		size_t				t;								// Next index to check/test/track.
		size_t				size;
		size_t				value;							// Current value. Probably not
															//	required. This is the value
															//	as obtained by the last change.
		char				cSourceFileName	[DBGCOUNTANDRACK_MAX_STRING];
		char				cFunctionName	[DBGCOUNTANDRACK_MAX_STRING];
		unsigned int		uiLine;
	} SDBGTRACKER;
#endif

/*
	SDBGTRACKER_INITIALISER

	Static/automatic initialiser.
*/
#define SDBGTRACKER_INITIALISER							\
			{											\
				{NULL}, 0, 0, {NULL}, {NULL}, 0			\
			}

/*
	DBG_DEFINE_CNTTRACKER

	Defines the counter cntname. Does nothing in release builds.

	Example:
	DBG_DEFINE_CNTTRACKER (myCounter)

	Note: Do NOT place a semicolon at the end.
*/
#ifdef DEBUG
	#define DBG_DEFINE_CNTTRACKER(cntname)				\
				SDBGTRACKER	cntname;
#else
	#define DBG_DEFINE_CNTTRACKER(cntname)
#endif

/*
	DBG_DEFINE_AND_INIT_COUNTER

	Defines and initialises the counter cntname to 0 in debug versions. Does nothing
	in release builds.

	Example:
	DBG_DEFINE_AND_INIT_COUNTER (myCounter);
*/
#ifdef DEBUG
	#define DBG_DEFINE_AND_INIT_CNTTRACKER(cntname)		\
				SDBGTRACKER	cntname = SDBGTRACKER_INITIALISER
#else
	#define DBG_DEFINE_AND_INIT_CNTTRACKER(cntname)
#endif

/*
	DBG_INIT_CNTTRACKER
	DBG_INIT_pCNTTRACKER

	Initialises the tracking counter.

	Example:

	SDBGTRACKER ourTracker;

	DBG_INIT_CNTTRACKER (ourTracker);
	or
	DBG_INIT_pCNTTRACKER (&ourTracker);
*/
#ifdef DEBUG
	#define DBG_INIT_CNTTRACKER(cntname)				\
				(cntname).trackers	= NULL;				\
				(cntname).n			= 0;				\
				(cntname).t			= 0;				\
				(cntname).size		= 0;				\
				(cntname).value		= 0
	#define DBG_INIT_pCNTTRACKER(cntname)				\
				(cntname)->trackers	= NULL;				\
				(cntname)->n		= 0;				\
				(cntname)->t		= 0;				\
				(cntname)->size		= 0;				\
				(cntname)->value	= 0
#else
	#define DBG_INIT_CNTTRACKER(cntname)
	#define DBG_INIT_pCNTTRACKER(cntname)
#endif

#ifdef DEBUG
	void resetDBGcountandtrack	(
			SDBGTRACKER *pt, const char *szFile, const char *szFunc, unsigned int line
								)
	;
#endif

/*
	DBG_RESET_CNTTRACKER
	DBG_RESET_pCNTTRACKER

	Prepares the tracking counter and resets it to 0.
*/
#ifdef DEBUG
	#define DBG_RESET_CNTTRACKER(cntname)				\
		resetDBGcountandtrack (&cntname, __FILE__, __FUNCTION__, __LINE__)
	#define DBG_RESET_pCNTTRACKER(cntname)				\
		resetDBGcountandtrack (cntname, __FILE__, __FUNCTION__, __LINE__)
#else
	#define DBG_RESET_CNTTRACKER(cntname)
	#define DBG_RESET_pCNTTRACKER(cntname)
#endif

#ifdef DEBUG
	void trackDBGcountandtrack	(
			SDBGTRACKER *pt, size_t value, const char *szFile, const char *szFunc,
			unsigned int line
								)
	;
#endif

/*
	DBG_TRACK_CNTTRACKER
	DBG_TRACK_pCNTTRACKER

	Tracks the counter.
*/
#ifdef DEBUG
	#define DBG_TRACK_CNTTRACKER(cntname, value)		\
		trackDBGcountandtrack (&cntname, (value), __FILE__, __FUNCTION__, __LINE__)
	#define DBG_TRACK_pCNTTRACKER(cntname)				\
		trackDBGcountandtrack (cntname, (value), __FILE__, __FUNCTION__, __LINE__)
#else
	#define DBG_TRACK_CNTTRACKER(cntname, value)
	#define DBG_TRACK_pCNTTRACKER(cntname, value)
#endif

/*
	DBG_RESET_CHECK_CNTTRACKER
	DBG_RESET_CHECK_pCNTTRACKER

	Prepares/resets checking the tracking counter.
*/
#ifdef DEBUG
	#define DBG_RESET_CHECK_CNTTRACKER(cntname)			\
		(cntname).t = 0
	#define DBG_RESET_CHECK_pCNTTRACKER(cntname)		\
		(cntname)->t = 0
#else
	#define DBG_RESET_CHECK_CNTTRACKER(cntname)
	#define DBG_RESET_CHECK_pCNTTRACKER(cntname)
#endif


#ifdef DEBUG
	void trackcheckDBGcountandtrack	(
			SDBGTRACKER *pt, size_t value, const char *szFile, const char *szFunc,
			unsigned int line
									)
	;
#endif

/*
	DBG_TRACK_CHECK_CNTTRACKER
	DBG_TRACK_CHECK_pCNTTRACKER

	Tracks the counter.
*/
#ifdef DEBUG
	#define DBG_TRACK_CHECK_CNTTRACKER(cntname, value)	\
		trackcheckDBGcountandtrack (&cntname, (value), __FILE__, __FUNCTION__, __LINE__)
	#define DBG_TRACK_CHECK_pCNTTRACKER(cntname)		\
		trackcheckDBGcountandtrack (cntname, (value), __FILE__, __FUNCTION__, __LINE__)
#else
	#define DBG_TRACK_CHECK_CNTTRACKER(cntname, value)
	#define DBG_TRACK_CHECK_pCNTTRACKER(cntname, value)
#endif


#ifdef	__cplusplus
				}
#endif

#endif														// Of #ifdef U_DBGCOUNTANDTRACK_H.
/****************************************************************************************

	File:		ubfmem.h
	Why:		Functions for memory handling.
	OS:			C99
	Author:		Thomas
	Created:	2016-10-31
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2016-10-31	Thomas			Created.

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

#ifndef U_UBFMEM_H_INCLUDED
#define U_UBFMEM_H_INCLUDED

// The Windows _ASSERT() macro.
//	Check out https://msdn.microsoft.com/en-us/library/ezb1wyez.aspx on how to use these macros.
//	The Wikipedia article https://en.wikipedia.org/wiki/Assert.h explains the Unix/Linux version.
#ifndef _ASSERT
	#ifdef DEBUG
		#define _ASSERT assert
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <malloc.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

// On Windows we could use the native functions.
#ifdef _WIN32
	#ifndef OS_IS_WINDOWS
	#define OS_IS_WINDOWS
	#endif
	#ifdef USE_WINDOWS_NATIVE_HEAP_FUNCTIONS
		#include <windows.h>
		#define malloc(size)			HeapAlloc (GetProcessHeap (), 0, size)
		#define calloc(n, s)			HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY, n * s)
		#define realloc(p, s)			HeapReAlloc (GetProcessHeap (), 0, p, s)
		//#define strdup(s)
		#define free(ptr)				HeapFree (GetProcessHeap (), 0, ptr)
		#define free(ptr)				HeapFree (GetProcessHeap (), 0, ptr)
		#define memcpy(d, s, l)			CopyMemory (d, s, l)
		#define memmovy(d, s, l)		MoveMemory (d, s, l)
		#define memset(p, v, s)			FillMemory (p, s, v)
		int memcmp (const void *str1, const void *str2, size_t count);
		#define DONT_USE_UBF_TYPE_DEFINITIONS
	#else
		#include <string.h>
	#endif
#endif

// https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif

/*
#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#define DONT_USE_UBF_TYPE_DEFINITIONS
#endif
#ifdef DONT_USE_UBF_TYPE_DEFINITIONS
	#include "./externC.h"
#else
	#ifdef UBF_TYPE_DEFINITIONS_USE_CURR_DIR
		#include "./ubf_type_definitions.h"
	#else
		#include "./../OS/ubf_type_definitions.h"
	#endif
#endif
*/

#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	#ifdef DEBUG
	#else
		// Not for release versions.
		#undef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	#endif
#endif

EXTERN_C_BEGIN

/*
	ubf_malloc
	ubf_calloc
	ubf_realloc
	ubf_strdup
	ubf_free
	ubf_free_accept_NULL
	ubf_memcpy
	ubf_memmove
	ubf_memset
	ubf_memcmp
	
	Debugging replacement for malloc (), calloc (), free (), etc. See
	https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm ,
	https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm ,
	and
	https://www.tutorialspoint.com/c_standard_library/c_function_free.htm .
	
	The function ubf_free () does not accept a NULL pointer in debug versions.
	Use ubf_free_accept_NULL () if the parameter can be NULL.

	Note that the functions ubf_memcpy (), ubf_memmove (), ubf_memset (),
	and ubf_memcmp () expect the base pointer (the one returned by ubf_malloc)
	as the first parameter, which is ignored when the debug versions are not used.
	For ubf_memcmp () the bse parameter is the base pointer of ptr1.
	
	
	ubf_mem_init_ptr
	
	Initialises the memory block of the bottom pointer btm with a usable size
	of usize.
	
	ubf_mem_usr_ptr
	
	Returns the start of the usable portion of the memory block with the bottom
	btm points to.
	
	ubf_mem_chk_ptr
	
	Checks the bottom pointer's memory debug guards. Note that ptr is a bottom
	pointer, not a base pointer.
	
	ubf_mem_chk_bse
	
	Checks the base pointer's memory debug guards. Note that bse is a base
	pointer, not a bottom pointer.
	
	ubf_mem_test_memdbg
	
	This function tests the memory debug functions.
	
	ubf_mem_done
	
	Performs cleanup work; should be called just before the application exists.
*/
#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
	void *ubf_malloc			(size_t size);
	void *ubf_calloc			(size_t nitems, size_t size);
	void *ubf_realloc			(void *ptr, size_t new_size);
	char *ubf_strdup			(const char *cc);
	void ubf_free				(void *ptr);
	void ubf_free_accept_NULL	(void *ptr);
	void *ubf_memcpy			(void *bse, void *dst, const void *src, size_t len);
	void *ubf_memmove			(void *bse, void *dst, const void *src, size_t len);
	void *ubf_memset			(void *bse, void *ptr, int value, size_t num);
	int ubf_memcmp				(const void *bse, const void *ptr1, const void *ptr2, size_t num);
	void ubf_mem_init_ptr		(void *btm, size_t usize);
	void *ubf_mem_usr_ptr		(void *btm);
	void ubf_mem_chk_ptr		(void *btm);
	void ubf_mem_chk_bse		(void *bse);
	void ubf_mem_test_memdbg	(void);
	void ubf_mem_done			(void);
#else
	#define ubf_malloc(size)			malloc (size)
	#define ubf_calloc(n,s)				calloc (n, s)
	#define ubf_realloc(p,s)			realloc (p, s)
	#define ubf_strdup(s)				strdup (s)
	#define ubf_free(ptr)				free (ptr)
	#define ubf_free_accept_NULL(ptr)	free (ptr)
	#define ubf_memcpy(b,d,s,l)			memcpy (d, s, l)
	#define ubf_memmove(b,d,s,l)		memmove (d, s, l)
	#define ubf_memset(b,d,v,l)			memset (d, v, l)
	#define ubf_memcmp(b,p1,p2,l)		memcmp (p1, p2, l)
	#define ubf_mem_init_ptr(b,s)
	#define ubf_mem_usr_ptr(b)			(b)
	#define ubf_mem_chk_ptr(b)
	#define ubf_mem_chk_bse(b)
	#define ubf_mem_test_memdbg()
	#define ubf_mem_done()
#endif

/*
	ubf_aligned_malloc_intern

	Wrapper function or macro for aligned_alloc () or similar, depending on the target
	platform and compiler. See https://en.cppreference.com/w/c/memory/aligned_alloc .
	Note that the first argument is the size of the alignment, and the second parameter
	specifies the size of the memory block to allocate. The debug version of the function
	checks for size >= alignment and asserts that this condition is met. The idea behind
	this is that an aligned memory block is only required if the data requires alignment,
	which can only be the case when the data block has at least the size of the
	alignment. On Android, this function calls posix_memalign (), which is only available
	since API level 16. It is always a function on Android, never a macro. See
	http://pubs.opengroup.org/onlinepubs/9699919799/functions/posix_memalign.html for the
	documentation of posix_memalign (). It should also be noted that the system function
	is called _aligned_malloc () on Windows while it is called aligned_alloc () on other
	Linux type platforms. Pay attention to "...malloc" and "...alloc" in these function
	names, not just the underscore ("_") character.
*/
#ifdef OS_IS_WINDOWS
	#ifdef DEBUG
		// The debug version has a function definition.
		void *ubf_aligned_malloc_intern (size_t alignment, size_t size);
	#else
		#define ubf_aligned_malloc_intern(alignment, size) _aligned_malloc (alignment, size)
	#endif
#else
	#ifdef DEBUG
		// The debug version has a function definition.
		void *ubf_aligned_malloc_intern (size_t alignment, size_t size);
	#else
		#define ubf_aligned_malloc_intern(alignment, size) aligned_alloc (alignment, size)
	#endif
#endif

// Memory allocation. See https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
//	and https://linux.die.net/man/3/aligned_alloc . We can use ubf_aligned_malloc ()
//	to be compatible with both worlds. The functions and macros are defined in
//	ubfmem.h/c.
#ifdef OS_IS_ANDROID
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_IOS
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_LINUX
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_OSX
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_UNIX
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					free (p)
#endif
#ifdef OS_IS_WINDOWS
	#define ubf_aligned_malloc(align,size)		ubf_aligned_malloc_intern (align, size)
	#define ubf_aligned_free(p)					_aligned_free (p)
#endif

/*
	ubf_alloca

	This is a wrapper for the various alloca () functions, inline functions, and macros.
*/
/*
#ifdef DEBUG
	void *ubf_alloca (size_t size);
#else
	#define ubf_alloca(s)	alloca (s)
#endif
*/

/*
	ubf_memdup
	
	Like strdup () but with a length.
*/
void *ubf_memdup (const void *mem, size_t len);

/*
	ubf_memdup_siz
	
	Like strdup () but with length to copy and size to allocate.
	In other words, a copy of mem with a size of siz is created and the first len octets
	copied from mem to the new buffer.

	Debug versions assert that siz >= len.
*/
void *ubf_memdup_siz (const void *mem, size_t len, size_t siz);

/*
	strdup_l

	Since MSVC doesn't provide strndup () yet, we roll our own.

	Copies len bytes/octets from str to a newly allocated buffer. The new buffer is always
	NUL-terminated.
*/
char *strdup_l (const char *str, size_t len);

/*
	ZeroMemory
	
	See
	https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366920(v%3Dvs.85) .
	
	This is to provide the Windows function for non-Windows platforms.
*/
#ifndef OS_IS_WINDOWS
	#ifndef _WIN32
		#define ZeroMemory(Destination,Length)				\
					memset((Destination),0,(Length))
	#endif
#endif

EXTERN_C_END

#endif															// Of U_UBFMEM_H_INCLUDED.
/****************************************************************************************

	File:		bulkmalloc.h
	Why:		Functions for bulk dynamic memory handling.
	OS:			C99
	Author:		Thomas
	Created:	2021-07-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-07-29	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Simple module for providing dynamically allocated bulk memory (or memory pools;
	also called arenas). See
	https://en.wikipedia.org/wiki/Region-based_memory_management .
	
	The idea is to allocate a huge piece of heap memory and then gradually consume it instead
	of single malloc () calls.

	This module is not meant to replace fully-grown memory managers. A bulk memory block
	can only be deallocated as a whole. When the bulk memory block is exhausted, either
	new allocations fail or additional bulk blocks are allocated in a singly linked list.
	To keep performance high it is recommended to make the bulk blocks as big as
	required/reasonably possible to avoid the singly-link list from growing too big.
	
	None of the functions in this module/unit are thread-safe. In multi-threaded environments
	the caller is responsible for providing suitable locking mechanisms.

	For the user, the heart of a bulk memory list is the SBULKMEM structure. This structure
	serves as its plinth.
	
	To initialise an SBULKMEM structure when it is static or automatic, use the macro
	SBULKMEM_INITIALISER(). Otherwise call InitSBULKMEM () to initialise the structure.
	
	static SBULKMEM sbm	= SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_SIZE);

	To create an SBULKMEM structure on the heap and initialise it, call AllocInitSBULKMEM ().
	The function AllocInitSBULKMEM () initialises an already existing structure, or creates a
	new one on the heap, depending on its first parameter.

	Memory can then be requested with calls to GetMemFromSBULKMEM () or one of its wrappers.
	
	Example 1 (static SBULKMEM structure):

		#define OUR_BULK_DATA_ARRAY_SIZE	(100)

		SBULKMEM	sbulk	= SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_SIZE);
		void		*pData [OUR_BULK_DATA_ARRAY_SIZE];
		int			i;

		for (i = 0; i < OUR_BULK_DATA_ARRAY_SIZE; ++i)
		{
			pData [i] = GetMemFromSBULKMEM (&sbulk, 1024, 8, EN_SBULKMEM_CAN_GROW);
			if (pData [i])
			{
				memset (pData [i], 0xFF, 1024);
			}
		}
		DoneSBULKMEM (&sbulk);

	Example 2 (SBULKMEM structure on heap):

		#define OUR_BULK_DATA_ARRAY_SIZE	(100)
		SBULKMEM	*pBulk	= AllocInitSBULKMEM (NULL, DEFAULT_SBULKMEM_SIZE);
		if (pBulk)
		{
			void		*pData [OUR_BULK_DATA_ARRAY_SIZE];
			int			i;

			for (i = 0; i < OUR_BULK_DATA_ARRAY_SIZE; ++i)
			{
				pData [i] = GetMemFromSBULKMEM (&sbulk, 1024, 0, EN_SBULKMEM_CAN_GROW);
				if (pData [i])
				{
					memset (pData [i], 0xFF, 1024);
				}
			}
			DoneSBULKMEM (&sbulk);
		}

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

/*
	Builds support for the function popSBULKMEM ().
*/
#ifndef BUILD_POPSBULKMEM
//#define BUILD_POPSBULKMEM
#endif

#ifndef BULKMALLOC_H
#define BULKMALLOC_H

#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./SingleBits.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/SingleBits.h"
	#endif

#endif

#ifndef DEFAULT_SBULKMEM_SIZE
#define DEFAULT_SBULKMEM_SIZE					(1024 * 1024)	// Default bulk memory block size
																//	in octets (bytes).
#endif

/*
	See
	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc?view=msvc-150 .
	Default alignment size on 32 bit Windows is 8 octets and 16 octets on 64 bit platforms.
*/
// Memory alignments. Use 16 octets/bytes for 64 bit platforms. We're going to support more
//	platforms in the future.
#if defined (_WIN64) || defined (__x86_64__)
	// For 64 bit platforms.
    #define DEFAULT_SBULKMEM_ALIGNMENT			(16)
#elif defined (_WIN32)
	// For 32 bit platforms.
    #define DEFAULT_SBULKMEM_ALIGNMENT			(8)
#else
    #error "Either a 32 bit or a 64 bit platform must be determined."
#endif

EXTERN_C_BEGIN

enum en_sbulkmem_unit
{
		EN_SBULKMEM_UNIT_OCTETS									// Size is in octets (bytes).
	,	EN_SBULKMEM_UNIT_BYTES		= EN_SBULKMEM_UNIT_OCTETS
	,	EN_SBULKMEM_UNIT_IGNORED	= EN_SBULKMEM_UNIT_OCTETS
	,	EN_SBULKMEM_UNIT_KiB									// Size is in KiB.
	,	EN_SBULKMEM_UNIT_MiB									// Size is in MiB.
	,	EN_SBULKMEM_UNIT_GiB									// Size is in GiB.
};

/*
	CalculateSizeFromUnit

	Helper function to calculate the size form a unit.
*/
size_t CalculateSizeFromUnit (size_t size, enum en_sbulkmem_unit unit)
;

/*
	One bulk memory block.
	
	pMemBlockBase is a pointer to the allocated bulk memory. This structure is
	usually transparent to the caller/user.
*/
typedef struct sbulkmemblock
{
	void					*pMemBlockBase;					// Pointer to the base of the block.
	size_t					stSize;							// Its total size.
	void					*pNextAvailable;				// Pointer to the next available
															//	memory block, which is returned
															//	on next allocation.
	size_t					stFreeSize;
	struct sbulkmemblock	*pNextElement;					// Next element in the linked list.
	uint64_t				uiFlags;
} SBULKMEMBLOCK;

/*
	The plinth of a bulk memory block list and the interface structure.
*/
typedef struct sbulkmemplinth
{
	SBULKMEMBLOCK			*psbulkFirst;					// The first bulk memory block.
	SBULKMEMBLOCK			*psbulkLast;					// The last bulk memory block.
	size_t					stDefaultSize;					// Default size of a single block.
	uint64_t				uiFlags;
#ifdef BUILD_POPSBULKMEM
	SBULKMEMBLOCK			*psbulkLastUsed;				// The block to which has been
															//	written most recently.
#endif
} SBULKMEM;

/*
	Flags for the uiFlags member of the SBULKMEMBLOCK and SBULKMEM structures.
*/
#define USBM_STRUCT_ALLOCATED		SINGLE_BIT_UINT64 (0)	// Structure itself on heap.
#define USBM_MEM_BLOCK_ALLOCATED	SINGLE_BIT_UINT64 (1)	// Member pMemBlockBase of SBULKMEMBLOCK
															//	allocated on heap.
#define USBM_STRUCT_INITIALISED		SINGLE_BIT_UINT64 (2)	// Structure is initialised already.

/*
	CalculateAlignedSize

	Calculates the required size to ensure a given alignment is possible. For instance, if
	size is 10 and an alignment of 8 is wanted, the function returns 16 to ensure there's a
	memory block of at least 10 octets available with a base address aligned to 8 octets,
	independent of the original start address.
*/
size_t CalculateAlignedSize (size_t size, uint16_t alignment)
;

/*
	AlignMemblock

	Increments the pointer pBlock to alignment. The caller is responsible for ensuring that
	the memory block pBlock points to is big enough to be aligned.

	Example:

	// Windows aligns memory on an 8 octet boundary (32 bit) or 16 octet boundary (64 bit)
	//	only but we require 32.
	void *p = malloc (CalculateAlignedSize (237, 32));
	if (p)
	{
		p_aligned = AlignMemblock (p, 237, 32);
	}
*/
void *AlignMemblock (void *pBlock, size_t size, uint16_t alignment)
;

/*
	InitSBULKMEM

	Initialises the SBULKMEM plinth pPlinth points to.
*/
#ifdef DEBUG
	void InitSBULKMEM (SBULKMEM *pPlinth, size_t defaultSize);
#else
	#ifdef BUILD_POPSBULKMEM
		#define InitSBULKMEM(p, defaultSize)			\
			(p)->psbulkFirst	= NULL;					\
			(p)->psbulkLast		= NULL;					\
			(p)->stDefaultSize	= defaultSize;			\
			(p)->uiFlags		= 0;					\
			(p)->psbulkLastUsed = NULL
	#else
		#define InitSBULKMEM(p, defaultSize)			\
			(p)->psbulkFirst	= NULL;					\
			(p)->psbulkLast		= NULL;					\
			(p)->stDefaultSize	= defaultSize;			\
			(p)->uiFlags		= 0
	#endif
#endif

/*
	AllocInitSBULKMEM

	Allocates memory for a new block of bulk memory.
	
	If pPlinth is NULL, the function allocates an SBULKMEM structure, a memory block
	header structure SBULKMEMBLOCK, and the associated memory block (buffer) on the heap.
	The entire construct is correctly initialised.
	
	If pPlinth is not NULL, the function expects that it points to an already existing
	and initialised SBULKMEM structure. In this case the function only allocates a
	memory block header structure SBULKMEMBLOCK and its associated memory block on the
	heap if the SBULKMEM structure does not contain them yet. If a memory block for the
	structure is available already, the function does nothing.

	The function returns a pointer, either to the newly created and initialised SBULKMEM
	structure, block header, and memory block upon success, or pPlinth if pPlinth is not
	NULL.
	The function returns NULL if not enough heap memory is available or any other error
	occurred.
*/
SBULKMEM *AllocInitSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							stDefaultSize
							)
;

/*
	SBULKMEM_INITIALISER

	Static or automatic initialiser.

	Example:
	SBULKMEM smp = SBULKMEM_INITIALISER (DEFAULT_SBULKMEM_PAGE_SIZE);
*/
#ifdef BUILD_POPSBULKMEM
	#define SBULKMEM_INITIALISER(s)						\
		{												\
			NULL,										\
			NULL,										\
			(s),										\
			USBM_STRUCT_INITIALISED,					\
			NULL										\
		}
#else
	#define SBULKMEM_INITIALISER(s)						\
		{												\
			NULL,										\
			NULL,										\
			(s),										\
			USBM_STRUCT_INITIALISED						\
		}
#endif

/*
	EmptySBULKMEM

	Empties the singly-linked SBULKMEM list pPlinth points to without deallocating
	its buffers. After the function returns, the entire bulk memory is available again.

	The function does not overwrite or reset the buffers' contents. It simply resets the
	level pointers of all its SBULKMEMBLOCK structures.

	To deallocate the SBULKMEM structure pPlinth points to call DoneSBULKMEM ().
*/
void EmptySBULKMEM (SBULKMEM *pPlinth)
;

/*
	DoneSBULKMEM

	Deallocates the singly-linked SBULKMEM list pPlinth points to, including maintenance
	structures, memory blocks, and the base SBULKMEM structure. The function takes into
	consideration when the plinth SBULKMEM structure is static or automatic, in which case
	it is not deallocated.

	The parameter pPlinth cannot be NULL, and debug versions abort.

	The function returns NULL to indicate that the entire list, including the SBULKMEM
	structure pPlinth points to, has been deallocated. The function returns pPlinth if
	it is a static or automatic structure.

	After the function returns and its return value is not NULL, the SBULKMEM structure
	can be re-used. However, if the SBULKMEM structure is intended to be re-used, it is
	recommended to call EmptySBULKMEM () instead of DoneSBULKMEM (). The function
	EmptySBULKMEM () resets the level pointers only rather than deallocating the actual
	buffers, which is usually a much faster operation.
*/
SBULKMEM *DoneSBULKMEM (SBULKMEM *pPlinth)
;

/*
	The enum for the parameter grow of the function GetMemFromSBULKMEM ().
*/
enum en_sbulkmem_allow_growth
{
		EN_SBULKMEM_CAN_GROW
	,	EN_SBULKMEM_ALLOW_GROWTH	= EN_SBULKMEM_CAN_GROW
	,	EN_SBULKMEM_CANNOT_GROW
	,	EN_SBULKMEM_PREVENT_GROWTH	= EN_SBULKMEM_CANNOT_GROW
};

/*
	GrowSBULKMEM
	
	Grows the SBULKMEM structure pbm points to by one element, i.e. extends the singly
	linked list by one bulk memory block, consisting of structure and actual memory
	block.
	
	The parameter pPlinth must not be NULL but is not checked by the function. Debug
	versions abort, release versions run into undefined behaviour or access violations.

	If size is less than the default size stored in the member stDefaultSize of the
	SBULKMEM structure pPlinth points to, the value of stDefaultSize is used.
	If size is greater than the stored default size, the new bulk memory block will
	have the size of the parameter size to honour the caller's request.
	
	The function returns a pointer to the newly allocated SBULKMEMBLOCK structure after
	it has been added to the singly linked list with pPlinth as its base/plinth. The
	function returns NULL if not enough heap memory is available and no new block
	could be added.
*/
SBULKMEMBLOCK *GrowSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							size
							)
;

/*
	GetMemFromSBULKMEMBLOCKifAvailable

	Returns a pointer to a memory block of size size from the SBULKMEMBLOCK structure
	pbm points to. The function fails and returns NULL if the block does not contain
	enough empty space for size octets.

	The function does not perform parameter checks. The parameter pbm must not be
	NULL.

	The function does not perform any memory alignment. If you need the returned memory
	block to be aligned, call AlignMemblock () on the returned pointer.

	Example for an alignment of 32 octets:

	SBULKMEMBLOCK	*pbm = GrowSBULKMEM (pPlinth, 1024, 32);
	void			*pData;

	pData = GetMemFromSBULKMEMBLOCKifAvailable (pbm, 128);
	pData = AlignMemblock (pData, 128, 32);
*/
void *GetMemFromSBULKMEMBLOCKifAvailable (SBULKMEMBLOCK *pbm, size_t size)
;

/*
	GetMemFromSBULKMEM
	
	Returns a block of memory from the bulk memory block SBULKMEM pPlinth points to.
	This parameter must therefore not be NULL.

	The requested size of the memory block is specified by the parameter size.
	
	The parameter alignment specifies the alignment, if needed. If this parameter
	is 0, a default alignment of 8 is assumed on 32 bit platforms and 16 octets on
	64 bit platforms. If it is 1, the returned memory block is not aligned. If not 0,
	only powers of 2 are allowed for this parameter, with the lowest allowed value being
	8 (i.e. 8, 16, 32, etc). The highest possible alignment size is 128 octets.
	
	The parameter grow specifies if the bulk memory block is allowed to grow. If grow
	is EN_SBULKMEM_CANNOT_GROW or EN_SBULKMEM_PREVENT_GROWTH, the function fails when
	the bulk memory block can not provide the requested size. If grow is
	EN_SBULKMEM_CAN_GROW or EN_SBULKMEM_ALLOW_GROWTH the function tries to add another
	SBULKMEMBLOCK structure to the singly linked list, allocates bulk memory for it, and
	returns a valid memory block from the newly created bulk memory block to the caller
	(provided, of course, that none of the heap allocations fails).
	When the total requested size, while unit is taken into consideration, is smaller than
	or equal to the member stDefaultSize of the SBULKMEM structure, the new bulk memory
	block gets this block's default size. When the size is bigger than the default size,
	the function creates a block with the requested size and marks the block as fully
	filled/occupied.
	
	The function returns a pointer to a memory block within the bulk memory block it
	reserved for the caller. The function returns NULL when it fails. The function
	can fail when the bulk memory block is exhausted but the block is prevented
	from growing. The function can also fail when a heap allocation function fails.
	
	In most cases the caller might want to use GetAlignedMemFromSBULKMEMgrow () instead,
	which is the equivalent to malloc () for bulk memory blocks.
*/
void *GetMemFromSBULKMEM	(
			SBULKMEM						*pPlinth,
			size_t							size,
			uint8_t							alignment,
			enum en_sbulkmem_allow_growth	grow
							)
;

/*
	GetAlignedMemFromSBULKMEMgrow

	The function works as if it calls GetMemFromSBULKMEM () with the parameter alignment
	set to 0 and parameter grow set to EN_SBULKMEM_ALLOW_GROWTH. In reality, for performance
	reasons the function is an altered copy of GetMemFromSBULKMEM ().
	
	This is most likely the function you want to call most of the time. The function
	is the equivalent call to malloc () for bulk memory blocks.
	
	The function returns the same value GetMemFromSBULKMEM () would have returned.
*/
void *GetAlignedMemFromSBULKMEMgrow	(
			SBULKMEM						*pPlinth,
			size_t							size
									)
;

/*
	GetAlignedMemFromSBULKMEMnogrow
	
	Calls GetMemFromSBULKMEM () with the parameter alignment set to 8 on 32 bit platforms
	and 16 on 64 bit platforms, and parameter grow set to EN_SBULKMEM_PREVENT_GROWTH to
	prevent the bulk memory block from growing.
	
	The function returns the value returned by GetMemFromSBULKMEM (). The function fails
	and returns NULL if the builk memory does not hold enough space to reserve the requested
	amount of memory.
*/
void *GetAlignedMemFromSBULKMEMnogrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
;

/*
	GetUnalignedMemFromSBULKMEMgrow
	
	Calls GetMemFromSBULKMEM () with the parameter alignment set to 1 and parameter grow
	set to EN_SBULKMEM_ALLOW_GROWTH. This means the returned memory block is not
	aligned in any way.
	
	The function returns the value returned by GetMemFromSBULKMEM ().
*/
void *GetUnalignedMemFromSBULKMEMgrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
;

/*
	GetUnalignedMemFromSBULKMEMnogrow
	
	Calls GetMemFromSBULKMEM () with the parameter alignment set to 1 and parameter grow
	set to EN_SBULKMEM_PREVENT_GROWTH. This means the memory block returned is not
	aligned in any way.
	
	The function returns the value returned by GetMemFromSBULKMEM ().
*/
void *GetUnalignedMemFromSBULKMEMnogrow	(
			SBULKMEM						*pPlinth,
			size_t							size
										)
;

/*
	popSBULKMEMBLOCK
	
	Pops the provided size (parameter size) of bytes from the SBULKMEMBLOCK structure's
	bulk memory block.
	
	The function increases the available size of the memory block by decreasing its
	used space by size octets. The function does not perform any checks. It blindly
	substracts the size, in octets, from the member pNextAvailable and increases
	stFreeSize by the same amount. The caller is responsible for the correct alignment
	and prevention of data corruption.
*/
void popSBULKMEMBLOCK					(
			SBULKMEMBLOCK					*pb,
			size_t							size
										)
;

/*
	popSBULKMEM
	
	Pops the provided size (parameter size) of bytes from the SBULKMEM bulk memory
	pPlinth points to. The pop occurs on the most recently used SBULKMEMBLOCK structure
	within the singly-linked list. This should ensure that the most recently allocated
	memory block can be popped.

	The function increases the available size of the memory block by decreasing its
	used space by size octets. The function does not perform any checks. It blindly
	substracts the size, in octets, from the member pNextAvailable and increases
	stFreeSize by the same amount. The caller is responsible for the correct alignment
	and prevention of data corruption.
	
	The trick with storing the most recently used SBULKMEMBLOCK in one of the plinth's
	members is probably not the best approach. The entire design might change in the
	future.
*/
#ifdef BUILD_POPSBULKMEM
	void popSBULKMEM						(
				SBULKMEM						*pPlinth,
				size_t							size
											)
	;
#endif

/*
	Result structur for getSBULKMEMstats ().
*/
typedef struct sbulkmemstats
{
	unsigned int		nSBULKMEMBLOCKs;					// Amount of SBULKMEMBLOCK structures
															//	in the singly-linked list.
	size_t				stDefaultSize;						// The default size.
	size_t				stTotal;							// Total size of all blocks.
	size_t				stFreeTotal;						// Combined available (free) size.
	size_t				stFreeLargest;						// Largest available (free) block.
	size_t				stFreeSmallest;						// Smallest available (free) block.
	size_t				stFreeAverage;						// Average available size.
} SBULKMEMSTATS;

/*
	getSBULKMEMstats

	Obtains some statistics of the SBULKMEM structure pPlinth points to and returns
	the data in the SBULKMEMSTATS structure pStats points to.

	Neither parameter must be NULL.
*/
void getSBULKMEMstats (SBULKMEMSTATS *pStats, SBULKMEM *pPlinth)
;

// To build the test function.
#ifdef DEBUG
	#ifndef BUILD_BULKMALLOC_TEST_FUNCTIONS
	//#define BUILD_BULKMALLOC_TEST_FUNCTIONS
	#endif
#endif

#ifdef BUILD_BULKMALLOC_TEST_FUNCTIONS
	bool bulkmalloc_test_fnct (void);
#else
	#define bulkmalloc_test_fnct()						\
		(true)
#endif

EXTERN_C_END

#endif															// Of #ifndef BULKMALLOC_H.
/****************************************************************************************

	File:		memstrstr.h
	Created:	?

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2014-03-10	Thomas			This history added.
2019-10-13	Thomas			Include files moved to the header.

	The original version of memstrstr () has been taken from
	http://www.koders.com/c/fid2330745E0E8C0A0F5E2CF94799642712318471D0.aspx?s=getopt#L459
	which needed fixing first. The page has disappeared in the meantime (2018). The
	Wayback Machine also holds no copy of it.

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

#ifndef MEMSTRSTR_H
#define MEMSTRSTR_H

// Make sure that rand_s() is available on Windows systems with MSVC 2005
//	or higher.
#if defined(_MSC_VER) && _MSC_VER>=1400
	#ifndef _CRT_RAND_S
		#define _CRT_RAND_S
	#endif
#endif
// Actually, we're not building with outdated compilers anymore.
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif
#include <stdio.h>
#ifdef _MSC_VER
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
	memstrstr

	The function returns a pointer to the first occurrence of s2 in s1.
	If s2 cannot be found in s1 the return value is NULL. If size2 is
	0 the function returns s1.

	The function memstrstr is basically a replacement for strstr
	(http://www.cppreference.com/stdstring/strstr.html) but does not require
	NULL terminated strings. It can handle any buffer which can contain any
	byte sequence including NULL characters.

	The original version of this function has been taken from
	http://www.koders.com/c/fid2330745E0E8C0A0F5E2CF94799642712318471D0.aspx?s=getopt#L459
	which needed fixing first. The page has disappeared in the meantime (2018). The
	Wayback Machine also holds no copy of it.

	For Linux systems, this function could be replaced by memmem (). See
	https://man7.org/linux/man-pages/man3/memmem.3.html .
*/
char *memstrstr (const char *s1, size_t size1, const char *s2, size_t size2)
;

/*
	memstrstrn

	Like memstrstr but only returns the nth occurrance of s2 in s1 if
	s2 has been found amount times in s1. Returns NULL if s1 does not
	contain s2 amount times.

	Example:
	s1: "This is a test for memstrstrn."
	s2: "e"
	amount: 2 (second occurrance of s2 in s1)
	memstrstrn (s1, strlen (s1), s2, strlen (s2), 2);
	Returns "emstrstrn."
*/
char *memstrstrn (char *s1, size_t size1, char *s2, size_t size2, size_t amount)
;

/*
	memchrreplace

	Replaces all occurrences of s1 in s with s2.
*/
size_t memchrreplace (char *s, size_t size, char s1, char s2)
;

/*
	memstrchr
	
	Like strchr but honours the length of str by returning NULL if character is not
	within the memory block up to str + len. See
	https://cplusplus.com/reference/cstring/strchr/ for more information.
*/
char *memstrchr (const char *str, size_t len, char character);

/*
	memstrrchr
	
	Like strrchr but with a length parameter instead of a NUL-terminated string.
	See https://cplusplus.com/reference/cstring/strrchr/ for more information.
*/
char *memstrrchr (const char *str, size_t len, char character);

#ifdef __cplusplus
}																// Closing bracket for extern "C".
#endif

#endif															// Of #ifndef MEMSTRSTR_H .
/****************************************************************************************

	File:		VectorC.h
	Why:		Implements vector types in C.
	OS:			-
	Author:		Thomas
	Created:	2019-12-09
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-12-09	Thomas			Created.
2020-01-17	Thomas			Documentation from https://github.com/rxi/vec partly
							 added here for convenience.
							 
****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Implements vectors (variable arrays) in C. If you change this text please copy
	and paste it in the code or header file too.

	The code has been inspired by several different sources and changed/extended.

	Sources:
	https://github.com/rxi/vec
	https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
	https://stackoverflow.com/questions/4694401/how-to-replicate-vector-in-c
	https://github.com/Mashpoe/c-vector

	Most of the code comes from https://github.com/rxi/vec .
	A good introduction can be found at https://jameshfisher.com/2017/04/06/rxi-vec/ .
	The project itself at https://github.com/rxi/vec contains the basics.

	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Since most of the code is from the rxi implementation: Copyright (c) 2014 rxi

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

#ifndef VECTORC_H
#define VECTORC_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../pre/externC.h"
	#endif

#endif

BEGIN_C_DECLS

/** 
 * Copyright (c) 2014 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */
 
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <stdlib.h>
#include <string.h>

#define VEC_VERSION "0.2.1"

/*
	vec
	
	A type-safe dynamic array implementation for C.
	Installation
	
	The vec.c and vec.h files can be dropped into an existing C project and compiled along with it.
	Usage
	
	Before using a vector it should first be initialised using the vec_init() function.
	
	vec_int_t v;
	vec_init(&v);
	vec_push(&v, 123);
	vec_push(&v, 456);
	
	To access the elements of the vector directly the vector's data field can be used.
	
	printf("%d\n", v.data[1]); // Prints the value at index 1
	
	The current length of the vector is stored in the length field of the vector
	
	printf("%d\n", v.length); // Prints the length of the vector
	
	When you are done with the vector the vec_deinit() function should be called on it.
	This will free any memory the vector allocated during use.
	
	vec_deinit(&v);
	
	Types
	
	vec.h provides the following predefined vector types:
	Contained Type 	Type name
	void* 	vec_void_t
	char* 	vec_str_t
	int 	vec_int_t
	char 	vec_char_t
	float 	vec_float_t
	double 	vec_double_t
	
	To define a new vector type the vec_t() macro should be used:
	
	/// Creates the type uint_vec_t for storing unsigned ints
	typedef vec_t(unsigned int) uint_vec_t;
	
	Functions
	
	All vector functions are macro functions. The parameter v in each function should be
	a pointer to the vec struct which the operation is to be performed on.
	vec_t(T)
	
	Creates a vec struct for containing values of type T.
	
	// Typedefs the struct `fp_vec_t` as a container for type FILE*
	typedef vec_t(FILE*) fp_vec_t;
	
*/

#define vec_unpack_(v)\
  (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)


#define vec_t(T)\
  struct { T *data; size_t length, capacity; }

/*
	vec_init(v)
	
	Initialises the vector, this must be called before the vector can be used.
*/
#define vec_init(v)\
  memset((v), 0, sizeof(*(v)))

/*
	vec_deinit(v)
	
	Deinitialises the vector, freeing the memory the vector allocated during use;
	this should be called when we're finished with a vector.
*/
#define vec_deinit(v)\
  ( free((v)->data),\
    vec_init(v) ) 

/*
	vec_push(v, val)
	
	Pushes a value to the end of the vector. Returns 0 if the operation was successful,
	otherwise -1 is returned and the vector remains unchanged.
*/
#define vec_push(v, val)\
  ( vec_expand_(vec_unpack_(v)) ? -1 :\
    ((v)->data[(v)->length++] = (val), 0), 0 )

/*
	vec_pop(v)
	
	Removes and returns the value at the end of the vector.
*/
#define vec_pop(v)\
  (v)->data[--(v)->length]

/*
	vec_splice(v, start, count)
	
	Removes the number of values specified by count, starting at the index start.
	
	vec_splice(&v, 2, 4); // Removes the values at indices 2, 3, 4 and 5
*/
#define vec_splice(v, start, count)\
  ( vec_splice_(vec_unpack_(v), start, count),\
    (v)->length -= (count) )

/*
	vec_swapsplice(v, start, count)
	
	Removes the number of values specified by count, starting at the index start;
	the removed values are replaced with the last count values of the vector. This
	does not preserve ordering but is O(1).
*/
#define vec_swapsplice(v, start, count)\
  ( vec_swapsplice_(vec_unpack_(v), start, count),\
    (v)->length -= (count) )

/*
	vec_insert(v, idx, val)
	
	Inserts the value val at index idx shifting the elements after the index to make
	room for the new value.
	
	// Inserts the value 123 at the beginning of the vec
	vec_insert(&v, 0, 123);
	
	Returns 0 if the operation was successful, otherwise -1 is returned and the
	vector remains unchanged.
*/
#define vec_insert(v, idx, val)\
  ( vec_insert_(vec_unpack_(v), idx) ? -1 :\
    ((v)->data[idx] = (val), 0), (v)->length++, 0 )
    
/*
	vec_sort(v, fn)
	
	Sorts the values of the vector; fn should be a qsort-compatible compare function.
*/
#define vec_sort(v, fn)\
  qsort((v)->data, (size_t) (v)->length, sizeof(*(v)->data), fn)

/*
	vec_swap(v, idx1, idx2)
	
	Swaps the values at the indices idx1 and idx2 with one another.
*/
#define vec_swap(v, idx1, idx2)\
  vec_swap_(vec_unpack_(v), idx1, idx2)

/*
	vec_truncate(v, len)
	
	Truncates the vector's length to len. If len is greater than the vector's current
	length then no change is made.
*/
#define vec_truncate(v, len)\
  ((v)->length = (len) < (v)->length ? (len) : (v)->length)

/*
	vec_clear(v)
	
	Clears all values from the vector reducing the vector's length to 0.
*/
#define vec_clear(v)\
  ((v)->length = 0)

/*
	vec_first(v)
	
	Returns the first value in the vector. This should not be used on an empty vector.
*/
#define vec_first(v)\
  (v)->data[0]

/*
	vec_last(v)
	
	Returns the last value in the vector. This should not be used on an empty vector.
*/
#define vec_last(v)\
  (v)->data[(v)->length - 1]

/*
	vec_reserve(v, n)
	
	Reserves capacity for at least n elements in the given vector; if n is less than
	the current capacity then vec_reserve() does nothing. Returns 0 if the operation
	was successful, otherwise -1 is returned and the vector remains unchanged.
*/
#define vec_reserve(v, n)\
  vec_reserve_(vec_unpack_(v), n)

/*
	vec_compact(v)
	
	Reduces the vector's capacity to the smallest size required to store its current
	number of values. Returns 0 if the operation is successful, otherwise -1 is
	returned and the vector remains unchanged.
*/
#define vec_compact(v)\
  vec_compact_(vec_unpack_(v))

/*
	vec_pusharr(v, arr, count)
	
	Pushes the contents of the array arr to the end of the vector. count should be the
	number of elements in the array.
*/
#define vec_pusharr(v, arr, count)\
  do {\
    int i__, n__ = (count);\
    if (vec_reserve_po2_(vec_unpack_(v), (v)->length + n__) != 0) break;\
    for (i__ = 0; i__ < n__; i__++) {\
      (v)->data[(v)->length++] = (arr)[i__];\
    }\
  } while (0)

/*
	vec_extend(v, v2)
	
	Appends the contents of the v2 vector to the v vector.
*/
#define vec_extend(v, v2)\
  vec_pusharr((v), (v2)->data, (v2)->length)

/*
	vec_find(v, val, idx)
	
	Finds the first occurrence of the value val in the vector. idx should be an int
	where the value's index will be written; idx is set to -1 if val could not be
	found in the vector.
*/
#define vec_find(v, val, idx)\
  do {\
    for ((idx) = 0; (idx) < (v)->length; (idx)++) {\
      if ((v)->data[(idx)] == (val)) break;\
    }\
    if ((idx) == (v)->length) (idx) = -1;\
  } while (0)

/*
	vec_remove(v, val)
	
	Removes the first occurrence of the value val from the vector. If the val is not
	contained in the vector then vec_remove() does nothing.
*/
#define vec_remove(v, val)\
  do {\
    int idx__;\
    vec_find(v, val, idx__);\
    if (idx__ != -1) vec_splice(v, idx__, 1);\
  } while (0)

/*
	vec_reverse(v)
	
	Reverses the order of the vector's values in place. For example, a vector
	containing 4, 5, 6 would contain 6, 5, 4 after reversing.
*/
#define vec_reverse(v)\
  do {\
    size_t i__ = (v)->length / 2;\
    while (i__--) {\
      vec_swap((v), i__, (v)->length - (i__ + 1));\
    }\
  } while (0)

/*
	vec_foreach(v, var, iter)
	
	Iterates the values of the vector from the first to the last. var should be a
	variable of the vector's contained type where the value will be stored with each
	iteration. iter should be an int used to store the index during iteration.
	
	// Iterates and prints the value and index of each value in the float vec
	int i; float val;
	vec_foreach(&v, val, i) {
	  printf("%d : %f\n", i, val);
	}
*/
#define vec_foreach(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = 0;\
        (iter) < (v)->length && (((var) = (v)->data[(iter)]), 1);\
        ++(iter))

/*
	vec_foreach_rev(v, var, iter)
	
	Iterates the values of the vector from the last to the first. See vec_foreach()
*/
#define vec_foreach_rev(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = (v)->length - 1;\
        (iter) >= 0 && (((var) = (v)->data[(iter)]), 1);\
        --(iter))

/*
	vec_foreach_ptr(v, var, iter)
	
	Iterates the value pointers of the vector from first to last. var should be a
	variable of the vector's contained type's pointer. See vec_foreach().
	
	// Iterates and prints the value and index of each value in the float vector
	int i; float *val;
	vec_foreach_ptr(&v, val, i) {
	  printf("%d : %f\n", i, *val);
}
*/
#define vec_foreach_ptr(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = 0;\
        (iter) < (v)->length && (((var) = &(v)->data[(iter)]), 1);\
        ++(iter))

/*
	vec_foreach_ptr_rev(v, var, iter)
	
	Iterates the value pointers of the vector from last to first. See vec_foreach_ptr()
*/
#define vec_foreach_ptr_rev(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = (v)->length - 1;\
        (iter) >= 0 && (((var) = &(v)->data[(iter)]), 1);\
        --(iter))

/*
	License
	
	This library is free software; you can redistribute it and/or modify it under the
	terms of the MIT license. See LICENSE for details.
*/

int vec_expand_(char **data, size_t *length, size_t *capacity, size_t memsz);
int vec_reserve_(char **data, size_t *length, size_t *capacity, size_t memsz, size_t n);
int vec_reserve_po2_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t n);
int vec_compact_(char **data, size_t *length, size_t *capacity, size_t memsz);
int vec_insert_(char **data, size_t *length, size_t *capacity, size_t memsz,
                size_t idx);
void vec_splice_(char **data, size_t *length, size_t *capacity, size_t memsz,
	size_t start, size_t count);
void vec_swapsplice_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t start, size_t count);
void vec_swap_(char **data, size_t *length, size_t *capacity, size_t memsz,
               size_t idx1, size_t idx2);

typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(float) vec_float_t;
typedef vec_t(double) vec_double_t;
// More type definitions can be found in VectorCtypes.h.

END_C_DECLS

#endif															// End of VECTORC_H.
/****************************************************************************************

	File		shortmonths.h
	Why:		An array with the short month names in English.
	OS:			C99
	Created:	2025-02-02

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-02	Thomas			Created.

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

#ifndef U_SHORTMONTHS_H
#define U_SHORTMONTHS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./DLLimport.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/DLLimport.h"
	#endif

#endif

/*
	Our short months.
*/
CUNILOG_DLL_IMPORT extern const char ccdtMnths [12][4];

#endif														// Of #ifdef U_SHORTMONTHS_H.
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
/****************************************************************************************

	File		ISO__DATE__.h
	Why:		Predefined macros __DATE__ and __TIME__ in ISO 8601 format.
	OS:			C99
	Created:	2024-10-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-29	Thomas			Created.

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

#ifndef ISO__DATE__H
#define ISO__DATE__H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

#ifndef LEN_ISO8601DATE
#define LEN_ISO8601DATE						(10)				// "YYYY-MM-DD"
#endif
#ifndef SIZ_ISO8601DATE
#define SIZ_ISO8601DATE						(LEN_ISO8601DATE + 1)
#endif

#ifndef LEN_ISO8601DATETIMESTAMP_NO_OFFS
#define LEN_ISO8601DATETIMESTAMP_NO_OFFS	(19)				// "YYYY-MM-DD hh:mm:ss"
#endif
#ifndef SIZ_ISO8601DATETIMESTAMP_NO_OFFS
#define SIZ_ISO8601DATETIMESTAMP_NO_OFFS	(LEN_ISO8601DATETIMESTAMP_NO_OFFS + 1)
#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef _ISO_DATE_
#define _ISO_DATE_						"_ISO_DATE_"
#endif

EXTERN_C_BEGIN

/*
	szBuild_ISO__DATE__

	Returns the build date in ISO 8601 format, like "2024-10-30".

	The function is only re-entrant after it returned from its first invocation.
*/
const char *szBuild_ISO__DATE__ (void);
TYPEDEF_FNCT_PTR (const char *, szBuild_ISO__DATE__) (void);

/*
	szBuild_ISO__TIME__

	Returns the build time, like "16:20:14". This function/macro only exists for
	completeness, because the predefinded macro __TIME__ serves the very same
	purpose, which is in fact precisely what the function/macro returns.
*/
#if defined (DEBUG) && !defined (CUNILOG_BUILD_SHARED_LIBRARY)
	const char *szBuild_ISO__TIME__ (void);
#else
	#define szBuild_ISO__TIME__()	__TIME__
#endif

/*
	szBuild_ISO__DATE__TIME__

	Returns the build date and time in ISO 8601 format, like "2024-10-30 23:59:01".
	Note that ISO 8601 requires a 'T' between date and time, while this function
	puts a blank (space, ' ') in its place instead.

	The function is only re-entrant after it returned from its first invocation, or
	after the function szBuild_ISO__DATE__ () has been called.
*/
const char *szBuild_ISO__DATE__TIME__ (void);
TYPEDEF_FNCT_PTR (const char *, szBuild_ISO__DATE__TIME__) (void);

/*
	replace_ISO_DATE_

	Replaces all occurrences of "_ISO_DATE_" in sz with the build date in ISO 8601
	format, like "2024-10-30". Note that the two strings have the same length, hence
	the replacement(s) won't change the length of sz.
	
	The parameter len can be (size_t) -1, in which case the function calls strlen ()
	to obtain it. For convenience, the macro USE_STRLEN is defined as ((size_t) -1).

	The function returns the amount of replacements carried out.

	The function is only re-entrant after it returned from its first invocation, or
	after the function szBuild_ISO__DATE__ () has been called.
*/
size_t replace_ISO_DATE_ (char *sz, size_t len);
TYPEDEF_FNCT_PTR (size_t, replace_ISO_DATE_) (char *sz, size_t len);

/*
	ISO_DATE_Test_function

	Tests the module.
*/
#ifdef ISO_DATE_BUILD_TEST_FNCT
	bool ISO_DATE_Test_function (void);
#else
	#define ISO_DATE_Test_function() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef ISO__DATE__H.
/****************************************************************************************

	File:		ubfdebug.h
	Why:		Contains debugging functions.
	OS:			Windows/POSIX
	Author:		Thomas
	Created:	2017-10-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2017-10-24	Thomas			Created.
2018-05-26	Thomas			Compiler warning Linux/Android fixed by changing
							 the loop variable from int to unsigned int.
2019-08-24	Thomas			Module OS/ubf_debug.c/h should be obsolete now.

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

#ifndef U_UBF_DEBUG_DEB_H_INCLUDED
#define U_UBF_DEBUG_DEB_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	#include <assert.h>
#endif

/*
	Below are the macros that turn on the functions listed in the comments on the right-
	hand side of the macro definitions.
*/
#ifndef UBF_DEBUG_HEX_DUMP
//#define UBF_DEBUG_HEX_DUMP									// When defined, enables
																//	ubf_debug_hex_dump ().
#endif
#ifdef UBF_DEBUG_NO_HEX_DUMP
	#undef UBF_DEBUG_HEX_DUMP
#endif

// When defined, enables ubf_debug_printf () and ubf_debug_puts ().
#ifdef DEBUG
	#ifndef UBF_DEBUG_USE_PRINTF
	#define UBF_DEBUG_USE_PRINTF
	#endif
#endif

// When defined, uses our output abort functions. If not, a simple
//	ABORT() macro is used. It is not recommended to uncomment this
//	definition. Rather define UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
//	in the development environment or project file.
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#ifndef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#define UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#endif
#endif
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#ifdef UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
		#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#undef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#endif
	#endif
#endif

#ifndef UBF_DEBUG_MSG_STRLEN
#define UBF_DEBUG_MSG_STRLEN		(4096)
#endif

// The character used to identify buffer overruns and uninitialised areas. Can (and
//	should) be used as a general filler for debug purposes.
#ifndef UBF_ERROR_CHAR
#define UBF_ERROR_CHAR	'\x55'
#endif
#ifndef UBF_ERROR_CINT
#define UBF_ERROR_CINT	0x55
#endif

EXTERN_C_BEGIN

/*
	Macros to check if all members of a structure or union have been initialised.
	Check to see if we forgot to initialise a member. This is important when more
	members are added later.
	
	UBF_DEBUG_CHECK_STRUCT_DECLARATION()
	
	Sets the character used to initialise the structure before the real initialisation
	takes place.
	
	UBF_DEBUG_CHECK_STRUCT_ASSERTION()
	
	Checks if there are any octets within the structure's memory block that haven't been
	initialised by testing that no byte contains the character set with the macro
	UBF_DEBUG_CHECK_STRUCT_DECLARATION().
	
	
	Example:
	
	typedef struct structname
	{
		int		i1;
		int		i2;
		int		i3;
		int		i4;
		int		in;
	} STRUCTNAME;
	
	void test (void)
	{
		STRUCTNAME		sn;
		
		UBF_DEBUG_CHECK_STRUCT_DECLARATION (&sn, STRUCTNAME, 0x0D);
		sn.i1 = 1;
		sn.i2 = 2;
		//...
		sn.in = -1;
		UBF_DEBUG_CHECK_STRUCT_ASSERTION (&sn, STRUCTNAME);
	}
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(pstructure, typestruct, c)				\
		unsigned int	uStructCheck;													\
		unsigned char	*chStructCheck;													\
		unsigned char	cStructCheck		= (c);										\
		memset ((pstructure), (c), sizeof (typestruct))
#else
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(c)
#endif
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)						\
		chStructCheck = (char *) (pstructure);											\
		for (uStructCheck = 0; uStructCheck < sizeof (typestruct); uStructCheck ++)		\
		{																				\
			if (*chStructCheck == cStructCheck)											\
				_ASSERT (false);														\
			++ chStructCheck;															\
		}
#else
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)
#endif

/*
	UBF_DEBUG_CHECK_CALLED_ONLY_ONCE
	
	Macro to check that the function using it is only invoked once. Useful for
	initialisation functions.
	
	UBF_DEBUG_CHECK_RESET_ONLY_ONCE
	
	Resets the flag. Useful to check that a function that is not re-entrant is
	not called again before the previous instance has returned.
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)	\
		static bool	flagname;							\
		ubf_assert (!flagname);							\
		flagname = TRUE
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)	\
		flagname = FALSE
#else
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)
#endif

/*
	UBF_DEFINE_GUARD_VAR										// Define guard variable.
	UBF_CHECK_GUARD_VAR											// Check/test guard variable.
	UBF_DEF_GUARD_VAR											// Define guard variable.
	UBF_TST_GUARD_VAR											// Check/test guard variable.
	UBF_CHK_GUARD_VAR											// Check/test guard variable.
	
	Macros to define and to check guard variables. The variable defined is of
	type char []. These macros can help find buffer overruns.
	
	Examples:
	
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	The following example checks for an overrun of the array:
	
	int		i [105];
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	...
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	If data is written beyond the array's memory location testvar is overwritten,
	at least on some platforms.
	Test data is defined with UBF_DEFINE_GUARD_VAR().
	The macro UBF_CHECK_GUARD_VAR() determines if the test variable's content has
	been destroyed.
*/
#ifdef DEBUG
	#ifndef UBF_DEFINE_GUARD_VAR
	#define UBF_DEFINE_GUARD_VAR(var, value)			\
		char	var [] = #value
	#endif
	#ifndef UBF_CHECK_GUARD_VAR
	#define UBF_CHECK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_DEF_GUARD_VAR
	#define UBF_DEF_GUARD_VAR(var, value)				\
		char	var [] = #value
	#endif
	#ifndef UBF_TST_GUARD_VAR
	#define UBF_TST_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_CHK_GUARD_VAR
	#define UBF_CHK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
#else
	#define UBF_DEFINE_GUARD_VAR(var, value)
	#define UBF_CHECK_GUARD_VAR(var, value)
	#define UBF_DEF_GUARD_VAR(var, value)
	#define UBF_TST_GUARD_VAR(var, value)
	#define UBF_CHK_GUARD_VAR(var, value)
#endif

/*
	ubf_debug_assert

	Outputs the message only if the assertion doesn't pass.
	
	ubf_debug_assert_pass

	Outputs the message chDebugMessage and then implements an _ASSERT () with bAssert.

	Use the macro UBF_DEBUG_ASSERT() or ubf_assert_msg() to fill in __FILE__ and __LINE__
	for the parameters chFilePath and uiLineNum. Both macros are identical. See
	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html for an explanation
	of the __FILE__ and __LINE__ macros. The macro ubf_assert () is probably what should
	be used as often as possible.

	In release versions these are macros that expand to nothing.
	
	It is recommended to use the ubf_assert() macro, which expects one parameter only. It
	stringifies this parameter for the output text. Since this is sometimes not possible
	due to the limitations of the preprocessor's stringify operator, or it's not
	desirable if condition and message text should differ, the macro ubf_assert_msg() can
	be used.

	Examples:

	// All these lines have the same or similar functionality:
	ubf_debug_assert (a > b, "a > b", __FILE__, __LINE__);
	UBF_DEBUG_ASSERT (a > b, "a > b", __FILE__, __LINE__);
	ubf_assert (a > b);
	ubf_assert_msg (a > b, "a > b");
	
	Explanation and further notes:
	
	Although assert () on Windows and Linux works great, it does exactly what the
	documentation says on Android: it aborts. No message, no information on where
	it stopped, nor why.
	
	ubf_assert (a > b) is a replacement for assert (). It displays a message with
	the assertion before it aborts.
	
	ubf_assert_msg (a > b, "Arbitrary message") is a replacement for assert () that
	outputs "Arbitrary message" when the assertion fails instead of the actual
	assertion.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	// Debug version.
	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ubf_debug_assert		(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert(b, c, p, n)			\
			ASSERT (b)
	#endif
	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ubf_debug_assert_pass	(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert_pass(b, c, p, n)		\
			ASSERT (b)
	#endif
	#ifndef UBF_DEBUG_ASSERT
	#define UBF_DEBUG_ASSERT(b)							\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert
	#define ubf_assert(b)								\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_msg
	#define ubf_assert_msg(b,m)							\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_message
	#define ubf_assert_message(b,m)						\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_pass
	#define ubf_assert_pass(b)							\
				ubf_debug_assert_pass ((b), #b, __FILE__, __LINE__)
	#endif
	/*
		ubf_assert_Android
		
		Prints the message on Android but is a simple _ASSERT() on other platforms. That's
		because the application simply dies with an _ASSERT() on Android.
	*/
	#ifdef OS_IS_ANDROID
		#define ubf_assert_Android(b)					\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
		#define ubf_assert_Android_msg(b,m)				\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Android(b)					\
				_ASSERT (b)
		#define ubf_assert_Android_msg(b,m)				\
				_ASSERT (b)
	#endif
	/*
		ubf_assert_Linux
		
		Prints the message on Linux but is a simple _ASSERT() on other platforms.
	*/
	#ifdef OS_IS_LINUX
		#define ubf_assert_Linux(b)						\
				ubf_debug_assert ((b), #b, __FILE__, __LINE__)
		#define ubf_assert_Linux_msg(b,m)				\
				ubf_debug_assert ((b), m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Linux(b)						\
				_ASSERT (b)
		#define ubf_assert_Linux_msg(b, m)				\
				_ASSERT (b)
	#endif
#else
	// Release version.
	#define ubf_debug_assert(b,m,f,l)
	#define ubf_debug_assert_pass(b,m,f,l)
	#define UBF_DEBUG_ASSERT(b)
	#define ubf_assert(b)
	#define ubf_assert_msg(b,m)
	#define ubf_assert_message(b,m)
	#define ubf_assert_pass(b)
	#ifdef UBF_ANDROID
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#else
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#endif
	#ifdef UBF_LINUX
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#else
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#endif
#endif

/*
	ubf_debug_fill_mem

	Fills the memory mem points to with UBF_ERROR_CHAR, which is 55h, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem (void *mem, size_t len);
#else
	#define ubf_debug_fill_mem(m,l)
#endif

/*
	ubf_debug_check_mem
	
	Assert that a memory block consists of UBF_ERROR_CHAR octets.
*/
#ifdef DEBUG
	void ubf_debug_check_mem (char *mem, size_t len);
#else
	#define ubf_debug_check_mem(m, l)
#endif

/*
	ubf_debug_fill_mem_with

	Fills the memory mem points to with the value of c, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem_with (void *mem, char c, size_t len);
#else
	#define ubf_debug_fill_mem_with(m, c, l)
#endif

/*
	ubf_debug_check_mem_with

	Assert that a memory block consists of len octets filled with c.
*/
#ifdef DEBUG
	void ubf_debug_check_mem_with (char *mem, char c, size_t len);
#else
	#define ubf_debug_check_mem_with(m, c, l)
#endif

/*
	ubf_debug_hex_dump
	
	Calls ubf_data_dump_puts () in ubfdump.c if UBF_DEBUG_HEX_DUMP is defined.
	If UBF_DEBUG_HEX_DUMP is not defined, the function is expanded to a no-operation.
*/
#ifdef UBF_DEBUG_HEX_DUMP
	void ubf_debug_hex_dump (const char *chOutput, size_t stOutput);
#else
	#define ubf_debug_hex_dump(ch,st)
#endif

/*
	ubf_debug_printf
	ubf_debug_puts
	
	Debug versions of printf () and puts (). To make these calls no-operations (empty)
	macros, undefine UBF_DEBUG_USE_PRINTF. In release versions they are empty definitions.
*/
#ifdef UBF_DEVICE_GUI
	#ifdef DEBUG
		void ubf_debug_printf (const char *format, ...);
		void ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
	#ifdef UBF_DEBUG_USE_PRINTF
		#undef UBF_DEBUG_USE_PRINTF
	#endif
#else
	#ifdef UBF_DEBUG_USE_PRINTF
		int ubf_debug_printf (const char *format, ...);
		int ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
#endif

// Debug sleep. Sleeps in debug versions (milliseconds) but not in release builds.
#ifdef DEBUG
	#define ubf_debug_sleep_ms(s)			ubf_sleep_ms (s)
#else
	#define ubf_debug_sleep_ms(s)
#endif

// Macros to abort in debug versions.
#ifdef DEBUG
	#define DEBUGABORT()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORTDEBUG()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORT()			ASSERT (false)
#else
	#define DEBUGABORT()
	#define DBGABORT()
	#define ABORTDEBUG()
	#define DBGABORT()
	#define ABORT()
#endif

/*
	ubf_expect_bool_AND
	ubf_assert_bool_AND

	Macro to binary AND an expectation. Useful in test functons.

	bool	bOk		= TRUE;
	int		a		= 0;
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 3 == a);
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 6 == a);
	ubf_assert_true (bOk);
*/
#define ubf_expect_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))
#define ubf_assert_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))

/*
	ubf_expect_bool_AND_0
	ubf_assert_bool_AND_0

	Macro to binary AND an expectation to be 0.
*/
#define ubf_expect_bool_AND_0(b, expectation)			\
			(b) &= (0 == (expectation));				\
			ubf_assert (0 == (expectation))
#define ubf_assert_bool_AND_0(b, expectation)			\
			(b) &= (0 == (expectation));				\
			ubf_assert (0 == (expectation))

/*
	ubf_assert_TRUE
	ubf_assert_FALSE
	ubf_expect_TRUE
	ubf_expect_FALSE
	ubf_assert_true
	ubf_expect_true
	ubf_assert_false
	ubf_expect_false

	Macros that assert that the provided boolean is either TRUE or FALSE.
*/
#define ubf_assert_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_expect_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_assert_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_expect_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_assert_true(b)								\
			ubf_assert (true == (b))
#define ubf_expect_true(b)								\
			ubf_assert (true == (b))
#define ubf_assert_false(b)								\
			ubf_assert (false == (b))
#define ubf_expect_false(b)								\
			ubf_assert (false == (b))


/*
	ubf_assert_NULL
	ubf_expect_NULL
	ubf_assert_not_NULL
	ubf_expect_not_NULL
	ubf_assert_non_NULL
	ubf_expect_non_NULL

	Macros that assert that the provided pointer is either NULL or non-NULL.
*/
#define ubf_assert_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_expect_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_assert_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_assert_non_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_non_NULL(p)							\
			ubf_assert (NULL != (p))

/*
	ubf_assert_0
	ubf_expect_0
	ubf_assert_non_0
	ubf_expect_non_0
	ubf_assert_zero
	ubf_expect_zero
	ubf_assert_non_zero
	ubf_expect_non_zero

	Macros that assert that the parameter expression evaluates to zero or
	non-zero.
*/
#define ubf_assert_0(v)									\
			ubf_assert (0 == (v))
#define ubf_expect_0(v)									\
			ubf_assert (0 == (v))
#define ubf_assert_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_expect_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_assert_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_expect_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_assert_non_zero(v)							\
			ubf_assert (0 != (v))
#define ubf_expect_non_zero(v)							\
			ubf_assert (0 != (v))

/*
	ONLY_IN_DEBUG

	Emits the given code only in debug versions.
*/
#ifdef DEBUG
	#define ONLY_IN_DEBUG(code)							\
				code;
#else
	#define ONLY_IN_DEBUG(code)
#endif

EXTERN_C_END

#endif															// Of U_UBF_DEBUG_DEB_H_INCLUDED.
/****************************************************************************************

	File:		stransi.h
	Why:		Functions for ANSI escape codes.
	OS:			C99
	Author:		Thomas
	Created:	2025-02-14

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-14	Thomas			Created.

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

#ifndef U_STRANSI_H
#define U_STRANSI_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdarg.h>
	#include <stdbool.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

/*
	Reset.
*/
#define STR_ANSI_RESET					"\033[0m"
#define SIZ_ANSI_RESET					(sizeof (STR_ANSI_RESET))
#define LEN_ANSI_RESET					(SIZ_ANSI_RESET - 1)

/*
	Coulrs only. These are not ANSI escape sequences on their own and cannot be used
	as such!
*/
#define STR_ANSI_STDCOL_BLACK			"30m"
#define STR_ANSI_STDCOL_RED				"31m"
#define STR_ANSI_STDCOL_GREEN			"32m"
#define STR_ANSI_STDCOL_YELLOW			"33m"
#define STR_ANSI_STDCOL_BLUE			"34m"
#define STR_ANSI_STDCOL_MAGENTA			"35m"
#define STR_ANSI_STDCOL_CYAN			"36m"
#define STR_ANSI_STDCOL_WHITE			"37m"

/*
	Normal foreground colours.
*/
#define STR_ANSI_FGCOL_BLACK			"\033[30m"
#define SIZ_ANSI_FGCOL_BLACK			(sizeof (STR_ANSI_FGCOL_BLACK))
#define LEN_ANSI_FGCOL_BLACK			(SIZ_ANSI_FGCOL_BLACK - 1)

#define STR_ANSI_FGCOL_RED				"\033[31m"
#define SIZ_ANSI_FGCOL_RED				(sizeof (STR_ANSI_FGCOL_RED))
#define LEN_ANSI_FGCOL_RED				(SIZ_ANSI_FGCOL_RED - 1)

#define STR_ANSI_FGCOL_GREEN			"\033[32m"
#define SIZ_ANSI_FGCOL_GREEN			(sizeof (STR_ANSI_FGCOL_GREEN))
#define LEN_ANSI_FGCOL_GREEN			(SIZ_ANSI_FGCOL_GREEN - 1)

#define STR_ANSI_FGCOL_YELLOW			"\033[33m"
#define SIZ_ANSI_FGCOL_YELLOW			(sizeof (STR_ANSI_FGCOL_YELLOW))
#define LEN_ANSI_FGCOL_YELLOW			(SIZ_ANSI_FGCOL_YELLOW - 1)

#define STR_ANSI_FGCOL_BLUE				"\033[34m"
#define SIZ_ANSI_FGCOL_BLUE				(sizeof (STR_ANSI_FGCOL_BLUE))
#define LEN_ANSI_FGCOL_BLUE				(SIZ_ANSI_FGCOL_BLUE - 1)

#define STR_ANSI_FGCOL_MAGENTA			"\033[35m"
#define SIZ_ANSI_FGCOL_MAGENTA			(sizeof (STR_ANSI_FGCOL_MAGENTA))
#define LEN_ANSI_FGCOL_MAGENTA			(SIZ_ANSI_FGCOL_MAGENTA - 1)

#define STR_ANSI_FGCOL_CYAN				"\033[36m"
#define SIZ_ANSI_FGCOL_CYAN				(sizeof (STR_ANSI_FGCOL_CYAN))
#define LEN_ANSI_FGCOL_CYAN				(SIZ_ANSI_FGCOL_CYAN - 1)

#define STR_ANSI_FGCOL_WHITE			"\033[37m"
#define SIZ_ANSI_FGCOL_WHITE			(sizeof (STR_ANSI_FGCOL_WHITE))
#define LEN_ANSI_FGCOL_WHITE			(SIZ_ANSI_FGCOL_WHITE - 1)

/*
	Bright foreground colours.

	Note that bright black is grey.
*/
#define STR_ANSI_FGCOL_BRIGHT_BLACK		"\033[90m"
#define SIZ_ANSI_FGCOL_BRIGHT_BLACK		(sizeof (STR_ANSI_FGCOL_BRIGHT_BLACK))
#define LEN_ANSI_FGCOL_BRIGHT_BLACK		(SIZ_ANSI_FGCOL_BRIGHT_BLACK - 1)

#define STR_ANSI_FGCOL_GREY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define SIZ_ANSI_FGCOL_GREY				(sizeof (STR_ANSI_FGCOL_GREY))
#define LEN_ANSI_FGCOL_GREY				(SIZ_ANSI_FGCOL_GREY - 1)

#define STR_ANSI_FGCOL_GRAY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define SIZ_ANSI_FGCOL_GRAY				(sizeof (STR_ANSI_FGCOL_GRAY))
#define LEN_ANSI_FGCOL_GRAY				(SIZ_ANSI_FGCOL_GRAY - 1)

#define STR_ANSI_FGCOL_BRIGHT_RED		"\033[91m"
#define SIZ_ANSI_FGCOL_BRIGHT_RED		(sizeof (STR_ANSI_FGCOL_BRIGHT_RED))
#define LEN_ANSI_FGCOL_BRIGHT_RED		(SIZ_ANSI_FGCOL_BRIGHT_RED - 1)

#define STR_ANSI_FGCOL_BRIGHT_GREEN		"\033[92m"
#define SIZ_ANSI_FGCOL_BRIGHT_GREEN		(sizeof (STR_ANSI_FGCOL_BRIGHT_GREEN))
#define LEN_ANSI_FGCOL_BRIGHT_GREEN		(SIZ_ANSI_FGCOL_BRIGHT_GREEN - 1)

#define STR_ANSI_FGCOL_BRIGHT_YELLOW	"\033[93m"
#define SIZ_ANSI_FGCOL_BRIGHT_YELLOW	(sizeof (STR_ANSI_FGCOL_BRIGHT_YELLOW))
#define LEN_ANSI_FGCOL_BRIGHT_YELLOW	(SIZ_ANSI_FGCOL_BRIGHT_YELLOW - 1)

#define STR_ANSI_FGCOL_BRIGHT_BLUE		"\033[94m"
#define SIZ_ANSI_FGCOL_BRIGHT_BLUE		(sizeof (STR_ANSI_FGCOL_BRIGHT_BLUE))
#define LEN_ANSI_FGCOL_BRIGHT_BLUE		(SIZ_ANSI_FGCOL_BRIGHT_BLUE - 1)

#define STR_ANSI_FGCOL_BRIGHT_MAGENTA	"\033[95m"
#define SIZ_ANSI_FGCOL_BRIGHT_MAGENTA	(sizeof (STR_ANSI_FGCOL_BRIGHT_MAGENTA))
#define LEN_ANSI_FGCOL_BRIGHT_MAGENTA	(SIZ_ANSI_FGCOL_BRIGHT_MAGENTA - 1)

#define STR_ANSI_FGCOL_BRIGHT_CYAN		"\033[96m"
#define SIZ_ANSI_FGCOL_BRIGHT_CYAN		(sizeof (STR_ANSI_FGCOL_BRIGHT_CYAN))
#define LEN_ANSI_FGCOL_BRIGHT_CYAN		(SIZ_ANSI_FGCOL_BRIGHT_CYAN - 1)

#define STR_ANSI_FGCOL_BRIGHT_WHITE		"\033[97m"
#define SIZ_ANSI_FGCOL_BRIGHT_WHITE		(sizeof (STR_ANSI_FGCOL_BRIGHT_WHITE))
#define LEN_ANSI_FGCOL_BRIGHT_WHITE		(SIZ_ANSI_FGCOL_BRIGHT_WHITE - 1)

/*
	Background colours.

	Note that bright black is grey.
*/
#define STR_ANSI_BGCOL_BLACK			"\033[40m"
#define STR_ANSI_BGCOL_RED				"\033[41m"
#define STR_ANSI_BGCOL_GREEN			"\033[42m"
#define STR_ANSI_BGCOL_YELLOW			"\033[43m"
#define STR_ANSI_BGCOL_BLUE				"\033[44m"
#define STR_ANSI_BGCOL_MAGENTA			"\033[45m"
#define STR_ANSI_BGCOL_CYAN				"\033[46m"
#define STR_ANSI_BGCOL_WHITE			"\033[47m"

/*
	Bright background colours.

	Note that bright black is grey.
*/
#define STR_ANSI_BGCOL_BRIGHT_BLACK		"\033[100m"
#define STR_ANSI_BGCOL_GREY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_BGCOL_GRAY				STR_ANSI_FGCOL_BRIGHT_BLACK
#define STR_ANSI_BGCOL_BRIGHT_RED		"\033[101m"
#define STR_ANSI_BGCOL_BRIGHT_GREEN		"\033[102m"
#define STR_ANSI_BGCOL_BRIGHT_YELLOW	"\033[103m"
#define STR_ANSI_BGCOL_BRIGHT_BLUE		"\033[104m"
#define STR_ANSI_BGCOL_BRIGHT_MAGENTA	"\033[105m"
#define STR_ANSI_BGCOL_BRIGHT_CYAN		"\033[106m"
#define STR_ANSI_BGCOL_BRIGHT_WHITE		"\033[107m"

/*
#define STR_ANSI_TEXT_REGULAR			"\033[0;31m"
#define STR_ANSI_TEXT_BOLD				"\033[1;31m"
#define STR_ANSI_TEXT_LOWINTENSITY		"\033[2;31m"
#define STR_ANSI_TEXT_ITALIC			"\033[3;31m"
#define STR_ANSI_TEXT_UNDERLINE			"\033[4;31m"
#define STR_ANSI_TEXT_BLINKING			"\033[5;31m"
#define STR_ANSI_TEXT_REVERSE			"\033[6;31m"
#define STR_ANSI_TEXT_BACKGROUND		"\033[7;31m"
#define STR_ANSI_TEXT_INVISIBLE			"\033[8;31m"
*/

EXTERN_C_BEGIN

typedef struct stransicoloursequence
{
	char	*szColSequence;
	size_t	lnColSequence;
} STRANSICOLOURSEQUENCE;


/*
	isANSIescSequence

	Checks if the character sequence starting at sz with length ln is an ANSI
	escape sequence.

	The Wikipedia article https://en.wikipedia.org/wiki/ANSI_escape_code has been used
	as the basis to determine if sz is an ANSI escape sequence:

	https://en.wikipedia.org/wiki/ANSI_escape_code#Control_Sequence_Introducer_commands

	"For Control Sequence Introducer, or CSI, commands, the ESC [ (written as \e[, \x1b[
	or \033[ in several programming languages) is followed by any number (including none)
	of "parameter bytes" in the range 0x30-0x3F (ASCII 0-9:;<=>?), then by any number of
	"intermediate bytes" in the range 0x20-0x2F (ASCII space and !"#$%&'()*+,-./), then
	finally by a single "final byte" in the range 0x40-0x7E (ASCII @A-Z[\]^_`a-z{|}~)"

	The function returns the amount of characters belonging to the escape sequence,
	or 0, if sz does not start with an ANSI escape sequence. It never returns a
	value greater than ln.

	The function's purpose is not the ensure that an ANSI escape sequence is syntactically
	correct. Its purpose is rather to identify sequences for removal. For instance, the
	function returns 1 for a single ESC character (1Bh), and 2 for ESC + "[", but both
	are not on their own valid ANSI escape sequences.

	The parameter ln can be USE_STRLEN, in which case the function calls strlen () on sz
	to determine its length.
*/
size_t isANSIescSequence (const char *sz, size_t ln)
;

/*
	removeANSIescSequences

	Removes all ANSI escape sequences from sz and returns its new length.

	The function calls isANSIescSequence () to determine whether an ANSI escape sequence
	should be removed or not. If at leas one ANSI escape sequence has been found at replaced,
	then the function NUL-terminates sz even if it hasn't been NUL-terminated before the
	call.

	The parameter ln can be USE_STRLEN, in which case the function calls strlen () on sz
	to determine its length.

	The return value is the length of the string sz after all found ANSI escape sequences
	have been removed.
*/
size_t removeANSIescSequences (char *sz, size_t ln)
;

/*
	stransi_test_fnct

	Function to test the module.
*/
#ifdef STRANSI_BUILD_TEST_FNCT
	bool stransi_test_fnct (void);
#else
	#define stransi_test_fnct()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_STRANSI_H.
/****************************************************************************************

	File:		check_utf8.h
	Why:		Checks for valid UTF-8
	OS:			C99
	Author:		Thomas
	Created:	2025-01-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-27	Thomas			This history created.
							Acquired from https://github.com/yasuoka/check_utf8 .
							Thanks to YASUOKA Masahiko.
							Function renamed to c_check_utf8 ().

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
	For the original unchanged version, see https://github.com/yasuoka/check_utf8 .
*/

/*
 * Copyright (c) 2024 YASUOKA Masahiko <yasuoka@yasuoka.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef U_CHECK_UTF8_H
#define U_CHECK_UTF8_H

#include <stdbool.h>
#include <stddef.h>

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

EXTERN_C_BEGIN

bool c_check_utf8(const char *str, size_t len);
TYPEDEF_FNCT_PTR (bool, c_check_utf8) (const char *str, size_t len);

#ifdef U_CHECK_UTF8_BUILD_TEST_FNCT
	bool Check_utf8_test_function (void);
#else
	#define Check_utf8_test_function() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_CHECK_UTF8_H.
/****************************************************************************************

	File:		strcustomfmt.h
	Why:		Functions for user-defined format specifiers.
	OS:			C99
	Author:		Thomas
	Created:	2024-12-26

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-12-26	Thomas			Created.

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

#ifndef STRCUSTOMFMT_H
#define STRCUSTOMFMT_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdarg.h>
	#include <stdbool.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

EXTERN_C_BEGIN

typedef struct sstrcustfmt SSTRCUSTFMT;

/*
	Functions provided by the caller/user.

	The module first calls custfmtGetRqSize () to obtain the required buffer size for the
	associated argument pCustFmtArg of the custom format specifier. This size is assumed to
	be without space for a terminating NUL character.
	
	The module then provides a buffer big enough for this size plus an additional NUL-
	terminator before it calls custfmtStoreData ().

	custfmtGetRqSize		User function that returns the required output buffer size for
							pCustFmtArg. The return value of this function is without a
							terminating NUL character.

	custfmtStoreData		User function that stores the output of pCustFmtArg in szBuf.
							The parameter len contains the length of the buffer szBuf points
							to. This is equal to or greater than the value returned by
							custfmtGetRqSize ().
							Although there is an additional octet/byte after this buffer
							reserved for a NUL terminator, the parameter len does not include
							it. In other words, the user can still write a NUL terminator at
							the end. Like custfmtGetRqSize (), the function must return the amount
							of characters written to szBuf, also without counting a terminating
							NUL character.
*/
typedef size_t (*custfmtGetRqSize)	(void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT);
typedef size_t (*custfmtStoreData)	(char *szBuf, size_t len, void *pCustFmtArg, SSTRCUSTFMT *pSSTRCUSTFMT);

/*
	The structure for a custom format specifier.
	
	The member pCustom is ignored by this module and therefore entirely available to the caller/
	user for passing on information from getRqSize () to storeData ().
*/
typedef struct sstrcustfmt
{
	const char			*ccFormatSpecifier;					// A custom format specifier. Cannot
															//	be NULL and cannot point to empty
															//	string.
	size_t				lenFormatSpecifier;					// Its length. This cannot be
															//	0 and also not (size_t) -1.
	custfmtGetRqSize	getRqSize;							// Returns the required buffer size.
	custfmtStoreData	storeData;							// Actual output function.

	void				*pCustom;							// Arbitrary pointer. Can be set by
															//	getRqSize () and read by
															//	storeData ().
} SSTRCUSTFMT;

/*
	The base (or plinth) of an array of SSTRCUSTFMT structures. This is what the functions in
	this module expect. See function TestStrCustomFmt () on how to construct this array with its
	plinth/base.
*/
typedef struct sstrcustfmtbase
{
	SSTRCUSTFMT			*psstrcustfmt;						// Pointer to an array of SSTRCUSTFMT
															//	structures.
	size_t				n;									// Number of elements in the array.
} SSTRCUSTFMTBASE;

/*
	strcustomfmtGetRqSizeCust

	Returns the required size for custom format specifiers.

	pb				A pointer to a fully initialised SSTRCUSTFMTBASE structure. The caller
					is responsible for initialising this structure. Cannot be NULL.

	lenCust			The length, in octets/bytes, of the buffer cust points to. Can be
					USE_STRLEN, in which case the function calls strlen () on the string
					to obtain its length.

	cust			The string that may contain custom format specifiers.

	The function returns the required length, excluding NUL terminator, the function
	strcustomfmtStoreDataCust () requires to store its output in strBuf.
	Before calling strcustomfmtStoreDataCust (), make sure the buffer for the parameter strBuf
	is at least strcustomfmtGetRqSizeCust () + 1 octets.
*/
size_t strcustomfmtGetRqSizeCust (SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, ...)
;

/*
	strcustomfmtStoreDataCust

	Stores the actual data expanded by custom format specifiers.

	strBuf			A pointer to the buffer that receives the output. Cannot be NULL. The
					size of this buffer is expected to be strcustomfmtGetRqSizeCust () + 1
					to accommodate for an additional NUL terminator.

	sizBuf			The size, in octets, of the buffer strBuf points to. The buffer must
					be big enough to hold the data to store including room for a NUL
					terminator, if required. Use strcustomfmtGetRqSizeCust ()
					to obtain this size and provide a buffer for strBuf of
					strcustomfmtGetRqSizeCust () + 1.
					This parameter cannot be 0.

	pb				A pointer to a fully initialised SSTRCUSTFMTBASE structure. The caller
					is responsible for initialising this structure. Cannot be NULL.

	lenCust			The length, in octets/bytes, of the buffer cust points to. Can be
					USE_STRLEN, in which case the function calls strlen () on the string
					to obtain its length.

	cust			The string that may contain custom format specifiers.
*/
size_t strcustomfmtStoreDataCust (char *strBuf, size_t sizBuf, SSTRCUSTFMTBASE *pb, size_t lenCust, const char *cust, ...)
;

#ifdef DEBUG
	//#define STRCUSTOMFMT_BUILD_TEST_FNCTS
#endif

/*
	TestStrCustomFmt

	Test function.
*/
#ifdef STRCUSTOMFMT_BUILD_TEST_FNCTS
	bool TestStrCustomFmt (void);
#else
	#define TestStrCustomFmt()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRCUSTOMFMT_H.
/****************************************************************************************

	File:		strfilesys.h
	Why:		File system string functions.
	OS:			C99.
	Author:		Thomas
	Created:	2023-05-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-27	Thomas			Created.

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

#ifndef STRFILESYS_H
#define STRFILESYS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

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

EXTERN_C_BEGIN

/*
	is_directory_separator

	Macro to check if c is a directory separator.
*/
#ifndef is_directory_separator
#define is_directory_separator(c)						\
			(UBF_WIN_DIR_SEP == c || UBF_PSX_DIR_SEP == c)
#endif
#ifndef is_path_separator
#define is_path_separator(c)	is_directory_separator (c)
#endif

/*
	str_find_path_navigator
	
	Returns a pointer to the first path navigator found in szString, or NULL if
	szString does not contain any path navigators. A path navigator is "../" on
	POSIX platforms and "..\" on Windows. The function treats both as equally
	valid on either platform and returns a pointer to the first one found.

	Note that this function does NOT support USE_STRLEN, which is (size_t) -1
	for the parameter lnString. The length MUST be specified appropriately.
*/
char *str_find_path_navigator (char *szString, size_t lnString)
;

/*
	str_remove_path_navigators
	remove_path_navigators_str
	
	Removes relative path navigators from chPath. The macro remove_path_navigators_str()
	is a redefinition of the function str_remove_path_navigators (). Relative path
	navigators consist of two periods followed by a slash, which is a forward slash on
	Unix/Linux platforms and a backward slash on Windows. The function recognises both
	types of path navigators.

	Relative path navigator
	"../"					Unix/Linux/Android/iOS/...
	"..\", escaped "..\\"	Windows

	Parameters

	chPath			A pointer to a string that contains the path with
					relative path navigators. This parameter cannot be NULL.

	pLen			A pointer to a size_t that contains the length of the string in
					chPath, not counting a NUL terminator. If this parameter is NULL,
					the function calls strlen (chPath) to obtain the length of the string
					chPath points to. If this parameter points to a size_t variable with a
					value of USE_STRLEN, which is (size_t) -1, the function calls
					strlen (chPath) too. If this parameter points to a size_t variable that
					contains a length other than USE_STRLEN, the parameter chPath does not
					need to be NUL-terminated.
					On return, the function updates the value with the new length of the path
					after relative path navigators have been removed, provided that pLen is
					not NULL.
					
	Examples - chPath as input on the left, chPath changed as output on the right:
	"../../test1/test2/test3/../../file.ext"	->	"../../test1/file.ext"
	"../../../1/2/3/4/5/6/7/../f.ext"			->	"../../../1/2/3/4/5/6/f.ext"
	"C:this is a test/test1/test2/../file.ext"	->	"C:this is a test/test1/file.ext"
	"/1/2/3/4/../../../../f.e"					->	"/f.e"
	"1/../f"									->	"f"
	"../f"										->	"../f"
	"1/2/../../f"								->	"f"
	"1/2/../../../f"							->	"../f"

	The function returns the amount of relative path navigators that were removed by the
	function. If pLen is not NULL, the function returns the new length in this size_t value
	after all relative path navigators have been removed.

	If path navigators have been removed, the function adds a NUL terminator to chPath since
	the string always shrinks in this case and at least several byte of additional space are
	made available. If no replacement occurs, the function does not change the buffer chPath
	points to.
*/
size_t str_remove_path_navigators (char *chPath, size_t *pLen);
#define remove_path_navigators_str(chPath,pLen)	str_remove_path_navigators (chPath, pLen)

/*
	ubf_correct_directory_separators_str
	
	The function replaces all directory separators with the correct directory separator
	of the host system before it removes all duplicate separators apart from the first
	two forward/backward slashes in a UNC path ("//server/share" or "\\server\share").
	
	chPath			Pointer to the path in which directory separators should be
					corrected.
	plenPath		Pointer to a value that specifies the length of the path chPath
					points to, excluding a terminating NUL character. If this parameter
					is NULL or points to a value of (size_t) -1, which is USE_STRLEN, the
					function uses strlen (chPath) to obtain its length.
	pReps			Pointer to a size_t that receives the amount of
					replacements the function has performed. This parameter can be NULL
					if this information is not needed.
	
	The function returns true on success, false when it fails. The amount of adjustments
	made is returned at the address pReps points to, i.e the amount of path
	separators replaced or removed, provided pReps is not NULL. If stPath is not NULL,
	the function returns the new length, excluding a terminating NUL, at the address it
	points to. The function returns false when chPath is NULL, in which case debug
	versions abort. The function also returns false when *pstPath is 0. Debug versions
	abort in this case too.
*/
bool ubf_correct_directory_separators_str	(
			char			*chPath,
			size_t			*cunilog_restrict plenPath,
			size_t			*cunilog_restrict pReps
											)
;

/*
	ubf_change_directory_separators
	
	Changes all directory separators ('/' and '\\') to newSeparator. Note that newSeparator
	can be any character that fits in a char.
*/
void ubf_change_directory_separators (char *szPath, size_t len, const char newSeparator);

/*
	ubf_len_with_last_directory_separator
	
	Returns the length of szPath that includes the last directory separator,
	or 0 if sz does not contain any directory separators.
	
	"/home/file"	-> 6, which would be the same as strlen ("/home/");
	"/"				-> 1, which would be the same as strlen ("/");
	"home"			-> 0, which would be the same as strlen ("");
	"C:\\dir"		-> 3, which would be the same as strlen ("C:\\");
	
	In Windows, although "C:file.ext" is actually the current path of the current
	process on the C: drive, the function accepts this as an absolute path for a file,
	but only if the first character of szPath is a letter and the second character is
	a colon, and no other directory separator can be found:
	"C:file.ext"	-> 2, which would be the same as strlen ("C:");
	
	If szPath is NULL, the function returns 0.
*/
size_t ubf_len_with_last_directory_separator (const char *szPath, size_t len);

/*
	str_correct_dir_separators
	
	Corrects the directory separators in str.
	
	The function returns the amount of directory separators replaced.
*/
size_t str_correct_dir_separators (char *str, size_t len)
;

/*
	str_remove_last_dir_separator

	Returns the length of str, if str does not end with a path (directory) separator. It
	returns len - 1, if str ends with a path separator. The function accepts USE_STRLEN
	for parameter len, in which case it calls strlen (str) to obtain its length.
	If str is NULL, the function returns 0.

	The function does not expect (or remove) more than one path separator at the end of str.
*/
size_t str_remove_last_dir_separator (const char *str, size_t len)
;

/*
	ubf_test_ubf_strfilesys
	
	Tests this module.
*/
#ifdef BUILD_DEBUG_UBF_STRFILESYS_TESTS
	bool ubf_test_ubf_strfilesys (void);
#else
	#define ubf_test_ubf_strfilesys() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRFILESYS_H.
/****************************************************************************************

	File:		strhex.h
	Why:		Functions for hexadecimal digits.
	OS:			C99
	Author:		Thomas
	Created:	2020-03-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-03-07	Thomas			Created. Functions have been moved from ubfsecure.c/h into
							 this module and renamed (without the "secure" part in them).

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

#ifndef U_STR_HEX_H
#define U_STR_HEX_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

// Minimum string length and size to hold an 8 bit hexadecimal number in ASCII.
#ifndef UBF_HEX8_STRLEN
#define UBF_HEX8_STRLEN				(2)
#endif
#ifndef UBF_HEX8_STRSIZ
#define UBF_HEX8_STRSIZ				(UBF_HEX8_STRLEN + 1)
#endif
// Minimum string length and size to hold a 16 bit hexadecimal number in ASCII.
#ifndef UBF_HEX16_STRLEN
#define UBF_HEX16_STRLEN			(4)
#endif
#ifndef UBF_HEX16_STRSIZ
#define UBF_HEX16_STRSIZ			(UBF_HEX16_STRLEN + 1)
#endif
// Minimum string length and size to hold a 32 bit hexadecimal number in ASCII.
#ifndef UBF_HEX32_STRLEN
#define UBF_HEX32_STRLEN			(8)
#endif
#ifndef UBF_HEX32_STRSIZ
#define UBF_HEX32_STRSIZ			(UBF_HEX32_STRLEN + 1)
#endif
// Minimum string length and size to hold a 64 bit hexadecimal number in ASCII.
#ifndef UBF_HEX64_STRLEN
#define UBF_HEX64_STRLEN			(16)
#endif
#ifndef UBF_HEX64_STRSIZ
#define UBF_HEX64_STRSIZ			(UBF_HEX64_STRLEN + 1)
#endif

// We can as well have SIZE_T_MAX because it seems more natural/reasonable.
#ifndef SIZE_T_MAX
#define SIZE_T_MAX	SIZE_MAX
#endif

// Error codes.
#define UBF_INVALID_HEX_CHAR		((unsigned char) -1)
#define UBF_INVALID_OCT_CHAR		((unsigned char) -1)
#define UBF_INVALID_BIN_CHAR		((unsigned char) -1)

// The maximum amount of hexadecimal ASCII digits for
#define UINT16_ASCII_HEX_DIGITS			 (4)
#define UINT32_ASCII_HEX_DIGITS			 (8)
#define UINT64_ASCII_HEX_DIGITS			(16)

/*
	ubf_is_octal_digit

	Returns or evaluates to TRUE if c contains an ASCII digit between 0 and 7, FALSE
	otherwise.
*/
#define ubf_is_octal_digit_macro(c)						\
		((unsigned char) (c) >= '0' && (unsigned char) (c) <= '7')
#ifdef DEBUG
	bool ubf_is_octal_digit (char c);
#else
    #define ubf_is_octal_digit(c)	ubf_is_octal_digit_macro (c)
#endif

/*
	ubf_is_hex_digit

	Returns or evaluates to true if c contains an ASCII hexadecimal digit, false
	otherwise. Hexadecimal digits are the decimal digits 0 to 9, plus the the letters
	A to F.
*/
#define ubf_is_hex_digit_macro(c)						\
(														\
		((unsigned char) (c) >= '0' && (unsigned char) (c) <= '9')\
	||	((unsigned char) (c) >= 'A' && (unsigned char) (c) <= 'F')\
	||	((unsigned char) (c) >= 'a' && (unsigned char) (c) <= 'f')\
)
#ifdef DEBUG
	bool ubf_is_hex_digit (char c);
#else
	#define ubf_is_hex_digit(c)		ubf_is_hex_digit_macro (c)
#endif

/*
	ubf_value_of_ASCII_hex
	
	Returns the value of the hexadecimal character in c. The function returns
	UBF_INVALID_HEX_CHAR, which is defined as (unsigned char) -1 if c does not
	contain a valid hexadecimal character.
	
	Valid hexadecimal characters are the digits "0" to "9", and the letters
	"A" to "F" or "a" to "f".
	"0" returns 0.
	"1" returns 1.
	...
	"9" returns 9.
	"A" returns 10.
	...
	"F" returns 15.
	"a" returns 10.
	...
	"f" returns 15.
	Anything else returns UBF_INVALID_HEX_CHAR, which is defined as (unsigned char) -1.
*/
#define ubf_value_of_ASCII_hex_macro(c)					\
	(													\
		(unsigned char) (c) >= '0' && (unsigned char) (c) <= '9' ? (unsigned char) (c) - '0' :\
		(unsigned char) (c) >= 'a' && (unsigned char) (c) <= 'f' ? (unsigned char) (c) - 'a' + 10 :\
		(unsigned char) (c) >= 'A' && (unsigned char) (c) <= 'F' ? (unsigned char) (c) - 'A' + 10 :\
		UBF_INVALID_HEX_CHAR							\
	)
#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_hex (const char c);
#else
	#define ubf_value_of_ASCII_hex(c)	ubf_value_of_ASCII_hex_macro (c)
#endif

/*
	ubf_value_of_ASCII_oct
	
	Returns the value of the octal character in c. The function returns
	UBF_INVALID_OCT_CHAR, which is defined as (unsigned char) -1 if c does
	not contain a valid octal character ('0', '1', '2', '3', '4', '5', '6',
	or '7').
*/
#define ubf_value_of_ASCII_oct_macro(c)					\
	(													\
			(unsigned char) (c) >= '0'					\
		&&	(unsigned char) (c) <= '7'					\
		?	(unsigned char) (c) - '0'					\
		:	UBF_INVALID_OCT_CHAR						\
	)
#ifdef DEBUG
	unsigned char ubf_value_of_ASCII_oct (const char c);
#else
	#define ubf_value_of_ASCII_oct(c)	ubf_value_of_ASCII_oct_macro (c)
#endif

/*
	ubf_octet_from_hex
	
	Reads up to two hexadecimal characters from chHx and writes the resulting
	binary octet to the location o points to.
	
	The function expects that it can read up to two characters from chHx.
	It does not perform a NUL check.
		
	The function returns the amount of hexadecimal characters that were
	read and used from the location chHx points to to produce the octet
	stored at o, which can be either 0 (if the first character is not a hex
	character), 1 (if only the first character is a hexadecimal character),
	or 2 (if both characters are hexadecimal).
*/
size_t ubf_octet_from_hex (unsigned char *o, const char *chHx);

/*
	ubf_octet_from_oct
	
	Reads up to three octal characters from chOc and writes the resulting
	binary octet (byte) to the location o points to.
	
	Valid octal bytes start at 000 (0d) up to 377 (255d, FFh). The function
	does not consume anything above octet boundary. For instance, an input
	of "477" would consume the first two characters ("47") only because the
	octal number 477 requires more than a single octet to be stored.
	
	The function returns the amount of octal characters consumed to produce
	the value that is written to the location o points to.
*/
size_t ubf_octet_from_oct (unsigned char *o, const char *chOc);

/*
	ubf_octet_from_bin
	
	Reads up to 8 binary characters from chOb and writes the resulting
	binary octet (byte) to the location o points to.
	
	Valid binary characters are '0' and '1'. The function does not consume
	anything above byte boundary.
	
	The function returns the amount of binary digits consumed to produce
	the value that is written to the location o points to.
*/
size_t ubf_octet_from_bin (unsigned char *o, const char *chOb);

/*
	ubf_uint16_from_hex

	Returns a 16 bit unsigned integer read from its hexadecimal ASCII
	representation chHx16 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx16
	and used to create the 16 bit unsigned value stored at the location pui16
	points to. If chHx16 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui16 points
	to.
	
	The pointer to the target value pui16 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.
	
	The function consumes a maximum of 4 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint16_from_hex (uint16_t *pui16, const char *chHx16)
;

/*
	ubf_uint32_from_hex
	
	Returns a 32 bit unsigned integer read from its hexadecimal ASCII
	representation chHx32 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx32
	and used to create the 32 bit unsigned value stored at the location pui32
	points to. If chHx32 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui32 points
	to.
	
	The pointer to the target value pui32 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.

	The function consumes a maximum of 8 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint32_from_hex (uint32_t *pui32, const char *chHx32)
;

/*
	ubf_uint64_from_hex
	
	Returns a 64 bit unsigned integer read from its hexadecimal ASCII
	representation chHx64 points to. Upper as well as lower-case hexadecimal ASCII
	characters are accepted by the function.

	The function returns the amount of hexadeciaml ASCII digits consumed from chHx64
	and used to create the 64 bit unsigned value stored at the location pui64
	points to. If chHx64 does not start with at least one hexadecimal ASCII digit,
	the function returns 0 and does not write anything to the location pui64 points
	to.
	
	The pointer to the target value pui64 can be NULL, in which case the function does
	not store the result of the conversion but returns the amount of hexadecimal ASCII
	digits that would have been consumed.

	The function consumes a maximum of 16 hexadecimal ASCII digits, which is the maximum
	value the function returns.
*/
size_t ubf_uint64_from_hex (uint64_t *pui64, const char *chHx64)
;

/*
	uint64_from_hex_str

	Returns the value of the hexadecimal string hexstr points to as a uint64_t. The
	function does not check for an overrun. Processing stops at the first character in
	hexstr that is not a hexadecimal character. Both, upper and lower-case characters
	are accepted.

	Examples:						Return value
	"12345"							-> 12345
	"A"								-> 10
	"228"							-> 552
	"ax"							-> 10
	"g"								-> 0
	""								-> 0
*/
uint64_t uint64_from_hex_str (const char *hexstr);

/*
	uint64_from_dec_or_hex_str

	Returns the value of the decimal or hexadecimal string decorhex points to as a
	uint64_t. Processing stops at the first character in decorhex that is not a digit
	or a hexadecimal character. A hexadeximal number is expected to start with "0x"
	or "0X", otherwise the number is assumed to be a decimal number and treated
	accordingly, for instance "0A" would return 0.

	Examples:						Return value
	"0A"							-> 0
	"0xA"							-> 10
	"55"							-> 55
*/
uint64_t uint64_from_dec_or_hex_str (const char *decorhex);

/*
	ubf_hex2bin
	
	This is our own version of Libsodium's sodium_hex2bin () function.
	
	The function expects a hexadecimal ASCII string in hex_input with hex_len octets/
	characters and writes the binary version of it to bin_output. The parameter
	bin_maxlen specifies the size of the buffer bin_output points to.
	
	Note that each octet written to bin_output requires two hexadecimal ASCII digits
	read from hex_input. This means that
	a) hex_len must be an even number, and
	b) bin_maxlen must be at least hex_len/2 if the input is supposed to be fully
	converted.
	
	The function stops converting when it encounters a character in hex_input that
	is not a valid hexadecimal ASCII digit ("0" to "9", "A" to "F", or "a" to "f").

	The function returns the amount of octets written to bin_output at the address
	pbin_len points to, provided it is not NULL.
	
	Note that if the binary output is interpreted as a multi-octet number this
	number will be in big-endian notation, since this function converts octet by
	octet in the order of the hexadecimal input.

	Returns TRUE on success, FALSE if it fails. The function returns FALSE if
	hex_len is not an even number, as this would not allow for a conversion. If
	pbin_len is not NULL, the function writes the amount of bytes written to
	bin_output to this address. It does this independent of the function's return
	value of TRUE or FALSE.
*/
bool ubf_hex2bin	(
			unsigned char		*bin_output,					// The output.
			const size_t		bin_maxlen,						// Length of the output buffer,
																//	in octets (bytes).
			const char			*hex_input,						// The input in hexadecimal
																//	ASCII representation.
			const size_t		hex_len,						// Length of the input buffer,
																//	in octets (bytes).
			size_t *const		pbin_len						// The amount of bytes written.
                   )
;

/*
	asc_hex_from_octet
	asc_hex_from_octet_lower

	Writes the two characters representing the hexadecimal notation of the byte/octet
	(8 bit data word) ui to the location pc points to. The function writes exactly two
	ASCII characters to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_octet (char *pc, uint8_t ui)
;
void asc_hex_from_octet_lower (char *pc, uint8_t ui)
;

/*
	URI_encode_hex_from_octet

	Writes a percent character ("%") plus two characters representing the hexadecimal notation
	of the byte/octet (8 bit data word) ui to the location pc points to. The function writes
	exactly three ASCII characters to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void URI_encode_hex_from_octet (char *pc, uint8_t ui)
;
void URI_encode_hex_from_octet_lower (char *pc, uint8_t ui)
;

/*
	asc_hex_from_word

	Writes the four characters representing the hexadecimal notation of the 16 bit data word
	ui to the location pc points to. The function writes exactly four ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_word (char *pc, uint16_t ui)
;
void asc_hex_from_word_lower (char *pc, uint16_t ui)
;

/*
	asc_hex_from_dword

	Writes the 8 characters representing the hexadecimal notation of the 32 bit data
	ui to the location pc points to. The function writes exactly 8 ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_dword (char *pc, uint32_t ui)
;
void asc_hex_from_dword_lower (char *pc, uint32_t ui)
;

/*
	asc_hex_from_qword

	Writes the 16 characters representing the hexadecimal notation of the 64 bit data
	ui to the location pc points to. The function writes exactly 16 ASCII characters
	to pc. No NUL terminator is written.

	The _lower version writes lower-case hexadecimal characters.
*/
void asc_hex_from_qword (char *pc, uint64_t ui)
;
void asc_hex_from_qword_lower (char *pc, uint64_t ui)
;

/*
	asc_bin_from_octet

	Writes the 8 characters representing the binary notation of the byte/octet
	(8 bit data word) ui to the location pc points to. The function writes exactly 8
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_octet (char *pc, uint8_t ui)
;

/*
	asc_bin_from_word

	Writes the 16 characters representing the binary notation of the 16 bit data
	word ui to the location pc points to. The function writes exactly 16
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_word (char *pc, uint16_t ui)
;

/*
	asc_bin_from_dword

	Writes the 32 characters representing the binary notation of the 32 bit data
	word ui to the location pc points to. The function writes exactly 32
	ASCII characters of '0' and '1' to pc. No NUL terminator is written.
*/
void asc_bin_from_dword (char *pc, uint32_t ui)
;

/*
	ubf_hex_from_octet

	Returns the hexadecimal ASCII notation of ui in chResult. It is expected that the
	buffer chResult points to is at least 3 characters (including the terminating NUL
	character) long.
	Byte 0 is for the ASCII character of the MSB nibble (tetrade). Values are from '0'
	to 'F'.
	Byte 1 is for the ASCII character of the LSB nibble (tetrade). Values are from '0'
	to 'F'.
	Byte 2 is overwritten with a NUL byte to terminate the result.
*/
void ubf_hex_from_octet (char *chResult, uint8_t ui);

/*
	ubf_hex_from_word
	ubf_hex_from_uint16

	Returns the hexadecimal notation of the 16 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 5 characters long, which
	includes the terminating NUL character. The constant UBF_HEX16_STRSIZ can be used
	to determine this length, which is 4 + 1 octets.
*/
void ubf_hex_from_word (char *chResult, uint16_t ui);
#define ubf_hex_from_uint16(r,u)			\
			ubf_hex_from_word (r, u)

/*
	ubf_hex_from_dword
	ubf_hex_from_uint32

	Returns the hexadecimal notation of the 32 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 9 characters long, which
	includes the terminating NUL character. The constant UBF_HEX32_STRSIZ is defined as
	9 and can be utilised for this purpose.
*/
void ubf_hex_from_dword (char *chResult, uint32_t ui);
#define ubf_hex_from_uint32(r,u)			\
			ubf_hex_from_dword (r, u)

/*
	ubf_hex_from_qword
	ubf_hex_from_uint64

	Returns the hexadecimal notation of the 64 bit unsigned integer ui in chResult. It
	is expected that the buffer chResult points to is at least 17 characters long, which
	includes the terminating NUL character. The constant UBF_HEX64_STRSIZ is defined as
	being this length, including the NUL character.
*/
void ubf_hex_from_qword (char *chResult, uint64_t ui);
#define ubf_hex_from_uint64(r,u)			\
			ubf_hex_from_qword (r, u)

/*
	asc_hex_zero_from_qword

	Returns the hexadecimal notation of the 64 bit unsigned integer ui in the buffer
	chResult points to. The parameter stWidthResult restricts or extends the width of the
	result, beginning from the right side, excluding a terminating NUL character.

	The function is identical to asc_hex_zero_from_qword () except that it does not write
	a terminating NUL character.
*/
void asc_hex_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui)
;

/*
	ubf_hex_str_zero_from_qword
	
	Returns the hexadecimal notation of the 64 bit unsigned integer ui in the buffer
	chResult points to. The parameter stWidthResult restricts or extends the width of the
	result, beginning from the right side, excluding a terminating NUL character. To use
	chResult as a standard C string it must hold space for at least stWidthResult
	characters plus an additional NUL character, hence the buffer chResult points to must
	always provide space for at least stWidthResult + 1 octets (bytes).
	
	Examples:
	
	ui		stWidthResult	chResult
	----------------------------------------
	65535	4				"FFFF"
	16		2				"10"
	16		1				"0"
	65535	5				"0FFFF"
	65535	10				"000000FFFF"
	65535	2				"FF"
	
	int main(void)
	{
		char		ch [1024];
		int			i;
		
		for (i = 0; i <= 30; i ++)
		{
			ubf_hex_str_zero_from_qword (ch, i, 5);
			printf ("i: %d, \"%s\", len = %zu\n", i, ch, strlen (ch));
		}
		return 0;
	}

	i: 0, "", len = 0
	i: 1, "5", len = 1
	i: 2, "05", len = 2
	i: 3, "005", len = 3
	i: 4, "0005", len = 4
	i: 5, "00005", len = 5
	i: 6, "000005", len = 6
	i: 7, "0000005", len = 7
	i: 8, "00000005", len = 8
	i: 9, "000000005", len = 9
	i: 10, "0000000005", len = 10
	i: 11, "00000000005", len = 11
	i: 12, "000000000005", len = 12
	i: 13, "0000000000005", len = 13
	i: 14, "00000000000005", len = 14
	i: 15, "000000000000005", len = 15
	i: 16, "0000000000000005", len = 16
	i: 17, "00000000000000005", len = 17
	i: 18, "000000000000000005", len = 18
	i: 19, "0000000000000000005", len = 19
	i: 20, "00000000000000000005", len = 20
	i: 21, "000000000000000000005", len = 21
	i: 22, "0000000000000000000005", len = 22
	i: 23, "00000000000000000000005", len = 23
	i: 24, "000000000000000000000005", len = 24
	i: 25, "0000000000000000000000005", len = 25
	i: 26, "00000000000000000000000005", len = 26
	i: 27, "000000000000000000000000005", len = 27
	i: 28, "0000000000000000000000000005", len = 28
	i: 29, "00000000000000000000000000005", len = 29
	i: 30, "000000000000000000000000000005", len = 30
	
*/
void ubf_hex_str_zero_from_qword (char *chResult, size_t stWidthResult, uint64_t ui);

/*
	ubf_hex_str_blank_from_qword
	
	The function is identical to ubf_hex_str_zero_from_qword () with the exception
	that leading zeros are replaced by blanks (spaces, SPC, ASCII 32d, 20h).
*/
void ubf_hex_str_blank_from_qword (char *chResult, size_t stWidthResult, uint64_t ui);

/*
	UCS2UTF16bin_from_hex
	
	The function expects a hexadecimal ASCII input string that contains UCS-2 or UTF-16
	characters, represented as hexadecimal ASCII. It writes out the 16 bit characters
	to u16result, up to max_u16result characters.
	
	If u16result is NULL, the function does not write output but returns the amount of
	uint16_t that would have been written at the address pU16written points to, unless
	pU16written is also NULL. Note that the value of max_u16result is still taken into
	consideration in this case. So, in order to obtain the size of the required array
	of u16result, set max_u16result to a value greater than the expected size or to
	SIZE_T_MAX.
	
	size_t		required_size;
	UCS2UTF16bin_from_hex (NULL, SIZE_T_MAX, "00410042", 8, &required_size);
	// Amount of uint16_t required is now in required_size.
	required_size *= sizeof (uint16_t);							// In bytes/octets.
	
	The function fails if len_cchex is not dividable by 4, as each UCS-2 or UTF-16 16 bit
	data written to u16result requires four hexadecimal ASCII characters in the input
	string cchex. The function also fails when len_cchex is 0.
	
	cchex				u16result
	"0031"				31
	"00310032"			31, 32
	
	Note that the function does not terminate the buffer u16result points to with a NUL
	character unless the hexadecimal ASCII input string cchex ends with a character
	string of "0000", which is a NUL terminator in UCS-2/UTF-16.
	
	The function returns TRUE on success, FALSE otherwise. Independent of the function's
	return value the amount of uint16_t (16 bit) values written to u16result is returned
	at the address pU16written points to.
*/
bool UCS2UTF16bin_from_hex	(
			uint16_t			*u16result,						// The output as 16 bit UCS-2 or
																//	UTF-16.
			size_t				max_u16result,					// The size of the buffer
																//	u16result points to, in
																//	uint16_t (NOT octets).
			const char			*cchex,							// The input string consisting
																//	of hexadecimal ASCII characters,
																//	4 hexadecimal ASCII characters
																//	for each uint16_t (UCS-2 or
																//	UTF-16) written to u16result.
			size_t				len_cchex,						// The length of the input string,
																//	excluding NUL.
			size_t				*pU16written
							)
;

/*
	ubf_hex_simple_hash
	
	This is a very simple hash function. It is meant as a (pretty simplistic)
	stand-in for Libsodium's ubf_crypto_generichash () in its absense.
	
	Do not use this function in security-critical applications.
	Use ubf_crypto_generichash () if the hash is important.
	
	The length of the hash stLenHash is currently fixed at 32 octets.
*/
void ubf_hex_simple_hash	(
				unsigned char	*pHash,		size_t	stLenHash,	// Hash and its length.
				const char		*pData,		size_t	stLenData	// Data and its length.
							)
;

/*
	ubf_hex_test_function
	
	Test function. Tests the functions in this module.
*/
#ifdef DEBUG
	#ifndef UBF_HEX_BUILD_TEST_FUNCTION
	#define UBF_HEX_BUILD_TEST_FUNCTION
	#endif
#else
#endif
#ifdef UBF_HEX_BUILD_TEST_FUNCTION
	bool ubf_hex_test_function (void);
#else
	#define ubf_hex_test_function()	(true)
#endif

EXTERN_C_END

#endif															// End of #ifndef U_STR_HEX_H.
/****************************************************************************************

	File:		strlineextract.h
	Why:		Line extractor.
	OS:			C99.
	Author:		Thomas
	Created:	2022-03-31

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-31	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The module provides a simple line extractor for various purposes.
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

#ifndef U_STRLINEEXTRACT_H
#define U_STRLINEEXTRACT_H

#include <stddef.h>
#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./membuf.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

enum enStrlineExtractCharSet
{
		EN_STRLINEEXTRACT_UTF8
	,	EN_STRLINEEXTRACT_UTF16								// Not supported yet.
};

/*
	Our default string parameters for single and multi-line comments, open
	and closing quotes, equality signs, and section start and end strings.
*/
extern const char	*ccCulStdLineCComment	[];
extern unsigned int	nCulStdLineCComment;

extern const char	*ccCulStdLineUComment	[];
extern unsigned int	nCulStdLineUComment;

extern const char	*ccCulStdBegMultComment	[];
extern const char	*ccCulStdEndMultComment	[];
extern unsigned int	nccCulStdMultComment;

extern const char	*ccCulStdOpenQuotes		[];
extern const char	*ccCulStdClosQuotes		[];
extern unsigned int	nCulStdQuotes;

extern const char	*ccCulStdEqualSigns		[];
extern unsigned int	nCulStdEquals;

extern char			*ccCulStdStrtSection	[];
extern char			*ccCulStdExitSection	[];
extern unsigned int	nCulStdSections;

/*
	
*/
typedef struct sculmltstrings
{
	const char		**ccLineComments;
	unsigned int	nLineComments;

	const char		**ccBegMultiComments;
	const char		**ccEndMultiComments;
	unsigned int	nMultiComments;

	const char		**ccOpenQuotes;
	const char		**ccClosQuotes;
	unsigned int	nQuotes;

	const char		**ccEquals;
	unsigned int	nEquals;

	char			**ccStrtSections;
	char			**ccExitSections;
	unsigned int	nSections;
} SCULMLTSTRINGS;

/*
	The members pchStartMultiCommentStr and pchEndMultiCommentStr point to string arrays that
	define the start and end of a block comment (multi-line comment). The member
	nMultiCommentStr holds the amount of array elements. Both arrays need to have the same
	amount of elements, and nMultiCommentStr must be precisely this value. Both arrays
	can be set to NULL if nMultiCommentStr is 0. No multi-line (block) comments are accepted
	in this case.
*/
typedef struct strlineconf
{
	enum enStrlineExtractCharSet	CharacterSet;			// Specifies the used character set.
															//	Currently, only
															//	EN_STRLINEEXTRACT_UTF8 is
															//	supported.
	size_t							tabSize;				// The width of a TAB character.
															//	Currently not used/supported.
	const char						**pchLineCommentStr;	// Pointer to an array of strings, in
															//	UTF-8, containing line comment
															//	characters. If this is NULL, no
															//	line comments are accepted.
	size_t							nLineCommentStr;		// Size of the array of strings
															//	pchLineCommentStr points to.
															//	Must be 0 if pchLineCommentStr
															//	is NULL. If this is 0, no line
															//	comments are accepted.
	// Start and end multi-line comments characters.
	const char						**pchStartMultiCommentStr;
	const char						**pchEndMultiCommentStr;
	size_t							nMultiCommentStr;
	#ifdef DEBUG
		bool						bInitialised;
	#endif
} STRLINECONF;

/*
	STRLINEINF

	The structure passed on to the callback function.
*/
typedef struct strlineinf
{
	const char			*szStart;							// Pointer to the first character
															//	of a line that is not a white
															//	space character.
	size_t				lnLength;							// Length of a line, not counting
															//	ending white space characters
															//	or new line control codes.
	size_t				lineNumber;							// The line number within the buffer.
															//	First line is 1.
	size_t				charNumber;							// The position of pStart within
															//	a line. 1 = first column/character.
	size_t				absPosition;						// Position within the entire buffer.
															//	1 = first position/character.
	void				*pCustom;							// Can be used by the caller.
	#ifdef DEBUG
		bool			bInitialised;
	#endif
} STRLINEINF;

/*
	User callback function.

	Should return true for every line processed. When this function returns false,
	the functions StrLineExtract () or StrLineExtractU8 () return too, and return the amount
	of times the callback function has been invoked.
*/
typedef bool (*StrLineExtractCallback) (STRLINEINF *psli);

/*
	InitSTRLINECONFforUBFL

	Initialises the STRLINECONF structure pc points to for UBFL language translation
	file single and multi-line (block) comments and a tab size of 4. Character set is UTF-8
	(EN_STRLINEEXTRACT_UTF8).
	
	In addition to C/C++ multi (block) and single line comments, UBFL language translation
	files also accept the following characters as the start of a line comment:
	"#", ";", "+", "-", "!".
	Their multi (block) and single line comment characters are therefore suitable for some
	scripting languages.
*/
void InitSTRLINECONFforUBFL (STRLINECONF *pc)
;

/*
	InitSTRLINECONFforC
	
	Initialises the STRLINECONF structure pc points to for C/C++ lines and multi-line
	comments and a tab size of 4. Character set is UTF-8 (EN_STRLINEEXTRACT_UTF8).
*/
void InitSTRLINECONFforC (STRLINECONF *pc);

/*
	InitSCULMLTSTRINGSforUBFL
	InitSCULMLTSTRINGSforC

	Initialisation functions for a SCULMLTSTRINGS structure, either for C or for UBFL
	language translation file single and block comments.
*/
void InitSCULMLTSTRINGSforUBFL (SCULMLTSTRINGS *psmls);
void InitSCULMLTSTRINGSforC (SCULMLTSTRINGS *psmls);

/*
	SanityCheckMultiComments

	Performs a simple sanity check on the string arrays that define the multi/block comments.
	This function is NOT a replacement for the caller to ensure the comments and their amounts
	are correct! It is the responsibility of the caller to ensure the members
	pchStartMultiCommentStr, pchEndMultiCommentStr, and nMultiCommentStr are initialised
	correctly.

	The function returns true if the sanity check is passed, false if not.
*/
bool SanityCheckMultiComments (STRLINECONF *pc);

/*
	StrLineExtractU8

	The actual UTF-8 line extractor, which is called by StrLineExtract () depending
	on the CharacterSet member of the STRLINECONF structure. Debug versions assert that
	this member is EN_STRLINEEXTRACT_UTF8.

	See descrption of StrLineExtract () for details.

	The function returns how many times the callback function has been invoked,
	which can be 0.
*/
unsigned int StrLineExtractU8	(
				const char				*pBuf,
				size_t					lenBuf,
				STRLINECONF				*pConf,
				StrLineExtractCallback	cb,
				void					*pCustom
								)
;

/*
	StrLineExtract

	The entry function for the line extractor. It calls the callback function for each
	extracted line. The STRLINECONF structure pConf points to controls how lines are
	extracted while line and block (multi-line) comments are ignored. Each extracted
	line is stripped of leading and trailing white space before it is passed on to the
	callback function cb points to. Lines only consisting of comments (single and multi)
	are stripped. Multi-line comments that start and end on a single line are stripped
	only when they appear before any significant character. They are not removed anywhere
	else, since the function does not know the syntax the caller deems valid.

	The callback function receives a pointer to a STRLINEINF structure that contains a
	pointer to the line buffer, its length, and a few other parameters, like for
	instance the line number.

	Call InitSTRLINECONFforC () to configure the STRLINECONF structure for C-style
	line and block comments, call InitSTRLINECONFforUBFL () to initialise the structure
	for UBFL language file line and multi-line comments, or use either function as an
	example to roll your own.

	pBuf			A pointer to the buffer that contains the data of which lines are
					to be extracted. This buffer does not have to be NUL-terminated
					unless lenBuf is set to USE_STRLEN.

	lenBuf			The length of the buffer, in characters. This can be USE_STRLEN,
					in which case the function obtains the length of pBuf by calling
					strlen () on it. For any other value, the buffer does not need to
					be NUL-terminated.

	pConf			A pointer to an initialised STRLINECONF structure. The caller fills
					this structure to control the function. If this parameter is NULL,
					the function uses its own STRLINECONF structure and calls
					InitSTRLINECONFforUBFL () for it before it is used.

	cb				A pointer to a StrLineExtractCallback () callback function. This
					function is called for each extracted line. The function is passed
					an STRLINEINF structure with some information. The callback function
					returns true for each line processed. When the function returns
					false, StrLineExtract returns too, returning the amount of times
					the callback function has been called so far.

	pCustom			An arbitrary pointer passed on to the callback function through
					the pCustom member of the STRLINEINF structure.

	When the function succeeds, it returns how many times the callback function has been
	invoked, which can be 0. If the function fails, the return value is UINT_MAX.
*/
unsigned int StrLineExtract	(
				const void				*pBuf,
				size_t					lenBuf,
				STRLINECONF				*pConf,
				StrLineExtractCallback	cb,
				void					*pCustom
							)
;

/*
	strlineextractRemoveLeadingWhiteSpace

	Returns a pointer inside szLine with leading white space removed. The parameter pLen
	points to contains the new length without the white space.
*/
const char *strlineextractRemoveLeadingWhiteSpace (size_t *pLen, const char *szLine, size_t lnLine)
;

/*
	strlineextractIsOpenString

	Returns the 1-based index of an opening string if szLine starts with it,
	or 0 if szLine doesn't start with an opening string.
	The returned 1-based index can be passed to the function
	strlineextractIsCloseString () as the parameter idxCloseString1based if it is greater
	than 0.
*/
unsigned int strlineextractIsOpenString	(
		const char		*szLine,			size_t			lnLine,
		unsigned int	nOpenStrings,		const char		**pszOpenStrings
										)
;

/*
	strlineextractIsCloseString

	Returns true if szLine starts with the closing string that has the 1-based index
	idxCloseString1based. The parameter idxCloseString1based is the return value of the
	function strlineextractIsOpenString (), but not 0. Do not call this function if
	strlineextractIsOpenString () returned 0.
*/
bool strlineextractIsCloseString	(
		const char		*szLine,			size_t			lnLine,
		const char		**pszCloseStrings,
		unsigned int	idxCloseString1based
								)
;

/*
	strlineextractIsEqual

	Wrapper for strlineextractIsOpenString (), because the function name looks
	odd when we check for an equality sign.
*/
#define strlineextractIsEqual(lne, len, nO, pS)			\
	strlineextractIsOpenString (lne, len, nO, pS)

/*
	strlineextractKeyOrValue

	Extracts a key or a value by taking quotations, if any, into consideration.
	The key or value is extracted without quotes. If no quotes are encountered,
	the key or value is extracted up to the last character before white space
	before an equality sign, or, if no equality sign is found, up to the last
	character before white space.
	
	If the key or value is quoted, the key or value inside the quotes is extracted.
	The function fails (returns false) if no closing quote is found.

	If a key or value doesn't start with an opening quote but contains quotes,
	these quotes are treated as normal characters.

	The extracted key is not NUL-terminated, since it is only a pointer to a buffer,
	and its length, inside the original buffer szLine points to.

	Leading and trailing white space, if any, is ignored.

	Parameters
	----------

	pszKeyOrVal		A pointer that receives the start address of the key or value, depending
					on whether an equality string is encountered. If an equality string is
					enountered towards the right side of the line, the returned pointer is
					a key, otherwise it's a value. This parameter cannot be NULL. This
					returned string is not NUL-terminated, because it is just a pointer
					within the buffer szLine.

	plnKeyOrVal		A pointer to a size_t that receives the length of the key or value
					returned in the parameter pszKeyOrVal. This parameter must not be NULL.

	pszEqual		If an equality string is encountered, this is a pointer to it. Otherwise
					it receives NULL. If a non-NULL address is returned, the paramter
					pszKeyOrVal points to a key. If it receives NULL, pszKeyOrVal points
					to a value.

	pidxEqual1based	A pointer to a size_t that receives the 1-based index of the equality
					string found. If pszKeyOrVal points to a key, the function sets this
					value to 0.

	szLine			A pointer to the buffer that contains the "key = value" string.

	lnLine			The length of szLine. If this parameter is USE_STRLEN, the function
					obtains it with strlen (szLine).


	The following parameters have been replaced with the SCULMLTSTRINGS structure psmlt:

	nQuotes			The amount of quote strings. See parameters szOpenQuotes and
					szClosQuotes below. If this value is 0, no quotes are recognised.

	pszOpenQuotes	A pointer to an array of NUL-terminated strings recognised as opening
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszClosQuotes	A pointer to an array of NUL-terminated strings recognised as closing
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszEquals		A pointer to an array of NUL-terminated strings recognised as equality
					characters/strings. The parameter nEquals specifies the number of
					stings/elements in this array. If this parameter is NULL, the function
					fails and returns false.

	nEquals			The number of strings that are recognised as equality signs pointed
					to by the parameter pszEquals. If this parameter is 0, the function is
					bound to fail and return false, as a key/value pair cannot be identified
					without at least one accepted equality sign character or string that
					separates key and value.

*/
bool strlineextractKeyOrValue	(
		const char		**cunilog_restrict pszKeyOrVal,	size_t	*plnKeyOrVal,	// Out.
		const char		**cunilog_restrict pszEqual,	size_t	*plnEqual,		// Out.
		unsigned int	*pidxEqual1based,										// Out.
		const char		*szLine,						size_t	lnLine,			// In.
		SCULMLTSTRINGS	*psmlt													// In.
								)
;

/*
	strlineextractKeyAndValue

	Extracts a key and value from szLine with length lnLine. If lnLine is USE_STRLEN,
	the function calls strlen (szLine) to obtain it.

	Parameters
	----------

	pszKey			A pointer that receives the start address of the key. This parameter
					cannot be NULL. This returned string is not NUL-terminated, because it
					is just a pointer within the buffer szLine.

	plnKey			A pointer to a size_t that receives the length of the key. This parameter
					must not be NULL.

	pszVal			A pointer that receives the start address of the value. This
					parameter cannot be NULL. The string is not NUL-terminated, as it is
					only a pointer within the buffer of szLine.

	lnVal			A pointer to a size_t that receives the length of the value string.
					This parameter cannot be NULL.

	szLine			A pointer to the buffer that contains the "key = value" string.

	lnLine			The length of szLine. If this parameter is USE_STRLEN, the function
					obtains it with strlen (szLine).

	The following parameters have been replaced with the SCULMLTSTRINGS structure psmlt:

	nQuotes			The amount of quote strings. See parameters szOpenQuotes and
					szClosQuotes below. If this value is 0, no quotes are recognised.

	pszOpenQuotes	A pointer to an array of NUL-terminated strings recognised as opening
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszClosQuotes	A pointer to an array of NUL-terminated strings recognised as closing
					quotation marks/strings. The parameter nQuotes specifies the number
					of elements in this array.

	pszEquals		A pointer to an array of NUL-terminated strings recognised as equality
					characters/strings. The parameter nEquals specifies the number of
					stings/elements in this array. If this parameter is NULL, the function
					fails and returns false.

	nEquals			The number of strings that are recognised as equality signs pointed
					to by the parameter pszEquals. If this parameter is 0, the function is
					bound to fail and return false, as a key/value pair cannot be identified
					without at least one accepted equality sign character or string that
					separates key and value.

	The function returns true if a key and a value could be extracted from the line,
	which includes an empty string for the value but not for the key. The function
	returns false if szLine is NULL or lnLine is 0.
*/
bool strlineextractKeyAndValue	(
		const char		**cunilog_restrict pszKey,	size_t	*plnKey,		// Out.
		const char		**cunilog_restrict pszVal,	size_t	*plnVal,		// Out.
		const char		*cunilog_restrict szLine,	size_t	lnLine,			// In.
		SCULMLTSTRINGS	*psmlt												// In.
								)
;

enum en_strlineextract_white_space
{
	strlineextract_accept_white_space_and_comments,
	strlineextract_accept_leading_and_trailing_white_space,
	strlineextract_accept_leading_white_space,
	strlineextract_accept_trailing_white_space,
	strlineextract_reject_white_space
};
typedef enum en_strlineextract_white_space en_strlineextract_ws;

/*
	strlineextractSection

	Extracts the name of a section from the line szLine with length lnLine.
	If lnLine is USE_STRLEN, the function calls strlen (szLine) to obtain it.

	Parameters
	----------

	pszSec			A pointer that receives the start address of the section name. This
					parameter cannot be NULL. This returned string is not NUL-terminated,
					because it is just a pointer within the buffer szLine.

	plnSec			A pointer to a size_t that receives the length of the section name.
					This parameter must not be NULL.

	szLine			A pointer to the buffer that contains the "[section]" string.

	lnLine			The length of szLine. If this parameter is USE_STRLEN, the function
					obtains it with strlen (szLine).

	psmlt			A pointer to an SCULMLTSTRINGS structure. The following members are
					expected and used by the function:

					nSections			The amount of opening/starting and closing/exiting
										section strings. This value cannot be 0, as it
										wouldn't make sense to call the function without
										any declarations for section starts and exits.

					ccStrtSections		An array of strings that specify accepted section
										starts. The amount of strings in this array is
										specified by the member nSections.

					ccExitSections		An array of strings that secify accepted section
										ends/exits. The amount of elements in this array is
										given by the member nSections.

					Additionally, if ws is strlineextract_accept_white_space_and_comments,
					the following members are expected and used by the function:

					ccLineComments		An array of strings that serve as the start of a line
										comment.

					nLineComments		The size of the ccLineComments array.

					ccBegMultiComments	An array of strings that contain the starts of
										block comments.

					ccEndMultiComments	An array of strings the contain the ends of block
										comments.

					nMultiComments		The amounts of opening/starting and closing/ending
										block comment strings.

	ws				One of the values of the enum en_strlineextract_white_space to
					determine if and what kind of white space is accepted/permitted or
					rejected. If white space is encountered that doesn't fit this value,
					the function fails and returns false.

	The function returns true if a section name could be extracted from the line. It
	returns false, if for example a closing/exiting section string is missing.
	The function also returns false if szLine is NULL or lnLine is 0.
*/
bool strlineextractSection	(
		const char				**cunilog_restrict pszSec,	size_t	*plnSec,
		const char				*cunilog_restrict szLine,	size_t	lnLine,
		SCULMLTSTRINGS			*psmlt,
		en_strlineextract_ws	ws
							)
;

/*
	test_strlineextract

	Function that tests the module. Returns true if all tests have been completed
	successfully, false otherwise.
*/
#ifdef STRLINEEXTRACT_BUILD_TEST_FNCT
	bool test_strlineextract (void);
#else
	#define test_strlineextract()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef U_STRLINEEXTRACT_H.
/****************************************************************************************

	File:		strnewline.h
	Why:		New line functions.
	OS:			C99
	Author:		Thomas
	Created:	2022-04-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-04-11	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This module supports the following build options:


	CUNILOG_NEWLINE_POSIX_ONLY
	
	Only POSIX line endings (LF) are supported. The enumeration values for other line endings
	are removed by the preprocessor.


	CUNILOG_NEWLINE_WINDOWS_ONLY

	Only Windows (CRLF) line endings are supported. The enumeration values for other line
	endings are removed by the preprocessor.


	CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY

	Only POSIX (LF) and Windows (CRLF) line endings are supported. The enumeration values
	for other line endings are removed by the preprocessor. Since June 2025, this is the
	default and does not need to be defined anymore.


	CUNILOG_NEWLINE_EXTENDED

	All line endings supported are recognised. Overrides all other line ending definitions.
	When CUNILOG_NEWLINE_EXTENDED is defined, three more definitions are implicitely defined
	as well to allow for conditional builds:
	CUNILOG_NEWLINE_POSIX, CUNILOG_NEWLINE_WINDOWS, and CUNILOG_NEWLINE_POSIX_AND_WINDOWS

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

// Used for testing the definitions.
//#define CUNILOG_NEWLINE_WINDOWS_ONLY

#ifndef STRNEWLINE_H
#define STRNEWLINE_H

// For quick checks.
//#define CUNILOG_NEWLINE_EXTENDED

/*
	Correct the definitions. This also sets priorities and overrides of the definitions.
*/
#if !defined (CUNILOG_NEWLINE_POSIX_ONLY) && !defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#endif
#endif
#if defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	#ifdef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#endif
	#ifdef CUNILOG_NEWLINE_WINDOWS_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX
	#define CUNILOG_NEWLINE_POSIX
	#endif
	#ifndef CUNILOG_NEWLINE_WINDOWS
	#define CUNILOG_NEWLINE_WINDOWS
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#endif
#endif
#if defined (CUNILOG_NEWLINE_POSIX_ONLY) && defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#endif
#endif
#ifdef CUNILOG_NEWLINE_EXTENDED
	#ifdef CUNILOG_NEWLINE_POSIX_ONLY
	#undef CUNILOG_NEWLINE_POSIX_ONLY
	#endif
	#ifdef CUNILOG_NEWLINE_WINDOWS_ONLY
	#undef CUNILOG_NEWLINE_WINDOWS_ONLY
	#endif
	#ifdef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#undef CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX
	#define CUNILOG_NEWLINE_POSIX
	#endif
	#ifndef CUNILOG_NEWLINE_WINDOWS
	#define CUNILOG_NEWLINE_WINDOWS
	#endif
	#ifndef CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#define CUNILOG_NEWLINE_POSIX_AND_WINDOWS
	#endif
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

/*
	The maximum length of a line ending in this module, and its size including NUL.
*/
#ifndef MAX_LEN_LINE_ENDING
#define MAX_LEN_LINE_ENDING				(3)
#endif
#ifndef MAX_SIZ_LINE_ENDING
#define MAX_SIZ_LINE_ENDING				(1 + MAX_LEN_LINE_ENDING)
#endif

EXTERN_C_BEGIN

/*
	newline_t

	Represents a new line.

	Recommended is unilogNewLineDefault.

	The value cunilogNewLineSystem uses the operating system/platform default, which is
	currently cunilogNewLineWindows (CRLF) in Windows and cunilogNewLinePOSIX (LF) for every
	other platform.

	The value cunilogNewLineDefault used to be cunilogNewLineSystem to ensure logfiles
	could be opened with Notepad on Windows systems, but since newer versions of Notepad
	(Windows 10 and newer) can perfectly display files that have POSIX line endings, the
	default is now cunilogNewLinePOSIX to save one octet per event line. Use
	cunilogNewLineWindows or cunilogNewLineSystem if textual logfiles need to be opened/
	viewed with Notepad for Windows versions before Windows 10, or if they are opened/
	viewed/processed later with any other application that can't cope with POSIX line
	endings.
*/
#if defined (CUNILOG_NEWLINE_POSIX_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX		= cunilogNewLineSystem	// LF only.
		,	cunilogNewLineDefault	= cunilogNewLinePOSIX
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLineWindows	= cunilogNewLineSystem	// CR + LF.
		,	cunilogNewLineDefault	= cunilogNewLineWindows
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#elif defined (CUNILOG_NEWLINE_POSIX_AND_WINDOWS_ONLY)
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		,	cunilogNewLineWindows							// CR + LF.
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#else
	enum enLineEndings
	{
			cunilogNewLineSystem							// Use operating system default.
		,	cunilogNewLinePOSIX								// LF only.
		,	cunilogNewLineDefault = cunilogNewLinePOSIX
		,	cunilogNewLineWindows							// CR + LF.
		,	cunilogNewLineApple								// CR only.
		,	cunilogNewLineRISCOS							// LF + CR.
		,	cunilogNewLineQNXbef4							// RS (1Eh)
		,	cunilogNewLineIBMzOS							// EBCDIC NL (15h)
		,	cunilogNewLineNEL								// Unicode newline NEL (U+0085)
		,	cunilogNewLineLS								// Unicode line separator LS (U+2028)
		,	cunilogNewLinePS								// Unicode paragraph separator PS
															//	(U+2029)
		// Do not add anything below this line.
		,	cunilogNewLineAmountEnumValues					// Used for table sizes.
		// Do not add anything below unilogNewLineAmountEnumValues.
	};
#endif
typedef enum enLineEndings	newline_t;

/*
	The array with the line endings and the array with their lengths.
*/
const char	*aszLineEndings	[];
size_t		lenLineEndings	[];

/*
	ccLineEnding

	Returns the line ending for nl. Note that szLineEnding () also returns
	its length.
*/
#ifdef DEBUG
	const char *ccLineEnding (newline_t nl);
#else
	#define ccLineEnding(nl)	aszLineEndings [nl]
#endif

/*
	lnLineEnding

	Returns the length of the line ending nl. The value does not include the NUL
	terminator.
*/
#ifdef DEBUG
	size_t lnLineEnding (newline_t nl);
#else
	#define lnLineEnding(nl)	lenLineEndings [nl]
#endif

/*
	szLineEnding

	Returns the line ending and its length. The length does not include the NUL
	terminator.
*/
const char *szLineEnding (newline_t nl, size_t *pln);

/*
	strIsNewLine

	Since 2024-11-29 this function is considered deprecated. Use strIsLineEndings () instead.
	Note that strIsLineEndings () returns a size_t instead of an unsigned int.

	Since 2025-06-25 this function is not built anymore by default. It is instead a wrapper
	macro for strIsLineEndings (). Define STRNEWLINE_FORCE_ORG_STRISNEWLINE to build and use
	this function instead of strIsLineEndings ().

	Checks if ch points to one or more newline markers. The function returns the amount of
	new lines found, 0 if ch does not point to a new line marker.

	See https://en.wikipedia.org/wiki/Newline .
	
	For our implementation, a new line is found when:
		<CR>		(0x0D)
		<CR><LF>	(0x0D)(0x0A)
		<LF>		(0x0A)
		This counts as two new lines (a single CR and a single LF):
		<LF><CR>	(0x0A)(0x0D)

	Parameters:
	ch					A pointer to the character string to be checked.
						Since stJump stores the amount of bytes that make up the
						newline marker, if the caller increments ch by stJump the
						new value of ch points to the first byte after the newline
						marker.
	stLen				Length of the character string in octets, not including
						a terminating NUL character.  If this parameter is (size_t) -1,
						the function obtains the length with a call to strlen (ch).
	stJump				A pointer to the amount of octets in the new line phrase
						returned by the function. The caller can for instance use
						this information to increment the pointer to the character
						string in order to jump over the new line marker. If
						stJump is NULL, this parameter is ignored.
						Possible return values:
						stJump = 0			The found byte is not part of a newline
											marker.
						stJump = 1			A single <CR> (carriage return) was found
											or a single <LF> was found.
						stJump = 2			A <CR><LF> pair was found.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.
*/
#ifdef STRNEWLINE_FORCE_ORG_STRISNEWLINE
	unsigned int strIsNewLine (char *ch, size_t stLen, size_t *stJump);
#else
	#define strIsNewLine(sz, ln, pj)					\
		(unsigned int) strIsLineEndings (sz, ln, pj)
#endif

/*
	strIsLineEndings

	Checks if ch points to one or more newline markers/line endings. The function returns
	the amount of consecutive line endings encountered, or 0 if ch does not point to at
	least one.

	The function is similar to strIsNewLine () but treats all possible line endings
	of the enum enLineEndings as line endings, and counts them accordingly.

	Parameters:
	ch					A pointer to the character string to be checked.
						Since stJump stores the amount of octets that make up the
						newline marker(s), if the caller increments ch by stJump the
						new value of ch points to the first byte after the encountered
						line endings.
	stLen				Length of the character string in octets, not including
						a terminating NUL character.  If this parameter is (size_t) -1,
						the function obtains the length with a call to strlen (ch).
	stJump				A pointer to the amount of octets of consecutive line endings
						returned by the function. The caller can for instance use
						this information to increment the pointer to the character
						string in order to jump over new line markers.
						If not required, this parameter can be NULL.

	The function returns the amount of new lines found, or 0 if ch does not point
	to at least one new line marker.

	Note that the current implementation of this function does not recognise RiscOS
	line endings (LF + CR) correctly, as it finds a POSIX line ending (LF only) first,
	and then an Apple line ending (CR only), and therefore identifies two consecutive
	line endings instead of a single RiscOS line ending. If/when an implementation of
	this function is required that identifies RiscOS line endings correctly, it will
	have to be updated/implemented first.
*/
size_t strIsLineEndings (const char *ch, size_t stLen, size_t *stJump)
;

/*
	strFirstLineEnding

	Finds and returns a pointer to the first line ending in the buffer ch points to,
	or returns NULL if no line ending could be found.

	The function reads up to len octets/bytes from ch. If len is USE_STRLEN, the function
	calls strlen (ch) to obtain it. The parameter ch can be NULL if len is 0.
*/
char *strFirstLineEnding (const char *ch, size_t len);

/*
	strFirstLineEnding_l

	The function is identical to strFirstLineEnding () but additionally returns the length
	of the line ending encountered. The parameter plLE can be NULL, in which case the
	length of the line ending is not returned. if no line ending is found, the size_t
	plLE points to is not touched.

	If len is USE_STRLEN, the function calls strlen (ch) to obtain it.
	The parameter ch can be NULL if len is 0.

	If no line ending is found, the function returns NULL.
*/
char *strFirstLineEnding_l (const char *ch, size_t len, size_t *plLE);

/*
	strPrevLineEnding_l

	The function is identical to strFirstLineEnding_l () but searches for the first line
	ending before ch + strtIdx, i.e. the previous line ending. The length of the found line
	ending is returned at the address plLE points to, unless plLE is NULL.

	If len is USE_STRLEN, the function calls strlen (ch) to obtain it.
	The parameter len or, if USE_STRLEN, the obtained length, must be greater or equal to
	strtIdx. The function searches backwards (towards the first character in ch) from
	ch + strtIdx down to ch for the line ending.

	The parameter ch can be NULL if len is 0.

	If no line ending is found, the function returns NULL. If strtIdx >= len, the function
	returns NULL. When the function returns NULL, the address plLE points to is set to 0.
*/
char *strPrevLineEnding_l (const char *ch, size_t len, size_t strtIdx, size_t *plLE);

/*
	strRemoveLineEndingsFromEnd

	Removes line endings from the right side of sz.
	
	The string parameter cannot be NULL but the function does not check this.

	The parameter len specifies the length of sz. The string does not have to be
	NUL-terminated.

	If len is USE_STRLEN, the function calls strlen () on sz. Note that sz must be
	NUL-terminated in this case.

	The function returns the new length of sz, which excludes the found line endings.
*/
size_t strRemoveLineEndingsFromEnd (const char *sz, size_t len);


#ifdef DEBUG
	#ifndef STRNEWLINE_BUILD_TEST
	#define STRNEWLINE_BUILD_TEST
	#endif
#endif

/*
	Test function.
*/
#ifdef STRNEWLINE_BUILD_TEST
	bool test_strnewline (void);
#else
	#define test_strnewline()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRNEWLINE_H.
/****************************************************************************************

	File:		strhexdumpstructs.h
	Why:		Structures for data dumps.
	OS:			C99
	Author:		Thomas
	Created:	2024-09-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-10	Thomas			Created. Based on ubfdumpstructs.h, which is now obsolete.

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

#ifndef STRHEXDUMPSTRUCTS_H
#define STRHEXDUMPSTRUCTS_H

#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strnewline.h"

#endif

// Errors.
#define STR_DATA_DUMP_ERR_NO_ERROR						0
#define STR_DATA_DUMP_ERR_NO_DATA						2		// Either chDumpData is NULL or the
																//	length is 0.
#define STR_DATA_DUMP_ERR_NUM_FORMAT					3		// Only one number system is
																//	possible.
#define STR_DATA_DUMP_ERR_OUT_OF_MEMORY					4		// Not enough space available on
																//	the heap.

// Option flags.
#define STR_DATA_DUMP_OPTS_NONE					0x00000000		// No option. Everything is
																//	default.
#define STR_DATA_DUMP_OPTS_BINARY				0x00000001		// Use binary format for data
																//	instead of hex.
#define STR_DATA_DUMP_OPTS_DECIMAL				0x00000002		// Use decimal format for data
																//	instead of hex.
/*
#define STR_DATA_DUMP_OPTS_NO_FIRST_OFF_SEP		0x00000004		// Suppresses the first separator
																//	(usually a colon) after the
																//	offset.
*/
/*
#define STR_DATA_DUMP_OPTS_NO_LAST_VAL_SEP		0x00000008		// Omit the last value separator.
*/
#define STR_DATA_DUMP_OPTS_OFFS_DECIMAL			0x00000010		// The offset is in decimal.
#define STR_DATA_DUMP_OPTS_NS_INDICATOR_L		0x00000020		// Add an indicator which number
																//	system is used
																//	in lower case.
																//	Uses "h" for hexadecimal,
																//	"b" for binary, and
																//	"d" for decimal.
#define STR_DATA_DUMP_OPTS_NS_INDICATOR_U		0x00000040		// Add an indicator which number
																//	system is used
																//	in upper case.
																//	Uses "H" for hexadecimal,
																//	"B" for binary, and
																//	"D" for decimal.
#define STR_DATA_DUMP_OPTS_HEX_DATA_LOWER		0x00000080		// Show hexadecimal data in
																//	lower case. Default is upper
																//	case.
#define STR_DATA_DUMP_OPTS_OFFS_USE_BLANKS		0x00000100		// Output blanks (" ") in the
																//	offset instead of zeros ("0").
#define STR_DATA_DUMP_OPTS_LINEST_FIRST_ONLY	0x00000200		// The member chLineStart is only
																//	used for the first output
																//	line. All other lines are
																//	filled up with stLineStart
																//	blanks (SCP, ASCII 20h, 32d).

#ifdef __cplusplus
	extern "C" {
#endif

/*
	SHEX_DUMP_PARS
	
	The parameter structure for data dumps.

	A data dump consists of the following characteristics:
	- An optional text provided by the caller that precedes each line of the dump.
		The example from Wikipedia below does not contain such a text.
	- The offset value. The offset values in the example below contain offsets of
		0000, 0010, 0020, and 0030 hexadecimal.
	- The first offset separator. In the example below this is a colon (":").
	- The second offset separator. In the example below this is a space (or blank),
		ASCII 20h, 30d.
	- The data values. The first line of data values in the example below starts with
		57, 69, 6B, 69, etc, in hexadecimal.
	- The data value separators. Each data value in the example below is separated by
		a blank (or space) character, which is ASCII 32d, or 20h. Data value separators
		follow the extracted data. The separator of the last data value may not be
		desired and can therefore be suppressed with the option flag
		STR_DATA_DUMP_OPTS_NO_LAST_VAL_SEP.
	- The display separator. In the example from Wikipedia below the display separator
		is a blank (or space) character (ASCII 20 hex, 32 decimal).
	- The plain display text. In the example below, the plain display text of the first
		dump line is "Wikipedia, the f".
	
	Example of a hex dump, taken from https://en.wikipedia.org/wiki/Hex_dump:

		      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+------ Number of values (uinValues)
		      !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !
		      V  V  V  V  V  V  V  V  V  V  V  V  V  V  V  V
		0000: 57 69 6B 69 70 65 64 69 61 2C 20 74 68 65 20 66  Wikipedia, the f
		0010: 72 65 65 20 65 6E 63 79 63 6C 6F 70 65 64 69 61  ree encyclopedia
		0020: 20 74 68 61 74 20 61 6E 79 6F 6E 65 20 63 61 6E   that anyone can
		0030: 20 65 64 69 74 00 00 00 00 00 00 00 00 00 00 00   edit...........
	^	^   ^ ^ ^                    ^                     ^ ^ ^
	!	!   ! ! !                    !                     ! ! !
	!	!   ! ! !                    !                     ! ! +-- Plain display text.
	!	!   ! ! !                    !                     ! ! 
	!	!   ! ! !                    !                     ! +---- Display separator.
	!	!   ! ! !                    !                     +------ Last data value.
	!	!   ! !                      +---------------------------- Half line separator (ccHalfLineSep).
	!	!   ! ! +------------------------------------------------- First data value separator.
	!	!   ! +--------------------------------------------------- First data value.
	!	!	!
	!	!   +----------------------------------------------------- Offset separator (member ccOffsetSep).
	!	+--------------------------------------------------------- Offset value.
	+------------------------------------------------------------- Line start (member ccLineStart).

	Members of the structure:
	
	le						The line ending/newline character(s) to use. See enum enLineEndings
							in strnewline.h for details. If unsure, use unilogNewLineDefault,
							which is a POSIX line ending of LF only. This works on POSIX platforms
							as well as on Windows 10 and up. Use unilogNewLineSystem or
							unilogNewLineWindows for Windows versions before Windows 10.

	ccHeader				A pointer to a string that serves as header text. A line ending is
							added automatically. If this member is NULL, the member lenHeader also
							needs to be 0, and this does not insert a header at all. To create a
							header that consists of a single line ending only, point ccHeader to
							an empty string ("") and set lenHeader to either 0 or USE_STRLEN.
	
	lenHeader				The length of the buffer ccHeader points to, in octets/bytes.
							If lenHeader is USE_STRLEN, which is (size_t) -1, ccHeader must be
							NUL-terminated and obviously can't contain NUL bytes.

	ccLineStart				An optional text provided that precedes each line of the dump.
							This member can be NULL, if not required/used. Since the member
							stLineStart provides the length of this string, in octets,
							excluding a terminating NUL character, the buffer ccLineStart
							points to does not have to be NUL terminated. If this member
							is NULL, the member lenLineStart also must be 0.
							
	lenLineStart			The length of the optional text that precedes each line of
							the dump. If this member is 0, a call to strlen (ccLineStart) is used
							to obtain its value, which means that ccLineStart must be NUL-
							terminated.
							
	stFirstOffset			An optional value that is added to each offset in the output.
							A value of 0 makes the offset start at 0. The offset in the
							output is placed after a line start (member chLineStart).

	uiError					An error code in case of failure. This member contains one of
							the STR_DATA_DUMP_ERR... constants when one of the functions
							fails. This is the only member that is returned by one of the
							dump functions. All other members are input members, meaning
							the functions read and use their values. A value of
							STR_DATA_DUMP_ERR_NO_ERROR is returned if no error occurred.
							
	uiOffsetWidth			The width of the offset. This value must not be 0.
	
	uiOffsetSep01			This member contains the character placed directly after the
							offset.
	
*/
typedef struct shex_dump_pars
{
	newline_t			le;										// How to represent line endings.

	const char			*ccHeader;								// Header.
	size_t				lenHeader;								// Length of ccHeader.

	const char			*ccLineStart;							// Pointer to a character string
																//	to be inserted at the start
																//	of each line.
	size_t				lenLineStart;							// The length of chLineStart, not
																//	including a terminating NUL
																//	character.

	size_t				stFirstOffset;							// This value is added to the
																//	returned offset. If this member
																//	is set to (size_t) -1, the
																//	pointer value of the data to
																//	dump is used.
	uint8_t				uiOffsetWidth;							// The amount of digits in the offset.

	const char			*ccOffsetSep;							// The separator between the offset
																//	and the values.
	size_t				lenOffsetSep;							// Its length.

	uint8_t				uinValues;								// The width of a data dump line.
																//	This is the amount of values
																//	(usually octets/bytes)
																//	displayed on a single line.

	uint8_t				uiValueSize;							// The width of a single value,
																//	in bytes (octets). Not (yet)
																//	supported. Ignored.

	const char			*ccValSeparator;						// The separator between values.
																//	Default is SPC (20h, 32d).
	size_t				lenValSeparator;						// Its length.

	const char			*ccHalfLineSep;							// The separator between half of
																//	the values.
	uint8_t				lenHalfLineSep;							// Its length.

	const char			*ccDisplaySep;							// The separator between the
																//	values block and the ASCII
																//	display.
	uint8_t				lenDispSep;								// Its length.

	const char			*ccUnprintable;							// Representation of an
																//	unprintable character.
	size_t				lenUnprintable;							//	Its length.

	const char			*ccNoMoreDataVal;						// Representation of a value
																//	when the data
																//	can't fill the last line
																//	(values).
	size_t				lenNoMoreDataVal;						// Its length.
	const char			*ccNoMoreDataDisp;						// Representation when the data
																//	can't fill the last line
																//	(ASCII display text).
	size_t				lenNoMoreDataDisp;						// Its length.

	unsigned int		uiOptions;								// Option flags. See above.
	unsigned int		uiError;								// A more detailed error code on
																//	failure. See above.
} SHEX_DUMP_PARS;

/*
	The structure that holds the values already calculated.

	The member bInitialised is used as an indicator that the function requires initialisation.
	To initialise the structure:

	SHEX_DUMP_SAN	s;
	s.bInitialised = false;

*/
typedef struct shex_dump_san
{
	bool				bInitialised;
	size_t				lenHeader;
	size_t				lenLineStart;
	size_t				lenOffset;
	size_t				lenOffsetSep;
	size_t				lenValSeparator;
	size_t				lenHalfLineSep;
	size_t				lenUnprintable;
	size_t				lenNoMoreDataVal;
	size_t				lenNoMoreDataDisp;
	size_t				lenDispSeparator;
	size_t				lenOneLine;
	size_t				lenValuesWidth;
	size_t				stNextOffset;
	const char			*ccNxtValToDump;
	size_t				lenValToDumpLeft;
} SHEX_DUMP_SAN;

#ifdef __cplusplus
	}
#endif

#endif															// Of #ifndef STRHEXDUMPSTRUCTS_H.
/****************************************************************************************

	File:		strhexdump.h
	Why:		Functions for data dumps.
	OS:			C99
	Author:		Thomas
	Created:	2024-09-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-10	Thomas			Created. Based on ubfdump.h, which is now obsolete.

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

#ifndef STRHEXDUMP_H
#define STRHEXDUMP_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./strhexdumpstructs.h"
		#include "./strmembuf.h"
	#else
		#include "./strhexdumpstructs.h"
		#include "./strmembuf.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	Advanced hex dump. As of Jan 2025 the advanced hex dump is considered incomplete/abandoned.
	Use the simple hex dump instead. See further down.
*/

/*
	A default SUBF_DUMP_PARS structure for general use.
*/
extern	SHEX_DUMP_PARS		sdp_default;

/*
	ubf_data_dump_def_SUBF_DUMP_PARS
	
	Copies all members of the default SUBF_DUMP_PARS structure into the
	SUBF_DUMP_PARS structure s points to.
*/
void ubf_data_dump_def_SUBF_DUMP_PARS (SHEX_DUMP_PARS *s);

/*
	UBF_DATA_DUMP_DEF_SUBF_DUMP_PARS
	
	Convenience wrapper macro for ubf_data_dump_def_SUBF_DUMP_PARS to dereference the
	pointer.
*/
#define UBF_DATA_DUMP_DEF_SUBF_DUMP_PARS(a)		\
			ubf_data_dump_def_SUBF_DUMP_PARS (&(a))

/*
	ubf_data_dump_SMEMBUF
	
	Creates a dump of the data pointed to by chDumpData with the length stDumpDataLen
	into the SMEMBUF structure pointed to by mbOutput. The type and parameters of the
	data dump is determined by the SUBF_DUMP_PARS structure pointed to by sDumpPars.
	
	mbOutput			The SMEMBUF structure that receives the output.

	chDumpData			A pointer to the start of the dump data.

	lenDumpData			The length of the dump data, in octets (bytes).

	sDumpPars			A pointer to a SHEX_DUMP_PARS structure, which determines several
						parameters of the output.

	pdSanDPars			A pointer to a writable SHEX_DUMP_SAN structure. This can
						be used for consecutive invocations to avoid recalculating some
						values. If this parameter is NULL, the function uses its own
						automatic version and recalculates its members every time it is
						called. Each SHEX_DUMP_PARS requires its own SHEX_DUMP_SAN
						structure to preserve its calculated parameters.
						Set the structures lenHeader header to 0 before calling the
						function the first time. This tells it to calculate its values.
						It can then be re-used in consecutive calls and no recalculations
						are required.

	The function returns the amount of octets/bytes written to the buffer of mbOutput,
	excluding the terminating NUL character.
*/
size_t ubf_data_dump_SMEMBUF	(
		SMEMBUF				*mbOutput,						// The target SUBF_STRING.
		const char			*ccDumpData,					// The data to dump.
		size_t				lenDumpData,					// The length of the data to dump.
		SHEX_DUMP_PARS		*psDumpPars,					// The SUBF_DUMP_PARS structure.
		SHEX_DUMP_SAN		*pdSanDPars						// Can be carried to the next invokation.
								)
;

#ifdef nix
/*
	ubf_data_dump_puts

	The function is identical to ubf_data_dump_SUBF_STRING () with the exception that it
	doesn't need the SUBF_STRING parameter ssTarget and directly prints the dump output
	to stdout.

	The function provides a SUBF_STRING structure and calls ubf_data_dump_SUBF_STRING (),
	then uses puts () to output the SUBF_STRING structure's buffer if the call to
	ubf_data_dump_SUBF_STRING () was successful. It outputs nothing when the call
	to ubf_data_dump_SUBF_STRING () failed.

	If the type (const char *) is an issue, use ubf_data_dump_puts_typeless () to cast
	the first parameter.

	The function returns TRUE on success, FALSE on failure. The return value is obtained
	from the call to ubf_data_dump ().
*/
bool ubf_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
						);

/*
	ubf_debug_data_dump_puts
	
	Debug-only version of ubf_data_dump_puts (). Only outputs the data dump in debug
	versions.
*/
#ifdef DEBUG
	bool ubf_debug_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
									);
#else
	#define ubf_debug_data_dump_puts(a, b, c)
#endif

/*
	ubf_data_dump_puts_typeless

	Wrapper macro for ubf_data_dump_puts () to cast the first parameter into the (const
	char *) ubf_data_dump_puts () is declared for.
*/
#define ubf_data_dump_puts_typeless(d,l,p)		\
			ubf_data_dump_puts ((const char *) d, l, p)

/*
	ubf_debug_data_dump_puts_typeless
	
	Debug version of the macro ubf_data_dump_puts_typeless(). Only outputs in debug
	versions.
*/
#define ubf_debug_data_dump_puts_typeless(d,l,p)		\
			ubf_debug_data_dump_puts ((const char *) d, l, p)


/*
	ubf_data_dump_puts_default
	
	Macro wrapper for ubf_data_dump_puts () that only requires the first two parameters
	and sets the last one (SUBF_DUMP_PARS) to NULL.
*/
#define ubf_data_dump_puts_default(d,l)			\
			ubf_data_dump_puts ((const char *) d, l, NULL)

#endif														// Of #ifdef nix.

/*
	Simple hex dump. This is what you need/want.
*/

enum enDataDmpWidth
{
	enDataDumpWidth16,
	enDataDumpWidth32
};
typedef enum enDataDmpWidth ddumpWidth;

/*
	requiredOutputSizeHexDump

	Returns the required buffer size for a hex dump. The return value
*/
size_t hxdmpRequiredSize		(
		size_t				lenDumpData,					// The length of the data to dump.
		ddumpWidth			width,							// Output width.
		newline_t			nl
								)
;

/*
	hxdmpWriteHexDump

	Stores a hex dump in szOutput. The buffer szOutput points to must be sufficiently large.
	It should have been obtained via a call to hxdmpRequiredSize ().
*/
size_t hxdmpWriteHexDump		(
		char				*szOutput,						// The output.
		const unsigned char	*ccDumpData,					// The data to dump.
		size_t				lenDumpData,					// The length of the data to dump.
		ddumpWidth			width,
		newline_t			nl
								)
;

/*
	test_strhexdump

	Test function.
*/
#ifdef DEBUG
	#ifndef BUILD_STRHEXDUMP_TEST_FNCT
	#define BUILD_STRHEXDUMP_TEST_FNCT
	#endif
#endif
#ifdef BUILD_STRHEXDUMP_TEST_FNCT
	bool test_strhexdump (void);
#else
	#define test_strhexdump()
#endif

EXTERN_C_END

#endif															// Of #ifndef STRHEXDUMP_H.
/****************************************************************************************

	File:		strintuint.h
	Why:		Conversion functions between character strings and integers.
	OS:			C99.
	Author:		Thomas
	Created:	2019-08-28
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-08-28	Thomas			Created.

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


	The functions ubf_itoa (), ubf_n_itoa10 (), ubf_str_from_uint16 (), ubf_str_from_int64 (),
	and ubf_str_from_uint64 () are (c) Lukas Chmela and derived from the versions at
	http://www.strudel.org.uk/itoa/ :

	* C++ version 0.4 char* style "itoa":
	* Written by Lukas Chmela
	* Released under GPLv3.

*/

#ifndef U_STR_INT_UINT_INCLUDED
#define U_STR_INT_UINT_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../pre/platform.h"
	#endif
#endif

#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

// Maximum lengths of unsigned and signed integer values in ASCII representation.
//	The definitions that end with _LEN specify the length excluding NUL, the ones
//	that end with _SIZE include the NUL terminator.
#ifndef UBF_INT8_LEN
#define UBF_INT8_LEN					(4)						// "-128"
// "1234" = 4.
#endif
#ifndef UBF_INT8_SIZE
#define UBF_INT8_SIZE					(4 + 1)					// "-128"
// "1234" = 4.
#endif
#ifndef UBF_INT16_LEN
#define UBF_INT16_LEN					(6)						// "-32768" = 6.
#endif
#ifndef UBF_INT16_SIZE
#define UBF_INT16_SIZE					(6 + 1)					// "-32768" = 6.
#endif
#ifndef UBF_INT32_LEN
#define UBF_INT32_LEN					(11)					// "-4294967296" = 11.
#endif
#ifndef UBF_INT32_SIZE
#define UBF_INT32_SIZE					(11 + 1)				// "-4294967296" = 11.
#endif
#ifndef UBF_INT64_LEN
#define UBF_INT64_LEN					(21)					// "+18446744073709551615".
// "+12345678901234567890" = 21.
#endif
#ifndef UBF_INT64_SIZE
#define UBF_INT64_SIZE					(21 + 1)				// "+18446744073709551615".
// "+12345678901234567890" = 21.
#endif
#ifndef UBF_UINT8_LEN
#define UBF_UINT8_LEN					(3)						// "255".
// "123" = 3.
#endif
#ifndef UBF_UINT8_SIZE
#define UBF_UINT8_SIZE					(3 + 1)					// "255".
// "123" = 3.
#endif
#ifndef UBF_UINT16_LEN
#define UBF_UINT16_LEN					(5)						// "65535".
// "12345" = 5.
#endif
#ifndef UBF_UINT16_SIZE
#define UBF_UINT16_SIZE					(5 + 1)					// "65535".
// "12345" = 5.
#endif
#ifndef UBF_UINT32_LEN
#define UBF_UINT32_LEN					(10)					// "4294967296";
// "1234567890" = 10.
#endif
#ifndef UBF_UINT32_SIZE
#define UBF_UINT32_SIZE					(10 + 1)				// "4294967296";
// "1234567890" = 10.
#endif
#ifndef UBF_UINT64_LEN
#define UBF_UINT64_LEN					(20)					// "18446744073709551615".
// "12345678901234567890" = 20.
#endif
#ifndef UBF_UINT64_SIZE
#define UBF_UINT64_SIZE					(20 + 1)				// "18446744073709551615".
// "12345678901234567890" = 20.
#endif

#ifndef ASCII_NUL
#define ASCII_NUL			'\0'
#endif
#ifndef ASCII_NUL_STR
#define ASCII_NUL_STR		"\0"
#endif

// Fall through comment used in switch () statements. See
//	https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wimplicit-fallthrough .
#if defined(_MSC_VER)
#ifndef UBF_FALLTHROUGH_HINT
#define UBF_FALLTHROUGH_HINT		/* FALLTHRU */
#endif
#else
#ifndef UBF_FALLTHROUGH_HINT
#define UBF_FALLTHROUGH_HINT						\
			__attribute__((fallthrough));
#endif
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef HAVE_C_ITO_ALPHABET
	#define HAVE_C_ITO_ALPHABET
	#define UBUILD_C_ITO_ALPHABET_IN_HERE
	extern char	c_ito_alphabet [];
#endif

/*
	Our version of itoa (). Taken from http://www.strudel.org.uk/itoa/ .
	It seems to be a very fast version.
*/
char *ubf_itoa (int value, char *result, int base);

/*
	ubf_n_itoa10

	This is an itoa () function that returns the amount of bytes written to result and
	uses a base of 10.
*/
size_t ubf_n_itoa10 (int value, char *result);

/*
	ubf_str0_from_59max

	Copies the resulting ASCII representation of the value ui59m, which can have values
	between 0 and 59, to the buffer result points to. This buffer must therefore have a
	size of at least two octets/bytes.

	The actual range of ui59m can be from 0 to 61, and the lookup table is big enough.
	See https://en.cppreference.com/w/c/chrono/tm for more details.
	"Range allows for a positive leap second. Two leap seconds in the same minute are
	not allowed (the C89 range 0..61 was a defect)."
	The lookup table holds 62 values (0 to 61) to avoid issues with C89 compilers.

	The function does not add a NUL-terminator to result, nor does it return a value.
	It always writes exactly two bytes to result. For example, if ui59m is 26, the
	function writes the non-NUL-terminated string "26" to result.

	The caller is responsible for ensuring that the function is not called with any
	values of ui59m greater than 59. Debug versions provide an assertion for this case.

	The function's purpose is to return ASCII representations of minutes, seconds,
	months, hours, days in a month, week numbers, or any unsigned integer of up to 59 very
	quickly through an indexed table.

	If the returned string is required to be NUL-terminated, use ubf_str0_from_59max_n ()
	instead.
*/
#ifdef DEBUG
	void ubf_str0_from_59max (char *result, uint8_t ui59m);
#else
	extern char c_0_to_59_str0 [62][2];
	#define ubf_str0_from_59max(r,u)	memcpy ((r), c_0_to_59_str0 [(u)], 2)
#endif

/*
	ubf_str0_from_59max_n

	The function or macro is identical to ubf_str0_from_59max () but does add a NUL-
	terminator.

	Copies the resulting ASCII representation of the value ui59m, which can have values
	between 0 and 59, to the buffer result points to. This buffer must therefore have a
	size of at least three octets/bytes since the function adds a NUL-terminator to result.

	The function's purpose is to return ASCII representations of minutes, seconds,
	months, hours, days in a month, week numbers, or any unsigned integer of up to 59 very
	quickly through a lookup table.
*/
#ifdef DEBUG
	void ubf_str0_from_59max_n (char *result, uint8_t ui59m);
#else
	#define ubf_str0_from_59max_n(r,u)					\
		memcpy ((r), c_0_to_59_str0 [(u)], 2);			\
		(r) [2] = '\0'
#endif

/*
	ubf_str_from_uint8
	
	Returns an ASCII representation of the value of ui8, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT8_SIZE octets long.

	The function returns the amount of decimal digits written to result, not
	counting the terminating NUL character.
*/
size_t ubf_str_from_uint8 (char *result, uint8_t ui8);

/*
	ubf_str_from_uint16
	
	Returns an ASCII representation of the value of ui16, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT16_SIZE bytes long.

	The function returns the amount of decimal digits written to result, which
	does not include the terminating NUL character.
*/
size_t ubf_str_from_uint16 (char *result, uint16_t ui16);

/*
	ubf_str0_from_uint16

	Returns an ASCII representation with leading zeroes of the value of ui16,
	in decimal (base 10). The buffer result points to must be at least digits + 1
	octets/bytes long.

	The parameter dgts cannot be 0.

	The function is identical to ubf_str_from_uint16 but writes leading zeroes to
	the buffer result points to. The parameter digits specifies the total amount
	of digits for the result, which should be any value between 1 and UBF_UINT16_LEN,
	which is 5. Values for digits greater than UBF_UINT16_LEN always produce leading
	zeroes only for the range between UBF_UINT16_LEN + 1 and digits because the
	value of ui16 can never become big enough to fill this area with any other
	number.

	The function returns the amount of digits written to result, not counting
	leading zeros, and also not counting a terminating NUL, or STR0_NOT_ENOUGH_DIGITS
	if the value of ui16 cannot be represented in the specified amount of digits.
	
	If the value of digits is not big enough to hold the ASCII
	representation of the value ui16, the function fills result up to digits
	numerical digits from the right and returns (size_t) -1, which is defined as
	STR0_NOT_ENOUGH_DIGITS.
	
	Note that the buffer result points to must be at least one octet larger
	than digits to hold a terminating NUL character. It is recommended to use a
	buffer size of UBF_UINT16_SIZE, which is UBF_UINT16_LEN + 1 for the NUL
	character.
*/
size_t ubf_str0_from_uint16 (char *result, size_t digits, uint16_t ui16);

/*
	ubf_str_from_int64

	Returns an ASCII representation of the value of i64, in decimal (base 10). The
	buffer result points to must be at least UBF_INT64_LEN bytes long.

	The function returns the amount of characters written to result, not counting
	the terminating NUL character.
*/
size_t ubf_str_from_int64 (char *result, int64_t i64);

/*
	ubf_str_to_int64

	Obtains a signed 64 bit integer of the ASCII string chStr in the address pi points
	to. The function stops at the first character that is not a numerical digit. However,
	chStr may start with an ASCII '+' or an ASCII '-' character. If pi is not NULL, the
	result of the conversion is returned at the memory location pi points to. For a
	function that is more picky and returns an error if chStr contains non-numerical
	characters, see ubf_int64_from_str ().

	The function returns the amount of characters used up for the conversion.
*/
size_t ubf_str_to_int64 (const char *chStr, int64_t *pi);

/*
	ubf_std_int64_from_str
	
	Wrapper macro for ubf_str_to_int64 () that reverses the order of its parameters
	and provides an API that is more standardised.
*/
#define ubf_std_int64_from_str(pi, pS)					\
	ubf_str_to_int64 (pS, pi)

/*
	ubf_str_from_uint64

	Returns an ASCII representation of the value of ui64, in decimal (base 10). The
	buffer result points to must be at least UBF_UINT64_SIZE bytes long, which is
	UBF_UINT64_LEN + 1, or 21.

	The function returns the amount of digits written to result, not counting the
	terminating NUL character.
*/
size_t ubf_str_from_uint64 (char *result, uint64_t ui64);

#ifndef STR0_NOT_ENOUGH_DIGITS
#define STR0_NOT_ENOUGH_DIGITS	((size_t) -1)
#endif

/*
	ubf_str0_from_uint64

	Returns an ASCII representation with leading zeroes of the value of ui64,
	in decimal (base 10). The buffer result points to must be at least digits + 1
	octets/bytes long.

	The parameter dgts cannot be 0.

	The function is identical to ubf_str_from_uint64 but writes leading zeroes to
	the buffer result points to. The parameter digits specifies the total amount
	of digits for the result, which should be any value between 1 and UBF_UINT64_LEN,
	which is 20. Values for dgts greater than UBF_UINT64_LEN always produce leading
	zeroes only for the range between UBF_UINT64_LEN + 1 and digits because the
	value of ui64 can never become big enough to fill this area with any other
	number.

	The function returns the amount of digits written to result, not counting
	leading zeros, and also not counting a terminating NUL, or STR0_NOT_ENOUGH_DIGITS
	if the value of ui64 cannot be represented in the specified amount of digits.
	
	If the value of digits is not big enough to hold the ASCII
	representation of the value ui64, the function fills result up to digits
	numerical digits from the right and returns (size_t) -1, which is defined as
	STR0_NOT_ENOUGH_DIGITS.
	
	Note that the buffer result points to must be at least one octet larger
	than digits to hold a terminating NUL character. It is recommended to use a
	buffer size of UBF_UINT64_SIZE, which is UBF_UINT64_LEN + 1 for the NUL
	character.
*/
size_t ubf_str0_from_uint64 (char *result, size_t digits, uint64_t ui64);

/*
	ubf_str__from_uint64

	The function is identical to ubf_str0_from_uint64 () with the exception
	that it returns an ASCII representation with leading spaces of the value of ui64,
	in decimal (base 10).
*/
size_t ubf_str__from_uint64 (char *result, size_t digits, uint64_t ui64)
;

/*
	ubf_uint64_from_str

	Obtains an unsigned 64 bit integer of the ASCII string chStr in ui. The conversion
	stops at the first white space or any character that is not a valid decimal digit.
	Additionally, the string chStr may start with an ASCII '+' character. If ui is not
	NULL, the result of the conversion is returned at the memory location ui points to.
	If ui is NULL, the result of the conversion is not stored but all checks are
	performed and the result value indicates success or failure. If chStr is NULL the
	function treats it as an emptry string, with the result of the conversion being 0.
	If chStr starts with an ASCII '-' or any other non-numeric character the function
	treats it as an empty string/number, which means 0 is returned.

	The function returns TRUE if the conversion was successful, FALSE otherwise. The
	conversion fails if chStr contains a number that is greater than UINT64_MAX.
	
	If the amount of characters consumed by the function is required, or if the
	amount of characters to be processed needs to be restricted, use
	ubf_uint64_from_str_n () instead.
*/
bool ubf_uint64_from_str (uint64_t *ui, const char *chStr);

/*
	ubf_uint64_from_str_n
	
	The function is similar to ubf_uint64_from_str () but only processes chStr
	up to nLen bytes/characters and returns the amount of characters consumed
	and used up for the value stored in ui by the function. The string can start
	with an optional '+' if the parameter s is enUintFromStrAllowPlus.
	
	If nLen should not be used, pass (size_t) -1 to the function. The function
	then stops when the NUL terminator is encountered.
	
	The function returns the amount of octets consumed from chStr.
*/
enum enUintFromStrN
{
	enUintFromStrDontAllowPlus,									// No '+' allowed.
	enUintFromStrAllowPlus										// Allow preceding '+'.
};
size_t ubf_uint64_from_str_n (uint64_t *ui, const char *chStr, size_t nLen, enum enUintFromStrN s);

/*
	ubf_std_uint64_from_str
	
	Wrapper macro for ubf_uint64_from_str_n () that provides an API that is more
	standardised. The caller does not need to provied a length paramter, and
	'+' is always considered a valid character.
*/
#define ubf_std_uint64_from_str(pui, pStr)				\
	ubf_uint64_from_str_n (pui, pStr, (size_t) -1,		\
			enUintFromStrAllowPlus)

/*
	is_number_str_l

	Returns true if str up to a length of len is a valid number.
	The function checks if len characters are digits, and if they are,
	returns true.

	If len is 0, nothing is read from str, and the function returns true.

	The function does not read beyond len unless len is USE_STRLEN.
	If len is USE_STRLEN, the function calls strlen (str) to obtain it,
	in which case str must be NUL-terminated.
*/
bool is_number_str_l (const char *str, size_t len);

/*
	ubf_int64_from_str

	Obtains a signed 64 bit integer of the ASCII string chStr in the address pi points
	to. All possible checks are performed. The string in chStr must not contain white
	space or any character that is not a valid decimal digit. However, chStr may start
	with an ASCII '+' or an ASCII '-' character. If pi is not NULL, the result of the
	conversion is returned at the memory location pi points to. If pi is NULL, the result
	of the conversion is not stored but all checks are performed and the result value
	indicates success or failure. If chStr is NULL the function treats it as an emptry
	string, with the result of the conversion being 0. For a function that stops at the
	first non-numerical digit, see ubf_str_to_int64 ().

	The function returns TRUE if the conversion was successful, FALSE otherwise. The
	conversion fails if chStr contains a number that is greater than INT64_MAX or
	smaller than INT64_MIN. It also fails if chStr contains any character that is not a
	digit, and not a '+', or a '-' as its first character.
*/
bool ubf_int64_from_str (int64_t *pi, const char *chStr);

/*
	ubf_uint16_from_str
	ubf_ushort_from_str

	Returns an unsigned 16 bit integer (uint16_t) of the ASCII string chStr in the
	address pu points to. The function calls ubf_uint64_from_str () to obtain the result.
	If pus is NULL, the return value of the function indicates the success or failure of
	the conversion without returning the actual result of the conversion. The biggest
	number that can be successfully converted to a uint16_t is USHRT_MAX, which is
	usually 0xFFFF.

	A return value of TRUE means the conversion was successful. If the function returns
	FALSE the conversion was unsuccessful. The function returns TRUE if the conversion
	was successful but due to pus being NULL the result of it could not be returned to
	the caller.
*/
bool ubf_uint16_from_str (uint16_t *pus, const char *chStr);
#define ubf_ushort_from_str(a,b)					\
			ubf_uint16_from_str (a, b)

/*
	ubf_strd_from_uint64

	Returns the decimal representation of u64 in ASCII. The buffer chStr points to must
	be at least UBF_UINT64_STRLEN bytes long. For a function with identical functionality
	but that returns the bytes written to the result, see ubf_str_from_uint64 (). Unlike
	ubf_str_from_uint64 (), the function ubf_strd_from_uint64 () calls the library
	routine snprintf () to perform the conversion but discards its return value.
	
	Note that this function is around 4 times slower than ubf_str_from_uint64 (). It is
	therefore disabled.
*/
//void ubf_strd_from_uint64 (char *chStr, uint64_t u64);
#define ubf_strd_from_uint64(s,u)						\
		error Function ubf_strd_from_uint64 () is obsolete. Use ubf_str_from_uint64. See comment.

/*
	Test function builds.
*/
#ifdef DEBUG
	#ifndef UBF_BUILD_STRINTUINT_TEST
	//#define UBF_BUILD_STRINTUINT_TEST
	#endif
#endif
#ifdef UBF_BUILD_STRINTUINT_TEST
	bool ubf_test_str_from_uint8 (void);
	bool ubf_test_str0 (void);
	bool Test_strintuint (void);
#else
	#define ubf_test_str_from_uint8()		(true)
	#define ubf_test_str0()					(true)
	#define Test_strintuint()				(true)
#endif


#ifdef __cplusplus
	}
#endif

#endif															// End of U_STR_INT_UINT_INCLUDED.
/****************************************************************************************

	File:		strabsolutepath.h
	Why:		String functions for absolute/relative paths.
	OS:			C99
	Author:		Thomas
	Created:	2021-07-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The functions in this module do not use any file system functions.
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

#ifndef STRISABSOLUTEPATH_H
#define STRISABSOLUTEPATH_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

EXTERN_C_BEGIN

/*
	is_absolute_path_unix
	is_absolute_path_unx
	
	Returns or evaluates to true if the string chPath points to is an absolute Unix/Linux path,
	false if it is not. An absolute Unix/Linux path starts with a forward slash
	("/").

	The buffer chPath (in debug versions) or p (in release versions) points to must be at least
	one octet/byte long.
*/
#ifdef DEBUG
	bool is_absolute_path_unix (const char *chPath);
#else
	#define is_absolute_path_unix(p)					\
			('/' == (p)[0])
#endif
#define is_absolute_path_unx(p)							\
			is_absolute_path_unix (p)

/*
	is_unc_path

	Evaluates to true if the NUL-terminated string p is a UNC path
	like "\\host\path" or "//host/path". The buffer p points to must
	be NUL-terminated.
*/
#define is_unc_path(p)									\
			(											\
					(									\
							'\\' == (p)[0]				\
						&&	'\\' == (p)[1]				\
					)									\
				||	(									\
							'/' == (p)[0]				\
						&&	'/' == (p)[1]				\
					)									\
			)

/*
	is_absolute_drive_path

	Evaluates to true if the NUL-terminated string p is a typical Windows drive path
	like "X:\" or "X:/". The buffer p points to must be NUL-terminated.
*/
#define is_absolute_drive_path(p)						\
			(											\
					isalpha ((p)[0])					\
				&&	':' == (p)[1]						\
				&&	('\\' == (p)[2]	||	'/' == (p)[2])	\
			)

#define is_drive_path(p)								\
	error "Macro obsolete. Use is_full_drive_path() instead"

/*
	is_absolute_path_win
	is_absolute_path_windows
	
	Returns true if the string chPath points to is an absolute Windows path,
	false otherwise. An absolute Windows path either starts with two consecutive
	slashes (forward or backward) or starts with a drive letter and a colon
	sequence.
	
	Note that the function does not accept a mix of starting forward and backward
	slashes like "/\" or "\/". The function returns false in these cases.
*/
bool is_absolute_path_win (const char *chPath);
#define is_absolute_path_windows(p)						\
			is_absolute_path_win (p)

/*
	is_absolute_path
	
	Returns true if the path is an absolute path on either Windows or Unix/Linux.
	
	This is a function in debug versions, a macro in release versions.
	The function/macro calls is_absolute_path_unix () and is_absolute_path_win ().
*/
#ifdef DEBUG
	bool is_absolute_path (const char *chPath);
#else
	#define is_absolute_path(p)							\
		(												\
				is_absolute_path_unix	(p)				\
			||	is_absolute_path_win	(p)				\
		)

#endif

/*
	is_absolute_path_unix_l

	Returns or evaluates to true if len is greater than 0 and the first character
	chPath points to is a forward slash.

	This is a function in debug versions, a macro in release versions.
*/
#ifdef DEBUG
	bool is_absolute_path_unix_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_unix_l(p, l)				\
		(l && '/' == (p)[0])
#endif

/*
	is_absolute_path_win_l

	Returns or evaluates to true if chPath either points to a Windows UNC path or
	a full drive path. UNC paths start with two backslashes. A full drive path starts
	with a drive letter, a colon, and a backslash.

	The parameter len specifies the length of the buffer chPath points to.

	This is a function in debug versions, a macro in release versions.
*/
#ifdef DEBUG
	bool is_absolute_path_win_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_win_l(p, l)				\
		(												\
				(l > 1 && is_unc_path (p))				\
			||	(l > 2 && is_absolute_drive_path (p))	\
		)
#endif

/*
	is_absolute_path_l

	Returns true if the path is an absolute path on either Windows or Unix/Linux.

	The parameter len specifies the length of the buffer chPath points to.

	This is a function in debug versions, a macro in release versions.
	The function/macro calls is_absolute_path_unix_l () and is_absolute_path_win_l ().
*/
#ifdef DEBUG
	bool is_absolute_path_l (const char *chPath, size_t len);
#else
	#define is_absolute_path_l(p, l)					\
		(												\
				is_absolute_path_unix_l (p, l)			\
			||	is_absolute_path_win_l (p, l)			\
		)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRISABSOLUTEPATH_H.
/****************************************************************************************

	File:		strisdotordotdot.h
	Why:		Checks for "." and ".." file/folder names.
	OS:			C99.
	Author:		Thomas
	Created:	2022-05-18

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-05-18	Thomas			Created.

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

#ifndef STRISDOTORDOTDOT_H
#define STRISDOTORDOTDOT_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	isDotOrDotDotW

	Returns true if the path wcPath points to is "." or "..", false otherwise.
*/
#ifdef OS_IS_WINDOWS
	bool isDotOrDotDotW (wchar_t *wcPath);
#endif

/*
	isDotOrDotDotU8

	UTF-8 version of isDotOrDotDotW (). Returns true if the path cPath points to
	is "." or "..", false otherwise.
*/
bool isDotOrDotDotU8 (char *cPath);

EXTERN_C_END

#endif														// Of #ifndef STRISDOTORDOTDOT_H.
/****************************************************************************************

	File		struri.h
	Why:		Helpers for URIs.
	OS:			C99
	Created:	2025-01-06

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-06	Thomas			Created.

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

#ifndef STRURI_H
#define STRURI_H

#include <stdint.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./restrict.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/restrict.h"
	#endif

#endif

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

EXTERN_C_BEGIN

/*
	uri_encode_str

	Encodes the source string str suitable for URIs. The parameter len specifies the length
	of the buffer str points to. If len is USE_STRLEN, the function obtains its length via a
	call to strlen ().

	The function returns the amounts of characters written to szURIencoded, excluding the
	terminating NUL. If szURIencoded is NULL, the functions returns the amount of characters
	(octets) required to store the encoded string, including the terminating NUL.

	The maximum buffer required to store str as a URI encoded string is 3 times the length of
	str (plus NUL terminator).
*/
size_t uri_encode_str	(
			char			*cunilog_restrict szURIencoded,
			const char		*cunilog_restrict str,
			size_t			len
						)
;

EXTERN_C_END

#endif														// Of #ifndef STRURI_H.
/****************************************************************************************

	File:		strmembuf.h
	Why:		String helper functions for SMEMBUF structures.
	OS:			C99
	Author:		Thomas
	Created:	2023-05-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2023-05-25	Thomas			Created.

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

#ifndef STRMEMBUF_H
#define STRMEMBUF_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./membuf.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../mem/membuf.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

#ifndef STRMEMBUF_DEFAULT_ALIGNMENT
#define STRMEMBUF_DEFAULT_ALIGNMENT		(16)
#endif

EXTERN_C_BEGIN

/*
	SMEMBUFfromStrReserveBytes
	
	Duplicates str and fills the SMEMBUF structure pmb points to accordingly.
	If len is (size_t) -1, the function strlen () is used to obtain the length of str.
	The macro USE_STRLEN is defined as ((size_t) -1).
	The buffer the function allocates is len + reserve octets (bytes).
	The string in the buffer is always NUL-terminated.

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, which is len on success, or 0 when the heap allocation fails. The NUL
	terminator the function always writes is not included in the return value.
*/
size_t SMEMBUFfromStrReserveBytes (SMEMBUF *pmb, const char *str, size_t len, size_t reserve)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFfromStrReserveBytes) (SMEMBUF *pmb, const char *str, size_t len, size_t reserve)
;

/*
	SMEMBUFfromStr

	Duplicates str and fills the SMEMBUF structure pmb points to accordingly.
	If len is USE_STRLEN the function calls strlen () to obtain the string's length.
	A NUL terminator is written at the end of the buffer.

	If str is NULL, len must be 0. If len is 0, the function writes out a NUL-terminator
	only

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes, which is len on success,
	or 0 when the heap allocation fails.
*/
size_t SMEMBUFfromStr (SMEMBUF *pmb, const char *str, size_t len);
TYPEDEF_FNCT_PTR (size_t, SMEMBUFfromStr) (SMEMBUF *pmb, const char *str, size_t len);

/*
	SMEMBUFfromStrFmt_va

	Variadic version of SMEMBUFfromStr () that expects a va_list argument.

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes. It returns 0 when the
	heap allocation fails.
*/
size_t SMEMBUFfromStrFmt_va (SMEMBUF *pmb, const char *fmt, va_list ap)
;

/*
	SMEMBUFfromStrFmt

	Variadic version of SMEMBUFfromStr ().

	The function returns the amount of bytes (octets) copied to the buffer of the SMEMBUF
	structure, not counting the NUL terminator the function writes. It returns 0 when the
	heap allocation fails.
*/
size_t SMEMBUFfromStrFmt (SMEMBUF *pmb, const char *fmt, ...)
;

/*
	SMEMBUFstrFromUINT64
	
	Converts the value of ui to a string and stores the result in the buffer of pmb.
	The string is NUL-terminated.
	
	The function returns the amount of octets/bytes written to the buffer of the SMEMBUF
	structure, not counting the NUL-terminator.
*/
size_t SMEMBUFstrFromUINT64 (SMEMBUF *pmb, uint64_t ui)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrFromUINT64) (SMEMBUF *pmb, uint64_t ui)
;

/*
	SMEMBUFstrconcatReserve

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the string str with a length of lenstr, storing the result in the SMEMBUF
	structure's buffer. Both length parameters, len and lenstr, can be USE_STRLEN. If precise
	lengths are given, the strings do not need to be NUL-terminated.
	
	If str is NULL, the parameter lenstr is ignored and the buffer of the SMEMBUF structure
	is not changed, i.e. if str is NULL or lenstr is 0, the function returns len without
	touching the buffer.

	The resulting string in the buffer of pmb is NUL-terminated.

	If the buffer of pmb needs reallocating, the buffer is made big enough to additionally
	hold at least reserve octets. Set reserve to 0 if no additional buffer space is needed.
	If the buffer of pmb is already big enough to hold the original string plus str plus
	a NUL terminator, its size is not changed and the parameter reserve ignored.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
size_t SMEMBUFstrconcatReserve (SMEMBUF *pmb, size_t len, char *str, size_t lenstr, size_t reserve)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcatReserve) (SMEMBUF *pmb, size_t len, char *str, size_t lenstr, size_t reserve);

/*
	SMEMBUFstrconcat

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the string str with a length of lenstr, storing the result in the SMEMBUF
	structure's buffer. Both length parameters, len and lenstr, can be USE_STRLEN. If precise
	lengths are given, the strings do not need to be NUL-terminated.
	
	If str is NULL, the parameter lenstr is ignored and the buffer of the SMEMBUF structure
	is not changed, i.e. if str is NULL or lenstr is 0, the function returns len without
	touching the buffer.

	The resulting string in the buffer of pmb is NUL-terminated.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
size_t SMEMBUFstrconcat (SMEMBUF *pmb, size_t len, char *str, size_t lenstr)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcat) (SMEMBUF *pmb, size_t len, char *str, size_t lenstr);

/*
	SMEMBUFstrconcatW

	This function is only available on Windows.

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the Windows UTF-16 string wstr with a length of lenwstr, storing the result
	in the SMEMBUF structure's buffer. Before the concatenation, wstr is converted to UTF-8.
	Both length parameters, len and lenwstr, can be USE_STRLEN. If precise lengths are given,
	the strings do not need to be NUL-terminated. The length parameter lenwstr is the length
	of wstr in 16-bit words, not octets/bytes.

	The resulting string in the buffer of pmb is NUL-terminated.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
#ifdef PLATFORM_IS_WINDOWS
	size_t SMEMBUFstrconcatW (SMEMBUF *pmb, size_t len, wchar_t *wstr, size_t lenwstr);
	TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcatW)
		(SMEMBUF *pmb, size_t len, wchar_t *wstr, size_t lenwstr);
#endif

/*
	SMEMBUFstrconcatpaths

	Concatenates the string with a length of len in the buffer of the SMEMBUF structrue pmb
	points to and the string strPath with a length of lenPath, storing the result in the SMEMBUF
	structure's buffer. Both length parameters, len and lenPath, can be USE_STRLEN. If precise
	lengths are given, the strings do not need to be NUL-terminated.
	
	The function is identical to SMEMBUFstrconcat (), but assumes that both strings are either
	directories/paths or that the buffer of the SMEMBUF structure contains a path/directory
	and strPath is a filename. It concatenates the paths or path and filename correctly by
	removing/ignoring excess forward or backward slashes (path separators) at the end of
	the structure's buffer and from the start of strPath. Only single separators are removed.

	The function does not distinguish between POSIX and Windows path separators. Forward and
	backward slashes are treated identically, but if a directory separator is added by the
	function, it will be the correct directory separator for the current platform.

	The buffer of the SMEMBUF structure takes precedence over strPath, meaning that if the
	buffer does not end with a directory separator, one is appended. If strPath starts with
	a directory separator, it is removed. This may lead to a different separator being
	inserted than the one strPath originally contained, as the function always inserts the
	correct separator for the current platform, which is a forward slash ("/") on POSIX and a
	backslash ("\") on Windows.

	If the buffer of pmb is empty, strPath is copied unchanged, ignoring any slash/backslash
	it may contain. If lenPath is 0, or is deduced to be 0 via a call to strlen (), len is
	returned and the buffer not changed.

	The function returns the new length of the string in the buffer of pmb. The length
	is without a terminating NUL character.

	Do not use the return value to determine whether the function succeeded or failed. Use the
	macro isUsableSMEMBUF() instead.
*/
size_t SMEMBUFstrconcatpaths (SMEMBUF *pmb, size_t len, char *strPath, size_t lenPath)
;
TYPEDEF_FNCT_PTR (size_t, SMEMBUFstrconcatpaths) (SMEMBUF *pmb, size_t len, char *strPath, size_t lenPath);

/*
	SMEMBUFstrStartsWithStr
	SMEMBUFstrEndsWithStr

	The functions return true if the buffer of the SMEMBUF structure pmb points to starts
	with the string str of length lenStr. If len or lenStr is USE_STRLEN, the functions call
	strlen () to obtain the value in question.
*/
bool SMEMBUFstrStartsWithStr (SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);
bool SMEMBUFstrEndsWithStr (SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);
TYPEDEF_FNCT_PTR (bool, SMEMBUFstrStartsWithStr)
	(SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);
TYPEDEF_FNCT_PTR (bool, SMEMBUFstrEndsWithStr)
	(SMEMBUF *pmb, size_t len, const char *str, size_t lenStr);

/*
	test_strmembuf

	Test function for the module.
	returns true on success, false otherwise.
*/
#ifdef STRMEMBUF_BUILD_TEST_FNCT
	bool test_strmembuf (void);
#else
	#define test_strmembuf()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifdef STRMEMBUF_H.
/****************************************************************************************

	File:		strwildcards.h
	Why:		Wildcard functions
	OS:			C99.
	Author:		Thomas
	Created:	2022-03-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-21	Thomas			Created.

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

#ifndef STRWILDCARDS_H
#define STRWILDCARDS_H

#include <stdbool.h>
#include <inttypes.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

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

#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif

/*
	Test function in debug versions only (default).
*/
#ifdef DEBUG
	#ifndef STRWILDCARDS_BUILD_TEST_FNCT
	//#define STRWILDCARDS_BUILD_TEST_FNCT
	#endif
#endif

EXTERN_C_BEGIN

/*
	wildCardFileName
	
	Obtains the last part of a path if it contains wildcard characters.
	
	The function returns the filename, preceeded by a directory separator, of a path that
	contains wildcard characters and optionally, with parameter plen, its length. If no
	wildcard filename can be found, the function returns NULL. If the function returns
	NULL, and plen is not NULL, the address plen points to is set to 0.
	
	Examples:
	
	ccPath					returns		plen
	"C:\*.*"				"\*.*"		4
	"C:\test\*.tx?"			"\*.tx?"	6
*/
const char *wildCardFileName (size_t *plen, const char *ccPath)
;

/*
	lenPathWithoutWildcardFileName
	
	Returns the length of the path that ends with a wildcard filename, including the
	directory separator.
	
	ccPath					returns
	"C:\*.*"				3
	"C:\test\*.tx?"			8
	"C:*.*"					2
	"C:\test"				7			There are no wildcards.
*/
size_t lenPathWithoutWildcardFileName (const char *ccPath)
;

/*
	matchWildcardPattern
	matchWildcardPatternW

	Note that the function has been renamed from globMatch () to matchWildcardPattern ().

	The function matchWildcardPattern () expects UTF-8 strings while the function
	matchWildcardPatternW () is its wide string version. The length parameters for
	matchWildcardPatternW () are in UTF-16 characters, not octets/bytes. Whenever
	this comment block mentions "octet" or "octets", for matchWildcardPatternW () this
	means "UTF-16 16 bit word" or "UTF-16 16 bit words".

	The function compares ccStri with length lnStri against the glob pattern (a string
	that can contain wildcard characters) ccGlob with length lnGlob. It is not a replacement
	for fnmatch () (https://www.man7.org/linux/man-pages/man3/fnmatch.3.html) and does
	not support any type of regular expression. It is a simple helper function that filters
	for a file mask when enumerating the contents of a directory.

	The string parameter ccStri is not meant to contain wildcard characters. The string
	parameter ccGlob can contain wildard characters.

	The length arguments lnStri and lnGlob can have the value USE_STRLEN, which is (size_t)
	-1, in which case the length in question is obtained via a call to strlen (). For
	matchWildcardPatternW (), the length is obtained via a call to wcslen ().

	Both, ccStri and ccGlob, can contain NUL characters if lnStri and lnGlob are provided,
	i.e. are not USE_STRLEN.

	Unless a length is USE_STRLEN, the function does not read from the buffers beyond their
	length parameters. This means that if a length value is 0 nothing will ever be read from
	the string buffer. In the examples below the buffer in these cases is shown as "" but
	could as well be NULL or any other arbitrary value.

	The buffers ccStri and ccGlob must not point to the same memory location and must not
	overlap.

	The function returns true if ccStri matches the pattern ccGlob points to, false if not.

	If both lengths are 0, the function treats this as a match and returns true. If lnStri
	is 0 but lnGlob is not, the function in this case assumes that a match is impossible and
	returns false. If lnGlob is 0, this is treated as a match against anything, and the
	function returns true independent of the value of lnStri or the contents of ccStri.

	Match rules for the glob pattern ccGlob:
	- The comparison is case-sensitive. "A" does not match "a" and vice versa.
	- A single question mark ("?") matches a single octet in ccStri including path
		separators ("/" or "\").
	- An asterisk ("*") matches zero or more octets but not path separators ("/" or "\").
	- Two or more asterisks ("**", "***", "****", etc.) match zero or more octets including
		path separators ("/" or "\").
	- The path separators (forward and backward, "/" and "\") are treated as equal and
		therefore match each other.
	- A question mark ("?") after two or more asterisks ("**", "***", "****", etc.) never
		matches, because the asterisks will have consumed the string entirely. To match
		a minimum amount of characters, place the question mark(s) first. For instance,
		use "?**123" to match "0123" but not "123".
	
	ccStri		lnStri		ccGlob		lnGlob			return
	""			0			""			0				true
	"a"			1			""			0				true
	"a"			1			"a"			1				true
	"a/b/c"		5			"a\*"		3				false				See (1) below.
	"a\b\c"		5			"a\*\*"		5				true				See (1) below.
	"/"			1			"\"			1				true				See (1) below.
	"/home/usr" USE_STRLEN	"\*?usr"	6				true				See (1) below.
	"1/2/3"		5			"1?2?3"		5				true				See (2) below.
	"/1"		2			"?**"		3				true				See (3) below.

	Some explanations/help:
	In the above examples, strings are not C literals as backslashes are not escaped.
	(1) The function treats forward slashes and backslashes as being identical characters.
	(2) A question mark also matches a path separator.
	(3) Since two or more asterisks followed by a question mark never match, place the
		question mark first to match a minimum of a single character: "?**"

	See function strwildcards_test_function () for a more complete list of expectations.
*/
bool matchWildcardPattern	(
		const char		*cunilog_restrict ccStri,	size_t lnStri,
		const char		*cunilog_restrict ccGlob,	size_t lnGlob
							)
;
bool matchWildcardPatternW	(
		const wchar_t	*cunilog_restrict ccStri,	size_t lnStri,
		const wchar_t	*cunilog_restrict ccGlob,	size_t lnGlob
							)
;

/*
	strwildcards_test_function

	Test function for the module.
*/
#ifdef STRWILDCARDS_BUILD_TEST_FNCT
	bool strwildcards_test_function (void);
#else
	#define strwildcards_test_function() (true)
#endif

EXTERN_C_END

#endif														// Of #ifndef STRWILDCARDS_H.
/****************************************************************************************

	File:		ubfcharscountsandchecks.h
	Why:		Character counting and check routines
	OS:			C99
	Author:		Thomas
	Created:	2020-08-31
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2020-08-31	Thomas			Created.

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

#ifndef UBFCHARSCOUNTSANDCHECKS
#define UBFCHARSCOUNTSANDCHECKS

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

#endif

/*
	The defintion for unknown string lengths. Functions taking this value for a length
	call strlen () to obtain the correct length.
*/
#ifndef USE_STRLEN
#define USE_STRLEN							((size_t) -1)
#endif
#ifndef SUBF_STRING_UNKNOWN_LENGTH
#define SUBF_STRING_UNKNOWN_LENGTH			USE_STRLEN
#endif
#ifndef SUBF_STRING_LENGTH_UNKNOWN
#define SUBF_STRING_LENGTH_UNKNOWN			USE_STRLEN
#endif
#ifndef SUBF_STRING_USE_STRLEN
#define SUBF_STRING_USE_STRLEN				USE_STRLEN
#endif

EXTERN_C_BEGIN

/*
	ubf_is_printable_ASCII

	Returns true if the value of c is greater than 0x1F and lower than 0x7F.
	A character counts as printable if it is within the range from SPC (20h, 32d) to '~'
	(7Eh, 126d), in which case the function returns true.
	
	The macro/function returns false if the octet in c is outside this range.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool ubf_is_printable_ASCII (char c);
	TYPEDEF_FNCT_PTR (bool, ubf_is_printable_ASCII) (char c);
#else
	// From SPC (20h, 32d) to '~' (7Eh, 126d).
	#define ubf_is_printable_ASCII(c)					\
		((unsigned char) c > 0x1F && (unsigned char) c < 0x7F)
#endif

/*
	str_has_only_printable_ASCII

	Returns true if sz only contains printable ASCII characters.
*/
bool str_has_only_printable_ASCII (const char *sz, size_t len)
;
TYPEDEF_FNCT_PTR (bool, str_has_only_printable_ASCII) (const char *sz, size_t len)
;

/*
	ubf_is_letter
	
	Returns true if the character in c is >= 'A' and <= 'Z' or >= 'a' and <= 'z',
	false otherwise. The function is identical to the standard C function isalpha (),
	which is defined as ubf_isalpha () in platform.h.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool ubf_is_letter (char c);
	TYPEDEF_FNCT_PTR (bool, ubf_is_letter) (char c);
#else
	#define ubf_is_letter(c)	ubf_isalpha(c)
#endif

/*
	ubf_is_letter_until
	
	Returns a pointer that points after the first occurrance of c in ch, provided that all
	characters before this first occurrance are letters, determined by invokations of
	ubf_is_letter () for each character.
	
	The function returns NULL if the string in c contains any character that is not a letters
	or if c could not be found.
*/
char *ubf_is_letter_until (char *ch, char c);
TYPEDEF_FNCT_PTR (char *, ubf_is_letter_until) (char *ch, char c);

/*
	ubf_is_special
	
	Macro that evaluates to TRUE if the character c is not a letter and not a numerical
	digit. In other words, it evaluates to TRUE if the character c is a special character.
*/
#define ubf_is_special(c)								\
	(													\
			!ubf_is_letter	(c)							\
		&&	!ubf_isdigit	(c)							\
	)

/*
	isWhiteSpace

	Returns true if c is white space. Line endings like CR and LF do not count as white space.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool isWhiteSpace (char c);
	TYPEDEF_FNCT_PTR (bool, isWhiteSpace) (char c);
#else
	#define isWhiteSpace(c)								\
		(			ASCII_SPC	== (c)					\
				||	ASCII_BS	== (c)					\
				||	ASCII_TAB	== (c)					\
				||	ASCII_VT	== (c)					\
				||	ASCII_FF	== (c)					\
		)
#endif

/*
	isDirectorySeparator
	isDirSep

	Evaluates to true if c is a directory separator, which can be either a forward
	or a backward slash.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool isDirectorySeparator (char c);
	TYPEDEF_FNCT_PTR (bool, isDirectorySeparator) (char c);
#else
	#define isDirectorySeparator(c)						\
		('/' == (c) || '\\' == (c))
#endif
#define isDirSep(c)			isDirectorySeparator (c)

/*
	isWrongDirectorySeparator
	isWrongDirSep
	
	Evaluates to true if c is the wrong directory separator. The wrong directory separator
	on Windows systems is the forward slash ("/"), on POSIX systems the backslash ("\").
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	bool isWrongDirectorySeparator (char c);
	TYPEDEF_FNCT_PTR (bool, isWrongDirectorySeparator) (char c);
#else
	#define isWrongDirectorySeparator(c)				\
		(UBF_WRONG_DIR_SEP == c)
#endif
#define isWrongDirSep(c)	isWrongDirectorySeparator (c)

/*
	ubf_count_numerical_digits
	
	Returns the amount of numerical digits (between '0' and '9') within the character string
	cc points to. The string cc points to is required to be NUL-terminated.
*/
size_t ubf_count_numerical_digits (const char *cc);
TYPEDEF_FNCT_PTR (size_t, ubf_count_numerical_digits) (const char *cc);

/*
	ubf_count_starts_with_numerical_digits_up_to
	
	Returns the amount of numerical digits (between '0' and '9') the character string
	cc points starts with, up to len characters/octets.
*/
size_t ubf_count_starts_with_numerical_digits_up_to (const char *cc, size_t len);
TYPEDEF_FNCT_PTR (size_t, ubf_count_starts_with_numerical_digits_up_to) (const char *cc, size_t len);

/*
	ubf_count_special_characters
	
	Returns the amount of special characters in the string cc points to. Special characters
	for this function are characters that are neither upper or lower case letters nor numerical
	digits.
*/
size_t ubf_count_special_characters (const char *cc);
TYPEDEF_FNCT_PTR (size_t, ubf_count_special_characters) (const char *cc);

/*
	ubf_count_char

	Counts how many times c occurs in cc and returns this number.
*/
size_t ubf_count_char (const char *cc, char c);
TYPEDEF_FNCT_PTR (size_t, ubf_count_char) (const char *cc, char c);

/*
	ubf_obtain_strlen
	STRLENSZ

	Returns the length of the NUL-terminated or non-NUL-terminated string sz.

	- If sz is NULL, the function returns 0.
	- If providedLength is (size_t) -1, the function returns strlen (sz). This requires sz to
		be NUL-terminated.
	- For any other value of providedLength, the function or macro returns providedLength.
		This should be the length of sz without the NUL-terminator, as would be obtained
		via strlen (sz) if sz was NUL-terminated.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	size_t ubf_obtain_strlen (const char *sz, size_t providedLength);
	TYPEDEF_FNCT_PTR (size_t, ubf_obtain_strlen) (const char *sz, size_t providedLength);
#else
	#define ubf_obtain_strlen(sz, len)					\
		(sz) ? (USE_STRLEN == (len) ? strlen (sz) : (len)) : 0
#endif
#define STRLENSZ(s, l)	ubf_obtain_strlen (s, l)

EXTERN_C_END

#endif															// Of UBFCHARSCOUNTSANDCHECKS.
/****************************************************************************************

	File		testProcesHelper.h
	Why:		Test for module ProcesHelper.
	OS:			C99
	Created:	2025-07-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-07-25	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The purpose of this module is to provide a playground for testing the function
	CreateAndRunCmdProcessCapture () in module ProcessHelper.
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

#ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS

#ifndef U_TEST_PROCESS_HELPER_H
#define U_TEST_PROCESS_HELPER_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		//#include "./restrict.h"
	#else
		#include "./../pre/externC.h"
		//#include "./../pre/restrict.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	Arguments and commands.
*/
extern const char *szTstPrsHlpsExitcode;					// Argument is an int.
extern const char *szTstPrsHlpsInput;						// Argument is an int,
															//	which specifies the amount
															//	of lines to read from stdin.
															//	Each line is echoed back to
															//	stdout.
extern const char *szTstPrsHlpsOutput;						// Argument is three ints:
															//	Seed, amount lines, and max
															//	line length.
															//	Random output goes to stdout.

/*
	Internal test function for this module.
*/
#ifdef TEST_PROCESS_HELPER_BUILD_TEST_FNCT
	bool TestProcessHelperTestFnct (void);
#else
	#define TestProcessHelperTestFnct()	(true)
#endif


EXTERN_C_END

#endif														// Of #ifndef U_TEST_PROCESS_HELPER_H.

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
/****************************************************************************************

	File:		cunilogcfgparser.h
	Why:		Simple configuration parser.
	OS:			C99
	Author:		Thomas
	Created:	2024-11-28
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-28	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	Implements a simple config parser. The Windows ini file format
	(https://en.wikipedia.org/wiki/INI_file) served as its base. Notable differences
	include support for C++-style multi-line comments, C-style comments, arbitrary
	quotes, and white space.
	
	Section names and key names are case-sensitive by default.


	Not implemented yet:

	In the future, an implementation similar to a config file reader/parser for Libucl
	(https://github.com/vstakhov/libucl) is planned too.

	The library couldn't be used for several reasons:
	- Too big and too feature-rich.
	- Doesn't support C++ style line comments (//).
	- Lots of error handling.

	Compared to libucl, this module is very simple.

	Example from https://github.com/vstakhov/libucl:

	param = value;
	section {
		param = value;
		param1 = value1;
		flag = true;
		number = 10k;
		time = 0.2s;
		string = "something";
		subsection {
			host = {
				host = "hostname";
				port = 900;
			}
			host = {
				host = "hostname";
				port = 901;
			}
		}
	}

	Each config entity is treated as a key/value pair, for instance:
	key = value;
	The semicolon at the end of a key/value pair is optional.
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

#ifndef CUNILOGCFGPARSER_H
#define CUNILOGCFGPARSER_H

#ifdef CUNILOG_BUILD_CFG_PARSER

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./restrict.h"
		//#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/restrict.h"
		//#include "./../pre/platform.h"
	#endif

#endif

#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

EXTERN_C_BEGIN

/*
	The structures for ini files.
*/
typedef struct scuniloginikeyvalue
{
	const char				*szKeyName;
	size_t					lnKeyName;
	const char				*szValue;
	size_t					lnValue;
} SCUNILOGINIKEYVALUE;

typedef struct scuniloginisection
{
	const char				*szSectionName;
	size_t					lnSectionName;
	SCUNILOGINIKEYVALUE		*pKeyValuePairs;
	unsigned int			nKeyValuePairs;
} SCUNILOGINISECTION;

typedef struct scunilogini
{
	char					*buf;
	SCUNILOGINISECTION		*pIniSections;
	unsigned int			nIniSections;
	SCUNILOGINIKEYVALUE		*pKeyValuePairs;
	unsigned int			nKeyValuePairs;

	// Parse error.
	size_t					errLineNumber;					// The line number within the buffer.
															//	First line is 1.
	size_t					errCharNumber;					// The position of pStart within
															//	a line. 1 = first column/character.
	size_t					errAbsPosition;					// Position within the entire buffer.
															//	1 = first position/character.
	bool					bParseFail;
} SCUNILOGINI;
/*
	End of structures for ini files.
*/


typedef uint64_t	cunilogcfgopts;

#ifndef SCUNILOGCFGNODE_LINKED_LIST
#define SCUNILOGCFGNODE_LINKED_LIST		((size_t) -1)
#endif

enum scunilogcfgnode_valuetype
{
	scunilogval_pstring,
	scunilogval_pvoid,
	scunilogval_uint,										// No pointer.
	scunilogval_size										// No pointer.
};
typedef enum scunilogcfgnode_valuetype	scunilogvaltype;

/*
	A single config node.

	If nChildren is SCUNILOGCFGNODE_LINKED_LIST, pChildren points to a singly-linked list instead
	of an array.

	String values are stored NUL-terminated and lenValue is set to strlen (szValue), meaning that
	the size of the value data is lenValue + 1. For all other data lenValue is identical to the
	allocated size.
*/
typedef struct scunilogcfgnode
{
	struct scunilogcfgnode	*pParent;						// If NULL, this is the root.
	char					*szKeyName;
	size_t					lenKeyName;
	scunilogvaltype			valtype;
	union uval
	{
		char				*szValue;
		void				*pvValue;
		size_t				stValue;
		uint64_t			uiValue;
	} val;
	size_t					lenValue;
	struct scunilogcfgnode	*pChildren;
	size_t					nChildren;
	struct scunilogcfgnode	*pNext;							// NULL if nChildren is
															//	SCUNILOGCFGNODE_LINKED_LIST.
} SCUNILOGCFGNODE;

/*
	Errors that can be returned.
*/
enum cunilogcfgerrors
{
	cunilogcfgError,
	cunilogcfgErrorNoIdea
};
typedef enum cunilogcfgerrors	cunilogCfgError;

/*
	Structure to return a parse error.
*/
typedef struct cunilogcfgerr
{
	size_t					errLine;						// Line number, starts at 1.
	size_t					errColumn;						// Column, starts at 1.
	cunilogCfgError			err;							// Error code.
} CUNILOGCFGERR;

/*
	The parser status structure.
*/
typedef struct cunilogcfgparserstatus
{
	// Positions.
	char					*szCfg;							// Pointer to the next octet.
	size_t					lnCfg;							// Remaining length in octets.
	size_t					linNum;							// Line number; starts at 1.
	size_t					colNum;							// Column number; starts at 1.

	// Current status.
	char					litChr;							// First and last octet of a literal.
	size_t					litNum;							// Amount of open literals.
	size_t					mulCom;							// Amount of open multi-line comments.

	// Error.
	CUNILOGCFGERR			cfgErr;
} CUNILOGCFGPARSERSTATUS;

/*
	ParseCunilogRootConfigData

	Parses the config data szConfigData points to up to a length of lenData and returns a
	newly allocated SCUNILOGCFGNODE root structure.

	In case of an error the function returns NULL and fills the members of the CUNILOGCFGERR
	structure pErr points to accordingly to provide some clue about the nature of the error.
*/
SCUNILOGCFGNODE *ParseCunilogRootConfigData (char *szConfigData, size_t lenData, CUNILOGCFGERR *pErr)
;

/*
	DoneCunilogRootConfigData

	Deallocates the resources used by the SCUNILOGCFGNODE root structure cfg points to.
*/
void DoneCunilogRootConfigData (SCUNILOGCFGNODE *cfg)
;

/*
	CreateSCUNILOGINI

	Parses the ini buffer szIniBuf points to with length of lnIniBuf. If lnIniBuf is
	USE_STRLEN, the function uses strlen () to obtain it. Otherwise, the buffer does not
	need to be NUL-terminated.

	The structure pCunilogIni receives the structure data of the ini buffer. Use one of the
	CunilogGetIni... () functions to obtain data from it.

	The function returns true on success, false otherwise. When the function returns false,
	the members errLineNumber, errCharNumber, and errAbsPosition of the SCUNILOGINI structure
	pCunilogIni point to contain the position at which the buffer couldn't be parsed.
	Additionally, the boolean bParseFail is set to true.

	The caller does not need to initialise the SCUNILOGINI structure pCunilogIni points
	to beforehand.
*/
bool CreateSCUNILOGINI (SCUNILOGINI *pCunilogIni, const char *szIniBuf, size_t lnIniBuf)
;

/*
	DoneSCUNILOGINI

	Frees the resources taken by the SCUNILOGINI structure pCunilogIni points to.
	
	After this function has been called on the structure, none of the
	CunilogGetIni... () functions can be used on it anymore until it is initialised again
	with CreateSCUNILOGINI ().
*/
void DoneSCUNILOGINI (SCUNILOGINI *pCunilogIni)
;

/*
	CunilogGetIniValueFromKey

	Retrieves the value of a key that belongs to section szSection..

	pLen			A pointer to a size_t that receives the length of the returned string.
					If this parameter is NULL, the function does not provide the length
					of the returned string. Note that the string value the function
					returns is not NUL-terminated, hence it is not recommended to set this
					parameter NULL.

	szSection		The name of the section the key belongs to. Keys do not necessarily
					belong to a section. To obtain a key that is not part of a section,
					set szSection to NULL and lnSection to 0.

	lnSection		The length of the section name szSection. Use USE_STRLEN for the
					function to call strlen (szSection). Otherwise the name does not
					need to be NUL-terminated.

	szKey			The name of the key whose value is to be retrieved. This parameter
					cannot be NULL.

	lnKey			The length of the key name. If USE_STRLEN, the function uses strlen ()
					to obtain it. Otherwise the name does not need to be NUL-terminated.

	pCunilogIni		A pointer to an SCUNILOGINI structure. The structure must have been
					initialised with CreateSCUNILOGINI ().

	The function returns a pointer to the value of the key, without quotation markers.
	This string is not NUL-terminated. If pLen is not NULL, the function provides the length
	of the returned string at the address it points to.

	The function returns NULL if the key does not exist. When the function returns NULL,
	the address pLen points to is not changed.
*/
const char *CunilogGetIniValueFromKey	(
				size_t			*pLen,
				const char		*cunilog_restrict szSection,	size_t	lnSection,
				const char		*cunilog_restrict szKey,		size_t	lnKey,
				SCUNILOGINI		*pCunilogIni
										)
;

/*
	TestCunilogCfgParser

	Test function for the module.
*/
#ifdef CUNILOG_BUILD_CFG_PARSER_TEST_FNCT
	bool TestCunilogCfgParser (void);
#else
	#define TestCunilogCfgParser()
#endif

EXTERN_C_END

#else
	#define TestCunilogCfgParser()
#endif														// Of #ifdef CUNILOG_BUILD_CFG_PARSER.

#endif														// Of #ifndef CUNILOGCFGPARSER_H.
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
/****************************************************************************************

	File:		cunilogstructs.h
	Why:		Structures for cunilog.
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

#ifndef CUNILOGSTRUCTS_H
#define CUNILOGSTRUCTS_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./cunilogdefs.h"
	#include "./cunilogerrors.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./DLLimport.h"
		#include "./SingleBits.h"
		#include "./ubf_times.h"
		#include "./membuf.h"
		#include "./bulkmalloc.h"
		#include "./VectorC.h"
		#include "./platform.h"
		#include "./strintuint.h"
		#include "./strnewline.h"
		#include "./strhexdump.h"
		#include "./dbgcountandtrack.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/DLLimport.h"
		#include "./../pre/SingleBits.h"
		#include "./../datetime/ubf_times.h"
		#include "./../mem/membuf.h"
		#include "./../mem/bulkmalloc.h"
		#include "./../mem/VectorC.h"
		#include "./../pre/platform.h"
		#include "./../string/strintuint.h"
		#include "./../string/strnewline.h"
		#include "./../string/strhexdump.h"
		#include "./../dbg/dbgcountandtrack.h"
	#endif

#endif

/*
	For testing only.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
//#define CUNILOG_BUILD_SINGLE_THREADED_ONLY
#endif

#ifdef OS_IS_WINDOWS
	#include <Windows.h>
#else
	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		#include <semaphore.h>
		#include <pthread.h>
	#endif
#endif

/*
	Build options.

	CUNILOG_BUILD_SINGLE_THREADED_ONLY			Builds for a single-threaded application only.
												Code for other types than unilogSingleThreaded
												won't be built.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#ifdef CUNILOG_BUILD_MULTI_THREADED
	#error Either CUNILOG_BUILD_SINGLE_THREADED_ONLY or CUNILOG_BUILD_MULTI_THREADED can be defined but not both.
	#endif
	#ifdef CUNILOG_BUILD_MULTI_PROCESSES
	#error Only CUNILOG_BUILD_SINGLE_THREADED_ONLY or UNILOG_BUILD_MULTI_PROCESSES can be defined but not both.
	#endif
#endif

/*
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, CUNILOG_BUILD_SINGLE_THREADED_QUEUE
	can be defined additionally to provide a target queue. This enables some queue functions.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_QUEUE
//#define CUNILOG_BUILD_SINGLE_THREADED_QUEUE
#endif

/*
	Currently not planned.

#ifdef CUNILOG_BUILD_MULTI_THREADED
	#ifdef CUNILOG_BUILD_MULTI_PROCESSES
	#error Only CUNILOG_BUILD_MULTI_THREADED or CUNILOG_BUILD_MULTI_PROCESSES can be defined but not both.
	#endif
#endif
#ifdef CUNILOG_BUILD_MULTI_PROCESSES
#endif
*/

/*
	If we're building a Windows DLL we got to turn all our features on.
	Otherwise we'd have to maintain different .def files depending on the build
	options defined.
*/
#ifdef CUNILOG_BUILD_SHARED_LIBRARY

	#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#undef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#undef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	#undef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	#undef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	#endif

	#ifdef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	#undef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	#endif

#endif


BEGIN_C_DECLS

/*
	The constants for the log file extension. We got this in UTF-8
	(szCunilogLogFileNameExtension) and Windows UTF-16 (wcCunilogLogFileNameExtension).
	The constant lenCunilogLogFileNameExtension is the length in characters (not octets!).
*/
CUNILOG_DLL_IMPORT extern const char	*szCunilogLogFileNameExtension;	// ".log"
CUNILOG_DLL_IMPORT extern const wchar_t	*wcCunilogLogFileNameExtension;	// ".log"
CUNILOG_DLL_IMPORT extern const size_t	lenCunilogLogFileNameExtension;	// ".log"
CUNILOG_DLL_IMPORT extern const size_t	sizCunilogLogFileNameExtension;	// ".log" + NUL

/*
	enum cunilogtype

	Specifies the application type of a cunilog target and how processing events is
	protected. These values are valid for a single target.
	Applications however can in theory work with an arbitrary number of targets, even if
	the targets are configured differently.


	cunilogSingleThreaded

	Only a single thread from one instance of the current application can safely write out
	logging information. Cunilog does not apply any concurrency protection.
	Writing logging information from more than a single thread, another instance of the
	same application, or from a different application is not supported and resulta in data
	corruption and application crashes. In a best case it may only lead to unusable
	logging information.

	Every logging function blocks as it executes the list of processors before returning.


	cunilogSingleThreadedSeparateLoggingThread

	Identical to cunilogSingleThreaded but the application must be built with multi-threading
	support. The process of writing out logging information (i.e. executing the list of
	logging processors) takes place in a separate thread.
	Calling logging functions from more than a single thread, another instance of the
	same application, or from a different application is not supported and results in
	data corruption and application crashes. In a best case it may only lead to unusable
	logging information.
	
	However, due to how this is currently implemented, some of these restrictions do not apply
	right now because cunilogSingleThreadedSeparateLoggingThread is actually identical to
	unilogMultiThreadedSeparateLoggingThread. Since this might and most likely will change in
	future versions of the software, use cunilogMultiThreadedSeparateLoggingThread to be safe.


	cunilogSingleThreadedQueueOnly

	This type is also single-threaded and identical to cunilogSingleThreaded with the
	exception that it doesn't write out anything. No logging processors are created nor
	executed. Events are accumulated in a singly-linked event list instead.

	This is meant as a replacement target when the real target is not available (yet). For
	instance, an application might choose to read some parameters of the logging target from
	a configuration file or obtain these parameters through other means, maybe from
	command-line arguments. This means the actual logging target can only be created once
	these parameters are available. You can use a cunilogSingleThreadedQueueOnly or a
	cunilogMultiThreadedQueueOnly target as a dummy target to log to until the real target
	can be created with the correct parameters. After the real target has been created,
	the entire queue can be moved over to the new target, and no event is lost.


	cunilogMultiThreaded

	Multiple threads from a single instance of the current application can safely write out
	logging information. Cunilog provides necessary concurrency protection for this case but
	does not protect logging information from being overwritten/destroyed by other processes.
	Any logging function called from any thread blocks as it works its way through the list of
	processors before releasing its lock and returning.


	cunilogMultiThreadedSeparateLoggingThread

	Identical to cunilogMultiThreaded but the process of writing out logging information (i.e.
	executing the list of processors) takes place in its own thread. Logging functions do
	not block. This is the preferred mode for most multi-threaded applications.


	cunilogMultiThreadedQueueOnly

	This is a mix of cunilogSingleThreadedQueueOnly, cunilogMultiThreaded, and
	cunilogMultiThreadedSeparateLoggingThread. This type doesn't write out anything. No logging
	processors are executed or even created. Events are instead accumulated in a singly-linked
	event list. The difference to cunilogSingleThreadedQueueOnly is that a target of type
	cunilogMultiThreadedQueueOnly can be logged to from several threads because the list is
	protected by a mutex (POSIX) or critical section object (Windows).


	cunilogMultiProcesses

	Logging information is fully protected and can be written from different threads as well
	as from different processes. This is currently not supported and hasn't been implemented
	yet.
*/
enum cunilogtype
{
		cunilogSingleThreaded
	,	cunilogSingleThreadedSeparateLoggingThread
	,	cunilogSingleThreadedQueueOnly
	,	cunilogMultiThreaded
	,	cunilogMultiThreadedSeparateLoggingThread
	,	cunilogMultiThreadedQueueOnly
	,	cunilogMultiProcesses
	// Do not add anything below this line.
	,	cunilogTypeAmountEnumValues							// Used for table sizes.
	// Do not add anything below cunilogTypeAmountEnumValues.
};

/*
	The postfix applied to the application name.

	Example for cunilogPostfixMinute:
	"MyApp" + "_" + "YYYY-MM-DD HH_MI"

	Postfixes are ascending by default, meaning that newer logfiles cantain
	higher dates/numbers. For numbers we allow a maximum width of 20 digits,
	which is enough for a uint64_t.
*/
enum cunilogpostfix
{
		cunilogPostfixNone
	,	cunilogPostfixMinute								// "YYYY-MM-DD HH_MI"
	,	cunilogPostfixMinuteT								// "YYYY-MM-DDTHH_MI"
	,	cunilogPostfixHour									// "YYYY-MM-DD HH"
	,	cunilogPostfixHourT									// "YYYY-MM-DDTHH"
	,	cunilogPostfixDay									// "YYYY-MM-DD"
	,	cunilogPostfixDefault = cunilogPostfixDay
	,	cunilogPostfixWeek									// "YYYY-Wnn"
	,	cunilogPostfixMonth									// "YYYY-MM"
	,	cunilogPostfixYear									// "YYYY"

	// Current/active logfile has no postfix, but less recent ones have.
	//	"file.log", "file_YYYY-MM-DD HH_MI.log", etc.
	,	cunilogPostfixLogMinute
	,	cunilogPostfixLogMinuteT
	,	cunilogPostfixLogHour
	,	cunilogPostfixLogHourT
	,	cunilogPostfixLogDay
	,	cunilogPostfixLogWeek
	,	cunilogPostfixLogMonth
	,	cunilogPostfixLogYear

	//	"file.log", "file.log.1", "file.log.2", etc.
	,	cunilogPostfixDotNumberMinutely						// ".<number>", rotation every minute.
	,	cunilogPostfixDotNumberHourly						// ".<number>", rotation every hour.
	,	cunilogPostfixDotNumberDaily
	,	cunilogPostfixDotNumberWeekly
	,	cunilogPostfixDotNumberMonthly
	,	cunilogPostfixDotNumberYearly
	// Do not add anything below this line.
	,	cunilogPostfixAmountEnumValues						// Used for table sizes.
	// Do not add anything below cunilogPostfixAmountEnumValues.
};

/*
	The possible processors. This is the member task of a CUNILOG_PROCESSOR structure.


	cunilogProcessNoOperation

	This is a dummy processor and does nothing.


	cunilogProcessEchoToConsole

	Echoes/outputs the event line to the console


	cunilogProcessUpdateLogFileName

	Updates the name of the logfile. This probably shouldn't be a processor but if no logfile
	is required, not having this processor can save a few CPU cycles.


	cunilogProcessWriteToLogFile

	Carries out the actual write operation to the logfile. The member pData must be NULL.
	If the file doesn't exist yet it is created and opened for writing. If the logfile exists,
	it is opened for writing. The file is closed when no longer required.


	cunilogProcessFlushLogFile

	Flushes the logfile. The member pData must be NULL.


	cunilogProcessRotateLogfiles
	
	A logfile rotator. The member pDate points to a CUNILOG_ROTATION_DATA structure that
	contains details about the rotation.


	cunilogProcessCustomProcessor

	A custom processor. The member pData points to a CUNILOG_CUSTPROCESS structure that
	contains a pointer to a callback function to carry out the actual task of the processor.


	cunilogProcessTargetRedirector

	Redirects to another target. The member pData points to a fully initialised CUNILOG_TARGET
	structure to which events are redirectred to. After the redirection further processing
	within the current target is suppressed, meaning that this is the last processor.

	If pData is NULL, no redirection takes place and the remaining processors are worked
	through as usual. Since this is most likely not what the caller intended, a debug
	assertion expects pData not being NULL.
*/
enum cunilogprocesstask
{
		cunilogProcessNoOperation							// Does nothing.
	,	cunilogProcessEchoToConsole							// Echoes to console.
	,	cunilogProcessUpdateLogFileName						// Updates full path to logfile.
	,	cunilogProcessWriteToLogFile						// Writes to logfile.
	,	cunilogProcessFlushLogFile							// Flushes the logfile.
	,	cunilogProcessRotateLogfiles						// Rotates logfiles.
	,	cunilogProcessCustomProcessor						// An external/custom processor.
	,	cunilogProcessTargetRedirector						// Redirect to different target.
	,	cunilogProcessTargetFork							// Fork the event to another target.
	// Do not add anything below this line.
	,	cunilogProcessXAmountEnumValues						// Used for table sizes.
	// Do not add anything below cunilogProcessAmountEnumValues.
};

enum cunilogprocessfrequency
{
		cunilogProcessAppliesTo_nEvents						// Threshold is incremented for
															//	each event.
	,	cunilogProcessAppliesTo_nOctets						// Threshold counts the amount of
															//	octets logged.
	,	cunilogProcessAppliesTo_nAlways						// Threshold does not apply; always
															//	processed.
	,	cunilogProcessAppliesTo_SecondChanged				// Processed whenever the second
															//	changes.
	,	cunilogProcessAppliesTo_MinuteChanged				// Processed whenever the minute
															//	changes.
	,	cunilogProcessAppliesTo_HourChanged					// Processed whenever the hour
															//	changes.
	,	cunilogProcessAppliesTo_DayChanged					// Processed whenever the day
															//	changes.
	,	cunilogProcessAppliesTo_WeekChanged					// Processed whenever the week
															//	changes.
	,	cunilogProcessAppliesTo_MonthChanged				// Processed whenever the month
															//	changes.
	,	cunilogProcessAppliesTo_YearChanged					// Processed whenever the year
															//	changes.
	,	cunilogProcessAppliesTo_Auto						// Picks frequency automatically.
};

typedef struct CUNILOG_TARGET CUNILOG_TARGET;
typedef struct cunilog_processor
{
	enum cunilogprocesstask			task;					// What to apply.
	enum cunilogprocessfrequency	freq;					// When to apply
															//	(frequency/theshold type).

	// Trigger threshold and its current value. These are 0-indexed.
	uint64_t						thr;					// Required value of cur before this
															//	processor is applied/run.
	uint64_t						cur;					// The current counter value.

	void							*pData;					// Pointer to processor-specific data.
	uint64_t						uiOpts;					// Option flags. See OPT_CUNPROC_
															//	definitions below.
} CUNILOG_PROCESSOR;

/*
	Option flags for the uiOpts member of a CUNILOG_PROCESSOR structure.
*/
#define OPT_CUNPROC_NONE				(0)
#define OPT_CUNPROC_FORCE_NEXT			SINGLEBIT64 (0)		// Carry on with the next processor
															//	even if this one has not been
															//	processed.
#define OPT_CUNPROC_AT_STARTUP			SINGLEBIT64 (1)		// Executes the processor on startup
															//	by ignoring cunilogprocesstype.
															//	The flag is then cleared.
#define OPT_CUNPROC_ALLOCATED			SINGLEBIT64 (2)		// This processor has been allocated
															//	on the heap and needs to be freed.
#define OPT_CUNPROC_DATA_ALLOCATED		SINGLEBIT64	(3)		// The pData member has been allocated
															//	on the heap and needs to be freed.
#define OPT_CUNPROC_DISABLED			SINGLEBIT64 (4)		// The processor is disabled, i.e.
															//	prevented from being processed.
															//	Carries on with the next processor
															//	unconditionally, just like
															//	OPT_CUNPROC_FORCE_NEXT.

/*
	Macros for some flags.
*/

#define optCunProcHasOPT_CUNPROC_AT_STARTUP(v)			\
	((v) & OPT_CUNPROC_AT_STARTUP)
#define optCunProcClrOPT_CUNPROC_AT_STARTUP(v)			\
	((v) &= ~ OPT_CUNPROC_AT_STARTUP)

#define optCunProcHasOPT_CUNPROC_DISABLED(v)			\
	((v) & OPT_CUNPROC_DISABLED)
#define optCunProcSetOPT_CUNPROC_DISABLED(v)			\
	((v) |= OPT_CUNPROC_DISABLED)
#define optCunProcClrOPT_CUNPROC_DISABLED(v)			\
	((v) &= ~ OPT_CUNPROC_DISABLED)

/*
	A pData structure for a unilogProcessWriteToLogFile or a unilogProcessFlushLogFile processor.
	This probably shouldn't be a structure but leaves room for possible extensions.
*/
typedef struct cunilog_logfile
{
	#ifdef OS_IS_WINDOWS
		HANDLE			hLogFile;
	#else
		FILE			*fLogFile;
	#endif
} CUNILOG_LOGFILE;

/*
	Note that
	cunilogrotationtask_MoveToTrashLogfiles			and
	cunilogrotationtask_MoveToRecycleBinLogfiles	are identical to accomodate for
	Linux or Windows naming preference.
*/
enum cunilogrotationtask
{
		cunilogrotationtask_None							// Ignored. No operation.
	,	cunilogrotationtask_RenameLogfiles					// Rotates by renaming files.
	,	cunilogrotationtask_FScompressLogfiles				// Compress logfiles with the help
															//	of the file system.
	,	cunilogrotationtask_MoveToTrashLogfiles
	,	cunilogrotationtask_MoveToRecycleBinLogfiles = cunilogrotationtask_MoveToTrashLogfiles
	,	cunilogrotationtask_DeleteLogfiles

	// Do not add anything below this line.
	,	cunilogrotationtask_XAmountEnumValues				// Used for table sizes.
	// Do not add anything below cunilogrotationtask_XAmountEnumValues.
};

/*
	A pData structure for a unilogProcessRotateLogfiles processor.
*/
typedef struct cunilog_rotation_data
{
	enum cunilogrotationtask	tsk;						// The task to carry out.
	uint64_t					nIgnore;					// Amount of files/objects/artefacts
															//	to ignore.
	uint64_t					nCnt;						// Counter for nIgnore.
	uint64_t					nMaxToRotate;				// Don't rotate more than this.
															//	Ignored when 0.

	// Source and destiantion path names. Probably not required, at least with NTFS compression.
	SMEMBUF						mbSrcMask;					// Search mask. Only used when
															//	CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK
															//	set. See option flags below.
	SMEMBUF						mbDstFile;					// Name of file to rotate (destination
															//	file name). Only used when
															//	CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE
															//	set. See option flags below.
	CUNILOG_TARGET				*plogCUNILOG_TARGET;		// Pointer to a logging target.
															//	If this is NULL, the processor's
															//	target is logged to, without
															//	rotation.
	uint64_t					uiFlgs;						// Option flags. See below.
} CUNILOG_ROTATION_DATA;

/*
	CUNILOG_ROTATION_DATA option flags.
*/
#define CUNILOG_ROTATOR_FLAG_NONE							(0)

// Used by some rotators to distinguish if they need further initialisation.
#define CUNILOG_ROTATOR_FLAG_INITIALISED		SINGLEBIT64 (0)

// The rotator makes use of the mbSrcMask member. Without this flag, the rotator uses the
//	member mbLogFileMask of the CUNILOG_TARGET structure.
#define CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK		SINGLEBIT64 (1)

// The rotator makes use of the mbDstFile member. Without this flag, the rotator uses the
//	member mbFilToRotate of the CUNILOG_TARGET structure
#define CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE		SINGLEBIT64 (2)

/*
	Macros for checking, setting, and clearing some of the flags above.
*/
#define cunilogHasRotatorFlag_USE_MBSRCMASK(prd)		\
	((prd)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogSetRotatorFlag_USE_MBSRCMASK(prd)		\
	((prd)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)
#define cunilogClrRotatorFlag_USE_MBSRCMASK(prd)		\
	((prd)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBSRCMASK)

#define cunilogHasRotatorFlag_USE_MBDSTFILE(prd)		\
	((prd)->uiFlgs & CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogSetRotatorFlag_USE_MBDSTFILE(prd)		\
	((prd)->uiFlgs |= CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)
#define cunilogClrRotatorFlag_USE_MBDSTFILE(prd)		\
	((prd)->uiFlgs &= ~ CUNILOG_ROTATOR_FLAG_USE_MBDSTFILE)


// Value of member nMaxToRotate of a CUNILOG_ROTATION_DATA structure to be obtained
//	during initialisation.
#ifndef CUNILOG_MAX_ROTATE_AUTO
#define CUNILOG_MAX_ROTATE_AUTO			(UINT64_MAX)
#endif

/*
	Initialisers for CUNILOG_ROTATION_DATA structures.

	Note that
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_TRASH()			and
	CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN()	are identical.
*/
/*
	
*/
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES \
{														\
	cunilogrotationtask_RenameLogfiles,					\
	0, 0, CUNILOG_MAX_ROTATE_AUTO,						\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}

/*
	Argument k is the amount of logfiles to keep/not touch.
*/
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_FS_COMPRESS(k)\
{														\
	cunilogrotationtask_FScompressLogfiles,				\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_TRASH(k)\
{														\
	cunilogrotationtask_MoveToTrashLogfiles,			\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_MOVE_TO_RECYCLE_BIN(k)\
{														\
	cunilogrotationtask_MoveToRecycleBinLogfiles,		\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}
#define CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_DELETE(k)\
{														\
	cunilogrotationtask_DeleteLogfiles,					\
	(k), 0, CUNILOG_MAX_ROTATE_AUTO,					\
	SMEMBUF_INITIALISER, SMEMBUF_INITIALISER,			\
	NULL,												\
	CUNILOG_ROTATOR_FLAG_NONE							\
}

/*
	Initialisers for processor tasks.
*/
#define CUNILOG_INIT_DEF_ECHO_PROCESSOR					\
{														\
	cunilogProcessEchoToConsole,						\
	cunilogProcessAppliesTo_nAlways,					\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
#define CUNILOG_INIT_DEF_UPDATELOGFILENAME_PROCESSOR	\
{														\
	cunilogProcessUpdateLogFileName,					\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
/*
	Argument plf is a pointer to a CUNILOG_LOGFILE structure.
*/
#define CUNILOG_INIT_DEF_WRITETTOLOGFILE_PROCESSOR		\
{														\
	cunilogProcessWriteToLogFile,						\
	cunilogProcessAppliesTo_nAlways,					\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_NONE									\
}
#define CUNILOG_INIT_DEF_FLUSHLOGFILE_PROCESSOR			\
{														\
	cunilogProcessFlushLogFile,							\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	NULL,												\
	OPT_CUNPROC_FORCE_NEXT								\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_RenameLogfiles. Such a structure can
	be initialised with the CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_RENAME_LOGFILES()
	macro.
*/
#define CUNILOG_INIT_DEF_RENAMELOGFILES_PROCESSOR(p)	\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),												\
	OPT_CUNPROC_NONE									\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_FScompressLogfiles. Such a structure can
	be initialised with the CUNILOG_INIT_DEF_CUNILOG_ROTATION_DATA_FS_COMPRESS()
	macro.
*/
#define CUNILOG_INIT_DEF_LOGFILESFSCOMPRESS_PROCESSOR(p)\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),												\
	OPT_CUNPROC_NONE									\
}
/*
	Argument p is a pointer to a CUNILOG_ROTATION_DATA structure with member
	tsk set to cunilogrotationtask_MoveToRecycleBinLogfiles.
*/
#define CUNILOG_INIT_DEF_LOGFILESMOVETOTRASH_PROCESSOR(p)\
{														\
	cunilogProcessRotateLogfiles,						\
	cunilogProcessAppliesTo_Auto,						\
	0, 0,												\
	(p),												\
	OPT_CUNPROC_NONE									\
}


/*
	FillCUNILOG_PROCESSOR

	Function/macro to initialise a CUNILOG_PROCESSOR structure. The data (pData) member
	is set to NULL and the member uiOpts to OPT_CUNPROC_NONE, which means no option flags
	are set. The caller is responsible for setting those members to their desired values
	afterwards.
*/
#define FillCUNILOG_PROCESSOR(cup, task,				\
								freq, thrs)				\
	ubf_assert_non_NULL (cup);							\
	(cup)->task		= task;								\
	(cup)->freq		= freq;								\
	(cup)->thr		= thrs;								\
	(cup)->cur		= 0;								\
	(cup)->pData	= NULL;								\
	(cup)->uiOpts	= OPT_CUNPROC_NONE;

#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	typedef struct CUNILOG_EVENT CUNILOG_EVENT;
#else
	typedef struct cunilog_locker
	{
		#ifdef OS_IS_WINDOWS
			CRITICAL_SECTION	cs;
		#else
			pthread_mutex_t		mt;
		#endif
		#ifdef CUNILOG_BUILD_DEBUG_TEST_LOCKER
			bool				bInitialised;
		#endif
	} CUNILOG_LOCKER;

	typedef struct cunilog_semaphore
	{
		#ifdef OS_IS_WINDOWS
			HANDLE				hSemaphore;
		#else
			sem_t				tSemaphore;
		#endif
	} CUNILOG_SEMAPHORE;

	typedef struct cunilog_thread
	{
		#ifdef OS_IS_WINDOWS
			HANDLE				hThread;
		#else
			pthread_t			tThread;
		#endif
	} CUNILOG_THREAD;

	typedef struct CUNILOG_EVENT CUNILOG_EVENT;
	typedef struct cunilog_queue_base
	{
		CUNILOG_EVENT			*first;						// First event.
		CUNILOG_EVENT			*last;						// Last event.
		size_t					num;						// Current amount of queue
															//	elements.
	} CUNILOG_QUEUE_BASE;
#endif

/*
	Textual representations of date/timestamp formats for an event/event line.
	The default is ""YYYY-MM-DD HH:MI:SS.000+01:00", followed by a space character.
	The value unilogEvtTS_ISO8601T follows the ISO 8601 specification by separating
	date and time with a 'T'.

	The value cunilogEvtTS_ISO8601_3spc adds 3 spaces instead of one, and so does the
	value cunilogEvtTS_ISO8601T_3spc but with a 'T' between date and time.

	Value cunilogEvtTS_NCSADT denotes a terribly hugly date/timestamp format webservers
	introduced just after the dinosaurs went extinct 66 million years ago. Worst part of
	this bit of history is probably that the date/timestamp is not the first column of an
	event line. See Common Log Format (https://en.wikipedia.org/wiki/Common_Log_Format)
	for details on the scope of the horror.
*/
enum cunilogeventTSformat
{
		cunilogEvtTS_ISO8601								// "YYYY-MM-DD HH:MI:SS.000+01:00 "
	,	cunilogEvtTS_Default		= cunilogEvtTS_ISO8601
	,	cunilogEvtTS_ISO8601T								// "YYYY-MM-DDTHH:MI:SS.000+01:00 "
	,	cunilogEvtTS_ISO8601_3spc							// "YYYY-MM-DD HH:MI:SS.000+01:00   "
	,	cunilogEvtTS_ISO8601T_3spc							// "YYYY-MM-DDTHH:MI:SS.000+01:00   "
	,	cunilogEvtTS_NCSADT									// "[10/Oct/2000:13:55:36 -0700] "
	// Do not add anything below this line.
	,	cunilogEvtTS_AmountEnumValues						// Used for table sizes.
	// Do not add anything below cunilogEvtTS_AmountEnumValues.
};

enum cunilogRunProcessorsOnStartup
{
		cunilogRunProcessorsOnStartup
	,	cunilogDontRunProcessorsOnStartup
	// Do not add anything below this line.
	,	cunilogRunProcessors_AmountEnumValues				// Used for table sizes.
	// Do not add anything below cunilogRunProcessors_AmountEnumValues.
};
typedef enum cunilogRunProcessorsOnStartup runProcessorsOnStartup;

/*
	SCUNILOGDUMP

	Holds the parameter structures for binary/octal/decimal/hex dumps.
*/
typedef struct scunilogdump
{
	void		*dump_prs;									// Pointer to a SHEX_DUMP_SAN structure.
	void		*dump_sns;									// Pointer to a SHEX_DUMP_SAN structure.
	SMEMBUF		mbDumpHeader;
	size_t		lnDumpHeader;
} SCUNILOGDUMP;

/*
	Structure for the vector that holds the filenames.
	A single char * would probably do if no length information is required.
*/
typedef struct cunilog_fls
{
	char	*chFilename;
	size_t	stFilename;
} CUNILOG_FLS;
typedef vec_t(CUNILOG_FLS) vec_cunilog_fls;

/*
	Base folder for a relative path or path if no path at all is given.

	These are the possible enumeration values of the parameter relLogPath of the
	CUNILOG_TARGET initialisation functions.

	cunilogPath_isAbsolute

	The path parameter cannot be NULL, and it cannot be a relative path.


	cunilogPath_relativeToExecutable
	
	If path is a relative path, it is assumed to be relative to the path of
	the executable file. If the path is NULL, the path of the executable file is used.


	cunilogPath_relativeToCurrentDir

	If the path parameter is a relative path, the path is assumed to be relative to the
	current working directory. If path is NULL, the current working directory is used.
	The current working directory is obtained by the CUNILOG_TARGET initialisation functions
	and stays constant during the lifetime of this CUNILOG_TARGET. It is therefore safe for
	the application to change this directory any time after the initialisation function
	returned. Or, an application could set the current working directory to the desired
	szLogPath, call an CUNILOG_TARGET initialisation function with szLogPath set to NULL.


	cunilogPath_relativeToHomeDir

	If path is a relative path, the path is assumed to be relative to the current user's
	home folder. If path is NULL, the user's home directory is used.
*/
enum cunilogRelPath
{
		cunilogPath_isAbsolute
	,	cunilogPath_relativeToExecutable
	,	cunilogPath_relativeToCurrentDir
	,	cunilogPath_relativeToHomeDir
	// Do not add anything below this line.
	,	cunilogPath_XAmountEnumValues						// Used for sanity checks.
	// Do not add anything below unilogRotationAmountEnumValues.
};
typedef enum cunilogRelPath enCunilogRelPath;

/*
	Structure to leave some information for the next processor.
*/
typedef struct scunilognpi
{
	SMEMBUF							smbRotMask;				// File search mask/glob pattern the
															//	next processor should use to
															//	enumerate files. Only required for
															//	rotators.
	size_t							lenRotMask;				// The length, excluding NUL, of
															//	smbRotMask; If this is 0,
															//	smbRotMask is unused/uninitialised.
	uint64_t						nIgnoredTotal;			// Ignored so far. Only if lenRotMask
															//	is 0.
	vec_cunilog_fls					*pNextVecCunilogFls;	// The next file to process. If this
															//	is NULL, the next rotator
															//	needs to start from scratch.
} SCUNILOGNPI;

#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	/*
		Possible return values of the error/fail callback function.

		cunilogErrCB_ignore					Just carry on as if nothing happened.			

		cunilogErrCB_next_processor			The current processor is cancelled and the next
											processor is going to be processed. The error/fail
											callback function is called again for the next
											processor that fails, even for the same event.

		cunilogErrCB_next_event				The current event is cancelled. No other processors
											are run.

		cunilogErrCB_shutdown				The Cunilog target is shutdown.

		cunilogErrCB_cancel					The Cunilog target is cancelled.
	*/
	enum enErrCBretval
	{
			cunilogErrCB_ignore
		,	cunilogErrCB_next_processor
		,	cunilogErrCB_next_event
		,	cunilogErrCB_shutdown
		,	cunilogErrCB_cancel
		// Do not add anything below this line.
		,	cunilogErrCB_AmountEnumValues						// Used for sanity checks.
		// Do not add anything below cunilogErrCB_AmountEnumValues.
	};
	typedef enum enErrCBretval errCBretval;

	/*
		Error/fail callback function.
	*/
	typedef errCBretval (*cunilogErrCallback)	(
						CUNILOG_ERROR				error,
						CUNILOG_PROCESSOR			*cup,
						CUNILOG_EVENT				*pev
												);
#endif

typedef struct cunilog_rotator_args CUNILOG_ROTATOR_ARGS;

/*
	The type/format of an event severity level.
*/
enum cunilogeventseveritytpy
{
		cunilogEvtSeverityTypeChars3							// "EMG", "DBG"... (default).
	,	cunilogEvtSeverityTypeChars5							// "EMRGY", "DEBUG"...
	,	cunilogEvtSeverityTypeChars9							// "EMERGENCY", "DEBUG    "...
	,	cunilogEvtSeverityTypeChars3InBrackets					// "[EMG]", "[DBG]"...
	,	cunilogEvtSeverityTypeChars5InBrackets					// "[EMRGY]", "[DEBUG]"...
	,	cunilogEvtSeverityTypeChars9InBrackets					// "[EMERGENCY]", "[DEBUG    ]"...
	,	cunilogEvtSeverityTypeChars5InTightBrackets				// "[FAIL] "...
	,	cunilogEvtSeverityTypeChars9InTightBrackets				// "[DEBUG]    "...
	// Do not add anything below this line.
	,	cunilogEvtSeverityTypeXAmountEnumValues					// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityTypeXAmountEnumValues.
};
typedef enum cunilogeventseveritytpy cueventsevfmtpy;

/*
	The default event severity type.
*/
extern cueventsevfmtpy cunilogEvtSeverityTypeDefault;

/*
	Default ANSI escape colour output for the cunilog_puts... and cunilog_printf...
	type functions.
*/
extern bool bUseCunilogDefaultOutputColour;

/*
	SUNILOGTARGET

	The base config structure for using cunilog. Do not alter any of its members directly.
	Always use the functions provided to alter its members.
*/
typedef struct CUNILOG_TARGET
{
	enum cunilogtype				culogType;
	enum cunilogpostfix				culogPostfix;
	uint64_t						uiOpts;
	SMEMBUF							mbLogPath;				// The logging folder/path to logfiles.
															//	On Windows, its last character is a
															//	backslash. On POSIX, its last character
															//	is a forward slash.
	size_t							lnLogPath;				// Its length excl. NUL terminator.
	SMEMBUF							mbAppName;				// Plain application name. Not NUL-terminated.
	size_t							lnAppName;				// Its length.
	#ifdef PLATFORM_IS_POSIX
		SMEMBUF						mbLogFold;				// The logging folder/path to logfiles.
															//	Same as mbLogPath but NUL-terminated
															//	and without slash at the end.
		size_t						lnLogFold;				// Its length exl. NUL terminator.
	#endif
	SMEMBUF							mbLogfileName;			// Path and name of current log file.
	char							*szDateTimeStamp;		// Points inside mbLogfileName.buf.pch.
	char							cPrevDateTimeStamp [LEN_ISO8601DATEHOURANDMINUTE];
	SMEMBUF							mbLogFileMask;			// The search mask for log files. It
															//	does not include the path.
	size_t							lnLogFileMask;			// Its length.
	SMEMBUF							mbFilToRotate;			// The file obtained by the cb function.
	size_t							stFilToRotate;			// Its length including the NUL terminator.
	SMEMBUF							mbLogEventLine;			// Buffer that holds the event line.
	size_t							lnLogEventLine;			// The current length of the event line.

	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
		SMEMBUF						mbColEventLine;			// Buffer that holds the coloured
															//	event line.
		size_t						lnColEventLine;			// The current length of the coloured
															//	event line.
	#endif

	DBG_DEFINE_CNTTRACKER(evtLineTracker)					// Tracker for the size of the event
															//	line.

	SCUNILOGNPI						scuNPI;					// Information for the next processor.
	CUNILOG_PROCESSOR				**cprocessors;
	unsigned int					nprocessors;

	#if defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY) && defined (CUNILOG_BUILD_SINGLE_THREADED_QUEUE)
		CUNILOG_QUEUE_BASE			qu;						// The actual event queue.
	#else
		CUNILOG_LOCKER				cl;						// Locker for events queue.
		CUNILOG_SEMAPHORE			sm;						// Semaphore for event queue.
		CUNILOG_QUEUE_BASE			qu;						// The actual event queue.
		CUNILOG_THREAD				th;						// The separate logging thread.

		size_t						nPendingNoRotEvts;		// Amount of currently pending non-
															//	rotation events.

		size_t						nPausedEvents;			// Amount of events queued because
															//	the logging thread is/was paused.
	#endif

	enum cunilogeventTSformat		unilogEvtTSformat;		// The format of an event timestamp.
	newline_t						unilogNewLine;
	CUNILOG_LOGFILE					logfile;
	SBULKMEM						sbm;					// Bulk memory block.
	vec_cunilog_fls					fls;					// The vector with str pointers to
															//	the files to rotate within sbm.
	// We're not using the configurable dump anymore.
	//SCUNILOGDUMP					*psdump;				// Holds the dump parameters.
	ddumpWidth						dumpWidth;

	cueventsevfmtpy					evSeverityType;			// Format of the event severity.

	CUNILOG_ERROR					error;
	#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
		cunilogErrCallback			errorCB;				// Error/fail callback function.
	#endif
	CUNILOG_ROTATOR_ARGS			*prargs;				// Current rotator arguments.
} CUNILOG_TARGET;

/*
	Internal option flags for the uiOpts member of a CUNILOG_TARGET structure.
	These should not be changed by callers/users.
*/

// The initialiser.
#define CUNILOGTARGET_NO_FLAGS					(0)

// Event queue is shutting down or has shut down already.
//	This flags prevents further logging.
#define CUNILOGTARGET_SHUTDOWN_INITIATED		SINGLEBIT64 (0)

// Separate logging thread has shut down.
#define CUNILOGTARGET_SHUTDOWN_COMPLETE			SINGLEBIT64 (1)

// The structure has been allocated on the heap. This is for DoneSUNILOGTARGET ()
//	to deallocate it.
#define CUNILOGTARGET_ALLOCATED					SINGLEBIT64 (2)

// The filename of the log file has been allocated on the heap.
#define CUNILOGTARGET_LOGPATH_ALLOCATED			SINGLEBIT64 (3)

// The application name has been allocated on the heap.
#define CUNILOGTARGET_APPNAME_ALLOCATED			SINGLEBIT64 (4)

// The entire path plus name of the logfile has been allocated on the heap.
#define CUNILOGTARGET_LOGFILE_ALLOCATED			SINGLEBIT64 (5)

// The file mask.
#define CUNILOGTARGET_LOGF_MASK_ALLOCATED		SINGLEBIT64 (6)

// The (complete) filename of the file to rotate.
#define CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED	SINGLEBIT64 (7)

// The array of pointers to processors.
#define CUNILOGTARGET_PROCESSORS_ALLOCATED		SINGLEBIT64 (8)

// Run all processors on startup, independent of their individual flags.
#define CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP	SINGLEBIT64 (9)

// The filesystem that holds the log files doesn't return filenames in
//	descending alphabetic order.
#define CUNILOGTARGET_FS_NEEDS_SORTING			SINGLEBIT64 (10)

#define CUNILOGTARGET_FLS_IS_SORTED				SINGLEBIT64 (11)

// The "file.log.1" (dot number postfix) requires this.
//#define CUNILOGTARGET_NEEDS_NUMBER_SORTING		SINGLEBIT64 (12)

// The elements of the member fls (a vecotr) are in reversed order.
#define CUNILOGTARGET_FLS_REVERSED				SINGLEBIT64 (13)

// The separate logging thread, if one exists, is paused.
#define CUNILOGTARGET_PAUSED					SINGLEBIT64 (14)

// Debug versions ensure that one of the initialisation function has been called.
#ifdef DEBUG
	#define CUNILOGTARGET_INITIALISED			SINGLEBIT64 (15)
	#define cunilogSetTargetInitialised(pt)				\
			((pt)->uiOpts |= CUNILOGTARGET_INITIALISED)
	#define cunilogIsTargetInitialised(pt)				\
			((pt)->uiOpts & CUNILOGTARGET_INITIALISED)
#else
	#define cunilogSetTargetInitialised(pt)	(true)
	#define cunilogIsTargetInitialised(pt)	(true)
#endif

// The callback function errorCB is called as often as possible,
//	even when there's no error. Used for tests.
//	Requires CUNILOG_BUILD_WITH_TEST_ERRORCB.
//	Ignored when CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
//	is defined.
//	Error code is usually one of the CUNILOG_ERROR_TEST_ definitions
//	in cunilogerrors.h.
#define CUNILOGTARGET_ALWAYS_CALL_ERRORCB		SINGLEBIT64 (16)

// Debug flag when the queue is locked. To be removed in the future.
#define CUNILOGTARGET_DEBUG_QUEUE_LOCKED		SINGLEBIT64 (20)

#define cunilogTargetSetShutdownInitiatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_SHUTDOWN_INITIATED)
#define cunilogTargetHasShutdownInitiatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_SHUTDOWN_INITIATED)

#define cunilogTargetSetShutdownCompleteFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_SHUTDOWN_COMPLETE)
#define cunilogTargetHasShutdownCompleteFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_SHUTDOWN_COMPLETE)

#define cunilogTargetSetTargetAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_ALLOCATED)
#define cunilogTargetHasTargetAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_ALLOCATED)

#define cunilogTargetSetLogPathAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_LOGPATH_ALLOCATED)
#define cunilogTargetHasLogPathAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_LOGPATH_ALLOCATED)

#define cunilogTargetSetAppNameAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_APPNAME_ALLOCATED)
#define cunilogTargetHasAppNameAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_APPNAME_ALLOCATED)

#define cunilogTargetSetLogFileAllocatedFlag(put)		\
	((put)->uiOpts |= CUNILOGTARGET_LOGFILE_ALLOCATED)
#define cunilogTargetHasLogFileAllocatedFlag(put)		\
	((put)->uiOpts & CUNILOGTARGET_LOGFILE_ALLOCATED)

#define cunilogTargetSetLogFileMaskAllocatedFlag(put)	\
	((put)->uiOpts |= CUNILOGTARGET_LOGF_MASK_ALLOCATED)
#define cunilogTargetHasLogFileMaskAllocatedFlag(put)	\
	((put)->uiOpts & CUNILOGTARGET_LOGF_MASK_ALLOCATED)

#define cunilogTargetSetFileToRotateAllocatedFlag(put)	\
	((put)->uiOpts |= CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)
#define cunilogTargetHasFileToRotateAllocatedFlag(put)	\
	((put)->uiOpts & CUNILOGTARGET_FILE_TO_ROTATE_ALLOCATED)

#define cunilogTargetSetProcessorsAllocatedFlag(put)	\
	((put)->uiOpts |= CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogTargetClrProcessorsAllocatedFlag(put)	\
	((put)->uiOpts &= ~ CUNILOGTARGET_PROCESSORS_ALLOCATED)
#define cunilogTargetHasProcessorsAllocatedFlag(put)	\
	((put)->uiOpts & CUNILOGTARGET_PROCESSORS_ALLOCATED)

#define cunilogTargetHasRunProcessorsOnStartup(put)		\
	((put)->uiOpts & CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogTargetClrRunProcessorsOnStartup(put)		\
	((put)->uiOpts &= ~ CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)
#define cunilogTargetSetRunProcessorsOnStartup(put)		\
	((put)->uiOpts |= CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP)

#define cunilogTargetHasFSneedsSorting(put)				\
	((put)->uiOpts & CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogTargetClrFSneedsSorting(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FS_NEEDS_SORTING)
#define cunilogTargetSetFSneedsSorting(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FS_NEEDS_SORTING)

#define cunilogTargetHasFLSisSorted(put)				\
	((put)->uiOpts & CUNILOGTARGET_FLS_IS_SORTED)
#define cunilogTargetClrFLSisSorted(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FLS_IS_SORTED)
#define cunilogTargetSetFLSisSorted(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FLS_IS_SORTED)

/*
#define cunilogTargetHasNumberSorting(put)				\
	((put)->uiOpts & CUNILOGTARGET_NEEDS_NUMBER_SORTING)
#define cunilogTargetClrNumberSorting(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_NEEDS_NUMBER_SORTING)
#define cunilogTargetSetNumberSorting(put)				\
	((put)->uiOpts |= CUNILOGTARGET_NEEDS_NUMBER_SORTING)
*/

#define cunilogTargetHasFLSreversed(put)				\
	((put)->uiOpts & CUNILOGTARGET_FLS_REVERSED)
#define cunilogTargetClrFLSreversed(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_FLS_REVERSED)
#define cunilogTargetSetFLSreversed(put)				\
	((put)->uiOpts |= CUNILOGTARGET_FLS_REVERSED)

#define cunilogTargetHasIsPaused(put)					\
	((put)->uiOpts & CUNILOGTARGET_PAUSED)
#define cunilogTargetClrIsPaused(put)					\
	((put)->uiOpts &= ~ CUNILOGTARGET_PAUSED)
#define cunilogTargetSetIsPaused(put)					\
	((put)->uiOpts |= CUNILOGTARGET_PAUSED)

#if defined (DEBUG) && !defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY)
	#define cunilogHasDebugQueueLocked(put)				\
		((put)->uiOpts & CUNILOGTARGET_DEBUG_QUEUE_LOCKED)
	#define cunilogClrDebugQueueLocked(put)				\
		((put)->uiOpts &= ~ CUNILOGTARGET_DEBUG_QUEUE_LOCKED)
	#define cunilogSetDebugQueueLocked(put)				\
		((put)->uiOpts |= CUNILOGTARGET_DEBUG_QUEUE_LOCKED)
#else
	#define cunilogHasDebugQueueLocked(put)	(true)
	#define cunilogClrDebugQueueLocked(put)
	#define cunilogSetDebugQueueLocked(put)
#endif

#define cunilogTargetHasAlwaysCallErrorCB(put)			\
	((put)->uiOpts & CUNILOGTARGET_ALWAYS_CALL_ERRORCB)
#define cunilogTargetClrAlwaysCallErrorCB(put)			\
	((put)->uiOpts &= ~ CUNILOGTARGET_ALWAYS_CALL_ERRORCB)
#define cunilogTargetSetAlwaysCallErrorCB(put)			\
	((put)->uiOpts |= CUNILOGTARGET_ALWAYS_CALL_ERRORCB)


/*
	Public option flags for the uiOpts member of a CUNILOG_TARGET structure.
	Flags callers/users can change/use.
*/

// Tells the initialiser function(s) not to allocate/assign default processors.
//	The target is not ready when this option flag is used. The function
//	ConfigCUNILOG_TARGETprocessorList () must be called before the target
//	is usable.
#define CUNILOGTARGET_NO_DEFAULT_PROCESSORS		SINGLEBIT64 (32)

/*
	By default, timestamps are created when an event is created.With this bit set,
	timestamps are created when they are enqueued. This ensures that events that
	are enqueued later have a newer timestamp but also locks the queue much longer
	because the timestamp is obtained during this process. Without this flag,
	timestamps are created when the event is created, and outside the lock.
*/
#define CUNILOGTARGET_ENQUEUE_TIMESTAMPS		SINGLEBIT64 (33)

// The echo/console output processor is skipped.
#define CUNILOGTARGET_NO_ECHO					SINGLEBIT64 (34)

// The processor that writes to the logfile is skipped.
#define CUNILOGTARGET_DONT_WRITE_TO_LOGFILE		SINGLEBIT64 (35)

// Colour information should be used.
#define CUNILOGTARGET_USE_COLOUR_FOR_ECHO		SINGLEBIT64 (36)

/*
	Macros for public/user/caller flags.
*/
#define cunilogIsNoEcho(put)							\
	((put)->uiOpts & CUNILOGTARGET_NO_ECHO)
#define cunilogClrNoEcho(put)							\
	((put)->uiOpts &= ~ CUNILOGTARGET_NO_ECHO)
#define cunilogSetNoEcho(put)							\
	((put)->uiOpts |= CUNILOGTARGET_NO_ECHO)

#define cunilogHasDontWriteToLogfile(put)				\
	((put)->uiOpts & CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogClrNoWriteToLogfile(put)					\
	((put)->uiOpts &= ~ CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)
#define cunilogSetNoWriteToLogfile(put)					\
	((put)->uiOpts |= CUNILOGTARGET_DONT_WRITE_TO_LOGFILE)

#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#ifndef cunilogTargetHasUseColourForEcho
		#define cunilogTargetHasUseColourForEcho(put)	\
			((put)->uiOpts & CUNILOGTARGET_USE_COLOUR_FOR_ECHO)
	#endif
	#ifndef cunilogTargetClrUseColourForEcho
		#define cunilogTargetClrUseColourForEcho(put)	\
			((put)->uiOpts &= ~ CUNILOGTARGET_USE_COLOUR_FOR_ECHO)
	#endif
	#ifndef cunilogTargetSetUseColourForEcho
		#define cunilogTargetSetUseColourForEcho(put)	\
			((put)->uiOpts |= CUNILOGTARGET_USE_COLOUR_FOR_ECHO)
	#endif
#endif

#define cunilogHasEnqueueTimestamps(put)				\
	((put)->uiOpts & CUNILOGTARGET_ENQUEUE_TIMESTAMPS)
#define cunilogClrEnqueueTimestamps(put)				\
	((put)->uiOpts &= ~ CUNILOGTARGET_ENQUEUE_TIMESTAMPS)
#define cunilogSetEnqueueTimestamps(put)				\
	((put)->uiOpts |= CUNILOGTARGET_ENQUEUE_TIMESTAMPS)


/*
	Event severities.

	If changed, please update the copy in the comments of cunilog.c too.
*/
enum cunilogeventseverity
{
		cunilogEvtSeverityNone									//  0
	,	cunilogEvtSeverityNonePass								//  1
	,	cunilogEvtSeverityNoneFail								//  2
	,	cunilogEvtSeverityNoneWarn								//  3
	,	cunilogEvtSeverityBlanks								//  4
	,	cunilogEvtSeverityEmergency								//	5
	,	cunilogEvtSeverityNotice								//	6
	,	cunilogEvtSeverityInfo									//  7
	,	cunilogEvtSeverityMessage								//  8
	,	cunilogEvtSeverityWarning								//  9
	,	cunilogEvtSeverityError									// 10
	,	cunilogEvtSeverityPass									// 11
	,	cunilogEvtSeverityFail									// 12
	,	cunilogEvtSeverityCritical								// 13
	,	cunilogEvtSeverityFatal									// 14
	,	cunilogEvtSeverityDebug									// 15
	,	cunilogEvtSeverityTrace									// 16
	,	cunilogEvtSeverityDetail								// 17
	,	cunilogEvtSeverityVerbose								// 18
	,	cunilogEvtSeverityIllegal								// 19
	,	cunilogEvtSeveritySyntax								// 20
	// Do not add anything below this line.
	,	cunilogEvtSeverityXAmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogEvtSeverityXAmountEnumValues.
};
typedef enum cunilogeventseverity cueventseverity;

enum cunilogeventtype
{
		cunilogEvtTypeNormalText							// Normal UTF-8 text.
	,	cunilogEvtTypeCommand								// Event is config/command event.

		/*
			Caption + hex dump. The number specifies the bit width of the caption's length.
			The caption text follows its length. The caption is not NUL-terminated.
			Member lenDataToLog only counts the amount of data to dump out, excluding
			caption and its length.
		*/
	,	cunilogEvtTypeHexDumpWithCaption8					// Caption length is 8 bit.
	,	cunilogEvtTypeHexDumpWithCaption16					// Caption length is 16 bit.
	,	cunilogEvtTypeHexDumpWithCaption32					// Caption length is 32 bit.
	,	cunilogEvtTypeHexDumpWithCaption64					// Caption length is 64 bit.
	// Do not add anything below this line.
	,	cunilogEvtTypeAmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogEvtTypeAmountEnumValues.
};
typedef enum cunilogeventtype cueventtype;

/*
	CUNILOG_EVENT

	A logging event structure.

	Note that if the data is dump data, szDataToLog points to a length field of between 1
	and 8 octets, followed by a caption text without NUL, and this again followed by the
	actual dump data. The member lenDataToLog contains the length of the actual dump data
	*only*,. i.e. neither length field nor caption text count towards lenDataToLog.
*/
typedef struct CUNILOG_EVENT
{
	CUNILOG_TARGET				*pCUNILOG_TARGET;			// The event's target/destination.
	uint64_t					uiOpts;						// Option flags.
	UBF_TIMESTAMP				stamp;						// Its date/timestamp.
	unsigned char				*szDataToLog;				// Data to log.
	size_t						lenDataToLog;				// Its length, not NUL-terminated.

	#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
		struct CUNILOG_EVENT	*next;
	#endif
	cueventseverity				evSeverity;
	cueventtype					evType;						// The event's type of data.
	size_t						sizEvent;					// The total allocated size of the
															//	event. If 0, the size is the size
															//	of the structure.
} CUNILOG_EVENT;

/*
	FillCUNILOG_EVENT

	Macro to fill a CUNILOG_EVENT structure. Note that the structure doesn't have a
	->next member if CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#ifdef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define FillCUNILOG_EVENT(pev, pt,					\
				opts, dts, sev, tpy, dat, len, siz)		\
		(pev)->pCUNILOG_TARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len;			\
		(pev)->evSeverity				= sev;			\
		(pev)->evType					= tpy;			\
		(pev)->sizEvent					= siz
#else
	#define FillCUNILOG_EVENT(pev, pt,					\
				opts, dts, sev, tpy, dat, len, siz)		\
		(pev)->pCUNILOG_TARGET			= pt;			\
		(pev)->uiOpts					= opts;			\
		(pev)->stamp					= dts;			\
		(pev)->szDataToLog				= dat;			\
		(pev)->lenDataToLog				= len;			\
		(pev)->next						= NULL;			\
		(pev)->evSeverity				= sev;			\
		(pev)->evType					= tpy;			\
		(pev)->sizEvent					= siz
#endif

/*
	Member uiOpts of a CUNILOG_EVENT structure.
*/

#define CUNILOGEVENT_NO_FLAGS			(0)

// The structure has been allocated on the heap. This is for DoneSUNILOGEVENT ()
//	to deallocate it.
#define CUNILOGEVENT_ALLOCATED					SINGLEBIT64 (0)

// The data has been allocated. This is also for DoneSUNILOGEVENT ().
#define CUNILOGEVENT_DATA_ALLOCATED				SINGLEBIT64 (1)

// Shuts down logging.
#define CUNILOGEVENT_SHUTDOWN					SINGLEBIT64 (2)

// Suppresses echo/console output processor.
#define CUNILOGEVENT_NO_ECHO					SINGLEBIT64 (3)

// This is an internal event. Internal events are generated
//	within processors.
#define CUNILOGEVENT_IS_INTERNAL				SINGLEBIT64 (4)

// Add fullstop automatically.
#define CUNILOGEVENT_AUTO_FULLSTOP				SINGLEBIT64 (5)

// No rotation for this event. This is very fast/quick logging.
//	It is also used for internal logging.
#define CUNILOGEVENT_NOROTATION					SINGLEBIT64 (6)

// Suppresses the remaining processors.
#define CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS\
												SINGLEBIT64	(7)

// Only process the echo processor. All others are suppressed.
#define CUNILOGEVENT_ECHO_ONLY					SINGLEBIT64 (8)

// Macros to set and check flags.
#define cunilogSetEventAllocated(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventAllocated(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_ALLOCATED)
#define cunilogIsEventDataAllocated(pev)				\
	((pev)->uiOpts & CUNILOGEVENT_DATA_ALLOCATED)

#define cunilogSetEventShutdown(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventShutdown(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_SHUTDOWN)
#define cunilogIsEventCancel(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_CANCEL)

#define cunilogSetEventNoEcho(pev)						\
	((pev)->uiOpts |= CUNILOGEVENT_NO_ECHO)
#define cunilogClrEventNoEcho(pev)						\
	((pev)->uiOpts &= ~ CUNILOGEVENT_NO_ECHO)
#define cunilogHasEventNoEcho(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_NO_ECHO)

#define cunilogSetEventInternal(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_IS_INTERNAL)
#define cunilogClrEventInternal(pev)					\
	((pev)->uiOpts &= ~ CUNILOGEVENT_IS_INTERNAL)
#define cunilogIsEventInternal(pev)						\
	((pev)->uiOpts & CUNILOGEVENT_IS_INTERNAL)

#define cunilogSetEventAutoFullstop(pev)				\
	((pev)->uiOpts |= CUNILOGEVENT_AUTO_FULLSTOP)
#define cunilogIsEventAutoFullstop(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_AUTO_FULLSTOP)

#define cunilogHasEventNoRotation(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_NOROTATION)
#define cunilogSetEventNoRotation(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_NOROTATION)

#define cunilogEventSetIgnoreRemainingProcessors(pev)	\
	((pev)->uiOpts |= CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS)
#define cunilogEventClrIgnoreRemainingProcessors(pev)	\
	((pev)->uiOpts &= ~ CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS)
#define cunilogEventHasIgnoreRemainingProcessors(pev)	\
	((pev)->uiOpts & CUNILOGEVENT_IGNORE_REMAINING_PROCESSORS)

#define cunilogSetEventEchoOnly(pev)					\
	((pev)->uiOpts |= CUNILOGEVENT_ECHO_ONLY)
#define cunilogClrEventEchoOnly(pev)					\
	((pev)->uiOpts &= ~ CUNILOGEVENT_ECHO_ONLY)
#define cunilogHasEventEchoOnly(pev)					\
	((pev)->uiOpts & CUNILOGEVENT_ECHO_ONLY)

/*
	Return type of the separate logging thread.
*/
#ifdef OS_IS_WINDOWS
	#define SEPARATE_LOGGING_THREAD_RETURN_TYPE			\
			DWORD WINAPI
#else
	#define SEPARATE_LOGGING_THREAD_RETURN_TYPE			\
			void *
#endif

/*
	Return values of the separate logging thread.
*/
#ifdef OS_IS_WINDOWS
	#define SEPARATE_LOGGING_THREAD_RETURN_SUCCESS		\
			(EXIT_SUCCESS)
	#define SEPARATE_LOGGING_THREAD_RETURN_FAILURE		\
			(EXIT_FAILURE)
#else
	#define SEPARATE_LOGGING_THREAD_RETURN_SUCCESS		\
			((void *) EXIT_SUCCESS)
	#define SEPARATE_LOGGING_THREAD_RETURN_FAILURE		\
			((void *) EXIT_FAILURE)
#endif

/*
	A callback function of a custom/user defined processor.
*/
typedef bool (*pfCustProc) (CUNILOG_PROCESSOR *, CUNILOG_EVENT *);

/*
	Callback function for cleaning up a custom/user defined processor.
*/
typedef void (*pfDoneProc) (CUNILOG_PROCESSOR *);

/*
	A pData structure for a unilogProcessCustomProcessor (custom/user/external) processor.

	Members:

	pCust			Pointer to a data structure provided and used by the caller. Cunilog
					does not access this value. To access this member from a callback function,
					cast the pData member of the CUNILOG_PROCESSOR structure to a pointer
					to a CUNILOG_CUSTPROCESS structure.
	procFnct		Pointer to a custom/user function provided by the caller that handles
					the processor. This member cannot be NULL.
	procDone		Pointer to a function that is called when the processor is destroyed.
					This member can be NULL if this custom (or user/external) processor
					does not require cleanup code.

	Note that there's no callback function for initialisation. If dynamic initialisation is
	required, it is recommended to initialise pCust to NULL and initialise the custom data
	structure within the first call to procFnct.
*/
typedef struct cunilog_customprocess
{
	void			*pCust;
	pfCustProc		procFnct;
	pfDoneProc		procDone;
} CUNILOG_CUSTPROCESS;

/*
	Parameter structure for a rotator processor.
*/
typedef struct cunilog_rotator_args
{
	CUNILOG_PROCESSOR		*cup;
	CUNILOG_EVENT			*pev;
	char					*nam;							// Name of file to rotate.
	size_t					siz;							// Its size, incl. NUL.
	size_t					idx;							// Vector index of curr file.
} CUNILOG_ROTATOR_ARGS;

/*
	The priority levels of the separate logging thread.

	When changing this enum, please also update the comment in cunilog.c.
*/
enum enCunilogLogPriority
{
	cunilogPrioNormal,
	cunilogPrioBelowNormal,
	cunilogPrioLow,
	cunilogPrioIdle,
	cunilogPrioBeginBackground,
	cunilogPrioEndBackground,
	// Do not insert enum values below this line.
	cunilogPrioAmountEnumValues
};
typedef enum enCunilogLogPriority	cunilogprio;

/*
	An element of the array with the files.
*/
typedef struct cunilogfilename
{
	const char	*szFilename;
	size_t		stLen;
} CUNILOGFILENAME;

END_C_DECLS

#endif														// Of #ifndef CUNILOGSTRUCTS_H.
/****************************************************************************************

	File		cunilogevtcmdsstructs.h
	Why:		Cunilog helper functions for event commands.
	OS:			C99
	Created:	2025-02-18

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-18	Thomas			Created.

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

#ifndef U_CUNILOGEVTCMDSSTRUCTS_H
#define U_CUNILOGEVTCMDSSTRUCTS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdbool.h>
	#include <inttypes.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		//#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		//#include "./../mem/ubfmem.h"
	#endif

#endif

EXTERN_C_BEGIN

enum cunilogEvtCmd
{
		cunilogCmdConfigUseColourForEcho
	,	cunilogCmdConfigEventSeverityFormatType
	,	cunilogCmdConfigCunilognewline
	,	cunilogCmdConfigDisableTaskProcessors
	,	cunilogCmdConfigEnableTaskProcessors
	,	cunilogCmdConfigDisableEchoProcessor
	,	cunilogCmdConfigEnableEchoProcessor
	,	cunilogCmdConfigSetLogPriority
	// Do not add anything below this line.
	,	cunilogCmdConfigXAmountEnumValues						// Used for sanity checks.
	// Do not add anything below cunilogCmdConfigXAmountEnumValues.
};


EXTERN_C_END

#endif														// Of #ifndef U_CUNILOGEVTCMDSSTRUCTS_H.
/****************************************************************************************

	File		cunilogevtcmds.h
	Why:		Cunilog helper functions for event commands.
	OS:			C99
	Created:	2025-02-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-17	Thomas			Created.

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

#ifndef U_CUNILOGEVTCMDS_H
#define U_CUNILOGEVTCMDS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdbool.h>
	#include <inttypes.h>

	#include "./cunilogevtcmdsstructs.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifndef CUNILOG_CMD_INVALID_SIZE
#define CUNILOG_CMD_INVALID_SIZE			(0)
#endif

EXTERN_C_BEGIN

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS

/*
	culIsValidCmd

	Returns true if cmd is a valid Cunilog command. Note that this is the only function/
	macro that checks that cmd is a valid Cunilog command, and that this is the only function/
	macro that does not abort in debug versions if the command is invalid.
	
	All other functions/macros do not check if a Cunilog command is valid or not.
*/
#ifdef DEBUG
	bool culIsValidCmd (enum cunilogEvtCmd cmd)
	;
#else
	#define culIsValidCmd(cmd)							\
		((0 <= cmd) && (cmd) < cunilogCmdConfigXAmountEnumValues)
#endif

/*
	culCmdRequiredSize

	Returns the required data size for the Cunilog event command cmd.
	The returned size includes space for the command itself plus the space required for
	additional parameters/arguments.
*/
size_t culCmdRequiredSize (enum cunilogEvtCmd cmd)
;

/*
	culCmdStoreCmdConfigUseColourForEcho

	Stores the command to change whether colours are used or not plus the boolean bUseColour
	in the buffer szOut points to.
*/
void culCmdStoreCmdConfigUseColourForEcho (unsigned char *szOut, bool bUseColour)
;

/*
	culCmdStoreCmdConfigCunilognewline

	Stores the command to change the newline representation and the value of nl in the
	buffer szOut points to.
*/
void culCmdStoreCmdConfigCunilognewline (unsigned char *szOut, newline_t nl)
;

/*
	culCmdStoreConfigEventSeverityFormatType

	Stores the command to change the event severity type and the value of sevTpy in the
	buffer szOut points to.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigEventSeverityFormatType (unsigned char *szOut, cueventsevfmtpy sevTpy)
	;
#endif

/*
	culCmdStoreCmdConfigDisableTaskProcessors
	culCmdStoreCmdConfigEnableTaskProcessors

	These functions store a command to disable or enable a particular type of processor in
	the buffer szOut points to.
*/
void culCmdStoreCmdConfigDisableTaskProcessors (unsigned char *szOut, enum cunilogprocesstask task);
void culCmdStoreCmdConfigEnableTaskProcessors (unsigned char *szOut, enum cunilogprocesstask task);

/*
	culCmdStoreConfigLogThreadPriority

	Stores the command to change the priority of the logging thread in the buffer szOut
	points to.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigLogThreadPriority (unsigned char *szOut, cunilogprio prio);
#endif

/*
	culCmdSetCurrentThreadPriority
*/
bool culCmdSetCurrentThreadPriority (cunilogprio prio);

/*
	culCmdChangeCmdConfigFromCommand

	Changes members/flags of the CUNILOG_TARGET structure pev->pCUNILOG_TARGET points to
	for event type cunilogEvtTypeCommand (member pev->evType).

	This function must only be called for events of type cunilogEvtTypeCommand.
*/
void culCmdChangeCmdConfigFromCommand (CUNILOG_EVENT *pev)
;

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS.

EXTERN_C_END

#endif														// Of #ifndef U_CUNILOGEVTCMDS_H.
/****************************************************************************************

	File:		cunilog.h
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
	1. Create a CUNILOG_TARGET structure and initialise it. Use either your own structure
		or create a new one with CreateNewSUNILOGTARGET () or InitOrCreateSUNILOGTARGET ().
		Or use the internal structure of this module with InitSUNILOGTARGETstatic () instead.
		The latter is most likely what you want.

	2. Use the logging functions repeatedly as you please. Depending on the member unilogType
		of the CUNILOG_TARGET structure, you might do this from a single or multiple
		threads.

	4. When not required anymore, probably just before the application exits, call
		ShutdownCUNILOG_TARGET () or ShutdownCUNILOG_TARGETstatic, depending on the structure
		you used. Call DoneSUNILOGTARGET () on the the CUNILOG_TARGET structure afterwards,
		or call DoneSUNILOGTARGETstatic () if the internal structure was used.

		Example for internal static structure:

--- Begin example in Using.md ---
// Application start

CUNILOG_TARGET *put = InitCUNILOG_TARGETstatic	(
			"logs", 4,
			"MyApp", USE_STRLEN,
			cunilogPath_relativeToHomeDir,
			cunilogMultiThreadedSeparateLoggingThread
						);
if (NULL == put)
{
	// InitCUNILOG_TARGETstatic () failed.
	exit (EXIT_FAILURE);
}

// Use the log...static () family of functions and macros for logging.
logTextU8_static ("A simple line to go in the logfile.");
logTextU8l_static ("Another line.", 13);
logTextU8l_static ("And another one.", USE_STRLEN);

// Just before the application exists shut down the logging target and deallocate
//	its resources.
ShutdownCUNILOG_TARGETstatic ();		// Blocks until the queue is empty.
DoneCUNILOG_TARGETstatic ();
--- End of example in Using.md ---

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

#ifndef CUNILOG_H
#define CUNILOG_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./functionptrtpydef.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/functionptrtpydef.h"
	#endif

	#include "./cunilogversion.h"
	#include "./cunilogstructs.h"

#endif

// To build the test functions.
/*
#ifndef CUNILOG_BUILD_TEST_FNCTS
#define CUNILOG_BUILD_TEST_FNCTS
#endif
*/

// Inserts function calls to output the current files list. Sometimes used for debugging.
#ifndef CUNILOG_BUILD_DEBUG_OUTPUT_FILES_LIST
//#define CUNILOG_BUILD_DEBUG_OUTPUT_FILES_LIST
#endif

// Inserts checks for the queue locker. For obvious reasons, this can't work reliably
//	and was only used for initial tests.
#ifndef CUNILOG_BUILD_DEBUG_TEST_LOCKER
//#define CUNILOG_BUILD_DEBUG_TEST_LOCKER
#endif

// Some functions accept string lengths of (size_t) -1 to obtain a length via a call
//	to strlen ().
#ifndef USE_STRLEN
#define USE_STRLEN						((size_t) -1)
#endif

// Failure return value for (size_t).
#ifndef CUNILOG_SIZE_ERROR
#define CUNILOG_SIZE_ERROR				((size_t) -1)
#endif


/*
	Memory alignments. Use 16 octets/bytes for 64 bit platforms.
	Use CUNILOG_DEFAULT_ALIGNMENT for structures and CUNILOG_POINTER_ALIGNMENT
	for pointers.
	Also, see https://learn.microsoft.com/en-us/cpp/build/reference/zp-struct-member-alignment?view=msvc-170 .
*/
#if defined (_M_X64)
	#ifndef CUNILOG_DEFAULT_ALIGNMENT
	#define CUNILOG_DEFAULT_ALIGNMENT	(16)
	#endif
#else
	#ifndef CUNILOG_DEFAULT_ALIGNMENT
	#define CUNILOG_DEFAULT_ALIGNMENT	(8)
	#endif
#endif
#if defined (_M_X64)
	#ifndef CUNILOG_POINTER_ALIGNMENT
	#define CUNILOG_POINTER_ALIGNMENT	(8)
	#endif
#else
	#ifndef CUNILOG_POINTER_ALIGNMENT
	#define CUNILOG_POINTER_ALIGNMENT	(8)
	#endif
#endif


// Our standard size for error messages on the stack.
#ifndef CUNILOG_STD_MSG_SIZE
#define CUNILOG_STD_MSG_SIZE			(256)
#endif

// Our standard size for bulk memory allocations.
#ifndef CUNILOG_STD_BULK_ALLOC_SIZE
#define CUNILOG_STD_BULK_ALLOC_SIZE		(4096 - sizeof (SBULKMEMBLOCK))
#endif

// The size we're going to expand the vector containing the names of logfiles.
#ifndef CUNILOG_STD_VECT_EXP_SIZE
#define CUNILOG_STD_VECT_EXP_SIZE		(128)
#endif

// The stack/heap threshold for the ...sfmt type logging functions.
#ifndef CUNILOG_DEFAULT_SFMT_SIZE
#define CUNILOG_DEFAULT_SFMT_SIZE		(256)
#endif

/*
	The default initial size of an event line. Note that this is not the space for the text
	but rather the entire line, including timestamp etc. If you know in advance that your
	texts (including stamp etc) are going to be longer you may override this with a higher
	value to possibly save some initial heap reallocations.

	This value must be greater than 0.
*/
#ifndef CUNILOG_INITIAL_EVENTLINE_SIZE
#define CUNILOG_INITIAL_EVENTLINE_SIZE			(256)
#endif

#if CUNILOG_INITIAL_EVENTLINE_SIZE <= 0
	#error CUNILOG_INITIAL_EVENTLINE_SIZE must be greater than zero
#endif

/*
	The default initial size of an event line that contains ANSI colour codes for severity
	levels plus the event line itself.
	If you know in advance that your texts (including stamp etc) are going to be longer you
	may override this with a higher value to possibly save some initial heap reallocations.
	The default is CUNILOG_INITIAL_EVENTLINE_SIZE.

	This value must be greater than 0.

	If you don't need coloured console output for severity levels you can switch it off by
	defining CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR or CUNILOG_BUILD_WITHOUT_CONSOLE_COLOR.
*/
#ifdef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOR
	#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#define CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#endif
#endif
#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#ifndef CUNILOG_INITIAL_COLEVENTLINE_SIZE
	#define CUNILOG_INITIAL_COLEVENTLINE_SIZE		(CUNILOG_INITIAL_EVENTLINE_SIZE)
	#endif
	#if CUNILOG_INITIAL_COLEVENTLINE_SIZE <= 0
		#error CUNILOG_INITIAL_COLEVENTLINE_SIZE must be greater than zero
	#endif
#endif

// Literally an arbitray character. This is used to find buffer overruns in debug
//	versions.
#ifndef CUNILOG_DEFAULT_DBG_CHAR
#define CUNILOG_DEFAULT_DBG_CHAR		'\x17'
#endif

// The spin count for the critical section on Windows.
#ifndef CUNILOG_WINDOWS_CRITICAL_SECTION_SPIN_COUNT
#define CUNILOG_WINDOWS_CRITICAL_SECTION_SPIN_COUNT		(5000)
#endif

// The default rotation thresholds in debug and release versions.
#ifdef CUNILOG_DEBUG_USE_TEST_ROTATOR_VALUES

	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED	(2)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED		(3)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED		(4)
	#endif

#else

	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_UNCOMPRESSED	(10)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONTRASHED		(100)
	#endif
	#ifndef CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED
	#define CUNILOG_DEFAULT_ROTATOR_KEEP_NONDELETED		(100)
	#endif

#endif

// The mode for opening the current logfile.
#ifdef PLATFORM_IS_WINDOWS
	#define CUNILOG_DEFAULT_OPEN_MODE	(FILE_APPEND_DATA)
	/*
		pl->hLogFile = CreateFileU8	(
						szLogFileName, GENERIC_WRITE,
						FILE_SHARE_DELETE | FILE_SHARE_READ,
						NULL, OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						NULL
									);
	*/
#else
	#define CUNILOG_DEFAULT_OPEN_MODE	"a"
#endif

EXTERN_C_BEGIN

/*
	The pointer to the module's internal static CUNILOG_TARGET structure.
	The _static versions of the logging functions operate on this structure.
*/
CUNILOG_DLL_IMPORT extern CUNILOG_TARGET *pCUNILOG_TARGETstatic;

/*
	Functions
*/

/*
	CreateCopyCUNILOG_PROCESSORs

	Creates a copy of the array of pointers to CUNILOG_PROCESSOR structures with n processors.
	The copy contains a copy of the array of pointers to the structures, a copy of the
	structures themselves, and a copy of all pData members. This is as deep as the function
	goes.

	The copy is created as a single memory block, hence can be deallocated again with a single
	call to ubf_free (). However, for consistency it is recommended to call
	DoneCopyCUNILOG_PROCESSORs () on the returned memory block.

	The function returns a pointer to the allocated memory block where the copy of the array
	of pointers to CUNILOG_PROCESSOR structures can be found, including all CUNILOG_PROCESSOR
	structures and their pData structures. It returns NULL if the heap allocation fails.
*/
CUNILOG_PROCESSOR **CreateCopyCUNILOG_PROCESSORs (CUNILOG_PROCESSOR *cps [], unsigned int n);
TYPEDEF_FNCT_PTR (CUNILOG_PROCESSOR **, CreateCopyCUNILOG_PROCESSORs)
	(CUNILOG_PROCESSOR *cps [], unsigned int n);

/*
	DoneCopyCUNILOG_PROCESSORs

	Destroys a copy of CUNILOG_PROCESSORs created with CreateCopyCUNILOG_PROCESSORs ().
	The parameter cps must not be NULL.
	
	The function is literally just a wrapper for ubf_free () and always returns NULL.
*/
void *DoneCopyCUNILOG_PROCESSORs (CUNILOG_PROCESSOR *cps []);
TYPEDEF_FNCT_PTR (void *, DoneCopyCUNILOG_PROCESSORs) (CUNILOG_PROCESSOR *cps []);

/*
	Table with the length of the rotational date/timestamp.
*/
extern size_t arrLengthTimeStampFromPostfix [cunilogPostfixAmountEnumValues];

/*
	lenDateTimeStampFromRotation
	
	Returns the length of the timestamp of the current rotation.
*/
#ifdef DEBUG
	size_t lenDateTimeStampFromPostfix (enum cunilogpostfix postfix);
#else
	#define lenDateTimeStampFromPostfix(pfx)			\
		(arrLengthTimeStampFromPostfix [(pfx)])
#endif

/*
	Table with the rotation wildcard masks.
*/
extern const char *arrPostfixWildcardMask [cunilogPostfixAmountEnumValues];

/*
	postfixMaskFromLogPostfix
	
	Returns a string representing a file name wildcard mask for rotation that can be used
	to search for files, for instance a rotation with a value of unilogEveryMinute returns
	"????-??-?? ??:??".
*/
#ifdef DEBUG
	const char *postfixMaskFromLogPostfix (enum cunilogpostfix postfix);
#else
	#define postfixMaskFromLogPostfix(pfx)			\
		(arrPostfixWildcardMask [pfx])
#endif

/*
	CunilogSetConsoleTo

	Sets the console to UTF-8 or UTF-16 on Windows.
*/
#ifdef PLATFORM_IS_WINDOWS
	enum enclconsoleoutpCP
	{
			cunilogConsoleIsUninitialised
		,	cunilogConsoleIsUTF8
		,	cunilogConsoleIsUTF16
		,	cunilogConsoleIsNeither
	};
	typedef enum enclconsoleoutpCP culogconcp;

	void CunilogSetConsoleTo (culogconcp cp);
	TYPEDEF_FNCT_PTR (void, CunilogSetConsoleTo) (culogconcp cp);
#endif

/*
	CunilogSetConsoleToUTF8
	CunilogSetConsoleToUTF16
	CunilogSetConsoleToNone

	Macros to set the console to UTF-8 or UTF-16 on Windows. They do nothing on POSIX.

	By default the echo/console output processor changes the Windows console input
	and output character sets/code pages to UTF-8 when invoked for the first time.
	Calling one of these functions beforehand explicitely sets the code pages/console
	character sets and prevents the echo/console output processor from changing them
	when a logging function that echoes to the console is called the first time.

	The function CunilogSetConsoleToNone () does not change the code pages/character
	sets for the attached console but simply prevents the Cunilog echo/console output
	processor from changing them when a logging function that writes to the console is
	called for the first time.
*/
#ifdef PLATFORM_IS_WINDOWS
	#define CunilogSetConsoleToUTF8()	CunilogSetConsoleTo (cunilogConsoleIsUTF8)
#else
	#define CunilogSetConsoleToUTF8()
#endif
#ifdef PLATFORM_IS_WINDOWS
	#define CunilogSetConsoleToUTF16()	CunilogSetConsoleTo (cunilogConsoleIsUTF16)
#else
	#define CunilogSetConsoleToUTF16()
#endif
#ifdef PLATFORM_IS_WINDOWS
	#define CunilogSetConsoleToNone()	CunilogSetConsoleTo (cunilogConsoleIsNeither)
#else
	#define CunilogSetConsoleToNone()
#endif

/*
	CunilogEnableANSI
	CunilogDisableANSI
	CunilogIsANSIenabled

	Enable or disable the Windows console for ANSI escape sequences,
	or check if the Windows console is configured for ANSI escape sequences.

	Note that these functions configure the Windows console only. They have
	no influence on what Cunilog sends/writes to the console.

	The functions return true on success, false otherwise.
	
	The function CunilogIsANSIenabled () returns true if ANSI escape sequences are
	enabled, false if not. On POSIX, CunilogIsANSIenabled () always evaluates to
	true.
*/
#ifdef PLATFORM_IS_WINDOWS
	bool CunilogEnableANSI	(void);
	TYPEDEF_FNCT_PTR (bool, CunilogEnableANSI)	(void);
	bool CunilogDisableANSI	(void);
	TYPEDEF_FNCT_PTR (bool, CunilogDisableANSI)	(void);
	bool CunilogIsANSIenabled (void);
	TYPEDEF_FNCT_PTR (bool, CunilogIsANSIenabled) (void);
#else
	#define CunilogEnableANSI()
	#define CunilogDisableANSI()
	#define CunilogIsANSIenabled() (true)
#endif

/*
	CunilogGetEnv

	Wrapper function for getenv () on Windows and secure_getenv () on POSIX.
*/
char *CunilogGetEnv (const char *szName);
TYPEDEF_FNCT_PTR (char *, CunilogGetEnv) (const char *szName);

/*
	Cunilog_Have_NO_COLOR

	Returns true if the environment variable NO_COLOR exists and has a value (is not empty).
	See https://no-color.org/ for the specification.

	The function checks the environment variable NO_COLOR every time it is called. It is
	therefore recommended to call the function only when really required, for example at the
	start of an application, and store its return value in a variable.
*/
bool Cunilog_Have_NO_COLOR (void);
TYPEDEF_FNCT_PTR (bool, Cunilog_Have_NO_COLOR) (void);

/*
	CunilogGetAbsPathFromAbsOrRelPath

	Obtains an absolute path from a relative path. The parameter absOrRelPath specifies
	to what a relative path is relative to.

	The function adds a forward or backward slash to the buffer psmb points to, as it
	assumes the parameters are paths, not filenames. However, the function also works
	with paths to filenames but since it adds a slash the caller needs to remove this
	manually, for example by overwriting it with an ASCII_NUL character.

	psmb			A pointer to an SMEMBUF structure whose buffer receives the absolut
					path.

	plmb			A pointer to a size_t that receives the length of the buffer.

	szAbsOrRelPath	The path. Can be relative or absolute.

	lnAbsOrRelPath	Its length as would be retrieved by strlen (). Can be USE_STRLEN,
					in which case the function calls strlen (szAbsOrRelPath) to obtain
					it.

	absOrRelPath	An enum that specifies what the path is relative to. The the enum
					enCunilogRelPath for possible values.
*/
bool CunilogGetAbsPathFromAbsOrRelPath	(
		SMEMBUF				*psmb,
		size_t				*plmb,
		const char			*szAbsOrRelPath,
		size_t				lnAbsOrRelPath,
		enCunilogRelPath	absOrRelPath
										)
;
TYPEDEF_FNCT_PTR (bool, CunilogGetAbsPathFromAbsOrRelPath)
								(
		SMEMBUF				*psmb,
		size_t				*plmb,
		const char			*szAbsOrRelPath,
		size_t				lnAbsOrRelPath,
		enCunilogRelPath	absOrRelPath
								)
;

// This seems to be useful.
#define requiresCUNILOG_TARGETseparateLoggingThread(p)	\
(														\
		cunilogSingleThreadedSeparateLoggingThread	== (p)->culogType\
	||	cunilogMultiThreadedSeparateLoggingThread	== (p)->culogType\
)

/*
	InitCUNILOG_TARGETex

	Initialises an existing CUNILOG_TARGET structure.

	Parameters

	put					A pointer to an CUNILOG_TARGET structure that holds all required
						parameters. The function does not create a copy of this structure and
						therefore it must be available/accessible until DoneSUNILOGTARGET ()
						and ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () are called on
						it. In other words the structure is required to either be static or is
						created as an automatic structure in main ().
						The function InitCUNILOG_TARGETstatic () uses the module's internal static
						structure.

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory), or
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either cunilogRunProcessorsOnStartup or
						cunilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to puz on success, NULL otherwise.
*/
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
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGETex)
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
;

/*
	InitCUNILOG_TARGET

	Simplified version of InitCUNILOG_TARGETex ().
*/
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
	;
	TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGET)
	(
		  CUNILOG_TARGET			*put				// Must not be NULL.
		, const char				*szLogPath			// Path to the logging information.
		, size_t					lenLogPath			// Length of szLogPath
		, const char				*szAppName			// Application name.
		, size_t					lenAppName			// Length of szApplication.
		, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
		, enum cunilogtype			type
	)
	;
#else
	#define InitCUNILOG_TARGET(put,						\
				szLogPath,	lenLogPath,					\
				szAppName,	lenAppName,					\
				relLogPath,								\
				type)									\
				InitCUNILOG_TARGETex	(				\
					(put),								\
					(szLogPath), (lenLogPath),			\
					(szAppName), (lenAppName),			\
					(relLogPath),						\
					(type),								\
					cunilogPostfixDefault,				\
					NULL, 0,							\
					cunilogEvtTS_Default,				\
					cunilogNewLineDefault,				\
					cunilogRunProcessorsOnStartup		\
										)
#endif

/*
	CreateNewCUNILOG_TARGET

	Creates a new CUNILOG_TARGET structure on the heap and initialises it.

	Parameters

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelLogPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogLogPath_relativeToExecutable (the executable file),
						cunilogLogPath_relativeToCurrentDir (the current directory), or
						cunilogLogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogLogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either unilogRunProcessorsOnStartup or
						unilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	For performance reasons and to simplify data handling, the function allocates a single memory
	block that holds enough space for the CUNILOG_TARGET structure as well as szLogPath and
	szAppName.

	If the function succeeds it returns a pointer to a valid SUNILOGTARGET structure.
	If the function fails, the return value is NULL.
*/
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
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, CreateNewCUNILOG_TARGET)
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
;

/*
	InitOrCreateCUNILOG_TARGET

	Initialises an existing CUNILOG_TARGET structure or creates a new one on the heap.

	If put is NULL, the function calls CreateNewCUNILOG_TARGET () and returns a pointer
	to the newly allocated and initialised CUNILOG_TARGET structure.
	
	If put is not NULL, the function initialises it and returns put by calling
	InitCUNILOG_TARGET () on it. If put is not NULL, the function does not create a copy of
	this structure. The caller therefore must ensure that it is available/accessible until
	DoneCUNILOG_TARGET () and ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () are called
	on it, i.e. that the structure is either static or is created as an automatic structure
	in main ().

	If the cuProcessorList parameter is not NULL, the function does not create a copy of
	this list and therefore must be available/accessible until DoneCUNILOG_TARGET () and
	ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () are called on it. In other
	words the list is required to either reside on the heap, is static, or is created
	as automatic in main ().

	The function returns NULL if it fails.

	Call DoneCUNILOG_TARGET () when done with the structure, independent of whether it
	has been created on the heap or provided as the parameter psu.
*/
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
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitOrCreateCUNILOG_TARGET)
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
;

/*
	InitCUNILOG_TARGETstaticEx
	
	Initialises the internal CUNILOG_TARGET structure. If the _static versions of the logging
	functions are used, an application must call this function before any of these functions
	are called.
	
	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogPath_relativeToExecutable (the executable file),
						cunilogPath_relativeToCurrentDir (the current directory), or
						cunilogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.

	postfix				The postfix used for the SUNILOGTARGET's logfile. See cunilogstructs.h
						for more details.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

	unilogTSformat		The format of an event date/timestamp. Use unilogEvtTS_Default, which is
						an ISO 8601 date/timestamp with a space between date and time.

	unilogNewLine		The representation of a new line character to write into the logfile.
						A value of unilogNewLineSystem picks a default representation for the
						operating system.

	rp					Can be either cunilogRunProcessorsOnStartup or
						cunilogDontRunProcessorsOnStartup to run or not run all processors the
						first time a logging function is called.

	The function returns a pointer to the internal CUNILOG_TARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneCUNILOG_TARGETstatic () to free the structure's resources.
*/
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
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGETstaticEx)
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
;

/*
	InitCUNILOG_TARGETstatic

	Simplified version of InitCUNILOG_TARGETstaticEx ().

	szLogPath			The path where the log files are written to. This can either be an
						absolute or a relative path. If the path is relative, it is assumed to
						be relative to what the enumeration parameter relLogPath specifies.
						If this parameter is NULL, the function picks a folder according to
						what the enumeration parameter relLogPath specifies, or the function
						fails.
						This string does not have to be NUL-terminated if lenLogPath is given
						correctly and not as (size_t) -1 (or USE_STRLEN).

	lenLogPath			The length of szLogPath. If this parameter is (size_t) -1, the function
						calls strlen () to obtain it. Conveniently USE_STRLEN is defined as
						(size_t) -1. If this parameter is 0, the function uses the executable
						module's path.

	szAppName			The name of the application. This is the part of the log file's name
						before the date/timestamp, for instance "myApp" in "myApp_2022-10-18.log".
						If this parameter is NULL, the function uses the executable module's name.
						The string does not need to be NUL-terminated if lenAppName holds the
						correct length.

	lenAppName			The length of szApplication. If this parameter is (size_t) -1, the
						function calls strlen (szApplication) to obtain it. USE_STRLEN is defined
						as (size_t) -1.
						If this parameter is 0, the function uses the executable module's name.

	relLogPath			One of the values in the enCunilogRelPath enumeration that specify
						the base path if szLogPath is either relative or NULL. If szLogPath is
						relative, the path is relative to
						cunilogPath_relativeToExecutable (the executable file),
						cunilogPath_relativeToCurrentDir (the current directory), or
						cunilogPath_relativeToHomeDir (the user's home directory).
						See cunilogstructs.h for details.
						The value of this parameter is ignored if szLogPath is an absolute
						path. If this value is cunilogPath_isAbsolute and szLogPath is a
						relative path or NULL, the function fails.

	type				The type of the SUNILOGTARGET. See cunilogstructs.h for more details.

	The function returns a pointer to the internal CUNILOG_TARGET cunilognewlinestructure
	upon success, NULL otherwise.

	Call DoneCUNILOG_TARGETstatic () to free the structure's resources.
*/
CUNILOG_TARGET *InitCUNILOG_TARGETstatic
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
;
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, InitCUNILOG_TARGETstatic)
(
	  const char				*szLogPath			// Path to the logging information.
	, size_t					lenLogPath			// Length of szLogPath
	, const char				*szApplication		// Application name.
	, size_t					lenApplication		// Length of szApplication.
	, enCunilogRelPath			relLogPath			// Rel. to home, exe, or current dir.
	, enum cunilogtype			type
)
;

/*
	MoveCUNILOG_TARGETqueueToFrom

	Moves the queue of the target putFrom to target putTo.
	The function requires that both targets have a queue. It fails if this is not
	the case.

	The function returns true on success, false otherwise.
*/
bool MoveCUNILOG_TARGETqueueToFrom	(
		CUNILOG_TARGET *cunilog_restrict putTo,
		CUNILOG_TARGET *cunilog_restrict putFrom
									)
;
TYPEDEF_FNCT_PTR (bool, MoveCUNILOG_TARGETqueueToFrom)
(
		CUNILOG_TARGET *cunilog_restrict putTo,
		CUNILOG_TARGET *cunilog_restrict putFrom
);

/*
	HAS_CUNILOG_TARGET_A_QUEUE

	Macro to check if a CUNILOG_TARGET structure has an event quueue.
*/
#define HAS_CUNILOG_TARGET_A_QUEUE(put)					\
(														\
		cunilogSingleThreadedSeparateLoggingThread	== put->culogType\
	||	cunilogMultiThreadedSeparateLoggingThread	== put->culogType\
	||	cunilogSingleThreadedQueueOnly				== put->culogType\
	||	cunilogMultiThreadedQueueOnly				== put->culogType\
)

/*
	GetAbsoluteLogPathCUNILOG_TARGET

	Returns the absolute path to the folder logfiles are written to, including a directory
	separator. If plen is not NULL, the function returns the length of the path at the address
	plen points to. This is the value strlen () would return.

	The last character of the returned path is a directory separator, which is a backslash
	on Windows and a forward slash on all other systems.

	The function returns NULL if it fails. In this case it will not have changed the address
	plen points to.
*/
const char *GetAbsoluteLogPathCUNILOG_TARGET (CUNILOG_TARGET *put, size_t *plen);
TYPEDEF_FNCT_PTR (const char *, GetAbsoluteLogPathCUNILOG_TARGET)
	(CUNILOG_TARGET *put, size_t *plen);

/*
	GetAbsoluteLogPathCUNILOG_TARGET_static

	Calls GetAbsoluteLogPathCUNILOG_TARGET () to obtain the absolute path to the folder
	logfiles for the internal static CUNILOG_TARGET structure are written to.
*/
const char *GetAbsoluteLogPathCUNILOG_TARGET_static (size_t *plen);
TYPEDEF_FNCT_PTR (const char *, GetAbsoluteLogPathCUNILOG_TARGET_static)
	(size_t *plen);

/*
	GetCUNILOG_PROCESSOR

	Returns a pointer to the nth processor that performs processing task task.
	If n is 0, the function finds the first processor of task task, if it is
	1, it returns the second procossor of task task.
	Returns NULL if a processor for task task does not exist or if n is higher
	than the number of task processors - 1. For instance, if a processor list
	only contains one echo processor, and if n = 1, the function returns NULL.

	For example, to obtain the echo processor:
	CUNILOG_PROCESSOR *cup = GetCUNILOG_PROCESSOR	(
								put, cunilogProcessEchoToConsole, 0
													);
*/
CUNILOG_PROCESSOR *GetCUNILOG_PROCESSOR	(
						CUNILOG_TARGET				*put,
						enum cunilogprocesstask		task,
						unsigned int				n
										)
;
TYPEDEF_FNCT_PTR (CUNILOG_PROCESSOR *, GetCUNILOG_PROCESSOR)
										(
						CUNILOG_TARGET				*put,
						enum cunilogprocesstask		task,
						unsigned int				n
										)
;

/*
	GetCUNILOG_PROCESSORrotationTask

	Returns a pointer to the nth rotation processor that performs rotation task rot.
	If n is 0, the function finds the first rotation processor of task rot, if it is
	1, it returns the second rotation procossor of task rot.
	Returns NULL if a rotation processor for task rot does not exist or if n is higher
	than the number of this type of ratation processors - 1. For instance, if a processor
	list only contains one cunilogrotationtask_MoveToTrashLogfiles rotation processor,
	and if n = 1, the function returns NULL.

	For example, to obtain a pointer to the rotation processor that moves files to the
	recycle bin/trash:
	CUNILOG_PROCESSOR *cup = GetCUNILOG_PROCESSORrotationTask	(
								put, cunilogrotationtask_MoveToTrashLogfiles, 0
																);
*/
CUNILOG_PROCESSOR *GetCUNILOG_PROCESSORrotationTask	(
						CUNILOG_TARGET				*put,
						enum cunilogrotationtask	rot,
						unsigned int				n
													)
;

/*
	ConfigCUNILOG_TARGETerrorCallbackFunction

	Sets the error callback function of the specified Cunilog target put points to.
*/
#ifndef CUNILOG_BUILD_WITHOUT_ERROR_CALLBACK
	void ConfigCUNILOG_TARGETerrorCallbackFunction (CUNILOG_TARGET *put, cunilogErrCallback errorCB);
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETerrorCallbackFunction)
		(CUNILOG_TARGET *put, cunilogErrCallback errorCB);
#else
	#define ConfigCUNILOG_TARGETerrorCallbackFunction(put, errorCB)
#endif

/*
	ConfigCUNILOG_TARGETeventStampFormat

	Sets the member unilogEvtTSformat of the CUNILOG_TARGET structure put points to to the
	value of tsf.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETeventStampFormat (CUNILOG_TARGET *put, enum cunilogeventTSformat tsf)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETeventStampFormat)
		(CUNILOG_TARGET *put, enum cunilogeventTSformat tsf);
#else
	#define ConfigCUNILOG_TARGETeventStampFormat(put, f)	\
				(put)->unilogEvtTSformat = (f)
#endif

/*
	ConfigCUNILOG_TARGETrunProcessorsOnStartup

	Sets the flag CUNILOGTARGET_RUN_PROCESSORS_ON_STARTUP of the uiOpts member of the
	CUNILOG_TARGET structure put points to according to the value of the runProcessorsOnStartup
	enumeration rp.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETrunProcessorsOnStartup (CUNILOG_TARGET *put, runProcessorsOnStartup rp)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETrunProcessorsOnStartup)
		(CUNILOG_TARGET *put, runProcessorsOnStartup rp);
#else
	#define ConfigCUNILOG_TARGETrunProcessorsOnStartup(put, rp)	\
		switch (rp)												\
		{														\
			case cunilogRunProcessorsOnStartup:					\
				cunilogSetRunAllProcessorsOnStartup (put);		\
				break;											\
			case cunilogDontRunProcessorsOnStartup:				\
				cunilogClrRunAllProcessorsOnStartup (put);		\
				break;											\
			default:											\
				cunilogSetRunAllProcessorsOnStartup (put);		\
				break;											\
		}
#endif

/*
	ConfigCUNILOG_TARGETcunilognewline

	Sets the member unilogNewLine of the CUNILOG_TARGET structure put points to to the
	value of nl.

	This function should only be called directly after the target has been initialised and
	before any of the logging functions has been called unless
	CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETcunilognewline (CUNILOG_TARGET *put, newline_t nl);
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETcunilognewline)
		(CUNILOG_TARGET *put, newline_t nl);
#else
	#define ConfigCUNILOG_TARGETcunilognewline(put, nl)			\
		(put)->unilogNewLine = (nl)
#endif

/*
	ConfigCUNILOG_TARGETeventSeverityFormatType

	Sets the format type of event severities for the target structure put. It
	sets the member evSeverityType of the CUNILOG_TARGET structure put to the
	value of eventSeverityFormatType.
*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETeventSeverityFormatType	(
			CUNILOG_TARGET				*put,
			cueventsevfmtpy				eventSeverityFormatType
														)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETeventSeverityFormatType)
														(
			CUNILOG_TARGET				*put,
			cueventsevfmtpy				eventSeverityFormatType
														)
	;
#else
	#define ConfigCUNILOG_TARGETeventSeverityFormatType(put, evstpy)	\
		(put)->evSeverityType = (evstpy)
#endif

/*
	ConfigCUNILOG_TARGETuseColourForEcho

	Switches on/off using colours for console output depending on event severity level.

	The NO_COLOR suggestion at https://no-color.org/ recommends that this function is
	called after checking the environment variable NO_COLOR first:
	ConfigCUNILOG_TARGETuseColourForEcho (target, !Cunilog_Have_NO_COLOR ());
*/
#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
	#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ConfigCUNILOG_TARGETuseColourForEcho (CUNILOG_TARGET *put, bool bUseColour)
		;
		TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETuseColourForEcho)
			(CUNILOG_TARGET *put, bool bUseColour);
	#else
		#define ConfigCUNILOG_TARGETuseColourForEcho(put, b)	\
			if (bUseColour)										\
				cunilogSetUseColourForEcho (put);				\
			else												\
				cunilogClrUseColourForEcho (put)
	#endif
#endif

/*
	ConfigCUNILOG_TARGETprocessorList

	Sets the processors for a CUNILOG_TARGET struture.

	Parameters

	put					A pointer to a CUNILOG_TARGET structure for which the processors
						are set.

	cuProcessorList		A pointer to a list with cunilog processors. This parameter can be
						NULL, in which case a standard set of processors will be used.
						If this parameter is not NULL, the function does not create a
						copy of the provided processor list, which means the list must be
						available/accessible until ShutdownCUNILOG_TARGET () or
						CancelCUNILOG_TARGET (), and then DoneSCUNILOGTAREGE () are called
						on it. In other words the list is required to either reside on the
						heap, is static, or is created as automatic in main ().

	nProcessors			The amount of processors cuProcessorList points to.

*/
#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void ConfigCUNILOG_TARGETprocessorList	(
					CUNILOG_TARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	;
	TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETprocessorList)
											(
					CUNILOG_TARGET			*put
				,	CUNILOG_PROCESSOR		**cuProcessorList	// One or more post-processors.
				,	unsigned int			nProcessors			// Number of processors.
											)
	;
#else
	#define ConfigCUNILOG_TARGETprocessorList(put,		\
				cup, n)									\
				prepareProcessors (put, cuProcessorList, nProcessors)
#endif

/*
	ConfigCUNILOG_TARGETdisableTaskProcessors
	ConfigCUNILOG_TARGETenableTaskProcessors

	Disables/enables processors for task task.
*/
void ConfigCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);
void ConfigCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);

TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETdisableTaskProcessors)
	(CUNILOG_TARGET *put, enum cunilogprocesstask task);
TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETenableTaskProcessors)
	(CUNILOG_TARGET *put, enum cunilogprocesstask task);

/*
	ConfigCUNILOG_TARGETdisableEchoProcessor
	ConfigCUNILOG_TARGETenableEchoProcessor

	Disables/enables echo (console output) processors. Echo or console output processors
	are processors whose task is cunilogProcessEchoToConsole.
*/
void ConfigCUNILOG_TARGETdisableEchoProcessor	(CUNILOG_TARGET *put);
void ConfigCUNILOG_TARGETenableEchoProcessor	(CUNILOG_TARGET *put);

TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETdisableEchoProcessor)	(CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (void, ConfigCUNILOG_TARGETenableEchoProcessor)	(CUNILOG_TARGET *put);

/*
	EnterCUNILOG_TARGET
	LockCUNILOG_TARGET

	LeaveCUNILOG_TARGET
	UnlockCUNILOG_TARGET

	EnterCUNILOG_TARGETstatic
	LockCUNILOG_TARGETstatic

	LockCUNILOG_TARGETstatic
	UnlockCUNILOG_TARGETstatic

	Interface functions/macros to lock (enter) and unlock (leave) the critical section or
	mutex of the singly-linked events list of the CUNILOG_TARGET structure put points to.
	The ...static versions lock and unlock the internal static CUNILOG_TARGET structure.

	Since Cunilog provides several means of accessing the events list of a CUNILOG_TARGET
	structure, and since it handles the events list internally, these functions/macros are most
	likely not required and should probably not be used.

	Note that these functions/macros do NOT lock or unlock access to the CUNILOG_TARGET
	structure's members. They are merely for locking and unlocking the singly-linked list
	containing the events to log.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, these macros/functions do nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void EnterCUNILOG_TARGET (CUNILOG_TARGET *put);
	void LeaveCUNILOG_TARGET (CUNILOG_TARGET *put);
	#define LockCUNILOG_TARGET(put)						\
				EnterCUNILOG_TARGET (put)
	#define UnlockCUNILOG_TARGET(put)					\
				LeaveCUNILOG_TARGET (put)
	#define EnterCUNILOG_TARGETstatic()					\
				LeaveCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	#define LeaveCUNILOG_TARGETstatic()					\
				EnterCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	#define LockCUNILOG_TARGETstatic()					\
				EnterCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	#define UnlockCUNILOG_TARGETstatic()				\
				LeaveCUNILOG_TARGET (pCUNILOG_TARGETstatic)
	
	TYPEDEF_FNCT_PTR (void, EnterCUNILOG_TARGET) (CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (void, LeaveCUNILOG_TARGET) (CUNILOG_TARGET *put);
#else
	#define EnterCUNILOG_TARGET(put)
	#define LeaveCUNILOG_TARGET(put)
	#define LockCUNILOG_TARGET(put)
	#define UnlockCUNILOG_TARGET(put)
	#define EnterCUNILOG_TARGETstatic()
	#define LeaveCUNILOG_TARGETstatic()
	#define LockCUNILOG_TARGETstatic()
	#define UnlockCUNILOG_TARGETstatic()
#endif

/*
	DoneCUNILOG_TARGET

	Deallocates all resources of the CUNILOG_TARGET put points to. After a structure has been
	processed by this function, none of the logging functions can be called on it anymore, but
	it could however be re-used by initialising it again.

	Before calling this function, call ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET ()
	first to either process or discard the target's event queue.

	The function always returns NULL.
*/
CUNILOG_TARGET *DoneCUNILOG_TARGET (CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (CUNILOG_TARGET *, DoneCUNILOG_TARGET) (CUNILOG_TARGET *put);

/*
	DoneCUNILOG_TARGETstatic
	
	Deallocates all resources of the internal static CUNILOG_TARGET structure by calling
	DoneCUNILOG_TARGET () on it.

	The function always returns NULL.
*/
#define DoneCUNILOG_TARGETstatic()						\
			DoneCUNILOG_TARGET (pCUNILOG_TARGETstatic)

/*
	ShutdownCUNILOG_TARGET

	Blocks further logging by forcing all logging functions to return false. It then waits
	for the events of the current queue to be processed and returns after an existing separate
	logging thread has exited.

	Logging events that are produced by currently executing logging functions themselves are
	not blocked until the queue is empty. This means internal non-rotating events like
	"Deleting file..." etc. are still processed until none are left.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, meaning that only further logging is blocked and logging functions called
	afterwards return false.

	This function should be called just before DoneCUNILOG_TARGET ().

	The function returns true on success, false otherwise.
*/
bool ShutdownCUNILOG_TARGET (CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (bool, ShutdownCUNILOG_TARGET) (CUNILOG_TARGET *put);

/*
	ShutdownCUNILOG_TARGETstatic

	Calls ShutdownCUNILOG_TARGET () on the internal static CUNILOG_TARGET structure.
	This function should be called just before DoneCUNILOG_TARGETstatic ();
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
#define ShutdownCUNILOG_TARGETstatic()					\
			ShutdownCUNILOG_TARGET (pCUNILOG_TARGETstatic)

/*
	CancelCUNILOG_TARGET

	Empties the logging queue for the CUNILOG_TARGET put without processing its events.
	The events currently in the queue are discarded. Logging functions called afterwards
	for this CUNILOG_TARGET structure fail and return false.

	The function waits for an existing separate logging thread to exit.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
bool CancelCUNILOG_TARGET (CUNILOG_TARGET *put);
TYPEDEF_FNCT_PTR (bool, CancelCUNILOG_TARGET) (CUNILOG_TARGET *put);

/*
	CancelCUNILOG_TARGETstatic

	Calls CancelCUNILOG_TARGET () on the internal static SUNILOGSTRUCT structure.
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined there is no queue to shut down or
	to cancel, but further logging is blocked. Logging functions called afterwards
	return false.

	The function returns true on success, false otherwise.
*/
#define CancelCUNILOG_TARGETstatic ()					\
			CancelCUNILOG_TARGET (pCUNILOG_TARGETstatic)

/*
	PauseLogCUNILOG_TARGET

	Pauses/suspends logging to the CUNILOG_TARGET structure put points to while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogCUNILOG_TARGET () to resume the separate logging thread.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	void PauseLogCUNILOG_TARGET (CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (void, PauseLogCUNILOG_TARGET) (CUNILOG_TARGET *put);
#else
	#define PauseLogCUNILOG_TARGET(put)
#endif

/*
	PauseLogCUNILOG_TARGETstatic

	Pauses/suspends logging to the internal CUNILOG_TARGET structure while still
	allowing logging functions to add events. After this function has been called, all
	future events are added to the queue only, with no actual logging or rotation taking
	place for these events.

	The separate logging thread itself is not paused by this function. It still continues
	to log and rotate logfiles for events enqueued before this function was called.

	Call ResumeLogCUNILOG_TARGETstatic () to resume the separate logging thread again.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define PauseLogCUNILOG_TARGETstatic()				\
		PauseLogCUNILOG_TARGET (pCUNILOG_TARGETstatic)
#else
	#define PauseLogCUNILOG_TARGETstatic()
#endif

/*
	ResumeLogCUNILOG_TARGET

	Resumes logging to the CUNILOG_TARGET structure put points to after a call to
	PauseLogCUNILOG_TARGET () and triggers it for each queued event since
	PauseLogCUNILOG_TARGET () was called.

	The function returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogCUNILOG_TARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	size_t ResumeLogCUNILOG_TARGET (CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (size_t, ResumeLogCUNILOG_TARGET) (CUNILOG_TARGET *put);
#else
	#define ResumeLogCUNILOG_TARGET(put)
#endif

/*
	ResumeLogCUNILOG_TARGETstatic

	Resumes logging to the internal CUNILOG_TARGET structure after a call to
	PauseLogCUNILOG_TARGET () and triggers it for each queued event since
	PauseLogCUNILOG_TARGET () was called.

	The macro returns the number of events in the queue it has triggered for
	processing by the separate logging thread.

	Note that this function triggers the semaphore of the separate logging thread for
	every single queue element (logging event) that was queued since the last call
	to PauseLogCUNILOG_TARGET (). Depending on the amount of queued events, this might
	be considered a block. Although the WinAPI function ReleaseSemaphore () supports
	increments of more than one, sem_post () from the POSIX spec does not. Therefore,
	on POSIX this function loops and increments the semaphore by 1 only and could
	possibly block.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to nothing.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define ResumeLogCUNILOG_TARGETstatic()			\
				ResumeLogCUNILOG_TARGET (pCUNILOG_TARGETstatic)
#else
	#define ResumeLogCUNILOG_TARGETstatic()		(0)
#endif

/*
	CreateCUNILOG_EVENT_Data

	Allocates a buffer that points to a new event structure CUNILOG_EVENT plus data,
	initialises it with the function parameters, and returns a pointer to the newly
	created and initialised structure and data buffer. The event is written out as binary
	data, which results in a hex dump.

	Note that you can NOT use USE_STRLEN as the parameter siz.

	The function returns false if it fails.
*/
CUNILOG_EVENT *CreateCUNILOG_EVENT_Data	(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz,
					const char					*ccCapt,
					size_t						lenCapt
											)
;
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, CreateCUNILOG_EVENT_Data)
(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccData,
					size_t						siz,
					const char					*ccCapt,
					size_t						lenCapt
											)
;

/*
	CreateCUNILOG_EVENT_Text

	This is the text version of CreateCUNILOG_EVENT_Data (). If the string ccText is
	NUL-terminated len can be set to USE_STRLEN, and the function calls strlen () to
	obtain its length.
*/
CUNILOG_EVENT *CreateCUNILOG_EVENT_Text		(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, CreateCUNILOG_EVENT_Text)
											(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len
											)
;

/*
	CreateCUNILOG_EVENT_TextTS

	This function is identical to CreateCUNILOG_EVENT_Text () but expects the timestamp
	for the event in the additional UBF_TIMESTAMP parameter ts.
*/
CUNILOG_EVENT *CreateCUNILOG_EVENT_TextTS		(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len,
					UBF_TIMESTAMP				ts
											)
;
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, CreateCUNILOG_EVENT_TextTS)
											(
					CUNILOG_TARGET				*put,
					cueventseverity				sev,
					const char					*ccText,
					size_t						len,
					UBF_TIMESTAMP				ts
											)
;

/*
	DuplicateCUNILOG_EVENT

	Creates a copy of the event pev on the heap. If the event has a size other than
	sizeof (CUNILOG_EVENT) this is taken into consideration. The target of the newly
	created event is identical to the target of the event pev points to.

	Call DoneCUNILOG_EVENT () to destroy it.

	The function returns a pointer to a newly allocated event, which is an exact copy
	of pev apart from that the newly allocated event has the option flag CUNILOGEVENT_ALLOCATED
	set regardless of whether this flag was present in pev.
*/
CUNILOG_EVENT *DuplicateCUNILOG_EVENT (CUNILOG_EVENT *pev);
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, DuplicateCUNILOG_EVENT) (CUNILOG_EVENT *pev);

/*
	DoneCUNILOG_EVENT

	Destroys an SUNILOGEVENT structure including all its resources if the event belongs
	to target put. If put is NULL the event is destroyed regardless.

	The function always returns NULL.
*/
CUNILOG_EVENT *DoneCUNILOG_EVENT (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);
TYPEDEF_FNCT_PTR (CUNILOG_EVENT *, DoneCUNILOG_EVENT) (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);

/*
	Logging functions.
	==================
*/

/*
	logEv

	Writes out the event pev points to to the logging target put points to. The function
	only sets the pCUNILOG_TARGET member of the CUNILOG_EVENT structure and calls
	cunilogProcessOrQueueEvent () on it.

	Returns true on success, false otherwise. The function fails after ShutdownCUNILOG_TARGET ()
	or CancelCUNILOG_TARGET () have been called on the CUNILOG_TARGET structure put points to.
*/
bool logEv (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);
TYPEDEF_FNCT_PTR (bool, logEv) (CUNILOG_TARGET *put, CUNILOG_EVENT *pev);


/*
	logEv_static

	Macro wrapper for the static version of logEv () that uses the module's internal static
	structure and does not require a pointer to a CUNILOG_TARGET structure as their first
	parameter.
*/
#define logEv_static(pev)	logEv (pCUNILOG_TARGETstatic, (pev))

/*
	The functions expect an CUNILOG_TARGET structure as their first parameter.
	The _static macros use the module's internal static structure and do not require
	a pointer to a CUNILOG_TARGET structure as their first parameter. If you only intend to
	write to a single logfile, the _static macros are ideal.

	The logText functions or macros expect text output.
	The logHexDump functions expect text and binary data to output a hex dump with the text
	as caption.

	The logHexDump () function outputs a hex dump. The function logHexOrText () examines the
	provided data and treats it either as ASCII or binary data for a hex dump. The function
	logHexOrTextU8 () also accepts UTF-8 as text and creates a hex dump if the data to output
	contains invalid UTF-8.

	The functions without a severity use severity level/severity type cunilogEvtSeverityNone.
	Functions containing sev in their names accept a severity type.

	Functions that have U8 in their names are for UTF-8, the ones with a WU16 are intended for
	Windows UTF-16 encoding. On POSIX systems the WU16 functions are not available.

	Functions whose name contains a c only output to the console. Other processors are simply
	ignored.

	Function names with an l accept a length parameter for the text's length, in octets/bytes.
	You can use USE_STRLEN for this parameter, in which case the text buffer's length is obtained
	via a call to strlen () and the string needs to be NUL-terminated. NUL-termination is not
	required otherwise. Note that the length parameter denotes the length of the text, in octets,
	not its size, and also not in characters. The text "abc" has a length of 3 but a size of 4
	octets, which includes the NUL-terminator. UTF-8 characters can have up to 4 octets/bytes.
	Cunilog writes out only UTF-8 but doesn't actually understand its encoding.

	Functions ending in ts expect the timestamp of the event in an additional UBF_TIMESTAMP
	parameter.

	The vfmt versions are variadic functions/macros that expect a va_list argument. Note that
	these functions/macros are normal logging functions and do not compose the output and write
	to a buffer provided by the caller like standard library functions vsnprintf () and family
	would.

	The fmt versions offer variadic functionality like printf () does. The function
	logTextU8fmt () uses an additional memory allocation and deallocation internally. The sfmt
	type functions like logTextU8sfmt () attempt to use the stack for the fmt output if less
	than CUNILOG_DEFAULT_SFMT_SIZE bytes are required. Otherwise the heap is used.
	
	Function names containing a "q" (for quick) do not invoke any rotation processors.

	The functions logTextU8smbfmtsev () and logTextU8smbfmt () additionally expect an
	initialised parameter structure of type SMEMBUF. The SMEMBUF structure can be re-used
	for consecutive calls. Within the same thread this can save memory allocations if the
	functions are called several times. Example:

	SMEMBUF smb = SMEMBUF_INITIALISER;
	logTextU8smbfmt_static (&smb, "Text to log");
	logTextU8smbfmt_static (&smb, "Another text to log");
	doneSMEMBUF (&smb);

	All functions return true on success, false otherwise. Functions may for instance fail if
	a memory allocation fails or if a separate logging thread failed to start.
	They also fail after ShutdownCUNILOG_TARGET () or CancelCUNILOG_TARGET () have been called
	on the CUNILOG_TARGET structure put points to.
*/
bool logTextU8sevl			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8sevlts		(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8sevlq			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8sevlqts		(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8sev			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8sevq			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8l				(CUNILOG_TARGET *put, const char *ccText, size_t len);
bool logTextU8lts			(CUNILOG_TARGET *put, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8lq			(CUNILOG_TARGET *put, const char *ccText, size_t len);
bool logTextU8lqts			(CUNILOG_TARGET *put, const char *ccText, size_t len, UBF_TIMESTAMP ts);
bool logTextU8				(CUNILOG_TARGET *put, const char *ccText);
bool logTextU8q				(CUNILOG_TARGET *put, const char *ccText);
bool logTextU8vfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8fmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8qvfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8qfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8svfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8sfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8sqvfmt		(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8sqfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8svfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8sfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbvfmtsev	(CUNILOG_TARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8smbfmtsev		(CUNILOG_TARGET *put, SMEMBUF *smb, cueventseverity sev, const char *fmt, ...);
bool logTextU8smbvfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, va_list ap);
bool logTextU8smbfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logHexDumpU8sevl		(CUNILOG_TARGET *put, cueventseverity sev, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDumpU8l			(CUNILOG_TARGET *put, const void *pBlob, size_t size, const char *ccCaption, size_t lenCaption);
bool logHexDump				(CUNILOG_TARGET *put, const void *pBlob, size_t size);
bool logHexDumpq			(CUNILOG_TARGET *put, const void *pBlob, size_t size);
bool logHexOrText			(CUNILOG_TARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt);
bool logHexOrTextq			(CUNILOG_TARGET *put, const void *szHexOrTxt, size_t lenHexOrTxt);
bool logHexOrTextU8			(CUNILOG_TARGET *put, const void *szHexOrTxtU8, size_t lenHexOrTxtU8);

#ifdef PLATFORM_IS_WINDOWS
bool logTextWU16sevl		(CUNILOG_TARGET *put, cueventseverity sev, const wchar_t *cwText, size_t len);
bool logTextWU16sev			(CUNILOG_TARGET *put, cueventseverity sev, const wchar_t *cwText);
bool logTextWU16l			(CUNILOG_TARGET *put, const wchar_t *cwText, size_t len);
bool logTextWU16			(CUNILOG_TARGET *put, const wchar_t *cwText);
#endif

// Console output only. No other processors are invoked.
bool logTextU8csevl			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText, size_t len);
bool logTextU8csev			(CUNILOG_TARGET *put, cueventseverity sev, const char *ccText);
bool logTextU8cl			(CUNILOG_TARGET *put, const char *ccText, size_t len);
bool logTextU8c				(CUNILOG_TARGET *put, const char *ccText);
bool logTextU8cvfmt			(CUNILOG_TARGET *put, const char *fmt, va_list ap);
bool logTextU8cfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8csfmt			(CUNILOG_TARGET *put, const char *fmt, ...);
bool logTextU8csmbvfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, va_list ap);
bool logTextU8csmbfmt		(CUNILOG_TARGET *put, SMEMBUF *smb, const char *fmt, ...);
bool logTextU8csvfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, va_list ap);
bool logTextU8csfmtsev		(CUNILOG_TARGET *put, cueventseverity sev, const char *fmt, ...);

#define logTextU8sevl_static(v, t, l)	logTextU8sevl		(pCUNILOG_TARGETstatic, (v), (t), (l))
#define logTextU8sevlts_static(v, t, l, ts)				\
										logTextU8sevlts		(pCUNILOG_TARGETstatic, (v), (t), (l), (ts))
#define logTextU8sevlq_static(v, t, l)	logTextU8sevlq		(pCUNILOG_TARGETstatic, (v), (t), (l))
#define logTextU8sev_static(v, t)		logTextU8sevl		(pCUNILOG_TARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8sevq_static(v, t)		logTextU8sevq		(pCUNILOG_TARGETstatic, (v), (t), USE_STRLEN)
#define logTextU8l_static(t, l)			logTextU8l			(pCUNILOG_TARGETstatic, (t), (l))
#define logTextU8lts_static(t, l, ts)	logTextU8lts		(pCUNILOG_TARGETstatic, (t), (l), (ts))
#define logTextU8lq_static(t, l)		logTextU8lq			(pCUNILOG_TARGETstatic, (t), (l))
#define logTextU8lqts_static(t, l, ts)	logTextU8lqts		(pCUNILOG_TARGETstatic, (t), (l), (ts))
#define logTextU8_static(t)				logTextU8l			(pCUNILOG_TARGETstatic, (t), USE_STRLEN)
#define logTextU8q_static(t)			logTextU8lq			(pCUNILOG_TARGETstatic, (t), USE_STRLEN)
#define logTextU8fmt_static(...)		logTextU8fmt		(pCUNILOG_TARGETstatic, __VA_ARGS__)
#define logTextU8qvfmt_static(t, ap)	logTextU8qvfmt		(pCUNILOG_TARGETstatic, (t), (ap))
#define logTextU8qfmt_static(...)		logTextU8qfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__)
#define logTextU8sqvfmt_static(t, ap)	logTextU8sqvfmt		(pCUNILOG_TARGETstatic, (t), (ap));
#define logTextU8sfmt_static(...)		logTextU8sfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__)
#define logTextU8sfmtsev_static(s, ...)	logTextU8sfmtsev	(pCUNILOG_TARGETstatic, (s), __VA_ARGS__)
#define logTextU8smbfmtsev_static(s, m, ...)			\
										logTextU8smbfmtsev	(pCUNILOG_TARGETstatic, (s), (m), __VA_ARGS__)
#define logTextU8smbfmt_static(m, ...)	logTextU8smbfmt		(pCUNILOG_TARGETstatic, (m), __VA_ARGS__)
#define logHexDumpU8sevl_static(s, d, n, c, l)			\
										logHexDumpU8sevl	(pCUNILOG_TARGETstatic, (s), (d), (n), (c), (l))
#define logHexDumpU8l_static(d, n, c,					\
			l)							logHexDumpU8l		(pCUNILOG_TARGETstatic, (d), (n), (c), (l))
#define logHexDump_static(d, s)			logHexDump			(pCUNILOG_TARGETstatic, (d), (s))
#define logHexOrText_static(d, s)		logHexOrText		(pCUNILOG_TARGETstatic, (d), (s))
#define logHexOrTextU8_static(d, s)		logHexOrTextU8		(pCUNILOG_TARGETstatic, (d), (s))

#ifdef PLATFORM_IS_WINDOWS
#define logTextWU16sevl_static(v, t, l)	logTextWU16sevl		(pCUNILOG_TARGETstatic, (v), (t), (l))
#define logTextWU16sev_static(v, t)		logTextWU16sevl		(pCUNILOG_TARGETstatic, (v), (t), USE_STRLEN)
#define logTextWU16l_static(t, l)		logTextWU16l		(pCUNILOG_TARGETstatic, (t), (l))
#define logTextWU16_static(t)			logTextWU16l		(pCUNILOG_TARGETstatic, (t), USE_STRLEN);
#endif

// Console output only. No other processors are invoked.
#define logTextU8csevl_static(s, t, l)	logTextU8csevl		(pCUNILOG_TARGETstatic, (s), (t), (l));
#define logTextU8csev_static(s, t)		logTextU8csev		(pCUNILOG_TARGETstatic, (s), (t));
#define logTextU8cl_static(t, l)		logTextU8cl			(pCUNILOG_TARGETstatic, (t), (l));
#define logTextU8c_static(t)			logTextU8c			(pCUNILOG_TARGETstatic, (t));
#define logTextU8cvfmt_static(t, ap)	logTextU8cvfmt		(pCUNILOG_TARGETstatic, (t), (ap));
#define logTextU8cfmt_static(...)		logTextU8cfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__);
#define logTextU8csfmt_static(...)		logTextU8csfmt		(pCUNILOG_TARGETstatic, __VA_ARGS__);
#define logTextU8csmbvfmt_static(m, t, ap)				\
										logTextU8csmbvfmt	(pCUNILOG_TARGETstatic, (m), (t), (ap));
#define logTextU8csmbfmt_static(m, ...)	logTextU8csmbfmt	(pCUNILOG_TARGETstatic, (m), __VA_ARGS__);
#define logTextU8csvfmtsev_static(s, t, ap)				\
										logTextU8csvfmtsev	(pCUNILOG_TARGETstatic, (s), (t), (ap));
#define logTextU8csfmtsev_static(s, ...)				\
										logTextU8csfmtsev	(pCUNILOG_TARGETstatic, (s), __VA_ARGS__);

/*	ChangeCUNILOG_TARGETuseColourForEcho
	ChangeCUNILOG_TARGETuseColorForEcho
	ChangeCUNILOG_TARGETuseColourForEcho_static
	ChangeCUNILOG_TARGETuseColorForEcho_static

	Creates and queues an event that changes the colour output of event severity
	types. A value of false for bUseColour disables coloured output. A value of true
	switches it on.

	The _static versions of the function/macros use the internal static CUNILOG_TARGET
	structure.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETuseColourForEcho (CUNILOG_TARGET *put, bool bUseColour)
	;
	#define ChangeCUNILOG_TARGETuseColourForEcho_static(bc)	\
				ChangeCUNILOG_TARGETuseColourForEcho (pCUNILOG_TARGETstatic, (bc))
	#define ChangeCUNILOG_TARGETuseColorForEcho(p, bc)		\
				ChangeCUNILOG_TARGETuseColourForEcho ((p), (bc))
	#define ChangeCUNILOG_TARGETuseColorForEcho_static(bc)	\
				ChangeCUNILOG_TARGETuseColourForEcho (pCUNILOG_TARGETstatic, (bc))
#endif

/*
	ChangeCUNILOG_TARGETcunilognewline
	ChangeCUNILOG_TARGETcunilognewline_static

	Creates and queues an event that changes the member unilogNewLine of the CUNILOG_TARGET
	structure put points to to the value of nl.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETcunilognewline (CUNILOG_TARGET *put, newline_t nl)
	;
	#define ChangeCUNILOG_TARGETcunilognewline_static(nl)	\
				ChangeCUNILOG_TARGETcunilognewline (pCUNILOG_TARGETstatic, (nl))
#endif

/*
	ChangeCUNILOG_TARGETdisableTaskProcessors
	ChangeCUNILOG_TARGETenableTaskProcessors

	The functions return true if the event was queued successfully, false otherwise.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);
	bool ChangeCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);

	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETdisableTaskProcessors) (CUNILOG_TARGET *put, enum cunilogprocesstask task);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETenableTaskProcessors) (CUNILOG_TARGET *put, enum cunilogprocesstask task);
#endif

/*
	ChangeCUNILOG_TARGETdisableEchoProcessor
	ChangeCUNILOG_TARGETenableEchoProcessor

	The functions return true if the event was queued successfully, false otherwise.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
	bool ChangeCUNILOG_TARGETdisableEchoProcessor	(CUNILOG_TARGET *put);
	bool ChangeCUNILOG_TARGETenableEchoProcessor	(CUNILOG_TARGET *put);

	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETdisableEchoProcessor)	(CUNILOG_TARGET *put);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETenableEchoProcessor)	(CUNILOG_TARGET *put);
#endif

/*
	ChangeCUNILOG_TARGETeventSeverityFormatType

	Queues an event to set the format type of event severities for the target structure put.
	It sets the member evSeverityType of the CUNILOG_TARGET structure put to the
	value of eventSeverityFormatType.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	bool ChangeCUNILOG_TARGETeventSeverityFormatType (CUNILOG_TARGET *put, cueventsevfmtpy sevTpy);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETeventSeverityFormatType)
		(CUNILOG_TARGET *put, cueventsevfmtpy sevTpy);
#endif
#endif

/*
	ChangeCUNILOG_TARGETlogPriority

	Queues an event to set the priority of the separate logging thread that belongs to the
	specified CUNILOG_TARGET structure put points to.
	
	If CUNILOG_BUILD_SINGLE_THREADED_ONLY or CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS are defined,
	this is a macro that evaluates to true.

	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file),
	although they are not really nice values as the priority is applied to the separate
	logging thread only.
	Neither the table nor this function have been tested to ensure the approximations
	for POSIX are accurate.

	Windows systems support cunilogPrioBeginBackground and cunilogPrioEndBackground. These
	values change the separate logging thread's priority to THREAD_MODE_BACKGROUND_BEGIN and
	THREAD_MODE_BACKGROUND_END respectively. See
	https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority
	for details.
	Since directly comparable functionality is not available on POSIX,
	cunilogPrioBeginBackground is identical to cunilogPrioIdle, which sets the thread priority
	value to 19, and cunilogPrioEndBackground is identical to a value of 0, which means normal
	priority. See https://www.man7.org/linux/man-pages/man3/pthread_setschedprio.3.html .

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the CUNILOG_TARGET structure doesn't
	have a separate logging thread, the function returns true. The function returns false if the
	value for prio is invalid.
*/
#if !defined (CUNILOG_BUILD_SINGLE_THREADED_ONLY) && !defined (CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS)
	bool ChangeCUNILOG_TARGETlogPriority (CUNILOG_TARGET *put, cunilogprio prio);
	TYPEDEF_FNCT_PTR (bool, ChangeCUNILOG_TARGETlogPriority) (CUNILOG_TARGET *put, cunilogprio prio);
#else
	#define ChangeCUNILOG_TARGETlogPriority(put, prio) (true)
#endif

/*
	ChangeCUNILOG_TARGETlogPriority_static

	Sets the priority of the separate logging thread that belongs to the internal static
	CUNILOG_TARGET structure.

	The priority levels are based on Windows thread priority levels. See the cunilogprio
	enum type (parameter prio) for possible values. For POSIX, these have been placed in
	a table with nice values as approximations (table icuWinPrioTable; see code file).
	Neither the table nor this function have been tested to ensure the approximations
	are accurate.

	If CUNILOG_BUILD_SINGLE_THREADED_ONLY is defined, this is a macro that evaluates
	to true.

	Returns true on success, false otherwise. If the CUNILOG_TARGET structure doesn't
	have a separate logging thread, the function returns true.
*/
#ifndef CUNILOG_BUILD_SINGLE_THREADED_ONLY
	#define ChangeCUNILOG_TARGETlogPriority_static(prio)	\
				ChangeCUNILOG_TARGETlogPriority (pCUNILOG_TARGETstatic, prio)
#else
	#define ChangeCUNILOG_TARGETlogPriority_static(prio) (true)
#endif

/*
	CunilogChangeCurrentThreadPriority

	Sets the priority of the current thread.

	This is a platform-independent way of changing the current thread's priority.

	The function returns true on success, false otherwise.
*/
bool CunilogChangeCurrentThreadPriority (cunilogprio prio);
TYPEDEF_FNCT_PTR (bool, CunilogChangeCurrentThreadPriority) (cunilogprio prio);

/*
	cunilogSetDefaultPrintEventSeverityFormatType

	Sets the default event severity format type that is used by the cunilog_printf...
	and cunilog_puts... type functions (see below).

*/
void cunilogSetDefaultPrintEventSeverityFormatType (cueventsevfmtpy fmtpy);
TYPEDEF_FNCT_PTR (void, cunilogSetDefaultPrintEventSeverityFormatType) (cueventsevfmtpy fmtpy);

/*
	cunilogUseColourForOutput

	Coloured output for the cunilog_printf... and cunilog_puts... type funcitons (see
	below).

	Configures whether ANSI escape sequences are inserted in the output to enable colours.
	The default is true, meaning that by default event severities are sent to the console
	with ANSI escape colour sequences enabled.
*/
void cunilogUseColourForOutput (bool bUseColour);
TYPEDEF_FNCT_PTR (void, cunilogUseColourForOutput) (bool bUseColour);

/*
	cunilog_printf_sev_fmtpy_vl
	cunilog_printf_sev_fmtpy
	cunilog_printf_sev
	cunilog_printf
	cunilog_puts_sev_fmtpy_l
	cunilog_puts_sev_fmtpy
	cunilog_puts_sev_l
	cunilog_puts_sev
	cunilog_puts_l
	cunilog_puts

	The Cunilog printf () and puts () functions.

	The _sev_fmtpy_vl versions expect a severity, a serverity format type, and a va_list
	argument. The _sev_fmtpy versions expect a severity and a severity format type while
	the _sev versions expect a severity only.

	The _l functions expect a length parameter. The value USE_STRLEN can be provided instead
	of the length, in which case these functions use strlen () to obtain it.

	None of these functions abide by the NO_COLOR standard (see https://no-color.org/).
	To make an application NO_COLOR complient, guard them with the return value of
	Cunilog_Have_NO_COLOR ().

	bool bUserWantsColour = !Cunilog_Have_NO_COLOR ();		// At application start.

	if (bUserWantsColour)
		cunilogUseColourForOutput (true);
	else
		cunilogUseColourForOutput (false);

	Or, simpler, since the default is to use ANSI escape colours:

	if (Cunilog_Have_NO_COLOR ())
		cunilogUseColourForOutput (false);

	The functions cunilog_printf () and cunilog_puts () are replacements for the standard
	library functions printf () and puts () respectively. These functions honour Cunilog's
	console settings functions CunilogSetConsoleToUTF8 (), CunilogSetConsoleToUTF16 (),
	and CunilogSetConsoleToNone () on Windows, and its default output severity format functions
	cunilogSetDefaultPrintEventSeverityFormatType (), and cunilogUseColourForOutput ().

*/
int cunilog_printf_sev_fmtpy_vl	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		va_list				ap
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf_sev_fmtpy_vl)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		va_list				ap
								)
;


int cunilog_printf_sev_fmtpy	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		...
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf_sev_fmtpy)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*format,
		...
								)
;


int cunilog_printf_sev			(
		cueventseverity		sev,
		const char			*format,
		...
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf_sev)
								(
		cueventseverity		sev,
		const char			*format,
		...
								)
;

int cunilog_printf				(
		const char			*format,
		...
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_printf)
								(
		const char			*format,
		...
								)
;

int cunilog_puts_sev_fmtpy_l	(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8,
		size_t				len
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev_fmtpy_l)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8,
		size_t				len
								)
;

int cunilog_puts_sev_fmtpy		(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev_fmtpy)
								(
		cueventseverity		sev,
		cueventsevfmtpy		sftpy,
		const char			*strU8
								)
;


int cunilog_puts_sev_l			(
		cueventseverity		sev,
		const char			*strU8,
		size_t				len
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev_l)
								(
		cueventseverity		sev,
		const char			*strU8,
		size_t				len
								)
;

int cunilog_puts_sev			(
		cueventseverity		sev,
		const char			*strU8
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_sev)
								(
		cueventseverity		sev,
		const char			*strU8
								)
;

int cunilog_puts_l				(
		const char			*strU8,
		size_t				len
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts_l)
								(
		const char			*strU8,
		size_t				len
								)
;

int cunilog_puts				(
		const char			*strU8
								)
;
TYPEDEF_FNCT_PTR (int, cunilog_puts)
								(
		const char			*strU8
								)
;

/*
	The version as text, its year, and as a 64 bit number.
	Currently still unsupported.
*/
extern const char		ccCunilogVersionText [];
extern const char		ccCunilogVersionYear [];
extern const uint64_t	uiCunilogVersion;

/*
	cunilogCheckVersion

	Compares the version of cunilog.c with the version of cunilogversion.h and returns
	the result of the comparison.

	-1		The version of cunilog.c is less than the one in cunilogversion.h.
	0		The version of cunilog.c is identical to the one in cunilogversion.h.
	1		The version of cunilog.c is greater than the one in cunilogversion.h.

	When cunilog is built as a static library, an application includes cunilog_combined.h
	only. This function/macro ensures that the static library and cunilog_combined.h (actually:
	cunilogversion.h) fit together.

	The function aborts in debug versions. In release builds it merely returns the result
	of the comparison.

	Example:

	if (0 != cunilogCheckVersion ())
	{
		puts ("Version of cunilog_combined.h and libcunilog different.");
		return EXIT_FAILURE;
	}
*/
#define CUNILOG_VERSION_HDR							\
(		((uint64_t) CUNILOG_VERSION_MAJOR	<< 48)	\
	|	((uint64_t) CUNILOG_VERSION_MINOR	<< 32)	\
	|	((uint64_t) CUNILOG_VERSION_SUB		<< 16)	\
	|	((uint64_t) CUNILOG_VERSION_BUILD)			\
)
int cunilogCheckVersionIntChk (uint64_t cunilogHdrVersion);
#define cunilogCheckVersion() cunilogCheckVersionIntChk (CUNILOG_VERSION_HDR)

/*
	Tests
	=====
*/
#ifdef CUNILOG_BUILD_TEST_FNCTS
	bool test_cunilog (void);
#else
	#define test_cunilog()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifndef CUNILOG_H.
/****************************************************************************************

	File:		bottom.h
	Why:		Provides the bottom/foot of the combined cunilog.h header file.
	OS:			C99.
	Author:		Thomas
	Created:	2024-08-05

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-05	Thomas			Created.

****************************************************************************************/

#endif														// Of #ifndef CUNILOG_COMBINED_INCLUDED.
