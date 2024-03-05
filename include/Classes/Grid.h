#pragma once
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

    bool view_pos = true;
	bool view_vel = true;
	bool view_acc = true;
    bool view_other = true;

    const int density = 1;
    const int size = 1000;
    const int single_cell_size = 100;

    int cells[DENSITY][DENSITY][SINGLE_CELL_SIZE];

    Node objects[SIZE];
    
    Grid(SDL_Window* window, SDL_Renderer* rnd);
    ~Grid();
    
    int put(int x, int y);
    void remove();
    void remove(int id);
    void remove_all();
    void update();
    void renderAll();
    void printCells();
    void printObjs();
    void clean();
};