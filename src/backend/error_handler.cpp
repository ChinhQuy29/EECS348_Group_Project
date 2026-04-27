#include "../../include/error_handler.hpp"

/*
Description: This file implements the CalculatorException class and the ErrorHandler class.
The CalculatorException class contains error information for custom errors related to the calculator.
Each exception instance includes the type of error, a message, and the position in the expression where the error occurred.
The ErrorHandler class provides a static method to format error messages based on the CalculatorException instance passed to it.

Input: This module takes an ErrorType (defined in error_types.hpp), a string with error details, and an optional unsigned integer position of an error.

Output: A formatted error string.

Algorithm: When a CalculatorException is created, the constructor initializes the error type, message, and position.
The input message is changed and stored using the formatError method.
*/

CalculatorException::CalculatorException(ErrorType type, const std::string& message, std::size_t position)
    : type(type), position(position) {
    this->message = ErrorHandler::formatError(type, message, position);
}

// Getter for the error message (formatted as an array of characters not std::string)
const char* CalculatorException::what() const noexcept { return message.c_str(); }

ErrorType CalculatorException::getType() const { return type; }

std::size_t CalculatorException::getPosition() const { return position; }

std::string ErrorHandler::formatError(ErrorType type, const std::string& details, std::size_t position) {
    std::string prefix;

    switch (type) {
        case ErrorType::Lexical:
            prefix = "Lexical error";
            break;
        case ErrorType::Syntax:
            prefix = "Syntax error";
            break;
        case ErrorType::Evaluation:
            prefix = "Evaluation error";
            break;
        case ErrorType::EmptyExpression:
            prefix = "Empty expression";
            break;
        case ErrorType::DivisionByZero:
            prefix = "Division by zero";
            break;
        case ErrorType::InvalidCharacter:
            prefix = "Invalid character";
            break;
        case ErrorType::InvalidNumber:
            prefix = "Invalid number";
            break;
        case ErrorType::MismatchedParentheses:
            prefix = "Mismatched parentheses";
            break;
        case ErrorType::InvalidExpression:
            prefix = "Invalid expression";
            break;
        default:
            prefix = "Error";
            break;
    }

    if (position > 0) {
        return prefix + " at position " + std::to_string(position) + ": " + details;
    }

    return prefix + ": " + details;
}