/****************************************************************************************

	File		cunilogevtcmds.c
	Why:		Cunilog helper functions for event commands.
	OS:			C99
	Created:	2025-02-17

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-02-17	Thomas			Created.

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

	#include "./cunilogstructs.h"
	#include "./cunilogevtcmds.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ArrayMacros.h"
		#include "./platform.h"
		#include "./ubfmem.h"
		#include "./ubfdebug.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/ArrayMacros.h"
		#include "./../pre/platform.h"
		#include "./../mem/ubfmem.h"
		#include "./../dbg/ubfdebug.h"
	#endif

#endif

#ifdef PLATFORM_IS_POSIX
	#include <pthread.h>
#endif

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS

#define SIZCMDENUM	(sizeof (enum cunilogEvtCmd))

typedef struct sculCmdArr
{
	size_t		siz;
} SCULCMDARR;

SCULCMDARR culCmdSizes [] =
{
		SIZCMDENUM + sizeof (bool)							// cunilogCmdConfigUseColourForEcho
	,	SIZCMDENUM + sizeof (cueventsevfmtpy)				// cunilogCmdConfigEventSeverityFormatType
	,	SIZCMDENUM + sizeof (newline_t)						// cunilogCmdConfigCunilognewline
	,	SIZCMDENUM + sizeof (enum cunilogprocesstask)		// cunilogCmdConfigDisableTaskProcessors
	,	SIZCMDENUM + sizeof (enum cunilogprocesstask)		// cunilogCmdConfigEnableTaskProcessors
	,	SIZCMDENUM											// cunilogConfigDisableEchoProcessor
	,	SIZCMDENUM											// cunilogConfigEnableEchoProcessor
	,	SIZCMDENUM + sizeof (cunilogprio)					// cunilogCmdConfigSetLogPriority
};

#ifdef DEBUG
	bool culIsValidCmd (enum cunilogEvtCmd cmd)
	{
		ubf_assert (GET_ARRAY_LEN (culCmdSizes) == cunilogCmdConfigXAmountEnumValues);

		return 0 <= cmd && cunilogCmdConfigXAmountEnumValues > cmd;
	}
#endif

size_t culCmdRequiredSize (enum cunilogEvtCmd cmd)
{
	ubf_assert (0 <= cmd);
	ubf_assert (cunilogCmdConfigXAmountEnumValues > cmd);
	ubf_assert (GET_ARRAY_LEN (culCmdSizes) == cunilogCmdConfigXAmountEnumValues);

	if (culIsValidCmd (cmd))
		return culCmdSizes [cmd].siz;
	return CUNILOG_CMD_INVALID_SIZE;
}

void culCmdStoreEventCommand (unsigned char *szOut, enum cunilogEvtCmd cmd)
{
	ubf_assert_non_NULL (szOut);
	ubf_assert (sizeof (enum cunilogEvtCmd) == sizeof (cmd));
	ubf_assert (0 <= cmd);
	ubf_assert (cunilogCmdConfigXAmountEnumValues > cmd);
	ubf_assert (GET_ARRAY_LEN (culCmdSizes) == cunilogCmdConfigXAmountEnumValues);

	memcpy (szOut, &cmd, sizeof (cmd));
}

void culCmdStoreCmdConfigUseColourForEcho (unsigned char *szOut, bool bUseColour)
{
	ubf_assert_non_NULL (szOut);

	culCmdStoreEventCommand (szOut, cunilogCmdConfigUseColourForEcho);
	memcpy (szOut + sizeof (enum cunilogEvtCmd), &bUseColour, sizeof (bool));
}

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigEventSeverityFormatType (unsigned char *szOut, cueventsevfmtpy sevTpy)
	{
		ubf_assert_non_NULL (szOut);
		ubf_assert (sizeof (cueventsevfmtpy) == sizeof (sevTpy));

		culCmdStoreEventCommand (szOut, cunilogCmdConfigEventSeverityFormatType);
		memcpy (szOut + sizeof (enum cunilogEvtCmd), &sevTpy, sizeof (sevTpy));
	}
#endif

void culCmdStoreCmdConfigCunilognewline (unsigned char *szOut, newline_t nl)
{
	ubf_assert_non_NULL (szOut);
	ubf_assert (sizeof (newline_t) == sizeof (nl));

	culCmdStoreEventCommand (szOut, cunilogCmdConfigCunilognewline);
	memcpy (szOut + sizeof (enum cunilogEvtCmd), &nl, sizeof (nl));
}

/*
	These declarations are from cunilog.h. They are defined in cunilog.c.
*/
void ConfigCUNILOG_TARGETdisableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);
void ConfigCUNILOG_TARGETenableTaskProcessors (CUNILOG_TARGET *put, enum cunilogprocesstask task);
void ConfigCUNILOG_TARGETdisableEchoProcessor (CUNILOG_TARGET *put);
void ConfigCUNILOG_TARGETenableEchoProcessor (CUNILOG_TARGET *put);

