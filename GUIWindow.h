#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class GUIWindow;
}

class GUIWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUIWindow(QWidget *parent = 0);
    ~GUIWindow();

private:
    Ui::GUIWindow *ui;
};

#endif // MAINWINDOW_H
