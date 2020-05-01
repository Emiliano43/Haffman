#include "stdafx.h"
#include "CppUnitTest.h"
#include"../Haffman/solution.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Haffman_
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(test_random_string)
		{
			string str = "Hello";
			string encrypted;
			CodingTree* haffmanTree = new CodingTree(str);
			RBtree<char, string>* hoffman = haffmanTree->get_codes_map();
			List<DataCouple<char, int>>* list_symbol = haffmanTree -> get_list_of_symbols();
			for (int i = 0; i < str.size(); i++)
				encrypted += hoffman->find(str[i]);
			Assert::AreEqual(encrypted, string("1001111100"));
		}
		TEST_METHOD(text_function_decoding)
		{
			string str = "Fools admire, but men of sense approve";
			string encrypted;
			CodingTree* haffmanTree = new CodingTree(str);
			RBtree<char, string>* hoffman = haffmanTree->get_codes_map();
			List<DataCouple<char, int>>* list_symbol = haffmanTree -> get_list_of_symbols();
			for (int i = 0; i < str.size(); i++)
				encrypted += hoffman->find(str[i]);
			string decoded = haffmanTree->source_string(encrypted);
			Assert::AreEqual(str, decoded);
		}

	};
}