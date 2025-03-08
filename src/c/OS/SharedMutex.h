/****************************************************************************************

	File:		SharedMutex.h
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

#ifndef UBF_SHARED_MUTEX_H
#define UBF_SHARED_MUTEX_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdbool.h>
	#include <inttypes.h>

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ArrayMacros.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/ArrayMacros.h"
		#include "./../pre/platform.h"
	#endif

	#if defined (PLATFORM_IS_POSIX) && defined (PLATFORM_IS_WINDOWS)
		#error Only one platform can be defined
	#endif
	#ifdef PLATFORM_IS_POSIX
		#include "./POSIX/PsxSharedMutex.h"
	#endif
	#ifdef PLATFORM_IS_WINDOWS
		#include "./Windows/WinSharedMutex.h"
	#endif

#endif

/*
	The prefix to make a kernel object global on Windows.
*/
#define UBF_WIN_SHARED_MUTEX_GLOBAL_PFX		"Global\\"

EXTERN_C_BEGIN

// Initialize a new shared mutex with given `name`. If a mutex
// with such name exists in the system, it will be loaded.
// Otherwise a new mutes will by created.
//
// In case of any error, it will be printed into the standard output
// and the returned structure will have `ptr` equal `NULL`.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** In case when the mutex appears to be uncreated,
// this function becomes *non-thread-safe*. If multiple threads
// call it at one moment, there occur several race conditions,
// in which one call might recreate another's shared memory
// object or rewrite another's pthread mutex in the shared memory.
// There is no workaround currently, except to run first
// initialization only before multi-threaded or multi-process
// functionality.
/*
	2021-02-24, Thomas
	
	The parameter name must not contain any forward or backward slashes.
	In Linux, the name is automatically prepended a forward slash.
	In Windows, the name is automatically prepended a global namespace
	identifier ("Global\"). See
	https://docs.microsoft.com/en-us/windows/win32/termserv/kernel-object-namespaces
	for information.
*/
shared_mutex_t InitSharedMutex (const char *name);

// Close access to the shared mutex and free all the resources,
// used by the structure.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not destroy the mutex. The mutex would not
// only be available to other processes using it right now,
// but also to any process which might want to use it later on.
// For complete desctruction use `shared_mutex_destroy` instead.
//
// **NOTE:** It will not unlock locked mutex.
int CloseSharedMutex (shared_mutex_t mutex);

// Close and destroy shared mutex.
// Any open pointers to it will be invalidated.
//
// Returns 0 in case of success. If any error occurs, it will be
// printed into the standard output and the function will return -1.
// `errno` wil not be reset in such case, so you may used it.
//
// **NOTE:** It will not unlock locked mutex.
int DestroySharedMutex(shared_mutex_t mutex);

/*
	EnterSharedMutex
	LeaveSharedMutex
*/
int EnterSharedMutex (shared_mutex_t mutex);
int LeaveSharedMutex (shared_mutex_t mutex);

EXTERN_C_END

#endif															// Of #ifndef SHAREDMUTEX_H.
