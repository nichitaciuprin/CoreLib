root=./../..
deps=$root/deps
build=./build

# -O      Same as -O1
# -O0     do no optimize, the default if no optimization level is specified
# -O1     optimize minimally, favoring compilation time
# -O2     optimize more, without speed/size tradeoff
# -O3     optimize even more, favoring speed
# -Ofast  optimize very aggressively to the point of breaking standard compliance, favoring speed. May change program behavior
# -Og     optimize debugging experience. -Og enables optimizations that do not interfere with debugging. It should be the optimization level of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.
# -Os     optimize for size. -Os enables all -O2 optimizations that do not typically increase code size. It also performs further optimizations designed to reduce code size. -Os disables the following optimization flags: -falign-functions -falign-jumps -falign-loops -falign-labels -freorder-blocks -freorder-blocks-and-partition -fprefetch-loop-arrays -ftree-vect-loop-version

# TODO add -Wall
flags="-g3 -Og -std=c++17 -Werror -Wno-missing-braces -pthread -m64"

include=
include="$include -I$deps/Base/include"
include="$include -I$deps/Sys/include"
include="$include -I./src"

src=
src="$src $deps/Sys/src/SysHelper.c"
src="$src $deps/Sys/src/SysWindow.c"
src="$src $deps/Sys/src/SysNet.c"

rm -rf build
mkdir build

g++ main.cpp $src -o build/CampfireClient $flags $include $lib -lGL -lm -lpthread -ldl -lrt -lX11
