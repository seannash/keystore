#pragma once

#include <crow.h>
#include <string>
#include <map>
#include <memory>
#include "middleware/json_rpc_validation.h"

class Server {
private:
    using handler_t = std::function<void(crow::request&, crow::response&, const crow::json::rvalue&, const crow::json::rvalue&)>;
    std::map<std::string, handler_t> handlers_;

public:
    Server();
    void handle_request(crow::request& req, crow::response& res, middleware::JsonRpcValidationMiddleware::context& ctx);
};