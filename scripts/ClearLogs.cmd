@echo.
@echo Script: %~n0%~x0
@echo.
@echo -----------------------------------------------------------------------
@echo This batch script removes log files from the ..\logs folder.
@echo.
@echo Press ENTER to delete all log files. Use CTRL-C or close the window
@echo to abort.
@echo.
@echo -----------------------------------------------------------------------
@pause
@echo.
@echo del /q "..\logs\*.log"
@del /q "..\logs\*.log"
@echo.
@echo del /q "..\logs\*.log.*"
@del /q "..\logs\*.log.*"
@echo.
@echo del /q /s "..\*.log"
@del /q /s "..\*.log"
@echo.
@echo del /q /s "..\*.log.*"
@del /q /s "*..\.log.*"
@echo.
@pause
