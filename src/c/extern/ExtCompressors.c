/****************************************************************************************

	File:		ExtCompressors.c
	Why:		Interface module/unit for external compressors.
	OS:			POSIX, Windows.
	Author:		Thomas
	Created:	2024-11-01

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-11-01	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024-2026 Thomas

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

	#include "./ExtCompressors.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#include "./miniz.h"
		#include "./pragmaMinizc.c"
		#include "./miniz.c"
		#include "./pragmaDefault.c"

		#include "./ArrayMacros.h"
		#include "./ubfdebug.h"
		#include "./cunilogstructs.h"

		#ifdef PLATFORM_IS_WINDOWS
			#include "./WinAPI_U8.h"
		#else
		#endif

	#else

		#include "./miniz/miniz.h"
		#include "./../pre/pragmaMiniz.c"
		#include "./miniz/miniz.c"
		#include "./../pre/pragmaDefault.c"

		#include "./../pre/ArrayMacros.h"
		#include "./../dbg/ubfdebug.h"
		#include "./../cunilog/cunilogstructs.h"

		#ifdef PLATFORM_IS_WINDOWS
			#include "./../OS/Windows/WinAPI_U8.h"
		#else
		#endif

	#endif
	
#endif


/*
	See https://en.wikipedia.org/wiki/Gzip .
*/
static const unsigned char ccGzipHeader [10] =
{
	0x1F, 0x8B,				// ID1 and ID2: Magic number.
	0x08,					// CM: Compression method. Must be 8 (Deflate).
	0x00,					// FLG: No flags.
	0x00, 0x00, 0x00, 0x00,	// MTIME: No last modified time.
	0x02,					// XFL: Max compression (level 9)
	0xFF					// OS: Unknown
};

/*
	The deflated (compressed) file consists of:
	
		ccGzipHeader
	+	compressed data
	+	CRC32 of uncompressed data
	+	size of uncompressed data modulo 2^32
*/

static inline bool openFileForReading (CUNILOG_LOGFILE *pclf, const char *szFileName)
{
	ubf_assert_non_NULL	(pclf);
	ubf_assert_non_NULL	(szFileName);

	#ifdef PLATFORM_IS_WINDOWS
		pclf->hLogFile = CreateFileU8long	(
							szFileName,
							OPEN_EXISTING,
							FILE_SHARE_DELETE, // | FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING,
							FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN,
							NULL
											);
		return INVALID_HANDLE_VALUE != pclf->hLogFile;
	#else
		pclf->fd = open (szFileName, O_RDONLY | O_LARGEFILE | O_DIRECT);
		if (pclf->fd < 0)
			return false;
		if (flock(fd, LOCK_EX | LOCK_NB) < 0)
		{
			close (pclf->fd);
			pclf->fd = -1;
			return false;
		}
		return true;
	#endif
}

static inline bool openFileForOverWriting (CUNILOG_LOGFILE *pclf, const char *szFileName)
{
	ubf_assert_non_NULL	(pclf);
	ubf_assert_non_NULL	(szFileName);

	#ifdef PLATFORM_IS_WINDOWS
		// It seems we can't have FILE_APPEND_DATA and CREATE_ALWAYS at the same time.
		//	This creates a system error code 87 (invalid paramter).
		pclf->hLogFile	=	CreateFileU8long	(
								szFileName,
								GENERIC_WRITE,
								0, //FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
								NULL, CREATE_ALWAYS,
								FILE_FLAG_NO_BUFFERING,
								NULL
											);
		if (INVALID_HANDLE_VALUE == pclf->hLogFile)
		{
			DWORD dw = GetLastError ();
			char msg [128];
			GetWinErrorTextU8 (msg, 128, dw);
		}
		return INVALID_HANDLE_VALUE != pclf->hLogFile;
	#else
		Pclf->fd = open (szFileName, O_WRONLY | O_CREAT | O_LARGEFILE | O_DIRECT);
		return -1 != pclf->fd;
	#endif
}

static inline void closeFile (CUNILOG_LOGFILE clf)
{
	#ifdef PLATFORM_IS_WINDOWS
		if (INVALID_HANDLE_VALUE != clf.hLogFile)
		{
			CloseHandle (clf.hLogFile);
			clf.hLogFile = INVALID_HANDLE_VALUE;
		}
	#else
		if (-1 !=clf.fd)
		{
			close (clf.fd);
			clf.fd = -1;
		}
	#endif
}

