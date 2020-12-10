#include <iostream>
#include <fstream>
#include <vector>
#include "header.h"

using namespace std; 

/************************************************************
        	READ ELEMENTS
		From the Job file generated from the optimisation loop
		Stores the node numbers for each FE in the vector nodes_element
		and returns the number of elements
*************************************************************/   

int Read_element_file(vector<Nodes>& nodes_element) 
{
    ifstream infile("Job-1.inp");
    int node, j; 	
    char comma;
    int i=0;
    Nodes nodes;
	
	string temp;
    infile>>temp;
    while (temp!="*Element,") {
    	infile>>temp;
    }
    
    infile>>temp; // type=C3D10
    infile>>temp; // first element
 	while (temp!="*Nset,") {   
		infile>>nodes.n0;
		infile>>comma;
		infile>>nodes.n1;
		infile>>comma;
		infile>>nodes.n2;
		infile>>comma;
		infile>>nodes.n3;
        
        for(j=4;j<NODES_PER_ELEM;j++) { // not useful for geometry definition
           infile>>comma;
           infile>>node;
        }
        
        nodes_element.push_back(nodes);
        infile>>temp; // next element (with comma) or *Nset,
		i++;        
    } 
    
    infile.close();
    return nodes_element.size();
}
