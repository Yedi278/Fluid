#include "ObjectArray.h"

ObjectArray::ObjectArray(SDL_Renderer* rndr, int size){

	this->rndr = rndr;
	this->size = size;
	array = new Node[size];
}

ObjectArray::~ObjectArray(){
	delete[] array;
}

void ObjectArray::init(SDL_Window* window){

	//ciao, u little idiot//
}

void ObjectArray::add(GameObject* obj, int pos){

	array[pos].obj = obj;
}

void ObjectArray::add(int index, int x, int y){
	
	GameObject* tmp = new GameObject(x,y,0,0,0,0);
	array[index].obj = tmp;

}