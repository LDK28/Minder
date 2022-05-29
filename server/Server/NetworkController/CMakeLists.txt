cmake_minimum_required(VERSION 3.0.0)
project(NetworkController)
  
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC 
                                        ../${JSON_INC} 
                                        ../${SERVER_INC} 
                                        ${SERVER_LOGIC_INC}
                                        ${DATABASE_USERS_CLIENT_INC}
                                        ${DATABASE_SESSION_CLIENT_INC}
                                        ${DATABASE_DRAW_DESK_CLIENT_INC}
                                        ${POSTGRE_DATABASE_CLIENT_INC}
                                        ${DATABASE_CLIENT_INC})

set(NETWORK_CONTROLLER_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(NETWORK_CONTROLLER_INC ${INCLUDE_DIRS} PARENT_SCOPE)