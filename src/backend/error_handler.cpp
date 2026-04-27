#include "../../include/error_handler.hpp"
#include <array>

/*
Description: This file implements the CalculatorException class and the ErrorHandler class.
The CalculatorException class contains error information for custom errors related to the calculator.
Each exception instance includes the type of error, a message, and the position in the expression where the error occurred.
The ErrorHandler class provides a static method to format error messages based on the CalculatorException instance passed to it.

Implements CalculatorException and ErrorHandler.
CalculatorException stores an `ErrorType`, a formatted message, and the error position in the expression.
ErrorHandler provides `formatError()` which builds human-readable error strings.

Input: This module takes an ErrorType (defined in error_types.hpp), an std::string_view with error details, and an optional unsigned integer position of an error.

Output: Returns a formatted std::string containing information from the error prefix, details, and optional position.

Algorithm: When a CalculatorException is created, the constructor initializes the error type, message, and position.
Type and position are directly assigned from the constructor parameters, then the error message is generated and stored using the formatError method.
formatError() uses a compile-time constant lookup table of message prefixes.
*/

CalculatorException::CalculatorException(ErrorType type, std::string_view details, std::size_t position)
    : type(type), position(position) {
    this->message = ErrorHandler::formatError(type, details, position);
}

// Getter for the error message (formatted as an array of characters not std::string)
const char* CalculatorException::what() const noexcept { return message.c_str(); }

ErrorType CalculatorException::getType() const { return type; }

std::size_t CalculatorException::getPosition() const { return position; }

std::string ErrorHandler::formatError(ErrorType type, std::string_view details, std::size_t position) {
    static constexpr std::array<std::string_view, 9> prefixes = {
        "Lexical error",
        "Syntax error",
        "Evaluation error",
        "Empty expression",
        "Division by zero",
        "Invalid character",
        "Invalid number",
        "Mismatched parentheses",
        "Invalid expression",
    };

    std::string_view prefix = "Error";
    auto idx = static_cast<std::size_t>(type);
    if (idx < prefixes.size()) prefix = prefixes[idx];

    // Reserve estimated size to avoid multiple reallocations
    std::string result;
    if (position > 0) {
        // prefix + " at position " + position digits + ": " + details
        result.reserve(prefix.size() + 14 + details.size());
        result.append(prefix);
        result.append(" at position ");
        result.append(std::to_string(position));
        result.append(": ");
        result.append(details);
    } else {
        result.reserve(prefix.size() + 2 + details.size());
        result.append(prefix);
        result.append(": ");
        result.append(details);
    }

    return result;
}