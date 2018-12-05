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
protected:
	BinaryNode<T>* searchAsNode(BinaryNode<T> *pSearch, T data)
	{
		if (root == nullptr || *(root->getData()) == data)
			return root;//returns node or nullptr

						// Key is greater than root's key 
		if (*(root->getData()) < data)
			return searchAsNode(root->getRightChild(), data);

		// Key is smaller than root's key 
		return searchAsNode(root->getLeftChild(), data);
	}

	BinaryNode<T> * remove(T toRemove)
	{
		return DeleteNodeInBST(root, toRemove);
	}
	BinaryNode<T> * DeleteNodeInBST(BinaryNode<T>* root, T data)
	{
		if (root == NULL) return root;
		else if (data < root->getData())
			root->setLeftChild(DeleteNodeInBST(root->getLeftChild(), data));
		else if (data > root->getData())
			root->setRightChild(DeleteNodeInBST(root->getRightChild(), data));
		else
		{

			if (root->getLeftChild() == nullptr)
			{
				BinaryNode<T> *temp = root->getRightChild();
				free(root);
				return temp;
			}
			else if (root->getRightChild() == nullptr)
			{
				BinaryNode<T> *temp = root->getLeftChild();
				free(root);
				return temp;
			}
			// node with two children: Get the inorder successor (smallest 
			// in the right subtree) 
			BinaryNode<T> temp = getLeftmost(root->getRightChild());

			// Copy the inorder successor's content to this node 
			root->setData(temp.getData());

			// Delete the inorder successor 
			root->setRightChild(DeleteNodeInBST(root->getRightChild(), temp.getData()));
		}
		return root;
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

	//Overloads using T are a wrapper for the BinaryNode version so you don't need to manually define the node.
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
			else // >=
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
		std::cout << "Now searching: " << *data << std::endl;
		return searchAsNode(root, data);
	}
};