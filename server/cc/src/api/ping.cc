#include <crow.h>
#include <string>
#include "ping.h"
#include "handler.h"
#include <jsonutil.h>

namespace api {

void PingHandler::handle(crow::request& req, crow::response& res, 
                        const crow::json::rvalue& params, 
                        const crow::json::rvalue& id) {
    if (params.has("message")) {
        JsonUtil::send_success(res, params["message"], id);
    } else {
        JsonUtil::send_error(res, -32602, "Invalid params", id);
    }
}

} // namespace api 