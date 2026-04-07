#pragma once

#include "tokenizer.h"
#include <vector>

class Parser {
public:
    std::vector<Token> toPostfix(const std::vector<Token>& infixTokens) const;

private:
    int precedence(TokenType type) const;
    bool isOperator(TokenType type) const;
};