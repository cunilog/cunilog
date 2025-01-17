@ECHO OFF
REM	************************************************************************************
REM
REM	File:		Creates the combined/merged unilog source code file.
REM	Why:		To make it easier to include cunilog in other projects.
REM	OS:			Windows 10
REM	Author:		Thomas
REM	Created:	2024-07-14
REM
REM License:	Public domain.
REM  
REM	History
REM	-------
REM
REM	When		Who				what
REM	------------------------------------------------------------------------------------
REM	2024-08-01	Thomas			Created (actually: this history added).
REM 2024-11-02	Thomas			Changed to make it read SingleFiles.txt.
REM
REM	***********************************************************************************/
SETLOCAL

cls
ECHO *************************************************************************
ECHO Windows batch script to create the combined cunilog source code files.
ECHO *************************************************************************
ECHO.
ECHO Press any key to carry out the creation, or close the window to
ECHO cancel.
PAUSE >NUL

set destcombinedpath=..\src\c\combined
ECHO.
if not exist "%destcombinedpath%" (
	ECHO Error: Cannot find path "%destcombinedpath%".
	GOTO :Exit
)

set cunilog=%destcombinedpath%\cunilog_combined
set src=..\src\c

rem Go through the file and process it line by line.
set ext=
set srcf=
FOR /F "eol=; tokens=1* delims=" %%i in (SingleFiles.txt) do (
	call :OneLine %%i
)
call :cpyFile
goto :Exit

:OneLine
	set filename=%1
	set isColon=%filename:~0,1%
	set newExte=%filename:~1,2%
	if "%isColon%."==":." (
		call :ChgExt
		goto :eof
	)
	set filename=%filename:/=\%
	rem echo FN: %filename%%ext%
	if "%srcf%."=="." (
		call :noSrcf
		goto :eof
	)
	set frst=%filename:~0,1%
	if "%frst%."=="\." (
		set srcf=%srcf% + %src%%filename%%ext%
	) else (
		set srcf=%srcf% + %filename%%ext%
	)
	rem echo P: %srcf%
	rem pause
goto :eof

:ChgExt
	set exo=%ext%
	if not "%exo%."=="%newExte%." call :cpyFile
	set ext=%newExte%
	goto :eof
goto :eof

:noSrcf
	rem We got no previous file yet.
	set srcf=%filename%%ext%
goto :eof

:cpyFile
	if "%exo%."=="." goto :eof
	rem echo copy %srcf% %cunilog%%exo% /B
	echo Creating file %cunilog%%ext% /B
	copy %srcf% %cunilog%%ext% /B
	set srcf=
	rem echo Old: %exo% New: %ext%
	rem pause
goto :eof

:Exit
echo Done "%~f0".
ENDLOCAL

PAUSE
