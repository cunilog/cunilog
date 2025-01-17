/****************************************************************************************

	File		TestCombinedSource.h
	Why:		To test the combined source and header files.
	OS:			-
	Created:	2024-07-19

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-10	Thomas			Created.

****************************************************************************************/

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
