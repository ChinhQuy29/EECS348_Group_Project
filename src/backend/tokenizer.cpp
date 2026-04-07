#include "../../include/tokenizer.hpp"

#include <cctype>
#include <stdexcept>

std::vector<Token> Tokenizer::tokenize(const std::string& expression) const {
    std::vector<Token> tokens;
    std::size_t i = 0;

    while (i < expression.size()) {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::string number;
            bool hasDecimalPoint = false;

            while (i < expression.size() &&
                   (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    if (hasDecimalPoint) {
                        throw std::runtime_error("Invalid number: multiple decimal points");
                    }
                    hasDecimalPoint = true;
                }
                number += expression[i];
                ++i;
            }

            if (number == ".") {
                throw std::runtime_error("Invalid number: '.'");
            }

            tokens.push_back({TokenType::Number, number});
            continue;
        }

        switch (c) {
            case '+':
                tokens.push_back({TokenType::Plus, "+"});
                break;
            case '-':
                tokens.push_back({TokenType::Minus, "-"});
                break;
            case '*':
                tokens.push_back({TokenType::Multiply, "*"});
                break;
            case '/':
                tokens.push_back({TokenType::Divide, "/"});
                break;
            case '(':
                tokens.push_back({TokenType::LeftParen, "("});
                break;
            case ')':
                tokens.push_back({TokenType::RightParen, ")"});
                break;
            default:
                throw std::runtime_error(std::string("Invalid character: ") + c);
        }

        ++i;
    }

    return tokens;
}