#include "Location.h"
#include <math.h>

Location::Location() {
	latitude = 0;
	longitude = 0;
}

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
	//I'm not sure either but it works
	double radians = acos((sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 - long1));
	return radians * radius;
}

std::string Location::getCoordinates() {
	return std::to_string(latitude) + "\t" + std::to_string(longitude);
}

void Location::setRelativeDistance(Location otherPlace) {
	relativeDistance = getDistance(otherPlace);
}
