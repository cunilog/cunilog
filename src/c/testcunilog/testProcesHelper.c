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

#endif

/*
	The following code has been taken, without intentional modifications, from
	https://en.wikipedia.org/wiki/Mersenne_Twister in 2025-07.

	It is used to generate the test pattern for the module ProcessHelper.
	Do NOT use this code for anything else! It is not cryptographically secure.
	The reason why I copied this code from Wikipedia is because the ProcessHelper
	test needs to seed a random number generator (RNG). If rand () and srand (), or
	any other RNG provided by the OS or a library were used for this purpose, there's
	a good chance that the test could interfere with an application that uses the
	same RNG in other places.
*/
#include <stdint.h>

#define n 624
#define m 397
#define w 32
#define r 31
#define UMASK (0xffffffffUL << r)
#define LMASK (0xffffffffUL >> (w-r))
#define a 0x9908b0dfUL
#define u 11
#define s 7
#define t 15
#define l 18
#define b 0x9d2c5680UL
#define c 0xefc60000UL
#define f 1812433253UL

typedef struct
{
	uint32_t state_array[n];         // the array for the state vector 
	int state_index;                 // index into state vector array, 0 <= state_index <= n-1   always
} mt_state;


static void initialize_state(mt_state* state, uint32_t seed) 
{
	uint32_t* state_array = &(state->state_array[0]);
	
	state_array[0] = seed;                          // suggested initial seed = 19650218UL
	
	for (int i=1; i<n; i++)
	{
		seed = f * (seed ^ (seed >> (w-2))) + i;    // Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
		state_array[i] = seed; 
	}
	
	state->state_index = 0;
}


static uint32_t random_uint32(mt_state* state)
{
	uint32_t* state_array = &(state->state_array[0]);
	
	int k = state->state_index;      // point to current state location
									 // 0 <= state_index <= n-1   always
	
//  int k = k - n;                   // point to state n iterations before
//  if (k < 0) k += n;               // modulo n circular indexing
									 // the previous 2 lines actually do nothing
									 //  for illustration only
	
	int j = k - (n-1);               // point to state n-1 iterations before
	if (j < 0) j += n;               // modulo n circular indexing

	uint32_t x = (state_array[k] & UMASK) | (state_array[j] & LMASK);
	
	uint32_t xA = x >> 1;
	if (x & 0x00000001UL) xA ^= a;
	
	j = k - (n-m);                   // point to state n-m iterations before
	if (j < 0) j += n;               // modulo n circular indexing
	
	x = state_array[j] ^ xA;         // compute next value in the state
	state_array[k++] = x;            // update new state value
	
	if (k >= n) k = 0;               // modulo n circular indexing
	state->state_index = k;
	
	uint32_t y = x ^ (x >> u);       // tempering 
			 y = y ^ ((y << s) & b);
			 y = y ^ ((y << t) & c);
	uint32_t z = y ^ (y >> l);
	
	return z; 
}
/*
	End of code taken from https://en.wikipedia.org/wiki/Mersenne_Twister .
*/
#undef n
#undef m
#undef w
#undef r
#undef UMASK
#undef LMASK
#undef a
#undef u
#undef s
#undef t
#undef l
#undef b
#undef c
#undef f

static uint8_t testProcessHelperGetRndmOctet (mt_state *state)
{
	uint32_t n = random_uint32 (state);
	uint8_t u = n & 0xFF;
	return u;
}

static uint16_t testProcessHelperGetRndmWord (mt_state *state)
{
	uint32_t n = random_uint32 (state);
	uint16_t u = n & 0xFFFF;
	return u;
}

/*
	Only vertical tab, digits, letters, punctuation marks, number operators, brackets, etc.
	This means ASCII characters 9 (tab), or between 32 (space) and 126 (tilde ~).
*/
static char testProcessHelperGetRndmChar (mt_state *state)
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
						mt_state	*state,
						uint32_t	uiMaxLen,
						SMEMBUF		*psmb,
						bool		bAddLN
											)
{
	uint32_t ln = random_uint32 (state);
	while (ln > uiMaxLen)
		ln -= uiMaxLen >> 1;
	growToSizeSMEMBUF (psmb, ln + MAX_SIZ_LINE_ENDING);
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
		mt_state state;
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
