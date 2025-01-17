/****************************************************************************************

	File:		strhexdump.c
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
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024 Thomas

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

#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./strhexdump.h"
	#include "./strnewline.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./ubfcharscountsandchecks.h"
		#include "./strhex.h"
	#else
		#include "./../dbg/ubfdebug.h"
		#include "./../string/ubfcharscountsandchecks.h"
		#include "./../string/strhex.h"
	#endif

#endif

#ifdef BUILD_STRHEXDUMP_TEST_FNCT
	#include <stdio.h>
#endif

// The standard SUBF_DUMP_PARS structure. It is used if the parameter sDumpPars is NULL.
#ifdef DEBUG
SHEX_DUMP_PARS		sdp_default	=	{
						cunilogNewLineDefault,
						NULL, 0,				// The header ccHeader.
						NULL,					// No line start.
						0,						// Length of the line start.
						(size_t) -1,			// Value added to the offset. In the debug version we're outputting
												//	the data's address.
						8,						// The width of the offset in digits.
						": ",					// The separator between offset and values.
						2,						// Its length.
						16,						// The default line width, i.e the amount of data bytes to display.
						1,						// The width of a value in octets (bytes).
						" ",					// The value separator.
						1,						// Its length.
						"-",					// The value separator between the first and the second half of the values.
						1,
						" ",					// ASCII display text separator.
						1,
						".",					// Unprintable character.
						1,
						"  ",					// Fill string if the data is shorter than a line boundary (value).
						2,
						" ",					// Fill character if the data doesn't fit a line boundary (ASCII display text).
						1,
						STR_DATA_DUMP_OPTS_NONE,
						0						// No error.
									};
#else
SHEX_DUMP_PARS		sdp_default	=	{
						cunilogNewLineDefault,
						NULL, 0,				// The header ccHeader.
						NULL,					// No line start.
						0,						// Length of the line start.
						0,						// Value added to the offset.
						4,						// The width of the offset in digits.
						": ",					// The separator between offset and values.
						2,						// Its length.
						16,						// The default line width, i.e the amount of data bytes to display.
						1,						// The width of a value in octets (bytes).
						" ",					// The value separator.
						1,						// Its length.
						"-",					// The value separator between the first and the second half of the values.
						1,
						" ",					// ASCII display text separator.
						1,
						".",					// Unprintable character.
						1,
						"  ",					// Fill string if the data is shorter than a line boundary (value).
						2,
						" ",					// Fill character if the data doesn't fit a line boundary (ASCII display text).
						1,
						STR_DATA_DUMP_OPTS_NONE,
						0						// No error.
									};
#endif

void ubf_data_dump_def_SUBF_DUMP_PARS (SHEX_DUMP_PARS *s)
{
	ubf_assert (NULL != s);

	memcpy (s, &sdp_default, sizeof (SHEX_DUMP_PARS));
}

static const char *szLineEndingFromSHEX_DUMP_PARS (SHEX_DUMP_PARS *pd)
{
	ubf_assert_non_NULL (pd);

	return ccLineEnding (pd->le);
}

static size_t lnLineEndingFromSHEX_DUMP_PARS (SHEX_DUMP_PARS *pd)
{
	ubf_assert_non_NULL (pd);

	return lnLineEnding (pd->le);
}

void writeOffsetQword (unsigned char *ucOut, SHEX_DUMP_PARS *sdp, uint64_t uiValue)
{
	if (sdp->uiOptions & STR_DATA_DUMP_OPTS_OFFS_USE_BLANKS)
	{
		ubf_hex_str_blank_from_qword	(		// Use leading blanks in the offset.
				(char *) ucOut,
				sdp->uiOffsetWidth,
				uiValue
										);
	} else
	{
		ubf_hex_str_zero_from_qword		(
				(char *) ucOut,				// Use leading zeros in the offset.
				sdp->uiOffsetWidth,
				uiValue
										);
	}
}

size_t widthOfValues (SHEX_DUMP_PARS *pdp, SHEX_DUMP_SAN *pob)
{
	ubf_assert_non_NULL (pdp);
	ubf_assert (0 < pdp->uinValues);

	size_t widthOfValues = pob->lenDispSeparator;

	/*
		xx|xx|xx|xx|xx|xx:	One separator less than values.
	*/
	size_t widthOfSepars = pdp->uinValues * pob->lenValSeparator - pob->lenValSeparator;
	if (pdp->uinValues > 1)
	{	// Remove one separator and add the separator that splits the values in half instead.
		widthOfSepars -= pob->lenValSeparator;
		widthOfSepars += pob->lenHalfLineSep;
	}
	if (pdp->uiOptions & STR_DATA_DUMP_OPTS_BINARY)
	{	// Binary format. Every octet requires 8 characters.
		widthOfValues = (size_t) pdp->uinValues * 8;
	} else
	if (pdp->uiOptions & STR_DATA_DUMP_OPTS_DECIMAL)
	{	// Decimal format. Every octet requires 3 characters (000...255).
		widthOfValues = (size_t) pdp->uinValues * 3;
	} else
	{	// Hexadecimal format. Every octet requires 2 characters.
		widthOfValues = (size_t) pdp->uinValues * 2;
	}
	return widthOfValues + widthOfSepars;
}

