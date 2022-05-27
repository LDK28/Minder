cmake_minimum_required(VERSION 3.0.0)
project(ServerLogic)
  
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# set(DATABASE_PATH ../../Database)
# include_directories(${DATABASE_PATH} ${DATABASE_PATH}/DatabaseUsersClient ${DATABASE_PATH}/DatabaseSessionClient ${DATABASE_PATH}/DatabaseDrawDeskClient)
# link_libraries(DatabaseUsersClient DatabaseSessionClient DatabaseDrawDeskClient)

# add_library(../../Database)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../${JSON_INC} ../${SERVER_INC})

set(SERVER_LOGIC_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(SERVER_LOGIC_INC ${INCLUDE_DIRS} PARENT_SCOPE)