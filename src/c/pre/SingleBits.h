/****************************************************************************************

	File:		SingleBits.h
	Why:		Macros for single bits.
	OS:			Platform independent
	Author:		Thomas
	Created:	2019-05-07

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-05-07	Thomas			Created.

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

#ifndef SINGLEBITS_H
#define SINGLEBITS_H

#define SINGLE_BIT(bitnum)									\
	(1 << bitnum)

#ifdef __cplusplus
	#define SINGLE_BIT_UINT32(bitnum)						\
		((static_cast<uint32_t>(1)) << bitnum)
#else
	#define SINGLE_BIT_UINT32(bitnum)						\
		(((uint32_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UINT64(bitnum)						\
		((static_cast<uint64_t>(1)) << bitnum)
#else
	#define SINGLE_BIT_UINT64(bitnum)						\
		(((uint64_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UINT64_NONE							\
		(static_cast<uint64_t>(0))
#else
	#define SINGLE_BIT_UINT64_NONE							\
		((uint64_t) 0)
#endif

// Short form of SINGLE_BIT_UINT64().
#ifdef __cplusplus
	#define SINGLEBIT64(bitnum)								\
		((static_cast<uint64_t>(1)) << bitnum)
#else
	#define SINGLEBIT64(bitnum)								\
		(((uint64_t) 1) << bitnum)
#endif

#ifdef __cplusplus
	#define SINGLEBIT64_NONE								\
		(static_cast<uint64_t>(0))
#else
	#define SINGLEBIT64_NONE								\
		((uint64_t) 1)
#endif

#ifdef __cplusplus
	#define SINGLE_BIT_UNSIGNED_INT(bitnum)					\
		((static_cast<unsigned int>(1)) << bitnum)
#else
	#define SINGLE_BIT_UNSIGNED_INT(bitnum)					\
		(((unsigned int) 1) << bitnum)
#endif

#define SetBit(val, bit)	(val | (1 << bit))					// Set.
#define ClrBit(val, bit)	(val & (~(1 << bit)))				// Clear.
#define TglBit(val, bit)	(val ^ (1 << bit))					// Toggle.
#define HasBit(val, bit)	((val >> bit) & 1)					// Check.

#endif															// Of #ifndef SINGLEBITS_H.
