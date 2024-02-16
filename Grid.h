#include "ObjectList.h"


class Grid{

private:
    SDL_Window* window = nullptr;
public:

    const int density = 10;
    ObjectArray* cells = nullptr;
    Grid(SDL_Window* window);
    ~Grid();

};