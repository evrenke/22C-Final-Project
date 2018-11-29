#pragma once
#include <string>
#include "Location.h"
class Contact {
private:
	Location location;
	std::string name;
	std::string address;
	int contactNum;
public:
	Contact()
	{
		name = "No man";
		address = "Middle of Nowhere";
		contactNum = 5555555555;
		location = Location();
	}
	Contact(std::string n, std::string a, int num, Location l)
	{
		name = n;
		address = a;
		contactNum = num;
		location = l;
	}
	std::string getName() { return name; }
	std::string getAdress() { return address; }
	int getContactNum() { return contactNum; }
	Location getLocation(){ return location; }
};
