cmake_minimum_required(VERSION 3.10)
project(crow_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)

find_package(reflectcpp REQUIRED)
find_package(Crow REQUIRED)
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cc
    src/api/ping.cc
    src/framework/json_rpc_validation.cc
    src/framework/jsonserver.cc
    src/framework/genericapp.cc
    src/publicserver.cc
    src/privateserver.cc
    src/api/put.cc
    src/api/get.cc
    src/model/store.cc
    src/caller/get.cc
    src/caller/put.cc
    src/context.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${crow_SOURCE_DIR}/include
    ${reflect-cpp_SOURCE_DIR}/include
    src
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        reflectcpp::reflectcpp
        Crow::Crow
    PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
        stdc++fs
        pthread
)

add_executable(put
    src/clients/put.cc
    src/caller/put.cc
)

target_include_directories(put
    PRIVATE
        src
)

target_link_libraries(put
    PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
)

add_executable(get
    src/clients/get.cc
    src/caller/get.cc
)

target_include_directories(get
    PRIVATE
        src
)

target_link_libraries(get
    PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
)