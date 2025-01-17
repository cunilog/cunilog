/****************************************************************************************

	File:		ubfdebug.h
	Why:		Contains debugging functions.
	OS:			Windows/POSIX
	Author:		Thomas
	Created:	2017-10-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2017-10-24	Thomas			Created.
2018-05-26	Thomas			Compiler warning Linux/Android fixed by changing
							 the loop variable from int to unsigned int.
2019-08-24	Thomas			Module OS/ubf_debug.c/h should be obsolete now.

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

#ifndef U_UBF_DEBUG_DEB_H_INCLUDED
#define U_UBF_DEBUG_DEB_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef _MSC_VER
	#include <crtdbg.h>
#else
	#include <assert.h>
#endif

/*
	Below are the macros that turn on the functions listed in the comments on the right-
	hand side of the macro definitions.
*/
#ifndef UBF_DEBUG_HEX_DUMP
//#define UBF_DEBUG_HEX_DUMP									// When defined, enables
																//	ubf_debug_hex_dump ().
#endif
#ifdef UBF_DEBUG_NO_HEX_DUMP
	#undef UBF_DEBUG_HEX_DUMP
#endif

// When defined, enables ubf_debug_printf () and ubf_debug_puts ().
#ifdef DEBUG
	#ifndef UBF_DEBUG_USE_PRINTF
	#define UBF_DEBUG_USE_PRINTF
	#endif
#endif

// When defined, uses our output abort functions. If not, a simple
//	ABORT() macro is used. It is not recommended to uncomment this
//	definition. Rather define UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
//	in the development environment or project file.
#ifdef DEBUG
	#ifndef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#define UBF_USE_DBG_ABRT_OUTPUT_FNCTS
	#endif
#endif
#ifdef DEBUG
	#ifdef UBF_DONT_USE_DBG_ABRT_OUTPUT_FNCTS
		#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#undef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		#endif
	#endif
#endif

#ifndef UBF_DEBUG_MSG_STRLEN
#define UBF_DEBUG_MSG_STRLEN		(4096)
#endif

// The character used to identify buffer overruns and uninitialised areas. Can (and
//	should) be used as a general filler for debug purposes.
#ifndef UBF_ERROR_CHAR
#define UBF_ERROR_CHAR	'\x55'
#endif
#ifndef UBF_ERROR_CINT
#define UBF_ERROR_CINT	0x55
#endif

EXTERN_C_BEGIN

/*
	Macros to check if all members of a structure or union have been initialised.
	Check to see if we forgot to initialise a member. This is important when more
	members are added later.
	
	UBF_DEBUG_CHECK_STRUCT_DECLARATION()
	
	Sets the character used to initialise the structure before the real initialisation
	takes place.
	
	UBF_DEBUG_CHECK_STRUCT_ASSERTION()
	
	Checks if there are any octets within the structure's memory block that haven't been
	initialised by testing that no byte contains the character set with the macro
	UBF_DEBUG_CHECK_STRUCT_DECLARATION().
	
	
	Example:
	
	typedef struct structname
	{
		int		i1;
		int		i2;
		int		i3;
		int		i4;
		int		in;
	} STRUCTNAME;
	
	void test (void)
	{
		STRUCTNAME		sn;
		
		UBF_DEBUG_CHECK_STRUCT_DECLARATION (&sn, STRUCTNAME, 0x0D);
		sn.i1 = 1;
		sn.i2 = 2;
		//...
		sn.in = -1;
		UBF_DEBUG_CHECK_STRUCT_ASSERTION (&sn, STRUCTNAME);
	}
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(pstructure, typestruct, c)				\
		unsigned int	uStructCheck;													\
		unsigned char	*chStructCheck;													\
		unsigned char	cStructCheck		= (c);										\
		memset ((pstructure), (c), sizeof (typestruct))
#else
	#define UBF_DEBUG_CHECK_STRUCT_DECLARATION(c)
#endif
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)						\
		chStructCheck = (char *) (pstructure);											\
		for (uStructCheck = 0; uStructCheck < sizeof (typestruct); uStructCheck ++)		\
		{																				\
			if (*chStructCheck == cStructCheck)											\
				_ASSERT (false);														\
			++ chStructCheck;															\
		}
#else
	#define UBF_DEBUG_CHECK_STRUCT_ASSERTION(pstructure,typestruct)
#endif

/*
	UBF_DEBUG_CHECK_CALLED_ONLY_ONCE
	
	Macro to check that the function using it is only invoked once. Useful for
	initialisation functions.
	
	UBF_DEBUG_CHECK_RESET_ONLY_ONCE
	
	Resets the flag. Useful to check that a function that is not re-entrant is
	not called again before the previous instance has returned.
*/
#ifdef DEBUG
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)	\
		static bool	flagname;							\
		ubf_assert (!flagname);							\
		flagname = TRUE
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)	\
		flagname = FALSE
