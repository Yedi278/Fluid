#include "Grid.h"

Grid::Grid(SDL_Window* window)
{
    ObjectArray* arr[density][density];

    arr[0][0]->size = 10;
    SDL_Log("%d",arr[0][0]->size);
}

Grid::~Grid()
{
}