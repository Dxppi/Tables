#pragma once
#include "Table.h"


class Stack {
private:
	size_t max_size;
	size_t cur_size;
	Node** elements;
public:
	explicit Stack(size_t = 1000);
	Stack(const Stack&);
	~Stack();
	bool is_empty();
	bool is_full();
	void push(Node*);
	Node* pop();
	Node* top();
};