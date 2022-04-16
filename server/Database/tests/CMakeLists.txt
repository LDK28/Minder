cmake_minimum_required(VERSION 3.0.0)
project(test)

file(GLOB SRCS_USERS_CLIENT_TEST test_database_users_client.cpp)

find_package(GTest REQUIRED)

set(database_users_test "${PROJECT_NAME}_database_users")

add_executable(${database_users_test} ${SRCS_USERS_CLIENT_TEST})
target_include_directories(${database_users_test} PUBLIC ${DATABASE_USERS_CLIENT_INC} ../${JSON_INC})
target_link_libraries(${database_users_test} ${DATABASE_USERS_CLIENT_LIB} GTest::gtest_main)


file(GLOB SRCS_DRAW_DESK_CLIENT_TEST test_database_draw_desk_client.cpp)

find_package(GTest REQUIRED)

set(database_draw_desk_test "${PROJECT_NAME}_database_draw_desk")

add_executable(${database_draw_desk_test} ${SRCS_DRAW_DESK_CLIENT_TEST})
target_include_directories(${database_draw_desk_test} PUBLIC ${DATABASE_DRAW_DESK_CLIENT_INC} ../${JSON_INC})
target_link_libraries(${database_draw_desk_test} ${DATABASE_DRAW_DESK_CLIENT_LIB} GTest::gtest_main)

file(GLOB SRCS_SESSION_CLIENT_TEST test_database_session_client.cpp)

find_package(GTest REQUIRED)

set(database_session_test "${PROJECT_NAME}_database_session")

add_executable(${database_session_test} ${SRCS_SESSION_CLIENT_TEST})
target_include_directories(${database_session_test} PUBLIC ${DATABASE_SESSION_CLIENT_INC} ../${JSON_INC})
target_link_libraries(${database_session_test} ${DATABASE_SESSION_CLIENT_LIB} GTest::gtest_main)

