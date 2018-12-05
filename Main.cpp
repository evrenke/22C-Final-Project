/*
	
	Authors: Evren Keskin, Jason Hagene, Oh Reum Kwom, Tommasso M Framba

	Date: 12/05/2018

	Description:
	This program will use data structures and algorithms to allow the user to interact with a list of contact information
	
	A hashtable and a BST database of pointers are created to dynamic memory of contact objects
	Then, the user is repeatedly prompted for any kind of interaction to have with the database
		They can add a new contact to the database
		They can remove a contact from the database
		They can search the database for a contact
		They can modify a contacts information (excluding the name)
		They can list the contacts as whole
			As a chart
			As the hashtable
			As a distance based chart from a contact of their choice
		They can see the contacts as the BST that they're stored in
		They can look up the distance between two contacts of their choice
		Each step is followed by the updating of the database files
	When the user is done the program will delete the contacts after updating the database
	The hashtable and BST will decontruct themselves to free up space

*/
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Menu.h"
#include "Contact.h"
#include "TemplateBST.h"
#include "HashTable.h"

template<class T>
void updateFiles(std::ofstream *out, BinaryNode<T> *data);

template<class T>
void eraseContacts(BinaryNode<T> *data);

void chart(BinaryNode<Contact *> *data);
void inorderChart(BinaryNode<Contact *> *data);
void chartDistance(Contact *from, BinaryNode<Contact *> *data);
void inorderChartDistance(Contact *from, BinaryNode<Contact *> *data);
void printValueTable(HashTable<Contact *> *data);
void BSTPrinter(int tabs, BinaryNode<Contact *> *data);

int* getPhoneNumberInput();