static inline bool readFromFile (uint32_t *pRead, unsigned char *ucBuf, uint32_t toRead, CUNILOG_LOGFILE clf)
{
	ubf_assert_non_NULL	(pRead);
	ubf_assert_non_NULL	(ucBuf);

	#ifdef PLATFORM_IS_WINDOWS
		ubf_assert (sizeof (DWORD) == sizeof (uint32_t));
		if (INVALID_HANDLE_VALUE != clf.hLogFile)
		{
			// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
			uint32_t read;
			if (ReadFile (clf.hLogFile, ucBuf, toRead, (DWORD *) &read, NULL))
			{
				*pRead = read;
				return true;
			}
		}
	#else
		ubf_assert (toRead <= SSIZE_MAX);
		ubf_assert (toRead >= 0);
		if (-1 !=clf.fd)
		{
			ssize_t rd = read (clf.fd, ucBuf, toRead);
			ubf_assert (rd <= UINT32_MAX);
			if (rd >= 0)
			{
				*pRead = (uint32_t) rd;
				return true;
			}
		}
	#endif
	return false;
}

static inline bool writeToFile	(
					uint32_t				*pWritten,
					CUNILOG_LOGFILE			clf,
					const unsigned char		*ucBuf,
					uint32_t				toWrite
								)
{
	ubf_assert_non_NULL	(pWritten);
	ubf_assert_non_NULL	(ucBuf);

	#ifdef PLATFORM_IS_WINDOWS
		ubf_assert (sizeof (DWORD) == sizeof (uint32_t));
		if (INVALID_HANDLE_VALUE != clf.hLogFile)
		{
			uint32_t written;
			if (WriteFile (clf.hLogFile, ucBuf, toWrite, (DWORD *) & written, NULL))
			{
				*pWritten = written;
				return true;
			}
		}
	#else
		ubf_assert (toWrite <= SSIZE_MAX);
		ubf_assert (toWrite >= 0);
		if (-1 !=clf.fd)
		{
			ssize_t wn = write (clf.fd, ucBuf, toWrite);
			ubf_assert (rd <= UINT32_MAX);
			if (wn >= 0)
			{
				*pWritten = (uint32_t) wn;
				return true;
			}
		}
	#endif
	return false;
}

static inline bool moveFilePointerForward (CUNILOG_LOGFILE clf, uint32_t distance)
{
	#ifdef PLATFORM_IS_WINDOWS
		LARGE_INTEGER pos;
		pos.QuadPart = distance;

		bool b;
		b = SetFilePointerEx (clf.hLogFile, pos, NULL, FILE_CURRENT);
		DWORD dw = GetLastError ();
		UNREFERENCED_PARAMETER (dw);
		return b;
	#else
		/*	Not required on POSIX.
		ubf_assert (sizeof (off_t) > sizeof (uint32_t));
		off_t odt = distance;
		off_t off = lseek (clf.fd, odt, SEEK_CUR);
		return (off_t) -1 != off;
		*/
		return true;
	#endif
}

static inline bool truncateFile (CUNILOG_LOGFILE *pclf, const char *szFileName, uint64_t newSize)
{
	ubf_assert_non_NULL	(pclf);

	CloseHandle (pclf->hLogFile);

	pclf->hLogFile	=	CreateFileU8long	(
							szFileName,
							GENERIC_WRITE,
							FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL
										);
	if (INVALID_HANDLE_VALUE != pclf->hLogFile)
	{
		LARGE_INTEGER pos;
		pos.QuadPart = newSize;

		bool b;
		b = SetFilePointerEx (pclf->hLogFile, pos, NULL, FILE_BEGIN);
		DWORD dw = GetLastError ();
		UNREFERENCED_PARAMETER (dw);
		SetEndOfFile (pclf->hLogFile);
		return b;
	}
	return false;
}

static inline bool deleteFile (const char *szFileToDelete)
{
	#ifdef PLATFORM_IS_WINDOWS
		bool b = DeleteFileU8 (szFileToDelete);
		return b;
	#else
		int u = unlink (szFileToDelete);
		return 0 == u;
	#endif
}

#ifdef PLATFORM_IS_WINDOWS
	static inline void *mallocAligned (size_t alignment, size_t size)
	{
		return _aligned_malloc (size, alignment);
	}
#else
	static inline void *mallocAligned (size_t alignment, size_t size)
	{
		void	*pRet = NULL;
		
		if (posix_memalign (&pRet, alignment, size))
			return NULL;
		return pRet;
	}
