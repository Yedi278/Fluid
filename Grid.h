#include "ObjectArray.h"

struct ArrayNode{
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

public:

    const int density = 10;
    const int size = 1000;
    const int single_cell_size = 100;

    int*** cells = nullptr;
    ArrayNode* objects = nullptr;


    Grid(SDL_Window* window);
    ~Grid();
    void put(GameObject* obj, int x, int y);
    void update();

};