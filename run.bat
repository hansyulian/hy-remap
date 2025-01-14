@echo off
set "script_to_run=debug.bat"

:: Run the first script and wait for it to complete
call "%script_to_run%"
if errorlevel 1 (
    echo Error: "%script_to_run%" failed. Exiting.
    exit /b 1
)

:: Continue with the rest of the script only if the first script succeeded
cd build/debug
call HyRemap.exe
cd ../..
:: Exit without confirmation
exit /b
