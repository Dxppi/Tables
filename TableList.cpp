#include "TableList.h"
#include <iostream>
#include <iomanip>

TableList::TableList() {
    entries = new List[SIZE];
}

TableList::~TableList() {
    delete[] entries;
}

void TableList::add(const std::string& item) {

  counter = 1;
  entries->add(item, counter);
}

int TableList::del(const std::string& item) {
    counter = 1;
    return entries->del(item, counter);
}

void TableList::print() const {
    if (is_empty()) {
        std::cout << "В таблице нет элементов" << std::endl;
        return;
    }
        std::cout<<
        std::setw(30) << std::left << "WORD" <<
        std::setw(30) << std::left << "AMOUNT" << std::endl;

    for (int i = 0; i < SIZE; i++)
        if (!entries[i].is_empty())
            entries[i].print(i);
}

int TableList::get(const std::string& item) {
  int res;
  counter = 1;
  res = entries->get(item, counter);
  return res;
}

bool TableList::is_empty() const {
    for (int i = 0; i < SIZE; i++)
        if (!entries[i].is_empty())
            return false;
    return true;
}

bool TableList::is_full() const{
    Link* tmp;
    tmp = new Link;
    return tmp == nullptr;
}
