deps=./../../deps
main=./main.cpp

flags=
flags="$flags -g3 -Og -std=c++17 -pthread -m64"
flags="$flags -Werror -Wall -Wno-missing-braces"

include=
include="$include -I./src"
include="$include -I$deps/corelib/include"
include="$include -I$deps/raylib/include"
include="$include -I$deps/raylibWrap/include"
include="$include -I$deps/ReactPhysics3D/include"
include="$include -I$deps/ReactPhysics3DWrap/include"

src=
src="$src $deps/corelib/src/SysHelper.c"
src="$src $deps/corelib/src/SysWindow.c"
src="$src $deps/corelib/src/SysNet.c"
src="$src $deps/raylibWrap/src/RaylibWrap.cpp"

lib=
lib="$lib -L$deps/raylib/lib -lraylib_linux"
lib="$lib -L$deps/ReactPhysics3D/lib -lreactphysics3d_linux"
lib="$lib -lX11 -ldl"

rm -rf ./build
mkdir ./build

g++ $main $src -o ./build/main $include $lib $flags
