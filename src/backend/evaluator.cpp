#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"

#include <cmath>
#include <ctime>
#include <stack>
#include <string>
#include <random>

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
    struct ValueToken {
        long double value;
        std::size_t index;
    };

    std::stack<ValueToken> values; // Stack to hold intermediate values and indices during evaluation

    for (std::size_t i = 0; i < postfixTokens.size(); ++i) { // Iterate through each currentToken in the postfix expression
        const Token& currentToken = postfixTokens[i];

        // If the currentToken is a number, convert it to a double and push it onto the stack
        if (currentToken.type == TokenType::Number) {
            values.push({std::stold(currentToken.value), currentToken.index});
            continue;
        }
        if (currentToken.type == TokenType::RandomMax) {
            std::default_random_engine generator(static_cast<unsigned int>(std::time(nullptr)));
            std::uniform_int_distribution<int> distribution(1, std::stoi(currentToken.value));
            values.push({static_cast<long double>(distribution(generator)), currentToken.index});
            continue;
        }

        //If there are fewer than 2 values on the stack when an operator is encountered,
        //throw an exception indicating that there are not enough operands for the operator
        ErrorHandler::validatePostfixOperandCount(values.size(), currentToken);

        //Pop the top two values from the stack to use as operands for the operator
        ValueToken right = values.top();
        values.pop();
        ValueToken left = values.top();
        values.pop();

        //Perform the appropriate operation based on the type of operator currentToken and push the result back onto the stack
        switch (currentToken.type) {
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

            case TokenType::Mod:
                ErrorHandler::validateDivisionByZero(right.value, right.index);
                values.push({static_cast<long double>(std::fmod(left.value, right.value)), right.index});
                break;

            case TokenType::Exponentiate:
                values.push({static_cast<long double>(std::pow(left.value, right.value)), right.index});
                break;
            // No default case needed, LeftParen and RightParen never appear in postfixTokens
        }
    }

    return values.top().value;
}