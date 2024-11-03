@echo off
setlocal

set scripts=%~dp0..\..\scripts

call %scripts%\buildlib

set input=%~dp0main.cpp
set output=%~dp0build/client.exe
call %scripts%\buildtest
