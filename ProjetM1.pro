TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp \
    Source.cpp \
    GravitationalLense.cpp \
    Object.cpp \
    PointGravitationalLense.cpp \
    PointSource.cpp

HEADERS += \
    Source.h \
    GravitationalLense.h \
    Object.h \
    PointGravitationalLense.h \
    PointSource.h

