#include <iostream>
#include "stdlib.h"
#include "restaurant.h"
#include <string>
using namespace std;

restaurant::restaurant(string restName, string cname) {
    name = restName; 
    cuisine = cname;
}

string restaurant::getName() {
    return this->name;
}

string restaurant::getCuisine() {
    return this->cuisine;
}



