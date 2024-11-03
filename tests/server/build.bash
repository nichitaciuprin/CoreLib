deps=./../../deps

flags=
flags="$flags -g3 -Og -std=c++17 -pthread -m64"
flags="$flags -Werror -Wno-missing-braces -Wall"

src=
src="$src $deps/corelib/src/SysHelper.c"
src="$src $deps/corelib/src/SysWindow.c"
src="$src $deps/corelib/src/SysNet.c"

include=
include="$include -I./src"
include="$include -I$deps/corelib/include"

lib=
lib="$lib -lX11"

rm -rf build
mkdir build

g++ main.cpp $src -o build/server $include $lib $flags
