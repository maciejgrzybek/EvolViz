#include <cassert>
#include <memory>

#include <QPainter>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PointInitializationDialog.h"
#include "RandomInitializationDialog.h"

#include "ConstMutationDialog.h"
#include "GaussMutationDialog.h"

#include "CrossOverOptionsDialog.h"
#include "QualityAvgCrossOverDialog.h"

#include "ModelOptions.h"

#include "FitnessFunctionCalculator.h"

class Image
{
public:
    Image(const QPixmap& pixmap, double width, double height)
        : image(pixmap),
          width(width),
          height(height)
    {}

    Image(const std::string& formula, double width, double height)
        : calculator(new common::FitnessFunctionCalculator(formula)),
          width(width),
          height(height)
    {}

    void prepare(const QRectF& crect)
    {
        assert(calculator); // FIXME not valid when default constructor used!

        const QRectF rect = crect.normalized();
        image = QPixmap(rect.width(), rect.height());
        QPainter painter;
        painter.begin(&image);

        const std::pair<double, double> minMax = getMinMaxOfFunction(width, height);

        const double widthFactor = width/rect.width();
        const double heightFactor = height/rect.height();

        for (int i = 0; i < rect.width(); ++i)
        {
            for (int j = 0; j < rect.height(); ++j)
            {
                const double value = (*calculator)(i * widthFactor, j * heightFactor);
                const double normalization = std::min(getNormalization(value, minMax), 1.0);
                assert(normalization >= 0.0 && normalization <= 1.0);

                painter.setPen(QPen(QColor(255 * normalization, 0, 0), 1));
                painter.drawPoint(i, j);
            }
        }

        painter.end();
    }

    void drawPoint(double x, double y, const QColor& color = QColor(Qt::yellow))
    {
        const double widthFactor = (double)width/image.width();
        const double heightFactor = (double)height/image.height();

        QPainter painter;
        painter.begin(&image);
        painter.setPen(QPen(color, 2));
        painter.drawPoint(x/widthFactor, y/heightFactor);
        painter.end();
    }

    QPixmap image;

private:
    double getNormalization(double value, std::pair<double, double> minMax) const
    {
        const double distance = minMax.second - minMax.first;
        const double v = value - minMax.first;
        if (distance == 0)
            return 1.0;
        const double result = std::max(std::min(v/distance, 1.0), 0.0);
        return result;
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
                const double value = (*calculator)(i, j);
                if (value < min)
                    min = value;
                if (value > max)
                    max = value;
            }
        }

        return std::make_pair(min, max);
    }

    std::unique_ptr<common::FitnessFunctionCalculator> calculator;
    double width;
    double height;
};

