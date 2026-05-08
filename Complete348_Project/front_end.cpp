#include "front_end.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "history_manager.hpp"
#include "error_handler.hpp"

#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSizePolicy>

Tokenizer tokenizer;
Parser parser;
Evaluator evaluator;
HistoryManager historyManager;

// ----------------------- Calculator page -----------------------
Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    display = new QLineEdit("");
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);
    display->setStyleSheet("font-size: 20px;");

    sessionHistory = new QTextEdit();
    sessionHistory->setReadOnly(true);
    sessionHistory->setFixedWidth(150);

    QGridLayout *grid = new QGridLayout;

    grid->addWidget(display, 0, 0, 1, 5);
    grid->addWidget(sessionHistory, 0, 5, 8, 1);

    QString buttons[7][5] = {
        {QString(""),        QString("d2"),  QString("d4"),  QString("d6"),  QString("d8")},
        {QString(u'π'),      QString("d10"), QString("d12"), QString("d20"), QString("d100")},
        {QString('e'),       QString('('),    QString(')'),   QString('%'),   QString('^')},
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
            if(text[0].isDigit() || text == QString('.') || text == QString('+') || text == QString('-') || text == QString(u'×') || text == QString(u'÷') || text == QString('^') || text == QString('%') || text == QString(u'π') || text == QString('e') || text == QString('(') || text == QString(')'))
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
    setWindowTitle("CalcTTRPG - Calculator");
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
    if (qExpression.isEmpty()) return;

    const std::string expression = qstos(qExpression);

    try {
        const std::vector<Token> tokens = tokenizer.tokenize(expression);
        const std::vector<Token> postfix = parser.toPostfix(tokens);
        const long double result = evaluator.evaluatePostfix(postfix);

        QString qEquation = QString("%1 = %2").arg(qExpression).arg((double)result);

        addToHistory(qEquation);

        display->setText(QString::number(double(result)));

    } catch (const CalculatorException& e) {
        const QStringView before = QStringView(qExpression).first(e.getPosition()-1);
        const QString middle = QString("<b style='color:red;'>%1</b>").arg(qExpression[e.getPosition()-1]);
        const QStringView after = QStringView(qExpression).sliced(e.getPosition());
        const QStringView newExpression = before + middle + after;
        const QString emphasizedError = QString("%1 <i style='color:gray;'>%2</i>").arg(newExpression).arg(e.what());

        addToHistory(emphasizedError);

        display->setText("Error");
    }

}

void Calculator::historyClicked(){
    QStackedWidget* window = qobject_cast<QStackedWidget*>(parentWidget());
    if (!window) return;

    if (auto *history = qobject_cast<History*>(window->widget(1))) {
        history->reloadHistory();
    }

    window->setCurrentIndex(1);
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
    int sides = btn->text().sliced(1).toInt();

    display->setText(display->text()+QChar(u'①' - 1 + sides));
}

void Calculator::addToHistory(const QString &entry){
    sessionHistory->append(entry);
    historyManager.saveCalculation(entry.toStdString());
}

// ----------------------- History page -----------------------
History::History(QWidget *parent)
    : QWidget(parent)
{
    historyDisplay = new QTextEdit();
    historyDisplay->setReadOnly(true);
    historyDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout *grid = new QGridLayout;

    grid->addWidget(historyDisplay, 0, 1, 8, 8);
    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);
    reloadHistory();

    QString buttons[7] = {
        QString(""),
        QString(""),
        QString(""),
        QString(""),
        QString("Return"),
        QString(""),
        QString("Clear")
    };

    for(int r = 0; r < 7; r++){
        QString text = buttons[r];
        if(text == "") continue;

        QPushButton *btn = new QPushButton(text);
        btn->setFixedSize(60,40);

        // Color
        btn->setStyleSheet("background:#e07a7a;");

        grid->addWidget(btn, r+1, 0);

        // Connections
        if(text == QString("Return"))
            connect(btn,&QPushButton::clicked,this,&History::returnClicked);
        else if(text == QString("Clear"))
            connect(btn,&QPushButton::clicked,this,&History::clearClicked);
    }

    setLayout(grid);
    setWindowTitle("CalcTTRPG - History");
}

void History::clearClicked(){
    historyManager.clearHistory();
    historyDisplay->clear();
}

void History::reloadHistory(){
    const std::vector<std::string> calculations = historyManager.getCalculations();
    QString data;
    for (const std::string& entry : calculations) {
        data += QString::fromStdString(entry);
        data += '\n';
    }
    historyDisplay->setText(data);
}

void History::returnClicked(){
    QStackedWidget* window = qobject_cast<QStackedWidget*>(parentWidget());
    window->setCurrentIndex(0);
}
