#include "ObjectList.h"

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