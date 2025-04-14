cmake_minimum_required(VERSION 3.10)
project(crow_server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch ASIO library first
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-34-2
)

# Fetch Crow library
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.2.1.2
)

# Make ASIO available first
FetchContent_MakeAvailable(asio)

# Set ASIO include directory
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include CACHE PATH "ASIO include directory")

# Make Crow available
FetchContent_MakeAvailable(crow)

# Add executable
add_executable(${PROJECT_NAME} main.cpp)

# Include Crow and ASIO headers
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${crow_SOURCE_DIR}/include
    ${ASIO_INCLUDE_DIR}
)

# No need to link with Crow as it's header-only 