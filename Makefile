CC=g++
CFLAGS= -Wall 
SRC= $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)

INCLUDE = -Iinclude/Classes -Iinclude/imgui 
SDL_LIB= -I C:\\Libraries\\SDL2-2.30.0-MNGW\\i686-w64-mingw32\\include -LC:\\Libraries\\SDL2-2.30.0-MNGW\\i686-w64-mingw32\\lib
LIB = -Llib


lib = -lSDL2main -lSDL2
BUILD_DIR = build

windows: 
	$(CC) $(CFLAGS)	$(SRC) $(INCLUDE)$(SDL_LIB) $(LIB) $(lib) -lmingw32 -o $(BUILD_DIR)/Build
	./build/Build.exe

compile:
	$(CC) $(CFLAGS)	$(SRC)\main.cpp $(SRC) $(INCLUDE) $(LIB) $(lib) -o $(BUILD_DIR)/Build

linux:
	$(CC) $(CFLAGS)	$(SRC) $(INCLUDE) $(LIB) $(lib) -o $(BUILD_DIR)/Build

run:
	./build/Build
