#include <memory>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue,
                       QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      blockingQueue(blockingQueue)
{
    ui->setupUi(this);

    connect(ui->actionPerform_single_step, SIGNAL(triggered(bool)), SLOT(performSingleStep()));
    connect(ui->actionEvaluate_generation, SIGNAL(triggered(bool)), SLOT(evaluateGeneration()));
    connect(ui->action_Restart, SIGNAL(triggered(bool)), SLOT(restart()));
    connect(ui->action_Exit, SIGNAL(triggered(bool)), SLOT(exit()));

    connect(ui->fitnessFunctionCommit, SIGNAL(clicked()), SLOT(fitnessFunctionChangeRequested()));
    connect(ui->initializationType, SIGNAL(activated(int)), SLOT(showInitializationPropertiesWindow(int)));

    connect(this, SIGNAL(drawSnapshotSig(common::PopulationSnapshot)), SLOT(drawSnapshot(common::PopulationSnapshot)));
    connect(this, SIGNAL(drawFitnessFunctionSig(QString)), SLOT(drawFitnessFunction(QString)));
}

void MainWindow::drawSnapshot(const common::PopulationSnapshot& snapshot)
{
    // TODO
    // draw points from snapshot on graphicsView
}

void MainWindow::drawFitnessFunction(const QString& formula)
{
    // TODO:
    // parse formula and draw it
}

void MainWindow::fitnessFunctionChangeRequested()
{
    blockingQueue->push(common::MessagePtr(new common::FitnessFunctionChangeRequestedMessage(ui->fitnessFunctionLineEdit->text().toStdString())));
}

void MainWindow::performSingleStep()
{
    blockingQueue->push(common::MessagePtr(new common::PerformSingleStepMessage));
}

void MainWindow::evaluateGeneration()
{
    blockingQueue->push(common::MessagePtr(new common::EvaluateGenerationMessage));
}

void MainWindow::restart()
{
    blockingQueue->push(common::MessagePtr(new common::StopRequestedMessage));
    blockingQueue->push(common::MessagePtr(new common::StartRequestedMessage));
}

void MainWindow::exit()
{
    blockingQueue->push(common::MessagePtr(new common::StopRequestedMessage));
}

void MainWindow::showInitializationPropertiesWindow(int choosenInitializationType)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGraph(const common::PopulationSnapshot& snapshot)
{
    emit drawSnapshotSig(snapshot);
}

void MainWindow::changeFitnessFunction(const std::string& formula)
{
    emit drawFitnessFunctionSig(QString::fromStdString(formula));
}

void MainWindow::onFunctionParsingCompleted()
{

}

void MainWindow::onFunctionParsingFailed()
{

}