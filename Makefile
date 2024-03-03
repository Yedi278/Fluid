CC=g++
CFLAGS=
SRC= $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)

INCLUDE = -Iinclude -IC:\\Libraries\\SDL2-2.30.0-MNGW\\i686-w64-mingw32\\include 
LIB = -LC:\\Libraries\\SDL2-2.30.0-MNGW\\i686-w64-mingw32\\lib -Llib

lib = -lmingw32 -lSDL2main -lSDL2
BUILD_DIR = build

default: 
	$(CC) $(CFLAGS)	$(SRC) $(INCLUDE) $(LIB) $(lib) -o $(BUILD_DIR)/Build
	./build/Build.exe

compile:
	$(CC) $(CFLAGS)	$(SRC)\main.cpp $(SRC) $(INCLUDE) $(LIB) $(lib) -o $(BUILD_DIR)/Build

run:
	./build/Build