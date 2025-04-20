#pragma once

#include <crow.h>
#include <string>
#include <memory>
#include <unordered_map>

namespace framework {

class OAuthMiddleware : public crow::ILocalMiddleware {
public:
    struct OAuthConfig {
        std::string client_id;
        std::string client_secret;
        std::string redirect_uri;
        std::string auth_endpoint;
        std::string token_endpoint;
        std::string scope;
    };

    struct context {
        std::string token;
    };

    explicit OAuthMiddleware(const OAuthConfig& config);
    ~OAuthMiddleware() = default;

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);

private:
    bool validate_token(const std::string& token);
    std::string get_auth_url() const;
    std::string exchange_code_for_token(const std::string& code);

    OAuthConfig config_;
    std::unordered_map<std::string, std::string> token_cache_;
};

} // namespace framework 