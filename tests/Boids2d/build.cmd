@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.cpp

set flags=
set flags=%flags% -g3 -Og -std=c++17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set include=
set include=%include% -I%deps%\raylib\include
set include=%include% -I%deps%\corelib\include

set lib=
set lib=%lib% -L%deps%\raylib\lib -lraylib
set lib=%lib% -lglmf32 -lgdi32 -lwinmm

if exist %build% rmdir /S /Q %build%
   mkdir %build%

g++ %main% %src% -o build/main.exe %include% %lib% %flags%
