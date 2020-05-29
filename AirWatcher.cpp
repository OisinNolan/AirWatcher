#include <iostream>

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
void getImpact() {
    
}

int getAtmo() {

}

double getAverageAirQuality() {

}


int main() {
    return 0;
}