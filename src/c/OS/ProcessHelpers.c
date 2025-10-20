/****************************************************************************************

	File:		ProcessHelpers.c
	Why:		Functions for creating and handling processes.
	OS:			C99
	Author:		Thomas
	Created:	2025-06-05
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-06-05	Thomas			Created.

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

#ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS

#include <string.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./ProcessHelpers.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE

		#if defined (PLATFORM_IS_WINDOWS)
			#include "./WinAPI_U8.h"
		#elif defined (PLATFORM_IS_POSIX)

		#elif
			#error Not supported
		#endif

		#include "./ubfdebug.h"
		#include "./membuf.h"
		#include "./unref.h"
		#include "./strnewline.h"
		#include "./strmembuf.h"

		#ifdef PROCESS_HELPERS_BUILD_TEST_FNCT

		#endif

	#else

		#if defined (PLATFORM_IS_WINDOWS)
			#include "./Windows/WinAPI_U8.h"
		#elif defined (PLATFORM_IS_POSIX)

		#elif
			#error Not supported
		#endif

		#include "./../dbg/ubfdebug.h"
		#include "./../mem/membuf.h"
		#include "./../pre/unref.h"
		#include "./../string/strnewline.h"
		#include "./../string/strmembuf.h"

		#ifdef PROCESS_HELPERS_BUILD_TEST_FNCT

		#endif

	#endif

#endif

/*
*/
size_t phlpsStdBufSize = PRCHLPS_DEF_EXCESS_BUFFER;

size_t ProcessHelpersSetBufferSize (size_t bufsize)
{
	ubf_assert_non_0 (bufsize);

	size_t prev = phlpsStdBufSize;
	phlpsStdBufSize = bufsize;
	return prev;
}

/*
	Squeezes the executable's name plus all arguments in a single string.
	The executable's name is going to be the first argument.
*/
char *CreateArgsList (const char *szExecutable, int argc, const char *argv [], bool bNoExeArg)
{
	ubf_assert (NULL != szExecutable);

	int		n;
	size_t	r	= 0;
	size_t	l;

	if (!bNoExeArg)
	{
		r += 2;												// For the double quotes.
		r += strlen (szExecutable);
		++ r;												// NUL.
	}
	for (n = 0; n < argc; ++ n)
	{
		if (n)
			++ r;											// For the space between args.
		r += strlen (argv [n]);
	}
	r += 0 == r ? 1 : n ? 1 : 0;							// NUL.
	char *szArgsList = ubf_malloc (r);
	if (szArgsList)
	{
		if (1 == r)
		{
			szArgsList [0] = ASCII_NUL;
			return szArgsList;
		}

		char *wri = szArgsList;

		if (!bNoExeArg)
		{
			*wri ++ = '\"';
			l = strlen (szExecutable);
			memcpy (wri, szExecutable, l);
			wri += l;
			*wri ++ = '\"';
			*wri = ASCII_NUL;
		}
		for (n = 0; n < argc; ++ n)
		{
			if (n || !bNoExeArg)
				*wri ++ = ' ';
			l = strlen (argv [n]);
			memcpy (wri, argv [n], l);
			wri += l;
			*wri = ASCII_NUL;
		}
		ubf_assert (strlen (szArgsList) == r - 1);
		return szArgsList;
	}
	return NULL;
}

char *CreateArgsListFromString (const char *szExecutable, const char *szCmdLine, bool bNoExeArg)
{
	size_t	r	= 0;
	size_t	l;

	if (!bNoExeArg)
	{
		r += 2;												// For the double quotes.
		r += strlen (szExecutable);
		++ r;												// NUL.
	}
	if (szCmdLine)
	{
		r += strlen (szCmdLine);
		++ r;
	}
	r += 0 == r ? 1 : 0;									// NUL.
	char *szArgsList = ubf_malloc (r);
	if (szArgsList)
	{
		if (1 == r)
		{
			szArgsList [0] = ASCII_NUL;
			return szArgsList;
		}

		char *wri = szArgsList;

		if (!bNoExeArg)
		{
			*wri ++ = '\"';
			l = strlen (szExecutable);
			memcpy (wri, szExecutable, l);
			wri += l;
			*wri ++ = '\"';
			*wri = ASCII_NUL;
		}
		l = szCmdLine ? strlen (szCmdLine) : 0;
		if (szCmdLine && l)
		{
			if (!bNoExeArg)
				*wri ++ = ' ';
			memcpy (wri, szCmdLine, l);
			wri += l;
			*wri = ASCII_NUL;
		}
		ubf_assert (strlen (szArgsList) <= r - 1);
		return szArgsList;
	}
	return NULL;
}

void DoneArgsList (char *szArgsList)
{
	if (szArgsList)
		ubf_free (szArgsList);
}

