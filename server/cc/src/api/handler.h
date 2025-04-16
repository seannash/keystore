#pragma once

#include <crow.h>
#include <string>

namespace api {

class Handler {
public:
    virtual ~Handler() = default;

    // Pure virtual function that all API handlers must implement
    virtual void handle(crow::request& req, crow::response& res, 
                       const crow::json::rvalue& params, 
                       const crow::json::rvalue& id) = 0;

 
};

} // namespace api 