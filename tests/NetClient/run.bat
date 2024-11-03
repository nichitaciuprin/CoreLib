@echo off
setlocal

echo y | gdb -q -ex=run -ex=backtrace -ex=quit --args build\client.exe %1 %2
