#include <iostream>
#include "stdlib.h"
#include "userNodes.h"
#include "friendships.h"
using namespace std;

friendships::friendships() {

}

friendships::friendships(userNodes &user, userNodes &friendOfUser) {
    user1 = &user;
    user2 = &friendOfUser;
}

friendships::friendships(const friendships &otherEdge) {
    user1 = otherEdge.user1;
    user2 = otherEdge.user2;
}

friendships::~friendships() {
    user1 = nullptr;
    user2 = nullptr;
}

friendships friendships::operator=(const friendships &otherEdge) {
    user1 = otherEdge.user1;
    user2 = otherEdge.user2;
    return otherEdge;
}


