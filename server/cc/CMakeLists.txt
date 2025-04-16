cmake_minimum_required(VERSION 3.10)
project(crow_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Conan-generated files
include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)

# Find dependencies installed by Conan
find_package(reflectcpp REQUIRED)
find_package(Crow REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cc
    src/api/ping.cc
    src/server.cc
    src/middleware/json_rpc_validation.cc
    src/jsonutil.cc
)

# Include headers
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${crow_SOURCE_DIR}/include
    ${reflect-cpp_SOURCE_DIR}/include
    src
)

# Link with libraries
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        reflectcpp::reflectcpp
        Crow::Crow
    PRIVATE
        stdc++fs
        pthread
)

# No need to link with Crow as it's header-only 