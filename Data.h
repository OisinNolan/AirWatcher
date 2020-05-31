/*

*/
#ifndef DATA_H
#define DATA_H

#include <string>
#include <iostream>

using namespace std;

class Data {
public:
    string time;
    string sensorId;
    string type;
    double value;
    Data(string timeParam, string sensorIdParam, string typeParam, double valueParam)
        : time(timeParam), sensorId(sensorIdParam), type(typeParam), value(valueParam)
        {}

    friend ostream& operator<<(ostream& os, const Data& d){
         os << d.sensorId << "|" << d.type << "|" << d.value;
        return os;
    }

};


#endif