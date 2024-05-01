#pragma once
#include "Table.h"


class Queue {
private:
	size_t max_size;
	size_t size;
	Node** elements;
	size_t head;
	size_t tail;
	size_t next_index(size_t);
public:
	explicit Queue(size_t = 1000);
	Queue(const Queue&);
	~Queue();
	void push(Node*);
	Node* pop();
	Node* get_head();
	bool is_full();
	bool is_empty();
};