#pragma once
#include <iostream>
#include <string>

int takeIntegerInput(int min, int max);
int takeIntegerInput();
double takeDoubleInput();
char takeCharInput();
std::string takeStringInput();
void printOptionsList(std::string options[], int length);

int takeIntegerInput(int min, int max)
{
	int chosen = 0;
	bool properNumber = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid integer: ";
		std::string input = "";
		std::getline(std::cin, input);
		try {
			chosen = std::stoi(input);
			properNumber = true;
		}
		catch (...)
		{
			properNumber = false;
		}
	} while (!properNumber && (chosen <= min || chosen > max));
	system("CLS");
	return chosen;
}

int takeIntegerInput()
{
	return takeIntegerInput(-2147483647, 2147483647); // max range
}

double takeDoubleInput()
{
	double chosen = 0;
	bool properNumber = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid double: ";
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

char takeCharInput()
{
	char chosen = '0';
	bool properChar = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid char: ";
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
std::string takeStringInput()
{
	std::string chosen = "";
	bool properString = false;
	std::cout << std::endl;
	do
	{
		std::cout << "Enter a valid string: ";
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

void printOptionsList(std::string options[], int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << (i + 1) << ")" << options[i] << std::endl;
	}
}
