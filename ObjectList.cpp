#include "ObjectList.h"
#include <iostream>

ObjectArray::ObjectArray(SDL_Renderer* rndr, int size){

	this->rndr = rndr;
	this->size = size;
	array = new ArrayNode[size];
}

ObjectArray::~ObjectArray(){
	delete[] array;
}

void ObjectArray::printArray(){

	for(int i=0; i< size; i++){	
		if(array[i].obj != nullptr){
			SDL_Log("%f,%f\n",array[i].obj->x,array[i].obj->y);
		}
	}

}

void ObjectArray::init(SDL_Window* window){

	int w,h;
	int r = 30;
	SDL_GetWindowSize(window,&w,&h);
	w_c = w/2;
	h_c = h/2;
	int k1 = w_c - size*r/2;
	int k2 = h_c - size*r/2;
	int w_p = 3;
	int h_p = 3;
	int index = 0;

	for(int i=0; i<w_p; i++){
		for(int j=0; j<h_p; j++){

			// array[i+j].id = i+j;

			int x = k1 + 2*r*i;
			int y = k2 + 2*r*j;
			Vector2* v = new Vector2(x,y);
			
			// SDL_Log("%d, %d : %d",i,j,ind);
			array[2].obj = new GameObject(v);
			index++;//ciao, u little idiot//
		}

	}
}

void ObjectArray::render_all(){

	SDL_Rect* rect = new SDL_Rect();

	for(int i=0; i<size; i++){

		if(array[i].obj != nullptr){

			array[i].obj->render(rndr,rect);

		}
	}
}

void ObjectArray::update_all(){

	for(int i=0; i<size; i++){

		if(array[i].obj != nullptr){

		}
	}
}

void ObjectArray::add(GameObject* obj, int pos){

	array[pos].obj = obj;
}

void ObjectArray::add(int pos){
	
	GameObject* tmp = new GameObject(200,200,0,0,0,0);
	array[pos].obj = tmp;

}