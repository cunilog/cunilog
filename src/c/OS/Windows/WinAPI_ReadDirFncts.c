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

	Copyright (c) 2024-2026 Thomas

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
		#include "./ArrayMacros.h"
		#include "./unref.h"
		#include "./ubfdebug.h"
		#include "./ubfmem.h"
		#include "./strfilesys.h"
		#include "./strisdotordotdot.h"
		#include "./strmembuf.h"
		#include "./strwildcards.h"
	#else
		#include "./../../pre/ArrayMacros.h"
		#include "./../../pre/unref.h"
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
			pstrPath = (char *) strPathWorU8;
			hFind = FindFirstFileU8 (pstrPath, &wfdLocal);
			break;
		case EN_READ_DIR_ENTS_SDIRW_UTF16:
			pwstrPath = (WCHAR *) strPathWorU8;
			hFind = FindFirstFileExW	(
				pwstrPath, FindExInfoBasic, &wfdLocal,
				FindExSearchNameMatch, NULL, FIND_FIRST_EX_CASE_SENSITIVE
										);
			/*
			hFind = FindFirstFileW (pwstrPath, &wfdLocal);
			*/
			break;
	}

	// Parameter for the ignore callback funciton.
	sicData.UTF8orUTF16.strOrgPathWorU8	= strPathWorU8;
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
		#ifdef UBF_MEM_DEBUG_USE_OUR_DEBUG_FUNCS
			ubf_free (swd);
		#else
			free (swd);
		#endif
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

		sdOneEntry.UTF8orUTF16.strOrgPathWorU8	= strPathU8;
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

static const char	ccCoverAllMask []	= "\\*";
#define SIZCOVERALLMSK	(sizeof (ccCoverAllMask))
#define LENCOVERALLMSK	(sizeof (ccCoverAllMask) - 1)

