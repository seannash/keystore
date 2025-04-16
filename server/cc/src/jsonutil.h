#pragma once

#include <crow.h>
#include <string>

namespace JsonUtil {

void send_error(crow::response& res, int code, const std::string& message, 
                          const crow::json::rvalue& id, const std::string& data = "");
void send_success(crow::response& res, const crow::json::wvalue& result, const crow::json::rvalue& id);

};
