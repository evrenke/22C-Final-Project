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
		contactNum = new int[3]
		{
			0, 0, 0
		};
		location = Location();
	}
	Contact(std::string n, std::string a, int *num, Location l)
	{
		name = n;
		address = a;
		contactNum = num;
		location = l;
	}
	~Contact()
	{

	}
	std::string getName() { return name; }
	std::string getAddress() { return address; }
	int* getContactNum() { return contactNum; }
	std::string getNumStr()
	{
		return std::to_string(contactNum[0]) + std::to_string(contactNum[1]) + std::to_string(contactNum[2]);
	}
	Location getLocation(){ return location; }
	void setAddress(std::string a)
	{
		address = a;
	}
	void setContactNum(int * num)
	{
		contactNum = num;
	}
	void setLocation(Location l)
	{
		location = l;
	}

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
		out << "Name        :" << ct.name << std::endl;
		out << "Phone Number:" << ct.contactNum[0] << ct.contactNum[1] << ct.contactNum[2] << std::endl;
		out << "Address     :" << ct.address << std::endl;
		return out;
	}
};