add_library(framework
    json_rpc_validation.cc
    json_rpc_validation.h
    jsonserver.cc
    jsonserver.h
    genericapp.cc
    genericapp.h
    genericappwithcontext.cc
    genericappwithcontext.h
)

target_include_directories(framework PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(framework PUBLIC 
    reflectcpp::reflectcpp
    Crow::Crow
) 