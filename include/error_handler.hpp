#pragma once

#include <exception>
#include <string>
#include <string_view>

enum class ErrorType {
    Lexical,
    Syntax,
    Evaluation,
    EmptyExpression,
    DivisionByZero,
    InvalidCharacter,
    InvalidNumber,
    MismatchedParentheses,
    InvalidExpression
};

class CalculatorException : public std::exception {
public:
    CalculatorException(ErrorType type, std::string_view message, std::size_t position = 0);

    const char* what() const noexcept override;
    ErrorType getType() const;
    std::size_t getPosition() const;

private:
    ErrorType type;
    std::string message;
    std::size_t position;
};

class ErrorHandler {
public:
    static std::string formatError(ErrorType type, std::string_view details, std::size_t position = 0);
};