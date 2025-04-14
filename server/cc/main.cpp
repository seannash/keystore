#include <crow.h>
#include <string>

int main() {
    crow::SimpleApp app;

    // Define the JSON-RPC endpoint
    CROW_ROUTE(app, "/")
        .methods("POST"_method)
        ([](const crow::request& req) {
            try {
                auto json = crow::json::load(req.body);
                if (!json) {
                    return crow::response(400, "Invalid JSON");
                }

                // Validate JSON-RPC 2.0 request
                if (!json.has("jsonrpc") || json["jsonrpc"].s() != "2.0") {
                    return crow::response(400, "Invalid JSON-RPC version");
                }
                if (!json.has("method")) {
                    return crow::response(400, "Missing method");
                }
                if (!json.has("params")) {
                    return crow::response(400, "Missing params");
                }
                if (!json.has("id")) {
                    return crow::response(400, "Missing id");
                }

                std::string method = json["method"].s();
                auto params = json["params"];
                auto id = json["id"];

                // Handle Ping method
                if (method == "Ping") {
                    if (!params.has("message")) {
                        crow::json::wvalue error_response;
                        error_response["jsonrpc"] = "2.0";
                        error_response["error"] = {
                            {"code", -32602},
                            {"message", "Invalid params"},
                            {"data", "Missing 'message' parameter"}
                        };
                        error_response["id"] = id;
                        return crow::response(400, error_response);
                    }

                    std::string message = params["message"].s();
                    
                    // Create JSON-RPC 2.0 response
                    crow::json::wvalue response;
                    response["jsonrpc"] = "2.0";
                    response["result"] = {
                        {"message", message}
                    };
                    response["id"] = id;
                    
                    return crow::response(200, response);
                } else {
                    // Method not found
                    crow::json::wvalue error_response;
                    error_response["jsonrpc"] = "2.0";
                    error_response["error"] = {
                        {"code", -32601},
                        {"message", "Method not found"}
                    };
                    error_response["id"] = id;
                    return crow::response(404, error_response);
                }
            }
            catch (const std::exception& e) {
                crow::json::wvalue error_response;
                error_response["jsonrpc"] = "2.0";
                error_response["error"] = {
                    {"code", -32603},
                    {"message", "Internal error"},
                    {"data", e.what()}
                };
                error_response["id"] = nullptr; // null id for internal errors
                return crow::response(500, error_response);
            }
        });

    // Set the server to listen on port 9001
    app.port(9001).multithreaded().run();
    
    return 0;
} 