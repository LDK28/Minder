cmake_minimum_required(VERSION 3.0.0)
project(PostgreDatabaseClient)
  
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq -fPIC")
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)


add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../${JSON_INC} ../${DATABASE_CLIENT_INC})
target_link_libraries(${PROJECT_NAME} ${PQXX_LIB} ${PQ_LIB})

set(POSTGRE_DATABASE_CLIENT_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(POSTGRE_DATABASE_CLIENT_INC ${INCLUDE_DIRS} PARENT_SCOPE)
