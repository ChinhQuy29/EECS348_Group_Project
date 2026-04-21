#include "../../include/calculator_engine.hpp"

#include "../../include/tokenizer.hpp"
#include "../../include/parser.hpp"
#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"

#include <cctype>
#include <vector>

double CalculatorEngine::evaluate(const std::string& expression) const {
    bool onlyWhitespace = true;
    for (char c : expression) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            onlyWhitespace = false;
            break;
        }
    }

    if (expression.empty() || onlyWhitespace) {
        throw CalculatorException(
            ErrorType::EmptyExpression,
            "input expression is empty"
        );
    }

    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;

    std::vector<Token> tokens = tokenizer.tokenize(expression);
    std::vector<Token> postfix = parser.toPostfix(tokens);
    return evaluator.evaluatePostfix(postfix);
}