static size_t widthOfDisplay (SHEX_DUMP_PARS *pdp)
{
	ubf_assert_non_NULL (pdp);
	ubf_assert (0 < pdp->uinValues);

	// Each octet/byte is displayed as a single ASCII character.
	//	Note that this function only exists in case of future changes,
	//	for instance when several values might be combined.
	return pdp->uinValues;
}

static size_t obtainCorrectedLength (const char *ccStr, size_t stLen)
{
	size_t stRet = 0;

	if (ccStr)
	{
		stRet = USE_STRLEN == stLen ? strlen (ccStr) : stLen;
	}
	return stRet;
}

size_t required_data_dump_size	(
			size_t							stDumpDataLen,	// The length of the data to dump.
			SHEX_DUMP_PARS					*pdp,			// The SUBF_DUMP_PARS structure.
			SHEX_DUMP_SAN					*pob			// Already obtained.
									)
{
	ubf_assert (USE_STRLEN != stDumpDataLen);
	ubf_assert_non_NULL (pdp);
	ubf_assert_non_NULL (pob);

	if (!pob->bInitialised)
	{
		if (pdp->ccHeader)
		{
			/*
				The spec for the header says that an empty (not NULL!) header should produce a
				single line ending. If ccHeader is NULL, no header is used.
			*/
			pob->lenHeader = USE_STRLEN == pdp->lenHeader ? strlen (pdp->ccHeader) : pdp->lenHeader;
			pob->lenHeader += lnLineEndingFromSHEX_DUMP_PARS (pdp);
		} else
			pob->lenHeader = 0;
		/*
			If lenHeader is 0, we don't want a header.
			If lenHeader is equal to a line ending, the header consists of a single line ending.
			Any higher value means a header including line ending.
			Any lower value than a line ending is an error.
		*/
		ubf_assert (0 == pob->lenHeader || lnLineEndingFromSHEX_DUMP_PARS (pdp) <= pob->lenHeader);

		pob->lenOffset			= pdp->uiOffsetWidth;
		pob->lenLineStart		= obtainCorrectedLength (pdp->ccLineStart,		pdp->lenLineStart);
		pob->lenOffsetSep		= obtainCorrectedLength (pdp->ccOffsetSep,		pdp->lenOffsetSep);
		pob->lenValSeparator	= obtainCorrectedLength (pdp->ccValSeparator,	pdp->lenValSeparator);
		pob->lenHalfLineSep		= obtainCorrectedLength (pdp->ccHalfLineSep,	pdp->lenHalfLineSep);
		pob->lenNoMoreDataVal	= obtainCorrectedLength (pdp->ccHalfLineSep,	pdp->lenHalfLineSep);
		pob->lenUnprintable		= obtainCorrectedLength (pdp->ccHalfLineSep,	pdp->lenHalfLineSep);
		pob->lenNoMoreDataDisp	= obtainCorrectedLength (pdp->ccHalfLineSep,	pdp->lenHalfLineSep);
		pob->lenDispSeparator	= obtainCorrectedLength (pdp->ccDisplaySep,		pdp->lenDispSep);
		pob->lenValuesWidth		= widthOfValues (pdp, pob);
		pob->lenOneLine			=	pdp->lenLineStart			+
									pdp->uiOffsetWidth			+
									pob->lenOffsetSep			+
									pob->lenValuesWidth			+
									pob->lenDispSeparator		+
									widthOfDisplay (pdp)		+
									lnLineEndingFromSHEX_DUMP_PARS (pdp);
		pob->bInitialised		= true;
	}

	size_t stRetVal =	pob->lenHeader										+
						(stDumpDataLen / pdp->uinValues * pob->lenOneLine)	+
						(stDumpDataLen % pdp->uinValues * pob->lenOneLine);
	// NUL terminator.
	++ stRetVal;
	return stRetVal;
}

