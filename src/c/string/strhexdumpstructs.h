/****************************************************************************************

	File:		strhexdumpstructs.h
	Why:		Structures for data dumps.
	OS:			C99
	Author:		Thomas
	Created:	2024-09-10
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-09-10	Thomas			Created. Based on ubfdumpstructs.h, which is now obsolete.

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

#ifndef STRHEXDUMPSTRUCTS_H
#define STRHEXDUMPSTRUCTS_H

#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strnewline.h"

#endif

// Errors.
#define STR_DATA_DUMP_ERR_NO_ERROR						0
#define STR_DATA_DUMP_ERR_NO_DATA						2		// Either chDumpData is NULL or the
																//	length is 0.
#define STR_DATA_DUMP_ERR_NUM_FORMAT					3		// Only one number system is
																//	possible.
#define STR_DATA_DUMP_ERR_OUT_OF_MEMORY					4		// Not enough space available on
																//	the heap.

// Option flags.
#define STR_DATA_DUMP_OPTS_NONE					0x00000000		// No option. Everything is
																//	default.
#define STR_DATA_DUMP_OPTS_BINARY				0x00000001		// Use binary format for data
																//	instead of hex.
#define STR_DATA_DUMP_OPTS_DECIMAL				0x00000002		// Use decimal format for data
																//	instead of hex.
/*
#define STR_DATA_DUMP_OPTS_NO_FIRST_OFF_SEP		0x00000004		// Suppresses the first separator
																//	(usually a colon) after the
																//	offset.
*/
/*
#define STR_DATA_DUMP_OPTS_NO_LAST_VAL_SEP		0x00000008		// Omit the last value separator.
*/
#define STR_DATA_DUMP_OPTS_OFFS_DECIMAL			0x00000010		// The offset is in decimal.
#define STR_DATA_DUMP_OPTS_NS_INDICATOR_L		0x00000020		// Add an indicator which number
																//	system is used
																//	in lower case.
																//	Uses "h" for hexadecimal,
																//	"b" for binary, and
																//	"d" for decimal.
#define STR_DATA_DUMP_OPTS_NS_INDICATOR_U		0x00000040		// Add an indicator which number
																//	system is used
																//	in upper case.
																//	Uses "H" for hexadecimal,
																//	"B" for binary, and
																//	"D" for decimal.
#define STR_DATA_DUMP_OPTS_HEX_DATA_LOWER		0x00000080		// Show hexadecimal data in
																//	lower case. Default is upper
																//	case.
#define STR_DATA_DUMP_OPTS_OFFS_USE_BLANKS		0x00000100		// Output blanks (" ") in the
																//	offset instead of zeros ("0").
#define STR_DATA_DUMP_OPTS_LINEST_FIRST_ONLY	0x00000200		// The member chLineStart is only
																//	used for the first output
																//	line. All other lines are
																//	filled up with stLineStart
																//	blanks (SCP, ASCII 20h, 32d).

