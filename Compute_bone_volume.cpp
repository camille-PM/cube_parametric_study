#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include "header.h"

using namespace std;

/************************************************************
        	COMPUTE BONE VOLUME
		In the available volume (not occupied by scaffold)
		at the end of the simulation
*************************************************************/

float Compute_bone_volume(char objective_lattice[LATTICE_X][LATTICE_Y][LATTICE_Z])
{
	float count_bone, count_scaffold, total;
	int h = int(0.5/CELL_DIAMETER)+1;
	total = LATTICE_X*LATTICE_Y*(LATTICE_Z-2*h);
	count_bone=count_scaffold=0.0;
	int i, j, k;
	
	for (i=0; i<LATTICE_X; i++) {
		for (j=0;j<LATTICE_Y;j++) {
            for (k=h+1;k<LATTICE_Z-h;k++) {
            	if (objective_lattice[i][j][k]==12) {
            		count_scaffold+=1;
				}
				if (objective_lattice[i][j][k]==2) {
            		count_bone+=1;
				}
            }
        }
	}
	
	return(count_bone/(total-count_scaffold));
}
