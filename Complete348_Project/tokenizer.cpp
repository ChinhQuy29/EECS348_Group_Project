#include "tokenizer.hpp"
#include "error_handler.hpp"

#include <cctype>

std::vector<Token> Tokenizer::tokenize(const std::string& expression) const {
    std::vector<Token> tokens;
    std::size_t i = 0;

    while (i < expression.size()) {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }

        // Handle unary minus for negative numbers
        if (c == '-') {
            bool unaryMinus = false;

            if (tokens.empty()) {
                unaryMinus = true;
            } else {
                TokenType prev = tokens.back().type;

                if (prev == TokenType::Plus ||
                    prev == TokenType::Minus ||
                    prev == TokenType::Multiply ||
                    prev == TokenType::Divide ||
                    prev == TokenType::LeftParen) {
                    unaryMinus = true;
                }
            }

            if (unaryMinus) {
                std::string number = "-";
                ++i;

                if (i >= expression.size() ||
                    (!std::isdigit(static_cast<unsigned char>(expression[i])) && expression[i] != '.')) {
                    throw CalculatorException(
                        ErrorType::InvalidNumber,
                        "expected digits after unary minus",
                        i + 1
                    );
                }

                bool hasDecimalPoint = false;

                while (i < expression.size() &&
                       (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                    if (expression[i] == '.') {
                        if (hasDecimalPoint) {
                            throw CalculatorException(
                                ErrorType::InvalidNumber,
                                "multiple decimal points in number",
                                i + 1
                            );
                        }
                        hasDecimalPoint = true;
                    }

                    number += expression[i];
                    ++i;
                }

                if (number == "-.") {
                    throw CalculatorException(
                        ErrorType::InvalidNumber,
                        "invalid negative decimal number",
                        i
                    );
                }

                tokens.push_back({TokenType::Number, number});
                continue;
            }
        }

        // Handle normal numbers
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::string number;
            bool hasDecimalPoint = false;
            std::size_t startPos = i;

            while (i < expression.size() &&
                   (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    if (hasDecimalPoint) {
                        throw CalculatorException(
                            ErrorType::InvalidNumber,
                            "multiple decimal points in number",
                            i + 1
                        );
                    }
                    hasDecimalPoint = true;
                }

                number += expression[i];
                ++i;
            }

            if (number == ".") {
                throw CalculatorException(
                    ErrorType::InvalidNumber,
                    "standalone decimal point is not a valid number",
                    startPos + 1
                );
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
                throw CalculatorException(
                    ErrorType::InvalidCharacter,
                    std::string("unexpected character '") + c + "'",
                    i + 1
                );
        }

        ++i;
    }

    return tokens;
}
