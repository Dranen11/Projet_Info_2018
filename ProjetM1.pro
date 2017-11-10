TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp \
    observer.cpp \
#    pointGravitationalLense.cpp \
#    pointSource.cpp \
#    gravitationalLense.cpp \
#    source.cpp \
    ray.cpp \
    pixel.cpp \
    test.cpp \
    vecteur.cpp \
    celestialBody.cpp

HEADERS += \
    observer.h \
#    pointSource.h \
#    source.h \
#    pointGravitationalLense.h \
#    gravitationalLense.h \
    vecteur.h \
    ray.h \
    pixel.h \
    test.h \
    celestialBody.h

