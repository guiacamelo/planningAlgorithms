#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "vertex.h"
#include <gridmap.h>
#include <globals.h>
using namespace std;

typedef list<Vertex> ListAdj;

class Graph {
private:
    vector<ListAdj> graph;

public:

    Graph();



    ListAdj insertNeighbour(ListAdj ListAdj,int id, int distance);
    ListAdj newVertex(int id);
    void print();
    int graphSize(){
        return graph.size();
    }


    void addEdge(int origin, int destiny, int distance);
    void insertVertex(ListAdj ListAdj);
    ListAdj* getNeighbourhood(int id);

    void loadGraph(string file);
    void buildRoadMap(GRID & grid);
    int originX;
    int originY;
    int goalX;
    int goalY;
    void setOrigin(int x,int y);
    void setGoal(int x,int y);

};

#endif // GRAPH_H
