#include "../../include/calculator_engine.hpp"

#include "../../include/tokenizer.hpp"
#include "../../include/parser.hpp"
#include "../../include/evaluator.hpp"

double CalculatorEngine::evaluate(const std::string& expression) const {
    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;

    std::vector<Token> tokens = tokenizer.tokenize(expression);
    std::vector<Token> postfix = parser.toPostfix(tokens);
    return evaluator.evaluatePostfix(postfix);
}