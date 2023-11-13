#include "heap.h"
#include "cuisine.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

    maxHeap::maxHeap() {
        num_elements = 1;
        //cuisine *temp = new cuisine("null");
       // pointsVector.push_back(*temp); 
        //pointsVector[0].addPoints(10000000);
    }

    string maxHeap::getMax() { //returns the cuisine
        return pointsVector[0].getName();
    }

    void maxHeap::percolateUp(int x) {
        if(x < pointsVector[x].getPoints() && pointsVector[parent(x)].getPoints() < pointsVector[x].getPoints()) {
            swap(pointsVector[x], pointsVector[parent(x)]);

            percolateUp(parent(x));        
        }
    }

    void maxHeap::percolateDown(int x) {
        int max = x;

        if(left(x) < getSize() && pointsVector[left(x)].getPoints() > pointsVector[x].getPoints()) {
            max = left(x);
        }

        if(right(x) < getSize() && pointsVector[right(x)].getPoints() > pointsVector[x].getPoints()) {
            max = right(x);
        }

        if(max != x) {
            swap(pointsVector[x], pointsVector[max]);
            percolateDown(max);
        }
    }

    void maxHeap::insert(cuisine *food) {
        //check if vector is full
        /*if(num_elements >= pointsVector.size()) {
            pointsVector.resize(pointsVector.size() + 1);
        }*/

        pointsVector.push_back(*food);
        int element = getSize()-1;
        percolateUp(element);
    }

    int maxHeap::getSize() {
        return pointsVector.size();

    }
    
    string maxHeap::extractMax() {
        cuisine point = pointsVector[0];
        pointsVector[0] = pointsVector.back();
        pointsVector.pop_back();

        percolateDown(0);

        return point.getName();
    }

    void maxHeap::addPointsHeap(string cuisineName, int additionalPoints) {
        //find the cuisine in the heap
        //use addPoints for that node
        for(int i = 0; i < pointsVector.size(); i++) {
            if(cuisineName == pointsVector[i].getName()) {
                pointsVector[i].addPoints(additionalPoints);
                percolateUp(i);
                break;
            }
        }
    }

    bool maxHeap::checkHeap(string cuisineName) {
        for(int i = 0; i < pointsVector.size(); i++) {
            if(cuisineName == pointsVector[i].getName()) {
                return true;
            }
        }

        return false;
    }

    int maxHeap::getIndex(string cuisineName) {
        for(int i = 0; i < pointsVector.size(); i++) {
            if(cuisineName == pointsVector[i].getName()) {
                return i;
            }
        }
        return -1;
    }

    string maxHeap::printHeap() {
        stringstream ss;
        for(int i = 0; i < pointsVector.size(); i++) {
            ss << "Name of cuisine: " << pointsVector[i].getName() << "Points:" <<pointsVector[i].getPoints() << endl;
        }
        string str = ss.str();
        return str;
    }


//to add points to an already added
//search the maxheap
//use cuisine function to increment crave
//then move it ot the right spot