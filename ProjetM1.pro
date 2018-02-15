TEMPLATE = app
CONFIG += console c++11
QT += core
#QT += gui

QMAKE_CXXFLAGS += -std=c++11 -O2 -march=native

SOURCES += main.cpp \
    observer.cpp \
    ray.cpp \
    test.cpp \
    vecteur.cpp \
    celestialBody.cpp \
    sphericalSource.cpp \
    gravitationalLense.cpp \
    GUI/imageManipulation.cpp

HEADERS += observer.h \
    vecteur.h \
    ray.h \
    test.h \
    celestialBody.h \
    sphericalSource.h \
    gravitationalLense.h \
    GUI/imageManipulation.h \
    task.h
