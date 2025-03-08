/****************************************************************************************

	File:		UserHome.c
	Why:		User home directory functions.
	OS:			C99.
	Author:		Thomas
	Created:	2025-03-03
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-03-03	Thomas			Created.

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

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./UserHome.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./externC.h"
		#include "./platform.h"
		#include "./ubfdebug.h"

		#if defined (PLATFORM_IS_WINDOWS)
			#include "./WinAPI_U8.h"
		#elif defined (PLATFORM_IS_POSIX)
			#include "./PsxHome.h"
		#endif
		
	#else

		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
		#include "./../dbg/ubfdebug.h"

		#if defined (PLATFORM_IS_WINDOWS)
			#include "./../OS/Windows/WinAPI_U8.h"
		#elif defined (PLATFORM_IS_POSIX)
			#include "./../OS/POSIX/PsxHome.h"
		#endif

	#endif

#endif


size_t ObtainUserHomeDirectoy (SMEMBUF *mb)
{
	ubf_assert_non_NULL (mb);
	ubf_assert (isInitialisedSMEMBUF (mb));

	size_t	r = 0;

	#if defined (PLATFORM_IS_WINDOWS)

		HANDLE	hToken	= 0;
		DWORD	dw		= 0;
		
		if (OpenProcessToken (GetCurrentProcess (), TOKEN_QUERY, &hToken))
		{
			GetUserProfileDirectoryU8 (hToken, NULL, &dw);
			growToSizeSMEMBUF (mb, (size_t) dw + 1);
			if (isUsableSMEMBUF (mb))
			{
				bool b = GetUserProfileDirectoryU8 (hToken, mb->buf.pch, &dw);
				if (b && dw > 1)
				{
					// This check is normally not required since we actually already
					//	know that the profile folder comes without a directory separator
					//	but we're going to play safe here.
					if ('\\' != mb->buf.pch [dw - 2])
					{
						++ dw;
						mb->buf.pch [dw - 2] = '\\';
						mb->buf.pch [dw - 1] = '\0';
					}
					ubf_assert ('\0' == mb->buf.pch [dw - 1]);
					r = (size_t) dw - 1;
				}
			}
			CloseHandle (hToken);
		}

	#elif defined (PLATFORM_IS_POSIX)

		size_t lnH;
		const char *szH = UserHomeDirectoryPOSIX (&lnH);
		// Same here:
		// This check is normally not required since we actually already
		//	know that the profile folder comes without a directory separator
		//	but we're going to play safe here.
		if (lnH && '/' != szH [lnH])
		{
			r = SMEMBUFfromStrReserveBytes (mb, szH, lnH + 1, 1) - 1;
			if (r)
			{
				mb->buf.pch [lnH]		= '/';
				mb->buf.pch [lnH + 1]	= '\0';
				++ r;
			}
		} else
			r = SMEMBUFfromStr (mb, szH, lnH + 1) - 1;

	#else

		#error Not supported!

	#endif

	return r;
}
