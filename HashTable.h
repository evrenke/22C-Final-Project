#pragma once
#include "HashNode.h"
#include <string>
template <class ot>
class HashTable {
private:
	int length;
	//Very basic hashing algorithm
	int hash(std::string key) {
		int total = 0;
		for (unsigned int i = 0; i < key.length(); i++) {
			total += key[i];
		}
		total = total % length;
		return total;
	}
	
	//Removes a HashNode that is equal to toRemove
	void remove(HashNode<ot>* toRemove) {
		//If the HashTable is empty
		if (length == 0) {
			return;
		}
		//If the HashTable only has one node
		else if (length == 1) {
			length = 0;
			arr = nullptr;
			return;
		}
		//If there is more than one node
		else {
			//If the node to be deleted is equal to the head of its list
			if (toRemove->getNext() == nullptr) {
				toRemove->setData(nullptr);
				toRemove->setKey("");
			}
			//If the node to be deleted is not the head
			else {
				HashNode<ot> *pPrev = nullptr;//Previous pointer
				HashNode<ot> *pCurr = toRemove;//Current pointer

				//Traverse the entire HashTable
				while (pCurr->getNext() != nullptr && pCurr->getKey() != toRemove->getKey())
				{
					pPrev = pCurr;
					pCurr = pCurr->getNext();
				}
				//Set the previous node of the current which equals toRemove
				//to point to the node that the current points to
				pPrev->setNext(pCurr->getNext());
				if(pCurr->getNext() == nullptr)
					delete pCurr;//Delete the current node
			}
		}
	}
public:
	HashNode<ot>* arr;
	//Size defaults to 11
	HashTable() {
		arr = new HashNode<ot>[11];
		length = 11;
	}
	//Option for a custom size
	HashTable(int s) {
		arr = new HashNode<ot>[s];
		length = s;
	}
	//Adds an object to the table
	void add(std::string key, ot data) {
		HashNode<ot>* temp = arr + hash(key);
		if (temp->getData() == nullptr) {
			temp->setData(data);
			temp->setKey(key);
			return;
		}
		while (temp->getNext() != nullptr) {
			temp = temp->getNext();
		}

		HashNode<ot>* add = new HashNode<ot>(data, key);
		temp->setNext(add);
	}

	ot* search(const std::string key)
	{
		HashNode<ot> *entry = (arr + hash(key));
		if (entry == nullptr) return nullptr;
		if (entry->getKey() == key)
			return entry->getData();
		while (entry->getKey() != key && entry->getNext() != nullptr) {
			entry = entry->getNext();
		}
		if (entry->getKey() == key)
			return entry->getData();
		return nullptr;
	}

	void remove(std::string key) {
		HashNode<ot>* temp = arr + hash(key);
		while (temp != nullptr && temp->getKey() != key) {
			temp = temp->getNext();
		}
		if (temp == nullptr) return;
		remove(temp);
	}
	void printTable(std::ostream& out) {
		for (int i = 0; i < length; i++) {
			out << i + 1 << ")." << " ";
			if (arr[i].getData() == nullptr)
				out << "NULL";
			else {
				out << *arr[i].getData();
				HashNode<ot>* temp = arr[i].getNext();
				while (temp != nullptr) {
					out << ", " << *temp->getData();
					temp = temp->getNext();
				}
			}
			out << std::endl;
		}
	}
	int getSize()
	{
		return length;
	}
};