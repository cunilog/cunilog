/****************************************************************************************

	File		functionptrtpydef.h
	Why:		Helper macros to create typedefs for function pointers.
	OS:			Windows
	Created:	2025-02-20

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-20	Thomas			Created.

****************************************************************************************/

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

#ifndef U_FUNCTIONPTRTPYDEF_H
#define U_FUNCTIONPTRTPYDEF_H

/*
	Prefix and postfix of function pointer typedefs when created with the macros
	TYPEDEF_FNCT_PTR() and TYPEDEF_FNCT_PTR_ARGS().
*/
#ifndef CUL_FNCTS_POINTER_PREFIX
#define CUL_FNCTS_POINTER_PREFIX	fncpt_
#endif
#ifndef CUL_FNCTS_POINTER_POSTFIX
#define CUL_FNCTS_POINTER_POSTFIX	_t
#endif

/*
	TYPEDEF_FNCT_PTR

	Creates a function pointer type definition.

	TYPEDEF_FNCT_PTR (bool, functionName);
		-> typedef bool (fncpt_functionName_t)
*/
#define TYPEDEF_FNCT_PTR(rettpy, fnctname)				\
			TYPEDEF_FNCT_PTR_	(						\
						rettpy, fnctname,				\
						CUL_FNCTS_POINTER_PREFIX,		\
						CUL_FNCTS_POINTER_POSTFIX		\
								)

#define TYPEDEF_FNCT_PTR_(rettpy, fnctname, prf, pof)	\
			TYPEDEF_FNCT_PTR__ (rettpy, fnctname, prf, pof)

#define TYPEDEF_FNCT_PTR__(rettpy, fnctname, prf, pof)	\
			typedef rettpy (*prf ## fnctname ## pof)

/*
	TYPEDEF_FNCT_PTR_ARGS

	Creates a function pointer type definition including its arguments.

	TYPEDEF_FNCT_PTR_ARGS (bool, functionName, int b);
		-> typedef bool (fncpt_functionName_t) (int b)
*/
#define TYPEDEF_FNCT_PTR_ARGS(rettpy, fnctname, ...)	\
			TYPEDEF_FNCT_PTR_ARGS_	(					\
						rettpy, fnctname,				\
						CUL_FNCTS_POINTER_PREFIX,		\
						CUL_FNCTS_POINTER_POSTFIX,		\
						__VA_ARGS__						\
									)

#define TYPEDEF_FNCT_PTR_ARGS_(rettpy, fnctname, prf, pof, ...)		\
			TYPEDEF_FNCT_PTR_ARGS__ (rettpy, fnctname, prf, pof, __VA_ARGS__)

#define TYPEDEF_FNCT_PTR_ARGS__(rettpy, fnctname, prf, pof, ...)	\
			typedef rettpy (*prf ## fnctname ## pof) (__VA_ARGS__)

#endif														// Of #ifndef U_FUNCTIONPTRTPYDEF_H.
