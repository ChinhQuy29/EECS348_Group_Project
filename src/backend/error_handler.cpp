#include "../../include/error_handler.hpp"

#include <array>
#include <algorithm>
#include <cctype>
#include <string>

/*
Description: This file implements the CalculatorException class and the ErrorHandler class.
The CalculatorException class contains error information for custom errors related to the calculator.
Each exception instance includes the type of error, a message, and the position in the expression where the error occurred.
The ErrorHandler class provides a static method to format error messages based on the CalculatorException instance passed to it.

Implements CalculatorException and ErrorHandler.
CalculatorException stores an `ErrorType`, a formatted message, and the error position (starting from one) in the expression.
ErrorHandler provides `formatError()` which builds human-readable error strings.

Input: This module takes an ErrorType (defined in error_types.hpp), an std::string_view with error details, and an optional unsigned integer position of an error.

Output: Returns a formatted std::string containing information from the error prefix, details, and optionally the one-indexed position.

Algorithm: When a CalculatorException is created, the constructor initializes the error type, message, and position.
Type and position are directly assigned from the constructor parameters, then the error message is generated and stored using the formatError method.
formatError() uses a compile-time constant lookup table of message prefixes.
*/

CalculatorException::CalculatorException(ErrorType type,
  std::string_view details,
  std::size_t position)
  : type(type), position(position) {
  this->message = CalculatorException::formatError(type, details, position);
}

const char* CalculatorException::what() const noexcept { return message.c_str(); }
ErrorType CalculatorException::getType() const { return type; }
std::size_t CalculatorException::getPosition() const { return position; }

std::string CalculatorException::formatError(ErrorType type, std::string_view details,
  std::size_t position) {
  static constexpr std::array<std::string_view, 10> prefixes = {
    "Lexical error",
    "Syntax error",
    "Evaluation error",
    "I/O error",
    "Empty expression",
    "Division by zero",
    "Invalid character",
    "Invalid number",
    "Mismatched parentheses",
    "Invalid expression",
  };

  std::string_view prefix;
  if (static_cast<std::size_t>(type) < prefixes.size()) {
    prefix = prefixes[static_cast<std::size_t>(type)];
  }
  else {
    prefix = "Error";
  }

  std::string result = std::string(prefix) + ": " + std::string(details);
  if (position != 0)
    result.insert(result.find(':'), " at position " + std::to_string(position));
  return result;
}

void ErrorHandler::validateExpression(std::string_view expression) {
  if (std::all_of(expression.begin(), expression.end(), [](unsigned char c) { return std::isspace(c); })) {
    throw CalculatorException(
      ErrorType::EmptyExpression,
      "input expression is empty");
  }
}

void ErrorHandler::validateUnaryMinus(std::string_view expression,
  std::size_t nextPosition) {
  if (nextPosition >= expression.size() ||
    (!std::isdigit(static_cast<unsigned char>(expression[nextPosition])) &&
      expression[nextPosition] != '.')) {
    throw CalculatorException(
      ErrorType::InvalidNumber,
      "expected digits after unary minus",
      nextPosition);
  }
}

void ErrorHandler::validateDecimalPoint(bool countDecimalPoint,
  std::size_t position) {
  // if already has a decimal point
  if (countDecimalPoint) {
    throw CalculatorException(
      ErrorType::InvalidNumber,
      "multiple decimal points in number",
      position);
  }
}

void ErrorHandler::validateCompletedNumber(std::string_view number,
  std::size_t position) {
  if (number == ".") {
    throw CalculatorException(
      ErrorType::InvalidNumber,
      "standalone decimal point is not a valid number",
      position);
  }
}

void ErrorHandler::validateCharacter(char character, std::size_t position) {
  std::string msg = "unexpected character '" + std::string(1, character) + "'";
  throw CalculatorException(
    ErrorType::InvalidCharacter,
    msg,
    position);
}


void ErrorHandler::validateOperatorExistence(const std::vector<Token>& tokens, std::size_t tokenIndex) {
  if (tokenIndex > 0 && tokenIndex < tokens.size() - 1) {
    TokenType previousType = tokens[tokenIndex - 1].type;

    // if not Plus, Minus, Multiply, Divide, nor LeftParen
    if (previousType == TokenType::Number || previousType == TokenType::RightParen) {
      throw CalculatorException(
        ErrorType::Syntax,
        "tokens must be separated by operators",
        tokenIndex + 1);
    }
  }
}

void ErrorHandler::validateOperatorPlacement(const std::vector<Token>& tokens,
  std::size_t tokenIndex) {
  if (tokenIndex == 0) {
    throw CalculatorException(
      ErrorType::Syntax,
      "operator cannot appear at the beginning of the expression",
      tokenIndex + 1);
  }

  if (tokenIndex == tokens.size() - 1) {
    throw CalculatorException(
      ErrorType::Syntax,
      "operator cannot appear at the end of the expression",
      tokenIndex + 1);
  }
  TokenType previousType = tokens[tokenIndex - 1].type;

  // if is Plus, Minus, Multiply, Divide, or LeftParen
  if (previousType != TokenType::Number && previousType != TokenType::RightParen) {
    throw CalculatorException(
      ErrorType::Syntax,
      "unexpected operator placement",
      tokenIndex + 1);
  }
}

void ErrorHandler::validateClosingParenthesis(
  std::stack<Token> operators, std::size_t position) {
  while (!operators.empty() && operators.top().type != TokenType::LeftParen) {
    operators.pop();
  }
  if (operators.empty()) {
    throw CalculatorException(
      ErrorType::MismatchedParentheses,
      "closing parenthesis does not have a matching opening parenthesis",
      position);
  }
}

void ErrorHandler::validateOpeningParenthesis(std::stack<std::size_t> positionLeftParen) {
  while (!positionLeftParen.empty()) {
    throw CalculatorException(
      ErrorType::MismatchedParentheses,
      "opening parenthesis does not have a matching closing parenthesis",
      positionLeftParen.top());
  }
}

void ErrorHandler::validatePostfixOperandCount(std::size_t valueCount,
  std::string_view token,
  std::size_t position) {
  if (valueCount < 2) {
    std::string msg = "not enough operands for operator '" +
      std::string(token) + "'";
    throw CalculatorException(
      ErrorType::InvalidExpression,
      msg,
      position);
  }
}

void ErrorHandler::validateDivisionByZero(double right, std::size_t position) {
  if (right == 0.0) {
    throw CalculatorException(
      ErrorType::DivisionByZero,
      "cannot divide by zero",
      position);
  }
}

void ErrorHandler::validateHistoryStream(bool streamOk) {
  if (!streamOk) {
    throw CalculatorException(
      ErrorType::IOError,
      "failed to open history file");
  }
}