from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class CrowServerRecipe(ConanFile):
    name = "crow_server"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"
    
    def requirements(self):
        self.requires("cpr/1.11.2")
        self.requires("reflect-cpp/0.18.0")
        self.requires("crowcpp-crow/1.2.0")
        self.requires("nlohmann_json/3.11.2")
    def generate(self):
        tc = CMakeToolchain(self)
        # Set the package configuration path
        tc.variables["CMAKE_PREFIX_PATH"] = "${CMAKE_CURRENT_BINARY_DIR}"
        # Set C++20 standard
        tc.variables["CMAKE_CXX_STANDARD"] = "20"
        tc.variables["CMAKE_CXX_STANDARD_REQUIRED"] = "ON"
        tc.generate()

