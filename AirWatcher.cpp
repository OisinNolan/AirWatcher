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

typedef tuple<double,double,double,double> moltup;

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

struct _Interval{

  int startDate;
  int endDate;

} typedef Interval;

int getAtmo( vector<moltup> vals, Interval* interval );

int convertDateInt( string date){
  
  const int MonthDurations[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
  int stMonth = stoi( date.substr(5,2));
  int stDay = stoi( date.substr(8,2));
  int st = MonthDurations[stMonth-1] + stDay;

  return st;

}

string IncrementDayBy( string date, int i){
  // this can't change months but maybe one day ??
  // can be used to decrement also if its not the first of the month
  // should be used with 2 if intended to be used with loadDataFileBetween

  int day = stoi(date.substr(8,2))+i;
  string s = to_string(day);
  if( s.length() == 1) s = "0" + s;
  string newDate = date;
  newDate.replace(8,2,s);

  return newDate;
}

string DecrementDayBy( string date, int i){
  // this should be able to go to month before
  // can't go back 2 months
  // we got data for a year so january is off limits

  const int MonthDayNumbers[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

  string m ="";

  int day = stoi(date.substr(8,2))-i;
  if( day <= 0 ){
    int month = stoi(date.substr(5,2))-1;
    day = day + MonthDayNumbers[month-1];
    m = to_string(month);
    if( m.length() == 1) m = "0" + m;
  }
  string s = to_string(day);
  if( s.length() == 1) s = "0" + s;
  string newDate = date;
  newDate.replace(8,2,s);
  if( m.length() != 0  )newDate.replace(5,2,m);

  return newDate;
}



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

  // 1. Calculate radiusen

  backend.loadSensorsFile();
  
  // load values at the start of the duration;
  string newDate = DecrementDayBy(AC.start,2);
  backend.loadDataFileBetween(newDate, AC.start);
  
  vector<Data> startVal;
  for( Data d : backend.data ) startVal.push_back(d);

  cout << "------------------------------" << endl;

  backend.data = vector<Data>();

  // load values at the end of the duration
  string endDate = AC.end.replace(11,2,"12"); // this is necessary because I want data from one day and because end date starts at 00:00:00 it complicates things
  newDate = DecrementDayBy(AC.end,2);
  backend.loadDataFileBetween(newDate,endDate);

  multimap<double,Sensor> concernedSensors;  // first int is distance between Sensor <-> Cleaner
  multimap<string,moltup> deltaVals; // first string is Sensor.id

  for( Sensor s : backend.Sensors ){

    double distAC = (AC.longitude - s.longitude)*(AC.longitude - s.longitude) + (AC.latitude - s.latitude)*(AC.latitude - s.latitude);
    double distOC = (OtherC.longitude - s.longitude)*(OtherC.longitude - s.longitude) + (OtherC.latitude - s.latitude)*(OtherC.latitude - s.latitude);

    if( distAC < distOC) 
    {
      concernedSensors.insert(make_pair(distAC,s));     
      int index = stoi(s.id)*4;
      //cout << index << endl;
      
      //cout << startVal[index+O3].value << "-+-" << backend.data[index+O3].value << endl;

      moltup t = make_tuple(
          backend.data[index+O3].value - startVal[index+O3].value ,
          backend.data[index+SO2].value - startVal[index+SO2].value,
          backend.data[index+NO2].value - startVal[index+NO2].value,
          backend.data[index+PM10].value - startVal[index+PM10].value
        );
      deltaVals.insert(make_pair(s.id,t));
    } 
  }

  /*
  // This is all the data from all the concerned sensors
  cout << "S|O3|SO2|NO2|PM10|" << endl;
  for (multimap<string,moltup>::iterator it = deltaVals.begin(); it != deltaVals.end(); ++it)
  {
    cout << it->first << "|";
    cout << get<O3>(it->second)<< "|";
    cout << get<SO2>(it->second)<< "|";
    cout << get<NO2>(it->second)<< "|";
    cout << get<PM10>(it->second)<< "|";
    cout << endl;
  }
  */

  cout << "|Distance|Id|O3|SO2|NO2|PM10|" << endl;
  // we will traverse the sensors one by one sorted by their distance to cleaner
  // distance is actually distance squared but no need to take its square root
  // if we are using it to only sort but later to calculate the radius we'll need to
  for( multimap<double,Sensor>::iterator it = concernedSensors.begin(); it != concernedSensors.end(); ++it )
  {
    Sensor s = it->second;
    moltup t = deltaVals.find(s.id)->second;
    
    cout << it->first << "|" <<s.id << "|";
    cout << get<O3>(t)<< "|";
    cout << get<SO2>(t)<< "|";
    cout << get<NO2>(t)<< "|";
    cout << get<PM10>(t)<< "|";
    cout << endl;
  
  }
  
  // I am not really sure yet how to get the radius so 
  // I'll assume we got the radius to continue
  double radius;
  string lastSensorId;

  // not sure if we need a radius tbh 
  // we can just cut off at certain point for the calculations
  Zone zone = Zone(AC.latitude,AC.longitude,radius); // and don't really need this tbh

  // we need all the data for ATMO
  backend.data.clear();
  backend.loadDataFileBetween(AC.start,AC.end);

  // we can find the indexes and stuff

  vector<moltup> ATMOvals;

  for( multimap<double,Sensor>::iterator it = concernedSensors.begin(); it != concernedSensors.end(); ++it )
  {
    // Well this dosent work yet
    // need to find the places of concerned sensors in backend.data
    // then add all that data in to the vector you were getting bs values because you were using delta vals instead
    ATMOvals.push_back(t);  
  }

  Interval* interval = getInterval(AC.start,AC.end);

  int Atmo = getAtmo(ATMOvals,interval);

  cout << "ATMO Index =" <<  Atmo << endl;

}

int getAtmo( vector<moltup> vals, Interval* interval ){

  moltup avg;

  // Actually we can pass a addes vector but oh well
  for( moltup t : vals ){
    cout << get<O3>(t) << endl;
    get<O3>(avg) += get<O3>(t);
    get<SO2>(avg) += get<SO2>(t);
    get<NO2>(avg) += get<NO2>(t);
    get<PM10>(avg) += get<PM10>(t);
      
  }

  int dur = interval->endDate - interval->startDate;

  cout << get<O3>(avg) << " dur = " << dur << endl;

  get<O3>(avg) = get<O3>(avg)/dur;
  get<SO2>(avg) = get<SO2>(avg)/dur;
  get<NO2>(avg) = get<NO2>(avg)/dur;
  get<PM10>(avg) = get<PM10>(avg)/dur;

  //cout << getIndex(O3,get<O3>(avg)) << endl ;

  int index[4] = 
  {
    getIndex(O3,get<O3>(avg)),
    getIndex(SO2,get<O3>(avg)),
    getIndex(NO2,get<O3>(avg)),
    getIndex(PM10,get<O3>(avg)),
  };

  int maximum = index[0];

  for( int i=0; i<4; i++ ){
    
    cout << index[i] << endl;  
    
    if(  index[i] > maximum ) maximum = index[i];
  } 
  return maximum;

}

double getAverageAirQuality() {

}
  





int main() {
  

  //backend.loadDataFileBetween(AC1.start, "2019-02-03 12:00:00");

  //backend.loadSensorsFile();

  getImpact("AC1");

  //backend.loadDataFileBetween(AC2.start,AC2.end);

  return 0;
}

