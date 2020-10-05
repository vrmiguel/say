TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_CXXFLAGS_RELEASE *= -ffast-math

SOURCES += \
        include/saylib.h \
        src/main.cpp \
        src/saylib.cpp
