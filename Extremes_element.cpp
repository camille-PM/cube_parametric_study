#include <fstream>
#include <iostream>
#include <vector>
#include "header.h"

using namespace std;

/************************************************************
        	COMPUTE EXTREMES OF EACH ELEMENT
		Min and max coordinates of each element (defines the cube containing it)
*************************************************************/

void Extremes_element(vector<Nodes>& extremes_element_nodes, vector<Point_abaqus>& extremes_node_positions, vector<Point>& extreme_min, 
	vector<Point>& extreme_max, float Global_min_extreme[3],float Global_max_extreme[3])
{
    int elem,node;
    int j; 
    float xmin,xmax,ymin,ymax,zmin,zmax;
     
    for (elem=0;elem<extremes_element_nodes.size();elem++) {
		node=extremes_element_nodes[elem].n0;
        xmin=extremes_node_positions[node-1].x;
        xmax=extremes_node_positions[node-1].x;
        ymin=extremes_node_positions[node-1].y;
        ymax=extremes_node_positions[node-1].y;
        zmin=extremes_node_positions[node-1].z;
        zmax=extremes_node_positions[node-1].z;
         
        for (j=1;j<4;j++) {
			if (j==1) {
        		node=extremes_element_nodes[elem].n1;
			}
			if (j==2) {
        		node=extremes_element_nodes[elem].n2;
			}
			if (j==3) {
        		node=extremes_element_nodes[elem].n3;
			}
			
            if (extremes_node_positions[node-1].x<xmin) {
                xmin=extremes_node_positions[node-1].x;
            }
            if (extremes_node_positions[node-1].x>xmax) {
                xmax=extremes_node_positions[node-1].x;
            }
            if (extremes_node_positions[node-1].y<ymin) {
                ymin=extremes_node_positions[node-1].y;
            }
            if (extremes_node_positions[node-1].y>ymax) {
                ymax=extremes_node_positions[node-1].y;
            }
            if (extremes_node_positions[node-1].z<zmin) {
                zmin=extremes_node_positions[node-1].z;
            }
            if (extremes_node_positions[node-1].z>zmax) {
                zmax=extremes_node_positions[node-1].z;
            }
        }
         
//        cout<<"xmin: "<<xmin<<endl;
//        cout<<"xmax: "<<xmax<<endl;       
//        cout<<"ymin: "<<ymin<<endl;
//        cout<<"ymax: "<<ymax<<endl;   
//        cout<<"zmin: "<<zmin<<endl;
//        cout<<"zmax: "<<zmax<<endl;   
           
        extreme_min[elem].x=int(((xmin-Global_min_extreme[0])/CELL_DIAMETER)+0.5); 
        extreme_min[elem].y=int(((ymin-Global_min_extreme[1])/CELL_DIAMETER)+0.5);
        extreme_min[elem].z=int(((zmin-Global_min_extreme[2])/CELL_DIAMETER)+0.5);
        extreme_max[elem].x=int(((xmax-Global_min_extreme[0])/CELL_DIAMETER)+0.5);                  
        extreme_max[elem].y=int(((ymax-Global_min_extreme[1])/CELL_DIAMETER)+0.5);
        extreme_max[elem].z=int(((zmax-Global_min_extreme[2])/CELL_DIAMETER)+0.5);
         
//        cout<<"element: "<<elem<<endl;
//        cout<<"xmin cell: "<<extreme_min[elem].x<<endl;
//        cout<<"xmax cell: "<<extreme_max[elem].x<<endl;
//        cout<<"ymin cell: "<<extreme_min[elem].y<<endl;
//        cout<<"ymax cell: "<<extreme_max[elem].y<<endl;
//        cout<<"zmin cell: "<<extreme_min[elem].z<<endl;
//        cout<<"zmax cell: "<<extreme_max[elem].z<<endl;
			
    }
}
