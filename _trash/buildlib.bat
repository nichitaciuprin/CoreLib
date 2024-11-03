@echo off
setlocal

echo building library

set include=%~dp0..\include
set src=%~dp0..\src
set build=%~dp0..\build
set buildtemp=%~dp0..\buildtemp

set mingw=C:\User1\Programs\mingw\x86_64-12.2.0-release-posix-seh-ucrt-rt_v10-rev2\mingw64

set arh1=%mingw%\x86_64-w64-mingw32\lib\libgdi32.a
set arh2=%mingw%\x86_64-w64-mingw32\lib\libws2_32.a

if exist %buildtemp% rmdir /S /Q %buildtemp%
   mkdir %buildtemp%

if exist %build% rmdir /S /Q %build%
   mkdir %build%

mkdir %build%\lib
mkdir %build%\include

ar -x %arh1% --output=%buildtemp%
ar -x %arh2% --output=%buildtemp%

g++  -c %src%\SysHelper.c  -o %buildtemp%\SysHelper.o  -I%include%
g++  -c %src%\SysWindow.c  -o %buildtemp%\SysWindow.o  -I%include%
g++  -c %src%\SysNet.c     -o %buildtemp%\SysNet.o     -I%include%

ar rcs %build%\lib\libcorelib.a %buildtemp%\*.o

rmdir /S /Q %buildtemp%

xcopy %include% %build%\include /E /H /C /I > nul
