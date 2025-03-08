/****************************************************************************************

	Project:	cunilog
	File:		cunilogversion.h
	Why:		
	OS:			
	Autor:		Thomas
	Created:	2024-10-16
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-16	Thomas			Created.

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

#ifndef HAVE_CUNILOG_VERSION__H
#define HAVE_CUNILOG_VERSION__H

// Some constants.
#define CUNILOG_PROJECT_NAME	"cunilog"					// Name of the project.
#define CUNILOG_PROGRAM_NAME	"cunilog"					// The application's name.
#define CUNILOG_PROGRAM_EXE		CUNILOG_PROGRAM_NAME ".exe"
#define CUNILOG_PROGRAM_DESCR	"Logging utility"			// Its description.
#define CUNILOG_PROGRAM_COMPANY "-"							// Company.
#define CUNILOG_PROGRAM_AUTHOR	"Thomas"					// Author.
#define CUNILOG_PROGRAM_EMAIL	"-"							// Email.

// Version numbers.
#define CUNILOG_VERSION_MAJOR	1							// Major version.
#define CUNILOG_VERSION_MINOR	0							// Minor version.
#define CUNILOG_VERSION_SUB		2							// Subversion for maintenance.
#define CUNILOG_VERSION_BUILD	9							// Build number.
#define CUNILOG_VERSION_YEAR	"2025"						// Copyright year.

// Convert constants to strings using ANSI stringify operator.
#define STRINGIFY(x) #x

// Convert constants to strings while expanding macros.
//	This is actually a helper define to force macro expansion.
#define EXPANDSTRINGIFY(x) STRINGIFY(x)

// Version string for display on startup.
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR)
#if (CUNILOG_VERSION_SUB != 0)
#undef CUNILOG_VERSION_STRING
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) "." EXPANDSTRINGIFY(CUNILOG_VERSION_SUB)
#endif
#if (CUNILOG_VERSION_BUILD != 0)
#undef CUNILOG_VERSION_STRING
#define CUNILOG_VERSION_STRING		EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) "." \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) "." EXPANDSTRINGIFY(CUNILOG_VERSION_SUB) \
	"." EXPANDSTRINGIFY(CUNILOG_VERSION_BUILD)
#endif
// Version string for executable version information.
#define CUNILOG_VERSION_RESOURCE	EXPANDSTRINGIFY(CUNILOG_VERSION_MAJOR) ", " \
	EXPANDSTRINGIFY(CUNILOG_VERSION_MINOR) ", " EXPANDSTRINGIFY(CUNILOG_VERSION_SUB) \
	", " EXPANDSTRINGIFY(CUNILOG_VERSION_BUILD)

// Copyright notice in executable version information.
#define CUNILOG_VERSION_COPYRIGHT	"Copyright (C) " CUNILOG_VERSION_YEAR \
	", " CUNILOG_PROGRAM_AUTHOR

#endif															// Of #ifndef HAVE_CUNILOG_VERSION__H.
