#pragma once
#include "Table.h"


class List {
private:
	Link* first;
	Link* search(const std::string key, int& counter);
public:
	List();
	List(const List&);
	~List();
	void add(const std::string key, int& counter);
	int del(const std::string key, int& counter);
	int get(const std::string key, int& counter);
	void print(int index);
	void print();
	bool is_empty();
	bool is_full();
	void clear();
};