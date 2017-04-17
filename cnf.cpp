#include "cnf.h"

namespace sat_solver {

void CNF::makeClauseUndef(int clauseNumber) {
  for (auto currentLiteral = clauses[clauseNumber].literals.begin();
       currentLiteral != clauses[clauseNumber].literals.end();
       ++currentLiteral) {
    if (*currentLiteral > 0) {
      ++literals[std::abs(*currentLiteral) - 1].counterPositiveClauses;
    } else {
      ++literals[std::abs(*currentLiteral) - 1].counterNegativeClauses;
    }
  }
}

void CNF::insertLiteralToClause(int literalNumber, int clauseNumber,
                                boolValue value, boolValue inClause) {
  if (value == isTrue) {
    --clauses[clauseNumber].counterPositiveLiterals;
    if (clauses[clauseNumber].counterPositiveLiterals == 0) {
      clauses[clauseNumber].value = undefined;
      makeClauseUndef(clauseNumber);
      --positiveClauses;
    }
  }
  if (inClause == isTrue) {
    clauses[clauseNumber].literals.push_back(literalNumber + 1);
  } else {
    clauses[clauseNumber].literals.push_back(-literalNumber - 1);
  }
}

void CNF::makeClauseTrue(int clauseNumber) {
  for (auto currentLiteral = clauses[clauseNumber].literals.begin();
       currentLiteral != clauses[clauseNumber].literals.end();
       ++currentLiteral) {
    int index = std::abs(*currentLiteral) - 1;
    if (*currentLiteral > 0) {
      --literals[index].counterPositiveClauses;
    } else {
      --literals[index].counterNegativeClauses;
    }
  }
}

void CNF::deleteLiteralFromClause(int literalNumber, int clauseNumber,
                                  boolValue value) {
  for (auto currentLiteral = clauses[clauseNumber].literals.begin();
       currentLiteral != clauses[clauseNumber].literals.end();
       ++currentLiteral) {
    if (std::abs(*currentLiteral) == literalNumber + 1) {
      size_t sizeClause = clauses[clauseNumber].literals.size();
      *currentLiteral = clauses[clauseNumber].literals[sizeClause - 1];
      clauses[clauseNumber].literals.pop_back();
      break;
    }
  }

  if (value == isTrue) {
    ++clauses[clauseNumber].counterPositiveLiterals;
    if (clauses[clauseNumber].value == undefined) {
      ++positiveClauses;
      makeClauseTrue(clauseNumber);
    }
    clauses[clauseNumber].value = isTrue;
  }
}
void CNF::addClause(const clauseInfo &nextClause) {
  clauseInfo newClause;
  clauses.push_back(newClause);
  for (auto currentLiteral = nextClause.literals.begin();
       currentLiteral != nextClause.literals.end(); ++currentLiteral) {
    if (*currentLiteral > 0) {
      literals[*currentLiteral - 1].clauses.push_back(amountClauses + 1);
      ++literals[*currentLiteral - 1].counterPositiveClauses;
    } else {
      literals[std::abs(*currentLiteral) - 1].clauses.push_back(-amountClauses -
                                                                1);
      ++literals[std::abs(*currentLiteral) - 1].counterNegativeClauses;
    }
    clauses[amountClauses].literals.push_back(*currentLiteral);
  }
  ++amountClauses;
}

CNF::CNF(size_t amountInputLiterals,
         std::vector<std::vector<int>> &inputClauses)
    : amountLiterals(amountInputLiterals),
      amountClauses(0),
      literals(amountInputLiterals),
      positiveClauses(0) {
  for (int currentClauses = 0; currentClauses < inputClauses.size();
       ++currentClauses) {
    clauseInfo clause;
    for (int currentLiteral = 0;
         currentLiteral < inputClauses[currentClauses].size();
         ++currentLiteral) {
      clause.literals.push_back(inputClauses[currentClauses][currentLiteral]);
    }
    addClause(clause);
  }
}

CNF::CNF(const CNF &formula)
    : amountLiterals(formula.amountLiterals),
      amountClauses(formula.amountClauses),
      literals(formula.literals),
      clauses(formula.clauses),
      positiveClauses(formula.positiveClauses) {}

void CNF::resetLiteral(int literalNumber) {
  if (literals[literalNumber].value == isTrue) {
    for (auto currentClause = literals[literalNumber].clauses.begin();
         currentClause != literals[literalNumber].clauses.end();
         ++currentClause) {
      if (*currentClause > 0) {
        insertLiteralToClause(literalNumber, *currentClause - 1, isTrue,
                              isTrue);
      } else {
        insertLiteralToClause(literalNumber, std::abs(*currentClause) - 1,
                              undefined, isFalse);
      }
    }
  } else if (literals[literalNumber].value == isFalse) {
    for (auto currentClause = literals[literalNumber].clauses.begin();
         currentClause != literals[literalNumber].clauses.end();
         ++currentClause) {
      if (*currentClause < 0) {
        insertLiteralToClause(literalNumber, std::abs(*currentClause) - 1,
                              isTrue, isFalse);
      } else {
        insertLiteralToClause(literalNumber, *currentClause - 1, undefined,
                              isTrue);
      }
    }
  }

  literals[literalNumber].value = undefined;
}

bool CNF::setLiteral(int literalNumber, boolValue value) {
  if (value == undefined) {
    return false;
  }
  if (literals[literalNumber].value != undefined) {
    resetLiteral(literalNumber);
  }

  bool flag = true;
  literals[literalNumber].value = value;
  if (value == isTrue) {
    for (auto currentClause = literals[literalNumber].clauses.begin();
         currentClause != literals[literalNumber].clauses.end();
         ++currentClause) {
      if (*currentClause > 0) {
        deleteLiteralFromClause(literalNumber, *currentClause - 1, isTrue);
      } else {
        deleteLiteralFromClause(literalNumber, std::abs(*currentClause) - 1,
                                undefined);
      }

      if (clauses[std::abs(*currentClause) - 1].literals.size() == 0 &&
          clauses[std::abs(*currentClause) - 1].value != isTrue) {
        flag = false;
      }
    }
  } else {
    for (auto currentClause = literals[literalNumber].clauses.begin();
         currentClause != literals[literalNumber].clauses.end();
         ++currentClause) {
      if (*currentClause < 0) {
        deleteLiteralFromClause(literalNumber, std::abs(*currentClause) - 1,
                                isTrue);
      } else {
        deleteLiteralFromClause(literalNumber, *currentClause - 1, undefined);
      }

      if (clauses[std::abs(*currentClause) - 1].literals.size() == 0 &&
          clauses[std::abs(*currentClause) - 1].value != isTrue) {
        flag = false;
      }
    }
  }
  return flag;
}

int CNF::findUnitClause(boolValue &value) {
  int number = -1;
  for (auto currentClause = clauses.begin(); currentClause != clauses.end();
       ++currentClause) {
    if ((*currentClause).value == undefined &&
        (int)(*currentClause).literals.size() == 1) {
      int findedLiteral = (*currentClause).literals[0];
      if (findedLiteral > 0) {
        value = isTrue;
      } else {
        value = isFalse;
      }
      number = std::abs((*currentClause).literals[0]) - 1;
      break;
    }
  }
  return number;
}

int CNF::findPureLiteral(boolValue &value) {
  int findedLiteral = -1;
  for (auto currenLiteral = literals.begin(); currenLiteral != literals.end();
       ++currenLiteral) {
    if ((*currenLiteral).value == undefined &&
        (*currenLiteral).counterPositiveClauses +
                (*currenLiteral).counterNegativeClauses >
            0) {
      if ((*currenLiteral).counterPositiveClauses == 0) {
        value = isFalse;
        findedLiteral = currenLiteral - literals.begin();
        break;
      } else if ((*currenLiteral).counterNegativeClauses == 0) {
        value = isTrue;
        findedLiteral = currenLiteral - literals.begin();
        break;
      }
    }
  }
  return findedLiteral;
}

int CNF::selectLiteral() {
  int findedLiteral = -1;
  int minSizeOfUndefinedClause = amountLiterals, findedClause = -1;
  for (auto currentClause = clauses.begin(); currentClause != clauses.end();
       ++currentClause) {
    if ((*currentClause).value == undefined) {
      if (0 < (*currentClause).literals.size() &&
          (*currentClause).literals.size() < minSizeOfUndefinedClause) {
        minSizeOfUndefinedClause = (*currentClause).literals.size();
        findedClause = currentClause - clauses.begin();
      }
    }
  }
  if (findedClause >= 0) {
    int maxAmountClausesInLiteral = 0;
    for (auto currentLiteral = clauses[findedClause].literals.begin();
         currentLiteral != clauses[findedClause].literals.end();
         ++currentLiteral) {
      if (literals[std::abs(*currentLiteral) - 1].value == undefined &&
          maxAmountClausesInLiteral <
              literals[std::abs(*currentLiteral) - 1].clauses.size()) {
        maxAmountClausesInLiteral ==
            literals[std::abs(*currentLiteral) - 1].clauses.size();
        findedLiteral = std::abs(*currentLiteral) - 1;
      }
    }
  }
  return findedLiteral;
}

bool CNF::checkClauses(std::vector<int> &solution) {
  if (positiveClauses == amountClauses) {
    solution.resize(amountLiterals);
    for (int currentLiteral = 0; currentLiteral < amountLiterals;
         ++currentLiteral) {
      if (literals[currentLiteral].value == isTrue) {
        solution[currentLiteral] = 1;
      } else if (literals[currentLiteral].value == isFalse) {
        solution[currentLiteral] = 0;
      } else {
        solution[currentLiteral] = -1;
      }
    }
    return true;
  }
  return false;
}
}
