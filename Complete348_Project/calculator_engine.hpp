#pragma once

#include <string>
#include <vector>

class CalculatorEngine {
public:
    double evaluate(const std::string& expression) const;
    std::vector<std::string> getHistory(std::size_t count = 10) const;
    void clearHistory() const;
};