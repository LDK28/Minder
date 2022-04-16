cmake_minimum_required(VERSION 3.0.0)
project(Server)

set(SERVER_INC .)
set(JSON_INC ../nlohmann)

add_subdirectory(NetworkController)
add_subdirectory(NetworkSession)
add_subdirectory(ServerLogic)
