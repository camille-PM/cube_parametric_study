#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "header.h"

using namespace std;

/************************************************************
        	PREPARE SIMULATION FILE
		For the given scaffold geometry (from optimisation loop)
		the new text files for the bone regeneration simulation
		are written.
*************************************************************/

void Prepare_simulation_file(int number_elems)
{
	// Open files
	system("del Cube_model.txt"); // remove previous model file (from previous simulation)
	system("del cube.inp");
	ofstream myfile, mytxtfile;
	mytxtfile.open("Cube_model.txt"); // model file to be used in later iterations
	myfile.open("cube.inp"); // initial simulation file
	ifstream infile("Job-1.inp");
	
	// Read & copy job file until ELSET section
	string line;
    getline(infile,line);
    while (line!="** Section: tissue") {
    	myfile<<line<<endl;
    	mytxtfile<<line<<endl;
    	getline(infile,line);
    }
	
	// Write set & section descriptions (one set & section per element) into model file
	int elem;
	for (elem=0;elem<number_elems;elem++) {
		ostringstream s1,s2;
		s2<<"Elset_"<<elem+1;
		string elemsetname=s2.str();
		s1<<"material_"<<elem+1;
		string materialname=s1.str();
		mytxtfile << "*Elset, elset="<<elemsetname<<endl;
		mytxtfile<<elem+1<<endl;
		mytxtfile<<"*Solid section, elset="<<elemsetname<<", "<<"material="<<materialname<<endl;
		mytxtfile<<"1.,"<<endl;
	}
	
	// Copy rest of the file
	getline(infile,line); // *Solid Section, elset=t, material=tt
	myfile<<line<<endl;
	getline(infile,line); // ,
	myfile<<line<<endl;
	getline(infile,line); // *End Part
	myfile<<line<<endl;
	while (line!="1000., 0.3") {
    	myfile<<line<<endl;
    	mytxtfile<<line<<endl;
    	getline(infile,line);
    }
    mytxtfile<<line;
    mytxtfile.close(); // close model text file
    
    while (line!="** OUTPUT REQUESTS") { // copy rest to initial job file
    	myfile<<line<<endl;
    	getline(infile,line);
    }
	
	// Write ending into job file (E and S output in dat file)
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
	
	// Close files
	infile.close();
	myfile.close();
}
