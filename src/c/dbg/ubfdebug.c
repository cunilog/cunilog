/****************************************************************************************

	File:		ubfdebug.c
	Why:		Contains debugging functions.
	OS:			Windows/POSIX
	Author:		Thomas
	Created:	2017-10-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2017-10-24	Thomas			Created.

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

// Windows warnings.
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ubfdebug.h"

	#ifdef UBF_STRINTUINT_USE_CURR_DIR
		#include "./strintuint.h"
	#else
		#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
			#include "./strintuint.h"
		#else
			#include "./../string/strintuint.h"
		#endif
	#endif
	#ifdef UBF_DEBUG_HEX_DUMP
		#include "./ubfdump.h"
	#endif

#endif

#if defined (DEBUG) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		const char	szDbgMsgM01	[]	= "ubf_debug_assert () - Failed \"";
		size_t		lnDbgMsgM01		= sizeof (szDbgMsgM01) - 1;
		const char	szDbgMsgM02 []	= "\" in \"";
		size_t		lnDbgMsgM02		= sizeof (szDbgMsgM02) - 1;
		const char	szDbgMsgM03 []	= "\", line ";
		size_t		lnDbgMsgM03		= sizeof (szDbgMsgM03) - 1;
		const char	szDbgMsgM04 []	= "...";
		size_t		lnDbgMsgM04		= sizeof (szDbgMsgM04) - 1;
		const char	szDbgMsgM05 []	= "ubf_debug_assert () - Testing \"";
		size_t		lnDbgMsgM05		= sizeof (szDbgMsgM05) - 1;
		const char	szDbgMsgM06 []	= "ubf_debug_assert () - \"";
		size_t		lnDbgMsgM06		= sizeof (szDbgMsgM06) - 1;
		const char	szDbgMsgM07 []	= "\" passed.";
		size_t		lnDbgMsgM07		= sizeof (szDbgMsgM07) - 1;
	#endif

	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ubf_debug_assert		(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									)
		{
			char	cMsg [UBF_DEBUG_MSG_STRLEN];
			char	*pMsg;
			char	cNum [UBF_UINT64_SIZE];
			size_t	lNum;

			size_t	lnDebugMessage	= strlen (chDebugMessage);
			size_t	lnFilePath		= strlen (chFilePath);
			size_t	lnTotal			= lnDbgMsgM01 + lnDebugMessage + lnDbgMsgM02
									+ lnFilePath + lnDbgMsgM03 + UBF_UINT64_SIZE
									+ lnDbgMsgM04;
			char	*ch;
			
			if (lnTotal < UBF_DEBUG_MSG_STRLEN)
			{
				ch		= cMsg;
				pMsg	= cMsg;
			} else
			{
				pMsg	= malloc (lnTotal + 1);
				if (NULL == pMsg)
				{	// Ouch!
					_ASSERT (false);
					return;
				}
				ch		= pMsg;
			}

			if (bAssert)
			{

			} else
			{
				ubf_str_from_uint64 (cNum, (uint64_t) uiLineNum);
				lNum = strlen (cNum);
				memcpy (ch, szDbgMsgM01, lnDbgMsgM01);			ch += lnDbgMsgM01;
				memcpy (ch, chDebugMessage, lnDebugMessage);	ch += lnDebugMessage;
				memcpy (ch, szDbgMsgM02, lnDbgMsgM02);			ch += lnDbgMsgM02;
				memcpy (ch, chFilePath, lnFilePath);			ch += lnFilePath;
				memcpy (ch, szDbgMsgM03, lnDbgMsgM03);			ch += lnDbgMsgM03;
				memcpy (ch, cNum, lNum);						ch += lNum;
				memcpy (ch, szDbgMsgM04, lnDbgMsgM04);			ch += lnDbgMsgM04;
				*ch = '\0';

				/*
				strcpy (chMsg, "ubf_debug_assert () - Failed \"");
				strncat (chMsg, chDebugMessage, UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				strncat (chMsg, "\" in \"", UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				strncat (chMsg, chFilePath, UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				strncat (chMsg, "\", line ", UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				strncat (chMsg, cNum, UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				strncat (chMsg, "...", UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				*/

				ubf_debug_puts (pMsg);
				_ASSERT (bAssert);
				/*
				strcpy (chMsg, "ubf_debug_assert () - \"");
				strncat (chMsg, chDebugMessage, UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				strncat (chMsg, "\" passed.", UBF_DEBUG_MSG_STRLEN - strlen (chMsg) - 1);
				ubf_debug_puts (chMsg);
				*/
			}
		}
	#endif

	#if defined (UBF_USE_DBG_ABRT_OUTPUT_FNCTS) || defined (CUNILOG_BUILD_SHARED_LIBRARY)
		void ubf_debug_assert_pass	(
						bool			bAssert,
						const char		*chDebugMessage,
						const char		*chFilePath,
						unsigned int	uiLineNum
									)
		{
			char	cMsg [UBF_DEBUG_MSG_STRLEN];
			char	*pMsg;
			char	cNum [UBF_UINT64_SIZE];
			size_t	lNum;

			size_t	lnDebugMessage	= strlen (chDebugMessage);
			size_t	lnFilePath		= strlen (chFilePath);
			size_t	lnTotal			= lnDbgMsgM05 + lnDebugMessage + lnDbgMsgM02
									+ lnFilePath + lnDbgMsgM03 + UBF_UINT64_SIZE
									+ lnDbgMsgM04;
			char	*ch;
			
			if (lnTotal < UBF_DEBUG_MSG_STRLEN)
			{
				ch		= cMsg;
				pMsg	= cMsg;
			} else
			{
				pMsg	= malloc (lnTotal + 1);
				if (NULL == pMsg)
				{	// Ouch!
					_ASSERT (false);
					return;
				}
				ch		= pMsg;
			}

			ubf_str_from_uint64 (cNum, (uint64_t) uiLineNum);
			lNum = strlen (cNum);

			memcpy (ch, szDbgMsgM05, lnDbgMsgM05);			ch += lnDbgMsgM05;
			memcpy (ch, chDebugMessage, lnDebugMessage);	ch += lnDebugMessage;
			memcpy (ch, szDbgMsgM02, lnDbgMsgM02);			ch += lnDbgMsgM02;
			memcpy (ch, chFilePath, lnFilePath);			ch += lnFilePath;
			memcpy (ch, szDbgMsgM03, lnDbgMsgM03);			ch += lnDbgMsgM03;
			memcpy (ch, cNum, lNum);						ch += lNum;
			memcpy (ch, szDbgMsgM04, lnDbgMsgM04);			ch += lnDbgMsgM04;
			*ch = '\0';

			/*
			strcpy (cMsg, "ubf_debug_assert () - Testing \"");
			strncat (cMsg, chDebugMessage, UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			strncat (cMsg, "\" in \"", UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			strncat (cMsg, chFilePath, UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			strncat (cMsg, "\", line ", UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			strncat (cMsg, cNum, UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			strncat (cMsg, "...", UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			*/

			ubf_debug_puts (pMsg);
			_ASSERT (bAssert);
			
			ch = pMsg;
			memcpy (ch, szDbgMsgM06, lnDbgMsgM06);			ch += lnDbgMsgM06;
			memcpy (ch, chDebugMessage, lnDebugMessage);	ch += lnDebugMessage;
			memcpy (ch, szDbgMsgM07, lnDbgMsgM07);			ch += lnDbgMsgM07;
			*ch = '\0';

			/*
			strcpy (cMsg, "ubf_debug_assert () - \"");
			strncat (cMsg, chDebugMessage, UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			strncat (cMsg, "\" passed.", UBF_DEBUG_MSG_STRLEN - strlen (cMsg) - 1);
			*/

			ubf_debug_puts (pMsg);
		}
	#endif
