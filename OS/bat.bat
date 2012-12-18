@echo off
make TOP_DIR=%CD%
if errorlevel 0 goto suc 
goto end
:end
	pause
:suc
	pause