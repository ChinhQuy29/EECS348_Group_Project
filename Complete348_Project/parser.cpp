#include "parser.hpp"
#include "error_handler.hpp"

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
    return type == TokenType::Plus ||
           type == TokenType::Minus ||
           type == TokenType::Multiply ||
           type == TokenType::Divide;
}

std::vector<Token> Parser::toPostfix(const std::vector<Token>& infixTokens) const {
    if (infixTokens.empty()) {
        throw CalculatorException(
            ErrorType::EmptyExpression,
            "no tokens were produced from the input"
        );
    }

    std::vector<Token> output;
    std::stack<Token> operators;

    for (std::size_t i = 0; i < infixTokens.size(); ++i) {
        const Token& token = infixTokens[i];

        if (token.type == TokenType::Number) {
            output.push_back(token);
        } else if (isOperator(token.type)) {
            // basic syntax check: operator cannot be first or last
            if (i == 0 || i == infixTokens.size() - 1) {
                throw CalculatorException(
                    ErrorType::Syntax,
                    "operator cannot appear at the beginning or end of the expression",
                    i + 1
                );
            }

            // previous token cannot be another operator or left paren
            TokenType prevType = infixTokens[i - 1].type;
            if (isOperator(prevType) || prevType == TokenType::LeftParen) {
                throw CalculatorException(
                    ErrorType::Syntax,
                    "unexpected operator placement",
                    i + 1
                );
            }

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
                throw CalculatorException(
                    ErrorType::MismatchedParentheses,
                    "closing parenthesis does not have a matching opening parenthesis",
                    i + 1
                );
            }
        }
    }

    while (!operators.empty()) {
        if (operators.top().type == TokenType::LeftParen ||
            operators.top().type == TokenType::RightParen) {
            throw CalculatorException(
                ErrorType::MismatchedParentheses,
                "opening parenthesis does not have a matching closing parenthesis"
            );
        }

        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}
