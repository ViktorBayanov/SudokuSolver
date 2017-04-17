#pragma once
#include <vector>

#include "cnf.h"

namespace sat_solver {
class Solver {
  CNF formula;

  bool solveSat(std::vector<int> &settedLiterals, std::vector<int> &solution);

  int unitPropagation();

  int pureLiteralElimination();

  void DPLLStep(std::vector<int> &settedLiterals, int &amountChange);

  void removeDPLLStep(std::vector<int> &settedLiterals, int &amountChange);

 public:
  Solver() = delete;

  Solver(const CNF &f) : formula(f) {}

  bool determineSatisfiability(std::vector<int> &solution);
};
}
