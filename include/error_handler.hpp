#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <stack>

#include "tokenizer.hpp"

enum class ErrorType {
    Lexical,
    Syntax,
    Evaluation,
    IOError,
    EmptyExpression,
    DivisionByZero,
    InvalidCharacter,
    InvalidNumber,
    MismatchedParentheses,
    InvalidExpression
};

class CalculatorException : public std::exception { // Inherit from standard exception class
public:
    CalculatorException(ErrorType type, std::string_view message, std::size_t position = 0);

    const char* what() const noexcept override; // Virtual function defined in parent
    ErrorType getType() const;
    std::size_t getPosition() const;

private: // Stored values
    ErrorType type;
    std::string message;
    std::size_t position;
};

class ErrorHandler {
public:
    static void validateExpression(std::string_view expression);
    static void validateUnaryMinus(std::string_view expression, std::size_t nextPosition);
    static void validateDecimalPoint(bool hasDecimalPoint, std::size_t position);
    static void validateCompletedNumber(std::string_view number, std::size_t position);
    static void validateCharacter(char character, std::size_t position);
    static void validateOperatorPlacement(const std::vector<Token>& tokens, std::size_t tokenIndex);
    static void validateClosingParenthesis(std::stack<Token> operators, std::size_t position);
    static void validateOpeningParentheses(std::stack<std::size_t> positionLeftParen);
    static void validatePostfixOperandCount(std::size_t valueCount, std::string_view token, std::size_t position);
    static void validateDivisionByZero(double right, std::size_t position);
    static void validateUnexpectedEvaluationToken(std::string_view value, std::size_t position);
    static void validateHistoryStream(bool streamOk);

    static std::string formatError(ErrorType type, std::string_view details, std::size_t position = 0);
};