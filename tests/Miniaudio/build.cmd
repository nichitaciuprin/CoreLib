@echo off
setlocal

set deps=%~dp0..\..\deps

set flags=
set flags=%flags% -g3 -Og -std=c++17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set include=
set include=%include% -I%deps%\corelib\include

if exist build rmdir /S /Q build
   mkdir build

g++ main.cpp -o build/main.exe %include% %flags%

copy .\sound.wav .\build\sound.wav > nul
