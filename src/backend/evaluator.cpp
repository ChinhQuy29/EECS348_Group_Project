#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"

#include <stack>
#include <string>

double Evaluator::evaluatePostfix(const std::vector<Token>& postfixTokens) const {
    struct ValueEntry {
        double value;
        std::size_t index;
    };

    std::stack<ValueEntry> values; // Stack to hold intermediate values and indices during evaluation

    for (std::size_t i = 0; i < postfixTokens.size(); ++i) { // Iterate through each token in the postfix expression
        const Token& token = postfixTokens[i];

        // If the token is a number, convert it to a double and push it onto the stack
        if (token.type == TokenType::Number) {
                values.push({std::stod(token.value), token.index});
            continue;
        }

        ErrorHandler::validatePostfixOperandCount(values.size(), token.value, token.index);

        //Pop the top two values from the stack to use as operands for the operator
        ValueEntry right = values.top();
        values.pop();
        ValueEntry left = values.top();
        values.pop();

        //Perform the appropriate operation based on the type of operator token and push the result back onto the stack
        switch (token.type) {
            case TokenType::Plus:
                values.push({left.value + right.value, right.index});
                break;

            case TokenType::Minus:
                values.push({left.value - right.value, right.index});
                break;

            case TokenType::Multiply:
                values.push({left.value * right.value, right.index});
                break;

            case TokenType::Divide:
                ErrorHandler::validateDivisionByZero(right.value, right.index);
                values.push({left.value / right.value, right.index});
                break;
            // No default case needed, leftPeren and RightParen never appear in postfixTokens
        }
    }

    return values.top().value;
}