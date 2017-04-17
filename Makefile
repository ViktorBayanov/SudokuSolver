CC=g++
CFLAGS=-std=c++14 -c

all: sudoku

sudoku: SatSolver.o cnf.o solver.o sudoku.o
	$(CC) SatSolver.o cnf.o solver.o sudoku.o -o sudoku


SatSolver.o: SatSolver.cpp
	$(CC) $(CFLAGS) SatSolver.cpp

cnf.o: cnf.cpp
	$(CC) $(CFLAGS) cnf.cpp

solver.o: solver.cpp
	$(CC) $(CFLAGS) solver.cpp

sudoku.o: sudoku.cpp
	$(CC) $(CFLAGS) sudoku.cpp

clean:
	rm -rf *.o sudoku
