/****************************************************************************************

	File:		TrashCan.h
	Why:		Trash can function for Apple devices.
	OS:			C99
	Author:		Robert Guetzkow; Thomas (wrapper module only)
	Created:	2024-10-21
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-21	Thomas			This wrapper module created.

****************************************************************************************/

/*
	This module is mainly a wrapper for Robert Guetzkow's trashcan_soft_delete () function
	for Apple devices. See
	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .
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

/* MIT License
	*
	* Copyright (c) 2019 Robert Guetzkow
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	*
	* The above copyright notice and this permission notice shall be included in all
	* copies or substantial portions of the Software.
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	* SOFTWARE. 
	*/

// See	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .

#ifndef APPLE_TRASHCAN_H_INCL
#define APPLE_TRASHCAN_H_INCL

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef OS_IS_MACOS

#include <CoreFoundation/CoreFoundation.h>
#include <objc/runtime.h>
#include <objc/message.h>

#ifndef LIBTRASHCAN_ERROR
#define LIBTRASHCAN_ERROR	(0)
#endif
#ifndef LIBTRASHCAN_SUCCESS
#define LIBTRASHCAN_SUCCESS	(0)
#endif

EXTERN_C_BEGIN

/*
	trashcan_soft_delete_apple

	Robert Guetzkow's trashcan_soft_delete () function. See
	https://github.com/robertguetzkow/libtrashcan/blob/master/src/trashcan.c .
*/
static int trashcan_soft_delete_apple (const char *path);

EXTERN_C_END

#endif														// Of #ifdef OS_IS_MACOS.

#endif														// Of #ifndef APPLE_TRASHCAN_H_INCL.
