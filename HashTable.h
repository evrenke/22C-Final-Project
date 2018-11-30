#pragma once
#include "HashNode.h"
#include <string>
template <class ot>
class HashTable {
private:
	HashNode<ot>* arr;
	int size;
	//Very basic hashing algorithm
	int hash(std::string key) {
		int total = 0;
		for (int i = 0; i < key.length(); i++) {
			total += key[i];
		}
		total = total % size;
		return total;
	}
	//TODO
	void remove(HashNode<ot>* toRemove) {
	}
public:
	//Size defaults to 11
	HashTable() {
		arr = new HashNode<ot>[11];
		size = 11;
	}
	//Option for a custom size
	HashTable(int s) {
		arr = new HashNode<ot>[s];
		size = s;
	}
	//Adds an object to the table
	void add(std::string key, ot& data) {
		HashNode<ot>* temp = arr + hash(key);
		if (temp->getData() == NULL) {
			temp->setData(data);
			temp->setKey(key);
			return;
		}
		while (temp->getNext() != NULL) {
			temp = temp->getNext();
		}

		HashNode<ot>* add = new HashNode<ot>(data, key);
		temp->setNext(add);
	}
	void remove(std::string key) {
		HashNode<ot>* temp = arr + hash(key);
		while (temp->getKey() != key && temp != NULL) {
			temp = temp->getNext();
		}
		if (temp == NULL) return;
		remove(temp);
	}
	void printTable(std::ostream& out) {
		for (int i = 0; i < size; i++) {
			out << i + 1 << ")." << " ";
			if (arr[i].getData() == NULL) out << "NULL";
			else {
				out << *arr[i].getData();
				HashNode<ot>* temp = arr[i].getNext();
				while (temp != NULL) {
					out << ", " << *temp->getData();
					temp = temp->getNext();
				}
			}
			out << std::endl;
		}
	}
};