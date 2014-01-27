#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "View.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
                   //public View
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

protected slots:
    void performSingleStep();
    void evaluateGeneration();
    void restart();
    void exit();

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
