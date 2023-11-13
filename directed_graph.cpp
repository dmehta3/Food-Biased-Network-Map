#include <iostream>
#include "stdlib.h"
#include "string.h"
#include <vector>
#include "userNodes.h"
#include "friendships.h"
#include "directed_graph.h"
#include <unordered_map>
#include "heap.h"
#include "cuisine.h"
#include <queue>
#include <unordered_set>
using namespace std;

directed_graph::directed_graph() {

}

directed_graph::~directed_graph() {
    vertices.clear();
    edges.clear();
}

bool directed_graph::addVertex(string name) {
    for (int i = 0; i < vertices.size(); ++i) {
        if(vertices.at(i)->name == name) {
            return false; //if vertex is already here, then returns false
        }
    }

    userNodes *newUser = new userNodes(name);
    vertices.push_back(newUser);    //might need to resize, need testing
    return true;
}

bool directed_graph::checkVertex(string name) {
    for (int i = 0; i < vertices.size(); ++i) {
        if(vertices.at(i)->name == name) {
            return true;    //returns true if vertex exists
        }
    }

    return false;
}

userNodes* directed_graph::findVertex(string name) {
    for (int i = 0; i < vertices.size(); ++i) {
        if(vertices.at(i)->name == name) {
            return vertices.at(i); 
        }
    }
    return (userNodes*)false;
}

bool directed_graph::addEdge(userNodes &user1, userNodes &user2) {
    for (int i = 0; i < edges.size(); ++i) {
        if((edges.at(i)->user1 == &user1) && (edges.at(i)->user2 == &user2)) {
            return false; //if edge is already here, then returns false
        }
    }
    
    friendships *newRelationship = new friendships(user1, user2);
    edges.push_back(newRelationship);       //might need to resize for similar reasons
    return true;
}  

bool directed_graph::removeEdge(userNodes &user1, userNodes &user2) {
    for (int i = 0; i < edges.size(); ++i) {
        if((edges.at(i)->user1 == &user1) && (edges.at(i)->user2 == &user2)) {
            delete edges.at(i); //delete the friendship itself
            edges.erase(edges.begin()+(i-1)); //remove friendship from vector of edges
            return true; //returns true, if edge can be found and removed
        }
    }

    return false; //edge could not be found, relationship doesn't exist
}

