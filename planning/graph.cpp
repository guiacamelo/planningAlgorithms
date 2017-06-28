#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "graph.h"
#include <algorithm>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsItem>
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

void Graph::buildRoadMapSamples(GRID & grid,int originX,int originY,int goalX,int goalY){
    int i=0;
    // empty the graph
    for(int k = 0; k < graph.size(); k++) graph.pop_back();
    int originId=grid[originX][originY].id;
    int goalId =grid[goalX][goalY].id;

    sampleIds.clear();    sampleIdsX.clear();    sampleIdsY.clear();

    sampleIds.push_back(originId);
    sampleIdsX.push_back(originX);
    sampleIdsY.push_back(originY);
    grid[originX][originY].isVertex = true;
    //cout<<" X-"<<originX<<"   Y -"<<originY<<"   id -"<<originId<<endl;
    insertVertex(newVertex(originId));



    sampleIds.push_back(goalId);
    sampleIdsX.push_back(goalX);
    sampleIdsY.push_back(goalY);
    grid[goalX][goalY].isVertex = true;
    //Initialization
    //cout<<" X-"<<goalX<<"   Y -"<<goalY<<"   id -"<<goalId<<endl;
    insertVertex(newVertex(goalId));





    //add initial points to unionfind
//    unionFind(originId);
//    unionFind(goalId);



    //connect Samples

    //graphsearch


    //print();
    //Max number of vertex would be N = GRID_SIZE*GRID_SIZE, number of cells
    //    while(i<(GRID_SIZE*GRID_SIZE))
    //    {

    //    }
    randomSampling(grid,originId,goalId);
}

//CREATE RANDOM SAMPLE ONLY CONSIDERS FREE SPACES
void Graph::randomSampling(GRID & grid,int idOrigin,int idGoal){
    for (int k = 0; k < SAMPLES; ++k) {
        int randX =round((rand()/(double)RAND_MAX)*((double)GRID_SIZE-1));
        int randY =round((rand()/(double)RAND_MAX)*((double)GRID_SIZE-1));

        //Only get free sampĺes
        if (!grid[randX][randY].obstacle){
            int sampleId= grid[randX][randY].id;
            // check if sample is not origin or goal Also check is same sample have not yet been added
            if ((sampleId!=idOrigin) && (sampleId!=idGoal)
                    &&!(std::find(sampleIds.begin(), sampleIds.end(), sampleId) != sampleIds.end())
                    ){
                //cout<<sampleId<<endl;
                sampleIds.push_back(sampleId);
                sampleIdsX.push_back(randX);
                sampleIdsY.push_back(randY);
                insertVertex(newVertex(sampleId));
                grid[randX][randY].isVertex = true;

            }
        }

    }
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