static size_t dump_header (char *ch, SHEX_DUMP_PARS *pd, SHEX_DUMP_SAN *ps)
{
	size_t r = ps->lenHeader;

	if (r)
	{
		size_t l = lnLineEndingFromSHEX_DUMP_PARS (pd);

		// Internal error. See explanation in required_data_dump_length ().
		ubf_assert (r >= l);

		if (l < r)
			memcpy (ch, pd->ccHeader, r - l);
		memcpy (ch + r - l, szLineEndingFromSHEX_DUMP_PARS (pd), l);
	}
	return r;
}

static size_t dump_linestart (char *ch, SHEX_DUMP_PARS *pd, SHEX_DUMP_SAN *ps)
{
	memcpy (ch, pd->ccLineStart, ps->lenLineStart);
	return ps->lenLineStart;
}

static size_t dump_offset (char *ch, SHEX_DUMP_PARS *pd, SHEX_DUMP_SAN *ps)
{
	asc_hex_zero_from_qword (ch, pd->uiOffsetWidth, ps->stNextOffset);
	ch += pd->uiOffsetWidth;
	memcpy (ch, pd->ccOffsetSep, ps->lenOffsetSep);
	ps->stNextOffset += pd->uinValues;
	return pd->uiOffsetWidth + ps->lenOffsetSep;
}

static size_t dumpTextIn (char *dest, const char *source, size_t len)
{
	memcpy (dest, source, len);
	return len;
}

static size_t dumpPrintableChar (char *dest, char c, SHEX_DUMP_PARS *pd, SHEX_DUMP_SAN *ps)
{
	if (ubf_is_printable_ASCII (c))
	{
		*dest = c;
		return 1;
	}
	memcpy (dest, pd->ccUnprintable, ps->lenUnprintable);
	return ps->lenUnprintable;
}

static size_t dump_values (char *ch, SHEX_DUMP_PARS *pd, SHEX_DUMP_SAN *ps)
{
	uint8_t		u2	= pd->uinValues / 2;
	char		*pVal = ch;
	char		*pDsp = ch + ps->lenValuesWidth + ps->lenDispSeparator;

	uint8_t		ui	= 0;
	while (ui ++ < pd->uinValues)
	{
		if (ps->lenValToDumpLeft)
		{	// Value/hex dump.
			asc_hex_from_octet (pVal, ps->ccNxtValToDump [0]);
			pVal += 2;
			ps->lenValToDumpLeft --;
		} else
			pVal += dumpTextIn (pVal, pd->ccNoMoreDataVal, ps->lenNoMoreDataVal);
		if (ui != u2)
		{
			if (ui < pd->uinValues)
				pVal += dumpTextIn (pVal, pd->ccValSeparator, ps->lenValSeparator);
			else
				pVal += dumpTextIn (pVal, pd->ccDisplaySep, ps->lenDispSeparator);
		} else
			pVal += dumpTextIn (pVal, pd->ccHalfLineSep, ps->lenHalfLineSep);
		pDsp += dumpPrintableChar (pDsp, ps->ccNxtValToDump [0], pd, ps);
		++ ps->ccNxtValToDump;
	}
	return pDsp - ch;
}

static size_t dumpLineEnding (char *ch, SHEX_DUMP_PARS *pd)
{
	size_t len = lnLineEndingFromSHEX_DUMP_PARS (pd);
	memcpy (ch, szLineEndingFromSHEX_DUMP_PARS (pd), len);
	return len;
}

