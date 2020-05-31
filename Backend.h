/*************************************************************************
                           Backend  -  description
                             -------------------
    d�but                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Backend> (fichier Backend.h) ----------------
#if ! defined ( BACKEND_H )
#define BACKEND_H

//--------------------------------------------------- Interfaces utilis�es

#include <vector>
#include <string>
#include "Zone.h"
#include "Sensor.h"
#include "Data.h"



//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// R�le de la classe <Backend>
//
//
//------------------------------------------------------------------------

class Backend
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    
    // I will add proper getter later maybe ??
    vector<Sensor> Sensors;
    vector<Data> data;

    
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
    // Donne une liste de donn�es restrictives

//------------------------------------------------- Surcharge d'op�rateurs
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
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s

    string dataFile;
    string sensorsFile;
};

//-------------------------------- Autres d�finitions d�pendantes de <Backend>

#endif // BACKEND_H

