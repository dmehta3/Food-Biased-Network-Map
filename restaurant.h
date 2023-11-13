#ifndef REST_H
#define REST_H
#include <iostream>
#include "stdlib.h"
#include <vector>
#include <string>

using namespace std;

class restaurant {
    public:
        restaurant(string restName, string cname);
        restaurant operator=(const restaurant &otherR);
        string getName();
        string getCuisine();

        string name;
        string cuisine;
};

#endif