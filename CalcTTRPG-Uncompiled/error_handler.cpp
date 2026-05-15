#include "error_handler.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <string>

/*
Description: This file implements the CalculatorException class and the
ErrorHandler class. The CalculatorException class contains error information for
custom errors related to the calculator. Each exception instance includes the
type of error, a message, and the 1-based position in the expression where the
error occurred. The ErrorHandler class provides a static method to format error
messages based on the CalculatorException instance passed to it.

Implements CalculatorException and ErrorHandler.
CalculatorException stores an `ErrorType`, a formatted message, and the error
position (1-based) in the expression. ErrorHandler provides `formatError()`
which builds human-readable error strings from 1-based positions.

Input: This module takes an ErrorType (defined in error_types.hpp), an
std::string_view with error details, and an optional unsigned integer index
(0-based expression index).

Output: Returns a formatted std::string containing information from the error
prefix, details, and optionally the 1-based position.

Algorithm: When a CalculatorException is created, the constructor initializes
the error type, message, and position. Type and position are directly assigned
from the constructor parameters, then the error message is generated and stored
using the formatError method. formatError() uses a compile-time constant lookup
table of message prefixes.
*/

CalculatorException::CalculatorException(ErrorType type,
                                         std::string_view details,
                                         std::size_t position)
    : type(type), position(position) {
  this->message = CalculatorException::formatError(type, details, position);
}

const char *CalculatorException::what() const noexcept {
  return message.c_str();
}
ErrorType CalculatorException::getType() const { return type; }
std::size_t CalculatorException::getPosition() const { return position; }

std::string CalculatorException::formatError(ErrorType type,
                                             std::string_view details,
                                             std::size_t position) {
  static constexpr std::array<std::string_view, 10> prefixes = {
      "Lexical error",      "Syntax error",     "Evaluation error",
      "I/O error",          "Empty expression", "Division by zero",
      "Invalid character",  "Invalid number",   "Mismatched parentheses",
      "Invalid expression",
  };

  std::string_view prefix;
  if (static_cast<std::size_t>(type) < prefixes.size()) {
    prefix = prefixes[static_cast<std::size_t>(type)];
  } else {
    prefix = "Error";
  }

  if (position != 0) {
    return std::string(prefix) + " at position " + std::to_string(position) +
           ": " + std::string(details);
  } else {
    return std::string(prefix) + ": " + std::string(details);
  }
}

// Used in tokenizer
void ErrorHandler::validateExpression(std::string_view expression) {
  if (std::all_of(expression.begin(), expression.end(), [](unsigned char c) {
        return (std::isspace(c) || c == '(' || c == ')');
      })) {
    throw CalculatorException(ErrorType::EmptyExpression,
                              "input expression is empty");
  }
}

// Used in tokenizer
void ErrorHandler::validateUnaryOperation(std::string_view expression,
                                          std::size_t nextIndex) {
  if (nextIndex >= expression.size() ||
      (!std::isdigit(static_cast<unsigned char>(expression[nextIndex])) &&
       expression[nextIndex] != '.')) {
    throw CalculatorException(ErrorType::InvalidNumber,
                              "expected digits after unary operation",
                              nextIndex + 1);
  }
}

// Used in tokenizer
void ErrorHandler::validateDecimalPoint(bool countDecimalPoint,
                                        std::size_t index) {
  // if already has a decimal point
  if (countDecimalPoint) {
    throw CalculatorException(ErrorType::InvalidNumber,
                              "multiple decimal points in number", index + 1);
  }
}

// Used in tokenizer
void ErrorHandler::validateCompletedNumber(std::string_view number,
                                           std::size_t index) {
  if (number == ".") {
    throw CalculatorException(ErrorType::InvalidNumber,
                              "standalone decimal point is not a valid number",
                              index + 1);
  }
}

// Used in tokenizer
void ErrorHandler::validateCharacter(char character, std::size_t index) {
  throw CalculatorException(
      ErrorType::InvalidCharacter,
      "unexpected character '" + std::string(1, character) + "'", index + 1);
}

// Used in parser
void ErrorHandler::validateOperatorExistence(const std::vector<Token> &tokens,
                                             std::size_t tokenIndex) {
  if (tokenIndex > 0) {
    TokenType previousType = tokens[tokenIndex - 1].type;

    // if previous is Number or RightParen
    if (previousType == TokenType::Number ||
        previousType == TokenType::RandomMax ||
        previousType == TokenType::RightParen) {
      throw CalculatorException(ErrorType::Syntax,
                                "tokens must be separated by operators",
                                tokens[tokenIndex].index + 1);
    }
  }
}

// Used in parser
void ErrorHandler::validateOperatorPlacement(const std::vector<Token> &tokens,
                                             std::size_t tokenIndex) {
  if (tokenIndex == 0) {
    throw CalculatorException(
        ErrorType::Syntax,
        "operator cannot appear at the beginning of the expression",
        tokens[tokenIndex].index + 1);
  }

  if (tokenIndex == tokens.size() - 1) {
    throw CalculatorException(
        ErrorType::Syntax,
        "operator cannot appear at the end of the expression",
        tokens[tokenIndex].index + 1);
  }

  TokenType previousType = tokens[tokenIndex - 1].type;

  // if previous is not Number and not RightParen
  if (previousType != TokenType::Number &&
      previousType != TokenType::RightParen) {
    throw CalculatorException(ErrorType::Syntax,
                              "unexpected operator placement",
                              tokens[tokenIndex].index + 1);
  }
}

// Used in parser
void ErrorHandler::validateClosingParenthesis(std::stack<Token> operators,
                                              std::size_t rightParenIndex) {
  while (!operators.empty() && operators.top().type != TokenType::LeftParen) {
    operators.pop();
  }
  if (operators.empty()) {
    throw CalculatorException(
        ErrorType::MismatchedParentheses,
        "closing parenthesis does not have a matching opening parenthesis",
        rightParenIndex + 1);
  }
}

// Used in parser
void ErrorHandler::validateOpeningParenthesis(
    std::stack<std::size_t> leftParenIndices) {
  while (!leftParenIndices.empty()) {
    throw CalculatorException(
        ErrorType::MismatchedParentheses,
        "opening parenthesis does not have a matching closing parenthesis",
        leftParenIndices.top() + 1);
  }
}

// Used in evaluator
void ErrorHandler::validatePostfixOperandCount(std::size_t valueCount,
                                               const Token &token) {
  if (valueCount < 2) {
    throw CalculatorException(ErrorType::Syntax,
                              "not enough operands for operator '" +
                                  token.value + "'",
                              token.index + 1);
  }
}

// Used in evaluator
void ErrorHandler::validateDivisionByZero(long double rightOperandValue,
                                          std::size_t rightOperandIndex) {
  if (rightOperandValue == 0.0) {
    throw CalculatorException(ErrorType::DivisionByZero,
                              "cannot divide by zero", rightOperandIndex + 1);
  }
}

void ErrorHandler::validateHistoryStream(bool streamOk) {
  if (!streamOk) {
    throw CalculatorException(ErrorType::IOError,
                              "failed to open history file");
  }
}
