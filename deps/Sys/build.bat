@echo off
setlocal

set include=%~dp0include
set src=%~dp0src
set objs=%~dp0objs
set lib=%~dp0lib\libsyswin.a

if exist %objs% rmdir /S /Q %objs%
   mkdir %objs%

set flags=%flags% -Werror -Wall -Wno-missing-braces
set flags=%flags% -std=c99 -m64
@REM set flags=%flags% -g3 -Og
set flags=%flags% -g0 -O3 -D NDEBUG

set mingw=C:\User1\Programs\mingw\x86_64-12.2.0-release-posix-seh-ucrt-rt_v10-rev2\mingw64
set mingwlib=%mingw%\x86_64-w64-mingw32\lib

ar -x %mingwlib%\libgdi32.a  --output=%objs%
ar -x %mingwlib%\libws2_32.a --output=%objs%

gcc %flags% -c %src%\SysHelper.c  -o %objs%\SysHelper.o  -I%include%
gcc %flags% -c %src%\SysWindow.c  -o %objs%\SysWindow.o  -I%include%
gcc %flags% -c %src%\SysNet.c     -o %objs%\SysNet.o     -I%include%

if exist del %lib%

ar rcs %lib% %objs%\*.o

rmdir /S /Q %objs%
