#include "Grid.h"

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);


Grid::~Grid()
{
    for( int i = 0; i < density; ++i )
    {
        delete[] cells[i];
    }
    delete[] cells;
    delete this;
}
Grid::Grid(SDL_Window* window, SDL_Renderer* rnd)
{
    this->rnd = rnd;
    SDL_GetWindowSize(window,&w,&h);
    w_cell = w/density;
    h_cell = w/density;

    objects = new ArrayNode2[size];
    cells = new int**[density];

    for(int i=0; i<density; i++){
        cells[i] = new int*[density];
    }

    for(int i=0; i<density; i++){
        for(int j=0; j<density; j++){

            cells[i][j] = new int[single_cell_size];

            for(int k=0; k<single_cell_size; k++){
                cells[i][j][k] = -1;        //Initialise id = -1
            }
        }
    }


}

int Grid::put(int x, int y){

    for(int i=0; i<size; i++){
        if(objects[i].obj == nullptr){

            objects[i].id = i;
            objects[i].obj = new GameObject(x,y,0,0);
            return i;

        }
    }
    return -1;
}

void Grid::update(){

    for(int i=0; i<size; i++){
        if(objects[i].obj != nullptr){

            GameObject* tmp = objects[i].obj;

            int id = objects[i].id;
            int x = tmp->pos.x / w_cell;
            int y = tmp->pos.y / h_cell;

            for(int k=0; k<single_cell_size; k++){

                if(cells[x][y][k] == id){
                    break;
                }
                if(cells[x][y][k] == -1){

                    cells[x][y][k] = id;
                    break;
                }
                if(k == single_cell_size-1){

                    SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Out of Bounds for Grid::Update()");
                
                }
            }
        }
    }
}

void Grid::getCell(int id, int* l, int * m){

    for (int i = 0; i < density; i++){
        for (int j = 0; j < density; j++){
            
            for(int k = 0; k < single_cell_size; k++){

                if(cells[i][j][k] == id){

                    *l = i;
                    *m = j;
                    
                }
            }
        }
    }
}

void Grid::fillCicle(int r, int x, int y){

	for (double dy = 1; dy <= r; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = x - dx;
		SDL_SetRenderDrawColor(rnd, 255,0,0,255);
		SDL_RenderDrawLine(rnd, x - dx, y + dy - r, x + dx, y + dy - r);
		SDL_RenderDrawLine(rnd, x - dx, y - dy + r, x + dx, y - dy + r);
	}
}

void Grid::renderAll(){

    for(int i=0; i<size; i++){
        if(objects[i].obj != nullptr){

        SDL_RenderFillCircle(rnd, objects[i].obj->pos.x,objects[i].obj->pos.y,objects[i].obj->radius);

        }
    }
}

void Grid::printCells(){

	for(int i=0; i<density; i++){
		for(int j=0;j<density;j++){
			for(int k=0;k<single_cell_size;k++){

				if(cells[i][j][k] != -1){

					SDL_Log("cell[%d][%d][%d] - id: %d \t x:%f y:%f",i,j,k, cells[i][j][k], objects[cells[i][j][k]].obj->pos.x, objects[cells[i][j][k]].obj->pos.y);
				
                }
			}
		}
	}
}

void Grid::clean(){

    for(int i=0; i<density; i++){
        for(int j=0; j<density; j++){
            for(int k=0; k<single_cell_size; k++){

                cells[i][j][k] = -1;

            }
        }
    }
}

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}