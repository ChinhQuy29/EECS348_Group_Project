#include <iostream>
#include <string>

#include "../include/calculator_engine.hpp"
#include "../include/error_handler.hpp"

int main() {
    CalculatorEngine engine;
    std::string expression;

    std::cout << "Enter expression: ";
    std::getline(std::cin, expression);

    try {
        double result = engine.evaluate(expression);
        std::cout << "Result: " << result << '\n';
    }
    catch (const CalculatorException& e) {
        std::cout << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << '\n';
    }

    return 0;
}
