#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include "header.h"

using namespace std;

/************************************************************
        	CELL PROLIFERATION
		Depending on Claes & Heigele stimulus and 
		predefined proliferation rates 
*************************************************************/

void Cell_proliferation(char cells_prol[LATTICE_X][LATTICE_Y][LATTICE_Z], short age_prol[LATTICE_X][LATTICE_Y][LATTICE_Z],vector<Point>& element_local_min,
	vector<Point>& element_local_max,int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z], vector<char>& stimulus_prol)
{
    int elem, elem2;
    int imin,imax,jmin,jmax,kmin,kmax;
    char stimulus;
    int i,j,k;
    int MSCs,fibroblasts,chondrocytes,mature_osteoblasts;
    int MSCs_to_prol,fibroblasts_to_prol,chondrocytes_to_prol,mature_osteoblasts_to_prol;
    int proliferated;
    int r1,r2,r3;
    int cell; // cell type
    
//    int resorp, bone, cartilage, fibrous;
//    resorp=bone=cartilage=fibrous=0;
        
    // Shuffle the elements to look them over in a random way (should not have a big impact though)
    vector<int> elements(stimulus_prol.size());
    for (elem=0;elem<elements.size();elem++){
    	elements[elem] = elem;
	}
	random_shuffle(elements.begin(), elements.end());
	
    for (elem2=0;elem2<elements.size();elem2++) {
		elem = elements[elem2];
		
//		if (stimulus_prol[elem] == 1)
//    		resorp++;
//    	if (stimulus_prol[elem] == 2)
//    		bone++;
//    	if (stimulus_prol[elem] == 4)
//    		cartilage++;
//    	if (stimulus_prol[elem] == 5)
//    		fibrous++;
		
		stimulus=stimulus_prol[elem];  
        imax=element_local_max[elem].x;
        imin=element_local_min[elem].x;
        jmax=element_local_max[elem].y;
        jmin=element_local_min[elem].y;
        kmax=element_local_max[elem].z;
        kmin=element_local_min[elem].z;
//        cout << "Stimulus " << stimulus << "; imin: " << imin << "; jmin: " << jmin << "; kmin: " << kmin << endl;

		MSCs=fibroblasts=chondrocytes=mature_osteoblasts=0;
		proliferated=0;
		
		for (i=imin;i<=imax;i++) {
			for (j=jmin;j<=jmax;j++) {
				for (k=kmin;k<=kmax;k++) {
					if (lattice_point_element[i][j][k]==elem+1) {
						switch (cells_prol[i][j][k]) {
							case 1:
								MSCs=MSCs+1;
								break;
							case 2:
								mature_osteoblasts=mature_osteoblasts+1;
								break;
							case 4:
								chondrocytes=chondrocytes+1;
								break;
							case 5:
								fibroblasts=fibroblasts+1;
								break;
						}
					}
				}
			}
		}
			 
			MSCs_to_prol=int(MSCs*0.6);
//			cout << "MSCs to proliferate: " << MSCs_to_prol << endl;
			fibroblasts_to_prol=int(fibroblasts*0.55);
			chondrocytes_to_prol=int(chondrocytes*0.20);
			mature_osteoblasts_to_prol=int(mature_osteoblasts*0.3);         
					 
			/******************************************
					 Proliferate MSCs
			******************************************/

			while (proliferated<MSCs_to_prol)
			{
			    r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
		        r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
		        r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
				i=imin+r1;
				j=jmin+r2;
				k=kmin+r3;
				
				if (lattice_point_element[i][j][k]==elem+1) // if still in same element
				{
					if (cells_prol[i][j][k]==1) // if it is an MSC here
					{
						cell=1;
						Cell_mitosis(cells_prol,i,j,k,cell,age_prol);                        
						proliferated=proliferated+1;
						//cout << "One cell proliferated!" << endl;               
					}
				}
				//cout << proliferated*(elem+1) << endl;
			}
	   
			proliferated=0;
			 
			/******************************************
				Proliferate fibroblasts 
			******************************************/
			if (stimulus==5)
			{
				while (proliferated<fibroblasts_to_prol)
				{
				    r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
			        r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
			        r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
					i=imin+r1;
					j=jmin+r2;
					k=kmin+r3;
					if (lattice_point_element[i][j][k]==elem+1)
					{
						if (cells_prol[i][j][k]==5)
						{
							cell=5;
							Cell_mitosis(cells_prol,i,j,k,cell,age_prol);                        
							proliferated=proliferated+1;                   
						}
					}
				}		  
			}

			proliferated=0;         

			/******************************************
				Proliferate chondrocytes
			******************************************/
			if (stimulus==4)
			{
				while (proliferated<chondrocytes_to_prol)
				{
				    r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
			        r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
			        r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
					i=imin+r1;
					j=jmin+r2;
					k=kmin+r3;
					  
					if (lattice_point_element[i][j][k]==elem+1)
					{
						if (cells_prol[i][j][k]==4)
						{
							cell=4;
							Cell_mitosis(cells_prol,i,j,k,cell,age_prol);                        
							proliferated=proliferated+1;                   
						}
					}
				}						 
			}     
			 
			proliferated=0; 
			 
			/******************************************
				Proliferate mature osteoblasts
			******************************************/
			if (stimulus==2)
			{
				while (proliferated<mature_osteoblasts_to_prol)
				{
				    r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
			        r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
			        r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
					i=imin+r1;
					j=jmin+r2;
					k=kmin+r3;
					if (lattice_point_element[i][j][k]==elem+1)
					{
						if (cells_prol[i][j][k]==2)
						{
							cell=2;
							Cell_mitosis(cells_prol,i,j,k,cell,age_prol);                        
							proliferated=proliferated+1;                   
						}
					}
				}
			}     
//        }  // end else (when if loop used)		
    }// end for element
     
    //Change all the new cells to cell number  
    for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for(k=0;k<LATTICE_Z;k++) {
                switch (cells_prol[i][j][k]) {
                    case 6:
                        cells_prol[i][j][k]=1;
                        break;
                    case 7:
                        cells_prol[i][j][k]=2;
                        break;
                    case 8:
                        cells_prol[i][j][k]=3;
                        break;
                    case 9:
                        cells_prol[i][j][k]=4;
                        break;
                    case 10:
                        cells_prol[i][j][k]=5;
                        break;
                }
            }
        }
    }
    
//    cout<<"Resorption: "<<resorp<<endl;
//    cout<<"Bone: "<<bone<<endl;
//    cout<<"Cartilage: "<<cartilage<<endl;
//    cout<<"Fibrous tissue: "<<fibrous<<endl;    
}
