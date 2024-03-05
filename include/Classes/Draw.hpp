#pragma once
#include "SDL2/SDL.h"
#include "Vector.hpp"


int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void SDL_RenderDrawArrow(SDL_Renderer* renderer, Vector center, Vector v, float alpha);