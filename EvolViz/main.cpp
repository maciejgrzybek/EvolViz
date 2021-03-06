#include <memory>
#include <thread>

#include <QApplication>

#include "ControllsState.h"
#include "Controller.h"
#include "MainWindow.h"

Q_DECLARE_METATYPE(common::PopulationSnapshot)
Q_DECLARE_METATYPE(common::ControllsState)
Q_DECLARE_METATYPE(common::PopulationSnapshot::Subject)

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<common::PopulationSnapshot>("PopulationSnapshot");
    qRegisterMetaType<common::ControllsState>("ControllsState");
    qRegisterMetaType<common::PopulationSnapshot::Subject>("Subject");
    const std::shared_ptr<Controller::BlockingQueue> bq = std::make_shared<Controller::BlockingQueue>();
    MainWindow w(bq);

    const std::shared_ptr<model::Model> m = std::make_shared<model::Model>();

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
