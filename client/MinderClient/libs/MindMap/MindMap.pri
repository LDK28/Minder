HEADERS_PATH = $$PWD/inc
SOURCES_PATH = $$PWD/src
FORMS_PATH = $$PWD/ui

INCLUDEPATH += $$PWD/inc

HEADERS += $$HEADERS_PATH/MindMap.h \
           $$HEADERS_PATH/Arrow.h \
           $$HEADERS_PATH/BlockImage.h \
           $$HEADERS_PATH/NewBlockCreationWindow.h

SOURCES += $$SOURCES_PATH/MindMap.cpp \
           $$SOURCES_PATH/Arrow.cpp \
           $$SOURCES_PATH/BlockImage.cpp \
           $$SOURCES_PATH/NewBlockCreationWindow.cpp

FORMS += $$FORMS_PATH/MindMap.ui \
         $$FORMS_PATH/NewBlockCreationWindow.ui

RESOURCES +=