#endif

#ifdef PLATFORM_IS_WINDOWS
	static inline void freeAligned (void *p)
	{
		_aligned_free (p);
	}
#else
	static inline void freeAligned (void *p)
	{
		free (p);
	}
#endif

static const char szGzipExt []	= ".gz";

// Original name as given by the caller (szOrgName) and deflated name (szZipName).
static inline void storeFileNames	(
						char			*szNames,
						char			*szZipName,
						const char		*szInflatedFile,	size_t lnInflatedFile
									)
{
	char *szOrgName = szNames;
	memcpy (szOrgName, szInflatedFile, lnInflatedFile);
	szOrgName [lnInflatedFile] = '\0';
	memcpy (szZipName, szInflatedFile, lnInflatedFile);
	memcpy (szZipName + lnInflatedFile, szGzipExt, sizeof (szGzipExt));
}

// See https://en.wikipedia.org/wiki/Gzip .
#define GZ_CRC32_ISIZE		(8)

static inline void storeGZ_CRC32_ISIZE (unsigned char *sz, uint32_t uiCRC32t, uint32_t uiTotSiz)
{
	ubf_assert_non_NULL (sz);
	sz [0]	= (unsigned char) ((uiCRC32t & 0xFF)		     );
	sz [1]	= (unsigned char) ((uiCRC32t & 0xFF00)		>>  8);
	sz [2]	= (unsigned char) ((uiCRC32t & 0xFF0000)	>> 16);
	sz [3]	= (unsigned char) ((uiCRC32t & 0xFF000000)	>> 24);

	sz [4]	= (unsigned char) ((uiTotSiz & 0xFF)		     );
	sz [5]	= (unsigned char) ((uiTotSiz & 0xFF00)		>>  8);
	sz [6]	= (unsigned char) ((uiTotSiz & 0xFF0000)	>> 16);
	sz [7]	= (unsigned char) ((uiTotSiz & 0xFF000000)	>> 24);
}

static inline bool storeCRCandSize	(
					z_stream				*pstream,
					uint64_t				*puiTotalOut,
					unsigned char			*ucOutBuf,
					uint32_t				stOutBuf,
					uint32_t				uiCRC32t,
					CUNILOG_LOGFILE			clout,
					uint32_t				uiPhysSectSize
									)
{
	uint32_t		uiWrittenToOutFile;
	uint32_t		uiBeforePadding;

	unsigned char	footer [GZ_CRC32_ISIZE];
	storeGZ_CRC32_ISIZE (footer, uiCRC32t, (uint32_t) pstream->total_in);

	unsigned int avail	= pstream->avail_out;
	unsigned int nfirst	= (avail >= GZ_CRC32_ISIZE) ? GZ_CRC32_ISIZE : avail;
	memcpy (pstream->next_out, footer, nfirst);
	avail				-= nfirst;
	uint32_t uiToWrite	= stOutBuf - avail;
	*puiTotalOut		+= uiToWrite;

	#ifdef PLATFORM_IS_WINDOWS
		uiBeforePadding = uiToWrite;
		uiToWrite = ALIGNED_SIZE (uiToWrite, uiPhysSectSize);

		// Overwrite the padding.
		if (uiBeforePadding != uiToWrite)
			memset (ucOutBuf + uiBeforePadding, 0, uiToWrite - uiBeforePadding);

		// This obviously requires that we're below the size of the buffer.
		ubf_assert (uiToWrite <= stOutBuf);
	#endif

	if (!writeToFile (&uiWrittenToOutFile, clout, ucOutBuf, uiToWrite))
		return false;
	if (uiWrittenToOutFile != uiToWrite)
		return false;

	unsigned int remaining = GZ_CRC32_ISIZE - nfirst;

	/* Was used for testing.
	remaining = 3;
	nfirst = GZ_CRC32_ISIZE - remaining;
	*/

	if (remaining)
	{
		memcpy (ucOutBuf, footer + nfirst, remaining);

		#ifdef PLATFORM_IS_WINDOWS
			uiToWrite = ALIGNED_SIZE (remaining, uiPhysSectSize);

			// Overwrite the padding.
			memset (ucOutBuf + remaining, 0, uiPhysSectSize - remaining);

			// This obviously requires that we're below the size of the buffer.
			ubf_assert (uiToWrite <= stOutBuf);
		#endif

		if (!writeToFile (&uiWrittenToOutFile, clout, ucOutBuf, uiToWrite))
			return false;
		if (uiWrittenToOutFile != uiToWrite)
			return false;
		
		*puiTotalOut += remaining;
	}
	return true;
}

