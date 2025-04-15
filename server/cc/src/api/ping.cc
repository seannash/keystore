#include <crow.h>
#include <string>
#include "ping.h"
#include "handler.h"

namespace api {

void PingHandler::handle(crow::request& req, crow::response& res, 
                        const crow::json::rvalue& params, 
                        const crow::json::rvalue& id) {
    if (params.has("message")) {
        Handler::send_success(res, params["message"], id);
    } else {
        Handler::send_error(res, -32602, "Invalid params", id);
    }
}

} // namespace api 