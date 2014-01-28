#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Controller.h"
#include "View.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,
                   public View
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue, QWidget* parent = nullptr);
    virtual ~MainWindow();

    virtual void drawGraph(const common::PopulationSnapshot& snapshot);
    virtual void changeFitnessFunction(const std::string& formula, double width, double height);

    virtual void onFunctionParsingCompleted();
    virtual void onFunctionParsingFailed();

    virtual void onExecutionAvailable();
    virtual void onExecutionNoMoreAvailable();

signals:
    void drawSnapshotSig(const common::PopulationSnapshot& snapshot);
    void drawFitnessFunctionSig(const QString& formula, double width, double height);

protected:
    virtual void resizeEvent(QResizeEvent* event)
    {
       QMainWindow::resizeEvent(event);
       windowResized();
    }

protected slots:
    void drawSnapshot(const common::PopulationSnapshot& snapshot);
    void drawFitnessFunction(const QString& formula, double width, double height);

    void fitnessFunctionChangeRequested();
    void reproductionFactoryChangeRequested();

    void performSingleStep();
    void evaluateGeneration();
    void restart();
    void exit();

    void windowResized();

    void showInitializationPropertiesWindow();
    void showInitializationPropertiesWindow(int chosenInitializationType);
    void rangeOptionsChangeRequest();

private:
    Ui::MainWindow* ui;
    std::vector<QDialog*> initializationOptions;
    std::shared_ptr<Controller::BlockingQueue> blockingQueue;
    class Image* image;
    common::PopulationSnapshot lastSnapshot;
    QPixmap background;
    double width;
    double height;
    QString formula;
    bool resizeNotifications;
};

#endif // MAINWINDOW_H
