#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"

#include <stack>
#include <string>

double Evaluator::evaluatePostfix(const std::vector<Token>& postfixTokens) const {
    std::stack<double> values; // Stack to hold intermediate values during evaluation

    for (std::size_t i = 0; i < postfixTokens.size(); ++i) { // Iterate through each token in the postfix expression
        const Token& token = postfixTokens[i];

        // If the token is a number, convert it to a double and push it onto the stack
        if (token.type == TokenType::Number) {
                values.push(std::stod(token.value));
            continue;
        }

        ErrorHandler::validatePostfixOperandCount(values.size(), token.value, i + 1);

        //Pop the top two values from the stack to use as operands for the operator
        double right = values.top();
        values.pop();
        double left = values.top();
        values.pop();

        //Perform the appropriate operation based on the type of operator token and push the result back onto the stack
        switch (token.type) {
            case TokenType::Plus:
                values.push(left + right);
                break;

            case TokenType::Minus:
                values.push(left - right);
                break;

            case TokenType::Multiply:
                values.push(left * right);
                break;

            case TokenType::Divide:
                ErrorHandler::validateDivisionByZero(right, i + 1);
                values.push(left / right);
                break;
            // No default case needed, leftPeren and RightParen never appear in postfixTokens
        }
    }

    return values.top();
}