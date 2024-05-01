#include <iostream>
#include <iomanip>
#include "BSTTable.h"
#include "queue.h"


BSTTable::BSTTable() : Table(), root(nullptr) {};

void BSTTable::add(const std::string& key) {
	Node* prev;
	Node* cur;
	Node* new_node;
	Stack* stack;
	stack = new Stack;
	prev = nullptr;

	counter = 1;
	if (is_empty()) {
		root = new Node(key, 1);
		return;
	}

	cur = root;
	while (cur != nullptr) {
		counter++;
		if (cur->data.key == key) {
			cur->data.value += 1;
			return;
		}
		else if (key > cur->data.key) {
			stack->push(cur);
			prev = cur;
			cur = cur->right;
		}
		else {
			stack->push(cur);
			prev = cur;
			cur = cur->left;
		}
	}

	counter++;
	if (is_full())
		throw std::length_error("В таблице нет места для добавления нового элемента!");

	new_node = new Node(key, 1);
	if (key > prev->data.key)
		prev->right = new_node;
	else
		prev->left = new_node;

	balance_after_add(new_node, stack);
}

int BSTTable::del(const std::string& key) {
	int res = 0;
	Node* cur;
	Node* prev;
	Node* replacement;
	Stack* stack;
	bool del_node_is_right = true;

	counter = 0;
	stack = new Stack;
	cur = root;
	bool is_find = false;
	while (cur != nullptr) {
		counter++;

		if (cur->data.key == key) {
			is_find = true;
			break;
		}
		else if (key > cur->data.key) {
			stack->push(cur);
			cur = cur->right;
		}
		else {
			stack->push(cur);
			cur = cur->left;
		}

	}

	counter++;
	if (!is_find)
		return res;
	else {
		res = cur->data.value;

		if (cur == root && root->right == nullptr && root->left == nullptr) {
			delete root;
			root = nullptr;
			return res;
		}
	}

	counter++;
	if (stack->is_empty())
		prev = nullptr;
	else
		prev = stack->top();
	if (cur->left == nullptr && cur->right == nullptr) {
		if (prev->left == cur) {
			del_node_is_right = false;
			prev->left = nullptr;
		}
		else
			prev->right = nullptr;
	}
	else if (cur->left == nullptr) {
		if (prev != nullptr)
			if (prev->left == cur) {
				del_node_is_right = false;
				prev->left = cur->right;
			}
			else
				prev->right = cur->right;
		else
			root = cur->right;
	}
	else if (cur->right == nullptr) {
		if (prev != nullptr)
			if (prev->left == cur) {
				del_node_is_right = false;
				prev->left = cur->left;
			}
			else
				prev->right = cur->left;
		else
			root = cur->left;
	}
	else {
		stack->push(cur);
		replacement = cur->left;

		if (replacement->right == nullptr) {
			del_node_is_right = false;
			cur->data = replacement->data;
			cur->left = replacement->left;
			cur = replacement;
		}

		else {
			while (replacement->right != nullptr) {
				counter++;
				stack->push(replacement);
				replacement = replacement->right;
			}
			cur->data = replacement->data;
			stack->top()->right = replacement->left;
			cur = replacement;
		}
	}
	delete cur;
	balance_after_del(del_node_is_right, stack);
	return res;
}

int BSTTable::get(const std::string& key) {
	int res = 0;
	Node* cur;
	counter = 1;
	cur = root;
	while (cur != nullptr) {
		counter++;
		if (cur->data.key == key) {
			res = cur->data.value;
			break;
		}
		else if (key > cur->data.key)
			cur = cur->right;
		else
			cur = cur->left;
	}
	return res;
}

void BSTTable::balance(Node*& parent, Node* prev_parent) {
	if (parent->dif == -2)
		if (parent->right->dif > 0)
			big_left_rotate(parent, prev_parent);
		else
			left_rotate(parent, prev_parent);
	else if (parent->dif == 2)
		if (parent->left->dif < 0)
			big_right_rotate(parent, prev_parent);
		else
			right_rotate(parent, prev_parent);
}

void BSTTable::balance_after_del(bool del_node_is_right, Stack* stack) {
	Node* parent;
	Node* child;
	Node* prev_parent;

	child = stack->top();
	while (!stack->is_empty()) {
		counter++;
		parent = stack->pop();
		if (parent->right == child || (parent == child && del_node_is_right))
			parent->dif += 1;
		else
			parent->dif -= 1;
		prev_parent = nullptr;
		if (!stack->is_empty())
			prev_parent = stack->top();

		balance(parent, prev_parent);

		if (parent->dif != 0)
			break;
		child = parent;
	}
	delete stack;
}

