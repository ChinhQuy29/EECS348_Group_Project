#include "history_manager.hpp"
#include "error_handler.hpp"

#include <QList>
#include <QString>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

/*
Description:
Implements a HistoryManager class that manages a history of calculator
operations, allowing saving expressions and their results to a file, retrieving
the most recent calculations, and clearing the stored history.

Input:
- expression (std::string): mathematical expression entered by the user
- result (std::string): evaluated result of the expression
- count (std::size_t): number of recent calculations to retrieve
- filename (std::string): name/path of the file used to store history data

Output:
- Writes formatted calculation entries to a file (std::ofstream)
  Format: "YYYY-MM-DD HH:MM:SS | expression = result"
- Returns a std::vector<std::string> containing the last 'count' calculations
- Clears all stored history when requested (file is truncated)
- Throws runtime_error if file operations fail

Constraints:
- expression and result are expected to be valid strings
- count must be a non-negative integer
- filename must refer to a valid file path accessible by the program

Algorithm:
1. Saving a calculation:
   - Open the history file in append mode, generate the current timestamp,
   format and write the timestamp, expression, and result to the file

2. Retrieving recent calculations:
   - Open the file for reading, read all non-empty lines into a vector,
   if total entries <= count, return all entries, otherwise,
   return only the last 'count' entries

3. Clearing history:
   - Open the file in truncate mode to erase all contents

4. Timestamp generation:
   - Get the current system time, convert it to local time in a thread-safe
manner, format it into a readable string using put_time().
*/


// Constructor that initializes the history manager with a filename for storing
// history
HistoryManager::HistoryManager(const std::string &filename)
    : filename(filename) {}

// Adds a new calculation (including all details) to the history file
void HistoryManager::saveCalculation(const std::string &input) {
  // Open the history file in append mode to avoid overwriting existing ones
  std::ofstream outFile(filename, std::ios::app);
  ErrorHandler::validateHistoryStream(static_cast<bool>(outFile));

  // Formatted entry: [timestamp] | expression = result
  outFile << getCurrentTimestamp() << " | " << input << '\n';
}

// Returns the last 'count' calculations from the history file
std::vector<std::string> HistoryManager::getCalculations() const {
  // Opens the history file for reading
  std::ifstream inFile(filename);

  // If the file cannot be opened, return empty vector (no history available)
  if (!inFile) {
    return {};
  }

  std::vector<std::string> allLines;
  std::string line;

  // Read file line by line
  while (std::getline(inFile, line)) {
    // Skip empty lines to avoid adding them to history list
    if (!line.empty()) {
      allLines.push_back(line);
    }
  }

  return allLines;
}

// Clears the entire history by opening the file in truncation mode
void HistoryManager::clearHistory() {
  // Open the history file in truncation mode
  std::ofstream outFile(filename, std::ios::trunc);
  ErrorHandler::validateHistoryStream(static_cast<bool>(outFile));
}

// Generates a timestamp in the format "YYYY-MM-DD HH:MM:SS" for the current
// local time
std::string HistoryManager::getCurrentTimestamp() const {
  // Gets current time as time_t
  std::time_t now = std::time(nullptr);
  // Struct to hold local time components
  std::tm localTime{};

// Thread-safe conversion of time_t to local time using platform-specific
// functions
#ifdef _WIN32 // Windows
  localtime_s(&localTime, &now);
#else // Linux/macOS
  localtime_r(&now, &localTime);
#endif

  // Converts struct tm to a formatted string
  std::ostringstream oss;
  oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}
