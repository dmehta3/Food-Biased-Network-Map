#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "heap.h"
#include "cuisine.h"
#include <unordered_map>
#include "directed_graph.h"
#include "algorithm"
#include "restaurant.h"

using namespace std;

bool contains(vector<cuisine> x, string name) {
    for(int i = 0; i < x.size(); i++) {
        if(x[i].getName() == name) {
            return true;
        }          
    }
    return false;
}

bool checkDuplicateRestuarants(vector<restaurant*> r, string name) {
   for(int i = 0; i < r.size(); i++) {
        if(r.at(i)->name == name) {
            return true;
        }          
    }
    return false;
}

void printRest(vector<restaurant*> r) {
   for(int i = 0; i < r.size(); i++) {
        cout << r.at(i)->name << endl;
    }
}

restaurant* findRest(vector<restaurant*> r, string name) {
   for(int i = 0; i < r.size(); i++) {
        if(r.at(i)->name == name) {
            return r.at(i);
        }          
    }
    return (restaurant* )NULL;
}

int main(int argc, char *argv[]) {
    vector<cuisine> cuisineList;
    vector<restaurant*> restaurantList;
    string menuOption = "";
    directed_graph *network = new directed_graph();


    //maxHeap *cuisinePoints = new maxHeap();
    unordered_map<string, userNodes> umap;

    while(true) {
        string choice;
        string fullLine;
        cout << " " << endl;
        cout << "Enter a command. Choose from" << endl;
        cout << "   CREATE <username>" << endl;
        cout << "   FRIEND <username1> <username2>" << endl;
        cout << "   UNFRIEND <username1> <username2>" << endl;
        cout << "   ADD <restaurant-name> <cuisine>" << endl;
        cout << "   REC <username> <restaurant-name>" << endl;
        cout << "   UNREC <username> <restaurant-name>" << endl;
        cout << "   CRAVE <username> <cuisine> <points>" << endl;
        cout << "   EAT <username> <friendship-distance>" << endl;
        cout << "   QUIT" << endl;
        cout << ":> ";

       getline(cin, fullLine);
       choice = fullLine.substr(0, fullLine.find(" "));
       transform(choice.begin(), choice.end(), choice.begin(), ::toupper);


        if(choice == "CREATE") {
            istringstream objectISS(fullLine);
            string choice;
            string username;
            objectISS >> choice >> username;
            userNodes *user = new userNodes(username);
            umap[username] = *user; 
            bool temp = network->addVertex(username);


            if (temp) {
                cout << "Successfully added user" << endl;
            }
            else {
                cout << "Error: User already exists" << endl;
            }

       } else if (choice == "FRIEND") {
            istringstream objectISS(fullLine);
            string choice;
            string username1;
            string username2;
            objectISS >> choice >> username1 >> username2;

                bool output1 = network->checkVertex(username1);
                bool output2 = network->checkVertex(username2);

                if (output1 && output2) {

                    userNodes *temp1 = network->findVertex(username1);
                    userNodes *temp2 = network->findVertex(username2);
                    bool temp3 = network->addEdge(*temp1, *temp2);

                    if (temp3) {
                        cout << username1 << " is now a friend with " << username2 << endl;
                    }
                    else {
                        cout << "Error: Friendship already existed" << endl;
                    }

                }
                else {
                    cout << "Error: One or two of the users does not exist" << endl;
                }

       } else if (choice == "UNFRIEND") {
            istringstream objectISS(fullLine);
            string choice;
            string username1;
            string username2;
            objectISS >> choice >> username1 >> username2;

            bool temp1 = network->checkVertex(username1);
            bool temp2 = network->checkVertex(username2);

            if (temp1 && temp2) {
                userNodes *temp1 = network->findVertex(username1);
                userNodes *temp2 = network->findVertex(username2);
                bool temp3 = network->removeEdge(*temp1, *temp2);
                
                //COMPILER ERROR BELOW IN COMMENTED AREA WITH BRACKETS ? 
                //DHRUV TAKE A LOOK
                if (temp3) {
                    cout << username1 << " Is no longer friends with " << username2 << endl;
                } else {
                    cout << "Error: Friendship did not exist" << endl;
                }
            }

       } else if(choice == "ADD") {
            istringstream objectISS(fullLine);
            string choice;
            string restaurantName;
            string cuisine1;
            objectISS >> choice >> restaurantName >> cuisine1;
            
            if (!checkDuplicateRestuarants(restaurantList, restaurantName)) {
                restaurant *rest = new restaurant(restaurantName, cuisine1);
                restaurantList.push_back(rest);
                //printRest(restaurantList);
            }
            else {
                cout << "Error: " << restaurantName << " already added" << endl;
            }

            if(contains(cuisineList, cuisine1)) {
                cout << "The restaurant: " << restaurantName << " has been successfully added" << endl;
            } 
            else {
                cuisine *food = new cuisine(cuisine1);
                cuisineList.push_back(cuisine1);
                cout << "The restaurant: " << restaurantName << " and the cuisine: " << cuisine1 << " has been successfully added" << endl;
            }

        } 
        else if (choice == "REC") {
            istringstream objectISS(fullLine);
            string choice;
            string username;
            string restaurantName;
            objectISS >> choice >> username >> restaurantName;

            
            userNodes *temp = network->findVertex(username);
            restaurant *retTemp = findRest(restaurantList, restaurantName);
            temp->addRec(*retTemp);
            cout << username << " recommended " << restaurantName << endl;
           // temp->printRecList();

       } 
       else if (choice == "UNREC") {
            istringstream objectISS(fullLine);
            string choice;
            string username;
            string restaurantName;
            objectISS >> choice >> username >> restaurantName;

            userNodes *temp = network->findVertex(username);
            restaurant *retTemp = findRest(restaurantList, restaurantName);
            temp->removeRec(*retTemp);
            //temp->printRecList();

       }
       else if(choice == "CRAVE") {
            istringstream objectISS(fullLine);
            string choice; 
            string username;
            string cuisine1;
            string points;
            objectISS >> choice >> username >> cuisine1 >> points;
            int point = stoi(points);
            if(contains(cuisineList, cuisine1)) { //if the cuisine exists
                 unordered_map<string, userNodes>::iterator check;
                /*if(check == umap.end()) {
                    cout << "This cuisine could not be craved, the user does not exist " << endl;
                    break;
                } else {*/
                    if(umap.at(username).cuisinePoints->checkHeap(cuisine1)) { //check the hashMaps User via key "username" then checks the users heap
                        //if it exists, we add crave points rather then add a new node
                        // cout << username << "Before the crave: " << endl;
                        // cout << umap[username].cuisinePoints->printHeap() << endl;
                        int index = umap.at(username).cuisinePoints->getIndex(cuisine1); 
                        umap.at(username).cuisinePoints->addPointsHeap(cuisine1, point); //if position in the max heap changes, it also changes in the map - must handle this!!!
                        cout << "ADDED " << point << " point's";
                        // cout << username <<"After the crave: " << endl;
                        // cout << umap[username].cuisinePoints->printHeap() << endl;
                        // cout << "GETTING MAX " << endl;
                        // cout << umap[username].cuisinePoints->getMax()<<endl;
                    } else {
                    cuisine *food = new cuisine(cuisine1);
                    //  cout << username << "Before the crave: " << endl;
                    // cout << umap[username].cuisinePoints->printHeap() << endl;
                    food->addPoints(point);
                    umap.at(username).cuisinePoints->insert(food);
                        cout << "ADDED " << point << " point's and created a new node" << endl;
                        // cout << "The cuisine name is " << food->getName() << endl;

                        // cout << username <<"After the crave: " << endl;
                        // cout << umap[username].cuisinePoints->printHeap() << endl;

                        // cout << "GETTING MAX " << endl;
                        // cout << umap[username].cuisinePoints->getMax()<<endl;
                    }
                //}
            } else {
                cout << "This cuisine does not exist, it cannot be craved" << endl;
            }

       } else if(choice == "EAT") {
         
            istringstream objectISS(fullLine);
            string choice;
            string username;
            string friendshipDistance;
            objectISS >> choice >> username >> friendshipDistance;
            int k = stoi(friendshipDistance);
            string cname = umap[username].cuisinePoints->extractMax();
            string rname = network->BFS(network->findVertex(username), k, cname);

            if (rname != "false") {
                cout << username << "'s friends recommend " << rname << " for " << cname << endl;
            }
            else
            {
                cout << "None of " << username << "'s friends recommend restauants for " << cname << endl;
            }
       } 
       else if (choice == "QUIT") {
            menuOption = "QUIT"; //QUIT
            break;
       } 
    }

    /*cout << umap[ok].cuisinePoints->printHeap() << endl;
    cout << "The map value is: " << umap[ok].name << endl;
    cout << "The max value gotten is :" << umap[ok].cuisinePoints->getMax() << endl;
    cout << "The max value extracred is :" << umap[ok].cuisinePoints->extractMax() << endl;
    cout << "The max value gotten2 is :" << umap[ok].cuisinePoints->getMax() << endl;
    cout << "HEAP" << endl;
    cout << umap[ok].cuisinePoints->printHeap() << endl;*/

   
    
}