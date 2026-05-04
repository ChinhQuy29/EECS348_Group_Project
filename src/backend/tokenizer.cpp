#include "../../include/tokenizer.hpp"
#include "../../include/error_handler.hpp"

#include <cctype>

/*
/ Extracts a number from the expression string starting at index i
/ WARNING: Takes i by reference and updates it to the index of the last digit of the number
*/
std::string Tokenizer::extractNumber(const std::string& expression, std::size_t& i) const {
    std::string number;
    bool countDecimalPoint = 0;

    // for the following characters that are part of a number
    for (; i < expression.size() && (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'); i++) {
        if (expression[i] == '.') {
            ErrorHandler::validateDecimalPoint(countDecimalPoint, i);
            countDecimalPoint = 1;
        }

        number += expression[i];
    }
    ErrorHandler::validateCompletedNumber(number, --i); // adjust i to the index of the last digit
    return number;
}

/*
/ Splits the expression string into a vector of Tokens in infix order
/ A Token stores the type of token and the substring of the expression that corresponds to it
*/
std::vector<Token> Tokenizer::tokenize(const std::string& expression) const {
    ErrorHandler::validateExpression(expression);
    std::vector<Token> tokens;

    for (std::size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c))) { // Handle whitespace
            // then ignore

        } else if (c == '-' // Handle unary minus
                   && (tokens.empty() // if first token or preceded by plus, minus, multiply, divide, or left parenthesis
                       || (tokens.back().type != TokenType::Number
                           && tokens.back().type != TokenType::RightParen))) {

            std::size_t minusIndex = i;
            ++i;
            ErrorHandler::validateUnaryMinus(expression, i);

            tokens.push_back({TokenType::Number, "-" + extractNumber(expression, i), minusIndex});

        } else if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') { // Handle normal numbers
            std::size_t numberIndex = i;
            tokens.push_back({TokenType::Number, extractNumber(expression, i), numberIndex});

        } else { // Handle operators and parentheses
            switch (c) {
                case '+':
                    tokens.push_back({TokenType::Plus, "+", i});
                    break;
                case '-':
                    tokens.push_back({TokenType::Minus, "-", i});
                    break;
                case '*':
                    tokens.push_back({TokenType::Multiply, "*", i});
                    break;
                case '/':
                    tokens.push_back({TokenType::Divide, "/", i});
                    break;
                case '(':
                    tokens.push_back({TokenType::LeftParen, "(", i});
                    break;
                case ')':
                    tokens.push_back({TokenType::RightParen, ")", i});
                    break;
                default:
                    ErrorHandler::validateCharacter(c, i);
            }
        }
    }

    return tokens;
}