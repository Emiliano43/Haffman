#pragma once
#include<iostream>
using namespace std;
template<typename T1>
class List
{
private:
	class Node {
	public:
		Node(T1 value = T1(), Node* next = nullptr) {
			this->value = value;
			this->next = next;
		}
		Node* next;
		T1 value;
	};

	Node* head;
	Node* tail;
	int size;

	void swap(T1& a, T1& b) {
		T1 c = a;
		a = b;
		b = c;
	}

	void divide(T1* mas, int first, int last)
	{
		T1 mid;
		int f = first, l = last;
		mid = mas[(f + l) / 2];
		do
		{
			while (mas[f] < mid) f++;
			while (mas[l] > mid) l--;
			if (f <= l)
			{
				swap(mas[f], mas[l]);
				f++;
				l--;
			}
		} while (f < l);
		if (first < l) divide(mas, first, l);
		if (f < last) divide(mas, f, last);
	}
public:
	List(Node* head = nullptr, Node* tail = nullptr, int Size = 0) :head(head), tail(tail), size(Size) {}
	~List() {
		if (head != nullptr) {
			this->clear();
		}
	};

	void push_back(T1 obj) {
		if (head != nullptr) {
			this->tail->next = new Node(obj);
			tail = tail->next;
		}
		else {
			this->head = new Node(obj);
			this->tail = this->head;
		}
		size++;
	}

	void push_front(T1 obj) {
		if (head != nullptr) {
			Node* current = new Node;
			current->value = obj;
			current->next = this->head;
			this->head = current;
		}
		else {
			this->head = new Node(obj);
		}
		this->size++;
	}
	void pop_back() {
		if (head != nullptr) {
			Node* current = head;
			while (current->next != tail)
				current = current->next;
			delete tail;
			tail = current;
			tail->next = nullptr;
			size--;
		}
		else throw std::out_of_range("out_of_range");
	}

	void pop_front() {
		if (head != nullptr) {
			Node* current = head;
			head = head->next;
			delete current;
			size--;
		}
		else throw std::out_of_range("out_of_range");
	}

	void insert(T1 obj, size_t k) {
		if (k >= 0 && this->size > k) {
			if (this->head != nullptr) {
				if (k == 0)
					this->push_front(obj);
				else
					if (k == this->size - 1)
						this->push_back(obj);
					else
					{
						Node* current = new Node;
						Node* current1 = head;
						for (int i = 0; i < k - 1; i++) {
							current1 = current1->next;
						}
						current->value = obj;
						current->next = current1->next;
						current1->next = current;
						size++;
					}
			}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	T1 at(size_t k) {
		if (this->head != nullptr && k >= 0 && k <= this->size - 1) {
			if (k == 0)
				return this->head->value;
			else
				if (k == this->size - 1)
					return this->tail->value;
				else
				{
					Node* current = head;
					for (int i = 0; i < k; i++) {
						current = current->next;
					}
					return current->value;
				}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	void remove(int k) {
		if (head != nullptr && k >= 0 && k <= size - 1) {
			if (k == 0) this->pop_front();
			else
				if (k == this->size - 1) this->pop_back();
				else
					if (k != 0) {
						Node* current = head;
						for (int i = 0; i < k - 1; i++) {
							current = current->next;
						}

						Node* current1 = current->next;
						current->next = current->next->Next;
						delete current1;
						size--;
					}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	size_t get_size() {
		return size;
	}

	void print_to_console() {
		if (this->head != nullptr) {
			Node* current = head;
			for (int i = 0; i < size; i++) {
				cout << current->value << ' ';
				current = current->next;
			}
		}
	}

	void clear() {
		if (head != nullptr) {
			Node* current = head;
			while (head != nullptr) {
				current = current->next;
				delete head;
				head = current;
			}
			size = 0;
		}
	}

	void set(size_t k, T1 obj) {
		if (this->head != nullptr && this->get_size() >= k && k >= 0) {
			Node* current = head;
			for (int i = 0; i < k; i++) {
				current = current->next;
			}
			current->value = obj;
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	bool isEmpty() {
		return (bool)(head);
	}

	void sort() {
		T1* array = new T1[this->size];
		Node* cur = head;
		int i = 0;
		while (cur != nullptr) {
			array[i] = cur->value;
			cur = cur->next;
			i++;
		}
		divide(array, 0, this->size - 1);
		cur = head;
		i = 0;
		while (cur != nullptr) {
			cur->value = array[i];
			cur = cur->next;
			i++;
		}
	}
};
