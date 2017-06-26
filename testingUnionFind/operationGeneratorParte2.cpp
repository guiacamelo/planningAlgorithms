
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cassert>
#include <time.h>
#include <iostream>
#include <string> 
#include <math.h> 

using namespace std;

int main(int argc, char *argv[])
{
	/* initialize random seed: */
 	 srand (time(NULL));
	int i = atoi(argv[1]);
	int nodes = pow(2,i);
	int edges = nodes/2;
	for (int i = 0; i < nodes; ++i){			
		cout<<"make-set " <<i<<"\n";
	}

	for (int i = 0; i < edges; ++i){			
		
		cout<<"union "<<rand()%nodes <<" "<< rand()%nodes <<"\n";


	}

	return 0;
}

