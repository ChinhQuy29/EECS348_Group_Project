#include "front_end.hpp"

#include <QApplication>
#include <QStackedWidget>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QStackedWidget *window = new QStackedWidget;
  QWidget *calculatorWidget = new Calculator;
  QWidget *historyWidget = new History;

  window->addWidget(calculatorWidget);
  window->addWidget(historyWidget);
  window->setCurrentIndex(0);
  window->show();
  return app.exec();
}
