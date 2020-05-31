#include <iostream>
#include <tuple>
#include <vector>
#include <map>  


#include "Sensor.h"
#include "AirCleaner.h"
#include "Backend.h"
#include "Zone.h"
#include "Atmo.h"

using namespace std;

// Here are some global stuff maybe we can make AirWatcher a real class 
// and call everyting from a main one day 

Backend backend = Backend();

AirCleaner AC1 = AirCleaner(
  "AC1",
  45.333333,
  1.333333,
  "2019-02-01 12:00:00",
  "2019-03-01 00:00:00",
  "AirCleaner1");

AirCleaner AC2 = AirCleaner(
  "AC2",
  46.666667,
  3.666667,
  "2019-02-01 12:00:00",
  "2019-03-01 00:00:00",
  "AirCleaner2");


int convertDateInt( string date){
  
  int MonthDurations[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

  int stMonth = stoi( date.substr(5,6));
  int stDay = stoi( date.substr(8,9));
  int st = MonthDurations[stMonth-1] + stDay;

  return st;

}

struct _Interval{

  int startDate;
  int endDate;

} typedef Interval;

Interval* getInterval( string start, string end ){

  Interval* interval = new Interval;
  interval->startDate = convertDateInt(start);
  interval->endDate = convertDateInt(end);

  return interval;

}

/*

Pseudocode:
1. Calculate radius:
    - Find list of relevant sensors:
        - get a list of all sensors that are closer to this aircleaner
          than the other aircleaner
        - Sort that list by distance from this aircleaner
        - Iterate over that list and for each sensor check if the difference
          is negligeable
            IF negligeable : cut the rest of the sensors in the list off
            ELSE : continue
    - The radius is the distance between the aircleaner and the last sensor in
      the sorted list of sensors.
2. Calculate impact:
    - At a specific interval on the cleaner's lifespan, calculate the air quality
    average over each sensor included in the cleaner's impact radius.
    - Add this data to a tableau to be returned.
3. Calculate ATMO index:
    - Calculate the atmo index before and after the air cleaner's work

*/


void getImpact( string CleanerID) {

  AirCleaner AC;
  AirCleaner OtherC;

  if( CleanerID == "AC1" ){
     AC = AC1; 
     OtherC = AC2;
  }
  else if( CleanerID == "AC2" ){
    AC = AC2;
    OtherC = AC1;
  }
  else{
    cout << "CLEANER NOT FOUND" << endl;
    return;
  }

  Interval* interval = getInterval(AC.start,AC.end); // actually is this useful here not sure

  // 1. Calculate radiusen

  backend.loadSensorsFile();
  backend.loadDataFileBetween(AC.start, AC.end);

  multimap<int,Sensor> concernedSensors;
  multimap<string,tuple<double,double,double,double>> deltaVals;

  for( Sensor s : backend.Sensors ){

    double distAC = (AC.longitude - s.longitude)*(AC.longitude - s.longitude) + (AC.latitude - s.latitude)*(AC.latitude - s.latitude);
    double distOC = (OtherC.longitude - s.longitude)*(OtherC.longitude - s.longitude) + (OtherC.latitude - s.latitude)*(OtherC.latitude - s.latitude);

    

    if( distAC < distOC) 
    {
      concernedSensors.insert(make_pair(distAC,s));
      //deltaVals.insert(make_pair(s.id,make_tuple(,,,,)))
    }
  }



}

int getAtmo( vector<tuple<double,double,double,double>> vals, Interval* interval ){

  tuple<double,double,double,double> avg;

  for( tuple<double,double,double,double> t : vals ){
    get<O3>(avg) += get<O3>(t);
    get<SO2>(avg) += get<SO2>(t);
    get<NO2>(avg) += get<NO2>(t);
    get<PM10>(avg) += get<PM10>(t);
      
  }

  int dur = interval->endDate - interval->startDate;

  get<O3>(avg) = get<O3>(avg)/dur;
  get<SO2>(avg) = get<SO2>(avg)/dur;
  get<NO2>(avg) = get<NO2>(avg)/dur;
  get<PM10>(avg) = get<PM10>(avg)/dur;


  int index[4] = 
  {
    getIndex(O3,get<O3>(avg)),
    getIndex(SO2,get<O3>(avg)),
    getIndex(NO2,get<O3>(avg)),
    getIndex(PM10,get<O3>(avg)),
  };

  int maximum = index[0];

  for( int i=0; i<3; i++ ) if(  index[i] > maximum ) maximum = index[i];

  return maximum;

}

double getAverageAirQuality() {

}
  





int main() {
  





  return 0;
}

