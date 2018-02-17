TEMPLATE = app
CONFIG += console c++11
QT += core gui

QMAKE_CXXFLAGS += -std=c++11 -O2 -march=native

SOURCES += main.cpp \
    observer.cpp \
    ray.cpp \
    test.cpp \
    vecteur.cpp \
    celestialBody.cpp \
    sphericalSource.cpp \
    gravitationalLense.cpp \
    GUI/imageManipulation.cpp \
    GUI/displaywindow.cpp \
    GUI/form.cpp \
    GUI/frameorientation.cpp \
    GUI/QScienceSpinBox.cpp

HEADERS += observer.h \
    vecteur.h \
    ray.h \
    test.h \
    celestialBody.h \
    sphericalSource.h \
    gravitationalLense.h \
    GUI/imageManipulation.h \
    task.h \
    GUI/displaywindow.h \
    GUI/form.h \
    GUI/frameorientation.h \
    GUI/QScienceSpinBox.h

FORMS += \
    GUI/form.ui
