/****************************************************************************************

	File:		PsxTrash.c
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./PsxTrash.h"
	#include "./PsxHome.h"
	
	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./ubfdebug.h"
		#include "./platform.h"
		#include "./strmembuf.h"
		#include "./ubf_date_and_time.h"

	#else

		#include "./../../dbg/ubfdebug.h"
		#include "./../../pre/platform.h"
		#include "./../../string/strmembuf.h"
		#include "./../../datetime/ubf_date_and_time.h"

	#endif

#endif

#ifdef OS_IS_LINUX

#include <string.h>
#include <errno.h>

// The filename extension of files in the "info" folder.
const char szDotTrashInfo	[]	= ".trashinfo";
// The info that goes in the file in the "info" folder with filename extension ".trashinfo".
const char szTrashInfo		[]	= "[Trash Info]";
const char szPath			[]	= "Path=";
const char szDelDate		[]	= "DeletionDate=";

static SMEMBUF smbTrashInfo			= SMEMBUF_INITIALISER;	// The ".trashinfo" file in "info".
static SMEMBUF smbTrashInfoFilename	= SMEMBUF_INITIALISER;	// Its filename.

static inline bool createTrashInfo (const char *szFilename, size_t lnFilename)
{
	size_t len =		sizeof (szTrashInfo)				// "[Trash Info]" + LF
					+	sizeof (szPath) + lnFilename		// "Path=" + szFilename + LF.
					+	sizeof (szDelDate) + LEN_ISO8601DATETIMESTAMP_NO_OFFS;
					
	return false;
}

/*
	There's two cases:
	
	1.	Per user:		~/.local/share/Trash/files
						Create manually if it doesn't exist.

	2.	Per volume:		/media/<username>/<volume_name>/.Trash/
						For instance	/media/thomas/sda1/.Trash/files/
										/media/thomas/sda1/.Trash/info/ (for metadata)
										
	
*/
bool MoveFileToTrashPOSIX (const char *szFilename)
{
	ubf_assert_non_NULL (szFilename);
	
	size_t		lnHome;
	const char *szHome = UserHomeDirectoryPOSIX (&lnHome);
	if (lnHome)
	{
		ubf_assert_non_NULL (szHome);
		
		size_t lnFilename = strlen (szFilename);
		if (createTrashInfo (szFilename, lnFilename))
		{

		}
		return false;
	}
	errno = ENOSYS;											// Function not implemented.
	return false;
}

#endif														// Of #ifdef OS_IS_LINUX.
