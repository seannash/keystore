#pragma once

#include "crow.h"
#include "json_rpc_validation.h"

namespace framework {

template<typename PublicServer, typename PrivateServer>
class GenericApp {
private:
    crow::App<framework::JsonRpcValidationMiddleware> app;
    PublicServer public_server;
    PrivateServer private_server;
public:
    GenericApp(crow::LogLevel loglevel);
    void run(int port);
};

template<typename PublicServer, typename PrivateServer>
void GenericApp<PublicServer, PrivateServer>::run(int port) {
    app.port(port).multithreaded().run();
}

template<typename PublicServer, typename PrivateServer>
GenericApp<PublicServer, PrivateServer>::GenericApp(crow::LogLevel loglevel) {
    app.loglevel(loglevel);
        // Define the public JSON-RPC endpoint
    CROW_ROUTE(app, "/public")
        .CROW_MIDDLEWARES(app, framework::JsonRpcValidationMiddleware)
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<framework::JsonRpcValidationMiddleware>(req);
            public_server.handle_request(req, res, ctx);
        });

    // Define the private JSON-RPC endpoint
    CROW_ROUTE(app, "/private")
    .CROW_MIDDLEWARES(app, framework::JsonRpcValidationMiddleware)
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<framework::JsonRpcValidationMiddleware>(req);
            private_server.handle_request(req, res, ctx);
        });
}

} // namespace framework