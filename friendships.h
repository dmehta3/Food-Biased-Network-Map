#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include "stdlib.h"
#include "userNodes.h"
using namespace std;

class friendships {
    public:
        friendships();
	    friendships(userNodes &user, userNodes &friendOfUser);
        friendships(const friendships &otherEdge);
        ~friendships();
        friendships operator=(const friendships &otherEdge);

        userNodes *user1;
        userNodes *user2;
};

#endif