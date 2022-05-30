HEADERS_PATH = $$PWD/inc
SOURCES_PATH = $$PWD/src

INCLUDEPATH += $$PWD/inc

SOURCES += \
    $$SOURCES_PATH/HttpClient.cpp \
    $$SOURCES_PATH/JsonParser.cpp 
    

HEADERS += \
    $$HEADERS_PATH/HttpClient.hpp \
    $$HEADERS_PATH/JsonParser.hpp \
    $$HEADERS_PATH/json.hpp
