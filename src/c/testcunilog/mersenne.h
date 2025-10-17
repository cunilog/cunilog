/****************************************************************************************

	File:		mersenne.h
	Why:		Implements a Mersenne Twister. The code has been taken, with little
				modifications, from https://en.wikipedia.org/wiki/Mersenne_Twister in
				2025-07.
	OS:			As many compilers and platforms as required.
	Author:		Thomas
	Created:	2025-09-29

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-09-29	Thomas			Created, i.e. code moved to its own module.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This code is public domain.
*/

#ifndef U_MERSENNE_TWISTER_H
#define U_MERSENNE_TWISTER_H

/*
	The following code has been taken, with little modifications, from
	https://en.wikipedia.org/wiki/Mersenne_Twister in 2025-07.

	It is used to generate the test pattern for the module ProcessHelper.
	Do NOT use this code for anything else! It is not cryptographically secure.
	The reason why I copied this code from Wikipedia is because the ProcessHelper
	test needs to seed a random number generator (RNG). If rand () and srand (), or
	any other RNG provided by the OS or a library were used for this purpose, there's
	a good chance that the test might interfere with an application that uses the
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
} mersenne_twister_state;


static void initialize_state(mersenne_twister_state* state, uint32_t seed) 
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


static uint32_t random_uint32(mersenne_twister_state* state)
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

#endif														// Of #ifndef U_MERSENNE_TWISTER_H.