#else
	#define UBF_DEBUG_CHECK_CALLED_ONLY_ONCE(flagname)
	#define UBF_DEBUG_CHECK_RESET_ONLY_ONCE(flagname)
#endif

/*
	UBF_DEFINE_GUARD_VAR										// Define guard variable.
	UBF_CHECK_GUARD_VAR											// Check/test guard variable.
	UBF_DEF_GUARD_VAR											// Define guard variable.
	UBF_TST_GUARD_VAR											// Check/test guard variable.
	UBF_CHK_GUARD_VAR											// Check/test guard variable.
	
	Macros to define and to check guard variables. The variable defined is of
	type char []. These macros can help find buffer overruns.
	
	Examples:
	
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	The following example checks for an overrun of the array:
	
	int		i [105];
	UBF_DEFINE_GUARD_VAR	(testvar, 1234567);
	...
	UBF_CHECK_GUARD_VAR		(testvar, 1234567);
	
	If data is written beyond the array's memory location testvar is overwritten,
	at least on some platforms.
	Test data is defined with UBF_DEFINE_GUARD_VAR().
	The macro UBF_CHECK_GUARD_VAR() determines if the test variable's content has
	been destroyed.
*/
#ifdef DEBUG
	#ifndef UBF_DEFINE_GUARD_VAR
	#define UBF_DEFINE_GUARD_VAR(var, value)			\
		char	var [] = #value
	#endif
	#ifndef UBF_CHECK_GUARD_VAR
	#define UBF_CHECK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_DEF_GUARD_VAR
	#define UBF_DEF_GUARD_VAR(var, value)				\
		char	var [] = #value
	#endif
	#ifndef UBF_TST_GUARD_VAR
	#define UBF_TST_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
	#ifndef UBF_CHK_GUARD_VAR
	#define UBF_CHK_GUARD_VAR(var, value)				\
		ubf_assert (!strcmp (#value, var))
	#endif
#else
	#define UBF_DEFINE_GUARD_VAR(var, value)
	#define UBF_CHECK_GUARD_VAR(var, value)
	#define UBF_DEF_GUARD_VAR(var, value)
	#define UBF_TST_GUARD_VAR(var, value)
	#define UBF_CHK_GUARD_VAR(var, value)
#endif

/*
	ubf_debug_assert

	Outputs the message only if the assertion doesn't pass.
	
	ubf_debug_assert_pass

	Outputs the message chDebugMessage and then implements an _ASSERT () with bAssert.

	Use the macro UBF_DEBUG_ASSERT() or ubf_assert_msg() to fill in __FILE__ and __LINE__
	for the parameters chFilePath and uiLineNum. Both macros are identical. See
	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html for an explanation
	of the __FILE__ and __LINE__ macros. The macro ubf_assert () is probably what should
	be used as often as possible.

	In release versions these are macros that expand to nothing.
	
	It is recommended to use the ubf_assert() macro, which expects one parameter only. It
	stringifies this parameter for the output text. Since this is sometimes not possible
	due to the limitations of the preprocessor's stringify operator, or it's not
	desirable if condition and message text should differ, the macro ubf_assert_msg() can
	be used.

	Examples:

	// All these lines have the same or similar functionality:
	ubf_debug_assert (a > b, "a > b", __FILE__, __LINE__);
	UBF_DEBUG_ASSERT (a > b, "a > b", __FILE__, __LINE__);
	ubf_assert (a > b);
	ubf_assert_msg (a > b, "a > b");
	
	Explanation and further notes:
	
	Although assert () on Windows and Linux works great, it does exactly what the
	documentation says on Android: it aborts. No message, no information on where
	it stopped, nor why.
	
	ubf_assert (a > b) is a replacement for assert (). It displays a message with
	the assertion before it aborts.
	
	ubf_assert_msg (a > b, "Arbitrary message") is a replacement for assert () that
	outputs "Arbitrary message" when the assertion fails instead of the actual
	assertion.
*/
#ifdef DEBUG
	// Debug version.
	#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		void ubf_debug_assert		(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert(b, c, p, n)			\
			ASSERT (b)
	#endif
	#ifdef UBF_USE_DBG_ABRT_OUTPUT_FNCTS
		void ubf_debug_assert_pass	(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									);
	#else
		#define ubf_debug_assert_pass(b, c, p, n)		\
			ASSERT (b)
	#endif
	#ifndef UBF_DEBUG_ASSERT
	#define UBF_DEBUG_ASSERT(b)							\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert
	#define ubf_assert(b)								\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_msg
	#define ubf_assert_msg(b,m)							\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_message
	#define ubf_assert_message(b,m)						\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#endif
	#ifndef ubf_assert_pass
	#define ubf_assert_pass(b)							\
				ubf_debug_assert_pass (b, #b, __FILE__, __LINE__)
	#endif
	/*
		ubf_assert_Android
		
		Prints the message on Android but is a simple _ASSERT() on other platforms. That's
		because the application simply dies with an _ASSERT() on Android.
	*/
	#ifdef OS_IS_ANDROID
		#define ubf_assert_Android(b)					\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
		#define ubf_assert_Android_msg(b,m)				\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Android(b)					\
				_ASSERT (b)
		#define ubf_assert_Android_msg(b,m)				\
				_ASSERT (b)
	#endif
	/*
		ubf_assert_Linux
		
		Prints the message on Linux but is a simple _ASSERT() on other platforms.
	*/
	#ifdef OS_IS_LINUX
		#define ubf_assert_Linux(b)						\
				ubf_debug_assert (b, #b, __FILE__, __LINE__)
		#define ubf_assert_Linux_msg(b,m)				\
				ubf_debug_assert (b, m, __FILE__, __LINE__)
	#else
		#define ubf_assert_Linux(b)						\
				_ASSERT (b)
		#define ubf_assert_Linux_msg(b,m)				\
				_ASSERT (b)
	#endif
#else
	// Release version.
	#define ubf_debug_assert(b,m,f,l)
	#define ubf_debug_assert_pass(b,m,f,l)
	#define UBF_DEBUG_ASSERT(b)
	#define ubf_assert(b)
	#define ubf_assert_msg(b,m)
	#define ubf_assert_message(b,m)
	#define ubf_assert_pass(b)
	#ifdef UBF_ANDROID
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#else
		#define ubf_assert_Android(b)
		#define ubf_assert_Android_msg(b,m)
	#endif
	#ifdef UBF_LINUX
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#else
		#define ubf_assert_Linux(b)
		#define ubf_assert_Linux_msg(b,m)
	#endif
#endif

/*
	ubf_debug_fill_mem

	Fills the memory mem points to with UBF_ERROR_CHAR, which is 55h, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem (void *mem, size_t len);
#else
	#define ubf_debug_fill_mem(m,l)
#endif

/*
	ubf_debug_check_mem
	
	Assert that a memory block consists of UBF_ERROR_CHAR octets.
*/
#ifdef DEBUG
	void ubf_debug_check_mem (char *mem, size_t len);
#else
	#define ubf_debug_check_mem(m, l)
#endif

/*
	ubf_debug_fill_mem_with

	Fills the memory mem points to with the value of c, up to a length of
	len octets (bytes). In release versions this is a macro that expands to nothing.
	Debug versions assert that mem is not NULL and len is not 0.
*/
#ifdef DEBUG
	void ubf_debug_fill_mem_with (void *mem, char c, size_t len);
#else
	#define ubf_debug_fill_mem_with(m, c, l)
#endif

/*
	ubf_debug_check_mem_with

	Assert that a memory block consists of len octets filled with c.
*/
#ifdef DEBUG
	void ubf_debug_check_mem_with (char *mem, char c, size_t len);
#else
	#define ubf_debug_check_mem_with(m, c, l)
#endif

/*
	ubf_debug_hex_dump
	
	Calls ubf_data_dump_puts () in ubfdump.c if UBF_DEBUG_HEX_DUMP is defined.
	If UBF_DEBUG_HEX_DUMP is not defined, the function is expanded to a no-operation.
*/
#ifdef UBF_DEBUG_HEX_DUMP
	void ubf_debug_hex_dump (const char *chOutput, size_t stOutput);
#else
	#define ubf_debug_hex_dump(ch,st)
#endif

/*
	ubf_debug_printf
	ubf_debug_puts
	
	Debug versions of printf () and puts (). To make these calls no-operations (empty)
	macros, undefine UBF_DEBUG_USE_PRINTF. In release versions they are empty definitions.
*/
#ifdef UBF_DEVICE_GUI
	#ifdef DEBUG
		void ubf_debug_printf (const char *format, ...);
		void ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
	#ifdef UBF_DEBUG_USE_PRINTF
		#undef UBF_DEBUG_USE_PRINTF
	#endif
#else
	#ifdef UBF_DEBUG_USE_PRINTF
		int ubf_debug_printf (const char *format, ...);
		int ubf_debug_puts (const char *str);
	#else
		#define ubf_debug_printf(f,...)
		#define ubf_debug_puts(s)
	#endif
#endif

// Debug sleep. Sleeps in debug versions (milliseconds) but not in release builds.
#ifdef DEBUG
	#define ubf_debug_sleep_ms(s)			ubf_sleep_ms (s)
#else
	#define ubf_debug_sleep_ms(s)
#endif

// Macros to abort in debug versions.
#ifdef DEBUG
	#define DEBUGABORT()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORTDEBUG()	ASSERT (false)
	#define DBGABORT()		ASSERT (false)
	#define ABORT()			ASSERT (false)
#else
	#define DEBUGABORT()
	#define DBGABORT()
	#define ABORTDEBUG()
	#define DBGABORT()
	#define ABORT()
#endif

/*
	ubf_expect_bool_AND

	Macro to binary AND an expectation. Useful in test functons.

	bool	bOk		= TRUE;
	int		a		= 0;
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 3 == a);
	FunctionShouldAdd (&a, 3);
	ubf_expect_and (bOk, 6 == a);
	ubf_assert_true (bOk);
*/
#define ubf_expect_bool_AND(b, expectation)				\
			(b) &= (expectation);						\
			ubf_assert (true == (b))

/*
	ubf_assert_TRUE
	ubf_assert_FALSE
	ubf_expect_TRUE
	ubf_expect_FALSE
	ubf_assert_true
	ubf_expect_true
	ubf_assert_false
	ubf_expect_false

	Macros that assert that the provided boolean is either TRUE or FALSE.
*/
#define ubf_assert_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_expect_TRUE(b)								\
			ubf_assert (true == (b))
#define ubf_assert_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_expect_FALSE(b)								\
			ubf_assert (false == (b))
#define ubf_assert_true(b)								\
			ubf_assert (true == (b))
#define ubf_expect_true(b)								\
			ubf_assert (true == (b))
#define ubf_assert_false(b)								\
			ubf_assert (false == (b))
#define ubf_expect_false(b)								\
			ubf_assert (false == (b))


/*
	ubf_assert_NULL
	ubf_expect_NULL
	ubf_assert_not_NULL
	ubf_expect_not_NULL
	ubf_assert_non_NULL
	ubf_expect_non_NULL

	Macros that assert that the provided pointer is either NULL or non-NULL.
*/
#define ubf_assert_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_expect_NULL(p)								\
			ubf_assert (NULL == (p))
#define ubf_assert_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_not_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_assert_non_NULL(p)							\
			ubf_assert (NULL != (p))
#define ubf_expect_non_NULL(p)							\
			ubf_assert (NULL != (p))

/*
	ubf_assert_0
	ubf_expect_0
	ubf_assert_non_0
	ubf_expect_non_0
	ubf_assert_zero
	ubf_expect_zero
	ubf_assert_non_zero
	ubf_expect_non_zero

	Macros that assert that the parameter expression evaluates to zero or
	non-zero.
*/
#define ubf_assert_0(v)									\
			ubf_assert (0 == (v))
#define ubf_expect_0(v)									\
			ubf_assert (0 == (v))
#define ubf_assert_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_expect_non_0(v)								\
			ubf_assert (0 != (v))
#define ubf_assert_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_expect_zero(v)								\
			ubf_assert (0 == (v))
#define ubf_assert_non_zero(v)							\
			ubf_assert (0 != (v))
#define ubf_expect_non_zero(v)							\
			ubf_assert (0 != (v))


EXTERN_C_END

#endif															// Of U_UBF_DEBUG_DEB_H_INCLUDED.
