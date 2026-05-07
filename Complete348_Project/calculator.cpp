#include "calculator.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "history_manager.hpp"
#include "error_handler.hpp"

#include <QGridLayout>
#include <QPushButton>

Tokenizer tokenizer;
Parser parser;
Evaluator evaluator;
HistoryManager historyManager;

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), storedValue(0)
{
    display = new QLineEdit("");
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
        {QString(""),        QString("d2"),  QString("d4"),  QString("d6"),  QString("d8")},
        {QString(u'π'),      QString("d10"), QString("d12"), QString("d20"), QString("d100")},
        {QString('e'),       QString(""),    QString('('),   QString(')'),   QString('^')},
        {QString(""),        QString('7'),   QString('8'),   QString('9'),   QString(u'÷')},
        {QString("History"), QString('4'),   QString('5'),   QString('6'),   QString(u'×')},
        {QString("Delete"),  QString('1'),   QString('2'),   QString('3'),   QString('-')},
        {QString("Clear"),   QString('0'),   QString('.'),   QString('='),   QString('+')}
    };

    for(int r = 0; r < 7; r++){
        for(int c = 0; c < 5; c++){
            QString text = buttons[r][c];
            if(text == "") continue;

            QPushButton *btn = new QPushButton(text);
            btn->setFixedSize(60,40);

            // Colors
            if(text[0] == 'd')
                btn->setStyleSheet("background:#f2d388;");
            else if(text[0].isDigit())
                btn->setStyleSheet("background:#a8c3a0;");
            else if(text == QString("Clear") || text == QString("Delete") || text == QString("History"))
                btn->setStyleSheet("background:#e07a7a;");
            else
                btn->setStyleSheet("background:#b0c4d4;");

            grid->addWidget(btn, r+1, c);

            // Connections
            if(text[0].isDigit() || text == QString('.') || text == QString('+') || text == QString('-') || text == QString(u'×') || text == QString(u'÷') || text == QString('^') || text == QString(u'π') || text == QString('e') || text == QString('(') || text == QString(')'))
                connect(btn,&QPushButton::clicked,this,&Calculator::literalClicked);
            else if(text == QString('='))
                connect(btn,&QPushButton::clicked,this,&Calculator::equalsClicked);
            else if(text[0] == QChar('d'))
                connect(btn,&QPushButton::clicked,this,&Calculator::diceClicked);
            else if(text == QString("History"))
                connect(btn,&QPushButton::clicked,this,&Calculator::historyClicked);
            else if(text == QString("Delete"))
                connect(btn,&QPushButton::clicked,this,&Calculator::deleteClicked);
            else if(text == QString("Clear"))
                connect(btn,&QPushButton::clicked,this,&Calculator::clearClicked);
        }
    }

    setLayout(grid);
    setWindowTitle("Dice Calculator");
}

std::string qstos(QString qs) {
    std::string ret;
    for (qsizetype i = 0; i < qs.length(); ++i) {
        QChar c = qs[i];
        if (c == QChar(u'π')) {
            ret += 'p';
        } else if (c == QChar(u'÷')) {
            ret += '/';
        } else if (c == QChar(u'×')) {
            ret += '*';
        } else if (u'①' <= c && c <= u'Ⓝ') {
            ret += 'D' + std::to_string(c.unicode() - (u'①' - 1));
        } else {
            ret += c.unicode();
        }
    }
    return ret;
}

// -------- Logic --------

void Calculator::literalClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    display->setText(display->text()+btn->text());
}

void Calculator::equalsClicked(){
    const QString qExpression = display->text();
    const std::string expression = qstos(qExpression);
    try {
        const std::vector<Token> tokens = tokenizer.tokenize(expression);
        const std::vector<Token> postfix = parser.toPostfix(tokens);
        const long double result = evaluator.evaluatePostfix(postfix);

        QString qEquation = QString("%1 = %2").arg(qExpression).arg(result);

        addToHistory(qEquation);
        display->setText(QString::number(double(result)));
    } catch (const CalculatorException& e) {
        display->setText(e.what());
    }

}

void Calculator::historyClicked(){

}

void Calculator::deleteClicked(){
    QString t = display->text();

    if(!t.isEmpty()) {
        t.chop(1);
    }
    display->setText(t);
}

void Calculator::clearClicked(){
    display->setText("");
}

void Calculator::diceClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int sides = btn->text().mid(1).toInt();

    display->setText(display->text()+QChar(u'①' - 1 + sides));
}

void Calculator::addToHistory(const QString &entry){
    history->append(entry);
}
