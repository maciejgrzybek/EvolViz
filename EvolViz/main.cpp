#include <memory>
#include <thread>

#include <QApplication>

#include "Controller.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    const std::shared_ptr<Controller::BlockingQueue> bq = std::make_shared<Controller::BlockingQueue>();
    MainWindow w(bq);

    const std::shared_ptr<model::Model> m = std::make_shared<model::Model>();
    Controller c(bq, m);
    std::thread t(std::ref(c));

    w.show();

    const int exitCode = a.exec();
    c.asyncStop();
    t.join();

    return exitCode;
}
