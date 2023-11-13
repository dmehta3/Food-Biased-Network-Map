#ifndef heap_H
#define heap_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "cuisine.h"

using namespace std;

class maxHeap{
    private:
    int num_elements;
    vector<cuisine> pointsVector;
    int parent(int i) {
        return (i-1)/2;
    };
    int left(int i) {
        return (i*2)+1;
    };
    int right(int i) {
        return (i*2)+2;
    };


    public:
    maxHeap();
    string getMax(); //return the object
    string extractMax(); //return the object
    void insert(cuisine* food);
    void percolateUp(int x);
    void percolateDown(int x); //
    int getSize();
    void addPointsHeap(string cuisineName, int additionalPoints);
    bool checkHeap(string cuisineName);
    int getIndex(string cuisineName);
    string printHeap();
    //string to feed to the graph to look for the restaurant
    //


};

#endif