#include <iostream>
#include <fstream>
#include <vector>

#include "cnf.h"
#include "solver.h"
#include "sudoku.h"

const int size_grid = 9;

bool fillGrid(std::ifstream &stream, std::vector<std::vector<int>> &grid) {
  for (int row = 0; row < size_grid; ++row) {
    for (int column = 0; column < size_grid; ++column) {
      stream >> grid[row][column];
      if (grid[row][column] < 0 || size_grid < grid[row][column]) {
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Need to point an input file!" << std::endl;
    return 0;
  }

  std::ifstream sudokuInput(argv[1]);
  if (!sudokuInput) {
    std::cout << "Counldn't open the file!" << std::endl;
    return 0;
  }

  std::vector<std::vector<int>> grid(size_grid, std::vector<int>(size_grid));
  if (!fillGrid(sudokuInput, grid)) {
    std::cout << "Incorrect input!\n";
    return 0;
  }
  sudokuInput.close();

  _sudoku::Sudoku sudoku(size_grid, grid);
  std::vector<std::vector<int>> clauses;
  sudoku.getSudokuSatFormula(clauses);

  int amountLiterals = size_grid * size_grid * size_grid;
  sat_solver::CNF formula(amountLiterals, clauses);

  sat_solver::Solver solver(formula);
  std::vector<int> solution;
  if (solver.determineSatisfiability(solution)) {
    std::cout << "solution: " << std::endl;
    sudoku.satSolutionToSudokuSolution(solution);
    std::cout << sudoku;
  } else {
    std::cout << "this sudoku haven't a solution!" << std::endl;
  }
  return 0;
}
