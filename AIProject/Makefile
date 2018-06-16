demo: graph.o main.o
	g++ -o demo graph.o main.o
graph.o: graph.cpp graph.h
	g++ -c graph.h graph.cpp
main.o: main.cpp
	g++ -c main.cpp
clear:
	rm *.o *.h.gch demo