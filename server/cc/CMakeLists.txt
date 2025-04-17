cmake_minimum_required(VERSION 3.10)
project(crow_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)

find_package(reflectcpp REQUIRED)
find_package(Crow REQUIRED)
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)


add_library(keystore 
    src/keystore/api/ping.cc
    src/keystore/publicserver.cc
    src/keystore/privateserver.cc
    src/keystore/api/put.cc
    src/keystore/api/get.cc
    src/keystore/model/store.cc
    src/keystore/context.cc
)

target_include_directories(keystore PRIVATE 
    ${crow_SOURCE_DIR}/include
    ${reflect-cpp_SOURCE_DIR}/include
    src
)

target_link_libraries(keystore
    PUBLIC 
        reflectcpp::reflectcpp
        Crow::Crow
    PRIVATE
        framework
        caller
        pthread
)

add_executable(${PROJECT_NAME} 
    src/keystore/main.cc
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
        keystore
    framework
        caller
        pthread
)


add_library(framework
    src/framework/json_rpc_validation.cc
    src/framework/json_rpc_validation.h
    src/framework/jsonserver.cc
    src/framework/jsonserver.h
    src/framework/genericapp.cc
    src/framework/genericapp.h
    src/framework/genericappwithcontext.cc
    src/framework/genericappwithcontext.h
)

target_include_directories(framework
    PRIVATE
        src
)

target_link_libraries(framework
    PUBLIC 
        reflectcpp::reflectcpp
        Crow::Crow
)

add_library(caller
    src/caller/get.cc
    src/caller/put.cc
    src/caller/get.h
    src/caller/put.h
)

target_include_directories(caller
    PRIVATE
        src
)

target_link_libraries(caller
    PUBLIC 
        cpr::cpr
        nlohmann_json::nlohmann_json
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