#pragma once
#include "GameObject.hpp"

struct Node{
	int id=0;
	GameObject* obj = nullptr;
};

class ObjectArray{

private:
	int w_c;
	int h_c;
	SDL_Renderer* rndr = nullptr;

public:
	int size = 0;
	Uint8 r = 10;
	Node* array = nullptr;
	ObjectArray(SDL_Renderer* rndr, int size);
	~ObjectArray();
	
	void init(SDL_Window* window);
	void add(GameObject* obj, int pos);
	void add(int index, int x, int y);

};