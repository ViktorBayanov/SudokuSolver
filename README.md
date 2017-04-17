# SudokuSolver
This project solves sudoku puzzles. Input grid of sudoku is reduced to conjunctive normal form (CNF). This CNF is solved by DPLL algorithm for Boolean Satisfiability Problem. Then empty cells of the grid are filled using the solution of the CNF. At the end the grid is shown.

In order to link and run the project You need to write "make" in terminal and then "./sudoku input_file", where input_file is the name of file containing a sudoku puzzle. Input file must contain grid of sudoku in the following format: 


7 0 8     0 0 6     3 0 0 

0 0 0     0 0 0    9 0 8

0 0 3     0 0 0      4 0 7

0 0 7   0 6 0   0 9 2

8 9 6   0 7 0   0 0 0

1 0 0   0 0 0   0 0 0

6 0 0   0 0 0   0 7 3

3 7 4   0 0 8   0 0 9

0 0 1   0 9 0   0 8 0

where zero denotes not filled cells. The file "sudoku.txt" contains examples of sudoku. It can also be used as input file.
