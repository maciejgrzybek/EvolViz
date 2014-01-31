#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T18:11:31
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EvolViz
TEMPLATE = app
INCLUDEPATH += ../gsl/include
INCLUDEPATH += ../mu/include
DEFINES += GSL_AVAILABLE
LIBS += -L../gsl/lib -lgsl
LIBS += -L../mu/lib -lmuparser

SOURCES += main.cpp\
    MainWindow.cpp \
    Alignator.cpp \
    Controller.cpp \
    Crosser.cpp \
    EvolFunctions.cpp \
    Evolution.cpp \
    FitnessFunctionCalculator.cpp \
    FitnessFunctioner.cpp \
    Initializer.cpp \
    Message.cpp \
    Model.cpp \
    ModelExample.cpp \
    ModelObserver.cpp \
    ModelOptions.cpp \
    Mutator.cpp \
    Population.cpp \
    Reproductor.cpp \
    Selector.cpp \
    View.cpp \
    PointInitializationDialog.cpp \
    RandomInitializationDialog.cpp \
    GaussMutationDialog.cpp \
    ConstMutationDialog.cpp \
    QualityAvgCrossOverDialog.cpp \
    CrossOverOptionsDialog.cpp \
    BackgroundDrawingThread.cpp \
    Image.cpp

HEADERS  += MainWindow.h \
    Alignator.h \
    atomic.h \
    BlockingQueue.hpp \
    Controller.h \
    Crosser.h \
    EvolFunctions.hpp \
    Evolution.h \
    FitnessFunctionCalculator.h \
    FitnessFunctioner.h \
    GraphDescription.h \
    Initializer.h \
    Message.h \
    Model.h \
    ModelExample.h \
    ModelObserver.h \
    ModelOptions.h \
    Mutator.h \
    Population.h \
    PopulationSnapshot.h \
    Reproductor.h \
    SafeQueue.hpp \
    Selector.h \
    View.h \
    Visitor.h \
    PointInitializationDialog.h \
    RandomInitializationDialog.h \
    GaussMutationDialog.h \
    ConstMutationDialog.h \
    QualityAvgCrossOverDialog.h \
    CrossOverOptionsDialog.h \
    ControllsState.h \
    BackgroundDrawingThread.h \
    Image.h

FORMS    += MainWindow.ui \
    PointInitializationDialog.ui \
    RandomInitializationDialog.ui \
    GaussMutationDialog.ui \
    ConstMutationDialog.ui \
    QualityAvgCrossOverDialog.ui \
    CrossOverOptionsDialog.ui
