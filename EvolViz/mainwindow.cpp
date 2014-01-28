#include <cassert>
#include <memory>

#include <QPainter>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PointInitializationDialog.h"
#include "RandomInitializationDialog.h"

#include "FitnessFunctionCalculator.h"

class SceneWithFunctionInBackground// : public QGraphicsScene
{
public:
    SceneWithFunctionInBackground(const std::string& formula)
        : //QGraphicsScene(),
          calculator(formula),
          formula(formula),
          width(width),
          height(height)
    {}

protected:
    virtual void drawBackground(QPainter* painter, const QRectF& crect)
    {
        if (backgroundImage.size().width() != crect.width() || backgroundImage.size().height() != crect.height())
            prepareBackground(crect);

        painter->drawImage(crect.x(), crect.y(), backgroundImage);
    }

private:
    void prepareBackground(const QRectF& crect)
    {
        const QRectF rect = crect.normalized();
        backgroundImage = QImage(rect.width(), rect.height(), QImage::Format_RGB32);
        QPainter painter;
        painter.begin(&backgroundImage);

        const std::pair<double, double> minMax = getMinMaxOfFunction(rect.width(), rect.height());

        const int weightFactor = rect.width()/width;
        const int heightFactor = rect.height()/height;

        for (int i = 0; i < rect.width(); ++i)
        {
            for (int j = 0; j < rect.height(); ++j)
            {
                const double value = calculator(i/weightFactor, j/heightFactor);
                const double normalization = getNormalization(value, minMax);

                painter.setPen(QPen(QColor(255 * normalization, 0, 0), 1));
                painter.drawPoint(i, j);
            }
        }

        painter.end();
    }

    double getNormalization(double value, std::pair<double, double> minMax) const
    {
        const double distance = minMax.second - minMax.first;
        const double v = value - minMax.first;
        return v/distance;
    }

    std::pair<double, double> getMinMaxOfFunction(double width, double height) const
    {
        assert(width > 0 && height > 0);

        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();

        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                const double value = calculator(i, j);
                if (value < min)
                    min = value;
                if (value > max)
                    max = value;
            }
        }

        return std::make_pair(min, max);
    }

    mutable common::FitnessFunctionCalculator calculator;
    std::string formula;
    QImage backgroundImage;
    int width;
    int height;
};

class Image
{
public:
    Image(const std::string& formula, int width, int height)
        : calculator(formula),
          width(width),
          height(height)
    {}

    void prepare(const QRectF& crect)
    {
        const QRectF rect = crect.normalized();
        image = QPixmap(rect.width(), rect.height());
        QPainter painter;
        painter.begin(&image);

        const std::pair<double, double> minMax = getMinMaxOfFunction(rect.width(), rect.height());

        const double widthFactor = width/rect.width();
        const double heightFactor = height/rect.height();

        for (int i = 0; i < rect.width(); ++i)
        {
            for (int j = 0; j < rect.height(); ++j)
            {
                const double value = calculator(i * widthFactor, j * heightFactor);
                const double normalization = getNormalization(value, minMax);

                painter.setPen(QPen(QColor(255 * normalization, 0, 0), 1));
                painter.drawPoint(i, j);
            }
        }

        painter.end();
    }

    void drawPoint(double x, double y)
    {
        const double widthFactor = (double)width/image.width();
        const double heightFactor = (double)height/image.height();

        QPainter painter;
        painter.begin(&image);
        painter.setPen(QPen(QColor(Qt::yellow), 2));
        painter.drawPoint(x/widthFactor, y/heightFactor);
        painter.end();
    }

    QPixmap image;

private:
    double getNormalization(double value, std::pair<double, double> minMax) const
    {
        const double distance = minMax.second - minMax.first;
        const double v = value - minMax.first;
        return v/distance;
    }

    std::pair<double, double> getMinMaxOfFunction(double width, double height) const
    {
        assert(width > 0 && height > 0);

        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();

        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                const double value = calculator(i, j);
                if (value < min)
                    min = value;
                if (value > max)
                    max = value;
            }
        }

        return std::make_pair(min, max);
    }

    mutable common::FitnessFunctionCalculator calculator;
    int height;
    int width;
};

MainWindow::MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue,
                       QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      blockingQueue(blockingQueue)
      //scene(new SceneWithFunctionInBackground("sin(x) + sin(y)", 5, 5))
{
    ui->setupUi(this);
    image = new Image("sin(x) + sin(y)", 5, 5);


//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->scale(1, 1);
//    ui->graphicsView->fitInView(0, 0, 5, 5);


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
    drawFitnessFunction("sin(x) + sin(y)");
    //scene->clear();
    for (auto& item : snapshot.subjects)
        image->drawPoint(item.x, item.y);
        //scene->addEllipse(item.x, item.y, 1, 1, QPen(QColor(Qt::yellow)));

    ui->image->setPixmap(image->image);
}

void MainWindow::drawFitnessFunction(const QString& formula)
{
    delete image;
    image = new Image(formula.toStdString(), 5, 5);
    image->prepare(QRectF(0, 0, ui->image->size().width(), ui->image->size().height()));

    ui->image->setPixmap(image->image);
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
