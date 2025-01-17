/****************************************************************************************

	File:		unref.h
	Why:		Some macros for unreferenced parameters/arguments etc.
	OS:			-
	Author:		Thomas
	Created:	2024-09-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-23	Thomas			Created.

****************************************************************************************/

/*
	Include this file _after_ <Windows.h> or when <Windows.h> is not included at all,
	like for instance on POSIX.
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

#ifndef UNREF_H_INCLUDED
#define UNREF_H_INCLUDED

#ifndef CUNILOG_USE_COMBINED_MODULE

	// Unreferenced parameters. These come from winnt.h and other sources.
	#ifndef UNREFERENCED_PARAMETER
	#define UNREFERENCED_PARAMETER(P)			\
		{										\
			(P) = (P);							\
		}
	#endif
	#ifndef UNUSED_PARAMETER
	#define UNUSED_PARAMETER(x) (void)(x)
	#endif
	#ifndef UNUSED_PARAMETER2
	#define UNUSED_PARAMETER2(x,y) UNUSED_PARAMETER(x),UNUSED_PARAMETER(y)
	#endif

	#ifndef UNREFERENCED_LOCAL_VARIABLE
	#define UNREFERENCED_LOCAL_VARIABLE(V)		(V)
	#endif
	#ifndef DBG_UNREFERENCED_PARAMETER
	#define DBG_UNREFERENCED_PARAMETER(P)		(P)
	#endif
	#ifndef DBG_UNREFERENCED_LOCAL_VARIABLE
	#define DBG_UNREFERENCED_LOCAL_VARIABLE(V)	(V)
	#endif

#endif														// Of #ifndef CUNILOG_USE_COMBINED_MODULE.

#ifndef UNUSED
#define UNUSED(var) (void)(var)
#endif

#endif														// Of #ifndef UNREF_H_INCLUDED.
