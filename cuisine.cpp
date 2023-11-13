#include "cuisine.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

    cuisine::cuisine() {
        name = " ";
        cravePoints = 0;
    }

    cuisine::cuisine(string x) {
        name = x;
        cravePoints = 0;
    }

    string cuisine::getName() {
        return this->name;
    }

    int cuisine::getPoints() {
        return this->cravePoints;
    }

    void cuisine::addPoints(int x) {
        this->cravePoints = this->cravePoints + x;
    }

