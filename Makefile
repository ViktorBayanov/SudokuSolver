CC=g++
CFLAGS=-std=c++14 -c

all: sudoku

sudoku: main.o cnf.o solver.o sudoku.o
	$(CC) main.o cnf.o solver.o sudoku.o -o sudoku


main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

cnf.o: cnf.cpp
	$(CC) $(CFLAGS) cnf.cpp

solver.o: solver.cpp
	$(CC) $(CFLAGS) solver.cpp

sudoku.o: sudoku.cpp
	$(CC) $(CFLAGS) sudoku.cpp

clean:
	rm -rf *.o sudoku
