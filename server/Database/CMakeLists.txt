cmake_minimum_required(VERSION 3.0.0)
project(DatabaseClient)

set(DATABASE_CLIENT_INC .)
set(JSON_INC ../nlohmann)


add_subdirectory(PostgreDatabaseClient)
add_subdirectory(DatabaseUsersClient)
add_subdirectory(DatabaseSessionClient)
add_subdirectory(DatabaseDrawDeskClient)

add_subdirectory(tests)

