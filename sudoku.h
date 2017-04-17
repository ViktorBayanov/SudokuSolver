#pragma once
#include <iostream>
#include <vector>
#include <cmath>

namespace _sudoku {
class Sudoku {
  size_t sizeBlock;
  size_t sizeGrid;
  std::vector<std::vector<int>> grid;

  void setLiterals(std::vector<std::vector<std::vector<int>>>&);
  void addConstraintsOfCells(std::vector<std::vector<int>>&,
                             const std::vector<std::vector<std::vector<int>>>&);
  void addConstraintsOfRows(std::vector<std::vector<int>>&,
                            const std::vector<std::vector<std::vector<int>>>&);
  void addConstraintsOfColumns(
      std::vector<std::vector<int>>&,
      const std::vector<std::vector<std::vector<int>>>&);
  void addConstraintsOfBlocks(
      std::vector<std::vector<int>>&,
      const std::vector<std::vector<std::vector<int>>>&);

 public:
  Sudoku() = delete;

  Sudoku(size_t sizeInputGrid, const std::vector<std::vector<int>>& inputGrid)
      : sizeGrid(sizeInputGrid), grid(inputGrid) {
    sizeBlock = size_t(sqrt(sizeInputGrid));
  }

  void getSudokuSatFormula(std::vector<std::vector<int>>& clauses);

  void satSolutionToSudokuSolution(const std::vector<int>& solution);

  friend std::ostream& operator<<(std::ostream& stream, const Sudoku& sudoku);
};
}
