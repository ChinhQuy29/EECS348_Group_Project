#include "../../include/calculator_engine.hpp"

#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "history_manager.hpp"

#include <cctype>
#include <vector>
#include <sstream>

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
    HistoryManager historyManager;

    std::vector<Token> tokens = tokenizer.tokenize(expression);
    std::vector<Token> postfix = parser.toPostfix(tokens);
    double result = evaluator.evaluatePostfix(postfix);

    std::ostringstream oss;
    oss << result;

    historyManager.saveCalculation(expression, oss.str());

    return result;
}

std::vector<std::string> CalculatorEngine::getHistory(std::size_t count) const {
    HistoryManager historyManager;
    return historyManager.getLastCalculations(count);
}

void CalculatorEngine::clearHistory() const {
    HistoryManager historyManager;
    historyManager.clearHistory();
}