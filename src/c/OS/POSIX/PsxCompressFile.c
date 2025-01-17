/****************************************************************************************

	File:		PsxCompressFile.c
	Why:		Module to compress files on POSIX platforms.
	OS:			POSIX.
	Author:		Thomas
	Created:	2024-10-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2024-10-17	Thomas			Created.

****************************************************************************************/

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

	#include "./PsxCompressFile.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./platform.h"
	#else
		#include "./../../pre/platform.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX

#ifdef CHAT_GPT_NONSENSE
/*
	2024-10-17

	This code supposed to be for the btrfs file system, created by ChatGPT.
	
	Q: "How do I write a C program that compresses a file on the btrfs file system?"

	Obviously, this code is utter nonsense. I shall leave it here for future references
	whenever someone suggests ChatGPT as being a useful tool.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/btrfs.h>
#include <string.h>
#include <stdlib.h>

void enable_compression (const char *path)
{
	int fd = open (path, O_RDWR);
	if (fd < 0)
	{
		perror ("Failed to open file");
		return;
	}

	// Set the compression type to zlib (you can also use lzo or zstd)
	struct btrfs_ioctl_set_compression_args comp_args;
	memset (&comp_args, 0, sizeof (comp_args));
	comp_args.compression = BTRFS_COMPRESS_ZLIB;  // Choose your compression type

	if (ioctl (fd, BTRFS_IOC_SET_COMPRESSION, &comp_args) < 0)
	{
		perror ("Failed to set compression");
		close (fd);
		return;
	}

	printf ("Compression enabled for %s\n", path);
	close (fd);
}

int main (int argc, char *argv [])
{
	if (argc < 2)
	{
		fprintf (stderr, "Usage: %s <file_path>\n", argv [0]);
		return 1;
	}

	enable_compression (argv [1]);
	return 0;
}
#endif


#endif														// Of #ifdef PLATFORM_IS_POSIX.
