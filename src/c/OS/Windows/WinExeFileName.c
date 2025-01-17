/****************************************************************************************

	File:		WinExeFileName.c
	Why:		Obtains the name of the executable.
	OS:			Windows.
	Author:		Thomas
	Created:	2024-05-21

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-05-21	Thomas			Created.

****************************************************************************************/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

	#include "./WinExeFileName.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./WinAPI_U8.h"
		#include "./unref.h"
		#include "./memstrstr.h"
		#include "./ubfdebug.h"
		#include "./Warnings.h"
	#else
		#include "./WinAPI_U8.h"
		#include "./../../pre/unref.h"
		#include "./../../pre/Warnings.h"
		#include "./../../mem/memstrstr.h"
		#include "./../../dbg/ubfdebug.h"
		#include "./../../pre/Warnings.h"
	#endif

#endif

#ifdef OS_IS_WINDOWS

	SMEMBUF mbOurExecutablePath = SMEMBUF_INITIALISER;
	size_t	lnOurExectuablePath = 0;

	/*
		Stores our executable's module name and its length in the variables above.
	*/
	static void StoreExecutableModuleName (SMEMBUF *mb, size_t ln)
	{
		ubf_assert_non_NULL (mb);
		ubf_assert (isInitialisedSMEMBUF (mb));
		ubf_assert_non_0 (ln);
		ubf_assert (USE_STRLEN != ln);

		if (!isUsableSMEMBUF (&mbOurExecutablePath))
		{
			copySMEMBUF (&mbOurExecutablePath, mb);
			lnOurExectuablePath = ln;

			// Ensure we have a NUL terminator.
			ubf_assert (0 == mbOurExecutablePath.buf.pch [ln]);
			ubf_assert (strlen (mbOurExecutablePath.buf.pch) == ln);
		}
	}

	/*
		If we already obtained our own executable's module name, the function resizes
		the buffer of mb to the size of mbOurExecutablePath and copies it in, basically
		returning a copy of our executable's module name.

		The function returns the length of the previously obtained module name, or 0
		if none has been obtained yet.
	*/
	static size_t WeHaveExecutableModuleNameAlready (SMEMBUF *mb)
	{
		ubf_assert_non_NULL (mb);
		ubf_assert (isInitialisedSMEMBUF (mb));

		if (isUsableSMEMBUF (&mbOurExecutablePath))
		{
			copySMEMBUF (mb, &mbOurExecutablePath);
			// Note that we do not check here if the copy operation was successful.
			//	We leave this within the caller's responsibility.
			return lnOurExectuablePath;
		}
		return 0;
	}

	DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

	size_t WinObtainExecutableModuleName (SMEMBUF *mb)
	{
		ubf_assert_non_NULL (mb);

		size_t len;												// The return value.
		if (len = WeHaveExecutableModuleNameAlready (mb))
			return len;

		DWORD	dwCurrSiz	= EXEFILENAME_MALLOC_BLOCKSIZE;
		DWORD	dw;
		char	*szExe		= (char *) &dw;						// Dummy value.

		while (szExe)
		{
			szExe = malloc (dwCurrSiz);
			if (szExe)
			{
				dw = GetModuleFileNameU8 (NULL, szExe, dwCurrSiz);
				if (dw && dw < dwCurrSiz)
				{	// See
					//	https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew .
					size_t	elen = dw;
					growToSizeSMEMBUF (mb, elen + 1);
					if (isUsableSMEMBUF (mb))
					{
						size_t l = strlen (szExe);
						UNUSED_PARAMETER (l);
						memcpy (mb->buf.pch, szExe, elen + 1);
						size_t m = strlen (mb->buf.pch);
						UNUSED_PARAMETER (m);
						StoreExecutableModuleName (mb, elen);
						free (szExe);
						return dw;
					}
				}
				free (szExe);
				if (0 == dw)
				{
					ubf_assert (false);
					return false;
				}
				dwCurrSiz += EXEFILENAME_MALLOC_BLOCKSIZE;
			}
		}
		return 0;
	}

	DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

	DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

	size_t WinObtainAppNameFromExecutableModule (SMEMBUF *mb)
	{
		ubf_assert_non_NULL (mb);

		size_t	l;

		if ((l = WinObtainExecutableModuleName (mb)))
		{
		
			// This works only on Windows:
			char *dot = memstrrchr (mb->buf.pch, l, '.');
			if (dot)
			{
				*dot = '\0';
				char *sl = memstrrchr (mb->buf.pch, strlen (mb->buf.pch), '\\');
				if (sl)
				{
					char	*sn = sl + 1;							// From after '\\'
					size_t	len = dot - sn;							//	to before '\0'.
					memmove (mb->buf.pch, sn, len + 1);
					return len;
				}
				// No backslash. Not sure if this needs a different implementation.
				ubf_assert (false);
			}
		}
		return 0;
	}

	DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION ()

	size_t WinObtainPathFromExecutableModule (SMEMBUF *mb)
	{
		ubf_assert_non_NULL (mb);

		if (WinObtainExecutableModuleName (mb))
		{
			size_t	l = strlen (mb->buf.pch);
			UNUSED_PARAMETER (l);
		
			char *sl = memstrrchr (mb->buf.pch, strlen (mb->buf.pch), '\\');
			if (sl)
			{
				++ sl;
				*sl = '\0';
				return sl - mb->buf.pch;
			}
			// No backslash. Not sure if this needs a different implementation.
			ubf_assert (false);
		}
		return 0;
	}

#endif														// Of #ifdef OS_IS_WINDOWS
