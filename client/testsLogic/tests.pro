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
    testsUser.h \
    $$PWD/../LogicLib/UserLogic.h \
    $$PWD/../LogicLib/DrawingLogic.h \
    $$PWD/../LogicLib/LogicController.h \
    $$PWD/../LogicLib/HttpClient.h \
    $$PWD/../LogicLib/ScreenController.h

SOURCES += \
        main.cpp \
        $$PWD/../LogicLib/UserLogic.cpp \
        $$PWD/../LogicLib/DrawingLogic.cpp \
        $$PWD/../LogicLib/LogicController.cpp \
        $$PWD/../LogicLib/HttpClient.cpp \
        $$PWD/../LogicLib/ScreenController.cpp

INCLUDEPATH += $$PWD/../LogicLib/
