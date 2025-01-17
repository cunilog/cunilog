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
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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
