#ifndef HEAP_H
#define HEAP_H


// Purpose:   Create a d-ary heap
// Author:    Guilherme Antonio Camelo

//#include <iostream>
#include "vertex.h"
#include <vector>
using namespace std;

// Class to represent Heap
class Heap
{
private:
  int d; // represents how many child each node can have d-ary heap
  std::vector<Vertex> heap;
  int currentSize;

  vector<int> pos;
public:
    Heap(int qtdChild = 1):d(qtdChild)
    {
        currentSize = 0;
        //cout << "Heap constructor called" << endl;
        currentSize = heap.size();
    }
    // Inline initialization


    //Print Heap
    void printHeap ();
    void printVector(std::vector<int> vector);

    void updateVertex(Vertex v,int dist);
    void updateHeap(Vertex v,int toBeUpdatedIndex);

    void insertIntoHeap(int n , int dist);
    void insertIntoHeap(Vertex v);

    void swap(int nodeA,int nodeB);

    void siftUp(int nodeIndex);

    Vertex deleteMin();
    void deleteFromHeap(int toBeRemovedIndex);
    void siftDown(int nodeIndex);
    int getLowerChild(std::vector<int> childList);

    bool hasChild(int nodeIndex);
    int getChildQnt(int nodeIndex);

    int getParentIndex(int i);
    std::vector<int> getChildIndexes(int parent);

    double heapUpQty, heapDownQty, FindQty;
    bool isEmpty(){
        return currentSize==0;
    }
};



#endif // HEAP_H
