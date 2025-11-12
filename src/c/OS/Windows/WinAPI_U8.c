/****************************************************************************************

	File		WinAPI_U8.c
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

#ifdef _WIN32

#include <Windows.h>
#include <limits.h>
#include <malloc.h>

#include <io.h>
#include <fcntl.h>

#ifdef _MSC_VER
	#include <crtdbg.h>
#endif

/*
	2025-11-11, Thomas:
	HAVE_WINUSER changed to HAVE_USER32
*/
#ifdef HAVE_WINUSER
	#ifndef HAVE_USER32
	#define HAVE_USER32
	#endif
#endif

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_U8.h"

	#ifdef HAVE_STRWILDCARDS
		#if defined (UBF_STRWILDCARDS_USE_CURR_DIR) || defined (UBF_USE_FLAT_FOLDER_STRUCTURE)
			#include "./strwildcards.h"
		#else
			#include "./../../string/strwildcards.h"
		#endif
		#ifdef WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH
			#include "./../../string/strslashes.h"
		#endif
	#endif

#endif

WCHAR		wcLongFileNamePrefix []	= L"\\\\?\\";				// "\\?\" prefix for very
																//	long filenames.
const char	ccLongFileNamePrefix [] = "\\\\?\\";				// The ASCII/UTF-8 version.
// The length of the long filename prefix in characters, exlcuding the NUL-terminator.
#define LENOF_LONGFILENAMEPREFIX						\
	((sizeof (ccLongFileNamePrefix)) - 1)

#ifdef WINAPIU8_CONVERT_FORWARD_TO_BACKSLASH
	// Uses the functions in strslashes.h.
#else
	// Dummy macros.
	#define forward_to_backslashU8(s,l)
	#define forward_to_backslashW(w,l)
#endif

