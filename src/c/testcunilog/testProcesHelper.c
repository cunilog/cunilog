/****************************************************************************************

	File		testProcesHelper.c
	Why:		Test for module ProcesHelper.
	OS:			C99
	Created:	2025-07-25

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-07-25	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	The purpose of this module is to provide a playground for testing the function
	CreateAndRunCmdProcessCapture () in module ProcessHelper.
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

#ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS

#include <stdio.h>
#include <stdlib.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
		#include "./membuf.h"
		#include "./strnewline.h"
	#else
		#include "./../dbg/ubfdebug.h"
		#include "./../mem/membuf.h"
		#include "./../string/strnewline.h"
	#endif

	#include "./mersenne.h"

#endif

static uint8_t testProcessHelperGetRndmOctet (mersenne_twister_state *state)
{
	uint32_t n = random_uint32 (state);
	uint8_t u = n & 0xFF;
	return u;
}

static uint16_t testProcessHelperGetRndmWord (mersenne_twister_state *state)
{
	uint32_t n = random_uint32 (state);
	uint16_t u = n & 0xFFFF;
	return u;
}

/*
	Only vertical tab, digits, letters, punctuation marks, number operators, brackets, etc.
	This means ASCII characters 9 (tab), or between 32 (space) and 126 (tilde ~).
*/
static char testProcessHelperGetRndmChar (mersenne_twister_state *state)
{
	unsigned char c = 0;

	while	(
					c != '\t'
				&&	(
						c < ' ' || c > 126
					)
			)
	{
		c = testProcessHelperGetRndmOctet (state);
	}
	return c;
}

static const char *testProcessHelperGetLine	(
						size_t		*pLen,
						mersenne_twister_state	*state,
						uint32_t	uiMaxLen,
						SMEMBUF		*psmb,
						bool		bAddLN
											)
{
	uint32_t ln = random_uint32 (state);
	while (ln > uiMaxLen)
		ln -= uiMaxLen >> 1;
	growToSizeSMEMBUF (psmb, (size_t) ln + MAX_SIZ_LINE_ENDING);
	if (isUsableSMEMBUF (psmb))
	{	// Note that ln could also be 0.
		uint32_t o = 0;
		while (o < ln)
		{
			psmb->buf.pch [o ++] = testProcessHelperGetRndmChar (state);
		}
		if (bAddLN)
			memcpy (psmb->buf.pch + o, ccLineEnding (cunilogNewLineDefault), lnLineEnding (cunilogNewLineDefault) + 1);
		else
			psmb->buf.pch [o] = ASCII_NUL;
		if (pLen)
			*pLen = ln;
		return psmb->buf.pcc;
	}
	return NULL;
}

#ifdef TEST_PROCESS_HELPER_BUILD_TEST_FNCT
	bool TestProcessHelperTestFnct (void)
	{
		bool	b = true;

		uint32_t n1, n2;
		mersenne_twister_state state;
		initialize_state (&state, 19650218UL);
		n1 = random_uint32 (&state);
		initialize_state (&state, 19650218UL);
		n2 = random_uint32 (&state);
		ubf_expect_bool_AND (b, n1 == n2);

		SMEMBUF smb = SMEMBUF_INITIALISER;
		size_t	st;
		initialize_state (&state, 19650218UL);
		const char	*cc = testProcessHelperGetLine (&st, &state, 32, &smb, false);
		ubf_expect_bool_AND (b, 32 >= st);
		ubf_expect_bool_AND (b, NULL != cc);
		SMEMBUF smb2 = SMEMBUF_INITIALISER;
		size_t	st2;
		initialize_state (&state, 19650218UL);
		const char	*cc2 = testProcessHelperGetLine (&st2, &state, 32, &smb2, false);
		ubf_expect_bool_AND (b, 32 >= st2);
		ubf_expect_bool_AND (b, NULL != cc2);
		ubf_expect_bool_AND (b, !memcmp (cc, cc2, st2 + 1));

		// Different seed.
		initialize_state (&state, 7438535);
		st = 0;
		cc = testProcessHelperGetLine (&st, &state, 64, &smb, false);
		ubf_expect_bool_AND (b, 0 != st);
		ubf_expect_bool_AND (b, 64 >= st);
		ubf_expect_bool_AND (b, NULL != cc);
		initialize_state (&state, 7438535);
		st2 = 0;
		cc2 = testProcessHelperGetLine (&st2, &state, 64, &smb2, false);
		ubf_expect_bool_AND (b, 0 != st2);
		ubf_expect_bool_AND (b, 64 >= st2);
		ubf_expect_bool_AND (b, NULL != cc2);
		ubf_expect_bool_AND (b, !memcmp (cc, cc2, st2 + 1));

		initialize_state (&state, 1444444444);
		st = 0;
		cc = testProcessHelperGetLine (&st, &state, 256, &smb, false);
		ubf_expect_bool_AND (b, 0 != st);
		ubf_expect_bool_AND (b, 256 >= st);
		ubf_expect_bool_AND (b, NULL != cc);
		initialize_state (&state, 1444444444);
		st2 = 0;
		cc2 = testProcessHelperGetLine (&st2, &state, 256, &smb2, false);
		ubf_expect_bool_AND (b, 0 != st2);
		ubf_expect_bool_AND (b, 256 >= st2);
		ubf_expect_bool_AND (b, NULL != cc2);
		ubf_expect_bool_AND (b, !memcmp (cc, cc2, st2 + 1));

		// Ok, if we're this far, the RNG and seeding it works.

		return b;
	}
