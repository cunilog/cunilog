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
		#include "./ubfmem.h"
		#include "./strisdotordotdot.h"
		#include "./ubfdebug.h"
	#else
		#include "./../../mem/ubfmem.h"
		#include "./../../string/strisdotordotdot.h"
		#include "./../../dbg/ubfdebug.h"
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
	uint64_t ForEachDirectoryEntryU8_Ex	(
					const char				*strPathU8,
					pForEachDirEntryU8		fedEnt,
					void					*pCustom,
					unsigned int			*pnSubLevels,
					SMEMBUF                 *pmb
										)
	{
		HANDLE				hFind;
		WIN32_FIND_DATAW	wfdW;
		uint64_t			uiEnts				= 0;			// The return value.
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
						unsigned int nSubLevels = *pnSubLevels;
						uiEnts += ForEachDirectoryEntryU8_Ex	(
												pmb->buf.pch,
												fedEnt,
												pCustom,
												&nSubLevels,
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

uint64_t ForEachDirectoryEntryU8	(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				unsigned int			*pnSubLevels
									)
{
	HANDLE				hFind;
	WIN32_FIND_DATAW	wfdW;
	uint64_t			uiEnts				= 0;			// The return value.
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
					unsigned int nSubLevels = *pnSubLevels;
					uiEnts += ForEachDirectoryEntryU8	(
									subPath,
									fedEnt,
									pCustom,
									&nSubLevels
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

#endif														// Of #ifdef _WIN32.
