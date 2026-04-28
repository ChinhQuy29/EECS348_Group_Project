/*
Description: A Tokenizer class that converts a mathematical expression string into a vector of tokens, which can then be used by the parser and evaluator to compute the result. The tokenizer handles numbers (including negative and decimal numbers), operators, and parentheses, while also performing error checking for invalid characters and malformed numbers.

Input: - expression (std::string): a mathematical expression entered by the user, which may include numbers, operators (+, -, *, /), and parentheses.

Output: - A std::vector<Token> containing the sequence of tokens extracted from the input expression. Each Token consists of a TokenType (Number, Plus, Minus, Multiply, Divide, LeftParen, RightParen) and a string value representing the token's content.

Algorithm: 
1. Initialize an empty vector of tokens and an index variable to track the current position in the input string.
2. Loop through each character in the input expression: 
    a. If the character is whitespace, skip it.
    b. If the character is a '-' and it is determined to be a unary minus (based on its position and preceding tokens), start building a negative number token.
    c. If the character is a digit or a decimal point, start building a number token, ensuring that only one decimal point is allowed.
    d. If the character is an operator or parenthesis, create the corresponding token and add it to the vector.
    e. If an invalid character is encountered, throw a CalculatorException with details about the error and its position in the input string.

Constraints:
- The input expression must be a valid mathematical expression consisting of numbers, operators, and parentheses.
- The tokenizer must correctly identify unary minus for negative numbers and handle decimal points in numbers.
- The tokenizer must throw exceptions for invalid characters and malformed numbers, providing clear error messages and positions for debugging.

*/

#include "../../include/tokenizer.hpp"
#include "../../include/error_handler.hpp"

#include <cctype>

// Converts an input expression string into a vector of tokens, performing error checking for invalid characters and malformed numbers
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

            // A '-' is considered a unary minus if it is at the beginning of the expression or if it follows an operator or left parenthesis
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

            // If it's a unary minus, we need to parse the following number as a negative number
            if (unaryMinus) {
                std::string number = "-";
                ++i;

                // After a unary minus, we expect to see digits or a decimal point to form a valid negative number. If we encounter anything else, it's an error.
                if (i >= expression.size() ||
                    (!std::isdigit(static_cast<unsigned char>(expression[i])) && expression[i] != '.')) {
                    throw CalculatorException(
                        ErrorType::InvalidNumber,
                        "expected digits after unary minus",
                        i + 1
                    );
                }

                // Now we parse the number following the unary minus, allowing for digits and at most one decimal point
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

                // A negative number cannot consist of just a '-' or '-.' without any digits, so we check for that case and throw an error if it occurs
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

            // Parse a number token, allowing for digits and at most one decimal point. If multiple decimal points are found or if the number is malformed (e.g., just a '.'), throw an exception with details about the error and its position in the input string.
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

        // Handle operators and parentheses, throwing an exception for any invalid characters with details about the error and its position in the input string
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