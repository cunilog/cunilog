/****************************************************************************************

	File:		dbgcountandtrack.h
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
	This is a simple module to track a counter.
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

#ifndef U_DBGCOUNTANDTRACK_H
#define U_DBGCOUNTANDTRACK_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./platform.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/platform.h"
	#endif

#endif

#ifdef	__cplusplus
	extern "C"	{
#endif

#ifndef DBGCOUNTANDRACK_MAX_STRING
#define DBGCOUNTANDRACK_MAX_STRING		(128)
#endif

#ifndef DBGCOUNTANDTRACK_RESERVE_NUM
#define DBGCOUNTANDTRACK_RESERVE_NUM	(32)
#endif

#ifdef DEBUG
	typedef struct sdbgcountandtrack
	{
		size_t				value;
		char				cSourceFileName	[DBGCOUNTANDRACK_MAX_STRING];
		char				cFunctionName	[DBGCOUNTANDRACK_MAX_STRING];
		unsigned int		uiLine;
	} SDBGCOUNTANDTRACK;
#endif

#ifdef DEBUG
	typedef struct sdbgtracker
	{
		SDBGCOUNTANDTRACK	*trackers;
		size_t				n;								// Next index to write to.
		size_t				t;								// Next index to check/test/track.
		size_t				size;
		size_t				value;							// Current value. Probably not
															//	required. This is the value
															//	as obtained by the last change.
		char				cSourceFileName	[DBGCOUNTANDRACK_MAX_STRING];
		char				cFunctionName	[DBGCOUNTANDRACK_MAX_STRING];
		unsigned int		uiLine;
	} SDBGTRACKER;
#endif

/*
	SDBGTRACKER_INITIALISER

	Static/automatic initialiser.
*/
#define SDBGTRACKER_INITIALISER							\
			{											\
				{NULL}, 0, 0, {NULL}, {NULL}, 0			\
			}

/*
	DBG_DEFINE_CNTTRACKER

	Defines the counter cntname. Does nothing in release builds.

	Example:
	DBG_DEFINE_CNTTRACKER (myCounter)

	Note: Do NOT place a semicolon at the end.
*/
#ifdef DEBUG
	#define DBG_DEFINE_CNTTRACKER(cntname)				\
				SDBGTRACKER	cntname;
#else
	#define DBG_DEFINE_CNTTRACKER(cntname)
#endif

/*
	DBG_DEFINE_AND_INIT_COUNTER

	Defines and initialises the counter cntname to 0 in debug versions. Does nothing
	in release builds.

	Example:
	DBG_DEFINE_AND_INIT_COUNTER (myCounter);
*/
#ifdef DEBUG
	#define DBG_DEFINE_AND_INIT_CNTTRACKER(cntname)		\
				SDBGTRACKER	cntname = SDBGTRACKER_INITIALISER
#else
	#define DBG_DEFINE_AND_INIT_CNTTRACKER(cntname)
#endif

/*
	DBG_INIT_CNTTRACKER
	DBG_INIT_pCNTTRACKER

	Initialises the tracking counter.

	Example:

	SDBGTRACKER ourTracker;

	DBG_INIT_CNTTRACKER (ourTracker);
	or
	DBG_INIT_pCNTTRACKER (&ourTracker);
*/
#ifdef DEBUG
	#define DBG_INIT_CNTTRACKER(cntname)				\
				(cntname).trackers	= NULL;				\
				(cntname).n			= 0;				\
				(cntname).t			= 0;				\
				(cntname).size		= 0;				\
				(cntname).value		= 0
	#define DBG_INIT_pCNTTRACKER(cntname)				\
				(cntname)->trackers	= NULL;				\
				(cntname)->n		= 0;				\
				(cntname)->t		= 0;				\
				(cntname)->size		= 0;				\
				(cntname)->value	= 0
#else
	#define DBG_INIT_CNTTRACKER(cntname)
	#define DBG_INIT_pCNTTRACKER(cntname)
#endif

#ifdef DEBUG
	void resetDBGcountandtrack	(
			SDBGTRACKER *pt, const char *szFile, const char *szFunc, unsigned int line
								)
	;
#endif

/*
	DBG_RESET_CNTTRACKER
	DBG_RESET_pCNTTRACKER

	Prepares the tracking counter and resets it to 0.
*/
#ifdef DEBUG
	#define DBG_RESET_CNTTRACKER(cntname)				\
		resetDBGcountandtrack (&cntname, __FILE__, __FUNCTION__, __LINE__)
	#define DBG_RESET_pCNTTRACKER(cntname)				\
		resetDBGcountandtrack (cntname, __FILE__, __FUNCTION__, __LINE__)
#else
	#define DBG_RESET_CNTTRACKER(cntname)
	#define DBG_RESET_pCNTTRACKER(cntname)
#endif

#ifdef DEBUG
	void trackDBGcountandtrack	(
			SDBGTRACKER *pt, size_t value, const char *szFile, const char *szFunc,
			unsigned int line
								)
	;
#endif

/*
	DBG_TRACK_CNTTRACKER
	DBG_TRACK_pCNTTRACKER

	Tracks the counter.
*/
#ifdef DEBUG
	#define DBG_TRACK_CNTTRACKER(cntname, value)		\
		trackDBGcountandtrack (&cntname, (value), __FILE__, __FUNCTION__, __LINE__)
	#define DBG_TRACK_pCNTTRACKER(cntname)				\
		trackDBGcountandtrack (cntname, (value), __FILE__, __FUNCTION__, __LINE__)
#else
	#define DBG_TRACK_CNTTRACKER(cntname, value)
	#define DBG_TRACK_pCNTTRACKER(cntname, value)
#endif

/*
	DBG_RESET_CHECK_CNTTRACKER
	DBG_RESET_CHECK_pCNTTRACKER

	Prepares/resets checking the tracking counter.
*/
#ifdef DEBUG
	#define DBG_RESET_CHECK_CNTTRACKER(cntname)			\
		(cntname).t = 0
	#define DBG_RESET_CHECK_pCNTTRACKER(cntname)		\
		(cntname)->t = 0
#else
	#define DBG_RESET_CHECK_CNTTRACKER(cntname)
	#define DBG_RESET_CHECK_pCNTTRACKER(cntname)
#endif


#ifdef DEBUG
	void trackcheckDBGcountandtrack	(
			SDBGTRACKER *pt, size_t value, const char *szFile, const char *szFunc,
			unsigned int line
									)
	;
#endif

/*
	DBG_TRACK_CHECK_CNTTRACKER
	DBG_TRACK_CHECK_pCNTTRACKER

	Tracks the counter.
*/
#ifdef DEBUG
	#define DBG_TRACK_CHECK_CNTTRACKER(cntname, value)	\
		trackcheckDBGcountandtrack (&cntname, (value), __FILE__, __FUNCTION__, __LINE__)
	#define DBG_TRACK_CHECK_pCNTTRACKER(cntname)		\
		trackcheckDBGcountandtrack (cntname, (value), __FILE__, __FUNCTION__, __LINE__)
#else
	#define DBG_TRACK_CHECK_CNTTRACKER(cntname, value)
	#define DBG_TRACK_CHECK_pCNTTRACKER(cntname, value)
#endif


#ifdef	__cplusplus
				}
#endif

#endif														// Of #ifdef U_DBGCOUNTANDTRACK_H.
