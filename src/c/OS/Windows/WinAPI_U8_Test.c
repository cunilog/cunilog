/****************************************************************************************

	File		WinAPI_U8_Test.c
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

#ifdef _WIN32

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_U8.h"
	#include "./WinAPI_U8_Test.h"
	#include "./WinAPI_ReadDirFncts.h"
	#include "./WinExeFileName.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./ubfmem.h"
		#include "./strisdotordotdot.h"
	#else
		#include "./../../dbg/ubfdebug.h"
		#include "./../../mem/ubfmem.h"
		#include "./../../string/strisdotordotdot.h"
	#endif

#endif

#ifdef BUILD_TEST_WINAPI_U8_FNCT
	bool Test_AllocU8path_from_U8path_and_WinU16FileName (void)
	{
		bool		b			= true;
		char		*chU8Path;
		
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\Fil*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\*?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\??????????", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\?????????*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:*?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:????????????", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\share\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share*?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\?????????", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path) + 1));
		DoneU8 (chU8Path);

		return b;
	}
#endif

#ifdef BUILD_TEST_WINAPI_U8_FNCT
	bool Test_WinAPI_U8 (void)
	{
		bool b;

		b = Test_AllocU8path_from_U8path_and_WinU16FileName ();
		ubf_expect_bool_AND (b, !isDotOrDotDotW (L""));
		ubf_expect_bool_AND (b, !isDotOrDotDotW (L"A"));
		ubf_expect_bool_AND (b, isDotOrDotDotW (L"."));
		ubf_expect_bool_AND (b, isDotOrDotDotW (L".."));

		wchar_t	wc	[2 * WINAPI_U8_HEAP_THRESHOLD];
		char	str [WINAPI_U8_HEAP_THRESHOLD];
		char	*pstr;
		
		wcscpy (wc, L"This is a test.");
		pstr = AllocU8_from_WinU16l (wc, 0);
		ubf_expect_bool_AND (b, NULL != pstr);
		ubf_expect_bool_AND (b, ASCII_NUL == pstr [0]);
		DoneU8 (pstr);
		pstr = AllocU8_from_WinU16l (NULL, 0);
		ubf_expect_bool_AND (b, NULL != pstr);
		ubf_expect_bool_AND (b, ASCII_NUL == pstr [0]);
		DoneU8 (pstr);
		pstr = AllocU8_from_WinU16l (wc, 1);
		ubf_expect_bool_AND (b, NULL != pstr);
		ubf_expect_bool_AND (b, !memcmp ("T", pstr, 2));
		DoneU8 (pstr);
		pstr = AllocU8_from_WinU16l (wc, wcslen (wc) + 1);
		ubf_expect_bool_AND (b, NULL != pstr);
		ubf_expect_bool_AND (b, !memcmp ("This is a test.", pstr, wcslen (wc) + 1));
		DoneU8 (pstr);
		pstr = AllocU8_from_WinU16l (wc, wcslen (wc));
		ubf_expect_bool_AND (b, NULL != pstr);
		ubf_expect_bool_AND (b, !memcmp ("This is a test.", pstr, wcslen (wc) + 1));
		DoneU8 (pstr);

		wcscpy (wc, L"This is a test.");
		pstr = AllocU8fromWinU16orUseThresholdl (str, wc, wcslen (wc));
		// We expect the output to be NUL-terminated.
		ubf_expect_bool_AND (b, !memcmp ("This is a test.", str, wcslen (wc) + 1));

		DoneU8fromWinU16orUseThreshold (pstr, str);

		char			sz [1024];
		unsigned int	ui, u2, u3;

		/*
			Return value checks for GetSystemDirectoryU8 () and GetSystemWindowsDirectoryU8 ().

			From
			https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemdirectoryw
			and
			https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemwindowsdirectoryw :

			Return value

			If the function succeeds, the return value is the length, in TCHARs, of the string
			copied to the buffer, not including the terminating null character. If the length
			is greater than the size of the buffer, the return value is the size of the buffer
			required to hold the path, including the terminating null character.

			If the function fails, the return value is zero. To get extended error information,
			call GetLastError.
		*/
		ui = GetSystemDirectoryU8 (sz, 1024);
		ubf_expect_bool_AND (b, ui > 0);
		// We assume that the returned directory is not longer than 1024 characters.
		for (u2 = 0; u2 < ui; ++ u2)
		{
			u3 = GetSystemDirectoryU8 (sz, u2);
			ubf_expect_bool_AND (b, ui + 1 == u3);
		}
		u2 = GetSystemDirectoryU8 (sz, ui);
		ubf_expect_bool_AND (b, ui + 1 == u2);
		const char *szSysDir = SystemDirectoryU8 ();
		ubf_expect_bool_AND (b, 0 == memcmp (sz, szSysDir, SystemDirectoryU8len () + 1));
		DoneSystemDirectoryU8 ();
		/*
			The same applies to our GetSystemWindowsDirectoryU8 () function.
		*/
		ui = GetSystemWindowsDirectoryU8 (sz, 1024);
		ubf_expect_bool_AND (b, ui > 0);
		// We assume that the returned directory is not longer than 1024 characters.
		for (u2 = 0; u2 < ui; ++ u2)
		{
			u3 = GetSystemWindowsDirectoryU8 (sz, u2);
			ubf_expect_bool_AND (b, ui + 1 == u3);
		}
		u2 = GetSystemWindowsDirectoryU8 (sz, ui);
		ubf_expect_bool_AND (b, ui + 1 == u2);
		const char *szWinDir = SystemWindowsDirectoryU8 ();
		ubf_expect_bool_AND (b, 0 == memcmp (sz, szWinDir, SystemWindowsDirectoryU8len () + 1));
		DoneSystemWindowsDirectoryU8 ();

		b &= GetWinErrorTextU8 (sz, 1024, 455);
		ubf_assert_true (b);
		// Since we don't know in which language the text appears we just assume it's
		//	longer than 10 octets/bytes.
		ubf_expect_bool_AND (b, 10 < strlen (sz));
		b &= GetWinErrorTextU8 (sz, 1024, 456);
		ubf_assert_true (b);
		ubf_assert_bool_AND (b, 10 < strlen (sz));
		b &= GetWinErrorTextU8 (sz, 1024, 457);
		ubf_assert_true (b);
		ubf_assert_bool_AND (b, 10 < strlen (sz));

		// Since we don't know how we're called, there's not much to test here.
		//	Let's see if the function crashes.
		DWORD dw = GetNumberOfProcessesAttachedToConsole ();
		UNREFERENCED_PARAMETER (dw);
		printf (" Processes attached to current console: %u ", dw);
		bool bOnlyConsole = IsOnlyProcessAttachedToConsole ();
		UNREFERENCED_PARAMETER (bOnlyConsole);

		#ifdef HAVE_VERSION
			DWORD dwMaj;
			DWORD dwMin;
			DWORD dwBld;
			DWORD dwRev;
			//b &= GetFileVersionNumbers (&dwMaj, &dwMin, &dwBld, &dwRev, WinGetExecutableModuleNameStr ());
			b &= GetFileVersionNumbers (&dwMaj, &dwMin, &dwBld, &dwRev, "C:\\Windows\\System32\\notepad.exe");
			bool bs = WinNotepadSupportsLineFeed ();
			UNREFERENCED_PARAMETER (bs);
		#endif

		return b;
	}
#endif

#endif														// Of #ifdef _WIN32.
