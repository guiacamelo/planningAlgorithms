#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "vertex.h"

#include <boost/tuple/tuple.hpp>
using namespace std;

enum union_result_t {ORIGIN_IS_CHILD,TARGET_IS_CHILD,SAME_SET};

class DisjointSet
{
public:
	int qtd;
	int qtdFind;
	int qtdUnion;
	vector<int> iterations;
	class   Node 
	{	
	public:
		int 		id;
		int         data;
		int         rank;
		bool        isRoot;
		Node*       parent;
		int			numChild;

		Node() : data(0), rank(0),isRoot(true),numChild(0),
		parent(this) {} 
	};	
	DisjointSet() : qtd(0),qtdFind(0),qtdUnion(0){
		iterations.resize(20);
		for (int i = 0; i < 20; ++i) {
			iterations[i]=0;
		}
	} 
	void unionSetPC(Node* x,Node* y);
	void 	 unionSet(Node* x,Node* y);
	boost::tuple< Node*			 	,int> findSetPC(Node* x,int iterations);
	boost::tuple< Node*			 	,int> findSet(Node* x,int iterations);

};

