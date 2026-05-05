#pragma once

#include <string>
#include <vector>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    Mod,
    Exponentiate,
    LeftParen,
    RightParen
};

struct Token {
    TokenType type;
    std::string value;
    size_t index; // 0-based index in the original expression for error reporting
};

class Tokenizer {
public:
    std::vector<Token> tokenize(const std::string& expression) const;
private:
    std::string extractNumber(const std::string& expression, std::size_t& i) const;
};