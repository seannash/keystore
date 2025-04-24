# Find required packages
find_package(reflectcpp REQUIRED)
find_package(Crow REQUIRED)
find_package(cpr REQUIRED)

# Add framework library
add_library(framework
    json_rpc_validation.cc
    json_rpc_validation.h
    jsonserver.cc
    jsonserver.h
    genericapp.cc
    genericapp.h
    genericappwithcontext.cc
    genericappwithcontext.h
    oauthmiddleware.cc
    oauthmiddleware.h
)

# Set include directories
target_include_directories(framework PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(framework PUBLIC 
    reflectcpp::reflectcpp
    Crow::Crow
    cpr::cpr
) 