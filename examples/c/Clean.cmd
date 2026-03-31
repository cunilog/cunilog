@echo.
@echo Script: %~n0%~x0
@echo.
@echo -----------------------------------------------------------------------
@echo This batch script removes compiler output files *.exe and *.obj from
@echo this folder.
@echo.
@echo Press ENTER to clean all output files. Use CTRL-C or close the window
@echo to abort.
@echo.
@echo -----------------------------------------------------------------------
@pause
@echo.
@echo del /q *.exe
@del /q *.exe
@echo.
@echo del /q *.obj
@del /q *.obj
@echo.
@pause
