#include "Grid.hpp"

void Grid::init(){

    int size = 10;
    for(auto& rows : cells){
        for(auto &col : rows){
            for(auto& ind : col){

                ind = nullptr;

            }
        }
    }
}

Grid::Grid(SDL_Renderer* renderer, SDL_Window* window){

    this->rnd = renderer;
    this->wnd = window;

    SDL_GetWindowSize(window, &this->w, &this->h);

}

void Grid::add(GameObject* obj){

    objects.emplace_back(obj);
}

void Grid::render(){

    for(auto obj : objects){

        SDL_SetRenderDrawColor(rnd, obj->color.r, obj->color.g, obj->color.b ,255);
        SDL_RenderFillCircle(rnd, obj->pos.x,obj->pos.y,obj->radius);
        SDL_SetRenderDrawColor(rnd, 0,0,255,255);
        if(view_vel) SDL_RenderDrawArrow(rnd, obj->pos, obj->vel , 5);
        SDL_SetRenderDrawColor(rnd, 0,255,0,255);
        if(view_acc) SDL_RenderDrawArrow(rnd, obj->pos, obj->acc , 5);
        if(view_pos) SDL_RenderDrawLine(rnd, obj->pos.x, obj->pos.y, w/2,h/2);
        SDL_SetRenderDrawColor(rnd, 255,255,255,255);
        if(view_other){
            SDL_RenderDrawLine(rnd, obj->pos.x,obj->pos.y,
                    obj->pos.x + obj->other.x , obj->pos.y + obj->other.y);
        }
    }
}

void Grid::create(int x, int y){

    Vector pos = Vector(x,y);
    GameObject* obj = new GameObject(pos);
    
    objects.emplace_back(obj);

}

void Grid::clean(){

    for(auto& rows : cells){
        for(auto &col : rows){
            for(auto ind : col){
                
                ind = nullptr;
            }
        }
    }

}

void Grid::update(){

    int x,y,counter;

    for(auto obj : objects){ if(obj){

        //calculate x and y position in the grid
        x = obj->pos.x*WIDTH_DENSITY/w;
        y = obj->pos.y*HEIGHT_DENSITY/h;

        counter=0;
        for(auto ind : cells[x][y]){

            //if no object in place --> ind == nullptr
            if(!ind){
                ind = obj;
                break;
            }

            if(counter == CELL_DENSITY-1){
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Out of bounds for grid, Increase density!");
            }
            counter++;
        }
    }
    }

}

void Grid::display(){

    for(auto& rows : cells){
        for(auto &col : rows){
            for(auto ind : col){
                
                SDL_Log("%d",ind);
            }
        }
    }
}

int Grid::cellx(int xpos){

    return xpos*WIDTH_DENSITY/w;
    
}

int Grid::celly(int ypos){

    return ypos*HEIGHT_DENSITY/h;
    
}