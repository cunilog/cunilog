/****************************************************************************************

	File:		SharedMutex.c
	Why:		Implements a mutex for interprocess-locking.
	OS:			C99
	Author:		Thomas
	Created:	2021-02-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-02-23	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
MIT License

Copyright (c) 2018 Oleg Yamnikov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./SharedMutex.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
	#else
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

shared_mutex_t InitSharedMutex (const char *name)
{
	char	cName [1024];
	char	namebuf [512];
	
	ubf_assert (NULL != name);
	ubf_assert (0 < name [0]);
	ubf_assert ('\\' != name [0]);
	ubf_assert ('/' != name [0]);

	memcpy (namebuf, name, strlen (name) < 512 ? strlen (name) + 1 : 511);
	namebuf [511] = '\0';

	#if defined (PLATFORM_IS_WINDOWS)

		ubf_assert (512 > strlen (name));
		memcpy (cName, UBF_WIN_SHARED_MUTEX_GLOBAL_PFX, LENOFSTR (UBF_WIN_SHARED_MUTEX_GLOBAL_PFX));
		memcpy (cName + LENOFSTR (UBF_WIN_SHARED_MUTEX_GLOBAL_PFX), namebuf, strlen (namebuf) + 1);
		return WinInitSharedMutex (cName);

	#elif defined (PLATFORM_IS_POSIX)

		cName [0] = '/';
		memcpy (cName + 1, namebuf, strlen (namebuf) + 1);
		return PsxInitSharedMutex (cName, S_IRUSR | S_IWUSR);

	#elif
		#error Not supported
	#endif
}

int CloseSharedMutex (shared_mutex_t mutex)
{
	#ifdef PLATFORM_IS_POSIX
		return PsxCloseSharedMutex (mutex);
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		return WinCloseSharedMutex (mutex);
	#endif
}

int DestroySharedMutex (shared_mutex_t mutex)
{
	#ifdef PLATFORM_IS_POSIX
		return PsxDestroySharedMutex (mutex);
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		return WinDestroySharedMutex (mutex);
	#endif
}

int EnterSharedMutex (shared_mutex_t mutex)
{
	#ifdef PLATFORM_IS_POSIX
		return pthread_mutex_lock (mutex.ptr);
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		DWORD dw;
		dw = WaitForSingleObject (mutex, INFINITE);
		return WAIT_OBJECT_0 == dw ? 0 : 1;
	#endif
}

int LeaveSharedMutex (shared_mutex_t mutex)
{
	#ifdef UBF_LINUX
		return pthread_mutex_unlock (mutex.ptr);
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		return ReleaseMutex (mutex) ? 0 : 1;
	#endif
}
