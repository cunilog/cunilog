/****************************************************************************************

	File:		WinSharedMutex.c
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

#ifdef _WIN32

#ifndef CUNILOG_USE_COMBINED_MODULE
	#include "./WinSharedMutex.h"
#endif

shared_mutex_t WinInitSharedMutex(const char *name)
{
	shared_mutex_t s = malloc (sizeof (struct ssharedmutext));
	if (s)
	{
		s->h = CreateMutexU8 (NULL, FALSE, name);
		if (s->h)
		{
			DWORD dwErr = GetLastError ();
			s->bCreatedHere = ERROR_ALREADY_EXISTS != dwErr;
		} else
			goto fail;
	}
	return s;

fail:
	free (s);
	return NULL;
}

int WinCloseSharedMutex(shared_mutex_t mutex)
{
	return CloseHandle (mutex->h) ? 0 : 1;
}

void WinDestroySharedMutex(shared_mutex_t mutex)
{	// In Windows, the mutex is destroyed automatically when the last open
	//	handle to it is closed. Refer to
	//	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw
	//	for clarification.
	if (mutex->h)
		CloseHandle (mutex->h);
	free (mutex);
}

#endif															// Of #ifdef _WIN32
