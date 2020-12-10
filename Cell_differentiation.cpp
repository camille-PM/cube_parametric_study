#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "header.h"

using namespace std;

/************************************************************
        	CELL DIFFERENTIATION AND APOPTOSIS
		Depending on Claes & Heigele stimulus    
*************************************************************/

void Cell_differentiation(char cells_dif[LATTICE_X][LATTICE_Y][LATTICE_Z],short age_dif[LATTICE_X][LATTICE_Y][LATTICE_Z],vector<char>& stimulus_dif, 
	vector<Point>& element_local_min,vector<Point>& element_local_max,int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z])
{ 
    /************************************************************
        			CLAES-HEIGELE STIMULUS
		If Stimulus = 5               Fibrous tissue
        If Stimulus = 4               Cartilage (endochondral ossif)        
        If Stimulus = 2        		  Bone    
		If Stimulus = 1				  Resorption      
    *************************************************************/
     
    int elem;
    int points;
    int i,j,k;
    int imin,imax,jmin,jmax,kmin,kmax;
    int r1,r2,r3;
    int i1,j1,k1;
    int i2,j2,k2;
    int i3,j3,k3;
    int EC;
    int cells_to_differentiate;
    int cells_differentiated;
    int mature_osteoblasts,chondrocytes,fibroblasts;
    const int age_mature_cell=0;
    const int oxygen_diffusion_distance=10;
        
    int chondrocytes_apoptosis;
    int fibroblasts_apoptosis;
    int mature_osteoblasts_apoptosis;
    
    const float apoptosis_rate_osteoblasts=0.16;
    const float apoptosis_rate_chondrocytes=0.1;
    const float apoptosis_rate_fibroblasts=0.05;
    
    int chondrocytes_removed;
    int fibroblasts_removed;
    int mature_osteoblasts_removed;
    
    for (elem=0;elem<stimulus_dif.size();elem++) {
    	
        cells_to_differentiate=0;
        cells_differentiated=0;

        mature_osteoblasts=0;
        chondrocytes=0;
        fibroblasts=0;
        
        imax=element_local_max[elem].x;
        imin=element_local_min[elem].x;
        jmax=element_local_max[elem].y;
        jmin=element_local_min[elem].y;
        kmax=element_local_max[elem].z;
        kmin=element_local_min[elem].z;
         
        for (i=imin;i<imax;i++) {
            for (j=jmin;j<jmax;j++) {
                for (k=kmin;k<kmax;k++) {
                    if (lattice_point_element[i][j][k]==elem+1) {
                        
                        if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell) {
                            cells_to_differentiate=cells_to_differentiate+1;
                        }
                        if (cells_dif[i][j][k]==2) {
                            mature_osteoblasts=mature_osteoblasts+1;                          
                        }
                        if (cells_dif[i][j][k]==4) {
                           chondrocytes=chondrocytes+1;
                        }
                        if (cells_dif[i][j][k]==5) {
                           fibroblasts=fibroblasts+1;
                        }
                    }
                }
            }
        }
        
        cells_to_differentiate=int(cells_to_differentiate*0.3);
        
		mature_osteoblasts_apoptosis=int(mature_osteoblasts*apoptosis_rate_osteoblasts);
        chondrocytes_apoptosis=int(chondrocytes*apoptosis_rate_chondrocytes);
        fibroblasts_apoptosis=int(fibroblasts*apoptosis_rate_fibroblasts);
        chondrocytes_removed=fibroblasts_removed=mature_osteoblasts_removed=0;
        
        /*********************************************************************************************************
                                            FIBROUS TISSUE         
        **********************************************************************************************************/
        if (stimulus_dif[elem]==5)
        {
            //cout<<"fibroblast differentiation"<<endl;                 
            //CELL APOPTOSIS
            while (chondrocytes_removed<chondrocytes_apoptosis)
            {
                //cout<<"apoptosis chondrocytes under fibroblast stimulus"<<endl;
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {                       
                    if (cells_dif[i][j][k]==4)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        chondrocytes_removed=chondrocytes_removed+1;                    
                    }
                }
            }
                  
            //CELL DIFFERENTIATION
            while (cells_differentiated<cells_to_differentiate)
            {
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell)
                    {
                        cells_dif[i][j][k]=5;
                        age_dif[i][j][k]=1;
                        cells_differentiated=cells_differentiated+1;
                    }                                        
                }
            }                
        }//end stimulus fibrous tissue
        
        /*********************************************************************************************************
                                             CHONDROCYTES         
        **********************************************************************************************************/
          
        if (stimulus_dif[elem]==4)
        {
            //cout<<"cartilage differentiation"<<endl;
            //CELL APOPTOSIS
            while (fibroblasts_removed<fibroblasts_apoptosis)
            {
                //cout<<"apoptosis fibroblasts under cartilage stimulus"<<endl;
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==5)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        fibroblasts_removed=fibroblasts_removed+1;                    
                    }
                }
            }
                  
            //CELL DIFFERENTIATION
            while (cells_differentiated<cells_to_differentiate)
            {
                //cout<<"cartilage differentiation"<<endl;
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell)
                    {
                        cells_dif[i][j][k]=4;
                        age_dif[i][j][k]=1;
                        cells_differentiated=cells_differentiated+1;
                    }                                     
                }
            }                
                                  
        } //end stimulus chondrocyte
                 
        /*********************************************************************************************************
                                             MATURE BONE         
        **********************************************************************************************************/                  
        if (stimulus_dif[elem]==2)
        {
            //cout<<"mature bone differentiation"<<endl;                    
            //CELL APOPTOSIS
            while (fibroblasts_removed<fibroblasts_apoptosis)
            {
                       
                //cout<<"fibroblast apoptosis under mature bone stimulus"<<endl;                    
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==5)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        fibroblasts_removed=fibroblasts_removed+1;                    
                    }                                         
                }
            }

            while (chondrocytes_removed<chondrocytes_apoptosis)
            {
                //cout<<"chondrocytes apoptosis under mature bone stimulus"<<endl; 
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==4)
                    {
                        EC=1;
                        if (EC==1)
                        {
                            cells_dif[i][j][k]=0;
                            age_dif[i][j][k]=0;   
                        }
                        chondrocytes_removed=chondrocytes_removed+1;                    
                    }                                             
                }
            }        
     
            //CELL DIFFERENTIATION
            while (cells_differentiated<cells_to_differentiate)
            {
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    EC=1;                       
                    if (EC==1)  //There is oxygen
                    {
                       if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell)
                       {
                          cells_dif[i][j][k]=2;
                          age_dif[i][j][k]=1;
                          cells_differentiated=cells_differentiated+1;
                       }
                    }
                    else
                    {
                        if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell)
                        {
                           cells_dif[i][j][k]=4;
                           age_dif[i][j][k]=1;
                           cells_differentiated=cells_differentiated+1;
                        }
                    }                                                                            
                }// end if         
            }             
        } //end stimulus mature osteoblasts

        /*********************************************************************************************************
                                             BONE RESORPTION      
        **********************************************************************************************************/        
        if (stimulus_dif[elem]==1)
        {
                //CELL APOPTOSIS
            //cout<<"bone resorption"<<endl;

            while (fibroblasts_removed<fibroblasts_apoptosis)
            {
	            r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
            	i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==5)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        fibroblasts_removed=fibroblasts_removed+1;                    
                    }                                      
                }
            }
              
            while (chondrocytes_removed<chondrocytes_apoptosis)
            {
            	//cout<<"apoptosis chondrocytes under fibroblast stimulus"<<endl;
	            r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {                       
                    if (cells_dif[i][j][k]==4)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        chondrocytes_removed=chondrocytes_removed+1;                    
                    }
                }
            }

            while (mature_osteoblasts_removed<mature_osteoblasts_apoptosis)
            {
	            r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==2)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        mature_osteoblasts_removed=mature_osteoblasts_removed+1;                    
                    } 
                }
        	} 
        }//end for bone resorption
    }// end for element

} 
