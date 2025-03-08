/****************************************************************************************

	File:		strhexdump.h
	Why:		Functions for data dumps.
	OS:			C99
	Author:		Thomas
	Created:	2024-09-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-10	Thomas			Created. Based on ubfdump.h, which is now obsolete.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

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

#ifndef STRHEXDUMP_H
#define STRHEXDUMP_H

#include <stdbool.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./strhexdumpstructs.h"
		#include "./strmembuf.h"
	#else
		#include "./strhexdumpstructs.h"
		#include "./strmembuf.h"
	#endif

#endif

EXTERN_C_BEGIN

/*
	Advanced hex dump. As of Jan 2025 the advanced hex dump is considered incomplete/abandoned.
	Use the simple hex dump instead. See further down.
*/

/*
	A default SUBF_DUMP_PARS structure for general use.
*/
extern	SHEX_DUMP_PARS		sdp_default;

/*
	ubf_data_dump_def_SUBF_DUMP_PARS
	
	Copies all members of the default SUBF_DUMP_PARS structure into the
	SUBF_DUMP_PARS structure s points to.
*/
void ubf_data_dump_def_SUBF_DUMP_PARS (SHEX_DUMP_PARS *s);

/*
	UBF_DATA_DUMP_DEF_SUBF_DUMP_PARS
	
	Convenience wrapper macro for ubf_data_dump_def_SUBF_DUMP_PARS to dereference the
	pointer.
*/
#define UBF_DATA_DUMP_DEF_SUBF_DUMP_PARS(a)		\
			ubf_data_dump_def_SUBF_DUMP_PARS (&(a))

/*
	ubf_data_dump_SMEMBUF
	
	Creates a dump of the data pointed to by chDumpData with the length stDumpDataLen
	into the SMEMBUF structure pointed to by mbOutput. The type and parameters of the
	data dump is determined by the SUBF_DUMP_PARS structure pointed to by sDumpPars.
	
	mbOutput			The SMEMBUF structure that receives the output.

	chDumpData			A pointer to the start of the dump data.

	lenDumpData			The length of the dump data, in octets (bytes).

	sDumpPars			A pointer to a SHEX_DUMP_PARS structure, which determines several
						parameters of the output.

	pdSanDPars			A pointer to a writable SHEX_DUMP_SAN structure. This can
						be used for consecutive invocations to avoid recalculating some
						values. If this parameter is NULL, the function uses its own
						automatic version and recalculates its members every time it is
						called. Each SHEX_DUMP_PARS requires its own SHEX_DUMP_SAN
						structure to preserve its calculated parameters.
						Set the structures lenHeader header to 0 before calling the
						function the first time. This tells it to calculate its values.
						It can then be re-used in consecutive calls and no recalculations
						are required.

	The function returns the amount of octets/bytes written to the buffer of mbOutput,
	excluding the terminating NUL character.
*/
size_t ubf_data_dump_SMEMBUF	(
		SMEMBUF				*mbOutput,						// The target SUBF_STRING.
		const char			*ccDumpData,					// The data to dump.
		size_t				lenDumpData,					// The length of the data to dump.
		SHEX_DUMP_PARS		*psDumpPars,					// The SUBF_DUMP_PARS structure.
		SHEX_DUMP_SAN		*pdSanDPars						// Can be carried to the next invokation.
								)
;

#ifdef nix
/*
	ubf_data_dump_puts

	The function is identical to ubf_data_dump_SUBF_STRING () with the exception that it
	doesn't need the SUBF_STRING parameter ssTarget and directly prints the dump output
	to stdout.

	The function provides a SUBF_STRING structure and calls ubf_data_dump_SUBF_STRING (),
	then uses puts () to output the SUBF_STRING structure's buffer if the call to
	ubf_data_dump_SUBF_STRING () was successful. It outputs nothing when the call
	to ubf_data_dump_SUBF_STRING () failed.

	If the type (const char *) is an issue, use ubf_data_dump_puts_typeless () to cast
	the first parameter.

	The function returns TRUE on success, FALSE on failure. The return value is obtained
	from the call to ubf_data_dump ().
*/
bool ubf_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
						);

/*
	ubf_debug_data_dump_puts
	
	Debug-only version of ubf_data_dump_puts (). Only outputs the data dump in debug
	versions.
*/
#ifdef DEBUG
	bool ubf_debug_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
									);
#else
	#define ubf_debug_data_dump_puts(a, b, c)
#endif

/*
	ubf_data_dump_puts_typeless

	Wrapper macro for ubf_data_dump_puts () to cast the first parameter into the (const
	char *) ubf_data_dump_puts () is declared for.
*/
#define ubf_data_dump_puts_typeless(d,l,p)		\
			ubf_data_dump_puts ((const char *) d, l, p)

/*
	ubf_debug_data_dump_puts_typeless
	
	Debug version of the macro ubf_data_dump_puts_typeless(). Only outputs in debug
	versions.
*/
#define ubf_debug_data_dump_puts_typeless(d,l,p)		\
			ubf_debug_data_dump_puts ((const char *) d, l, p)


/*
	ubf_data_dump_puts_default
	
	Macro wrapper for ubf_data_dump_puts () that only requires the first two parameters
	and sets the last one (SUBF_DUMP_PARS) to NULL.
*/
#define ubf_data_dump_puts_default(d,l)			\
			ubf_data_dump_puts ((const char *) d, l, NULL)

#endif														// Of #ifdef nix.

/*
	Simple hex dump. This is what you need/want.
*/

enum enDataDmpWidth
{
	enDataDumpWidth16,
	enDataDumpWidth32
};
typedef enum enDataDmpWidth ddumpWidth;

/*
	requiredOutputSizeHexDump

	Returns the required buffer size for a hex dump. The return value
*/
size_t hxdmpRequiredSize		(
		size_t				lenDumpData,					// The length of the data to dump.
		ddumpWidth			width,							// Output width.
		newline_t			nl
								)
;

/*
	hxdmpWriteHexDump

	Stores a hex dump in szOutput. The buffer szOutput points to must be sufficiently large.
	It should have been obtained via a call to hxdmpRequiredSize ().
*/
size_t hxdmpWriteHexDump		(
		char				*szOutput,						// The output.
		const unsigned char	*ccDumpData,					// The data to dump.
		size_t				lenDumpData,					// The length of the data to dump.
		ddumpWidth			width,
		newline_t			nl
								)
;

/*
	test_strhexdump

	Test function.
*/
#ifdef DEBUG
	#ifndef BUILD_STRHEXDUMP_TEST_FNCT
	#define BUILD_STRHEXDUMP_TEST_FNCT
	#endif
#endif
#ifdef BUILD_STRHEXDUMP_TEST_FNCT
	bool test_strhexdump (void);
#else
	#define test_strhexdump()
#endif

EXTERN_C_END

#endif															// Of #ifndef STRHEXDUMP_H.
