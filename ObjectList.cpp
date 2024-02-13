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
	void SDL_GetWindowSize(SDL_Window *window, int *w, int *h);
	int w_c = w/2;
	int h_c = h/2;


	for(int i=0; i<size; i++){

		array[i].id = i;
		// int x = w_c + pow(-1,i)*r*i;
		// int y = h_c + pow(-1,i)*r*i;

		// Vector2* vect = new Vector2(x,y);
		// array[i].obj = new GameObject(rndr, vect);

	}
}

void ObjectArray::render_all(){

	for(int i=0; i<size; i++){

		// SDL_Log("Y value: %f",array[i].obj->y);

		if(array[i].obj != nullptr){

			array[i].obj->render(rndr);

		}
	}
}

void ObjectArray::update_all(){

	for(int i=0; i<size; i++){

		if(array[i].obj != nullptr){

		}
	}

}



//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////



ObjectList::ObjectList() {
	head = new Node();
}

ObjectList::~ObjectList() {
	delete this;
}

void ObjectList::append_top(GameObject* obj) {

	Node* node = new Node();
	node->object = obj;
	node->id = head->id +1;
	node->prev = head;
	node->next = nullptr;

	if (head != nullptr) {
		head->next = node;
		head = node;
	}
}

void ObjectList::update_all(Uint32 time) {

	Node* tmp = head;
	while (head != NULL) {
		if (head->object != nullptr) {

			head->object->update(time);
			// physics(object list);
		}
		head = head->prev;
	}
	head = tmp;

}

void ObjectList::render_all(SDL_Renderer* parent_renderer) {
	Node* tmp = head;
	while (head != NULL) {
		if (head->object!= nullptr) {
			
			head->object->render(parent_renderer);
		}
		head = head->prev;
	}
	head = tmp;
}

void ObjectList::printList() {

	Node* tmp = head;
	while (head != NULL) {
		head = head->prev;
	}
	head = tmp;
}
