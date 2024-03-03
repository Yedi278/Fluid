#pragma once
#include "SDL2/SDL.h"
#include "GameObject.h"
#include "Draw.hpp"

#define DENSITY 30
#define SINGLE_CELL_SIZE 10
#define SIZE 1000

struct Node{
	int id = -1;
	GameObject* obj = nullptr;
};

class Grid{

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* rnd = nullptr;
    int w = 0;
    int h = 0;
    int w_cell;
    int h_cell;

public:

    const int density = 10;
    const int size = 1000;
    const int single_cell_size = 100;

    int cells[DENSITY][DENSITY][SINGLE_CELL_SIZE];

    Node objects[SIZE];
    
    Grid(SDL_Window* window, SDL_Renderer* rnd);
    ~Grid();
    
    int put(int x, int y);
    void update();
    void renderAll();
    void printCells();
    void printObjs();
    void clean();
};