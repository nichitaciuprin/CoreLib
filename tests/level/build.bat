@echo off
setlocal

echo building library
call %~dp0..\..\buildlib

echo building test
set input=%~dp0main.cpp
set output=%~dp0build/level.exe
call %~dp0..\..\buildtest
