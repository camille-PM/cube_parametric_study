#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "header.h"


using namespace std;

int main()
{
	vector<Point_abaqus> nodes;
	vector<Nodes> elements; // store element node indices
	vector<Point> element_local_min, element_local_max; // store min and max lattice indices for each element (cube containing it)
	float* Global_minimum = new float[3];
	float* Global_maximum = new float[3];
	vector<char> stimulus;
	char (*lattice)[LATTICE_Y][LATTICE_Z] = new char[LATTICE_X][LATTICE_Y][LATTICE_Z];
	int (*lattice_point_element)[LATTICE_Y][LATTICE_Z] = new int[LATTICE_X][LATTICE_Y][LATTICE_Z]; //element number for each lattice point
	
	srand((unsigned)time(NULL)); // seed for random numbers
    
	int number_elems, number_nodes; // to be read from input file
    int iteration;
    int i,j,k;
    float objective;
	
    /****************************************************************************************
    	Set lattice points (12:scaffold & plate, 11:bone, 0:free, age 666)
    *****************************************************************************************/
	int h = int(0.5/CELL_DIAMETER)+1; // 0.5 mm height;
	
	cout<<"Initialize lattice"<<endl;
	for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<LATTICE_Z;k++) {
                lattice[i][j][k]=0; // first empty everywhere, then given regions will be filled appropriately
						                
				// points in the cube containing the scaffold and modeled in ABAQUS are initialized as scaffold
            	if (k>h && k<LATTICE_Z-h-1) {
                	lattice[i][j][k]=12; // relevant positions will be freed for tissue later on
				}
        	}
    	}
    }
    
    /**************************************************************************************
                                              Read node file
    *****************************************************************************************/
    cout<<"Read nodes"<<endl;
    number_nodes = Read_node_file(nodes);
 
    /**************************************************************************************
                                              Read element file
    *****************************************************************************************/
    cout<<"Read elements"<<endl;
    number_elems = Read_element_file(elements);
	element_local_min.resize(number_elems);
	element_local_max.resize(number_elems);
	stimulus.resize(number_elems);
		
	/**************************************************************************************
                Read (initial) input file and write model file and first FEA input file
    *****************************************************************************************/
    cout<<"Prepare simulation file"<<endl;
	Prepare_simulation_file(number_elems);
 
    /**************************************************************************************
                                     Calculate dimensions of the lattice
    *****************************************************************************************/
    cout<<"Calculate dimensions lattice"<<endl;
    Calculate_lattice(elements,nodes,Global_minimum,Global_maximum);
    
    /**************************************************************************************
                               Calculate extreme values of x,y and z of the element
    *****************************************************************************************/
    cout<<"Calculate extreme dimensions element (cube that contains it)"<<endl;
    Extremes_element(elements,nodes,element_local_min,element_local_max,Global_minimum,Global_maximum); 

    /**************************************************************************************
                               Calculate lattice points inside each element
    *****************************************************************************************/
    cout<<"Calculate lattice points inside each tissue element and make them free"<<endl;
    Lattice_point_in_element(lattice,lattice_point_element,element_local_min,element_local_max,Global_minimum,Global_maximum,nodes,elements);
	    
    /**************************************************************************************
                                     Launch first FEA
    *****************************************************************************************/
    cout<<"run abaqus"<<endl;
    system("run.bat"); // ./run.bat in LINUX; run.bat in WINDOWS
        
    /****************************************************************************************
                                           Read stimulus
    *****************************************************************************************/   
    cout<<"Read stimulus"<<endl;
    Read_stimulus(stimulus, number_elems);
    
    /**************************************************************************************
                                           Proliferation
    *****************************************************************************************/   
    cout<<"Stimulus in lattice"<<endl;
    Lattice_stimulus(lattice,lattice_point_element,stimulus); 

    /**************************************************************************************
                        Compute objective and write output for MATLAB optimisation
    *****************************************************************************************/
    cout<<"Compute and output objective to text file"<<endl;
    objective = Compute_bone_volume(lattice);
    Write_text_output(objective);
    
	delete[] Global_minimum;
	delete[] Global_maximum;
	delete[] lattice;
	delete[] lattice_point_element;
	
    //system("PAUSE");
    return 0;
}
