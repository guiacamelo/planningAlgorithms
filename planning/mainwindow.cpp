#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridmap.h"
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <math.h>
using namespace std;
#include<iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <unionfind.h>

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
    bool originSet=false;
    bool goalSet=false;
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::mousePressEvent(QMouseEvent * e){

    if(!ui->graphicsView->isEnabled())
        return;
    if (originSet&&goalSet){
        ui->lblTopMessage->setText("Origin and Goal Points already set");
        return;
    }

    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

    //POSITION ON THE GRID CLICKED
    int posXCliked=floor(relativeOrigin.x()/QT_CELL_SIZE);
    int posYCliked=floor(relativeOrigin.y()/QT_CELL_SIZE);

    //protect from clicks out of the grid
    if(posXCliked<0||posYCliked<0)
        return;

    //protect from clicks out of the grid
    if(posXCliked>gridMap.grid.size()-1||posYCliked>gridMap.grid.size()-1)
        return;

    // check is position is free
    if (gridMap.grid[posXCliked][posYCliked].obstacle){
        ui->lblTopMessage->setText("Not a free cell, Click on a free space");
    }else{

        if (!originSet){
            paintMouseClickPos(posXCliked,posYCliked,ORIGIN);
            ui->lblTopMessage->setText("Origin Point Set");
            originSet=true;
            //Save origin on gridMap Obect
            gridMap.setOrigin(posXCliked,posYCliked);

        }else if (!goalSet){
            if(gridMap.originX==posXCliked&&gridMap.originY==posYCliked){
                ui->lblTopMessage->setText("This is the origin point choose other goal.");
                return;
            }
            paintMouseClickPos(posXCliked,posYCliked,GOAL);
            ui->lblTopMessage->setText("Goal Point Set");
            goalSet=true;
            //Save goal on gridMap Obect
            gridMap.setGoal(posXCliked,posYCliked);
            ui->btnPlanPath->setEnabled(true);
        }else{
            ui->lblTopMessage->setText("Origin and Goal Points already set");
        }
    }
}

void MainWindow::paintMouseClickPos(int posX,int posY,int originOrGoal){
    if (originOrGoal == ORIGIN)
        scene->addRect(posX*QT_CELL_SIZE,posY*QT_CELL_SIZE,QT_CELL_SIZE,QT_CELL_SIZE,QPen(Qt::magenta),QBrush(Qt::magenta));
    if (originOrGoal == GOAL)
        scene->addRect(posX*QT_CELL_SIZE,posY*QT_CELL_SIZE,QT_CELL_SIZE,QT_CELL_SIZE,QPen(Qt::red),QBrush(Qt::red));
}

void MainWindow::on_btnGenerateMap_clicked()
{
    ui->btnPlanPath->setEnabled(false);
    ui->graphicsView->setEnabled(true);
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




    GRID newGrid (GRID_SIZE,std::vector <GRID_CELL>(GRID_SIZE));
    gridMap.grid= newGrid;
    scene->clear();

    originSet=false;
    goalSet=false;

    generateGridAndNodes(gridMap.grid);
    generateAndDrawObstacles(gridMap.grid);
    printObstacleGridToFile(gridMap.grid);
    printGridIdToFile(gridMap.grid);
    plotObstacles(gridMap.grid);
}


