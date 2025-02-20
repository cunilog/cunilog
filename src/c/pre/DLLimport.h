/****************************************************************************************

	File		DLLimport.h
	Why:		The definition for DLL imports for Windows
	OS:			Windows
	Created:	2025-02-20

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-20	Thomas			Created.

****************************************************************************************/

#ifndef U_DLL_IMPORT_H
#define U_DLL_IMPORT_H

#if defined (_WIN32) && defined (CUNILOG_IMPORT_FROM_DLL)
	#define CUNILOG_DLL_IMPORT		__declspec(dllimport)
#else
	#define CUNILOG_DLL_IMPORT
#endif

#endif														// Of #ifndef U_DLL_IMPORT_H.
