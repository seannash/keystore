#include <crow.h>
#include "api/ping.h"
#include "framework/jsonserver.h"
#include "framework/json_rpc_validation.h"
#include "jsonutil.h"

int main() {
    crow::App<framework::JsonRpcValidationMiddleware> app;
    framework::JsonServer server;

    app.loglevel(crow::LogLevel::Debug);

    // Define the public JSON-RPC endpoint
    CROW_ROUTE(app, "/public")
        .CROW_MIDDLEWARES(app, framework::JsonRpcValidationMiddleware)
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<framework::JsonRpcValidationMiddleware>(req);
            server.handle_request(req, res, ctx);
        });

    // Define the private JSON-RPC endpoint
    CROW_ROUTE(app, "/private")
    .CROW_MIDDLEWARES(app, framework::JsonRpcValidationMiddleware)
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<framework::JsonRpcValidationMiddleware>(req);
            server.handle_request(req, res, ctx);
        });

    // Set the server to listen on port 9001
    app.port(9001).multithreaded().run();
    
    return 0;
} 