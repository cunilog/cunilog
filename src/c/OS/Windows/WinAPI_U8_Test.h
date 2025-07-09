/****************************************************************************************

	File		WinAPI_U8_Test.h
	Why:		Test module for WinAPI_U8.
	OS:			Windows
	Author:		Thomas
	Created:	2021-04-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-04-17	Thomas			Created.

****************************************************************************************/

#ifndef WINAPI_U8_TEST_H
#define WINAPI_U8_TEST_H

#ifdef _WIN32
	#ifndef CUNILOG_USE_COMBINED_MODULE

		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./WinAPI_U8.h"
		#else
			#include "./WinAPI_U8.h"
		#endif

	#endif
#endif

#ifdef _WIN32

EXTERN_C_BEGIN

/*
	Test_WinAPI_U8
	
	Test function for the WinAPI_U8 module.
*/
#ifdef BUILD_TEST_WINAPI_U8_FNCT
	bool Test_WinAPI_U8 (void);
#else
	#define Test_WinAPI_U8()	(true)
#endif

EXTERN_C_END

#endif														// Of #ifdef _WIN32.

#endif														// Of #ifndef WINAPI_U8_TEST_H.
