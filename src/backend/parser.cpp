#include "../include/parser.h"

#include <stack>
#include <stdexcept>

int Parser::precedence(TokenType type) const {
    switch (type) {
        case TokenType::Plus:
        case TokenType::Minus:
            return 1;
        case TokenType::Multiply:
        case TokenType::Divide:
            return 2;
        default:
            return 0;
    }
}

bool Parser::isOperator(TokenType type) const {
    return type == TokenType::Plus ||
           type == TokenType::Minus ||
           type == TokenType::Multiply ||
           type == TokenType::Divide;
}

std::vector<Token> Parser::toPostfix(const std::vector<Token>& infixTokens) const {
    std::vector<Token> output;
    std::stack<Token> operators;

    for (const Token& token : infixTokens) {
        if (token.type == TokenType::Number) {
            output.push_back(token);
        } else if (isOperator(token.type)) {
            while (!operators.empty() &&
                   isOperator(operators.top().type) &&
                   precedence(operators.top().type) >= precedence(token.type)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        } else if (token.type == TokenType::LeftParen) {
            operators.push(token);
        } else if (token.type == TokenType::RightParen) {
            bool foundLeftParen = false;

            while (!operators.empty()) {
                if (operators.top().type == TokenType::LeftParen) {
                    foundLeftParen = true;
                    operators.pop();
                    break;
                }
                output.push_back(operators.top());
                operators.pop();
            }

            if (!foundLeftParen) {
                throw std::runtime_error("Mismatched parentheses");
            }
        }
    }

    while (!operators.empty()) {
        if (operators.top().type == TokenType::LeftParen ||
            operators.top().type == TokenType::RightParen) {
            throw std::runtime_error("Mismatched parentheses");
        }

        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}