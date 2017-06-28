#ifndef GRIDMAP_H
#define GRIDMAP_H

#include"globals.h"
#include <vector>

class GridMap
{
public:
    GridMap();
    GRID grid;
    void setOrigin(int x,int y);
    void setGoal(int x,int y);
    int originX;
    int originY;
    int goalX;
    int goalY;

};

#endif // GRIDMAP_H
