@echo off
setlocal

call %~dp0..\..\buildlib

set input=%~dp0main.cpp
set output=%~dp0build/client.exe
call %~dp0..\..\buildtest
