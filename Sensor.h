/*

*/
#ifndef SENSOR_H
#define SENSOR_H

#include <string>

using namespace std;

class Sensor {
public:
    string id;
    double latitude;
    double longitude;
    string description;
    Sensor(string idParam, double latitudeParam, double longitudeParam, string descriptionParam)
    : id(idParam), latitude(latitudeParam), longitude(longitudeParam), description(descriptionParam)
    { }
};

#endif