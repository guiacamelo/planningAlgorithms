#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "disjointSet.h"

using namespace std;


boost::tuple< DisjointSet::Node*	,int>   DisjointSet::findSetPC(DisjointSet::Node* n,int iterations)
{
	qtdFind++;
	iterations++;
	if (n != n->parent) {
		DisjointSet::Node* foo;
		int bar;
		//return findSetPC(n->parent,iterations); //Without Path Compression
		boost::tie(foo, bar) = findSetPC(n->parent,iterations); // With Pash Compression
		n->parent = foo;
		iterations = bar;
	}
	return boost::make_tuple(n->parent,iterations);
}

//boost::tuple< union_result_t ,int> DisjointSet::unionSetPC(DisjointSet::Node* x,	DisjointSet::Node* y)
void DisjointSet::unionSetPC(DisjointSet::Node* x,	DisjointSet::Node* y)
{
	qtdUnion++;
	int iterationsX;
	int iterationsY;
	int bar;	
	boost::tie(x, iterationsX) = findSetPC(x,0);
	iterations[iterationsX]++;
	boost::tie(y, iterationsY) = findSetPC(y,0);
	iterations[iterationsY]++;
	
	if (x == y){
	
		return ;// return boost::make_tuple(SAME_SET,(iterationsX+iterationsY));
	}
	if (x->rank > y->rank) {
		y->parent = x; 	
		x->isRoot = true;
		y->isRoot = false;
		x->numChild += y->numChild + 1;
		qtd--;	
		return ;// returnboost::make_tuple(TARGET_IS_CHILD,(iterationsX+iterationsY));
	} else {
		x->parent = y;		
		y->isRoot = true;
		x->isRoot = false;
		y->numChild += x->numChild + 1;

		if (x->rank == y->rank) {
			++(y->rank);			
		}
		qtd--;
		return; //return boost::make_tuple(ORIGIN_IS_CHILD,(iterationsX+iterationsY));

	 
	}
}


//boost::tuple< union_result_t ,int> DisjointSet::unionSetPC(DisjointSet::Node* x,	DisjointSet::Node* y)
void DisjointSet::unionSet(DisjointSet::Node* x,	DisjointSet::Node* y)
{
	qtdUnion++;
	int iterationsX;
	int iterationsY;
	int bar;	
	boost::tie(x, iterationsX) = findSet(x,0);
	iterations[iterationsX]++;
	boost::tie(y, iterationsY) = findSet(y,0);
	iterations[iterationsY]++;
	
	if (x == y){
	
		return ;// return boost::make_tuple(SAME_SET,(iterationsX+iterationsY));
	}
	if (x->rank > y->rank) {
		y->parent = x; 	
		x->isRoot = true;
		y->isRoot = false;
		x->numChild += y->numChild + 1;
		qtd--;	
		return ;// returnboost::make_tuple(TARGET_IS_CHILD,(iterationsX+iterationsY));
	} else {
		x->parent = y;		
		y->isRoot = true;
		x->isRoot = false;
		y->numChild += x->numChild + 1;

		if (x->rank == y->rank) {
			++(y->rank);			
		}
		qtd--;
		return; //return boost::make_tuple(ORIGIN_IS_CHILD,(iterationsX+iterationsY));

	 
	}
}


boost::tuple< DisjointSet::Node*	,int>   DisjointSet::findSet(DisjointSet::Node* n,int iterations)
{
	qtdFind++;
	iterations++;
	if (n != n->parent) {
		DisjointSet::Node* foo;
		int bar;
		//return findSetPC(n->parent,iterations); //Without Path Compression
		return findSet(n->parent,iterations); // With Pash Compression		
	}
	return boost::make_tuple(n->parent,iterations);
}