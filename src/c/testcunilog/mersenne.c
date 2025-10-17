/****************************************************************************************

	File:		mersenne.c
	Why:		Implements a Mersenne Twister. The code has been taken, with little
				modifications, from https://en.wikipedia.org/wiki/Mersenne_Twister in
				2025-07.
	OS:			As many compilers and platforms as required.
	Author:		Thomas
	Created:	2025-09-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-09-29	Thomas			Created, i.e. code moved to its own module.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This code is public domain.
*/

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./mersenne.h"
	#else
		#include "./mersenne.h"
	#endif

#endif

/*
	This is a header-only module. See mersenne.h for details.
*/
