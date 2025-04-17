#include <string>
#include "getkey.h"

namespace api {

int GetKey::handle(const request_t& params, 
                        combined_response_t& response_out) {
    if (!params.key.empty()) {
        response_t response {
            .value = "42",
            .status = "success"
        };
        response_out = response;
        return 200;
    } else {
        error_response_t error {
            .code = -32602,
            .message = "Invalid parameters"
        };
        response_out = error;
        return -32602;
    }

}

} // namespace api 