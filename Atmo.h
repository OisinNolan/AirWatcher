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

int MolIndex[4][10] = {
    {0,30,55,80,105,130,150,180,210,240 },  // O3
    {0,40,80,120,160,200,250,300,400,500 }, // SO2
    {0,30,55,85,110,135,165,200,275,400 },  // NO2
    {0,7,14,21,28,35,42,50,65,80 }          // PM10
};

inline int getIndex( Molecule m, int val ){

    for( int i=0;i<9; i++ ){

        if( val >= MolIndex[m][i] && val < MolIndex[m][i+1]  ) return i+1;

    }

    return 10;
}

#endif