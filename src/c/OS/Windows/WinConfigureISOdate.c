/****************************************************************************************

	File:		WinConfigureISOdate.c
	Why:		Module to configure date and time format in the Windows registry.
	OS:			Windows.
	Author:		Thomas
	Created:	2025-11-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-11-17	Thomas			Created.

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
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinConfigureISOdate.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
	#else
	#endif

	#ifdef BUILD_WINCONFIGUREISODATE_TEST
		#include <stdio.h>
	#endif

#endif

#ifdef PLATFORM_IS_WINDOWS

#define WCI_M	L"-"										// Date component separator.
#define WCI_D	L"yyyy-MM-dd"
//#define WCI_L	L"dddd yyyy-MM-dd"							// We do not set the long date.

#define WCI_C	L":"										// Time component separator.
#define WCI_S	L"HH:mm"
#define WCI_T	L"HH:mm:ss"

const WCHAR		wcUSER_HK_KEY	[] = L"HKEY_CURRENT_USER";
const WCHAR		wcUSER_ISO_DATE [] = L"Control Panel\\International";

const WCHAR		wcALL_HK_KEY	[]	= L"HKEY_USERS";
const WCHAR		wcALL_ISO_DATE	[]	= L".DEFAULT\\Control Panel\\International";

#define reg_rights	(KEY_READ | KEY_SET_VALUE)

bool setISO8601inRegistry (enum enISOregistry reg)
{
	const WCHAR	*pwSKey				= NULL;
	const WCHAR	*pwBKey				= NULL;
	HKEY		key;
	HKEY		hk;
	LSTATUS		ls;

	switch (reg)
	{
		case enISOregistryCurrentUser:	key		= HKEY_CURRENT_USER;
										pwBKey	= wcUSER_HK_KEY;
										pwSKey	= wcUSER_ISO_DATE;
										break;
		case enISOregistryAllUsers:		key		= HKEY_USERS;
										pwBKey	= wcALL_HK_KEY;
										pwSKey	= wcALL_ISO_DATE;
										break;
		default:						return false;
	}

	ls = RegOpenKeyExW (key, pwSKey, 0, reg_rights, &hk);
	if (ERROR_SUCCESS != ls) return false;
	ls = RegSetValueExW (hk, L"sDate", 0, REG_SZ, (LPBYTE) WCI_M, (DWORD) sizeof (WCI_M));
	if (ERROR_SUCCESS != ls) goto Escape;
	ls = RegSetValueExW (hk, L"sShortDate", 0, REG_SZ, (LPBYTE) WCI_D, (DWORD) sizeof (WCI_D));
	if (ERROR_SUCCESS != ls) goto Escape;
	// We do not set the long date.
	/*
	ls = RegSetValueExW (hk, "sLongDate", 0, REG_SZ, (LPBYTE) WCI_L, (DWORD) sizeof (WCI_L));
	if (ERROR_SUCCESS != ls) goto Escape;
	*/
	ls = RegSetValueExW (hk, L"sTime", 0, REG_SZ, (LPBYTE) WCI_C, (DWORD) sizeof (WCI_C));
	if (ERROR_SUCCESS != ls) goto Escape;
	ls = RegSetValueExW (hk, L"sShortTime", 0, REG_SZ, (LPBYTE) WCI_S, (DWORD) sizeof (WCI_S));
	if (ERROR_SUCCESS != ls) goto Escape;
	ls = RegSetValueExW (hk, L"sTimeFormat", 0, REG_SZ, (LPBYTE) WCI_T, (DWORD) sizeof (WCI_T));

	Escape:
	SetLastError (ls);
	RegCloseKey(hk);
	return ERROR_SUCCESS == ls;
}

#ifdef BUILD_WINCONFIGUREISODATE_TEST
	bool WinConfigureISOdateTestFnct (void)
	{
		return setISO8601inRegistry (enISOregistryCurrentUser);
	}
#endif

#endif													// Of #ifdef PLATFORM_IS_WINDOWS.
