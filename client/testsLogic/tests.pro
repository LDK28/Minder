include(gtest_dependency.pri)

QT += widgets

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

HEADERS += \
    mockClient.h \
    testsDrawing.h \
    testsLogicController.h \
    testsUser.h

SOURCES += \
        main.cpp

INCLUDEPATH += $$PWD/../LogicLib/
