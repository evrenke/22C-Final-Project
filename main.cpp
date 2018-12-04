/*
Authors: Evren Keskin, Jason Hagene, Oh Reum Kwom, Tommasso M Framba
Date: 11/29/2018
Description:
	Fuck idk
*/
#include <string>
#include <iostream>
#include <fstream>

#include "Menu.h"
#include "Contact.h"
#include "TemplateBST.h"
#include "HashTable.h"
/*
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
*/
/*
https://simplemaps.com/data/us-cities
*/

/*
Read contact info from file into BST
In a loop
Ask user for option
Do result of option
Update files
Ask if user wants to exit program
*/

template <class T>
void updateFiles(std::ofstream*, BST<T> *);
int main()
{
	std::string dataFile = "Contacts.txt";
	std::ofstream outputFile;
	std::ifstream inputFile;
	inputFile.open(dataFile);

	BST<Contact> contactBST;

	std::string name, address, number, phoneNumber, coordinates;
	double longitude, latitude;
	Location location;
	Contact *newContact;
	int *nums;
	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		getline(inputFile, address, '\n');
		getline(inputFile, number, '\n');
		getline(inputFile, coordinates, '\n');
		phoneNumber = number;
		// a string 650 555 5555
		nums = new int[3]
		{
			std::stoi(number.substr(0,3)),
			std::stoi(number.substr(4,7)),
			std::stoi(number.substr(7,10))
		};
		longitude = std::stod(coordinates.substr(0, coordinates.find(' ')));
		latitude = std::stod(coordinates.substr(coordinates.find(' ') + 1, coordinates.length()));
		location = Location(longitude,latitude);

		newContact = new Contact(name, address, nums, location);

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
	while (answer != mainmenu.getOptionsLength()) // exiting
	{
		answer = mainmenu.printOptionsList();

		switch (answer)
		{
		case 1:
			std::cout << "Add new friend contact:" << std::endl;
			// name, address, location, phone number
			std::cout << "What is your friends name?" << std::endl;
			name = mainmenu.takeStringInput();
			std::cout << name << std::endl;
			std::cout << "What is their phone number?" << std::endl;
			phoneNumber = mainmenu.takeStringInput();
			std::cout << name << std::endl << phoneNumber << std::endl;
			std::cout << "Where does your friend live?" << std::endl;
			address = mainmenu.takeStringInput();
			std::cout << name << std::endl << phoneNumber << std::endl << address << std::endl;
			std::cout << "What is their longitude and latitude?" << std::endl;
			std::cout << "Longitude:" << std::endl;
			longitude = mainmenu.takeDoubleInput();
			std::cout << "Latitude:" << std::endl;
			latitude = mainmenu.takeDoubleInput();
			std::cout << "Name        :" << name << std::endl;
			std::cout << "Phone Number:" << phoneNumber << std::endl;
			std::cout << "Address     :" << address << std::endl;
			std::cout << "Location    :" << longitude << " , " << latitude << std::endl;
			//newContact = new Contact(name, address, ;
			break;
		case 2:
			std::cout << "Delete friend contact:" << std::endl;
			std::cout << "Which friend's contact do you want removed?" << std::endl;
			name = mainmenu.takeStringInput();
			if (contactBST.search(Contact(name, "", {0}, Location())))
			{

			}
			break;
		case 3:
			std::cout << "Search by friend name: " << std::endl;
			break;
		case 4:
			std::cout << "Modify friend contact info:" << std::endl;
			break;
		case 5:
			std::cout << "List all friends:" << std::endl;
			break;
		case 6:
			std::cout << "Print Tree by the name of the User" << std::endl;
			break;
		case 7:
			std::cout << "Distance calculator" << std::endl;
			break;
		case 8:
			std::cout << "You chose to exit the menu, good for you!" << std::endl;
			break;
		}
		updateFiles(&outputFile, &contactBST);
	}
	mainmenu.pause();
	//_CrtDumpMemoryLeaks();
	return 0;
}

template<class T>
void updateFiles(std::ofstream *, BST<T> *)
{

}