/****************************************************************************************

	File		WinAPI_ReadDirFncts.c
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

#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <stdlib.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_ReadDirFncts.h"
	#include "./WinAPI_U8.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./ubfmem.h"
		#include "./strfilesys.h"
		#include "./strisdotordotdot.h"
		#include "./strmembuf.h"
		#include "./strwildcards.h"
	#else
		#include "./../../dbg/ubfdebug.h"
		#include "./../../mem/ubfmem.h"
		#include "./../../string/strfilesys.h"
		#include "./../../string/strisdotordotdot.h"
		#include "./../../string/strmembuf.h"
		#include "./../../string/strwildcards.h"
	#endif

#endif

#ifdef _WIN32

BOOL ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition (SRDIRONEENTRYSTRUCT *pign)
{
	ubf_assert_non_NULL (pign);

	return
			isDotOrDotDotW (pign->pwfd->cFileName)
		||	pign->pwfd->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN
		||	pign->pwfd->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM
	;
}

SDIRW *ReadDirectoryEntriesSDIRW_WU8_ex	(
						void					*strPathWorU8,
						enum enrdirentssdirw	u,
						DWORD					*pdwEntries,
						IgnoreCondCB			pIgnore,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
{
	HANDLE				hFind				= INVALID_HANDLE_VALUE;
	SDIRW				*swdFirst			= NULL;
	SDIRW				*swd;
	SDIRW				*swdPrev			= NULL;
	WIN32_FIND_DATAW	wfdLocal;
	DWORD				dwEnts				= 0;
	SRDIRONEENTRYSTRUCT	sicData;

	// Distinguish between UFT-16 and UTF-8 version.
	WCHAR				*pwstrPath;
	char				*pstrPath;

	switch (u)
	{
		case EN_READ_DIR_ENTS_SDIRW_UTF8:
			pwstrPath = (WCHAR *) strPathWorU8;
			hFind = FindFirstFileW (pwstrPath, &wfdLocal);
			break;
		case EN_READ_DIR_ENTS_SDIRW_UTF16:
			pstrPath = (char *) strPathWorU8;
			hFind = FindFirstFileU8 (pstrPath, &wfdLocal);
			break;
	}

	// Parameter for the ignore callback funciton.
	sicData.UTF8orUTF16.pstrPathWorU8	= strPathWorU8;
	sicData.pwfd						= &wfdLocal;
	sicData.u							= u;
	sicData.pCustom						= pCustom;
	// Ignore condition callback function.
	IgnoreCondCB pIgnoreEntry =	pIgnore	? pIgnore
										: (IgnoreCondCB) ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition;
	// Memory allocation callback function.
	#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
		RDEMallocCB pMallocEntry =
			pMalloc ? pMalloc : (RDEMallocCB) ubf_malloc;
	#else
		RDEMallocCB pMallocEntry =
			pMalloc ? pMalloc : (RDEMallocCB) malloc;
	#endif
	if (INVALID_HANDLE_VALUE == hFind)
	{	// Maybe no files or whatever.
		goto Return;
	}
	do
	{	// Go through the folder and pick up each file. Ignore accordingly.
		if (pIgnoreEntry (&sicData))
		{	// Entries to be ignored.
		} else
		{
			swd = pMallocEntry (sizeof (SDIRW));
			if (NULL == swd)
			{	// Not enough space on the heap.
				swdFirst = ReleaseDirectoryEntriesSDIRW (swdFirst);
				dwEnts = (DWORD) -1;
				SetLastError (ERROR_NOT_ENOUGH_MEMORY);
				goto Return;
			}
			++ dwEnts;										// Amount of found entries.
			swd->_next = NULL;
			copyWIN32_FIND_DATAW (&swd->wfdW, &wfdLocal);
			if (NULL == swdFirst)
				swdFirst = swd;
			if (swdPrev)
				swdPrev->_next = swd;
			swdPrev = swd;
		}
	} while (FindNextFileW (hFind, &wfdLocal) != 0);
	FindClose (hFind);
Return:
	//printf ("%d entries created.\n", dwEnts);
	if (pdwEntries)
		*pdwEntries = dwEnts;
	return swdFirst;
}

SDIRW *ReadDirectoryEntriesSDIRW_W		(
						WCHAR					*wstrPath,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
{
	return ReadDirectoryEntriesSDIRW_WU8_ex (wstrPath, EN_READ_DIR_ENTS_SDIRW_UTF16,
				pdwEntries, ig, pCustom, pMalloc);
}

SDIRW *ReadDirectoryEntriesSDIRW_U8		(
						char					*strPathU8,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
{
	return ReadDirectoryEntriesSDIRW_WU8_ex (strPathU8, EN_READ_DIR_ENTS_SDIRW_UTF8,
				pdwEntries, ig, pCustom, pMalloc);
}

SDIRW *ReleaseDirectoryEntriesSDIRW (SDIRW *swd)
{
	SDIRW	*swdNext;

	while (swd)
	{
		swdNext = swd->_next;
		ubf_free (swd);
		swd = swdNext;
	}
	return NULL;
}

uint64_t ReleaseDirectoryEntriesSDIRW_cnt (SDIRW *swd)
{
	SDIRW		*swdNext;
	uint64_t	uiRet		= 0;

	while (swd)
	{
		swdNext = swd->_next;
		ubf_free (swd);
		swd = swdNext;
		++ uiRet;
	}
	return uiRet;
}

#ifdef HAVE_MEMBUF
	size_t ForEachDirectoryEntryU8_Ex	(
					const char				*strPathU8,
					pForEachDirEntryU8		fedEnt,
					void					*pCustom,
					size_t					*pnSubLevels,
					SMEMBUF                 *pmb
										)
	{
		HANDLE				hFind;
		WIN32_FIND_DATAW	wfdW;
		size_t				uiEnts				= 0;			// The return value.
		SRDIRONEENTRYSTRUCT	sdOneEntry;
		DWORD				dwErrToReturn;

		sdOneEntry.UTF8orUTF16.pstrPathWorU8	= strPathU8;
		sdOneEntry.pwfd							= &wfdW;
		sdOneEntry.u							= EN_READ_DIR_ENTS_SDIRW_UTF8;
		sdOneEntry.pCustom						= pCustom;
		hFind = FindFirstFileU8 (strPathU8, &wfdW);
		if (INVALID_HANDLE_VALUE == hFind)
		{	// Maybe no files or whatever. Remember the system error code here.
			dwErrToReturn = GetLastError ();
			goto Return;
		}
		do
		{
			// Go through the folder and pick up each entry.
			if (!isDotOrDotDotW (wfdW.cFileName))
			{
				++ uiEnts;
				if (fedEnt)
				{
					if (!fedEnt (&sdOneEntry))
						break;
				}
				if	(
							wfdW.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
						&&	pnSubLevels
						&&	*pnSubLevels
					)
				{
					*pnSubLevels -= 1;
					bool bSubpath = U8pathSMEMBUF_from_U8path_and_WinU16FileName    (
										pmb, strPathU8, USE_STRLEN, wfdW.cFileName
																					);
					if (bSubpath)
					{	// Recursively invoke us again.
						uiEnts += ForEachDirectoryEntryU8_Ex	(
												pmb->buf.pch,
												fedEnt,
												pCustom,
												pnSubLevels,
												pmb
																);
					}
					*pnSubLevels += 1;
				}
			}
		} while (FindNextFileW (hFind, &wfdW) != 0);

		// We want the caller to be able to obtain the last error produced by FindNextFileW ()
		//	instead of FindClose ().
		dwErrToReturn = GetLastError ();
		FindClose (hFind);

	Return:
		SetLastError (dwErrToReturn);
		return uiEnts;
	}
#endif

size_t ForEachDirectoryEntryU8		(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels
									)
{
	HANDLE				hFind;
	WIN32_FIND_DATAW	wfdW;
	size_t				uiEnts				= 0;			// The return value.
	SRDIRONEENTRYSTRUCT	sdOneEntry;
	DWORD				dwErrToReturn;

	sdOneEntry.UTF8orUTF16.pstrPathWorU8	= strPathU8;
	sdOneEntry.pwfd							= &wfdW;
	sdOneEntry.u							= EN_READ_DIR_ENTS_SDIRW_UTF8;
	sdOneEntry.pCustom						= pCustom;
	hFind = FindFirstFileU8 (strPathU8, &wfdW);
	if (INVALID_HANDLE_VALUE == hFind)
	{	// Maybe no files or whatever.
		return uiEnts;
	}
	do
	{
		// Go through the folder and pick up each entry.
		if (!isDotOrDotDotW (wfdW.cFileName))
		{
			++ uiEnts;
			if (fedEnt)
			{
				if (!fedEnt (&sdOneEntry))
					break;
			}
			if	(
						wfdW.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
					&&	pnSubLevels
					&&	*pnSubLevels
				)
			{
				*pnSubLevels -= 1;
				char *subPath = AllocU8path_from_U8path_and_WinU16FileName (strPathU8, wfdW.cFileName);
				if (subPath)
				{	// Recursively invoke us again.
					uiEnts += ForEachDirectoryEntryU8	(
									subPath,
									fedEnt,
									pCustom,
									pnSubLevels
														);
					DoneU8 (subPath);
				}
				*pnSubLevels += 1;
			}
		}
	} while (FindNextFileW (hFind, &wfdW) != 0);

	// We want the caller to be able to obtain the last error produced by FindNextFileW ()
	//	instead of FindClose ().
	dwErrToReturn = GetLastError ();
	FindClose (hFind);

	SetLastError (dwErrToReturn);
	return uiEnts;
}

static const char	ccCoverAllMask []	= "\\*";
#define SIZCOVERALLMSK	(sizeof (ccCoverAllMask))
#define LENCOVERALLMSK	(sizeof (ccCoverAllMask) - 1)

/*
	Requires correct path navigators.
	Requires correct lengths.
	No NULL checks.
*/
size_t ForEachDirEntryMaskU8intern	(
				const char				*szFolder,
				size_t					lnFolder,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels,
				SRDIRONEENTRYSTRUCT		*psdE
									)
{
	ubf_assert_non_NULL	(psdE);
	ubf_assert			(USE_STRLEN != lnFolder);
	ubf_assert			(USE_STRLEN != psdE->lnFileMask);

	size_t				uiEnts			= 0;				// The return value.
	DWORD				dwErrToReturn	= ERROR_SUCCESS;

	growToSizeSMEMBUF (&psdE->mbSearchPath, lnFolder + SIZCOVERALLMSK);
	if (isUsableSMEMBUF (&psdE->mbSearchPath))
	{
		memcpy (psdE->mbSearchPath.buf.pch, szFolder, lnFolder);
		memcpy (psdE->mbSearchPath.buf.pch + lnFolder, ccCoverAllMask, SIZCOVERALLMSK);
		psdE->lnSearchPath = lnFolder + LENCOVERALLMSK;

		HANDLE hFind = FindFirstFileU8long (psdE->mbSearchPath.buf.pch, psdE->pwfd);
		if (INVALID_HANDLE_VALUE == hFind)
		{	// Maybe no files or whatever.
			return uiEnts;
		}

		ubf_assert_non_0 (sizeof (UBF_WIN_DIR_SEP_STR) - 1);
		ubf_assert_non_0 (1 == sizeof (UBF_WIN_DIR_SEP_STR) - 1);
		growToSizeRetainSMEMBUF (&psdE->mbFullPathU8, lnFolder + sizeof (UBF_WIN_DIR_SEP_STR) - 1 + UTF8_MAX_PATH);
		if (isUsableSMEMBUF (&psdE->mbFullPathU8))
		{
			memcpy	(
				psdE->mbFullPathU8.buf.pch + lnFolder,
				UBF_WIN_DIR_SEP_STR,
				sizeof (UBF_WIN_DIR_SEP_STR)
					);
			psdE->szPathU8		= psdE->mbFullPathU8.buf.pch + psdE->lnInitPathU8 + 1;
			psdE->szFileNameU8	= psdE->szPathU8;
			bool bContinue		= true;
			do
			{	// Go through the folder and pick up each entry.
				if (!isDotOrDotDotW (psdE->pwfd->cFileName))
				{
					++ uiEnts;
					psdE->stFileNameU8 = UTF8_from_WinU16	(
												psdE->szFileNameU8, UTF8_MAX_PATH,
												psdE->pwfd->cFileName
															);
					ubf_assert (0 < psdE->stFileNameU8);
					psdE->lnPathU8 = psdE->stFileNameU8 - 1;
					bool bMatch = matchWildcardPattern	(
									psdE->szPathU8,		psdE->lnPathU8,
									psdE->szFileMask,	psdE->lnFileMask
														);
					bContinue = fedEnt && bMatch ? fedEnt (psdE) : true;
					if (
								bContinue
							&&	pnSubLevels
							&&	*pnSubLevels
							&&	psdE->pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
						)
					{
						*pnSubLevels -= 1;
						/*
						psdE->lnSearchPath = SMEMBUFstrconcat	(
												&psdE->mbSearchPath,	psdE->lnSearchPath,
												psdE->szFileNameU8,		psdE->stFileNameU8 - 1,
												64
																);
						*/
						// Recursively invoke us again.
						//size_t lnFullPath = lnFolder + 1;	// Includes terminating path separator.
						psdE->lnFullPathU8 = lnFolder + 1 + psdE->stFileNameU8 - 1;
						ubf_assert (strlen (psdE->mbFullPathU8.buf.pch) == psdE->lnFullPathU8);
						uiEnts = ForEachDirEntryMaskU8intern	(
										psdE->mbFullPathU8.buf.pcc,
										psdE->lnFullPathU8,
										fedEnt, pCustom, pnSubLevels, psdE
																);
						*pnSubLevels += 1;
					}
				}
			} while (bContinue && FindNextFileW (hFind, psdE->pwfd));

			// We want the caller to be able to obtain the last error produced by FindNextFileW ()
			//	instead of FindClose ().
			dwErrToReturn = GetLastError ();
			FindClose (hFind);
		} else
			dwErrToReturn = ERROR_NOT_ENOUGH_MEMORY;
	} else
		dwErrToReturn = ERROR_NOT_ENOUGH_MEMORY;
	SetLastError (dwErrToReturn);
	return uiEnts;
}

