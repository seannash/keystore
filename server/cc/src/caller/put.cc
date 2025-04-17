#include "put.h"

#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <variant>

namespace api {

Put::Put(std::string_view endpoint_)
: endpoint_(endpoint_) {
}

int Put::call(const request_t& request,
              combined_response_t& combined_response) {
    try {
        nlohmann::json json_request = {
            {"jsonrpc", "2.0"},
            {"method", "put"},
            {"params", {
                {"key", request.key},
                {"value", request.value}
            }},
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
                .status = json_response["result"]["status"]
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

std::ostream& operator<<(std::ostream& os, const Put::combined_response_t& response) {
    if (std::holds_alternative<Put::response_t>(response)) {
        os << std::get<Put::response_t>(response);
    } else {
        os << std::get<Put::error_response_t>(response);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Put::request_t& request) {
    os << "[ key: " << request.key << ", value: " << request.value << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Put::response_t& response) {
    os << "[ status: " << response.status << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Put::error_response_t& error) {
    os << "[ code: " << error.code << ", message: " << error.message << " ]";
    return os;
}

} // namespace api 