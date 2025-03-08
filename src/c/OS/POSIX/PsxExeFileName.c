/****************************************************************************************

	File:		PsxExeFileName.c
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

#include <malloc.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./PsxExeFileName.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./membuf.h"
		#include "./memstrstr.h"
		#include "./ubfdebug.h"
		#include "./strintuint.h"
		#include "./unref.h"
	#else
		#include "./../../mem/membuf.h"
		#include "./../../mem/memstrstr.h"
		#include "./../../dbg/ubfdebug.h"
		#include "./../../string/strintuint.h"
		#include "./../../pre/unref.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX

#include <unistd.h>

SMEMBUF	mbOurExecutablePath		= SMEMBUF_INITIALISER;
size_t	lenOurExectuablePath;

/*
	Stores our executable's module name and its length in the variables above.
*/
static void StoreExecutableModuleName (SMEMBUF *mb, size_t ln)
{
	ubf_assert_non_NULL (mb);
	ubf_assert (isInitialisedSMEMBUF (mb));
	ubf_assert_non_0 (ln);
	ubf_assert (USE_STRLEN != ln);

	if (!isUsableSMEMBUF (&mbOurExecutablePath))
	{
		copySMEMBUF (&mbOurExecutablePath, mb);
		lenOurExectuablePath = ln;

		// Ensure we have a NUL terminator.
		ubf_assert (0 == mbOurExecutablePath.buf.pch [ln]);
		ubf_assert (strlen (mbOurExecutablePath.buf.pch) == ln);
	}
}

/*
	If we already obtained our own executable's module name, the function resizes
	the buffer of mb to the size of mbOurExecutablePath and copies it in, basically
	returning a copy of our executable's module name.

	The function returns the length of the previously obtained module name, or 0
	if none has been obtained yet.
*/
static size_t WeHaveExecutableModuleNameAlready (SMEMBUF *mb)
{
	ubf_assert_non_NULL (mb);
	ubf_assert (isInitialisedSMEMBUF (mb));

	if (isUsableSMEMBUF (&mbOurExecutablePath))
	{
		copySMEMBUF (mb, &mbOurExecutablePath);
		// Note that we do not check here if the copy operation was successful.
		//	We leave this within the caller's responsibility.
		return lenOurExectuablePath;
	}
	return 0;
}

static unsigned int		uiDetExeMethod;							// The strategy used to
																//	determine the executable's
																//	path/folder.

#ifdef OS_IS_MACOS
	/*
		Apple devices. See
		https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html .
	*/
	#include <mach-o/dyld.h>

	size_t PsxObtainExecutableModuleName (SMEMBUF *mb)
	{
		ubf_assert_non_NULL (mb);

		size_t len;												// The return value.
		if (len = WeHaveExecutableModuleNameAlready (mb))
			return len;

		chPath = ubf_malloc (exe_size);
		while (chPath && -1 == _NSGetExecutablePath (chPath, &exe_size))
		{
			ubf_free (chPath);
			exe_size += 256;
			#ifdef DEBUG
			if (8192 <= exe_size)
			{	// Emergency brake in debug version. In the release version we got no
				//	choice but to use however long the path is.
				ubf_assert (FALSE);
			}
			#endif
			chPath = ubf_malloc (exe_size);
			ubf_assert (NULL != chPath);
		}
		if (chPath)
		{
			ch_ubf_Executable_Path = chPath;
			ln_ubf_Executable_Path = (size_t) exe_size - 1;
			return ch_ubf_Executable_Path;
		}
		return NULL;
	}
#else
	/*
		Other Unixes. See
		https://stackoverflow.com/questions/24581908/c-lstat-on-proc-pid-exe .
	*/
	static size_t pid_as_string (char *szPID)
	{
		int pid = getpid ();
		ubf_assert (0 < pid);								// Negative PIDs relate to a group.
		if (pid > 0)
		{	// We only expect a normal PID.
			uint64_t ui = pid;
			return ubf_str_from_uint64 (szPID, ui);
		}
		return 0;
	}

	/*
		Check if these links exist on various operating systems anduse the one
		that does exist. The first one's Linux.
	*/
	const char szProc	[] = "/proc/";
	const char szExe	[] = "/exe";

	size_t PsxObtainExecutableModuleName (SMEMBUF *mb)
	{
		ubf_assert_non_NULL (mb);

		size_t len;
		if ((len = WeHaveExecutableModuleNameAlready (mb)))
			return len;

		char			cPath [1024];
		size_t			exe_size = 1024;
		size_t			exe_used;

		char szCheckLnk [32 + UBF_UINT64_SIZE];
		char *sz = szCheckLnk;
		uiDetExeMethod = 1;

		// "/proc/<pid>/exe"
		memcpy (sz, szProc, sizeof (szProc) - 1);
		sz += pid_as_string (sz + sizeof (szProc) - 1);
		memcpy (sz, szExe, sizeof (szExe) - 1);
		sz [sizeof (szExe) - 1] = '\0';

		exe_used = readlink (szCheckLnk, cPath, exe_size - 1);
		if ((size_t) -1 == exe_used)
		{	// FreeBSD.
			++ uiDetExeMethod;
			exe_used = readlink ("/proc/curproc/file", cPath, exe_size - 1);
			if ((size_t) -1 == exe_used)
			{	// Solaris.
				++ uiDetExeMethod;
				exe_used = readlink ("/proc/self/path/a.out", cPath, exe_size - 1);
				if ((size_t) -1 == exe_used)
				{	// Linux again.
					++ uiDetExeMethod;
					exe_used = readlink ("/proc/self/exe", cPath, exe_size - 1);
					if ((size_t) -1 == exe_used)
					{	// What else can we try?
						++ uiDetExeMethod;
						ubf_assert (false);
						ASSERT (false);
						return 0;
					}
				}
			}
		}
		if (exe_used == exe_size)
		{	// Buffer is too small.
			ubf_assert (false);
			return 0;
		}
		if (growToSizeSMEMBUF (mb, exe_used + 1))
		{
			memcpy (mb->buf.pch, cPath, exe_used);
			mb->buf.pch [exe_used] = '\0';
			StoreExecutableModuleName (mb, exe_used);
		}
		return exe_used;
	}
#endif

size_t PsxObtainAppNameFromExecutableModule (SMEMBUF *mb)
{
	ubf_assert_non_NULL (mb);

	size_t	l;

	if ((l = PsxObtainExecutableModuleName (mb)))
	{
		// This only works on POSIX.		
		char *sl = memstrrchr (mb->buf.pch, strlen (mb->buf.pch), '/');
		if (sl)
		{
			char	*sn = sl + 1;
			size_t	len = mb->buf.pch + l - sn;
			memmove (mb->buf.pch, sn, len + 1);
			return len;
		}
		// No forward slash. Not sure if this needs a different implementation.
		ubf_assert (false);
	}
	return 0;
}

size_t PsxObtainPathFromExecutableModule (SMEMBUF *mb)
{
	ubf_assert_non_NULL (mb);

	if (PsxObtainExecutableModuleName (mb))
	{
		size_t	l = strlen (mb->buf.pch);
		UNREFERENCED_PARAMETER (l);
		
		char *sl = memstrrchr (mb->buf.pch, strlen (mb->buf.pch), '/');
		if (sl)
		{
			++ sl;
			*sl = '\0';
			return sl - mb->buf.pch;
		}
		// No forward slash. Not sure if this needs a different implementation.
		ubf_assert (false);
	}
	return 0;
}

#endif													// Of #ifdef OS_IS_POSIX.
