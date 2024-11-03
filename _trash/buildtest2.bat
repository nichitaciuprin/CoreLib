@echo off
setlocal

echo building test

set include=%~dp0..\..\include
set src=%~dp0..\..\src

set wflags=-Werror -Wall -Wno-missing-braces

set flags=-g3 -Og -std=c++17 -pthread -m64

set fsrc=
set fsrc=%fsrc% %src%\SysHelper.c
set fsrc=%fsrc% %src%\SysWindow.c
set fsrc=%fsrc% %src%\SysNet.c

set finclude=-I%include%

set flib=
set flib=%flib% -lgdi32
set flib=%flib% -lWs2_32

if exist build rmdir /S /Q build
   mkdir build

g++ %input% %fsrc% -o %output% %finclude% %flib% %flags% %wflags%
