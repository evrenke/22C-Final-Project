//
//  Location.cpp
//  22C_Project
//
//  Created by Ohreum, Tommaso, Evren, Jason on 11/14/18.

#include "Location.h"
#include <math.h>

//Default Constructor
Location::Location() {
    latitude = 0;
    longitude = 0;
}

//Constructor with latitude and longitude as input
Location::Location( double inLat, double inLong) {
    latitude = inLat;
    longitude = inLong;
}

//Calculates the distance between 2 points on a sphere given ther coordiantes in degrees
double Location::getDistance(Location otherPlace) {
    //c++ doesn't use degrees for trig functions so we need to convert to radians
    double lat1 = toRadians(latitude);
    double lat2 = toRadians(otherPlace.latitude);
    double long1 = toRadians(longitude);
    double long2 = toRadians(otherPlace.longitude);
    double radians = acos((sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 - long1));
    return radians * radius;
}

//getter method to return latitude and longitude as coordinates
std::string Location::getCoordinates() {
    return std::to_string(latitude) + "\t" + std::to_string(longitude);
}

//setter method to set relative distance by using getDistance
void Location::setRelativeDistance(Location otherPlace) {
    relativeDistance = getDistance(otherPlace);
}
