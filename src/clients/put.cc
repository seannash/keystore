#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "caller/put.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <url> <key> <value>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    api::Put put(url);
    api::Put::request_t request {
        .key = argv[2],
        .value = argv[3]
    };

    api::Put::combined_response_t response;
    auto result = put.call(request, response);

    if (result != 0) {
        std::cerr << "Error: " << result << std::endl;
        return 1;
    }

    if (std::holds_alternative<api::Put::response_t>(response)) {
        std::cout << "Response: " << std::get<api::Put::response_t>(response) << std::endl;
    } else {
        std::cerr << "Error: " << std::get<api::Put::error_response_t>(response).code << " - " << std::get<api::Put::error_response_t>(response).message << std::endl;
        return 1;
    }

    return 0;
}
