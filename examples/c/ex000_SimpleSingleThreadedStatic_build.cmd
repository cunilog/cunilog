@ECHO OFF
REM	************************************************************************************
REM
REM	File:		
REM	Why:		Script to build a Cunilog example.
REM	OS:			Windows 11
REM	Author:		Thomas
REM	Created:	2025-04-04
REM
REM License:	Public domain.
REM  
REM	History
REM	-------
REM
REM	When		Who				what
REM	------------------------------------------------------------------------------------
REM	2025-04-04	Thomas			Created.
REM
REM	***********************************************************************************/
@ECHO ON

cl /DUNICODE ex000_SimpleSingleThreadedStatic.c ../../src/c/combined/cunilog_combined.c
