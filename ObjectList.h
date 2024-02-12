#pragma once
#include "GameObject.h"

struct List {

	List* prev = nullptr;

	GameObject* object = nullptr;

	List* next = nullptr;

};


class ObjectList
{
private:


public:

	struct List* head = nullptr;
	ObjectList();
	~ObjectList();
	void append_top(GameObject* obj);
	void printList();
	void update_all(Uint32 time);
	void render_all(SDL_Renderer* parent_renderer);
};
