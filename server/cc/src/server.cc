#include "server.h"
#include "api/ping.h"
#include "jsonutil.h"

Server::Server(): handlers_() {
    // Register API handlers
    handlers_["Ping"] = std::make_unique<api::PingHandler>();
}

void Server::handle_request(crow::request& req, crow::response& res, middleware::JsonRpcValidationMiddleware::context& ctx) {
    auto it = handlers_.find(ctx.method);
    if (it != handlers_.end()) {
        it->second->handle(req, res, ctx.params, ctx.id);
    } else {
        JsonUtil::send_error(res, -32601, "Method not found", ctx.id);
    }
}
