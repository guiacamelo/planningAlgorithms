#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPoint>
#include <QMouseEvent>
#include "gridmap.h"
#include "graph.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void generateGridAndNodes(GRID & gridMap);
    void generateAndDrawObstacles(GRID & grid);
    void randomPositionAndSize(int& posX,int& posY,int& rand_sizeX,int& rand_sizeY);
    void markAsObstacleOnGrid(GRID & grid, int posX,int posY, int sizeX, int sizeY);
    void printObstacleGridToFile(GRID & grid);
    void plotObstacles(GRID & grid);
    void paintMouseClickPos(int posX,int posY,int originOrGoal);
    void printGridIdToFile(GRID & grid);
    void plotVectorNode(int x,int y);

    void plotSamples(vector<int> sampleIds,vector<int> sampleIdsX,vector<int> sampleIdsY);
    void getDisconectedNeighborsInRadius(int x,int y,UnionFind *unionFind,Graph & graph);
    bool colisionCheckBresenham(int const sx,int const sy,int rx,int ry);
    int signer(int n);
    void plotEdge(int originX,int originY,int destX,int destY);
    vector<int> dijkstra(Graph graph, int s, int t);
    void printPath(vector<int> parent, int j);
    vector<int> pathDijkstra;
    void plotFinalPath(int x, int y);
    void plotInterconection(int x, int y);
    bool allInSameSet(int o,int d);

signals:

public slots:
    void mousePressEvent(QMouseEvent * e);



private slots:
    void on_btnGenerateMap_clicked();
    void on_btnPlanPath_clicked();

private:

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QBrush grayBrush;
    QPen grayPen;
    GridMap gridMap;
    bool originSet;
    bool goalSet;
    vector<int> interconectionsX;
    vector<int> interconectionsY;

};

#endif // MAINWINDOW_H
