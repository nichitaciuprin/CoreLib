# makes execution stop on error
# set -e

# libs='-lraylib -lGL -lm -lpthread -ldl -lrt -lX11'

# warnings='
# -pedantic -Werror -Wshadow -Wall -Wextra -Wcast-align -Wcast-qual
# -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op
# -Wmissing-include-dirs -Wredundant-decls -Wstrict-overflow=5
# -Wno-unused -Wno-variadic-macros -Wno-parentheses
# -Wundef -fdiagnostics-show-option'

# -pedantic
# -Wshadow
# -Wundef
# -Wextra

# include=../../include

root=./../..
deps=$root/deps2

flags="-g3 -O0 -Wall -std=c++17 -Wno-missing-braces -pthread -m64"

dep1="-I$deps/Base/include"
dep2="-I$deps/raylib/include          -L$deps/raylib/lib          -lraylib"
dep3="-I$deps/ReactPhysics3D/include  -L$deps/ReactPhysics3D/lib  -lreactphysics3d"
depX="$dep1 $dep2 $dep3 $dep4"

rm -rf build
mkdir build

# g++ main.cpp -o build/main -g -I$include $libs $warnings
# g++ main.cpp RaylibWrap.cpp -o build/main $flags $depX -lGL -lm -lpthread -ldl -lrt -lX11
# g++ main.cpp -o build/main $flags $depX
g++ main.cpp RaylibWrap.cpp -o build/main $flags $depX -ldl $warnings

# ./main
