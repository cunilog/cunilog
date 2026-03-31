/****************************************************************************************

	File:		pragmaDefault.c
	Why:		Pragmas after miniz.c has been included.
	Author:		Thomas
	Created:	2026-03-08
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2026-03-08	Thomas			Created.

****************************************************************************************/

#ifdef _MSC_VER

	#pragma runtime_checks ("", restore)
	#pragma warning (disable: 4127)							// Conditional expression in constant.

#endif
