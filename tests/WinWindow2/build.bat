@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.c

set flags=
set flags=%flags% -g3 -Og -std=c17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set include=
set include=%include% -I%~dp0src

set lib=
set lib=%lib% -lgdi32

if exist build rmdir /S /Q build
   mkdir build

gcc %main% %src% -o build/main.exe %include% %lib% %flags%
