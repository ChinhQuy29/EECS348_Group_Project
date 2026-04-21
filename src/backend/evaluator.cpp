#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"

#include <stack>
#include <string>

double Evaluator::evaluatePostfix(const std::vector<Token>& postfixTokens) const {
    std::stack<double> values;

    for (std::size_t i = 0; i < postfixTokens.size(); ++i) {
        const Token& token = postfixTokens[i];

        if (token.type == TokenType::Number) {
            try {
                values.push(std::stod(token.value));
            } catch (...) {
                throw CalculatorException(
                    ErrorType::InvalidNumber,
                    "failed to convert token '" + token.value + "' to a number",
                    i + 1
                );
            }
            continue;
        }

        if (values.size() < 2) {
            throw CalculatorException(
                ErrorType::InvalidExpression,
                "not enough operands for operator '" + token.value + "'",
                i + 1
            );
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
                    throw CalculatorException(
                        ErrorType::DivisionByZero,
                        "cannot divide by zero",
                        i + 1
                    );
                }
                values.push(left / right);
                break;

            default:
                throw CalculatorException(
                    ErrorType::Evaluation,
                    "unexpected token '" + token.value + "' during evaluation",
                    i + 1
                );
        }
    }

    if (values.size() != 1) {
        throw CalculatorException(
            ErrorType::InvalidExpression,
            "expression could not be fully evaluated"
        );
    }

    return values.top();
}