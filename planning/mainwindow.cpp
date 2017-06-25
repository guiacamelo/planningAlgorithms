#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridmap.h"
using namespace std;
#include<iostream>
#include <fstream>
#include <vector>
#include <time.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush grayBrush(Qt::gray);
    QPen grayPen(Qt::gray);

    time_t now;
    srand(time(&now));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerateMap_clicked()
{
    ui->lblTopMessage->setText("Generating Map");

    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    QPen outlinePen(Qt::black);

    QPen magentaPen(Qt::magenta);

    QBrush cyanBrush(Qt::cyan);
    outlinePen.setWidth(2);
    QPen coneGrayPen(Qt::darkGray);

    QBrush bBoxGrayPen(Qt::darkGreen);
    coneGrayPen.setWidth(2);


    gridMap gridMap;

    GRID newGrid (GRID_SIZE,std::vector <GRID_CELL>(GRID_SIZE));
    gridMap.grid= newGrid;
    scene->clear();
    generateGridAndNodes(gridMap.grid);
    generateAndDrawObstacles(gridMap.grid);
    printObstacleGridToFile(gridMap.grid);
    plotObstacles(gridMap.grid);
}


void MainWindow::generateGridAndNodes(GRID & grid){
    int contId=0;
    int i;
    for (i = 0; i < grid.size()-1; ++i) {
        // Create the grid
        scene->addLine(i*QT_CELL_SIZE,0,i*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE);
        scene->addLine(0,i*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE,i*QT_CELL_SIZE);
        for (int j=0; j < grid.size()-1; ++j) {
            NODE newNode;
            newNode.id=contId;
            newNode.distance=-1;
            newNode.posX=i*QT_CELL_SIZE;
            newNode.posY=j*QT_CELL_SIZE;
            grid[i][j].localNode = newNode;
            contId++;
        }
    }
    scene->addLine((i)*QT_CELL_SIZE,0,(i)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE);
    scene->addLine(0,(i)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE,(i)*QT_CELL_SIZE);
    scene->addLine((i+1)*QT_CELL_SIZE,0,(i+1)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE);
    scene->addLine(0,(i+1)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE,(i+1)*QT_CELL_SIZE);
}

void MainWindow::generateAndDrawObstacles(GRID & grid){
    int posX, posY, rand_sizeX,rand_sizeY;
    for (int i = 0; i < RECTANGLES; ++i) {

        // update values of posX,posY, rand_sizeX,rand_sizeY to a new random value
        randomPositionAndSize(posX,posY, rand_sizeX,rand_sizeY);

        //if size is smaller than 1 let it be 1;
        (rand_sizeX<1) ? rand_sizeX=1:NULL;
        (rand_sizeY<1) ? rand_sizeY=1:NULL;

        //Draw rectangle
        scene->addRect(posX*QT_CELL_SIZE,
                       posY*QT_CELL_SIZE,
                       rand_sizeX*QT_CELL_SIZE,
                       rand_sizeY*QT_CELL_SIZE,
                       QPen(Qt::cyan),QBrush((Qt::cyan)));

        // mark obstacles on the grid
        markAsObstacleOnGrid(grid,posX,posY,rand_sizeX,rand_sizeY);

    }

    for (int i = 0; i < SQUARES; ++i) {

        // update values of posX,posY, rand_sizeX,rand_sizeY to a new random value
        randomPositionAndSize(posX,posY, rand_sizeX,rand_sizeY);

        //if size is smaller than 1 let it be 1;
        (rand_sizeX<1) ? rand_sizeX=1:NULL;


        //Draw square use rand_sizeX for width and hight
        scene->addRect(posX*QT_CELL_SIZE,
                       posY*QT_CELL_SIZE,
                       rand_sizeX*QT_CELL_SIZE,
                       rand_sizeX*QT_CELL_SIZE,
                       QPen(Qt::cyan),QBrush((Qt::cyan)));

        // mark obstacles on the grid
        markAsObstacleOnGrid(grid,posX,posY,rand_sizeX,rand_sizeX);
    }


}

void MainWindow::markAsObstacleOnGrid(GRID & grid, int posX,int posY, int sizeX, int sizeY){
    for (int i = posX; i < posX+sizeX; ++i) {
        for (int j = posY; j < posY+sizeY; ++j) {
            grid[i][j].obstacle = true;
        }

    }
}

void MainWindow::randomPositionAndSize(int& posX,int& posY,int& rand_sizeX,int& rand_sizeY){
    // subtracting 20 and adding 10 will giv me a number between 2 an 98.
    posX=round(
                (rand()/(double)RAND_MAX)*
                ((double)GRID_SIZE-
                 2.0*MAX_OBJECT_PROPORTION*((double)GRID_SIZE)))
            +MAX_OBJECT_PROPORTION*((double)GRID_SIZE);

    // subtracting 20 and adding 10 will giv me a number between 10 an 90.
    posY=round(
                (rand()/(double)RAND_MAX)*
                ((double)GRID_SIZE-
                 2.0*MAX_OBJECT_PROPORTION*((double)GRID_SIZE)))
            +MAX_OBJECT_PROPORTION*((double)GRID_SIZE);

    //rand size will be the size of the object with a propotyion to the grid size
    rand_sizeX=round( (rand()/(double)RAND_MAX)*MAX_OBJECT_PROPORTION*(double)GRID_SIZE);

    rand_sizeY=round( (rand()/(double)RAND_MAX)*MAX_OBJECT_PROPORTION*(double)GRID_SIZE);

}
void MainWindow::printObstacleGridToFile(GRID & grid){
    ofstream outputFile;
    outputFile.open("obstacleGrid.txt");
    for (int i = 0; i < grid.size()-1; ++i) {
        for (int j=0; j < grid.size()-1; ++j) {
                if(grid[i][j].obstacle)
                    outputFile << "O";
                else
                    outputFile << "_";

            }
            outputFile << endl;
    }
}

void MainWindow::plotObstacles(GRID & grid){
    for (int i = 0; i < grid.size()-1; ++i) {
        for (int j=0; j < grid.size()-1; ++j) {
            if(grid[i][j].obstacle)
                scene->addRect(i*QT_CELL_SIZE +2 ,
                               j*QT_CELL_SIZE +2 ,
                               QT_CELL_SIZE -4,
                               QT_CELL_SIZE -4,
                               QPen(Qt::blue),QBrush((Qt::blue)));

        }
    }
}


