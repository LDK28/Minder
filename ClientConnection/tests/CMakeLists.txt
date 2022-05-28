cmake_minimum_required(VERSION 3.0.0)
project(test)

file(GLOB SRCS_USERS_CLIENT_TEST test_database_users_client.cpp)

set(JSON_PARSER ../JsonParser)

include_directories(${JSON_PARSER})

link_libraries(${JSON_PARSER})

find_package(GTest REQUIRED)

set(json_parser_test "${PROJECT_NAME}_json_parser")

add_executable(${json_parser_test} ${SRCS_USERS_CLIENT_TEST})
target_include_directories(${json_parser_test} PUBLIC 
                                            ${DATABASE_USERS_CLIENT_INC} 
                                            ../${JSON_INC} 
                                            ${POSTGRE_DATABASE_CLIENT_INC})
target_link_libraries(${json_parser_test} 
                                            ${DATABASE_USERS_CLIENT_LIB} 
                                            GTest::gtest_main
                                            ${POSTGRE_DATABASE_CLIENT_LIB})


file(GLOB SRCS_DRAW_DESK_CLIENT_TEST test_database_draw_desk_client.cpp)