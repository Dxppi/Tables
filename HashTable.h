#include "Table.h"
#include "List.h"

class HashTable : public Table {
private:
	List* entries;
	static const int SIZE = 10001;
	unsigned int get_hash(const std::string& value);
public:
	HashTable();
	~HashTable();
	void add(const std::string& key);
	int del(const std::string& key);
	int get(const std::string& key);
	void print() const;
	bool is_empty() const;
	bool is_full() const;
};