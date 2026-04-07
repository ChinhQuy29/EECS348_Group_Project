#include "../../include/evaluator.hpp"

#include <stack>
#include <stdexcept>
#include <string>

double Evaluator::evaluatePostfix(const std::vector<Token>& postfixTokens) const {
    std::stack<double> values;

    for (const Token& token : postfixTokens) {
        if (token.type == TokenType::Number) {
            values.push(std::stod(token.value));
            continue;
        }

        if (values.size() < 2) {
            throw std::runtime_error("Invalid expression");
        }

        double right = values.top();
        values.pop();
        double left = values.top();
        values.pop();

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
                if (right == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                values.push(left / right);
                break;
            default:
                throw std::runtime_error("Unexpected token in postfix evaluation");
        }
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return values.top();
}