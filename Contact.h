#pragma once
#include <string>
#include "Location.h"
class Contact {
private:
	Location location;
	std::string name;
	std::string address;
	int *contactNum;
public:
	Contact()
	{
		name = "No man";
		address = "Middle of Nowhere";
		int nums[] =
		{
			650, 555, 5555
		};
		contactNum = nums;
		location = Location();
	}
	Contact(std::string n, std::string a, int num[], Location l)
	{
		name = n;
		address = a;
		contactNum = num;
		location = l;
	}
	std::string getName() { return name; }
	std::string getAdress() { return address; }
	int* getContactNum() { return contactNum; }
	Location getLocation(){ return location; }
};