#ifndef UNICODE
	/*
		MSVC might be set to "Use Multi-Byte Character Set" or "Not set".
		This is not what we want.
		Go to the project properties, General, Character Set, and change it to
		"Use Unicode Character Set" for all configurations.
	*/
	#error This module can only be used in Windows applications compiled for unicode (Use Unicode Character Set)
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int reqUTF8size (const WCHAR *wcU16)
	{
		return WideCharToMultiByte (CP_UTF8, 0, wcU16, -1, NULL, 0, NULL, NULL);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int reqUTF8sizel (const WCHAR *wcU16, int lenU16)
	{
		return WideCharToMultiByte (CP_UTF8, 0, wcU16, lenU16, NULL, 0, NULL, NULL);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int UTF8_from_WinU16 (char *chU8, int sizeU8, const WCHAR *wcU16)
	{
		return WideCharToMultiByte (CP_UTF8, 0, wcU16, -1, chU8, sizeU8, NULL, NULL);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int UTF8_from_WinU16l (char *chU8, int sizeU8, const WCHAR *wcU16, int lenU16)
	{
		return WideCharToMultiByte (CP_UTF8, 0, wcU16, lenU16, chU8, sizeU8, NULL, NULL);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int reqWinU16wchars (const char *chU8)
	{
		return MultiByteToWideChar (CP_UTF8, 0, chU8, -1, NULL, 0);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	int WinU16_from_UTF8 (WCHAR *wcU16, int sizeU16, const char *chU8)
	{
		return MultiByteToWideChar (CP_UTF8, 0, chU8, -1, wcU16, sizeU16);
	}
#endif

int reqWinU16wcharsFileName (const char *ccU8FileName)
{
	if (!strncmp (ccU8FileName, ccLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX))
	{
		return reqWinU16wchars (ccU8FileName);
	} else
	{
		return reqWinU16wchars (ccU8FileName) + (int) LENOF_LONGFILENAMEPREFIX;
	}
}

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	BOOL HasLongFileNamePrefixW (const WCHAR *wcFileName)
	{
		ASSERT (NULL != wcFileName);
		if (wcFileName)
		{
			return !wcsncmp (wcFileName, wcLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX);
		}
		return FALSE;
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	BOOL HasLongFileNamePrefixU8 (const char *ccFileName)
	{
		ASSERT (NULL != ccFileName);
		if (ccFileName)
		{
			return !strncmp (ccFileName, ccLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX);
		}
		return FALSE;
	}
#endif

int WinU16_from_UTF8_FileName (WCHAR *wcU16FileName, int sizeU16, const char *ccU8FileName)
{
	if (!strncmp (ccU8FileName, ccLongFileNamePrefix, LENOF_LONGFILENAMEPREFIX))
	{
		return WinU16_from_UTF8 (wcU16FileName, sizeU16, ccU8FileName);
	} else
	{
		ASSERT (LENOF_LONGFILENAMEPREFIX == LENOFLONGFILENAMEPREFIX);
		if (sizeU16 > (int) LENOF_LONGFILENAMEPREFIX)
		{
			int	iRet;

			wcsncpy_s (wcU16FileName, sizeU16, wcLongFileNamePrefix, _TRUNCATE);
			iRet = WinU16_from_UTF8	(
						wcU16FileName + LENOF_LONGFILENAMEPREFIX,
						sizeU16 - LENOF_LONGFILENAMEPREFIX,
						ccU8FileName
									)
					+ LENOF_LONGFILENAMEPREFIX;
			forward_to_backslashW (wcU16FileName, sizeU16);
			return iRet;
		}
		// Output buffer too short.
		return 0;
	}
}

WCHAR *AllocWinU16_from_UTF8 (const char *ccU8)
{
	WCHAR	*pwc	= NULL;
	
	if (ccU8)
	{
		int	iRequiredSize = reqWinU16wchars (ccU8);
		pwc = ubf_malloc (iRequiredSize * sizeof (WCHAR));
		if (pwc)
			WinU16_from_UTF8 (pwc, iRequiredSize, ccU8);
	}
	return pwc;
}

WCHAR *AllocWinU16_from_UTF8_00 (const char *ccU8)
{
	WCHAR	*pwc	= NULL;
	
	if (ccU8)
	{
		int	iRequiredSize = reqWinU16wchars (ccU8) + 1;
		pwc = ubf_malloc (iRequiredSize * sizeof (WCHAR));
		if (pwc)
		{
			WinU16_from_UTF8 (pwc, iRequiredSize, ccU8);
			pwc [iRequiredSize - 1] = ASCII_NUL;
			return pwc;
		}
	}
	return NULL;
}

WCHAR *AllocWinU16_from_UTF8_FileName (const char *ccU8FileName)
{
	WCHAR	*pwc	= NULL;
	
	if (ccU8FileName)
	{
		int	iRequiredSize = reqWinU16wcharsFileName (ccU8FileName);
		pwc = ubf_malloc (iRequiredSize * sizeof (WCHAR));
		if (pwc)
		{
			WinU16_from_UTF8_FileName (pwc, iRequiredSize, ccU8FileName);
		}
	}
	return pwc;
}

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void DoneWinU16 (WCHAR *pwc)
	{
		if (pwc)
			ubf_free (pwc);
	}
#endif

char *AllocU8_from_WinU16l (const WCHAR *wc16, size_t ln16)
{
	ASSERT (ln16 < INT_MAX);

	char	*pc	= NULL;
	ln16 = USE_STRLEN == ln16 ? wcslen (wc16) : ln16;
	
	if (wc16)
	{
		int	iRequiredSize = reqUTF8sizel (wc16, (int) ln16);
		ASSERT (iRequiredSize < INT_MAX);
		pc = ubf_malloc (iRequiredSize + 1);
		if (pc)
		{
			UTF8_from_WinU16l (pc, iRequiredSize, wc16, (int) ln16);
			//pc [iRequiredSize] = ASCII_NUL;		//Intellisense doesn't like this.
			*(pc + iRequiredSize) = ASCII_NUL;
		}
	} else
	{
		ASSERT (0 == ln16);
		pc = ubf_malloc (1);
		if (pc)
			*pc = ASCII_NUL;
			//pc [0] = ASCII_NUL;					//Intellisense doesn't like this.
	}
	return pc;
}

char *AllocU8_from_WinU16 (const WCHAR *wc16)
{
	char	*pc	= NULL;
	
	if (wc16)
	{
		int	iRequiredSize = reqUTF8size (wc16);
		pc = ubf_malloc (iRequiredSize);
		if (pc)
		{
			UTF8_from_WinU16 (pc, iRequiredSize, wc16);
		}
	}
	return pc;
}

#ifdef HAVE_STRWILDCARDS
	char *AllocU8path_from_U8path_and_WinU16FileName (const char *ccPath, WCHAR *wcFileName)
	{
		ASSERT (NULL != ccPath);
		ASSERT (NULL != wcFileName);
	
		if (NULL == ccPath || NULL == wcFileName)
			return NULL;
		
		size_t		stPath		= strlen (ccPath);
		const char	*ccWCfname;
		size_t		stWCflen;										// Length of the wildcard
																	//	filename, if there is
																	//	one.
		char		*ccRet		= NULL;
		int			iReq;

		// Must not be an empty string or end with a directory separator.
		ASSERT (0 < stPath);										// Not supported.
		ASSERT ('\\' != ccPath [stPath - 1]);						// Not supported.
		ASSERT ('/' != ccPath [stPath - 1]);						// Not supported.
		if (0 == stPath)
			return NULL;
		ccWCfname = wildCardFileName (&stWCflen, ccPath);
		iReq = reqUTF8size (wcFileName);
		if (NULL == ccWCfname)
		{	// We got no wildcards in the filename. This is a simple copy operation.
			ccRet = ubf_malloc (stPath + iReq + 2);
			if (ccRet)
			{
				memcpy (ccRet, ccPath, stPath);
				memcpy (ccRet + stPath, "\\", 1);
				UTF8_from_WinU16 (ccRet + stPath + 1, iReq, wcFileName);
			}
			return ccRet;
		}
		// Note that iReq contains the NUL terminator already but to be sure we add
		//	2 octets more.
		ccRet = ubf_malloc (stPath + stWCflen + iReq + 2);
		if (ccRet)
		{
			if (ubf_isdirseparator (ccWCfname [0]))
				stPath -= stWCflen - 1;
			else
				stPath -= stWCflen;
			memcpy (ccRet, ccPath, stPath);
			UTF8_from_WinU16 (ccRet + stPath, iReq, wcFileName);
			/*
			if (ccWCfname && stWCflen)
			{	// We got a mask that needs to be added.
				memcpy (ccRet + stPath + iReq - 1, ccWCfname, stWCflen + 1);
			}
			*/
			forward_to_backslashU8 (ccRet, iReq);
		}
		return ccRet;
	}
#endif

#if defined (HAVE_STRWILDCARDS) && defined (HAVE_MEMBUF)
	bool U8pathSMEMBUF_from_U8path_and_WinU16FileName	(
					SMEMBUF				*pmbResult,
					const char			*ccPath,
					size_t				lnPath,
					WCHAR				*wcFileName
														)
	{
		ASSERT (isInitialisedSMEMBUF (pmbResult));
		ASSERT (NULL != ccPath);
		ASSERT (NULL != wcFileName);

		if (NULL == ccPath || NULL == wcFileName)
			return false;

		size_t		stPath		= USE_STRLEN == lnPath ? strlen (ccPath) : lnPath;
		const char	*ccWCfname;
		size_t		stWCflen;										// Length of the wildcard
																	//	filename, if there is
																	//	one.
		int			iReq;

		// Must not be an empty string or end with a directory separator.
		ASSERT (0 < stPath);										// Not supported.
		ASSERT ('\\' != ccPath [stPath - 1]);						// Not supported.
		ASSERT ('/' != ccPath [stPath - 1]);						// Not supported.
		if (0 == stPath)
			return false;
		ccWCfname = wildCardFileName (&stWCflen, ccPath);
		iReq = reqUTF8size (wcFileName);
		if (NULL == ccWCfname)
		{	// We got no wildcards in the filename. This is a simple copy operation.
			//ccRet = ubf_malloc (stPath + iReq + 2);
			growToSizeSMEMBUF (pmbResult, stPath + iReq + 2);
			if (isUsableSMEMBUF (pmbResult))
			{
				memcpy (pmbResult->buf.pch, ccPath, stPath);
				memcpy (pmbResult->buf.pch + stPath, "\\", 1);
				UTF8_from_WinU16 (pmbResult->buf.pch + stPath + 1, iReq, wcFileName);
				return true;
			}
			return false;
		}
		// Note that iReq contains the NUL terminator already but to be sure we add
		//	2 octets more.
		growToSizeSMEMBUF (pmbResult, stPath + stWCflen + iReq + 2);
		if (isUsableSMEMBUF (pmbResult))
		{
			stPath -= stWCflen - 1;								// We keep the dir separator.
			memcpy (pmbResult->buf.pch, ccPath, stPath);
			UTF8_from_WinU16 (pmbResult->buf.pch + stPath, iReq, wcFileName);
			if (ccWCfname && stWCflen)
			{	// We got a mask that needs to be added.
				memcpy (pmbResult->buf.pch + stPath + iReq - 1, ccWCfname, stWCflen + 1);
			}
			forward_to_backslashU8 (pmbResult->buf.pch, iReq);
			return true;
		}
		return false;
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void DoneU8 (char *pch)
	{
		if (pch)
			ubf_free (pch);
	}
#endif

WCHAR *AllocWinU16fromU8orUseThreshold (WCHAR *pwcStackVar, const char *pchU8)
{
	WCHAR	*pwcRet	= NULL;
	
	if (pchU8)
	{
		int		iLen;
		
		iLen = reqWinU16wchars (pchU8);
		if (iLen <= WINAPI_U8_HEAP_THRESHOLD)
		{
			WinU16_from_UTF8 (pwcStackVar, iLen, pchU8);
			pwcRet = pwcStackVar;
		} else
		{
			pwcRet = AllocWinU16_from_UTF8 (pchU8);
		}
	}
	return pwcRet;
}

WCHAR *AllocWinU16fromU8orUseThreshold_00 (WCHAR *pwcStackVar, const char *pchU8)
{
	WCHAR	*pwcRet	= NULL;
	
	if (pchU8)
	{
		int		iLen;
		
		iLen = reqWinU16wchars (pchU8) + 1;
		if (iLen <= WINAPI_U8_HEAP_THRESHOLD)
		{
			WinU16_from_UTF8 (pwcStackVar, iLen, pchU8);
			pwcStackVar [iLen - 1] = ASCII_NUL;
			pwcRet = pwcStackVar;
		} else
		{
			pwcRet = AllocWinU16_from_UTF8_00 (pchU8);
		}
	}
	return pwcRet;
}

WCHAR *AllocWinU16fromU8orUseThresholdLongFileName (WCHAR *pwcStackVar, const char *pchU8)
{
	int		iLen;
	WCHAR	*pwcRet	= NULL;
	
	if (pchU8)
	{
		iLen = reqWinU16wcharsFileName (pchU8);
		if (iLen <= WINAPI_U8_HEAP_THRESHOLD)
		{
			WinU16_from_UTF8_FileName (pwcStackVar, iLen, pchU8);
			pwcRet = pwcStackVar;
		} else
		{
			pwcRet = AllocWinU16_from_UTF8_FileName (pchU8);
		}
	}
	return pwcRet;
}

void DoneWinU16fromU8orUseThreshold (WCHAR *pwcHeapVar, WCHAR *pwcStackVar)
{
	ASSERT (NULL != pwcStackVar);
	if (pwcHeapVar && pwcHeapVar != pwcStackVar)
		DoneWinU16 (pwcHeapVar);
}

char *AllocU8fromWinU16orUseThresholdl (char *pszStackVar, const WCHAR *pwcU16, size_t lnU16)
{
	char	*szRet	= NULL;
	
	lnU16 = USE_STRLEN == lnU16 ? wcslen (pwcU16) : lnU16;
	ASSERT (lnU16 < INT_MAX);

	if (pwcU16)
	{
		int		iLen;
		
		iLen = reqUTF8sizel (pwcU16, (int) lnU16);
		if (iLen < WINAPI_U8_HEAP_THRESHOLD)
		{
			UTF8_from_WinU16l (pszStackVar, iLen, pwcU16, (int) lnU16);
			szRet = pszStackVar;
		} else
		{
			szRet = AllocU8_from_WinU16 (pwcU16);
		}
		if (iLen)
			szRet [iLen] = ASCII_NUL;
	}
	return szRet;
}

char *AllocU8fromWinU16orUseThreshold (char *pszStackVar, const WCHAR *pwcU16)
{
	return AllocU8fromWinU16orUseThresholdl (pszStackVar, pwcU16, USE_STRLEN);
}

void DoneU8fromWinU16orUseThreshold (char *pszHeapVar, char *pszStackVar)
{
	ASSERT (NULL != pszStackVar);
	if (pszHeapVar && pszHeapVar != pszStackVar)
		DoneU8 (pszHeapVar);
}

char **AllocU8ArgsFromWinU16 (int argc, WCHAR *argvw [])
{
	char **arr;
	
	arr = ubf_malloc (argc * sizeof (char *));
	if (arr)
	{
		int i = 0;
		while (i < argc)
		{
			arr [i] = AllocU8_from_WinU16 (argvw [i]);
			++ i;
		}
	}
	return arr;
}

void DoneU8Args (int argc, char *args [])
{
	char **arr = args;
	int i;
	
	for (i = 0; i < argc; ++ i)
	{
		DoneU8 (args [i]);
	}
	ubf_free (arr);
}

#ifdef HAVE_SHELLAPI
	#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		WCHAR **CmdLineArgsW (int *nArgs)
		{
			return CommandLineToArgvW (GetCommandLineW (), nArgs);
		}
	#endif
#endif

BOOL CopyFileU8(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
{
	WCHAR	wcExisting	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcNewFile	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcExisting;
	WCHAR	*pwcNewFile;
	BOOL	bRet		= FALSE;

	pwcExisting	= AllocWinU16fromU8orUseThreshold (wcExisting, lpExistingFileNameU8);
	pwcNewFile	= AllocWinU16fromU8orUseThreshold (wcNewFile, lpNewFileNameU8);
	bRet = CopyFileW (pwcExisting, pwcNewFile, bFailIfExists);
	DoneWinU16fromU8orUseThreshold (pwcExisting, wcExisting);
	DoneWinU16fromU8orUseThreshold (pwcNewFile, wcNewFile);
	return bRet;
}

BOOL CopyFileU8long(
	LPCSTR	lpExistingFileNameU8,
	LPCSTR	lpNewFileNameU8,
	BOOL	bFailIfExists
)
{
	WCHAR	wcExisting	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcNewFile	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcExisting;
	WCHAR	*pwcNewFile;
	BOOL	bRet		= FALSE;
	
	pwcExisting	= AllocWinU16fromU8orUseThresholdLongFileName (wcExisting, lpExistingFileNameU8);
	pwcNewFile	= AllocWinU16fromU8orUseThresholdLongFileName (wcNewFile, lpNewFileNameU8);
	bRet = CopyFileW (pwcExisting, pwcNewFile, bFailIfExists);
	DoneWinU16fromU8orUseThreshold (pwcExisting, wcExisting);
	DoneWinU16fromU8orUseThreshold (pwcNewFile, wcNewFile);
	return bRet;
}

BOOL CreateAllFoldersW (WCHAR *wcPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	DWORD	len						= (DWORD) wcslen (wcPath);

	if (len && len < WINAPI_U8_HEAP_THRESHOLD)
	{
		WCHAR	wcPathToCreate [WINAPI_U8_HEAP_THRESHOLD];
		memcpy (wcPathToCreate, wcPath, ((size_t) len + 1) * sizeof (WCHAR));

		WCHAR	*wc = wcPathToCreate;
		if (len > (sizeof (wcLongFileNamePrefix) - sizeof (WCHAR)) / sizeof (WCHAR))
		{
			// Ignore the long path prefix if we got one.
			if (!memcmp (wc, wcLongFileNamePrefix, sizeof (wcLongFileNamePrefix) - sizeof (WCHAR)))
			{
				wc += (sizeof (wcLongFileNamePrefix) - sizeof (WCHAR)) / sizeof (WCHAR);
				len -= (sizeof (wcLongFileNamePrefix) - sizeof (WCHAR)) / sizeof (WCHAR);
			}
		}
		// We don't want to call createDirectoryW on "D:" or "\\server".
		BOOL	bIgnoreFirst	= FALSE;
		if (len > 2)
		{
			if (!memcmp (wc, L"\\\\", 4))
			{	// Network resource "\\server".
				wc += 2;
				//len -= 2;
				bIgnoreFirst = TRUE;
			} else
			if (!memcmp (wc + 1, L":", sizeof (WCHAR)))
			{	// Root drive "D:"
				wc += 2;
				//len -= 2;
				bIgnoreFirst = TRUE;
			}
		}
		while (*wc)
		{
			while (*wc && L'\\' != *wc)
				++ wc;
			if (*wc)
			{
				*wc = L'\0';
				if (bIgnoreFirst)
				{
					bIgnoreFirst = FALSE;
				} else
				{
					CreateDirectoryIfNotExistsW (wcPathToCreate, lpSecurityAttributes);
				}
				*wc = L'\\';
				++ wc;
			}
		}
		return CreateDirectoryIfNotExistsW (wcPathToCreate, lpSecurityAttributes);
	}
	return FALSE;
}

BOOL CreateAllFoldersU8 (const char *szPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	WCHAR	wcPath	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcPath;
	BOOL	bRet		= FALSE;
	
	pwcPath	= AllocWinU16fromU8orUseThresholdLongFileName (wcPath, szPath);
	bRet = CreateAllFoldersW (pwcPath, lpSecurityAttributes);
	DoneWinU16fromU8orUseThreshold (pwcPath, wcPath);
	return bRet;
}

BOOL CreateDirectoryIfNotExistsW (WCHAR *wcDir, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	BOOL bRet = CreateDirectoryW (wcDir, lpSecurityAttributes);
	if (bRet)
	{
		return TRUE;
	} else
	{	// We want to return TRUE if it already exists.
		DWORD dwErr = GetLastError ();
		if (ERROR_ALREADY_EXISTS == dwErr)
			return TRUE;
	}
	return FALSE;
}

BOOL CreateDirectoryIfNotExistsU8 (const char *ccDirU8, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	BOOL bRet = CreateDirectoryU8 (ccDirU8, lpSecurityAttributes);
	if (bRet)
	{
		return TRUE;
	} else
	{	// We want to return TRUE if it already exists.
		DWORD dwErr = GetLastError ();
		if (ERROR_ALREADY_EXISTS == dwErr)
			return TRUE;
	}
	return FALSE;
}

BOOL CreateDirectoryU8(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
{
	WCHAR	wcPathName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcPathName;
	DWORD	dwRet		= FALSE;

	pwcPathName = AllocWinU16fromU8orUseThreshold (wcPathName, lpPathNameU8);
	dwRet = CreateDirectoryW (pwcPathName, lpSecurityAttributes);
	DoneWinU16fromU8orUseThreshold (pwcPathName, wcPathName);
	return dwRet;
}

BOOL CreateDirectoryU8long(
  LPCSTR                lpPathNameU8,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
)
{
	WCHAR	wcPathName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcPathName;
	DWORD	dwRet		= FALSE;

	pwcPathName = AllocWinU16fromU8orUseThresholdLongFileName (wcPathName, lpPathNameU8);
	dwRet = CreateDirectoryW (pwcPathName, lpSecurityAttributes);
	DoneWinU16fromU8orUseThreshold (pwcPathName, wcPathName);
	return dwRet;
}

HANDLE CreateEventU8(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCSTR                lpName
)
{
	if (lpName)
	{	// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventw .
		//	The name is limited to MAX_PATH characters.
		int iRequiredU16size = reqWinU16wcharsFileName (lpName);
		if (iRequiredU16size > MAX_PATH)
		{
			return NULL;
		}
		WCHAR	wcName [MAX_PATH + 1];
		WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpName);
		return CreateEventW (lpEventAttributes, bManualReset, bInitialState, wcName);
	}
	return CreateEventW (lpEventAttributes, bManualReset, bInitialState, NULL);
}

HANDLE CreateEventExU8(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
)
{
	if (lpName)
	{	// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventw .
		//	The name is limited to MAX_PATH characters.
		int iRequiredU16size = reqWinU16wcharsFileName (lpName);
		if (iRequiredU16size > MAX_PATH)
		{
			return NULL;
		}
		WCHAR	wcName [MAX_PATH + 1];
		WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpName);
		return CreateEventExW (lpEventAttributes, wcName, dwFlags, dwDesiredAccess);
	}
	return CreateEventExW (lpEventAttributes, NULL, dwFlags, dwDesiredAccess);
}

HANDLE CreateFileMappingU8(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCSTR                lpName
)
{
	if (lpName)
	{
		WCHAR	wcName [1024];
		WinU16_from_UTF8 (wcName, 1024, lpName);
		return CreateFileMappingW	(
					hFile, lpFileMappingAttributes, flProtect,
					dwMaximumSizeHigh, dwMaximumSizeLow, wcName
									);
	}
	return CreateFileMappingW	(
				hFile, lpFileMappingAttributes, flProtect,
				dwMaximumSizeHigh, dwMaximumSizeLow, NULL
								);
}

HANDLE CreateFileU8(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	HANDLE	hRet;
	
	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	hRet = CreateFileW	(
			pwcFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
			dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile
						);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return hRet;
}

HANDLE CreateFileU8long(
  LPCSTR                lpFileNameU8,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	HANDLE	hRet;
	
	pwcFileName = AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpFileNameU8);
	hRet = CreateFileW	(
			pwcFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
			dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile
						);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return hRet;
}

void STARTUPINFOW_from_STARTUPINFOA (STARTUPINFOW *siw, STARTUPINFOA *sia)
{
	ASSERT (NULL != siw);
	ASSERT (NULL != sia);
	ASSERT (NULL == sia->lpReserved);
	ASSERT (0 == sia->cbReserved2);
	ASSERT (NULL == sia->lpReserved2);
	ASSERT (sizeof (STARTUPINFOW) == sizeof (STARTUPINFOA));
	siw->cb					= sia->cb;
	ASSERT (NULL == sia->lpReserved);
	siw->lpReserved			= NULL;
	siw->lpDesktop			= NULL;
	siw->lpTitle			= NULL;
	siw->dwX				= sia->dwX;
	siw->dwY				= sia->dwY;
	siw->dwXSize			= sia->dwXSize;
	siw->dwYSize			= sia->dwYSize;
	siw->dwXCountChars		= sia->dwXCountChars;
	siw->dwYCountChars		= sia->dwYCountChars;
	siw->dwFillAttribute	= sia->dwFillAttribute;
	siw->dwFlags			= sia->dwFlags;
	siw->wShowWindow		= sia->wShowWindow;
	siw->cbReserved2		= sia->cbReserved2;
	siw->hStdInput			= sia->hStdInput;
	siw->hStdOutput			= sia->hStdOutput;
	siw->hStdError			= sia->hStdError;
	if (sia->lpDesktop)
	{
		siw->lpDesktop = AllocWinU16_from_UTF8 (sia->lpDesktop);
	}
	if (sia->lpTitle)
	{
		siw->lpTitle = AllocWinU16_from_UTF8 (sia->lpTitle);
	}
}

void DoneSTARTUPINFOW (STARTUPINFOW *siw)
{
	ASSERT (NULL != siw);
	ASSERT (NULL == siw->lpReserved);
	ubf_free_accept_NULL (siw->lpDesktop);
	ubf_free_accept_NULL (siw->lpTitle);
}

BOOL CloseHandleAndInvalidate (HANDLE *phHandle)
{
	ASSERT (NULL != phHandle);
	if (INVALID_HANDLE_VALUE != *phHandle)
	{
		BOOL b = CloseHandle (*phHandle);
		*phHandle = INVALID_HANDLE_VALUE;
		return b;
	}
	return FALSE;
}

HANDLE CreateMutexU8(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  BOOL                  bInitialOwner,
  LPCSTR                lpName
)
{
	WCHAR	wcName [MAX_PATH + 1];
	
	WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpName);
	return CreateMutexW (lpMutexAttributes, bInitialOwner, wcName);
}

HANDLE CreateMutexExU8(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
)
{
	WCHAR	wcName [MAX_PATH + 1];
	
	WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpName);
	return CreateMutexExW (lpMutexAttributes, wcName, dwFlags, dwDesiredAccess);
}

/*
	This is the MyCreatePipeEx () function originally found at
	http://www.davehart.net/remote/PipeEx.c .

	Taken from https://web.archive.org/web/20150125081922/http://www.davehart.net:80/remote/PipeEx.c .

	The function has been modified for UTF-16. The ID of the current thread is additionally
	part of the pipe name to make it safe for multi-threading.
*/

static volatile LONG PipeSerialNumber;

BOOL
APIENTRY
MyCreatePipeEx(
    OUT LPHANDLE lpReadPipe,
    OUT LPHANDLE lpWritePipe,
    IN LPSECURITY_ATTRIBUTES lpPipeAttributes,
    IN DWORD nSize,
    DWORD dwReadMode,
    DWORD dwWriteMode
    )

/*++

Routine Description:

    The CreatePipeEx API is used to create an anonymous pipe I/O device.
    Unlike CreatePipe FILE_FLAG_OVERLAPPED may be specified for one or
    both handles.
    Two handles to the device are created.  One handle is opened for
    reading and the other is opened for writing.  These handles may be
    used in subsequent calls to ReadFile and WriteFile to transmit data
    through the pipe.

Arguments:

    lpReadPipe - Returns a handle to the read side of the pipe.  Data
        may be read from the pipe by specifying this handle value in a
        subsequent call to ReadFile.

    lpWritePipe - Returns a handle to the write side of the pipe.  Data
        may be written to the pipe by specifying this handle value in a
        subsequent call to WriteFile.

    lpPipeAttributes - An optional parameter that may be used to specify
        the attributes of the new pipe.  If the parameter is not
        specified, then the pipe is created without a security
        descriptor, and the resulting handles are not inherited on
        process creation.  Otherwise, the optional security attributes
        are used on the pipe, and the inherit handles flag effects both
        pipe handles.

    nSize - Supplies the requested buffer size for the pipe.  This is
        only a suggestion and is used by the operating system to
        calculate an appropriate buffering mechanism.  A value of zero
        indicates that the system is to choose the default buffering
        scheme.

Return Value:

    TRUE - The operation was successful.

    FALSE/NULL - The operation failed. Extended error status is available
        using GetLastError.

--*/

{
	ASSERT (NULL != lpReadPipe);
	ASSERT (NULL != lpWritePipe);

    HANDLE ReadPipeHandle, WritePipeHandle;
    DWORD dwError;
    WCHAR PipeNameBuffer[ MAX_PATH ];

    //
    // Only one valid OpenMode flag - FILE_FLAG_OVERLAPPED
    //

    if ((dwReadMode | dwWriteMode) & (~FILE_FLAG_OVERLAPPED)) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    //
    //  Set the default timeout to 120 seconds
    //

    if (nSize == 0) {
        nSize = 4096;
        }

	// There's certainly a race condition here but even if this happens,
	//	we still got our unique thread ID, hence it's practically impossible to accidentally
	//	create two pipes with the same name.
	InterlockedIncrement (&PipeSerialNumber);
    swprintf( PipeNameBuffer, MAX_PATH,
				L"\\\\.\\Pipe\\culRWinAPI_U8.%08x.%08x.%08x",
				GetCurrentProcessId (),
				GetCurrentThreadId (),
				(ULONG) PipeSerialNumber
           );

    ReadPipeHandle = CreateNamedPipeW(
                         PipeNameBuffer,
                         PIPE_ACCESS_INBOUND | dwReadMode,
                         PIPE_TYPE_BYTE | PIPE_WAIT,
                         1,             // Number of pipes
                         nSize,         // Out buffer size
                         nSize,         // In buffer size
                         120 * 1000,    // Timeout in ms
                         lpPipeAttributes
                         );

    if (! ReadPipeHandle) {
        return FALSE;
    }

    WritePipeHandle = CreateFileW(
                        PipeNameBuffer,
                        GENERIC_WRITE,
                        0,                         // No sharing
                        lpPipeAttributes,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL | dwWriteMode,
                        NULL                       // Template file
                      );

    if (INVALID_HANDLE_VALUE == WritePipeHandle) {
        dwError = GetLastError();
        CloseHandle( ReadPipeHandle );
        SetLastError(dwError);
        return FALSE;
    }

    *lpReadPipe = ReadPipeHandle;
    *lpWritePipe = WritePipeHandle;
    return( TRUE );
}

BOOL CreatePipeOverlapped(
		PHANDLE					hReadPipe,
		bool					bOverlappedRead,
		PHANDLE					hWritePipe,
		bool					bOverlappedWrite,
		LPSECURITY_ATTRIBUTES	lpPipeAttributes,
		DWORD					nSize
)
{
	DWORD dwReadMode	= bOverlappedRead	? FILE_FLAG_OVERLAPPED : 0;
	DWORD dwWriteMode	= bOverlappedWrite	? FILE_FLAG_OVERLAPPED : 0; 
	BOOL b = MyCreatePipeEx	(
				hReadPipe, hWritePipe,
				lpPipeAttributes, nSize,
				dwReadMode, dwWriteMode
							);
	return b;
}

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
{
	ASSERT (NULL != lpStartupInfo);
	
	WCHAR	*wcApplicationName		= NULL;
	WCHAR	*wcCommandLine			= NULL;
	WCHAR	*wcCurrentDirectory		= NULL;
	if (lpApplicationName)
		wcApplicationName	= AllocWinU16_from_UTF8 (lpApplicationName);
	if (lpCommandLine)
		wcCommandLine		= AllocWinU16_from_UTF8 (lpCommandLine);
	if (lpCurrentDirectory)
		wcCurrentDirectory	= AllocWinU16_from_UTF8_FileName (lpCurrentDirectory);
	STARTUPINFOW	sw;
	STARTUPINFOW	*psw;
	if (dwCreationFlags & EXTENDED_STARTUPINFO_PRESENT)
	{
		STARTUPINFOA	*psa;
		STARTUPINFOEXW	swx;
		psa = &((STARTUPINFOEXA *) lpStartupInfo)->StartupInfo;
		swx.lpAttributeList = ((STARTUPINFOEXA *) lpStartupInfo)->lpAttributeList;
		STARTUPINFOW_from_STARTUPINFOA (&swx.StartupInfo, psa);
		// Pointer for CreateProcessW (). It is happy with the (STARTUPINFOW *)
		//	although we know it's actually a (STARTUPINFOEXW *).
		psw = (STARTUPINFOW *) &swx;
	} else
	{
		STARTUPINFOW_from_STARTUPINFOA (&sw, lpStartupInfo);
		psw = &sw;		
	}
	BOOL	bRet;
	bRet = CreateProcessW	(
				wcApplicationName,
				wcCommandLine,
				lpProcessAttributes,
				lpThreadAttributes,
				bInheritHandles,
				dwCreationFlags,
				lpEnvironment,
				wcCurrentDirectory,
				psw,
				lpProcessInformation
							);
	if (dwCreationFlags & EXTENDED_STARTUPINFO_PRESENT)
		DoneSTARTUPINFOW (&((STARTUPINFOEXW *) psw)->StartupInfo);
	else
		DoneSTARTUPINFOW (psw);
	DoneWinU16 (wcApplicationName);
	DoneWinU16 (wcCommandLine);
	DoneWinU16 (wcCurrentDirectory);
	return bRet;
}

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
{
	ASSERT (NULL != lpStartupInfo);

	if (lpEnvironment)
	{
		WCHAR *wcEnv = CreateWinU16EnvironmentFromU8 (lpEnvironment);
		BOOL	bRet;
	
		bRet = CreateProcessU8EnvW	(
					lpApplicationName,
					lpCommandLine,
					lpProcessAttributes,
					lpThreadAttributes,
					bInheritHandles,
					dwCreationFlags,
					wcEnv,
					lpCurrentDirectory,
					lpStartupInfo,
					lpProcessInformation
									);
		DoneWinU16Environment (wcEnv);
		return bRet;
	} else
	{
		return CreateProcessU8EnvW	(
					lpApplicationName,
					lpCommandLine,
					lpProcessAttributes,
					lpThreadAttributes,
					bInheritHandles,
					dwCreationFlags,
					NULL,
					lpCurrentDirectory,
					lpStartupInfo,
					lpProcessInformation
									);
	}
}

HANDLE CreateSemaphoreU8(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpNameU8
)
{
	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createsemaphorew .
	//	The name is limited to MAX_PATH characters.
	WCHAR wcSemName [MAX_PATH + 1];
	WinU16_from_UTF8 (wcSemName, MAX_PATH + 1, lpNameU8);
	return CreateSemaphoreW (lpSemaphoreAttributes, lInitialCount, lMaximumCount, wcSemName);
}

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
{
	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicea .
	//	The maximum string length for lpServiceName is 256 characters. The same goes for
	//	lpDisplayName. It is the caller's responsibility to adhere to these size limits.
	WCHAR	wcServiceName [512];
	WinU16_from_UTF8 (wcServiceName, 512, lpServiceName);
	WCHAR	wcDisplayName [512];
	WinU16_from_UTF8 (wcDisplayName, 512, lpDisplayName);
	WCHAR	*wcBinaryPathName	= AllocWinU16_from_UTF8 (lpBinaryPathName);
	WCHAR	*wcLoadOrderGroup	= AllocWinU16_from_UTF8 (lpLoadOrderGroup);
	WCHAR	*wcDependencies		= AllocWinU16_from_UTF8 (lpDependencies);
	WCHAR	*wcServiceStartName	= AllocWinU16_from_UTF8 (lpServiceStartName);
	WCHAR	*wcPassword			= AllocWinU16_from_UTF8 (lpPassword);
	SC_HANDLE	scReturn;
	scReturn = CreateServiceW	(
					hSCManager,
					wcServiceName,
					wcDisplayName,
					dwDesiredAccess,
					dwServiceType,
					dwStartType,
					dwErrorControl,
					wcBinaryPathName,
					wcLoadOrderGroup,
					lpdwTagId,
					wcDependencies,
					wcServiceStartName,
					wcPassword
								);
	ubf_free (wcBinaryPathName);
	ubf_free (wcLoadOrderGroup);
	ubf_free (wcDependencies);
	ubf_free (wcServiceStartName);
	ubf_free (wcPassword);
	return scReturn;
}
#endif

WCHAR **CreateWin16tringArrayFromU8 (const char **pu8, size_t numStrings)
{
	WCHAR		**pwcRet;
	
	pwcRet = ubf_malloc (sizeof (WCHAR *) * numStrings);
	if (pwcRet)
	{
		size_t n = 0;
		while (n < numStrings)
		{
			pwcRet [n] = AllocWinU16_from_UTF8 (pu8 [n]);
			++ n;
		}
	}
	return pwcRet;
}

void DoneWin16StringArray (WCHAR **pwcStringArray, size_t numStrings)
{
	size_t n = 0;
	while (n < numStrings)
	{
		ubf_free (pwcStringArray [n]);
		++ n;
	}
	ubf_free (pwcStringArray);
}

#ifdef _MSC_VER
#pragma warning (disable: 4706)									// Assignment within condition.
#endif

WCHAR *CreateWinU16EnvironmentFromU8 (const char *szU8Environment)
{
	if (szU8Environment)
	{
		const char	*chU		= szU8Environment;
		size_t		stU;
		int			stW			= 0;
		WCHAR		*wcRet;
		
		while ((stU = strlen (chU)))
		{
			stW += reqWinU16wchars (chU);
			chU += stU + 1;										// Next env variable or second NUL.
		}
		stW += 2;												// For the terminating NUL.
		wcRet = ubf_malloc (stW * sizeof (WCHAR));
		if (wcRet)
		{
			WCHAR *wc = wcRet;
			chU = szU8Environment;
			while ((stU = strlen (chU)))
			{
				stW = reqWinU16wchars (chU);
				WinU16_from_UTF8 (wc, stW, chU);
				wc += (size_t) stW + 1;
				chU += stU + 1;									// Next env variable or end.
			}
			wc [0] = L'\0';
		}
		return wcRet;
	}
	return NULL;
}

#ifdef _MSC_VER
#pragma warning (default: 4706)									// Assignment within condition.
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void DoneWinU16Environment (WCHAR *wcEnvironment)
	{
		ubf_free (wcEnvironment);
	}
#endif

#ifdef HAVE_ADVAPI32
BOOL DecryptFileU8(
  LPCSTR lpFileName,
  DWORD  dwReserved
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	BOOL	bRet;

	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileName);
	// See
	//	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-decryptfilew .
	//	The parameter dwReserved must be zero.
	//bRet = DecryptFileW (pwcFileName, dwReserved);
	ASSERT (0 == dwReserved);
	UNREFERENCED_PARAMETER (dwReserved);

	bRet = DecryptFileW (pwcFileName, 0);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}
#endif

BOOL DeleteFileU8(
  LPCSTR lpFileNameU8
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	BOOL	bRet;

	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	bRet = DeleteFileW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}

BOOL DeleteFileU8long(
  LPCSTR lpFileNameU8
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	BOOL	bRet;

	pwcFileName = AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpFileNameU8);
	bRet = DeleteFileW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}

#ifdef HAVE_ADVAPI32
BOOL EncryptFileU8(
  LPCSTR lpFileNameU8
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	BOOL	bRet;

	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	bRet = EncryptFileW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}
#endif


#ifdef HAVE_ADVAPI32
BOOL FileEncryptionStatusU8(
  LPCSTR  lpFileNameU8,
  LPDWORD lpStatus
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	BOOL	bRet;

	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	bRet = FileEncryptionStatusW (pwcFileName, lpStatus);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}
#endif

BOOL FileExistsU8 (const char *lpszFilenameU8)
{
	HANDLE hFile = CreateFileU8		(
						lpszFilenameU8, 0,
						FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						NULL, OPEN_EXISTING, 0, NULL
									);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		if (GetFileAttributesU8 (lpszFilenameU8) & FILE_ATTRIBUTE_DIRECTORY)
			return FALSE;
		else
			return TRUE;
	}
	return FALSE;
}

BOOL FileExistsU8long (const char *lpszFilenameU8)
{
	HANDLE hFile = CreateFileU8long	(
						lpszFilenameU8, 0,
						FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						NULL, OPEN_EXISTING, 0, NULL
									);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		if (GetFileAttributesU8long (lpszFilenameU8) & FILE_ATTRIBUTE_DIRECTORY)
			return FALSE;
		else
			return TRUE;
	}
	return FALSE;
}

