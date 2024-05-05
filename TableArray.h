#ifndef TABLEARRAY_H
#define TABLEARRAY_H
#include <string>
#include "Table.h"
#include <iostream>

class TableArray : public Table {
private:
	std::string* data;
	const int capacity;

public:
	TableArray(int capacity = 100);
	~TableArray() override;
	void add(const std::string& item) override;
	int del(const std::string& item) override;
	void print() const override;
	int get(const std::string& item);
	bool is_empty() const override;;
	bool is_full() const override;;
};

#endif
