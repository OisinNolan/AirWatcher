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

#include <List>
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
    bool loadSensorsFile();

    bool loadDataFile();

    bool loadDataFileAfter(string dateRef);

    bool loadDataFileIn(pair<string,string> intervalle);

    bool fillData(Zone zone, string dateDebut, string dateFin);



    void hello();

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
    list<Sensor> Sensors;
    list<Data> data;

};

//-------------------------------- Autres d�finitions d�pendantes de <Backend>

#endif // BACKEND_H