void MainWindow::generateGridAndNodes(GRID & grid){
    int contId=0;
    int i;
    for (i = 0; i < grid.size(); ++i) {
        // Create the grid
        scene->addLine(i*QT_CELL_SIZE,0,i*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE);
        scene->addLine(0,i*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE,i*QT_CELL_SIZE);
        for (int j=0; j < grid.size(); ++j) {

            grid[i][j].distance=-1;
            grid[i][j].id=contId;
            grid[i][j].isVertex=false;
            contId++;

            // this will be deleted
            NODE newNode;
            newNode.id=contId;
            newNode.distance=-1;
            newNode.posX=i*QT_CELL_SIZE;
            newNode.posY=j*QT_CELL_SIZE;



            // this will be deleted
            grid[i][j].localNode = newNode;


        }
    }
    scene->addLine((i)*QT_CELL_SIZE,0,(i)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE);
    scene->addLine(0,(i)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE,(i)*QT_CELL_SIZE);

    //    scene->addLine((i+1)*QT_CELL_SIZE,0,(i+1)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE);
    //    scene->addLine(0,(i+1)*QT_CELL_SIZE,GRID_SIZE*QT_CELL_SIZE,(i+1)*QT_CELL_SIZE);
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
    for (int i = 0; i < grid.size(); ++i) {
        for (int j=0; j < grid.size(); ++j) {
            if(grid[i][j].obstacle)
                outputFile << "O";
            else
                outputFile << "_";

        }
        outputFile << endl;
    }
}

void MainWindow::printGridIdToFile(GRID & grid){
    ofstream outputFile;
    outputFile.open("IdGrid.txt");
    for (int i = 0; i < grid.size(); ++i) {
        for (int j=0; j < grid.size(); ++j) {
            outputFile << grid[i][j].id<<" ";
        }
        outputFile << endl;
    }
}

void MainWindow::plotObstacles(GRID & grid){
    for (int i = 0; i < grid.size(); ++i) {
        for (int j=0; j < grid.size(); ++j) {
            if(grid[i][j].obstacle)
                scene->addRect(i*QT_CELL_SIZE +QT_CELL_SIZE/4 ,
                               j*QT_CELL_SIZE +QT_CELL_SIZE/4 ,
                               QT_CELL_SIZE -QT_CELL_SIZE/2.0,
                               QT_CELL_SIZE -QT_CELL_SIZE/2.0,
                               QPen(Qt::blue),QBrush((Qt::blue)));

        }
    }
}

void MainWindow::plotEdge(int originX,int originY,int destX,int destY){
    scene->addLine(originX*QT_CELL_SIZE+QT_CELL_SIZE/2.0 - QT_CELL_SIZE/3.0/2.0,
                   originY*QT_CELL_SIZE+QT_CELL_SIZE/2.0 - QT_CELL_SIZE/3.0/2.0,
                   destX*QT_CELL_SIZE+QT_CELL_SIZE/2.0 - QT_CELL_SIZE/3.0/2.0,
                   destY*QT_CELL_SIZE+QT_CELL_SIZE/2.0 - QT_CELL_SIZE/3.0/2.0,
                   QPen(Qt::green));
    //QPen(Qt::lightGray));
}

void MainWindow::plotVectorNode(int x,int y){
    scene->addRect(x*QT_CELL_SIZE+QT_CELL_SIZE/2.0 - QT_CELL_SIZE/3.0/2.0,
                   y*QT_CELL_SIZE+QT_CELL_SIZE/2.0 - QT_CELL_SIZE/3.0/2.0,
                   QT_CELL_SIZE/3.0,
                   QT_CELL_SIZE/3.0,
                   QPen(Qt::green),QBrush((Qt::green)));
}

void MainWindow::plotSamples(vector<int> sampleIds,vector<int> sampleIdsX,vector<int> sampleIdsY)
{
    for (int i = 0; i < sampleIds.size(); ++i) {
        int posX = sampleIdsX[i];
        int posY = sampleIdsY[i];
        plotVectorNode(posX,posY);
    }
}

