echo building library

include="../include"
src="../src"
build="../build"
buildtemp="../buildtemp"

flags=
flags="$flags -g3 -Og -std=c++17 -pthread -m64"
flags="$flags -Werror -Wno-missing-braces"

rm -rf $buildtemp
mkdir $buildtemp

rm -rf $build
mkdir $build

mkdir $build/lib
mkdir $build/include

ar -x /usr/lib/x86_64-linux-gnu/libX11.a --output=$buildtemp
ar -x /usr/lib/x86_64-linux-gnu/libdl.a  --output=$buildtemp
ar -x /usr/lib/x86_64-linux-gnu/libxcb.a --output=$buildtemp

g++  -c $src/SysHelper.c  -o $buildtemp/SysHelper.o  -I$include $flags
g++  -c $src/SysWindow.c  -o $buildtemp/SysWindow.o  -I$include $flags
g++  -c $src/SysNet.c     -o $buildtemp/SysNet.o     -I$include $flags

ar rcs $build/lib/libcorelib.a $buildtemp/*
# ar -c $build/lib/libcorelib.a $buildtemp/*

# rm -rf $buildtemp

cp -r $include/* $build/include