#ifdef PLATFORM_IS_WINDOWS
	typedef struct sPrcHlpsInOutBuf
	{
		SMEMBUF					smb;
		char					*szWrite;
		size_t					lenSmb;
		bool					bIOcomplete;
		bool					bNeedsWait;
		bool					bEOF;
		OVERLAPPED				ovlpd;
		enRCmdCBval				cbretval;
		HANDLE					hEvent;
		DWORD					dwTransferred;
		HANDLE					hDEvent;					// Dummy event.
	} SPRCHLPSINOUTBUF;

	typedef struct ph_sChildHandles
	{
		HANDLE	hChildInpRD;
		HANDLE	hChildInpWR;

		HANDLE	hChildOutRD;
		HANDLE	hChildOutWR;

		HANDLE	hChildErrRD;
		HANDLE	hChildErrWR;
	} PH_SCHILDHANDLES;

	static bool CloseInheritableHandlesForChild (PH_SCHILDHANDLES *ph)
	{
		ubf_assert_non_NULL (ph);

		bool b = true;
		b &= CloseHandle (ph->hChildInpRD);
		b &= CloseHandle (ph->hChildInpWR);
		b &= CloseHandle (ph->hChildOutRD);
		b &= CloseHandle (ph->hChildOutWR);
		b &= CloseHandle (ph->hChildErrRD);
		b &= CloseHandle (ph->hChildErrWR);
		return b;
	}

	/*
		Derived from:
		https://learn.microsoft.com/en-gb/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output?redirectedfrom=MSDN
	*/
	static bool CreateInheritableHandlesForChild (PH_SCHILDHANDLES *ph)
	{
		ubf_assert_non_NULL (ph);

		SECURITY_ATTRIBUTES	saAttr;

		saAttr.nLength				= sizeof (saAttr);
		saAttr.bInheritHandle		= true;
		saAttr.lpSecurityDescriptor	= NULL;

		bool b = true;
		b &= CreatePipeOverlapped	(
				&ph->hChildInpRD, false,
				&ph->hChildInpWR, true,
				&saAttr, 0
									);
		ubf_assert_true (b);
		b &= CreatePipeOverlapped	(
				&ph->hChildOutRD, true,
				&ph->hChildOutWR, false,
				&saAttr, 0
									);
		ubf_assert_true (b);
		b &= CreatePipeOverlapped	(
				&ph->hChildErrRD, true,
				&ph->hChildErrWR, false,
				&saAttr, 0
									);
		ubf_assert_true (b);
		// The child won't write to its input handle, and it won't read from its output handles.
		b &= SetHandleInformation (ph->hChildInpWR, HANDLE_FLAG_INHERIT, 0);	ubf_assert_true (b);
		b &= SetHandleInformation (ph->hChildOutRD, HANDLE_FLAG_INHERIT, 0);	ubf_assert_true (b);
		b &= SetHandleInformation (ph->hChildErrRD, HANDLE_FLAG_INHERIT, 0);	ubf_assert_true (b);
		return b;
	}

	/*
	DWORD DataAvailableOnPipe (HANDLE hPipe)
	{
		DWORD dwAvailable = 0;
		bool b = PeekNamedPipe (hPipe, NULL, 0, NULL, &dwAvailable, NULL);
		UNUSED (b);
		ubf_assert_true (b);
		return dwAvailable;
	}
	*/

	static DWORD avlbleSiz (SPRCHLPSINOUTBUF *pb)
	{
		ubf_assert_non_NULL	(pb);
		ubf_assert_non_NULL	(pb->smb.buf.pcc);
		ubf_assert_non_NULL	(pb->szWrite);
		ubf_assert			(pb->lenSmb + 2 < pb->smb.size);

		size_t s = 0;

		if (pb->smb.size)
		{
			s = pb->smb.size - pb->lenSmb - 2;
		}
		return (DWORD) s & 0xFFFFFFFF;
	}

	static enRCmdCBval callOutCB (SRUNCMDCBINF *pinf, rcmdOutCB cb, uint16_t flags, char *buf, size_t blen, void *pCustom)
	{
		enRCmdCBval	rv			= enRunCmdRet_Continue;
		char		cDummy []	= "";
		char		*pOut		= blen ? buf : cDummy;

		if (cb)
		{
			if (flags & RUNCMDPROC_CALLB_INTOUT)
			{
				if (flags & RUNCMDPROC_CALLB_STDOUT)
					rv = cb (pinf, pOut, blen, pCustom);
			} else
			{	// Implied but not checked: (flags & RUNCMDPROC_CALLB_INTERR)
				if (flags & RUNCMDPROC_CALLB_STDERR)
					rv = cb (pinf, pOut, blen, pCustom);
			}
		}
		return rv;
	}

	static enRCmdCBval callInpCB (SRUNCMDCBINF *pinf, rcmdInpCB cb, uint16_t flags, SPRCHLPSINOUTBUF *psb, void *pCustom)
	{
		enRCmdCBval	rv = enRunCmdRet_Continue;

		size_t stLen = psb->lenSmb;
		if (cb && flags & RUNCMDPROC_CALLB_STDINP)
			rv = cb (pinf, &psb->smb, &stLen, pCustom);
		psb->lenSmb = (DWORD) stLen & 0x00000000FFFFFFFF;
		return rv;
	}

	static void handleHow_AsIs		(
					SRUNCMDCBINF		*pinf,
					SPRCHLPSINOUTBUF	*sb,
					rcmdOutCB			cb,
					uint16_t			flags,
					void				*pCustom
									)
	{
		ubf_assert_non_NULL	(sb);
		ubf_assert_0		(sb->lenSmb);					// Should never change.

		if (enRunCmdRet_Continue == sb->cbretval)
		{
			if (sb->dwTransferred)
			{
				sb->szWrite [sb->dwTransferred]		= ASCII_NUL;
				sb->szWrite [sb->dwTransferred + 1]	= ASCII_NUL;
				sb->cbretval = callOutCB (pinf, cb, flags, sb->szWrite, sb->dwTransferred, pCustom);
				sb->dwTransferred					= 0;
				sb->szWrite	= sb->smb.buf.pch;
			}
		}
	}

	#ifdef _MSC_VER
	#pragma warning (disable: 4706)							// Assignment within condition.
	#endif

	static void handleHow_OneLine	(
					SRUNCMDCBINF		*pinf,
					SPRCHLPSINOUTBUF	*sb,
					rcmdOutCB			cb,
					uint16_t			flags,
					void				*pCustom
									)
	{
		ubf_assert_non_NULL (sb);

		if (enRunCmdRet_Continue == sb->cbretval)
		{
			if (sb->dwTransferred)
			{
				sb->lenSmb += (size_t) sb->dwTransferred;
				size_t	lnNewLn;
				char	*szNewLn;
				while (sb->lenSmb && (szNewLn = strFirstLineEnding_l (sb->smb.buf.pcc, sb->lenSmb, &lnNewLn)))
				{
					size_t lnLine = szNewLn - sb->smb.buf.pch;
					szNewLn [0] = ASCII_NUL;
					sb->cbretval = callOutCB (pinf, cb, flags, sb->smb.buf.pch, lnLine, pCustom);
					if (lnLine + lnNewLn == sb->lenSmb)
					{	// Fully consumed.
						sb->lenSmb = 0;
					} else
					{	// Read data exceeds beyond a single line ending.
						sb->lenSmb -= (DWORD) (lnLine + lnNewLn) & 0x00000000FFFFFFFF;
						memmove	(
							sb->smb.buf.pch,
							szNewLn + lnNewLn,
							sb->lenSmb
								);
					}
				}
				if (sb->lenSmb >= sb->smb.size - 2)
				{
					growToSizeRetainSMEMBUF (&sb->smb, sb->smb.size + phlpsStdBufSize);
				}
				sb->szWrite = sb->smb.buf.pch + sb->lenSmb;
				sb->dwTransferred = 0;
			}
		}
	}

	#ifdef _MSC_VER
	#pragma warning (default: 4706)							// Assignment within condition.
	#endif

	static void handleHow_All	(
					SPRCHLPSINOUTBUF	*sb
								)
	{
		ubf_assert_non_NULL (sb);

		//printf ("-> Data: %p, Length: %zu\n", sb->smb.buf.pch, sb->lenSmb);
		if (sb->dwTransferred)
		{
			sb->szWrite	+= sb->dwTransferred;
			sb->lenSmb	+= sb->dwTransferred;
			sb->dwTransferred = 0;
			if (sb->lenSmb >= sb->smb.size - 2)
			{
				growToSizeRetainSMEMBUF (&sb->smb, sb->smb.size + phlpsStdBufSize);
				sb->szWrite = sb->smb.buf.pch + sb->lenSmb;
			}
		}
		//printf ("<- Data: %p, Length: %zu\n", sb->smb.buf.pch, sb->lenSmb);
	}

	static void handleHow_Finalise		(
					SRUNCMDCBINF		*pinf,
					SPRCHLPSINOUTBUF	*sb,
					rcmdOutCB			cb,
					uint16_t			flags,
					enRCmdCBhow			cbHow,
					void				*pCustom
										)
	{
		if (sb->bEOF && enRunCmdHow_All == cbHow && sb->lenSmb)
		{
			ubf_assert (sb->lenSmb <= sb->smb.size - 2);
			sb->smb.buf.pch [sb->lenSmb]		= ASCII_NUL;
			sb->smb.buf.pch [sb->lenSmb + 1]	= ASCII_NUL;
			callOutCB (pinf, cb, flags, sb->smb.buf.pch, sb->lenSmb, pCustom);
		}
	}

	static void handleHeartbeat		(
					SRUNCMDCBINF		*pinf,
					SRCMDCBS			*pCBs,
					uint16_t			flags,
					void				*pCustom
									)
	{
		if (NULL != pCBs->cbHtb && (RUNCMDPROC_CALLB_HEARTB & flags) && enRunCmdRet_Continue == pinf->rvHtb)
		{
			pinf->rvHtb = pCBs->cbHtb (pinf, pCustom);
		}
	}

	static inline DWORD getLastWindowsError (DWORD *pdw)
	{
		ubf_assert_non_NULL (pdw);

		*pdw = GetLastError ();
		return *pdw;
	}

	void readFromHandle (SPRCHLPSINOUTBUF *sb, HANDLE hdl)
	{
		ubf_assert_non_NULL (sb);
		
		DWORD	dwErr;

		if (!sb->bNeedsWait)
		{
			sb->bIOcomplete = ReadFile (hdl, sb->szWrite, avlbleSiz (sb), &sb->dwTransferred, &sb->ovlpd);
			if (!sb->bIOcomplete && ERROR_IO_PENDING == getLastWindowsError (&dwErr))
				sb->bNeedsWait = true;
			ubf_assert (ERROR_INVALID_USER_BUFFER != getLastWindowsError (&dwErr));
		}
	}

	void writeToHandle (SPRCHLPSINOUTBUF *sb, HANDLE hdl)
	{
		ubf_assert_non_NULL (sb);
		
		DWORD	dwErr;

		if (!sb->bNeedsWait)
		{
			DWORD dwToTransfer =		USE_STRLEN == sb->lenSmb
									?	(DWORD) strlen (sb->smb.buf.pcc)
									:	(DWORD) sb->lenSmb;
			sb->bIOcomplete = WriteFile (hdl, sb->smb.buf.pcc, dwToTransfer, &sb->dwTransferred, &sb->ovlpd);
			sb->lenSmb -= sb->dwTransferred;
			if (!sb->bIOcomplete && ERROR_IO_PENDING == getLastWindowsError (&dwErr))
				sb->bNeedsWait = true;
			ubf_assert (ERROR_INVALID_USER_BUFFER != getLastWindowsError (&dwErr));
		}
	}

	void checkOverlapped (SPRCHLPSINOUTBUF *sb, HANDLE hdl)
	{
		ubf_assert_non_NULL (sb);
		
		DWORD	dwErr;

		if (sb->bNeedsWait)
		{
			sb->bIOcomplete = GetOverlappedResult (hdl, &sb->ovlpd, &sb->dwTransferred, false);
			if (sb->bIOcomplete)
				sb->bNeedsWait = false;
			sb->bEOF = !sb->bIOcomplete && ERROR_HANDLE_EOF == getLastWindowsError (&dwErr);
		}
	}

	static void handleReceiveBuffer		(
					SRUNCMDCBINF		*pinf,
					SPRCHLPSINOUTBUF	*sb,
					rcmdOutCB			cb,
					uint16_t			flags,
					enRCmdCBhow			cbHow,
					void				*pCustom
										)
	{
		ubf_assert_non_NULL (sb);

		if (sb->bIOcomplete && sb->dwTransferred)
		{
			switch (cbHow)
			{
				case enRunCmdHow_AsIs:
				case enRunCmdHow_AsIs0:
					if (sb->bIOcomplete)
						handleHow_AsIs (pinf, sb, cb, flags, pCustom);
					break;
				case enRunCmdHow_OneLine:
					if (sb->bIOcomplete)
						handleHow_OneLine (pinf, sb, cb, flags, pCustom);
					break;
				case enRunCmdHow_All:
					handleHow_All (sb);
					break;
			}
		}
	}

	#define OUTFLGS		(uiCBflags | RUNCMDPROC_CALLB_INTOUT)
	#define ERRFLGS		(uiCBflags | RUNCMDPROC_CALLB_INTERR)

	static bool HandleCommPipes	(
			SRUNCMDCBINF		*pinf,
			PROCESS_INFORMATION	*pi,
			PH_SCHILDHANDLES	*pph,
			SRCMDCBS			*pCBs,
			enRCmdCBhow			cbHow,
			uint16_t			uiCBflags,
			void				*pCustom
								)
	{
		ubf_assert_non_NULL (pi);
		ubf_assert_non_NULL (pi->hProcess);
		ubf_assert_non_NULL (pph);

		bool		bRet				= false;
		bool		bChldExited			= false;

		uint64_t	uiHeartbeatTimeout;
		DWORD		dwHeartbeatTimeOut	= INFINITE;
		if (RUNCMDPROC_CALLB_HEARTB & uiCBflags)
		{
			// Anything above MAXDWORD is currently not supported but planned for future releases.
			uiHeartbeatTimeout = pCBs->uiHtbMS;
			ubf_assert (uiHeartbeatTimeout <= MAXDWORD);
			dwHeartbeatTimeOut = uiHeartbeatTimeout & 0xFFFFFFFF;
		}

		// Anything above MAXDWORD is currently not supported but planned for future releases.
		ubf_assert (pinf->uiChildExitTimeout <= MAXDWORD);
		DWORD		dwChildExitTimeout	= pinf->uiChildExitTimeout & 0xFFFFFFFF;

		// Standard input (stdin) of child process.
		SPRCHLPSINOUTBUF	sbInp;
		memset (&sbInp, 0, sizeof (SPRCHLPSINOUTBUF));
		INITSMEMBUF (sbInp.smb);
		sbInp.cbretval		= enRunCmdRet_Continue;
		sbInp.hEvent		= CreateEvent (NULL, true, false, NULL);
		sbInp.ovlpd.hEvent	= sbInp.hEvent;
		sbInp.dwTransferred	= 0;
		sbInp.hDEvent		= CreateEvent (NULL, true, false, NULL);

		// Standard output (stdout) of child process.
		SPRCHLPSINOUTBUF	sbOut;
		memset (&sbOut, 0, sizeof (SPRCHLPSINOUTBUF));
		INITSMEMBUF (sbOut.smb);
		sbOut.cbretval		= enRunCmdRet_Continue;
		sbOut.hEvent		= CreateEvent (NULL, true, false, NULL);
		sbOut.ovlpd.hEvent	= sbOut.hEvent;
		sbOut.dwTransferred	= 0;
		sbOut.hDEvent		= CreateEvent (NULL, true, false, NULL);

		// Standard error (stderr) of child process.
		SPRCHLPSINOUTBUF	sbErr;
		memset (&sbErr, 0, sizeof (SPRCHLPSINOUTBUF));
		INITSMEMBUF (sbErr.smb);
		sbErr.cbretval		= enRunCmdRet_Continue;
		sbErr.hEvent		= CreateEvent (NULL, true, false, NULL);
		sbErr.ovlpd.hEvent	= sbErr.hEvent;
		sbErr.dwTransferred	= 0;
		sbErr.hDEvent		= CreateEvent (NULL, true, false, NULL);

		if	(
					NULL == sbInp.hEvent
				||	NULL == sbOut.hEvent
				||	NULL == sbErr.hEvent
				||	NULL == sbInp.hDEvent
				||	NULL == sbOut.hDEvent
				||	NULL == sbErr.hDEvent
			)
			goto Escape;

		//growToSizeSMEMBUF (&sbInp.smb, phlpsStdBufSize);
		growToSizeSMEMBUF (&sbOut.smb, phlpsStdBufSize);
		growToSizeSMEMBUF (&sbErr.smb, phlpsStdBufSize);
		sbOut.szWrite = sbOut.smb.buf.pch;
		sbErr.szWrite = sbErr.smb.buf.pch;

		do
		{
			bool bNoWaitRequired;
			do
			{
				// We call the write input handler callback function with every iteration,
				//	provided that the send buffer is empty.
				if (enRunCmdRet_Continue == sbInp.cbretval && 0 == sbInp.lenSmb)
					sbInp.cbretval = callInpCB (pinf, pCBs->cbInp, uiCBflags, &sbInp, pCustom);
				if (isUsableSMEMBUF (&sbInp.smb))
				{
					writeToHandle		(&sbInp, pph->hChildInpWR);
					checkOverlapped		(&sbInp, pph->hChildInpWR);
				}
				if (isUsableSMEMBUF (&sbOut.smb))
				{
					readFromHandle		(&sbOut, pph->hChildOutRD);
					checkOverlapped		(&sbOut, pph->hChildOutRD);
					handleReceiveBuffer	(pinf, &sbOut, pCBs->cbOut, OUTFLGS, cbHow, pCustom);
				} else
					goto Escape;
				if (isUsableSMEMBUF (&sbErr.smb))
				{
					readFromHandle		(&sbErr, pph->hChildErrRD);
					checkOverlapped		(&sbErr, pph->hChildErrRD);
					handleReceiveBuffer	(pinf, &sbErr, pCBs->cbErr, ERRFLGS, cbHow, pCustom);
				} else
					goto Escape;
				bNoWaitRequired = !(sbOut.bNeedsWait && sbErr.bNeedsWait);
			} while (bNoWaitRequired);

			#define PHNHDLS (4)
			HANDLE h [PHNHDLS];
			if (sbOut.bNeedsWait) h [0] = sbOut.hEvent; else h [0] = sbOut.hDEvent;
			if (sbErr.bNeedsWait) h [1] = sbErr.hEvent; else h [1] = sbErr.hDEvent;
			if (sbInp.bNeedsWait) h [2] = sbInp.hEvent; else h [2] = sbInp.hDEvent;
			h [3] = pi->hProcess;
			DWORD dw = WaitForMultipleObjects (PHNHDLS, h, false, dwHeartbeatTimeOut);
			//printf ("Wait complete with %d.\n", dw);
			if (WAIT_TIMEOUT == dw)
			{
				handleHeartbeat (pinf, pCBs, uiCBflags, pCustom);
			} else
			if (WAIT_OBJECT_0 <= dw && dw < WAIT_OBJECT_0 + PHNHDLS)
			{
				switch (dw - WAIT_OBJECT_0)
				{
					// The process has exited/terminated.
					case 3:		sbOut.bEOF = true;
								sbErr.bEOF = true;
								sbInp.bEOF = true;
								break;

					// We don't check which operation completed the wait. We just check all
					//	of them.
					default:	checkOverlapped		(&sbOut, pph->hChildOutRD);
								handleReceiveBuffer	(pinf, &sbOut, pCBs->cbOut, OUTFLGS, cbHow, pCustom);

								checkOverlapped		(&sbErr, pph->hChildErrRD);
								handleReceiveBuffer	(pinf, &sbErr, pCBs->cbErr, ERRFLGS, cbHow, pCustom);

								checkOverlapped		(&sbInp, pph->hChildInpWR);
								writeToHandle		(&sbInp, pph->hChildInpWR);
								break;
				}
			}

			if	(
						enRunCmdRet_Terminate		== sbOut.cbretval
					||	enRunCmdRet_TerminateFail	== sbOut.cbretval
					||	enRunCmdRet_Terminate		== sbErr.cbretval
					||	enRunCmdRet_TerminateFail	== sbErr.cbretval
					||	enRunCmdRet_Terminate		== sbInp.cbretval
					||	enRunCmdRet_TerminateFail	== sbInp.cbretval
					||	enRunCmdRet_Terminate		== pinf->rvHtb
					||	enRunCmdRet_TerminateFail	== pinf->rvHtb
				)
			{
				if (!bChldExited)
					bChldExited = TerminateProcessControlled (pi->hProcess, 0, dwChildExitTimeout);

				if	(
							enRunCmdRet_TerminateFail	== sbOut.cbretval
						||	enRunCmdRet_TerminateFail	== sbErr.cbretval
						||	enRunCmdRet_TerminateFail	== sbInp.cbretval
						||	enRunCmdRet_TerminateFail	== pinf->rvHtb
					)
					goto Escape;
			}
		} while (!sbOut.bEOF && !sbErr.bEOF && !sbInp.bEOF);

		bRet = true;

		handleHow_Finalise (pinf, &sbOut, pCBs->cbOut, OUTFLGS, cbHow, pCustom);
		handleHow_Finalise (pinf, &sbErr, pCBs->cbErr, ERRFLGS, cbHow, pCustom);

		Escape:
		DONESMEMBUF (sbInp.smb);
		DONESMEMBUF (sbOut.smb);
		DONESMEMBUF (sbErr.smb);

		// We better cancel outstanding I/O operations. See
		//	https://learn.microsoft.com/en-us/windows/win32/FileIO/cancelio .
		CancelIo (pph->hChildOutRD);
		CancelIo (pph->hChildErrRD);
		CancelIo (pph->hChildInpWR);

		if (sbInp.hEvent)	CloseHandle (sbInp.hEvent);
		if (sbInp.hDEvent)	CloseHandle (sbInp.hDEvent);
		if (sbOut.hEvent)	CloseHandle (sbOut.hEvent);
		if (sbOut.hDEvent)	CloseHandle (sbOut.hDEvent);
		if (sbErr.hEvent)	CloseHandle (sbErr.hEvent);
		if (sbErr.hDEvent)	CloseHandle (sbErr.hDEvent);

		return bRet;
	}

	static bool HandleCommunication	(
			SRUNCMDCBINF			*pinf,
			PROCESS_INFORMATION		*pi,
			PH_SCHILDHANDLES		*pph,
			SRCMDCBS				*pCBs,
			enRCmdCBhow				cbHow,
			uint16_t				uiCBflags,
			void					*pCustom
									)
	{
		ubf_assert_non_NULL (pi);
		ubf_assert_non_NULL (pi->hProcess);
		ubf_assert_non_NULL (pph);

		SRCMDCBS cbs;
		if (NULL == pCBs)
		{
			ZeroMemory (&cbs, sizeof (SRCMDCBS));
			pCBs = &cbs;
		}

		bool b = HandleCommPipes (pinf, pi, pph, pCBs, cbHow, uiCBflags, pCustom);

		return b;
	}
