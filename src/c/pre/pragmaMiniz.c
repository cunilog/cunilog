/****************************************************************************************

	File:		pragmaMiniz.c
	Why:		Pragmas before miniz.c is included.
	Author:		Thomas
	Created:	2026-03-08
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2026-03-08	Thomas			Created.

****************************************************************************************/

#ifdef _MSC_VER

	#pragma warning (disable: 4127)							// Conditional expression in constant.
		
	// Not ideal, but required. RTC can't be used for miniz.
	#pragma runtime_checks ("", off)

#endif
