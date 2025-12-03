/****************************************************************************************

	File		membuf.c
	Why:		Helpers for memory buffers
	OS:			C99
	Created:	2022-05-11

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-05-11	Thomas			Created.

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

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./membuf.h"
	#include "./ubfmem.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./ubfdebug.h"
	#else
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

void *setToSizeSMEMBUF (SMEMBUF *pb, size_t siz)
{
	ubf_assert_non_NULL (pb);

	if (siz != pb->size)
	{
		unsigned char *p;
		
		if (pb->buf.puc)
		{
			if (siz < pb->size)
			{
				p = ubf_realloc (pb->buf.puc, siz);
				if (NULL == p)
				{
					ubf_free (pb->buf.puc);
					pb->buf.puc = NULL;
					p = ubf_malloc (siz);
				}
			} else
			{
				ubf_free (pb->buf.puc);
				pb->buf.puc = NULL;
				//if (143 == siz) ubf_assert (false);
				p = ubf_malloc (siz);
			}
		} else
		{
			//if (81 == siz) ubf_assert (false);
			p = ubf_malloc (siz);
		}
		if (p)
		{
			pb->buf.puc	= p;
			pb->size	= siz;
			return p;
		} else
		{
			doneSMEMBUF (pb);
		}
	}
	return pb->buf.pvoid;
}

void *growToSizeSMEMBUF (SMEMBUF *pb, size_t siz)
{
	ubf_assert_non_NULL (pb);

	if (siz > pb->size)
	{
		setToSizeSMEMBUF (pb, siz);
	}
	return pb->buf.pvoid;
}

void *growToSizeSMEMBUFreserve (SMEMBUF *pb, size_t siz, size_t res)
{
	ubf_assert_non_NULL (pb);

	if (siz > pb->size)
	{
		setToSizeSMEMBUF (pb, siz + res);
	}
	return pb->buf.pvoid;
}

void *growToSizeSMEMBUF64aligned (SMEMBUF *pb, size_t siz)
{
	ubf_assert_non_NULL (pb);

	siz = ALIGN_SIZE (siz, 64);
	if (siz > pb->size)
	{
		setToSizeSMEMBUF (pb, siz);
	}
	return pb->buf.pvoid;
}

void *growToSizeRetainSMEMBUF (SMEMBUF *pb, size_t siz)
{
	ubf_assert_non_NULL (pb);

	if (siz > pb->size)
	{
		void *n = ubf_realloc (pb->buf.pvoid, siz);
		if (n)
		{
			pb->buf.pvoid	= n;
			pb->size		= siz;
		} else
		{
			n = ubf_malloc (siz);
			if (n)
			{
				memcpy (n, pb->buf.pvoid, pb->size);
				ubf_free (pb->buf.pvoid);
				pb->size = siz;
			} else
			{
				doneSMEMBUF (pb);
			}
		}
	}
	return pb->buf.pvoid;
}

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void freeSMEMBUF (SMEMBUF *pb)
	{
		ubf_assert_non_NULL (pb);
		ubf_assert_non_NULL (pb->buf.pvoid);

		if (pb->buf.pvoid)
		{
			ubf_assert (0 < pb->size);

			ubf_free (pb->buf.pvoid);
		}
		#ifdef DEBUG
			// Anything is Ok apart from 'A'.
			pb->initComplete = '#';
		#endif
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void freeSMEMBUFuncond (SMEMBUF *pb)
	{
		ubf_assert_non_NULL (pb);

		if (pb->buf.pvoid)
			freeSMEMBUF (pb);
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void doneSMEMBUF (SMEMBUF *pb)
	{
		ubf_assert_non_NULL (pb);

		if (pb->buf.pvoid)
		{
			ubf_assert (0 < pb->size);

			ubf_free (pb->buf.pvoid);
			initSMEMBUF (pb);
		}
	}
#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	void doneSMEMBUFuncond (SMEMBUF *pb)
	{
		ubf_assert_non_NULL (pb);

		freeSMEMBUFuncond (pb);
		initSMEMBUF (pb);
	}
#endif

void copySMEMBUF (SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src)
{
	ubf_assert_non_NULL	(dst);
	ubf_assert_non_NULL	(src);
	ubf_assert			(isInitialisedSMEMBUF (dst));
	ubf_assert			(isInitialisedSMEMBUF (src));
	ubf_assert			(dst != src);

	growToSizeSMEMBUF (dst, src->size);
	if (isUsableSMEMBUF (dst))
	{
		memcpy (dst->buf.pch, src->buf.pch, src->size);
	}
}

void copySMEMBUFsiz (SMEMBUF *cunilog_restrict dst, SMEMBUF *cunilog_restrict src, size_t siz)
{
	ubf_assert_non_NULL	(dst);
	ubf_assert_non_NULL	(src);
	ubf_assert			(isInitialisedSMEMBUF (dst));
	ubf_assert			(isInitialisedSMEMBUF (src));
	ubf_assert			(dst != src);
	ubf_assert			(siz <= src->size);

	growToSizeSMEMBUF (dst, siz);
	if (isUsableSMEMBUF (dst))
	{
		memcpy (dst->buf.pch, src->buf.pch, siz);
	}
}

void copySMEMBUFreserve	(
		SMEMBUF		*cunilog_restrict dst,
		SMEMBUF		*cunilog_restrict src,
		size_t		reserve
						)
{
	ubf_assert_non_NULL	(dst);
	ubf_assert_non_NULL	(src);
	ubf_assert			(isInitialisedSMEMBUF (dst));
	ubf_assert			(isInitialisedSMEMBUF (src));
	ubf_assert			(dst != src);

	growToSizeSMEMBUF (dst, src->size + reserve);
	if (isUsableSMEMBUF (dst))
	{
		memcpy (dst->buf.pch, src->buf.pch, src->size);
	}
}
