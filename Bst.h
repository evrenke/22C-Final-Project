//
//  Bst.h
//  22C_Lab_5
//
//  Created by Oh Reum Kwon and Tommaso Framba on 11/23/18.
//

#ifndef Bst_h
#define Bst_h
#include "People.h"
#include "Queue.h"
#include <fstream>

/*
Binary Search Tree that uses Binary Search Tree Nodes to store in a
Binary Search Tree manner. The tree can print in different configurations
and can insert and create new nodes.

Name inserts alphabetically
Birthday inserts by older date is larger
*/
template <typename T>
class Bst
{
private:
	int count;
	int type;//Name or Birthday tree
	People<T>* root;//root node at the top of tree
	std::string deleteStr;
	std::ofstream namePrint;//To print to namesoutput
	std::ofstream inputPrint;//to print to birthdaysoutput
public:
	//Default constructor which sets head to null
	Bst()
	{
		count = 0;
		namePrint.open("Output.txt", std::ofstream::app);
		root = NULL;
	}
	~Bst() {
		namePrint.close();
		inputPrint.close();
	}
	//Methods used by Binary Tree
	People<T> *CreateNewNode(std::string, std::string);
	People<T>* Insert(People<T>*, std::string, std::string);
	void addBstNode(std::string, std::string);
	void setType(int);

	//Printing Methods
	void Preorder(People<T>*);
	void PrintPreorder();
	void Postorder(People<T>*);
	void PrintPostorder();
	void Inorder(People<T>*);
	void PrintInorder();
	void BreadthFirst(People<T>*);
	void PrintBreadthFirst();
	void PrintTreeToFile();
	void PrintToFile(People<T>*);
	void PrintTree2D();
	void Print2D(People<T>*, int);
	int getCount();
	People<T>* FindMin(People<T>*);
	People<T>* Delete(People<T>*, T);
	std::string DeleteValue(T);
	People<T>* Search(People<T>*, T);
	People<T>* SearchValue(T);
};

template <typename T>
void Bst<T>::PrintTree2D() {
	if (count>0) {
		std::cout << "2D representation of Tree:" << endl;
		Print2D(root, 0);
		std::cout << endl << endl;
	}
}

template <typename T>
void Bst<T>::Print2D(People<T> *root, int space) {
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += count;

	// Process right child first 
	Print2D(root->getRight(), space);

	// Print current node after space 
	// count 
	std::cout << "\n";
	for (int i = count; i < space; i++)
		std::cout << " ";
	std::cout << root->getName() << endl;

	// Process left child 
	Print2D(root->getLeft(), space);
}


//Save The Input Data:
template <typename T>
void Bst<T>::PrintTreeToFile() {
	inputPrint.open("InputData.txt");
	if (count>0) {
		PrintToFile(root);
	}
}

template <typename T>
void Bst<T>::PrintToFile(People<T> *rootDel) {
	Queue<People<T>>* q = new Queue<People<T>>();
	q->Enqueue(*rootDel);
	inputPrint << rootDel->getName() << std::endl << rootDel->getBirthday() << std::endl;

	while (q->getQueueCount() > 0)
	{
		People<T> n = q->Dequeue();
		if (n.getLeft() != NULL)
		{
			inputPrint << n.getLeft()->getName() << std::endl << n.getLeft()->getBirthday() << std::endl;
			q->Enqueue(*n.getLeft());
		}
		if (n.getRight() != NULL)
		{
			inputPrint << n.getRight()->getName() << std::endl << n.getRight()->getBirthday() << std::endl;
			q->Enqueue(*n.getRight());
		}
	}
}

template <typename T>
People<T>* Bst<T>::SearchValue(T data) {
	return Search(root, data);
}

template <typename T>
People<T>* Bst<T>::Search(People<T> *root, T data) {
	if (root == NULL) {
		return NULL;
	}
	else if (root->getData(type) == data) {
		return root;
	}
	else if (data <= root->getData(type)) {
		return Search(root->getLeft(), data);
	}
	else {
		return Search(root->getRight(), data);
	}
}

template <typename T>
std::string Bst<T>::DeleteValue(T data) {
	if (count == 1) {
		count = 0;
		delete root;
		root = NULL;
	}
	else {
		count--;
		Delete(root, data);
	}
	return deleteStr;
}

//Function to find minimum in a tree. 
template <typename T>
People<T>* Bst<T>::FindMin(People<T>* root)
{
	while (root->getLeft() != NULL) root = root->getLeft();
	return root;
}

