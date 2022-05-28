cmake_minimum_required(VERSION 3.0.0)
project(ServerLogic)
  
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../${JSON_INC} ../${SERVER_INC})

include_directories("../../Database/DatabaseDrawDeskClient")
link_libraries(DatabaseDrawDeskClient)

include_directories("../../Database/DatabaseSessionClient")
link_libraries(DatabaseSessionClient)

include_directories("../../Database/DatabaseUsersClient")
link_libraries(DatabaseUsersClient)

include_directories("../../Database")
include_directories("../../Database/PostgreDatabaseClient")




set(SERVER_LOGIC_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(SERVER_LOGIC_INC ${INCLUDE_DIRS} PARENT_SCOPE)
