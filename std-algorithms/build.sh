# the $1 argument in the line below is the first argument
# passed to this script, which should be the filename
# of the file you want to compile
clang++ -Wall -std=c++17 -pedantic $1 $2 -I/usr/include/SDL2 -lSDL2 -lSDL2main
