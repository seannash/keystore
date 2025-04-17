#include "get.h"

#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <variant>
namespace api {

Get::Get(std::string_view endpoint_)
: endpoint_(endpoint_) {
}

int Get::call(const request_t& request,
              combined_response_t& combined_response) {
    try {
        nlohmann::json json_request = {
            {"jsonrpc", "2.0"},
            {"method", "get"},
            {"params", {{"key", request.key} }},
            {"id", 1}
        };
        auto call_response = cpr::Post(
            cpr::Url{endpoint_},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Body{json_request.dump()}
        );
        auto json_response = nlohmann::json::parse(call_response.text);
        if (call_response.status_code == 200) {
            response_t response {
                .value = json_response["result"]["value"]
            };
            combined_response = response;
        } else {
            error_response_t error {
                .code = json_response["code"],
                .message = json_response["message"]};
            combined_response = error;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;

}

std::ostream& operator<<(std::ostream& os, const Get::combined_response_t& response) {
    if (std::holds_alternative<Get::response_t>(response)) {
        os << std::get<Get::response_t>(response);
    } else {
        os << std::get<Get::error_response_t>(response);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Get::request_t& request) {
    os << "[ key: " << request.key << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Get::response_t& response) {
    os << "[ value: " << response.value << ", server: " << response.server << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Get::error_response_t& error) {
    os << "[ code: " << error.code << ", message: " << error.message << " ]";
    return os;
}


} // namespace api 