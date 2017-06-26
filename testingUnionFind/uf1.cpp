#include "disjointSet.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
int main()
{	
	DisjointSet::Node* nodeFound;
	int numInterations;
	vector<DisjointSet::Node*> v;
	vector<int>	vectorOfIDs(100);
	DisjointSet ds;
	int countMakeSet=0;

	while (!cin.eof())
	{
		
		vector <string> words; // used to split the line into substrings
		
		string line;
		// read line with make-set n, union n1 n2, or find n
		getline(cin, line);
		if (line.size()== 0){
			break;
		}
		istringstream iss(line);
		string s;
		while ( getline( iss, s, ' ' ) ) {
			words.push_back(s);
		}
		

		string operation = words[0]; // get operation
		int n1 = atoi(words[1].c_str()); // get n1
		int n2=-1; 
		if (operation.at(0)=='u'){   //UNION
			n2 = atoi(words[2].c_str()); // get n2
			int id_n1,id_n2;
			id_n1 =vectorOfIDs[n1];  // get id of nodes
			id_n2 =vectorOfIDs[n2];
			ds.unionSet(v[id_n1], v[id_n2]);
			
		}else if (operation.at(0)=='f'){ // FIND
			boost::tie(nodeFound, numInterations) =	ds.findSet(v[vectorOfIDs[n1]],0);
			ds.iterations[numInterations]++;
			cout << nodeFound->parent->data << endl;
		}else if (operation.at(0)=='m'){ //MAKESET
			v.resize(countMakeSet+1);
			if (int(vectorOfIDs.size()) < n1)
				vectorOfIDs.resize(n1+1);

			v[countMakeSet] = new DisjointSet::Node();
			v[countMakeSet]->id = countMakeSet;
			v[countMakeSet]->data = n1;

			vectorOfIDs[n1] = countMakeSet; // id
			ds.qtd++;
			countMakeSet++;
		}else{
			break;
		}

	}

	for (int i = 0; i < int(v.size()); ++i) {
		delete v[i];		
	}	
return 0;
}