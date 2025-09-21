/****************************************************************************************

	File:		ExeFileName.c
	Why:		Obtains the name of the executable.
	OS:			C99.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

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

#include <malloc.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ExeFileName.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
	#else
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

#ifdef CUNILOG_BUILD_EXEFILENAME_TEST_FNCT
	bool TestExeFileNameFnct (void)
	{
		bool b = true;

		// Do we get something at all?
		SMEMBUF smbE = SMEMBUF_INITIALISER;
		size_t stE = ObtainExecutableModuleName (&smbE);
		ubf_assert_bool_AND (b, 0 < stE);
		SMEMBUF smbA = SMEMBUF_INITIALISER;
		size_t stA = ObtainAppNameFromExecutableModule (&smbA);
		ubf_assert_bool_AND (b, 0 < stA);
		SMEMBUF smbP = SMEMBUF_INITIALISER;
		size_t stP = ObtainPathFromExecutableModule (&smbP);
		ubf_assert_bool_AND (b, 0 < stP);

		return b;
	}
#endif
