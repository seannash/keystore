#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

int main(int argc, char** argv) {
    // Default URL if none provided
    std::string url = "http://localhost:8080/api";
    std::string key {};

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <url> <key>" << std::endl;
        return 1;
    }

    url = argv[1];
    key = argv[2];

    try {
        // Create JSON-RPC request for Ping
        nlohmann::json request = {
            {"jsonrpc", "2.0"},
            {"method", "get"},
            {"params", {{"key", key} }},
            {"id", 1}
        };
        
        // Make POST request with JSON body
        auto response = cpr::Post(
            cpr::Url{url},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Body{request.dump()}
        );

        std::cout << "B\n";

        // Check if request was successful
        if (response.status_code == 200) {
            std::cout << "Response: " << response.text << std::endl;
        } else {
            std::cerr << "Error: " << response.status_code << " - " << response.text << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
