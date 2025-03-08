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

#ifndef CUNILOG_USE_COMBINED_MODULE
	#include "./WinSharedMutex.h"
#endif

#ifdef PLATFORM_IS_WINDOWS

shared_mutex_t WinInitSharedMutex(const char *name)
{
	HANDLE	hMut;
	hMut = CreateMutexU8 (NULL, FALSE, name);
	ASSERT (NULL != hMut);
	return hMut;
}

int WinCloseSharedMutex(shared_mutex_t mutex)
{
	return CloseHandle (mutex) ? 0 : 1;
}

int WinDestroySharedMutex(shared_mutex_t mutex)
{	// In Windows, the mutex is destroyed automatically when the last open
	//	handle to it is closed. Refer to
	//	https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw
	//	for clarification.
	UNREFERENCED_PARAMETER (mutex);
	return 0;
}

#endif															// Of #ifdef UBF_WINDOWS.