string directed_graph::BFS(userNodes* start, int distance, string cuisine) { //can take cuisine object or string, whatever is easiest to pass in main
    queue<userNodes*> frontierQueue;
    unordered_set<userNodes*> discoveredSet;
    userNodes *curr;
    //userNodes *curr;

    //node is user
    //edges are friends - adjacency list
    //as we visit we should be putting their friends into a queue

    //we dont wanna count the same friend - thats why we use the set
    //to store ppl already

    frontierQueue.push(findVertex(start));
    discoveredSet.insert(findVertex(start));

    while (frontierQueue.size() != 0) {
        curr = frontierQueue.front();
        frontierQueue.pop();
        //curr = frontierQueue.front();
        //do a not empty check on the queue
        userNodes* curr = frontierQueue.front();
        unordered_set<userNodes*>::const_iterator got2 = discoveredSet.find(curr);
        if(got2 == discoveredSet.end()) {
            discoveredSet.insert(curr); //add the user
        }

       // curr->visit_status = true;
        for(int j = 0; j<curr->recommendations.size(); j++) {
            if(curr->recommendations[j]->getCuisine() == cuisine) {
                return curr->recommendations[j]->getName();
            }
        }

        for(int i = 0; i < curr->friends.size(); i++) {
            unordered_set<userNodes*>::const_iterator got = discoveredSet.find(curr->friends[i]);
            if(got == discoveredSet.end()) {
                cout << "User Not Added" << endl;
                break;
            } else {
            discoveredSet.insert(curr->friends[i]); //add the users friend if it is not added already
            frontierQueue.push(curr->friends[i]); 
            frontierQueue.pop(); //pop the front user
            }
        }
        delete curr;
    }
   /*
    queue<userNodes*> frontierQueue;
    unordered_set<userNodes*> discoveredSet;
    userNodes *curr;
    int iterations = distance;
    //userNodes *curr;

    //node is user
    //edges are friends - adjacency list
    //as we visit we should be putting their friends into a queue

    //we dont wanna count the same friend - thats why we use the set
    //to store ppl already

    frontierQueue.push(findVertex(start));
    discoveredSet.insert(findVertex(start));

    while ((frontierQueue.size() != 0) && (iterations != 0)) {
        curr = frontierQueue.front();
        frontierQueue.pop();
        //curr = frontierQueue.front();
        //do a not empty check on the queue
        userNodes* curr = frontierQueue.front();
        unordered_set<userNodes*>::const_iterator got2 = discoveredSet.find(curr);
        if(got2 == discoveredSet.end()) {
            discoveredSet.insert(curr); //add the user
        }

       // curr->visit_status = true;
        for(int j = 0; j<curr->recommendations.size(); j++) {
            if(curr->recommendations[j]->getCuisine() == cuisine) {
                return curr->recommendations[j]->getName();
            }
        }

        for(int i = 0; i < curr->friends.size(); i++) {
            unordered_set<userNodes*>::const_iterator got = discoveredSet.find(curr->friends[i]);
            if(got == discoveredSet.end()) {
                cout << "User Not Added" << endl;
                break;
            } else {
            discoveredSet.insert(curr->friends[i]); //add the users friend if it is not added already
            frontierQueue.push(curr->friends[i]); 
            frontierQueue.pop(); //pop the front user
            }
        }
        delete curr;
    }

    queue<userNodes*> frontierQueue;
    unordered_set<userNodes*> discoveredSet;
    int iterations = distance;
    //userNodes *curr;

    //node is user
    //edges are friends - adjacency list
    //as we visit we should be putting their friends into a queue
    
    //we dont wanna count the same friend - thats why we use the set
    //to store ppl already

    frontierQueue.push(start);
    discoveredSet.insert(start);

    while ((frontierQueue.size() != 0) && (iterations != 0)) {
        //curr = frontierQueue.front();
        //do a not empty check on the queue
        userNodes* curr = frontierQueue.front();
        frontierQueue.pop();       //deque from the frontierqueue
        unordered_set<userNodes*>::const_iterator got2 = discoveredSet.find(curr);
        if(got2 == discoveredSet.end()) {
            discoveredSet.insert(curr); //add the user
        }

        for(int j = 0; j < curr->recommendations.size(); j++) {
            if(curr->recommendations.at(j)->cuisine == cuisine) {
                return curr->recommendations.at(j)->name;
            }
        }   

        for(int i = 0; i < curr->friends.size(); i++) {
            unordered_set<userNodes*>::const_iterator got = discoveredSet.find(curr->friends.at(i));
            if(got != discoveredSet.end()) {
                cout << "User Added" << endl;
                break;
            } 
            else {
                discoveredSet.insert(curr->friends.at(i)); //add the users friend if it is not added already
                frontierQueue.push(curr->friends.at(i)); 
                frontierQueue.pop(); 
                /*
                for(int j = 0; j < curr->friends.at(i)->recommendations.size(); j++) {
                    if(curr->friends.at(i)->recommendations.at(j)->cuisine == cuisine) {
                        return curr->friends.at(i)->recommendations.at(j)->name;
                    }
                }  
                
            }
        }
        iterations--;
        // delete curr;
    }


    return "false";
}
*/
    /*Zybooks pseudocode
    BFS(startV) {
        Enqueue startV in frontierQueue
        Add startV to discoveredSet

        while ( frontierQueue is not empty && distance <friendship distance ) {
            currentV = Dequeue from frontierQueue
            "Visit" currentV
            for each vertex adjV adjacent to currentV {
                if ( adjV is not in discoveredSet ) {
                    Enqueue adjV in frontierQueue
                    Add adjV to discoveredSet
                    check if recommendations match cusine 
                }
            }
        }
    }
    */
}
