#include "List.h"
#include <iostream>
#include <iomanip>

List::List() {
	first = new Link;
	first->next = first;
}

List::List(const List& other) {
	first = new Link;
	Link* cur;
	Link* other_cur;
	Link* tmp;
	cur = first;
	other_cur = other.first->next;
	while (other_cur != other.first) {
		tmp = new Link(*other_cur);
		cur->next = tmp;
		cur = tmp;
		other_cur = other_cur->next;
	}
	cur->next = first;
}

List::~List() {
	Link* tmp, * del;
	tmp = first->next;
	while (tmp != first) {
		del = tmp;
		tmp = tmp->next;
		delete del;
	}
	delete first;
}

Link* List::search(const std::string key, int& counter) {
	Link* cur, * prev;
	prev = first;
	cur = first->next;
	while (cur != first) {
		counter++;
		if (cur->data.key == key)
			break;
		prev = cur;
		cur = cur->next;
	}
	if (cur == first)
		prev = nullptr;
	return prev;
}


void List::add(const std::string key, int& counter) {
	Link* prev, * new_link;
	prev = search(key, counter);
	counter++;

	if (prev == nullptr) {
		if (is_full())
			throw std::length_error("В таблице нет места для добавления нового элемента!");
		new_link = new Link(key, 1);
		new_link->next = first->next;
		first->next = new_link;
	}
	else {
		prev->next->data.value++;
	}
}

int List::del(const std::string key, int& counter) {
	Link* prev, * cur;
	int res = 0;
	prev = search(key, counter);

	if (prev != nullptr) {
		counter++;
		cur = prev->next;
		prev->next = cur->next;
		res = cur->data.value;
		delete cur;
	}

	return res;
}

int List::get(const std::string key, int& counter) {
	Link* prev;
	int res = 0;
	prev = search(key, counter);

	if (prev != nullptr) {
		counter++;
		res = prev->next->data.value;
	}

	return res;
}

void List::print(int index) {
	Link* cur;
	cur = first->next;
	while (cur != first) {
		std::cout << std::setw(30) << std::left << index <<
			std::setw(30) << std::left << cur->data.key <<
			std::setw(30) << std::left << cur->data.value << std::endl;
		cur = cur->next;
	}
}

bool List::is_empty() {
	return first->next == first;
}

bool List::is_full() {
	Link* tmp;
	tmp = new Link;
	bool res = tmp == nullptr;
	delete tmp;
	return res;
}

void List::clear() {
	Link* tmp, * del;
	tmp = first->next;
	while (tmp != first) {
		del = tmp;
		tmp = tmp->next;
		delete del;
	}
	first->next = first;
}

