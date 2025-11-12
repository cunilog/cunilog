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
	a directory separator), while SystemDirectoryU8len () obtains its length.

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
	
	To use this function, define HAVE_USER32 and link to User32.lib.
*/
#ifdef HAVE_USER32
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
	
	To use this function, define HAVE_USER32 and link to User32.lib.
*/
#ifdef HAVE_USER32
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
	
	To use this function, define HAVE_USER32 and link to User32.lib.
*/
#ifdef HAVE_USER32
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

	The caller can control which of the above attempts is made but the order of these
	attempts is currently fixed. The caller can further control if the function should
	wait after each of these attempts. For instance, to only attempt to terminate the
	process by sending it a CTRL-Break event, set uiFlags to
	TERMCHILDPROCCONTROLLED_CTRL_BREAK | TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK.
	This instructs the function to attempt a CTRL-Break and then wait waitTime
	milliseconds for the process to exit. Specify all TERMCHILDPROCCONTROLLED_ flags
	for the attempts that should be made, and specify the additional
	TERMCHILDPROCCONTROLLED_WAIT_ flags to wait for the process to exit after the attempt
	in question.

	The function returns true if the process has exited within waitTime ms after each
	termination attempt. It returns false if the process has not exited within waitTime.

	Note that waitTime is waited for after each separate attempt to terminate the process.
	For instance, if you specify the flags TERMCHILDPROCCONTROLLED_CTRL_C to attempt
	sending CTRL-C and TERMCHILDPROCCONTROLLED_WAIT_CTRL_C to wait for its success, plus
	TERMCHILDPROCCONTROLLED_CTRL_BREAK and TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK to
	send CTRL-Break and wait for it to succeed, the function waits up to twice waitTime
	in case the first attempt (CTRL-C) is unsuccessful.
*/
#ifdef HAVE_USER32
bool TerminateProcessControlled (HANDLE hProcess, uint16_t uiFlags, DWORD waitTime);
TYPEDEF_FNCT_PTR (bool, TerminateProcessControlled) (HANDLE hProcess, uint16_t uiFlags, DWORD waitTime);
#endif

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
	and disposes of it if it is an executable argument.

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
