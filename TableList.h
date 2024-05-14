
#include "Table.h"
#include "List.h"
#include <string>

class TableList : public Table {
	private:
		List* entries;
		static const int SIZE = 120001;
	public:
		TableList();
		~TableList();
		void add(const std::string& key);
		int del(const std::string& key);
		int get(const std::string& key);
		void print() const;
		bool is_empty() const;
		bool is_full() const;
};