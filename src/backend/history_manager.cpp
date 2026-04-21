#include "../../include/history_manager.hpp"

#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

HistoryManager::HistoryManager(const std::string& filename)
    : filename(filename) {}

void HistoryManager::saveCalculation(const std::string& expression, const std::string& result) {
    std::ofstream outFile(filename, std::ios::app);

    if (!outFile) {
        throw std::runtime_error("Failed to open history file for writing");
    }

    outFile << getCurrentTimestamp()
            << " | "
            << expression
            << " = "
            << result
            << '\n';
}

std::vector<std::string> HistoryManager::getLastCalculations(std::size_t count) const {
    std::ifstream inFile(filename);

    if (!inFile) {
        return {};
    }

    std::vector<std::string> allLines;
    std::string line;

    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            allLines.push_back(line);
        }
    }

    if (allLines.size() <= count) {
        return allLines;
    }

    return std::vector<std::string>(allLines.end() - count, allLines.end());
}

void HistoryManager::clearHistory() {
    std::ofstream outFile(filename, std::ios::trunc);

    if (!outFile) {
        throw std::runtime_error("Failed to clear history file");
    }
}

std::string HistoryManager::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}