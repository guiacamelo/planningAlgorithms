#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "graph.h"

using namespace std;

Graph::Graph()
{
}

void Graph::setOrigin(int x,int y){
    originX=x;
    originY=y;
}

void Graph::setGoal(int x,int y){
    goalX=x;
    goalY=y;
}

void Graph::buildRoadMap(GRID & grid){
    int i=0;
    // empty the graph
    for(int k = 0; k < graph.size(); k++) graph.pop_back();

    //Initialization

    //Sampling

    //connect Samples

    //graphsearch
insertVertex(newVertex(1));
insertVertex(newVertex(2));
addEdge(1,2,9);
print();
    //Max number of vertex would be N = GRID_SIZE*GRID_SIZE, number of cells
//    while(i<(GRID_SIZE*GRID_SIZE))
//    {

//    }

}

void Graph::loadGraph(string fileName)
{
    ifstream fs;
    string in;
    int origin, destiny, distance;
    for(int i = 0; i < graph.size(); i++) graph.pop_back();
    fs.open(fileName.c_str());
    if (fs.is_open()){
        while(!fs.eof()){
            fs >> in;
            if(!in.compare("a")){
                fs>>in;origin = atoi (in.c_str());
                fs>>in;destiny = atoi (in.c_str());
                fs>>in;distance = atoi (in.c_str());
                addEdge(origin,destiny,distance);
            } else if (!in.compare("p")) {
              string dummy;
              unsigned nV, dummy2;
              fs >> dummy >> nV >> dummy2;
              //cout << "Graph has size " << nV << endl;
              graph.resize(nV);
            }
        }
        fs.close();
    }
    else cout <<"ERROR";
}


void Graph::addEdge(int origin, int destiny, int distance){
    ListAdj ListAdj;
    Vertex vertex(destiny,distance);

    if(origin > (int)graph.size()){
        for(int i = graph.size(); i < origin; i++){
            ListAdj = newVertex(i+1);
            insertVertex(ListAdj);
        }
    }
    graph[origin-1].push_back(vertex);
}
ListAdj Graph::insertNeighbour(ListAdj ListAdj,int id, int distance){
    Vertex v(id,distance);
    ListAdj.push_back(v);
    return ListAdj;
}

void Graph::insertVertex(ListAdj ListAdj){
    graph.push_back(ListAdj);
}

ListAdj* Graph::getNeighbourhood(int id){
    return &(graph[id-1]);
}

void Graph::print()
{
    vector<ListAdj>::iterator node;
    ListAdj::iterator it;
    int id;
    for(node = graph.begin(); node != graph.end(); node++){
        id = (*node).front().getId();
        for(it = (*node).begin(); it != (*node).end(); it++){
            cout << id << " " << (*it).getId() << " " << (*it).getDistance() << endl;
        }
    }
    cout << "Graph Size" <<graph.size() << endl;
}
ListAdj Graph::newVertex(int id){
    Vertex v(id,0);
    ListAdj ListAdj;
    ListAdj.push_back(v);
    return ListAdj;
}
