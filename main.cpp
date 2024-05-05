#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include "UnsortedTable.h";
#include "SortedTable.h"
#include "BSTTable.h"
#include "HashTable.h"
#include "TableArray.h"
#include "TableList.h"

using namespace std;

void read_file(vector <string>& words) {
	string filename, line, word;
	ifstream f;
	words.clear();
	cout << "Введите название файла: ";
	cin >> filename;
	f.open(filename);
	if (!f.is_open())
		throw runtime_error("Не удалось открыть файл!");

	while (getline(f, line)) {
		size_t prev = 0, pos;
		pos = line.find_first_of(" ,;.\t", prev);
		while (pos != string::npos) {
			if (pos > prev) {
				word = line.substr(prev, pos - prev);
				words.push_back(word);
			}
			prev = pos + 1;
			pos = line.find_first_of(" ,;.\t", prev);
		}
		if (prev < line.size())
			words.push_back(line.substr(prev, string::npos));
	}
	f.close();
}

void open_table(Table* table, const vector<string>& words) {
	int exit = 1;
	while (exit) {
		int menu;
		if (dynamic_cast<SortedTable*>(table))
			cout << "Отсортированная таблица:\n";
		else if (dynamic_cast<UnsortedTable*>(table))
			cout << "Неотсортированная таблица:\n";
		else if (dynamic_cast<BSTTable*>(table))
			cout << "Таблица на основе бинарного дерева:\n";
		else if (dynamic_cast<HashTable*>(table))
			cout << "Хеш таблица:\n";
		else if (dynamic_cast<TableArray*>(table))
			cout << "Таблица на массиве:\n";
		else if (dynamic_cast<TableList*>(table))
			cout << "Таблица на списках:\n";

		cout << " 1  внести текст в таблицу\n\
 2  добавить элемент в таблицу\n\
 3  удалить элемент из таблицы\n\
 4  получить элемент из таблицы\n\
 5  вывести таблицу\n";

		if (dynamic_cast<BSTTable*>(table))
			cout << " 6  вывести дерево по уровням\n";

cout << " 0  вернуться к выбору таблицы\n";

		cin >> menu;
		switch (menu) {
		case 1: {
			system("CLS");
			try {
				if (!words.size()) {
					cout << "Сначала нужно ввести текст из файла!" << endl;
					break;
				}

				for (string word : words)
					table->add(word);
				cout << "Слова успешно записаны в  таблицу!\n";
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 2: {
			system("CLS");
			string key;
			cout << "Введите ключ: ";
			cin >> key;
			try {
				table->add(key);
				cout << "Элемент успешно добавлен!\nКоличество операций для добавления: " << table->get_counter() << endl;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 3: {
			system("CLS");
			string key;
			cout << "Введите ключ: ";
			cin >> key;
			table->del(key);
			cout << "Элемент успешно удален!\nКоличество операций для удаления: " << table->get_counter() << endl;
			break;
		}
		case 4: {
			system("CLS");
			int elem;
			string key;
			cout << "Введите ключ: ";
			cin >> key;
			elem = table->get(key);
			cout << key << " - " << elem << endl;
			cout << "Количество операций для поиска элемента : " << table->get_counter() << endl;
			break;
		}
		case 5: {
			system("CLS");
			table->print();
			break;
		}
		case 6: {
			system("CLS");
			BSTTable* tmp;
			tmp = dynamic_cast<BSTTable*>(table);
			if (tmp)
				tmp->print_tree();
			break;
		}
		
		case 0: {
			system("CLS");
			return;
			break;
		}
		default: {
			system("CLS");
			break;
		}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <string> words;
	int exit = 1, menu;
	Table* tables[6] = {new UnsortedTable, new SortedTable, new BSTTable, new HashTable, new TableArray, new TableList};

	while(exit){
		cout << " 1  ввести текст из файла\n\
 2  использовать неотсортированную таблицу\n\
 3  использовать отсортированную таблицу\n\
 4  использовать таблицу на основе бинарного дерева\n\
 5  использовать хеш таблицу\n\
 6  использовать таблицу на массиве \n\
 7 использовать таблицу на списках\n\
 0  завершить работу\n";
		cin >> menu;
		switch (menu) {
		case 1: {
			int type;
			system("CLS");
			try {
				read_file(words);
				cout << "Текст успешно введен!\n";
			}
			catch(exception e){
				cout << e.what() << endl;;
			}
			break;
		}
		case 2: {
			system("CLS");
			open_table(tables[menu - 2], words);
			delete tables[menu - 2];
			tables[menu - 2] = new UnsortedTable;
			break;
		}
		case 3: {
			system("CLS");
			open_table(tables[menu - 2], words);
			delete tables[menu - 2];
			tables[menu - 2] = new SortedTable;
			break;
		}
		case 4: {
			system("CLS");
			open_table(tables[menu - 2], words);
			delete tables[menu - 2];
			tables[menu - 2] = new BSTTable;
			break;
		}
		case 5: {
			system("CLS");
			open_table(tables[menu - 2], words);
			delete tables[menu - 2];
			tables[menu - 2] = new HashTable;
			break;
		}
		case 6: {
			system("CLS");
			open_table(tables[menu - 2], words);
			delete tables[menu - 2];
			tables[menu - 2] = new TableArray;
			break;
		}
		case 7: {
			system("CLS");
			open_table(tables[menu - 2], words);
			delete tables[menu - 2];
			tables[menu - 2] = new TableList;
			break;
		}
		case 0: {
			system("CLS");
			exit = 0;
			break;
		}
		default: {
			system("CLS");
			break;
		}
		}
	}

	for (auto tb : tables)
		delete tb;
}