#endif

#ifdef DEBUG
	void ubf_debug_fill_mem (void *mem, size_t len)
	{
		ubf_assert (NULL != mem);
		ubf_assert (0 != len);
		memset (mem, UBF_ERROR_CHAR, len);
	}
#endif

#ifdef DEBUG
	void ubf_debug_check_mem (char *mem, size_t len)
	{
		size_t	st;

		ubf_assert (NULL != mem);
		ubf_assert (0 < len);
		ubf_assert (UBF_ERROR_CHAR == mem [0]);
		for (st = 0; st < len; ++ len)
		{
			ubf_assert (UBF_ERROR_CHAR == mem [st]);
		}
	}
#endif

#ifdef DEBUG
	void ubf_debug_fill_mem_with (void *mem, char c, size_t len)
	{
		ubf_assert (NULL != mem);
		ubf_assert (0 != len);
		memset (mem, c, len);
	}
#endif

#ifdef DEBUG
	void ubf_debug_check_mem_with (char *mem, char c, size_t len)
	{
		size_t	st;

		ubf_assert (NULL != mem);
		ubf_assert (0 < len);
		ubf_assert (c == mem [0]);
		for (st = 0; st < len; ++len)
		{
			ubf_assert (c == mem [st]);
		}
	}
#endif

#ifdef UBF_DEBUG_HEX_DUMP
	void ubf_debug_hex_dump (const char *chOutput, size_t stOutput)
	{
		ubf_data_dump_puts (chOutput, stOutput, NULL);
	}
#endif

#ifdef UBF_DEVICE_GUI
	#ifdef DEBUG
	void ubf_debug_printf (const char *format, ...)
	{
		va_list		args;
		va_start (args, format);
		vprintf (format, args);
		va_end (args);
		fflush (stdout);
		fflush (stderr);
	}

	void ubf_debug_puts (const char *str)
	{
		//ubf_qdebug_puts (str);
		puts (str);
		fflush (stdout);
		fflush (stderr);
	}
	#endif
#endif
	
#ifdef UBF_DEBUG_USE_PRINTF
	int ubf_debug_printf (const char *format, ...)
	{
		int			iRet;
		va_list		args;

		va_start (args, format);
		iRet = vprintf	(format, args);
		va_end (args);
		return iRet;
	}

	int ubf_debug_puts (const char *str)
	{
		return puts (str);
	}
#endif
