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
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\*?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\??????????", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:\\Test\\?????????*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:\\Test\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:*?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("D:????????????", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "D:File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\share\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share*", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\share*?", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server\\?????????", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path)));
		DoneU8 (chU8Path);
		chU8Path = AllocU8path_from_U8path_and_WinU16FileName ("\\\\Server", L"File.txt");
		ubf_expect_bool_AND (b, !memcmp (chU8Path, "\\\\Server\\File.txt", strlen (chU8Path)));
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
		b &= GetWinErrorTextU8 (sz, 1024, 456);
		ubf_assert_true (b);
		b &= GetWinErrorTextU8 (sz, 1024, 457);
		ubf_assert_true (b);


		return b;
	}
#endif

#endif														// Of #ifdef _WIN32.
