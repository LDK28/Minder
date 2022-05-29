cmake_minimum_required(VERSION 3.0.0)
project(ServerLogic)

message("--------------------------")
message(${DATABASE_USERS_CLIENT_INC})
message(${DATABASE_SESSION_CLIENT_INC})
message(${DATABASE_DRAW_DESK_CLIENT_INC})
message(${DATABASE_CLIENT_INC})
message("--------------------------")

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC 
                                        ../${JSON_INC} 
                                        ../${SERVER_INC}
                                        ${DATABASE_USERS_CLIENT_INC}
                                        ${DATABASE_SESSION_CLIENT_INC}
                                        ${DATABASE_DRAW_DESK_CLIENT_INC}
                                        ${POSTGRE_DATABASE_CLIENT_INC}
                                        ${DATABASE_CLIENT_INC})

# target_link_libraries(ServerLogic ${DATABASE_USERS_CLIENT_LIB} 
#                                 ${DATABASE_SESSION_CLIENT_LIB} 
#                                 ${DATABASE_DRAW_DESK_CLIENT_LIB})

set(SERVER_LOGIC_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(SERVER_LOGIC_INC ${INCLUDE_DIRS} PARENT_SCOPE)