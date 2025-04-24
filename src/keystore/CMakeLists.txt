add_library(keystore
    publicserver.cc
    privateserver.cc
    model/store.cc
    model/store.h
    api/ping.cc
    api/ping.h
    api/put.cc
    api/put.h
    api/get.cc
    api/get.h
    context.cc
)

target_include_directories(keystore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(keystore PRIVATE
    framework
    caller
    pthread
)

add_executable(${PROJECT_NAME} 
    main.cc
)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    keystore
    framework
    caller
    pthread
) 