int main()
{
	std::string dataFile = "Contacts.txt";
	std::ofstream outputFile;
	std::ifstream inputFile;
	inputFile.open(dataFile);
	if (!inputFile.is_open())
	{
		std::cerr << "Cant find file Contacts.txt" << std::endl;
		exit(4);
	}
	HashTable<Contact *> contactHash;
	ContactBST contactBST;

	std::string name, address, phoneNumber, coordinates, coor;
	double longitude, latitude;
	Location location;
	Contact *newContact = NULL, *newContact2 = NULL;
	int *nums;
	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		if (inputFile.eof()) break;
		getline(inputFile, address, '\n');
		if (inputFile.eof()) break;
		getline(inputFile, phoneNumber, '\n');
		if (inputFile.eof()) break;
		getline(inputFile, coordinates, '\n');
		// a string formatted as 6505551234
		nums = new int[3]
		{
			std::stoi(phoneNumber.substr(0, 3)),
			std::stoi(phoneNumber.substr(3, 3)),
			std::stoi(phoneNumber.substr(6, 10))
		};
		coor = coordinates.substr(0, coordinates.find('\t'));
		latitude = atof(coor.c_str())  ;
		coor = coordinates.substr(coordinates.find_last_of('\t') + 1, coordinates.length());
		longitude = atof(coor.c_str());
		location = Location(latitude, longitude);
		newContact = new Contact(name, address, nums, location);
		contactHash.add(name, newContact);
		contactBST.add(newContact);
	}
	inputFile.close();


	int optionsSize = 8;
	std::string options[] =
	{
		"Add New Contact", 
		"Delete A Contact",
		"Search Contacts by name",
		"Modify Contact Information(location, phone number, etc.)", 
		"List all users",
		"Print Tree by name of User", 
		"Distance Calculator",
		"Leave the menu",

	};
	Menu mainmenu = Menu(options, optionsSize);

	int answer = -1;
	char response = 'a';

	int listed = 3;
	int chosenList = -1;
	std::string listings[] =
	{
		"List database by Chart",
		"List database by HashTable",
		"List database by Distance from a Contact"
	};
	Menu lister = Menu(listings, listed);
	bool isUsingDistanceCal = true;

	while (answer != mainmenu.getOptionsLength()) // exiting
	{
		std::cout << "Welcome to Find Your Friends! " << std::endl;
		std::cout << "------------------------------" << std::endl;
		answer = mainmenu.printOptionsList();

		switch (answer)
		{
		case 1:
			std::cout << "Add new friend contact:" << std::endl;
			// name, address, phone number, location
			std::cout << "What is your friends name?" << std::endl;
			name = mainmenu.takeStringInput();
			std::cout << name << std::endl;
			std::cout << "What is their phone number?(formatted as 650 555 1234)" << std::endl;
			nums = getPhoneNumberInput();
			phoneNumber = std::to_string(nums[0]) + std::to_string(nums[1]) + std::to_string(nums[2]);
			std::cout << name << std::endl << phoneNumber << std::endl;
			std::cout << "Where does your friend live?" << std::endl;
			address = mainmenu.takeStringInput();
			std::cout << name << std::endl << phoneNumber << std::endl << address << std::endl;
			std::cout << "What is their latitude and longitude?" << std::endl;
			std::cout << "Latitude:" << std::endl;
			latitude = mainmenu.takeRangedDoubleInput(-90, 90);
			std::cout << "Longitude:" << std::endl;
			longitude = mainmenu.takeRangedDoubleInput(-180, 180);
			std::cout << "Name        :" << name << std::endl;
			std::cout << "Phone Number:" << phoneNumber << std::endl;
			std::cout << "Address     :" << address << std::endl;
			std::cout << "Location    :" << latitude << " , " << longitude << std::endl;

			location = Location(latitude, longitude);

			newContact = new Contact(name, address, nums, location);
			contactHash.add(name, newContact);
			contactBST.add(newContact);
			break;
		case 2:
			std::cout << "Delete friend contact:" << std::endl;
			std::cout << "Which friend's contact do you want removed?" << std::endl;
			name = mainmenu.takeStringInput();
			if (contactHash.search(name))
			{
				newContact = *contactHash.search(name);
				std::cout << *newContact;
				std::cout << "They have been found and removed." << std::endl;
				contactBST.remove(*contactHash.search(name));
				contactHash.remove(name);
				
			}
			else std::cout << "The contact to remove has not been found" << std::endl;
			break;
		case 3:
			std::cout << "Search friend contact:" << std::endl;
			std::cout << "Which friend's contact do you want to see?" << std::endl;
			name = mainmenu.takeStringInput();
			if (contactHash.search(name))
			{
				std::cout << "They have been found." << std::endl;
				newContact = *contactHash.search(name);
				std::cout << *newContact;
			}
			else std::cout << "The contact to remove has not been found" << std::endl;
			break;
		case 4:
			std::cout << "Modify friend contact info:" << std::endl;
			std::cout << "Which friend's contact do you want to modify?" << std::endl;
			name = mainmenu.takeStringInput();
			if (contactHash.search(name))
			{
				std::cout << "They have been found." << std::endl;
				newContact = *contactHash.search(name);
				std::cout << *newContact;
				do
				{
					std::cout << "Do you want to modify their address?(y/n)" << std::endl;
					response = mainmenu.takeCharInput();
				} while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
				if (response == 'y' || response == 'Y')
				{
					std::cout << "Enter their new address:" << std::endl;
					address = mainmenu.takeStringInput();
					newContact->setAddress(address);
					outputFile.open(dataFile);
					updateFiles(&outputFile, contactBST.root);
					outputFile.close();
				}
				do
				{
					std::cout << "Do you want to modify their phone number?(y/n)" << std::endl;
					response = mainmenu.takeCharInput();
				} while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
				if (response == 'y' || response == 'Y')
				{
					std::cout << "Enter their new number:" << std::endl;
					nums = getPhoneNumberInput();
					newContact->setContactNum(nums);
					outputFile.open(dataFile);
					updateFiles(&outputFile, contactBST.root);
					outputFile.close();
				}
				do
				{
					std::cout << "Do you want to modify their latitude?(y/n)" << std::endl;
					response = mainmenu.takeCharInput();
				} while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
				if (response == 'y' || response == 'Y')
				{
					std::cout << "Enter their new latitude:" << std::endl;
					latitude = mainmenu.takeRangedDoubleInput(-90, 90);
					newContact->setLocation(Location(latitude, newContact->getLocation().getLongitude()));
					outputFile.open(dataFile);
					updateFiles(&outputFile, contactBST.root);
					outputFile.close();
				}
				do
				{
					std::cout << "Do you want to modify their longitude?(y/n)" << std::endl;
					response = mainmenu.takeCharInput();
				} while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
				if (response == 'y' || response == 'Y')
				{
					std::cout << "Enter their new longitude:" << std::endl;
					longitude = mainmenu.takeRangedDoubleInput(-180, 180);
					newContact->setLocation(Location(newContact->getLocation().getLatitude(), longitude));
					outputFile.open(dataFile);
					updateFiles(&outputFile, contactBST.root);
					outputFile.close();
				}
			}
			else std::cout << "The contact to remove has not been found" << std::endl;
			break;
		case 5:
			std::cout << "List all friends:" << std::endl;
			chosenList = lister.printOptionsList();
			switch (chosenList)
			{
			case 1://list with neat chart
				chart(contactBST.root);
				break;
			case 2://list as hash table
				std::cout << "Hash Table Of Values (Names Only)" << std::endl;
				printValueTable(&contactHash);
				break;
			case 3:// list as distance from a certain contact
				isUsingDistanceCal = true;
				do
				{
					chart(contactBST.root);
					std::cout << "Which contact do you want to show distances from?(type a space to exit)" << std::endl;
					name = mainmenu.takeStringInput();
					if (name == " ")
						isUsingDistanceCal = false;
					else if (contactHash.search(name))
					{
						std::cout << "The contact:" << std::endl;
						newContact = *contactHash.search(name);
						std::cout << *newContact << std::endl;
						break;
					}
					else std::cout << "The contact hasnt been found" << std::endl;
				} while (isUsingDistanceCal);
				if(isUsingDistanceCal)
				{ 
					chartDistance(newContact, contactBST.root);
				}
				break;
			}
			break;
		case 6:
			std::cout << "Print Tree by the name of the User" << std::endl;
			BSTPrinter(0, contactBST.root);
			break;
		case 7:
			isUsingDistanceCal = true;
			newContact = nullptr;
			newContact2 = nullptr;
			do
			{
				chart(contactBST.root);
				std::cout << std::endl << "Distance calculator" << std::endl;
				std::cout << "Choose two contacts to compare distances for:" << std::endl;
				std::cout << "Find contact one by name:(type a space to exit)" << std::endl;
				name = mainmenu.takeStringInput();
				if (name == " ")
					isUsingDistanceCal = false;
				else if (contactHash.search(name))
				{
					std::cout << "The first contact:" << std::endl;
					newContact = *contactHash.search(name);
					std::cout << *newContact << std::endl;
					break;
				}
				else std::cout << "The contact hasnt been found" << std::endl;
			} while (isUsingDistanceCal);
			while (isUsingDistanceCal)
			{
				chart(contactBST.root);
				std::cout << std::endl << "Find the second contact by name:(type a space to exit)" << std::endl;
				name = mainmenu.takeStringInput();
				if (name == " ")
					isUsingDistanceCal = false;
				else if (contactHash.search(name))
				{
					std::cout << "They have been found." << std::endl;
					newContact2 = *contactHash.search(name);
					std::cout << *newContact2;
					break;
				}
				else std::cout << "The contact hasnt been found" << std::endl;
			}
			if (isUsingDistanceCal)
			{
				std::cout << "Distance of " << newContact->getName() << " and " << newContact2->getName() << std::endl;
				std::cout << newContact->getLocation().getDistance(newContact2->getLocation()) << " miles " << std::endl;
			}
			break;
		case 8:
			std::cout << "Thank you for using Find Your Friends!" << std::endl;
			break;
		}
		outputFile.open(dataFile);
		updateFiles(&outputFile, contactBST.root);
		outputFile.close();
		mainmenu.pause();
	}
	//DECONSTRUCT HASH TABLE AND BINARY SEARCH TREE OF POINTERS
	//ONLY DELETE CONTACTS FROM BST, THEN DECONTRUCT HASHTABLE WITHOUT WORRYING
	eraseContacts(contactBST.root);
	contactBST.~ContactBST();
	contactHash.~HashTable();
	return 0;
}

