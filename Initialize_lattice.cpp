#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <cmath>
#include <math.h>
#include "header.h"

using namespace std;

/************************************************************
        	INITIALIZE LATTICE
		Seeding MSCs in predefined spaces
		Here: in 30% of the volume 0.5mm above and below the cube
*************************************************************/

void Initialize_lattice(char initial_lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], short initial_age[LATTICE_X][LATTICE_Y][LATTICE_Z])
{
    int elem;
    int free_positions;
    int points=0;
    int r1,r2,r3;
    int osteoblasts_to_seed;
    int seeded_cells=0;
    int i,j,k;
    int i1,i2;
    int h;  
 
    //*********************************************************************
    //          Seeding of MSCs: from above and below cube
    //********************************************************************

	h = int(0.5/CELL_DIAMETER)+1; // 0.5 mm height
	
	for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<h/3;k+=3) { // 30% positions 
            	if (initial_lattice[i][j][h-k]==0) { // free position
                	initial_lattice[i][j][h-k]=1; // seed one MSC with age 1
 					initial_age[i][j][h-k]=1;
 				}
 				if (initial_lattice[i][j][LATTICE_Z-h+k]==0) { // free position
                	initial_lattice[i][j][LATTICE_Z-h+k]=1; // seed one MSC with age 1
 					initial_age[i][j][LATTICE_Z-h+k]=1;
 				}
 			}
 		}
 	}

}
