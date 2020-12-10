#include <fstream>
#include <iostream>
#include "header.h"

using namespace std;

/************************************************************
        	COUPLES LATTICE POINTS TO ELEMENTS
		For each lattice point, the corresponding FE is found.
		!! Applicable only for tetrahedral elements.
*************************************************************/

void Lattice_point_in_element (char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], vector<Point>& element_min, 
	vector<Point>& element_max,float Global_min[3], float Global_max[3],vector<Point_abaqus>& node_pos,vector<Nodes>& elem_nodes)
{
    int i,j,k;
    int elem;
    float xcoord,ycoord,zcoord;
    float face1[3][3],face2[3][3],face3[3][3],face4[3][3];
    int node;
    float s;

    for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<LATTICE_Z;k++) {
                lattice_points_element[i][j][k]=0;
            }
        }
    }
   
   
    for (elem=0;elem<elem_nodes.size();elem++)    
    {        
        //Calculate the four faces of the element
                   
        //  face 1: n0,n2,n1
        node=elem_nodes[elem].n0;
        face1[0][0]=node_pos[node-1].x;
        face1[0][1]=node_pos[node-1].y;
        face1[0][2]=node_pos[node-1].z;

        node=elem_nodes[elem].n2;
        face1[1][0]=node_pos[node-1].x;
        face1[1][1]=node_pos[node-1].y;
        face1[1][2]=node_pos[node-1].z;
                   
        node=elem_nodes[elem].n1;
        face1[2][0]=node_pos[node-1].x;
        face1[2][1]=node_pos[node-1].y;
        face1[2][2]=node_pos[node-1].z;                   

                   
        //  face 2: n0,n1,n3
        node=elem_nodes[elem].n0;
        face2[0][0]=node_pos[node-1].x;
        face2[0][1]=node_pos[node-1].y;
        face2[0][2]=node_pos[node-1].z;

        node=elem_nodes[elem].n1;
        face2[1][0]=node_pos[node-1].x;
        face2[1][1]=node_pos[node-1].y;
        face2[1][2]=node_pos[node-1].z;
                   
        node=elem_nodes[elem].n3;
        face2[2][0]=node_pos[node-1].x;
        face2[2][1]=node_pos[node-1].y;
        face2[2][2]=node_pos[node-1].z;                   

        //  face 3: n0,n3,n2
        node=elem_nodes[elem].n0;
        face3[0][0]=node_pos[node-1].x;
        face3[0][1]=node_pos[node-1].y;
        face3[0][2]=node_pos[node-1].z;

        node=elem_nodes[elem].n3;
        face3[1][0]=node_pos[node-1].x;
        face3[1][1]=node_pos[node-1].y;
        face3[1][2]=node_pos[node-1].z;
                   
        node=elem_nodes[elem].n2;
        face3[2][0]=node_pos[node-1].x;
        face3[2][1]=node_pos[node-1].y;
        face3[2][2]=node_pos[node-1].z;                   

        //  face 4: n1,n2,n3
        node=elem_nodes[elem].n1;
        face4[0][0]=node_pos[node-1].x;
        face4[0][1]=node_pos[node-1].y;
        face4[0][2]=node_pos[node-1].z;

        node=elem_nodes[elem].n2;
        face4[1][0]=node_pos[node-1].x;
        face4[1][1]=node_pos[node-1].y;
        face4[1][2]=node_pos[node-1].z;
                   
        node=elem_nodes[elem].n3;
        face4[2][0]=node_pos[node-1].x;
        face4[2][1]=node_pos[node-1].y;
        face4[2][2]=node_pos[node-1].z;                   
       
       
        for (k=element_min[elem].z;k<=element_max[elem].z;k++) {
            for (j=element_min[elem].y;j<=element_max[elem].y;j++) {
                for (i=element_min[elem].x;i<=element_max[elem].x;i++) {
                   
                    //Calculate position of lattice point in global coordinates
                    xcoord=i*CELL_DIAMETER+Global_min[0];
                    ycoord=j*CELL_DIAMETER+Global_min[1];
                    zcoord=k*CELL_DIAMETER+Global_min[2];

                    if (lattice_points_element[i][j][k]==0) // if it is equal to an element number the lattice point has already been checked
                    {
                        //check if lattice point is below face 1 of the element                      
                        s=Plane_intersection(face1,xcoord,ycoord,zcoord);
                        if (s<=0) {
                            s=Plane_intersection(face2,xcoord,ycoord,zcoord);
                            if (s<=0) {
                                s=Plane_intersection(face3,xcoord,ycoord,zcoord);
                                if (s<=0) {
                                    s=Plane_intersection(face4,xcoord,ycoord,zcoord);
                                    if (s<=0) {
                                        lattice_points_element[i][j][k]=elem+1;
										lattice[i][j][k]=0; //the lattice point is inside an element (of the tissue/callus) and therefore we make free the position for a cell
										//cout<<"element: "<<elem<<endl;
										//cout<<"lattice_point: "<<i<<", "<<j<<", "<<k<<endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }//end for element
     
}
