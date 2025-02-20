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

	//#include <stdbool.h>
	//#include <inttypes.h>
	//#include "./cunilogevtcmdsstructs.h"
	#include "./cunilogstructs.h"
	#include "./cunilogevtcmds.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ArrayMacros.h"
		#include "./ubfmem.h"
		#include "./ubfdebug.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/ArrayMacros.h"
		#include "./../mem/ubfmem.h"
		#include "./../dbg/ubfdebug.h"
	#endif

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
	,	SIZCMDENUM + sizeof (cueventsevtpy)					// cunilogCmdConfigEventSeverityFormatType
	,	SIZCMDENUM + sizeof (newline_t)						// cunilogCmdConfigCunilognewline
	,	SIZCMDENUM + sizeof (enum cunilogprocesstask)		// cunilogCmdConfigDisableTaskProcessors
	,	SIZCMDENUM + sizeof (enum cunilogprocesstask)		// cunilogCmdConfigEnableTaskProcessors
	,	SIZCMDENUM											// cunilogConfigDisableEchoProcessor
	,	SIZCMDENUM											// cunilogConfigEnableEchoProcessor
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

	memcpy (szOut, &cmd, sizeof (cmd));
}

void culCmdStoreCmdConfigUseColourForEcho (unsigned char *szOut, bool bUseColour)
{
	ubf_assert_non_NULL (szOut);

	culCmdStoreEventCommand (szOut, cunilogCmdConfigUseColourForEcho);
	memcpy (szOut + sizeof (enum cunilogEvtCmd), &bUseColour, sizeof (bool));
}

void culCmdStoreCmdConfigCunilognewline (unsigned char *szOut, newline_t nl)
{
	ubf_assert_non_NULL (szOut);
	ubf_assert (sizeof (newline_t) == sizeof (nl));

	culCmdStoreEventCommand (szOut, cunilogCmdConfigCunilognewline);
	memcpy (szOut + sizeof (enum cunilogEvtCmd), &nl, sizeof (nl));
}

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigEventSeverityFormatType (unsigned char *szOut, cueventsevtpy sevTpy)
	{
		ubf_assert_non_NULL (szOut);
		ubf_assert (sizeof (cueventsevtpy) == sizeof (sevTpy));

		culCmdStoreEventCommand (szOut, cunilogCmdConfigEventSeverityFormatType);
		memcpy (szOut + sizeof (enum cunilogEvtCmd), &sevTpy, sizeof (sevTpy));
	}
#endif

void culCmdChangeCmdConfigFromCommand (SCUNILOGEVENT *pev)
{
	ubf_assert_non_NULL (pev);
	ubf_assert_non_NULL (pev->szDataToLog);
	ubf_assert_non_0	(pev->lenDataToLog);
	ubf_assert_non_NULL (pev->pSCUNILOGTARGET);
	ubf_assert			(cunilogEvtTypeCommand == pev->evType);

	SCUNILOGTARGET *put = pev->pSCUNILOGTARGET;
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
					cunilogSetUseColourForEcho (put);
				else
					cunilogClrUseColourForEcho (put);
			#endif
			break;
		case cunilogCmdConfigEventSeverityFormatType:
			#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
				memcpy (&put->evSeverityType, szData, sizeof (cueventsevtpy));
			#endif
			break;
		case cunilogCmdConfigCunilognewline:
			memcpy (&put->unilogNewLine, szData, sizeof (newline_t));
			ubf_assert (0 <=put->unilogNewLine);
			ubf_assert (cunilogNewLineAmountEnumValues > put->unilogNewLine);
			break;
		case cunilogCmdConfigDisableTaskProcessors:
			break;
		case cunilogCmdConfigEnableTaskProcessors:
			break;
		case cunilogConfigDisableEchoProcessor:
			break;
		case cunilogConfigEnableEchoProcessor:
			break;
	}
}

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS.