size_t ForEachDirectoryEntryMaskU8	(
				const char				*strFolderU8,
				size_t					lenFolderU8,
				const char				*strFileMaskU8,
				size_t					lenFileMaskU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels
									)
{
	ubf_assert_non_NULL	(strFolderU8);
	ubf_assert_non_0	(lenFolderU8);

	size_t	uiEnts		= 0;
	size_t	folderU8len = str_remove_last_dir_separator (strFolderU8, lenFolderU8);
	char	*szFolder;
	if (folderU8len)
	{
		szFolder = ubf_malloc (folderU8len + 1);
		if (szFolder)
		{
			memcpy (szFolder, strFolderU8, folderU8len); szFolder [folderU8len] = ASCII_NUL;
			str_correct_dir_separators (szFolder, folderU8len);
			str_remove_path_navigators (szFolder, &folderU8len);
			size_t fileMaskU8len = strFileMaskU8 ? (USE_STRLEN == lenFileMaskU8 ? strlen (strFileMaskU8) : lenFileMaskU8) : 0;

			WIN32_FIND_DATAW	wfdW;
			SRDIRONEENTRYSTRUCT	sdOneEntry;
			sdOneEntry.UTF8orUTF16.pstrPathWorU8	= strFolderU8;
			sdOneEntry.u							= EN_READ_DIR_ENTS_SDIRW_UTF8;
			sdOneEntry.pwfd							= &wfdW;
			sdOneEntry.pCustom						= pCustom;
			sdOneEntry.szFileMask					= strFileMaskU8;
			sdOneEntry.lnFileMask					= fileMaskU8len;
			sdOneEntry.szPathU8						= NULL;

			INITSMEMBUF (sdOneEntry.mbSearchPath);
			INITSMEMBUF (sdOneEntry.mbFullPathU8);

			sdOneEntry.lnInitPathU8 = folderU8len;
			size_t stToReserve = folderU8len + sizeof (UBF_WIN_DIR_SEP_STR) - 1 + UTF8_MAX_PATH;
			growToSizeSMEMBUF (&sdOneEntry.mbFullPathU8, stToReserve);
			if (isUsableSMEMBUF (&sdOneEntry.mbFullPathU8))
			{
				memcpy (sdOneEntry.mbFullPathU8.buf.pch, szFolder, folderU8len);
				memcpy	(
					sdOneEntry.mbFullPathU8.buf.pch + folderU8len,
					UBF_WIN_DIR_SEP_STR, sizeof (UBF_WIN_DIR_SEP_STR)
						);
				uiEnts = ForEachDirEntryMaskU8intern	(
							szFolder, folderU8len,
							fedEnt, pCustom, pnSubLevels, &sdOneEntry
														);
			}

			DONESMEMBUF (sdOneEntry.mbFullPathU8);
			DONESMEMBUF (sdOneEntry.mbSearchPath);
			ubf_free (szFolder);
		}
	} else
		SetLastError (ERROR_INVALID_PARAMETER);
	return uiEnts;
}

