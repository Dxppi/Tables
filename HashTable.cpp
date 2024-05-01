#include "HashTable.h"
#include <iostream>
#include <iomanip>

HashTable::HashTable() : Table() {
	entries = new List[SIZE];
}

HashTable::~HashTable() {
	delete[] entries;
}

unsigned int HashTable::get_hash(const std::string& value) {
	unsigned int res = 0;
	for (int i = 0; i < value.size(); i++)
		res += (int)value[i] * (i + 1);
	res %= SIZE;
	return res;
}

void HashTable::add(const std::string& key) {
	counter = 1;
	unsigned int index;
	index = get_hash(key);
	entries[index].add(key, counter);
}

int HashTable::del(const std::string& key) {
	int res;
	unsigned int index;
	counter = 1;
	index = get_hash(key);
	res = entries[index].del(key, counter);
	return res;
}

int HashTable::get(const std::string& key) {
	int res;
	unsigned int index;
	counter = 1;
	index = get_hash(key);
	res = entries[index].get(key, counter);
	return res;

}

void HashTable::print() const {
	if (is_empty()) {
		std::cout << "В таблице нет элементов" << std::endl;
		return;
	}

	std::cout << std::setw(30) << std::left << "INDEX" <<
		std::setw(30) << std::left << "WORD" <<
		std::setw(30) << std::left << "AMOUNT" << std::endl;

	for (int i = 0; i < SIZE; i++)
		if (!entries[i].is_empty())
			entries[i].print(i);
}

bool HashTable::is_empty() const {
	for (int i = 0; i < SIZE; i++)
		if (!entries[i].is_empty())
			return false;
	return true;
}

bool HashTable::is_full() const {
	Link* tmp;
	tmp = new Link;
	return tmp == nullptr;
}