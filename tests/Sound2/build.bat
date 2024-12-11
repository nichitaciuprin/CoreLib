@echo off
setlocal

set scripts=%~dp0..\..\scripts
set main=%~dp0main.cpp

call %scripts%\buildlib

set input=%~dp0main.cpp
set output=%~dp0build/sound.exe
call %scripts%\buildtest
