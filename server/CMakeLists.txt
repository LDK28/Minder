cmake_minimum_required(VERSION 3.0.0)
project(MinderServer)

set(JSON_INC ../nlohmann)

add_subdirectory(Database)
add_subdirectory(Server)

# target_include_directories(${PROJECT_NAME} PUBLIC ${NETWORK_CONTROLLER_INC})
# link_libraries(NetworkController)
include_directories(./nlohmann
                    ${NETWORK_CONTROLLER_INC}
                    ${SERVER_LOGIC_INC}
                    ${DATABASE_USERS_CLIENT_INC}
                    ${DATABASE_SESSION_CLIENT_INC}
                    ${DATABASE_DRAW_DESK_CLIENT_INC}
                    ${POSTGRE_DATABASE_CLIENT_INC}
                    ${DATABASE_CLIENT_INC})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SERVER_LOGIC_LIB}
                                                ${NETWORK_CONTROLLER_LIB}
                                                ${DATABASE_USERS_CLIENT_LIB}
                                                ${DATABASE_SESSION_CLIENT_LIB}
                                                ${DATABASE_DRAW_DESK_CLIENT_LIB}
                                                ${POSTGRE_DATABASE_CLIENT_LIB}
                                                ${DATABASE_CLIENT_LIB})