#include "../../include/parser.hpp"
#include "../../include/error_handler.hpp"

#include <stack>

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
    // Not Number, LeftParen, nor RightParen
    return type == TokenType::Plus ||
           type == TokenType::Minus ||
           type == TokenType::Multiply ||
           type == TokenType::Divide;
}

std::vector<Token> Parser::toPostfix(const std::vector<Token>& infixTokens) const {
    std::vector<Token> postfixTokens;
    std::stack<Token> operators;
    std::stack<std::size_t> positionLeftParen; // Stack to track positions of left parentheses for error reporting

    // for each token in the infix expression
    for (std::size_t i = 0; i < infixTokens.size(); ++i) {
        const Token& token = infixTokens[i];

        if (token.type == TokenType::Number) {
            postfixTokens.push_back(token);
        } else if (isOperator(token.type)) {
            ErrorHandler::validateOperatorPlacement(infixTokens, i);

            while (!operators.empty() &&
                   isOperator(operators.top().type) &&
                   precedence(operators.top().type) >= precedence(token.type)) {
                postfixTokens.push_back(operators.top());
                operators.pop();
            }

            operators.push(token);
        } else if (token.type == TokenType::LeftParen) {
            operators.push(token);
            positionLeftParen.push(i + 1);
        } else if (token.type == TokenType::RightParen) {
            ErrorHandler::validateClosingParenthesis(operators, i + 1);
            
            // while inside the parentheses, move operators to output
            while (operators.top().type != TokenType::LeftParen) {
                postfixTokens.push_back(operators.top());
                operators.pop();
            }

            // Pop the left parenthesis
            operators.pop();
            positionLeftParen.pop();
        }
    }

    ErrorHandler::validateOpeningParentheses(positionLeftParen);

    while (!operators.empty()) {
        postfixTokens.push_back(operators.top());
        operators.pop();
    }

    return postfixTokens;
}