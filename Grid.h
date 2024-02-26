#pragma once
#include "SDL2/SDL.h"
#include "GameObject.h"

struct ArrayNode2{
	int id = 0;
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
    Uint8 radius = 10;

public:

    const int density = 10;
    const int size = 1000;
    const int single_cell_size = 100;

    int*** cells = nullptr;
    ArrayNode2* objects = nullptr;


    Grid(SDL_Window* window, SDL_Renderer* rnd);
    ~Grid();
    
    int put(int x, int y);
    void update();
    void getCell(int id, int* i, int * j);
    void renderAll();
    void fillCicle(int r, int x, int y);
    void printCells();
    void clean();
};