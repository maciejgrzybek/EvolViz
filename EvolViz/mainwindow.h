#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Controller.h"
#include "View.h"

class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,
                   public View
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue,
                        QWidget* parent = 0);
    virtual ~MainWindow();

    virtual void drawGraph(const common::PopulationSnapshot& snapshot);
    virtual void changeFitnessFunction(const std::string& formula);

    virtual void onFunctionParsingCompleted();
    virtual void onFunctionParsingFailed();

    virtual void onExecutionAvailable();
    virtual void onExecutionNoMoreAvailable();

signals:
    void drawSnapshotSig(const common::PopulationSnapshot& snapshot);
    void drawFitnessFunctionSig(const QString& formula);

protected slots:
    void drawSnapshot(const common::PopulationSnapshot& snapshot);
    void drawFitnessFunction(const QString& formula);

    void fitnessFunctionChangeRequested();
    void reproductionFactoryChangeRequested();

    void performSingleStep();
    void evaluateGeneration();
    void restart();
    void exit();

    void showInitializationPropertiesWindow();
    void showInitializationPropertiesWindow(int chosenInitializationType);

private:
    Ui::MainWindow* ui;
    std::vector<QDialog*> initializationOptions;
    std::shared_ptr<Controller::BlockingQueue> blockingQueue;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