void chart(BinaryNode<Contact *> *data)
{
	std::cout << std::left << std::setw(20) << std::setfill(' ') << "Name" << " | "
		<< std::left << std::setw(15) << std::setfill(' ') << "Phone Number" << " | "
		<< std::left << std::setw(40) << std::setfill(' ') << "Address" << " | "
		<< std::left << std::setw(29) << std::setfill(' ') << "Coordinates" << " |" << std::endl;
	std::cout << std::string(115, '-') << "\n";
	inorderChart(data);

}

void inorderChart(BinaryNode<Contact *> *data)
{
	if (data == nullptr)
		return;
	inorderChart(data->getLeftChild());
	std::cout << std::left << std::setw(20) << std::setfill(' ') << data->getData()->getName() << " | "
		<< std::left << std::setw(15) << std::setfill(' ') << data->getData()->getNumStr() << " | "
		<< std::left << std::setw(40) << std::setfill(' ') << data->getData()->getAddress() << " | "
		<< std::left << std::setw(27) << std::setfill(' ') << data->getData()->getLocation().getCoordinates() << " |" << std::endl;
	inorderChart(data->getRightChild());
}

void chartDistance(Contact *from, BinaryNode<Contact *> *data)
{
	//		Name		|	Phone Number |       Address       |     Coordinates    |     Distance     |
	//------------|---------------|---------------------|--------------------|
	// printfspace|               |                     |                    |
	//            |               |                     |                    |
	//            |               |                     |                    |
	//            |               |                     |                    |
	std::cout << std::left << std::setw(20) << std::setfill(' ') << "Name" << " | "
		<< std::left << std::setw(15) << std::setfill(' ') << "Phone Number" << " | "
		<< std::left << std::setw(40) << std::setfill(' ') << "Address" << " | "
		<< std::left << std::setw(29) << std::setfill(' ') << "Coordinates" << " | "
		<< std::left << std::setw(13) << std::setfill(' ') << "Distance to " << from->getName() << " (in miles)"<< std::endl;
	std::cout << std::string(135, '-') << "\n";
	inorderChartDistance(from, data);

}

