#include "gridmap.h"

GridMap::GridMap()
{

}


void GridMap::setOrigin(int x,int y){
    originX=x;
    originY=y;
}

void GridMap::setGoal(int x,int y){
    goalX=x;
    goalY=y;
}
