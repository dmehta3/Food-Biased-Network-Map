all: main

main: main.o directed_graph.o cuisine.o friendships.o userNodes.o heap.o restaurant.o
	g++ main.o directed_graph.o cuisine.o friendships.o userNodes.o heap.o restaurant.o -o main -g3

main.o: main.cpp 
	g++ -c main.cpp -g3

directed_graph.o: directed_graph.cpp directed_graph.h
	g++ -c directed_graph.cpp -g3

cuisine.o: cuisine.cpp cuisine.h
	g++ -c cuisine.cpp -g3

friendships.o: friendships.cpp friendships.h
	g++ -c friendships.cpp -g3 

userNodes.o: userNodes.cpp userNodes.h
	g++ -c userNodes.cpp -g3 

heap.o: heap.cpp heap.h
	g++ -c heap.cpp -g3

restaurant.o: restaurant.cpp restaurant.h
	g++ -c restaurant.cpp -g3

clean:
	rm -f *.o main