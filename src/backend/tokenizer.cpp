#include "../../include/tokenizer.hpp"
#include "../../include/error_handler.hpp"

#include <cctype>

/*
/ Extracts a number from the expression string starting at index i
/ WARNING: Takes i by reference and updates it to the position after the number
*/
std::string Tokenizer::extractNumber(const std::string& expression, std::size_t& i) const {
    std::string number;
    bool countDecimalPoint = 0;

    // for the following characters that are part of a number
    for (; i < expression.size() && (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'); i++) {
        if (expression[i] == '.') {
            ErrorHandler::validateDecimalPoint(countDecimalPoint, i + 1);
            countDecimalPoint = 1;
        }

        number += expression[i];
    }
    ErrorHandler::validateCompletedNumber(number, i);
    i--; // adjust i to the index of the last digit
    return number;
}

/*
/ Splits the expression string into a vector of Tokens
/ A Token stores the type of token and the substring of the expression that corresponds to it
*/
std::vector<Token> Tokenizer::tokenize(const std::string& expression) const {
    ErrorHandler::validateExpression(expression);
    std::vector<Token> tokens;
    

    for (std::size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            continue; // ignore
        }

        if (c == '-') {
            bool unaryMinus = false;

            // if first token
            if (tokens.empty()) {
                unaryMinus = true;
            } else {
                TokenType prev = tokens.back().type;

                // if is plus, minus, multiply, divide, or left parenthesis
                if (prev != TokenType::Number && prev != TokenType::RightParen) {
                    unaryMinus = true;
                }
            }

            // Handle unary minus for negative numbers
            if (unaryMinus) {
                ++i;
                ErrorHandler::validateUnaryMinus(expression, i);

                tokens.push_back({TokenType::Number, "-" + extractNumber(expression, i)});
                continue;
            }
        }

        // Handle normal numbers
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            tokens.push_back({TokenType::Number, extractNumber(expression, i)});
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
    }

    return tokens;
}