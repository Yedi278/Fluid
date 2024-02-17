#include "Grid.h"

Grid::~Grid()
{
    for( int i = 0; i < density; ++i )
    {
        delete[] cells[i];
    }
    delete[] cells;
    delete this;
}
Grid::Grid(SDL_Window* window)
{
    SDL_GetWindowSize(window,&w,&h);
    w_cell = w/density;
    h_cell = w/density;

    objects = new ArrayNode[size];
    cells = new int**[density];

    for(int i=0; i<density; i++){
        cells[i] = new int*[density];
    }

    for(int i=0; i<density; i++){
        for(int j=0; j<density; j++){

            cells[i][j] = new int[single_cell_size];
            
        }
    }
}

void Grid::put(GameObject* obj, int x, int y){

    int x_ind = x/w_cell;
    int y_ind = y/h_cell;

}