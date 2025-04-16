#include <crow.h>
#include <crow/middlewares/cors.h>
#include "server.h"

int main() {
    crow::App<middleware::JsonRpcValidationMiddleware> app;
    Server server;

    app.loglevel(crow::LogLevel::Debug);

    // Define the public JSON-RPC endpoint
    CROW_ROUTE(app, "/public")
        .CROW_MIDDLEWARES(app, middleware::JsonRpcValidationMiddleware)
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<middleware::JsonRpcValidationMiddleware>(req);
            server.handle_request(req, res, ctx);
        });

    // Define the private JSON-RPC endpoint
    CROW_ROUTE(app, "/private")
    .CROW_MIDDLEWARES(app, middleware::JsonRpcValidationMiddleware)
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<middleware::JsonRpcValidationMiddleware>(req);
            server.handle_request(req, res, ctx);
        });

    // Set the server to listen on port 9001
    app.port(9001).multithreaded().run();
    
    return 0;
} 