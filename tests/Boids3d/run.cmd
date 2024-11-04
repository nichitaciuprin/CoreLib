@echo off
setlocal

gdb -q -ex=run -ex=backtrace -ex=quit --args build\main.exe

@REM build\main.exe
@REM if %errorlevel% neq 0 echo === ERROR === %errorlevel%