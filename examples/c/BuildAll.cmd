@echo.
@echo Script: %~n0%~x0
@echo.
@echo -----------------------------------------------------------------------
@echo This batch script builds all C examples in this folder, provided that
@echo the command-line has all the environment variables required for the
@echo build process have been set up correcty.
@echo.
@echo Press ENTER to clean all output files. Use CTRL-C or close the window
@echo to abort.
@echo.
@echo -----------------------------------------------------------------------
@pause
@echo.

call ex000_SimpleSingleThreadedStatic_build.cmd
call ex001_SimpleSingleThreadedStaticFilesToKeep_build.cmd
call ex002_SimpleSingleThreadedStaticEx_build.cmd
call ex003_SimpleSingleThreadedStaticExLoopWarn_build.cmd
call ex004_SimpleSingleThreadedStaticExFilesToKeep_build.cmd
call ex005_SimpleSingleThreadedStaticExLoopNum_build.cmd
