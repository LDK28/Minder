cmake_minimum_required(VERSION 3.0.0)
project(ClientConnection)

set(CLIENT_CONNECTION_INC .)
set(JSON_INC ./nlohmann)

add_subdirectory(JsonParser)
add_subdirectory(HttpClient)

include_directories(./nlohmann
                    ${JSON_PARSER_INC}
                    ${HTTP_CLIENT_INC})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${JSON_PARSER_LIB}
                                                ${HTTP_CLIENT_LIB})