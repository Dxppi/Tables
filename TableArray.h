#include <string>
#include "Table.h"
#include <iostream>

class TableArray : public Table {
private:
    static const int MAX_SIZE = 100001; // Максимальный размер массива
    Entry entries[MAX_SIZE];

public:
    TableArray() : Table() {}
    void add(const std::string& key) override;
    int del(const std::string& key) override;
    void print() const override;
    int get(const std::string& key) override;
    bool is_empty() const override;
    bool is_full() const override;
};