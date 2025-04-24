# Add model source files to parent keystore library
target_sources(keystore
    PRIVATE
        store.cc
)

# Set include directories
target_include_directories(keystore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
) 