#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>  
#include "Sensor.h"

using namespace std;



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

struct _Interval{

  int startDate;
  int endDate;

} typedef Interval;



void getImpact() {
    
}

int getAtmo( vector<tuple<double,double,double,double>> vals, Interval* interval ){

  tuple<double,double,double,double> avg;

  for( tuple<double,double,double,double> t : vals ){
    get<0>(avg) += get<0>(t);
    get<1>(avg) += get<1>(t);
    get<2>(avg) += get<2>(t);
    get<3>(avg) += get<3>(t);
      
  }

  int dur = interval->endDate - interval->startDate;

  get<0>(avg) = get<0>(avg)/dur;
  get<1>(avg) = get<1>(avg)/dur;
  get<2>(avg) = get<2>(avg)/dur;
  get<3>(avg) = get<3>(avg)/dur;

  int maximum = max(
    max(get<0>(avg),get<1>(avg)),
    max(get<2>(avg),get<3>(avg))
  );

  return maximum;

}

double getAverageAirQuality() {

}
  

int convertDateInt( string date){
  
  int MonthDurations[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

  int stMonth = stoi( date.substr(5,6));
  int stDay = stoi( date.substr(8,9));
  int st = MonthDurations[stMonth-1] + stDay;

  return st;

}

Interval* getInterval( string start, string end ){

  Interval* interval = new Interval;
  interval->startDate = convertDateInt(start);
  interval->endDate = convertDateInt(end);

  return interval;

}

int main() {
  
  Interval* interval = getInterval("2019-01-01","2019-03-01");

  cout << interval->startDate << " + " << interval->endDate << endl;

  return 0;
}

