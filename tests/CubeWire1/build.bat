@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.cpp

set flags=
set flags=%flags% -g3 -Og -std=c++17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set src=
set src=%src% %deps%\Sys\src\SysHelper.c
set src=%src% %deps%\Sys\src\SysWindow.c
set src=%src% %deps%\Sys\src\SysNet.c

set include=
set include=%include% -I%~dp0src
set include=%include% -I%deps%\corelib\include
set include=%include% -I%deps%\sys\include

set lib=
set lib=%lib% -lgdi32
set lib=%lib% -lWs2_32

if exist %build% rmdir /S /Q %build%
   mkdir %build%

g++ %main% %src% -o build/main.exe %include% %lib% %flags%
