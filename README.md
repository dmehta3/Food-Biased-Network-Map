#Collaborators - Dhruv, Adam, Daksh

    Fabricate a C++ program that simulated user relationships and food preferences based on cuisines and restaurants
    Implement a directed graph, breadth first search, unordered map and a max heap to represent friend networks, 
    recommended restaurants, user cravings, and cuisine preferences
    Accept user requests to manipulate data structures and return visualizations of the data structures
    
    
    
    Brainstorm Notes:
        We could use vector, but we can't use make_heap(), we would need to implement that ourselves

        Ideas: 
            Using Directed Graph for friends, easiest implementation 
            Breadthfirst search is the right algorithm to use
                When you call eat, you call a cuisine and a distance, all the friends within the distance, the BFS goes that many times for the distance, return the first instance of 
                restaurant with a matching cuisine that is recommended by a friend
            Friends can have associated restaurants that they recommend 
            

            Crave or Eat, best data structure is max heap organized by cravings points 
                Everytime craving points are added, you should percolate up the node
                    Change where the hash map points as well (unordered_map)
                Whatever is the root is what you will eat, after eating, re-insert at bottom (value of 0 points)
            Two cuisines with the same craving points, either are fine
            Percolating can have a less than or less than or equal to as the condition
            Searching for a cuisine, use the hash map to know exactly where the cuisine is in the heap, reduce      search time
                Tell your hash map where you move something in the heap 
                    Add craving points and percolate up 
                    Move pointer in hash map 
                    ***Use hash map instead of pointers in the heap (makes it a lot more simple)
                        Make sure we do this^^^^^
            FIFO queue of nodes to put in order, breadthfirst search visits all the nodes that are connected in a specific order 
            Color to mark whether a nodes been visited or not

                    
                    


