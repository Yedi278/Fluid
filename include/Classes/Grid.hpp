#include <vector>
#include "Draw.hpp"
#include "GameObject.hpp"

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
    int** cells = nullptr;

    Grid(SDL_Renderer* rnd, SDL_Window* wnd);
    
    void init();
    void add(GameObject* obj);
    void create(int x, int y);
    void render();
    void clean();
    void update();
};