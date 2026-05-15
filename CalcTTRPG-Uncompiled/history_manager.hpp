#pragma once

#include <QList>
#include <QString>
#include <string>
#include <vector>

class HistoryManager {
public:
  explicit HistoryManager(
      const std::string &filename = "calculation_history.txt");

  void saveCalculation(const std::string &expression);
  std::vector<std::string> getCalculations() const;
  void clearHistory();

private:
  std::string filename;

  std::string getCurrentTimestamp() const;
};
