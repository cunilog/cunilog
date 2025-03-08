/****************************************************************************************

	File		cunilogevtcmds.h
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

#ifndef U_CUNILOGEVTCMDS_H
#define U_CUNILOGEVTCMDS_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include <stdbool.h>
	#include <inttypes.h>

	#include "./cunilogevtcmdsstructs.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif

#ifndef CUNILOG_CMD_INVALID_SIZE
#define CUNILOG_CMD_INVALID_SIZE			(0)
#endif

EXTERN_C_BEGIN

#ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS

/*
	culIsValidCmd

	Returns true if cmd is a valid Cunilog command. Note that this is the only function/
	macro that checks that cmd is a valid Cunilog command, and that this is the only function/
	macro that does not abort in debug versions if the command is invalid.
	
	All other functions/macros do not check if a Cunilog command is valid or not.
*/
#ifdef DEBUG
	bool culIsValidCmd (enum cunilogEvtCmd cmd)
	;
#else
	#define culIsValidCmd(cmd)							\
		((0 <= cmd) && (cmd) < cunilogCmdConfigXAmountEnumValues)
#endif

/*
	culCmdRequiredSize

	Returns the required data size for the Cunilog event command cmd.
	The returned size includes space for the command itself plus the space required for
	additional parameters/arguments.
*/
size_t culCmdRequiredSize (enum cunilogEvtCmd cmd)
;

/*
	culCmdStoreCmdConfigUseColourForEcho

	Stores the command to change whether colours are used or not plus the boolean bUseColour
	in the buffer szOut points to.
*/
void culCmdStoreCmdConfigUseColourForEcho (unsigned char *szOut, bool bUseColour)
;

/*
	culCmdStoreCmdConfigCunilognewline

	Stores the command to change the newline representation and the value of nl in the
	buffer szOut points to.
*/
void culCmdStoreCmdConfigCunilognewline (unsigned char *szOut, newline_t nl)
;

/*
	culCmdStoreConfigEventSeverityFormatType

	Stores the command to change the event severity type and the value of sevTpy in the
	buffer szOut points to.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigEventSeverityFormatType (unsigned char *szOut, cueventsevtpy sevTpy)
	;
#endif

/*
	culCmdStoreCmdConfigDisableTaskProcessors
	culCmdStoreCmdConfigEnableTaskProcessors

	These functions store a command to disable or enable a particular type of processor in
	the buffer szOut points to.
*/
void culCmdStoreCmdConfigDisableTaskProcessors (unsigned char *szOut, enum cunilogprocesstask task);
void culCmdStoreCmdConfigEnableTaskProcessors (unsigned char *szOut, enum cunilogprocesstask task);

/*
	culCmdStoreConfigLogThreadPriority

	Stores the command to change the priority of the logging thread in the buffer szOut
	points to.
*/
#ifndef CUNILOG_BUILD_WITHOUT_EVENT_SEVERITY_TYPE
	void culCmdStoreConfigLogThreadPriority (unsigned char *szOut, cunilogprio prio);
#endif

/*
	culCmdSetCurrentThreadPriority
*/
bool culCmdSetCurrentThreadPriority (cunilogprio prio);

/*
	culCmdChangeCmdConfigFromCommand

	Changes members/flags of the SCUNILOGTARGET structure pev->pSCUNILOGTARGET points to
	for event type cunilogEvtTypeCommand (member pev->evType).

	This function must only be called for events of type cunilogEvtTypeCommand.
*/
void culCmdChangeCmdConfigFromCommand (SCUNILOGEVENT *pev)
;

#endif														// Of #ifndef CUNILOG_BUILD_WITHOUT_EVENT_COMMANDS.

EXTERN_C_END

#endif														// Of #ifndef U_CUNILOGEVTCMDS_H.