size_t ubf_data_dump_SMEMBUF	(
		SMEMBUF				*mbOutput,						// The target SUBF_STRING.
		const char			*ccDumpData,					// The data to dump.
		size_t				lenDumpData,					// The length of the data to dump.
		SHEX_DUMP_PARS		*psDumpPars,					// The SUBF_DUMP_PARS structure.
		SHEX_DUMP_SAN		*pdSanDPars						// Can be carried to the next invokation.
								)
{
	ubf_assert_non_NULL (mbOutput);
	ubf_assert	(
						(NULL == ccDumpData && 0 == lenDumpData)
					||	(USE_STRLEN == lenDumpData && ccDumpData)
					||	(ccDumpData)
				);

	SHEX_DUMP_SAN		ourSan;

	if (NULL == pdSanDPars)
	{
		ourSan.bInitialised = false;
		pdSanDPars = &ourSan;
	}
	lenDumpData	= USE_STRLEN == lenDumpData ? strlen (ccDumpData) : lenDumpData;
	psDumpPars = psDumpPars ? psDumpPars : &sdp_default;
	pdSanDPars->stNextOffset = (size_t) -1 == psDumpPars->stFirstOffset
								? (size_t) ccDumpData : psDumpPars->stFirstOffset;
	pdSanDPars->ccNxtValToDump = ccDumpData;
	pdSanDPars->lenValToDumpLeft = lenDumpData;

	size_t stRet = 0;
	size_t stReq = required_data_dump_size (lenDumpData, psDumpPars, pdSanDPars);
	growToSizeSMEMBUF (mbOutput, stReq);
	if (isUsableSMEMBUF (mbOutput))
	{
		char *ch = mbOutput->buf.pch;

		ch += dump_header (ch, psDumpPars, pdSanDPars);

		while (pdSanDPars->lenValToDumpLeft)
		{
			ch += dump_linestart	(ch, psDumpPars, pdSanDPars);
			ch += dump_offset		(ch, psDumpPars, pdSanDPars);
			ch += dump_values		(ch, psDumpPars, pdSanDPars);
			ch += dumpLineEnding	(ch, psDumpPars);
		}
		*ch = '\0';
		stRet = ch - mbOutput->buf.pch;

		// Return value and prepared buffer should be identical, apart
		//	from the NUL that's missing in the return value.
		ubf_assert (stReq == stRet + 1);
	}
	return stRet;
}

#ifdef nix
/*
bool ubf_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
						)
{
	SUBF_STRING		s		= SUBF_STRING_INITIALISER;
	BOOL			b;

	ubf_assert (NULL != chDumpData);
	ubf_assert (0 != stDumpDataLen);
	if (chDumpData && stDumpDataLen)
	{
		b = ubf_data_dump_SUBF_STRING (&s, chDumpData, stDumpDataLen, sDumpPars, FALSE);
		if (b)
			ubf_puts (s.buf);
		UBF_FREE_SUBF_STRING (s);
	} else
		b = FALSE;
	fflush (stdout);
	return b;
}

#ifdef DEBUG
	bool ubf_debug_data_dump_puts	(
							const char			*chDumpData,	// The data to dump.
							size_t				stDumpDataLen,	// The length of the data to dump.
							SHEX_DUMP_PARS		*sDumpPars		// The SUBF_DUMP_PARS structure.
									)
	{
		return ubf_data_dump_puts (chDumpData, stDumpDataLen, sDumpPars);
	}
#endif
*/

#endif

/*
	Some tests.
*/
#ifdef BUILD_STRHEXDUMP_TEST_FNCT
	bool test_strhexdump (void)
	{
		bool	bRet = false;
		size_t	st1, st2;

		SMEMBUF	buf = SMEMBUF_INITIALISER;
		SHEX_DUMP_SAN	s;
		s.bInitialised = false;

		const char ccDump [] = "01ABCDEFGHIJKLMN";
		size_t lnDump = sizeof (ccDump) - 1;

		st1 = required_data_dump_size (lnDump, &sdp_default, &s);
		st2 = ubf_data_dump_SMEMBUF (&buf, ccDump, lnDump, NULL, &s);
		ubf_assert (st1 == st2 + 1);
		puts (buf.buf.pch);
		return bRet;
	}
#endif
