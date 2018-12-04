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

	friend bool operator==(const Contact &c1, const Contact &c2)
	{
		return c1.name == c2.name;
	}
	friend bool operator!=(const Contact &c1, const Contact &c2)
	{
		return c1.name != c2.name;
	}

	friend bool operator> (const Contact &c1, const Contact &c2)
	{
		return c1.name > c2.name;
	}
	friend bool operator<= (const Contact &c1, const Contact &c2)
	{
		return c1.name <= c2.name;
	}

	friend bool operator< (const Contact &c1, const Contact &c2)
	{
		return c1.name < c2.name;
	}
	friend bool operator>= (const Contact &c1, const Contact &c2)
	{
		return c1.name >= c2.name;
	}
	friend std::ostream& operator<<(std::ostream& out, const Contact& ct)
	{
		out << "Name		:" << ct.name << std::endl;
		out << "Phone Number:" << ct.contactNum[0] << ct.contactNum[1] << ct.contactNum[2] << std::endl;
		out << "Address		:" << ct.address << std::endl;
		return out;
	}
};