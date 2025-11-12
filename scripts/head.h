/****************************************************************************************

	File:		head.h
	Why:		Provides the head of the combined cunilog.h header file.
	OS:			C99.
	Author:		Thomas
	Created:	2024-08-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-01	Thomas			Created.

****************************************************************************************/

#ifndef CUNILOG_USE_COMBINED_MODULE
#define CUNILOG_USE_COMBINED_MODULE
#endif

/*
	These definitions are only required for Windows but defining them
	unconditionally won't do any harm.
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef HAVE_STRWILDCARDS
#define HAVE_STRWILDCARDS
#endif
#ifndef HAVE_SHELLAPI
#define HAVE_SHELLAPI
#endif
#ifndef HAVE_USERENV
#define HAVE_USERENV
#endif
#ifndef HAVE_MEMBUF
#define HAVE_MEMBUF
#endif

/*
	Debug versions of heap allocation functions.
	It is recommended to also define _CRTDBG_MAP_ALLOC in the project settings.
	
	See
	https://learn.microsoft.com/en-us/cpp/c-runtime-library/crtdbg-map-alloc?view=msvc-170
	and
	https://learn.microsoft.com/en-us/cpp/c-runtime-library/debug-versions-of-heap-allocation-functions?view=msvc-170 .
*/
#ifndef CUNILOG_DONT_USE_CRTDBG_MAP_ALLOC
	#ifndef _CRTDBG_MAP_ALLOC
	#define _CRTDBG_MAP_ALLOC
	#endif
#endif

/*
	Our include guard.
	The #endif is in bottom.h.
*/
#ifndef CUNILOG_COMBINED_INCLUDED
#define CUNILOG_COMBINED_INCLUDED
