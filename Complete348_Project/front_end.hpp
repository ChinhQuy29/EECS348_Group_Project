#ifndef FRONT_END_H
#define FRONT_END_H

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
    void literalClicked();
    void equalsClicked();
    void historyClicked();
    void deleteClicked();
    void clearClicked();
    void diceClicked();
};

#endif
