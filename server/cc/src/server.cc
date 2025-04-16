#include "server.h"

#include "jsonutil.h"
#include <rfl/json.hpp>
#include <rfl.hpp>
#include <crow.h>

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

template<typename T>
void json_handle_request_wrapper(T& handler, crow::request& req, crow::response& res, const crow::json::rvalue& params, const crow::json::rvalue& id) {
    crow::json::wvalue my_wvalue(params);
    std::string as = my_wvalue.dump();
    auto request_params = rfl::json::read<typename T::request_t>(as).value();        
    typename T::combined_response_t response_out;
    auto code = handler.handle(req, res, request_params, response_out);
    if (std::holds_alternative<typename T::response_t>(response_out)) {
        std::string json = rfl::json::write(std::get<typename T::response_t>(response_out));
        auto result = crow::json::load(json);
        res = make_success(id, code, result);
        res.end();
    } else {
        std::string json = rfl::json::write(std::get<typename T::error_response_t>(response_out));
        auto result = crow::json::load(json);
        res = make_error(id, code, result);
        res.end();
    }
}

#define REGISTER_HANDLER(METHOD, HANDLER) handlers_[METHOD] = [this](crow::request& req, crow::response& res, const crow::json::rvalue& params, const crow::json::rvalue& id) { \
    return json_handle_request_wrapper<>(this->HANDLER, req, res, params, id); \
}

Server::Server()
: handlers_()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}

void Server::handle_request(crow::request& req, crow::response& res, middleware::JsonRpcValidationMiddleware::context& ctx) {
    auto it = handlers_.find(ctx.method);
    if (it != handlers_.end()) {
        it->second(req, res, ctx.params, ctx.id);
    } else {
        JsonUtil::send_error(res, -32601, "Method not found", ctx.id);
    }
}
