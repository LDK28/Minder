QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIB_PATH = "libs/"
SRC_PATH = "src/"
RESOURCES_PATH = "resources/"
TESTS_PATH = "tests/"

include($${LIB_PATH}/Arrow/Arrow.pri)
include($${LIB_PATH}/AuthorizationWindow/AuthorizationWindow.pri)
include($${LIB_PATH}/BlockImage/BlockImage.pri)
include($${LIB_PATH}/LogicController/LogicController.pri)
include($${LIB_PATH}/MindMap/MindMap.pri)
include($${LIB_PATH}/NewBlockCreationWindow/NewBlockCreationWindow.pri)
include($${LIB_PATH}/RegisterWindow/RegisterWindow.pri)
include($${LIB_PATH}/ScreenController/ScreenController.pri)
include($${LIB_PATH}/SessionConnectionWindow/SessionConnectionWindow.pri)
include($${LIB_PATH}/SessionCreationWindow/SessionCreationWindow.pri)
include($${LIB_PATH}/SessionUsersList/SessionUsersList.pri)
include($${LIB_PATH}/SessionWindow/SessionWindow.pri)
include($${LIB_PATH}/SettingsWindow/SettingsWindow.pri)
include($${LIB_PATH}/ToolsPalette/ToolsPalette.pri)
include($${LIB_PATH}/DataStructures/DataStructures.pri)

SOURCES += \
    $${SRC_PATH}/main.cpp

HEADERS +=

FORMS +=

RESOURCES += \
    $${RESOURCES_PATH}/resources.qrc

DISTFILES +=

# include($${TESTS_PATH}/tests.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
