#include "Table.h"
#include "Stack.h"


class BSTTable : public Table {
private:
	Node* root;
	void balance_after_add(Node* node, Stack* stack);
	void balance_after_del(bool del_node_is_right, Stack* stack);
	void balance(Node*& parent, Node* prev_parent);
	void left_rotate(Node*& parent, Node* prev_parent);
	void right_rotate(Node*& parent, Node* prev_parent);
	void big_left_rotate(Node*& parent, Node* prev_parent);
	void big_right_rotate(Node*& parent, Node* prev_parent);
	void delete_tree(Node* node);
	void rec_print_tree(Node* node) const;
public:
	BSTTable();
	~BSTTable();
	void add(const std::string& key) override;
	int del(const std::string& key) override;
	int get(const std::string& key) override;
	void print() const override;
	void print_tree() const;
	bool is_empty() const override;
	bool is_full() const override;
};