/*
	Requires correct path navigators.
	Requires correct lengths.
	No NULL checks.
*/
size_t ForEachDirEntryMaskU8intern		(
				size_t					lenFolderU8,
				pForEachDirEntryU8		fedEntCB,
				SRDIRONEENTRYSTRUCT		*psdE,
				size_t					*pnSubLevels,
				void					*pCustom
									)
{
	ubf_assert_non_NULL	(psdE);
	ubf_assert_non_NULL (psdE->mbPathBuf.buf.pcc);
	ubf_assert			(isInitialisedSMEMBUF (&psdE->mbPathBuf));
	ubf_assert			(EN_READ_DIR_ENTS_SDIRW_UTF8 == psdE->u);
	ubf_assert			(USE_STRLEN != psdE->lnMaskU8);

	size_t				uiEnts			= 0;				// The return value.
	bool				bContinue		= true;
	
	// Here we only take care of the current folder level.
	size_t stPathBuf		= lenFolderU8
							+ LENOFSTR (UBF_WIN_DIR_SEP_STR) + UTF8_MAX_PATH
							+ 1;							// NUL terminator.
	stPathBuf				+= LENCOVERALLMSK;
	growToSizeRetainSMEMBUF (&psdE->mbPathBuf,		stPathBuf);
	if (!isUsableSMEMBUF (&psdE->mbPathBuf))
		return uiEnts;

	memcpy (psdE->mbPathBuf.buf.pch + lenFolderU8, ccCoverAllMask, SIZCOVERALLMSK);

	HANDLE hFind = FindFirstFileU8long (psdE->mbPathBuf.buf.pch, psdE->pwfd);
	if (INVALID_HANDLE_VALUE == hFind)
		return uiEnts;

	do
	{
		if (isDotOrDotDotW (psdE->pwfd->cFileName))
			continue;

		// The buffer already contains a backslash because ccCoverAllMask starts with one.
		psdE->szFullPathU8	= psdE->mbPathBuf.buf.pcc;
		psdE->szPathU8		= psdE->mbPathBuf.buf.pcc + psdE->lnOrgPathU8 + LENOFSTR (UBF_WIN_DIR_SEP_STR);

		psdE->szFileNameU8	= psdE->mbPathBuf.buf.pcc + lenFolderU8 + LENOFSTR (UBF_WIN_DIR_SEP_STR);
		size_t stFileNameU8 = UTF8_from_WinU16	(
									(char *) psdE->szFileNameU8, UTF8_MAX_PATH,
									psdE->pwfd->cFileName
												);
		psdE->lnFileNameU8 = stFileNameU8 - 1;
		ubf_assert (0 < stFileNameU8);
		ubf_assert (ASCII_NUL == psdE->szFileNameU8 [psdE->lnFileNameU8]);

		psdE->lnFullPathU8	= lenFolderU8 + LENOFSTR (UBF_WIN_DIR_SEP_STR) + psdE->lnFileNameU8;
		psdE->lnPathU8		= lenFolderU8 + psdE->lnFileNameU8 - psdE->lnOrgPathU8;
		ubf_assert (ASCII_NUL == psdE->szPathU8 [psdE->lnPathU8]);

		bool bMatch = matchWildcardPattern	(
						psdE->szPathU8,	psdE->lnPathU8,
						psdE->szMaskU8,	psdE->lnMaskU8
											);

		// Ensure that everything's fine for the callback function.
		ubf_assert (ASCII_NUL == psdE->szFullPathU8 [psdE->lnFullPathU8]);
		ubf_assert (strlen (psdE->szFullPathU8)		== psdE->lnFullPathU8);
		ubf_assert (strlen (psdE->szPathU8)			== psdE->lnPathU8);
		ubf_assert (strlen (psdE->szFileNameU8)		== psdE->lnFileNameU8);

		if (psdE->pwfd->dwFileAttributes & psdE->dwExcludeAttrs)
			bContinue = true;
		else
		{
			++ uiEnts;
			bContinue = fedEntCB && bMatch ? fedEntCB (psdE) : true;
		}
		
		if	(
					bContinue
				&&	pnSubLevels
				&&	*pnSubLevels
				&&	psdE->pwfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
			)
		{
			*pnSubLevels -= 1;
			uiEnts = ForEachDirEntryMaskU8intern	(
							psdE->lnFullPathU8, fedEntCB, psdE, pnSubLevels, pCustom
													);
			*pnSubLevels += 1;
		}
	} while (bContinue && FindNextFileW (hFind, psdE->pwfd));

	FindClose (hFind);
	return uiEnts;
}

static void prepareInitialPathBuf (SMEMBUF *pmb, const char *strPath, size_t lnPath)
{
	ubf_assert_non_NULL	(pmb);
	ubf_assert			(isInitialisedSMEMBUF (pmb));
	ubf_assert			(isUsableSMEMBUF (pmb));
	ubf_assert_non_NULL	(strPath);
	ubf_assert_non_0	(lnPath);

	memcpy (pmb->buf.pch, strPath, lnPath);
	pmb->buf.pch [lnPath] = ASCII_NUL;
	str_correct_dir_separators (pmb->buf.pch, lnPath);
	str_remove_path_navigators (pmb->buf.pch, &lnPath);
}