BOOL FileOrPathExistsU8 (const char *lpszFilenameU8)
{
	HANDLE hFile = CreateFileU8	(
						lpszFilenameU8, 0,
						FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						NULL, OPEN_EXISTING, 0, NULL
								);	
	if (INVALID_HANDLE_VALUE != hFile)
	{
		CloseHandle(hFile);
		return TRUE;
	} else
	{	// Maybe it's a directory.
		WIN32_FIND_DATAW	_fileEntry;
		HANDLE hDir = FindFirstFileU8 (lpszFilenameU8, &_fileEntry);
		if (INVALID_HANDLE_VALUE == hDir)
		{
		} else
		{
			FindClose (hDir);
			return TRUE;
		}
	}
	return (FALSE);
}

BOOL FileOrPathExistsU8long (const char *lpszFilenameU8)
{
	HANDLE hFile = CreateFileU8long	(
						lpszFilenameU8, 0,
						FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						NULL, OPEN_EXISTING, 0, NULL
									);	
	if (INVALID_HANDLE_VALUE != hFile)
	{
		CloseHandle(hFile);
		return TRUE;
	} else
	{	// Maybe it's a directory.
		WIN32_FIND_DATAW	_fileEntry;
		HANDLE hDir = FindFirstFileU8 (lpszFilenameU8, &_fileEntry);
		if (INVALID_HANDLE_VALUE == hDir)
		{
		} else
		{
			FindClose (hDir);
			return TRUE;
		}
	}
	return (FALSE);
}

HANDLE FindFirstChangeNotificationU8(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
{
	WCHAR	wcPathName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcPathName;
	HANDLE	hRet;
	
	pwcPathName = AllocWinU16fromU8orUseThreshold (wcPathName, lpPathNameU8);
	hRet = FindFirstChangeNotificationW (pwcPathName, bWatchSubtree, dwNotifyFilter);
	DoneWinU16fromU8orUseThreshold (pwcPathName, wcPathName);
	return hRet;
}

HANDLE FindFirstChangeNotificationU8long(
  LPCSTR lpPathNameU8,
  BOOL   bWatchSubtree,
  DWORD  dwNotifyFilter
)
{
	WCHAR	wcPathName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcPathName;
	HANDLE	hRet;
	
	pwcPathName = AllocWinU16fromU8orUseThresholdLongFileName (wcPathName, lpPathNameU8);
	hRet = FindFirstChangeNotificationW (pwcPathName, bWatchSubtree, dwNotifyFilter);
	DoneWinU16fromU8orUseThreshold (pwcPathName, wcPathName);
	return hRet;
}

HANDLE FindFirstFileExU8(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	HANDLE	hRet;
	
	/*
		See
		https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexa .
		
		Excerpt from 2021-02-05:
		
		lpSearchFilter

		A pointer to the search criteria if the specified fSearchOp needs structured search
		information.
		At this time, none of the supported fSearchOp values require extended search
		information. Therefore, this pointer must be NULL.
	*/
	ASSERT (NULL == lpSearchFilter);
	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	hRet = FindFirstFileExW	(
				pwcFileName, fInfoLevelId, lpFindFileData,
				fSearchOp, lpSearchFilter, dwAdditionalFlags
							);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return hRet;
}

HANDLE FindFirstFileExU8long(
  LPCSTR             lpFileNameU8,
  FINDEX_INFO_LEVELS fInfoLevelId,
  LPVOID             lpFindFileData,
  FINDEX_SEARCH_OPS  fSearchOp,
  LPVOID             lpSearchFilter,
  DWORD              dwAdditionalFlags
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	HANDLE	hRet;
	
	/*
		See
		https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexa .
		
		Excerpt from 2021-02-05:
		
		lpSearchFilter

		A pointer to the search criteria if the specified fSearchOp needs structured search
		information.
		At this time, none of the supported fSearchOp values require extended search
		information. Therefore, this pointer must be NULL.
	*/
	ASSERT (NULL == lpSearchFilter);
	pwcFileName = AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpFileNameU8);
	hRet = FindFirstFileExW	(
				pwcFileName, fInfoLevelId, lpFindFileData,
				fSearchOp, lpSearchFilter, dwAdditionalFlags
							);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return hRet;
}

