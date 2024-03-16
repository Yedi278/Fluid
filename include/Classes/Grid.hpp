#include <vector>
#include "Draw.hpp"
#include "GameObject.hpp"
#include <iostream>

#define WIDTH_DENSITY 10
#define HEIGHT_DENSITY 10
#define CELL_DENSITY 100

struct Node
{
    int id = -1;
    GameObject* obj = nullptr;
};


class Grid{

private:

    SDL_Renderer* rnd;
    SDL_Window* wnd;

    //window sizes
    int h=0;
    int w=0;

public:
    //ImGui visualising condition variables
    bool view_vel = true;
    bool view_acc = true;
    bool view_pos = false;
    bool view_other = true;

    Uint16 density_per_cell = 100;
    
    //Objects Array
    std::vector <GameObject*> objects;
    //Grid of ojects indices
    GameObject* cells[WIDTH_DENSITY][HEIGHT_DENSITY][CELL_DENSITY];

    Grid(SDL_Renderer* rnd, SDL_Window* wnd);
    
    void init();
    void add(GameObject* obj);
    void create(int x, int y);
    void render();
    void clean();
    void update();
    void display();
    int cellx(int xpos);
    int celly(int ypos);

};