all: graph

graph: main.o graph.o
	gcc main.o graph.o -Wall -g -o graph

main.o: main.c graph.h
	gcc -Wall -g -c main.c graph.h

graph.o: graph.c 
	gcc -Wall -g -c graph.c 


clean:
	rm -f *.o graph