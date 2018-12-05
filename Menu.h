/*
	Author: Evren Keskin

	Version: 12/03/2018

	Description:
		This is a generalized menu object
		that can take inputs of any specification
		and allow an easy usage of list-based menus to the user
*/

#pragma once
#include <iostream>
#include <string>

class Menu
{
private:
	std::string *options;
	int length;
public:
	Menu()
	{
		std::string choices[] = { "DO NOT USE"};
		options = choices;
		length = 0;
	}
	Menu(std::string opt[], int len)
	{
		options = opt;
		length = len;
	}
	int getOptionsLength() { return length; }
	int takeRangedIntInput(int min, int max);
	int takeIntegerInput();
	double takeDoubleInput();
	char takeCharInput();
	std::string takeStringInput();
	int printOptionsList();
	void pause();
};

int Menu::takeRangedIntInput(int min, int max)
{
	int chosen = 0;
	bool properNumber = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid INTEGER: ";
		std::string input = "";
		std::getline(std::cin, input);
		try {
			chosen = std::stoi(input);
			if (chosen >= min && chosen <= max)
				properNumber = true;
		}
		catch (...)
		{
			properNumber = false;
		}
	} while (!properNumber);
	system("CLS");
	return chosen;
}

int Menu::takeIntegerInput()
{
	return takeRangedIntInput(-2147483647, 2147483647); // max range
}

double Menu::takeDoubleInput()
{
	double chosen = 0;
	bool properNumber = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid DOUBLE: ";
		std::string input = "";
		std::getline(std::cin, input);
		try {
			chosen = std::stod(input);
			properNumber = true;
		}
		catch (...)
		{
			properNumber = false;
		}
	} while (!properNumber);
	system("CLS");
	return chosen;
}

char Menu::takeCharInput()
{
	char chosen = '0';
	bool properChar = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid CHAR: ";
		std::string input = "";
		std::getline(std::cin, input);
		if (input.length() == 1)
		{
			chosen = input.at(0);
			properChar = true;
		}
	} while (!properChar);
	system("CLS");
	return chosen;
}
std::string Menu::takeStringInput()
{
	std::string chosen = "";
	bool properString = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid STRING: ";
		std::string input = "";
		std::getline(std::cin, input);
		if (input.length() != 0)
		{
			chosen = input;
			properString = true;
		}
	} while (!properString);
	system("CLS");
	return chosen;
}

int Menu::printOptionsList()
{
	int optionsIndex;
	for (optionsIndex = 0; optionsIndex < length; optionsIndex++)
	{
		std::cout << (optionsIndex + 1) << ")" << options[optionsIndex] << std::endl;
	}
	return takeRangedIntInput(1, optionsIndex);
}

void Menu::pause()
{
	std::cout << "Press any key to continue..." << std::endl;
	std::string waste = "";
	std::getline(std::cin, waste);
	system("CLS");
}