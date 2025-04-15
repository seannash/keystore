#include <crow.h>
#include <crow/middlewares/cors.h>
#include <string>
#include <map>
#include "api/ping.h"

// Middleware to handle JSON-RPC validation
struct JsonRpcValidationMiddleware : public crow::ILocalMiddleware {
    struct context {
        crow::json::rvalue json;
        std::string method;
        crow::json::rvalue params;
        crow::json::rvalue id;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        try {
            ctx.json = crow::json::load(req.body);
            if (!ctx.json) {
                crow::json::wvalue error_response;
                error_response["jsonrpc"] = "2.0";
                error_response["error"] = {
                    {"code", -32700},
                    {"message", "Parse error"},
                    {"data", "Invalid JSON"}
                };
                error_response["id"] = crow::json::load("null");
                res.code = 400;
                res.body = error_response.dump();
                res.end();
                return;
            }

            // Validate JSON-RPC 2.0 request
            if (!ctx.json.has("jsonrpc") || ctx.json["jsonrpc"].s() != "2.0") {
                crow::json::wvalue error_response;
                error_response["jsonrpc"] = "2.0";
                error_response["error"] = {
                    {"code", -32600},
                    {"message", "Invalid Request"},
                    {"data", "Invalid JSON-RPC version"}
                };
                error_response["id"] = ctx.json.has("id") ? ctx.json["id"] : crow::json::load("null");
                res.code = 400;
                res.body = error_response.dump();
                res.end();
                return;
            }

            if (!ctx.json.has("method")) {
                crow::json::wvalue error_response;
                error_response["jsonrpc"] = "2.0";
                error_response["error"] = {
                    {"code", -32600},
                    {"message", "Invalid Request"},
                    {"data", "Missing method"}
                };
                error_response["id"] = ctx.json.has("id") ? ctx.json["id"] : crow::json::load("null");
                res.code = 400;
                res.body = error_response.dump();
                res.end();
                return;
            }

            if (!ctx.json.has("params")) {
                crow::json::wvalue error_response;
                error_response["jsonrpc"] = "2.0";
                error_response["error"] = {
                    {"code", -32600},
                    {"message", "Invalid Request"},
                    {"data", "Missing params"}
                };
                error_response["id"] = ctx.json.has("id") ? ctx.json["id"] : crow::json::load("null");
                res.code = 400;
                res.body = error_response.dump();
                res.end();
                return;
            }

            if (!ctx.json.has("id")) {
                crow::json::wvalue error_response;
                error_response["jsonrpc"] = "2.0";
                error_response["error"] = {
                    {"code", -32600},
                    {"message", "Invalid Request"},
                    {"data", "Missing id"}
                };
                error_response["id"] = crow::json::load("null");
                res.code = 400;
                res.body = error_response.dump();
                res.end();
                return;
            }

            ctx.method = ctx.json["method"].s();
            ctx.params = ctx.json["params"];
            ctx.id = ctx.json["id"];
        }
        catch (const std::exception& e) {
            crow::json::wvalue error_response;
            error_response["jsonrpc"] = "2.0";
            error_response["error"] = {
                {"code", -32603},
                {"message", "Internal error"},
                {"data", e.what()}
            };
            error_response["id"] = crow::json::load("null");
            res.code = 500;
            res.body = error_response.dump();
            res.end();
        }
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx) {
        // Nothing to do after handle
    }
};

class ApiServer {
private:
    std::map<std::string, std::unique_ptr<api::Handler>> handlers_;

public:
    ApiServer() {
        // Register API handlers
        handlers_["Ping"] = std::make_unique<api::PingHandler>();
    }

    void handle_request(crow::request& req, crow::response& res, JsonRpcValidationMiddleware::context& ctx) {
        auto it = handlers_.find(ctx.method);
        if (it != handlers_.end()) {
            it->second->handle(req, res, ctx.params, ctx.id);
        } else {
            api::Handler::send_error(res, -32601, "Method not found", ctx.id);
        }
    }
};

int main() {
    crow::App<JsonRpcValidationMiddleware> app;
    ApiServer api_server;

    // Define the public JSON-RPC endpoint
    CROW_ROUTE(app, "/public")
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<JsonRpcValidationMiddleware>(req);
            api_server.handle_request(req, res, ctx);
        });

    // Define the private JSON-RPC endpoint
    CROW_ROUTE(app, "/private")
        .methods("POST"_method)
        ([&](crow::request& req, crow::response& res) {
            auto& ctx = app.get_context<JsonRpcValidationMiddleware>(req);
            api_server.handle_request(req, res, ctx);
        });

    // Set the server to listen on port 9001
    app.port(9001).multithreaded().run();
    
    return 0;
} 