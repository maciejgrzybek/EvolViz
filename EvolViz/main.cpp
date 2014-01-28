#include <memory>
#include <thread>

#include <QApplication>

#include "Controller.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<common::PopulationSnapshot>("PopulationSnapshot");
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
