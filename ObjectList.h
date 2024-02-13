#pragma once
#include "GameObject.h"

struct ArrayNode{
	int id=0;
	GameObject* obj = nullptr;
};

class ObjectArray{

private:
	SDL_Renderer* rndr = nullptr;

public:
	int size = 0;
	Uint8 r = 10;
	ArrayNode* array = nullptr;
	ObjectArray(SDL_Renderer* rndr, int size);
	~ObjectArray();
	
	void init(SDL_Window* window);
	void printArray();
	void update_all();
	void render_all();
	void add(GameObject* obj);
	
};

//////////////////////////////////////


struct Node {

	Node* prev = nullptr;

	Uint32 id=0;
	GameObject* object = nullptr;

	Node* next = nullptr;

};

class ObjectList
{
private:

public:
	struct Node* head = nullptr;

	ObjectList();
	~ObjectList();

	void printList();

	void append_top(GameObject* obj);
	void update_all(Uint32 time);
	void render_all(SDL_Renderer* parent_renderer);
};
