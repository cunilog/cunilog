/****************************************************************************************

	File		functionptrtpydef.h
	Why:		Helper macro to create a typedef for a function pointer.
	OS:			Windows
	Created:	2025-02-20

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-20	Thomas			Created.

****************************************************************************************/

#ifndef U_FUNCTIONPTRTPYDEF_H
#define U_FUNCTIONPTRTPYDEF_H

/*
	TYPEDEF_FNCT_PTR

	Creates a function pointer type definition.
*/
#define TYPEDEF_FNCT_PTR(rettpy, fnctname)						\
			typedef rettpy (*fncpt_ ## fnctname)

/*
	TYPEDEF_FNCT_PTR_ARGS

	Creates a function pointer type definition including its arguments.
*/
#define TYPEDEF_FNCT_PTR_ARGS(rettpy, fnctname, ...)			\
			typedef rettpy (*fncpt_ ## fnctname) (__VA_ARGS__)

#endif														// Of #ifndef U_FUNCTIONPTRTPYDEF_H.
