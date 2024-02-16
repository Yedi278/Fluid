#include "ObjectList.h"

ObjectArray::ObjectArray(SDL_Renderer* rndr, int size){

	this->rndr = rndr;
	this->size = size;
	array = new ArrayNode[size];
}

ObjectArray::~ObjectArray(){
	delete[] array;
}

void ObjectArray::init(SDL_Window* window){

	//ciao, u little idiot//
}

void ObjectArray::render_all(){

	// SDL_Rect* rect = new SDL_Rect();

	for(int i=0; i<size; i++){

		if(array[i].obj != nullptr){

			array[i].obj->render(rndr);

		}
	}
}

void ObjectArray::add(GameObject* obj, int pos){

	array[pos].obj = obj;
}

void ObjectArray::add(int pos){
	
	GameObject* tmp = new GameObject(300,200,0,0,0,0);
	array[pos].obj = tmp;

}