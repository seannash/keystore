# Find required packages
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

# Add caller library
add_library(caller
    get.cc
    put.cc
    get.h
    put.h
)

# Set include directories
target_include_directories(caller PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
target_link_libraries(caller PUBLIC
    cpr::cpr
    nlohmann_json::nlohmann_json 
) 