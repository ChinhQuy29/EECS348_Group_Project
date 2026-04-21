#include "historywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HistoryWindow w;
    w.show();
    return QCoreApplication::exec();
}
