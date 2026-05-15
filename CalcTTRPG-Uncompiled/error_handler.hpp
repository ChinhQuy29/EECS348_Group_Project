#pragma once

#include <exception>
#include <stack>
#include <string>
#include <string_view>

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

class CalculatorException
    : public std::exception { // Inherit from standard exception class
public:
  CalculatorException(ErrorType type, std::string_view message,
                      std::size_t position = 0);

  const char *
  what() const noexcept override; // Virtual function defined in parent
  ErrorType getType() const;
  std::size_t getPosition() const;

private:
  ErrorType type;
  std::string message;
  std::size_t position;

  static std::string formatError(ErrorType type, std::string_view details,
                                 std::size_t position = 0);
};

class ErrorHandler {
public:
  static void validateExpression(std::string_view expression);
  static void validateUnaryOperation(std::string_view expression,
                                     std::size_t nextIndex);
  static void validateDecimalPoint(bool hasDecimalPoint, std::size_t index);
  static void validateCompletedNumber(std::string_view number,
                                      std::size_t index);
  static void validateCharacter(char character, std::size_t index);
  static void validateOperatorExistence(const std::vector<Token> &tokens,
                                        std::size_t tokenIndex);
  static void validateOperatorPlacement(const std::vector<Token> &tokens,
                                        std::size_t tokenIndex);
  static void validateClosingParenthesis(std::stack<Token> operators,
                                         std::size_t rightParenIndex);
  static void
  validateOpeningParenthesis(std::stack<std::size_t> leftParenIndices);
  static void validatePostfixOperandCount(std::size_t valueCount,
                                          const Token &token);
  static void validateDivisionByZero(long double rightOperandValue,
                                     std::size_t rightOperandIndex);
  static void validateHistoryStream(bool streamOk);
};