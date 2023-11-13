#ifndef cuisine_H
#define cuisine_H
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class cuisine {
    private:
        string name;
        int cravePoints;

    public:
        cuisine();
        cuisine(string x);
        string getName();
        int getPoints();
        void addPoints(int x);
};

#endif