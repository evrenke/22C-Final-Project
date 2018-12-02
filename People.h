//
//  BstNode.h
//  22C_Lab_5
//
//  Created by Oh Reum Kwon and Tommaso Framba on 11/21/18.
//

#ifndef People_h
#define People_h
#include "Node.h"

/*
BstNode class contains four attributes: name, birthday, right pointer, and left pointer.
This class also has multiple get functions and set functions to access the attributes.
*/
template<class T>
class People : private Node<T>
{
private:
	std::string name;
	std::string birthday;
	Node<T>* peopleNode;
	People<T> * right;
	People<T> * left;
public:
	People<T>()
	{
		left = nullptr;
		right = nullptr;
	}
	/*
	Constructor which sets
	next pointer to null
	*/
	People<T>(const T& n, const T& b, int a)
	{
		name = n;
		birthday = b;
		left = nullptr;
		right = nullptr;
	}
	T getData(int);
	T getName();
	T getBirthday();
	People<T> *getLeft();
	People<T> *getRight();
	void setRight(People<T> *newNext);
	void setLeft(People<T> *newNext);
	void setName(T);
	void setBirthday(T);
};

/*
Getter method that returns name
*/
template <class T>
void People<T>::setBirthday(T data)
{
	birthday = data;
}

/*
Getter method that returns name
*/
template <class T>
void People<T>::setName(T data)
{
	name = data;
}

/*
Getter method that returns name
*/
template <class T>
T People<T>::getName()
{
	if (name != "")return name;
}

/*
Getter method that returns birthday
*/
template <class T>
T People<T>::getBirthday()
{
	if(birthday != "")return birthday;
}

/*
Getter method that returns name if input is 1
and returns birthday if input is 2
*/
template <class T>
T People<T>::getData(int type)
{
	if (type == 1) {
		return name;
	}
	else if (type == 2) {
		return birthday;
	}
}

/*
Getter method that returns left pointer
*/
template<class T>
People<T>* People<T>::getLeft()
{
	return left;
}

/*
Getter method that returns right pointer
*/
template<class T>
People<T>* People<T>::getRight()
{
	return right;
}

/*
Setter method which sets right pointer to new BstNode
that is passed through the parameter
*/
template <class T>
void People<T>::setRight(People<T> *newNext)
{

	if (newNext == NULL)
	{
		right = NULL;
	}
	else
	{
		right = newNext;
	}
}

/*
Setter method which sets left pointer to new BstNode
that is passed through the parameter
*/
template <class T>
void People<T>::setLeft(People<T> *newNext)
{

	if (newNext == NULL)
	{
		left = NULL;
	}
	else
	{
		left = newNext;
	}
}
#endif /* BST_Node_h */