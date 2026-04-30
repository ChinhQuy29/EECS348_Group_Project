#include "../../include/calculator_engine.hpp"

#include "../../include/tokenizer.hpp"
#include "../../include/parser.hpp"
#include "../../include/evaluator.hpp"
#include "../../include/error_handler.hpp"
#include "../../include/history_manager.hpp"

#include <vector>
#include <sstream>

double CalculatorEngine::evaluate(const std::string& expression) const {
    ErrorHandler::validateExpression(expression);

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