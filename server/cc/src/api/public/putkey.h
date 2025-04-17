#pragma once

#include <string>
#include <variant>
#include <model/store.h>
namespace api {

class PutKey {
protected:
    model::Store& store_;
public:
    PutKey(model::Store& store);

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

    using combined_response_t =std::variant<response_t, error_response_t>;

    int handle(const request_t& params, 
               combined_response_t& response_out);
};

} // namespace api 