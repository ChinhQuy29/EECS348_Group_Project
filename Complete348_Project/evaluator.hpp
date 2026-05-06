#pragma once

#include "tokenizer.hpp"
#include <vector>

class Evaluator {
public:
    double evaluatePostfix(const std::vector<Token>& postfixTokens) const;
};