#ifdef PLATFORM_IS_POSIX
	static inline bool GetPhysicalSectorSizeFromFD (CUNILOG_LOGFILE clf, blksize_t *pblksize)
	{
		struct stat	statbuf;

		if (0 == fstat (clf.fd, &statbuf))
		{
			*pblksize = statbuf.st_blksize;
			return true;
		}
		return false;
	}
#endif

bool extCompressFile	(
		const char		*szInflatedFile,
		size_t			lnInflatedFile,
		uint32_t		*pphysicalSectorSize,
		enum encprrmve	compressOrDelete
					)
{
	ubf_assert_non_NULL	(szInflatedFile);
	ubf_assert			(sizeof (DWORD) == sizeof (uint32_t));
	ubf_assert			(10 == sizeof (ccGzipHeader));

	lnInflatedFile = USE_STRLEN == lnInflatedFile ? strlen (szInflatedFile) : lnInflatedFile;

	bool bRet = false;

	// We use a single allocation for both paths.
	char *szNames = malloc	(
									ALIGNED_SIZE (lnInflatedFile + 1, CUNILOG_DEFAULT_ALIGNMENT)
								+	lnInflatedFile + sizeof (szGzipExt)
							);
	if (szNames)
	{
		char *szOrgName = szNames;
		char *szZipName = szNames + ALIGNED_SIZE (lnInflatedFile + 1, CUNILOG_DEFAULT_ALIGNMENT);
		storeFileNames (szNames, szZipName, szInflatedFile, lnInflatedFile);

		CUNILOG_LOGFILE clinp;
		if (!openFileForReading (&clinp, szOrgName))
			goto cant_open_input_file;

		uint32_t uiPhysSectSize;
		if (pphysicalSectorSize && *pphysicalSectorSize)
			uiPhysSectSize = *pphysicalSectorSize;
		else
		{
			bool b;
			#ifdef PLATFORM_IS_WINDOWS
				b = GetPhysicalSectorSizeFromHandle (clinp.hLogFile, (DWORD *) &uiPhysSectSize);
				UNUSED_PARAMETER (b);
			#else
				blksize_t st_blksize;
				b = GetPhysicalSectorSizeFromFD (clinp.fd, &st_blksize);
				uiPhysSectSize = (uint32_t) st_blksize;
			#endif

			if (!b)
				uiPhysSectSize = EXTCOMPRESSORS_DEF_SECT_SIZE;
			if (pphysicalSectorSize)
				*pphysicalSectorSize = uiPhysSectSize;
		}

		CUNILOG_LOGFILE clout;
		if (!openFileForOverWriting (&clout, szZipName))
			goto cant_open_output_file;

		// Our buffers.
		uint32_t uiReadWrite = EXTCOMPRESSORS_DEF_SECT_FACTOR * uiPhysSectSize;
		unsigned char *ucInpBuf = mallocAligned (uiPhysSectSize, uiReadWrite);
		if (NULL == ucInpBuf)
			goto cant_malloc_input_buf;
		unsigned char *ucOutBuf = mallocAligned (uiPhysSectSize, uiReadWrite);
		if (NULL == ucOutBuf)
			goto cant_malloc_output_buf;
		memcpy (ucOutBuf, ccGzipHeader, sizeof (ccGzipHeader));

		uint64_t	uiTotalOut	= sizeof (ccGzipHeader);
		z_stream	stream;
		memset (&stream, 0, sizeof (stream));
		stream.next_in			= ucInpBuf;
		stream.avail_in			= 0;
		stream.next_out			= ucOutBuf		+ sizeof (ccGzipHeader);
		stream.avail_out		= uiReadWrite	- sizeof (ccGzipHeader);

		/*
			See https://www.zlib.net/manual.html .

			"windowBits can also be -8..-15 for raw deflate. In this case, -windowBits
			determines the window size. deflate() will then generate raw deflate data
			with no zlib header or trailer, and will not compute a check value."
		*/
		if (Z_OK != deflateInit2 (&stream, Z_BEST_COMPRESSION, Z_DEFLATED, -15, 9, Z_DEFAULT_STRATEGY))
			goto cant_deflate_init;

		uint32_t	uiReadFromInpFile	= 0;
		uint32_t	uiWrittenToOutFile;
		int			currsts				= Z_OK;
		mz_ulong	ulCRC32				= 0;

		while (true)
		{
			if (0 == stream.avail_in)
			{
				if (readFromFile (&uiReadFromInpFile, ucInpBuf, uiReadWrite, clinp))
				{
					ubf_assert (uiReadFromInpFile <= uiReadWrite);
					moveFilePointerForward (clinp, uiReadFromInpFile);

					stream.next_in		= ucInpBuf;
					stream.avail_in		= uiReadFromInpFile;

					ulCRC32 = mz_crc32 (ulCRC32, ucInpBuf, uiReadFromInpFile);
				}
			}

			mz_ulong muprev = stream.avail_out;
			ubf_assert_non_0 (stream.avail_out);
			currsts = deflate (&stream, uiReadFromInpFile == uiReadWrite ? Z_NO_FLUSH : Z_FINISH);
			ubf_assert (Z_OK == currsts || Z_STREAM_END == currsts);
			uiTotalOut += muprev - stream.avail_out;

			if (0 == stream.avail_out)
			{
				if (writeToFile (&uiWrittenToOutFile, clout, ucOutBuf, uiReadWrite))
				{
					stream.next_out		= ucOutBuf;
					stream.avail_out	= uiReadWrite;
					uiTotalOut			+= uiReadWrite;
					moveFilePointerForward (clout, uiReadWrite);
				}
			}
			if (Z_STREAM_END == currsts)
			{
				deflateEnd (&stream);

				bRet = storeCRCandSize	(
						&stream, &uiTotalOut, ucOutBuf, uiReadWrite,
						(uint32_t) ulCRC32, clout, uiPhysSectSize
										);
				break;
			}
		}
		#ifdef PLATFORM_IS_WINDOWS
			// We got unbuffered I/O. The last chunk was rounded up to sector size.
			truncateFile (&clout, szZipName, uiTotalOut);
		#endif

	cant_deflate_init:
		freeAligned (ucOutBuf);

	cant_malloc_output_buf:
		closeFile (clout);
		freeAligned (ucInpBuf);

	cant_malloc_input_buf:
	cant_open_output_file:
		if (bRet && encompress_delete_source_file == compressOrDelete)
			deleteFile (szOrgName);
		closeFile (clinp);

	cant_open_input_file:
		free (szNames);
	}
	return bRet;
}

