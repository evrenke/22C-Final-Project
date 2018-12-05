#pragma once
#include "BinaryNode.h"

class ContactBST {
private:
	//Returns the left/rightmost node below a certain root (inclusive of the root itself)
	BinaryNode<Contact *>* getRightmost(BinaryNode<Contact *>* head)
	{
		BinaryNode<Contact *>* temp = head;
		while (temp->getRightChild() != nullptr)
		{
			temp = temp->getRightChild();
		}
		return temp;
	}
	BinaryNode<Contact *>* getLeftmost(BinaryNode<Contact *> * head)
	{
		BinaryNode<Contact *>* temp = head;
		while (temp->getLeftChild() != nullptr)
		{
			temp = temp->getLeftChild();
		}
		return temp;
	}
protected:
	void add(BinaryNode<Contact *>* pNode)
	{
		if (root == NULL)
		{
			root = pNode;
			return;
		}
		BinaryNode<Contact *>* temp = root;
		while (true)
		{
			if (*(pNode->getData()) < *(temp->getData()))
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
	BinaryNode<Contact *>* searchAsNode(BinaryNode<Contact *> *pSearch, Contact * data)
	{
		if (root == nullptr || *(root->getData()) == *data)
			return root;//returns node or nullptr

						// Key is greater than root's key 
		if (*(root->getData()) < *data)
			return searchAsNode(root->getRightChild(), data);

		// Key is smaller than root's key 
		return searchAsNode(root->getLeftChild(), data);
	}

	BinaryNode<Contact *> * DeleteNodeInBST(BinaryNode<Contact *>* root, Contact * data)
	{
		if (root == nullptr) return root;
		else if (*data < *(root->getData()))
			root->setLeftChild(DeleteNodeInBST(root->getLeftChild(), data));
		else if (*data > *(root->getData()))
			root->setRightChild(DeleteNodeInBST(root->getRightChild(), data));
		else
		{

			if (root->getLeftChild() == nullptr)
			{
				BinaryNode<Contact *> *temp = root->getRightChild();
				free(root);
				return temp;
			}
			else if (root->getRightChild() == nullptr)
			{
				BinaryNode<Contact *> *temp = root->getLeftChild();
				free(root);
				return temp;
			}
			// node with two children: Get the inorder successor (smallest 
			// in the right subtree) 
			BinaryNode<Contact *> *temp = getLeftmost(root->getRightChild());

			// Copy the inorder successor's content to this node 
			root->setInfo(temp->getData());

			// Delete the inorder successor 
			root->setRightChild(DeleteNodeInBST(root->getRightChild(), temp->getData()));
		}
		return root;
	}
public:
	BinaryNode<Contact *>* root;
	ContactBST() { root = nullptr; }
	ContactBST(Contact *head) { root = new BinaryNode<Contact *> (head); }
	//Don't worry the children are deleted in the BinaryNode destructor
	~ContactBST()
	{
		delete root;
		root = nullptr;
	}

	//Overloads using T are a wrapper for the BinaryNode version so you don't need to manually define the node.
	//Other one may still be called with no issue if there is a Node that must be added.
	void add(Contact * toAdd)
	{
		BinaryNode<Contact *>* pNode = new BinaryNode<Contact *>(toAdd);
		add(pNode);
	}

	//Returns NULL if none is found. Beware of carelessly dereferencing it
	BinaryNode<Contact *>* search(Contact * data)
	{
		return searchAsNode(root, data);
	}

	BinaryNode<Contact *> * remove(Contact * toRemove)
	{
		return DeleteNodeInBST(root, toRemove);
	}
};