void culCmdStoreCmdConfigDisableTaskProcessors (unsigned char *szOut, enum cunilogprocesstask task)
{
	ubf_assert_non_NULL (szOut);

	culCmdStoreEventCommand (szOut, cunilogCmdConfigDisableTaskProcessors);
	memcpy (szOut + sizeof (enum cunilogEvtCmd), &task, sizeof (task));
}

void culCmdStoreCmdConfigEnableTaskProcessors (unsigned char *szOut, enum cunilogprocesstask task)
{
	ubf_assert_non_NULL (szOut);

	culCmdStoreEventCommand (szOut, cunilogCmdConfigEnableTaskProcessors);
	memcpy (szOut + sizeof (enum cunilogEvtCmd), &task, sizeof (task));
}

void culCmdConfigDisableTaskProcessors (CUNILOG_TARGET *put, unsigned char *szData)
{
	enum cunilogprocesstask task;

	memcpy (&task, szData, sizeof (task));
	ubf_assert (0 <= task);
	ubf_assert (task < cunilogProcessXAmountEnumValues);

	ConfigCUNILOG_TARGETdisableTaskProcessors (put, task);
}

void culCmdConfigEnableTaskProcessors (CUNILOG_TARGET *put, unsigned char *szData)
{
	enum cunilogprocesstask task;

	memcpy (&task, szData, sizeof (task));
	ubf_assert (0 <= task);
	ubf_assert (task < cunilogProcessXAmountEnumValues);

	ConfigCUNILOG_TARGETenableTaskProcessors (put, task);
}

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigLogThreadPriority (unsigned char *szOut, cunilogprio prio)
	{
		ubf_assert_non_NULL (szOut);
		ubf_assert (sizeof (cunilogprio) == sizeof (prio));

		culCmdStoreEventCommand (szOut, cunilogCmdConfigSetLogPriority);
		memcpy (szOut + sizeof (enum cunilogEvtCmd), &prio, sizeof (prio));
	}
#endif

#ifdef OS_IS_WINDOWS
	int icuWinPrioTable [cunilogPrioAmountEnumValues] =
	{
			/* cunilogPrioNormal			*/	THREAD_PRIORITY_NORMAL
		,	/* cunilogPrioBelowNormal		*/	THREAD_PRIORITY_BELOW_NORMAL
		,	/* cunilogPrioLow				*/	THREAD_PRIORITY_LOWEST
		,	/* cunilogPrioIdle				*/	THREAD_PRIORITY_IDLE
		,	/* cunilogPrioBeginBackground	*/	THREAD_MODE_BACKGROUND_BEGIN
		,	/* cunilogPrioEndBackground		*/	THREAD_MODE_BACKGROUND_END
	};
