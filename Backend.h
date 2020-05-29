/*************************************************************************
                           Backend  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Backend> (fichier Backend.h) ----------------
#if ! defined ( BACKEND_H )
#define BACKEND_H

//--------------------------------------------------- Interfaces utilisées

#include <List>
#include <string>
#include "Zone.h"
#include "Sensor.h"
#include "Data.h"



//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Backend>
//
//
//------------------------------------------------------------------------

class Backend
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    bool loadSensorsFile();

    bool loadDataFile();
    // Mode d'emploi :
    //
    //  Retrieve MAX_DATA_LINES (set to 1000 by default) number of measurements from dataFile,
    //  in order to avoid fetching 140K lines of data.
    //
    // Contrat :
    //
    //
    //


    bool loadDataFileBetween(string dateDebut, string dateFin =  "4019-12-31 12:00:01");
    // Mode d'emploi :
    //
    //  Retrieve all measurements between dateDebut and dateFin.
    //  Can be used to retrieve all measurements after a certain date by setting dateDebut to 0,
    //  Can be used to retrieve all measurements before a certain date by by not passing anything
    //  off as this attribute (or by deliberately setting it very high).
    //
    // Contrat :
    //
    //
    //

    bool fillData(Zone zone, string dateDebut, string dateFin);

    string getDataFile() {return dataFile;}



    //bool Fill(Zone zone, char* dateStart, char* dateEnd);
    // Donne une liste de données restrictives

//------------------------------------------------- Surcharge d'opérateurs
    //Backend & operator = ( const Backend & unBackend );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Backend( const Backend & unBackend );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Backend();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Backend ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    string dataFile;
    string sensorsFile;
    list<Sensor> Sensors;
    list<Data> data;

};

//-------------------------------- Autres définitions dépendantes de <Backend>

#endif // BACKEND_H

