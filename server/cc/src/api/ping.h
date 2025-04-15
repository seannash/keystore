#pragma once

#include <crow.h>
#include "handler.h"

namespace api {

class PingHandler : public Handler {
public:
    void handle(crow::request& req, crow::response& res, 
                const crow::json::rvalue& params, 
                const crow::json::rvalue& id) override;
};

} // namespace api 