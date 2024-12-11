@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.cpp

set flags=
set flags=%flags% -g3 -Og -std=c++17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set src=

set include=
set include=%include% -I%~dp0src
set include=%include% -I%deps%\MiniAudio\include

set lib=

if exist %build% rmdir /S /Q %build%
   mkdir %build%

g++ %main% %src% -o build/main.exe %include% %lib% %flags%

copy .\sound.wav .\build\sound.wav > nul
