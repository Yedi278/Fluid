CC = g++
CFLAGS = -Wall

SRC = $(wildcard src/*.cpp) $(wildcard lib/imgui/lib/*.cpp)

INCLUDE = -Iinclude/Classes
LIB= -I lib\SDL2\i686-w64-mingw32\include -L lib\SDL2\i686-w64-mingw32\lib -I lib\imgui\include -L lib\imgui\lib

lib = -lSDL2main -lSDL2

BUILD_DIR = build

default: windows run

debug: windowsDeb runDeb

windows: 
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) $(LIB) $(lib) -lmingw32 -o $(BUILD_DIR)/Build

windowsDeb:
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) $(LIB) $(lib) -lmingw32 -o $(BUILD_DIR)/Build -g

run:
	./build/Build
runDeb:
	gdb ./build/BuildDeb