static DWORD obtainExcludeAttrsFromExcludeFlags (uint32_t uiExcludeFlags)
{
	DWORD dwAttrs = 0;

	dwAttrs |= FEDEMDIRENT_NO_DIRECTORY		& uiExcludeFlags ? FILE_ATTRIBUTE_DIRECTORY		: 0;
	dwAttrs |= FEDEMDIRENT_NO_SYSTEM		& uiExcludeFlags ? FILE_ATTRIBUTE_SYSTEM		: 0;
	dwAttrs |= FEDEMDIRENT_NO_READONLY		& uiExcludeFlags ? FILE_ATTRIBUTE_READONLY		: 0;
	dwAttrs |= FEDEMDIRENT_NO_HIDDEN		& uiExcludeFlags ? FILE_ATTRIBUTE_HIDDEN		: 0;
	dwAttrs |= FEDEMDIRENT_NO_TEMPORARY		& uiExcludeFlags ? FILE_ATTRIBUTE_TEMPORARY		: 0;
	dwAttrs |= FEDEMDIRENT_NO_ARCHIVE		& uiExcludeFlags ? FILE_ATTRIBUTE_ARCHIVE		: 0;
	dwAttrs |= FEDEMDIRENT_NO_NORMAL		& uiExcludeFlags ? FILE_ATTRIBUTE_NORMAL		: 0;
	dwAttrs |= FEDEMDIRENT_NO_COMPRESSED	& uiExcludeFlags ? FILE_ATTRIBUTE_COMPRESSED	: 0;
	dwAttrs |= FEDEMDIRENT_NO_LINKS			& uiExcludeFlags ? FILE_ATTRIBUTE_REPARSE_POINT	: 0;
	return dwAttrs;
}

