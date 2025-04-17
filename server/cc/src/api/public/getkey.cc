#include <string>
#include "getkey.h"

namespace api {

GetKey::GetKey(model::Store& store)
: store_(store) {
}

int GetKey::handle(const request_t& params, 
                        combined_response_t& response_out) {
    if (!params.key.empty()) {
        auto value = store_.get(params.key);
        response_t response {
            .value = value,
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