HANDLE FindFirstFileU8(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
{
	return FindFirstFileExU8	(
				lpFileNameU8, FindExInfoBasic, lpFindFileData,
				FindExSearchNameMatch, NULL, FIND_FIRST_EX_CASE_SENSITIVE
								);
}

HANDLE FindFirstFileU8long(
  LPCSTR             lpFileNameU8,
  LPWIN32_FIND_DATAW lpFindFileData
)
{
	return FindFirstFileExU8long	(
				lpFileNameU8, FindExInfoBasic, lpFindFileData,
				FindExSearchNameMatch, NULL, FIND_FIRST_EX_CASE_SENSITIVE
									);
}

void WIN32_FIND_DATAU8_from_WIN32_FIND_DATAW (WIN32_FIND_DATAU8 *pwfdU8, WIN32_FIND_DATAW *pwfdW)
{
	ASSERT (NULL != pwfdU8);
	ASSERT (NULL != pwfdW);
	UTF8_from_WinU16 (pwfdU8->cFileName, UTF8_MAX_PATH, pwfdW->cFileName);
	pwfdU8->dwFileAttributes	= pwfdW->dwFileAttributes;
	pwfdU8->ftCreationTime		= pwfdW->ftCreationTime;
	pwfdU8->ftLastAccessTime	= pwfdW->ftLastAccessTime;
	pwfdU8->ftLastWriteTime		= pwfdW->ftLastWriteTime;
	pwfdU8->nFileSizeHigh		= pwfdW->nFileSizeHigh;
	pwfdU8->nFileSizeLow		= pwfdW->nFileSizeLow;
	pwfdU8->dwReserved0			= pwfdW->dwReserved0;
	pwfdU8->dwReserved1			= pwfdW->dwReserved1;
	#ifdef _MAC													// No idea. That's so in
																//	the Windows header
																//	file.
		pwfdU8->dwFileType		= pwfdW->dwFileType;
		pwfdU8->dwCreatorType	= pwfdW->dwCreatorType;
		pwfdU8->wFinderFlags	= pwfdW->wFinderFlags;
	#endif
}

void copyWIN32_FIND_DATAW (WIN32_FIND_DATAW *pwfdDest, WIN32_FIND_DATAW *pwfdSrc)
{
	ASSERT (NULL != pwfdDest);
	ASSERT (NULL != pwfdSrc);

	memcpy (pwfdDest, pwfdSrc, sizeof (WIN32_FIND_DATAW));
}

void copyWIN32_FIND_DATAU8 (WIN32_FIND_DATAU8 *pu8fdDest, WIN32_FIND_DATAU8 *pu8fdSrc)
{
	ASSERT (NULL != pu8fdDest);
	ASSERT (NULL != pu8fdSrc);

	memcpy (pu8fdDest, pu8fdSrc, sizeof (WIN32_FIND_DATAU8));
}

/*
	The skeleton for this function has been taken from
	https://github.com/Arvanaghi/Windows-DLL-Injector/blob/master/Source/DLL_Injector.c .
*/
#ifdef HAVE_KERNEL32
HANDLE FindProcessByNameU8 (const char *szProcessName)
{
	HANDLE				hProcessSnap;
	HANDLE				hProcess;
	PROCESSENTRY32		pe32;
	int					iU16size;
	
	iU16size = reqWinU16wchars (szProcessName);
	WCHAR wcProcessName [1024];
	if (iU16size > 1024)
	{
		ASSERT (FALSE);
		return FALSE;
	}
	WinU16_from_UTF8 (wcProcessName, 1024, szProcessName);
	
	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnap)
		return NULL;
	// Set the size of the structure before using it.
	pe32.dwSize = sizeof (PROCESSENTRY32);
	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First (hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}
	// Now walk through the snapshot.
	do
	{
		if (!wcscmp (pe32.szExeFile, wcProcessName))
		{
			//wprintf(L"[+] The process %s was found in memory.\n", pe32.szExeFile);
			hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			return hProcess;
		}

	} while (Process32Next (hProcessSnap, &pe32));
	//printf("[---] %s has not been loaded into memory, aborting.\n", wcProcessName);
	SetLastError (ERROR_FILE_NOT_FOUND);
	return NULL;
}
#endif

BOOL GetComputerNameExU8(
  COMPUTER_NAME_FORMAT NameType,
  LPSTR                lpBuffer,
  LPDWORD              lpnSize
)
{
	BOOL	bRet	= FALSE;
	
	if (lpBuffer)
	{
		if (lpnSize)
		{
			DWORD	dwSize;
			dwSize = *lpnSize;
			WCHAR *pwc = ubf_malloc (*lpnSize * sizeof (WCHAR));
			if (pwc)
			{
				bRet = GetComputerNameExW (NameType, pwc, &dwSize);
				if (bRet)
				{
					ASSERT (*lpnSize <= INT_MAX);
					int	iReqU8size = reqUTF8size (pwc);
					if (iReqU8size > (int) *lpnSize)
					{
						SetLastError (ERROR_MORE_DATA);
						bRet = FALSE;
					} else
					{
						UTF8_from_WinU16 (lpBuffer, iReqU8size, pwc);
					}
					*lpnSize = iReqU8size ? (DWORD) iReqU8size - 1 : 0;
				} else
				{
					ASSERT (ERROR_MORE_DATA == GetLastError ());
					if (lpnSize)
						*lpnSize *= 2;
				}
				ubf_free (pwc);
			}
		} else
		{	// C6387 because lpnSize is 0. We need to let the API handle this case.
			bRet = GetComputerNameExW (NameType, NULL, lpnSize);
		}
	} else
	{
		bRet = GetComputerNameExW (NameType, NULL, lpnSize);
		if (FALSE == bRet)
		{
			ASSERT (ERROR_MORE_DATA == GetLastError ());
			if (lpnSize)
				*lpnSize *= 4;
		}
	}
	return bRet;
}

BOOL GetComputerNameU8(
  LPSTR   lpBuffer,
  LPDWORD lpnSize
)
{
	return GetComputerNameExU8 (ComputerNameNetBIOS, lpBuffer, lpnSize);
}

DWORD GetEnvironmentVariableU8(
  char		*szNameU8,
  char		*szOut,
  DWORD		nSize
)
{
	WCHAR	wcName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcName;
	DWORD	dwRet;
	WCHAR	*pwcOut		= NULL;

	pwcName = AllocWinU16fromU8orUseThreshold (wcName, szNameU8);
	if (nSize)
	{
		pwcOut = ubf_malloc (sizeof (WCHAR) * reqUTF16charsFromUTF8chars (nSize));
		dwRet = GetEnvironmentVariableW (pwcName, pwcOut, nSize);
	} else
	{
		dwRet = GetEnvironmentVariableW (pwcName, pwcOut, nSize);
		if (dwRet)
		{
			if (dwRet < nSize)
			{
				UTF8_from_WinU16 (szOut, (int) nSize, pwcOut);
				dwRet = reqUTF8size (pwcOut);
			} else
				dwRet = reqUTF8sizeFromUTF16wchars (dwRet);
		}
	}
	if (NULL != pwcOut)
		ubf_free (pwcOut);
	DoneWinU16fromU8orUseThreshold (pwcName, wcName);
	return dwRet;
}

DWORD GetFileAttributesU8(
  LPCSTR lpFileNameU8
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	DWORD	dwRet;

	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	dwRet = GetFileAttributesW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return dwRet;
}

DWORD GetFileAttributesU8long(
  LPCSTR lpFileNameU8
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	DWORD	dwRet;

	pwcFileName = AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpFileNameU8);
	dwRet = GetFileAttributesW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return dwRet;
}

BOOL GetFilePointerEx (LARGE_INTEGER *liCurrFilePointer, HANDLE hFile)
{
	LARGE_INTEGER	liZero;

	ASSERT (NULL != liCurrFilePointer);
	liZero.QuadPart = 0;
	BOOL b = SetFilePointerEx (hFile, liZero, liCurrFilePointer, FILE_CURRENT);
	return b;
}

#ifdef HAVE_ADVAPI32
BOOL GetFileSecurityU8(
		LPCSTR					lpFileNameU8,
		SECURITY_INFORMATION	RequestedInformation,
		PSECURITY_DESCRIPTOR	pSecurityDescriptor,
		DWORD					nLength,
		LPDWORD					lpnLengthNeeded
)
{
	WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcFileName;
	BOOL	bRet;

	pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	bRet = GetFileSecurityW (pwcFileName, RequestedInformation, pSecurityDescriptor,
							nLength, lpnLengthNeeded);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}
#endif

enum en_wapi_fs_type GetFileSystemType (const char *chDriveRoot)
{
	DWORD	MaximumComponentLength;
	DWORD	FileSystemFlags;
	char	cFileSystemName [64];

	if (GetVolumeInformationU8 (chDriveRoot,
							NULL, 0,
							NULL,
							&MaximumComponentLength,
							&FileSystemFlags,
							cFileSystemName, 64))
	{
		if (!strcmp (cFileSystemName, "NTFS"))
			return FS_TYPE_NTFS;
		if (!strcmp (cFileSystemName, "FAT"))
			return FS_TYPE_FAT;
		if (!strcmp (cFileSystemName, "FAT32"))
			return FS_TYPE_FAT32;
	}
	_ASSERT (FALSE);
	return FS_TYPE_ERROR;
}

#ifdef DEBUG
	BOOL IsFileSystemFAT (const char *chDriveRoot)
	{
		return FS_TYPE_FAT == GetFileSystemType (chDriveRoot);
	}
#endif

#ifdef DEBUG
	BOOL IsFileSystemFAT32 (const char *chDriveRoot)
	{
		return FS_TYPE_FAT32 == GetFileSystemType (chDriveRoot);
	}
#endif

#ifdef DEBUG
	BOOL IsFileSystemFATorFAT32 (const char *chDriveRoot)
	{
		return IsFileSystemFAT32 (chDriveRoot) || IsFileSystemFAT (chDriveRoot);
	}
#endif

#ifdef DEBUG
	BOOL IsFileSystemNTFS (const char *chDriveRoot)
	{
		return FS_TYPE_NTFS == GetFileSystemType (chDriveRoot);
	}
#endif

DWORD GetNumberOfProcessesAttachedToConsole (void)
{
	DWORD dwLst [1];

	/*
		https://learn.microsoft.com/en-us/windows/console/getconsoleprocesslist

		Excerpt:

		"If the buffer is too small to hold all the valid process identifiers, the return
		value is the required number of array elements. The function will have stored no
		identifiers in the buffer. In this situation, use the return value to allocate a
		buffer that is large enough to store the entire list and call the function again."
	*/
	DWORD dwRet = GetConsoleProcessList (dwLst, 1);
	if (0 == dwRet)
	{	// Fail. See https://learn.microsoft.com/en-us/windows/console/getconsoleprocesslist .
		DWORD dwErr = GetLastError ();
		ASSERT (false);
		UNREFERENCED_PARAMETER (dwErr);
	}
	return dwRet;
}

bool IsOnlyProcessAttachedToConsole (void)
{
	return 1 == GetNumberOfProcessesAttachedToConsole ();
}

DWORD GetFullPathNameU8(
  LPCSTR lpFileName,
  DWORD  nBufferLength,
  LPSTR  lpBuffer,
  LPSTR  *lpFilePart
)
{
	int			iRequiredU16size;
	WCHAR		wcFileName [4096];
	WCHAR		*pwcFileName;
	WCHAR		*pFilePartW			= NULL;
	
	// Note that as of 2021-04-19 the documentation for GetFullPathNameW () at
	//	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamew
	//	is incorrect. The function does not support long filenames, at least not as the
	//	lpFileName parameter.
	/*
		Excerpt (which is wrong):

		lpFileName

		The name of the file.

		This parameter can be a short (the 8.3 form) or long file name. This string can also be
		a share or volume name.

		In the ANSI version of this function, the name is limited to MAX_PATH characters. To
		extend this limit to 32,767 wide characters, call the Unicode version of the function
		(GetFullPathNameW), and prepend "\\?\" to the path. For more information, see Naming a File.
	*/
	if (lpFileName)
	{
		//iRequiredU16size = reqWinU16wcharsFileName (lpFileName);
		iRequiredU16size = reqWinU16wchars (lpFileName);
		if (iRequiredU16size <= 4096)
		{
			WinU16_from_UTF8 (wcFileName, iRequiredU16size, lpFileName);
			pwcFileName = wcFileName;
		} else
		{
			pwcFileName = AllocWinU16_from_UTF8_FileName (lpFileName);
		}
	} else
	{
		pwcFileName			= NULL;
	}
	DWORD	dwRet;
	if (lpBuffer && nBufferLength)
	{
		WCHAR		*pwcBuffer;
		//WCHAR		*pwcToConv;
		DWORD		dwWbuflen;
		int			iU8size;
		
		// Not supported/documentation doesn't mention that relative paths cannot
		//	contain "." and "..".
		//dwWbuflen = (nBufferLength + LENOFLONGFILENAMEPREFIX) * sizeof (WCHAR);
		dwWbuflen = nBufferLength * sizeof (WCHAR);
		pwcBuffer = ubf_malloc (dwWbuflen);
		if (pwcBuffer)
		{
			//ASSERT (FALSE);
			// This was used to find out that the documentation is wrong. A long filename
			//	prefix is not supported by GetFullPathNameW ().
			//pwcFileName += 4;
			dwRet = GetFullPathNameW (pwcFileName, dwWbuflen / 2, pwcBuffer, &pFilePartW);
			/*
			// If the caller provided a long file name prefix we give it back to them.
			//	If not, we remove it from the returned path before we convert to UTF-8.
			if	(
						lpFileName
					&&	!HasLongFileNamePrefixU8 (lpFileName)
					&&	HasLongFileNamePrefixW (pwcBuffer)
				)
				pwcToConv = pwcBuffer + LENOFLONGFILENAMEPREFIX;
			else
				pwcToConv = pwcBuffer;
			*/
			iU8size = reqUTF8size (pwcBuffer);
			ASSERT (nBufferLength <= INT_MAX);
			if (iU8size < (int) nBufferLength)
			{
				if (iU8size)
				{
					UTF8_from_WinU16 (lpBuffer, iU8size, pwcBuffer);
					-- iU8size;
					ASSERT (strlen (lpBuffer) == (size_t) iU8size);
					ASSERT ((int) strlen (lpBuffer) == iU8size);
					dwRet = iU8size;
				} else
				{
					dwRet = 0;
				}
			} else
			{
				dwRet = GetFullPathNameW (pwcFileName, 0, NULL, NULL);
				dwRet *= 4;										// Up to 4 octets per WCHAR.
			}
			ubf_free (pwcBuffer);
		} else
		{
			SetLastError (ERROR_NOT_ENOUGH_MEMORY);
			dwRet = 0;
		}
	} else
	{	// C6387 because pwcFileName could be NULL. This is between our caller and the API,
		//	not us.
		dwRet = GetFullPathNameW (pwcFileName, 0, NULL, NULL);
		dwRet *= 4;												// Up to 4 octets per WCHAR.
	}
	if (pwcFileName != wcFileName)
	{
		ubf_free (pwcFileName);
	}
	if (lpFilePart)
	{
		/*
			Excerpt from
			https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamew :
			
			"A pointer to a buffer that receives the address (within lpBuffer) of the final
			file name component in the path.
			This parameter can be NULL.
			If lpBuffer refers to a directory and not a file, lpFilePart receives zero."

			Tests showed that GetFullPathNameW () seems to distinguish between a file and
			a directory only by checking for a trailing backslash. This is not relevant for
			us because we check pFilePartW, which is what we've passed on to
			GetFullPathNameW () ourselves.
		*/
		if (pFilePartW && *pFilePartW)
		{
			char *ccFilePart;
			ccFilePart = strrchr (lpBuffer, '\\');
			if (!ccFilePart)
				ccFilePart = strrchr (lpBuffer, '/');
			if (ccFilePart)
				++ ccFilePart;									// First octet after slash.
			*lpFilePart = ccFilePart;
		} else
		{
			*lpFilePart = 0;
		}
	}
	return dwRet;
}

DWORD GetModuleFileNameU8(
		HMODULE	hModule,
		LPSTR	lpFilenameU8,
		DWORD	nSize
)
{
	DWORD	dwRet;
	WCHAR	wcModuleName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcModuleName = wcModuleName;
	int		iu8;
	
	if (0 == nSize)
		return 0;

	dwRet = GetModuleFileNameW (hModule, pcModuleName, WINAPI_U8_HEAP_THRESHOLD);
	if (WINAPI_U8_HEAP_THRESHOLD == dwRet)
	{	// Stack buffer (WINAPI_U8_HEAP_THRESHOLD) too small.
		DWORD dwtot = WINAPI_U8_HEAP_THRESHOLD;
		do
		{
			if (pcModuleName != wcModuleName)
				ubf_free (pcModuleName);
			dwtot += WINAPI_U8_HEAP_THRESHOLD;
			pcModuleName = ubf_malloc (sizeof (WCHAR) * dwtot);
			if (NULL == pcModuleName)
				return 0;
			dwRet = GetModuleFileNameW (hModule, pcModuleName, dwtot);
		} while (dwRet == dwtot);
	}
	iu8 = reqUTF8size (pcModuleName);
	ASSERT (0 < iu8);
	if ((DWORD) iu8 < nSize)
	{	// Success.
		int iRet = UTF8_from_WinU16 (lpFilenameU8, iu8, pcModuleName);
		if (pcModuleName != wcModuleName)
			ubf_free (pcModuleName);
		ASSERT (0 < iRet);
		return (DWORD) iRet - 1;
	}
	// Buffer provided by the user too small.
	#ifdef GETMODULEFILENAMEU8_ASSERT_BUFFER_TOO_SMALL
		ASSERT (FALSE);
	#endif
	UTF8_from_WinU16 (lpFilenameU8, (int) nSize, pcModuleName);
	lpFilenameU8 [nSize - 1] = ASCII_NUL;
	if (pcModuleName != wcModuleName)
		ubf_free (pcModuleName);
	SetLastError (ERROR_INSUFFICIENT_BUFFER);
	return nSize;
}

