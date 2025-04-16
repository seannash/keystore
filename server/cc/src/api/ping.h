#pragma once

#include <crow.h>
#include <string>

namespace api {

class PingHandler {
public:
    struct request_t {
        std::string message;
    };

    void handle(crow::request& req, crow::response& res, 
                const request_t& params, 
                const crow::json::rvalue& id);
};

} // namespace api 