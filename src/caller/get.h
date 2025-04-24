#pragma once

#include <string>
#include <variant>

namespace api {

class Get {
protected:
    std::string endpoint_;

public:
    Get(std::string_view endpoint_);

    struct request_t {
        std::string key;
    };

    struct response_t {
        int server;
        std::string value;
    };

    struct error_response_t {
        int code;
        std::string message;
    };

    using combined_response_t = std::variant<response_t, error_response_t>;

    int call(const request_t& request, 
             combined_response_t& response);
};

std::ostream& operator<<(std::ostream& os, const Get::combined_response_t& response);
std::ostream& operator<<(std::ostream& os, const Get::request_t& request);
std::ostream& operator<<(std::ostream& os, const Get::response_t& response);
std::ostream& operator<<(std::ostream& os, const Get::error_response_t& error);

} // namespace api 