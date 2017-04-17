# SudokuSolver
This project solve the sudoku puzzle. Input grid of sudoku is reduced to conjunctive normal form(cnf). This cnf is solved by DPLL algorithm for Boolean Satisfiability Problem. Then empty cells of the grid are filled using the solution for the cnf. At the end the grid is showed.

In order to assemble and run the project need to write "make" in terminal and then "./sudoku name of input file". In input file must contains grid of sudoku in next format: 


7 0 8   0 0 6   3 0 0
0 0 0   0 0 0   9 0 8
0 0 3   0 0 0   4 0 7

0 0 7   0 6 0   0 9 2
8 9 6   0 7 0   0 0 0
1 0 0   0 0 0   0 0 0

6 0 0   0 0 0   0 7 3
3 7 4   0 0 8   0 0 9
0 0 1   0 9 0   0 8 0

where zero denotes not filled cells.
