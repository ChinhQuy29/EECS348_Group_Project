#pragma once

#include <string>
#include <vector>
#include <QString>
#include <QList>

class HistoryManager {
public:
    explicit HistoryManager(const std::string& filename = "calculation_history.txt");

    void saveCalculation(const std::string& expression, const std::string& result);
    std::vector<std::string> getLastCalculations(std::size_t count = 10) const;
    void clearHistory();
    void addEntry(const QString &entry);
    void addError(const QString &entry);

private:
    QList<QString> sessionHistory;

    std::string filename;

    std::string getCurrentTimestamp() const;
};