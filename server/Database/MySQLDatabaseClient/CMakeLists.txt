cmake_minimum_required(VERSION 3.0.0)
project(MySQLDatabaseClient)
  
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq -fPIC")
find_library(MYSQL_LIB mysqlcppconn)


add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../${JSON_INC} ../${DATABASE_CLIENT_INC})
target_link_libraries(${PROJECT_NAME} ${MYSQL_LIB})

set(MYSQL_DATABASE_CLIENT_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(MYSQL_DATABASE_CLIENT_INC ${INCLUDE_DIRS} PARENT_SCOPE)
