#include "json_rpc_validation.h"

namespace framework {

void JsonRpcValidationMiddleware::before_handle(crow::request& req, crow::response& res, context& ctx) {
    try {
        ctx.json = crow::json::load(req.body);
        ctx.id = crow::json::load("42");
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

void JsonRpcValidationMiddleware::after_handle(crow::request& req, crow::response& res, context& ctx) {
    // Nothing to do after handle
}

} // namespace framework 