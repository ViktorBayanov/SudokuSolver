#include "solver.h"
#include "cnf.h"

namespace sat_solver {

bool Solver::solveSat(std::vector<int> &settedLiterals,
                      std::vector<int> &solution) {
  int amountChange = 0;
  DPLLStep(settedLiterals, amountChange);

  int numberLiteral = formula.selectLiteral();
  if (numberLiteral < 0) {
    if (formula.checkClauses(solution)) {
      return true;
    }
  } else {
    if (formula.setLiteral(numberLiteral, isTrue)) {
      if (solveSat(settedLiterals, solution)) {
        return true;
      }
    }
    formula.resetLiteral(numberLiteral);

    if (formula.setLiteral(numberLiteral, isFalse)) {
      if (solveSat(settedLiterals, solution)) {
        return true;
      }
    }
    formula.resetLiteral(numberLiteral);
  }

  removeDPLLStep(settedLiterals, amountChange);
  return false;
}

int Solver::unitPropagation() {
  boolValue value;
  int number = formula.findUnitClause(value);
  if (number >= 0) {
    formula.setLiteral(number, value);
  }
  return number;
};

int Solver::pureLiteralElimination() {
  boolValue value;
  int number = formula.findPureLiteral(value);
  if (number >= 0) {
    formula.setLiteral(number, value);
  }
  return number;
};

void Solver::DPLLStep(std::vector<int> &settedLiterals, int &amountChange) {
  bool flag = true;
  while (flag) {
    flag = false;

    int number = unitPropagation();
    if (number >= 0) {
      flag = true;
      ++amountChange;
      settedLiterals.push_back(number);
    }

    number = pureLiteralElimination();
    if (number >= 0) {
      flag = true;
      ++amountChange;
      settedLiterals.push_back(number);
    }
  }
}

void Solver::removeDPLLStep(std::vector<int> &settedLiterals,
                            int &amountChange) {
  while (amountChange--) {
    int number = settedLiterals.back();
    settedLiterals.pop_back();
    formula.resetLiteral(number);
  }
}

bool Solver::determineSatisfiability(std::vector<int> &solution) {
  std::vector<int> settedLiterals;
  return solveSat(settedLiterals, solution);
}
}
