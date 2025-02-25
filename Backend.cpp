/*************************************************************************
                           Backend  -  description
                             -------------------
    d�but                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- R�alisation de la classe <Backend> (fichier Backend.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <tuple>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Sensor.h"
#include "Backend.h"

//------------------------------------------------------------- Constantes

const int MAX_DATA_LINES = 1000;
const int MAX_SENSORS_LINES = 100;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
// type Backend::M�thode ( liste des param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode

    bool Backend::loadSensorsFile() {


        int nb_of_lines = 0;
        ifstream fichier(sensorsFile.c_str());


        if(fichier)
        {

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne) && nb_of_lines < MAX_SENSORS_LINES) //Tant qu'on n'est pas � la fin, on lit
            {
                nb_of_lines++;

                string id = ligne.substr(0,ligne.find(';'));
                id = id.erase(0,6);
                ligne.erase(0, ligne.find(";")+1);

                string latitude = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                string longitude = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                double la = stod(latitude);
                double lo = stod(longitude);
                string descr = "";

                Sensor s(id,la, lo, descr);
                Sensors.push_back(s);

            }

            /*
            vector <Sensor> :: iterator it;
            for(it = Sensors.begin(); it != Sensors.end(); ++it)
                cout  << (*it).id << '|' << (*it).latitude << '|' << (*it).longitude << endl;
            cout << '\n';
            */

            return true;

        }
        else
        {
          cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
          return false;
        }
    }




    bool Backend::loadDataFile()
    //Parcourt le fichier des mesures et les stockes.
    {
        int nb_of_lines = 0;
        ifstream fichier(dataFile.c_str());


        if(fichier)
        {
            //L'ouverture s'est bien pass�e, on peut donc lire

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne) && nb_of_lines < MAX_DATA_LINES) //Tant qu'on n'est pas � la fin, on lit
            {
                nb_of_lines++;
                //cout << ligne << endl;

                // /*
                string date = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                string id = ligne.substr(0,ligne.find(';'));
                id = id.erase(0,6);
                ligne.erase(0, ligne.find(";")+1);

                string molecule = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                string c = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                Data d(date, id, molecule, stod(c));
                data.push_back(d);

            }

            /*
            vector <Data> :: iterator it;
            for(it = data.begin(); it != data.end(); ++it)
                cout  << (*it).time << '|' << (*it).sensorId << '|' << (*it).type << '|' << (*it).value << endl;
            cout << '\n';
            */

            return true;

        }
        else
        {
          cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
          return false;
        }
    }


    bool Backend::loadDataFileBetween(string dateDebut, string dateFin)
    {
        ifstream fichier(dataFile.c_str());

        if(fichier)
        {

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne)) //Tant qu'on n'est pas � la fin, on lit
            {
                string date = ligne.substr(0,ligne.find(';'));

                ligne.erase(0, ligne.find(";")+1);

                if(date>dateDebut && date < dateFin)
                {
                    string id = ligne.substr(0,ligne.find(';'));
                    id = id.erase(0,6);
                    ligne.erase(0, ligne.find(";")+1);

                    string molecule = ligne.substr(0,ligne.find(';'));
                    ligne.erase(0, ligne.find(";")+1);

                    string c = ligne.substr(0,ligne.find(';'));
                    ligne.erase(0, ligne.find(";")+1);



                    Data d(date, id, molecule, stod(c));
                    data.push_back(d);


                }


            }

            /*
            vector <Data> :: iterator it;
            for(it = data.begin(); it != data.end(); ++it)
                cout  << (*it).time << '|' << (*it).sensorId << '|' << (*it).type << '|' << (*it).value << endl;
            cout << '\n';
            */

            return true;

        }
        else
        {
          cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
          return false;
        }
    }

    // Ideally this would read AirCleaners from csv, but im just using the objects
    // Aydin made for convenience here. If we have time we can parse the csv properly.
    bool Backend::loadAirCleaners() {
        // Here we get the AirCleaner data
        AirCleaner AC1 = AirCleaner(
        "AC1",
        45.333333,
        1.333333,
        "2019-02-01 12:00:00",
        "2019-03-01 00:00:00",
        "AirCleaner1"
        );

        AirCleaner AC2 = AirCleaner(
        "AC2",
        46.666667,
        3.666667,
        "2019-02-01 12:00:00",
        "2019-03-01 00:00:00",
        "AirCleaner2"
        );

        // We populate a hashmap with cleanerId as key, corresponding object as value,
        // for easy access.
        airCleaners[AC1.cleanerId] = AC1;
        airCleaners[AC2.cleanerId] = AC2;
    }



    bool Backend::fillData(Zone zone, string dateDebut, string dateFin) {
    //Rempli la liste Data avec les mesures prises dans la zone entre
    //la date de d�but et la date de fin.


        ifstream fichier(dataFile.c_str());


        if(fichier)
        {
            //L'ouverture s'est bien pass�e, on peut donc lire

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne)) //Tant qu'on n'est pas � la fin, on lit
            {

                string date = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                if(date > dateDebut && date < dateFin) {

                    string id = ligne.substr(0,ligne.find(';'));
                    id = id.erase(0,6);
                    ligne.erase(0, ligne.find(";")+1);

                    //on retrouve le capteur
                    vector <Sensor> :: iterator it;
                    for(it = Sensors.begin(); it != Sensors.end(); ++it)
                    {
                        if ((*it).id == id ) {

                            Sensor s = *it;

                            if(zone.IsWithin( s.latitude, s.longitude)) {

                                string molecule = ligne.substr(0,ligne.find(';'));
                                ligne.erase(0, ligne.find(";")+1);

                                string c = ligne.substr(0,ligne.find(';'));
                                ligne.erase(0, ligne.find(";")+1);

                                Data d(date, id, molecule, stod(c));
                                data.push_back(d);
                            }
                        break;

                        }
                    }


                }
            }

            //Affichage
            vector <Data> :: iterator it;
            for(it = data.begin(); it != data.end(); ++it)
                cout  << (*it).time << '|' << (*it).sensorId << '|' << (*it).type << '|' << (*it).value << endl;
            cout << '\n';

            return true;

        }
        else    {   cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;return false;}
    }






//------------------------------------------------- Surcharge d'op�rateurs
/*
Backend & Backend::operator = ( const Backend & unBackend )
// Algorithme :
//
{
} //----- Fin de operator =Backend
*/


//-------------------------------------------- Constructeurs - destructeur
/*
Backend::Backend ( const Backend & unBackend )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Backend>" << endl;
#endif
} //----- Fin de Backend (constructeur de copie)*/


Backend::Backend ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <Backend>" << endl;
    #endif

    dataFile = "csv/measurements.csv";
    sensorsFile = "csv/sensors.csv";


} //----- Fin de Backend


Backend::~Backend ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Backend>" << endl;
#endif
} //----- Fin de ~Backend


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

