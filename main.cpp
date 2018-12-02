//
//  main.cpp
//  22C_Lab_5
//
//  Created by Oh Reum Kwon and Tommaso Framba on 11/23/18.
//
/*
Our main creates two binary search trees from the BirthdaysOutput.txt and prints them
using different ranversial manners
*/

#include <string>
#include <iostream>
#include "Node.h"
#include "People.h"
#include "Bst.h"
#include <fstream>
using namespace std;

int main()
{
	string deleteStr;
	Bst<string> nameTree;
	nameTree.setType(1);
	Bst<string> birthdayTree;
	birthdayTree.setType(2);
	string nameLine;
	ifstream myfile("InputData.txt");
	ofstream myfile2("Output.txt");
	ofstream myfile4;
	if (myfile.is_open())
	{
		while (getline(myfile, nameLine))
		{
			string bdayLine;
			getline(myfile, bdayLine);
			birthdayTree.addBstNode(nameLine, bdayLine);
			nameTree.addBstNode(nameLine, bdayLine);
		}
		myfile.close();
	}

	int selection = 0;

	while (selection != -1) {
		cout << "Select an option: " << endl << "1. Print Tree to File and Console" << endl << "2. To Enter a Value" << 
			endl << "3. Delete a Value" << endl << "4. Search for a Value" << endl << "-1. To Exit"
			<< endl << endl;
		cin >> selection;
		if (selection == 1) {
			if (nameTree.getCount() > 0 ) {
				myfile2 << "Pre-Order Of Tree:" << endl;
				cout << "Pre-Order Of Tree:" << endl;
				myfile2.close();
				nameTree.PrintPreorder();
				myfile2.open("Output.txt", std::ofstream::app);
				myfile2 << endl << "Post-Order Of Tree:" << endl;
				cout << endl << "Post-Order Of Tree:" << endl;
				myfile2.close();
				nameTree.PrintPostorder();
				myfile2.open("Output.txt", std::ofstream::app);
				myfile2 << endl << "In-Order Of Tree:" << endl;
				cout << endl << "In-Order Of Tree:" << endl;
				myfile2.close();
				nameTree.PrintInorder();
				myfile2.open("Output.txt", std::ofstream::app);
				cout << endl << "Breadth-First of Tree: " << endl;
				myfile2 << endl << "Breadth-First of Tree: " << endl;
				nameTree.PrintBreadthFirst();
				cout << endl << endl;
				nameTree.PrintTree2D();
			}
			else {
				cout << "Trees are empty" << endl;
			}
		}
		else if (selection == 2) {
			string tempName;
			string tempBirthday;
			cout << "Enter a name: ";
			cin.ignore();
			getline(cin, tempName);
			cout << "Enter a Birthday: ";
			getline(cin, tempBirthday);
			birthdayTree.addBstNode(tempName, tempBirthday);
			nameTree.addBstNode(tempName, tempBirthday);
			myfile4.open("InputData.txt", std::ofstream::app);
			myfile4 << tempName << endl << tempBirthday << endl;
			myfile4.close();
		}
		else if (selection == 3) {
			int nameOrBirthday;
			cout << "Delete in 1.Name or 2.Birthday: ";
			cin >> nameOrBirthday;

			if (nameOrBirthday == 1) {
				string name;
				cout << "Enter the name: ";
				cin.ignore();
				getline(cin, name);
				nameTree.DeleteValue(name);
				nameTree.PrintTreeToFile();
				string line;
				
			}
			else if (nameOrBirthday == 2) {
				string bday;
				cout << "Enter birthday: ";
				cin.ignore();
				getline(cin, bday);
				string temp = birthdayTree.DeleteValue(bday);
				deleteStr += temp;

				bool andNext = false;
				string line;
				while (getline(myfile, line))
				{
					if (line == temp) {
						line.replace(line.find(line), line.length(), "");
					}
					if (line.find(temp)) {
						andNext = true;
					}
					else {
						andNext = false;
					}
					line.replace(line.find(temp), temp.length(), "");
				}
			}
			else {
				cout << endl << "Bad selection" << endl;
			}
		}
		else if (selection == 4) {
			string nameOr;
			cout << "Value to Search: ";
			cin.ignore();
			getline(cin, nameOr);
			People<string>* temp = nameTree.SearchValue(nameOr);
			if (temp == NULL) {
				cout << "Bad Search" << endl;
			}
			else {
				cout << "Name: " << temp->getName() << "Bday: " << temp->getBirthday() << endl;
				cout << "Enter Value to Modify: ";
				string temp2;
				getline(cin, temp2);
				temp->setName(temp2);
			}

			nameTree.PrintTreeToFile();
		}
	}
	nameTree.PrintTreeToFile();
	system("pause");
	return 0;
}