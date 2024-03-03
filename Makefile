CC=g++
CFLAGS=
SOURCE=src
INCLUDE=-Iinclude -IC:\\Libraries\\SDL2-2.30.0-MNGW\\i686-w64-mingw32\\include 
LIB=-LC:\\Libraries\\SDL2-2.30.0-MNGW\\i686-w64-mingw32\\lib -Llib
lib=-lmingw32 -lSDL2main -lSDL2
BUILD=build

FILES=$(SOURCE)\Draw.cpp $(SOURCE)\Engine.cpp $(SOURCE)\GameObject.cpp $(SOURCE)\Grid.cpp $(SOURCE)\Objectarray.cpp $(SOURCE)\Physics.cpp $(SOURCE)\Vector.cpp


all: 
	$(CC) $(CFLAGS)	$(SOURCE)\main.cpp $(FILES) $(INCLUDE) $(LIB) $(lib) -o $(BUILD)/Build
	./build/Build.exe

compile:
	$(CC) $(CFLAGS)	$(SOURCE)\main.cpp $(FILES) $(INCLUDE) $(LIB) $(lib) -o $(BUILD)/Build

run:
	./build/Build