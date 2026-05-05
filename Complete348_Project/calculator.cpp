#include "calculator.h"
#include <QGridLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <cmath>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), storedValue(0)
{
    display = new QLineEdit("0");
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);
    display->setStyleSheet("font-size: 20px;");

    history = new QTextEdit();
    history->setReadOnly(true);
    history->setFixedWidth(150);

    QGridLayout *grid = new QGridLayout;

    grid->addWidget(display, 0, 0, 1, 5);
    grid->addWidget(history, 0, 5, 8, 1);

    QString buttons[7][5] = {
        {"", "d2","d4","d6","d8"},
        {"pi","d10","d12","d20","d100"},
        {"e","","(",")","/"},
        {"","7","8","9","*"},
        {"hstry","4","5","6","-"},
        {"del","1","2","3","+"},
        {"clr","0",".","=",""}
    };

    for(int r=0;r<7;r++){
        for(int c=0;c<5;c++){
            QString text = buttons[r][c];
            if(text == "") continue;

            QPushButton *btn = new QPushButton(text);
            btn->setFixedSize(60,40);

            // Colors
            if(text.startsWith("d"))
                btn->setStyleSheet("background:#f2d388;");
            else if(text[0].isDigit())
                btn->setStyleSheet("background:#a8c3a0;");
            else if(text=="clr" || text=="del" || text=="hstry")
                btn->setStyleSheet("background:#e07a7a;");
            else
                btn->setStyleSheet("background:#b0c4d4;");

            grid->addWidget(btn, r+1, c);

            // Connections
            if(text[0].isDigit() || text==".")
                connect(btn,&QPushButton::clicked,this,&Calculator::digitClicked);
            else if(text=="+"||text=="-"||text=="*"||text=="/")
                connect(btn,&QPushButton::clicked,this,&Calculator::operatorClicked);
            else if(text=="=")
                connect(btn,&QPushButton::clicked,this,&Calculator::equalsClicked);
            else if(text=="clr")
                connect(btn,&QPushButton::clicked,this,&Calculator::clearClicked);
            else if(text=="del")
                connect(btn,&QPushButton::clicked,this,&Calculator::deleteClicked);
            else if(text=="pi" || text=="e")
                connect(btn,&QPushButton::clicked,this,&Calculator::constantClicked);
            else if(text.startsWith("d"))
                connect(btn,&QPushButton::clicked,this,&Calculator::diceClicked);
        }
    }

    setLayout(grid);
    setWindowTitle("Dice Calculator");
}

// -------- Logic --------

void Calculator::digitClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(display->text()=="0")
        display->setText(btn->text());
    else
        display->setText(display->text()+btn->text());
}

void Calculator::operatorClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    storedValue = display->text().toDouble();
    pendingOp = btn->text();
    display->clear();
}

void Calculator::equalsClicked(){
    double value = display->text().toDouble();
    double result = 0;

    if(pendingOp=="+") result = storedValue + value;
    if(pendingOp=="-") result = storedValue - value;
    if(pendingOp=="*") result = storedValue * value;
    if(pendingOp=="/") result = storedValue / value;

    QString entry = QString("%1 %2 %3 = %4")
                        .arg(storedValue).arg(pendingOp).arg(value).arg(result);

    addToHistory(entry);
    display->setText(QString::number(result));
}

void Calculator::clearClicked(){
    display->setText("0");
}

void Calculator::deleteClicked(){
    QString t = display->text();
    t.chop(1);
    if(t.isEmpty()) t="0";
    display->setText(t);
}

void Calculator::constantClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn->text()=="pi")
        display->setText(QString::number(M_PI));
    else if(btn->text()=="e")
        display->setText(QString::number(M_E));
}

int Calculator::rollDice(int sides){
    return QRandomGenerator::global()->bounded(1, sides+1);
}

void Calculator::diceClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int sides = btn->text().mid(1).toInt();

    int result = rollDice(sides);
    display->setText(QString::number(result));

    addToHistory(QString("d%1 → %2").arg(sides).arg(result));
}

void Calculator::addToHistory(const QString &entry){
    history->append(entry);
}