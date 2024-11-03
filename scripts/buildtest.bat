@echo off
setlocal

echo building test

set corelib=%~dp0..\build

set include=%corelib%\include
set lib=%corelib%\lib

set flags1=-g3 -Og -std=c++17 -pthread -m64
set flags2=-Werror -Wall -Wno-missing-braces

set flags=%flags1% %flags2%

if exist build rmdir /S /Q build
   mkdir build

g++ %input% -o %output% -I%include% -L%lib% -lcorelib %flags%
