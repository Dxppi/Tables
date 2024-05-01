#pragma once
#include <string>


struct Entry {
	std::string key;
	int value;
};

class Node {
public:
	Node* left;
	Node* right;
	int dif;
	Entry data;
	Node(const std::string& key = "", int val = 0) :left(nullptr), right(nullptr), dif(0) {
		data.key = key;
		data.value = val;
	}
};

class Link {
public:
	Entry data;
	Link* next;
	Link(const std::string& key = "", int val = 0) : next(nullptr) {
		data.key = key;
		data.value = val;
	}
	Link(Link& other) : data(other.data), next(other.next) {}

};

class Table {
protected:
	int counter;
public:
	Table() : counter(0) {};
	virtual ~Table() {};
	virtual void add(const std::string&) = 0;
	virtual int del(const std::string&) = 0;
	virtual void print() const = 0;
	virtual int get(const std::string&) = 0;
	virtual bool is_empty() const = 0;
	virtual bool is_full() const = 0;
	virtual int get_counter() { return counter; }
};