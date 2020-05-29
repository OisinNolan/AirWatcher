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

    bool loadDataFileAfter(string dateRef);

    bool loadDataFileIn(pair<string,string> intervalle);

    bool fillData(Zone zone, string dateDebut, string dateFin);



    void hello();

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
    list<Sensor> Sensors;
    list<Data> data;

};

//-------------------------------- Autres définitions dépendantes de <Backend>

#endif // BACKEND_H