void BSTTable::balance_after_add(Node* child, Stack* stack) {
	Node* parent, * prev_parent;
	while (!stack->is_empty()) {
		counter++;
		parent = stack->pop();
		if (parent->right == child)
			parent->dif -= 1;
		else
			parent->dif += 1;

		prev_parent = nullptr;
		if (!stack->is_empty())
			prev_parent = stack->top();

		balance(parent, prev_parent);

		if (parent->dif == 0)
			break;
		child = parent;
	}
	delete stack;
}

void BSTTable::left_rotate(Node*& parent, Node* prev_parent) {
	Node* right;
	right = parent->right;
	if (prev_parent != nullptr) {
		if (prev_parent->right == parent)
			prev_parent->right = right;
		else
			prev_parent->left = right;
	}
	else
		root = right;

	if (right->dif == 0)
		parent->dif = -1;
	else
		parent->dif = 0;
	right->dif += 1;

	parent->right = right->left;
	right->left = parent;
	parent = right;
}

void BSTTable::right_rotate(Node*& parent, Node* prev_parent) {
	Node* left;
	left = parent->left;
	if (prev_parent != nullptr) {
		if (prev_parent->right == parent)
			prev_parent->right = left;
		else
			prev_parent->left = left;
	}
	else
		root = left;

	if (left->dif == 0)
		parent->dif = 1;
	else
		parent->dif = 0;
	left->dif -= 1;

	parent->left = left->right;
	left->right = parent;
	parent = left;
}

void BSTTable::big_left_rotate(Node*& parent, Node* prev_parent) {
	int old_dif = parent->right->left->dif;
	Node* right = parent->right;
	right_rotate(right, parent);
	left_rotate(parent, prev_parent);
	parent->dif = 0;
	if (old_dif == 0) {
		parent->left->dif = 0;
		parent->right->dif = 0;
	}
	else if (old_dif == 1) {
		parent->left->dif = 0;
		parent->right->dif = -1;
	}
	else if (old_dif == -1) {
		parent->left->dif = 1;
		parent->right->dif = 0;
	}

}

void BSTTable::big_right_rotate(Node*& parent, Node* prev_parent) {
	int old_dif = parent->left->right->dif;
	Node* left = parent->left;
	left_rotate(left, parent);
	right_rotate(parent, prev_parent);
	parent->dif = 0;
	if (old_dif == 0) {
		parent->left->dif = 0;
		parent->right->dif = 0;
	}
	else if (old_dif == 1) {
		parent->left->dif = -1;
		parent->right->dif = 0;
	}
	else if (old_dif == -1) {
		parent->left->dif = 0;
		parent->right->dif = 1;
	}
}

bool BSTTable::is_empty() const {
	return root == nullptr;
}

bool BSTTable::is_full() const {
	bool res = false;
	Node* check;
	check = new Node;
	if (check == nullptr)
		res = true;
	delete check;
	return res;
}

void BSTTable::print() const {
	if (is_empty()) {
		std::cout << "В таблице нет элементов" << std::endl;
		return;
	}
	std::cout << std::setw(30) << std::left << "WORD" <<
		std::setw(30) << std::left << "AMOUNT" << std::endl;
	rec_print_tree(root);
}

void BSTTable::rec_print_tree(Node* node) const {
	if (node->left != nullptr)
		rec_print_tree(node->left);

	std::cout << std::setw(30) << std::left << node->data.key <<
		std::setw(30) << std::left << node->data.value << std::endl;

	if (node->right != nullptr)
		rec_print_tree(node->right);
}

void BSTTable::print_tree() const {
	Node* last;
	Node* parent;
	Node* child;
	Queue queue;

	if (root == nullptr) {
		std::cout << "Пустое дерево\n";
		return;
	}

	last = root;
	queue.push(root);
	while (!queue.is_empty()) {
		child = nullptr;
		parent = queue.pop();
		std::cout << '(' << parent->data.key << ", " << parent->data.value << ")\t";

		if (parent->left != nullptr) {
			child = parent->left;
			queue.push(child);
		}


		if (parent->right != nullptr) {
			child = parent->right;
			queue.push(child);
		}

		if (parent == last) {
			std::cout << '\n';
			last = child;
		}
	}
	std::cout << '\n';
}

void BSTTable::delete_tree(Node* node) {
	if (node == nullptr)
		return;
	if (node->left != nullptr)
		delete_tree(node->left);
	if (node->right != nullptr)
		delete_tree(node->right);
	delete node;
}

BSTTable::~BSTTable() {
	delete_tree(root);
}


