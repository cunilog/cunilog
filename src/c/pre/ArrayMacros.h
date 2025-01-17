/****************************************************************************************

	File:		ArrayMacros.h
	Why:		Macros for arrays and alignments. This header file does not have a code
				file.
	OS:			C99
	Author:		Thomas
	Created:	2022-03-27
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-03-27	Thomas			Created.

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

#ifndef HAVE_ARRAYMACROS_H
#define HAVE_ARRAYMACROS_H

#ifndef CUNILOG_USE_COMBINED_MODULE
	#include "./externC.h"
#endif

EXTERN_C_BEGIN

#ifndef UBF_TYPE_DEFINITIONS_INCL_H

// Some macros taken from
//	https://www.codeproject.com/Articles/567335/Essential-Macros-for-C-Programming .
// Number of elements in an array.
#ifndef GET_ARRAY_LEN
#define GET_ARRAY_LEN(arrayName) (sizeof (arrayName) / sizeof ((arrayName)[0]))
#endif
#ifndef UBF_GET_ARRAY_LEN
#define UBF_GET_ARRAY_LEN(arrayName)					\
			GET_ARRAY_LEN (arrayName)
#endif
#ifndef GET_ARRAY_MAX_IDX
#define GET_ARRAY_MAX_IDX(arrayName)					\
		((sizeof(arrayName) / sizeof ((arrayName)[0])) - 1)
#endif
// Aligns the supplied size to the specified PowerOfTwo
#ifndef ALIGN_SIZE
#define ALIGN_SIZE(sizeToAlign, PowerOfTwo)				\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif
#ifndef ALIGNED_SIZE
#define ALIGNED_SIZE(sizeToAlign, PowerOfTwo)			\
		(((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#endif
// Checks whether the supplied size is aligned to the specified PowerOfTwo
#ifndef IS_SIZE_ALIGNED
#define IS_SIZE_ALIGNED(sizeToTest, PowerOfTwo)			\
		(((sizeToTest) & ((PowerOfTwo) - 1)) == 0)
#endif
// Allocate the structure StructName.
#ifndef ALLOC_STRUCT
#define ALLOC_STRUCT(StructName) ((StructName *) ubf_malloc (sizeof (StructName)))
#endif

#endif														// Of #ifndef UBF_TYPE_DEFINITIONS_INCL_H.

EXTERN_C_END

#endif														// Of #ifndef HAVE_ARRAYMACROS_H.