void inorderChartDistance(Contact *from, BinaryNode<Contact *> *data)
{
	if (data == nullptr)
		return;
	inorderChartDistance(from, data->getLeftChild());
	if(data->getData()->getName() != from->getName())
	std::cout << std::left << std::setw(20) << std::setfill(' ') << data->getData()->getName() << " | "
		<< std::left << std::setw(15) << std::setfill(' ') << data->getData()->getNumStr() << " | "
		<< std::left << std::setw(40) << std::setfill(' ') << data->getData()->getAddress() << " | "
		<< std::left << std::setw(27) << std::setfill(' ') << data->getData()->getLocation().getCoordinates() << " | " 
		<< std::left << std::setw(20) << std::setfill(' ') << from->getLocation().getDistance(data->getData()->getLocation())  << std::endl;
	inorderChartDistance(from, data->getRightChild());
}

void printValueTable(HashTable<Contact *> *data) {
	for (int i = 0; i < data->getSize(); i++) {
		std::cout << i + 1 << ")." << " ";
		HashNode<Contact*>* temp = data->arr[i].getNext();
		if (temp->getData() != nullptr) {
			std::cout << (*temp->getData())->getName();
			temp = temp->getNext();
		}
		temp = temp->getNext();
		while (temp != nullptr) {
			std::cout << ", " << (*temp->getData())->getName();
			temp = temp->getNext();
		}
		std::cout << "NULL" << std::endl;
	}
}

void BSTPrinter(int tabs, BinaryNode<Contact *> *data)
{
	for (int ind = 0; ind < tabs; ind++)
	{
		std::cout << "\t";
	}
	if (data == nullptr)
	{
		std::cout << "NULL" << std::endl;
		return;
	}
	//preorder for BST printing
	std::cout << data->getData()->getName() << ":" << std::endl;
	BSTPrinter(tabs + 1, data->getLeftChild());
	BSTPrinter(tabs + 1, data->getRightChild());
}

template<class T>
void updateFiles(std::ofstream *out, BinaryNode<T> *data)
{
	if (data != NULL)
	{
		
		*out << (*(data->getData())).getName() << std::endl;
		*out << (*(data->getData())).getAddress() << std::endl;
		*out << std::to_string(*((*(data->getData())).getContactNum())) << std::to_string(*((*(data->getData())).getContactNum() + 1)) << std::to_string(*((*(data->getData())).getContactNum() + 2)) << std::endl;
		*out << (*(data->getData())).getLocation().getCoordinates() << std::endl;
		updateFiles(out, data->getLeftChild());
		updateFiles(out, data->getRightChild());
	}
}

template<class T>
void eraseContacts(BinaryNode<T> *data)
{
	if (data != nullptr)
	{
		eraseContacts(data->getLeftChild());
		eraseContacts(data->getRightChild());
		delete (data->getData());
		data->setInfo(nullptr);
	}
}

int * getPhoneNumberInput()
{
	std::string input = "";
	std::string number = "";
	int *numbers = new int[3];
	bool validNumber = false;
	do
	{
		std::cout << "Enter the phone number:";
		//650555444
		//or 650 555 3333
		//or (605) 111 2222
		// or 123 4567
		//
		std::getline(std::cin, input);
		int numeralCount = 0;
		for (unsigned int ind = 0; ind < input.length(); ind++)
		{
			if (input.at(ind) >= 48 && input.at(ind) <= 57) // a numeral
			{
				numeralCount++;
				number += input.at(ind);
			}
		}
		if (numeralCount != 10)
		{
			std::cout << "That was not all ten numerals of a phone number" << std::endl;
			validNumber = false;
		}
		else
		{
			numbers[0] = std::stoi(number.substr(0, 3));
			numbers[1] = std::stoi(number.substr(3, 3));
			numbers[2] = std::stoi(number.substr(6, 9));
			validNumber = true;
		}
	} while (! validNumber);
	system("CLS");
	return numbers;
}