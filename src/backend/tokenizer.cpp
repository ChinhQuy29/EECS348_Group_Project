#include "../../include/tokenizer.hpp"
#include "../../include/error_handler.hpp"

#include <cctype>

/*
/ Splits the expression string into a vector of Tokens
/ A Token stores the type of token and the substring of the expression that corresponds to it
*/

std::vector<Token> Tokenizer::tokenize(const std::string& expression) const {
    ErrorHandler::validateExpression(expression);
    std::vector<Token> tokens;
    std::size_t i = 0;

    while (i < expression.size()) {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue; // ignore
        }

        if (c == '-') {
            bool unaryMinus = false;

            // if first token
            if (tokens.empty()) {
                unaryMinus = true;
            } else {
                TokenType prev = tokens.back().type;

                // if not Number nor RightParen
                if (prev == TokenType::Plus ||
                    prev == TokenType::Minus ||
                    prev == TokenType::Multiply ||
                    prev == TokenType::Divide ||
                    prev == TokenType::LeftParen) {
                    unaryMinus = true;
                }
            }

            // Handle unary minus for negative numbers
            if (unaryMinus) {
                ++i;
                std::string number;
                bool hasDecimalPoint = false;

                ErrorHandler::validateUnaryMinus(expression, i);

                // while the following characters are part of a number
                while (i < expression.size() &&
                       (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                    if (expression[i] == '.') {
                        ErrorHandler::validateDecimalPoint(hasDecimalPoint, i + 1);
                        hasDecimalPoint = true;
                    }

                    number += expression[i];
                    ++i;
                }
                ErrorHandler::validateCompletedNumber(number, i);

                tokens.push_back({TokenType::Number, "-" + number});
                continue;
            }
        }

        // Handle normal numbers
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::string number;
            bool hasDecimalPoint = false;

            // while the following characters are part of a number
            while (i < expression.size() &&
                   (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    ErrorHandler::validateDecimalPoint(hasDecimalPoint, i + 1);
                    hasDecimalPoint = true;
                }

                number += expression[i];
                ++i;
            }
            ErrorHandler::validateCompletedNumber(number, i);

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
                ErrorHandler::validateCharacter(c, i + 1);
        }

        ++i;
    }

    return tokens;
}