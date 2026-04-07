#include <iostream>
#include "calculator_engine.h"

int main() {
    CalculatorEngine engine;

    try {
        std::cout << engine.evaluate("3 + 4 * 2") << '\n';
        std::cout << engine.evaluate("(1 + 2) * 5") << '\n';
        std::cout << engine.evaluate("((2 + 3) * (4 + (5 * 6)))") << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}