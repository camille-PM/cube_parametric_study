#include <fstream>
#include <iostream>
#include "header.h"

using namespace std;

/************************************************************
        	ATTRIBUTES STIMULUS VALUE TO EACH LATTICE POINT
*************************************************************/

void Lattice_stimulus (char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], std::vector<char>& stimulus)
{
    int i,j,k;
    for (i=0; i<LATTICE_X; ++i) {
    	for (j=0; j<LATTICE_Y; ++j) {
    		for (k=0; k<LATTICE_Z; ++k) {
    			if (lattice_points_element[i][j][k]!=0) { // it is a tissue element
    				lattice[i][j][k] = stimulus[lattice_points_element[i][j][k]-1];
				}
    		}
    	}
	}
}
