#ifndef AIRWATCHER_H
#define AIRWATCHER_H

#include <iostream>
#include <tuple>
#include <vector>
#include <map> 
#include <set>
#include <math.h>
#include <cmath> 

#include "Sensor.h"
#include "AirCleaner.h"
#include "Backend.h"
#include "Zone.h"

typedef tuple<double,double,double,double> moltup;

using namespace std;

enum Molecule{
	O3,
    SO2,
    NO2,
    PM10,
};

inline int getIndex( Molecule m, int val ){

    int MolIndex[4][10] = {
    {0,30,55,80,105,130,150,180,210,240 },  // O3
    {0,40,80,120,160,200,250,300,400,500 }, // SO2
    {0,30,55,85,110,135,165,200,275,400 },  // NO2
    {0,7,14,21,28,35,42,50,65,80 }          // PM10
    };

    for( int i=0;i<9; i++ ){

        if( val >= MolIndex[m][i] && val < MolIndex[m][i+1]  ) return i+1;

    }

    return 10;
}

inline void printMoltup(moltup m) {
  std::cout << "(" << get<O3>(m) << ", " << get<SO2>(m) << ", " << get<NO2>(m) << ", " << get<PM10>(m) << ")";
}

struct _Interval{

  int startDate;
  int endDate;

} typedef Interval;

class AirWatcher {

    public:
      void getImpact( string CleanerID );
      void getSimilarSensors( Interval interval, Zone zone );
      AirWatcher();

    private:
      Backend backend;
      int getAtmo( vector<moltup> vals, Interval* interval );
      double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
      double deg2rad(double deg);
      bool isNearestAirCleaner(AirCleaner ac, Sensor s);

};

#endif