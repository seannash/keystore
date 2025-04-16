#include <jsonutil.h>

#include <crow.h>

namespace JsonUtil {

void send_error(crow::response& res, int code, const std::string& message, 
                          const crow::json::rvalue& id, const std::string& data) {
        crow::json::wvalue error_response;
        error_response["jsonrpc"] = "2.0";
        error_response["error"] = {
            {"code", code},
            {"message", message}
        };
        if (!data.empty()) {
            error_response["error"]["data"] = data;
        }
        error_response["id"] = id;
        res.code = (code == -32601) ? 404 : 400; // Method not found gets 404, others get 400
        res.body = error_response.dump();
        res.end();
    }
    
void send_success(crow::response& res, const crow::json::wvalue& result, 
                           const crow::json::rvalue& id) {
        crow::json::wvalue response = {
            {"jsonrpc", "2.0"},
            {"result", result},
            {"id", id}
        };
        res.code = 200;
        res.body = response.dump();
        res.end();
    }
} // namespace JsonUtil