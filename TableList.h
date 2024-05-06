#ifndef TABLELIST_H
#define TABLELIST_H
#include "Table.h"
#include "List.h"
#include <string>

class TableList : public Table {
private:
	List* entries;
	static const int SIZE =120002;

public:
	TableList();
	~TableList();
	void add(const std::string& item)override;
	int del(const std::string& item);
	void print() const override;
	int get(const std::string& item);
	bool is_empty() const;
	bool is_full()const;
};

#endif
