#include "../include/calculator_engine.hpp"

// We use the EXPORT macro so the UI can be used if this is a shared library
class CALCULATORZ_FRONTEND_EXPORT Calculator : public QWidget {
    Q_OBJECT

private:
    QLineEdit *display;
    QPushButton *createButton(const QString &text, const char *member, const QString &style);

    CalculatorEngine engine;
};

