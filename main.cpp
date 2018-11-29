//
//  main.cpp
//  22C_Project
//
//  Created by Oh Reum Kwon on 11/7/18.
//  Copyright © 2018 Oh Reum Kwon. All rights reserved.
//
/*
	Authors: Evren Keskin, Jason Hagene, Oh Reum Kwom, Tommasso M Framba

	Date: 11/29/2018

*/
#include <string>
#include <iostream>
#include <fstream>

#include "Menu.h"
#include "Contact.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

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
void pause();

int main()
{
	
	std::ifstream inputFile;
	inputFile.open("Contacts.txt");

	std::string name, address, number, coordinates;
	int phoneNumber;
	Location location;

	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		getline(inputFile, address, '\n');
		getline(inputFile, number, '\n');
		getline(inputFile, coordinates, '\n');
		phoneNumber = std::stoi(number);
		location = Location(std::stod(coordinates.substr(0, coordinates.find(' '))), 
			std::stod(coordinates.substr(coordinates.find(' ') + 1, coordinates.length())));

		Contact *newContact = new Contact(name, address, phoneNumber, location);

		//add to binary tree
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
			std::cout << "Your input: " << mainmenu.takeStringInput() << std::endl;
			break;
		case 2:
			std::cout << "Your input: " << mainmenu.takeCharInput() << std::endl;
			break;
		case 3:
			std::cout << "Your input: " << mainmenu.takeDoubleInput() << std::endl;
			break;
		case 4:
			std::cout << "Your input: " << mainmenu.takeIntegerInput() << std::endl;
			break;
		case 5:
			std::cout << "You chose to exit the menu, good for you!" << std::endl;
			break;
		case 6:
			std::cout << "You chose to exit the menu, good for you!" << std::endl;
			break;
		case 7:
			std::cout << "You chose to exit the menu, good for you!" << std::endl;
			break;
		case 8:
			std::cout << "You chose to exit the menu, good for you!" << std::endl;
			break;
		}
	}
	pause();
	_CrtDumpMemoryLeaks();
	return 0;
}

void pause()
{
	std::cout << "Press any key to continue..." << std::endl;
	std::cin.get();
	system("CLS");
}
