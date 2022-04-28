QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arrow.cpp \
    AuthorizationWindow.cpp \
    BlockImage.cpp \
    LogicController.cpp \
    MindMap.cpp \
    NewBlockCreationWindow.cpp \
    RegisterWindow.cpp \
    ScreenController.cpp \
    SessionConnectionWindow.cpp \
    SessionCreationWindow.cpp \
    SessionUsersList.cpp \
    SessionWindow.cpp \
    SettingsWindow.cpp \
    ToolsPalette.cpp \
    main.cpp

HEADERS += \
    Arrow.h \
    AuthorizationWindow.h \
    BlockImage.h \
    DataStructures.h \
    LogicController.h \
    MindMap.h \
    NewBlockCreationWindow.h \
    RegisterWindow.h \
    ScreenController.h \
    SessionConnectionWindow.h \
    SessionCreationWindow.h \
    SessionUsersList.h \
    SessionWindow.h \
    SettingsWindow.h \
    ToolsPalette.h

FORMS += \
    AuthorizationWindow.ui \
    MindMap.ui \
    NewBlockCreationWindow.ui \
    RegisterWindow.ui \
    SessionConnectionWindow.ui \
    SessionCreationWindow.ui \
    SessionUsersList.ui \
    SessionWindow.ui \
    SettingsWindow.ui \
    ToolsPalette.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

DISTFILES +=