#ifdef __cplusplus
	extern "C" {
#endif

/*
	SHEX_DUMP_PARS
	
	The parameter structure for data dumps.

	A data dump consists of the following characteristics:
	- An optional text provided by the caller that precedes each line of the dump.
		The example from Wikipedia below does not contain such a text.
	- The offset value. The offset values in the example below contain offsets of
		0000, 0010, 0020, and 0030 hexadecimal.
	- The first offset separator. In the example below this is a colon (":").
	- The second offset separator. In the example below this is a space (or blank),
		ASCII 20h, 30d.
	- The data values. The first line of data values in the example below starts with
		57, 69, 6B, 69, etc, in hexadecimal.
	- The data value separators. Each data value in the example below is separated by
		a blank (or space) character, which is ASCII 32d, or 20h. Data value separators
		follow the extracted data. The separator of the last data value may not be
		desired and can therefore be suppressed with the option flag
		STR_DATA_DUMP_OPTS_NO_LAST_VAL_SEP.
	- The display separator. In the example from Wikipedia below the display separator
		is a blank (or space) character (ASCII 20 hex, 32 decimal).
	- The plain display text. In the example below, the plain display text of the first
		dump line is "Wikipedia, the f".
	
	Example of a hex dump, taken from https://en.wikipedia.org/wiki/Hex_dump:

		      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+------ Number of values (uinValues)
		      !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !
		      V  V  V  V  V  V  V  V  V  V  V  V  V  V  V  V
		0000: 57 69 6B 69 70 65 64 69 61 2C 20 74 68 65 20 66  Wikipedia, the f
		0010: 72 65 65 20 65 6E 63 79 63 6C 6F 70 65 64 69 61  ree encyclopedia
		0020: 20 74 68 61 74 20 61 6E 79 6F 6E 65 20 63 61 6E   that anyone can
		0030: 20 65 64 69 74 00 00 00 00 00 00 00 00 00 00 00   edit...........
	^	^   ^ ^ ^                    ^                     ^ ^ ^
	!	!   ! ! !                    !                     ! ! !
	!	!   ! ! !                    !                     ! ! +-- Plain display text.
	!	!   ! ! !                    !                     ! ! 
	!	!   ! ! !                    !                     ! +---- Display separator.
	!	!   ! ! !                    !                     +------ Last data value.
	!	!   ! !                      +---------------------------- Half line separator (ccHalfLineSep).
	!	!   ! ! +------------------------------------------------- First data value separator.
	!	!   ! +--------------------------------------------------- First data value.
	!	!	!
	!	!   +----------------------------------------------------- Offset separator (member ccOffsetSep).
	!	+--------------------------------------------------------- Offset value.
	+------------------------------------------------------------- Line start (member ccLineStart).

	Members of the structure:
	
	le						The line ending/newline character(s) to use. See enum enLineEndings
							in strnewline.h for details. If unsure, use unilogNewLineDefault,
							which is a POSIX line ending of LF only. This works on POSIX platforms
							as well as on Windows 10 and up. Use unilogNewLineSystem or
							unilogNewLineWindows for Windows versions before Windows 10.

	ccHeader				A pointer to a string that serves as header text. A line ending is
							added automatically. If this member is NULL, the member lenHeader also
							needs to be 0, and this does not insert a header at all. To create a
							header that consists of a single line ending only, point ccHeader to
							an empty string ("") and set lenHeader to either 0 or USE_STRLEN.
	
	lenHeader				The length of the buffer ccHeader points to, in octets/bytes.
							If lenHeader is USE_STRLEN, which is (size_t) -1, ccHeader must be
							NUL-terminated and obviously can't contain NUL bytes.

	ccLineStart				An optional text provided that precedes each line of the dump.
							This member can be NULL, if not required/used. Since the member
							stLineStart provides the length of this string, in octets,
							excluding a terminating NUL character, the buffer ccLineStart
							points to does not have to be NUL terminated. If this member
							is NULL, the member lenLineStart also must be 0.
							
	lenLineStart			The length of the optional text that precedes each line of
							the dump. If this member is 0, a call to strlen (ccLineStart) is used
							to obtain its value, which means that ccLineStart must be NUL-
							terminated.
							
	stFirstOffset			An optional value that is added to each offset in the output.
							A value of 0 makes the offset start at 0. The offset in the
							output is placed after a line start (member chLineStart).

	uiError					An error code in case of failure. This member contains one of
							the STR_DATA_DUMP_ERR... constants when one of the functions
							fails. This is the only member that is returned by one of the
							dump functions. All other members are input members, meaning
							the functions read and use their values. A value of
							STR_DATA_DUMP_ERR_NO_ERROR is returned if no error occurred.
							
	uiOffsetWidth			The width of the offset. This value must not be 0.
	
	uiOffsetSep01			This member contains the character placed directly after the
							offset.
	
*/
typedef struct shex_dump_pars
{
	newline_t			le;										// How to represent line endings.

	const char			*ccHeader;								// Header.
	size_t				lenHeader;								// Length of ccHeader.

	const char			*ccLineStart;							// Pointer to a character string
																//	to be inserted at the start
																//	of each line.
	size_t				lenLineStart;							// The length of chLineStart, not
																//	including a terminating NUL
																//	character.

	size_t				stFirstOffset;							// This value is added to the
																//	returned offset. If this member
																//	is set to (size_t) -1, the
																//	pointer value of the data to
																//	dump is used.
	uint8_t				uiOffsetWidth;							// The amount of digits in the offset.

	const char			*ccOffsetSep;							// The separator between the offset
																//	and the values.
	size_t				lenOffsetSep;							// Its length.

	uint8_t				uinValues;								// The width of a data dump line.
																//	This is the amount of values
																//	(usually octets/bytes)
																//	displayed on a single line.

	uint8_t				uiValueSize;							// The width of a single value,
																//	in bytes (octets). Not (yet)
																//	supported. Ignored.

	const char			*ccValSeparator;						// The separator between values.
																//	Default is SPC (20h, 32d).
	size_t				lenValSeparator;						// Its length.

	const char			*ccHalfLineSep;							// The separator between half of
																//	the values.
	uint8_t				lenHalfLineSep;							// Its length.

	const char			*ccDisplaySep;							// The separator between the
																//	values block and the ASCII
																//	display.
	uint8_t				lenDispSep;								// Its length.

	const char			*ccUnprintable;							// Representation of an
																//	unprintable character.
	size_t				lenUnprintable;							//	Its length.

	const char			*ccNoMoreDataVal;						// Representation of a value
																//	when the data
																//	can't fill the last line
																//	(values).
	size_t				lenNoMoreDataVal;						// Its length.
	const char			*ccNoMoreDataDisp;						// Representation when the data
																//	can't fill the last line
																//	(ASCII display text).
	size_t				lenNoMoreDataDisp;						// Its length.

	unsigned int		uiOptions;								// Option flags. See above.
	unsigned int		uiError;								// A more detailed error code on
																//	failure. See above.
} SHEX_DUMP_PARS;

/*
	The structure that holds the values already calculated.

	The member bInitialised is used as an indicator that the function requires initialisation.
	To initialise the structure:

	SHEX_DUMP_SAN	s;
	s.bInitialised = false;

*/
typedef struct shex_dump_san
{
	bool				bInitialised;
	size_t				lenHeader;
	size_t				lenLineStart;
	size_t				lenOffset;
	size_t				lenOffsetSep;
	size_t				lenValSeparator;
	size_t				lenHalfLineSep;
	size_t				lenUnprintable;
	size_t				lenNoMoreDataVal;
	size_t				lenNoMoreDataDisp;
	size_t				lenDispSeparator;
	size_t				lenOneLine;
	size_t				lenValuesWidth;
	size_t				stNextOffset;
	const char			*ccNxtValToDump;
	size_t				lenValToDumpLeft;
} SHEX_DUMP_SAN;

#ifdef __cplusplus
	}
#endif

#endif															// Of #ifndef STRHEXDUMPSTRUCTS_H.
