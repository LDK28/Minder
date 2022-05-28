cmake_minimum_required(VERSION 3.0.0)
project(MinderServer)

set(CLIENT_CONNECTION_INC .)
set(JSON_INC ./nlohmann)

add_subdirectory(JsonParser)
add_subdirectory(HttpClient)