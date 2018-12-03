//
//  sLinkedList.h
//  22C_Lab_3
//
//  Created by Oh Reum Kwon on 10/28/18.
//  Copyright © 2018 Oh Reum Kwon. All rights reserved.
//

#ifndef sLinkedList_h
#define sLinkedList_h
#include "Node.h"//import the node file

/*
A Singly Linked List ADT which is composed of one or more of our nodes.
Implements the most common linked-list behaviors - new list,
add anywhere, delete anywhere, find anywhere, count of items in the list,
empty the list.
*/
template<class T>
class LinkedList
{
private:
	Node<T> * head;//head is the first node
	Node<T> * tail;//tail is the last node
	int count = 0;//total number of nodes in the list
public:
	LinkedList() {//Default Constructor sets head and tail to NULL
		head = NULL;
		tail = NULL;
	}
	virtual ~LinkedList();//Destructor

	void newList(Node<T> *newNode);
	void addLast(T val);
	void addFirst(T val);
	void addAnywhere(T val, int pos);
	T deleteAnywhere(int pos);
	T findAnywhere(int pos);
	int countOfItems();
	void emptyList();
	void print();
};



template<class T>
LinkedList<T>::~LinkedList()
{
	Node<T> * pCurr = head;
	while (head)
	{
		head = head->getNext();
		//delete pCurr;
		//pCurr = head;
	}
}

template <class T>
void LinkedList<T>::newList(Node<T> *newNode)
{
	head = newNode;
	tail = newNode;
}

template<class T>
void LinkedList<T>::addLast(T val)
{
	Node<T> * newNode = new Node<T>(val);
	count++;
	if (tail == NULL)
	{
		newNode->setNext(tail);
		tail = newNode;
		head = newNode;
		return;
	}
	tail->setNext(newNode);
	tail = tail->getNext();
}

template<class T>
void LinkedList<T>::addFirst(T val)
{
	Node<T> * newNode = new Node<T>(val);
	newNode->setNext(head);
	head = newNode;
	count++;
	if (head->getNext() == NULL)
		tail = newNode;
}

template<class T>
void LinkedList<T>::addAnywhere(T val, int pos)
{
	if (pos == 0)
	{
		addFirst(val);
		count++;
	}
	else if (pos == count)
	{
		addLast(val);
		count++;
	}
	else if (pos > count || pos < 0)
	{
		std::cout << "Out of Bounds Error at Position: " << pos << std::endl;
	}
	else
	{
		Node<T> *n = new Node<T>(val);
		int counter = 0;
		Node<T> *current = head;

		while (counter < pos - 1)
		{
			current = current->getNext();
			counter++;
		}
		Node<T> *temp = current->getNext();
		current->setNext(n);
		n->setNext(temp);
		count++;
	}
}

template<class T>
T LinkedList<T>::deleteAnywhere(int pos)
{
	if (pos == 0)
	{
		Node<T> *temp = head;
		if (count == 1)
		{
			count = 0;
			head = NULL;
			return temp->getData();
		}
		else
		{
			head = head->getNext();
			count--;
			//std::cout << "Deleting " << temp->getData() << std::endl;
			return temp->getData();
			delete temp;
		}

	}
	else if (pos > count || pos < 0)
	{
		std::cout << "Out of Bounds Error at Position: " << pos << std::endl;
		//return NULL;
	}
	else
	{
		Node<T> *pPrev = nullptr;
		Node<T> *pCurr = head;
		int counter = 0;
		while (counter < pos)
		{
			pPrev = pCurr;
			pCurr = pCurr->getNext();
			counter++;
		}
		pPrev->setNext(pCurr->getNext());
		//std::cout << "Deleting: " << pCurr->getData() << std::endl;
		count--;
		return pCurr->getData();
		delete pCurr;
	}
}

template <class T>
T LinkedList<T>::findAnywhere(int pos)
{
	if (pos == 0) {
		return head->getData();
	}
	Node<T> *pCurr = head;
	if (head == NULL)
	{
		std::cout << "The List is empty!" << std::endl;
		//return NULL;
	}
	else if (pos > count || pos < 0)
	{
		std::cout << "Out of Bounds Error at Position: " << pos << std::endl;
		//return NULL;
	}
	else
	{
		int counter = 0;
		while (counter < pos)
		{
			pCurr = pCurr->getNext();
			counter++;
		}
		return pCurr->getData();
	}
}

template <class T>
int LinkedList<T>::countOfItems()
{
	return count;
}

template <class T>
void LinkedList<T>::emptyList()
{
	if (head == NULL)
	{
		std::cout << "The List is already empty!" << std::endl;
	}
	else
	{
		Node<T> *temp = head;
		while (temp != NULL)
		{
			head = head->getNext();
			delete temp;
			temp = head;
			count--;
		}
	}
}


template<class T>
void LinkedList<T>::print()
{
	Node<T> * pCurr = head;
	while (pCurr)
	{
		std::cout << pCurr->getData() << " --> ";
		pCurr = pCurr->getNext();
	}
	std::cout << "NULL" << std::endl;
}


#endif /* sLinkedList_h */