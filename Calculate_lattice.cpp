#include <fstream>
#include <iostream>
#include <vector>
#include "header.h"

using namespace std;

/************************************************************
        	CALCULATE LATTICE
		Compute minimum and maximum lattice coordinates
		depending on FEA geometry 
*************************************************************/

void Calculate_lattice(vector<Nodes>& lattice_element, vector<Point_abaqus>& lattice_node_position, float Global_min[3], float Global_max[3])
{
    float xmin,xmax;
    float ymin,ymax;
    float zmin,zmax;
    int size_x,size_y,size_z;    
    int node,element;
    int j;
    
    node=lattice_element[0].n1;
    xmin=lattice_node_position[node-1].x;
    xmax=lattice_node_position[node-1].x;
    ymin=lattice_node_position[node-1].y;
    ymax=lattice_node_position[node-1].y;
    zmin=lattice_node_position[node-1].z;
    zmax=lattice_node_position[node-1].z;
    
    
    for (element=0;element<lattice_element.size();element++) {
    
        for (j=0;j<4;j++) {
        	if (j==0) {
        		node=lattice_element[element].n0;
			}
			if (j==1) {
        		node=lattice_element[element].n1;
			}
			if (j==2) {
        		node=lattice_element[element].n2;
			}
			if (j==3) {
        		node=lattice_element[element].n3;
			}

            if (lattice_node_position[node-1].x<xmin && lattice_node_position[node-1].x!=999999)
            {
               xmin=lattice_node_position[node-1].x;
            }
            if (lattice_node_position[node-1].x>xmax && lattice_node_position[node-1].x!=999999)
            {
               xmax=lattice_node_position[node-1].x;
            }
            if (lattice_node_position[node-1].y<ymin && lattice_node_position[node-1].y!=999999)
            {
               ymin=lattice_node_position[node-1].y;
            }
            if (lattice_node_position[node-1].y>ymax && lattice_node_position[node-1].y!=999999)
            {
               ymax=lattice_node_position[node-1].y;
            }
            if (lattice_node_position[node-1].z<zmin && lattice_node_position[node-1].z!=999999)
            {
               zmin=lattice_node_position[node-1].z;
            }
            if (lattice_node_position[node-1].z>zmax && lattice_node_position[node-1].z!=999999)
            {
               zmax=lattice_node_position[node-1].z;
            }
        
            //system("PAUSE");
        }
    }
    
    Global_min[0]=xmin; 
    Global_min[1]=ymin;
    Global_min[2]=zmin-0.5; // global min in the lattice model is 0.5mm lower than in Abaqus
    
//    cout<<"Global minimum x: "<<Global_min[0]<<endl;
//    cout<<"Global minimum y: "<<Global_min[1]<<endl;
//    cout<<"Global minimum z: "<<Global_min[2]<<endl;
    
    Global_max[0]=xmax;
    Global_max[1]=ymax;
    Global_max[2]=zmax+0.5;

/*    cout<<"Global maximum x: "<<Global_max[0]<<endl;
    cout<<"Global maximum y: "<<Global_max[1]<<endl;
    cout<<"Global maximum z: "<<Global_max[2]<<endl;
    
    // Global lattice dimensions
    size_x=int(((xmax-xmin)/CELL_DIAMETER)+0.5)+1;
    size_y=int(((ymax-ymin)/CELL_DIAMETER)+0.5)+1;
    size_z=int(((zmax-zmin)/CELL_DIAMETER)+0.5)+1;
    
            
    cout<<"number cells x direction: "<<x<<endl;
    cout<<"number cells y direction: "<<y<<endl;
    cout<<"number cells z direction: "<<z<<endl; 
    system("PAUSE"); */

}
