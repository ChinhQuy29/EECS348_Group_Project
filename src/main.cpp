#include <iostream>
#include <string>
#include <vector>

#include "../include/calculator_engine.hpp"
#include "../include/error_handler.hpp"

int main() {
    CalculatorEngine engine;
    std::string input;

    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Calculate expression\n";
        std::cout << "2. View last 10 calculations\n";
        std::cout << "3. Clear history\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";

        std::getline(std::cin, input);

        if (input == "1") {
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
        }
        else if (input == "2") {
            std::vector<std::string> history = engine.getHistory(10);

            if (history.empty()) {
                std::cout << "No calculation history found.\n";
            } else {
                std::cout << "\nLast 10 calculations:\n";
                for (const std::string& entry : history) {
                    std::cout << entry << '\n';
                }
            }
        }
        else if (input == "3") {
            try {
                engine.clearHistory();
                std::cout << "History cleared.\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << '\n';
            }
        }
        else if (input == "4") {
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}