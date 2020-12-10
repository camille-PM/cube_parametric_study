#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "header.h"

// For a new model: adapt LATTICE_X, LATTICE_Y, LATTICE_Z, NUMBER_ITERATIONS, NODES_PER_ELEM (header.h); min_elem_callus (update_model.cpp)
//       Initial cell seeding (Initialize_lattice.cpp and main.cpp)
//       Update_model.cpp : loads & BCs + file names + material properties (different species)
// 		 Calculate_lattice.cpp : adapt Global_min and Global_max if necessary (if boundaries different between FE model and 3D lattice)
//		 Cell_migration.cpp & Jump_migration.cpp: zones to be excluded from the migration process; number of jumps
//		 Read_stimulus: file name

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
	short (*age_cells)[LATTICE_Y][LATTICE_Z] = new short[LATTICE_X][LATTICE_Y][LATTICE_Z];
	int (*lattice_point_element)[LATTICE_Y][LATTICE_Z] = new int[LATTICE_X][LATTICE_Y][LATTICE_Z]; //element number for each lattice point
	vector< vector<float> > Young_modulus(NUMBER_ITERATIONS), Poisson_ratio(NUMBER_ITERATIONS); // contain material properties in each element, for each iteration
	
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
                age_cells[i][j][k]=666;
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

    /**************************************************************************************
                                    Material property initialization
    *****************************************************************************************/
	element_local_min.resize(number_elems);
	element_local_max.resize(number_elems);
	stimulus.resize(number_elems);
	
	for(int i=0;i<6;i++) {
		Young_modulus[i].resize(number_elems);
		Poisson_ratio[i].resize(number_elems);
		for(int elem=0; elem!=number_elems; elem++) {
			Young_modulus[i][elem] = 0.2;
			Poisson_ratio[i][elem]=0.167;
		}
	}
	for(int i=6;i<NUMBER_ITERATIONS;i++) {
		Young_modulus[i].resize(number_elems);
		Poisson_ratio[i].resize(number_elems);
	}
	
	/**************************************************************************************
                Read (initial) input file and write model file and first FEA input file
    *****************************************************************************************/
    cout<<"Prepare simulation files"<<endl;
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
                                        Initialize lattice
    *****************************************************************************************/
    cout<<"Initialize lattice"<<endl;
    Initialize_lattice(lattice,age_cells);                    
    
    /**************************************************************************************
                                     Launch first FEA
    *****************************************************************************************/
    cout<<"run abaqus"<<endl;
    system("run.bat"); // ./run.bat in LINUX; run.bat in WINDOWS
    
//    system("PAUSE");
    
    for (iteration=0;iteration<NUMBER_ITERATIONS;iteration++)
    {
    
        /****************************************************************************************
                                               Read stimulus
        *****************************************************************************************/   
        cout<<"Read stimulus"<<endl;
        Read_stimulus(stimulus, number_elems);   
        
        /**************************************************************************************
                                               Differentiation
        *****************************************************************************************/   
        if (iteration>5)
        {
           cout<<"Cell differentiation"<<endl;
           Cell_differentiation(lattice,age_cells,stimulus,element_local_min,element_local_max,lattice_point_element);           
        }  
        
        /**************************************************************************************
                                               Proliferation
        *****************************************************************************************/   
        cout<<"Cell proliferation"<<endl;
        Cell_proliferation(lattice,age_cells,element_local_min,element_local_max,lattice_point_element,stimulus); 
            
        /**************************************************************************************
                                               Migration
        *****************************************************************************************/   
        cout<<"Cell migration"<<endl;
        Cell_migration(lattice,age_cells,lattice_point_element);
        
        /**************************************************************************************
                                              Update model
        *****************************************************************************************/  
        if (iteration>5 && iteration<NUMBER_ITERATIONS-1) // no need to update model in the last iteration
        {
           cout<<"Update model"<<endl;
           Update_model(lattice, Young_modulus, Poisson_ratio, iteration, element_local_min, element_local_max, lattice_point_element);
        }
        /**************************************************************************************
                                           Increase cell age
        *****************************************************************************************/               
        
		if (iteration<NUMBER_ITERATIONS-1) // not for last iteration
		{
			cout<<"Increase_age"<<endl;
        	Cell_age(age_cells); 
    	}
             
        /**************************************************************************************
                                              Run abaqus
        *****************************************************************************************/  
        if (iteration>5 && iteration<NUMBER_ITERATIONS-1 && iteration%3==0) // no need to run ABAQUS model in the last iteration; run every 3 iterations
        {
            cout<<"run abaqus"<<endl;
            system("run.bat"); // ./run.bat in LINUX; run.bat in WINDOWS
        }
        
        cout<<"Iteration no."<<iteration<<" completed!"<<endl;
        
    }
    
    /**************************************************************************************
                        Compute objective and write output for MATLAB optimisation
    *****************************************************************************************/
    cout<<"Compute and output objective to text file"<<endl;
    objective = Compute_bone_volume(lattice);
    Write_text_output(objective);
    
	delete[] Global_minimum;
	delete[] Global_maximum;
	delete[] lattice;
	delete[] age_cells;
	delete[] lattice_point_element;
	
    //system("PAUSE");
    return 0;
}
