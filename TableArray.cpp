#include "TableArray.h"
#include <iomanip>

void TableArray::add(const std::string& key) {
    if (is_full()) {
        throw std::length_error("В таблице нет места для добавления нового элемента!");
        return;
    }
    
    for (int i = 0; i < counter; ++i) {
        if (entries[i].key == key) {
            entries[i].value += 1; 
            return;
        }    
    } 
    entries[counter].key = key;
    entries[counter].value = 1;
    counter++;
}

int TableArray::del(const std::string& key) {
    for (int i = 0; i < counter; ++i) {
        if (entries[i].key == key) {
            int value = entries[i].value;
            // Сдвигаем все элементы после удаленного влево
            for (int j = i; j < counter - 1; ++j) {
                entries[j] = entries[j + 1];
            }
            counter--;
            return value;
        }
    }
    throw std::length_error("Элемент не был найден");
    return -1; // Указываем, что элемент не найден
}

void TableArray::print() const {
    if (is_empty()) {
        std::cout << "В таблице нет элементов" << std::endl;
        return;
    }

    std::cout << std::setw(30) << std::left << "WORD" <<
        std::setw(30) << std::left << "AMOUNT" << std::endl;

    for (int i = 0; i < counter; i++)
        std::cout << std::setw(30) << std::left << entries[i].key <<
        std::setw(30) << std::left << entries[i].value << std::endl;
}

int TableArray::get(const std::string& key) {
    for (int i = 0; i < counter; ++i) {
        if (entries[i].key == key) {
            return entries[i].value;
        }
    }
    std::cerr << "элемент не найден\n";
    return -1; // Указываем, что элемент не найден
}

bool TableArray::is_empty() const {
    return counter == 0;
}

bool TableArray::is_full() const {
    return counter >= MAX_SIZE;
}
