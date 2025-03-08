/****************************************************************************************

	File:		PsxHome.c
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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./PsxHome.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./platform.h"
		#include "./strmembuf.h"
	#else
		#include "./../../dbg/ubfdebug.h"
		#include "./../../pre/platform.h"
		#include "./../../string/strmembuf.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX

#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

static bool	bInitialised;
static SMEMBUF		smbUserName			= SMEMBUF_INITIALISER;
static size_t		lenUserName;
static SMEMBUF		smbUserHome			= SMEMBUF_INITIALISER;
static size_t		lenUserHome;
static SMEMBUF		smbXDG_DATA_HOME	= SMEMBUF_INITIALISER;
static size_t		lenXDG_DATA_HOME;
static bool			bXDG_DATA_HOMEunavailable;
static SMEMBUF		smbUserTrashFolder	= SMEMBUF_INITIALISER;
static size_t		lenUserTrashFolder;

static SMEMBUF		smbUserID			= SMEMBUF_INITIALISER;
static size_t		lenUserID;
static uid_t		uidUserID;

// See
//	https://wiki.archlinux.org/title/XDG_Base_Directory .
bool obtainXDG_DATA_HOME (void)
{
	if (bXDG_DATA_HOMEunavailable)
		return false;
	char *sz = getenv ("XDG_DATA_HOME");
	if (sz)
	{
		lenXDG_DATA_HOME = SMEMBUFfromStr (&smbXDG_DATA_HOME, sz, strlen (sz) + 1);
		if (lenXDG_DATA_HOME) -- lenXDG_DATA_HOME;
		return true;
	}
	bXDG_DATA_HOMEunavailable = true;
	return false;
}

static inline void setTxtUserID (uid_t uid)
{
	if (uid != uidUserID)
	{
		lenUserID = SMEMBUFstrFromUINT64 (&smbUserID, uid);
		if (lenUserID) -- lenUserID;
	}
}

static inline uid_t getOurUserID (void)
{
	uid_t	uid;
	
	// Not sure what should be used here. The real or the effective user id?
	uid = geteuid ();
	//uid = getuid ();
	uidUserID = uid;
	
	setTxtUserID (uid);
	return uid;
}

bool obtainCurrentUserNamePOSIX (void)
{
	uid_t uid = getOurUserID ();
	const struct passwd *pw = getpwuid (uid);
	if (pw)
	{
		lenUserName = SMEMBUFfromStr (&smbUserName, pw->pw_name, strlen (pw->pw_name) + 1);
		if (lenUserName) -- lenUserName;
		return true;
	}
	
	ubf_assert_msg (false, "obtainCurrentUserNamePOSIX () failed.");
	return false;
}

static inline const char *ccCurrentUserName (void)
{
	if (NULL == smbUserName.buf.pcc)
		obtainCurrentUserNamePOSIX ();
    return smbUserName.buf.pcc;    
}

bool InitPsxHome (void)
{
	bool bRet;
	
	obtainXDG_DATA_HOME ();
	bRet = obtainCurrentUserNamePOSIX ();
	
	return bRet;
}

// See https://www.man7.org/linux/man-pages/man3/getpwnam.3.html .
const char *UserHomeDirectoryPOSIX (size_t *plen)
{
	if (!bInitialised)
	{
		struct passwd pw;
		struct passwd *ppw;
		
		const char *szMe = ccCurrentUserName ();
		if (szMe)
		{
			size_t siz = sysconf (_SC_GETPW_R_SIZE_MAX);
			if ((size_t) - 1 == siz)						// Max. size could not be determined.
				siz = 16384;								// Should be sufficient enough.
			char *pwdbuf = malloc (siz);
			if (pwdbuf)
			{
				getpwnam_r (szMe, &pw, pwdbuf, siz, &ppw);
				if (ppw)
				{	
					lenUserHome = SMEMBUFfromStr	(
						&smbUserHome, ppw->pw_dir, strlen (ppw->pw_dir) + 1
													);
					if (lenUserHome) -- lenUserHome;
				}
				free (pwdbuf);
			}
		}
	}
	if (plen)
		*plen = lenUserHome;
	return smbUserHome.buf.pcc;
}

static const char	ccTrash		[]	= "Trash";
static const char	ccHTrash	[]	= ".local/share/Trash";

static void buildXDG_DATA_HomeTrashName (void)
{
	// $HOME/.local/share + / + Trash + NUL
	growToSizeSMEMBUF (&smbUserTrashFolder, lenXDG_DATA_HOME + sizeof (ccTrash) + 1);
	if (isUsableSMEMBUF (&smbUserTrashFolder))
	{
		memcpy (smbUserTrashFolder.buf.pch, smbXDG_DATA_HOME.buf.pch, lenXDG_DATA_HOME);
		smbUserTrashFolder.buf.pch [lenXDG_DATA_HOME] = '/';
		memcpy (smbUserTrashFolder.buf.pch + lenXDG_DATA_HOME + 1, ccTrash, sizeof (ccTrash));
		lenUserTrashFolder = lenXDG_DATA_HOME + sizeof (ccTrash);
	}
}

static void buildUserHomeTrashName (void)
{
	if (NULL == smbUserHome.buf.pcc)
		UserHomeDirectoryPOSIX (NULL);
	if (smbUserHome.buf.pcc)
	{
		growToSizeSMEMBUF (&smbUserTrashFolder, lenUserHome + sizeof (ccHTrash) + 1);
		if (isUsableSMEMBUF (&smbUserTrashFolder))
		{
			memcpy (smbUserTrashFolder.buf.pch, smbUserHome.buf.pch, lenUserHome);
			smbUserTrashFolder.buf.pch [lenUserHome] = '/';
			memcpy (smbUserTrashFolder.buf.pch + lenUserHome + 1, ccHTrash, sizeof (ccHTrash));
			lenUserTrashFolder = lenUserHome + sizeof (ccHTrash);
		}
	}
}

const char *UserTrashFolder (size_t *plen)
{
	if (NULL == smbUserTrashFolder.buf.pcc)
	{
		if (obtainXDG_DATA_HOME ())
			buildXDG_DATA_HomeTrashName ();
		else
			buildUserHomeTrashName ();
	}
	if (plen)
		*plen = lenUserTrashFolder;
	return smbUserTrashFolder.buf.pcc;
}

#endif														// Of #ifdef PLATFORM_IS_POSIX.

#ifdef PLATFORM_IS_POSIX
	#ifdef PSXHOME_BUILD_TEST_FNCT
		bool TestPsxHome (void)
		{
			bool	b = false;
			
			b = obtainXDG_DATA_HOME ();
			size_t st;
			const char *szTrash = UserTrashFolder (&st);
			b = NULL != szTrash;
			return b;
		}
	#endif
#endif
