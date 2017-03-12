CC=CC
CFLAG=-g

all: assign2

main.o: main.cpp main.h
	$(CC) $(CFLAG) -c main.cpp

graph.o: graph.cpp graph.h
	$(CC) $(CFLAG) -c graph.cpp

assign2: main.o graph.o
	$(CC) $(CFLAG) main.o graph.o -o assign2

run: all
	./assign2

valgrind: allvalgrind --leak-check=yes assign2

clean:
	rm -f *.o assign2

core:
	rm core*