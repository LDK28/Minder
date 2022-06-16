cmake_minimum_required(VERSION 3.0.0)
project(MinderServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(JSON_INC ../nlohmann)

add_subdirectory(Database)
add_subdirectory(Server)

include_directories(./nlohmann
                    ${DATABASE_USERS_CLIENT_INC}
                    ${DATABASE_SESSION_CLIENT_INC}
                    ${DATABASE_DRAW_DESK_CLIENT_INC}
                    ${POSTGRE_DATABASE_CLIENT_INC}
                    ${MYSQL_DATABASE_CLIENT_INC}
                    ${DATABASE_CLIENT_INC}
                    ${BUISNESS_LOGIC_INC}
                    ${SERVER_LOGIC_INC}
                    ${NETWORK_CONTROLLER_INC})


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${DATABASE_USERS_CLIENT_LIB}
                                                ${DATABASE_SESSION_CLIENT_LIB}
                                                ${DATABASE_DRAW_DESK_CLIENT_LIB}
                                                ${POSTGRE_DATABASE_CLIENT_LIB}
                                                ${MYSQL_DATABASE_CLIENT_LIB}
                                                ${DATABASE_CLIENT_LIB}
                                                ${BUISNESS_LOGIC_LIB}
                                                ${SERVER_LOGIC_LIB}
                                                ${NETWORK_CONTROLLER_LIB})
