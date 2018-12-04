#pragma once
#include "BinaryNode.h"
template <class T>
class BST {
private:
	//Returns the left/rightmost node below a certain root (inclusive of the root itself)
	BinaryNode<T>* getRightmost(BinaryNode<T>* head)
	{
		BinaryNode<T>* temp = head;
		while (temp->getRightChild() != nullptr)
		{
			temp = temp->getRightChild();
		}
		return temp;
	}
	BinaryNode<T>* getLeftmost(BinaryNode<T>* head)
	{
		BinaryNode<T>* temp = head;
		while (temp->getLeftChild() != nullptr)
		{
			temp = temp->getLeftChild();
		}
		return temp;
	}
public:
	BinaryNode<T>* root;
	BST() { root = NULL; }
	BST(T *head) { root = new BinaryNode<T>(head); }
	//Don't worry the children are deleted in the BinaryNode destructor
	~BST()
	{
		delete root;
		root = nullptr;
	}

	//Overloads using Person are a wrapper for the BinaryNode version so you don't need to manually define the node.
	//Other one may still be called with no issue if there is a Node that must be added.
	void add(T *toAdd)
	{
		BinaryNode<T>* pNode = new BinaryNode<T>(toAdd);
		add(pNode);
	}
	void add(BinaryNode<T>* pNode)
	{
		if (root == NULL)
		{
			root = pNode;
			return;
		}
		BinaryNode<T>* temp = root;
		while (true)
		{
			if (pNode->getData() < temp->getData())
			{
				if (temp->getLeftChild() == nullptr)
				{
					temp->setLeftChild(pNode);
					return;
				}
				temp = temp->getLeftChild();
			}
			else
			{
				if (temp->getRightChild() == nullptr)
				{
					temp->setRightChild(pNode);
					return;
				}
				temp = temp->getRightChild();
			}
		}
	}

	//Returns NULL if none is found. Beware of carelessly dereferencing it
	BinaryNode<T>* search(T data)
	{
		BinaryNode<T>* pSearch = root;
		while (true)
		{
			if (pSearch->getData() == data)
			{
				return pSearch->getData();
			}
			else if (pSearch->getData() > data)
			{
				if (pSearch->getLeftChild() == nullptr) return nullptr;
				pSearch = pSearch->getLeftChild();
			}
			else
			{
				if (pSearch->getRightChild() == nullptr) return nullptr;
				pSearch = pSearch->getRightChild();
			}
		}
	}

	void remove(T toRemove)
	{
		BinaryNode<T>** pSearch = &root;
		while (toRemove != (*pSearch)->getData())
		{
			if ((*pSearch)->getData() > toRemove) {
				if ((*pSearch)->getLeftChild() == nullptr)
					break;
				*pSearch = (*pSearch)->getLeftChild();
			}
			else if ((*pSearch)->getData() < toRemove) {
				if ((*pSearch)->getRightChild() == nullptr)
					break;
				*pSearch = (*pSearch)->getRightChild();
			}
		}
		remove(pSearch);
	}
	BinaryNode<T> * DeleteNodeInBST(BinaryNode<T>* root, int data)
	{
		if (root == NULL) return root;
		else if (data <= root->getData())
			root->setLeftChild(DeleteNodeInBST(root->getLeftChild(), data));
		else if (data> root->getData())
			root->setRightChild(DeleteNodeInBST(root->getRightChild(), data));
		else
		{
			//No child
			if (root->getRightChild() == nullptr && root->getLeftChild() == nullptr)
			{
				delete root;
				root = nullptr;
			}
			//One child 
			else if (root->getRightChild() == nullptr)
			{
				BinaryNode<T>* temp = root;
				root = root->getLeftChild();
				delete temp;
			}
			else if (root->getLeftChild() == nullptr)
			{
				BinaryNode<T>* temp = root;
				root = root->getRightChild();
				delete temp;
			}
			//two child
			else
			{
				BinaryNode<T>* temp = findmax(root);
				root->setData(temp->getData());
				root->setLeftChild(DeleteNodeInBST(root->getLeftChild(), temp->getData()));
			}
		}
		return root;
	}
	BinaryNode<T>* FindMax(BinaryNode<T>* root)
	{
		if (root == nullptr)
			return nullptr;

		while (root->getRightChild() != nullptr)
		{
			root = root->getRightChild();
		}
		return root;
	}
};