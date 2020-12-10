#include <iostream>
#include <fstream>
#include <vector>
#include "header.h"

using namespace std;

/************************************************************
        	READ NODES
		From the Job file generated from the optimisation loop
		Stores the coordinates for each node in the vector nodes_position
		and returns the number of nodes
*************************************************************/ 

int Read_node_file(vector<Point_abaqus>& nodes_position)
{
    ifstream infile("Job-1.inp");

    float pos_x,pos_y,pos_z;
    char comma;
    Point_abaqus coordinates;
    int node=0;
    
    string temp;
    infile>>temp;
    while (temp!="*Node") {
    	infile>>temp;
    }
	    
	infile>>temp; // first node
    while (temp!="*Element,") {
    	node++;
        //infile>>comma;
        infile>>coordinates.x;
        infile>>comma;
        infile>>coordinates.y;
        infile>>comma;
        infile>>coordinates.z;
        //system("PAUSE");
        
        nodes_position.push_back(coordinates); // new point added to the vector of nodes
        infile>>temp; // next node (or *Element)
    }
	
	infile.close();
	return nodes_position.size(); // last node index read is also the number of nodes 
}
