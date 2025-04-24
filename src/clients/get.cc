#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "caller/get.h"

int main(int argc, char** argv) {

   if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <url> <key>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    api::Get get(url);
    api::Get::request_t request {.key = argv[2]};

    api::Get::combined_response_t response;
    auto result = get.call(request, response);

    if (result != 0) {
        std::cerr << "Error: " << result << std::endl;
        return 1;
    }

    if (std::holds_alternative<api::Get::response_t>(response)) {
        std::cout << "Response: " << std::get<api::Get::response_t>(response) << std::endl;
    } else {
        std::cerr << "Error: " << std::get<api::Get::error_response_t>(response).code << " - " << std::get<api::Get::error_response_t>(response).message << std::endl;
        return 1;
    }
    

    return 0;
}
