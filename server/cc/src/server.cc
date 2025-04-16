#include "server.h"
#include "api/ping.h"
#include "jsonutil.h"
#include <rfl/json.hpp>
#include <rfl.hpp>
#include <crow.h>
Server::Server(): handlers_() {
    // Register API handlers
    handlers_["Ping"] = [](crow::request& req, crow::response& res, const crow::json::rvalue& params, const crow::json::rvalue& id) {
        //std::string params_str = params.dump();
        crow::json::wvalue my_wvalue(params);
        std::string as = my_wvalue.dump();
        auto request_params = rfl::json::read<api::PingHandler::request_t>(as).value();
        api::PingHandler().handle(req, res, request_params, id);
    };
}

void Server::handle_request(crow::request& req, crow::response& res, middleware::JsonRpcValidationMiddleware::context& ctx) {
    auto it = handlers_.find(ctx.method);
    if (it != handlers_.end()) {
        it->second(req, res, ctx.params, ctx.id);
    } else {
        JsonUtil::send_error(res, -32601, "Method not found", ctx.id);
    }
}
