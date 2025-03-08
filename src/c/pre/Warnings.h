/****************************************************************************************

	File:		Warnings.h
	Why:		Macros to disable/enable some warnings.
	OS:			C99
	Author:		Thomas
	Created:	2024-08-07
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-08-07	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

#ifdef _MSC_VER

	// Array is too small to include a terminating NUL.
	#ifndef DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()		\
		_Pragma ("warning (disable: 4295)")
	#endif

	#ifndef DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()		\
		_Pragma ("warning (default: 4295)")
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()	\
		_Pragma ("warning (disable: 4701)")
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()	\
		_Pragma ("warning (default: 4701)")
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()	\
		_Pragma ("warning (disable: 4703)")
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()	\
		_Pragma ("warning (default: 4703)")
	#endif

	// Assignment within conditional expression.
	#ifndef DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()	\
		_Pragma ("warning (disable: 4706)")
	#endif

	#ifndef DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()	\
		_Pragma ("warning (default: 4706)")
	#endif

#else

	// Array is too small to include a terminating NUL.
	#ifndef DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DISABLE_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()
	#endif

	#ifndef DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR
	#define DEFAULT_WARNING_ARRAY_TOO_SMALL_FOR_NUL_TERMINATOR()
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_VARIABLE_USED()
	#endif

	//  Potentially uninitialized local variable used.
	#ifndef DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DISABLE_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()
	#endif

	#ifndef DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED
	#define DEFAULT_WARNING_POTENTIALLY_UNINITIALISED_LOCAL_POINTER_USED()
	#endif

	// Assignment within conditional expression.
	#ifndef DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DISABLE_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()
	#endif

	#ifndef DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION
	#define DEFAULT_WARNING_ASSIGNMENT_WITHIN_CONDITIONAL_EXPRESSION()
	#endif

#endif														// Of #ifdef _MSC_VER.