#endif

#if defined (PLATFORM_IS_WINDOWS)

	bool CreateAndRunCmdProcessCapture	(
			const char				*szExecutable,
			const char				*szCmdLine,
			const char				*szWorkingDir,
			SRCMDCBS				*pCBsHB,				// CB functions and heartbeat interval.
			enRCmdCBhow				cbHow,					// How to call the callback functions.
			uint16_t				uiRCflags,				// One or more of the RUNCMDPROC_
															//	flags.
			void					*pCustom,				// Passed on unchanged to callback
															//	functions.
			uint64_t				uiChildExitTimeout,		// Time in ms to wait for the child to
															//	exit/terminate.
			int						*pExitCode				// Exit code of process.
										)
	{
		if (pExitCode)
			*pExitCode = EXIT_FAILURE;
		if (NULL == szExecutable)
			return false;

		PROCESS_INFORMATION	pi;
		ZeroMemory (&pi, sizeof(pi));

		PH_SCHILDHANDLES	ph;
		bool				b;

		b = CreateInheritableHandlesForChild (&ph);		ubf_assert_true (b);
		if (b)
		{
			STARTUPINFOA		si;
			ZeroMemory (&si, sizeof(si));
			si.cb			= sizeof(si);
			si.hStdInput	= ph.hChildInpRD;
			si.hStdOutput	= ph.hChildOutWR;
			si.hStdError	= ph.hChildErrWR;
			si.dwFlags		= STARTF_USESTDHANDLES;

			//char *szArgsList = CreateArgsList (szExecutable, argc, argv, uiCBflags & RUNCMDPROC_EXEARG_NOEXE);
			char *szArgsList = CreateArgsListFromString	(
									szExecutable, szCmdLine, uiRCflags & RUNCMDPROC_EXEARG_NOEXE
														);
			if (szArgsList)
			{
				SRUNCMDCBINF inf;
				inf.szExecutable		= szExecutable;
				inf.lnExecutable		= strlen (szExecutable);
				inf.szArgsList			= szArgsList;
				inf.lnArgsList			= strlen (szArgsList);
				inf.szWorkingDir		= szWorkingDir;
				inf.lnWorkingDir		= szWorkingDir ? strlen (szWorkingDir) : 0;
				inf.rvHtb				= enRunCmdRet_Continue;
				inf.uiChildExitTimeout	= uiChildExitTimeout;

				DWORD dwCreationFlags	= CREATE_NEW_PROCESS_GROUP;
				b &= CreateProcessU8	(
						szExecutable, szArgsList,			// Command line arguments.
						NULL, NULL, true,					// Inherits our handles.
						dwCreationFlags,					// Creation flags.
						NULL,								// Use our environment block.
						szWorkingDir,						// Child's startup folder.
						&si,								// Pointer to STARTUPINFOA.
						&pi									// Pointer to PROCESS_INFORMATION.
										);

				#ifdef DEBUG
					DWORD dwErr = GetLastError ();
					if (dwErr) {}
				#endif
				inf.childProcessId	= pi.dwProcessId;

				// This function returns false if a callback funciton returned enRunCmdRet_TerminateFail.
				b &= b ? HandleCommunication (&inf, &pi, &ph, pCBsHB, cbHow, uiRCflags, pCustom) : false;

				if (pExitCode)
				{
					DWORD dwExitCode;
					GetExitCodeProcess (pi.hProcess, &dwExitCode);
					*pExitCode = dwExitCode;
				}

				DoneArgsList (szArgsList);
			}
		}

		// Close process and thread handles.				// May have terminated already.
		b &= CloseHandle (pi.hProcess);						// ubf_assert_true (b);
		b &= CloseHandle (pi.hThread);						// ubf_assert_true (b);
		b &= CloseInheritableHandlesForChild (&ph);
		return b;
	}

