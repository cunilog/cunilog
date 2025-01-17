/****************************************************************************************

	File:		PsxReadDirFncts.c
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

#include <malloc.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./PsxReadDirFncts.h"
	#include "./../../pre/unref.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./membuf.h"
		#include "./ubfdebug.h"
		#include "./strintuint.h"
	#else
		#include "./../../mem/membuf.h"
		#include "./../../dbg/ubfdebug.h"
		#include "./../../string/strintuint.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

uint64_t ForEachPsxDirEntry	(
				const char				*strFolderName,
				pForEachPsxDirEntry		fedEnt,
				void					*pCustom,
				unsigned int			*pnSubLevels
							)
{
	uint64_t			uiEnts				= 0;			// The return value.
	DIR					*dir;
	struct dirent		*dent;
	unsigned char		tpy;
	SONEDIRENT			pod;

	UNUSED (pnSubLevels);

	pod.pCustom = pCustom;

	dir = opendir (strFolderName);
	if (dir)
	{
		while (NULL != (dent = readdir (dir)))
		{
			tpy = dent->d_type;
			if (DT_DIR == tpy)
			{	// Recursion is currently not supported because Cunilog doesn't
				//	require it.
			} else
			if (DT_REG == tpy)
			{	// Regular file.
				++ uiEnts;
				pod.dirEnt = dent;
				if (!fedEnt (&pod))
					break;
			} else
			if (DT_UNKNOWN == tpy)
			{	// See https://man7.org/linux/man-pages/man3/readdir.3.html .
				/*
					Excerpt:
					Currently, only some filesystems (among them: Btrfs, ext2,
					ext3, and ext4) have full support for returning the file
					type in d_type.  All applications must properly handle a
					return of DT_UNKNOWN.
				*/

				/*
				if (!isDotOrDotDotW (dent->d_name))
				{
					
				}
				*/
			}
		}
		closedir (dir);
	} else
	{	// Fail. See https://man7.org/linux/man-pages/man3/opendir.3.html .
		/*
			   EACCES	Permission denied.
			   EBADF	fd is not a valid file descriptor opened for reading.
			   EMFILE	The per-process limit on the number of open file
						descriptors has been reached.
			   ENFILE	The system-wide limit on the total number of open files
						has been reached.
			   ENOENT	Directory does not exist, or name is an empty string.
			   ENOMEM	Insufficient memory to complete the operation.
			   ENOTDIR	name is not a directory.
		*/
	}
	return uiEnts;
}



#endif													// Of #ifdef OS_IS_POSIX.