HMODULE GetModuleHandleU8(
  LPCSTR lpModuleName
)
{
	int iModuleName = reqWinU16wchars (lpModuleName);
	if (iModuleName <= WINAPI_U8_HEAP_THRESHOLD)
	{
		WCHAR	wcModuleName [WINAPI_U8_HEAP_THRESHOLD];
		WinU16_from_UTF8 (wcModuleName, iModuleName, lpModuleName);
		return GetModuleHandleW (wcModuleName);
	}
	ASSERT (FALSE);
	return NULL;
}

typedef enum en_StringOrArray
{
	ensa_String,
	ensa_Array
} enStrOrArr;

size_t copyStrOrArrSizeInReturnValue (char *szReturned, WCHAR *pwc, DWORD nSize, enStrOrArr w)
{
	size_t	stRet;

	switch (w)
	{
		// Single string.
		case ensa_String:
			UTF8_from_WinU16 (szReturned, nSize, pwc);
			return reqUTF8size (pwc);

		// An array. That's a bit more complicated.
		case ensa_Array:
			stRet = 0;
			while (pwc [0])
			{
				stRet += reqUTF8size (pwc);					// Includes NUL.
				if (stRet <= nSize)
				{
					UTF8_from_WinU16 (szReturned, nSize, pwc);
					nSize -= (DWORD) stRet;
					szReturned += stRet;
				}
				pwc += wcslen (pwc);
				pwc ++;										// Jump over NUL.
			}
			return stRet;
	}
	// Bug.
	_ASSERT (FALSE);
	return (size_t) -1;
}

DWORD GetPrivateProfileStringU8(
	LPCSTR lpAppName,
	LPCSTR lpKeyName,
	LPCSTR lpDefault,
	LPSTR  lpReturnedString,
	DWORD  nSize,
	LPCSTR lpFileName
)
{
	WCHAR	wcAppName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcKeyName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcDefault	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcFileName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcAppName		= NULL;
	WCHAR	*pwcKeyName		= NULL;
	WCHAR	*pwcDefault		= NULL;
	WCHAR	*pwcFileName	= NULL;
	WCHAR	*pwcReturned;
	DWORD	dwRet;
	size_t	sizeRet;

	if (0 == nSize)
	{
		return 0;
	}
	ASSERT (0 < nSize);
	if (lpAppName)
		pwcAppName	= AllocWinU16fromU8orUseThreshold (wcAppName, lpAppName);
	if (lpKeyName)
		pwcKeyName	= AllocWinU16fromU8orUseThreshold (wcKeyName, lpKeyName);
	if (lpDefault)
		pwcDefault	= AllocWinU16fromU8orUseThreshold (wcDefault, lpDefault);
	// Note that the documentation does not explicitely mention a long file name
	//	prefix. See
	//	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getprivateprofilestringw .
	if (lpFileName)
		pwcFileName	= AllocWinU16fromU8orUseThreshold (wcFileName, lpFileName);
	pwcReturned = ubf_malloc (((size_t) nSize) * 4);
	dwRet = GetPrivateProfileStringW	(
				pwcAppName, pwcKeyName, pwcDefault, pwcReturned, nSize, pwcFileName
										);
	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getprivateprofilestringw .
	/*
		If neither lpAppName nor lpKeyName is NULL and the supplied destination buffer is
		too small to hold the requested string, the string is truncated and followed by a
		null character, and the return value is equal to nSize minus one.
	*/
	if (lpAppName && lpKeyName)
	{
		sizeRet = copyStrOrArrSizeInReturnValue (lpReturnedString, pwcReturned, nSize, ensa_String);
		if (dwRet == nSize * 4 - 1)
		{
			dwRet = nSize - 1;
			lpReturnedString [dwRet - 1] = '\0';
		}
		if (sizeRet >= nSize)
		{
			dwRet = nSize - 1;
			lpReturnedString [dwRet - 1] = '\0';
		}
	} else
	/*
		If either lpAppName or lpKeyName is NULL and the supplied destination buffer is too
		small to hold all the strings, the last string is truncated and followed by two null
		characters. In this case, the return value is equal to nSize minus two.
	*/
	if (NULL == lpAppName || NULL == lpKeyName)
	{
		sizeRet = copyStrOrArrSizeInReturnValue (lpReturnedString, pwcReturned, nSize, ensa_Array);
		if (dwRet == nSize * 4 - 2)
		{
			if (nSize >= 2)
			{
				dwRet = nSize - 2;
				lpReturnedString [dwRet - 2] = '\0';
				lpReturnedString [dwRet - 1] = '\0';
			} else
			{
				lpReturnedString [dwRet - 1] = '\0';
				dwRet = 0;
			}
		}
		if (sizeRet >= nSize)
		{
			// Not implemented yet.
			ASSERT (FALSE);
		}
	}
	if (lpAppName)
		DoneWinU16fromU8orUseThreshold (pwcAppName, wcAppName);
	if (lpKeyName)
		DoneWinU16fromU8orUseThreshold (pwcKeyName, wcKeyName);
	if (lpDefault)
		DoneWinU16fromU8orUseThreshold (pwcDefault, wcDefault);
	if (lpFileName)
		DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	ubf_free (pwcReturned);
	return dwRet;
}

