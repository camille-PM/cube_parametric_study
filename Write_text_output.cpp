#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "header.h"

using namespace std;

/************************************************************
        	WRITE TEXT OUTPUT
		At the end of the simulation, writes the objective value
		for this scaffold geometry.
		To be read by the external optimisation loop
*************************************************************/ 

void Write_text_output(float objective)
{
	system("del out.info");
	ofstream myfile;
	myfile.open("out.info");
	myfile<<objective;
	myfile.close();
}
