#include "queue.h"
#include <stdexcept>


Queue::Queue(size_t sz) : max_size(sz), size(0), head(0), tail(0) {
	if (sz < 1)
		throw std::range_error("Размер очереди должен быть положительным значением");
	elements = new Node * [max_size];
}

Queue::Queue(const Queue& other) : max_size(other.max_size),
size(other.size), head(other.head), tail(other.tail) {
	elements = new Node * [max_size];
	for (int i = 0; i < max_size; i++)
		elements[i] = other.elements[i];
}

Queue::~Queue() {
	delete[] elements;
}

size_t Queue::next_index(size_t cur_index) {
	return (cur_index + 1) % max_size;
}

void Queue::push(Node* elem) {
	elements[tail] = elem;
	tail = next_index(tail);
	size++;
}

Node* Queue::pop() {
	Node* elem = elements[head];
	head = next_index(head);
	size--;
	return elem;
}

Node* Queue::get_head() {
	return elements[head];
}

bool Queue::is_full() {
	return size == max_size;
}

bool Queue::is_empty() {
	return !size;
}
