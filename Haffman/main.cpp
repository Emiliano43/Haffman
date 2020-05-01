#include<iostream>
#include"RBtree.h"
#include<string>
#include"solution.h"
using namespace std;



int main() {
	string str;
	string encrypted;
	setlocale(LC_ALL, "Russian");
	cout << "Введите строку: ";
	getline(cin, str);
	CodingTree* haffmanTree = new CodingTree(str);
	RBtree<char, string>* haffman_codes_map = haffmanTree->get_codes_map();
	List<DataCouple<char, int>>* list_symbol = haffmanTree->get_list_of_symbols();
	cout << "Таблица кодов:" << endl;
	cout << "Символ - код : частота встречаемости" << endl;
	for (int i = 0; i < list_symbol->get_size(); i++)
		cout << "   " << list_symbol->at(i).letter<< " - " << haffman_codes_map->find(list_symbol->at(i).letter) << " : " << list_symbol->at(i).frequency << endl;
	cout << "Исходная строка: " << str << endl;
	for (int i = 0; i < str.size(); i++)
		encrypted += haffman_codes_map->find(str[i]);
	cout << "Новая строка: " << encrypted << endl;
	string decoded = haffmanTree->source_string(encrypted);
	cout << "Размер исходной строки = " << decoded.size() * 8 << " бит" << endl;
	cout << "Размер закодированной строки = " << encrypted.size() << " бит" << endl;
	cout << "Коэффициент сжатия: x" << (((double)(decoded.size() * 8) / (encrypted.size()))) << endl;
	delete haffmanTree;
	system("pause");
	return 0;
}