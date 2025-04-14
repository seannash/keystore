cmake_minimum_required(VERSION 3.10)
project(crow_server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch Crow library
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.0+5
)

# Make Crow available
FetchContent_MakeAvailable(crow)

# Add executable
add_executable(${PROJECT_NAME} main.cpp)

# Include Crow headers
target_include_directories(${PROJECT_NAME} PRIVATE ${crow_SOURCE_DIR}/include)

# No need to link with Crow as it's header-only 