#endif

const char *szTstPrsHlpsExitcode	= "exitcode";
const char *szTstPrsHlpsInput		= "input";
const char *szTstPrsHlpsOutput		= "output";

#ifdef U_TEST_PROCESS_HELPER_BUILD_MAIN
	int main (int argc, char *argv [])
	{
		SMEMBUF	smbOneLine	= SMEMBUF_INITIALISER;
		int		iArg		= 0;
		int		iExitCode	= 0;
		int32_t	uiSeed		= 0;
		int		nLines		= 0;
		int		nLength		= 0;
		int		nInputs		= 0;

		if (argc)
		{	// First argument always goes to stdout.
			fprintf (stdout, "argv [0]: %s\n", argv [iArg]);
			-- argc;
			++ iArg;
		}

		while (argc)
		{	// Then we process our commands.
			if (!strcmp (szTstPrsHlpsExitcode, argv [iArg]))
			{
				-- argc;
				++ iArg;
				if (argc)
				{
					iExitCode = atoi (argv [iArg]);
				} else
					fprintf (stderr, "Missing exit code.\n");
			} else
			if (!strcmp (szTstPrsHlpsInput, argv [iArg]))
			{
				-- argc;
				++ iArg;
				if (argc)
				{
					nInputs = atoi (argv [iArg]);
					for (int i = 0; i < nInputs; ++ i)
					{
						char sz [1024];
						memset (sz, 0, 1024);
						fprintf (stdout, "Input: ");
						char *o = fgets (sz, 1024, stdin);
						if (o)
							fputs (sz, stdout);
						else
							fputs ("Input error.\n", stderr);
					}
				} else
					fputs ("Missing number of input lines.\n", stderr);
			}
			if (!strcmp (szTstPrsHlpsOutput, argv [iArg]))
			{
				-- argc;
				++ iArg;
				if (argc)
				{
					uiSeed = atoi (argv [iArg]);
					-- argc;
					++ iArg;
					if (argc)
					{
						nLines = atoi (argv [iArg]);
						-- argc;
						++ iArg;
						if (argc)
						{
							nLength = atoi (argv [iArg]);
							mt_state state;
							initialize_state (&state, uiSeed);
							for (int i = 0; i < nLines; ++ i)
							{
								size_t		stLen;
								const char	*szOut = testProcessHelperGetLine	(
														&stLen, &state, nLength,
														&smbOneLine, true
																				);
								if (szOut)
									fputs (szOut, stdout);
							}
						} else
							fputs ("Missing max. line length.\n", stderr);
					} else
						fputs ("Missing number of output lines.\n", stderr);
				} else
					fputs ("Missing seed.\n", stderr);
			}
			-- argc;
			++ iArg;
		}
		DONESMEMBUF (smbOneLine);
		fprintf (stdout, "Exiting. Returning %d...\n", iExitCode);
		return iExitCode;
	}
#endif

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
