/*
Description:
Implements the Parser class, which converts a mathematical expression
from infix notation to postfix notation using a stack-based algorithm.
The parser ensures correct operator precedence and validates syntax,
including proper operator placement and matching parentheses.

Input:
- infixTokens (std::vector<Token>): list of tokens representing the expression

Tokens may include:
- Numbers
- Operators (+, -, *, /)
- Parentheses ( ( and ) )

Output:
- Returns a std::vector<Token> representing the postfix expression
- Throws errors for invalid syntax or mismatched parentheses

Constraints:
- Token list must not be empty
- Operators cannot appear at the beginning or end
- Operators cannot follow another operator or '('
- Parentheses must be properly matched

Algorithm:
1. Check if token list is empty -> throws error if true

2. Iterate through each token:
   - If number -> add to output
   - If operator:
       - Validate placement
       - Pop operators from stack based on precedence
       - Push current operator to stack
   - If '(' -> push to stack
   - If ')' -> pop until matching '('

3. After iteration:
   - Pop remaining operators to output
   - Throw error if unmatched parentheses remain

4. Return postfix token list
*/

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
        case TokenType::Mod:
            return 2;
        case TokenType::Exponentiate:
            return 3;
        default:
            return 0;
    }
}

bool Parser::isOperator(TokenType type) const {
    // Not Number, RandomMax, LeftParen, nor RightParen
    return type == TokenType::Plus ||
           type == TokenType::Minus ||
           type == TokenType::Multiply ||
           type == TokenType::Divide ||
           type == TokenType::Mod ||
           type == TokenType::Exponentiate;
}

std::vector<Token> Parser::toPostfix(const std::vector<Token>& infixTokens) const {
    std::vector<Token> postfixTokens;
    std::stack<Token> operators;
    std::stack<std::size_t> leftParenIndices; // Stack to track indices of left parentheses for error reporting

    // for each token in the infix expression
    for (std::size_t i = 0; i < infixTokens.size(); ++i) {
        const Token& token = infixTokens[i];

        if (token.type == TokenType::Number || token.type == TokenType::RandomMax) {
            ErrorHandler::validateOperatorExistence(infixTokens, i);
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
        }
        else if (token.type == TokenType::LeftParen) {
            ErrorHandler::validateOperatorExistence(infixTokens, i);
            operators.push(token);
            leftParenIndices.push(token.index);
        } else if (token.type == TokenType::RightParen) {
            ErrorHandler::validateClosingParenthesis(operators, token.index);
            
            // while inside the parentheses, move operators to output
            while (operators.top().type != TokenType::LeftParen) {
                postfixTokens.push_back(operators.top());
                operators.pop();
            }

            // Pop the left parenthesis
            operators.pop();
            leftParenIndices.pop();
        }
    }

    ErrorHandler::validateOpeningParenthesis(leftParenIndices);

    while (!operators.empty()) {
        postfixTokens.push_back(operators.top());
        operators.pop();
    }

    return postfixTokens;
}