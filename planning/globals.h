#ifndef GLOBALS_H
#define GLOBALS_H
#include "globals.h"
#include <vector>
#include<math.h>
#define QT_CELL_SIZE 8
#define GRID_SIZE 100
//#define GRID_SIZE 5
//#define GRID_SIZE 10
#define SQUARES 25
#define RECTANGLES 25

//#define SQUARES 1
//#define RECTANGLES 2
#define PLOT_GRID false
#define PLOT_EDGES true
#define PLOT_PATH true

#define MAX_OBJECT_PROPORTION 0.1

#define ORIGIN 0
#define GOAL 1
#define NEAREST_K 15
#define NEAR 5
#define RADIUS_K 5

#define SAMPLEPERCENTAGE 0.14
#define SAMPLES round(double(GRID_SIZE*GRID_SIZE*SAMPLEPERCENTAGE))
#define MAX_NUMBER_OF_NODES GRID_SIZE*GRID_SIZE
#define STOP_WHEN_PATH_FOUND false
// this will be deleted
typedef struct {
    int id;
    int distance;
    int posX;
    int posY;
} NODE;

typedef struct {
    bool obstacle;
    double distance;
    int id;
    bool isVertex;
    NODE localNode; // this will be deleted
} GRID_CELL;

typedef std::vector<std::vector<GRID_CELL>> GRID;

#endif // GLOBALS_H


