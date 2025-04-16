#include "jsonserver.h"

#include "jsonutil.h"
#include <rfl/json.hpp>
#include <rfl.hpp>
#include <crow.h>

namespace framework {

crow::response make_error(const crow::json::rvalue& id,int code, const crow::json::wvalue& error_response) {
    crow::json::wvalue body = {
        {"jsonrpc", "2.0"},
        {"error", error_response},
        {"id", id}
    };
    crow::response res {};
    res.code = (code == -32601) ? 404 : 400; // Method not found gets 404, others get 400
    res.body = body.dump();
    return res;
}
    
crow::response make_success(const crow::json::rvalue& id, int code, const crow::json::wvalue& result) {
    crow::json::wvalue body = {
        {"jsonrpc", "2.0"},
        {"result", result},
        {"id", id}
    };
    crow::response res {};
    res.code = 200;
    res.body = body.dump();
    return res;
}

JsonServer::JsonServer()
: handlers_()
{}

void JsonServer::handle_request(crow::request& req, crow::response& res, framework::JsonRpcValidationMiddleware::context& ctx) {
    auto it = handlers_.find(ctx.method);
    if (it != handlers_.end()) {
        it->second(req, res, ctx.params, ctx.id);
    } else {
        JsonUtil::send_error(res, -32601, "Method not found", ctx.id);
    }
}

} // namespace framework
