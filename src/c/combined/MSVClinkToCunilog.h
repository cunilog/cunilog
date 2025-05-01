/****************************************************************************************

	File:		MSVClinkToCunilog.h
	Why:		Links to the Cunilog library dynamically or statically, depending
				on the MSVC project settings and if CUNILOG_IMPORT_FROM_DLL is
				defined or not.
	OS:			Windows, Microsoft Visual Studio (MSVC)
	Author:		Thomas
	Created:	2025-04-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-04-23	Thomas			Created.

****************************************************************************************/

/*
	This header file causes MSVC to link to the correct version of the Cunilog dynamic
	or static library.
	
	If CUNILOG_IMPORT_FROM_DLL is defined, an import library is linked to and Cunilog
	is required as a DLL at runtime.
*/

/*
	License: Public domain.
*/

#ifndef HAVE_WINLINKTOCUNILOG_H
#define HAVE_WINLINKTOCUNILOG_H

#ifdef _MSC_VER


/*
	Link to the correct version of libcunilog.

	See
	https://learn.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-170
	and
	https://learn.microsoft.com/en-us/cpp/preprocessor/comment-c-cpp?view=msvc-170 .

	The following code assumes that the project repository and the cunilog repository rest
	side-by-side in the same root folder and that the cunilog folder structure hasn't been
	changed from the default.
*/

#if defined (_MSC_VER) && defined (_WIN32)

	// Climbs all the way up to our project's root. The compiler/linker starts in our project
	//	folder, which is the folder that hosts the MSVC project file (.vcxproj).
	#ifndef LIBCUNILOG_BASEPATH
	#define LIBCUNILOG_BASEPATH "./../../../../"
	#endif
	// Climbs up one folder to above our project's root and then down to our cunilog solution.
	//	Assumes that cunilog is in a sister directory.
	#ifndef LIBCUNILOG_PROJPATH
	#define LIBCUNILOG_PROJPATH "../cunilog/msproj/msvc2019/libcunilog/"
	#endif

	#ifdef CUNILOG_IMPORT_FROM_DLL

		// Load-time shared library (DLL). Uses an import library.
		#if defined (_M_X64)
			// 64 bit
			#ifndef LIBCUNILOG_X64PATH
			#define LIBCUNILOG_X64PATH "x64/"
			#endif
			#ifndef LIBCUNILOG_PATH
			#define LIBCUNILOG_PATH LIBCUNILOG_BASEPATH LIBCUNILOG_PROJPATH LIBCUNILOG_X64PATH
			#endif
			#if defined (_MT) && defined (_DLL) && !defined (_DEBUG)
				// MD
				#pragma comment (lib, LIBCUNILOG_PATH "ReleaseDLL/libcunilog.lib")
			#elif defined (_MT) && defined (_DLL) && defined (_DEBUG)
				// MDd
				#pragma comment (lib, LIBCUNILOG_PATH "DebugDLL/libcunilog.lib")
			#elif defined (_MT) && !defined (_DLL) && !defined (_DEBUG)
				// MT
				#pragma comment (lib, LIBCUNILOG_PATH "ReleaseDLLMT/libcunilog.lib")
			#elif defined (_MT) && !defined (_DLL) && defined (_DEBUG)
				// MTd
				#pragma comment (lib, LIBCUNILOG_PATH "DebugDLLMT/libcunilog.lib")
			#endif
		#else
			// 32 bit
			#ifndef LIBCUNILOG_X32PATH
			#define LIBCUNILOG_X32PATH ""
			#endif
			#ifndef LIBCUNILOG_PATH
			#define LIBCUNILOG_PATH LIBCUNILOG_BASEPATH LIBCUNILOG_PROJPATH LIBCUNILOG_X32PATH
			#endif
			#if defined (_MT) && defined (_DLL) && !defined (_DEBUG)
				// MD
				#pragma comment (lib, LIBCUNILOG_PATH "ReleaseDLL/libcunilog.lib")
			#elif defined (_MT) && defined (_DLL) && defined (_DEBUG)
				// MDd
				#pragma comment (lib, LIBCUNILOG_PATH "DebugDLL/libcunilog.lib")
			#elif defined (_MT) && !defined (_DLL) && !defined (_DEBUG)
				// MT
				#pragma comment (lib, LIBCUNILOG_PATH "ReleaseDLLMT/libcunilog.lib")
			#elif defined (_MT) && !defined (_DLL) && defined (_DEBUG)
				// MTd
				#pragma comment (lib, LIBCUNILOG_PATH "DebugDLLMT/libcunilog.lib")
			#endif
		#endif

	#else

		// Static import library.
		#if defined (_M_X64)
			// 64 bit
			#ifndef LIBCUNILOG_X64PATH
			#define LIBCUNILOG_X64PATH "x64/"
			#endif
			#ifndef LIBCUNILOG_PATH
			#define LIBCUNILOG_PATH LIBCUNILOG_BASEPATH LIBCUNILOG_PROJPATH LIBCUNILOG_X64PATH
			#endif
			#if defined (_MT) && defined (_DLL) && !defined (_DEBUG)
				// MD
				#pragma comment (lib, LIBCUNILOG_PATH "Release/libcunilog.lib")
			#elif defined (_MT) && defined (_DLL) && defined (_DEBUG)
				// MDd
				#pragma comment (lib, LIBCUNILOG_PATH "Debug/libcunilog.lib")
			#elif defined (_MT) && !defined (_DLL) && !defined (_DEBUG)
				// MT
				#pragma comment (lib, LIBCUNILOG_PATH "ReleaseMT/libcunilogMT.lib")
			#elif defined (_MT) && !defined (_DLL) && defined (_DEBUG)
				// MTd
				#pragma comment (lib, LIBCUNILOG_PATH "DebugMT/libcunilogMT.lib")
			#endif
		#else
			// 32 bit
			#ifndef LIBCUNILOG_X32PATH
			#define LIBCUNILOG_X32PATH ""
			#endif
			#ifndef LIBCUNILOG_PATH
			#define LIBCUNILOG_PATH LIBCUNILOG_BASEPATH LIBCUNILOG_PROJPATH LIBCUNILOG_X32PATH
			#endif
			#if defined (_MT) && defined (_DLL) && !defined (_DEBUG)
				// MD
				#pragma comment (lib, LIBCUNILOG_PATH "Release/libcunilog.lib")
			#elif defined (_MT) && defined (_DLL) && defined (_DEBUG)
				// MDd
				#pragma comment (lib, LIBCUNILOG_PATH "Debug/libcunilog.lib")
			#elif defined (_MT) && !defined (_DLL) && !defined (_DEBUG)
				// MT
				#pragma comment (lib, LIBCUNILOG_PATH "ReleaseMT/libcunilogMT.lib")
			#elif defined (_MT) && !defined (_DLL) && defined (_DEBUG)
				// MTd
				#pragma comment (lib, LIBCUNILOG_PATH "DebugMT/libcunilogMT.lib")
			#endif
		#endif

	#endif
#endif


#endif														// Of #ifdef _MSC_VER.

#endif														// Of #ifndef HAVE_WINLINKTOCUNILOG_H.
