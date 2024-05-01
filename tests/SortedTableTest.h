#include "SortedTable.h"

class SortedTableTest: public SortedTable {
public:
	SortedTableTest(): SortedTable() {};
	SortedTableTest(int cz, Entry* entr) {
		cur_size = cz;
		entries = entr;
	}
	Entry* get_entries() { return entries; }
	int get_size() { return cur_size; }
};

void add_sorted_table_test();
void del_sorted_table_test();
void get_sorted_table_test();
void run_sorted_table_tests();