#elif defined (PLATFORM_IS_POSIX)

	// Taken from somewhere. Won't build and totally untested.
	bool CreateAndRunCmdProcessCapture	(
			const char				*szExecutable,
			const char				*szCmdLine,
			const char				*szWorkingDir,
			SRCMDCBS				*pCBs,
			enRCmdCBhow				cbHow,					// How to call the callback functions.
			uint16_t				uiRCflags,				// One or more of the RUNCMDPROC_
															//	flags.
			void					*pCustom,				// Passed on unchanged to callback
															//	functions.
			int						*pExitCode				// Exit code of process.
										)
	{
		#include <stdio.h>
		#include <stdlib.h>
		#include <unistd.h>

		int main() {
			int pipefd[2];
			if (pipe(pipefd) == -1) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}

			pid_t pid = fork();
			if (pid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if (pid == 0) {  // Child process
				close(pipefd[0]);  // Close unused read end
				dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
				close(pipefd[1]);

				execl("/path/to/executable", "executable", (char *) NULL);
				perror("execl");  // Exec failed
				exit(EXIT_FAILURE);
			} else {  // Parent process
				close(pipefd[1]);  // Close unused write end
				char buffer[128];
				ssize_t count;
				while ((count = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
					buffer[count] = '\0';  // Null terminate
					printf("Output: %s", buffer);
				}
				close(pipefd[0]);
			}

			return 0;
		}
	}

#elif

	// Neither Windows nor POSIX.
	#error Not supported

#endif

#ifdef PROCESS_HELPERS_BUILD_TEST_FNCT
	static unsigned int uiLn = 0;

	enRCmdCBval cbInp (SRUNCMDCBINF *pinf, SMEMBUF *psmb, size_t *plnData, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (pCustom);

		*plnData = SMEMBUFfromStr (psmb, "dir\ndir\nexit\n", USE_STRLEN);
		return enRunCmdRet_Continue;
	}
	enRCmdCBval cbOutWhoAmI (SRUNCMDCBINF *pinf, const char *szData, size_t lnData, void *pCustom)
	{
		ubf_assert_non_NULL	(szData);
		ubf_assert			((void *) 1 == pCustom);
		UNUSED (pinf);
		UNUSED (pCustom);

		if (szData && lnData)
			return enRunCmdRet_Continue;
		return enRunCmdRet_Ignore;
	}
	enRCmdCBval cbErrWhoAmI (SRUNCMDCBINF *pinf, const char *szData, size_t lnData, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (szData);
		UNUSED (lnData);
		UNUSED (pCustom);

		ubf_assert_non_NULL	(szData);
		//ubf_assert			((void *) 1 == pCustom);

		if (szData && lnData)
			return enRunCmdRet_Continue;
		return enRunCmdRet_Ignore;
	}

	enRCmdCBval cbOut (SRUNCMDCBINF *pinf, const char *szData, size_t lnData, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (szData);
		UNUSED (lnData);
		UNUSED (pCustom);

		//printf ("Data: %p, Length: %zu\n", szData, lnData);
		//puts (szData);
		//printf ("Data: %p, Length: %zu\n", szData, lnData);
		return enRunCmdRet_Continue;
	}
	enRCmdCBval cbOutOneLine (SRUNCMDCBINF *pinf, const char *szData, size_t lnData, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (szData);
		UNUSED (lnData);
		UNUSED (pCustom);

		ubf_assert (strlen (szData) == lnData);

		/*
		if (0 == uiLn)
			puts ("");
		*/

		++ uiLn;
		/*
		if (lnData)
			printf ("%5.5d %s\n", uiLn, szData);
		else
			printf ("%5.5d\n", uiLn);
		*/
		//return enRunCmdRet_TerminateFail;
		return enRunCmdRet_Continue;
	}
	enRCmdCBval cbErr (SRUNCMDCBINF *pinf, const char *szData, size_t lnData, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (szData);
		UNUSED (lnData);
		UNUSED (pCustom);

		ASSERT (false);
		return enRunCmdRet_Continue;
	}

	enRCmdCBval cbHtb (SRUNCMDCBINF *pinf, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (pCustom);

		return enRunCmdRet_Continue;
	}

	enRCmdCBval cbHtbClose (SRUNCMDCBINF *pinf, void *pCustom)
	{
		UNUSED (pinf);
		UNUSED (pCustom);

		return enRunCmdRet_Terminate;
	}

	bool ProcessHelpersTestFnct (void)
	{
		bool				b		= true;
		char				*sz;

		sz = CreateArgsList ("exe", 0, NULL, true);
		ubf_expect_bool_AND (b, !memcmp (sz, "", 1));
		ubf_free (sz);
		sz = CreateArgsList ("exe", 0, NULL, false);
		ubf_expect_bool_AND (b, !memcmp (sz, "\"exe\"", 6));
		ubf_free (sz);
		sz = CreateArgsList ("exe exe", 0, NULL, false);
		ubf_expect_bool_AND (b, !memcmp (sz, "\"exe exe\"", 10));
		ubf_free (sz);
		char *args [10];
		args [0] = "arg1";
		args [1] = "arg2";
		args [2] = "arg3";
		sz = CreateArgsList ("exe", 1, args, false);
		ubf_expect_bool_AND (b, !memcmp (sz, "\"exe\" arg1", 11));
		ubf_free (sz);
		sz = CreateArgsList ("exe", 1, args, true);
		ubf_expect_bool_AND (b, !memcmp (sz, "arg1", 5));
		ubf_free (sz);
		sz = CreateArgsList ("exe", 2, args, true);
		ubf_expect_bool_AND (b, !memcmp (sz, "arg1 arg2", 10));
		ubf_free (sz);
		sz = CreateArgsList ("exe", 3, args, true);
		ubf_expect_bool_AND (b, !memcmp (sz, "arg1 arg2 arg3", 15));
		ubf_free (sz);
		sz = CreateArgsList ("exe", 2, args, false);
		ubf_expect_bool_AND (b, !memcmp (sz, "\"exe\" arg1 arg2", 16));
		ubf_free (sz);
		sz = CreateArgsList ("exe", 3, args, false);
		ubf_expect_bool_AND (b, !memcmp (sz, "\"exe\" arg1 arg2 arg3", 21));
		ubf_free (sz);

		SRCMDCBS cbs;
		cbs.cbInp = cbInp;
		cbs.cbOut = cbOutOneLine;
		cbs.cbErr = cbErr;

		uint16_t cbflgs	=		RUNCMDPROC_CALLB_STDINP
							|	RUNCMDPROC_CALLB_STDOUT
							|	RUNCMDPROC_CALLB_STDERR;

		const char *argv [10];
		argv [0] = "/C DIR";

		#if defined (PLATFORM_IS_WINDOWS)

			char szSystemFolder [512];
			UINT uiw = GetSystemDirectoryU8 (szSystemFolder, 512);
			if (uiw > 512 - 1)
			{	// Buffer too small.
				ubf_assert_msg (false, "Increase static buffer of currently 512 octets! It's only for tests.");
				return false;
			}

			//char *szURL = "https://raw.githubusercontent.com/cunilog/cunilog/refs/heads/master/src/c/combined/cunilog_combined.c";
			char szArgs [1024];
			//snprintf (szArgs, 1024, "%s --silent --show-error", szURL);
			snprintf (szArgs, 1024, "/C dir");
			cbs.cbOut = cbOut;

			char szCmd [2056];

			//cunilog_printf ("Retrieving log file from \"%s\"...\n", szURL);
			/*
			b &= CreateAndRunCmdProcessCaptureStdout	(
					"C:\\Windows\\System32\\cmd.exe",
					szArgs, NULL,
					&cbs, enRunCmdHow_All, cbflgs, NULL
														);
			*/

			snprintf (szArgs, 1024, "/C type ..\\..\\..\\..\\src\\def\\libcunilog.def");
			snprintf (szArgs, 1024, "/C type ..\\..\\..\\..\\src\\c\\combined\\cunilog_combined.c");
			//snprintf (szArgs, 1024, "/C type testcunilog.vcxproj");
			
			snprintf (szCmd, 2048, "%s%s", szSystemFolder, "cmd.exe");

			int iExitCode;

			/*	This doesn't work anymore, as the Windows accessories now create
				a new process from the executables in C:\Program files\WindowsApps.

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\notepad.exe",
					"", NULL,
					&cbs, enRunCmdHow_All, cbflgs, NULL, 10000, &iExitCode
														);
			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\calc.exe",
					"", NULL,
					&cbs, enRunCmdHow_All, cbflgs, NULL, 10000, &iExitCode
														);
			*/

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					szArgs, NULL,
					&cbs, enRunCmdHow_All, cbflgs, NULL, 1000, &iExitCode
														);

			cbs.cbOut = cbOutOneLine;
			snprintf (szArgs, 1024, "/C type ..\\..\\..\\..\\src\\def\\libcunilog.def");
			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					szArgs, NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, NULL, 1000, &iExitCode
														);

			uiLn = 0;
			snprintf (szArgs, 1024, "/C type ..\\..\\..\\..\\src\\c\\combined\\cunilog_combined.c");
			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					szArgs, NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, NULL, 1000, &iExitCode
														);


			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					"/C dir", NULL,
					&cbs, enRunCmdHow_All, cbflgs, NULL, 1000, &iExitCode
														);

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					"/C dir", NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, NULL, 1000, &iExitCode
														);

			cbs.cbOut = cbOutWhoAmI;
			cbs.cbErr = cbErrWhoAmI;
			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\whoami.exe",
					"", NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, (void *) 1, 1000, &iExitCode
														);
			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\whoami.exe",
					"some argument that fails whoami", NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, (void *) 1, 1000, &iExitCode
														);

			cbs.cbOut = cbOut;

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					"/C dir", NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, NULL, 1000, &iExitCode
														);

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\whoami.exe",
					"", NULL,
					&cbs, enRunCmdHow_AsIs, cbflgs, NULL, 1000, &iExitCode
														);

			cbs.cbOut = cbOut;

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\whoami.exe",
					"", NULL,
					&cbs, enRunCmdHow_OneLine, cbflgs, NULL, 1000, &iExitCode
														);

			b &= CreateAndRunCmdProcessCapture	(
					"C:\\Windows\\System32\\cmd.exe",
					"/C dir", NULL,
					&cbs, enRunCmdHow_All, cbflgs, NULL, 1000, &iExitCode
														);

			// Enable heartbeat.
			cbs.cbHtb	= cbHtb;
			cbs.cbHtb	= cbHtbClose;
			cbs.uiHtbMS	= 15000;
			cbflgs |= RUNCMDPROC_CALLB_HEARTB;
			cbflgs |= RUNCMDPROC_EXEARG_NOEXE;

			/*
				Wouldn't work if not installed.

			// Should stay open for some time.
			b &= CreateAndRunCmdProcessCapture	(
					//"C:\\Windows\\System32\\notepad.exe",
					"C:\\Program Files\\Jellyfin\\Server\\jellyfin.exe",
					"",
					"C:\\Program Files\\Jellyfin",
					&cbs, enRunCmdHow_All, cbflgs, NULL, 10000, &iExitCode
														);
			*/

		#elif defined (PLATFORM_IS_POSIX)

			b &= CreateAndRunProcessCaptureStdout	(
					"whoami",
					1, argv, NULL,
					&cbs, enRunCmdHow_AsIs, cbflgs, NULL, &iExitCode
													);

		#elif
			b = false;
		#endif
		//ubf_expect_true (b);

		return b;
	}
#endif

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_PROCESS_HELPERS.
