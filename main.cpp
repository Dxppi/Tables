#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h> 
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
	cout << "������� �������� �����: ";
	cin >> filename;
	f.open(filename);
	if (!f.is_open())
		throw runtime_error("�� ������� ������� ����!");

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

static void compare_search_performance() {
	string key;
	Table* tables[6] = { new UnsortedTable, new SortedTable, new BSTTable, new HashTable, new TableArray, new TableList };
	vector <string> words;
	read_file(words);
	time_t start = 0, end = 0;
	start = clock();
	for (string word : words) {

		tables[0]->add(word);
		tables[1]->add(word);
		tables[2]->add(word);
		tables[3]->add(word);
		tables[4]->add(word);
		tables[5]->add(word);

	}
	double res;

	int elem;

	cout << "������� ����" << endl;
	cin >> key;
	clock_t start_time = clock();

	elem = tables[0]->get(key);
	cout << key << " - " << elem << endl;
	cout << "���������� �������� ��� ������ �������� : " << tables[0]->get_counter() << endl;

	clock_t end_time = clock();
	res = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	cout << "�����: " << res << endl;

	start_time = clock();

	elem = tables[1]->get(key);
	cout << key << " - " << elem << endl;
	cout << "���������� �������� ��� ������ �������� : " << tables[1]->get_counter() << endl;

	end_time = clock();
	res = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	cout << "�����: " << res << endl;
	/*tables[1]->print();*/

	start_time = clock();

	elem = tables[2]->get(key);
	cout << key << " - " << elem << endl;
	cout << "���������� �������� ��� ������ �������� : " << tables[2]->get_counter() << endl;

	end_time = clock();
	res = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	cout << "�����: " << res << endl;


	start_time = clock();

	elem = tables[3]->get(key);
	cout << key << " - " << elem << endl;
	cout << "���������� �������� ��� ������ �������� : " << tables[3]->get_counter() << endl;
	
	end_time = clock();
	res = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	cout << "�����: " << res << endl;

	start_time = clock();


	elem = tables[4]->get(key);
	cout << key << " - " << elem << endl;
	cout << "���������� �������� ��� ������ �������� : " << tables[4]->get_counter() << endl;

	end_time = clock();
	res = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	cout << "�����: " << res << endl;

	start_time = clock();

	elem = tables[5]->get(key);
	cout << key << " - " << elem << endl;
	cout << "���������� �������� ��� ������ �������� : " << tables[5]->get_counter() << endl;

	end_time = clock();
	res = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	cout << "�����: " << res << endl;
	system("pause");
}




void open_table(Table* table, const vector<string>& words) {
	int exit = 1;
	while (exit) {
		int menu;
		if (dynamic_cast<SortedTable*>(table))
			cout << "��������������� �������:\n";
		else if (dynamic_cast<UnsortedTable*>(table))
			cout << "����������������� �������:\n";
		else if (dynamic_cast<BSTTable*>(table))
			cout << "������� �� ������ ��������� ������:\n";
		else if (dynamic_cast<HashTable*>(table))
			cout << "��� �������:\n";
		else if (dynamic_cast<TableArray*>(table))
			cout << "������� �� �������:\n";
		else if (dynamic_cast<TableList*>(table))
			cout << "������� �� �������:\n";

		cout << " 1  ������ ����� � �������\n\
 2  �������� ������� � �������\n\
 3  ������� ������� �� �������\n\
 4  �������� ������� �� �������\n\
 5  ������� �������\n";

		if (dynamic_cast<BSTTable*>(table))
			cout << " 6  ������� ������ �� �������\n";

cout << " 0  ��������� � ������ �������\n";

		cin >> menu;
		switch (menu) {
		case 1: {
			system("CLS");
			try {
				if (!words.size()) {
					cout << "������� ����� ������ ����� �� �����!" << endl;
					break;
				}

				for (string word : words)
					table->add(word);
				cout << "����� ������� �������� �  �������!\n";
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 2: {
			system("CLS");
			string key;
			cout << "������� ����: ";
			cin >> key;
			try {
				table->add(key);
				cout << "������� ������� ��������!\n���������� �������� ��� ����������: " << table->get_counter() << endl;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 3: {
			system("CLS");
			string key;
			cout << "������� ����: ";
			cin >> key;
			table->del(key);
			cout << "������� ������� ������!\n���������� �������� ��� ��������: " << table->get_counter() << endl;
			break;
		}
		case 4: {
			system("CLS");
			int elem;
			string key;
			cout << "������� ����: ";
			cin >> key;
			elem = table->get(key);
			cout << key << " - " << elem << endl;
			cout << "���������� �������� ��� ������ �������� : " << table->get_counter() << endl;
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
		cout << " 1  ������ ����� �� �����\n\
 2  ������������ ����������������� �������\n\
 3  ������������ ��������������� �������\n\
 4  ������������ ������� �� ������ ��������� ������\n\
 5  ������������ ��� �������\n\
 6  ������������ ������� �� ������� \n\
 7  ������������ ������� �� �������\n\
 8  �������� �������� ������ ������\n\
 0  ��������� ������\n";
		cin >> menu;
		switch (menu) {
		case 1: {
			int type;
			system("CLS");
			try {
				read_file(words);
				cout << "����� ������� ������!\n";
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
		case 8: {
			system("CLS");
			compare_search_performance();
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
