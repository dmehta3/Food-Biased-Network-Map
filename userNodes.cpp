#include <iostream>
#include "stdlib.h"
#include "userNodes.h"
#include "restaurant.h"
#include "heap.h"
#include <vector>
using namespace std;

 

userNodes::userNodes(){
    name = "";
    cuisinePoints = new maxHeap();
}

userNodes::userNodes(string userName) {
    name = userName;
    cuisinePoints = new maxHeap();
}

userNodes::userNodes(const userNodes &otherNode) {
    name = otherNode.name;
    cuisinePoints = otherNode.cuisinePoints;
}

userNodes::~userNodes() {
    name = "";
    delete cuisinePoints;
}

/*userNodes userNodes::operator=(const userNodes &otherNode) {
    name = otherNode.name;
    cuisinePoints = otherNode.cuisinePoints;
}*/

bool userNodes::compare(string uname) {     //lets you compare userNodes to an input name
    if (name == uname) {
        return true;
    }
    return false;
}


//adds restaurants recommended by friend, should make it easier for BFS
bool userNodes::addRec(restaurant &rec) {
    restaurant* tmp = &rec;

    string flag = searchRecs(tmp->name, tmp->cuisine);

    if (flag != "false") {
        return false;
    }
    else {
        recommendations.push_back(tmp);   //use restauarnt class instead of string
        return true;
    }
}

int getIndex(vector<restaurant*> r, string name) {
   for(int i = 0; i < r.size(); i++) {
        if(r.at(i)->name == name) {
            return i;
        }          
    }
    return (int) NULL;
}

bool userNodes::removeRec(restaurant &rec) {
    restaurant *temp = &rec;
    string flag = searchRecs(temp->name, temp->cuisine);

    if (flag != "false") {
        int k = getIndex(recommendations, temp->name);
        cout << name << " unrecommended " << recommendations.at(k)->name << endl;
        recommendations.erase(recommendations.begin()+k);
        return true;
    }
    else {
        cout << "Didn't work " << endl;
        return false;
    }
}

void userNodes::printRecList() {
    for (int i = 0; i < recommendations.size(); ++i) {
        cout << recommendations.at(i)->name << endl;
    }
}

//will make it easier to search each friend for recommended restaurants
string userNodes::searchRecs(string rname, string cname) {    //use restauarnt class instead of string, return restaurant instead
    for (int i = 0; i < recommendations.size(); ++i) {
        if((recommendations.at(i)->cuisine == cname)) {
            return recommendations.at(i)->name;
        }
    }

    return "false";
}



bool userNodes::addFriend(userNodes &user2) {
    userNodes* tmp = &user2;
    friends.push_back(tmp);
    return true;
    
    // friendships *newRelationship = new friendships(user1, user2);
    // edges.push_back(newRelationship);       //might need to resize for similar reasons
}

bool userNodes::removeFriend(userNodes &user2) {
    userNodes* tmp = &user2;
    
    for (int i = 0; i < friends.size(); ++i) {
        if (tmp == friends.at(i)) {
            friends.erase(friends.begin()+i);   // i?
            return true;
        }
    }

    return false;
}

void userNodes::printFList() {
    for (int i = 0; i < friends.size(); ++i) {
        cout << friends.at(i)->name << endl;
    }
}

string userNodes::getName() {
    return this->name;
}

    