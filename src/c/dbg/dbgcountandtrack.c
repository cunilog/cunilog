/****************************************************************************************

	File:		dbgcountandtrack.c
	Why:		Simple counter debug module
	OS:			-
	Author:		Thomas
	Created:	2025-01-22

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-01-22	Thomas			Created.

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

#include <string.h>
#include <stdlib.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./dbgcountandtrack.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
	#else
		#include "./ubfdebug.h"
	#endif

#endif

#ifndef UNUSED
#define UNUSED(var) (void)(var)
#endif

#ifdef DEBUG
	void cpyDBGcountandtrack (char *szDst, const char *szSrc)
	{
		size_t l = strlen (szSrc);

		if (l < DBGCOUNTANDRACK_MAX_STRING)
			memcpy (szDst, szSrc, l + 1);
		else
		{
			memcpy (szDst, szSrc, DBGCOUNTANDRACK_MAX_STRING - 1);
			szDst [DBGCOUNTANDRACK_MAX_STRING] = ASCII_NUL;
		}
	}
#endif

#ifdef DEBUG
	void setMembers	(
			SDBGCOUNTANDTRACK *t, size_t value, const char *file, const char *func,
			unsigned int line
					)
	{
		t->value = value;
		cpyDBGcountandtrack (t->cSourceFileName,	file);
		cpyDBGcountandtrack (t->cFunctionName,		func);
		t->uiLine = line;
	}
#endif

#ifdef DEBUG
	void resetDBGcountandtrack	(
			SDBGTRACKER *pt, const char *szFile, const char *szFunc, unsigned int line
								)
	{
		cpyDBGcountandtrack (pt->cSourceFileName,	szFile);
		cpyDBGcountandtrack (pt->cFunctionName,		szFunc);
		pt->uiLine	= line;
		pt->value	= 0;
		pt->n		= 0;
		pt->t		= 0;
	}
#endif

#ifdef DEBUG
	void trackDBGcountandtrack	(
			SDBGTRACKER *pt, size_t value, const char *szFile, const char *szFunc,
			unsigned int line
								)
	{
		if (pt->size > pt->n)
		{
			setMembers (&pt->trackers [pt->n], value, szFile, szFunc, line);
			++ pt->n;
		} else
		{
			size_t currSize = sizeof (SDBGCOUNTANDTRACK) * pt->size;
			size_t resvSize = sizeof (SDBGCOUNTANDTRACK) * DBGCOUNTANDTRACK_RESERVE_NUM;
			SDBGCOUNTANDTRACK *t = malloc (currSize + resvSize);
			if (t)
			{
				if (pt->size)
				{
					memcpy (t, pt->trackers, currSize);
					free (pt->trackers);
				}
				pt->trackers = t;
				pt->n = pt->size;
				pt->size += DBGCOUNTANDTRACK_RESERVE_NUM;
				setMembers (&pt->trackers [pt->n], value, szFile, szFunc, line);
				++ pt->n;
			}
		}
		pt->value = value;
	}
#endif

#ifdef DEBUG
	void trackcheckDBGcountandtrack	(
			SDBGTRACKER *pt, size_t value, const char *szFile, const char *szFunc,
			unsigned int line
									)
	{
		UNUSED (value);
		UNUSED (szFile);
		UNUSED (szFunc);
		UNUSED (line);

		if (pt->size > pt->n)
		{
			ubf_assert (value == pt->trackers [pt->t].value);
			++ pt->t;
			return;
		}
		ubf_assert (false);
	}
#endif
