#pragma once

#include <string>
#include <variant>
#include <model/store.h>

namespace api {

class Put {
protected:
    std::string endpoint_;

public:
    Put(std::string_view endpoint_);

    struct request_t {
        std::string key;
        std::string value;
    };

    struct response_t {
        std::string status;
    };

    struct error_response_t {
        int code;
        std::string message;
    };

    using combined_response_t = std::variant<response_t, error_response_t>;

    int call(const request_t& request, 
             combined_response_t& response);
};

std::ostream& operator<<(std::ostream& os, const Put::combined_response_t& response);
std::ostream& operator<<(std::ostream& os, const Put::request_t& request);
std::ostream& operator<<(std::ostream& os, const Put::response_t& response);
std::ostream& operator<<(std::ostream& os, const Put::error_response_t& error);

} // namespace api 