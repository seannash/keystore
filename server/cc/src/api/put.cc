#include <string>
#include "put.h"

namespace api {

Put::Put(model::Store& store)
: store_(store) {
}

int Put::handle(const request_t& params, 
                        combined_response_t& response_out) {
    if (!params.key.empty() && !params.value.empty()) {
        store_.put(params.key, params.value);
        response_t response {
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