#else
	// These values haven't been tested yet! I (Thomas) just made them up in
	//	the hope they might do well enough.
	int icuPsxPrioTable [cunilogPrioAmountEnumValues] =
	{
			/* cunilogPrioNormal			*/	0
		,	/* cunilogPrioBelowNormal		*/	5
		,	/* cunilogPrioLow				*/	10
		,	/* cunilogPrioIdle				*/	19
		,	/* cunilogPrioBeginBackground	*/	19
		,	/* cunilogPrioEndBackground		*/	0
	};
#endif

#ifdef OS_IS_WINDOWS
	static bool SetWinCurrThreadPriority (int prio)
	{
		HANDLE hThread = GetCurrentThread ();
		return SetThreadPriority (hThread, prio);
	}
#else
	static bool SetPsxCurrThreadPriority (int prio)
	{	// See https://man7.org/linux/man-pages/man3/pthread_setschedprio.3.html .
		pthread_t tThread = pthread_self ();
		return 0 == pthread_setschedprio (tThread, prio);
	}
#endif

bool culCmdSetCurrentThreadPriority (cunilogprio prio)
{
	ubf_assert			(0 <= prio);
	ubf_assert			(prio < cunilogPrioAmountEnumValues);

	#ifdef PLATFORM_IS_WINDOWS
		return SetWinCurrThreadPriority (icuWinPrioTable [prio]);
	#else
		return SetPsxCurrThreadPriority (icuPsxPrioTable [prio]);
	#endif
}

void culCmdConfigSetLogPriority (unsigned char *szData)
{
	ubf_assert_non_NULL (szData);

	cunilogprio prio;

	memcpy (&prio, szData, sizeof (cunilogprio));

	#ifdef DEBUG
		bool b = culCmdSetCurrentThreadPriority (prio);
		ubf_assert_true (b);
	#else
		culCmdSetCurrentThreadPriority (prio);
	#endif
}

void culCmdChangeCmdConfigFromCommand (CUNILOG_EVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->szDataToLog);
	ubf_assert_non_0	(pev->lenDataToLog);
	ubf_assert_non_NULL (pev->pCUNILOG_TARGET);
	ubf_assert			(cunilogEvtTypeCommand == pev->evType);

	CUNILOG_TARGET *put = pev->pCUNILOG_TARGET;
	ubf_assert_non_NULL (put);

	unsigned char		*szData = pev->szDataToLog;
	enum cunilogEvtCmd	cmd;

	memcpy (&cmd, szData, sizeof (enum cunilogEvtCmd));
	szData += sizeof (enum cunilogEvtCmd);

	bool boolVal;

	switch (cmd)
	{
		case cunilogCmdConfigUseColourForEcho:
			#ifndef CUNILOG_BUILD_WITHOUT_CONSOLE_COLOUR
				memcpy (&boolVal, szData, sizeof (bool));
				if (boolVal)
					cunilogTargetSetUseColourForEcho (put);
				else
					cunilogTargetClrUseColourForEcho (put);
			#endif
			break;
		case cunilogCmdConfigEventSeverityFormatType:
			#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
				memcpy (&put->evSeverityType, szData, sizeof (cueventsevfmtpy));
			#endif
			break;
		case cunilogCmdConfigCunilognewline:
			memcpy (&put->unilogNewLine, szData, sizeof (newline_t));
			ubf_assert (0 <=put->unilogNewLine);
			ubf_assert (cunilogNewLineAmountEnumValues > put->unilogNewLine);
			break;
		case cunilogCmdConfigDisableTaskProcessors:
			culCmdConfigDisableTaskProcessors (put, szData);
			break;
		case cunilogCmdConfigEnableTaskProcessors:
			culCmdConfigEnableTaskProcessors (put, szData);
			break;
		case cunilogCmdConfigDisableEchoProcessor:
			ConfigCUNILOG_TARGETdisableEchoProcessor (put);
			break;
		case cunilogCmdConfigEnableEchoProcessor:
			ConfigCUNILOG_TARGETenableEchoProcessor (put);
			break;
		case cunilogCmdConfigSetLogPriority:
			culCmdConfigSetLogPriority (szData);
			break;
	}
}

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS.
