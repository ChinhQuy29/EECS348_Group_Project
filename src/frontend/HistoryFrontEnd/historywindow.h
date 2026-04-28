#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class HistoryWindow;
}
QT_END_NAMESPACE

class HistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = nullptr);
    ~HistoryWindow() override;

private:
    Ui::HistoryWindow *ui;
};
#endif // HISTORYWINDOW_H
