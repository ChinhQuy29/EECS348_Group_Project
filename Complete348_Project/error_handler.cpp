#include "error_handler.hpp"

CalculatorException::CalculatorException(ErrorType type, const std::string& message, std::size_t position)
    : type(type), position(position) {
    this->message = ErrorHandler::formatError(type, message, position);
}

const char* CalculatorException::what() const noexcept {
    return message.c_str();
}

ErrorType CalculatorException::getType() const {
    return type;
}

std::size_t CalculatorException::getPosition() const {
    return position;
}

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
