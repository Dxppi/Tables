#include <iostream>
#include <iomanip>
#include "UnsortedTable.h"


UnsortedTable::UnsortedTable(int ms) : Table(), MAX_SIZE(ms), cur_size(0) {
	entries = new Entry[MAX_SIZE];
}

UnsortedTable::UnsortedTable(const UnsortedTable& other) : Table(), MAX_SIZE(other.MAX_SIZE), cur_size(other.cur_size) {
	entries = new Entry[MAX_SIZE];
	for (int i = 0; i < cur_size; i++)
		entries[i] = other.entries[i];
}

UnsortedTable:: ~UnsortedTable() {
	delete[] entries;
}

int UnsortedTable::search(const std::string& key) {
	for (int i = 0; i < cur_size; i++) {
		counter++;
		if (entries[i].key == key)
			return i;
	}
	return -1;
}

void UnsortedTable::add(const std::string& key) {
	int search_res;
	counter = 1;
	search_res = search(key);
	if (search_res > -1)
		entries[search_res].value++;
	else {
		if (is_full())
			throw std::length_error("В таблице нет места для добавления нового элемента!");
		else {
			entries[cur_size].key = key;
			entries[cur_size].value = 1;
			cur_size++;
		}
	}
}

int UnsortedTable::del(const std::string& key) {
	int res = 0;
	int search_res;
	counter = 0;
	search_res = search(key);
	if (search_res > -1) {
		counter++;
		res = entries[search_res].value;
		cur_size--;
		entries[search_res] = entries[cur_size];
	}
	return res;
}

int UnsortedTable::get(const std::string& key) {
	int res = 0;
	int search_res;
	counter = 0;
	search_res = search(key);
	if (search_res > -1)
		res = entries[search_res].value;
	return res;
}

bool UnsortedTable::is_empty() const {
	return !cur_size;
}

bool UnsortedTable::is_full() const {
	return cur_size == MAX_SIZE;
}

void UnsortedTable::print() const {
	if (is_empty()) {
		std::cout << "В таблице нет элементов" << std::endl;
		return;
	}

	std::cout << std::setw(30) << std::left << "WORD" <<
		std::setw(30) << std::left << "AMOUNT" << std::endl;
	for (int i = 0; i < cur_size; i++)
		std::cout << std::setw(30) << std::left << entries[i].key <<
		std::setw(30) << std::left << entries[i].value << std::endl;
}