size_t ForEachDirectoryEntryMaskU8	(
				const char				*strFolderU8,
				size_t					lenFolderU8,
				const char				*strMaskU8,
				size_t					lenMaskU8,
				pForEachDirEntryU8		fedEntCB,
				size_t					*pnSubLevels,
				uint32_t				uiExcludeFlags,
				void					*pCustom
									)
{
	ubf_assert_non_NULL	(strFolderU8);
	ubf_assert_non_0	(lenFolderU8);

	size_t	uiEnts		= 0;
	lenFolderU8	= str_remove_last_dir_separator (strFolderU8, lenFolderU8);
	if (lenFolderU8)
	{
		lenMaskU8 = strMaskU8 ? (USE_STRLEN == lenMaskU8 ? strlen (strMaskU8) : lenMaskU8) : 0;

		WIN32_FIND_DATAW		wfdW;
		SRDIRONEENTRYSTRUCT		sdE;
		memset (&sdE, 0, sizeof (SRDIRONEENTRYSTRUCT));
		sdE.UTF8orUTF16.strOrgPathWorU8	= strFolderU8;
		sdE.lnOrgPathU8					= lenFolderU8;
		sdE.u							= EN_READ_DIR_ENTS_SDIRW_UTF8;
		sdE.pwfd						= &wfdW;
		sdE.dwExcludeAttrs				= obtainExcludeAttrsFromExcludeFlags (uiExcludeFlags);
		sdE.pCustom						= pCustom;
		sdE.szMaskU8					= strMaskU8;
		sdE.lnMaskU8					= lenMaskU8;
		INITSMEMBUF (sdE.mbPathBuf);

		size_t stPathBuf		= lenFolderU8
								+ LENOFSTR (UBF_WIN_DIR_SEP_STR) + UTF8_MAX_PATH
								+ 1;							// NUL terminator.

		// If we're allowed to dig into sublevels, allow for at least one more level beforehand.
		if (pnSubLevels && *pnSubLevels)
			stPathBuf			+= LENOFSTR (UBF_WIN_DIR_SEP_STR) + UTF8_MAX_PATH;
		
		// Plus the length of the actual mask ("\*") to use it for FindFirstFile ().
		stPathBuf				+= LENCOVERALLMSK;

		growToSizeSMEMBUF (&sdE.mbPathBuf,		stPathBuf);
		// Windows is going to set the last error here for us.
		if (!isUsableSMEMBUF (&sdE.mbPathBuf))
			return uiEnts;

		prepareInitialPathBuf (&sdE.mbPathBuf,		strFolderU8, lenFolderU8);

		uiEnts = ForEachDirEntryMaskU8intern	(
					lenFolderU8, fedEntCB, &sdE, pnSubLevels, pCustom
												);
		DONESMEMBUF (sdE.mbPathBuf);

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

		char cFilename [4 * UTF8_MAX_PATH];
		UTF8_from_WinU16 (cFilename, UTF8_MAX_PATH, psdE->pwfd->cFileName);
		/*
		puts ("");
		printf ("Org:  %s,\t%s\n", psdE->UTF8orUTF16.chOrgPathU8, cFilename);
		printf ("Full: %s,\t%s\n", psdE->szFullPathU8, cFilename);
		printf ("Path: %s,\t%s\n", psdE->szPathU8, cFilename);
		printf ("File: %s,\t%s\n", psdE->szFileNameU8, cFilename);
		*/
		/*
		puts ("");
		puts (psdE->szFullPathU8);
		puts (psdE->szPathU8);
		puts (psdE->szFileNameU8);
		*/
		++ uiTstGlob;
		/*
		if (uiTstGlob >= 100)
			ubf_assert (false);
		*/
		return true;
	}

	bool ForEachDirectoryEntryMaskU8TestFnct (void)
	{
		bool b = true;

		/*
			Test for ReadDirectoryEntriesSDIRW_WU8_ex ().
		*/
		// ReadDirectoryEntriesSDIRW_WU8_ex () UTF-16.
		DWORD dwNum;
		SDIRW *sd = ReadDirectoryEntriesSDIRW_WU8_ex	(
			L"C:\\temp\\*", EN_READ_DIR_ENTS_SDIRW_UTF16, &dwNum, NULL, NULL, NULL
														);
		DWORD dw = 0;
		SDIRW *sd2 = sd;
		while (sd2)
		{
			b &= 0 != sd2->wfdW.cFileName [0];
			ubf_assert (b);
			++ dw;
			sd2 = sd2->_next;
		}
		ubf_expect_bool_AND (b, NULL == sd2);
		ubf_expect_bool_AND (b, dw == dwNum);
		ReleaseDirectoryEntriesSDIRW (sd);

		// ReadDirectoryEntriesSDIRW_WU8_ex () UTF-8.
		DWORD dw2;
		sd = ReadDirectoryEntriesSDIRW_WU8_ex	(
			"C:\\temp\\*", EN_READ_DIR_ENTS_SDIRW_UTF8, &dw2, NULL, NULL, NULL
												);
		DWORD dw3 = 0;
		sd2 = sd;
		while (sd2)
		{
			b &= 0 != sd2->wfdW.cFileName [0];
			ubf_assert (b);
			++ dw3;
			sd2 = sd2->_next;
		}
		ubf_expect_bool_AND (b, NULL == sd2);
		ubf_expect_bool_AND (b, dw == dwNum);
		ubf_expect_bool_AND (b, dw2 == dw);
		ubf_expect_bool_AND (b, dw2 == dwNum);
		ubf_expect_bool_AND (b, dw3 == dw2);
		ReleaseDirectoryEntriesSDIRW (sd);
		/*
			End of test for ReadDirectoryEntriesSDIRW_WU8_ex ().
		*/

		size_t	ui	= SIZE_MAX;
		size_t	n;

		//puts ("");
		n = ForEachDirectoryEntryMaskU8	(
				"C:\\temp",		USE_STRLEN,
				//"*.txt",		USE_STRLEN,
				"**",			USE_STRLEN,
				perFile, &ui, 0, NULL
										);
		//puts ("Done.");

		uint32_t	uiDontList	=		FEDEMDIRENT_NO_DIRECTORY
									|	FEDEMDIRENT_NO_SYSTEM
									|	FEDEMDIRENT_NO_HIDDEN;

		n = ForEachDirectoryEntryMaskU8	(
				"C:\\temp",		USE_STRLEN,
				//"*.txt",		USE_STRLEN,
				"**",			USE_STRLEN,
				perFile, &ui, uiDontList, NULL
										);
		//puts ("Done.");

		n = ForEachDirectoryEntryMaskU8	(
				"C:\\Windows",		USE_STRLEN,
				//"*.txt",		USE_STRLEN,
				"**",			USE_STRLEN,
				perFile, &ui, uiDontList, NULL
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
