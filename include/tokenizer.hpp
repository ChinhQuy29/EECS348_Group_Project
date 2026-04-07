#pragma once

#include <string>
#include <vector>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    LeftParen,
    RightParen
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
public:
    std::vector<Token> tokenize(const std::string& expression) const;
};