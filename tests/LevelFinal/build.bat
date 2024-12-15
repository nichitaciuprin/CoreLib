@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.c

set flags=%flags% -Werror -Wall -Wno-missing-braces
set flags=%flags% -std=c99 -m64
@REM set flags=%flags% -g3 -Og
set flags=%flags% -g0 -O3 -D NDEBUG

@REM set src=%src% %deps%\Sys\src\SysHelper.c
@REM set src=%src% %deps%\Sys\src\SysWindow.c
@REM set src=%src% %deps%\Sys\src\SysNet.c

set include=%include% -I%~dp0src
set include=%include% -I%deps%\corelib\include
set include=%include% -I%deps%\sys\include

set lib=%lib% -L%deps%\Sys\lib -lsyswin

if exist %build% rmdir /S /Q %build%
   mkdir %build%

gcc %main% %src% -o %build%/level.exe %include% %lib% %flags%
