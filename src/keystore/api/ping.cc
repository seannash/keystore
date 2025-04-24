#include <string>
#include "ping.h"

namespace keystore::api {

int PingHandler::handle(const request_t& params, 
                        combined_response_t& response_out) {
    if (!params.message.empty()) {
        response_t response {
            .message = params.message
        };
        response_out = response;
        return 200;
    } else {
        error_response_t error {
            .code = -32602
        };
        response_out = error;
        return -32602;
    }

}

} // namespace keystore::api 