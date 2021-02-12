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
	system("del cube.inp");
	ofstream myfile, mytxtfile;
	myfile.open("cube.inp"); // initial simulation file
	ifstream infile("Job-1.inp");
	
	// Read & copy job file until ELSET section
	string line;
    getline(infile,line);
    while (line!="** Section: tissue") {
    	myfile<<line<<endl;
    	getline(infile,line);
    }
	
	// Copy rest of the file
	getline(infile,line); // *Solid Section, elset=t, material=tt
	myfile<<line<<endl;
	getline(infile,line); // ,
	myfile<<line<<endl;
	getline(infile,line); // *End Part
	myfile<<line<<endl;
	while (line!=" 0.2, 0.167") {
    	myfile<<line<<endl;
    	getline(infile,line);
    }
    
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
