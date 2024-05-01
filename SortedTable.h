#include "UnsortedTable.h"

class SortedTable :public UnsortedTable {
private:
	int binary_search(const std::string& key);
public:
	explicit SortedTable(int MAX_SIZE = 100) : UnsortedTable(MAX_SIZE) {};
	SortedTable(const SortedTable& other) : UnsortedTable(other) {};
	void add(const std::string& key) override;
	int del(const std::string& key) override;
	int get(const std::string& key) override;
};