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

using namespace std;

//------------------------------------------------------ Include personnel

#include "Sensor.h"
#include "Backend.h"

//------------------------------------------------------------- Constantes

const int MAX_DATA_LINES = 100;
const int MAX_SENSORS_LINES = 20;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
// type Backend::M�thode ( liste des param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode




    bool Backend::LoadDataFile()
    //Parcourt le fichier des mesures et les stockes.
    {
        int nb_of_lines = 0;
        string sensorFile = "measurements.csv";
        ifstream fichier(sensorFile.c_str());


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


                // */




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

    bool Backend::loadSensorsFile() {


        int nb_of_lines = 0;
        string sensorFile = "Sensors.csv";
        ifstream fichier(sensorFile.c_str());


        if(fichier)
        {
            //L'ouverture s'est bien pass�e, on peut donc lire

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne) && nb_of_lines < MAX_SENSORS_LINES) //Tant qu'on n'est pas � la fin, on lit
            {
                nb_of_lines++;
                //cout << ligne << endl;

                // /*
                string id = ligne.substr(0,ligne.find(';'));
                id = id.erase(0,6);
                //cout << "id = " << id << endl;
                ligne.erase(0, ligne.find(";")+1);

                string latitude = ligne.substr(0,ligne.find(';'));
                //cout << "latitude =" <<  latitude << endl;
                ligne.erase(0, ligne.find(";")+1);

                string longitude = ligne.substr(0,ligne.find(';'));
                //cout << "longitude = " << longitude << endl;
                ligne.erase(0, ligne.find(";")+1);

                double la = stod(latitude);
                double lo = stod(longitude);
                string descr = "";

                Sensor s(id,la, lo, descr);
                Sensors.push_back(s);
                // */




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


     bool Backend::loadDataFileAfter(string dateRef)
    //Parcourt le fichier des mesures et les stockes.
    {
        int nb_of_lines = 0;
        string sensorFile = "measurements.csv";
        ifstream fichier(sensorFile.c_str());


        if(fichier)
        {
            //L'ouverture s'est bien pass�e, on peut donc lire

            string ligne; //Une variable pour stocker les lignes lues

            while(getline(fichier, ligne)) //Tant qu'on n'est pas � la fin, on lit
            {
                nb_of_lines++;
                //cout << ligne << endl;

                // /*
                string date = ligne.substr(0,ligne.find(';'));
                ligne.erase(0, ligne.find(";")+1);

                if(date > dateRef) {

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
                // */




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

