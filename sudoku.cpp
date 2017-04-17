#include "sudoku.h"

namespace _sudoku {
void Sudoku::setLiterals(
    std::vector<std::vector<std::vector<int>>> &settedLiterals) {
  for (int row = 0; row < sizeGrid; ++row) {
    for (int column = 0; column < sizeGrid; ++column) {
      if (grid[row][column] != 0) {
        int value = grid[row][column];
        for (int it = 0; it < sizeGrid; ++it) {
          settedLiterals[row][column][it + 1] = 0;
          settedLiterals[it][column][value] = 0;
          settedLiterals[row][it][value] = 0;
          settedLiterals[(row / sizeBlock) * sizeBlock +
                         (it / sizeBlock)][(column / sizeBlock) * sizeBlock +
                                           (it % sizeBlock)][value] = 0;
        }
        settedLiterals[row][column][value] = 1;
      }
    }
  }
}

void Sudoku::addConstraintsOfCells(
    std::vector<std::vector<int>> &clauses,
    const std::vector<std::vector<std::vector<int>>> &settedLiterals) {
  for (int row = 0; row < sizeGrid; ++row) {
    for (int column = 0; column < sizeGrid; ++column) {
      std::vector<int> clause;
      int valueClause = -1;
      for (int value = 0; value < sizeGrid; ++value) {
        if (settedLiterals[row][column][value + 1] == 1) {
          valueClause = 1;
        } else if (settedLiterals[row][column][value + 1] == 0) {
          continue;
        }
        int literal = sizeGrid * sizeGrid * row + sizeGrid * column + value + 1;
        clause.push_back(literal);
      }
      if (valueClause != 1 && (int)clause.size() > 0) clauses.push_back(clause);

      for (int firstValue = 0; firstValue < sizeGrid; ++firstValue) {
        for (int secondValue = firstValue + 1; secondValue < sizeGrid;
             ++secondValue) {
          if (settedLiterals[row][column][firstValue + 1] != 0 &&
              settedLiterals[row][column][secondValue + 1] != 0) {
            int firstLiteral =
                sizeGrid * sizeGrid * row + sizeGrid * column + firstValue + 1;
            int secondLiteral =
                sizeGrid * sizeGrid * row + sizeGrid * column + secondValue + 1;
            clauses.push_back({-firstLiteral, -secondLiteral});
          }
        }
      }
    }
  }
}

void Sudoku::addConstraintsOfRows(
    std::vector<std::vector<int>> &clauses,
    const std::vector<std::vector<std::vector<int>>> &settedLiterals) {
  for (int row = 0; row < sizeGrid; ++row) {
    for (int value = 0; value < sizeGrid; ++value) {
      std::vector<int> clause;
      int valueClause = -1;
      for (int column = 0; column < sizeGrid; ++column) {
        if (settedLiterals[row][column][value + 1] == 1) {
          valueClause = 1;
        } else if (settedLiterals[row][column][value + 1] == 0) {
          continue;
        }
        int literal = sizeGrid * sizeGrid * row + sizeGrid * column + value + 1;
        clause.push_back(literal);
      }
      if (valueClause != 1 && (int)clause.size() > 0) clauses.push_back(clause);

      for (int leftColumn = 0; leftColumn < sizeGrid; ++leftColumn) {
        for (int rightColumn = leftColumn + 1; rightColumn < sizeGrid;
             ++rightColumn) {
          if (settedLiterals[row][leftColumn][value + 1] != 0 &&
              settedLiterals[row][rightColumn][value + 1] != 0) {
            int firstLiteral =
                sizeGrid * sizeGrid * row + sizeGrid * leftColumn + value + 1;
            int secondLiteral =
                sizeGrid * sizeGrid * row + sizeGrid * rightColumn + value + 1;
            clauses.push_back({-firstLiteral, -secondLiteral});
          }
        }
      }
    }
  }
}

void Sudoku::addConstraintsOfColumns(
    std::vector<std::vector<int>> &clauses,
    const std::vector<std::vector<std::vector<int>>> &settedLiterals) {
  for (int column = 0; column < sizeGrid; ++column) {
    for (int value = 0; value < sizeGrid; ++value) {
      std::vector<int> clause;
      int valueClause = -1;
      for (int row = 0; row < sizeGrid; ++row) {
        if (settedLiterals[row][column][value + 1] == 1) {
          valueClause = 1;
        } else if (settedLiterals[row][column][value + 1] == 0) {
          continue;
        }
        int literal = sizeGrid * sizeGrid * row + sizeGrid * column + value + 1;
        clause.push_back(literal);
      }
      if (valueClause != 1 && (int)clause.size() > 0) clauses.push_back(clause);

      for (int upperRow = 0; upperRow < sizeGrid; ++upperRow) {
        for (int downRow = upperRow + 1; downRow < sizeGrid; ++downRow) {
          if (settedLiterals[upperRow][column][value + 1] != 0 &&
              settedLiterals[downRow][column][value + 1] != 0) {
            int firstLiteral =
                sizeGrid * sizeGrid * upperRow + sizeGrid * column + value + 1;
            int secondLiteral =
                sizeGrid * sizeGrid * downRow + sizeGrid * column + value + 1;
            clauses.push_back({-firstLiteral, -secondLiteral});
          }
        }
      }
    }
  }
}

void Sudoku::addConstraintsOfBlocks(
    std::vector<std::vector<int>> &clauses,
    const std::vector<std::vector<std::vector<int>>> &settedLiterals) {
  for (int block = 0; block < sizeGrid; ++block) {
    for (int value = 0; value < sizeGrid; ++value) {
      std::vector<int> clause;
      int valueClause = -1;
      for (int cell = 0; cell < sizeGrid; ++cell) {
        int row = (block / sizeBlock) * sizeBlock + cell / sizeBlock;
        int column = (block % sizeBlock) * sizeBlock + cell % sizeBlock;
        if (settedLiterals[row][column][value + 1] == 1) {
          valueClause = 1;
        } else if (settedLiterals[row][column][value + 1] == 0) {
          continue;
        }
        int literal = sizeGrid * sizeGrid * row + sizeGrid * column + value + 1;
        clause.push_back(literal);
      }
      if (valueClause != 1 && (int)clause.size() > 0) clauses.push_back(clause);

      for (int firstCell = 0; firstCell < sizeGrid; ++firstCell) {
        for (int secondCell = firstCell + 1; secondCell < sizeGrid;
             ++secondCell) {
          int firstRow =
              (block / sizeBlock) * sizeBlock + firstCell / sizeBlock;
          int firstColumn =
              (block % sizeBlock) * sizeBlock + firstCell % sizeBlock;

          int secondRow =
              (block / sizeBlock) * sizeBlock + secondCell / sizeBlock;
          int secondColumn =
              (block % sizeBlock) * sizeBlock + secondCell % sizeBlock;

          if (settedLiterals[firstRow][firstColumn][value + 1] != 0 &&
              settedLiterals[secondRow][secondColumn][value + 1] != 0) {
            int firstLiteral = sizeGrid * sizeGrid * firstRow +
                               sizeGrid * firstColumn + value + 1;
            int secondLiteral = sizeGrid * sizeGrid * secondRow +
                                sizeGrid * secondColumn + value + 1;
            clauses.push_back({-firstLiteral, -secondLiteral});
          }
        }
      }
    }
  }
}

void Sudoku::getSudokuSatFormula(std::vector<std::vector<int>> &clauses) {
  std::vector<std::vector<std::vector<int>>> settedLiterals(
      sizeGrid, std::vector<std::vector<int>>(
                    sizeGrid, std::vector<int>(sizeGrid + 1, -1)));

  setLiterals(settedLiterals);

  addConstraintsOfCells(clauses, settedLiterals);

  addConstraintsOfRows(clauses, settedLiterals);

  addConstraintsOfColumns(clauses, settedLiterals);

  addConstraintsOfBlocks(clauses, settedLiterals);
}

void Sudoku::satSolutionToSudokuSolution(const std::vector<int> &solution) {
  for (int literal = 0; literal < solution.size(); ++literal) {
    if (solution[literal] > 0) {
      int value = literal % sizeGrid + 1;
      int row = literal / (sizeGrid * sizeGrid);
      int column = (literal - sizeGrid * sizeGrid * row) / sizeGrid;
      if (grid[row][column] == 0) grid[row][column] = value;
    }
  }
}

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku) {
  for (int row = 0; row < sudoku.sizeGrid; ++row) {
    if (row % sudoku.sizeBlock == 0) {
      stream << "\n";
    }
    for (int column = 0; column < sudoku.sizeGrid; ++column) {
      if (column % sudoku.sizeBlock == 0) {
        stream << "  ";
      }
      stream << sudoku.grid[row][column] << " ";
    }
    stream << "\n";
  }
  stream << "\n";
}
}

