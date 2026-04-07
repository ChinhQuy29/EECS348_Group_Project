#pragma once

#include "tokenizer.h"
#include <vector>

class Evaluator {
public:
    double evaluatePostfix(const std::vector<Token>& postfixTokens) const;
};