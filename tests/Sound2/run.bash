# TODO skip confirmation
# echo y | gdb -q -ex=run -ex=backtrace -ex=quit --args ./build/main
# gdb -q -ex=run -ex=backtrace -ex=quit --args ./build/main
# ./build/main

./build/main 11025 1 4 < ~/Music/test/theetone.wav
