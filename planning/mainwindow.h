#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "gridmap.h"
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

private slots:
    void on_btnGenerateMap_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QBrush grayBrush;
    QPen grayPen;

};

#endif // MAINWINDOW_H
