#ifndef UNODE_H
#define UNODE_H
#include <iostream>
#include "stdlib.h"
#include <vector>
#include "heap.h"
#include "restaurant.h"
using namespace std;

class userNodes {
    public:
        userNodes();
	    userNodes(string userName);
        userNodes(const userNodes &otherNode);
        ~userNodes();
        //userNodes operator=(const userNodes &otherNode);
        bool addRec(restaurant &rec);
        bool removeRec(restaurant &rec);
        string searchRecs(string rname, string cname);
        void printRecList();
        bool addFriend(userNodes &user2);
        bool removeFriend(userNodes &user2);
        void printFList();
        bool compare(string uname);
        string getName();

        string name;
        vector<restaurant*> recommendations; //need a restaurant class, change to restaurant instead of string
        vector<userNodes*> friends;
        maxHeap *cuisinePoints;
        //color status for BFS
};

#endif