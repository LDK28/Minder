QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrow.cpp \
    authorizationwindow.cpp \
    blockimage.cpp \
    logiccontroller.cpp \
    mindmap.cpp \
    newblockcreationwindow.cpp \
    registerwindow.cpp \
    screencontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    sessionconnectionwindow.cpp \
    sessioncreationwindow.cpp \
    sessionuserlist.cpp \
    sessionwindow.cpp \
    settingswindow.cpp \
    toolspalette.cpp

HEADERS += \
    arrow.h \
    authorizationwindow.h \
    blockimage.h \
    datastructures.h \
    logiccontroller.h \
    mainwindow.h \
    mindmap.h \
    newblockcreationwindow.h \
    registerwindow.h \
    screencontroller.h \
    sessionconnectionwindow.h \
    sessioncreationwindow.h \
    sessionuserlist.h \
    sessionwindow.h \
    settingswindow.h \
    toolspalette.h

FORMS += \
    authorizationwindow.ui \
    mainwindow.ui \
    mindmap.ui \
    newblockcreationwindow.ui \
    registerwindow.ui \
    sessionconnectionwindow.ui \
    sessioncreationwindow.ui \
    sessionuserlist.ui \
    sessionwindow.ui \
    settingswindow.ui \
    toolspalette.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
