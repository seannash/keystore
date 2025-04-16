#pragma once

#include <crow.h>
#include <string>

namespace middleware {

class JsonRpcValidationMiddleware : public crow::ILocalMiddleware {
public:
    struct context {
        crow::json::rvalue json;
        std::string method;
        crow::json::rvalue params;
        crow::json::rvalue id;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

} // namespace middleware 