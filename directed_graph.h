#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "stdlib.h"
#include <vector>
#include "userNodes.h"
#include "friendships.h"
#include "heap.h"
#include <unordered_map>
#include "cuisine.h"
using namespace std;

class directed_graph {
    public:
        directed_graph();
        ~directed_graph();
        bool addVertex(string name);
        userNodes* findVertex(string name);
        bool checkVertex(string name);
        bool addEdge(userNodes &user1, userNodes &user2);
        bool removeEdge(userNodes &user1, userNodes &user2);
        string BFS(userNodes* start, int distance, string cuisine);

        vector<userNodes*> vertices;
        vector<friendships*> edges;
        //maxHeap *cuisinePoints = new maxHeap();
        //unordered_map<int, cuisine> umap;
};

#endif