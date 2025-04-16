#pragma once

#include <crow.h>
#include <string>
#include <map>
#include <memory>
#include "framework/json_rpc_validation.h"
#include "api/ping.h"
#include <rfl/json.hpp>
#include <rfl.hpp>


namespace framework {

 crow::response make_error(const crow::json::rvalue& id,int code, const crow::json::wvalue& error_response);
 crow::response make_success(const crow::json::rvalue& id, int code, const crow::json::wvalue& result);

template<typename T>
void json_handle_request_wrapper(T& handler, crow::request& req, crow::response& res, const crow::json::rvalue& params, const crow::json::rvalue& id) {
    crow::json::wvalue my_wvalue(params);
    std::string as = my_wvalue.dump();
    auto request_params = rfl::json::read<typename T::request_t>(as).value();        
    typename T::combined_response_t response_out;
    auto code = handler.handle(request_params, response_out);
    if (std::holds_alternative<typename T::response_t>(response_out)) {
        std::string json = rfl::json::write(std::get<typename T::response_t>(response_out));
        auto result = crow::json::load(json);
        res = framework::make_success(id, code, result);
        res.end();
    } else {
        std::string json = rfl::json::write(std::get<typename T::error_response_t>(response_out));
        auto result = crow::json::load(json);
        res = framework::make_error(id, code, result);
        res.end();
    }
}

#define REGISTER_HANDLER(METHOD, HANDLER) handlers_[METHOD] = [this](crow::request& req, crow::response& res, const crow::json::rvalue& params, const crow::json::rvalue& id) { \
    return framework::json_handle_request_wrapper<>(this->HANDLER, req, res, params, id); \
}

class JsonServer {
private:
    using handler_t = std::function<void(crow::request&, crow::response&, const crow::json::rvalue&, const crow::json::rvalue&)>;

protected:
    std::map<std::string, handler_t> handlers_;

public:
    JsonServer();
    void handle_request(crow::request& req, crow::response& res, framework::JsonRpcValidationMiddleware::context& ctx);
};

} // namespace framework