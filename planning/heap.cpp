// Purpose:   Create a d-ary heap
// Author:    Guilherme Antonio Camelo

#include "heap.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;





    //Print Heap
void Heap::printHeap (){
    //cout << "Begin of heap\n" << endl;
    for (int i=0; i<heap.size();i++){
        cout << "ID "<< heap[i].getId() <<" Distance "<< heap[i].getDistance() << endl;
    }
    //cout << "End of heap\n" << endl;

}

void Heap::printVector (std::vector<int> vector){
    for (int i=0; i<vector.size();i++){
        cout << vector[i] << endl;
    }
}

void Heap::updateVertex(Vertex v,int dist)
{
    Vertex new_v(v.getId(), dist);
    updateHeap(new_v,pos[v.getId()]);
}
void Heap::updateHeap(Vertex v,int toBeUpdatedIndex)
{
    heapUpQty = 0;
    heapDownQty = 0;
    if(heap[toBeUpdatedIndex].getDistance() > v.getDistance())
    {
        heap[toBeUpdatedIndex]= v;
        siftUp(toBeUpdatedIndex);
    }
    else{
        heap[toBeUpdatedIndex]= v;
        siftDown(toBeUpdatedIndex);
    }


}

// void Heap::updateHeap(int toBeUpdatedIndex,int value)
// {
// 	if(value<heap[toBeUpdatedIndex]){
// 		heap[toBeUpdatedIndex]= value;
// 		siftUp(toBeUpdatedIndex);
// 	}
// 	if(value>heap[toBeUpdatedIndex]){
// 		heap[toBeUpdatedIndex]= value;
// 		siftDown(toBeUpdatedIndex);
// 	}

// }
void Heap::swap(int nodeA,int nodeB)
{
    pos[heap[nodeA].getId()] = nodeB;
    pos[heap[nodeB].getId()] = nodeA;
    Vertex OldNodeA(0,0);
    OldNodeA = heap[nodeA];
    heap[nodeA] = heap[nodeB];
    heap[nodeB] = OldNodeA;
}

void Heap::insertIntoHeap(int n , int dist)
{
    Vertex v(n,dist);
    //cout << "Inser into heap id "<<v.getId()<<"  dist "<<v.getDistance() << endl;
    insertIntoHeap(v);
}
void Heap::insertIntoHeap(Vertex v)
{
//cout << "Inser into heap vertex " << endl;
    currentSize++;
    heapUpQty = 0;
    heapDownQty = 0;
    size_t insertedIndex =heap.size();
    heap.push_back(v);

    if(v.getId()+1 > (int)pos.size()){
        for(int i = pos.size(); i <= v.getId(); i++){
            pos.push_back(0);
        }
    }
    pos[v.getId()] = currentSize-1;

    siftUp(currentSize-1);
      //printHeap();
}


void Heap::siftUp(int nodeIndex)
{
    heapUpQty++;
    if (nodeIndex!=0) // not root
    {
        int parentIndex = getParentIndex(nodeIndex);
        //cout << "Node index "<< nodeIndex << "     Parent Index:"<< parentIndex  << endl;
        if (heap[parentIndex].getDistance()> heap[nodeIndex].getDistance())
        {
          //cout << "Parent greater then child" << endl;
            swap(parentIndex,nodeIndex);
            siftUp(parentIndex);
            //cout << "Sifting" << endl;
        }
    } else {
        //cout << "Element is the root, no need to move" << endl;
    }
}

Vertex Heap::deleteMin()
{
    Vertex v = heap[0];
    deleteFromHeap(0);
    return v;
}

void Heap::deleteFromHeap(int toBeRemovedIndex)
{

    // heap[toBeRemovedIndex]= heap[heap.size()-1];
    // heap.pop_back();
    //currentSize--;
    // siftDown(toBeRemovedIndex);
        // printHeap();
    currentSize--;heapUpQty=0; heapDownQty =0;
    swap(toBeRemovedIndex, currentSize);
    heap.pop_back();
    siftDown(toBeRemovedIndex);
}
void Heap::siftDown(int nodeIndex)
{
    heapDownQty++;
    if (hasChild(nodeIndex)){
        if(getChildQnt(nodeIndex)==1){
            //cout << "Element "<< nodeIndex << "has one child" << endl;

            int child = getChildIndexes(nodeIndex).back();
            if (heap[child].getDistance()<heap[nodeIndex].getDistance()){
                swap(child,nodeIndex);
                siftDown(child);
            }
        }
        else{ // swap with the lower child
            //cout << "Element "<< nodeIndex << "has more then one child" << 	endl;

            std::vector<int> childList = getChildIndexes(nodeIndex);
            //printVector(childList);

            int lowerChild = getLowerChild(childList);
            //cout << "lowerChild "<< lowerChild << "value  "<< heap[lowerChild].getDistance() << 	endl;

            if (heap[lowerChild].getDistance()<heap[nodeIndex].getDistance()){
                swap(lowerChild,nodeIndex);
                siftDown(lowerChild);
            }
        }

    }
    else {
        //cout << "Element is the leaf, no need to move" << endl;
    }

}
int Heap::getLowerChild(std::vector<int> childList){
    int lowerValue = heap[childList[0]].getDistance();
    int lowerIndex = childList[0];
    for (int i=0; i<childList.size();i++){
        if (lowerValue>heap[childList[i]].getDistance()){
            lowerValue=heap[childList[i]].getDistance();
            lowerIndex=childList[i];
        }

    }
    return lowerIndex;
}

