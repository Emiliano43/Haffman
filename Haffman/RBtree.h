#pragma once
#define RED true
#define BLACK false

#include"List_.h"
#include"DataCouple.h"
#include<string>

using namespace std;

template<typename T1, typename T2>
class RBtree {
public:
	class Node
	{
	public:
		Node(bool color = RED, T1 key = T1(), Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, T2 value = T2()) :color(color), key(key), parent(parent), left(left), right(right), value(value) {}
		T1 key;
		T2 value;
		bool color;
		Node* parent;
		Node* left;
		Node* right;
	};
	RBtree(Node* Top = nullptr, Node* Leaf = new Node(0)) :root(Top), leaf(Leaf) {}
	~RBtree() {
		if (this->root != nullptr)
			this->clear();
		root = nullptr;
		delete leaf;
		leaf = nullptr;
	}

	void  insert(T1 key, T2 value) {

		if (this->root != nullptr) {
			Node* node = nullptr;
			Node* parent = nullptr;
			for (node = this->root; node != leaf; )// Search leaf for new element 
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else if (key > node->key)
					node = node->right;
				else if (key == node->key)
					throw out_of_range("key is repeated");
			}
			node = new Node(RED, key, leaf, leaf, leaf, value);
			node->parent = parent;
			if (parent != leaf) {
				if (key < parent->key)
					parent->left = node;
				else
					parent->right = node;
			}
			balance(node);
		}
		else {
			this->root = new Node(BLACK, key, leaf, leaf, leaf, value);
		}
	}

	List<DataCouple<T1, T2>>* get_pairs() {
		List<DataCouple<T1, T2>>* list = new List<DataCouple<T1, T2>>();
		this->ListPairs(root, list);
		return list;
	}

	List<T1>* get_keys() {
		List<T1>* list = new List<T1>();
		this->ListKeyOrValue(1, list);
		return list;
	}

	List<T2>* get_values() {
		List<T2>* list = new List<T2>();
		this->ListKeyOrValue(2, list);
		return list;
	}

	T2 find(T1 key) {
		Node* node = root;
		while (node != leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != leaf)
			return node->value;
		else
			throw std::out_of_range("Key is missing");
	}

	void clear() {
		this->delAlltree(this->root);
		this->root = nullptr;
	}

	bool is_in_map(T1 key) {
		Node* node = root;
		while (node != nullptr && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != nullptr)
			return true;
		else
			return false;
	}

	void add_entry(T1 key) {
		Node* current = this->get_node(key);
		current->value++;
	}

	void remove(T1 key) {
		Node* needed = root;
		while (needed->key != key) {
			if (needed->key < key)
				needed = needed->right;
			else
				needed = needed->left;
		}
		deleteNode(needed);
	}

private:
	Node* root;
	Node* leaf;

	Node* get_node(T1 key) {
		Node* node = root;

		while (node != leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != leaf)
			return node;

	}

	void deleteNode(Node* current) {				//delete node current from tree
		Node* fixed, *changed;
		if (!current || current == leaf) return;
		
		if (current->left == leaf || current->right == leaf) {					//changed has a Leaf node as a child
			changed = current;
		}
		else {
			changed = current->right;											//find tree successor with a Leaf node as a child
			while (changed->left != leaf) changed = changed->left;
		}
		if (changed->left != leaf)												//fixed is changed's only child
			fixed = changed->left;
		else
			fixed = changed->right;

		fixed->parent = changed->parent;										//remove changed from the parent chain
		if (changed->parent)
			if (changed == changed->parent->left)
				changed->parent->left = fixed;
			else
				changed->parent->right = fixed;
		else
			root = fixed;

		if (changed != current) {
			current->key = changed->key;
			current->value = changed->value;
		}

		if (changed->color == BLACK)
			balance(fixed);
	}

	void delAlltree(Node* tree) {
		if (tree != leaf) {
			delAlltree(tree->left);
			delAlltree(tree->right);
			delete tree;
		}
	}

	void ListKeyOrValue(int mode, List<T1>* list) {
		if (this->root != leaf)
			this->KeyOrValue(root, list, mode);
		else
			throw std::out_of_range("Tree empty!");
	}
	void KeyOrValue(Node* tree, List<T1>* list, int mode) {

		if (tree != leaf) {
			KeyOrValue(tree->left, list, mode);
			if (mode == 1)
				list->push_back(tree->key);
			else
				list->push_back(tree->value);
			KeyOrValue(tree->right, list, mode);
		}
	}

	Node* minValueNode(Node* node) {					//returns a minimal left node
		while (node->left != leaf)
		{
			node = node->left;
		}
		return node;
	}
	Node* maxValueNode(Node* node) {					//returns a maximal right node
		while (node->right != leaf)
		{
			node = node->right;
		}
		return node;
	}
	void ListPairs(Node* tree, List<DataCouple<T1, T2>>* list) {
		if (tree != leaf) {
			ListPairs(tree->left, list);
			DataCouple<T1, T2> current(tree->key, tree->value);
			list->push_back(current);
			ListPairs(tree->right, list);
		}
	}
	
	Node* grandparent(Node* cur) {
		if ((cur != leaf) && (cur->parent != leaf))
			return cur->parent->parent;
		else
			return leaf;
	}

	Node* uncle(Node* cur) {
		Node* cur1 = grandparent(cur);						//auxiliary node
		if (cur1 == leaf)
			return leaf;									// No grandparent means no uncle
		if (cur->parent == cur1->left)
			return cur1->right;
		else
			return cur1->left;
	}

	Node* brother(Node* cur) {
		if (cur == cur->parent->left)
			return cur->parent->right;
		else
			return cur->parent->left;
	}

	Node* find_key(T1 key) {
		Node* node = this->root;
		while (node != leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != leaf)
			return node;
		else
			throw out_of_range("Key is missing");
	}

	void balance(Node* node) {
		Node* uncle;
		while (node != this->root && node->parent->color == RED)					//current node is red
		{
			if (node->parent == this->grandparent(node)->left)						//node in left tree of grandfather
			{
				uncle = this->uncle(node);
				if (uncle->color == RED) {											//ñase 1 - uncle is red
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {																//cases 2 and 3 - uncle is black
					if (node == node->parent->right) {					
						node = node->parent;
						this->left_rotate(node);
					}
					node->parent->color = BLACK;									//ñase 3
					this->grandparent(node)->color = RED;
					this->right_rotate(this->grandparent(node));
				}
			}
			else {																	//if node in right tree of grandfather
				uncle = this->uncle(node);
				if (uncle->color == RED) {										//uncle is red
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {															//uncle is black
					if (node == node->parent->left) {
						node = node->parent;
						this->right_rotate(node);
					}
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->left_rotate(this->grandparent(node));
				}
			}
		}
		this->root->color = BLACK;
	}

	void left_rotate(Node* node) {
		Node* right = node->right;
		node->right = right->left;
		if (right->left != leaf)
			right->left->parent = node;
		if (right != leaf)
			right->parent = node->parent;
		if (node->parent != leaf) {
			if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		else {
			this->root = right;
		}
		right->left = node;
		if (node != leaf)
			node->parent = right;
	}
	void right_rotate(Node* node) {
		Node* left = node->left;
		node->left = left->right;
		if (left->right != leaf)
			left->right->parent = node;
		if (left != leaf)
			left->parent = node->parent;
		if (node->parent != leaf) {
			if (node == node->parent->right)
				node->parent->right = left;
			else
				node->parent->left = left;
		}
		else {
			this->root = left;
		}
		left->right = node;
		if (node != leaf)
			node->parent = left;
	}
};