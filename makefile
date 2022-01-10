CC = gcc
AR = ar
FLAGS = -Wall -g 
OBJECTS = main.o pq.o algo.o edges.o

all: graph
graph: $(OBJECTS) 
	$(CC) $(FLAGS) -o graph $(OBJECTS)
main.o: main.c algo.h 
	$(CC) $(FLAGS) -c main.c
pq.o: pq.c pq.h 
	$(CC) $(FLAGS) -c pq.c
algo.o: algo.c algo.h pq.h
	$(CC) $(FLAGS) -c algo.c
edges.o: edges.c edges.h algo.h
	$(CC) $(FLAGS) -c edges.c
.PHONY: all clean
clean:
