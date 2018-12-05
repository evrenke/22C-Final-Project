//
//  Contact.h
//  22C_Project
//
//  Created by Ohreum, Tommaso, Evren, Jason on 11/14/18.

#ifndef Contact_h
#define Contact_h

/*
 Contact class contains 4 private variables: location, name, address, and contact number.
 It also contains constructors, a destructor, getter and setter methods
 */
#include <string>
#include "Location.h"
class Contact {
private:
    Location location;
    std::string name;
    std::string address;
    int *contactNum;
public:
    //Default constructor
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
    //default destructor
    ~Contact()
    {
        
    }
    //returns name
    std::string getName() { return name; }
    //returns address
    std::string getAddress() { return address; }
    // returns phone number
    int* getContactNum() { return contactNum; }
    // returns phone number as a string
    std::string getNumStr()
    {
        return std::to_string(contactNum[0]) + std::to_string(contactNum[1]) + std::to_string(contactNum[2]);
    }
    // returns location of user
    Location getLocation(){ return location; }
    //sets address
    void setAddress(std::string a)
    {
        address = a;
    }
    //sets phone number
    void setContactNum(int * num)
    {
        contactNum = num;
    }
    //sets location
    void setLocation(Location l)
    {
        location = l;
    }
    // overloaded operators for name
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
    //overloaded output operator for all information
    friend std::ostream& operator<<(std::ostream& out, const Contact& ct)
    {
        out << "Name        :" << ct.name << std::endl;
        out << "Phone Number:" << ct.contactNum[0] << ct.contactNum[1] << ct.contactNum[2] << std::endl;
        out << "Address     :" << ct.address << std::endl;
        return out;
    }
};
#endif /* Contact_h */
