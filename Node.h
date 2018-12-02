//
//  Node.h
//  22C_Lab_3
//
//  Created by Oh Reum Kwon on 10/28/18.
//  Copyright © 2018 Oh Reum Kwon. All rights reserved.
//

#ifndef Node_h
#define Node_h

/*
Node class contains two attributes: data and a node pointer.
This class also has 2 get functions and one set function.
*/
template<class T>
class Node
{
private:
	T data;
	Node<T> * next;
public:
	Node<T>() {}
	/*
	Constructor which sets data to d and
	sets next pointer to null
	*/
	Node<T>(const T& d)
	{
		data = d;
		next = nullptr;
	}
	T getData();
	Node<T> *getNext();
	void setNext(Node<T> *newNext);

};

/*
Getter method that returns data inside the node
*/
template <class T>
T Node<T>::getData()
{
	return data;
}

/*
Getter method that returns next pointer
*/
template<class T>
Node<T>* Node<T>::getNext()
{
	return next;
}

/*
Stter method which sets next pointer to new node
that is passed through the parameter
*/
template <class T>
void Node<T>::setNext(Node<T> *newNext)
{
	if (newNext == NULL)
	{
		next = NULL;
	}
	else
	{
		next = newNext;
	}
}
#endif /* Node_h */