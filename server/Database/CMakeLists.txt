cmake_minimum_required(VERSION 3.0.0)
project(DatabaseClient)

set(DATABASE_CLIENT_INC .)
set(JSON_INC ../nlohmann)


add_subdirectory(PostgreDatabaseClient)
add_subdirectory(DatabaseUsersClient)
add_subdirectory(DatabaseSessionClient)
add_subdirectory(DatabaseDrawDeskClient)


# add_executable(${PROJECT_NAME} main.cpp)
# target_include_directories(${PROJECT_NAME} PUBLIC 
#                         ${POSTGRE_DATABASE_CLIENT_INC} 
#                         ${DATABASE_USERS_CLIENT_INC} 
#                         ${DATABASE_SESSION_CLIENT_INC}
#                         ../${JSON_INC})


# target_link_libraries(${PROJECT_NAME} 
#                         ${POSTGRE_DATABASE_CLIENT_LIB} 
#                         ${DATABASE_USERS_CLIENT_LIB} 
#                         ${DATABASE_SESSION_CLIENT_LIB} )

message("asdadas")

add_subdirectory(tests)

