#pragma once

#include <crow.h>
#include <string>
#include <map>
#include <memory>
#include "api/handler.h"
#include "middleware/json_rpc_validation.h"

class Server {
private:
    std::map<std::string, std::unique_ptr<api::Handler>> handlers_;

public:
    Server();
    void handle_request(crow::request& req, crow::response& res, middleware::JsonRpcValidationMiddleware::context& ctx);
};