UINT GetSystemDirectoryU8(
	LPSTR	lpBuffer,
	UINT	uSize
)
{
	WCHAR	wcSysDir [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcSysDir = wcSysDir;

	if (uSize > INT_MAX)
		return 0;
	UINT uReqSize = GetSystemDirectoryW (pcSysDir, WINAPI_U8_HEAP_THRESHOLD);
	if (0 == uReqSize)
		return 0;
	if (uReqSize >= WINAPI_U8_HEAP_THRESHOLD)
	{
		pcSysDir = ubf_malloc (sizeof (wchar_t) * uReqSize);
		if (pcSysDir)
			GetSystemDirectoryW (pcSysDir, uReqSize);
	}

	int iReq = reqUTF8size (pcSysDir);
	if ((int) uSize >= iReq)
	{
		iReq = UTF8_from_WinU16 (lpBuffer, uSize, pcSysDir);
		if (iReq)
			-- iReq;
	}
	if (pcSysDir && pcSysDir != wcSysDir)
		ubf_free (pcSysDir);
	return (UINT) iReq;
}

static const char	*szWinSystemDirectory;
static size_t		lnWinSystemDirectory;

const char *SystemDirectoryU8 (void)
{
	if (NULL == szWinSystemDirectory)
	{
		UINT ui = GetSystemDirectoryU8 (NULL, 0);
		szWinSystemDirectory = ubf_malloc (ui);
		if (szWinSystemDirectory)
		{
			UINT u2 = GetSystemDirectoryU8 ((char *) szWinSystemDirectory, ui);
			ASSERT (ui == u2 + 1);
			lnWinSystemDirectory = u2;
		}
	}
	return szWinSystemDirectory;
}

size_t SystemDirectoryU8len (void)
{
	if (0 == lnWinSystemDirectory)
		SystemDirectoryU8 ();
	return lnWinSystemDirectory;
}

void DoneSystemDirectoryU8 (void)
{
	if (szWinSystemDirectory)
		ubf_free ((char *) szWinSystemDirectory);
	szWinSystemDirectory = NULL;
	lnWinSystemDirectory = 0;
}

UINT GetSystemWindowsDirectoryU8(
	LPSTR	lpBuffer,
	UINT	uSize
)
{
	WCHAR	wcWinDir [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcWinDir = wcWinDir;

	if (uSize > INT_MAX)
		return 0;
	UINT uReqSize = GetSystemWindowsDirectoryW (pcWinDir, WINAPI_U8_HEAP_THRESHOLD);
	if (0 == uReqSize)
		return 0;
	if (uReqSize >= WINAPI_U8_HEAP_THRESHOLD)
	{
		pcWinDir = ubf_malloc (sizeof (wchar_t) * uReqSize);
		if (pcWinDir)
			GetSystemWindowsDirectoryW (pcWinDir, uReqSize);
	}

	int iReq = reqUTF8size (pcWinDir);
	if ((int) uSize >= iReq)
	{
		iReq = UTF8_from_WinU16 (lpBuffer, uSize, pcWinDir);
		if (iReq)
			-- iReq;
	}
	if (pcWinDir && pcWinDir != wcWinDir)
		ubf_free (pcWinDir);
	return (UINT) iReq;
}

static const char	*szWinSystemWindowsDirectory;
static size_t		lnWinSystemWindowsDirectory;

const char *SystemWindowsDirectoryU8 (void)
{
	if (NULL == szWinSystemWindowsDirectory)
	{
		UINT ui = GetSystemWindowsDirectoryU8 (NULL, 0);
		szWinSystemWindowsDirectory = ubf_malloc (ui);
		if (szWinSystemWindowsDirectory)
		{
			UINT u2 = GetSystemWindowsDirectoryU8 ((char *) szWinSystemWindowsDirectory, ui);
			ASSERT (ui == u2 + 1);
			lnWinSystemWindowsDirectory = u2;
		}
	}
	return szWinSystemWindowsDirectory;
}

size_t SystemWindowsDirectoryU8len (void)
{
	if (0 == lnWinSystemWindowsDirectory)
		SystemWindowsDirectoryU8 ();
	return lnWinSystemWindowsDirectory;
}

void DoneSystemWindowsDirectoryU8 (void)
{
	if (szWinSystemWindowsDirectory)
		ubf_free ((char *) szWinSystemWindowsDirectory);
	szWinSystemWindowsDirectory = NULL;
	lnWinSystemWindowsDirectory = 0;
}

#ifdef HAVE_ADVAPI32
	BOOL GetUserNameU8(
	  LPSTR   lpBuffer,
	  LPDWORD pcbBuffer
	)
	{
		BOOL	bRet;
		DWORD	dwLen;
	
		ASSERT (NULL != lpBuffer);
		ASSERT (NULL != pcbBuffer);
		// As of 2021-01-24 and Windows 10 SDK UNLEN is 256. See
		//	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew
		//	for more information.
		WCHAR	wcUserName [UNLEN + 1];
		dwLen = UNLEN + 1;
		#ifdef DEBUG
			bRet = GetUserNameW (wcUserName, &dwLen);
		#else
			GetUserNameW (wcUserName, &dwLen);
		#endif
		ASSERT (FALSE != bRet);
		ASSERT (UNLEN >= dwLen);
		int iReq = reqUTF8size (wcUserName);
		ASSERT (INT_MAX > *pcbBuffer);
		if (iReq <= (int) *pcbBuffer)
		{
			UTF8_from_WinU16 (lpBuffer, iReq, wcUserName);
			bRet = TRUE;
		} else
		{
			SetLastError (ERROR_INSUFFICIENT_BUFFER);
			bRet = FALSE;
		}
		*pcbBuffer = (DWORD) iReq;
		return bRet;
	}
#endif

#ifdef HAVE_USERENV
BOOL GetDefaultUserProfileDirectoryU8(
	LPSTR   lpProfileDirU8,
	LPDWORD lpcchSize
)
{
	ASSERT (NULL != lpcchSize);

	BOOL	bRet = false;
	WCHAR	wcProfDir [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcProfDir;

	DWORD	dw = 0;
	GetDefaultUserProfileDirectoryW (NULL, &dw);
	if (dw <= WINAPI_U8_HEAP_THRESHOLD)
		pcProfDir = wcProfDir;
	else
		pcProfDir = malloc (dw * sizeof (WCHAR));
	if (pcProfDir)
	{
		BOOL b = GetDefaultUserProfileDirectoryW (pcProfDir, &dw);
		if (b)
		{
			int r = reqUTF8size (pcProfDir);
			if (*lpcchSize >= (DWORD) r)
			{
				UTF8_from_WinU16 (lpProfileDirU8, r, pcProfDir);
				bRet = true;
			}
			*lpcchSize = r;
		}
		if (wcProfDir != pcProfDir)
			free (pcProfDir);
	}
	return bRet;
}
#endif

#ifdef HAVE_USERENV
BOOL GetUserProfileDirectoryU8(
	HANDLE  hToken,
	LPSTR   lpProfileDirU8,
	LPDWORD lpcchSize
)
{
	ASSERT (NULL != lpcchSize);

	BOOL	bRet = false;
	WCHAR	wcProfDir [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcProfDir;

	DWORD	dw = 0;
	GetUserProfileDirectoryW (hToken, NULL, &dw);
	if (dw <= WINAPI_U8_HEAP_THRESHOLD)
		pcProfDir = wcProfDir;
	else
		pcProfDir = malloc (dw * sizeof (WCHAR));
	if (pcProfDir)
	{
		bool b = GetUserProfileDirectoryW (hToken, pcProfDir, &dw);
		if (b)
		{
			int r = reqUTF8size (pcProfDir);
			if (*lpcchSize >= (DWORD) r)
			{
				UTF8_from_WinU16 (lpProfileDirU8, r, pcProfDir);
				bRet = true;
			}
			*lpcchSize = r;
		}
		if (wcProfDir != pcProfDir)
			free (pcProfDir);
	}
	return bRet;
}
#endif

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
{
	int		iReqSize;
	WCHAR	wcFileSystemNameBuffer [MAX_PATH + 1];				// The file system's name to query.
	BOOL	bRet		= FALSE;

	ASSERT (NULL == lpVolumeNameBuffer);						// Currently not supported.
	ASSERT (0 == nVolumeNameSize);								// Currently not supported.
	ASSERT (nFileSystemNameSize <= INT_MAX);

	UNREFERENCED_PARAMETER (lpVolumeNameBuffer);
	iReqSize = reqWinU16wchars (lpRootPathName);
	if (iReqSize)
	{
		if (iReqSize <= WINAPI_U8_HEAP_THRESHOLD)
		{
			WCHAR	wcRFN [WINAPI_U8_HEAP_THRESHOLD];
			WinU16_from_UTF8 (wcRFN, iReqSize, lpRootPathName);
			// See
			//	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationw .
			bRet = GetVolumeInformationW	(
							wcRFN, NULL, nVolumeNameSize,
							lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags,
							wcFileSystemNameBuffer, MAX_PATH + 1
											);
		} else
		{
			ASSERT (FALSE);
			return FALSE;
		}
		if (bRet)
		{
			iReqSize = reqUTF8size (wcFileSystemNameBuffer);
			if (iReqSize <= (int) nFileSystemNameSize)
			{
				UTF8_from_WinU16 (lpFileSystemNameBuffer, iReqSize, wcFileSystemNameBuffer);
				return bRet;
			}
		}
	}
	ASSERT (FALSE);
	return FALSE;
}

BOOL GetWinErrorTextU8 (char *lpszBuf, DWORD dwSize, DWORD dwError)
{
	int		iReqSize;
	DWORD	dwRet									= 1;
	WCHAR	wcErrText [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcErrText								= wcErrText;
	DWORD	dwErrText								= WINAPI_U8_HEAP_THRESHOLD;

	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar .
	//iReqSize = MultiByteToWideChar (CP_UTF8, 0, lpRootPathName, -1, NULL, 0);

	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-formatmessagew .
	do
	{
		if (0 == dwRet)
		{
			if (pcErrText != wcErrText)
				free (pcErrText);
			ASSERT (INT_MAX < MAXDWORD);
			if (dwErrText <= INT_MAX - WINAPI_U8_HEAP_THRESHOLD)
				dwErrText += WINAPI_U8_HEAP_THRESHOLD;
			else
				return false;
			pcErrText = malloc (sizeof (WCHAR) * dwErrText);
		}
		if (pcErrText)
		{
			dwRet = FormatMessageW	(
							FORMAT_MESSAGE_FROM_SYSTEM
						|	FORMAT_MESSAGE_ARGUMENT_ARRAY
						|	FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						dwError,
						0,
						pcErrText,
						dwErrText - 1,
						NULL
									);
		} else
		{
			return false;
		}
	} while (0 == dwRet && ERROR_INSUFFICIENT_BUFFER == GetLastError ());
	if (dwRet > 2)
    {	// Remove the line ending (CR/LF).
		pcErrText [dwRet - 2] = L'\0';
		// Convert to UTF-8.
		iReqSize = reqUTF8size (pcErrText);
		char *szU8 = malloc (iReqSize);
		if (szU8)
		{
			UTF8_from_WinU16 (szU8, iReqSize, pcErrText);
			snprintf (lpszBuf, dwSize, "\"%s\" (Error %lu, 0%lXh)", szU8, dwError, dwError);
			free (szU8);
			if (pcErrText != wcErrText)
				free (pcErrText);
			return TRUE;
		}
    }
	_ASSERT (FALSE);										// Must be a bug.
	if (pcErrText != wcErrText)
		free (pcErrText);
	return FALSE;
}

#ifdef HAVE_ADVAPI32
	BOOL InitiateSystemShutdownExU8(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwTimeout,
		BOOL   bForceAppsClosed,
		BOOL   bRebootAfterShutdown,
		DWORD  dwReason
	)
	{
		WCHAR	wcMachineName	[WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	wcMessage		[WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	*pwcMachineName	= NULL;
		WCHAR	*pwcMessage		= NULL;
		BOOL	bRet;
		
		pwcMachineName	= AllocWinU16fromU8orUseThreshold (wcMachineName, lpMachineNameU8);
		pwcMessage		= AllocWinU16fromU8orUseThreshold (wcMessage, lpMessageU8);
		
		bRet = InitiateSystemShutdownExW	(
					pwcMachineName, pwcMessage,
					dwTimeout, bForceAppsClosed, bRebootAfterShutdown,
					dwReason
											);
		DoneWinU16fromU8orUseThreshold (wcMachineName, pwcMachineName);
		DoneWinU16fromU8orUseThreshold (wcMessage, pwcMessage);
		return bRet;
	}
#endif
	
#ifdef HAVE_ADVAPI32
	DWORD InitiateShutdownU8(
		const char *lpMachineNameU8,
		const char *lpMessageU8,
		DWORD  dwGracePeriod,
		DWORD  dwShutdownFlags,
		DWORD  dwReason
		)
	{
		WCHAR	wcMachineName	[WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	wcMessage		[WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	*pwcMachineName	= NULL;
		WCHAR	*pwcMessage		= NULL;
		BOOL	bRet;
		
		pwcMachineName	= AllocWinU16fromU8orUseThreshold (wcMachineName, lpMachineNameU8);
		pwcMessage		= AllocWinU16fromU8orUseThreshold (wcMessage, lpMessageU8);
		
		bRet = InitiateShutdownW	(
					pwcMachineName, pwcMessage,
					dwGracePeriod, dwShutdownFlags,
					dwReason
									);
		DoneWinU16fromU8orUseThreshold (wcMachineName, pwcMachineName);
		DoneWinU16fromU8orUseThreshold (wcMessage, pwcMessage);
		return bRet;
	}
#endif
	
BOOL IsCmdArgumentSwitchW	(
			WCHAR							*wcArgument,
			const WCHAR						*wcConstIs,
			size_t							nRelevant,
			enum en_is_cmd_argument			enHow,
			enum en_is_cmd_case_sensitive	enCase
                            )
{
	UNREFERENCED_PARAMETER (nRelevant);
	UNREFERENCED_PARAMETER (enHow);
	UNREFERENCED_PARAMETER (enCase);

	ASSERT (NULL != wcArgument);
	ASSERT (NULL != wcConstIs);
	ASSERT (0 != wcArgument [0]);
	ASSERT (0 != wcConstIs [0]);
	if (EN_IS_CMD_ARG_ALLOW_NO_DASH_ONLY == enHow && L'-' == wcConstIs [0])
		return FALSE;

	// To do!!!
	if (wcscmp (wcArgument, wcConstIs))
	{	// We allow both options ("-delete" and "delete") if the argument
		//	is supposed to start with a "-".
		if (L'-' == wcConstIs [0])
		{
			return !wcscmp (wcArgument, wcConstIs + 1);			
		}
	} else
	{
		return TRUE;
	}
	return FALSE;
}

BOOL IsEqualUpToW	(
			const WCHAR						*wc1,
			const WCHAR						*wc2,
			size_t							n,
			enum en_is_cmd_case_sensitive	cse
					)
{
	size_t		st1 = wcslen (wc1);
	size_t		st2 = wcslen (wc2);
	
	ASSERT (st1 >= n);											// That's what the function is
																//	about. To be fixed by the
																//	caller.
	ASSERT	(		EN_IS_CMD_CASE_SENSITIVE	== cse
				||	EN_IS_CMD_CASE_INSENSITIVE	== cse
			);
	if (st1 < n)
		return FALSE;
	if (st2 < n)
		return FALSE;
	if (st1 == st2)
	{
		return	EN_IS_CMD_CASE_SENSITIVE == cse		?
				0 == wcscmp (wc1, wc2)				:			// Case-sensitive.
				0 == _wcsicmp (wc1, wc2)			;			// Case-insensitive.
	}
	if (st1 < st2)
		return FALSE;
	// String wc1 is longer than the first one.
	ASSERT (st2 >= n);											// This is the only option left
																//	here anyway.
	return 0 == wcsncmp (wc1, wc2, st2);
}

BOOL IsPathDirectoryU8 (const char *szPath)
{
	// We first try an absolute path.
	DWORD dwAttrib = GetFileAttributesU8long (szPath);
	// If this didn't work we assume that the path is relative and can't
	//	have a long filename prefix.
	if (INVALID_FILE_ATTRIBUTES == dwAttrib)
		dwAttrib = GetFileAttributesU8 (szPath);
	return	(
					(dwAttrib != INVALID_FILE_ATTRIBUTES)
				&&	(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)
			);
}

BOOL IsPathDirectoryW (const WCHAR *wcPath)
{
	DWORD dwAttrib = GetFileAttributesW (wcPath);
	return	(
					(dwAttrib != INVALID_FILE_ATTRIBUTES)
				&&	(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)
			);
}

HMODULE LoadLibraryExU8(
	char	*szLibFileNameU8,
	HANDLE	hFile,
	DWORD	dwFlags
)
{
	HANDLE	hModule	= NULL;

	WCHAR	wcLibName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcLibName	= NULL;

	pwcLibName	= AllocWinU16fromU8orUseThreshold (wcLibName, szLibFileNameU8);
	if (pwcLibName)
	{
		hModule = LoadLibraryExW (pwcLibName, hFile, dwFlags);
		DoneWinU16fromU8orUseThreshold (pwcLibName, wcLibName);
	}
	return hModule;
}

HMODULE LoadLibraryU8(
  char *chLibFileNameU8
)
{
	HANDLE	hModule	= NULL;

	WCHAR	wcLibName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcLibName	= NULL;

	pwcLibName	= AllocWinU16fromU8orUseThreshold (wcLibName, chLibFileNameU8);
	if (pwcLibName)
	{
		hModule = LoadLibraryW (pwcLibName);
		DoneWinU16fromU8orUseThreshold (pwcLibName, wcLibName);
	}
	return hModule;
}

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
    {
        ASSERT (NULL != cchReferencedDomainName);
    
        WCHAR	wcSystemName	[1024];
        WCHAR	wcAccountName	[1024];
        WCHAR	*pwcSystemName				= NULL;
        WCHAR	*pwcAccountName				= NULL;
        WCHAR	*pwcDomain;
    
        if (lpSystemName)
        {
            WinU16_from_UTF8 (wcSystemName, 1024, lpSystemName);
            pwcSystemName = wcSystemName;
        }
        if (lpAccountName)
        {
            WinU16_from_UTF8 (wcAccountName, 1024, lpAccountName);
            pwcAccountName = wcAccountName;
        }
        DWORD	dwReferenceDomainName	= *cchReferencedDomainName;
        pwcDomain = ubf_malloc (dwReferenceDomainName * sizeof (WCHAR) * 2);
        BOOL	bRet;
        bRet = LookupAccountNameW	(
                    pwcSystemName, pwcAccountName,
                    Sid, cbSid,
                    pwcDomain, &dwReferenceDomainName,
                    peUse
                                    );
        int iRequiredDomainSize = reqUTF8size (pwcDomain);
        UTF8_from_WinU16 (ReferencedDomainName, *cchReferencedDomainName, pwcDomain);
        // See
        //	https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-lookupaccountnamew .
        /*
            cchReferencedDomainName
    
            A pointer to a variable. On input, this value specifies the size, in TCHARs, of the
            ReferencedDomainName buffer. If the function fails because the buffer is too small,
            this variable receives the required buffer size, including the terminating null
            character. If the ReferencedDomainName parameter is NULL, this parameter must be zero.
            
            It doesn't say anything that we should store that value back unless the required
            size of the buffer is bigger than what the caller provided.
        */
        ASSERT (dwReferenceDomainName <= INT_MAX);
        if (iRequiredDomainSize > (int) dwReferenceDomainName)
            *cchReferencedDomainName = dwReferenceDomainName;
        ubf_free (pwcDomain);
        return bRet;
    }
#endif

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
    {
        WCHAR	*pwcSystemName	= NULL;
        WCHAR	*pwcName		= NULL;
        WCHAR	*pwcDomainName	= NULL;
        WCHAR	wcSystemName	[WINAPI_U8_HEAP_THRESHOLD];
        DWORD	dwName;
        DWORD	dwDomainName;
        size_t	stName;
        size_t	stDomainName;
        int		iReq;
        BOOL	bRet			= FALSE;
        
        // Not sure if the Windows API accepts NULL for the lengths parameters.
        ASSERT (NULL != cchNameU8);
        ASSERT (NULL != cchReferencedDomainNameU8);
        
        // Parameter lpSystemNameU8 -> pwcSystemName.
        if (lpSystemNameU8)
        {
            iReq = reqWinU16wchars (lpSystemNameU8);
            if (iReq <= WINAPI_U8_HEAP_THRESHOLD)
            {
                WinU16_from_UTF8 (wcSystemName, iReq, lpSystemNameU8);
                pwcSystemName = wcSystemName;
            } else
            {
                pwcSystemName = AllocWinU16_from_UTF8 (lpSystemNameU8);
                if (pwcSystemName)
                {
                    WinU16_from_UTF8 (pwcSystemName, iReq, lpSystemNameU8);
                }
            }
        }
        if (NameU8)
        {	// User obviously expects this parameter back.
            stName = sizeof (WCHAR) * *cchNameU8;
            pwcName = ubf_malloc (stName);
        }
        if (ReferencedDomainNameU8)
        {	// User obviously expects this parameter back.
            stDomainName = sizeof (WCHAR) * *cchReferencedDomainNameU8;
            pwcDomainName = ubf_malloc (stDomainName);
        }
        // Although not quite correct (UTF-8 can require up to 50 % more than UTF-16),
        //	we use the original sizes the user has provided.
        dwName			= *cchNameU8;
        dwDomainName	= *cchReferencedDomainNameU8;
        bRet = LookupAccountSidW	(
                    pwcSystemName, Sid, pwcName, &dwName, pwcDomainName, &dwDomainName, peUse
                                    );
        if (dwName != *cchNameU8)
        {	// The Windows API has changed the length of the name.
        
        }
        if (dwDomainName != *cchReferencedDomainNameU8)
        {	// The Windows API has changed the length of the reference domain name.
        
        }
        ubf_free_accept_NULL (pwcDomainName);
        ubf_free_accept_NULL (pwcName);
        if (NULL != pwcSystemName && pwcSystemName != wcSystemName)
            DoneWinU16 (pwcSystemName);
        return bRet;
    }
#endif

#ifdef HAVE_USER32
    int MessageBoxU8(
      HWND   hWnd,
      LPCSTR lpText,
      LPCSTR lpCaption,
      UINT   uType
    )
    {
        return MessageBoxExU8 (hWnd, lpText, lpCaption, uType, 0);
    }
#endif

#ifdef HAVE_USER32
    int MessageBoxExU8(
      HWND   hWnd,
      LPCSTR lpText,
      LPCSTR lpCaption,
      UINT   uType,
      WORD   wLanguageId
    )
    {
        WCHAR	wcText		[WINAPI_U8_HEAP_THRESHOLD];
        WCHAR	wcCaption	[WINAPI_U8_HEAP_THRESHOLD];
        WCHAR	*pwcText;
        WCHAR	*pwcCaption;
        int		iRetVal;
    
        pwcText		= AllocWinU16fromU8orUseThreshold (wcText, lpText);
        pwcCaption	= AllocWinU16fromU8orUseThreshold (wcCaption, lpCaption);
        iRetVal = MessageBoxExW (hWnd, pwcText, pwcCaption, uType, wLanguageId);
        DoneWinU16fromU8orUseThreshold (pwcText, wcText);
        DoneWinU16fromU8orUseThreshold (pwcCaption, wcCaption);
        return iRetVal;
    }
#endif

#ifdef HAVE_USER32
	BOOL PostSysCommandWPARAMtoThisConsole (WPARAM wparam)
	{
		HWND		hConsoleWindow;
	
		hConsoleWindow = GetConsoleWindow ();
		if (hConsoleWindow)
		{
			return PostMessageW (hConsoleWindow, WM_SYSCOMMAND, wparam, (LPARAM) NULL);
		}
		return FALSE;
	}
#endif

#ifdef HAVE_USER32
	BOOL MaxiMiseThisConsoleWindow (void)
	{
		return PostSysCommandWPARAMtoThisConsole (SC_MAXIMIZE);
	}
#endif

#ifdef HAVE_USER32
	BOOL MiniMiseThisConsoleWindow (void)
	{
		return PostSysCommandWPARAMtoThisConsole (SC_MINIMIZE);
	}
#endif

#ifdef HAVE_USER32
	BOOL RestoreThisConsoleWindow (void)
	{
		return PostSysCommandWPARAMtoThisConsole (SC_RESTORE);
	}
#endif

BOOL MoveFileU8(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
)
{
	BOOL	bRet;
	WCHAR	wcSrc [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcSrc;
	WCHAR	wcTgt [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcTgt;
	
	pwcSrc = AllocWinU16fromU8orUseThreshold (wcSrc, lpExistingFileNameU8);
	pwcTgt = AllocWinU16fromU8orUseThreshold (wcTgt, lpNewFileNameU8);
	bRet = MoveFileW (pwcSrc, pwcTgt);
	DoneWinU16fromU8orUseThreshold (pwcTgt, wcTgt);
	DoneWinU16fromU8orUseThreshold (pwcSrc, wcSrc);
	return bRet;
}

BOOL MoveFileU8long(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8
)
{
	BOOL	bRet;
	WCHAR	wcSrc [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcSrc;
	WCHAR	wcTgt [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcTgt;
	
	pwcSrc = AllocWinU16fromU8orUseThresholdLongFileName (wcSrc, lpExistingFileNameU8);
	pwcTgt = AllocWinU16fromU8orUseThresholdLongFileName (wcTgt, lpNewFileNameU8);
	bRet = MoveFileW (pwcSrc, pwcTgt);
	DoneWinU16fromU8orUseThreshold (pwcTgt, wcTgt);
	DoneWinU16fromU8orUseThreshold (pwcSrc, wcSrc);
	return bRet;
}

BOOL MoveFileExU8(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
{
	BOOL	bRet;
	WCHAR	wcSrc [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcSrc;
	WCHAR	wcTgt [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcTgt;

	pwcSrc = AllocWinU16fromU8orUseThreshold (wcSrc, lpExistingFileNameU8);
	pwcTgt = AllocWinU16fromU8orUseThreshold (wcTgt, lpNewFileNameU8);
	bRet = MoveFileExW (pwcSrc, pwcTgt, dwFlags);
	DoneWinU16fromU8orUseThreshold (pwcTgt, wcTgt);
	DoneWinU16fromU8orUseThreshold (pwcSrc, wcSrc);
	return bRet;
}

BOOL MoveFileExU8long(
  const char *lpExistingFileNameU8,
  const char *lpNewFileNameU8,
  DWORD dwFlags
)
{
	BOOL	bRet;
	WCHAR	wcSrc [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcSrc;
	WCHAR	wcTgt [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcTgt;

	pwcSrc = AllocWinU16fromU8orUseThresholdLongFileName (wcSrc, lpExistingFileNameU8);
	pwcTgt = AllocWinU16fromU8orUseThresholdLongFileName (wcTgt, lpNewFileNameU8);
	bRet = MoveFileExW (pwcSrc, pwcTgt, dwFlags);
	DoneWinU16fromU8orUseThreshold (pwcTgt, wcTgt);
	DoneWinU16fromU8orUseThreshold (pwcSrc, wcSrc);
	return bRet;
}

BOOL MoveFileWithProgressU8(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
{
	BOOL	bRet;
	WCHAR	wcSrc [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcSrc;
	WCHAR	wcTgt [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcTgt;

	pwcSrc = AllocWinU16fromU8orUseThreshold (wcSrc, lpExistingFileNameU8);
	pwcTgt = AllocWinU16fromU8orUseThreshold (wcTgt, lpNewFileNameU8);
	bRet = MoveFileWithProgressW (pwcSrc, pwcTgt, lpProgressRoutine, lpData, dwFlags);
	DoneWinU16fromU8orUseThreshold (pwcTgt, wcTgt);
	DoneWinU16fromU8orUseThreshold (pwcSrc, wcSrc);
	return bRet;
}

BOOL MoveFileWithProgressU8long(
  const char			*lpExistingFileNameU8,
  const char			*lpNewFileNameU8,
  LPPROGRESS_ROUTINE	lpProgressRoutine,
  LPVOID				lpData,
  DWORD					dwFlags
)
{
	BOOL	bRet;
	WCHAR	wcSrc [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcSrc;
	WCHAR	wcTgt [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcTgt;

	pwcSrc = AllocWinU16fromU8orUseThresholdLongFileName (wcSrc, lpExistingFileNameU8);
	pwcTgt = AllocWinU16fromU8orUseThresholdLongFileName (wcTgt, lpNewFileNameU8);
	bRet = MoveFileWithProgressW (pwcSrc, pwcTgt, lpProgressRoutine, lpData, dwFlags);
	DoneWinU16fromU8orUseThreshold (pwcTgt, wcTgt);
	DoneWinU16fromU8orUseThreshold (pwcSrc, wcSrc);
	return bRet;
}

#ifdef HAVE_SHELLAPI
	BOOL MoveToRecycleBinU8 (const char *chFileName8)
	{
		WCHAR	wcFileName [WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	*pwcFileName;
		BOOL	bRet;
		
		pwcFileName = AllocWinU16fromU8orUseThreshold_00 (wcFileName, chFileName8);

		SHFILEOPSTRUCTW		s;
	
		memset (&s, 0, sizeof (SHFILEOPSTRUCTW));
		s.hwnd		= NULL;
		s.wFunc		= FO_DELETE;
		s.pFrom		= pwcFileName;
		s.pTo		= NULL;
		s.fFlags	=	FOF_ALLOWUNDO	| FOF_NOCONFIRMATION	| FOF_NOCONFIRMMKDIR |
						FOF_NOERRORUI	| FOF_RENAMEONCOLLISION	| 
						FOF_SILENT		| FOF_FILESONLY;
		s.fAnyOperationsAborted	= FALSE;
		s.hNameMappings			= NULL;
		s.lpszProgressTitle		= NULL;
		int iR = SHFileOperationW (&s);

		DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
		bRet = 0 == iR;
		return bRet;
	}
#endif

#ifdef HAVE_SHELLAPI
	BOOL MoveToRecycleBinW (const WCHAR *wcFileName)
	{
		SHFILEOPSTRUCTW		s;
	
		memset (&s, 0, sizeof (SHFILEOPSTRUCTW));
		s.hwnd		= NULL;
		s.wFunc		= FO_DELETE;
		s.pFrom		= wcFileName;
		s.pTo		= NULL;
		s.fFlags	=	FOF_ALLOWUNDO	| FOF_NOCONFIRMATION	| FOF_NOCONFIRMMKDIR |
						FOF_NOERRORUI	| FOF_RENAMEONCOLLISION	| 
						FOF_SILENT		| FOF_FILESONLY;
		s.fAnyOperationsAborted	= FALSE;
		s.hNameMappings			= NULL;
		s.lpszProgressTitle		= NULL;
		int iR = SHFileOperationW (&s);

		// See
		//	https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shfileoperationw .
		_ASSERT_EXPR (0x7C != iR, "Parameter wcFileName requires two NUL ternimators!");

		return 0 == iR;
	}
#endif

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
	)
	{
		WCHAR			wcServerName	[WINAPI_U8_HEAP_THRESHOLD];
		WCHAR			*pcServerName;

		pcServerName = AllocWinU16fromU8orUseThreshold (wcServerName, servernameU8);
		NET_API_STATUS nap = NetUserEnum	(
								pcServerName, level, filter, bufptr, prefmaxlen,
								entriesread, totalentries, resume_handle
											);
		DoneWinU16fromU8orUseThreshold (pcServerName, wcServerName);
		return nap;
	}
#endif

HANDLE OpenEventU8(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
{
	HANDLE	hRet;
	WCHAR	wcName [MAX_PATH + 1];

	/*
		The name of an event can only be MAX_PATH characters long, hence we can implement
		this function in a very simple manner. See
		https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw .
	*/

	WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpName);
	hRet = OpenEventW (dwDesiredAccess, bInheritHandle, wcName);
	return hRet;
}

#ifdef HAVE_ADVAPI32
HANDLE OpenEventLogU8(
	LPCSTR lpUNCServerNameU8,
	LPCSTR lpSourceNameU8
)
{
	WCHAR   wcUNCServerName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR   wcSourceName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR   *pcUNCServerName;
	WCHAR   *pcSourceName;
	HANDLE  hRet;

	pcUNCServerName = AllocWinU16fromU8orUseThreshold (wcUNCServerName, lpUNCServerNameU8);
	pcSourceName    = AllocWinU16fromU8orUseThreshold (wcSourceName, lpSourceNameU8);

	hRet = OpenEventLogW (pcUNCServerName, pcSourceName);

	DoneWinU16fromU8orUseThreshold (pcUNCServerName, wcUNCServerName);
	DoneWinU16fromU8orUseThreshold (pcSourceName, wcSourceName);

	return hRet;
}
#endif

#ifdef HAVE_ADVAPI32
BOOL ClearEventLogU8(
  HANDLE  hEventLog,
  LPCSTR lpBackupFileNameU8
)
{
	WCHAR   wcBackupFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR   *pcBackupFileName;
	BOOL    bRet;

	pcBackupFileName = AllocWinU16fromU8orUseThreshold (wcBackupFileName, lpBackupFileNameU8);
	bRet = ClearEventLogW (hEventLog, pcBackupFileName);
	DoneWinU16fromU8orUseThreshold (pcBackupFileName, wcBackupFileName);
	return bRet;
}
#endif

HANDLE OpenFileMappingU8(
	DWORD  dwDesiredAccess,
	BOOL   bInheritHandle,
	LPCSTR lpName
)
{
	HANDLE	hRet;
	WCHAR	wcName [MAX_PATH + 1];

	WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpName);
	hRet = OpenFileMappingW (dwDesiredAccess, bInheritHandle, wcName);
	return hRet;
}

HANDLE OpenMutexU8(
  DWORD		dwDesiredAccess,
  BOOL		bInheritHandle,
  LPCSTR	lpNameU8
)
{
	/*
		The name of a mutex can only be MAX_PATH characters long, hence we can implement
		this function slightly simpler. See
		https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw .

		WCHAR	wcMutexName [WINAPI_U8_HEAP_THRESHOLD];
		WCHAR	*pwcMutexName;
		HANDLE	hRet;

		pwcMutexName = AllocWinU16fromU8orUseThreshold (wcMutexName, lpNameU8);
		hRet = OpenMutexW (dwDesiredAccess, bInheritHandle, pwcMutexName);
		DoneWinU16fromU8orUseThreshold (pwcMutexName, wcMutexName);
		return hRet;
	*/

	WCHAR	wcName [MAX_PATH + 1];

	WinU16_from_UTF8 (wcName, MAX_PATH + 1, lpNameU8);
	return OpenMutexW (dwDesiredAccess, bInheritHandle, wcName);
}

#ifdef HAVE_ADVAPI32
SC_HANDLE OpenSCManagerU8(
  LPCSTR lpMachineName,
  LPCSTR lpDatabaseName,
  DWORD  dwDesiredAccess
)
{
	WCHAR	wcMachineName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcDatabaseName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcMachineName;
	WCHAR	*pwcDatabaseName;
	SC_HANDLE	hRet;

	pwcMachineName	= AllocWinU16fromU8orUseThreshold (wcMachineName, lpMachineName);
	pwcDatabaseName	= AllocWinU16fromU8orUseThreshold (wcDatabaseName, lpDatabaseName);

	hRet = OpenSCManagerW (pwcMachineName, pwcDatabaseName, dwDesiredAccess);

	DoneWinU16fromU8orUseThreshold (pwcDatabaseName, wcDatabaseName);
	DoneWinU16fromU8orUseThreshold (pwcMachineName, wcMachineName);

	return hRet;
}
#endif

#ifdef HAVE_ADVAPI32
SC_HANDLE OpenServiceU8(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  DWORD     dwDesiredAccess
)
{
	if (lpServiceName)
	{
		// See
		//	https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-openservicew .
		//	The maximum string length for lpServiceName is 256 characters. We leave it
		//	with the caller to ensure this length is not exceeded.
		WCHAR	wcServiceName [512];
		WinU16_from_UTF8 (wcServiceName, 512, lpServiceName);
		return OpenServiceW (hSCManager, wcServiceName, dwDesiredAccess);
	} else
	{
		return OpenServiceW (hSCManager, NULL, dwDesiredAccess);
	}
}
#endif

BOOL PathsEqualfromEndW (WCHAR *exe, WCHAR *arg)
{
	DWORD	lene	= (DWORD) wcslen (exe);
	DWORD	lena	= (DWORD) wcslen (arg);

	if (lene && lena)
	{
		while (lene && lena && towupper (*(exe + lene)) == towupper (*(arg + lena)))
		{
			-- lene;
			-- lena;
		}
		if (0 == lene || 0 == lena)
		{	// One of the two parameters has been fully consumed.
			return TRUE;
		}
		if (lene && L'\\' == *(exe + lene))
		{
			return TRUE;
		}
		if (lena && L'\\' == *(arg + lena))
		{
			return TRUE;
		}
	}
	// If both strings have no length we want that they are not treated
	//	as equal.
	return FALSE;
}

#ifdef HAVE_SHLWAPI
BOOL PathIsUNCU8(
	LPSTR	pszPathU8
)
{	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathisuncw .
	//	Can only be up to MAX_PATH.
	WCHAR	wcPath [MAX_PATH + 1];

	WinU16_from_UTF8 (wcPath, MAX_PATH + 1, pszPathU8);
	return PathIsUNCW (wcPath);
}
#endif

#ifdef HAVE_SHLWAPI
BOOL PathIsNetworkPathU8(
	LPSTR	pszPathU8
)
{	// See
	//	https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathisnetworkpathw .
	//	Can only be up to MAX_PATH.
	WCHAR	wcPath [MAX_PATH + 1];

	WinU16_from_UTF8 (wcPath, MAX_PATH + 1, pszPathU8);
	return PathIsNetworkPathW (wcPath);
}
#endif

#ifdef HAVE_SHLWAPI
LPCSTR PathFindNextComponentU8(
	LPSTR pszPathU8
)
{	// See
	//	https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfindnextcomponentw .
	/*
		Excerpt:
		"PathFindNextComponent walks a path string until it encounters a backslash ("\"), ignores
		everything up to that point including the backslash, and returns the rest of the path.
		Therefore, if a path begins with a backslash (such as \path1\path2), the function simply
		removes the initial backslash and returns the rest (path1\path2)."

		OUTPUT:
		===========
		The path c:\path1\path2\file.txt returns path1\path2\file.txt
		The path path1\path2\file.txt returns path2\file.txt
		The path path2\file.txt returns file.txt
		The path file.txt returns a pointer to the terminating null character
		The terminating null character returns NULL

		The path \path1 returns path1
		The path \path1\path2 returns path1\path2
		The path path1\path2 returns path2
		The path c:\file.txt returns file.txt
	*/
	LPCSTR pszRet = NULL;
	if (pszPathU8 && *pszPathU8)
	{
		pszRet = strchr (pszPathU8, '\\');
		if (pszRet)
			++ pszRet;
		else
			pszRet = pszPathU8 + strlen (pszPathU8);
	}
	return pszRet;
}
#endif

#ifdef HAVE_ADVAPI32
HANDLE RegisterEventSourceU8(
  LPCSTR lpUNCServerName,
  LPCSTR lpSourceName
)
{
	WCHAR	wcUNCServerName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcSourceName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcUNCServerName;
	WCHAR	*pwcSourceName;
	HANDLE	hRet;
	
	pwcUNCServerName	= AllocWinU16fromU8orUseThreshold (wcUNCServerName, lpUNCServerName);
	pwcSourceName		= AllocWinU16fromU8orUseThreshold (wcSourceName, lpSourceName);
	hRet = RegisterEventSourceW (pwcUNCServerName, pwcSourceName);
	DoneWinU16fromU8orUseThreshold (pwcSourceName, wcSourceName);
	DoneWinU16fromU8orUseThreshold (pwcUNCServerName, wcUNCServerName);
	return hRet;
}
#endif

#ifdef HAVE_ADVAPI32
SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerU8(
  LPCSTR             lpServiceName,
  LPHANDLER_FUNCTION lpHandlerProc
)
{
	if (lpServiceName)
	{
		// Note that the maximum length for lpServiceName is 256 characters.
		//	We leave it with the caller to ensure this is adhered to.
		WCHAR	wcServiceName [512];
		WinU16_from_UTF8 (wcServiceName, 512, lpServiceName);
		return RegisterServiceCtrlHandlerW (wcServiceName, lpHandlerProc);
	}
	return RegisterServiceCtrlHandlerW (NULL, lpHandlerProc);
}
#endif

#ifdef HAVE_ADVAPI32
SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerExU8(
  LPCSTR                lpServiceName,
  LPHANDLER_FUNCTION_EX lpHandlerProc,
  LPVOID                lpContext
)
{
	if (lpServiceName)
	{
		// Note that the maximum length for lpServiceName is 256 characters.
		//	We leave it with the caller to ensure this is adhered to.
		WCHAR	wcServiceName [512];
		WinU16_from_UTF8 (wcServiceName, 512, lpServiceName);
		return RegisterServiceCtrlHandlerExW (wcServiceName, lpHandlerProc, lpContext);
	}
	return RegisterServiceCtrlHandlerExW (NULL, lpHandlerProc, lpContext);
}
#endif

BOOL RemoveDirectoryU8(
	LPCSTR lpPathNameU8
)
{
	WCHAR wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpPathNameU8);
	BOOL bRet = RemoveDirectoryW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}

BOOL RemoveDirectoryU8long(
	LPCSTR lpPathNameU8
)
{
	WCHAR wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcFileName = AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpPathNameU8);
	BOOL bRet = RemoveDirectoryW (pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}

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
{
	BOOL	bRet			= FALSE;
	WCHAR	**wstrArray;
	
	wstrArray = CreateWin16tringArrayFromU8 (lpStrings, wNumStrings);
	if (wstrArray)
	{
		bRet = ReportEventW	(
					hEventLog, wType, wCategory, dwEventID, lpUserSid, wNumStrings,
					dwDataSize, (const WCHAR **) wstrArray, lpRawData
							);
		DoneWin16StringArray (wstrArray, wNumStrings);
	}
	return bRet;
}
#endif

void SetConsoleCodePageToANSI (void)
{
	SetConsoleCP (CP_UTF8);
	SetConsoleOutputCP (1252);
}

void SetConsoleCodePageToUTF8 (void)
{
	SetConsoleCP (CP_UTF8);
	SetConsoleOutputCP (CP_UTF8);
}

bool SetConsoleEnableANSI (void)
{
	bool b = false;

	HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != hConsole)
	{
		DWORD	dwMode;
		b = GetConsoleMode (hConsole, &dwMode);
		if (b)
		{
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			b = SetConsoleMode (hConsole, dwMode);
		}
	}
	return b;
}

int WinSetStdoutToUTF16 (void)
{
	// Change stdout to Unicode UTF-16
    return _setmode(_fileno(stdout), _O_U16TEXT);
}

int WinSetStdinToUTF16 (void)
{
	// Change stdout to Unicode UTF-16
    return _setmode(_fileno(stdin), _O_U16TEXT);
}

BOOL SetCurrentDirectoryU8(
  const char *lpPathNameU8
)
{
	WCHAR wcPathName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcPathName	= AllocWinU16fromU8orUseThreshold (wcPathName, lpPathNameU8);
	BOOL bRet			= SetCurrentDirectoryW (pwcPathName);
	DoneWinU16fromU8orUseThreshold (pwcPathName, wcPathName);
	return bRet;
}

BOOL SetCurrentDirectoryU8long(
  const char *lpPathNameU8
)
{
	WCHAR wcPathName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcPathName	= AllocWinU16fromU8orUseThresholdLongFileName (wcPathName, lpPathNameU8);
	BOOL bRet			= SetCurrentDirectoryW (pwcPathName);
	DoneWinU16fromU8orUseThreshold (pwcPathName, wcPathName);
	return bRet;
}

DWORD SetFileAttributesU8(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
{
	WCHAR wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcFileName	= AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	DWORD dwRet			= SetFileAttributesW (pwcFileName, dwFileAttributes);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return dwRet;
}

DWORD SetFileAttributesU8long(
  LPCSTR	lpFileNameU8,
  DWORD		dwFileAttributes
)
{
	WCHAR wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcFileName	= AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpFileNameU8);
	DWORD dwRet			= SetFileAttributesW (pwcFileName, dwFileAttributes);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return dwRet;
}

#ifdef HAVE_ADVAPI32
BOOL SetFileSecurityU8(
  char					*lpFileNameU8,
  SECURITY_INFORMATION	SecurityInformation,
  PSECURITY_DESCRIPTOR	pSecurityDescriptor
)
{
	WCHAR wcFileName [WINAPI_U8_HEAP_THRESHOLD];
	WCHAR *pwcFileName = AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	BOOL bRet = SetFileSecurityW (pwcFileName, SecurityInformation, pSecurityDescriptor);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	return bRet;
}
#endif

typedef struct spostmsgtoprocwnds
{
	DWORD	dwProcessId;
	UINT	msg;
} SPOSTMSGTOPROCWNDS;

BOOL CALLBACK postMessageToProcessWindows (HWND hwnd, LPARAM lParam)
{
	ASSERT (NULL != (void *) lParam);
	if (NULL == (void *) lParam)
		return FALSE;

	SPOSTMSGTOPROCWNDS *ppst = (SPOSTMSGTOPROCWNDS *) lParam;
	ASSERT (NULL != ppst);

	DWORD	dwWinProcessID;
	GetWindowThreadProcessId (hwnd, &dwWinProcessID);
	//printf ("Close: Child: %d; Window: %d\n", dwChildProcessId, dwWinProcessID);
	if (ppst->dwProcessId == dwWinProcessID)
	{
		PostMessageW (hwnd, ppst->msg, (WPARAM) NULL, (LPARAM) NULL);
	}
	return TRUE;
}

static DWORD waitForProcessToExit (HANDLE hProcess, uint16_t uiFlags, uint16_t flgCheck, DWORD waitTime)
{
	if (flgCheck & uiFlags)
		return WaitForSingleObject (hProcess, waitTime);
	else
		return WaitForSingleObject (hProcess, 0);
}

bool TerminateProcessControlled (HANDLE hProcess, uint16_t uiFlags, DWORD waitTime)
{
	bool	b			= true;
	DWORD	dwWait;

	if (NULL == hProcess)
		return false;

	// If no flags are set, we set all of them.
	if (0 == uiFlags)
		uiFlags = UINT16_MAX;

	DWORD	dwChildProcessId = GetProcessId (hProcess);
	// See
	//	https://learn.microsoft.com/en-us/windows/console/generateconsolectrlevent .
	if (TERMCHILDPROCCONTROLLED_CTRL_C & uiFlags)
	{
		b &= GenerateConsoleCtrlEvent (CTRL_C_EVENT, dwChildProcessId);
		dwWait = waitForProcessToExit (hProcess, uiFlags, TERMCHILDPROCCONTROLLED_WAIT_CTRL_C, waitTime);
		if (WAIT_OBJECT_0 == dwWait)
			goto cleanUp;
	}
	if (TERMCHILDPROCCONTROLLED_CTRL_BREAK & uiFlags)
	{
		b &= GenerateConsoleCtrlEvent (CTRL_BREAK_EVENT,	dwChildProcessId);
		dwWait = waitForProcessToExit (hProcess, uiFlags, TERMCHILDPROCCONTROLLED_WAIT_CTRL_BREAK, waitTime);
		if (WAIT_OBJECT_0 == dwWait)
			goto cleanUp;
	}

	if (TERMCHILDPROCCONTROLLED_WM_CLOSE & uiFlags)
	{
		SPOSTMSGTOPROCWNDS pst;
		pst.dwProcessId	= dwChildProcessId;
		pst.msg			= WM_CLOSE;
		EnumWindows ((WNDENUMPROC) postMessageToProcessWindows, (LPARAM) &pst);
		dwWait = waitForProcessToExit (hProcess, uiFlags, TERMCHILDPROCCONTROLLED_WAIT_WM_CLOSE, waitTime);
		if (WAIT_OBJECT_0 == dwWait)
			goto cleanUp;
	}

	if (TERMCHILDPROCCONTROLLED_WM_QUIT & uiFlags)
	{
		SPOSTMSGTOPROCWNDS pst;
		pst.dwProcessId	= dwChildProcessId;
		pst.msg			= WM_QUIT;
		EnumWindows ((WNDENUMPROC) postMessageToProcessWindows, (LPARAM) &pst);
		dwWait = waitForProcessToExit (hProcess, uiFlags, TERMCHILDPROCCONTROLLED_WAIT_WM_QUIT, waitTime);
		if (WAIT_OBJECT_0 == dwWait)
			goto cleanUp;
	}

	if (TERMCHILDPROCCONTROLLED_TERMINATE & uiFlags)
	{
		b &= TerminateProcess (hProcess, ERROR_PROCESS_ABORTED);
		dwWait = waitForProcessToExit (hProcess, uiFlags, TERMCHILDPROCCONTROLLED_WAIT_TERMINATE, waitTime);
		if (WAIT_OBJECT_0 == dwWait)
			goto cleanUp;
	}
	b = false;

	cleanUp:
	return b;
}

BOOL IsFirstArgumentExeArgumentW (int *pargc, WCHAR **pargv [])
{
	ASSERT (NULL != pargc);

	if (*pargc)
	{
		WCHAR *arg	= *pargv [0];
		// Remove "." and ".." prefixes.
		if (L'.' == arg [0])
			++ arg;
		if (L'.' == arg [0])
			++ arg;

		WCHAR wcExe [4096];
		DWORD dwLenModuleFileName;

		if ((dwLenModuleFileName = GetModuleFileNameW (NULL, wcExe, 4096)) < 4096)
		{
			if (PathsEqualfromEndW (wcExe, arg))
			{	// Is executable argument.
				return TRUE;
			}
			WCHAR *wc = wcsrchr (wcExe, L'.');
			if (wc)
				*wc = L'\0';
			if (PathsEqualfromEndW (wcExe, arg))
			{	// Is executable argument.
				return TRUE;
			}
		} else
		{	// The executable path is too long.
			ASSERT (FALSE);
		}
	}
	return FALSE;
}

BOOL SwallowExeArgumentW (int *pargc, WCHAR **pargv [])
{
	ASSERT (NULL != pargc);

	if (IsFirstArgumentExeArgumentW (pargc, pargv))
	{
		*pargc -= 1;										// Argument counter.
		*pargv += 1;										// Point to new first argument.
		return TRUE;
	}
	return FALSE;
}

WCHAR **InsertExeArgumentIfMissingW(int *pargc, WCHAR **pargv [])
{
	ASSERT (NULL != pargc);

	if (IsFirstArgumentExeArgumentW (pargc, pargv))
	{
		return *pargv;
	}

	WCHAR	wcExe [4096];
	DWORD	dwLenModuleFileName;
	WCHAR	**pwcRet;
	int		n;

	++ *pargc;
	if ((dwLenModuleFileName = GetModuleFileNameW (NULL, wcExe, 4096)) < 4096)
	{
		pwcRet = ubf_malloc (*pargc * sizeof (WCHAR*));
		if (pwcRet)
		{
			pwcRet [0] = _wcsdup (wcExe);
			for (n = 1; n < *pargc; ++ n)
			{
				pwcRet [n] = *pargv [n - 1];
			}
		}
		return pwcRet;
	} else
	{	// The executable path is too long.
		ASSERT (FALSE);
	}
	return *pargv;
}

#ifdef _MSC_VER
#pragma warning (default: 4456)									// Previous declaration hidden
																//	(wcExe).
#endif

#ifdef HAVE_MPR
DWORD WNetGetUniversalNameU8(
	LPCSTR  lpLocalPathU8,
	DWORD   dwInfoLevel,
	LPVOID  lpBuffer,
	LPDWORD lpBufferSize
)
{
	int iReqSize = reqWinU16wchars (lpLocalPathU8);
	if (iReqSize <= WINAPI_U8_HEAP_THRESHOLD)
	{
		WCHAR wcPath [WINAPI_U8_HEAP_THRESHOLD];
		WinU16_from_UTF8 (wcPath, iReqSize, lpLocalPathU8);
		return WNetGetUniversalNameW (wcPath, dwInfoLevel, lpBuffer, lpBufferSize);
	} else
	{
		DWORD	dwRet;
		WCHAR *pwcPath = AllocWinU16_from_UTF8 (lpLocalPathU8);
		if (pwcPath)
		{
			dwRet = WNetGetUniversalNameW (pwcPath, dwInfoLevel, lpBuffer, lpBufferSize);
			DoneWinU16 (pwcPath);
			return dwRet;
		}
	}
	ASSERT (FALSE);
	return FALSE;
}
#endif

BOOL WritePrivateProfileStringU8(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8
)
{
	WCHAR	wcAppName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcKeyName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcString	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcFileName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcAppName		= NULL;
	WCHAR	*pwcKeyName		= NULL;
	WCHAR	*pwcString		= NULL;
	WCHAR	*pwcFileName	= NULL;
	BOOL	bRet			= FALSE;
	
	if (lpAppNameU8)
		pwcAppName	= AllocWinU16fromU8orUseThreshold (wcAppName, lpAppNameU8);
	if (lpKeyNameU8)
		pwcKeyName	= AllocWinU16fromU8orUseThreshold (wcKeyName, lpKeyNameU8);
	if (lpStringU8)
		pwcString	= AllocWinU16fromU8orUseThreshold (wcString, lpStringU8);
	if (lpFileNameU8)
		pwcFileName	= AllocWinU16fromU8orUseThreshold (wcFileName, lpFileNameU8);
	bRet = WritePrivateProfileStringW (pwcAppName, pwcKeyName, pwcString, pwcFileName);
	if (lpFileNameU8)
		DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	if (lpStringU8)
		DoneWinU16fromU8orUseThreshold (pwcString, wcString);
	if (lpKeyNameU8)
		DoneWinU16fromU8orUseThreshold (pwcKeyName, wcKeyName);
	if (lpAppNameU8)
		DoneWinU16fromU8orUseThreshold (pwcAppName, wcAppName);
	return bRet;
}

/*
	Only an example! The API does not support long filename prefixes!
	
BOOL WritePrivateProfileStringU8long(
	LPCSTR lpAppNameU8,
	LPCSTR lpKeyNameU8,
	LPCSTR lpStringU8,
	LPCSTR lpFileNameU8absolute
)
{
	WCHAR	wcAppName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcKeyName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcString	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	wcFileName	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pwcAppName		= NULL;
	WCHAR	*pwcKeyName		= NULL;
	WCHAR	*pwcString		= NULL;
	WCHAR	*pwcFileName	= NULL;
	BOOL	bRet			= FALSE;
	
	pwcAppName	= AllocWinU16fromU8orUseThreshold (wcAppName, lpAppNameU8);
	pwcKeyName	= AllocWinU16fromU8orUseThreshold (wcKeyName, lpKeyNameU8);
	pwcString	= AllocWinU16fromU8orUseThreshold (wcString, lpStringU8);
	pwcFileName	= AllocWinU16fromU8orUseThresholdLongFileName (wcFileName, lpFileNameU8absolute);
	bRet = WritePrivateProfileStringW (pwcAppName, pwcKeyName, pwcString, pwcFileName);
	DoneWinU16fromU8orUseThreshold (pwcFileName, wcFileName);
	DoneWinU16fromU8orUseThreshold (pwcString, wcString);
	DoneWinU16fromU8orUseThreshold (pwcKeyName, wcKeyName);
	DoneWinU16fromU8orUseThreshold (pwcAppName, wcAppName);
	return bRet;
}
*/

int vfprintfU8toU16stream (FILE *stream, const char *format, va_list ap)
{
	int			iReq;
	int			iRet		= -1;

	iReq = vsnprintf (NULL, 0, format, ap);

	WCHAR	wcToPrint	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcToPrint;

	if (iReq < WINAPI_U8_HEAP_THRESHOLD)
	{
		char	szToPrint	[WINAPI_U8_HEAP_THRESHOLD];

		vsnprintf (szToPrint, WINAPI_U8_HEAP_THRESHOLD, format, ap);
		pcToPrint = AllocWinU16fromU8orUseThreshold (wcToPrint, szToPrint);
		if (pcToPrint)
		{
			iRet = fwprintf (stream, pcToPrint);
			DoneWinU16fromU8orUseThreshold (pcToPrint, wcToPrint);
		}
	} else
	{
		char	*szToPrint = ubf_malloc (((size_t) (iReq)) + 1);

		if (szToPrint)
		{
			vsnprintf (szToPrint, ((size_t) (iReq)) + 1, format, ap);
			pcToPrint = AllocWinU16fromU8orUseThreshold (wcToPrint, szToPrint);
			if (pcToPrint)
			{
				iRet = fwprintf (stream, pcToPrint);
				DoneWinU16fromU8orUseThreshold (pcToPrint, wcToPrint);
			}
			ubf_free (szToPrint);
		}
	}
	return iRet;
}

int fprintfU8toU16stream (FILE *stream, const char *format, ...)
{
	int			iRet		= -1;
	va_list		args;

	va_start (args, format);
	iRet = vfprintfU8toU16stream (stream, format, args);
	va_end (args);

	return iRet;
}

int putsU8toU16stdout (const char *strU8)
{
	WCHAR	wcToPrint	[WINAPI_U8_HEAP_THRESHOLD];
	WCHAR	*pcToPrint;
	int		iRet		= EOF;

	pcToPrint = AllocWinU16fromU8orUseThreshold (wcToPrint, strU8);
	if (pcToPrint)
	{
		iRet = _putws (pcToPrint);
		DoneWinU16fromU8orUseThreshold (pcToPrint, wcToPrint);
	}
	return iRet;
}

#endif														// Of #ifdef _WIN32.
