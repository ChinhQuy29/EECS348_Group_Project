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
    QTextEdit *sessionHistory;

    void addToHistory(const QString &entry);

private slots:
    void literalClicked();
    void equalsClicked();
    void historyClicked();
    void deleteClicked();
    void clearClicked();
    void diceClicked();
};

class History : public QWidget
{
    Q_OBJECT

public:
    History(QWidget *parent = nullptr);
    void reloadHistory();

private:
    QTextEdit *historyDisplay;

private slots:
    void returnClicked();
    void clearClicked();
};

#endif
