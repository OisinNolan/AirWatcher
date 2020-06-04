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

        inline string toString() {
            return "AirCleaner {\n  id : " + cleanerId + ",\n  location : (" + to_string(latitude) + ", "
            + to_string(longitude) + "),\n  lifespan : " + start + " -> " + end + ",\n  description : " 
            + description + "\n}\n";
        };
    
        AirCleaner( string id, double lat, double lon, string start, string end, string desc ){
            cleanerId = id;
            latitude = lat;
            longitude = lon;
            this->start = start;
            this->end = end;
            description = desc;

        }

        AirCleaner(){};

};

#endif
