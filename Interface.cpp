
#include <iostream>
#include <string>

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
            case 1:
                break;
            case 2: {
                string airCleanerId;
                cout << "Enter AirCleaner ID: ";
                cin >> airCleanerId;
                cout << "\nImpact of AirCleaner " << airCleanerId << ":\n";
                cout << "-------------------------------------\n";
                AW.getImpact(airCleanerId);
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