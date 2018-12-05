#pragma once

template <class ObjectType>
class Node
{
private:
	Node * ptr;
	ObjectType object;
protected:
	void setData(ObjectType ot) {
		object = ot;
	}
public:
	Node() {
		ptr = nullptr;
		object = NULL;
	}
	Node(Node *nextPtr, ObjectType ot)
	{
		ptr = nextPtr;
		object = ot;
	}
	Node(ObjectType ot)
	{
		ptr = nullptr;
		object = ot;
	}

	//Returns the pointer to the next Node
	Node* getNext() {
		return ptr;
	}

	void setNext(Node* nextPtr) {
		ptr = nextPtr;
	}

	//Returns the pointer to the object within the Node
	ObjectType getData() {
		return object;
	}

	~Node()
	{
	}
};