bool Heap::hasChild(int nodeIndex)
{
    if (getChildIndexes(nodeIndex).size()==0)
        return false;
    else
        return true;
}

int Heap::getChildQnt(int nodeIndex)
{
    return getChildIndexes(nodeIndex).size();
}




int Heap::getParentIndex(int i)
{
    float aux = i-1.0;
    float float_d = (float) d ;
    float parentIndex = aux / ((float) d);
      //cout << "BEGIN GET PARENT INDEX FUNCTION" << endl;
      //cout << "         aux "<< aux << "     float_d :"<< d<< "     parentIndex :"<< parentIndex  << endl;

      //cout << "END GET PARENT INDEX FUNCTION" << endl;

    int parentIndexInt = (int) parentIndex ;
    return parentIndexInt;
}

std::vector<int> Heap::getChildIndexes(int parent)
{
    std::vector<int> childs_indexes;
    for (int i=0;i<d;i++) {
        int child = parent*d + i +1;
        if (child<currentSize)
            childs_indexes.push_back(child);
    }
    return childs_indexes;
}


int heapTest()
{
    Heap binaryHeap(2); //heap binario
    //Heap ternaryHeap(3); //heap binario
    //Heap quadHeap(4); //heap binario
    //Heap fithHeap(5); //heap binario
//    binaryHeap.printHeap();
    binaryHeap.insertIntoHeap(10,5);
    binaryHeap.insertIntoHeap(1,9);
    binaryHeap.insertIntoHeap(2,2);
    binaryHeap.insertIntoHeap(3,2);
    binaryHeap.insertIntoHeap(4,9);
    binaryHeap.insertIntoHeap(5,1);
    binaryHeap.insertIntoHeap(6,9);
    binaryHeap.insertIntoHeap(7,8);
//	binaryHeap.printHeap();

    // firstHeap.printVector(firstHeap.getChildIndexes(0));
    // firstHeap.printVector(firstHeap.getChildIndexes(1));
    // firstHeap.printVector(firstHeap.getChildIndexes(2));
    // firstHeap.printVector(firstHeap.getChildIndexes(3));
    // firstHeap.printVector(firstHeap.getChildIndexes(4));
    // firstHeap.printVector(firstHeap.getChildIndexes(5));
    // Heap secondHeap(4); // heap ternario
    // secondHeap.insertIntoHeap(7);
    // secondHeap.insertIntoHeap(11);
    // secondHeap.insertIntoHeap(1);
    // secondHeap.insertIntoHeap(10);
    // secondHeap.insertIntoHeap(4);
    // secondHeap.insertIntoHeap(6);
    // secondHeap.insertIntoHeap(8);
    // secondHeap.insertIntoHeap(2);
    // secondHeap.insertIntoHeap(5);
    // secondHeap.insertIntoHeap(12);
    // secondHeap.insertIntoHeap(9);
    // secondHeap.insertIntoHeap(3);
    // secondHeap.insertIntoHeap(3);
    // secondHeap.insertIntoHeap(5);
    // secondHeap.insertIntoHeap(38);
    // secondHeap.insertIntoHeap(11);
    // secondHeap.insertIntoHeap(37);
    // secondHeap.insertIntoHeap(50);
    // secondHeap.insertIntoHeap(41);
    // secondHeap.insertIntoHeap(23);
    // secondHeap.printHeap();

    // create array of child
    //int heapArray[firstHeap.getQtdChild()];
    //heapArray[0] = firstHeap.getQtdChild();
    //cout << heapArray[0] << endl;
    return 1;
}

// int getLowerChild(std::vector<int> childList){
// 		int lower = heap[childList[0]];
// 		for (int i=0; i<childList.size();i++){
// 			if (lower>heap[childList[i]])
// 				lower=childList[i];
// 		}
// 		return lower;
// 	}
