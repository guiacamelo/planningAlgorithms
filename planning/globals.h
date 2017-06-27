#ifndef GLOBALS_H
#define GLOBALS_H
#include "globals.h"
#include <vector>

#define QT_CELL_SIZE 8
#define GRID_SIZE 100
#define SQUARES 50
#define RECTANGLES 50
#define MAX_OBJECT_PROPORTION 0.1
#define ORIGIN 0
#define GOAL 1


typedef struct {
    int id;
    int distance;
    int posX;
    int posY;
} NODE;

typedef struct {
    bool obstacle;
    double distance;

    NODE localNode;
} GRID_CELL;

typedef std::vector<std::vector<GRID_CELL>> GRID;

#endif // GLOBALS_H


