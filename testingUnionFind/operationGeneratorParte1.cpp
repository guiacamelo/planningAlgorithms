
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cassert>
#include <time.h>
#include <iostream>
#include <string> 

using namespace std;

int main(int argc, char *argv[])
{
	ofstream output;

	int nodes = atoi(argv[1]);
	output.open (argv[2],std::ios::app); 
	for (int i = 0; i < nodes; ++i){			
		output<<"make-set " <<i<<"\n";
	}

	for (int i = 0; i < 100*nodes; ++i){			
		int a =rand() %5;
		if (a == 0) {
			output<<"union "<<rand()%nodes <<" "<< rand()%nodes <<"\n";

		}else{
			output<<"find "<<rand()%nodes<<"\n" ;
		}

	}

	output.close();
	return 0;
}

