@echo off
setlocal

set flags=
set flags=%flags% -g3 -Og -std=c++17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces
set main=%~dp0main.cpp

set lib=
set lib=%lib% -ld3d11 -ld3dcompiler

if exist build rmdir /S /Q build
   mkdir build

g++ %main% -o build/main.exe %lib% %flags%

copy .\shaders.hlsl .\build\shaders.hlsl > nul
