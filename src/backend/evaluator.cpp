#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"

#include <stack>
#include <string>

/*
Description: Evaluates a postfix (Reverse Polish Notation) expression and returns
its numeric result. Handles the four basic arithmetic operations and division-by-zero
detection.

Input: A std::vector<Token> representing a valid postfix expression. Each Token has
a type (Number, Plus, Minus, Multiply, Divide) and a string value. Number tokens
must be convertible to double. The vector is assumed to be ordered in postfix sequence.

Output: A double representing the computed result of the expression. Throws a
CalculatorException (ErrorType::InvalidNumber, InvalidExpression, DivisionByZero,
or Evaluation) if the input is malformed or an illegal operation is attempted.

Algorithm: Iterates through each token using an operand stack. Number tokens are
converted to double and pushed onto the stack. For each operator token, two operands
are popped, the operation is applied, and the result is pushed back. After all tokens
are processed, the single remaining stack value is returned as the final result.
*/

double Evaluator::evaluatePostfix(const std::vector<Token>& postfixTokens) const {
    std::stack<double> values; //Stack to hold intermediate values during evaluation

    for (std::size_t i = 0; i < postfixTokens.size(); ++i) { //Iterate through each token in the postfix expression
        const Token& token = postfixTokens[i];

        //If the token is a number, convert it to a double and push it onto the stack
        if (token.type == TokenType::Number) {
            try {
                values.push(std::stod(token.value));
            } catch (...) { //If conversion fails, throw an exception with details about the error
                throw CalculatorException( //Create a CalculatorException with the appropriate error type, message, and position
                    ErrorType::InvalidNumber,
                    "failed to convert token '" + token.value + "' to a number",
                    i + 1
                );
            }
            continue;
        }

        //If there are fewer than 2 values on the stack when an operator is encountered,
        //throw an exception indicating that there are not enough operands for the operator
        if (values.size() < 2) { 
            throw CalculatorException(
                ErrorType::InvalidExpression,
                "not enough operands for operator '" + token.value + "'",
                i + 1
            );
        }

        //Pop the top two values from the stack to use as operands for the operator
        double right = values.top();
        values.pop();

        //Pop the next value from the stack to use as the left operand for the operator
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
                if (right == 0.0) {
                    throw CalculatorException(
                        ErrorType::DivisionByZero,
                        "cannot divide by zero",
                        i + 1
                    );
                }
                values.push(left / right);
                break;

            // If the token is an operator that is not recognized, throw an exception indicating that an unexpected token was encountered during evaluation
            default:
                throw CalculatorException(
                    ErrorType::Evaluation,
                    "unexpected token '" + token.value + "' during evaluation",
                    i + 1
                );
        }
    }
    //After processing all tokens, there should be exactly one value left on the stack, which is the final result of the expression. 
    //If there are more than one value left, it means the expression was not valid and an exception is thrown.
    if (values.size() != 1) {
        throw CalculatorException(
            ErrorType::InvalidExpression,
            "expression could not be fully evaluated"
        );
    }

    return values.top();
}