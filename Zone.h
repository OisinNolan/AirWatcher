#ifndef ZONE_H
#define ZONE_H

#include <string>

class Zone {

    public:
        double latitude;
        double longitude;
        double radius;




        Zone( double lat, double lon, double rad ){
            latitude = lat;
            longitude = lon;
            radius = rad;
        }

        bool IsWithin(double lat, double lon);
};

//Check if this works
inline bool Zone::IsWithin( double lat, double lon ){

    return radius*radius > (latitude-lat)*(latitude-lat) + (longitude-lon)*(longitude-lon) ;
}


#endif
