#ifndef AIRCLEANER_H 
#define AIRCLEANER_H

#include <string>   

class AirCleaner {
        
    public:
        string cleanerId;
        double latitude;
        double longitude;
        string start;
        string end;
        string description;


        AirCleaner( string id, double lat, double lon, string start, string end, string desc ){
            cleanerId = id;
            latitude = lat;
            longitude = lon;
            this->start = start;
            this->end = end;
            description = desc;

        }

};

#endif
