# Add client executables
add_executable(put
    put.cc
)
target_include_directories(put PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(put PRIVATE 
    caller
)

add_executable(get
    get.cc
)
target_include_directories(get PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(get PRIVATE 
    caller
) 