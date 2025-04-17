#include <string>
#include "put.h"

namespace keystore::api {

Put::Put(Context& context)
: context_(context) {
}

int Put::handle(const request_t& params, 
                        combined_response_t& response_out) {
    if (!params.key.empty() && !params.value.empty()) {
        context_.store().put(params.key, params.value);
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

} // namespace keystore::api 