#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionPerform_single_step, SIGNAL(triggered(bool)), SLOT(performSingleStep()));
    connect(ui->actionEvaluate_generation, SIGNAL(triggered(bool)), SLOT(evaluateGeneration()));
    connect(ui->action_Restart, SIGNAL(triggered(bool)), SLOT(restart()));
    connect(ui->action_Exit, SIGNAL(triggered(bool)), SLOT(exit()));
}

void MainWindow::performSingleStep()
{

}

void MainWindow::evaluateGeneration()
{

}

void MainWindow::restart()
{

}

void MainWindow::exit()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
