#pragma once

#include <string>
#include <variant>

namespace api {

class GetKey {
public:
    struct request_t {
        std::string key;
    };

    struct response_t {
        std::string value;
        std::string status;
    };

    struct error_response_t {
        int code;
        std::string message;
    };

    using combined_response_t =std::variant<response_t, error_response_t>;

    int handle(const request_t& params, 
               combined_response_t& response_out);
};

} // namespace api 