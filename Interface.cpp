
#include <iostream>
#include <string>
#include <chrono> 

#include "AirWatcher.h"


using namespace std;

int main(){

    AirWatcher AW = AirWatcher();

    // 'Logo' display on startup
    cout   
<< "\n\n\n           _   __          __   _       _\n"       
<< "     /\\   (_)  \\ \\        / /  | |     | |\n"              
<< "    /  \\   _ _ _\\ \\  /\\  / /_ _| |_ ___| |__   ___ _ __\n"
<< "   / /\\ \\ | | '__\\ \\/  \\/ / _` | __/ __| '_ \\ / _ \\ '__|\n"
<< "  / ____ \\| | |   \\  /\\  / (_| | || (__| | | |  __/ |\n" 
<< " /_/    \\_\\_|_|    \\/  \\/ \\__,_|\\__\\___|_| |_|\\___|_|\n CONSOLE INTERFACE\n\n";

    // User options displayed on a loop
    while(1)
    {
        cout << "\n--------------------------------------------------" << endl;
        cout << " Options" << endl;
        cout << "\t1: List all AirCleaners" << endl;
        cout << "\t2: View the impact of an AirCleaner" << endl;
        cout << "\t3: List all Sensors" << endl;
        cout << "\t4: View similar Sensors" << endl;
        cout << "\t0: Quit" << endl;
        cout << "--------------------------------------------------\n" << endl;
        int choix;
        cout << "> ";
        scanf("%d", &choix);
        switch(choix)
        {
            case 0:
                goto fin;
            case 1:{
                auto start = chrono::high_resolution_clock::now(); 
                AW.listAirCleaners();
                auto stop = chrono::high_resolution_clock::now(); 
                auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); 
                cout << "Execution time = " <<duration.count() << " milliseconds" << endl; 
                break;
                }
            case 2: {
                string airCleanerId;
                cout << "Enter AirCleaner ID: ";
                cin >> airCleanerId;
                cout << "\nImpact of AirCleaner " << airCleanerId << ":\n";
                cout << "-------------------------------------\n";
                auto start = chrono::high_resolution_clock::now(); 
                AW.getImpact(airCleanerId);
                auto stop = chrono::high_resolution_clock::now(); 
                auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); 
                cout << "Execution time = " <<duration.count() << " milliseconds" << endl; 
                break;
            }
            case 3:{
                auto start = chrono::high_resolution_clock::now(); 
                AW.listSensors();
                auto stop = chrono::high_resolution_clock::now(); 
                auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); 
                cout << "Execution time = " <<duration.count() << " milliseconds" << endl; 
                break;
            }
            case 4: {
                string sensorId;
                cout << "Enter Sensor ID: ";
                cin >> sensorId;

                string start;
                cout << "When do you want to start the search? Enter start date in the form YYYY-MM-DD: ";
                cin >> start;

                string end;
                cout << "When do you want to end the search? Enter end date in the form YYYY-MM-DD: ";
                cin >> end;

                double radius;
                cout << "How far away from Sensor " << sensorId << " do you want to search? Enter radius in KM: ";
                cin >> radius;

                int tolerance;
                cout << "How similar should the Sensors be to Sensor " << sensorId << "? Enter a percentage: ";
                cin >> tolerance;

                cout << "\n Sensors that are similar to Sensor " << sensorId << ":\n";
                cout << "----------------------------------------\n";
                 auto startT = chrono::high_resolution_clock::now(); 
                AW.getSimilarSensors(sensorId, start, end, radius, tolerance);
                auto stop = chrono::high_resolution_clock::now(); 
                auto duration = chrono::duration_cast<chrono::milliseconds>(stop - startT); 
                cout << "Execution time = " <<duration.count() << " milliseconds" << endl; 
                break;
            }

            default:
                cout << "You must choose a valid option." << endl;
                goto fin;
        }
    }

    fin:
    return 0;
}