#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private:
    QLineEdit *display;
    QTextEdit *history;

    double storedValue;
    QString pendingOp;

    void addToHistory(const QString &entry);
    int rollDice(int sides);

private slots:
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();
    void deleteClicked();
    void constantClicked();
    void diceClicked();
};

#endif