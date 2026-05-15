#pragma once

#include "tokenizer.hpp"
#include <vector>

class Evaluator {
public:
  long double evaluatePostfix(const std::vector<Token> &postfixTokens) const;

private:
  unsigned int makeSeed() const;
};