MainWindow::MainWindow(std::shared_ptr<Controller::BlockingQueue> blockingQueue, QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      blockingQueue(blockingQueue),
      image(nullptr),
      resizeNotifications(false)
{
    ui->setupUi(this);

    connect(ui->actionPerform_single_step, SIGNAL(triggered(bool)), SLOT(performSingleStep()));
    connect(ui->actionEvaluate_generation, SIGNAL(triggered(bool)), SLOT(evaluateGeneration()));
    connect(ui->action_Restart, SIGNAL(triggered(bool)), SLOT(restart()));
    connect(ui->action_Exit, SIGNAL(triggered(bool)), SLOT(exitRequest()));

    connect(ui->fitnessFunctionCommit, SIGNAL(clicked()), SLOT(fitnessFunctionChangeRequested()));
    connect(ui->initializationType, SIGNAL(currentIndexChanged(int)), SLOT(commitInitializationProperties(int)));
    connect(ui->initializationToolButton, SIGNAL(clicked()), SLOT(showInitializationPropertiesWindow()));
    connect(ui->reproductionFactorCommitButton, SIGNAL(clicked()), SLOT(reproductionFactorChangeRequested()));
    connect(ui->rangeCommitButton, SIGNAL(clicked()), SLOT(rangeOptionsChangeRequest()));
    connect(ui->selectionType, SIGNAL(currentIndexChanged(int)), SLOT(selectionTypeChangeRequest(int)));
    connect(ui->goalCommitButton, SIGNAL(clicked()), SLOT(goalChangeRequest()));
    connect(ui->mutationToolButton, SIGNAL(clicked()), SLOT(showMutationPropertiesWindow()));
    connect(ui->populationCommitButton, SIGNAL(clicked()), SLOT(populationSizeChangeRequest()));
    connect(ui->crossOverCommitButton, SIGNAL(clicked()), SLOT(crossOverChangeRequest()));
    connect(ui->crossOverToolButton, SIGNAL(clicked()), SLOT(showCrossOverProperties()));
    connect(ui->crossOverType, SIGNAL(activated(int)), SLOT(crossOverTypeChange(int)));

    connect(this, SIGNAL(drawSnapshotSig(common::PopulationSnapshot)), SLOT(drawSnapshot(common::PopulationSnapshot)));
    connect(this, SIGNAL(drawFitnessFunctionSig(QString, double, double)), SLOT(drawFitnessFunction(QString, double, double)));
    connect(this, SIGNAL(performExit()), SLOT(close()));

    initializationOptions.push_back(new PointInitializationDialog(this));
    initializationOptions.push_back(new RandomInitializationDialog(this));

    mutationOptions.push_back(new MutationOptionsDialog("Min", "Max", "Min", "Max", this));
    mutationOptions.push_back(new MutationOptionsDialog("Expected", "Variation", "Expected", "Variation", this));
    mutationOptions.push_back(new ConstMutationDialog(this));

    crossOverOptions.push_back(new QualityAvgCrossOverDialog(this));
    crossOverOptions.push_back(new MutationOptionsDialog("", "", "", "", this)); // TODO rename texts appropriately
    crossOverOptions.push_back(new CrossOverOptionsDialog(this, "X min", "X max", "Y min", "Y max", "min", "max"));
    crossOverOptions.push_back(new CrossOverOptionsDialog(this, "X min", "X max", "Y min", "Y max", "expected", "variation"));
    crossOverOptions.push_back(new QualityAvgCrossOverDialog(this));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   windowResized();
}

void MainWindow::drawSnapshot(const common::PopulationSnapshot& snapshot)
{
    delete image;
    image = new Image(background, width, height);

    common::PopulationSnapshot::Subject subject;
    subject.value = std::numeric_limits<double>::min();

    for (auto& item : snapshot.subjects)
    {
        image->drawPoint(item.x, item.y);
        if (item.value > subject.value)
            subject = item;
    }

    image->drawPoint(subject.x, subject.y, QColor(Qt::blue));

    ui->image->setPixmap(image->image);

    lastSnapshot = snapshot;
}

void MainWindow::drawFitnessFunction(const QString& formula, double width, double height)
{
    resizeNotifications = true;
    this->width = width;
    this->height = height;
    this->formula = formula;
    delete image;
    image = new Image(formula.toStdString(), width, height);
    image->prepare(QRectF(0, 0, ui->image->size().width(), ui->image->size().height()));

    background = image->image;
    drawSnapshot(lastSnapshot);

    ui->image->setPixmap(image->image);
}

void MainWindow::fitnessFunctionChangeRequested()
{
    const std::string formula = ui->fitnessFunctionLineEdit->text().toStdString();
    blockingQueue->push(common::MessagePtr(new common::FitnessFunctionChangeRequestedMessage(formula)));
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
    blockingQueue->push(common::MessagePtr(new common::RestartRequestedMessage));
}

void MainWindow::exitRequest()
{
    blockingQueue->push(common::MessagePtr(new common::ExitRequestedMessage));
}

void MainWindow::windowResized()
{
    if (resizeNotifications)
        drawFitnessFunction(formula, width, height);
}

void MainWindow::showInitializationPropertiesWindow()
{
    switch (ui->initializationType->currentIndex())
    {
        case 0: // point
        {
            PointInitializationDialog* d = dynamic_cast<PointInitializationDialog*>(initializationOptions[0]);
            assert(d != nullptr);
            const int result = d->exec();
            if (result != QDialog::Accepted)
                break;

            commitInitializationProperties(0);
            break;
        }
        case 1: // random
        {
            RandomInitializationDialog* d = dynamic_cast<RandomInitializationDialog*>(initializationOptions[1]);
            assert(d != nullptr);
            const int result = d->exec();
            if (result != QDialog::Accepted)
                break;

            commitInitializationProperties(1);
            break;
        }
    }
}

void MainWindow::commitInitializationProperties(int chosenInitializationType)
{
    switch (chosenInitializationType)
    {
        case 0: // point
        {
            PointInitializationDialog* d = dynamic_cast<PointInitializationDialog*>(initializationOptions[0]);
            assert(d != nullptr);
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

void MainWindow::reproductionFactorChangeRequested()
{
    common::MessagePtr msg(new common::ReproductionOptionsChangeRequestedMessage(ui->reproductionFactor->value()));
    blockingQueue->push(std::move(msg));
}

void MainWindow::rangeOptionsChangeRequest()
{
    std::shared_ptr<common::RangeAlignmentOptions> options;

    const double x_min = ui->rangeXMin->value();
    const double x_max = ui->rangeXMax->value();
    const double y_min = ui->rangeYMin->value();
    const double y_max = ui->rangeYMax->value();

    switch (ui->rangeComboBox->currentIndex())
    {
        case 0: // rolling
            options.reset(new common::RollingRangeAlignment(x_min, x_max, y_min, y_max));
            break;
        case 1: // mirroring
            options.reset(new common::MirroringRangeAlignment(x_min, x_max, y_min, y_max));
            break;
        case 2: // universal
            options.reset(new common::UniversalRandomReinitializationAlignment(x_min, x_max, y_min, y_max));
            break;
    }

    common::MessagePtr msg(new common::RangeOptionsChangeRequestedMessage(options));
    blockingQueue->push(std::move(msg));
}

void MainWindow::selectionTypeChangeRequest(int /*chosenSelectionType*/)
{
    std::shared_ptr<common::SelectionOptions> options;

    switch (ui->selectionType->currentIndex())
    {
        case 0: // elite
            options.reset(new common::EliteSelection);
            break;
        case 1: // lot
            options.reset(new common::LoterySelection);
            break;
        case 2: // tourn
            options.reset(new common::TournamentSelection);
            break;
        case 3: // roulette
            options.reset(new common::RouletteSelection(-2.0)); //FIXME
            break;
    }

    common::MessagePtr msg(new common::SelectionOptionsChangeRequestedMessage(options));
    blockingQueue->push(std::move(msg));
}

void MainWindow::goalChangeRequest()
{
    common::MessagePtr msg(new common::GoalChangeRequestedMessage(ui->goalValue->value()));
    blockingQueue->push(std::move(msg));
}

void MainWindow::mutationChangeRequest()
{
    std::shared_ptr<common::MutationOptions> options;

    const double factor = ui->mutationFactor->value();

    switch (ui->mutationType->currentIndex())
    {
        case 0: // universal
        {
            MutationOptionsDialog* dialog = dynamic_cast<MutationOptionsDialog*>(mutationOptions[1]);
            common::UniversalRandomOptions x(dialog->getX1(), dialog->getX2());
            common::UniversalRandomOptions y(dialog->getY1(), dialog->getY2());
            options.reset(new common::UniversalRandomMutation(factor, x, y));
            break;
        }
        case 1: // gauss
        {
            MutationOptionsDialog* dialog = dynamic_cast<MutationOptionsDialog*>(mutationOptions[1]);
            common::GaussRandomOptions x(dialog->getX1(), dialog->getX2());
            common::GaussRandomOptions y(dialog->getY1(), dialog->getY2());
            options.reset(new common::GaussRandomMutation(factor, x, y));
            break;
        }
        case 2: // const
            break;
    }

    common::MessagePtr msg(new common::MutationChangeRequestedMessage(options));
}

void MainWindow::showMutationPropertiesWindow()
{
    showMutationPropertiesWindow(ui->mutationType->currentIndex());
}

void MainWindow::showMutationPropertiesWindow(int chosenMutationType)
{
    const double factor = ui->mutationFactor->value();

    switch (chosenMutationType)
    {
        case 0: // universal
        {
            MutationOptionsDialog* dialog = dynamic_cast<MutationOptionsDialog*>(mutationOptions[0]);
            assert(dialog != nullptr);
            const int result = dialog->exec();
            if (result != QDialog::Accepted)
                break;

            common::UniversalRandomOptions x(dialog->getX1(), dialog->getX2());
            common::UniversalRandomOptions y(dialog->getY1(), dialog->getY2());
            std::shared_ptr<common::MutationOptions> options(new common::UniversalRandomMutation(factor, x, y));
            blockingQueue->push(common::MessagePtr(new common::MutationChangeRequestedMessage(options)));
            break;
        }
        case 1: // gauss
        {
            MutationOptionsDialog* dialog = dynamic_cast<MutationOptionsDialog*>(mutationOptions[1]);
            assert(dialog != nullptr);
            const int result = dialog->exec();
            if (result != QDialog::Accepted)
                break;

            common::GaussRandomOptions x(dialog->getX1(), dialog->getX2());
            common::GaussRandomOptions y(dialog->getY1(), dialog->getY2());
            std::shared_ptr<common::MutationOptions> options(new common::GaussRandomMutation(factor, x, y));
            blockingQueue->push(common::MessagePtr(new common::MutationChangeRequestedMessage(options)));
            break;
        }
        case 2: // const
        {
            ConstMutationDialog* dialog = dynamic_cast<ConstMutationDialog*>(mutationOptions[2]);
            assert(dialog != nullptr);
            const int result = dialog->exec();
            if (result != QDialog::Accepted)
                break;

            std::shared_ptr<common::MutationOptions> options(new common::ConstMutation(factor, dialog->getX(), dialog->getY()));
            blockingQueue->push(common::MessagePtr(new common::MutationChangeRequestedMessage(options)));
            break;
        }
    }
}

void MainWindow::populationSizeChangeRequest()
{
    common::MessagePtr msg(new common::PopulationSizeChangeRequestedMessage(ui->populationSize->value()));
    blockingQueue->push(std::move(msg));
}


void MainWindow::crossOverChangeRequest()
{
    const double factor = ui->crossOverFactor->value();

    switch (ui->crossOverType->currentIndex())
    {
        case 0: // quality avg
        {
            QualityAvgCrossOverDialog* dialog = dynamic_cast<QualityAvgCrossOverDialog*>(crossOverOptions[0]);
            assert(dialog != nullptr);
            const std::shared_ptr<common::CrossOverOptions> options(
                        new common::QualityAvgCrossOver(factor, dialog->getNormalizator()));

            common::MessagePtr message(new common::CrossOverChangeRequestedMessage(options));
            blockingQueue->push(std::move(message));
            break;
        }
        case 1: // const avg
        {
            MutationOptionsDialog* dialog = dynamic_cast<MutationOptionsDialog*>(crossOverOptions[1]);
            const double x[2] = { dialog->getX1(), dialog->getX2() };
            const double y[2] = { dialog->getY1(), dialog->getY2() };
            const std::shared_ptr<common::CrossOverOptions> options(new common::ConstAvgCrossOver(factor, x, y));

            common::MessagePtr message(new common::CrossOverChangeRequestedMessage(options));
            blockingQueue->push(std::move(message));
            break;
        }
        case 2: // universal random
        {
            CrossOverOptionsDialog* dialog
                    = dynamic_cast<CrossOverOptionsDialog*>(crossOverOptions[2]);
            assert(dialog != nullptr);
            break;
        }
        case 3: // gauss random
        {
            CrossOverOptionsDialog* dialog
                    = dynamic_cast<CrossOverOptionsDialog*>(crossOverOptions[3]);
            assert(dialog != nullptr);
            const common::GaussRandomOptions x[2]
                    = { common::GaussRandomOptions(dialog->getXmin().first,
                        dialog->getXmin().second),
                        common::GaussRandomOptions(dialog->getXmax().first,
                        dialog->getXmax().second)};

            const common::GaussRandomOptions y[2]
                    = { common::GaussRandomOptions(dialog->getYmin().first,
                        dialog->getYmin().second),
                        common::GaussRandomOptions(dialog->getYmax().first,
                        dialog->getYmax().second)};
            const std::shared_ptr<common::CrossOverOptions> options(new common::GaussRandomAvgCrossOver(factor, x, y));

            common::MessagePtr message(new common::CrossOverChangeRequestedMessage(options));
            blockingQueue->push(std::move(message));
            break;
        }
        case 4: // quality random fixed
        {
            QualityAvgCrossOverDialog* dialog
                    = dynamic_cast<QualityAvgCrossOverDialog*>(crossOverOptions[4]);
            assert(dialog != nullptr);

            const std::shared_ptr<common::CrossOverOptions> options(
                        new common::QualityRandomFixedCrossOver(factor, dialog->getNormalizator()));

            common::MessagePtr message(new common::CrossOverChangeRequestedMessage(options));
            blockingQueue->push(std::move(message));
            break;
        }
        case 5: // universal random fixed
        {
            const std::shared_ptr<common::CrossOverOptions> options(
                        new common::UniversalRandomFixedCrossOver(factor));
            common::MessagePtr message(new common::CrossOverChangeRequestedMessage(options));
            blockingQueue->push(std::move(message));
            break;
        }
    }
}

void MainWindow::showCrossOverProperties()
{
    switch (ui->crossOverType->currentIndex())
    {
        case 0: // quality avg
        case 1: // const avg
        case 2: // universal random
        case 3: // gauss random
        case 4: // quality random fixed
        {
            QDialog* dialog = crossOverOptions[ui->crossOverType->currentIndex()];
            assert(dialog != nullptr);
            const int result = dialog->exec();
            if (result != QDialog::Accepted)
                break;

            crossOverChangeRequest();
            break;
        }
        case 5: // universal random fixed
        {
            assert(false && "Option should be disabled but was not.");
        }
    }
}

void MainWindow::crossOverTypeChange(int chosenType)
{
    if (chosenType == 5) // universal random fixed
        ui->crossOverToolButton->setEnabled(false);
    else
        ui->crossOverToolButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
}

void MainWindow::exit()
{
    emit performExit();
}

void MainWindow::drawGraph(const common::PopulationSnapshot& snapshot)
{
    emit drawSnapshotSig(snapshot);
}

void MainWindow::changeFitnessFunction(const std::string& formula, double width, double height)
{
    emit drawFitnessFunctionSig(QString::fromStdString(formula), width, height);
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
