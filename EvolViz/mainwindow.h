#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Controller.h"
#include "View.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
                   //public View
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue,
                        QWidget* parent = 0);
    virtual ~MainWindow();

protected slots:
    void performSingleStep();
    void evaluateGeneration();
    void restart();
    void exit();

    void showInitializationPropertiesWindow(int choosenInitializationType);

private:
    Ui::MainWindow* ui;
    std::shared_ptr<Controller::BlockingQueue> blockingQueue;
};

#endif // MAINWINDOW_H
