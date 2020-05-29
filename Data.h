/*

*/
#ifndef DATA_H
#define DATA_H

#include <string>

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
};

#endif