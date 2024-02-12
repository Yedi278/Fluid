#include "ObjectList.h"
#include <iostream>


ObjectList::ObjectList() {
	head = new List();
}

ObjectList::~ObjectList() {
	delete this;
}

void ObjectList::append_top(GameObject* obj) {

	List* node = new List();
	node->object = obj;
	node->prev = head;
	node->next = nullptr;

	if (head != nullptr) {
		head->next = node;
		head = node;
	}
}

void ObjectList::update_all(Uint32 time) {

	List* tmp = head;
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
	List* tmp = head;
	while (head != NULL) {
		if (head->object!= nullptr) {
			
			head->object->render(parent_renderer);
		}
		head = head->prev;
	}
	head = tmp;
}

void ObjectList::printList() {
	List* tmp = head;
	while (head != NULL) {
		head = head->prev;
	}
	head = tmp;
}