void MainWindow::on_btnPlanPath_clicked()
{


    ui->lblTopMessage->setText("Planning the Path!");
    Graph graph;

    graph.setGoal(gridMap.goalX,gridMap.goalY);

    graph.setOrigin(gridMap.originX,gridMap.originY);


    graph.buildRoadMapSamples(gridMap.grid,gridMap.originX,gridMap.originY,gridMap.goalX,gridMap.goalY);
    plotSamples(graph.sampleIds,graph.sampleIdsX,graph.sampleIdsY);

    //create unionFind
    UnionFind *unionFind = new UnionFind(MAX_NUMBER_OF_NODES);

    //Create copnnections between samples
    int connection=0;
    for (int i = 0; i < graph.sampleIds.size(); ++i) {
        getDisconectedNeighborsInRadius(graph.sampleIdsX[i],graph.sampleIdsY[i], unionFind,graph);
    }
    if (unionFind->isSameSet(gridMap.grid[gridMap.originX][gridMap.originY].id,gridMap.grid[gridMap.goalX][gridMap.goalY].id) )
        cout<<" Yes\n"<<endl;
    else
        cout<<" No\n"<<endl;

    cout<<unionFind->findSet(gridMap.grid[gridMap.originX][gridMap.originY].id)<< " "<<endl;
    cout<<unionFind->findSet(gridMap.grid[gridMap.goalX][gridMap.goalY].id)<< " "<<endl;

    graph.print();
}


void MainWindow::getDisconectedNeighborsInRadius(int x,int y,UnionFind  *unionFind,Graph & graph){
    int sampleId= gridMap.grid[x][y].id;
    int xLowerSweepLimit = x - RADIUS_K; xLowerSweepLimit<=0 ? xLowerSweepLimit =0 : true;
    int yLowerSweepLimit = y - RADIUS_K; yLowerSweepLimit<=0 ? yLowerSweepLimit =0 : true;

    int xUpperSweepLimit = x + RADIUS_K; xUpperSweepLimit>GRID_SIZE-1? xUpperSweepLimit =GRID_SIZE-1 : true;
    int yUpperSweepLimit = y + RADIUS_K; yUpperSweepLimit>GRID_SIZE-1? yUpperSweepLimit =GRID_SIZE-1 : true;
    for (int i = xLowerSweepLimit; i < xUpperSweepLimit; ++i) {
        for (int j = yLowerSweepLimit; j < yUpperSweepLimit; ++j) {
            // Check if there is a sample,
            if(gridMap.grid[i][j].isVertex){
                // Means it is a vertex and is in a free space
                int neighborId = gridMap.grid[i][j].id;

                //check if they are in same graph
                if(unionFind->isSameSet(sampleId,neighborId))
                    continue;
                else{
                    //They are not in the same graph, só lets try a connection between them
                    if (!colisionCheckBresenham(x,y,i,j)){
                        // no colision between the two points, a connection can be made

                        //calculate de distance
                        int diffx=abs(x-i);
                        int diffy=abs(y-j);
                        int distance=sqrt((diffx*diffx)*(diffy*diffy));
                        graph.addEdge(sampleId,neighborId,distance);
                        unionFind->unionSet(sampleId,neighborId);
                        //Plotting all edges
                        plotEdge(x,y,i,j);

                        if (STOP_WHEN_PATH_FOUND){
                            if(unionFind->isSameSet(gridMap.grid[gridMap.originX][gridMap.originY].id
                                                    ,gridMap.grid[gridMap.goalX][gridMap.goalY].id))

                                return;

                        }


                    }
                }

            }
        }

    }
}

