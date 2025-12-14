/****************************************************************************************

	File:		memstrstr.c
	Created:	?

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2014-03-10	Thomas			This history added.
2016-12-09	Thomas			Definitions for TRUE and FALSE removed.
2019-10-13	Thomas			Include files moved to the header.
2024-05-21	Thomas			Function memstrrchr () fixed.

	The original version of memstrstr () has been taken from
	http://www.koders.com/c/fid2330745E0E8C0A0F5E2CF94799642712318471D0.aspx?s=getopt#L459
	which is buggy and doesn't work under certain circumstances.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "memstrstr.h"

#endif

char *memstrstr (const char *s1, size_t size1, const char *s2, size_t size2)
{
	size_t		count1		= size1;
	size_t		count2		= size2;
	size_t		count3		= 0;
	const char	*s1_ptr		= s1;
	const char	*s2_ptr		= s2;

	if (0 == size2)
		return (char *) s1;
	while (count1 --)
	{
		if (*s1_ptr ++ == *s2_ptr ++)
		{
			if (-- count2 == 0)
				return (char *) (s1_ptr - size2);
			count3 ++;
			continue;
		} else
		{
			if (count3)
			{
				s1_ptr -= count3;
				count1 += count3;
				count3 = 0;
			}
		}
		count2 = size2;
		s2_ptr = s2;
	}
	return NULL;
}

char *memstrstrn (char *s1, size_t size1, char *s2, size_t size2, size_t amount)
{
	char		*chF	= s1;
	char		*chM	= s1 + size1 - 1;		// Max chF.
	size_t		a		= amount;
	size_t		st1		= size1;

	if (amount > size1)
		return NULL;
	while (a --)
	{
		if (chF)
		{
			chF = memstrstr (chF, st1, s2, size2);
			if ((chF) && (chF < chM))
			{
				chF ++;
				st1 = size1 - (size_t)(chF - s1);
			} else
			{
				if (a)
					return NULL;
			}
		} else
			return NULL;
	}
	return chF;
}

size_t memchrreplace (char *s, size_t size, char s1, char s2)
{
	size_t r	= 0;
	size_t o	= 0;

	while (o < size)
	{
		if (s [o] == s1)
		{
			s [o] = s2;
			++ r;
		}
		++ o;
	}
	return r;
}

char *memstrchr (const char *str, size_t len, char character)
{
	while (len && *str != character)
	{
		++ str;
		-- len;
	}
	return (char *) (len && *str == character ? str : NULL);
}

char *memstrrchr (const char *str, size_t len, char character)
{
	const char *sr = str;
	while (len && str [len - 1] != character)
	{
		-- len;
	}
	sr += len ? len - 1 : 0;
	return (char *) (*sr == character ? sr : NULL);
}
