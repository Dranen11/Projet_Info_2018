TEMPLATE = app
CONFIG += console c++11
QT += core gui

QMAKE_CXXFLAGS += -std=c++11 -fopenmp -O2 -march=native
QMAKE_LFLAGS += -fopenmp

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
    GUI/frameorientation.cpp \
    GUI/QScienceSpinBox.cpp \
    star.cpp \
    GUI/framestar.cpp \
    GUI/selectionwindow.cpp \
    GUI/dialoguesave.cpp

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
    GUI/frameorientation.h \
    GUI/QScienceSpinBox.h \
    star.h \
    GUI/framestar.h \
    GUI/selectionwindow.h \
    GUI/dialoguesave.h

FORMS +=
