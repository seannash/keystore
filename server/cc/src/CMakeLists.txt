find_package(reflectcpp REQUIRED)
find_package(Crow REQUIRED)
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)


add_subdirectory(framework)
add_subdirectory(caller)
add_subdirectory(keystore)
add_subdirectory(clients)
