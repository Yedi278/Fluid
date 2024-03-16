#include "Grid_old.hpp"
#include <iostream>

Grid::~Grid()
{
    delete this;
}
Grid::Grid(SDL_Window* window, SDL_Renderer* rnd)
{
    this->rnd = rnd;
    SDL_GetWindowSize(window,&w,&h);
    w_cell = w/density;
    h_cell = w/density;

    for(int i=0; i<SIZE; i++){
        objects[i].id = i;
    }

    for(auto& rows : cells){
        for(auto& cell : rows){
            for(auto& index : cell){
                index = -1;
            }
        }
    }

}

int Grid::put(int x, int y){

    for(auto& node : objects){
        if(node.obj == nullptr){

            node.obj = new GameObject(x,y,0,0);
            return node.id;

        }
    }
    return -1;
}

void Grid::update(){

    for(auto node : objects){
        if(node.obj != nullptr){

            int x = node.obj->pos.x / w_cell;
            int y = node.obj->pos.y / h_cell;

            for(int i=0; i<SINGLE_CELL_SIZE; i++){

                if(cells[x][y][i] == -1 || cells[x][y][i] == node.id){
                    
                    cells[x][y][i] = node.id;
                    break;
                }

                if(i == SINGLE_CELL_SIZE - 1){
                    SDL_LogWarn(SDL_LOG_CATEGORY_SYSTEM,"Out of Bounds for Grid::Update()");
                }
            }
        }
    }
}


void Grid::renderAll(){

    for(auto& node : objects){
        if(node.obj){
        

        SDL_SetRenderDrawColor(rnd, node.obj->color.r, node.obj->color.g, node.obj->color.b ,255);
        SDL_RenderFillCircle(rnd, node.obj->pos.x,node.obj->pos.y,node.obj->radius);
        SDL_SetRenderDrawColor(rnd, 0,0,255,255);
        if(view_vel) SDL_RenderDrawArrow(rnd, node.obj->pos, node.obj->vel , 5);
        SDL_SetRenderDrawColor(rnd, 0,255,0,255);
        if(view_acc) SDL_RenderDrawArrow(rnd, node.obj->pos, node.obj->acc , 5);
        if(view_pos) SDL_RenderDrawLine(rnd, node.obj->pos.x, node.obj->pos.y, w/2,h/2);
        SDL_SetRenderDrawColor(rnd, 255,255,255,255);
        if(view_other) SDL_RenderDrawLine(rnd, node.obj->pos.x,node.obj->pos.y,
                    node.obj->pos.x + node.obj->other.x , node.obj->pos.y + node.obj->other.y);

        }
    }
}

void Grid::clean(){

    for(auto& row : cells){
        for(auto& cell : row){
            for(auto& index : cell){
                index = -1;
            }
        }
    }
}

void Grid::remove_all(){
    for(auto node : objects){
        delete node.obj;
        node.obj = nullptr;
    }
}
