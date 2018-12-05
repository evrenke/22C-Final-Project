//
//  Location.h
//  22C_Project
//
//  Created by Ohreum, Tommaso, Evren, Jason on 11/14/18.


#ifndef Location_h
#define Location_h

#include <string>
#define pi 3.14159265358979323846
//Constant for radius of the Earth in desired units. Currently miles
#define radius 3959
/*
 This class contains 3 private variables: latitude, longitude, and relativeDistance.
 It also contains getter and setter methods to access the variables in the class.
*/
class Location {
private:
    double latitude, longitude, relativeDistance /*Used for sorting algorithms/lists so they don't need to call a trig funtion 12 times per distance check*/;
    double toRadians(double degrees) { return (degrees * pi) / 180; }
public:
    Location();
    Location(double, double);
    
    //Getter method to return latitude
    double getLatitude() { return latitude; }
    //Getter method to return longitude
    double getLongitude() { return longitude; }
    //Returns the distance between 2 different Location classes using the Great Circle Formula
    double getDistance(Location);
    //getter method to return both latitude and longitude
    std::string getCoordinates();
    //sets relative distance between two coordinates
    void setRelativeDistance(Location);
    void setRelativeDistance(double d) { relativeDistance = d; }
    //getter method to return relative distance
    double getRelativeDistance() { return relativeDistance; }
};

#endif /* Location_h */
