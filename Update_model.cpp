#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "header.h"

using namespace std;

/************************************************************
        	UPDATE MODEL
		At the end of each iteration
		Updates the material properties of each FE
		depending on the cell distribution
*************************************************************/ 

void Update_model(char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], vector< vector<float> >& Young_modulus_prop, vector< vector<float> >& Poison_ratio_prop, 
	int t_prop, vector<Point>& element_local_min, vector<Point>& element_local_max, int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z])
{    
    vector<float> Young_mod_elem(element_local_min.size());
	vector<float> Poison_rat_elem(element_local_min.size());
     
	int elem;
    int i,j,k;
    int imin,jmin,kmin;
    int imax,jmax,kmax;
    float total;
    float number_MSC,number_chondrocytes,number_fibroblasts,number_mature_osteoblasts;
    int count;
    int count2;
    int first_element = 1; // first element in callus
     
    for (elem=0;elem<(element_local_min.size());elem++)
    {
    	Young_mod_elem[elem]=Poison_rat_elem[elem]=0.0; // initialize value
            
        imin=element_local_min[elem].x;
        jmin=element_local_min[elem].y;
        kmin=element_local_min[elem].z;
        
        imax=element_local_max[elem].x;
        jmax=element_local_max[elem].y;
        kmax=element_local_max[elem].z;
         
        total=0.0;
        for (i=imin;i<imax;i++) {
            for (j=jmin;j<jmax;j++) {
                for (k=kmin;k<kmax;k++) {
                   if (lattice_point_element[i][j][k]==elem+1) {
                        total=total+1.0;
                   }
                }
            }
        }
                        
        if (total==0.0) {
            Young_mod_elem[elem]=0.2;
            Poison_rat_elem[elem]=0.167;
        }
        
        else {
            number_MSC=number_chondrocytes=number_fibroblasts=number_mature_osteoblasts=0;
    
            for (i=imin;i<imax;i++) {
                for (j=jmin;j<jmax;j++) {
                    for (k=kmin;k<kmax;k++) {
                        if (lattice_point_element[i][j][k]==elem+1) {
                            switch (lattice[i][j][k]) {
                                case 1:
                                    number_MSC=number_MSC+1.0;
                                    break;
                                case 2:
                                    number_mature_osteoblasts=number_mature_osteoblasts+1.0;
                                    break;
                                case 4:
                                    number_chondrocytes=number_chondrocytes+1.0;  
                                    break;
                                case 5:
                                    number_fibroblasts=number_fibroblasts+1.0; 
                                    break;    
                            }   
                        }
                    }
                }
            } //end for
            
	        Young_modulus_prop[t_prop][elem]=(number_chondrocytes*10.0/total)+(number_fibroblasts*2.0/total)
				+(number_mature_osteoblasts*17000.0/total)+((total-number_fibroblasts-number_mature_osteoblasts-number_chondrocytes)*0.2/total); 
	        Poison_ratio_prop[t_prop][elem]=(number_chondrocytes*0.167/total)+(number_fibroblasts*0.167/total)
				+(number_mature_osteoblasts*0.3/total)+((total-number_fibroblasts-number_chondrocytes-number_mature_osteoblasts)*0.167/total);
	
	        // Change of material properties - averaged over 10 iterations
			i=t_prop;         
	        count=0;
	        while (i>=0 && count<10) {
	            Young_mod_elem[elem]=Young_mod_elem[elem]+Young_modulus_prop[i][elem];
	            Poison_rat_elem[elem]=Poison_rat_elem[elem]+Poison_ratio_prop[i][elem];
	            count=count+1;
	            i=i-1;
	        }
	        if (count<=9) {
	            count2=10-count;
	            Young_mod_elem[elem]=Young_mod_elem[elem]+0.2*count2;
	            Poison_rat_elem[elem]=Poison_rat_elem[elem]+0.167*count2;
	        }
	         
	        Young_mod_elem[elem]=Young_mod_elem[elem]/10;
	        Poison_rat_elem[elem]=Poison_rat_elem[elem]/10;
	    } // end else total==0.0  
         
    }// end for element
    
    
	//************* Write to file ************//

	system("del cube.inp");
	system("copy Cube_model.txt cube.inp"); // cp in LINUX; copy in WINDOWS
	ofstream myfile;
	myfile.open("cube.inp",ios::app);
	for (elem=0;elem<Young_mod_elem.size();elem++)
	{
		ostringstream s1;
		s1<<"material_"<<elem+first_element;
		string materialname=s1.str();
		 
		myfile<<"\n*Material, name="<<materialname<<endl;
		myfile<<"*Elastic"<<endl;
		myfile<<Young_mod_elem[elem]<<","<<Poison_rat_elem[elem];
	}
	 
	//*** Write to file rest of FEM infodelation
	myfile<<"\n** BOUNDARY CONDITIONS"<<endl;
	myfile<<"**"<<endl;
	myfile<<"** Name: BC-1 Type: Symmetry/Antisymmetry/Encastre"<<endl;
	myfile<<"*Boundary"<<endl;
	myfile<<"m_Set-2, ENCASTRE"<<endl;
	myfile<<"**"<<endl;
	myfile<<"** ----------------------------------------------------------------"<<endl;
	myfile<<"**"<<endl;
	myfile<<"** STEP: Step-1"<<endl;
	myfile<<"** "<<endl;
	myfile<<"*Step, name=Step-1, nlgeom=NO"<<endl; 
	myfile<<"*Static"<<endl;
	myfile<<"1., 1., 1e-05, 1.,"<<endl; 
	myfile<<"** "<<endl;
	myfile<<"**--------------  Loads  ------------------------------------------"<<endl;
	myfile<<"**"<<endl;
	myfile<<"**"<<endl;
	myfile<<"** Name: Load-1   Type: Concentrated force"<<endl;
	myfile<<"*Cload"<<endl;
	myfile<<"m_Set-1, 3, -15."<<endl; 
	myfile<<"** "<<endl;
	myfile<<"**"<<endl;
	myfile<<"**---------------- OUTPUT REQUESTS -------------------------------"<<endl;
	myfile<<"** "<<endl;
	myfile<<"*Restart, write, frequency=0"<<endl;
	myfile<<"** "<<endl;
	myfile<<"** FIELD OUTPUT: F-Output-1"<<endl;
	myfile<<"**"<<endl; 
	myfile<<"*Output, field"<<endl;
	myfile<<"*Element Output, directions=YES"<<endl;
	myfile<<"E, S"<<endl;
	myfile<<"**"<<endl;
	myfile<<"**"<<endl;
	myfile<<"*EL PRINT, FREQUENCY=100, ELSET=Callus-1.Set-1"<<endl;
	myfile<<"EP, SP"<<endl;
	myfile<<"**"<<endl;
	myfile<<"**"<<endl;
	myfile<<"** HISTORY OUTPUT: H-Output-1"<<endl;
	myfile<<"**"<<endl;
	myfile<<"**"<<endl;
	myfile<<"*Output, history"<<endl;
	myfile<<"*Energy Output"<<endl;
	myfile<<"ALLAE,"<<endl;
	myfile<<"*End Step"<<endl;
    myfile.close();        
    
}
