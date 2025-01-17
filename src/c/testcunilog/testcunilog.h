/****************************************************************************************

	File:		testcunilog.h
	Why:		Test application for cunilog.
	OS:			C99.
	Author:		Thomas
	Created:	2024-07-09

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-07-09	Thomas			Created.

****************************************************************************************/

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

#define LOGS_FOLDER_NAME				"logs"

/*
	Our logs folder is located directly in the project folder.
	Depending on the executable version built and run we may have to climb up from
	this executable folder.

	For instance, the executable for the 64 bit MSVC debug version is generated at
	cunilog\builds\msvc2019\testcunilog\x64\Debug, the logs folder is at
	cunilog\logs . The climber therefore needs to go up 5 levels to reach the logs
	folder.
*/

#if defined (_WIN32) && defined (_WIN64)
	// 64 bit MSVC version.
	#ifndef STR_LOGS_FOLDER
	#define STR_LOGS_FOLDER				"..\\..\\..\\..\\..\\"			LOGS_FOLDER_NAME
	#endif
	#ifndef STR_HELLO_FROM_EXE
	#define STR_HELLO_FROM_EXE			"Hello from a 64 bit MSVC build!"
	#endif
#endif

#if defined (_WIN32) && !defined (_WIN64)
	// 32 bit MSVC version.
	#ifndef STR_LOGS_FOLDER
	#define STR_LOGS_FOLDER				"..\\..\\..\\..\\"				LOGS_FOLDER_NAME
	#endif
	#ifndef STR_HELLO_FROM_EXE
	#define STR_HELLO_FROM_EXE			"Hello from a 32 bit MSVC build!"
	#endif
#endif

#if !defined (_WIN32)
	#ifndef STR_LOGS_FOLDER
	#define STR_LOGS_FOLDER				"..\\..\\..\\..\\"				LOGS_FOLDER_NAME
	#endif
	#ifndef STR_HELLO_FROM_EXE
	#define STR_HELLO_FROM_EXE			"Hello from a non-MSVC build!"
	#endif
#endif