bool MainWindow::colisionCheckBresenham(int const sx,int const sy,int rx,int ry){
    if (std::min(rx, ry) >= 0 && std::max(rx, ry) < GRID_SIZE) {
        if (gridMap.grid[rx][ry].obstacle)
            return true;
    }

    // Bresenham Algorithm
    double dx = rx - sx;
    double dy = ry - sy;

    if (dx == 0) {
        for (int ty = std::min(ry, sy), tx = sx; ty <= std::max(ry, sy); ty++) {
            if ((tx != rx || ty != ry) /*&& std::min(tx, ty) >= 0 && std::max(tx, ty) < GRID_SIZE*/) {
                if (gridMap.grid[tx][ty].obstacle)
                    return true;
            }
        }
    } else if (dy == 0) {
        for (int tx = std::min(rx, sx), ty = sy; tx <= std::max(rx, sx); tx++) {
            if ((tx != rx || ty != ry) /*&& std::min(tx, ty) >= 0 && std::max(tx, ty) < GRID_SIZE*/) {
                if (gridMap.grid[tx][ty].obstacle)
                    return true;
            }
        }
    } else {
        int tx = sx;
        int ty = sy;

        int dx = abs(rx - sx);
        int dy = abs(ry - sy);

        int vx = signer(rx - sx);
        int vy = signer(ry - sy);

        int swap = 0;
        if (dy > dx) {
            int temp = dx;
            dx = dy;
            dy = temp;
            swap = 1;
        }

        int D = 2*dy - dx;

        for (int i = 0; i < dx; i++) {
            if ((tx != rx || ty != ry) /*&& std::min(tx, ty) >= 0 && std::max(tx, ty) < GRID_SIZE*/) {
                if (gridMap.grid[tx][ty].obstacle)
                    return true;

            }

            while (D >= 0) {
                D = D - 2*dx;

                if (swap)
                    tx += vx;
                else
                    ty += vy;
            }

            D = D + 2*dy;

            if (swap)
                ty += vy;
            else
                tx += vx;
        }
    }
    if (gridMap.grid[rx][ry].obstacle)
        return true;
    else
        return false;

}

int MainWindow::signer(int n){
    if (n>0) return 1;
    if (n<0) return -1;
    else return 0;
}

/*
vector<int> MainWindow::dijkstra(Graph graph, int s, int t)
{
    return vector<int> v;

    Heap q(7);
    int deletemin=0, incert=0, update=0;
    Vertex v(0,0), u(0,0);
    ListAdj *n;
    ListAdj::iterator it;
    vector<int> dist(graph.graphSize() + 1);
    vector<bool> visited(graph.graphSize() + 1);
    int i;
    double iterations = 0;
    for(i = 1; i < (int)dist.size(); i++){
        if(i != s){
            dist[i] = -1;
        } else dist[i] = 0;
    }
    for(i = 1; i < (int)visited.size(); i++){
        visited[i] = false;
    }

    q.insertIntoHeap(s, 0);
    iterations += q.heapUpQty+q.heapDownQty;

    while(!q.isEmpty())
    {
      //cout << "Visiting a vertex. Heap size is " << q.heap.size() << endl;
        v = q.deleteMin();deletemin++;
        //cout << "Removed the vertex. Heap size now is " << q.heap.size() << endl;
        iterations += q.heapUpQty+q.heapDownQty;

        if(v.getId() == t) break;
        visited[v.getId()] = true;
        //cout << "Before getNeighbourhood " << endl;
        //cout << "Visiting vertex " << v.getId() << endl;

        n = graph.getNeighbourhood(v.getId());
        //cout << "There are " << n->size() << " neighbors." << endl;

        //cout << "After getNeighbourhood "<<n << endl;
        for(it = n->begin(); it != n->end(); it++){
          //cout << "Iterate getNeighbourhood" << endl;

            u = (*it);
            if(!visited[u.getId()]){
                if(dist[u.getId()] == -1){
                    dist[u.getId()] = dist[v.getId()] + u.getDistance();
                    q.insertIntoHeap(u.getId(), dist[u.getId()]);incert++;
                    iterations += q.heapUpQty+q.heapDownQty;

                }
                else {
                    int aux = dist[u.getId()];
                    if ((dist[v.getId()] + u.getDistance()) > dist[u.getId()]){
                        dist[u.getId()] =	dist[u.getId()];
                    }else{
                        dist[u.getId()] =   (dist[v.getId()] + u.getDistance());
                    }




                    q.updateVertex(Vertex(u.getId(), aux), dist[u.getId()]);update++;
                    iterations += q.heapUpQty+q.heapDownQty;

                }
            }
        }
    }
    output <<" "<< iterations  <<" " <<deletemin <<" "<< incert<< " "<< update;
    //cout << "After Djikstra" << endl;
    return dist;
}
    */


