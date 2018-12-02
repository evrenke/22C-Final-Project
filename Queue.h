//
//  Queue.h
//  22C_Lab_3
//
//  Created by Oh Reum Kwon on 10/28/18.
//  Copyright © 2018 Oh Reum Kwon. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include "sLinkedList.h"

/*
Queue class contains two attributes: the front pointer and rear pointer
This class also implements the most common Queue operations such as enqueue,
dequeue, front, rear, empty, and print function.
*/
template <typename T>
class Queue : private LinkedList<T>
{
private:

public:
	//Default constructor which sets head to null
	Queue()
	{
	}
	~Queue() {}
	void Enqueue(T);
	int getQueueCount();
	T Dequeue();
	T Front() {
		return LinkedList<T>::findAnywhere(LinkedList<T>::countOfItems());
	}
	T Rear()
	{
		return LinkedList<T>::findAnywhere(1);
	}
	void Print();
};

template<typename T>
int Queue<T>::getQueueCount() {
	return LinkedList<T>::countOfItems();
}

template <typename T>
void Queue<T>::Enqueue(T data)
{
	LinkedList<T>::addFirst(data);
}

template <typename T>
T Queue<T>::Dequeue()
{
	return LinkedList<T>::deleteAnywhere(LinkedList<T>::countOfItems() - 1);
}

template <typename T>
void Queue<T>::Print()
{
	LinkedList<T>::print();
}

#endif /* Stack_h */
#pragma once