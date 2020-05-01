#pragma once
#include"List_.h"
#include"RBtree.h"
#include"DataCouple.h"
#include<string>
class CodingTree
{
	class Node {
	public:
		Node(DataCouple<char, int> couple = DataCouple<char, int>(), Node* left = nullptr, Node* right = nullptr) :couple(couple), left(left), right(right) {}
		DataCouple<char, int> couple;
		Node* left;
		Node* right;
	};
public:
	~CodingTree() {
		this->delAlltree(top);
	}
	CodingTree(string str) {
		RBtree<char, int>* map_of_symbols = new RBtree<char, int>();
		list_of_symbols = new List<DataCouple<char, int>>();
		for (int i = 0; i < str.size(); i++) {
			if (!map_of_symbols->is_in_map(str[i]))							//if the symbol is not in map then add symbol to map else increase the number of entries
				map_of_symbols->insert(str[i], 1);
			else
				map_of_symbols->add_entry(str[i]);
		}
		list_of_symbols = map_of_symbols->get_pairs();
		map_of_symbols->clear();
		list_of_symbols->sort();
		
		List<Node>* list_of_haffman_nodes = new List<Node>();				//build haffman tree
		for (int i = 0; i < list_of_symbols->get_size(); i++)
			list_of_haffman_nodes->push_back(Node(list_of_symbols->at(i)));
		build_tree(list_of_haffman_nodes);
	}
	List<DataCouple<char, int>>* get_list_of_symbols() {
		return list_of_symbols;
	}
	RBtree<char, string>*& get_codes_map() {
		RBtree<char, string>* haffman_codes_map = new RBtree<char, string>();
		string current;
		add_codes(haffman_codes_map, top, current);
		return haffman_codes_map;
	}
	string source_string(string& encrypted) {
		string decoded;
		int pos = 0;
		decode(top, encrypted, decoded, pos);
		return decoded;
	}
private:
	Node* top;
	List<DataCouple<char, int>>* list_of_symbols;

	void decode(Node* root, string& encrypted, string& decoded, int& position) {
		if (encrypted.size() > position) {
			while (root->right != nullptr && root->left != nullptr) {
				if (encrypted[position] == '0')
					root = root->left;
				else
					root = root->right;
				position++;
			}
			decoded += root->couple.letter;
			if (top->left == nullptr && top->right == nullptr)
				position++;
			decode(top, encrypted, decoded, position);
		}
	}
	void build_tree(List<Node>*& list_of_haffman_nodes) {
		top = nullptr;
		if (list_of_haffman_nodes->get_size() > 1) {
			while (list_of_haffman_nodes->get_size() != 0) {
				Node* current = new Node();
				current->left = new Node(list_of_haffman_nodes->at(0));
				current->right = new Node(list_of_haffman_nodes->at(1));
				current->couple.frequency = list_of_haffman_nodes->at(0).couple.frequency + list_of_haffman_nodes->at(1).couple.frequency;
				list_of_haffman_nodes->pop_front();
				list_of_haffman_nodes->pop_front();
				int i = 0;
				for (; i < list_of_haffman_nodes->get_size() && list_of_haffman_nodes->at(i).couple.frequency < current->couple.frequency; i++);
				if (list_of_haffman_nodes->get_size() != 0 && list_of_haffman_nodes->get_size() != i)
					list_of_haffman_nodes->insert(*current, i);
				else
					if (list_of_haffman_nodes->get_size() == i && list_of_haffman_nodes->get_size() != 0)
						list_of_haffman_nodes->push_back(*current);
				if (list_of_haffman_nodes->get_size() == 0) {
					top = current;
				}
			}
		}
		else {
			top = new Node(DataCouple<char, int>(list_of_haffman_nodes->at(0).couple.letter, list_of_haffman_nodes->at(0).couple.frequency));
		}
	}
	void add_codes(RBtree<char, string>* haffman_codes_map, Node* root, string current) {
		if (top->left != nullptr && top->right != nullptr) {
			if (root->left != nullptr && root->right != nullptr) {
				add_codes(haffman_codes_map, root->left, current + '0');
				add_codes(haffman_codes_map, root->right, current + '1');
			}
			else
			{
				haffman_codes_map->insert(root->couple.letter, current);
			}
		}
		else {
			haffman_codes_map->insert(root->couple.letter, current + '0');
		}
	}
	void delAlltree(Node* tree) {
		if (tree != nullptr) {
			delAlltree(tree->left);
			delAlltree(tree->right);
			delete tree;
		}
	}
};