#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
	static uint64_t uiTstGlob;

	bool perFile (SRDIRONEENTRYSTRUCT *psdE)
	{
		ubf_assert_non_NULL (psdE);
		ubf_assert (EN_READ_DIR_ENTS_SDIRW_UTF8 == psdE->u);

		char cFilename [UTF8_MAX_PATH];
		UTF8_from_WinU16 (cFilename, UTF8_MAX_PATH, psdE->pwfd->cFileName);
		printf ("P: %s, %s\n", psdE->UTF8orUTF16.chPathU8, cFilename);
		++ uiTstGlob;
		if (uiTstGlob >= 100)
			ubf_assert (false);
		return true;
	}

	bool ForEachDirectoryEntryMaskU8TestFnct (void)
	{
		bool b = true;

		size_t	ui	= SIZE_MAX;
		size_t	n;

		n = ForEachDirectoryEntryMaskU8	(
				"C:\\temp",		USE_STRLEN,
				"*.txt",		USE_STRLEN,
				perFile, NULL, &ui
										);
		UNREFERENCED_PARAMETER (n);
		/*
		n = ForEachDirectoryEntryMaskU8	(
				"C:/temp/",		USE_STRLEN,
				"*.txt",		USE_STRLEN,
				perFile, NULL, &ui
										);
		UNREFERENCED_PARAMETER (n);
		n = ForEachDirectoryEntryMaskU8	(
				"C:\\temp",		USE_STRLEN,
				"*.txt",		USE_STRLEN,
				perFile, NULL, &ui
										);
		UNREFERENCED_PARAMETER (n);

		n = ForEachDirectoryEntryMaskU8	(
				"C:\\temp\\",	USE_STRLEN,
				"*.txt",		USE_STRLEN,
				perFile, NULL, &ui
										);
		*/

		UNREFERENCED_PARAMETER (ui);
		UNREFERENCED_PARAMETER (n);
		UNREFERENCED_PARAMETER (b);

		return b;
	}
#endif

#endif														// Of #ifdef _WIN32.
