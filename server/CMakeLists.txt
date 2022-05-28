cmake_minimum_required(VERSION 3.0.0)
project(MinderServer)

set(JSON_INC ../nlohmann)

add_subdirectory(Server)

include_directories(./Server/NetworkController)
link_libraries(NetworkController)

add_executable(${PROJECT_NAME} main.cpp)