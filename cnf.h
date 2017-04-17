#pragma once
#include <iostream>
#include <vector>

namespace sat_solver {

enum boolValue { isFalse, isTrue, undefined };

struct literalInfo {
  boolValue value = undefined;
  size_t counterPositiveClauses = 0;
  size_t counterNegativeClauses = 0;
  std::vector<int> clauses;
};

struct clauseInfo {
  boolValue value = undefined;
  int counterPositiveLiterals = 0;
  std::vector<int> literals;
};

class CNF {
  size_t amountLiterals;
  size_t amountClauses;

  std::vector<clauseInfo> clauses;
  std::vector<literalInfo> literals;

  void makeClauseUndef(int numberClause);

  void insertLiteralToClause(int numberLiteral, int numberClause,
                             boolValue value, boolValue inClause);

  void makeClauseTrue(int numberClause);

  void deleteLiteralFromClause(int numberLiteral, int numberClause,
                               boolValue value);

  void addClause(const clauseInfo &nextClause);

 public:
  int positiveClauses;
  CNF() = delete;

  CNF(size_t amLit, std::vector<std::vector<int>> &inputClauses);

  CNF(const CNF &formula);

  void resetLiteral(int numberLiteral);

  bool setLiteral(int numberLiteral, boolValue value);

  int findUnitClause(boolValue &value);

  int findPureLiteral(boolValue &value);

  int selectLiteral();

  bool checkClauses(std::vector<int> &solution);
};
}
