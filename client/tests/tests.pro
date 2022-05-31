include(gtest_dependency.pri)

QT += widgets

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

HEADERS += \
    inc/mockClient.h \
    inc/testsDrawing.h \
    inc/testsLogicController.h \
    inc/testsUser.h \
    $$PWD/../LogicLib/inc/UserLogic.h \
    $$PWD/../LogicLib/inc/DrawingLogic.h \
    $$PWD/../LogicLib/inc/LogicController.h \
    $$PWD/../LogicLib/inc/HttpClient.h \
    $$PWD/../LogicLib/inc/ScreenController.h

SOURCES += \
        src/main.cpp \
        $$PWD/../LogicLib/src/UserLogic.cpp \
        $$PWD/../LogicLib/src/DrawingLogic.cpp \
        $$PWD/../LogicLib/src/LogicController.cpp \
        $$PWD/../LogicLib/src/ScreenController.cpp

INCLUDEPATH += $$PWD/../LogicLib/inc/ inc/
