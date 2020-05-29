/*************************************************************************
                           Backend  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Backend> (fichier Backend.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
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

//----------------------------------------------------- Méthodes publiques
// type Backend::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

    bool Backend::loadSensorsFile() {


        int nb_of_lines = 0;
        ifstream fichier(sensorsFile.c_str());


        if(fichier)
        {

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne) && nb_of_lines < MAX_SENSORS_LINES) //Tant qu'on n'est pas à la fin, on lit
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

            list <Sensor> :: iterator it;
            for(it = Sensors.begin(); it != Sensors.end(); ++it)
                cout  << (*it).id << '|' << (*it).latitude << '|' << (*it).longitude << endl;
            cout << '\n';
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
            //L'ouverture s'est bien passée, on peut donc lire

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne) && nb_of_lines < MAX_DATA_LINES) //Tant qu'on n'est pas à la fin, on lit
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

            list <Data> :: iterator it;
            for(it = data.begin(); it != data.end(); ++it)
                cout  << (*it).time << '|' << (*it).sensorId << '|' << (*it).type << '|' << (*it).value << endl;
            cout << '\n';

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

        cout << dateFin << endl;

        if(fichier)
        {

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
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

            list <Data> :: iterator it;
            for(it = data.begin(); it != data.end(); ++it)
                cout  << (*it).time << '|' << (*it).sensorId << '|' << (*it).type << '|' << (*it).value << endl;
            cout << '\n';

            return true;

        }
        else
        {
          cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
          return false;
        }
    }



    bool Backend::fillData(Zone zone, string dateDebut, string dateFin) {
    //Rempli la liste Data avec les mesures prises dans la zone entre
    //la date de début et la date de fin.


        ifstream fichier(dataFile.c_str());


        if(fichier)
        {
            //L'ouverture s'est bien passée, on peut donc lire

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
            {

                string date = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                if(date > dateDebut && date < dateFin) {

                    string id = ligne.substr(0,ligne.find(';'));
                    id = id.erase(0,6);
                    ligne.erase(0, ligne.find(";")+1);

                    //on retrouve le capteur
                    list <Sensor> :: iterator it;
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
            list <Data> :: iterator it;
            for(it = data.begin(); it != data.end(); ++it)
                cout  << (*it).time << '|' << (*it).sensorId << '|' << (*it).type << '|' << (*it).value << endl;
            cout << '\n';

            return true;

        }
        else    {   cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;return false;}
    }






//------------------------------------------------- Surcharge d'opérateurs
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

    dataFile = "measurements.csv";
    sensorsFile = "sensors.csv";


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

//----------------------------------------------------- Méthodes protégées

