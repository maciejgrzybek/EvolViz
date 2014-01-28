#include <memory>

#include <QGraphicsScene>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PointInitializationDialog.h"
#include "RandomInitializationDialog.h"

MainWindow::MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue,
                       QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      blockingQueue(blockingQueue),
      scene(new QGraphicsScene(0, 0, 50, 50))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(1, 1);

    connect(ui->actionPerform_single_step, SIGNAL(triggered(bool)), SLOT(performSingleStep()));
    connect(ui->actionEvaluate_generation, SIGNAL(triggered(bool)), SLOT(evaluateGeneration()));
    connect(ui->action_Restart, SIGNAL(triggered(bool)), SLOT(restart()));
    connect(ui->action_Exit, SIGNAL(triggered(bool)), SLOT(exit()));

    connect(ui->fitnessFunctionCommit, SIGNAL(clicked()), SLOT(fitnessFunctionChangeRequested()));
    connect(ui->initializationType, SIGNAL(activated(int)), SLOT(showInitializationPropertiesWindow(int)));
    connect(ui->initializationToolButton, SIGNAL(clicked()), SLOT(showInitializationPropertiesWindow()));
    connect(ui->reproductionFactorCommitButton, SIGNAL(clicked()), SLOT(reproductionFactorChangeRequested()));

    connect(this, SIGNAL(drawSnapshotSig(common::PopulationSnapshot)), SLOT(drawSnapshot(common::PopulationSnapshot)));
    connect(this, SIGNAL(drawFitnessFunctionSig(QString)), SLOT(drawFitnessFunction(QString)));

    initializationOptions.push_back(new PointInitializationDialog(this));
    initializationOptions.push_back(new RandomInitializationDialog(this));
}

void MainWindow::drawSnapshot(const common::PopulationSnapshot& snapshot)
{
    scene->clear();
    for (auto& item : snapshot.subjects)
        scene->addEllipse(item.x*10, item.y*10, 1, 1);
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

void MainWindow::reproductionFactoryChangeRequested()
{
    blockingQueue->push(common::MessagePtr(new common::ReproductionOptionsChangeRequestedMessage(ui->doubleSpinBox->value())));
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

void MainWindow::showInitializationPropertiesWindow()
{
    showInitializationPropertiesWindow(ui->initializationType->currentIndex());
}

void MainWindow::showInitializationPropertiesWindow(int chosenInitializationType)
{
    switch (chosenInitializationType)
    {
        case 0: // point
        {
            PointInitializationDialog* d = dynamic_cast<PointInitializationDialog*>(initializationOptions[0]);
            assert(d != nullptr);
            const int result = d->exec();
            if (result != QDialog::Accepted)
                break;
            auto opts = new common::InitializationOptionsChangeRequest(common::InitializationOptionsChangeRequest::Point);
            opts->x1 = d->getX();
            opts->y1 = d->getY();
            blockingQueue->push(common::MessagePtr(opts));
            break;
        }
        case 1: // random
        {
            RandomInitializationDialog* d = dynamic_cast<RandomInitializationDialog*>(initializationOptions[1]);
            assert(d != nullptr);
            const int result = d->exec();
            if (result != QDialog::Accepted)
                break;
            auto opts = new common::InitializationOptionsChangeRequest(common::InitializationOptionsChangeRequest::Random);
            opts->x1 = d->getXmin();
            opts->y1 = d->getYmin();
            opts->x2 = d->getXmax();
            opts->y2 = d->getYmax();
            blockingQueue->push(common::MessagePtr(opts));
            break;
        }
    }
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

void MainWindow::onExecutionAvailable()
{
    ui->actionPerform_single_step->setEnabled(true);
    ui->actionEvaluate_generation->setEnabled(true);
}

void MainWindow::onExecutionNoMoreAvailable()
{
    ui->actionChange_options->setEnabled(false);
    ui->actionEvaluate_generation->setEnabled(false);
}
