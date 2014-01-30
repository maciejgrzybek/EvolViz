#include <memory>
#include <thread>

#include <QApplication>

#include "Controller.h"
#include "MainWindow.h"

Q_DECLARE_METATYPE(common::PopulationSnapshot)

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<common::PopulationSnapshot>("PopulationSnapshot");
    const std::shared_ptr<Controller::BlockingQueue> bq = std::make_shared<Controller::BlockingQueue>();
    MainWindow w(bq);

    const std::shared_ptr<model::Model> m = std::make_shared<model::Model>();

    m->setFitnessFunction("sin(x) + sin(y)");
    m->setInitializationOptions(common::RandomInitialization(0, 5, 0, 5));
    m->setReproductionOptions(common::ReproductionOptions(2.0));
    m->setMutationOptions(common::GaussRandomMutation(0.25, common::GaussRandomOptions(0.0, 0.3), common::GaussRandomOptions(0.0, 0.3)));
    m->setCrossOverOptions(common::QualityAvgCrossOver(1.0, -2.0));
    m->setRangeOptions(common::MirroringRangeAlignment(0, 5, 0, 5));
    m->setSelectionType(common::EliteSelection());
    m->setPopulationSize(1000);
    m->setGoalValue(2);

    Controller c(bq, m, w);
    m->addObserver(&c);
    std::thread modelThread(std::ref(*m)); // TODO should be copy of shared_ptr
    std::thread controllerThread(std::ref(c));

    w.show();

    const int exitCode = a.exec();
    m->doExit();
    c.asyncStop();

    modelThread.join();
    controllerThread.join();

    return exitCode;
}
