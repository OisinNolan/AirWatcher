

// Used to convert lat/long distance unit to km

#include "AirWatcher.h"

using namespace std;

// Here are some global stuff maybe we can make AirWatcher a real class 
// and call everyting from a main one day 


int convertDateInt( string date){
  
  const int MonthDurations[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
  int stMonth = stoi( date.substr(5,2));
  int stDay = stoi( date.substr(8,2));
  int st = MonthDurations[stMonth-1] + stDay;

  return st;

}

Interval* getInterval( string start, string end ){

  Interval* interval = new Interval;
  interval->startDate = convertDateInt(start);
  interval->endDate = convertDateInt(end);

  return interval;

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

// Unit conversion function from https://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a
double AirWatcher::deg2rad(double deg) {
  double result =(deg * M_PI / 180);
  return result;
}

double AirWatcher::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  double result = 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
  return result;
}



// This function returns true if ac is the nearest AirCleaner to Sensor s, and false otherwise
bool AirWatcher::isNearestAirCleaner(AirCleaner ac, Sensor s) {

  double distAc = distanceEarth(ac.latitude, ac.longitude, s.latitude, s.longitude);
  
  for (auto& it : backend.airCleaners) {
    AirCleaner otherAc = it.second;
    double distOtherAc = distanceEarth(otherAc.latitude, otherAc.longitude, s.latitude, s.longitude);
    if(distOtherAc < distAc) {
      return false;
    }
  }

  return true;
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

void AirWatcher::getImpact( string cleanerID) {

  AirCleaner AC = backend.airCleaners[cleanerID];

  backend.loadSensorsFile();
  
  // load values at the start of the duration;
  string newDate = DecrementDayBy(AC.start,2);
  backend.loadDataFileBetween(newDate, AC.start);
  
  vector<Data> startVal;
  for( Data d : backend.data ) startVal.push_back(d);

  backend.data = vector<Data>();

  // load values at the end of the duration
  string endDate = AC.end.replace(11,2,"12"); 
  newDate = DecrementDayBy(AC.end,2);
  backend.loadDataFileBetween(newDate,endDate);

  set<string> nearbySensorIds;
  // This map associates each nearby sensor with the distance it is from AC
  // It is stored in a multimap with dist as key so as the sort the nearby sensors by distance.
  multimap<double,Sensor> nearbySensorDistance;
  // This map associates sensorId with the change in gas value from the start of AC lifetime to the end
  multimap<string,moltup> deltaVals;

  // Here we find all the sensors to whom AC is the nearest AirCleaner
  for( Sensor s : backend.Sensors ){

    // If AC is the nearest AirCleaner to s, then S is considered a 'concernedSensor'
    // We store dist(AC, s) as well as the change in gas values between start and end of AirCleaner's life.
    if(isNearestAirCleaner(AC, s)) 
    {
      nearbySensorDistance.insert(make_pair(distanceEarth(AC.latitude, AC.longitude, s.latitude, s.longitude),s));     
      int index = stoi(s.id)*4;

      moltup t = make_tuple(
        backend.data[index+O3].value - startVal[index+O3].value ,
        backend.data[index+SO2].value - startVal[index+SO2].value,
        backend.data[index+NO2].value - startVal[index+NO2].value,
        backend.data[index+PM10].value - startVal[index+PM10].value
      );
      deltaVals.insert(make_pair(s.id,t));
    } 
  }
  
  // This boolean will be false until we find an appropriate cutoff point for our list of sensors.
  // Once it is true, the loop will stop and we can cut the rest of out list off.
  multimap<double,Sensor>::iterator cutoffIndex;
  // this int will store the number of times the one of the elements of moltup t has been > 0
  // in a row. If this is > 3, we can infer that the impact of the aircleaner is no longer positive
  // at this distance.
  int positiveDeltaStreak = 0;

  for( multimap<double,Sensor>::iterator it = nearbySensorDistance.begin(); it != nearbySensorDistance.end(); ++it )
  {
    Sensor s = it->second;
    moltup t = deltaVals.find(s.id)->second;
    
    if(get<O3>(t) > 0 || get<SO2>(t) > 0 || get<NO2>(t) > 0 || get<PM10>(t) > 0) {
      ++positiveDeltaStreak;
    } else {
      positiveDeltaStreak = 0;
    }

    if(positiveDeltaStreak >= 3) {
      cutoffIndex = it;
      break;
    }
  }

  nearbySensorDistance.erase(cutoffIndex, nearbySensorDistance.end());

  for( multimap<double,Sensor>::iterator it = nearbySensorDistance.begin(); it != nearbySensorDistance.end(); ++it ) {
    Sensor s = it->second;
    nearbySensorIds.insert(s.id);
  }

  // The radius will be the distance between AC and the furthest away sensor
  // which it has impacted. (The sensor at the end of nearbySensorDistance)
  double radius = (--nearbySensorDistance.end())->first;

  // We get the data from the ~month before the AirCleaner started
  backend.data.clear();
  backend.loadDataFileBetween(DecrementDayBy(AC.start, 31),DecrementDayBy(AC.start, 1));
  vector<Data> monthBeforeACData = backend.data;
  vector<moltup> monthBeforeACVals;

  // We filter the data by considering only data from sensors within our radius.
  // We add the values from the relevant data to a vector, for which we can calculate an ATMO index.
  for(int i=0; i<monthBeforeACData.size()-4; i+=4) {
    if(nearbySensorIds.find(monthBeforeACData[i].sensorId) != nearbySensorIds.end()) {
      moltup vals = make_tuple(
        monthBeforeACData[i+O3].value,
        monthBeforeACData[i+SO2].value,
        monthBeforeACData[i+NO2].value,
        monthBeforeACData[i+PM10].value
      );
      monthBeforeACVals.push_back(vals);
    }
  }

  Interval * beforeACInterval = getInterval(DecrementDayBy(AC.start, 31), DecrementDayBy(AC.start, 1));
  int monthBeforeACAtmo = getAtmo(monthBeforeACVals, beforeACInterval);

  // We get the data from the time that the AirCleaner was working
  backend.data.clear();
  backend.loadDataFileBetween(DecrementDayBy(AC.start, 1), AC.end);
  vector<Data> monthDuringACData = backend.data;
  vector<moltup> monthDuringACVals;

  // We filter the data by considering only data from sensors within our radius.
  // We add the values from the relevant data to a vector, for which we can calculate an ATMO index.
  for(int i=0; i<monthDuringACData.size()-4; i+=4) {
    if(nearbySensorIds.find(monthDuringACData[i].sensorId) != nearbySensorIds.end()) {
      moltup vals = make_tuple(
        monthDuringACData[i+O3].value,
        monthDuringACData[i+SO2].value,
        monthDuringACData[i+NO2].value,
        monthDuringACData[i+PM10].value
      );
      monthDuringACVals.push_back(vals);
    }
  }

  Interval * duringACInterval = getInterval(DecrementDayBy(AC.start, 1), AC.end);
  int monthDuringACAtmo = getAtmo(monthDuringACVals, duringACInterval);

  cout << "ATMO for month before AirCleaner = " << monthBeforeACAtmo << endl;
  cout << "ATMO for month during AirCleaner = " << monthDuringACAtmo << endl;
  cout << "Radius = " << radius << "km" << endl;

}

// This function takes a set of gas values and an interval of time
// as parameters, and returns the ATMO index of those values in that time
int AirWatcher::getAtmo( vector<moltup> vals, Interval* interval ){

  // We calculate the average value for each gas in vals
  moltup avg;
  for( moltup t : vals ){
    get<O3>(avg) += get<O3>(t);
    get<SO2>(avg) += get<SO2>(t);
    get<NO2>(avg) += get<NO2>(t);
    get<PM10>(avg) += get<PM10>(t);
      
  }

  get<O3>(avg) = get<O3>(avg)/vals.size();
  get<SO2>(avg) = get<SO2>(avg)/vals.size();
  get<NO2>(avg) = get<NO2>(avg)/vals.size();
  get<PM10>(avg) = get<PM10>(avg)/vals.size();

  // We get an index for each gas, using a helper function getIndex()
  int index[4] = 
  {
    getIndex(O3,get<O3>(avg)),
    getIndex(SO2,get<O3>(avg)),
    getIndex(NO2,get<O3>(avg)),
    getIndex(PM10,get<O3>(avg)),
  };

  // We return the maximum of those indices -- this is our ATMO index
  int maximum = index[0];
  for( int i=0; i<4; i++ ) {
    if( index[i] > maximum ) maximum = index[i];
  } 
  return maximum;
}

void AirWatcher::getSimilarSensors(string sensorId, string start, string end, double radius){

  Interval* interval = getInterval(start,end);
  int duration = interval->endDate - interval->startDate; 
  cout << "Duration =" << duration << " Radius =" << radius  << endl;


  backend.data.clear(); // we should just put this in the backend
  backend.Sensors.clear();
  backend.loadSensorsFile();
  backend.loadDataFileBetween(start,end);
  
  Sensor sensor = backend.Sensors[stoi(sensorId)]; 

  Zone zone = Zone(sensor.latitude,sensor.longitude,radius);

  map<int,moltup> avgVals;

  // we get the average values for each molecule type in a given zone in a given interval
  for( Sensor s:backend.Sensors){

    if( zone.IsWithin( s.latitude, s.longitude )){

      int sensorIndex = stoi(s.id);
      moltup t = make_tuple(0.0,0.0,0.0,0.0);

      //cout << sensorIndex << endl;
      for( int i= sensorIndex*4; i < sensorIndex*4+ duration*4; i +=4 ){
        get<O3>(t) += backend.data[i+O3].value;
        get<SO2>(t) += backend.data[i+SO2].value;
        get<NO2>(t) += backend.data[i+NO2].value;
        get<PM10>(t) += backend.data[i+PM10].value;
      }
      
      get<O3>(t) = get<O3>(t)/duration;
      get<SO2>(t) =  get<SO2>(t)/duration;
      get<NO2>(t) = get<NO2>(t)/duration; 
      get<PM10>(t) = get<PM10>(t)/duration;

      avgVals.insert(make_pair(sensorIndex,t));
      /*
      cout << sensorIndex << "-";
      printMoltup(t); 
      cout << endl;
      */
    }
  }

  // we normalize with the values of the sensor we chose

  moltup normal = avgVals.find(stoi(sensorId))->second;
  cout << "normal = ";
  printMoltup(normal);
  cout << endl;
  
  int tolerance = 10;
  int lower = 100 - tolerance;
  int upper = 100 + tolerance;

  for( map<int,moltup>::iterator it = avgVals.begin() ; it !=avgVals.end(); ++it ){
    
    if( it->first == stoi(sensorId) ) continue;



    moltup t = it->second;
    
    get<O3>(t) = get<O3>(t)/get<O3>(normal)*100;
    get<SO2>(t) =  get<SO2>(t)/get<SO2>(normal)*100;
    get<NO2>(t) = get<NO2>(t)/get<NO2>(normal)*100; 
    get<PM10>(t) = get<PM10>(t)/get<PM10>(normal)*100;

    if(
      get<O3>(t) >= lower && get<O3>(t) <= upper &&
      get<SO2>(t) >= lower && get<SO2>(t) <= upper &&
      get<NO2>(t) >= lower && get<NO2>(t) <= upper &&
      get<PM10>(t) >= lower && get<PM10>(t) <= upper
    )
      {
        cout << it->first << "-";
        printMoltup(t); 
        cout << endl;
      }
    
  } 
}

AirWatcher::AirWatcher(){

  backend = Backend();
  backend.loadDataFile();
  backend.loadSensorsFile();
  backend.loadAirCleaners();
}
