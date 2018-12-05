//
//  Location.h
//  22C_Project
//
//  Created by Ohreum, Tommaso, Evren, Jason on 11/16/18.

#pragma once
#include "Node.h"
/*
 This class has two private pointers: left and right child.
 It also has getter and setter methods for the pointers and information
 */
template<class ot>
class BinaryNode : public Node<ot> {
private:
	BinaryNode<ot>* rightChild;
	BinaryNode<ot>* leftChild;
public:
    //Default constructor
	BinaryNode() {
		//setData(nullptr);
		setLeftChild(nullptr);
		setRightChild(nullptr);
	}
	BinaryNode(ot object) {
		this->setData(object);
	}
    //returns left child
	BinaryNode<ot>* getLeftChild() { return leftChild; }
    //sets left child
	void setLeftChild(BinaryNode<ot>* in) { leftChild = in; }
    //returns right child
	BinaryNode<ot>* getRightChild() { return rightChild; }
    //sets right child
	void setRightChild(BinaryNode<ot>* in) { rightChild = in; }
    //returns data inside
	const ot getInfo() { return this->getData(); }
    //sets data inside
	void setInfo(ot in) { this->setData(in); }

	//Deletes all nodes below to prevent memory leaks. Deleting the root will delete the entire tree.
	//If removing a single node from the tree is desired, use the remove function within the BST class instead.
	~BinaryNode() {
		//delete this->getData();
		delete rightChild;
		delete leftChild;
	}
};
