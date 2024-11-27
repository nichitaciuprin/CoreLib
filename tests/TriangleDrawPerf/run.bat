@echo off
setlocal

build\level.exe
@REM echo y | gdb -q -ex=run -ex=backtrace -ex=quit --args build\level.exe