#cs
/****************************************************************************************

	File:		libcunilog.au3
	Why:		Provides AutoIt user functions for libcunilog.
	OS:			Windows
	Author:		Thomas
	Created:	2025-03-24
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2025-03-24	Thomas			Created.

****************************************************************************************/
#ce

#cs
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
#ce

#cs

	Cunilog example script for AutoItScript (https://www.autoitscript.com)
	
	Copy the following 3 lines into your main script:

	Global $CunilogHandle	= -1
	Global $CunilogTarget	= null
	Global $LogFolder		= @ScriptDir					; Where to log to.
	#include "libcunilog.au3"

#ce

#cs
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
#ce

#include <MsgBoxConstants.au3>
#include <File.au3>

ConsoleWrite ("Text")

Global $CunilogHandle	= -1
Global $CunilogTarget	= null
Global $LogFolder		= @ScriptDir ;& '\logs'

Local $bLibLoaded = LoadAndInitCunilog ($LogFolder, "MyLogFile")
#cs
If null <> $bLibLoaded Then
	MsgBox($MB_SYSTEMMODAL, "Title", "Loaded", 10)
Endif
#ce
;Ptr ($CunilogTarget [0])

$bLog = logTextU8 ("Log this line")

ShutdownCunilog ()
DoneCunilog ()

Func libcunilogPath ()
	Local $msvc_ver	= "msvc2019"
	Local $dbg_rel	= "Debug"
	Local $dbg_rel	= "Release"
	If 1 == @AutoItX64 Then
		;MsgBox ($MB_APPLMODAL, "Path", "64 bit")
		Return "..\..\msproj\" & $msvc_ver & "\libcunilog\x64\" & $dbg_rel & "DLLMT\"
		;Return "..\..\msproj\" & $msvc_ver & "\libcunilog\x64\" & $dbg_rel & "DLLMT\"
	Else
		Return "..\..\msproj\" & $msvc_ver & "\libcunilog\" & $dbg_rel & "DLLMT\"
		;Return "..\..\msproj\" & $msvc_ver & "\libcunilog\" & $dbg_rel & "DLLMT\"
	EndIf
EndFunc

#cs
	LoadAndInitCunilog
	
	Loads the DLL libcunilog.dll and initialises a Cunilog target.
#ce
Func LoadAndInitCunilog ($LogPath, $AppName)
	Local $DllPath = _PathFull (libcunilogPath () & 'libcunilog.dll')
	;MsgBox ($MB_APPLMODAL, "Path", $DllPath)
	$CunilogHandle = DllOpen ($DllPath)
	If $CunilogHandle <> -1 Then
		$CunilogTarget = DllCall	(			_
			$CunilogHandle, "ptr:cdecl",		_	; Return value and type.
			"CreateNewCUNILOG_TARGET",			_	; DLL function name.
			"str",	$LogPath, "ulong_ptr", -1,	_
			"str",	$AppName, "ulong_ptr", -1,	_
			"int",	0,							_
			"int",	3,							_
			"int",	5,							_
			"ptr",	null,						_
			"uint",	0,							_
			"int",	0,							_
			"int",	2,							_
			"int",	0							_
									)
		;MsgBox ($MB_APPLMODAL, "CreateNewCUNILOG_TARGET ()", $CunilogTarget [0])
		Return $CunilogTarget
	Else
		MsgBox ($MB_APPLMODAL, "Error", "Error loading DLL")	
	EndIf
	Return null
EndFunc

Func logTextU8 ($Text)
		;MsgBox ($MB_APPLMODAL, "CreateNewCUNILOG_TARGET ()", Ptr ($CunilogTarget [0]))
	$bRet = DllCall ($CunilogHandle, "bool", "logTextU8", "ptr", $CunilogTarget [0], "str", $Text)
	Return $bRet [0]
EndFunc

Func logTextU8debug ()
	If IsPtr ($CunilogTarget [0]) Then
		If null <> $CunilogTarget [0] Then
		
			$ResGetAbsPath = DllCall ($CunilogHandle, "str", "GetAbsoluteLogPathCUNILOG_TARGET", "ptr", $CunilogTarget [0], "ptr", 0)
			MsgBox ($MB_APPLMODAL, "Path", "Path: " & $ResGetAbsPath [0])
			$bLog = logTextU8 ("Log this line")
			MsgBox ($MB_APPLMODAL, "Path", "Logged: " & $bLog)
		Else
			MsgBox ($MB_APPLMODAL, "Path", "$CunilogTarget is null.")
		EndIf
	Else
		MsgBox ($MB_APPLMODAL, "Error", "$CunilogTarget is not a pointer.")
	EndIf
EndFunc

Func ShutdownCunilog ()
	$bRet = DllCall ($CunilogHandle, "bool", "ShutdownCUNILOG_TARGET", "ptr", $CunilogTarget [0])
	Return $bRet [0]
EndFunc

Func DoneCunilog ()
	DllCall ($CunilogHandle, "none", "ptr", $CunilogTarget [0])
	DllClose ($CunilogHandle)
	$CunilogHandle = -1
EndFunc