template <typename T>
People<T>* Bst<T>::Delete(People<T> *rootDel, T data) {
	if (rootDel == NULL) return rootDel;
	else if (data < rootDel->getData(type)) rootDel->setLeft(Delete(rootDel->getLeft(), data));
	else if (data > rootDel->getData(type)) rootDel->setRight(Delete(rootDel->getRight(), data));
	else {
		// Case 1:  No child
		if (rootDel->getLeft() == NULL && rootDel->getRight() == NULL) {
			if (root == rootDel) {
				delete root;
				root = NULL;
				count = 0;
			}
			delete rootDel;
			rootDel = NULL;
		}
		//Case 2: One child 
		else if (rootDel->getLeft() == NULL) {
			
			People<T> *temp = rootDel;
			if (root == rootDel) {
				root = rootDel->getRight();
			}
			else {
				rootDel = rootDel->getRight();
			}
			delete temp;
			
		}
		else if (rootDel->getRight() == NULL) {
			People<T> *temp = rootDel;
			if (root == rootDel) {
				root = rootDel->getLeft();
			}
			else {
				rootDel = rootDel->getLeft();
			}
			delete temp;

		}
		// case 3: 2 children
		else {
			if (root == rootDel) {
				People<T> *temp = FindMin(rootDel->getRight());
				root->getData(type) = temp->getData(type);
				root->setRight(Delete(rootDel->getRight(), temp->getData(type)));
				delete temp;
			}
			else {
				People<T> *temp = FindMin(rootDel->getRight());
				rootDel->getData(type) = temp->getData(type);
				rootDel->setRight(Delete(rootDel->getRight(), temp->getData(type)));
				delete temp;
			}
		}
	}
	return rootDel;
}

//Returns count of binary search tree
template <typename T>
int Bst<T>::getCount() {
	return count;
}

//Prints Tree Breadth First
template <typename T>
void Bst<T>::PrintBreadthFirst() {
	BreadthFirst(root);
}


//Prints Tree Breadth First
template <typename T>
void Bst<T>::BreadthFirst(People<T>* root) {
	Queue<People<T>>* q = new Queue<People<T>>();
	q->Enqueue(*root);
		namePrint << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
		std::cout << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	

	while (q->getQueueCount() > 0)
	{
		People<T> n = q->Dequeue();
		if (n.getLeft() != NULL)
		{
				namePrint << "Name: " << n.getLeft()->getName() << " Birthday: " << n.getLeft()->getBirthday() << std::endl;
				std::cout << "Name: " << n.getLeft()->getName() << " Birthday: " << n.getLeft()->getBirthday() << std::endl;
			
			
			q->Enqueue(*n.getLeft());
		}
		if (n.getRight() != NULL)
		{
				namePrint << "Name: " << n.getRight()->getName() << " Birthday: " << n.getRight()->getBirthday() << std::endl;
				std::cout << "Name: " << n.getRight()->getName() << " Birthday: " << n.getRight()->getBirthday() << std::endl;
			
			
			q->Enqueue(*n.getRight());
		}
	}
}

//Prints Tree InOrder
template <typename T>
void Bst<T>::PrintInorder() {
	Inorder(root);
}

//Prints Tree InOrder
template <typename T>
void Bst<T>::Inorder(People<T> *root) {
	if (root == NULL) return;

	Inorder(root->getLeft());       //Visit left subtree

	namePrint << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	std::cout << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	
	
	Inorder(root->getRight());      // Visit right subtree
}


//Prints Tree PostOrder
template <typename T>
void Bst<T>::PrintPostorder() {
	Postorder(root);
}

//Prints Tree PostOrder
template <typename T>
void Bst<T>::Postorder(People<T> *root) {
	if (root == NULL) return;

	Postorder(root->getLeft());    // Visit left subtree
	Postorder(root->getRight());   // Visit right subtree
	namePrint << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	std::cout << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	
	
}

//Prints Tree PreOrder
template <typename T>
void Bst<T>::PrintPreorder() {
	Preorder(root);
}

//Prints Tree PreOrder
template <typename T>
void Bst<T>::Preorder(People<T> *root) {
	// base condition for recursion
	// if tree/sub-tree is empty, return and exit
	if (root == NULL) return;

	namePrint << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	std::cout << "Name: " << root->getName() << " Birthday: " << root->getBirthday() << std::endl;
	
	
	Preorder(root->getLeft());     // Visit left subtree
	Preorder(root->getRight());    // Visit right subtree
}

//Sets type for name or birthday sorting
template <typename T>
void Bst<T>::setType(int t) {
	type = t;
}

//Sets
template <typename T>
void Bst<T>::addBstNode(std::string name, std::string bday) {
	root = Insert(root, name, bday);
	count++;
}

// Function to create a new Node in heap
template <typename T>
People<T>* Bst<T>::CreateNewNode(std::string name, std::string bday) {
	People<T>* newNode = new People<T>(name, bday, type);
	return newNode;
}

// To insert data in BST, returns address of root 
template <typename T>
People<T>* Bst<T>::Insert(People<T>* root, std::string name, std::string bday) {
	if (root == NULL) { // empty tree
		root = CreateNewNode(name, bday);
	}
	// if data to be inserted is lesser, insert in left subtree.
	else if (name <= root->getName()) {
		root->setLeft(Insert(root->getLeft(), name, bday));
	}
	// else, insert in right subtree. 
	else {
		root->setRight(Insert(root->getRight(), name, bday));
	}
	
	return root;
}


#endif /* Bst_h */