#ifdef EXTCOMPRESSORS_BUILD_TEST_FNCT

	bool testExtCompressors (void)
	{
		bool b = true;

		/*
			A quick test for miniz. Compress (deflate) "hello", then decompress (inflate) again.
		*/
		unsigned char cinp [256];
		unsigned char cout [256];

		strcpy ((char *) cinp, "hello");

		// Compress/deflate.
		z_stream	stream;
		memset (&stream, 0, sizeof (stream));
		stream.next_in			= cinp;
		stream.avail_in			= 5;
		stream.next_out			= cout;
		stream.avail_out		= 256;

		if (Z_OK != deflateInit (&stream, 9))
			ubf_assert (false);
		int stat;
		stat = deflate (&stream, Z_FINISH);
		if (Z_STREAM_END == stat)
			deflateEnd (&stream);
		uint32_t len = stream.total_out;

		/*
		puts ("");
		printf("len = %u\n", len);
		for (unsigned i = 0; i < len; i++)
			printf("%02X ", (unsigned char)cout[i]);
		printf("\n");
		puts ("");
		*/

		// Decompress/inflate.
		memset (&stream, 0, sizeof (stream));
		stream.next_in			= cout;
		stream.avail_in			= len;
		stream.next_out			= cinp;
		stream.avail_out		= 256;
		memset (cinp, 0, 256);
		if (Z_OK != inflateInit (&stream))
			ubf_assert (false);
		stat = inflate (&stream, Z_FINISH);
		if (Z_STREAM_END == stat)
			inflateEnd (&stream);
		ubf_assert_bool_AND (b, !memcmp (cinp, "hello", 5));
		/*
			End of quick test for miniz.
		*/

		//uint32_t physSectSize = 0;
		//b &= compressFile ("C:\\temp\\miniztest.txt", USE_STRLEN, &physSectSize, encompress_dont_delete_source);
		//b &= compressFile ("C:\\temp\\hello.txt", USE_STRLEN, &physSectSize, encompress_dont_delete_source);
		return b;
	}

#endif
