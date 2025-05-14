@echo off

SET mypath=%~dp0

rem -=-=-=-=-=-=-=- SETUP CLIENT -=-=-=-=-=-=-=-=-=-=-

rem REMOVE BUILD DIRECTORY IF IS EXIST
if exist %TMP%\logma-client\ (
	rmdir /S /Q %TMP%\logma-client
) 

rem CLONE CLIENT
git clone https://github.com/DStener/loGMa-Finance-Client.git %TMP%\logma-client
cd %TMP%\logma-client
git checkout devel

rem BUILD CLIENT
call npm install
call npm run -s build

rem REMOVE BUILD DIRECTORY IF IS EXIST
if exist %mypath:~0,-1%\root\ (
	rmdir /S /Q %mypath:~0,-1%\root
) 

rem COPY STATIC FILE OF CLIENT
xcopy /E /I dist\ %mypath:~0,-1%\root


rem -=-=-=-=-=-=-=- SETUP SERVER -=-=-=-=-=-=-=-=-=-=-

cd %mypath:~0,-1%

cmake -B build .
cd build\
cmake --build . -j %NUMBER_OF_PROCESSORS%



