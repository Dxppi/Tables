#include "TableArray.h"
#include <iomanip>


TableArray::TableArray(int capacity) : capacity(capacity) {
    data = new std::string[capacity];
    counter = 0;
}

TableArray::~TableArray()  {
    delete[] data;
}

void TableArray::add(const std::string& item)  {
    if (is_full()) {
        throw std::length_error("Недостаточно места для добавления нового элемента");
    }
    data[counter] = item;
    counter++;
}

int TableArray::del(const std::string& item)  {
    int deleted = 0;
    for (int i = 0; i < counter; i++) {
        if (data[i] == item) {
            // Shift 
            for (int j = i; j < counter - 1; j++) {
                data[j] = data[j + 1];
            }
            counter--;
            deleted++;
        }
    }
    return deleted;
}

void TableArray::print() const {

    if (is_empty()) {
        std::cout << "В таблице нет элементов" << std::endl;
        return;
    }

    std::cout <<
        std::setw(30) << std::left << "WORD" <<
        std::setw(30) << std::endl;

    for (int i = 0; i < capacity; i++)
        std::cout << std::setw(30) << std::left << data[i];
}

int TableArray::get(const std::string& item)  {
    int count = 0;
    for (int i = 0; i < counter; i++) {
        if (data[i] == item) {
            count++;
        }
    }
    return count;
}

bool TableArray::is_empty() const {
    return counter == 0;
}

bool TableArray::is_full() const  {
    return counter == capacity;
}
