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
int* getPhoneNumberInput();
int main()
{
	std::string dataFile = "Contacts.txt";
	std::ofstream outputFile;
	std::ifstream inputFile;
	inputFile.open(dataFile);

	HashTable<Contact *> contactHash;
	BST<Contact *> contactBST;

	std::string name, address, phoneNumber, coordinates;
	double longitude, latitude;
	Location location;
	Contact *newContact = NULL, *contactPTR = NULL;
	int *nums;
	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		getline(inputFile, address, '\n');
		getline(inputFile, phoneNumber, '\n');
		getline(inputFile, coordinates, '\n');
		// a string formatted as 6505551234
		nums = new int[3]
		{
			std::stoi(phoneNumber.substr(0, 3)),
			std::stoi(phoneNumber.substr(3, 3)),
			std::stoi(phoneNumber.substr(6, 10))
		};
		std::cout << nums[1];
		longitude = std::stod(coordinates.substr(0, coordinates.find(' ')));
		latitude = std::stod(coordinates.substr(coordinates.find(' ') + 1, coordinates.length()));
		location = Location(longitude,latitude);
		newContact = new Contact(name, address, nums, location);
		std::cout << *newContact;
		contactHash.add(name, newContact);
		contactBST.add(&newContact);
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
		//add greeting here
		answer = mainmenu.printOptionsList();

		switch (answer)
		{
		case 1:
			std::cout << "Add new friend contact:" << std::endl;
			// name, address, location, phone number
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
			std::cout << "What is their longitude and latitude?" << std::endl;
			std::cout << "Longitude:" << std::endl;
			longitude = mainmenu.takeDoubleInput();
			std::cout << "Latitude:" << std::endl;
			latitude = mainmenu.takeDoubleInput();
			std::cout << "Name        :" << name << std::endl;
			std::cout << "Phone Number:" << phoneNumber << std::endl;
			std::cout << "Address     :" << address << std::endl;
			std::cout << "Location    :" << longitude << " , " << latitude << std::endl;

			location = Location(longitude, latitude);

			newContact = new Contact(name, address, nums, location);
			contactHash.add(name, newContact);
			contactBST.add(&newContact);
			break;
		case 2:
			//fix search function first
			std::cout << "Delete friend contact:" << std::endl;
			std::cout << "Which friend's contact do you want removed?" << std::endl;
			name = mainmenu.takeStringInput();
			if (contactHash.get(name))
			{
				newContact = *contactHash.get(name);
				std::cout << "We did it team" << std::endl;
				std::cout << *newContact;
				contactHash.remove(name);
			}
			else std::cout << "We'll get em next time" << std::endl;
			break;
		case 3:
			//fix search function first
			std::cout << "Search friend contact:" << std::endl;
			std::cout << "Which friend's contact do you want to see?" << std::endl;
			name = mainmenu.takeStringInput();
			if (contactHash.get(name))
			{
				newContact = *contactHash.get(name);
				std::cout << "We did it team" << std::endl;
				std::cout << *newContact;
			}
			else std::cout << "We'll get em next time" << std::endl;
			break;
		case 4:
			std::cout << "Modify friend contact info:" << std::endl;
			break;
		case 5:
			std::cout << "List all friends:" << std::endl;
			break;
		case 6:
			std::cout << "Print Tree by the name of the User" << std::endl;

			/*
			pineapple:0
				kiwi:1
					grapes:3
						apple:5
							NULL
							NULL
						NULL
					orange:6
						lime:8
							NULL
							olives:9
								mango:10
									NULL
									NULL
								NULL
						NULL
				strawberry:4
					NULL
					watermelon:7
						NULL
						NULL
			*/
			break;
		case 7:
			std::cout << "Distance calculator" << std::endl;
			break;
		case 8:
			std::cout << "You chose to exit the menu, good for you!" << std::endl;
			break;
		}
		updateFiles(&outputFile, &contactBST);
		mainmenu.pause();
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}

template<class T>
void updateFiles(std::ofstream *, BST<T> *)
{

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

	return numbers;
}