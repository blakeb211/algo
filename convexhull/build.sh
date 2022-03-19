#!/bin/bash
# clang++ -Wall -std=c++20 -pedantic -v -stdlib=libc++ $1 -o a.out
clang++ -g -Wall -std=c++17 -pedantic $1 -I/usr/include/SDL2/ -lSDL2main -lSDL2
