HEADERS_PATH = $$PWD/inc
SOURCES_PATH = $$PWD/src
FORMS_PATH = $$PWD/ui

INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$SOURCES_PATH/DrawingLogic.cpp \
    $$SOURCES_PATH/LogicController.cpp \
    $$SOURCES_PATH/UserLogic.cpp

HEADERS += \
    $$HEADERS_PATH/DrawingLogic.h \
    $$HEADERS_PATH/LogicLib_global.h \
    $$HEADERS_PATH/LogicController.h \
    $$HEADERS_PATH/UserLogic.h

