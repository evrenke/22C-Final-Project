#pragma once
#include "HashNode.h"
#include <string>
template <class ot>
class HashTable {
private:
	HashNode<ot>* arr;
	int size;
	int filledSize = 0;
	//Very basic hashing algorithm
	int hash(std::string key) {
		int total = 0;
		for (int i = 0; i < key.length(); i++) {
			total += key[i];
		}
		total = total % size;
		return total;
	}
	
	//Removes a HashNode that is equal to toRemove
	void remove(HashNode<ot>* toRemove) {
		//If the HashTable is empty
		if (filledSize == 0) {
			return;
		}
		//If the HashTable only has one node
		else if (filledSize == 1) {
			filledSize = 0;
			arr = NULL;
			return;
		}
		//If there is more than one node
		else {
			//If the node to be deleted is equal to the head
			if (toRemove == arr) {
				HashNode<ot> *temp = arr;
				arr = arr->getNext();
				filledSize--;
				delete temp;
			}
			//If the node to be deleted is not the head
			else {
				HashNode<ot> *pPrev = nullptr;//Previous pointer
				HashNode<ot> *pCurr = arr;//Current pointer
				int counter = 0;//Counter starts at 0
				//Traverse the entire HashTable
				while (counter < filledSize)
				{
					pPrev = pCurr;
					pCurr = pCurr->getNext();
					//If found. Break out of the while loop.
					if (pCurr == toRemove) {
						counter = filledSize;
					}
					counter++;
				}
				//Set the previous node of the current which equals toRemove
				//to point to the node that the current points to
				pPrev->setNext(pCurr->getNext());
				filledSize--;//Minus total by 1
				delete pCurr;//Delete the current node
			}
		}
	}
public:
	//Size defaults to 11
	HashTable() {
		arr = new HashNode<ot>[11];
		for (int ind = 0; ind < 11; ind++)
			arr[ind] = HashNode<ot>();
		size = 11;
	}
	//Option for a custom size
	HashTable(int s) {
		arr = new HashNode<ot>[s];
		for (int ind = 0; ind < s; ind++)
			arr[ind] = HashNode<ot>();
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
		filledSize++;
	}

	ot* get(const std::string &key)
	{
		HashNode<ot> *entry = arr + hash(key);
		while (entry != NULL && entry->getKey() != key) {
			entry = entry->getNext();
		}
		if (entry == NULL) return NULL;
		return entry->getData();
	}

	void remove(std::string key) {
		HashNode<ot>* temp = arr + hash(key);
		while (temp != NULL && temp->getKey() != key) {
			temp = temp->getNext();
		}
		if (temp == NULL) return;
		remove(temp);
	}
	void printTable(std::ostream& out) {
		for (int i = 0; i < size; i++) {
			out << i + 1 << ")." << " ";
			if (arr[i].getData() == NULL) 
				out << "NULL";
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
	int getSize()
	{
		return size;
	}
};