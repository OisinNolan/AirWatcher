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

    inline string toString() {
        return "Sensor {\n  id : " + id + ",\n  location : (" + to_string(latitude) + ", "
            + to_string(longitude) + "),\n  description : " + description + "\n}\n";
    };
    
    Sensor(string idParam, double latitudeParam, double longitudeParam, string descriptionParam)
    : id(idParam), latitude(latitudeParam), longitude(longitudeParam), description(descriptionParam)
    { }
};

#endif