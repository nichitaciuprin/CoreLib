@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.c

set flags=
set flags=%flags% -g3 -Og -std=c17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set src=
@REM set src=%src% %deps%\corelib\src\SysHelper.c
@REM set src=%src% %deps%\corelib\src\SysWindow.c
@REM set src=%src% %deps%\corelib\src\SysNet.c

set include=
@REM set include=%include% -I%~dp0src
set include=%include% -I%deps%\corelib\include

set lib=
@REM set lib=%lib% -lgdi32
@REM set lib=%lib% -lWs2_32

if exist %build% rmdir /S /Q %build%
   mkdir %build%

gcc %main% %src% -o build/level.exe %include% %lib% %flags%
