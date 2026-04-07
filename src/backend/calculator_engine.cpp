#include "../include/calculator_engine.h"

#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/evaluator.h"

double CalculatorEngine::evaluate(const std::string& expression) const {
    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;

    std::vector<Token> tokens = tokenizer.tokenize(expression);
    std::vector<Token> postfix = parser.toPostfix(tokens);
    return evaluator.evaluatePostfix(postfix);
}