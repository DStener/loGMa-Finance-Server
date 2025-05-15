@echo off

SET mypath=%~dp0

call .\setup.bat

rem FINDE EXE FILE
for /r %mypath:~0,-1%\build %%a in (*) do if "%%~nxa"=="server.exe" set p=%%~dpnxa
if defined p (
call %p%
) else (
echo File not found
)