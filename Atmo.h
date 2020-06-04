#ifndef ATMO_H
#define ATMO_H

#include <map>

// Used in the calculation of atmo index
// if a number is greater than one value and less then the next
// its atmo index is its index  

enum Molecule{
	O3,
    SO2,
    NO2,
    PM10,
};

inline int getIndex( Molecule m, int val ){

    for( int i=0;i<9; i++ ){

        if( val >= MolIndex[m][i] && val < MolIndex[m][i+1]  ) return i+1;

    }

    return 10;
}

#endif