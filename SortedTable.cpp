#include <stdexcept>
#include "SortedTable.h"


int SortedTable::binary_search(const std::string& key) {
	int l, r, m;
	l = 0;
	r = cur_size - 1;
	while (l <= r) {
		counter++;
		m = (l + r) / 2;
		if (entries[m].key == key)
			return m;
		else if (entries[m].key > key)
			r = m - 1;
		else
			l = m + 1;
	}
	return l;
}


void SortedTable::add(const std::string& key) {
	int index;
	counter = 0;
	if (is_empty()) {
		counter++;
		entries[cur_size].key = key;
		entries[cur_size].value = 1;
		cur_size++;
		return;
	}

	index = binary_search(key);
	if (index < cur_size && entries[index].key == key)
		entries[index].value += 1;
	else
		if (is_full())
			throw std::length_error("В таблице нет места для добавления нового элемента!");
		else {
			for (int i = cur_size - 1; i >= index; i--) {
				counter++;
				entries[i + 1] = entries[i];
			}
			entries[index].key = key;
			entries[index].value = 1;
			cur_size++;
			counter++;

		}
}

int SortedTable::del(const std::string& key) {
	counter = 1;
	int res = 0;
	int index;
	if (is_empty())
		return res;

	index = binary_search(key);
	if (index < cur_size && entries[index].key == key) {
		res = entries[index].value;
		for (int i = index + 1; i < cur_size; i++) {
			counter++;
			entries[i - 1] = entries[i];
		}
		cur_size--;
		counter++;
	}
	return res;
}

int SortedTable::get(const std::string& key) {
	counter = 1;
	int res = 0;
	int index;
	if (is_empty())
		return res;
	index = binary_search(key);
	if (index < cur_size && entries[index].key == key)
		res = entries[index].value;
	return res;
}
