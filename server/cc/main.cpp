#include <crow.h>
#include <string>

int main() {
    crow::SimpleApp app;

    // Define the Ping endpoint
    CROW_ROUTE(app, "/ping")
        .methods("POST"_method)
        ([](const crow::request& req) {
            try {
                auto json = crow::json::load(req.body);
                if (!json) {
                    return crow::response(400, "Invalid JSON");
                }

                if (!json.has("message")) {
                    return crow::response(400, "Missing 'message' parameter");
                }

                std::string message = json["message"].s();
                
                // Create AWS JSON 2.0 response
                crow::json::wvalue response;
                response["message"] = message;
                
                return crow::response(200, response);
            }
            catch (const std::exception& e) {
                return crow::response(500, "Internal server error");
            }
        });

    // Set the server to listen on port 9001
    app.port(9001).multithreaded().run();
    
    return 0;
} 